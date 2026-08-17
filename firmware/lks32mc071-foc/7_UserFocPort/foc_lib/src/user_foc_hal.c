/**
 * 文件：user_foc_hal.c
 * 说明：用户FOC HAL接口的LKS32MC07x适配层。
 *
 * 本文件中的影子状态用于记录FOC算法层请求的PWM和驱动状态。
 * 只有通过基础状态检查后，才会把真实硬件写入委托给foc_lks_hw.c。
 * 这样调试早期可以把PWM输出和驱动使能集中在一个较窄的安全门控里。
 */

#include "foc_hal.h"
#include "foc_config.h"
#include "foc_lks_hw.h"

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

static void foc_lks_set_center_duty(uint8_t num)
{
    foc_lks_shadow[num].duty_u = PWM_ARR / 2U;
    foc_lks_shadow[num].duty_v = PWM_ARR / 2U;
    foc_lks_shadow[num].duty_w = PWM_ARR / 2U;
}

static void foc_hal_init(uint8_t num)
{
    if (!foc_lks_valid_motor(num))
        return;

    foc_lks_set_center_duty(num);
    foc_lks_shadow[num].pwm_started = 0U;
    foc_lks_shadow[num].driver_enabled = 0U;

    foc_lks_hw_init(num);
}

static void foc_hal_pwm_start(uint8_t num)
{
    if (!foc_lks_valid_motor(num))
        return;

    foc_lks_shadow[num].pwm_started = 1U;
    foc_lks_hw_pwm_start(num);
}

static void foc_hal_pwm_disable(uint8_t num)
{
    if (!foc_lks_valid_motor(num))
        return;

    foc_lks_shadow[num].pwm_started = 0U;
    foc_lks_shadow[num].driver_enabled = 0U;
    foc_lks_set_center_duty(num);

    foc_lks_hw_pwm_disable(num);
}

static void foc_hal_set_duty(uint8_t num, uint16_t du, uint16_t dv, uint16_t dw)
{
    if (!foc_lks_valid_motor(num))
        return;

    du = foc_lks_limit_duty(du);
    dv = foc_lks_limit_duty(dv);
    dw = foc_lks_limit_duty(dw);

    if ((foc_lks_shadow[num].pwm_started == 0U) ||
        (foc_lks_shadow[num].driver_enabled == 0U) ||
        (foc_lks_hw_fault_active(num) != 0U))
    {
        du = PWM_ARR / 2U;
        dv = PWM_ARR / 2U;
        dw = PWM_ARR / 2U;
    }

    foc_lks_shadow[num].duty_u = du;
    foc_lks_shadow[num].duty_v = dv;
    foc_lks_shadow[num].duty_w = dw;

    foc_lks_hw_pwm_set(num, du, dv, dw);
}

static void foc_hal_drv_enable(uint8_t num)
{
    if (!foc_lks_valid_motor(num))
        return;

    if (foc_lks_hw_fault_active(num) != 0U)
    {
        foc_lks_shadow[num].driver_enabled = 0U;
        foc_lks_hw_drv_disable(num);
        return;
    }

    foc_lks_shadow[num].driver_enabled = 1U;

    if (foc_lks_shadow[num].pwm_started != 0U)
    {
        foc_lks_hw_pwm_set(num,
                           foc_lks_shadow[num].duty_u,
                           foc_lks_shadow[num].duty_v,
                           foc_lks_shadow[num].duty_w);
        foc_lks_hw_drv_enable(num);
    }
}

static void foc_hal_drv_disable(uint8_t num)
{
    if (!foc_lks_valid_motor(num))
        return;

    foc_lks_shadow[num].driver_enabled = 0U;
    foc_lks_hw_drv_disable(num);
    foc_lks_hw_pwm_set(num, PWM_ARR / 2U, PWM_ARR / 2U, PWM_ARR / 2U);
}

static void foc_hal_adc_get_value(uint8_t num, uint16_t *adc_u, uint16_t *adc_v, uint16_t *adc_w)
{
    if (!foc_lks_valid_motor(num))
        return;

    foc_lks_hw_adc_get(num, adc_u, adc_v, adc_w);
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
