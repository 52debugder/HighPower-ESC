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

#define FOC_ADC_TRIGGER_DELAY_TICKS 288U
#define FOC_ADC_FILTER_WINDOW 3U

extern TIM_HandleTypeDef htim1;

typedef struct
{
    uint16_t u[FOC_ADC_FILTER_WINDOW];
    uint16_t w[FOC_ADC_FILTER_WINDOW];
    uint8_t index;
    uint8_t count;
} foc_adc_filter_t;

static foc_adc_filter_t adc_filter[3];

static uint16_t foc_hal_median3_u16(uint16_t a, uint16_t b, uint16_t c)
{
    uint16_t temp;

    if (a > b)
    {
        temp = a;
        a = b;
        b = temp;
    }
    if (b > c)
    {
        temp = b;
        b = c;
        c = temp;
    }
    if (a > b)
    {
        temp = a;
        a = b;
        b = temp;
    }

    return b;
}

static void foc_hal_adc_filter_sample(uint8_t num, uint16_t raw_u, uint16_t raw_w, uint16_t *adc_u, uint16_t *adc_w)
{
    foc_adc_filter_t *filter = &adc_filter[num];
    uint8_t index = filter->index;

    filter->u[index] = raw_u;
    filter->w[index] = raw_w;
    if (filter->count < FOC_ADC_FILTER_WINDOW)
        filter->count++;

    index++;
    if (index >= FOC_ADC_FILTER_WINDOW)
        index = 0U;
    filter->index = index;

    if (filter->count < FOC_ADC_FILTER_WINDOW)
    {
        *adc_u = raw_u;
        *adc_w = raw_w;
        return;
    }

    *adc_u = foc_hal_median3_u16(filter->u[0], filter->u[1], filter->u[2]);
    *adc_w = foc_hal_median3_u16(filter->w[0], filter->w[1], filter->w[2]);
}

static void foc_hal_init(uint8_t num)
{
    switch(num)
    {
        case 1:
            adc_filter[1] = (foc_adc_filter_t){0};
            HAL_ADCEx_Calibration_Start(&hadc1);
            if(HAL_ADCEx_InjectedStart_IT(&hadc1) != HAL_OK) // 启动adc注入组采样
                Error_Handler(); 
            if(HAL_TIM_Base_Start(&htim2) != HAL_OK) // 启动tim定时器（foc的pwm生成）
                Error_Handler();
            break;
        case 2:
            // adc_filter[2] = (foc_adc_filter_t){0};
            // HAL_ADCEx_Calibration_Start(&hadc2, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
            // HAL_ADC_Start_DMA(&hadc2, (uint32_t *)adc2_buf, sizeof(adc2_buf) / sizeof(adc2_buf[0])); // 启动ADC DMA采样
            // HAL_TIM_Base_Start_IT(&htim1);// 启动定时器（FOC计算）
            break;
    }
}

static void foc_hal_set_duty(uint8_t num, uint16_t du, uint16_t dv, uint16_t dw)
{
    switch(num)
    {
        case 1:
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, du);
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, dv);
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, dw);
            break;
        case 2:
            // __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, du);
            // __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, dv);
            // __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, dw);
            break;
    }
}

static void foc_hal_tim_start(uint8_t num)
{
    switch(num)
    {
        case 1:
            HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
            HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
            HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
            HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, __HAL_TIM_GET_AUTORELOAD(&htim2) - FOC_ADC_TRIGGER_DELAY_TICKS);
            break;
        case 2:
            // HAL_TIM_Base_MspInit(&htim1);
            // HAL_TIM_MspPostInit(&htim1);

            // HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
            // HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
            // HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
            // HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
            // __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, __HAL_TIM_GET_AUTORELOAD(&htim1) - FOC_ADC_TRIGGER_DELAY_TICKS);
            break;
    }
}

static void foc_hal_pwm_disable(uint8_t num)
{
    switch(num)
    {
        case 1: HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1); 
                HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2); 
                HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3); 
                break; // 启动PWM输出
        // case 2: __HAL_TIM_MOE_ENABLE(&htim1); break; // 启动PWM输出
    }
}

static void foc_hal_drive_init(uint8_t num)
{
    switch(num)
    {
        case 1: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); break; // 启动M1左电机
        // case 2: HAL_GPIO_WritePin(BM_ENB_GPIO_Port, BM_ENB_Pin, GPIO_PIN_SET); break; // 启动M2右电机
    }
}

static void foc_hal_drive_deinit(uint8_t num)
{
    switch(num)
    {
        case 1: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET); break; // 启动M1左电机
        // case 2: HAL_GPIO_WritePin(BM_ENB_GPIO_Port, BM_ENB_Pin, GPIO_PIN_RESET); break; // 启动M2右电机
    }
}

static void foc_hal_adc_get_value(uint8_t num, uint16_t *adc_u, uint16_t *adc_v, uint16_t *adc_w)
{
    switch(num)
    {
        case 1:
        {
            // SCB_InvalidateDCache_by_Addr((uint32_t*)adc1_buf, sizeof(adc1_buf));
            uint16_t raw_ch4 = hadc1.Instance->JDR1;
            uint16_t raw_ch5 = hadc1.Instance->JDR2;
            foc_hal_adc_filter_sample(num, raw_ch5, raw_ch4, adc_u, adc_w);
            *adc_v = 0;
            break;
        }
        // case 2:
        //     SCB_InvalidateDCache_by_Addr((uint32_t*)adc2_buf, sizeof(adc2_buf));
        //     foc_hal_adc_filter_sample(num, adc2_buf[1], adc2_buf[0], adc_u, adc_w);
        //     *adc_v = 0;
        //     break;
    }
}

const foc_hal_t foc_hal =
{
    .pwm_start = foc_hal_tim_start,
    .pwm_set_duty = foc_hal_set_duty,
    .drv_enable = foc_hal_drive_init,
    .drv_disable = foc_hal_drive_deinit,
    .adc_get_value = foc_hal_adc_get_value,
    .init = foc_hal_init,
    .pwm_disable = foc_hal_pwm_disable,
};
