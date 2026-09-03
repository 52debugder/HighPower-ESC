/**
 * 文件：user_foc_hal.c
 * 说明：FOC库到LKS32MC071平台的适配层。
 *
 * 这一层只做函数表转接，不再依赖STM32 HAL。
 * 具体的PWM、ADC、驱动使能和故障处理都由 foc_lks_hw.c 完成。
 */

#include "foc_hal.h"
#include "foc_lks_hw.h"

static void foc_hal_init(uint8_t num)
{
    foc_lks_hw_init(num);
}

static void foc_hal_pwm_start(uint8_t num)
{
    foc_lks_hw_pwm_start(num);
}

static void foc_hal_pwm_disable(uint8_t num)
{
    foc_lks_hw_pwm_disable(num);
}

static void foc_hal_pwm_set_duty(uint8_t num, uint16_t du, uint16_t dv, uint16_t dw)
{
    foc_lks_hw_pwm_set(num, du, dv, dw);
}

static void foc_hal_drv_enable(uint8_t num)
{
    foc_lks_hw_drv_enable(num);
}

static void foc_hal_drv_disable(uint8_t num)
{
    foc_lks_hw_drv_disable(num);
}

static void foc_hal_adc_get_value(uint8_t num, uint16_t *adc_u, uint16_t *adc_v, uint16_t *adc_w)
{
    foc_lks_hw_adc_get(num, adc_u, adc_v, adc_w);
}

const foc_hal_t foc_hal =
{
    .pwm_start = foc_hal_pwm_start,
    .pwm_disable = foc_hal_pwm_disable,
    .pwm_set_duty = foc_hal_pwm_set_duty,
    .drv_enable = foc_hal_drv_enable,
    .drv_disable = foc_hal_drv_disable,
    .adc_get_value = foc_hal_adc_get_value,
    .init = foc_hal_init,
};