#include "hfi.h"

#ifdef HFI_ENABLE
#include "foc_math.h"
#include "foc_utils.h"

static float HFI_Wrap_Angle(float angle)
{
    angle = fmodf(angle, _2_PI);
    if (angle < 0.0f)
        angle += _2_PI;
    return angle;
}

static float HFI_Wrap_Diff(float angle)
{
    if (angle > PI)
        angle -= _2_PI;
    else if (angle < -PI)
        angle += _2_PI;
    return angle;
}

static float HFI_Clamp(float value, float limit)
{
    if (value > limit)
        return limit;
    if (value < -limit)
        return -limit;
    return value;
}

void HFI_Init(foc_handle_t *motor)
{
    motor->hfi_enable = 0;
    motor->hfi_valid = 0;
    motor->hfi_warmup_cnt = 0;
    motor->theta_hfi = 0.0f;
    motor->theta_hfi_prev = 0.0f;
    motor->speed_hfi_observer = 0.0f;
    motor->hfi_pll_integral = 0.0f;
    motor->hfi_phase = 0.0f;
    motor->hfi_v_inj = 0.0f;
    motor->hfi_iq_lpf = 0.0f;
    motor->hfi_iq_hf = 0.0f;
    motor->hfi_demod = 0.0f;
    motor->hfi_error = 0.0f;
    motor->hfi_blend = 0.0f;
}

void HFI_Reset_Angle(foc_handle_t *motor, float theta)
{
    motor->theta_hfi = HFI_Wrap_Angle(theta);
    motor->theta_hfi_prev = motor->theta_hfi;
    motor->speed_hfi_observer = 0.0f;
    motor->hfi_pll_integral = 0.0f;
    motor->hfi_phase = 0.0f;
    motor->hfi_v_inj = 0.0f;
    motor->hfi_iq_lpf = motor->i_dq.q;
    motor->hfi_iq_hf = 0.0f;
    motor->hfi_demod = 0.0f;
    motor->hfi_error = 0.0f;
    motor->hfi_valid = 0;
    motor->hfi_warmup_cnt = HFI_WARMUP_CYCLES;
}

void HFI_Enable(foc_handle_t *motor)
{
    motor->hfi_enable = 1;
    HFI_Reset_Angle(motor, motor->theta);
}

void HFI_Disable(foc_handle_t *motor)
{
    motor->hfi_enable = 0;
    motor->hfi_valid = 0;
    motor->hfi_warmup_cnt = 0;
    motor->hfi_blend = 0.0f;
    motor->hfi_v_inj = 0.0f;
    motor->hfi_iq_hf = 0.0f;
    motor->hfi_demod = 0.0f;
    motor->hfi_error = 0.0f;
}

void HFI_Select_Angle(foc_handle_t *motor, float dt)
{
    (void)dt;

    if (!motor->hfi_enable)
    {
        motor->hfi_blend = 0.0f;
        return;
    }

    float smo_speed_rpm = motor->speed;
    float speed_abs = fabsf(smo_speed_rpm);

    // 计算HFI角度的权重
    if (speed_abs <= HFI_USE_SPEED_RPM)
    {
        motor->hfi_blend = 1.0f;
    }
    else if (speed_abs < HFI_BLEND_END_RPM)
    {
        motor->hfi_blend = (HFI_BLEND_END_RPM - speed_abs) / (HFI_BLEND_END_RPM - HFI_USE_SPEED_RPM);
    }
    else
    {
        motor->hfi_blend = 0.0f;
    }

    if (motor->hfi_blend > 0.0f)
    {
        float angle_diff = HFI_Wrap_Diff(motor->theta_hfi - motor->theta_Observer);
        motor->theta = HFI_Wrap_Angle(motor->theta_Observer + angle_diff * motor->hfi_blend);

        float hfi_speed_rpm = FOC_ElecRadPerSecToMechRpm(motor->speed_hfi_observer);
        motor->speed = smo_speed_rpm * (1.0f - motor->hfi_blend) + hfi_speed_rpm * motor->hfi_blend;
    }
    else
    {
        motor->theta = motor->theta_Observer;
    }
}

void HFI_Process_Current(foc_handle_t *motor, float dt)
{
    if (!motor->hfi_enable || motor->hfi_blend <= 0.0f)
        return;

    if (motor->hfi_warmup_cnt > 0)
    {
        motor->hfi_warmup_cnt--;
        motor->hfi_iq_lpf = motor->i_dq.q;
        motor->hfi_iq_hf = 0.0f;
        motor->hfi_demod = 0.0f;
        motor->hfi_error = 0.0f;
        return;
    }

    motor->hfi_iq_lpf += (motor->i_dq.q - motor->hfi_iq_lpf) * HFI_IQ_LPF_ALPHA;
    motor->hfi_iq_hf = motor->i_dq.q - motor->hfi_iq_lpf;
    if (fabsf(motor->hfi_iq_hf) > HFI_IQ_HF_LIMIT_PU)
    {
        HFI_Disable(motor);
        return;
    }

    float carrier = 0.0f;
    if (HFI_INJECTION_VOLTAGE_PU > 0.0f)
        carrier = motor->hfi_v_inj / HFI_INJECTION_VOLTAGE_PU;

    float demod = motor->hfi_iq_hf * carrier;
    motor->hfi_demod += (demod - motor->hfi_demod) * HFI_DEMOD_LPF_ALPHA;
    motor->hfi_error = HFI_ERROR_SIGN * motor->hfi_demod;
    motor->hfi_valid = (fabsf(motor->hfi_iq_hf) > HFI_MIN_RESPONSE_PU) ? 1 : motor->hfi_valid;

    motor->hfi_pll_integral += HFI_PLL_KI * motor->hfi_error * dt;
    motor->hfi_pll_integral = HFI_Clamp(motor->hfi_pll_integral, HFI_PLL_LIMIT);

    motor->speed_hfi_observer = HFI_PLL_KP * motor->hfi_error + motor->hfi_pll_integral;
    motor->speed_hfi_observer = HFI_Clamp(motor->speed_hfi_observer, HFI_PLL_LIMIT);

    motor->theta_hfi = HFI_Wrap_Angle(motor->theta_hfi + motor->speed_hfi_observer * dt);
}

void HFI_Add_Voltage(foc_handle_t *motor, float dt)
{
    if (!motor->hfi_enable || motor->hfi_blend <= 0.0f || motor->hfi_warmup_cnt > 0)
    {
        motor->hfi_v_inj = 0.0f;
        return;
    }

    motor->hfi_phase += _2_PI * HFI_INJECTION_FREQ * dt;
    motor->hfi_phase = HFI_Wrap_Angle(motor->hfi_phase);
    motor->hfi_v_inj = HFI_INJECTION_VOLTAGE_PU * sinf(motor->hfi_phase) * motor->hfi_blend;

    motor->u_dq.d += motor->hfi_v_inj;
    motor->u_dq.d = HFI_Clamp(motor->u_dq.d, FOC_VOLTAGE_LIMIT_PU);
}
#endif
