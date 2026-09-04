/**
 * 文件：foc_lks_hw.c
 * 说明：用户FOC HAL到LKS32MC071底层硬件的适配。
 *
 * MCPWM0的CH0/CH1/CH2分别对应A/B/C三相互补输出。
 * DRV8353S的ENABLE由P1.10控制，nFAULT由P2.3读取。
 * 默认先关闭功率级，再写入安全占空比，避免初始化阶段误开管。
 */

#include "foc_lks_hw.h"

#include "drv8353.h"
#include "foc_config.h"
#include "hardware_config.h"
#include "HALDrv.h"

extern void SoftDelay(u32 cnt);

#define FOC_LKS_HW_MOTOR0        (1U)
#define FOC_LKS_HW_ADC_MAX       (ADC_RESOLUTION - 1U)
#define FOC_LKS_HW_ADC_MIDPOINT  (ADC_RESOLUTION / 2U)

static uint8_t foc_lks_hw_valid_motor(uint8_t motor)
{
    return (motor == FOC_LKS_HW_MOTOR0);
}

static uint16_t foc_lks_hw_limit_duty(uint16_t duty)
{
    return (duty > PWM_ARR) ? PWM_ARR : duty;
}

#if (CURRENT_SAMPLE_TYPE_M0 == CURRENT_SAMPLE_2SHUNT)
static uint16_t foc_lks_hw_limit_adc(int32_t adc)
{
    if (adc < 0)
        return 0U;
    if (adc > (int32_t)FOC_LKS_HW_ADC_MAX)
        return (uint16_t)FOC_LKS_HW_ADC_MAX;
    return (uint16_t)adc;
}
#endif

static void foc_lks_hw_write_pwm(uint16_t duty_u, uint16_t duty_v, uint16_t duty_w)
{
    duty_u = foc_lks_hw_limit_duty(duty_u);
    duty_v = foc_lks_hw_limit_duty(duty_v);
    duty_w = foc_lks_hw_limit_duty(duty_w);

    MCPWM0_PRT = 0x0000DEAD;

    /* U/V/W按物理相序映射：U->A相CH0，V->B相CH1，W->C相CH2。 */
    MCPWM0_TH00 = (int16_t)(-duty_u);
    MCPWM0_TH01 = duty_u;

    MCPWM0_TH10 = (int16_t)(-duty_v);
    MCPWM0_TH11 = duty_v;

    MCPWM0_TH20 = (int16_t)(-duty_w);
    MCPWM0_TH21 = duty_w;

    MCPWM0_UPDATE = 0xFFU;
    MCPWM0_PRT = 0x00000000;
}

static void foc_lks_hw_write_safe_pwm(void)
{
    foc_lks_hw_write_pwm(PWM_ARR / 2U, PWM_ARR / 2U, PWM_ARR / 2U);
}

void foc_lks_hw_init(uint8_t motor)
{
    if (!foc_lks_hw_valid_motor(motor))
        return;

    EPWM0_OutPut(DISABLE);
    DRV8353_Init();
    DRV8353_Disable();
    foc_lks_hw_write_safe_pwm();
}

void foc_lks_hw_pwm_start(uint8_t motor)
{
    if (!foc_lks_hw_valid_motor(motor))
        return;

    foc_lks_hw_write_safe_pwm();
}

void foc_lks_hw_pwm_disable(uint8_t motor)
{
    if (!foc_lks_hw_valid_motor(motor))
        return;

    EPWM0_OutPut(DISABLE);
    foc_lks_hw_write_safe_pwm();
}

void foc_lks_hw_pwm_set(uint8_t motor, uint16_t duty_u, uint16_t duty_v, uint16_t duty_w)
{
    if (!foc_lks_hw_valid_motor(motor))
        return;

    foc_lks_hw_write_pwm(duty_u, duty_v, duty_w);
}

void foc_lks_hw_drv_enable(uint8_t motor)
{
    if (!foc_lks_hw_valid_motor(motor))
        return;

    foc_lks_hw_write_safe_pwm();
    DRV8353_Enable();
    EPWM0_OutPut(ENABLE);
}

void foc_lks_hw_drv_disable(uint8_t motor)
{
    if (!foc_lks_hw_valid_motor(motor))
        return;

    EPWM0_OutPut(DISABLE);
    foc_lks_hw_write_safe_pwm();
    DRV8353_Disable();
}

void foc_lks_hw_adc_get(uint8_t motor, uint16_t *adc_u, uint16_t *adc_v, uint16_t *adc_w)
{
    uint16_t sample_u;
    uint16_t sample_v;
    uint16_t sample_w;

    if (!foc_lks_hw_valid_motor(motor))
        return;

    sample_u = (uint16_t)GET_ADC0_DATA_M0;
    sample_v = (uint16_t)GET_ADC1_DATA_M0;

#if (CURRENT_SAMPLE_TYPE_M0 == CURRENT_SAMPLE_3SHUNT)
    sample_w = (uint16_t)ADC0_DAT2;
#elif (CURRENT_SAMPLE_TYPE_M0 == CURRENT_SAMPLE_2SHUNT)
    sample_w = foc_lks_hw_limit_adc((int32_t)(3U * FOC_LKS_HW_ADC_MIDPOINT) -
                                    (int32_t)sample_u -
                                    (int32_t)sample_v);
#else
    sample_w = FOC_LKS_HW_ADC_MIDPOINT;
#endif

    if (adc_u != 0)
        *adc_u = sample_u;
    if (adc_v != 0)
        *adc_v = sample_v;
    if (adc_w != 0)
        *adc_w = sample_w;
}

uint8_t foc_lks_hw_fault_active(uint8_t motor)
{
    if (!foc_lks_hw_valid_motor(motor))
        return 1U;

#if (EPWM0_USED == FUNCTION_ON)
    if (DRV8353_FaultActive() != 0U)
        return 1U;

    return ((MCPWM0_EIF & BIT5) != 0U) ? 1U : 0U;
#else
    return 1U;
#endif
}

void foc_lks_hw_fault_reset(uint8_t motor)
{
    if (!foc_lks_hw_valid_motor(motor))
        return;

    EPWM0_OutPut(DISABLE);
    foc_lks_hw_write_safe_pwm();
    DRV8353_ClearFault();
}
