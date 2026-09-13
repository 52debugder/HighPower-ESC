
#ifndef __HAL_LKSMCU_UART_H__
#define __HAL_LKSMCU_UART_H__
#include "stdint.h"
#include "../include/hal_lksmcu_gpio.h"
typedef enum
{
    HAL_UART_0,
    HAL_UART_1,
#ifdef HAL_TEST_NOT_SUPPORTED
    HAL_UART_2,
#endif
} HAL_UART_x;
typedef enum
{
    HAL_UART_MODE_LSB_STOP1_NONE, ///< 低位先发 1位停止位 无校验
    HAL_UART_MODE_LSB_STOP2_NONE, ///< 低位先发 2位停止位 无校验
    HAL_UART_MODE_LSB_STOP1_ODD,  ///< 低位先发 1位停止位 奇校验
    HAL_UART_MODE_LSB_STOP2_ODD,  ///< 低位先发 2位停止位 奇校验
    HAL_UART_MODE_LSB_STOP1_EVEN, ///< 低位先发 1位停止位 偶校验
    HAL_UART_MODE_LSB_STOP2_EVEN, ///< 低位先发 2位停止位 偶校验
    HAL_UART_MODE_MSB_STOP1_NONE, ///< 高位先发 1位停止位 无校验
    HAL_UART_MODE_MSB_STOP2_NONE, ///< 高位先发 2位停止位 无校验
    HAL_UART_MODE_MSB_STOP1_ODD,  ///< 高位先发 1位停止位 奇校验
    HAL_UART_MODE_MSB_STOP2_ODD,  ///< 高位先发 2位停止位 奇校验
    HAL_UART_MODE_MSB_STOP1_EVEN, ///< 高位先发 1位停止位 偶校验
    HAL_UART_MODE_MSB_STOP2_EVEN, ///< 高位先发 2位停止位 偶校验
} HAL_UART_MODE_x;

typedef enum
{
    HAL_UART_POL_RX_POS_TX_POS, // RX正逻辑 TX正逻辑 复位后的默认值
    HAL_UART_POL_RX_POS_TX_NEG, // RX正逻辑 TX负逻辑
    HAL_UART_POL_RX_NEG_TX_POS, // RX负逻辑 TX正逻辑
    HAL_UART_POL_RX_NEG_TX_NEG  // RX负逻辑 TX负逻辑
} HAL_UART_POL_x;
// 初始化
void HAL_UART_Reset(HAL_UART_x);   // 模块复位
void HAL_UART_Enable(HAL_UART_x);  // 模块打开
void HAL_UART_Disable(HAL_UART_x); // 模块关闭
//
void HAL_UART_SetBaud(HAL_UART_x, uint32_t baud);
void HAL_UART_SetClockDiv(HAL_UART_x UART_x, uint32_t div); // 设置UART全局工作时钟分频 div=实际除数(UART0/1共享)
uint32_t HAL_UART_GetClockDiv(HAL_UART_x UART_x);           // 获取UART工作时钟分频实际除数
uint32_t HAL_UART_GetClockFreq(HAL_UART_x UART_x);          // 获取UART工作时钟频率(Hz)
uint32_t HAL_UART_GetBaud(HAL_UART_x UART_x);               // 获取当前波特率
void HAL_UART_TxData(HAL_UART_x, uint8_t *data, uint32_t len);
void HAL_UART_SetMode(HAL_UART_x, HAL_UART_MODE_x);
void HAL_UART_SetPolarity(HAL_UART_x, HAL_UART_POL_x);

uint8_t HAL_UART_ReadBuffer(HAL_UART_x);
void HAL_UART_WriteBuffer(HAL_UART_x, uint8_t buff);
void HAL_UART_SetGpioTx(HAL_UART_x, HAL_GPIO_Px); // 设置用于输出的gpio
void HAL_UART_SetGpioRx(HAL_UART_x, HAL_GPIO_Px); // 设置用于输出的gpio

#endif
