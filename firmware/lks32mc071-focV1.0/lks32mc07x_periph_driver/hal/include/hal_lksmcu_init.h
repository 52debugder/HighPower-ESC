#ifndef __HAL_LKSMCU_INIT_H__
#define __HAL_LKSMCU_INIT_H__

/**
 * @brief 芯片的默认时钟频率
 */
#define HAL_INIT_DEFAULE_MCLK    96000000
#define HAL_INIT_DEFAULE_MCLK_US 96    // 上电后的默认时钟1uS分频系数
#define HAL_INIT_DEFAULE_MCLK_MS 96000 // 上电后的默认时钟1mS分频系数
typedef enum
{
    HAL_INIT_POWER_3_3V = 0, // 仅支持版本大于3的芯片(对于不支持的芯片，自动跳过等待)
    HAL_INIT_POWER_5V,
} HAL_INIT_POWER_x;
void HAL_INIT_SysInit(void);
void HAL_INIT_PowerReady(HAL_INIT_POWER_x powerx);

#endif
