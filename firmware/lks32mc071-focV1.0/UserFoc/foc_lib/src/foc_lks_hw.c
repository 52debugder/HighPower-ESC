#include "foc_lks_hw.h"

#include "drv8353.h"
#include "foc_config.h"
#include "hardware_init.h"

extern void SoftDelay(u32 cnt);

static uint8_t foc_lks_hw_valid_motor(uint8_t motor)
{
    return (motor == ESC_MOTOR_ID);
}

static uint16_t foc_lks_hw_limit_adc(int32_t adc)
{
    if (adc < 0)
        return 0U;
    if (adc > (int32_t)ESC_ADC_MAX)
        return (uint16_t)ESC_ADC_MAX;
    return (uint16_t)adc;
}

void foc_lks_hw_init(uint8_t motor)
{
    if (!foc_lks_hw_valid_motor(motor))
        return;

    ESC_PWM_Disable();
    ESC_PWM_SetSafeDuty();
    DRV8353_Init();
    DRV8353_Disable();
}

void foc_lks_hw_pwm_start(uint8_t motor)
{
    if (!foc_lks_hw_valid_motor(motor))
        return;

    ESC_PWM_SetSafeDuty();
}

void foc_lks_hw_pwm_disable(uint8_t motor)
{
    if (!foc_lks_hw_valid_motor(motor))
        return;

    ESC_PWM_Disable();
    ESC_PWM_SetSafeDuty();
}

void foc_lks_hw_pwm_set(uint8_t motor, uint16_t duty_u, uint16_t duty_v, uint16_t duty_w)
{
    if (!foc_lks_hw_valid_motor(motor))
        return;

    ESC_PWM_SetDuty(duty_u, duty_v, duty_w);
}

void foc_lks_hw_drv_enable(uint8_t motor)
{
    uint8_t drv_status;

    if (!foc_lks_hw_valid_motor(motor))
        return;

    ESC_PWM_Disable();
    ESC_PWM_SetSafeDuty();
    DRV8353_Enable();

    drv_status = DRV8353_ConfigureDefault();
//    while(1)
//    {
//        DRV8353_ReadReg(0x03);
//    }
    if (drv_status != DRV8353_CONFIG_OK)
    {
        ESC_PWM_Disable();
        return;
    }

    ESC_PWM_Enable();
}

void foc_lks_hw_drv_disable(uint8_t motor)
{
    if (!foc_lks_hw_valid_motor(motor))
        return;

    ESC_PWM_Disable();
    ESC_PWM_SetSafeDuty();
    DRV8353_Disable();
}

void foc_lks_hw_adc_get(uint8_t motor, uint16_t *adc_u, uint16_t *adc_v, uint16_t *adc_w)
{
#if (ESC_CURRENT_SAMPLE_TYPE == ESC_CURRENT_SAMPLE_2SHUNT)
    uint16_t sample_u;
    uint16_t sample_v;
#endif

    if (!foc_lks_hw_valid_motor(motor))
        return;

#if (ESC_CURRENT_SAMPLE_TYPE == ESC_CURRENT_SAMPLE_3SHUNT)
    ESC_ADC_GetPhaseRaw(adc_u, adc_v, adc_w);
#elif (ESC_CURRENT_SAMPLE_TYPE == ESC_CURRENT_SAMPLE_2SHUNT)
    ESC_ADC_GetPhaseRaw(&sample_u, &sample_v, 0);
    if (adc_u != 0)
        *adc_u = sample_u;
    if (adc_v != 0)
        *adc_v = sample_v;
    if (adc_w != 0)
    {
        *adc_w = foc_lks_hw_limit_adc((int32_t)(3U * ESC_ADC_MIDPOINT) -
                                      (int32_t)sample_u -
                                      (int32_t)sample_v);
    }
#else
    if (adc_u != 0)
        *adc_u = ESC_ADC_MIDPOINT;
    if (adc_v != 0)
        *adc_v = ESC_ADC_MIDPOINT;
    if (adc_w != 0)
        *adc_w = ESC_ADC_MIDPOINT;
#endif
}

uint8_t foc_lks_hw_fault_active(uint8_t motor)
{
    if (!foc_lks_hw_valid_motor(motor))
        return 1U;

    return ESC_BoardFaultActive();
}

void foc_lks_hw_fault_reset(uint8_t motor)
{
    if (!foc_lks_hw_valid_motor(motor))
        return;

    ESC_PWM_Disable();
    ESC_PWM_SetSafeDuty();
    DRV8353_ClearFault();
    (void)DRV8353_ConfigureDefault();
}