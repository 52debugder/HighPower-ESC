#ifndef __HAL_LKSMCU_DSP_H__
#define __HAL_LKSMCU_DSP_H__
#include "stdint.h"

typedef enum
{
    HAL_DSP_0, ///< DSP模块0
} HAL_DSP_x;
void HAL_DSP_Reset(HAL_DSP_x);   // 模块复位
void HAL_DSP_Enable(HAL_DSP_x);  // 模块打开
void HAL_DSP_Disable(HAL_DSP_x); // 模块关闭

int16_t HAL_DSP_Sin(HAL_DSP_x, int16_t angle);
int16_t HAL_DSP_Cos(HAL_DSP_x, int16_t angle);
void HAL_DSP_SinCos(HAL_DSP_x, int16_t angle, int16_t *sin, int16_t *cos);
uint16_t HAL_DSP_Sqrt(HAL_DSP_x, uint32_t);
int32_t HAL_DSP_Div(HAL_DSP_x, int32_t, int32_t);
#endif
