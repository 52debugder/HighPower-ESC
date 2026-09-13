#include "../include/hal_lksmcu_dma.h"
#include "../hal_lks32mc07x.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"

// 初始化
// 模块复位
static uint8_t HAL_DMA_ena = 0;
void HAL_DMA_Reset(HAL_DMA_x dma_x)
{
    (void)dma_x;
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();

    HAL_REG_SET(SYS_SFT_RST, SYS_SFT_RST_DMA0_SFT_RST_BIT);
    HAL_REG_RESET(SYS_SFT_RST, SYS_SFT_RST_DMA0_SFT_RST_BIT);
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}
// 模块打开
void HAL_DMA_Enable(HAL_DMA_x dma_x)
{
    (void)dma_x;
    HAL_DMA_ena |= (1 << dma_x);
    HAL_REG_SET(DMA0_CTRL, DMA0_CTRL_EN_BIT);
}
// 模块关闭
void HAL_DMA_Disable(HAL_DMA_x dma_x)
{
    HAL_DMA_ena &= ~(1 << dma_x);
    HAL_REG_RESET(HAL_DMA[dma_x]->CCR, DMA0_CCRx_EN_BIT);
    if (HAL_DMA_ena == 0)
    {
        HAL_REG_RESET(DMA0_CTRL, DMA0_CTRL_EN_BIT);
    }
}
// 内存复制
void HAL_DMA_MemCopy(HAL_DMA_x DMA_x, void *start, void *end, uint32_t len)
{
    uint32_t s, t;
    s = (uint32_t)(uintptr_t)start;
    t = (uint32_t)(uintptr_t)end;
    if (len == 0)
    {
        return;
    }
    for (; len > 0;)
    {
        uint32_t sentlen;
        if (len > DMA0_CTMSx_TMS_MAX)
        {
            sentlen = DMA0_CTMSx_TMS_MAX;
        }
        else
        {
            sentlen = len;
        }
        len -= sentlen;
        HAL_REG_WRITE(HAL_DMA[DMA_x]->CCR, 0);
        HAL_REG_WRITE(HAL_DMA[DMA_x]->SADR, s);
        HAL_REG_WRITE(HAL_DMA[DMA_x]->DADR, t);
        HAL_REG_WRITE(HAL_DMA[DMA_x]->CTMS, sentlen);
        HAL_REG_WRITE(HAL_DMA[DMA_x]->CCR, DMA0_CCRx_EN_BIT | DMA0_CCRx_DINC_BIT | DMA0_CCRx_SINC_BIT);
        HAL_REG_WRITE(DMA0_IF, DMA0_IF_CH0_FIF_BIT << DMA_x);
        HAL_REG_WRITE(HAL_DMA[DMA_x]->REN, DMA0_RENx_SW_REN_BIT);
        while (HAL_REG_READ_BIT(DMA0_IF, DMA0_IF_CH0_FIF_BIT << DMA_x) == 0)
        {
        }
        HAL_REG_WRITE(DMA0_IF, DMA0_IF_CH0_FIF_BIT << DMA_x);
        s += sentlen;
        t += sentlen;
    }
}
// dma使用uart发送数据,需要先初始化好对应的uart模块
void HAL_DMA_UartTx(HAL_DMA_x dma_x, HAL_UART_x UART_x, uint8_t *start, uint32_t len)
{
    HAL_REG_WRITE(HAL_DMA[dma_x]->CCR, 0);
    HAL_REG_WRITE(HAL_DMA[dma_x]->SADR, (uint32_t)(uintptr_t)start);
    HAL_REG_WRITE(HAL_DMA[dma_x]->DADR, (uint32_t)(uintptr_t)(&(HAL_UART[UART_x]->BUFF)));
    HAL_REG_WRITE(HAL_DMA[dma_x]->CTMS, len);
    HAL_REG_WRITE(HAL_DMA[dma_x]->CCR, DMA0_CCRx_EN_BIT | DMA0_CCRx_RMODE_BIT | DMA0_CCRx_SINC_BIT);
    if (UART_x == HAL_UART_0)
    {
        HAL_REG_WRITE(HAL_DMA[dma_x]->REN, DMA0_RENx_SW_REN_BIT | DMA0_RENx_UART0_TX_REN_BIT);
    }
    else // UART1
    {
        HAL_REG_WRITE(HAL_DMA[dma_x]->REN, DMA0_RENx_SW_REN_BIT | DMA0_RENx_UART1_TX_REN_BIT);
    }
}
// dma使用spi发送数据,需要先初始化好对应的spi模块
void HAL_DMA_SpiTx(HAL_DMA_x dma_x, HAL_SPI_x SPI_x, uint8_t *start, uint32_t len)
{
    HAL_REG_WRITE(HAL_DMA[dma_x]->CCR, 0);
    HAL_REG_WRITE(HAL_DMA[dma_x]->SADR, (uint32_t)(uintptr_t)start);
    HAL_REG_WRITE(HAL_DMA[dma_x]->DADR, (uint32_t)(uintptr_t)(&(HAL_SPI[SPI_x]->TXDATA)));
    HAL_REG_WRITE(HAL_DMA[dma_x]->CTMS, len);
    HAL_REG_WRITE(HAL_DMA[dma_x]->CCR, DMA0_CCRx_EN_BIT | DMA0_CCRx_RMODE_BIT | DMA0_CCRx_SINC_BIT);
    HAL_REG_WRITE(HAL_DMA[dma_x]->REN, DMA0_RENx_SW_REN_BIT | DMA0_RENx_SPI_TX_REN_BIT);
}
// dma使用i2c发送数据,需要先初始化好对应的i2c模块
void HAL_DMA_I2cTx(HAL_DMA_x dma_x, HAL_I2C_x I2Cx, uint8_t *start, uint32_t len)
{
    HAL_REG_WRITE(HAL_DMA[dma_x]->CCR, 0);
    HAL_REG_WRITE(HAL_DMA[dma_x]->SADR, (uint32_t)(uintptr_t)start);
    HAL_REG_WRITE(HAL_DMA[dma_x]->DADR, (uint32_t)(uintptr_t)(&(HAL_I2C[I2Cx]->DATA)));
    HAL_REG_WRITE(HAL_DMA[dma_x]->CTMS, len);
    HAL_REG_WRITE(HAL_DMA[dma_x]->CCR, DMA0_CCRx_EN_BIT | DMA0_CCRx_RMODE_BIT | DMA0_CCRx_SINC_BIT);
    HAL_REG_WRITE(HAL_DMA[dma_x]->REN, DMA0_RENx_SW_REN_BIT | DMA0_RENx_I2C0_TX_REN_BIT);
}
// dma使用uart接收数据,需要先初始化好对应的uart模块
void HAL_DMA_UartRx(HAL_DMA_x dma_x, HAL_UART_x UART_x, uint8_t *start, uint32_t len)
{
    HAL_REG_WRITE(HAL_DMA[dma_x]->CCR, 0);
    HAL_REG_WRITE(HAL_DMA[dma_x]->SADR, (uint32_t)(uintptr_t)(&(HAL_UART[UART_x]->BUFF)));
    HAL_REG_WRITE(HAL_DMA[dma_x]->DADR, (uint32_t)(uintptr_t)start);
    HAL_REG_WRITE(HAL_DMA[dma_x]->CTMS, len);
    HAL_REG_WRITE(HAL_DMA[dma_x]->CCR, DMA0_CCRx_EN_BIT | DMA0_CCRx_RMODE_BIT | DMA0_CCRx_DINC_BIT);
    if (UART_x == HAL_UART_0)
    {
        HAL_REG_WRITE(HAL_DMA[dma_x]->REN, DMA0_RENx_UART0_RX_REN_BIT);
    }
    else // UART1
    {
        HAL_REG_WRITE(HAL_DMA[dma_x]->REN, DMA0_RENx_UART1_RX_REN_BIT);
    }
}
// dma使用spi接收数据,需要先初始化好对应的spi模块
void HAL_DMA_SpiRx(HAL_DMA_x dma_x, HAL_SPI_x SPI_x, uint8_t *start, uint32_t len)
{
    HAL_REG_WRITE(HAL_DMA[dma_x]->CCR, 0);
    HAL_REG_WRITE(HAL_DMA[dma_x]->SADR, (uint32_t)(uintptr_t)(&(HAL_SPI[SPI_x]->RXDATA)));
    HAL_REG_WRITE(HAL_DMA[dma_x]->DADR, (uint32_t)(uintptr_t)start);
    HAL_REG_WRITE(HAL_DMA[dma_x]->CTMS, len);
    HAL_REG_WRITE(HAL_DMA[dma_x]->CCR, DMA0_CCRx_EN_BIT | DMA0_CCRx_RMODE_BIT | DMA0_CCRx_DINC_BIT);
    HAL_REG_WRITE(HAL_DMA[dma_x]->REN, DMA0_RENx_SPI_RX_REN_BIT);
}
// dma使用i2c接收数据,需要先初始化好对应的i2c模块
void HAL_DMA_I2cRx(HAL_DMA_x dma_x, HAL_I2C_x I2Cx, uint8_t *start, uint32_t len)
{
    HAL_REG_WRITE(HAL_DMA[dma_x]->CCR, 0);
    HAL_REG_WRITE(HAL_DMA[dma_x]->SADR, (uint32_t)(uintptr_t)(&(HAL_I2C[I2Cx]->DATA)));
    HAL_REG_WRITE(HAL_DMA[dma_x]->DADR, (uint32_t)(uintptr_t)start);
    HAL_REG_WRITE(HAL_DMA[dma_x]->CTMS, len);
    HAL_REG_WRITE(HAL_DMA[dma_x]->CCR, DMA0_CCRx_EN_BIT | DMA0_CCRx_RMODE_BIT | DMA0_CCRx_DINC_BIT);
    HAL_REG_WRITE(HAL_DMA[dma_x]->REN, DMA0_RENx_I2C0_RX_REN_BIT);
}
// 使用两个dma模块和一个spi模块,同时发送&接收数据,需要先初始化好对应的spi模块
void HAL_DMA_SpiRxTx(HAL_DMA_x DMA1_x, HAL_DMA_x DMA2_x, HAL_SPI_x SPI_x, uint8_t *txdata, uint8_t *rxdata, uint32_t len)
{
    HAL_REG_WRITE(HAL_DMA[DMA1_x]->CCR, 0);
    HAL_REG_WRITE(HAL_DMA[DMA1_x]->SADR, (uint32_t)(uintptr_t)(&(HAL_SPI[SPI_x]->RXDATA)));
    HAL_REG_WRITE(HAL_DMA[DMA1_x]->DADR, (uint32_t)(uintptr_t)rxdata);
    HAL_REG_WRITE(HAL_DMA[DMA1_x]->CTMS, len);
    HAL_REG_WRITE(HAL_DMA[DMA1_x]->CCR, DMA0_CCRx_EN_BIT | DMA0_CCRx_RMODE_BIT | DMA0_CCRx_DINC_BIT);
    HAL_REG_WRITE(HAL_DMA[DMA1_x]->REN, DMA0_RENx_SPI_RX_REN_BIT);

    HAL_REG_WRITE(HAL_DMA[DMA2_x]->CCR, 0);
    HAL_REG_WRITE(HAL_DMA[DMA2_x]->SADR, (uint32_t)(uintptr_t)txdata);
    HAL_REG_WRITE(HAL_DMA[DMA2_x]->DADR, (uint32_t)(uintptr_t)(&(HAL_SPI[SPI_x]->TXDATA)));
    HAL_REG_WRITE(HAL_DMA[DMA2_x]->CTMS, len);
    HAL_REG_WRITE(HAL_DMA[DMA2_x]->CCR, DMA0_CCRx_EN_BIT | DMA0_CCRx_RMODE_BIT | DMA0_CCRx_SINC_BIT);
    HAL_REG_WRITE(HAL_DMA[DMA2_x]->REN, DMA0_RENx_SW_REN_BIT | DMA0_RENx_SPI_TX_REN_BIT);
}
