/**
 * @file user_foc_hal.c
 * @brief LKS32MC07x port of the user FOC HAL interface.
 *
 * This adapter is intentionally safe for the first migration stage: it lets the
 * STM32-origin FOC library compile in the LKS project without taking ownership
 * of the live MCPWM/ADC power stage. Real PWM/ADC binding should be enabled
 * only after current scaling, dead time, brake input, and ISR timing are checked
 * on hardware.
 */

#include "foc_hal.h"
#include "foc_config.h"

#define FOC_LKS_ADC_MIDPOINT    (ADC_RESOLUTION / 2U)
#define FOC_LKS_MOTOR_MIN       1U
#define FOC_LKS_MOTOR_MAX       MAX_MOTOR_NUM

typedef struct
{
    uint16_t duty_u;
    uint16_t duty_v;
    uint16_t duty_w;
    uint8_t pwm_started;
    uint8_t driver_enabled;
} foc_lks_shadow_t;

static foc_lks_shadow_t foc_lks_shadow[MAX_MOTOR_NUM + 1U];

static uint8_t foc_lks_valid_motor(uint8_t num)
{
    return (num >= FOC_LKS_MOTOR_MIN) && (num <= FOC_LKS_MOTOR_MAX);
}

static uint16_t foc_lks_limit_duty(uint16_t duty)
{
    return (duty > PWM_ARR) ? PWM_ARR : duty;
}

static void foc_hal_init(uint8_t num)
{
    if (!foc_lks_valid_motor(num))
        return;

    foc_lks_shadow[num].duty_u = PWM_ARR / 2U;
    foc_lks_shadow[num].duty_v = PWM_ARR / 2U;
    foc_lks_shadow[num].duty_w = PWM_ARR / 2U;
    foc_lks_shadow[num].pwm_started = 0U;
    foc_lks_shadow[num].driver_enabled = 0U;
}

static void foc_hal_pwm_start(uint8_t num)
{
    if (!foc_lks_valid_motor(num))
        return;

    foc_lks_shadow[num].pwm_started = 1U;
}

static void foc_hal_pwm_disable(uint8_t num)
{
    if (!foc_lks_valid_motor(num))
        return;

    foc_lks_shadow[num].pwm_started = 0U;
    foc_lks_shadow[num].duty_u = PWM_ARR / 2U;
    foc_lks_shadow[num].duty_v = PWM_ARR / 2U;
    foc_lks_shadow[num].duty_w = PWM_ARR / 2U;
}

static void foc_hal_set_duty(uint8_t num, uint16_t du, uint16_t dv, uint16_t dw)
{
    if (!foc_lks_valid_motor(num))
        return;

    if ((foc_lks_shadow[num].pwm_started == 0U) ||
        (foc_lks_shadow[num].driver_enabled == 0U))
    {
        du = PWM_ARR / 2U;
        dv = PWM_ARR / 2U;
        dw = PWM_ARR / 2U;
    }

    foc_lks_shadow[num].duty_u = foc_lks_limit_duty(du);
    foc_lks_shadow[num].duty_v = foc_lks_limit_duty(dv);
    foc_lks_shadow[num].duty_w = foc_lks_limit_duty(dw);
}

static void foc_hal_drv_enable(uint8_t num)
{
    if (!foc_lks_valid_motor(num))
        return;

    foc_lks_shadow[num].driver_enabled = 1U;
}

static void foc_hal_drv_disable(uint8_t num)
{
    if (!foc_lks_valid_motor(num))
        return;

    foc_lks_shadow[num].driver_enabled = 0U;
}

static void foc_hal_adc_get_value(uint8_t num, uint16_t *adc_u, uint16_t *adc_v, uint16_t *adc_w)
{
    (void)num;

    if (adc_u != 0)
        *adc_u = FOC_LKS_ADC_MIDPOINT;
    if (adc_v != 0)
        *adc_v = FOC_LKS_ADC_MIDPOINT;
    if (adc_w != 0)
        *adc_w = FOC_LKS_ADC_MIDPOINT;
}

const foc_hal_t foc_hal =
{
    .pwm_start = foc_hal_pwm_start,
    .pwm_disable = foc_hal_pwm_disable,
    .pwm_set_duty = foc_hal_set_duty,
    .drv_enable = foc_hal_drv_enable,
    .drv_disable = foc_hal_drv_disable,
    .adc_get_value = foc_hal_adc_get_value,
    .init = foc_hal_init,
};
