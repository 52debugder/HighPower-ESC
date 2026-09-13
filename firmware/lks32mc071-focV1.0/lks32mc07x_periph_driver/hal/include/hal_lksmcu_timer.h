#ifndef __HAL_LKSMCU_TIMER_H__
#define __HAL_LKSMCU_TIMER_H__
#include "stdint.h"
#include "hal_lksmcu_gpio.h"

typedef enum
{
    HAL_TIMER_0, ///< TIMER模块0
    HAL_TIMER_1, ///< TIMER模块1
    HAL_TIMER_2, ///< TIMER模块2
    HAL_TIMER_3, ///< TIMER模块3
    HAL_TIMER_4, ///< TIMER模块3
} HAL_TIMER_x;
typedef enum
{
    HAL_TIMER_MODE_COUNT,  ///< 计数模式
    HAL_TIMER_MODE_PWMOUT, ///< PWM输出模式
    HAL_TIMER_MODE_PWMIN,  ///< PWM输入模式
} HAL_TIMER_MODE_x;

void HAL_TIMER_Reset(HAL_TIMER_x);   // 模块复位
void HAL_TIMER_Enable(HAL_TIMER_x);  // 模块打开
void HAL_TIMER_Disable(HAL_TIMER_x); // 模块关闭

void HAL_TIMER_SetPeriodCount(HAL_TIMER_x, uint32_t count); // 设置周期(计数值)
void HAL_TIMER_SetFreq(HAL_TIMER_x, uint32_t freq);         // 设置频率
void HAL_TIMER_SetPeriodmS(HAL_TIMER_x, uint32_t ms);       // 设置周期(ms)
void HAL_TIMER_SetPerioduS(HAL_TIMER_x, uint32_t us);       // 设置周期(uS)

uint32_t HAL_TIMER_GetFreq(HAL_TIMER_x);                                  // 获取当前的pwm频率
uint32_t HAL_TIMER_GetThCnt(HAL_TIMER_x);                                 // 获取计数器最大值
void HAL_TIMER_SetClockDiv(HAL_TIMER_x timer_x, uint32_t div);            // 设置时钟分频 div=1/2/4/8/16/32/64/128
uint32_t HAL_TIMER_GetClockDiv(HAL_TIMER_x timer_x);                      // 获取时钟分频实际除数
uint32_t HAL_TIMER_GetClockFreq(HAL_TIMER_x timer_x);                     // 获取分频后工作时钟(Hz)
void HAL_TIMER_StartCounting(HAL_TIMER_x);                                // 开始计数
void HAL_TIMER_StopCounting(HAL_TIMER_x);                                 // 停止计数(同时计数器回到0)
void HAL_TIMER_SetPwm(HAL_TIMER_x timer_x, int32_t t0, int32_t t1);       // 设置pwm波形 仅PWM模式下有效
void HAL_TIMER_SetPwmQ15(HAL_TIMER_x timer_x, int16_t t0, int16_t t1);    // 设置pwm波形q15格式输入 仅PWM模式下有效
void HAL_TIMER_SetWorkMode(HAL_TIMER_x timer_x, HAL_TIMER_MODE_x mode_x); // 设置工作模式

void HAL_TIMER_SetGpioOut(HAL_TIMER_x timer_x, HAL_GPIO_Px px);
void HAL_TIMER_SetGpioIn(HAL_TIMER_x timer_x, HAL_GPIO_Px px);
#endif
