#ifndef __HAL_LKSMCU_DAC_H__
#define __HAL_LKSMCU_DAC_H__
#include "stdint.h"
#include "hal_lksmcu_gpio.h"

typedef enum
{
    HAL_DAC_0, ///< DAC模块0
    HAL_DAC_1, ///< DAC模块1
#ifdef HAL_TEST_NOT_SUPPORTED
    HAL_DAC_2, ///< DAC模块2
    HAL_DAC_3, ///< DAC模块3
#endif
} HAL_DAC_x;
typedef enum
{
    HAL_DAC_RANGE_1_2   = 1, ///< 量程1.2V
    HAL_DAC_RANGE_4_85V = 0, ///< 量程4.85V

#ifdef HAL_TEST_NOT_SUPPORTED
    HAL_DAC_RANGE_3_0V  = 0, ///< 量程3.0V
    HAL_DAC_RANGE_4_76V = 0, ///< 量程4.76V
    HAL_DAC_RANGE_4_8V,      ///< 量程4.8V
#endif
} HAL_DAC_RANGE_x;
void HAL_DAC_Reset(HAL_DAC_x);   // 模块复位
void HAL_DAC_Enable(HAL_DAC_x);  // 模块打开
void HAL_DAC_Disable(HAL_DAC_x); // 模块关闭

void HAL_DAC_SetOutVal(HAL_DAC_x, uint16_t val);
uint16_t HAL_DAC_GetOutValMax(HAL_DAC_x);
void HAL_DAC_SetRange(HAL_DAC_x, HAL_DAC_RANGE_x);
float HAL_DAC_GetRange(HAL_DAC_x);

void HAL_DAC_SetOutVoltagemV(HAL_DAC_x, uint16_t vol_mV);

void HAL_DAC_Out2GpioEnable(HAL_DAC_x);
void HAL_DAC_Out2GpioDisable(HAL_DAC_x);
void HAL_DAC_SetGpioOut(HAL_DAC_x, HAL_GPIO_Px);
#endif
