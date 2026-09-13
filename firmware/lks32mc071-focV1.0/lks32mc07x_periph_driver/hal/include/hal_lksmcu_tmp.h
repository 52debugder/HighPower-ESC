
#ifndef __HAL_LKSMCU_TMP_H__
#define __HAL_LKSMCU_TMP_H__
#include "../include/hal_lksmcu_trim.h"
#include "../include/hal_lksmcu_adc.h"
#include "stdint.h"
typedef enum
{
    HAL_TMP_0,
    HAL_TMP_1,
} HAL_TMP_x;
// 初始化
void HAL_TMP_Reset(HAL_TMP_x);   // 模块复位
void HAL_TMP_Enable(HAL_TMP_x);  // 模块打开
void HAL_TMP_Disable(HAL_TMP_x); // 模块关闭

int32_t HAL_TMP_GetTemperature(HAL_TMP_x, HAL_ADC_x, HAL_ADC_SAMP_SEQUENCE_x);   // 获取当前芯片内部温度传感器测到的温度,单位摄氏度,需要配置ADC并采样温度传感器通道
int32_t HAL_TMP_GetTemperature01(HAL_TMP_x, HAL_ADC_x, HAL_ADC_SAMP_SEQUENCE_x); // 获取当前芯片内部温度传感器测到的温度,单位0.1摄氏度,需要配置ADC并采样温度传感器通道

int32_t HAL_TMP_Adc2Temperature(HAL_TMP_x, int32_t adc_value);   // 芯片内部温度传感器ADC值转温度 单位度
int32_t HAL_TMP_Adc2Temperature01(HAL_TMP_x, int32_t adc_value); // 芯片内部温度传感器ADC值转温度 单位0.1度
#endif
