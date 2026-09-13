#ifndef __HAL_LKSMCU_SPI_H__
#define __HAL_LKSMCU_SPI_H__
#include "stdint.h"
#include "../include/hal_lksmcu_gpio.h"
typedef enum
{
    HAL_SPI_0,
    HAL_SPI_1,
} HAL_SPI_x;
typedef enum
{
    HAL_SPI_MODE_MASTER_LSB_00 = 0, ///< 主模式 低位先发 CPOL0 CPHA0
    HAL_SPI_MODE_MASTER_LSB_01,     ///< 主模式 低位先发 CPOL0 CPHA1
    HAL_SPI_MODE_MASTER_LSB_10,     ///< 主模式 低位先发 CPOL1 CPHA0
    HAL_SPI_MODE_MASTER_LSB_11,     ///< 主模式 低位先发 CPOL1 CPHA1
    HAL_SPI_MODE_MASTER_MSB_00,     ///< 主模式 高位先发 CPOL0 CPHA0
    HAL_SPI_MODE_MASTER_MSB_01,     ///< 主模式 高位先发 CPOL0 CPHA1
    HAL_SPI_MODE_MASTER_MSB_10,     ///< 主模式 高位先发 CPOL1 CPHA0
    HAL_SPI_MODE_MASTER_MSB_11,     ///< 主模式 高位先发 CPOL1 CPHA1
    HAL_SPI_MODE_SLAVE_LSB_00,      ///< 从模式 低位先发 CPOL0 CPHA0
    HAL_SPI_MODE_SLAVE_LSB_01,      ///< 从模式 低位先发 CPOL0 CPHA1
    HAL_SPI_MODE_SLAVE_LSB_10,      ///< 从模式 低位先发 CPOL1 CPHA0
    HAL_SPI_MODE_SLAVE_LSB_11,      ///< 从模式 低位先发 CPOL1 CPHA1
    HAL_SPI_MODE_SLAVE_MSB_00,      ///< 从模式 高位先发 CPOL0 CPHA0
    HAL_SPI_MODE_SLAVE_MSB_01,      ///< 从模式 高位先发 CPOL0 CPHA1
    HAL_SPI_MODE_SLAVE_MSB_10,      ///< 从模式 高位先发 CPOL1 CPHA0
    HAL_SPI_MODE_SLAVE_MSB_11,      ///< 从模式 高位先发 CPOL1 CPHA1
} HAL_SPI_MODE_x;
// 初始化
void HAL_SPI_Reset(HAL_SPI_x);   // 模块复位
void HAL_SPI_Enable(HAL_SPI_x);  // 模块打开
void HAL_SPI_Disable(HAL_SPI_x); // 模块关闭

void HAL_SPI_SetBaud(HAL_SPI_x spi, uint32_t baud);
void HAL_SPI_SetClockDiv(HAL_SPI_x spi, uint32_t div); // 设置时钟分频 div=实际除数(2,4,6...)
uint32_t HAL_SPI_GetClockDiv(HAL_SPI_x spi);           // 获取时钟分频实际除数
uint32_t HAL_SPI_GetClockFreq(HAL_SPI_x spi);          // 获取SCK时钟频率(Hz)
uint32_t HAL_SPI_GetBaud(HAL_SPI_x spi);               // 获取当前波特率(=SCK频率)
void HAL_SPI_SetMode(HAL_SPI_x, HAL_SPI_MODE_x);

void HAL_SPI_SetGpioCs(HAL_SPI_x, HAL_GPIO_Px pin);
void HAL_SPI_SetGpioMosi(HAL_SPI_x, HAL_GPIO_Px pin);
void HAL_SPI_SetGpioMiso(HAL_SPI_x, HAL_GPIO_Px pin);
void HAL_SPI_SetGpioClk(HAL_SPI_x, HAL_GPIO_Px pin);

void HAL_SPI_SetGpioDi(HAL_SPI_x, HAL_GPIO_Px pin); // 不自动识别模式，直接指定输入或输出状态
void HAL_SPI_SetGpioDo(HAL_SPI_x, HAL_GPIO_Px pin); // 不自动识别模式，直接指定输入或输出状态

uint8_t HAL_SPI_TxData(HAL_SPI_x, uint8_t *data, uint32_t len);
uint8_t HAL_SPI_RxData(HAL_SPI_x, uint8_t *data, uint32_t len);
uint8_t HAL_SPI_RxTxData(HAL_SPI_x, uint8_t *rxdata, uint8_t *txdata, uint32_t len);
uint8_t HAL_SPI_TxDataWidth16(HAL_SPI_x, uint16_t *data, uint32_t len);
uint8_t HAL_SPI_RxDataWidth16(HAL_SPI_x, uint16_t *data, uint32_t len);
uint8_t HAL_SPI_RxTxDataWidth16(HAL_SPI_x, uint16_t *rxdata, uint16_t *txdata, uint32_t len);
#endif
