/**
 * @file smo.c
 * @author MING
 * @brief 滑膜观测器的算法主要在这个文件之中
 * @version 1.0
 * @date 2026-04-23
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "smo.h"

float angle_error;

/**
 * @brief BEMF观测器的算法
 * 
 * @param motor 电机结构体
 * @param dt 单位时间
 * @param mode 当前旋转模式是开环还是闭环
 */
void BEMF_Observer(foc_handle_t *motor, float dt, foc_mode_t mode)
{
    const float motor_r_pu = MOTOR_R * FOC_CURRENT_BASE_A / FOC_VOLTAGE_BASE_V;
    const float e_amp_min = FOC_VoltageToPu(0.5f);
    const float e_amp_low = FOC_VoltageToPu(0.1f);
    float e_alpha_raw = motor->u_ab.alpha - motor_r_pu * motor->i_ab.alpha;
    float e_beta_raw  = motor->u_ab.beta  - motor_r_pu * motor->i_ab.beta;
    
    motor->e_ab.alpha += (e_alpha_raw - motor->e_ab.alpha) * BEMF_LPF;
    motor->e_ab.beta  += (e_beta_raw  - motor->e_ab.beta)  * BEMF_LPF;
    
    float cos_obs;
    float sin_obs;
    FOC_GetSinCos(motor->theta_Observer, &sin_obs, &cos_obs);
    angle_error = -motor->e_ab.alpha * cos_obs - motor->e_ab.beta * sin_obs;

    float e_amp = FOC_FastNorm(motor->e_ab.alpha, motor->e_ab.beta);
    
    if (e_amp > e_amp_min)
    {
        angle_error /= e_amp;
    }
    else if (e_amp > e_amp_low)
    {
        angle_error = angle_error / e_amp_min * (e_amp / e_amp_min);
    }
    else
    {
        angle_error = 0.0f;
    }
    
    // pll锁相环
    motor->pi_pll.integral += angle_error * PLL_KI * dt;
    
    // 积分限幅
    if(motor->pi_pll.integral >  OB_SPEED_LIMIT) motor->pi_pll.integral =  OB_SPEED_LIMIT;
    if(motor->pi_pll.integral < -OB_SPEED_LIMIT) motor->pi_pll.integral = -OB_SPEED_LIMIT;
    
    // 速度低通滤波
    float speed_raw = PLL_KP * angle_error + motor->pi_pll.integral;
    motor->speed_observer += (speed_raw - motor->speed_observer) * 0.30f;
    
    // 观测器估测速度限幅
    if(motor->speed_observer >  OB_SPEED_LIMIT) motor->speed_observer =  OB_SPEED_LIMIT;
    if(motor->speed_observer < -OB_SPEED_LIMIT) motor->speed_observer = -OB_SPEED_LIMIT;
    
    motor->theta_Observer += motor->speed_observer * dt;
    motor->theta_Observer = FOC_fmod(&motor->theta_Observer, _2_PI);
    if(motor->theta_Observer < 0) motor->theta_Observer += _2_PI;
    
    if(mode == MOTOR_STATE_CLOSE)
        motor->theta = motor->theta_Observer;
    
    motor->speed = FOC_ElecRadPerSecToMechRpm(motor->speed_observer);
}

/**
 * @brief SMO观测器的算法
 * 
 * @param motor 电机结构体
 * @param dt 单位时间
 * @param mode 当前旋转模式是开环还是闭环
 */
void SMO_Observer(foc_handle_t *motor, float dt, foc_mode_t mode)
{
    const float a = 1.0f - MOTOR_R * dt / MOTOR_L;
    const float b = dt * FOC_VOLTAGE_BASE_V / (MOTOR_L * FOC_CURRENT_BASE_A);
    const float smo_k_pu = FOC_VoltageToPu(SMO_K);
    const float sat_boundary_pu = FOC_CurrentToPu(SAT_BOUNDARY);
    const float e_amp_min = FOC_VoltageToPu(0.5f);
    const float e_amp_low = FOC_VoltageToPu(0.1f);
    
    // ===== 第1步：电流误差 =====
    float err_alpha = motor->i_ab_hat.alpha - motor->i_ab.alpha;
    float err_beta  = motor->i_ab_hat.beta  - motor->i_ab.beta;
    
    float z_alpha = smo_k_pu * FOC_sat(err_alpha, sat_boundary_pu);
    float z_beta  = smo_k_pu * FOC_sat(err_beta, sat_boundary_pu);
    
    // ===== 第3步：电流观测器迭代 =====
    // Î[k+1] = a·Î[k] + b·(U[k] - Z[k])
    motor->i_ab_hat.alpha = a * motor->i_ab_hat.alpha 
                       + b * (motor->u_ab.alpha - z_alpha);
    motor->i_ab_hat.beta  = a * motor->i_ab_hat.beta  
                       + b * (motor->u_ab.beta  - z_beta);
    
    // ===== 第4步：BEMF = 切换项的低通滤波 =====
    #if FOC_PLL_ENABLE
    float speed_rpm = FOC_AbsElecRadPerSecToMechRpm(motor->speed_observer);
    #else
    float speed_rpm = (motor->speed >= 0.0f) ? motor->speed : -motor->speed;
    #endif // FOC_PLL_ENABLE
    
    motor->e_ab.alpha += (z_alpha - motor->e_ab.alpha) * FOC_calc_dynamic_lpf(speed_rpm);
    motor->e_ab.beta  += (z_beta  - motor->e_ab.beta)  * FOC_calc_dynamic_lpf(speed_rpm);

    // ===== 第5步：PLL=====
    #if FOC_PLL_ENABLE

    float theta_comp = motor->theta_Observer - calc_compensation_angle(motor->speed_observer);
    float cos_obs;
    float sin_obs;
    FOC_GetSinCos(theta_comp, &sin_obs, &cos_obs);

    float speed_sign = (motor->speed_observer >= 0.0f) ? 1.0f : -1.0f;
    angle_error = -motor->e_ab.alpha * cos_obs - motor->e_ab.beta  * sin_obs;
    angle_error *= speed_sign;

    float e_amp = FOC_FastNorm(motor->e_ab.alpha, motor->e_ab.beta);
    
    if (e_amp > e_amp_min) {
        angle_error /= e_amp;
    } else if (e_amp > e_amp_low) {
        angle_error = angle_error / e_amp_min * (e_amp / e_amp_min);
    } else {
        angle_error = 0.0f;
    }
    
    // pll锁相环
    motor->pi_pll.integral += angle_error * PLL_KI * dt;
    
    // 积分限幅
    if(motor->pi_pll.integral >  OB_SPEED_LIMIT) motor->pi_pll.integral =  OB_SPEED_LIMIT;
    if(motor->pi_pll.integral < -OB_SPEED_LIMIT) motor->pi_pll.integral = -OB_SPEED_LIMIT;
    
    // 速度低通滤波
    float speed_raw = PLL_KP * angle_error + motor->pi_pll.integral;
    motor->speed_observer += (speed_raw - motor->speed_observer) * SPEED_OBSERBER_LPF;
    
    // 观测器估测速度限幅
    if(motor->speed_observer >  OB_SPEED_LIMIT) motor->speed_observer =  OB_SPEED_LIMIT;
    if(motor->speed_observer < -OB_SPEED_LIMIT) motor->speed_observer = -OB_SPEED_LIMIT;
    
    motor->theta_Observer += motor->speed_observer * dt;
    motor->theta_Observer = FOC_fmod(&motor->theta_Observer, _2_PI);
    if(motor->theta_Observer < 0) motor->theta_Observer += _2_PI;
    
    if(mode == MOTOR_STATE_CLOSE)
        motor->theta = motor->theta_Observer;
    
    motor->speed = FOC_ElecRadPerSecToMechRpm(motor->speed_observer);

    #endif // FOC_PLL_ENABLE
}

