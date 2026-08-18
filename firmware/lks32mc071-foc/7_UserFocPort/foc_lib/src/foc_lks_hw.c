/**
 * 文件：foc_lks_hw.c
 * 说明：用户FOC HAL的LKS32MC071底层硬件适配。
 *
 * 本层只负责触碰MCPWM、ADC和现有LKS输出门控函数。
 * 软件状态和安全判断放在user_foc_hal.c中处理。
 * DRV8353S的ENABLE和SPI控制需要先在硬件上确认引脚与故障极性，
 * 再加入到这里，避免调试早期误开功率级。
 */

#include "foc_lks_hw.h"

#include "foc_config.h"
#include "hardware_config.h"
#include "HALDrv.h"

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

static uint16_t foc_lks_hw_limit_adc(int32_t adc)
{
    if (adc < 0)
        return 0U;
    if (adc > (int32_t)FOC_LKS_HW_ADC_MAX)
        return (uint16_t)FOC_LKS_HW_ADC_MAX;
    return (uint16_t)adc;
}

static void foc_lks_hw_write_pwm(uint16_t duty_u, uint16_t duty_v, uint16_t duty_w)
{
    MCPWM0_PRT = 0x0000DEAD;

    /* 现有LKS FOC代码中，B相对应TH0，A相对应TH1，C相对应TH2。
       用户FOC HAL使用U/V/W命名，因此这里映射为U->A，V->B，W->C。 */
    MCPWM0_TH00 = (int16_t)(-duty_u);
    MCPWM0_TH01 = duty_u;

    MCPWM0_TH10 = (int16_t)(-duty_v);
    MCPWM0_TH11 = duty_v;

    MCPWM0_TH20 = (int16_t)(-duty_w);
    MCPWM0_TH21 = duty_w;

    MCPWM0_UPDATE = 0xFFU;
    MCPWM0_PRT = 0x00000000;
}

void foc_lks_hw_init(uint8_t motor)
{
    if (!foc_lks_hw_valid_motor(motor))
        return;

    EPWM0_OutPut(DISABLE);
    foc_lks_hw_write_pwm(PWM_ARR / 2U, PWM_ARR / 2U, PWM_ARR / 2U);
}

void foc_lks_hw_pwm_start(uint8_t motor)
{
    if (!foc_lks_hw_valid_motor(motor))
        return;

    foc_lks_hw_write_pwm(PWM_ARR / 2U, PWM_ARR / 2U, PWM_ARR / 2U);
}

void foc_lks_hw_pwm_disable(uint8_t motor)
{
    if (!foc_lks_hw_valid_motor(motor))
        return;

    EPWM0_OutPut(DISABLE);
    foc_lks_hw_write_pwm(PWM_ARR / 2U, PWM_ARR / 2U, PWM_ARR / 2U);
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

    /* 这里只通过现有LKS驱动层打开MCPWM输出门控。
       在确认DRV8353S ENABLE引脚GPIO路径之前，不直接操作驱动芯片使能脚。 */
    EPWM0_OutPut(ENABLE);
}

void foc_lks_hw_drv_disable(uint8_t motor)
{
    if (!foc_lks_hw_valid_motor(motor))
        return;

    EPWM0_OutPut(DISABLE);
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
    return ((MCPWM0_EIF & BIT5) != 0U) ? 1U : 0U;
#else
    return 1U;
#endif
}
