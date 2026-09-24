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
foc_q15_t angle_error_q15;

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
    // ===== 第1步：电流误差 =====
    static uint16_t lfp_cnt = 0;
    float lpf, cos_obs, sin_obs;
    float err_alpha = motor->i_ab_hat.alpha - motor->i_ab.alpha;
    float err_beta  = motor->i_ab_hat.beta  - motor->i_ab.beta;
    
    float z_alpha = SMO_K_PU * FOC_sat(err_alpha, SMO_SAT_BOUNDARY_PU);
    float z_beta  = SMO_K_PU * FOC_sat(err_beta, SMO_SAT_BOUNDARY_PU);
    
    // ===== 第3步：电流观测器迭代 =====
    // Î[k+1] = a·Î[k] + b·(U[k] - Z[k])
    motor->i_ab_hat.alpha = SMO_A * motor->i_ab_hat.alpha 
                       + SMO_B * (motor->u_ab.alpha - z_alpha);
    motor->i_ab_hat.beta  = SMO_A * motor->i_ab_hat.beta  
                       + SMO_B * (motor->u_ab.beta  - z_beta);
    
    // ===== 第4步：BEMF = 切换项的低通滤波 =====
    #if FOC_PLL_ENABLE
    float speed_rpm = FOC_AbsElecRadPerSecToMechRpm(motor->speed_observer);
    #else
    float speed_rpm = (motor->speed >= 0.0f) ? motor->speed : -motor->speed;
    #endif // FOC_PLL_ENABLE
    
    lfp_cnt++;
    if(lfp_cnt >= 10)
    {
        lpf = FOC_calc_dynamic_lpf(speed_rpm);
        lfp_cnt = 0;
    }
        
    motor->e_ab.alpha += (z_alpha - motor->e_ab.alpha) * lpf;
    motor->e_ab.beta  += (z_beta  - motor->e_ab.beta)  * lpf;

    // ===== 第5步：PLL=====
    #if FOC_PLL_ENABLE

    float theta_comp = motor->theta_Observer - calc_compensation_angle(motor->speed_observer);
    FOC_GetSinCos(theta_comp, &sin_obs, &cos_obs);

    float speed_sign = (motor->speed_observer >= 0.0f) ? 1.0f : -1.0f;
    angle_error = -motor->e_ab.alpha * cos_obs - motor->e_ab.beta  * sin_obs;
    angle_error *= speed_sign;

    float e_amp = FOC_FastNorm(motor->e_ab.alpha, motor->e_ab.beta);
    
    if (e_amp > SMO_E_AMP_MIN) {
        angle_error /= e_amp; 
    } else if (e_amp > SMO_E_AMP_LOW) {
        angle_error = angle_error / SMO_E_AMP_MIN * (e_amp / SMO_E_AMP_MIN);
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

/**
 * @brief SMO观测器(q15)的算法
 * 
 * @param motor 电机结构体
 * @param dt 单位时间
 * @param mode 当前旋转模式是开环还是闭环
 */
void SMO_Observer_fx(foc_handle_t *motor, float dt, foc_mode_t mode)
{
    // ===== 第1步：电流误差 =====
    static uint16_t lfp_cnt = 0;
    foc_q15_t lpf;
    float cos_obs, sin_obs;
    foc_q15_t err_alpha_q15 = motor->i_ab_hat_fx.alpha - motor->i_ab_fx.alpha;
    foc_q15_t err_beta_q15  = motor->i_ab_hat_fx.beta  - motor->i_ab_fx.beta;
    
    foc_q15_t z_alpha_q15 = FOC_Q15Mul(SMO_K_Q15, FOC_sat_fx(err_alpha_q15, SMO_SAT_BOUNDARY_Q15));
    foc_q15_t z_beta_q15  = FOC_Q15Mul(SMO_K_Q15, FOC_sat_fx(err_beta_q15, SMO_SAT_BOUNDARY_Q15));
    
    // ===== 第3步：电流观测器迭代 =====
    // Î[k+1] = a·Î[k] + b·(U[k] - Z[k])
    motor->i_ab_hat_fx.alpha = FOC_Q15Mul(SMO_A_Q15, motor->i_ab_hat_fx.alpha) 
                       + FOC_Q15Mul(SMO_B_Q15, (motor->u_ab_fx.alpha - z_alpha_q15));
    motor->i_ab_hat_fx.beta  = FOC_Q15Mul(SMO_A_Q15, motor->i_ab_hat_fx.beta)  
                       + FOC_Q15Mul(SMO_B_Q15, (motor->u_ab_fx.beta  - z_beta_q15));
    
    // ===== 第4步：BEMF = 切换项的低通滤波 =====
    #if FOC_PLL_ENABLE
    foc_q15_t speed_rpm = FOC_AbsElecRadPerSecToMechRpm_fx(motor->speed_observer_fx);
    #else
    float speed_rpm = (motor->speed >= 0.0f) ? motor->speed : -motor->speed;
    #endif // FOC_PLL_ENABLE
    
    lfp_cnt++;
    if(lfp_cnt >= 10)
    {
        lpf = FOC_calc_dynamic_lpf_fx(speed_rpm);
        lfp_cnt = 0;
    }
        
    motor->e_ab_fx.alpha += (z_alpha_q15 - motor->e_ab_fx.alpha) * lpf;
    motor->e_ab_fx.beta  += (z_beta_q15  - motor->e_ab_fx.beta)  * lpf;

    // ===== 第5步：PLL=====
    #if FOC_PLL_ENABLE

    foc_q15_t theta_comp = motor->theta_Observer_fx - calc_compensation_angle_fx(motor->speed_observer_fx, lpf);
    foc_Trig_Components trig = FOC_Trig_Functions(theta_comp);

    uint8_t speed_sign = (motor->speed_observer_fx >= 0) ? 1 : -1;
    angle_error_q15 = -motor->e_ab_fx.alpha * trig.hCos - motor->e_ab_fx.beta  * trig.hSin;
    angle_error_q15 *= speed_sign;

    foc_q15_t e_amp = FOC_FastNorm_fx(motor->e_ab_fx.alpha, motor->e_ab_fx.beta);
    
    if (e_amp > SMO_E_AMP_MIN_Q15) {
        angle_error_q15 /= e_amp;
    } else if (e_amp > SMO_E_AMP_LOW_Q15) {
        angle_error_q15 = angle_error_q15 / FOC_Q15Mul(SMO_E_AMP_MIN_Q15, (e_amp / SMO_E_AMP_MIN_Q15));
    } else {
        angle_error_q15 = 0;
    }
    
    SMO_PLL_Update_Fx(motor, angle_error_q15, mode);

    #endif // FOC_PLL_ENABLE
}

void SMO_PLL_Update_Fx(foc_handle_t *motor, int16_t angle_error_q15, foc_mode_t mode)
{
    int32_t integral_delta, p_term_q16, speed_raw_q16;
    int32_t diff_q16, filtered_delta, theta_inc;

    /* ===== 1. 积分器 ===== */
    // integral += angle_error × PLL_KI × dt
    // Q16 增量 = ang_err_q15 × PLL_KI_DT_Q16 >> 15
    integral_delta = ((int32_t)angle_error_q15 * PLL_KI_DT_Q16) >> 15;
    motor->pi_pll_integral_q16 += integral_delta;

    // 积分限幅
    if (motor->pi_pll_integral_q16 >  OB_SPEED_LIMIT_Q16)
        motor->pi_pll_integral_q16 =  OB_SPEED_LIMIT_Q16;
    else if (motor->pi_pll_integral_q16 < -OB_SPEED_LIMIT_Q16)
        motor->pi_pll_integral_q16 = -OB_SPEED_LIMIT_Q16;

    /* ===== 2. 比例项 + 求和 ===== */
    // p_term_q16 = ang_err_q15 × PLL_KP_Q16 >> 15
    p_term_q16 = (int32_t)(((int64_t)angle_error_q15 * PLL_KP_Q16) >> 15);
    speed_raw_q16 = p_term_q16 + motor->pi_pll_integral_q16;

    /* ===== 3. 速度低通滤波 ===== */
    // speed_observer += (speed_raw - speed_observer) × LPF
    diff_q16 = speed_raw_q16 - motor->speed_observer_q16;
    filtered_delta = (int32_t)(((int64_t)diff_q16 * SPEED_OBS_LPF_Q15) >> 15);
    motor->speed_observer_q16 += filtered_delta;

    // 速度限幅
    if (motor->speed_observer_q16 >  OB_SPEED_LIMIT_Q16)
        motor->speed_observer_q16 =  OB_SPEED_LIMIT_Q16;
    else if (motor->speed_observer_q16 < -OB_SPEED_LIMIT_Q16)
        motor->speed_observer_q16 = -OB_SPEED_LIMIT_Q16;

    /* ===== 4. 角度积分 ===== */
    // theta += omega × dt，turn-domain 用 int16_t 自然回绕
    // Q16 速度 → Q16 turn 增量：
    //   theta_inc = omega_q16 × TS / (2π)  （单位：turn，1.0 = 2π）
    //   转成 int16_t turn-domain（1.0 = 65536）：
    //   theta_inc_fx = omega_q16 × TS / (2π) × 65536
    //                = omega_q16 × 34185 / 2^32
    theta_inc = (int32_t)(((int64_t)motor->speed_observer_q16 * PLL_THETA_INC_K_Q32) >> 32);
    motor->theta_observer_fx += (int16_t)theta_inc;  // 自动 mod 2π

    /* ===== 5. 更新浮点影子（可选）===== */
    motor->pi_pll.integral  = motor->pi_pll_integral_q16  * (1.0f / 65536.0f);
    motor->speed_observer   = motor->speed_observer_q16   * (1.0f / 65536.0f);
    motor->theta_Observer   = motor->theta_observer_fx * (2.0f * PI / 65536.0f);
    motor->speed = FOC_ElecRadPerSecToMechRpm(motor->speed_observer);

    if (mode == MOTOR_STATE_CLOSE)
        motor->theta = motor->theta_Observer;
}

