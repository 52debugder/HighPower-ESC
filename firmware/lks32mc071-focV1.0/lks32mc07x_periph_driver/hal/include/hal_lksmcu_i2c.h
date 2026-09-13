#ifndef __HAL_LKSMCU_I2C_H__
#define __HAL_LKSMCU_I2C_H__
#include "hal_lksmcu_gpio.h"
#include "stdint.h"
typedef enum
{
    HAL_I2C_0,
    HAL_I2C_1,
} HAL_I2C_x;
// 初始化
void HAL_I2C_Reset(HAL_I2C_x);   // 模块复位
void HAL_I2C_Enable(HAL_I2C_x);  // 模块打开
void HAL_I2C_Disable(HAL_I2C_x); // 模块关闭
//
void HAL_I2C_SetBaud(HAL_I2C_x, uint32_t baud);
void HAL_I2C_SetClockDiv(HAL_I2C_x i2c_x, uint32_t div); // 设置I2C全局工作时钟分频 div=实际除数(I2C0/1共享)
uint32_t HAL_I2C_GetClockDiv(HAL_I2C_x i2c_x);           // 获取I2C工作时钟分频实际除数
uint32_t HAL_I2C_GetClockFreq(HAL_I2C_x i2c_x);          // 获取I2C工作时钟频率(Hz)
uint32_t HAL_I2C_GetBaud(HAL_I2C_x i2c_x);               // 获取当前SCL波特率(Hz)
uint8_t HAL_I2C_TxData(HAL_I2C_x, uint8_t addr, uint8_t *data, uint32_t len);
uint8_t HAL_I2C_RxData(HAL_I2C_x, uint8_t addr, uint8_t *data, uint32_t len);

void HAL_I2C_SetGpioScl(HAL_I2C_x, HAL_GPIO_Px i2cgpio);
void HAL_I2C_SetGpioSda(HAL_I2C_x, HAL_GPIO_Px i2cgpio);

void HAL_I2C_BusReset(HAL_I2C_x); // 复位总线

#endif
