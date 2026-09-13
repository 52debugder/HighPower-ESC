#ifndef __HAL_LKSMCU_DMA_H__
#define __HAL_LKSMCU_DMA_H__

#include "../include/hal_lksmcu_spi.h"
#include "../include/hal_lksmcu_uart.h"
#include "../include/hal_lksmcu_i2c.h"
#include "stdint.h"
typedef enum
{
    HAL_DMA_0, ///< DMA模块0
    HAL_DMA_1, ///< DMA模块1
    HAL_DMA_2, ///< DMA模块2
    HAL_DMA_3, ///< DMA模块3

#ifdef HAL_TEST_NOT_SUPPORTED
    HAL_DMA_4, ///< DMA模块4
    HAL_DMA_5, ///< DMA模块5
    HAL_DMA_6, ///< DMA模块6
    HAL_DMA_7, ///< DMA模块7
#endif
} HAL_DMA_x;

// 初始化
void HAL_DMA_Reset(HAL_DMA_x);   // 模块复位
void HAL_DMA_Enable(HAL_DMA_x);  // 模块打开
void HAL_DMA_Disable(HAL_DMA_x); // 模块关闭

void HAL_DMA_MemCopy(HAL_DMA_x, void *start, void *end, uint32_t len); // 内存复制

void HAL_DMA_UartTx(HAL_DMA_x, HAL_UART_x, uint8_t *start, uint32_t len); // dma使用uart发送数据,需要先初始化好对应的uart模块
void HAL_DMA_SpiTx(HAL_DMA_x, HAL_SPI_x, uint8_t *start, uint32_t len);   // dma使用spi发送数据,需要先初始化好对应的spi模块
void HAL_DMA_I2cTx(HAL_DMA_x, HAL_I2C_x, uint8_t *start, uint32_t len);   // dma使用i2c发送数据,需要先初始化好对应的i2c模块
void HAL_DMA_UartRx(HAL_DMA_x, HAL_UART_x, uint8_t *start, uint32_t len); // dma使用uart接收数据,需要先初始化好对应的uart模块
void HAL_DMA_SpiRx(HAL_DMA_x, HAL_SPI_x, uint8_t *start, uint32_t len);   // dma使用spi接收数据,需要先初始化好对应的spi模块
void HAL_DMA_I2cRx(HAL_DMA_x, HAL_I2C_x, uint8_t *start, uint32_t len);   // dma使用i2c接收数据,需要先初始化好对应的i2c模块

void HAL_DMA_SpiRxTx(HAL_DMA_x, HAL_DMA_x, HAL_SPI_x, uint8_t *txdata, uint8_t *rxdata, uint32_t len); // 使用两个dma模块和一个spi模块,同时发送&接收数据,需要先初始化好对应的spi模块

#endif
