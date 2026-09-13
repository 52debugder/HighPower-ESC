#ifndef __HAL_LKSMCU_HALL_H__
#define __HAL_LKSMCU_HALL_H__
#include "stdint.h"
#include "hal_lksmcu_gpio.h"
typedef enum
{
    HAL_HALL_0,
    HAL_HALL_1,
} HAL_HALL_x;
// 初始化
void HAL_HALL_Reset(HAL_HALL_x);   // 模块复位
void HAL_HALL_Enable(HAL_HALL_x);  // 模块打开
void HAL_HALL_Disable(HAL_HALL_x); // 模块关闭
//
void HAL_HALL_SetFreq(HAL_HALL_x, uint32_t freq);          // 设置hall频率 SetFreq和SetTh配置其中一个即可
void HAL_HALL_SetTh(HAL_HALL_x, uint32_t th);              // 设置hall阈值 SetFreq和SetTh配置其中一个即可
void HAL_HALL_StartCounting(HAL_HALL_x);                   // 开始计数 HAL_HALL_Enable后默认开始计数
void HAL_HALL_StopCounting(HAL_HALL_x);                    // 停止计数(同时计数器回到0)
void HAL_HALL_SetFilter(HAL_HALL_x, uint32_t filter_mclk); // 设置滤波，单位：MCU时钟
void HAL_HALL_SetFilteruS(HAL_HALL_x, uint32_t filter_uS); // 设置滤波，单位：uS
void HAL_HALL_SetFilter75(HAL_HALL_x, uint8_t ena);        // 设置7/5滤波使能,0:关闭(默认),非0:使能

uint32_t HAL_HALL_ReadTh(HAL_HALL_x);        // 获取当前hall的周期计数值
uint8_t HAL_HALL_ReadHallData(HAL_HALL_x);   // 获取当前hall的数据
uint32_t HAL_HALL_ReadHallWidth(HAL_HALL_x); // 获取当前hall捕获到的宽度
uint32_t HAL_HALL_GetCNT(HAL_HALL_x);        // 获取当前hall计数器的值

void HAL_HALL_SetGpio(HAL_HALL_x, HAL_GPIO_Px); // 设置hall输入引脚
#endif
