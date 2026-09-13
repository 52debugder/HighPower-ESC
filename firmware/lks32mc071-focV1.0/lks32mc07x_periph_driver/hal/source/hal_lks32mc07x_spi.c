
#include "../include/hal_lksmcu_spi.h"
#include "../hal_lks32mc07x.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"

/**
 * @brief 模块复位
 * @param spi SPI模块号
 */
void HAL_SPI_Reset(HAL_SPI_x spi)
{
    (void)spi;
    HAL_REG_SYS_UNLOCK();
    HAL_REG_SET(SYS_SFT_RST, SYS_SFT_RST_SPI0_SFT_RST_BIT);
    HAL_REG_RESET(SYS_SFT_RST, SYS_SFT_RST_SPI0_SFT_RST_BIT);
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 模块打开
 * @param spi SPI模块号
 */
void HAL_SPI_Enable(HAL_SPI_x spi)
{
    HAL_REG_SYS_UNLOCK();
    HAL_REG_SET(SYS_CLK_FEN, SYS_CLK_FEN_SPI0_CLK_EN_BIT);
    HAL_REG_SYS_LOCK();
    HAL_REG_SET(HAL_SPI[spi]->CFG, SPI0_CFG_EN_BIT);
}

/**
 * @brief 模块关闭
 * @param spi SPI模块号
 */
void HAL_SPI_Disable(HAL_SPI_x spi)
{
    HAL_REG_RESET(HAL_SPI[spi]->CFG, SPI0_CFG_EN_BIT);
    HAL_REG_SYS_UNLOCK();
    HAL_REG_RESET(SYS_CLK_FEN, SYS_CLK_FEN_SPI0_CLK_EN_BIT);
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 设置波特率
 * @param spi SPI模块号
 */
void HAL_SPI_SetBaud(HAL_SPI_x spi, uint32_t baud)
{
    uint32_t mclk = HAL_CLK_GetMcuFreq();
    uint32_t cnt  = (mclk / (2 * baud)) - 1;
    HAL_REG_WRITE_BIT_MASK_POS(HAL_SPI[spi]->BAUD, SPI0_BAUD_BAUD, cnt);
}

// 设置时钟分频
void HAL_SPI_SetClockDiv(HAL_SPI_x spi, uint32_t div)
{
    if (div < 2) div = 2;
    HAL_REG_WRITE_BIT_MASK_POS(HAL_SPI[spi]->BAUD, SPI0_BAUD_BAUD, div / 2 - 1);
}

// 获取时钟分频实际除数
uint32_t HAL_SPI_GetClockDiv(HAL_SPI_x spi)
{
    return 2 * (HAL_REG_READ_BIT_MASK_POS(HAL_SPI[spi]->BAUD, SPI0_BAUD_BAUD) + 1);
}

// 获取SCK时钟频率
uint32_t HAL_SPI_GetClockFreq(HAL_SPI_x spi)
{
    return HAL_CLK_GetMcuFreq() / HAL_SPI_GetClockDiv(spi);
}

// 获取当前波特率(=SCK频率)
uint32_t HAL_SPI_GetBaud(HAL_SPI_x spi)
{
    return HAL_SPI_GetClockFreq(spi);
}

/**
 * @brief 设置SPI模式
 * @param spi SPI模块号
 * @param mode SPI模式
 */
void HAL_SPI_SetMode(HAL_SPI_x spi, HAL_SPI_MODE_x mode)
{
    uint32_t mask = SPI0_CFG_MS_BIT | SPI0_CFG_CPHA_BIT | SPI0_CFG_CPOL_BIT | SPI0_CFG_ENDIAN_BIT;
    switch (mode)
    {
        case HAL_SPI_MODE_MASTER_LSB_00:
            HAL_REG_WRITE_BIT(HAL_SPI[spi]->CFG, mask, SPI0_CFG_MS_BIT | SPI0_CFG_ENDIAN_BIT);
            break;
        case HAL_SPI_MODE_MASTER_LSB_01:
            HAL_REG_WRITE_BIT(HAL_SPI[spi]->CFG, mask, SPI0_CFG_MS_BIT | SPI0_CFG_CPOL_BIT | SPI0_CFG_ENDIAN_BIT);
            break;
        case HAL_SPI_MODE_MASTER_LSB_10:
            HAL_REG_WRITE_BIT(HAL_SPI[spi]->CFG, mask, SPI0_CFG_MS_BIT | SPI0_CFG_CPHA_BIT | SPI0_CFG_ENDIAN_BIT);
            break;
        case HAL_SPI_MODE_MASTER_LSB_11:
            HAL_REG_WRITE_BIT(HAL_SPI[spi]->CFG, mask, SPI0_CFG_MS_BIT | SPI0_CFG_CPHA_BIT | SPI0_CFG_CPOL_BIT | SPI0_CFG_ENDIAN_BIT);
            break;
        case HAL_SPI_MODE_MASTER_MSB_00:
            HAL_REG_WRITE_BIT(HAL_SPI[spi]->CFG, mask, SPI0_CFG_MS_BIT | 0);
            break;
        case HAL_SPI_MODE_MASTER_MSB_01:
            HAL_REG_WRITE_BIT(HAL_SPI[spi]->CFG, mask, SPI0_CFG_MS_BIT | SPI0_CFG_CPOL_BIT);
            break;
        case HAL_SPI_MODE_MASTER_MSB_10:
            HAL_REG_WRITE_BIT(HAL_SPI[spi]->CFG, mask, SPI0_CFG_MS_BIT | SPI0_CFG_CPHA_BIT);
            break;
        case HAL_SPI_MODE_MASTER_MSB_11:
            HAL_REG_WRITE_BIT(HAL_SPI[spi]->CFG, mask, SPI0_CFG_MS_BIT | SPI0_CFG_CPHA_BIT | SPI0_CFG_CPOL_BIT);
            break;
        case HAL_SPI_MODE_SLAVE_LSB_00:
            HAL_REG_WRITE_BIT(HAL_SPI[spi]->CFG, mask, SPI0_CFG_ENDIAN_BIT);
            break;
        case HAL_SPI_MODE_SLAVE_LSB_01:
            HAL_REG_WRITE_BIT(HAL_SPI[spi]->CFG, mask, SPI0_CFG_CPOL_BIT | SPI0_CFG_ENDIAN_BIT);
            break;
        case HAL_SPI_MODE_SLAVE_LSB_10:
            HAL_REG_WRITE_BIT(HAL_SPI[spi]->CFG, mask, SPI0_CFG_CPHA_BIT | SPI0_CFG_ENDIAN_BIT);
            break;
        case HAL_SPI_MODE_SLAVE_LSB_11:
            HAL_REG_WRITE_BIT(HAL_SPI[spi]->CFG, mask, SPI0_CFG_CPHA_BIT | SPI0_CFG_CPOL_BIT | SPI0_CFG_ENDIAN_BIT);
            break;
        case HAL_SPI_MODE_SLAVE_MSB_00:
            HAL_REG_WRITE_BIT(HAL_SPI[spi]->CFG, mask, 0);
            break;
        case HAL_SPI_MODE_SLAVE_MSB_01:
            HAL_REG_WRITE_BIT(HAL_SPI[spi]->CFG, mask, SPI0_CFG_CPOL_BIT);
            break;
        case HAL_SPI_MODE_SLAVE_MSB_10:
            HAL_REG_WRITE_BIT(HAL_SPI[spi]->CFG, mask, SPI0_CFG_CPHA_BIT);
            break;
        case HAL_SPI_MODE_SLAVE_MSB_11:
            HAL_REG_WRITE_BIT(HAL_SPI[spi]->CFG, mask, SPI0_CFG_CPHA_BIT | SPI0_CFG_CPOL_BIT);
            break;
        default:
            break;
    }
}

/**
 * @brief 初始化CS引脚
 * @param spi SPI模块号
 * @param pin GPIO引脚
 * @see 需要先初始化SPI
 */
void HAL_SPI_SetGpioCs(HAL_SPI_x spi, HAL_GPIO_Px pin)
{
    if (HAL_REG_READ_BIT(HAL_SPI[spi]->CFG, SPI0_CFG_MS_BIT) == 0)
    {
        // 从模式
        HAL_GPIO_SetAf(pin, HAL_GPIO_AF_SPI);
        HAL_GPIO_SetMode(pin, HAL_GPIO_MODE_IN);
    }
    else
    {
        // 主模式
        HAL_GPIO_SetAf(pin, HAL_GPIO_AF_SPI);
        HAL_GPIO_SetMode(pin, HAL_GPIO_MODE_OUT);
    }
}

/**
 * @brief 初始化Mosi引脚
 * @param spi SPI模块号
 * @param pin GPIO引脚
 * @see 需要先初始化SPI
 */
void HAL_SPI_SetGpioMosi(HAL_SPI_x spi, HAL_GPIO_Px pin)
{
    if (HAL_REG_READ_BIT(HAL_SPI[spi]->CFG, SPI0_CFG_MS_BIT) == 0)
    {
        // 从模式
        HAL_GPIO_SetAf(pin, HAL_GPIO_AF_SPI);
        HAL_GPIO_SetMode(pin, HAL_GPIO_MODE_IN);
    }
    else
    {
        // 主模式
        HAL_GPIO_SetAf(pin, HAL_GPIO_AF_SPI);
        HAL_GPIO_SetMode(pin, HAL_GPIO_MODE_OUT);
    }
}

/**
 * @brief 初始化Miso引脚
 * @param spi SPI模块号
 * @param pin GPIO引脚
 * @see 需要先初始化SPI
 */
void HAL_SPI_SetGpioMiso(HAL_SPI_x spi, HAL_GPIO_Px pin)
{
    if (HAL_REG_READ_BIT(HAL_SPI[spi]->CFG, SPI0_CFG_MS_BIT) == 0)
    {
        // 从模式
        HAL_GPIO_SetAf(pin, HAL_GPIO_AF_SPI);
        HAL_GPIO_SetMode(pin, HAL_GPIO_MODE_OUT);
    }
    else
    {
        // 主模式
        HAL_GPIO_SetAf(pin, HAL_GPIO_AF_SPI);
        HAL_GPIO_SetMode(pin, HAL_GPIO_MODE_IN);
    }
}

/**
 * @brief 初始化Clk引脚
 * @param spi SPI模块号
 * @param pin GPIO引脚
 * @see 需要先初始化SPI
 */
void HAL_SPI_SetGpioClk(HAL_SPI_x spi, HAL_GPIO_Px pin)
{
    if (HAL_REG_READ_BIT(HAL_SPI[spi]->CFG, SPI0_CFG_MS_BIT) == 0)
    {
        // 从模式
        HAL_GPIO_SetAf(pin, HAL_GPIO_AF_SPI);
        HAL_GPIO_SetMode(pin, HAL_GPIO_MODE_IN);
    }
    else
    {
        // 主模式
        HAL_GPIO_SetAf(pin, HAL_GPIO_AF_SPI);
        HAL_GPIO_SetMode(pin, HAL_GPIO_MODE_OUT);
    }
}

/**
 * @brief 初始化SPI的输入引脚
 * @param spi SPI模块号
 * @param pin GPIO引脚
 */
void HAL_SPI_SetGpioDi(HAL_SPI_x spi, HAL_GPIO_Px pin)
{
    (void)spi;
    HAL_GPIO_SetAf(pin, HAL_GPIO_AF_SPI);
    HAL_GPIO_SetMode(pin, HAL_GPIO_MODE_IN);
}

/**
 * @brief 初始化SPI的输出引脚
 * @param spi SPI模块号
 * @param pin GPIO引脚
 */
void HAL_SPI_SetGpioDo(HAL_SPI_x spi, HAL_GPIO_Px pin)
{
    (void)spi;
    HAL_GPIO_SetAf(pin, HAL_GPIO_AF_SPI);
    HAL_GPIO_SetMode(pin, HAL_GPIO_MODE_OUT);
}

/**
 * @brief 发送数据
 * @param spi SPI模块号
 * @param data 要发送的数据
 * @param len 数据长度
 * @return 发送状态
 */
uint8_t HAL_SPI_TxData(HAL_SPI_x spi, uint8_t *data, uint32_t len)
{
    uint32_t i = 0;
    HAL_REG_WRITE(HAL_SPI[spi]->SIZE, 8);
    HAL_REG_SET(HAL_SPI[spi]->BAUD, SPI0_BAUD_TRANS_MODE_BIT);
    HAL_REG_WRITE_BIT_MASK_POS(HAL_SPI[spi]->CFG, SPI0_CFG_DUPLEX, 2);
    for (i = 0; i < len; i++)
    {
        HAL_REG_WRITE_BIT(HAL_SPI[spi]->IE, 0x07, SPI0_IE_CMPLT_IF_BIT);
        HAL_REG_WRITE(HAL_SPI[spi]->TXDATA, data[i]);
        while (HAL_REG_READ(HAL_SPI[spi]->IE & SPI0_IE_CMPLT_IF_BIT) == 0)
        {
        }
    }
    return 0;
}

/**
 * @brief 接收数据
 * @param spi SPI模块号
 * @param data 接收缓冲区
 * @param len 数据长度
 * @return 接收状态
 */
uint8_t HAL_SPI_RxData(HAL_SPI_x spi, uint8_t *data, uint32_t len)
{
    uint32_t i = 0;
    HAL_REG_WRITE(HAL_SPI[spi]->SIZE, 8);
    HAL_REG_SET(HAL_SPI[spi]->BAUD, SPI0_BAUD_TRANS_MODE_BIT);
    HAL_REG_WRITE_BIT_MASK_POS(HAL_SPI[spi]->CFG, SPI0_CFG_DUPLEX, 3);
    for (i = 0; i < len; i++)
    {
        HAL_REG_WRITE_BIT(HAL_SPI[spi]->IE, 0x07, SPI0_IE_CMPLT_IF_BIT);
        HAL_REG_WRITE(HAL_SPI[spi]->TXDATA, 0); // 发送一个空字节,以触发接收
        while (HAL_REG_READ(HAL_SPI[spi]->IE & SPI0_IE_CMPLT_IF_BIT) == 0)
        {
        }
        data[i] = HAL_REG_READ(HAL_SPI[spi]->RXDATA);
    }
    // 实现接收数据的代码
    return 0; // 返回接收状态
}

/**
 * @brief 发送和接收数据
 * @param spi SPI模块号
 * @param rxdata 接收缓冲区
 * @param txdata 要发送的数据
 * @param len 数据长度
 * @return 发送和接收状态
 */
uint8_t HAL_SPI_RxTxData(HAL_SPI_x spi, uint8_t *rxdata, uint8_t *txdata, uint32_t len)
{
    uint32_t i = 0;
    HAL_REG_WRITE(HAL_SPI[spi]->SIZE, 8);
    HAL_REG_SET(HAL_SPI[spi]->BAUD, SPI0_BAUD_TRANS_MODE_BIT);
    HAL_REG_WRITE_BIT_MASK_POS(HAL_SPI[spi]->CFG, SPI0_CFG_DUPLEX, 0);
    for (i = 0; i < len; i++)
    {
        HAL_REG_WRITE_BIT(HAL_SPI[spi]->IE, 0x07, SPI0_IE_CMPLT_IF_BIT);
        HAL_REG_WRITE(HAL_SPI[spi]->TXDATA, txdata[i]);
        while (HAL_REG_READ(HAL_SPI[spi]->IE & SPI0_IE_CMPLT_IF_BIT) == 0)
        {
        }
        rxdata[i] = HAL_REG_READ(HAL_SPI[spi]->RXDATA);
    }
    return 0; // 返回发送和接收状态
}

/**
 * @brief 发送数据
 * @param spi SPI模块号
 * @param data 要发送的数据
 * @param len 数据长度，单位2字节
 * @return 发送状态
 */
uint8_t HAL_SPI_TxDataWidth16(HAL_SPI_x spi, uint16_t *data, uint32_t len)
{
    uint32_t i = 0;
    HAL_REG_WRITE(HAL_SPI[spi]->SIZE, 16);
    HAL_REG_SET(HAL_SPI[spi]->BAUD, SPI0_BAUD_TRANS_MODE_BIT);
    HAL_REG_WRITE_BIT_MASK_POS(HAL_SPI[spi]->CFG, SPI0_CFG_DUPLEX, 2);
    for (i = 0; i < len; i++)
    {
        HAL_REG_WRITE_BIT(HAL_SPI[spi]->IE, 0x07, SPI0_IE_CMPLT_IF_BIT);
        HAL_REG_WRITE(HAL_SPI[spi]->TXDATA, data[i]);
        while (HAL_REG_READ(HAL_SPI[spi]->IE & SPI0_IE_CMPLT_IF_BIT) == 0)
        {
        }
    }
    return 0;
}

/**
 * @brief 接收数据
 * @param spi SPI模块号
 * @param data 接收缓冲区
 * @param len 数据长度，单位2字节
 * @return 接收状态
 */
uint8_t HAL_SPI_RxDataWidth16(HAL_SPI_x spi, uint16_t *data, uint32_t len)
{
    uint32_t i = 0;
    HAL_REG_WRITE(HAL_SPI[spi]->SIZE, 16);
    HAL_REG_SET(HAL_SPI[spi]->BAUD, SPI0_BAUD_TRANS_MODE_BIT);
    HAL_REG_WRITE_BIT_MASK_POS(HAL_SPI[spi]->CFG, SPI0_CFG_DUPLEX, 3);
    for (i = 0; i < len; i++)
    {
        HAL_REG_WRITE_BIT(HAL_SPI[spi]->IE, 0x07, SPI0_IE_CMPLT_IF_BIT);
        HAL_REG_WRITE(HAL_SPI[spi]->TXDATA, 0); // 发送一个空字节,以触发接收
        while (HAL_REG_READ(HAL_SPI[spi]->IE & SPI0_IE_CMPLT_IF_BIT) == 0)
        {
        }
        data[i] = HAL_REG_READ(HAL_SPI[spi]->RXDATA);
    }
    return 0; // 返回接收状态
}

/**
 * @brief 发送和接收数据
 * @param spi SPI模块号
 * @param rxdata 接收缓冲区
 * @param txdata 要发送的数据
 * @param len 数据长度，单位2字节
 * @return 发送和接收状态
 */
uint8_t HAL_SPI_RxTxDataWidth16(HAL_SPI_x spi, uint16_t *rxdata, uint16_t *txdata, uint32_t len)
{
    uint32_t i = 0;
    HAL_REG_WRITE(HAL_SPI[spi]->SIZE, 16);
    HAL_REG_SET(HAL_SPI[spi]->BAUD, SPI0_BAUD_TRANS_MODE_BIT);
    HAL_REG_WRITE_BIT_MASK_POS(HAL_SPI[spi]->CFG, SPI0_CFG_DUPLEX, 0);
    for (i = 0; i < len; i++)
    {
        HAL_REG_WRITE_BIT(HAL_SPI[spi]->IE, 0x07, SPI0_IE_CMPLT_IF_BIT);
        HAL_REG_WRITE(HAL_SPI[spi]->TXDATA, txdata[i]);
        while (HAL_REG_READ(HAL_SPI[spi]->IE & SPI0_IE_CMPLT_IF_BIT) == 0)
        {
        }
        rxdata[i] = HAL_REG_READ(HAL_SPI[spi]->RXDATA);
    }
    return 0; // 返回发送和接收状态
}
