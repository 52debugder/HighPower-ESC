/* field_weakening.c */
#include "field_weakening.h"
#include "foc_math.h"

void FOC_FieldWeakening(foc_handle_t *motor, float dt)
{
#ifdef FW_ENABLE
    float vd; // d轴电压
    float vq; // q轴电压
    float vs; // dq轴电压矢量和幅值
    float voltage_limit; // 弱磁电压幅值
    float voltage_enter; // 弱磁电压进入门限
    float voltage_exit; // 弱磁电压退出门限
    float id_fw_new;
    float delta;
    float delta_max;
    float id_limit;
    float speed_abs;
    float target_abs;
    float fw_ki_scale;

    vd = motor->u_dq.d;
    vq = motor->u_dq.q;
    vs = sqrtf(vd * vd + vq * vq);
    motor->fw_voltage = vs;

    voltage_limit = FOC_VOLTAGE_LIMIT_PU;
    voltage_enter = voltage_limit * FW_VOLTAGE_THRESHOLD;
    voltage_exit = voltage_limit * FW_VOLTAGE_EXIT_THRESHOLD;

    speed_abs = fabsf(motor->speed);
    target_abs = fabsf(motor->target_speed);

    if (target_abs < SPEED_START_THRESHOLD)
    {
        motor->id_fw = 0.0f;
    }
    else
    {
        if (vs > voltage_enter && speed_abs < target_abs)
        {
            fw_ki_scale = (speed_abs < target_abs - FW_TARGET_HOLD_MARGIN_RPM) ? 1.0f : FW_HOLD_KI_SCALE;
            id_fw_new = motor->id_fw - FW_KI * fw_ki_scale * (vs - voltage_enter) * dt;
            delta = id_fw_new - motor->id_fw;
            delta_max = 0.05f;
            if (delta < -delta_max) delta = -delta_max;
            if (delta >  delta_max) delta = delta_max;
            motor->id_fw += delta;
        }
        else if (vs < voltage_exit ||
                 speed_abs > target_abs + FW_SPEED_MARGIN_RPM)
        {
            if (motor->id_fw < 0.0f)
            {
                motor->id_fw += FW_KI * FW_EXIT_RATE * dt;
                if (motor->id_fw > 0.0f)
                    motor->id_fw = 0.0f;
            }
        }
    }

    id_limit = fminf(FW_ID_MAX_PU, CURRENT_TARGET_LIMIT_PU);
    if (motor->id_fw < -id_limit)
        motor->id_fw = -id_limit;
    if (motor->id_fw > 0.0f)
        motor->id_fw = 0.0f;

    motor->fw_active = (motor->id_fw < 0.0f) ? 1.0f : 0.0f;
    motor->target_id = motor->id_fw;
    motor->pi_d.target = motor->id_fw;
#else
    motor->target_id = 0.0f;
    motor->id_fw = 0.0f;
    motor->fw_active = 0.0f;
    motor->fw_voltage = 0.0f;
#endif
}
