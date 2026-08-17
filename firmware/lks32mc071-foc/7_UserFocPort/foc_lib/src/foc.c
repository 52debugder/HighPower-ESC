/**
 * @file foc.c
 * @author MING
 * @brief foc调用库
 * @version 1.0
 * @date 2026-07-10
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "foc.h"

static foc_handle_t FOC_Motor[MAX_MOTOR_NUM + 1] = {0};
#if FOC_OPEN_I_DEBUG_EN || FOC_CLOSE_I_DEBUG_EN
static uint32_t vofa_cnt = 0;
#endif

#define FOC_PI_F 3.14159265358979323846f
#define FOC_ALIGN_STABLE_DELTA_RAD 0.01f
#define FOC_ALIGN_STABLE_COUNT 200U

static float foc_wrap_angle_0_2pi(float angle)
{
    if (angle >= FOC_TWO_PI_F)
        angle -= FOC_TWO_PI_F;
    else if (angle < 0.0f)
        angle += FOC_TWO_PI_F;

    return angle;
}

static float foc_wrap_delta_pm_pi(float delta)
{
    if (delta > FOC_PI_F)
        delta -= FOC_TWO_PI_F;
    else if (delta < -FOC_PI_F)
        delta += FOC_TWO_PI_F;

    return delta;
}

#if FOC_RUNTIME_FLOAT_SHADOW
static void foc_sync_pi_shadow_from_fx(foc_pid_t *pi_float, foc_pid_fx_t *pi_fx)
{
    pi_float->target = FOC_Q15ToFloat(pi_fx->target);
    pi_float->feedback = FOC_Q15ToFloat(pi_fx->feedback);
    pi_float->output = FOC_Q15ToFloat(pi_fx->output);
    pi_float->integral = FOC_Q15ToFloat(FOC_Q15Clamp(pi_fx->integral));
    pi_float->limit = FOC_Q15ToFloat(pi_fx->limit);
}
#endif

static foc_accum_t foc_q16_16_clamp(int64_t value)
{
    if (value > INT32_MAX)
        return INT32_MAX;
    if (value < INT32_MIN)
        return INT32_MIN;
    return (foc_accum_t)value;
}

static void foc_sync_pi_shadow_from_q16(foc_pid_t *pi_float, foc_pid_q16_t *pi_fx)
{
    pi_float->target = FOC_Q16_16ToFloat(pi_fx->target);
    pi_float->feedback = FOC_Q16_16ToFloat(pi_fx->feedback);
    pi_float->output = FOC_Q16_16ToFloat(pi_fx->output);
    pi_float->integral = FOC_Q16_16ToFloat(pi_fx->integral);
    pi_float->limit = FOC_Q16_16ToFloat(pi_fx->limit);
}

static void FOC_PI_Regulator_Q16(foc_pid_q16_t *pi)
{
    int64_t error = (int64_t)pi->target - pi->feedback;
    int64_t integral_delta = ((int64_t)pi->ki_dt * error + (1 << 15)) >> 16;
    int64_t integral = (int64_t)pi->integral + integral_delta;
    int64_t limit = pi->limit;
    int64_t output;
    int64_t limited_output;

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
        pi->integral = foc_q16_16_clamp(integral);

    pi->output = foc_q16_16_clamp(limited_output);
}

static void foc_sync_current_targets_to_fx(foc_handle_t *motor)
{
    motor->pi_d_fx.target = FOC_Q15FromCurrentPu(motor->pi_d.target);
    motor->pi_q_fx.target = FOC_Q15FromCurrentPu(motor->pi_q.target);
}

static void foc_set_udq_fx(foc_handle_t *motor, foc_q15_t d, foc_q15_t q)
{
    motor->u_dq_fx.d = d;
    motor->u_dq_fx.q = q;
#if FOC_RUNTIME_FLOAT_SHADOW
    motor->u_dq.d = FOC_Q15ToFloat(d);
    motor->u_dq.q = FOC_Q15ToFloat(q);
#endif
}

static foc_state_t Foc_Preprocess_CurrentSample(foc_handle_t *motor)
{
    foc_state_t foc_state = FOC_OK;
    int32_t raw_u = (int32_t)motor->i_adc_u - (int32_t)motor->i_cali_uvw.u;
    int32_t raw_w = (int32_t)motor->i_adc_w - (int32_t)motor->i_cali_uvw.w;
    int32_t iu_q15 = (raw_u * FOC_ADC_TO_CURRENT_PU_Q20 + (1 << 4)) >> 5;
    int32_t iw_q15 = (raw_w * FOC_ADC_TO_CURRENT_PU_Q20 + (1 << 4)) >> 5;

    if (iu_q15 >= FOC_Q15_MAX)
    {
        iu_q15 = FOC_Q15_MAX;
        foc_state = FOC_ERR_OVERCURRENT;
    }
    else if (iu_q15 <= FOC_Q15_MIN)
    {
        iu_q15 = FOC_Q15_MIN;
        foc_state = FOC_ERR_OVERCURRENT;
    }

    if (iw_q15 >= FOC_Q15_MAX)
    {
        iw_q15 = FOC_Q15_MAX;
        foc_state = FOC_ERR_OVERCURRENT;
    }
    else if (iw_q15 <= FOC_Q15_MIN)
    {
        iw_q15 = FOC_Q15_MIN;
        foc_state = FOC_ERR_OVERCURRENT;
    }

    motor->i_uvw_fx.u = (foc_q15_t)iu_q15;
    motor->i_uvw_fx.v = 0;
    motor->i_uvw_fx.w = (foc_q15_t)iw_q15;
#if FOC_RUNTIME_FLOAT_SHADOW
    motor->i_uvw.u = FOC_Q15ToFloat(motor->i_uvw_fx.u);
    motor->i_uvw.v = 0.0f;
    motor->i_uvw.w = FOC_Q15ToFloat(motor->i_uvw_fx.w);
#endif

    return foc_state;
}

static void Foc_SetElectricalAngle(foc_handle_t *motor, float theta)
{
    motor->theta = foc_wrap_angle_0_2pi(theta);
    motor->theta_fx = FOC_RadToQ15Angle(motor->theta);
}

static void Foc_RefreshTrigCache(foc_handle_t *motor)
{
    FOC_Updata_Trig(motor);
}

static void Foc_AdvanceOpenLoopAngle(foc_handle_t *motor, float dt)
{
    float theta = motor->theta;

    if (motor->target_speed > 0.0f)
        theta += OPEN_ELEC_SPEED * dt;
    else if (motor->target_speed < 0.0f)
        theta -= OPEN_ELEC_SPEED * dt;

    Foc_SetElectricalAngle(motor, theta);
}

static uint8_t Foc_LoadClosedLoopSensorAngle(foc_handle_t *motor, float dt)
{
    if ((motor->trig_sample_valid == 0U) || (motor->sensor_mech.sample_seq != motor->trig_sample_seq))
    {
        float mech_angle = foc_wrap_angle_0_2pi(motor->sensor_mech.angle - motor->sensor_mech.zero_offset);

        Foc_SetElectricalAngle(motor, FOC_MechAngleToElecAngle(mech_angle));
        motor->speed = motor->sensor_mech.speed;
        motor->trig_sample_seq = motor->sensor_mech.sample_seq;
        motor->trig_sample_valid = 1U;
        return 1U;
    }

    if (motor->sensor_mech.vaild != 0.0f)
    {
        float theta = motor->theta - FOC_MechRpmToElecRadPerSec(motor->speed) * dt;

        Foc_SetElectricalAngle(motor, theta);
        return 1U;
    }

    return 0U;
}

/**
 * @brief foc初始化
 * 
 * @param motor 
 * @return foc_state_t 
 */
foc_state_t Foc_Init(uint8_t motor_num, const foc_hal_t *hal_interface)
{
    foc_handle_t *motor = &FOC_Motor[motor_num];
    motor->num = motor_num;
    Foc_ParamInit(motor, hal_interface); // FOC初始化

    motor->hal.pwm_start(motor_num);
    FOC_Motor_Cali_Offset(motor);        // 电机零点校准（上电静止时执行）
    motor->hal.drv_enable(motor_num);            // 驱动使能
    motor->mode = MOTOR_STATE_IDLE;
    motor->state_timer = 0;
    motor->init_done = 1;

    return FOC_OK;
}


/**
 * @brief foc参数初始化
 * 
 * @param motor 
 * @return foc_state_t 
 */
foc_state_t Foc_ParamInit(foc_handle_t *motor, const foc_hal_t *hal_interface)
{
    // 绑定定时器
    // motor->htim = htim;
    motor->hal = *hal_interface; // 绑定HAL
    motor->hal.init(motor->num);
    // d轴电流环参数初始化
    motor->pi_d = (foc_pid_t){
        .kp = PI_KP_D_PU,
        .ki = PI_KI_D_PU,
        .limit = FOC_VOLTAGE_LIMIT_PU,
        .target = 0.0f};
    motor->pi_d_fx = (foc_pid_fx_t){
        .kp = FOC_FloatToQ16_16(PI_KP_D_PU),
        .ki_dt = FOC_FloatToQ16_16(PI_KI_D_DT_PU),
        .limit = FOC_Q15FromVoltagePu(FOC_VOLTAGE_LIMIT_PU),
        .target = 0,
        .feedback = 0,
        .output = 0,
        .integral = 0,
    };

    // q轴电流环参数初始化
    motor->pi_q = (foc_pid_t){
        .kp = PI_KP_Q_PU,
        .ki = PI_KI_Q_PU,
        .limit = FOC_VOLTAGE_LIMIT_PU,
        .target = 0.0f};
    motor->pi_q_fx = (foc_pid_fx_t){
        .kp = FOC_FloatToQ16_16(PI_KP_Q_PU),
        .ki_dt = FOC_FloatToQ16_16(PI_KI_Q_DT_PU),
        .limit = FOC_Q15FromVoltagePu(FOC_VOLTAGE_LIMIT_PU),
        .target = 0,
        .feedback = 0,
        .output = 0,
        .integral = 0,
    };

    // 速度PI参数初始化（库内标幺：pu速度 -> pu电流；ki_dt在运行时用真实dt计算）
    motor->pi_speed = (foc_pid_t){
        .kp = PI_KP_SPEED_PU,
        .ki = PI_KI_SPEED_PU,
        .limit = PI_LIMIT_SPEED_PU,
        .target = 0,
        .integral = 0.0f};
    motor->pi_speed_fx = (foc_pid_q16_t){
        .kp = FOC_FloatToQ16_16(PI_KP_SPEED_PU),
        .ki_dt = 0,
        .limit = FOC_FloatToQ16_16(PI_LIMIT_SPEED_PU),
        .target = 0,
        .feedback = 0,
        .output = 0,
        .integral = 0,
    };

    // 位置PI参数初始化（库内标幺：rad -> pu速度；ki_dt在运行时用真实dt计算）
    motor->pi_position = (foc_pid_t){
        .kp = PI_KP_POSITION_PU,
        .ki = PI_KI_POSITION_PU,
        .limit = PI_LIMIT_POSITION_PU,
        .target = 0.0f,
        .integral = 0.0f};
    motor->pi_position_fx = (foc_pid_q16_t){
        .kp = FOC_FloatToQ16_16(PI_KP_POSITION_PU),
        .ki_dt = 0,
        .limit = FOC_FloatToQ16_16(PI_LIMIT_POSITION_PU),
        .target = 0,
        .feedback = 0,
        .output = 0,
        .integral = 0,
    };

    // 初始占空比
    motor->pwm = (foc_pwm_t){
        .duty_u = PWM_ARR / 2,
        .duty_v = PWM_ARR / 2,
        .duty_w = PWM_ARR / 2,};

    // 上一次ab轴电流
    motor->i_ab_pre = (foc_ab_t){
        .alpha = 0.0f,
        .beta = 0.0f};

    motor->e_ab = (foc_ab_t){
        .alpha = 0.0f,
        .beta = 0.0f};

    motor->i_cali_uvw = (foc_uvw_t){
        .u = 0.0f,
        .v = 0.0f,
        .w = 0.0f,
    };

    motor->sensor_mech = (foc_sensor_mech_t){
        .angle = 0.0f,
        .speed = 0.0f,
        .vaild = 0.0f,
        .dir = 0U,
        .zero_offset = 0.0f,
        .sample_seq = 0U,
        .align_prev_sample_seq = 0U,
        .align_prev_angle = 0.0f,
        .align_stable_count = 0U,
        .align_has_prev = 0U,
        .zero_offset_locked = 0U,
    };

    motor->pi_pll.integral = 0.0f;
    motor->speed_observer = 0.0f;
    motor->theta_Observer = 0.0f;
    motor->theta_obs_prev = 0.0f;

    motor->theta = 0.0f;
    motor->theta_fx = 0;
    motor->sin_theta_fx = 0;
    motor->cos_theta_fx = FOC_Q15_MAX;
    motor->sin_theta = 0.0f;
    motor->cos_theta = 1.0f;
    motor->trig_sample_seq = 0U;
    motor->trig_sample_valid = 0U;

    motor->target_speed = 0.0f;
    motor->speed_ramp_target = 0.0f;
    motor->speed_sign = 1.0;
    motor->id_fw = 0.0f;
    motor->fw_active = 0.0f;
    motor->fw_voltage = 0.0f;

    motor->control_mode = FOC_CONTROL_SPEED;

    motor->target_position = 0.0f;
    motor->position_raw = 0.0f;
    motor->position = 0.0f;
    motor->position_offset = 0.0f;
    motor->position_dir = 0.0f;
#if HFI_ENABLE
    HFI_Init(motor);
#endif
    motor->state_timer = 0;
    motor->state = FOC_OK;
    return FOC_OK;
}

/**
 * @brief FOC失能初始化
 * 
 * @param motor 
 * @return foc_state_t 
 */
foc_state_t Foc_Deinit(foc_handle_t *motor)
{
    return FOC_OK;
}

/**
 * @brief FOC循环空状态转别的状态的准备工作
 * 
 * @param motor 电机结构体
 * @param motor_num 电机序号
 * @return foc_state_t foc状态
 */
static foc_state_t FOC_IDLE_Convert_Prepare(foc_handle_t *motor, uint8_t motor_num)
{
    motor->theta             = 0.0f;
    motor->pi_pll.integral   = 0.0f;
    motor->pi_d.integral        = 0.0f;
    motor->pi_q.integral        = 0.0f;
    motor->pi_d_fx.integral     = 0;
    motor->pi_q_fx.integral     = 0;
    motor->pi_speed.integral    = 0.0f;
    motor->pi_position.integral = 0.0f;
    motor->theta_obs_prev       = 0.0f;
    motor->id_fw                = 0.0f;
    motor->sensor_mech.speed = 0.0f;
    motor->sensor_mech.zero_offset = 0.0f;
    motor->sensor_mech.align_prev_sample_seq = motor->sensor_mech.sample_seq;
    motor->sensor_mech.align_prev_angle = 0.0f;
    motor->sensor_mech.align_stable_count = 0U;
    motor->sensor_mech.align_has_prev = 0U;
    motor->sensor_mech.zero_offset_locked = 0U;
    motor->trig_sample_valid = 0U;

    if (motor->control_mode == FOC_CONTROL_POSITION)
    {
        motor->position_raw = 0.0f;
        motor->position_offset = 0.0f;
        motor->position = 0.0f;
        motor->position_dir = 0.0f;
    }
    motor->state_timer          = 0;
    motor->hal.drv_enable(motor_num);
    motor->mode = MOTOR_STATE_ALIGN;
    return FOC_OK;
}

/**
 * @brief FOC循环角度对齐状态转别的状态的准备工作
 * 
 * @param motor 电机结构体
 * @param motor_num 电机序号
 * @return foc_state_t foc状态
 */
static foc_state_t FOC_Align_Convert_Prepare(foc_handle_t *motor, uint8_t motor_num)
{
    motor->state_timer = 0;

#if HFI_ENABLE // 使能高频注入
    if (motor->hfi_enable && motor->control_mode == FOC_CONTROL_POSITION)
    {
        motor->theta = 0.0f;
        motor->theta_Observer = 0.0f;
        motor->theta_obs_prev = 0.0f;
        motor->position_raw = 0.0f;
        motor->position_offset = 0.0f;
        motor->position = 0.0f;
        motor->speed_ramp_target = 0.0f;
        motor->pi_speed.integral = 0.0f;
        motor->pi_position.integral = 0.0f;
        HFI_Reset_Angle(motor, 0.0f);
        motor->PI_Speed_cnt = 0;
        motor->close_cnt = 0;
        motor->trig_sample_valid = 0U;
        motor->mode = MOTOR_STATE_CLOSE;
        break;
    }
#endif
    motor->pi_pll.integral = motor->target_speed > 0 ? OPEN_ELEC_SPEED : -OPEN_ELEC_SPEED;

#if FOC_SENSOR_EN && FOC_CLOSE_LOOP_EN
    motor->mode = MOTOR_STATE_CLOSE;
#else
    motor->mode = MOTOR_STATE_OPEN;
#endif
    return FOC_OK;
}

/**
 * @brief FOC循环角度对齐状态转别的状态的准备工作
 * 
 * @param motor 电机结构体
 * @param motor_num 电机序号
 * @return foc_state_t foc状态
 */
static foc_state_t FOC_Open_Convert_Prepare(foc_handle_t *motor, uint8_t motor_num)
{
    motor->pi_pll.integral = motor->target_speed > 0 ? fabsf(motor->speed_observer) : -fabsf(motor->speed_observer);
    motor->pi_d.integral = 0.0f;
    motor->pi_d.output = 0.0f;
    motor->pi_d_fx.integral = 0;
    motor->pi_d_fx.output = 0;

    motor->pi_speed.integral = 0.0f; // 初始驱动力
    motor->pi_speed.output = 6.7f;

    motor->pi_q.integral = FOC_VoltageToPu(PWM_VBUS * 0.5f);
    motor->pi_q.output = FOC_VoltageToPu(PWM_VBUS * 0.55f);
    motor->pi_q_fx.integral = FOC_Q15FromVoltagePu(motor->pi_q.integral);
    motor->pi_q_fx.output = FOC_Q15FromVoltagePu(motor->pi_q.output);

    if(motor->target_speed > 0)
        motor->speed_ramp_target = FOC_AbsElecRadPerSecToMechRpm(motor->speed_observer) + 50.0f;
    else
        motor->speed_ramp_target = -FOC_AbsElecRadPerSecToMechRpm(motor->speed_observer) + 50.0f;

    motor->theta_Observer = motor->theta;
    motor->theta_obs_prev = motor->theta;
    motor->pi_position.integral = 0.0f;
#if HFI_ENABLE
    if (motor->hfi_enable)
        HFI_Reset_Angle(motor, motor->theta);
#endif
    motor->PI_Speed_cnt = 0;
    motor->close_cnt = 0;
    motor->trig_sample_valid = 0U;

    motor->mode = MOTOR_STATE_CLOSE;
    return FOC_OK;
}

// float speed_diff;
/**
 * @brief foc主循环，用于在定时器中调用，采用了分段式处理，开环强拉到闭环状态
 * 
 * @param motor 
 * @return foc_state_t 
 */
foc_state_t Foc_Loop(uint8_t motor_num)
{
    foc_handle_t *motor = &FOC_Motor[motor_num];

    if (motor->init_done != 1)
        return FOC_ERR_NOT_INIT; // 初始化未完成，直接返回

    switch (motor->mode)
    {
    case MOTOR_STATE_IDLE: // 空状态
        // 每个控制周期都刷新为零电压，防止PWM寄存器残留
        motor->hal.pwm_set_duty(motor->num,
            PWM_ARR / 2, PWM_ARR / 2, PWM_ARR / 2);

        if (!Foc_Safe_Protect(motor->target_speed))
        {
            FOC_IDLE_Convert_Prepare(motor, motor_num);
        }
        break;

    case MOTOR_STATE_ALIGN:
        Foc_Align_Loop(motor, TS);

        // ALIGN 期间若遥控器归零 → 回 IDLE
        if (Foc_Safe_Protect(motor->target_speed))
        {
            motor->state_timer = 0;
            motor->mode = MOTOR_STATE_IDLE;
            break;
        }

        motor->state_timer++;

#if FOC_SENSOR_EN
        if (motor->state_timer > 4000 && motor->sensor_mech.vaild != 0.0f && motor->sensor_mech.zero_offset_locked != 0U)
#else
        if(motor->state_timer > 4000)
#endif
        {
            FOC_Align_Convert_Prepare(motor, motor_num);
        }
        break;

    case MOTOR_STATE_OPEN: // 开环启动：按设定转速匀速旋转
        Foc_Open_Loop(motor, TS);

        // ALIGN 期间若遥控器归零 → 回 IDLE
        if (Foc_Safe_Protect(motor->target_speed))
        {
            motor->hal.pwm_set_duty(motor->num,
                PWM_ARR / 2, PWM_ARR / 2, PWM_ARR / 2);
            motor->e_ab.alpha     = 0.0f;
            motor->e_ab.beta      = 0.0f;
            motor->i_ab_hat.alpha = 0.0f;
            motor->i_ab_hat.beta  = 0.0f;
            motor->speed_observer = 0.0f;
            motor->speed_sign     = 1.0f;
            motor->state_timer    = 0;
            motor->mode = MOTOR_STATE_IDLE;
            break;
        }

        motor->state_timer++;

#if FOC_CLOSE_LOOP_EN // 闭环使能
        {
            // 观测速度与开环速度接近才切换
            float speed_rpm = FOC_ElecRadPerSecToMechRpm(motor->speed_observer);
            float speed_diff = fabsf(fabsf(speed_rpm) - fabsf(OPEN_LOOP_SPEED_RPM));
            if (motor->state_timer > 8500 && speed_diff < OPEN_LOOP_SPEED_RPM * 0.1f && fabs(angle_error) < 0.1f)
            {
                FOC_Open_Convert_Prepare(motor, motor_num);
            }
        }
#endif

        break;

    case MOTOR_STATE_CLOSE:
        // 3. 闭环运行
#if !FOC_SENSOR_EN
        // 闭环期间若遥控器归零 → 回 IDLE
        if (motor->control_mode == FOC_CONTROL_SPEED && Foc_Safe_Protect(motor->target_speed))
        {
            // 先归零PWM再切状态
            motor->hal.pwm_set_duty(motor->num,
                PWM_ARR / 2, PWM_ARR / 2, PWM_ARR / 2);
            // 同时清空SMO残留状态，防止下次重启时观测器从错误状态收敛
            motor->e_ab.alpha     = 0.0f;
            motor->e_ab.beta      = 0.0f;
            motor->i_ab_hat.alpha = 0.0f;
            motor->i_ab_hat.beta  = 0.0f;
            motor->speed_observer = 0.0f;
            motor->speed_sign     = 1.0f;
            motor->mode = MOTOR_STATE_IDLE;
            break;
        }
#endif

        // 判断速度模式下，目标速度与运行速度的符号一致
        if (motor->control_mode == FOC_CONTROL_SPEED)
        {
            float run_sign    = (motor->speed_ramp_target >= 0.0f) ? 1.0f : -1.0f;
            float target_sign = (motor->target_speed      >= 0.0f) ? 1.0f : -1.0f;
            if (run_sign != target_sign)
            {
                // 关闭PWM输出，等惯性停下
                motor->hal.pwm_set_duty(motor->num, PWM_ARR/2, PWM_ARR/2, PWM_ARR/2);
                motor->mode = MOTOR_STATE_IDLE;
                break;
            }
        }
        Foc_Close_Loop(motor, TS);
        break;
    }
    return FOC_OK;
}

uint8_t Foc_Safe_Protect(float speed)
{
    uint8_t safe_flag = 0; // 安全保护标志,0:正常 1:异常

#if FOC_SENSOR_EN
    safe_flag = 0;
#else
    safe_flag = fabsf(speed) >= SPEED_START_THRESHOLD;
#endif
    return safe_flag;
}

/**
 * @brief 轴对齐
 * 
 * @param motor 
 * @param dt 
 * @return foc_state_t 
 */
foc_state_t Foc_Align_Loop(foc_handle_t *motor, float dt)
{
    // 1. 定位阶段：给 D 轴施加固定电压，Q 轴为 0，强制转子对齐到 0 度
    foc_set_udq_fx(motor, FOC_Q15FromVoltage(2.0f), 0);
    Foc_SetElectricalAngle(motor, 0.0f);
    motor->pi_pll.integral = 0;
    motor->theta_Observer = 0.0f;
    motor->theta_obs_prev = 0.0f;

    if (motor->sensor_mech.vaild != 0.0f)
    {
        if (motor->sensor_mech.sample_seq != motor->sensor_mech.align_prev_sample_seq)
        {
            float angle = motor->sensor_mech.angle;
            motor->sensor_mech.align_prev_sample_seq = motor->sensor_mech.sample_seq;

            if (motor->sensor_mech.align_has_prev == 0U)
            {
                motor->sensor_mech.align_prev_angle = angle;
                motor->sensor_mech.align_stable_count = 0U;
                motor->sensor_mech.align_has_prev = 1U;
            }
            else
            {
                float delta = foc_wrap_delta_pm_pi(angle - motor->sensor_mech.align_prev_angle);
                motor->sensor_mech.align_prev_angle = angle;

                if (fabsf(delta) <= FOC_ALIGN_STABLE_DELTA_RAD)
                {
                    if (motor->sensor_mech.align_stable_count < FOC_ALIGN_STABLE_COUNT)
                        motor->sensor_mech.align_stable_count++;
                }
                else
                {
                    motor->sensor_mech.align_stable_count = 0U;
                }
            }

            if ((motor->sensor_mech.zero_offset_locked == 0U) &&
                (motor->sensor_mech.align_stable_count >= FOC_ALIGN_STABLE_COUNT))
            {
                motor->sensor_mech.zero_offset = angle;
                motor->sensor_mech.zero_offset_locked = 1U;
            }
        }
    }
    else
    {
        motor->sensor_mech.align_stable_count = 0U;
        motor->sensor_mech.align_has_prev = 0U;
    }
    
    Foc_RefreshTrigCache(motor);
    FOC_InvPark_Transform_Fx(motor);
    FOC_SVPWM_Generate_Fx(motor);
    return FOC_OK;
}

/**
 * @brief 开环控制
 * 
 * @param motor 
 * @param dt 
 * @return foc_state_t 
 */
foc_state_t Foc_Open_Loop(foc_handle_t *motor, float dt)
{
    foc_state_t foc_state = Foc_Preprocess_CurrentSample(motor);

    // 3. Clark变换，
    FOC_Clark_Transform_Fx(motor);

#if FOC_SMO_EN // 观测器使能
    // 4. smo观测器推算转子位置，得到电角度和转速
    SMO_Observer(motor, dt, MOTOR_STATE_OPEN);
#endif

#if FOC_OPEN_I_DEBUG_EN // 开环电流环调试代码使能
    // 固定角度为0，不依赖观测器
    // Park变换
    motor->i_dq_fx.d = motor->i_ab_fx.alpha;
    motor->i_dq_fx.q = motor->i_ab_fx.beta;

    // d轴电流阶跃信号
    vofa_cnt++;
    if (vofa_cnt >= 34000)
        vofa_cnt = 0;

    if (vofa_cnt >= 30000)
        motor->pi_d_fx.target = FOC_Q15FromCurrentPu(FOC_CurrentToPu(CURRENT_LOOP_STEP_HIGH_A));
    else
        motor->pi_d_fx.target = FOC_Q15FromCurrentPu(FOC_CurrentToPu(CURRENT_LOOP_STEP_LOW_A));
    // motor->pi_d_fx.target = FOC_Q15FromCurrentPu(FOC_CurrentToPu(2.0f));
    motor->pi_q_fx.target = 0;
#if FOC_RUNTIME_FLOAT_SHADOW
    motor->pi_d.target = FOC_Q15ToFloat(motor->pi_d_fx.target);
    motor->pi_q.target = 0.0f;
#endif

    motor->pi_d_fx.feedback = motor->i_dq_fx.d;
    motor->pi_q_fx.feedback = motor->i_dq_fx.q;
    motor->pi_d_fx.limit = FOC_Q15_MAX;
    motor->pi_q_fx.limit = FOC_Q15_MAX;

    FOC_PI_Regulator_Fx(&motor->pi_d_fx); // pid计算
    FOC_PI_Regulator_Fx(&motor->pi_q_fx); // pid计算
    foc_set_udq_fx(motor, motor->pi_d_fx.output, motor->pi_q_fx.output);

    Foc_SetElectricalAngle(motor, 0.0f);
    Foc_RefreshTrigCache(motor);
#else
    Foc_RefreshTrigCache(motor);
    FOC_Park_Transform_Fx(motor);

    foc_set_udq_fx(motor, 0, FOC_Q15FromVoltagePu(FOC_VoltageToPu(PWM_VBUS * 0.35f)));

    Foc_AdvanceOpenLoopAngle(motor, dt);
#endif

    // 3. 反Park变换
    FOC_InvPark_Transform_Fx(motor);
    // 4. SVPWM生成并输出
    FOC_SVPWM_Generate_Fx(motor);
    return foc_state;
}

/**
 * @brief 闭环控制
 * 
 * @param motor 
 * @param dt 
 * @return foc_state_t 
 */
void Foc_Update_SpeedLoop(uint8_t motor_num, float dt)
{
    foc_handle_t *motor = &FOC_Motor[motor_num];

    if (motor->init_done != 1U || motor->mode != MOTOR_STATE_CLOSE)
        return;

#if FOC_SPEED_PI_EN
    // speed_loop_target 保持物理RPM，仅在进入定点PI前标幺化
    float speed_loop_target = motor->speed_ramp_target;

#if FOC_POSITION_PI_EN
    if (motor->control_mode == FOC_CONTROL_POSITION)
    {
        float position_error = motor->target_position - motor->position;
        if (fabsf(position_error) < POSITION_DEADBAND_RAD)
        {
            motor->pi_position.integral = 0.0f;
            motor->pi_position.output = 0.0f;
            motor->pi_position_fx.integral = 0;
            motor->pi_position_fx.output = 0;
            speed_loop_target = 0.0f;
        }
        else
        {
            // 位置环库内标幺：输入rad，输出pu速度；ki_dt用真实dt
            motor->pi_position_fx.target = FOC_FloatToQ16_16(motor->target_position);
            motor->pi_position_fx.feedback = FOC_FloatToQ16_16(motor->position);
            motor->pi_position_fx.ki_dt = FOC_FloatToQ16_16(PI_KI_POSITION_PU * dt);
            FOC_PI_Regulator_Q16(&motor->pi_position_fx);
            foc_sync_pi_shadow_from_q16(&motor->pi_position, &motor->pi_position_fx);
            // pu速度输出转回物理RPM，供速度环RPM接口使用
            speed_loop_target = FOC_SpeedPuToRpm(FOC_Q16_16ToFloat(motor->pi_position_fx.output));
#if HFI_ENABLE
            if (!motor->hfi_enable && motor->position_dir != 0.0f && speed_loop_target * motor->position_dir < 0.0f)
                speed_loop_target = 0.0f;
#else
            if (motor->position_dir != 0.0f && speed_loop_target * motor->position_dir < 0.0f)
                speed_loop_target = 0.0f;
#endif
        }
        motor->pi_speed.target = speed_loop_target;
        motor->speed_ramp_target = speed_loop_target;
    }
    else
#endif
    {
        if (motor->target_speed > motor->speed_ramp_target)
        {
            motor->speed_ramp_target += SPEED_RAMP_RATE * dt;
            if (motor->speed_ramp_target > motor->target_speed)
                motor->speed_ramp_target = motor->target_speed;
        }
        else if (motor->target_speed < motor->speed_ramp_target)
        {
            motor->speed_ramp_target -= SPEED_RAMP_RATE * dt;
            if (motor->speed_ramp_target < motor->target_speed)
                motor->speed_ramp_target = motor->target_speed;
        }
        speed_loop_target = motor->speed_ramp_target;
    }

    {
        // 速度环库内全程标幺：pu速度误差 -> pu电流指令
        motor->pi_speed_fx.target   = FOC_FloatToQ16_16(FOC_SpeedRpmToPu(speed_loop_target));
        motor->pi_speed_fx.feedback = FOC_FloatToQ16_16(FOC_SpeedRpmToPu(motor->speed));
        motor->pi_speed_fx.ki_dt    = FOC_FloatToQ16_16(PI_KI_SPEED_PU * dt);
        FOC_PI_Regulator_Q16(&motor->pi_speed_fx);
        foc_sync_pi_shadow_from_q16(&motor->pi_speed, &motor->pi_speed_fx);

        // 输出即pu电流，直接作为q轴电流环目标（ISR内 foc_sync_current_targets_to_fx 会转Q15）
        motor->pi_q.target = FOC_Q16_16ToFloat(motor->pi_speed_fx.output);
    }
#endif
}

foc_state_t Foc_Close_Loop(foc_handle_t *motor, float dt)
{
    foc_state_t foc_state = FOC_OK;
#if FW_ENABLE || FOC_CLOSE_I_DEBUG_EN
    const float current_target_limit_sq = CURRENT_TARGET_LIMIT_PU * CURRENT_TARGET_LIMIT_PU;
#endif
    // pi输出限幅缓启动
    foc_q15_t pi_limit_fx;

    if (motor->close_cnt < 500)
    {
        float pi_limit_v;
        motor->close_cnt++;
        pi_limit_v = 3.0f + motor->close_cnt * 0.007f;
        pi_limit_fx = FOC_Q15FromVoltagePu(FOC_VoltageToPu(pi_limit_v));
    }
    else
    {
        pi_limit_fx = FOC_Q15FromVoltagePu(FOC_VOLTAGE_LIMIT_PU);
    }

    // 电流前处理：减零偏、按A做保护判断，再写入p.u.
    foc_state = Foc_Preprocess_CurrentSample(motor);

    // Clark变换，
    FOC_Clark_Transform_Fx(motor);

    uint8_t trig_dirty = 0U;

#if FOC_SMO_EN // 观测器使能
    // MRAS观测器推算转子位置，得到电角度和转速
    SMO_Observer(motor, dt, MOTOR_STATE_CLOSE);
    trig_dirty = 1U;
#else
    trig_dirty = Foc_LoadClosedLoopSensorAngle(motor, dt);
#endif

#if HFI_ENABLE // HFI使能
    if (motor->hfi_enable || trig_dirty != 0U)
    {
        HFI_Select_Angle(motor, dt);
        trig_dirty = 1U;
    }
#endif

    if (trig_dirty != 0U)
        Foc_RefreshTrigCache(motor);

    FOC_Park_Transform_Fx(motor);
#if HFI_ENABLE // HFI使能
    HFI_Process_Current(motor, dt);
#endif

#if FOC_POSITION_PI_EN
    if (motor->control_mode == FOC_CONTROL_POSITION)
    {
        float position_error = motor->target_position - motor->position;
        uint8_t position_crossed = (motor->position_dir != 0.0f && position_error * motor->position_dir <= POSITION_DEADBAND_RAD);
#if HFI_ENABLE
        if (motor->hfi_enable)
            position_crossed = 0;
#endif
        if (fabsf(motor->speed) > POSITION_OVERSPEED_RPM || position_crossed)
        {
            motor->target_speed = 0.0f;
            motor->speed_ramp_target = 0.0f;
            motor->pi_speed.target = 0.0f;
            motor->pi_speed.integral = 0.0f;
            motor->pi_speed.output = 0.0f;
            motor->pi_speed_fx.target = 0;
            motor->pi_speed_fx.integral = 0;
            motor->pi_speed_fx.output = 0;
            motor->pi_position.integral = 0.0f;
            motor->pi_position.output = 0.0f;
            motor->pi_position_fx.target = 0;
            motor->pi_position_fx.integral = 0;
            motor->pi_position_fx.output = 0;
            motor->pi_q.target = 0.0f;
            motor->pi_q.integral = 0.0f;
            motor->pi_q_fx.target = 0;
            motor->pi_q_fx.integral = 0;
            motor->pi_q_fx.output = 0;
            motor->position_dir = 0.0f;
            motor->control_mode = FOC_CONTROL_SPEED;
            motor->hal.pwm_set_duty(motor->num, PWM_ARR / 2, PWM_ARR / 2, PWM_ARR / 2);
            motor->mode = MOTOR_STATE_IDLE;
            return foc_state;
        }
    }
#endif

// 6. 速度环已搬到前台主循环，ISR 内只保留电流环
    motor->pi_d.target = 0.0f;

#if FW_ENABLE // 弱磁
    FOC_FieldWeakening(motor, TS);
#endif

#if FOC_CLOSE_I_DEBUG_EN // 闭环电流环调试代码
    vofa_cnt++;
    if(vofa_cnt >= 17000 && vofa_cnt < 34000)
    {
        motor->pi_d_fx.target = FOC_Q15FromCurrentPu(FOC_CurrentToPu(CURRENT_LOOP_STEP_HIGH_A));
    }
    else if(vofa_cnt > 0 && vofa_cnt < 17000)
        motor->pi_d_fx.target = FOC_Q15FromCurrentPu(FOC_CurrentToPu(CURRENT_LOOP_STEP_LOW_A));
    else
        vofa_cnt = 0;
    motor->pi_q_fx.target = 0;
#elif FW_ENABLE // 弱磁
    float id_target = motor->pi_d.target;
    float iq_target_limit;

    if (id_target > CURRENT_TARGET_LIMIT_PU)
        id_target = CURRENT_TARGET_LIMIT_PU;
    else if (id_target < -CURRENT_TARGET_LIMIT_PU)
        id_target = -CURRENT_TARGET_LIMIT_PU;

    if (id_target == 0.0f)
    {
        iq_target_limit = CURRENT_TARGET_LIMIT_PU;
    }
    else
    {
        float iq_limit_sq = current_target_limit_sq - id_target * id_target;
        if (iq_limit_sq < 0.0f)
            iq_limit_sq = 0.0f;
        iq_target_limit = sqrtf(iq_limit_sq);
    }

    motor->pi_d.target = id_target;
    if (motor->pi_q.target > iq_target_limit)
        motor->pi_q.target = iq_target_limit;
    else if (motor->pi_q.target < -iq_target_limit)
        motor->pi_q.target = -iq_target_limit;
#else
    motor->pi_d.target = 0.0f;
#endif

    // 6. 电流环PI调节
#if FOC_RUNTIME_FLOAT_SHADOW
    motor->pi_d.limit = FOC_Q15ToFloat(pi_limit_fx);
    motor->pi_q.limit = motor->pi_d.limit;
#endif
    motor->pi_d_fx.limit = pi_limit_fx;
    motor->pi_q_fx.limit = pi_limit_fx;
    motor->pi_d_fx.feedback = motor->i_dq_fx.d;
    motor->pi_q_fx.feedback = motor->i_dq_fx.q;
    foc_sync_current_targets_to_fx(motor);

    FOC_PI_Regulator_Fx(&motor->pi_d_fx);
    FOC_PI_Regulator_Fx(&motor->pi_q_fx);
#if FOC_RUNTIME_FLOAT_SHADOW
    foc_sync_pi_shadow_from_fx(&motor->pi_d, &motor->pi_d_fx);
    foc_sync_pi_shadow_from_fx(&motor->pi_q, &motor->pi_q_fx);
#endif

    foc_set_udq_fx(motor, motor->pi_d_fx.output, motor->pi_q_fx.output);

    {
        foc_q15_t voltage_mag_fx = FOC_FastNorm_Fx(motor->u_dq_fx.d, motor->u_dq_fx.q);
        if (voltage_mag_fx > pi_limit_fx)
        {
            foc_accum_t scale_fx = ((foc_accum_t)pi_limit_fx << 15) / voltage_mag_fx;
            motor->u_dq_fx.d = FOC_Q15Clamp((scale_fx * motor->u_dq_fx.d + FOC_Q15_ROUND) >> 15);
            motor->u_dq_fx.q = FOC_Q15Clamp((scale_fx * motor->u_dq_fx.q + FOC_Q15_ROUND) >> 15);
            motor->pi_d_fx.output = motor->u_dq_fx.d;
            motor->pi_q_fx.output = motor->u_dq_fx.q;
            foc_set_udq_fx(motor, motor->u_dq_fx.d, motor->u_dq_fx.q);
#if FOC_RUNTIME_FLOAT_SHADOW
            foc_sync_pi_shadow_from_fx(&motor->pi_d, &motor->pi_d_fx);
            foc_sync_pi_shadow_from_fx(&motor->pi_q, &motor->pi_q_fx);
#endif
        }
    }
#if HFI_ENABLE // 高频注入
    HFI_Add_Voltage(motor, dt);
    foc_set_udq_fx(motor,
        FOC_Q15FromVoltagePu(motor->u_dq.d),
        FOC_Q15FromVoltagePu(motor->u_dq.q));
#endif

    // 7. 反Park变换
    FOC_InvPark_Transform_Fx(motor);

    // 8. SVPWM生成并输出
    FOC_SVPWM_Generate_Fx(motor);
    return foc_state;
}

/**
 * @brief foc失能
 * 
 * @param motor 
 * @return foc_state_t 
 */
foc_state_t Foc_Stop(uint8_t motor_num)
{
    foc_handle_t *motor = &FOC_Motor[motor_num];
    motor->target_speed = 0.0f;
    motor->pi_speed.target = 0.0f;
    motor->speed_ramp_target = 0.0f;
    motor->id_fw = 0.0f;
    motor->fw_active = 0.0f;
    motor->fw_voltage = 0.0f;
    motor->control_mode = FOC_CONTROL_SPEED;
    motor->pi_speed_fx.target = 0;
    motor->pi_speed_fx.integral = 0;
    motor->pi_speed_fx.output = 0;
    motor->pi_position.integral = 0.0f;
    motor->pi_position.output = 0.0f;
    motor->pi_position_fx.target = 0;
    motor->pi_position_fx.integral = 0;
    motor->pi_position_fx.output = 0;
    motor->pi_d_fx.target = 0;
    motor->pi_d_fx.integral = 0;
    motor->pi_d_fx.output = 0;
    motor->pi_q_fx.target = 0;
    motor->pi_q_fx.integral = 0;
    motor->pi_q_fx.output = 0;
    motor->position_dir = 0.0f;
#if HFI_ENABLE
    HFI_Disable(motor);
#endif
    motor->hal.drv_disable(motor_num); // 驱动失能
    return FOC_OK;
}

/**
 * @brief 设置目标速度
 * 
 * @param motor 
 * @param speed 
 * @return foc_state_t 
 */
foc_state_t Foc_Set_Speed(uint8_t motor_num, float speed)
{
    foc_handle_t *motor = &FOC_Motor[motor_num];
    if (motor->control_mode != FOC_CONTROL_SPEED)
    {
        // 说明还在位置环
        motor->pi_position.integral = 0.0f;
        motor->pi_position.output = 0.0f;
        motor->pi_position_fx.target = 0;
        motor->pi_position_fx.integral = 0;
        motor->pi_position_fx.output = 0;
        motor->pi_speed.integral = 0.0f;
        motor->pi_speed_fx.integral = 0;
        motor->pi_speed_fx.output = 0;
    }
    motor->control_mode = FOC_CONTROL_SPEED;
    if (fabsf(motor->target_speed - speed) > 1.0f)
    {
        motor->id_fw = 0.0f;
        motor->fw_active = 0.0f;
        motor->fw_voltage = 0.0f;
        }
    motor->target_speed = speed;
    // pi_speed(_fx).target 由 Foc_Update_SpeedLoop 每拍按pu重算，这里只更新物理命令
    return FOC_OK;
}

foc_state_t Foc_Set_Position(uint8_t motor_num, float position_rad)
{
    foc_handle_t *motor = &FOC_Motor[motor_num];
    if (motor->mode != MOTOR_STATE_CLOSE)
    {
#if HFI_ENABLE
        if (motor->hfi_enable)
        {
            float position_error = position_rad - motor->position;
            motor->control_mode = FOC_CONTROL_POSITION;
            motor->target_position = position_rad;
            motor->position_dir = fabsf(position_error) > POSITION_DEADBAND_RAD ? (position_error > 0.0f ? 1.0f : -1.0f) : 1.0f;
            motor->target_speed = motor->position_dir * OPEN_LOOP_SPEED_RPM;
            return FOC_OK;
        }
#endif
        motor->target_position = position_rad;
        return FOC_ERR_LOOP;
    }

    if (motor->control_mode != FOC_CONTROL_POSITION || fabsf(position_rad - motor->target_position) > POSITION_DEADBAND_RAD)
    {
        float position_error = position_rad - motor->position;
        motor->pi_position.integral = 0.0f;
        motor->pi_position.output = 0.0f;
        motor->pi_position_fx.integral = 0;
        motor->pi_position_fx.output = 0;
        motor->pi_speed.integral = 0.0f;
        motor->pi_speed_fx.integral = 0;
        motor->pi_speed_fx.output = 0;
        motor->position_dir = fabsf(position_error) > POSITION_DEADBAND_RAD ? (position_error > 0.0f ? 1.0f : -1.0f) : 0.0f;
    }

    motor->control_mode = FOC_CONTROL_POSITION;
    motor->target_position = position_rad;
    motor->target_speed = motor->position_dir * PI_LIMIT_POSITION_RPM;
    motor->pi_position_fx.target = FOC_FloatToQ16_16(position_rad);

    return FOC_OK;
}

foc_state_t Foc_Set_Control_Mode(uint8_t motor_num, foc_control_mode_t mode)
{
    if (mode != FOC_CONTROL_SPEED && mode != FOC_CONTROL_POSITION)
        return FOC_ERR_INVALID_PARAM;

    foc_handle_t *motor = &FOC_Motor[motor_num];
    if (motor->control_mode == mode)
        return FOC_OK;

    motor->control_mode = mode;
    motor->pi_position.integral = 0.0f;
    motor->pi_position.output = 0.0f;
    motor->pi_position_fx.target = 0;
    motor->pi_position_fx.integral = 0;
    motor->pi_position_fx.output = 0;
    motor->pi_speed.integral = 0.0f;
    motor->pi_speed_fx.target = 0;
    motor->pi_speed_fx.integral = 0;
    motor->pi_speed_fx.output = 0;
    motor->position_dir = 0.0f;

    if (mode == FOC_CONTROL_POSITION)
    {
        motor->target_position = motor->position;
        motor->pi_position_fx.target = FOC_FloatToQ16_16(motor->position);
    }

    return FOC_OK;
}

foc_state_t Foc_Zero_Position(uint8_t motor_num)
{
    foc_handle_t *motor = &FOC_Motor[motor_num];
    motor->position_offset = motor->position_raw;
    motor->position = 0.0f;
    motor->target_position = 0.0f;
    motor->pi_position.integral = 0.0f;
    motor->pi_position.output = 0.0f;
    motor->pi_position_fx.target = 0;
    motor->pi_position_fx.integral = 0;
    motor->pi_position_fx.output = 0;
    motor->position_dir = 0.0f;
    return FOC_OK;
}

float Foc_Get_Position(uint8_t motor_num)
{
    return FOC_Motor[motor_num].position;
}

foc_state_t Foc_GetCurrentLoopDebug(uint8_t motor_num, foc_current_loop_debug_t *debug)
{
    foc_handle_t *motor;

    if (debug == 0 || motor_num == 0U || motor_num > MAX_MOTOR_NUM)
        return FOC_ERR_INVALID_PARAM;

    motor = &FOC_Motor[motor_num];
    debug->speed = motor->speed;
    debug->speed_feedback = FOC_Q16ToSpeedRpm(motor->pi_speed_fx.feedback);
    debug->speed_target = FOC_Q16ToSpeedRpm(motor->pi_speed_fx.target);
    debug->id = FOC_Q15ToCurrent(motor->i_dq_fx.d);
    debug->id_target = FOC_Q15ToCurrent(motor->pi_d_fx.target);
    debug->id_feedback = FOC_Q15ToCurrent(motor->pi_d_fx.feedback);
    debug->ud_output = FOC_Q15ToVoltage(motor->pi_d_fx.output);
    debug->iq_target = FOC_Q15ToCurrent(motor->pi_q_fx.target);
    debug->iq_feedback = FOC_Q15ToCurrent(motor->pi_q_fx.feedback);
    debug->uq_output = FOC_Q15ToVoltage(motor->pi_q_fx.output);
    debug->Sensor_zero_offset_locked = motor->sensor_mech.zero_offset_locked * 1.0f;
    return FOC_OK;
}

foc_handle_t *Foc_GetStruct(uint8_t motor_num)
{
    return &FOC_Motor[motor_num];
}

#if HFI_ENABLE
foc_state_t Foc_HFI_Enable(uint8_t motor_num)
{
    HFI_Enable(&FOC_Motor[motor_num]);
    return FOC_OK;
}

foc_state_t Foc_HFI_Disable(uint8_t motor_num)
{
    HFI_Disable(&FOC_Motor[motor_num]);
    return FOC_OK;
}

uint8_t Foc_HFI_Is_Valid(uint8_t motor_num)
{
    return FOC_Motor[motor_num].hfi_valid;
}

float Foc_HFI_Get_Angle(uint8_t motor_num)
{
    return FOC_Motor[motor_num].theta_hfi;
}
#endif




