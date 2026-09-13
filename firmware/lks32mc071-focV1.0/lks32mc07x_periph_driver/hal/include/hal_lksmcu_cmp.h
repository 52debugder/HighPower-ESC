#ifndef __HAL_LKSMCU_CMP_H__
#define __HAL_LKSMCU_CMP_H__
#include "stdint.h"
#include "../include/hal_lksmcu_gpio.h"
typedef enum
{
    HAL_CMP_0, ///< CMP模块0
    HAL_CMP_1, ///< CMP模块1
    HAL_CMP_2, ///< CMP模块2
    HAL_CMP_3, ///< CMP模块3
    HAL_CMP_4, ///< CMP模块4
    HAL_CMP_5, ///< CMP模块5
} HAL_CMP_x;

typedef enum
{

    HAL_CMP_CHANNEL_IP0          = 0, ///< CMP模块外部正端输入0
    HAL_CMP_CHANNEL_IP_OPA0_IP   = 1, ///< 仅CMP0 运放0正端输入
    HAL_CMP_CHANNEL_IP_OPA3_IP   = 1, ///< 仅CMP1 运放3正端输入
    HAL_CMP_CHANNEL_IP_OPA0_OUTP = 2, ///< 仅CMP0 运放0正端输出
    HAL_CMP_CHANNEL_IP_OPA2_OUTP = 2, ///< 仅CMP1 运放2正端输出
    HAL_CMP_CHANNEL_IP_OPA1_OUTP = 3, ///< 仅CMP0 运放1正端输出
    HAL_CMP_CHANNEL_IP_OPA3_OUTP = 3, ///< 仅CMP1 运放3正端输出
    HAL_CMP_CHANNEL_IP1          = 4, ///< CMP模块外部正端输入1
    HAL_CMP_CHANNEL_IP2          = 5, ///< CMP模块外部正端输入2
    HAL_CMP_CHANNEL_IP3          = 6, ///< CMP模块外部正端输入3
    HAL_CMP_CHANNEL_IP4          = 7, ///< 仅CMP0 CMP模块外部正端输入4
    HAL_CMP_CHANNEL_IP_DAC0      = 7, ///< 仅CMP1 DAC0输出

#ifdef HAL_TEST_NOT_SUPPORTED
    HAL_CMP_CHANNEL_IP5,             ///< CMP模块外部正端输入5 不支持
    HAL_CMP_CHANNEL_IP6,             ///< CMP模块外部正端输入6 不支持
    HAL_CMP_CHANNEL_IP7,             ///< CMP模块外部正端输入7 不支持
    HAL_CMP_CHANNEL_IP_AVSS,         ///< 模拟地 不支持
    HAL_CMP_CHANNEL_IP_DAC1,         ///< DAC1输出 不支持
    HAL_CMP_CHANNEL_IP_OPA_OUT_CMP0, ///< 可以软件配置的运放输出0 不支持
    HAL_CMP_CHANNEL_IP_OPA0_IN,      ///< 运放0负端输入 不支持
    HAL_CMP_CHANNEL_IP_OPA0_OUTN,    ///< 运放0负端输出 不支持
    HAL_CMP_CHANNEL_IP_OPA1_IP,      ///< 运放1正端输入 不支持
    HAL_CMP_CHANNEL_IP_OPA1_IN,      ///< 运放1负端输入 不支持
    HAL_CMP_CHANNEL_IP_OPA1_OUTN,    ///< 运放1负端输出 不支持
    HAL_CMP_CHANNEL_IP_OPA2_IP,      ///< 运放2正端输入 不支持
    HAL_CMP_CHANNEL_IP_OPA2_IN,      ///< 运放2负端输入 不支持
    HAL_CMP_CHANNEL_IP_OPA2_OUTN,    ///< 运放2负端输出 不支持
    HAL_CMP_CHANNEL_IP_OPA3_IN,      ///< 运放3负端输入 不支持
    HAL_CMP_CHANNEL_IP_OPA3_OUTN,    ///< 运放3负端输出 不支持
    HAL_CMP_CHANNEL_IP_OPA4_IP,      ///< 运放4正端输入 不支持
    HAL_CMP_CHANNEL_IP_OPA4_IN,      ///< 运放4负端输入 不支持
    HAL_CMP_CHANNEL_IP_OPA4_OUTP,    ///< 运放4正端输出 不支持
    HAL_CMP_CHANNEL_IP_OPA4_OUTN,    ///< 运放4负端输出 不支持
    HAL_CMP_CHANNEL_IP_OPA5_IP,      ///< 运放4正端输入 不支持
    HAL_CMP_CHANNEL_IP_OPA5_IN,      ///< 运放5负端输入 不支持
    HAL_CMP_CHANNEL_IP_OPA5_OUTP,    ///< 运放5正端输出 不支持
    HAL_CMP_CHANNEL_IP_OPA5_OUTN,    ///< 运放5负端输出 不支持
#endif
} HAL_CMP_CHANNEL_IPx;
typedef enum
{
    HAL_CMP_CHANNEL_IN_0    = 0, ///< CMPN选择为外部负端输入
    HAL_CMP_CHANNEL_IN_REF  = 1, ///< CMPN选择为内部基准源
    HAL_CMP_CHANNEL_IN_DAC0 = 2, ///< CMPN选择为DAC输出
    HAL_CMP_CHANNEL_IN_MID  = 3, ///< CMPN选择为反电动势虚拟中心点
    HAL_CMP_CHANNEL_IN_DAC1 = 3, ///< 仅CMP2 CMPN选择为DAC输出

    HAL_CMP_CHANNEL_IN_DAC = HAL_CMP_CHANNEL_IN_DAC0, ///< CMPN选择为DAC输出
} HAL_CMP_CHANNEL_INx;
typedef enum
{
    HAL_CMP_MODE_RISING_EDGE  = 0x00U, ///< 上升沿触发模式
    HAL_CMP_MODE_FALLING_EDGE = 0x01U, ///< 下降沿触发模式
    HAL_CMP_MODE_HIGH_LEVEL   = 0x02U, ///< 高电平检测模式
    HAL_CMP_MODE_LOW_LEVEL    = 0x03U  ///< 低电平检测模式
} HAL_CMP_MODE_x;
typedef enum
{
    HAL_CMP_HYS_20mV = 0, ///< 回差20mV(默认)
    HAL_CMP_HYS_0mV  = 1, ///< 关闭回差
} HAL_CMP_HYS_x;
// 初始化
void HAL_CMP_Reset(HAL_CMP_x);   // 模块复位
void HAL_CMP_Enable(HAL_CMP_x);  // 模块打开
void HAL_CMP_Disable(HAL_CMP_x); // 模块关闭

void HAL_CMP_SetChannel(HAL_CMP_x, HAL_CMP_CHANNEL_IPx, HAL_CMP_CHANNEL_INx); // 设置CMP输入信号通道
uint32_t HAL_CMP_SetDigitalFilter(HAL_CMP_x, uint32_t filter);                // 设置数字滤波宽度 0-0xffff 单位MCU时钟周期,根据芯片不同,实际滤波宽度可能会有差异,返回值,实际滤波宽度
void HAL_CMP_SetMode(HAL_CMP_x, HAL_CMP_MODE_x);                              // 设置CMP中断触发模式
void HAL_CMP_SetHysteresis(HAL_CMP_x, HAL_CMP_HYS_x);                         // 设置比较器回差
void HAL_CMP_SetGpioOut(HAL_CMP_x cmpx, HAL_GPIO_Px cmpgpio);
void HAL_CMP_SetGpioIn(HAL_CMP_x cmpx, HAL_GPIO_Px cmpgpio);
uint8_t HAL_CMP_GetData(HAL_CMP_x);

#endif
