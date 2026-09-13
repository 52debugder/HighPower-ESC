#ifndef __HAL_LKSMCU_IWDG_H__
#define __HAL_LKSMCU_IWDG_H__
#include "stdint.h"
typedef enum
{
    HAL_IWDG_0,
} HAL_IWDG_x;
// 初始化
void HAL_IWDG_Reset(HAL_IWDG_x);   // 模块复位
void HAL_IWDG_Enable(HAL_IWDG_x);  // 模块打开
void HAL_IWDG_Disable(HAL_IWDG_x); // 模块关闭
//
void HAL_IWDG_SetResetTimemS(HAL_IWDG_x, int32_t ms); // 设置看门狗超时复位时间,单位mS,实际复位时间向上取整,例如设置为130mS,实际一步为128mS,则按照256mS进行配置
void HAL_IWDG_Feed(HAL_IWDG_x);                       // 喂狗
#endif
