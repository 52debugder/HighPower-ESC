#ifndef __HAL_LKSMCU_ADC_H__
#define __HAL_LKSMCU_ADC_H__
#include "stdint.h"
#include "hal_lksmcu_gpio.h"
/// @brief 主频
typedef enum
{
    HAL_ADC_CHANNEL_0,  ///< ADC采样端口0
    HAL_ADC_CHANNEL_1,  ///< ADC采样端口1
    HAL_ADC_CHANNEL_2,  ///< ADC采样端口2
    HAL_ADC_CHANNEL_3,  ///< ADC采样端口3
    HAL_ADC_CHANNEL_4,  ///< ADC采样端口4
    HAL_ADC_CHANNEL_5,  ///< ADC采样端口5
    HAL_ADC_CHANNEL_6,  ///< ADC采样端口6
    HAL_ADC_CHANNEL_7,  ///< ADC采样端口7
    HAL_ADC_CHANNEL_8,  ///< ADC采样端口8
    HAL_ADC_CHANNEL_9,  ///< ADC采样端口9
    HAL_ADC_CHANNEL_10, ///< ADC采样端口10
    HAL_ADC_CHANNEL_11, ///< ADC采样端口11
    HAL_ADC_CHANNEL_12, ///< ADC采样端口12
    HAL_ADC_CHANNEL_13, ///< ADC采样端口13
    HAL_ADC_CHANNEL_14, ///< ADC采样端口14
    HAL_ADC_CHANNEL_15, ///< ADC采样端口15

    HAL_ADC_CHANNEL_OPA0 = HAL_ADC_CHANNEL_0, ///< ADC采样端口运放0
    HAL_ADC_CHANNEL_OPA1 = HAL_ADC_CHANNEL_1, ///< ADC采样端口运放1
    HAL_ADC_CHANNEL_OPA2 = HAL_ADC_CHANNEL_2, ///< ADC采样端口运放2
    HAL_ADC_CHANNEL_OPA3 = HAL_ADC_CHANNEL_3, ///< ADC采样端口运放3

    HAL_ADC_CHANNEL_DAC0 = HAL_ADC_CHANNEL_14, ///< 仅ADC0 ADC采样DAC0输出
    HAL_ADC_CHANNEL_DAC1 = HAL_ADC_CHANNEL_15, ///< 仅ADC0 ADC采样DAC1输出

    HAL_ADC_CHANNEL_TMP0 = HAL_ADC_CHANNEL_14, ///< 仅ADC1 ADC采样端口温度传感器
    HAL_ADC_CHANNEL_VDD  = HAL_ADC_CHANNEL_15, ///< 仅ADC1 ADC采样供电

#ifdef HAL_TEST_NOT_SUPPORTED
    HAL_ADC_CHANNEL_REF,   ///< ADC采样芯片内部基准电压 不支持
    HAL_ADC_CHANNEL_AGND,  ///< ADC采样内部地 不支持
    HAL_ADC_CHANNEL_OPA4,  ///< ADC采样端口运放4 不支持
    HAL_ADC_CHANNEL_OPA5,  ///< ADC采样端口运放5 不支持
    HAL_ADC_CHANNEL_16,    ///< ADC采样端口16 不支持
    HAL_ADC_CHANNEL_17,    ///< ADC采样端口17 不支持
    HAL_ADC_CHANNEL_18,    ///< ADC采样端口18 不支持
    HAL_ADC_CHANNEL_19,    ///< ADC采样端口19 不支持
    HAL_ADC_CHANNEL_LDO12, ///< ADC采样芯片LDO12(1.2V)内核供电 不支持
#endif
} HAL_ADC_CHANNEL_x;
/// @brief ADC采样序列
typedef enum
{
    HAL_ADC_SAMP_SEQUENCE_0,  ///< ADC第0次采样
    HAL_ADC_SAMP_SEQUENCE_1,  ///< ADC第1次采样
    HAL_ADC_SAMP_SEQUENCE_2,  ///< ADC第2次采样
    HAL_ADC_SAMP_SEQUENCE_3,  ///< ADC第3次采样
    HAL_ADC_SAMP_SEQUENCE_4,  ///< ADC第4次采样
    HAL_ADC_SAMP_SEQUENCE_5,  ///< ADC第5次采样
    HAL_ADC_SAMP_SEQUENCE_6,  ///< ADC第6次采样
    HAL_ADC_SAMP_SEQUENCE_7,  ///< ADC第7次采样
    HAL_ADC_SAMP_SEQUENCE_8,  ///< ADC第8次采样
    HAL_ADC_SAMP_SEQUENCE_9,  ///< ADC第9次采样
    HAL_ADC_SAMP_SEQUENCE_10, ///< ADC第10次采样
    HAL_ADC_SAMP_SEQUENCE_11, ///< ADC第11次采样
    HAL_ADC_SAMP_SEQUENCE_12, ///< ADC第12次采样
    HAL_ADC_SAMP_SEQUENCE_13, ///< ADC第13次采样
    HAL_ADC_SAMP_SEQUENCE_14, ///< ADC第14次采样
    HAL_ADC_SAMP_SEQUENCE_15, ///< ADC第15次采样
    HAL_ADC_SAMP_SEQUENCE_16, ///< ADC第16次采样
    HAL_ADC_SAMP_SEQUENCE_17, ///< ADC第17次采样
    HAL_ADC_SAMP_SEQUENCE_18, ///< ADC第18次采样
    HAL_ADC_SAMP_SEQUENCE_19, ///< ADC第19次采样
} HAL_ADC_SAMP_SEQUENCE_x;
typedef enum
{
    HAL_ADC_0, ///< ADC模块0
    HAL_ADC_1, ///< ADC模块1
    HAL_ADC_2, ///< ADC模块2
    HAL_ADC_3, ///< ADC模块3
} HAL_ADC_x;
typedef enum
{
    HAL_ADC_SAMP_NUMBER_0,                            ///< ADC采样0次
    HAL_ADC_SAMP_NUMBER_1,                            ///< ADC采样1次
    HAL_ADC_SAMP_NUMBER_2,                            ///< ADC采样2次
    HAL_ADC_SAMP_NUMBER_3,                            ///< ADC采样3次
    HAL_ADC_SAMP_NUMBER_4,                            ///< ADC采样4次
    HAL_ADC_SAMP_NUMBER_5,                            ///< ADC采样5次
    HAL_ADC_SAMP_NUMBER_6,                            ///< ADC采样6次
    HAL_ADC_SAMP_NUMBER_7,                            ///< ADC采样7次
    HAL_ADC_SAMP_NUMBER_8,                            ///< ADC采样8次
    HAL_ADC_SAMP_NUMBER_9,                            ///< ADC采样9次
    HAL_ADC_SAMP_NUMBER_10,                           ///< ADC采样10次
    HAL_ADC_SAMP_NUMBER_11,                           ///< ADC采样11次
    HAL_ADC_SAMP_NUMBER_12,                           ///< ADC采样12次
    HAL_ADC_SAMP_NUMBER_13,                           ///< ADC采样13次
    HAL_ADC_SAMP_NUMBER_14,                           ///< ADC采样14次
    HAL_ADC_SAMP_NUMBER_15,                           ///< ADC采样15次
    HAL_ADC_SAMP_NUMBER_MAX = HAL_ADC_SAMP_NUMBER_15, ///< ADC采样15次
} HAL_ADC_SAMP_NUMBER_x;
typedef enum
{
    HAL_ADC_TRIGGER_MCPWM0,   ///< 使用MCPWM触发ADC采样
    HAL_ADC_TRIGGER_MCPWM0_1, ///< 使用MCPWM时基1触发ADC采样
    HAL_ADC_TRIGGER_TIMER0,   ///< 使用TIMER触发ADC采样
    HAL_ADC_TRIGGER_TIMER2,   ///< 使用TIMER触发ADC采样
    HAL_ADC_TRIGGER_SOFT,     ///< 使用软件触发ADC采样

    HAL_ADC_TRIGGER_MCPWM = HAL_ADC_TRIGGER_MCPWM0, ///< 使用MCPWM触发ADC采样
    HAL_ADC_TRIGGER_TIMER = HAL_ADC_TRIGGER_TIMER0, ///< 使用TIMER触发ADC采样

#ifdef HAL_TEST_NOT_SUPPORTED
    HAL_ADC_TRIGGER_MCPWM1_1, ///< 使用MCPWM时基1触发ADC采样
    HAL_ADC_TRIGGER_MCPWM1,   ///< 使用MCPWM触发ADC采样
    HAL_ADC_TRIGGER_TIMER1,   ///< 使用TIMER触发ADC采样
    HAL_ADC_TRIGGER_TIMER3,   ///< 使用TIMER触发ADC采样
    HAL_ADC_TRIGGER_TIMER4,   ///< 使用TIMER触发ADC采样
#endif
} HAL_ADC_TRIGGER_x;
typedef enum
{
    HAL_ADC_REFERENCE_INTERNAL,                                  ///< 使用内部基准源作为adc基准
    HAL_ADC_REFERENCE_INTERNAL_3_6 = HAL_ADC_REFERENCE_INTERNAL, ///< 使用内部3.6V基准源作为adc基准
    HAL_ADC_REFERENCE_INTERNAL_2_4,                              ///< 使用内部2.4V基准源作为adc基准
    HAL_ADC_REFERENCE_EXTERNAL,                                  ///< 使用芯片供电作为adc基准
#ifdef HAL_TEST_NOT_SUPPORTED
    HAL_ADC_REFERENCE_INTERNAL_3_3
#endif
} HAL_ADC_REFERENCE_x;

// 初始化
void HAL_ADC_Reset(HAL_ADC_x);   // 模块复位
void HAL_ADC_Enable(HAL_ADC_x);  // 模块打开
void HAL_ADC_Disable(HAL_ADC_x); // 模块关闭

// 自动采样配置
int16_t HAL_ADC_GetSamplingValues(HAL_ADC_x, HAL_ADC_SAMP_SEQUENCE_x);                     // 获取采样值 返回第n次采样结果
void HAL_ADC_SetSamplingChannel(HAL_ADC_x, HAL_ADC_SAMP_SEQUENCE_x, HAL_ADC_CHANNEL_x);    // 设置采样通道,输入参数 第n次采样channel通道
void HAL_ADC_SetSamplingQuantity(HAL_ADC_x, HAL_ADC_SAMP_NUMBER_x, HAL_ADC_SAMP_NUMBER_x); // 设置采样数量
void HAL_ADC_SetTriggerSignal(HAL_ADC_x, HAL_ADC_TRIGGER_x);                               // 设置触发信号
void HAL_ADC_EndSampling(HAL_ADC_x);                                                       // 中止当前采样
void HAL_ADC_SetReference(HAL_ADC_x, HAL_ADC_REFERENCE_x);                                 // 设置ADC基准源
void HAL_ADC_StateReset(HAL_ADC_x);                                                        // ADC状态机复位
float HAL_ADC_GetRange(HAL_ADC_x);                                                         // 获取adc量程,使用芯片供电作为adc基准时固定返回5.0
float HAL_ADC_GetValuesUnit(HAL_ADC_x);                                                    // 获取采样值单位
// 手动采样配置
void HAL_ADC_SoftTrigger(HAL_ADC_x);                          // 软件触发ADC开始采样
int16_t HAL_ADC_ManualSampling(HAL_ADC_x, HAL_ADC_CHANNEL_x); // 手动采样 需要先设置采样通道为软件触发

// IO配置
void HAL_ADC_SetGpioIn(HAL_ADC_x, HAL_GPIO_Px);         // 设置指定的GPIO为ADC输入
void HAL_ADC_SetGpioTriggerOut(HAL_ADC_x, HAL_GPIO_Px); // 设置指定的GPIO为ADC触发信号输出

#endif
