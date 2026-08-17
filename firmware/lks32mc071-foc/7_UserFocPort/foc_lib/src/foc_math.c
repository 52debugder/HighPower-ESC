/**
 * @file foc_math.c
 * @author MING
 * @brief foc有关计算函数，最新版本完善了动态相位补偿
 * @version 0.2
 * @date 2026-05-03
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "foc_math.h"

#define FOC_Q15_TO_FLOAT        (1.0f / 32768.0f)
#define FOC_RAD_TO_Q15_SCALE    (65536.0f / _2_PI)
#define FOC_FAST_NORM_GAIN      0.375f
#define FOC_INV_SQRT3           0.577350269f
#define FOC_HALF_VBUS_TO_PWM    (PWM_ARR / (2.0f * PWM_VBUS))
#define FOC_HALF_PWM_ARR        (PWM_ARR / 2.0f)
#define FOC_Q15_SHIFT           15
#define FOC_Q15_ONE             (1 << FOC_Q15_SHIFT)
#define FOC_Q15_ROUND           (1 << (FOC_Q15_SHIFT - 1))
#define FOC_CURRENT_TO_Q15      (32768.0f / CURRENT_LIMIT)
#define FOC_CURRENT_FROM_Q15    (CURRENT_LIMIT / 32768.0f)
#define FOC_VOLTAGE_TO_Q15      (32768.0f / CURRENT_PI_LIMIT)
#define FOC_VOLTAGE_FROM_Q15    (CURRENT_PI_LIMIT / 32768.0f)
#define FOC_Q15_SQRT3_2         28378
#define FOC_SVPWM_K_COUNT       ((int32_t)(CURRENT_PI_LIMIT * SQRT_3 * PWM_ARR / PWM_VBUS + 0.5f))
#define FOC_SVPWM_K             (0.95f * PWM_ARR)
// #define FOC_SVPWM_K             (SQRT_3 * PWM_ARR / PWM_VBUS)

static void FOC_PortDelayMs(uint16_t delay_ms)
{
    volatile uint32_t ticks;

    while (delay_ms-- > 0U)
    {
        for (ticks = 0U; ticks < 8000U; ticks++)
        {
        }
    }
}

static float FOC_Abs(float x)
{
    return (x >= 0.0f) ? x : -x;
}

static int32_t FOC_Q15Abs32(foc_q15_t value)
{
    return (value >= 0) ? value : -(int32_t)value;
}

static foc_q15_t FOC_Q15FromAccum(foc_accum_t value)
{
    return FOC_Q15Clamp(value);
}

static float FOC_FastAtan(float x)
{
    float ax = FOC_Abs(x);

    if (ax > 1.0f)
    {
        float inv = 1.0f / ax;
        float atan_inv = inv / (1.0f + 0.28f * inv * inv);
        float result = _PI_2 - atan_inv;
        return (x >= 0.0f) ? result : -result;
    }

    return x / (1.0f + 0.28f * x * x);
}

/**
 * @brief sat函数
 * 
 * @param x 
 * @param boundary 
 * @return float 
 */
float FOC_sat(float x, float boundary)
{
    if (x > boundary) return 1.0f;
    else if (x < -boundary) return -1.0f;
    else return x / boundary;
}

/**
 * @brief 动态反电动势低通滤波系数
 * 
 * @param speed_rpm 转速
 * @return float 滤波系数
 */
float FOC_calc_dynamic_lpf(float speed_rpm)
{
    float fe = FOC_Abs(FOC_MechRpmToElecRadPerSec(speed_rpm)) / FOC_TWO_PI_F;
    
    // 目标：截止频率 = 3~5 倍电频率
    float fc_target = 2.0f * fe;  
    
    // 限制范围
    if (fc_target < 80.0f)  fc_target = 80.0f;   // 最低100Hz
    if (fc_target > 800.0f) fc_target = 800.0f;   // 最高2000Hz 
    
    // 反算α。
    // fc = lfp × fs / (2π × (1-lfp))
    // lfp = 2π × fc × TS / (1 + 2π × fc × TS)
    float wc_ts = _2_PI * fc_target * TS;
    float lfp = wc_ts / (1.0f + wc_ts);
    
    return lfp;
}

/**
 * @brief 动态相位补偿
 * 
 * @param omega_e_est pll的电角度
 * @return float 补偿的角度
 */
float calc_compensation_angle(float omega_e_est)
{
    float fe = FOC_Abs(omega_e_est) / _2_PI;
    float speed_rpm = FOC_ElecRadPerSecToMechRpm(FOC_Abs(omega_e_est));
    float actual_lfp = FOC_calc_dynamic_lpf(speed_rpm);
    float fc = actual_lfp / (_2_PI * TS * (1.0f - actual_lfp));
    float comp = FOC_FastAtan(fe / fc);

    if (omega_e_est < 0.0f)
        comp = -comp;

    return comp;
}

/**
 * @brief 计算电流的零点偏移
 * 
 * @param motor motor结构体
 */
void FOC_Motor_Cali_Offset(foc_handle_t *motor)
{
    uint32_t sum_iu = 0, sum_iw = 0;
    uint16_t cali_cnt = 200;
    
    // 读取ADC平均值作为零点偏移
    for(uint16_t i=0; i<cali_cnt; i++)
    {
        uint16_t adc_temp_u, adc_temp_v, adc_temp_w;
        motor->hal.adc_get_value(motor->num, &adc_temp_u, &adc_temp_v, &adc_temp_w); // 读取ADC数据

        sum_iu += adc_temp_u;
        sum_iw += adc_temp_w;

        FOC_PortDelayMs(1U);
    }
    motor->i_cali_uvw.u = sum_iu / cali_cnt;
    motor->i_cali_uvw.w = sum_iw / cali_cnt;
}

/**
 * @brief clack变换
 * 
 * @param motor motor结构体
 */
void FOC_Clark_Transform(foc_handle_t *motor)
{
    float iu = motor->i_uvw.u;
    float iw = motor->i_uvw.w;

    motor->i_ab.alpha = iu;
    motor->i_ab.beta = -(iu + 2.0f * iw) * FOC_INV_SQRT3;
}

void FOC_Clark_Transform_Fx(foc_handle_t *motor)
{
    int32_t iu = motor->i_uvw_fx.u;
    int32_t iw = motor->i_uvw_fx.w;
    int32_t beta_input = iu + (iw << 1);

    motor->i_ab_fx.alpha = motor->i_uvw_fx.u;
    motor->i_ab_fx.beta = FOC_Q15Clamp(-((beta_input * FOC_INV_SQRT3_Q15 + FOC_Q15_ROUND) >> FOC_Q15_SHIFT));
#if FOC_RUNTIME_FLOAT_SHADOW
    motor->i_ab.alpha = FOC_Q15ToFloat(motor->i_ab_fx.alpha);
    motor->i_ab.beta = FOC_Q15ToFloat(motor->i_ab_fx.beta);
#endif
}

/**
 * @brief park变换
 * 
 * @param motor motor结构体
 */
void FOC_Park_Transform(foc_handle_t *motor)
{
    float sin_theta = motor->sin_theta;
    float cos_theta = motor->cos_theta;

    motor->i_dq.d = motor->i_ab.alpha * cos_theta + motor->i_ab.beta * sin_theta;
    motor->i_dq.q = -motor->i_ab.alpha * sin_theta + motor->i_ab.beta * cos_theta;
}

void FOC_Park_Transform_Fx(foc_handle_t *motor)
{
    foc_accum_t d = (foc_accum_t)motor->i_ab_fx.alpha * motor->cos_theta_fx + (foc_accum_t)motor->i_ab_fx.beta * motor->sin_theta_fx;
    foc_accum_t q = -(foc_accum_t)motor->i_ab_fx.alpha * motor->sin_theta_fx + (foc_accum_t)motor->i_ab_fx.beta * motor->cos_theta_fx;

    motor->i_dq_fx.d = FOC_Q15FromAccum((d + FOC_Q15_ROUND) >> FOC_Q15_SHIFT);
    motor->i_dq_fx.q = FOC_Q15FromAccum((q + FOC_Q15_ROUND) >> FOC_Q15_SHIFT);
#if FOC_RUNTIME_FLOAT_SHADOW
    motor->i_dq.d = FOC_Q15ToFloat(motor->i_dq_fx.d);
    motor->i_dq.q = FOC_Q15ToFloat(motor->i_dq_fx.q);
#endif
}

/**
 * @brief 反park变换
 * 
 * @param motor motor结构体
 */
void FOC_InvPark_Transform(foc_handle_t *motor)
{
    float sin_theta = motor->sin_theta;
    float cos_theta = motor->cos_theta;

    motor->u_ab.alpha = motor->u_dq.d * cos_theta - motor->u_dq.q * sin_theta;
    motor->u_ab.beta = motor->u_dq.d * sin_theta + motor->u_dq.q * cos_theta;
}

void FOC_InvPark_Transform_Fx(foc_handle_t *motor)
{
    foc_accum_t alpha = (foc_accum_t)motor->u_dq_fx.d * motor->cos_theta_fx - (foc_accum_t)motor->u_dq_fx.q * motor->sin_theta_fx;
    foc_accum_t beta = (foc_accum_t)motor->u_dq_fx.d * motor->sin_theta_fx + (foc_accum_t)motor->u_dq_fx.q * motor->cos_theta_fx;

    motor->u_ab_fx.alpha = FOC_Q15FromAccum((alpha + FOC_Q15_ROUND) >> FOC_Q15_SHIFT);
    motor->u_ab_fx.beta = FOC_Q15FromAccum((beta + FOC_Q15_ROUND) >> FOC_Q15_SHIFT);
#if FOC_RUNTIME_FLOAT_SHADOW
    motor->u_ab.alpha = FOC_Q15ToFloat(motor->u_ab_fx.alpha);
    motor->u_ab.beta = FOC_Q15ToFloat(motor->u_ab_fx.beta);
#endif
}

/**
 * @brief pid控制器
 * 
 * @param pi foc中的pid结构体
 * @param dt 单位时间
 */
void FOC_PI_Regulator(foc_pid_t *pi, float dt)
{
    float error = pi->target - pi->feedback;
    float p = pi->kp * error;
    float integral = pi->integral + pi->ki * error * dt;

    integral = (integral > pi->limit) ? pi->limit : (integral < -pi->limit) ? -pi->limit : integral;

    float output = p + integral;
    float limited_output = (output > pi->limit) ? pi->limit : (output < -pi->limit) ? -pi->limit : output;

    if (output == limited_output || (output > pi->limit && error < 0.0f) || (output < -pi->limit && error > 0.0f))
        pi->integral = integral;

    pi->output = limited_output;
}

void FOC_PI_Regulator_Fx(foc_pid_fx_t *pi)
{
    foc_accum_t error = (foc_accum_t)pi->target - pi->feedback;
    foc_accum_t integral_delta = ((int64_t)pi->ki_dt * error + (1 << 15)) >> 16;
    foc_accum_t integral = pi->integral + integral_delta;
    foc_accum_t limit = pi->limit;
    foc_accum_t output;
    foc_accum_t limited_output;

    if (integral > limit)
        integral = limit;
    else if (integral < -limit)
        integral = -limit;

    output = (((int64_t)pi->kp * error + (1 << 15)) >> 16) + integral;
    limited_output = output;
    if (limited_output > limit)
        limited_output = limit;
    else if (limited_output < -limit)
        limited_output = -limit;

    if (output == limited_output || (output > limit && error < 0) || (output < -limit && error > 0))
        pi->integral = integral;

    pi->output = FOC_Q15FromAccum(limited_output);
}

/**
 * @brief SVPWM正弦波生成
 * 
 * @param motor motor结构体
 */
void FOC_SVPWM_Generate(foc_handle_t *motor)
{
    // float u_alpha = FOC_VoltageFromPu(motor->u_ab.alpha);
    // float u_beta = FOC_VoltageFromPu(motor->u_ab.beta);
    uint16_t Ta, Tb, Tc;
    uint16_t Tx = 0.0f, Ty = 0.0f;
    uint8_t sector;

    // float k = SQRT_3 * PWM_ARR / PWM_VBUS;
    float U1 = motor->u_ab.beta;
    float U2 = -SQRT_3_2 * motor->u_ab.alpha - motor->u_ab.beta / 2.0f;
    float U3 = SQRT_3_2 * motor->u_ab.alpha - motor->u_ab.beta / 2.0f;

    uint8_t A = U1 > 0 ? 1 : 0;
    uint8_t B = U2 > 0 ? 1 : 0;
    uint8_t C = U3 > 0 ? 1 : 0;
    uint8_t N = A + B * 2 + C * 4;

    switch (N)
    {
        case 1: sector = 2; break;
        case 2: sector = 6; break;
        case 3: sector = 1; break;
        case 4: sector = 4; break;
        case 5: sector = 3; break;
        case 6: sector = 5; break;
        default: sector = 0; break;
    }

    switch (sector)
    {
        case 1:
            Tx = U2 * FOC_SVPWM_K;
            Ty = U1 * FOC_SVPWM_K;
            break;
        case 2:
            Tx = -U2 * FOC_SVPWM_K;
            Ty = -U3 * FOC_SVPWM_K;
            break;
        case 3:
            Tx = U1 * FOC_SVPWM_K;
            Ty = U3 * FOC_SVPWM_K;
            break;
        case 4:
            Tx = -U1 * FOC_SVPWM_K;
            Ty = -U2 * FOC_SVPWM_K;
            break;
        case 5:
            Tx = U3 * FOC_SVPWM_K;
            Ty = U2 * FOC_SVPWM_K;
            break;
        case 6:
            Tx = -U3 * FOC_SVPWM_K;
            Ty = -U1 * FOC_SVPWM_K;
            break;
        default:
            break;
    }

    if (Tx + Ty > PWM_ARR)
    {
        float T_sum = Tx + Ty;
        Tx = Tx / T_sum * PWM_ARR;
        Ty = Ty / T_sum * PWM_ARR;
    }

    Ta = (PWM_ARR + Tx + Ty) / 2;
    Tb = Ta - Tx;
    Tc = Tb - Ty;

    switch(sector)
    {
        case 1: motor->pwm.duty_u = Ta; motor->pwm.duty_v = Tb; motor->pwm.duty_w = Tc; break;
        case 2: motor->pwm.duty_u = Tb; motor->pwm.duty_v = Ta; motor->pwm.duty_w = Tc; break;
        case 3: motor->pwm.duty_u = Tc; motor->pwm.duty_v = Ta; motor->pwm.duty_w = Tb; break;
        case 4: motor->pwm.duty_u = Tc; motor->pwm.duty_v = Tb; motor->pwm.duty_w = Ta; break;
        case 5: motor->pwm.duty_u = Tb; motor->pwm.duty_v = Tc; motor->pwm.duty_w = Ta; break;
        case 6: motor->pwm.duty_u = Ta; motor->pwm.duty_v = Tc; motor->pwm.duty_w = Tb; break;
        default:
            motor->pwm.duty_u = PWM_ARR / 2;
            motor->pwm.duty_v = PWM_ARR / 2;
            motor->pwm.duty_w = PWM_ARR / 2;
            break;
    }

    motor->pwm.duty_u = (motor->pwm.duty_u > PWM_ARR) ? PWM_ARR : motor->pwm.duty_u;
    motor->pwm.duty_v = (motor->pwm.duty_v > PWM_ARR) ? PWM_ARR : motor->pwm.duty_v;
    motor->pwm.duty_w = (motor->pwm.duty_w > PWM_ARR) ? PWM_ARR : motor->pwm.duty_w;

    motor->hal.pwm_set_duty(motor->num, motor->pwm.duty_u, motor->pwm.duty_v, motor->pwm.duty_w);
}

void FOC_SVPWM_Generate_Fx(foc_handle_t *motor)
{
    uint16_t Ta, Tb, Tc;
    uint16_t Tx = 0U, Ty = 0U;
    uint8_t sector;
    foc_accum_t U1 = motor->u_ab_fx.beta;
    foc_accum_t U2 = -(((foc_accum_t)FOC_Q15_SQRT3_2 * motor->u_ab_fx.alpha + FOC_Q15_ROUND) >> FOC_Q15_SHIFT) - (motor->u_ab_fx.beta >> 1);
    foc_accum_t U3 = (((foc_accum_t)FOC_Q15_SQRT3_2 * motor->u_ab_fx.alpha + FOC_Q15_ROUND) >> FOC_Q15_SHIFT) - (motor->u_ab_fx.beta >> 1);
    uint8_t A = U1 > 0 ? 1U : 0U;
    uint8_t B = U2 > 0 ? 1U : 0U;
    uint8_t C = U3 > 0 ? 1U : 0U;
    uint8_t N = A + B * 2U + C * 4U;

    switch (N)
    {
        case 1: sector = 2; break;
        case 2: sector = 6; break;
        case 3: sector = 1; break;
        case 4: sector = 4; break;
        case 5: sector = 3; break;
        case 6: sector = 5; break;
        default: sector = 0; break;
    }

    switch (sector)
    {
        case 1:
            Tx = (uint16_t)(((int32_t)U2 * FOC_SVPWM_K_COUNT + FOC_Q15_ROUND) >> FOC_Q15_SHIFT);
            Ty = (uint16_t)(((int32_t)U1 * FOC_SVPWM_K_COUNT + FOC_Q15_ROUND) >> FOC_Q15_SHIFT);
            break;
        case 2:
            Tx = (uint16_t)(((-(int32_t)U2) * FOC_SVPWM_K_COUNT + FOC_Q15_ROUND) >> FOC_Q15_SHIFT);
            Ty = (uint16_t)(((-(int32_t)U3) * FOC_SVPWM_K_COUNT + FOC_Q15_ROUND) >> FOC_Q15_SHIFT);
            break;
        case 3:
            Tx = (uint16_t)(((int32_t)U1 * FOC_SVPWM_K_COUNT + FOC_Q15_ROUND) >> FOC_Q15_SHIFT);
            Ty = (uint16_t)(((int32_t)U3 * FOC_SVPWM_K_COUNT + FOC_Q15_ROUND) >> FOC_Q15_SHIFT);
            break;
        case 4:
            Tx = (uint16_t)(((-(int32_t)U1) * FOC_SVPWM_K_COUNT + FOC_Q15_ROUND) >> FOC_Q15_SHIFT);
            Ty = (uint16_t)(((-(int32_t)U2) * FOC_SVPWM_K_COUNT + FOC_Q15_ROUND) >> FOC_Q15_SHIFT);
            break;
        case 5:
            Tx = (uint16_t)(((int32_t)U3 * FOC_SVPWM_K_COUNT + FOC_Q15_ROUND) >> FOC_Q15_SHIFT);
            Ty = (uint16_t)(((int32_t)U2 * FOC_SVPWM_K_COUNT + FOC_Q15_ROUND) >> FOC_Q15_SHIFT);
            break;
        case 6:
            Tx = (uint16_t)(((-(int32_t)U3) * FOC_SVPWM_K_COUNT + FOC_Q15_ROUND) >> FOC_Q15_SHIFT);
            Ty = (uint16_t)(((-(int32_t)U1) * FOC_SVPWM_K_COUNT + FOC_Q15_ROUND) >> FOC_Q15_SHIFT);
            break;
        default:
            break;
    }

    if ((uint32_t)Tx + (uint32_t)Ty > PWM_ARR)
    {
        uint32_t sum = (uint32_t)Tx + (uint32_t)Ty;
        Tx = (uint16_t)((uint32_t)Tx * PWM_ARR / sum);
        Ty = (uint16_t)((uint32_t)Ty * PWM_ARR / sum);
    }

    Ta = (uint16_t)((PWM_ARR + Tx + Ty) / 2U);
    Tb = (uint16_t)(Ta - Tx);
    Tc = (uint16_t)(Tb - Ty);

    switch(sector)
    {
        case 1: motor->pwm.duty_u = Ta; motor->pwm.duty_v = Tb; motor->pwm.duty_w = Tc; break;
        case 2: motor->pwm.duty_u = Tb; motor->pwm.duty_v = Ta; motor->pwm.duty_w = Tc; break;
        case 3: motor->pwm.duty_u = Tc; motor->pwm.duty_v = Ta; motor->pwm.duty_w = Tb; break;
        case 4: motor->pwm.duty_u = Tc; motor->pwm.duty_v = Tb; motor->pwm.duty_w = Ta; break;
        case 5: motor->pwm.duty_u = Tb; motor->pwm.duty_v = Tc; motor->pwm.duty_w = Ta; break;
        case 6: motor->pwm.duty_u = Ta; motor->pwm.duty_v = Tc; motor->pwm.duty_w = Tb; break;
        default:
            motor->pwm.duty_u = PWM_ARR / 2U;
            motor->pwm.duty_v = PWM_ARR / 2U;
            motor->pwm.duty_w = PWM_ARR / 2U;
            break;
    }

    if (motor->pwm.duty_u > PWM_ARR) motor->pwm.duty_u = PWM_ARR;
    if (motor->pwm.duty_v > PWM_ARR) motor->pwm.duty_v = PWM_ARR;
    if (motor->pwm.duty_w > PWM_ARR) motor->pwm.duty_w = PWM_ARR;

    motor->hal.pwm_set_duty(motor->num, motor->pwm.duty_u, motor->pwm.duty_v, motor->pwm.duty_w);
}

/*快速三角函数*/
 
#define SIN_COS_TABLE {\
    0x0000,0x00C9,0x0192,0x025B,0x0324,0x03ED,0x04B6,0x057F,\
    0x0648,0x0711,0x07D9,0x08A2,0x096A,0x0A33,0x0AFB,0x0BC4,\
    0x0C8C,0x0D54,0x0E1C,0x0EE3,0x0FAB,0x1072,0x113A,0x1201,\
    0x12C8,0x138F,0x1455,0x151C,0x15E2,0x16A8,0x176E,0x1833,\
    0x18F9,0x19BE,0x1A82,0x1B47,0x1C0B,0x1CCF,0x1D93,0x1E57,\
    0x1F1A,0x1FDD,0x209F,0x2161,0x2223,0x22E5,0x23A6,0x2467,\
    0x2528,0x25E8,0x26A8,0x2767,0x2826,0x28E5,0x29A3,0x2A61,\
    0x2B1F,0x2BDC,0x2C99,0x2D55,0x2E11,0x2ECC,0x2F87,0x3041,\
    0x30FB,0x31B5,0x326E,0x3326,0x33DF,0x3496,0x354D,0x3604,\
    0x36BA,0x376F,0x3824,0x38D9,0x398C,0x3A40,0x3AF2,0x3BA5,\
    0x3C56,0x3D07,0x3DB8,0x3E68,0x3F17,0x3FC5,0x4073,0x4121,\
    0x41CE,0x427A,0x4325,0x43D0,0x447A,0x4524,0x45CD,0x4675,\
    0x471C,0x47C3,0x4869,0x490F,0x49B4,0x4A58,0x4AFB,0x4B9D,\
    0x4C3F,0x4CE0,0x4D81,0x4E20,0x4EBF,0x4F5D,0x4FFB,0x5097,\
    0x5133,0x51CE,0x5268,0x5302,0x539B,0x5432,0x54C9,0x5560,\
    0x55F5,0x568A,0x571D,0x57B0,0x5842,0x58D3,0x5964,0x59F3,\
    0x5A82,0x5B0F,0x5B9C,0x5C28,0x5CB3,0x5D3E,0x5DC7,0x5E4F,\
    0x5ED7,0x5F5D,0x5FE3,0x6068,0x60EB,0x616E,0x61F0,0x6271,\
    0x62F1,0x6370,0x63EE,0x646C,0x64E8,0x6563,0x65DD,0x6656,\
    0x66CF,0x6746,0x67BC,0x6832,0x68A6,0x6919,0x698B,0x69FD,\
    0x6A6D,0x6ADC,0x6B4A,0x6BB7,0x6C23,0x6C8E,0x6CF8,0x6D61,\
    0x6DC9,0x6E30,0x6E96,0x6EFB,0x6F5E,0x6FC1,0x7022,0x7083,\
    0x70E2,0x7140,0x719D,0x71F9,0x7254,0x72AE,0x7307,0x735E,\
    0x73B5,0x740A,0x745F,0x74B2,0x7504,0x7555,0x75A5,0x75F3,\
    0x7641,0x768D,0x76D8,0x7722,0x776B,0x77B3,0x77FA,0x783F,\
    0x7884,0x78C7,0x7909,0x794A,0x7989,0x79C8,0x7A05,0x7A41,\
    0x7A7C,0x7AB6,0x7AEE,0x7B26,0x7B5C,0x7B91,0x7BC5,0x7BF8,\
    0x7C29,0x7C59,0x7C88,0x7CB6,0x7CE3,0x7D0E,0x7D39,0x7D62,\
    0x7D89,0x7DB0,0x7DD5,0x7DFA,0x7E1D,0x7E3E,0x7E5F,0x7E7E,\
    0x7E9C,0x7EB9,0x7ED5,0x7EEF,0x7F09,0x7F21,0x7F37,0x7F4D,\
    0x7F61,0x7F74,0x7F86,0x7F97,0x7FA6,0x7FB4,0x7FC1,0x7FCD,\
    0x7FD8,0x7FE1,0x7FE9,0x7FF0,0x7FF5,0x7FF9,0x7FFD,0x7FFE}
static const int16_t hSin_Cos_Table[256] = SIN_COS_TABLE;
 
#define SIN_MASK        0x0300u
#define U0_90           0x0200u
#define U90_180         0x0300u
#define U180_270        0x0000u
#define U270_360        0x0100u
 
foc_Trig_Components FOC_Trig_Functions(int16_t hAngle)
{
 
  int32_t shindex;
  uint16_t uhindex;
  foc_Trig_Components Local_Components;
  /* 10 bit index computation  */
  shindex = ((int32_t)32768 + (int32_t)hAngle);
  uhindex = ((uint16_t)shindex) >> 6;
 
  switch ((uint16_t)(uhindex) & SIN_MASK)
  {
    case U0_90:
      Local_Components.hSin = hSin_Cos_Table[(uint8_t)(uhindex)];
      Local_Components.hCos = hSin_Cos_Table[(uint8_t)(0xFFu - (uint8_t)(uhindex))];
      break;
 
    case U90_180:
      Local_Components.hSin = hSin_Cos_Table[(uint8_t)(0xFFu - (uint8_t)(uhindex))];
      Local_Components.hCos = -hSin_Cos_Table[(uint8_t)(uhindex)];
      break;
 
    case U180_270:
      Local_Components.hSin = -hSin_Cos_Table[(uint8_t)(uhindex)];
      Local_Components.hCos = -hSin_Cos_Table[(uint8_t)(0xFFu - (uint8_t)(uhindex))];
      break;
 
    case U270_360:
      Local_Components.hSin =  -hSin_Cos_Table[(uint8_t)(0xFFu - (uint8_t)(uhindex))];
      Local_Components.hCos =  hSin_Cos_Table[(uint8_t)(uhindex)];
      break;
    default:
      break;
  }
  return (Local_Components);
}

int16_t FOC_RadToQ15Angle(float theta)
{
    if (theta >= _2_PI)
        theta -= _2_PI;
    else if (theta < 0.0f)
        theta += _2_PI;

    return (int16_t)((uint16_t)(theta * FOC_RAD_TO_Q15_SCALE));
}

void FOC_GetSinCos(float theta, float *sin_theta, float *cos_theta)
{
    foc_Trig_Components trig = FOC_Trig_Functions(FOC_RadToQ15Angle(theta));

    *sin_theta = (float)trig.hSin * FOC_Q15_TO_FLOAT;
    *cos_theta = (float)trig.hCos * FOC_Q15_TO_FLOAT;
}

float FOC_FastNorm(float alpha, float beta)
{
    float abs_alpha = FOC_Abs(alpha);
    float abs_beta = FOC_Abs(beta);
    float max_val = (abs_alpha > abs_beta) ? abs_alpha : abs_beta;
    float min_val = (abs_alpha > abs_beta) ? abs_beta : abs_alpha;

    return max_val + min_val * FOC_FAST_NORM_GAIN;
}

foc_q15_t FOC_FastNorm_Fx(foc_q15_t alpha, foc_q15_t beta)
{
    int32_t abs_alpha = FOC_Q15Abs32(alpha);
    int32_t abs_beta = FOC_Q15Abs32(beta);
    int32_t max_val = (abs_alpha > abs_beta) ? abs_alpha : abs_beta;
    int32_t min_val = (abs_alpha > abs_beta) ? abs_beta : abs_alpha;

    return FOC_Q15Clamp(max_val + ((min_val * FOC_FAST_NORM_GAIN_Q15 + FOC_Q15_ROUND) >> FOC_Q15_SHIFT));
}

void FOC_Updata_Trig(foc_handle_t *motor)
{
    motor->trig = FOC_Trig_Functions(motor->theta_fx);
    motor->sin_theta_fx = motor->trig.hSin;
    motor->cos_theta_fx = motor->trig.hCos;
#if FOC_RUNTIME_FLOAT_SHADOW
    motor->sin_theta = (float)motor->sin_theta_fx * FOC_Q15_TO_FLOAT;
    motor->cos_theta = (float)motor->cos_theta_fx * FOC_Q15_TO_FLOAT;
#endif
}

float FOC_fmod(float *x, float y)
{
    if(*x > y) return *x -= y;
    else if(*x < 0) return *x += y;
    else return *x;
}

