/**
 * @file foc_utils.h
 * @author MING
 * @brief 存放派生参数，调用者非必要无需更改
 * @version 0.1
 * @date 2026-03-21
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef __FOC_UTILS_H__
#define __FOC_UTILS_H__ 

#include "foc_types.h"
#include "foc_config.h"

#ifdef __cplusplus
extern "C" {
#endif


/*-------------------------------------派生参数 不需要更改-----------------------------------*/
#define FOC_TWO_PI_F        6.28318530717958647692f
#define OPEN_MECH_SPEED     (OPEN_LOOP_SPEED_RPM * FOC_TWO_PI_F / 60.0f)
#define OPEN_ELEC_SPEED     (OPEN_MECH_SPEED * POLE_PAIRS)
#define CURRENT_SCALE       (PWM_SCALE / (INA240_GAIN * SAMPLE_RESISTOR * ADC_RESOLUTION))  // 从ad数值转换到实际电流值的转换系数
#define TS_MOTORL           (TS/MOTOR_L)
#define DEAD_COMP_V         (PWM_VBUS * BTN7960_DEAD_TIME_S / TS)
#define PI_LIMIT            (PWM_VBUS * 0.95f / SQRT_3)                                     // 最大不失真电压 
#define SVPWM_K             (SQRT_3 * PWM_ARR / PWM_VBUS)
#define FOC_CURRENT_LIMIT_PU 1.0f                                                           // 标幺电流限幅
#define FOC_VOLTAGE_LIMIT_PU 1.0f                                                           // 标幺电压限幅
#define CURRENT_TARGET_LIMIT_PU (CURRENT_TARGET_LIMIT / FOC_CURRENT_BASE_A)
#define FW_ID_MAX_PU        (FW_ID_MAX / FOC_CURRENT_BASE_A)                                // 标幺弱磁电流限幅
#define HFI_INJECTION_VOLTAGE_PU (HFI_INJECTION_VOLTAGE / FOC_VOLTAGE_BASE_V)               // 标幺d轴高频注入电压(V)
#define HFI_IQ_HF_LIMIT_PU  (HFI_IQ_HF_LIMIT / FOC_CURRENT_BASE_A)                          // 标幺高频电流保护阈值(A)
#define HFI_MIN_RESPONSE_PU (HFI_MIN_RESPONSE / FOC_CURRENT_BASE_A)                         // 标幺HFI解调响应有效阈值
#define PI_KP_D_PU          (PI_KP_D * FOC_CURRENT_BASE_A / FOC_VOLTAGE_BASE_V)             // 标幺d轴kp参数
#define PI_KI_D_PU          (PI_KI_D * FOC_CURRENT_BASE_A / FOC_VOLTAGE_BASE_V)             // 标幺d轴ki参数
#define PI_KP_Q_PU          (PI_KP_Q * FOC_CURRENT_BASE_A / FOC_VOLTAGE_BASE_V)             // 标幺q轴kp参数
#define PI_KI_Q_PU          (PI_KI_Q * FOC_CURRENT_BASE_A / FOC_VOLTAGE_BASE_V)             // 标幺q轴ki参数
#define PI_KI_D_DT_PU       (PI_KI_D_PU * TS)                                               // 离散d轴ki*dt
#define PI_KI_Q_DT_PU       (PI_KI_Q_PU * TS)                                               // 离散q轴ki*dt
#define PI_KP_SPEED_PU      (PI_KP_SPEED * FOC_SPEED_BASE_RPM / FOC_CURRENT_BASE_A)         // 标幺速度环kp (pu电流/pu速度)
#define PI_KI_SPEED_PU      (PI_KI_SPEED * FOC_SPEED_BASE_RPM / FOC_CURRENT_BASE_A)         // 标幺速度环ki (pu电流/pu速度/s)
#define PI_LIMIT_SPEED_PU   (PI_LIMIT_SPEED / FOC_CURRENT_BASE_A)                           // 标幺速度环输出限幅(pu电流)
#define PI_KP_POSITION_PU   (PI_KP_POSITION / FOC_SPEED_BASE_RPM)                           // 标幺位置环kp (pu速度/rad)
#define PI_KI_POSITION_PU   (PI_KI_POSITION / FOC_SPEED_BASE_RPM)                           // 标幺位置环ki (pu速度/rad/s)
#define PI_LIMIT_POSITION_PU (PI_LIMIT_POSITION_RPM / FOC_SPEED_BASE_RPM)                   // 标幺位置环输出限幅(pu速度)

#define FOC_Q15_SCALE       32768.0f
#define FOC_Q16_16_SCALE    65536.0f
#define FOC_Q32_SCALE       4294967296.0f
#define FOC_Q15_SHIFT       15
#define FOC_Q15_ROUND       (1 << (FOC_Q15_SHIFT - 1))
#define FOC_Q15_MAX         32767
#define FOC_Q15_MIN         (-32768)
#define FOC_Q16_MAX         65535
#define FOC_Q16_MIN         (-65535)
#define FOC_Q32_MAX         4294967295
#define FOC_Q32_MIN         (-4294967295)
#define FOC_INV_SQRT3_Q15   18919
#define FOC_SQRT3_2_Q15     28378
#define FOC_FAST_NORM_GAIN_Q15 12288
#define FOC_ADC_TO_CURRENT_PU_Q20 ((int32_t)(CURRENT_SCALE * ((float)(1 << 20) / FOC_CURRENT_BASE_A) + 0.5f))
    
#define FOC_FC_TARGET_K (POLE_PAIRS / 60.0f)
#define FOC_FC_TARGET_K_Q16 (FOC_FC_TARGET_K * 65536)

/*滑膜观测器宏定义*/
#define SMO_A (1.0f - MOTOR_R * TS / MOTOR_L)
#define SMO_A_PU (SMO_A / FOC_VOLTAGE_BASE_V)
#define SMO_A_Q15 (SMO_A_PU * FOC_Q15_SCALE)
#define SMO_B (TS * FOC_VOLTAGE_BASE_V / (MOTOR_L * FOC_CURRENT_BASE_A))
#define SMO_B_PU (SMO_B / FOC_VOLTAGE_BASE_V)
#define SMO_B_Q15 (SMO_B_PU * FOC_Q15_SCALE)
#define SMO_K_PU (SMO_K / FOC_VOLTAGE_BASE_V)
#define SMO_K_Q15 (SMO_K_PU * FOC_Q15_SCALE)
#define SMO_SAT_BOUNDARY_PU (SAT_BOUNDARY / FOC_CURRENT_BASE_A)
#define SMO_SAT_BOUNDARY_Q15 (SMO_SAT_BOUNDARY_PU * FOC_Q15_SCALE)
#define SMO_E_AMP_MIN (0.5f / FOC_VOLTAGE_BASE_V)
#define SMO_E_AMP_MIN_Q15 (SMO_E_AMP_MIN * FOC_Q15_SCALE)
#define SMO_E_AMP_LOW (0.1f / FOC_VOLTAGE_BASE_V)
#define SMO_E_AMP_LOW_Q15 (SMO_E_AMP_LOW * FOC_Q15_SCALE)

// PLL_KI * TS = 5000 * 0.00005 = 0.25
#define PLL_KI_DT_Q16       ((int32_t)(PLL_KI * TS * FOC_Q16_16_SCALE))   // = 16384
// PLL_KP = 170
#define PLL_KP_Q16          ((int32_t)(PLL_KP * FOC_Q16_16_SCALE))        // = 11141120
// OB_SPEED_LIMIT = 8000
#define OB_SPEED_LIMIT_Q16  ((int32_t)(OB_SPEED_LIMIT * FOC_Q16_16_SCALE)) // = 524288000
// SPEED_OBSERBER_LPF = 0.05
#define SPEED_OBS_LPF_Q15   ((int32_t)(SPEED_OBSERBER_LPF * FOC_Q15_SCALE)) // = 1638
// theta 增量系数: TS / (2π)，再乘以 2^32
#define PLL_THETA_INC_K_Q32 ((int64_t)(TS / _2_PI * FOC_Q32_SCALE))  // ≈ 34185

#define _2_PI_q15 (_2_PI * FOC_Q15_MAX)
#define _2_PI_TS (_2_PI * TS)
#define _2_PI_TS_Q15 (int16_t)(_2_PI_TS * FOC_Q15_MAX)
#define _2_PI_TS_Q32 ((int64_t)(_2_PI_TS * FOC_Q32_MAX))

/*速度转换宏定义*/
#define ERAD_TO_RPM_K (60.0f / (FOC_TWO_PI_F * POLE_PAIRS))
#define RPM_TO_ERAD_K (FOC_TWO_PI_F * POLE_PAIRS / 60.0f)
#define RAD_TO_RPM_K (60.0f / FOC_TWO_PI_F)

static inline foc_q15_t FOC_Q15Clamp(int32_t value)
{
    if (value > FOC_Q15_MAX)
        return FOC_Q15_MAX;
    if (value < FOC_Q15_MIN)
        return FOC_Q15_MIN;
    return (foc_q15_t)value;
}

static inline foc_q15_t FOC_FloatToQ15(float value)
{
    float scaled = value * FOC_Q15_SCALE;

    if (scaled >= (float)FOC_Q15_MAX)
        return FOC_Q15_MAX;
    if (scaled <= (float)FOC_Q15_MIN)
        return FOC_Q15_MIN;
    return (foc_q15_t)scaled;
}

static inline float FOC_Q15ToFloat(foc_q15_t value)
{
    return (float)value / FOC_Q15_SCALE;
}

static inline foc_accum_t FOC_FloatToQ16_16(float value)
{
    return (foc_accum_t)(value * FOC_Q16_16_SCALE);
}

static inline float FOC_Q16_16ToFloat(foc_accum_t value)
{
    return (float)value / FOC_Q16_16_SCALE;
}

static inline foc_q15_t FOC_Q15Mul(foc_q15_t a, foc_q15_t b)
{
    int32_t product = (int32_t)a * (int32_t)b;
    product += (1 << 14);
    return FOC_Q15Clamp(product >> 15);
}

static inline foc_q15_t FOC_Q15FromCurrentPu(float current_pu)
{
    return FOC_FloatToQ15(current_pu);
}

static inline foc_q15_t FOC_Q15FromVoltagePu(float voltage_pu)
{
    return FOC_FloatToQ15(voltage_pu);
}

static inline float FOC_CurrentToPu(float current_a)
{
    return current_a / FOC_CURRENT_BASE_A;
}

static inline float FOC_CurrentFromPu(float current_pu)
{
    return current_pu * FOC_CURRENT_BASE_A;
}

static inline float FOC_VoltageToPu(float voltage_v)
{
    return voltage_v / FOC_VOLTAGE_BASE_V;
}

static inline float FOC_VoltageFromPu(float voltage_pu)
{
    return voltage_pu * FOC_VOLTAGE_BASE_V;
}

static inline float FOC_SpeedRpmToPu(float speed_rpm)
{
    return speed_rpm / FOC_SPEED_BASE_RPM;
}

static inline float FOC_SpeedPuToRpm(float speed_pu)
{
    return speed_pu * FOC_SPEED_BASE_RPM;
}

static inline foc_q15_t FOC_Q15FromCurrent(float current_a)
{
    return FOC_FloatToQ15(current_a / FOC_CURRENT_BASE_A);
}

static inline foc_q15_t FOC_Q15FromVoltage(float voltage_v)
{
    return FOC_FloatToQ15(voltage_v / FOC_VOLTAGE_BASE_V);
}

static inline float FOC_Q15ToCurrent(foc_q15_t current_q15)
{
    return FOC_Q15ToFloat(current_q15) * FOC_CURRENT_BASE_A;
}

static inline float FOC_Q15ToVoltage(foc_q15_t voltage_q15)
{
    return FOC_Q15ToFloat(voltage_q15) * FOC_VOLTAGE_BASE_V;
}

static inline foc_q15_t FOC_Q16FromSpeedRpm(float speed_rpm)
{
    return FOC_FloatToQ16_16(speed_rpm / FOC_SPEED_BASE_RPM);
}

static inline float FOC_Q16ToSpeedRpm(foc_accum_t speed_q16)
{
    return FOC_Q16_16ToFloat(speed_q16) * FOC_SPEED_BASE_RPM;
}

/**
 * @brief 机械速度（rpm）转电角速度（rad/s）
 * 
 * @param speed_rpm 机械速度（rpm）
 * @return float 电角速度（rad/s）
 */
static inline float FOC_MechRpmToElecRadPerSec(float speed_rpm)
{
    return speed_rpm * RPM_TO_ERAD_K;
}

/**
 * @brief 电角速度（rad/s）转机械速度（rpm）
 *
 * @param omega_elec 电角速度（rad/s）
 * @return float 机械转速（rpm）
 */
static inline float FOC_ElecRadPerSecToMechRpm(float omega_elec)
{
    return omega_elec * ERAD_TO_RPM_K;
}

/**
 * @brief 电角速度（rad/s）转机械速度（rpm）(Q15)
 *
 * @param omega_elec 电角速度（rad/s）
 * @return float 机械转速（rpm）
 */
static inline foc_q15_t FOC_ElecRadPerSecToMechRpm_fx(foc_q15_t omega_elec)
{
    return omega_elec;
}

/**
 * @brief 角速度（rad/s）转机械速度（rpm）
 * 
 * @param omega_mech 角速度（rad/s）
 * @return float 机械速度（rpm）
 */
static inline float FOC_MechRadPerSecToRpm(float omega_mech)
{
    return omega_mech * RAD_TO_RPM_K;
}

/**
 * @brief 先对电角速度（rad/s）取绝对值再转换为机械速度（rpm）
 * 
 * @param omega_elec 电角速度（rad/s）
 * @return float 机械速度（rpm）
 */
static inline float FOC_AbsElecRadPerSecToMechRpm(float omega_elec)
{
    float omega_abs = (omega_elec >= 0.0f) ? omega_elec : -omega_elec;
    return FOC_ElecRadPerSecToMechRpm(omega_abs);
}

/**
 * @brief 先对电角速度（rad/s）取绝对值再转换为机械速度（rpm）(q15)
 * 
 * @param omega_elec 电角速度（rad/s）
 * @return float 机械速度（rpm）
 */
static inline foc_q15_t FOC_AbsElecRadPerSecToMechRpm_fx(foc_q15_t omega_elec)
{
    foc_q15_t omega_abs = (omega_elec >= 0.0f) ? omega_elec : -1 * omega_elec;
    return FOC_ElecRadPerSecToMechRpm_fx(omega_abs);
}

/**
 * @brief 机械角度（rad）转电角度（rad）
 * 
 * @param mech_angle_rad 机械角度（rad）
 * @return float 电角角度（rad）
 */

static inline float FOC_MechAngleToElecAngle(float mech_angle_rad)
{
    return mech_angle_rad * POLE_PAIRS - FOC_ELECTRICAL_ANGLE_OFFSET;
}


#ifdef __cplusplus
}
#endif

#endif

