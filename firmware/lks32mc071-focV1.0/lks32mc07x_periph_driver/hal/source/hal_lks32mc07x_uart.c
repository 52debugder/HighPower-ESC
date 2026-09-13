#include "../include/hal_lksmcu_clk.h"
#include "../include/hal_lksmcu_uart.h"
#include "../hal_lks32mc07x.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"
#include "stdint.h"

static uint32_t hal_baud_set[2] = {0, 0};
// 初始化
// 模块复位
void HAL_UART_Reset(HAL_UART_x UART_x)
{
    switch (UART_x)
    {
        case HAL_UART_0:

            // 系统寄存器解锁
            HAL_REG_SYS_UNLOCK();
            HAL_REG_SET(SYS_SFT_RST, SYS_SFT_RST_UART0_SFT_RST_BIT);
            HAL_REG_RESET(SYS_SFT_RST, SYS_SFT_RST_UART0_SFT_RST_BIT);
            // 系统寄存器上锁
            HAL_REG_SYS_LOCK();
            break;
        case HAL_UART_1:

            // 系统寄存器解锁
            HAL_REG_SYS_UNLOCK();
            HAL_REG_SET(SYS_SFT_RST, SYS_SFT_RST_UART1_SFT_RST_BIT);
            HAL_REG_RESET(SYS_SFT_RST, SYS_SFT_RST_UART1_SFT_RST_BIT);
            // 系统寄存器上锁
            HAL_REG_SYS_LOCK();
            break;
        default:
            break;
    }
}
// 模块打开
void HAL_UART_Enable(HAL_UART_x UART_x)
{
    switch (UART_x)
    {
        case HAL_UART_0:

            // 系统寄存器解锁
            HAL_REG_SYS_UNLOCK();
            HAL_REG_SET(SYS_CLK_FEN, SYS_CLK_FEN_UART0_CLK_EN_BIT);
            // 系统寄存器上锁
            HAL_REG_SYS_LOCK();
            break;
        case HAL_UART_1:

            // 系统寄存器解锁
            HAL_REG_SYS_UNLOCK();
            HAL_REG_SET(SYS_CLK_FEN, SYS_CLK_FEN_UART1_CLK_EN_BIT);
            // 系统寄存器上锁
            HAL_REG_SYS_LOCK();
            break;
        default:
            break;
    }
}
// 模块关闭
void HAL_UART_Disable(HAL_UART_x UART_x)
{
    switch (UART_x)
    {
        case HAL_UART_0:

            // 系统寄存器解锁
            HAL_REG_SYS_UNLOCK();
            HAL_REG_RESET(SYS_CLK_FEN, SYS_CLK_FEN_UART0_CLK_EN_BIT);
            // 系统寄存器上锁
            HAL_REG_SYS_LOCK();
            break;
        case HAL_UART_1:

            // 系统寄存器解锁
            HAL_REG_SYS_UNLOCK();
            HAL_REG_RESET(SYS_CLK_FEN, SYS_CLK_FEN_UART1_CLK_EN_BIT);
            // 系统寄存器上锁
            HAL_REG_SYS_LOCK();
            break;
        default:
            break;
    }
}
void HAL_UART_SetBaud(HAL_UART_x UART_x, uint32_t baud)
{
    uint32_t mclk = HAL_CLK_GetMcuFreq();
    uint32_t div0;
    uint32_t div1;
    uint32_t divs   = 1;
    uint32_t divmax = (UARTx_DIVH_DIVH_MAX << 8) | UARTx_DIVL_DIVL_MAX;
    if (baud > mclk)
    {
        baud = mclk;
    }
    hal_baud_set[UART_x] = baud;

    if (hal_baud_set[0] != 0)
    {
        div0 = mclk / hal_baud_set[0];
    }
    else
    {
        div0 = 0;
    }
    if (hal_baud_set[1] != 0)
    {
        div1 = mclk / hal_baud_set[1];
    }
    else
    {
        div1 = 0;
    }

    while ((div0 > divmax) || (div1 > divmax))
    {
        // 为了方便计算，这里只考虑1 2 4 8 16 32 ... 这样的分频系数
        if (divs < SYS_CLK_DIV2_DIV2_MAX + 1)
        {
            divs <<= 1;
        }
        else
        {
            divs = SYS_CLK_DIV2_DIV2_MAX + 1;
        }
        div0 >>= 1;
        div1 >>= 1;
    }
    divs = divs - 1;
    HAL_REG_SYS_UNLOCK();
    HAL_REG_WRITE_BIT_MASK_POS(SYS_CLK_DIV2, SYS_CLK_DIV2_DIV2, divs);
    HAL_REG_SYS_LOCK();
    HAL_REG_WRITE_BIT_MASK_POS(HAL_UART[0]->DIVH, UARTx_DIVH_DIVH, div0 >> 8);
    HAL_REG_WRITE_BIT_MASK_POS(HAL_UART[0]->DIVL, UARTx_DIVL_DIVL, div0 & 0xff);
    HAL_REG_WRITE_BIT_MASK_POS(HAL_UART[1]->DIVH, UARTx_DIVH_DIVH, div1 >> 8);
    HAL_REG_WRITE_BIT_MASK_POS(HAL_UART[1]->DIVL, UARTx_DIVL_DIVL, div1 & 0xff);
}

// 设置UART全局工作时钟分频 (UART0/1共享)
void HAL_UART_SetClockDiv(HAL_UART_x UART_x, uint32_t div)
{
    (void)UART_x;
    if (div < 1) div = 1;
    HAL_REG_SYS_UNLOCK();
    HAL_REG_WRITE_BIT_MASK_POS(SYS_CLK_DIV2, SYS_CLK_DIV2_DIV2, div - 1);
    HAL_REG_SYS_LOCK();
}

// 获取UART工作时钟分频实际除数
uint32_t HAL_UART_GetClockDiv(HAL_UART_x UART_x)
{
    (void)UART_x;
    return HAL_REG_READ_BIT_MASK_POS(SYS_CLK_DIV2, SYS_CLK_DIV2_DIV2) + 1;
}

// 获取UART工作时钟频率
uint32_t HAL_UART_GetClockFreq(HAL_UART_x UART_x)
{
    return HAL_CLK_GetMcuFreq() / HAL_UART_GetClockDiv(UART_x);
}

// 获取当前波特率
uint32_t HAL_UART_GetBaud(HAL_UART_x UART_x)
{
    uint32_t clk  = HAL_UART_GetClockFreq(UART_x);
    uint32_t divh = HAL_REG_READ_BIT_MASK_POS(HAL_UART[UART_x]->DIVH, UARTx_DIVH_DIVH);
    uint32_t divl = HAL_REG_READ_BIT_MASK_POS(HAL_UART[UART_x]->DIVL, UARTx_DIVL_DIVL);
    return clk / ((divh << 8 | divl) + 1);
}

void HAL_UART_TxData(HAL_UART_x UART_x, uint8_t *data, uint32_t len)
{
    for (; len > 0; len--)
    {
        HAL_REG_WRITE(HAL_UART[UART_x]->BUFF, *data);
        data++;
        while (HAL_REG_READ_BIT(HAL_UART[UART_x]->STT, UARTx_STT_TX_BUF_EMPTY_BIT) == 0)
        {
        }
    }
}

void HAL_UART_SetMode(HAL_UART_x uart_x, HAL_UART_MODE_x mode_x)
{

    uint32_t mask = (UARTx_CTRL_CK_EN_BIT |
                     UARTx_CTRL_CK_TYPE_BIT |
                     UARTx_CTRL_BIT_ORDER_BIT |
                     UARTx_CTRL_STOP_LEN_BIT |
                     UARTx_CTRL_BYTE_LEN_BIT);
    switch (mode_x)
    {
        case HAL_UART_MODE_LSB_STOP1_NONE: ///< 低位先发 1位停止位 无校验
        {
            HAL_REG_WRITE_BIT(HAL_UART[uart_x]->CTRL, mask, 0);
            break;
        }
        case HAL_UART_MODE_LSB_STOP2_NONE: ///< 低位先发 2位停止位 无校验
        {
            HAL_REG_WRITE_BIT(HAL_UART[uart_x]->CTRL, mask, UARTx_CTRL_STOP_LEN_BIT);
            break;
        }
        case HAL_UART_MODE_LSB_STOP1_ODD: ///< 低位先发 1位停止位 奇校验
        {
            HAL_REG_WRITE_BIT(HAL_UART[uart_x]->CTRL, mask, UARTx_CTRL_CK_EN_BIT | UARTx_CTRL_CK_TYPE_BIT | UARTx_CTRL_BYTE_LEN_BIT);
            break;
        }
        case HAL_UART_MODE_LSB_STOP2_ODD: ///< 低位先发 2位停止位 奇校验
        {
            HAL_REG_WRITE_BIT(HAL_UART[uart_x]->CTRL, mask, UARTx_CTRL_CK_EN_BIT | UARTx_CTRL_CK_TYPE_BIT | UARTx_CTRL_STOP_LEN_BIT | UARTx_CTRL_BYTE_LEN_BIT);
            break;
        }
        case HAL_UART_MODE_LSB_STOP1_EVEN: ///< 低位先发 1位停止位 偶校验
        {
            HAL_REG_WRITE_BIT(HAL_UART[uart_x]->CTRL, mask, UARTx_CTRL_CK_EN_BIT | UARTx_CTRL_BYTE_LEN_BIT);
            break;
        }
        case HAL_UART_MODE_LSB_STOP2_EVEN: ///< 低位先发 2位停止位 偶校验
        {
            HAL_REG_WRITE_BIT(HAL_UART[uart_x]->CTRL, mask, UARTx_CTRL_CK_EN_BIT | UARTx_CTRL_STOP_LEN_BIT | UARTx_CTRL_BYTE_LEN_BIT);
            break;
        }
        case HAL_UART_MODE_MSB_STOP1_NONE: ///< 高位先发 1位停止位 无校验
        {
            HAL_REG_WRITE_BIT(HAL_UART[uart_x]->CTRL, mask, UARTx_CTRL_BIT_ORDER_BIT);
            break;
        }
        case HAL_UART_MODE_MSB_STOP2_NONE: ///< 高位先发 2位停止位 无校验
        {
            HAL_REG_WRITE_BIT(HAL_UART[uart_x]->CTRL, mask, UARTx_CTRL_BIT_ORDER_BIT | UARTx_CTRL_STOP_LEN_BIT);
            break;
        }
        case HAL_UART_MODE_MSB_STOP1_ODD: ///< 高位先发 1位停止位 奇校验
        {
            HAL_REG_WRITE_BIT(HAL_UART[uart_x]->CTRL, mask, UARTx_CTRL_CK_EN_BIT | UARTx_CTRL_CK_TYPE_BIT | UARTx_CTRL_BIT_ORDER_BIT | UARTx_CTRL_BYTE_LEN_BIT);
            break;
        }
        case HAL_UART_MODE_MSB_STOP2_ODD: ///< 高位先发 2位停止位 奇校验
        {
            HAL_REG_WRITE_BIT(HAL_UART[uart_x]->CTRL, mask, UARTx_CTRL_CK_EN_BIT | UARTx_CTRL_CK_TYPE_BIT | UARTx_CTRL_BIT_ORDER_BIT | UARTx_CTRL_STOP_LEN_BIT | UARTx_CTRL_BYTE_LEN_BIT);
            break;
        }
        case HAL_UART_MODE_MSB_STOP1_EVEN: ///< 高位先发 1位停止位 偶校验
        {
            HAL_REG_WRITE_BIT(HAL_UART[uart_x]->CTRL, mask, UARTx_CTRL_CK_EN_BIT | UARTx_CTRL_BIT_ORDER_BIT | UARTx_CTRL_BYTE_LEN_BIT);
            break;
        }
        case HAL_UART_MODE_MSB_STOP2_EVEN: ///< 高位先发 2位停止位 偶校验
        {
            HAL_REG_WRITE_BIT(HAL_UART[uart_x]->CTRL, mask, UARTx_CTRL_CK_EN_BIT | UARTx_CTRL_BIT_ORDER_BIT | UARTx_CTRL_STOP_LEN_BIT | UARTx_CTRL_BYTE_LEN_BIT);
            break;
        }
    }
}
/**
 * @brief 设置IO极性
 * @param uart_x UART模块编号
 * @param pol 极性配置
 */
void HAL_UART_SetPolarity(HAL_UART_x uart_x, HAL_UART_POL_x pol)
{
    switch (pol)
    {
        case HAL_UART_POL_RX_POS_TX_POS:
            HAL_REG_RESET(HAL_UART[uart_x]->IOC, UARTx_IOC_RXD_INV_BIT);
            HAL_REG_RESET(HAL_UART[uart_x]->IOC, UARTx_IOC_TXD_INV_BIT);
            break;
        case HAL_UART_POL_RX_POS_TX_NEG:
            HAL_REG_RESET(HAL_UART[uart_x]->IOC, UARTx_IOC_RXD_INV_BIT);
            HAL_REG_SET(HAL_UART[uart_x]->IOC, UARTx_IOC_TXD_INV_BIT);
            break;
        case HAL_UART_POL_RX_NEG_TX_POS:
            HAL_REG_SET(HAL_UART[uart_x]->IOC, UARTx_IOC_RXD_INV_BIT);
            HAL_REG_RESET(HAL_UART[uart_x]->IOC, UARTx_IOC_TXD_INV_BIT);
            break;
        case HAL_UART_POL_RX_NEG_TX_NEG:
            HAL_REG_SET(HAL_UART[uart_x]->IOC, UARTx_IOC_RXD_INV_BIT);
            HAL_REG_SET(HAL_UART[uart_x]->IOC, UARTx_IOC_TXD_INV_BIT);
            break;
        default:
            break;
    }
}
uint8_t HAL_UART_ReadBuffer(HAL_UART_x uart_x)
{
    return HAL_REG_READ(HAL_UART[uart_x]->BUFF);
}
void HAL_UART_WriteBuffer(HAL_UART_x uart_x, uint8_t buff)
{
    HAL_REG_WRITE(HAL_UART[uart_x]->BUFF, buff);
}
void HAL_UART_SetGpioTx(HAL_UART_x uart_x, HAL_GPIO_Px px)
{
    (void)uart_x;
    HAL_GPIO_SetAf(px, HAL_GPIO_AF_UART);
    HAL_GPIO_SetMode(px, HAL_GPIO_MODE_OUT);
}
void HAL_UART_SetGpioRx(HAL_UART_x uart_x, HAL_GPIO_Px px)
{
    (void)uart_x;
    HAL_GPIO_SetAf(px, HAL_GPIO_AF_UART);
    HAL_GPIO_SetMode(px, HAL_GPIO_MODE_IN);
}
