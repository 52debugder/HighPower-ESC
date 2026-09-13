#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lksmcu_i2c.h"
#include "../hal_lks32mc07x.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"
static HAL_GPIO_Px hal_i2cio[1][2];
static uint32_t hal_baud[1];
/**
 * @brief 复位I2C模块
 * @param i2c_x I2C模块编号
 */
void HAL_I2C_Reset(HAL_I2C_x i2c_x)
{
    (void)i2c_x;
    HAL_REG_SYS_UNLOCK();
    HAL_REG_SET(SYS_SFT_RST, SYS_SFT_RST_I2C_0SFT_RST_BIT);
    HAL_REG_RESET(SYS_SFT_RST, SYS_SFT_RST_I2C_0SFT_RST_BIT);
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 打开I2C模块
 * @param i2c_x I2C模块编号
 */
void HAL_I2C_Enable(HAL_I2C_x i2c_x)
{
    (void)i2c_x;
    HAL_REG_SYS_UNLOCK();
    HAL_REG_SET(SYS_CLK_FEN, SYS_CLK_FEN_I2C0_CLK_EN_BIT);
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 关闭I2C模块
 * @param i2c_x I2C模块编号
 */
void HAL_I2C_Disable(HAL_I2C_x i2c_x)
{
    (void)i2c_x;
    HAL_REG_SYS_UNLOCK();
    HAL_REG_RESET(SYS_CLK_FEN, SYS_CLK_FEN_I2C0_CLK_EN_BIT);
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 设置I2C模块波特率
 * @param i2c_x I2C模块编号
 * @param baud 波特率
 */
void HAL_I2C_SetBaud(HAL_I2C_x i2c_x, uint32_t baud)
{
    uint32_t BaudRate;
    (void)i2c_x;
    hal_baud[i2c_x] = baud;
    BaudRate        = ((uint32_t)HAL_CLK_GetMcuFreq() + ((baud * 17) >> 1)) / (baud * 17) - 1;
    HAL_REG_SYS_UNLOCK();
    HAL_REG_WRITE(SYS_CLK_DIV0, BaudRate);
    HAL_REG_SYS_LOCK();
}

// 设置I2C全局工作时钟分频 (I2C0/1共享)
void HAL_I2C_SetClockDiv(HAL_I2C_x i2c_x, uint32_t div)
{
    (void)i2c_x;
    if (div < 1) div = 1;
    HAL_REG_SYS_UNLOCK();
    HAL_REG_WRITE(SYS_CLK_DIV0, div - 1);
    HAL_REG_SYS_LOCK();
}

// 获取I2C工作时钟分频实际除数
uint32_t HAL_I2C_GetClockDiv(HAL_I2C_x i2c_x)
{
    (void)i2c_x;
    return HAL_REG_READ_BIT_MASK_POS(SYS_CLK_DIV0, SYS_CLK_DIV0_DIV0) + 1;
}

// 获取I2C工作时钟频率
uint32_t HAL_I2C_GetClockFreq(HAL_I2C_x i2c_x)
{
    return HAL_CLK_GetMcuFreq() / HAL_I2C_GetClockDiv(i2c_x);
}

// 获取当前SCL波特率
uint32_t HAL_I2C_GetBaud(HAL_I2C_x i2c_x)
{
    return HAL_I2C_GetClockFreq(i2c_x) / 17;
}

/**
 * @brief 发送数据到I2C设备
 * @param i2c_x I2C模块编号
 * @param addr 设备地址
 * @param data 数据缓冲区
 * @param len 数据长度
 * @return 0:成功 非0:失败
 */
uint8_t HAL_I2C_TxData(HAL_I2C_x i2c_x, uint8_t addr, uint8_t *data, uint32_t len)
{
    uint32_t i = 0;
    HAL_REG_SET(HAL_I2C[i2c_x]->CFG, I2C0_CFG_MST_MODE_BIT);
    if (HAL_REG_READ_BIT(HAL_I2C[i2c_x]->MSCR, I2C0_MSCR_BUSY_BIT))
    {
        return 1; // 发送数据时,i2c总线忙碌
    }
    if (len == 0)
    {
        return 1;
    }
    HAL_REG_WRITE(HAL_I2C[i2c_x]->SCR, 0);
    HAL_REG_WRITE(HAL_I2C[i2c_x]->MSCR, 1); // 触发I2C发送数据
    while (HAL_REG_READ_BIT(HAL_I2C[i2c_x]->MSCR, I2C0_MSCR_MST_CHECK_BIT) == 0)
    {
    }
    HAL_REG_WRITE(HAL_I2C[i2c_x]->DATA, addr);
    while (HAL_REG_READ(HAL_I2C[i2c_x]->SCR) == 0) // 等待地址发送完成
    {
    }

    if (HAL_REG_READ_BIT(HAL_I2C[i2c_x]->SCR, I2C0_SCR_RX_ACK_BIT)) // 收到nack
    {
        HAL_REG_WRITE(HAL_I2C[i2c_x]->SCR, 0);
        while (HAL_REG_READ_BIT(HAL_I2C[i2c_x]->MSCR, I2C0_MSCR_BUSY_BIT)) // 等待stop信号发送完成
        {
        }
        return 1;
    }
    for (i = 0; i < len; i++)
    {
        HAL_REG_WRITE(HAL_I2C[i2c_x]->DATA, data[i]);
        HAL_REG_WRITE(HAL_I2C[i2c_x]->SCR, I2C0_SCR_DATA_DIR_BIT);            // 触发发送
        while (HAL_REG_READ_BIT(HAL_I2C[i2c_x]->SCR, I2C0_SCR_Done_BIT) == 0) // 等待数据发送完成
        {
        }
        if (HAL_REG_READ_BIT(HAL_I2C[i2c_x]->SCR, I2C0_SCR_RX_ACK_BIT)) // 收到nack
        {
            HAL_REG_WRITE(HAL_I2C[i2c_x]->SCR, 0);
            while (HAL_REG_READ_BIT(HAL_I2C[i2c_x]->MSCR, I2C0_MSCR_BUSY_BIT)) // 等待stop信号发送完成
            {
            }
            return 1;
        }
    }
    HAL_REG_WRITE(HAL_I2C[i2c_x]->SCR, 0);
    while (HAL_REG_READ_BIT(HAL_I2C[i2c_x]->MSCR, I2C0_MSCR_BUSY_BIT)) // 等待stop信号发送完成
    {
    }
    return 0;
}

/**
 * @brief 从I2C设备接收数据
 * @param i2c_x I2C模块编号
 * @param addr 设备地址
 * @param data 数据缓冲区
 * @param len 数据长度
 * @return 0:成功 非0:失败
 */
uint8_t HAL_I2C_RxData(HAL_I2C_x i2c_x, uint8_t addr, uint8_t *data, uint32_t len)
{
    uint32_t i;
    HAL_REG_SET(HAL_I2C[i2c_x]->CFG, I2C0_CFG_MST_MODE_BIT);
    if (HAL_REG_READ_BIT(HAL_I2C[i2c_x]->MSCR, I2C0_MSCR_BUSY_BIT))
    {
        return 1; // 发送数据时,i2c总线忙碌
    }
    if (len == 0)
    {
        return 1;
    }
    HAL_REG_WRITE(HAL_I2C[i2c_x]->SCR, 0);
    HAL_REG_WRITE(HAL_I2C[i2c_x]->MSCR, 1);                                      // 触发I2C发送数据
    while (HAL_REG_READ_BIT(HAL_I2C[i2c_x]->MSCR, I2C0_MSCR_MST_CHECK_BIT) == 0) // 等待start信号发送完成
    {
    }
    HAL_REG_WRITE(HAL_I2C[i2c_x]->DATA, addr | 1); // 发送地址数据
    while (HAL_REG_READ(HAL_I2C[i2c_x]->SCR) == 0) // 等待地址发送完成
    {
    }
    if (HAL_REG_READ_BIT(HAL_I2C[i2c_x]->SCR, I2C0_SCR_RX_ACK_BIT)) // 收到nack
    {
        HAL_REG_WRITE(HAL_I2C[i2c_x]->SCR, 0);
        while (HAL_REG_READ_BIT(HAL_I2C[i2c_x]->MSCR, I2C0_MSCR_BUSY_BIT)) // 等待stop信号发送完成
        {
        }
        return 1;
    }
    for (i = 0; i < len; i++)
    {
        HAL_REG_WRITE(HAL_I2C[i2c_x]->SCR, I2C0_SCR_BYTE_CMPLT_BIT);          // 向从机发送ack响应
        while (HAL_REG_READ_BIT(HAL_I2C[i2c_x]->SCR, I2C0_SCR_Done_BIT) == 0) // 等待数据发送完成
        {
        }
        data[i] = HAL_REG_READ(HAL_I2C[i2c_x]->DATA);
    }
    HAL_REG_WRITE(HAL_I2C[i2c_x]->SCR, 0);
    while (HAL_REG_READ_BIT(HAL_I2C[i2c_x]->MSCR, I2C0_MSCR_BUSY_BIT)) // 等待stop信号发送完成
    {
    }
    return 0;
}

/**
 * @brief 设置I2C模块的GPIO
 * @param i2c_x I2C模块编号
 * @param i2cgpio GPIO编号
 */
void HAL_I2C_SetGpioScl(HAL_I2C_x i2c_x, HAL_GPIO_Px i2cgpio)
{
    (void)i2c_x;
    HAL_GPIO_SetAf(i2cgpio, HAL_GPIO_AF_I2C);
    HAL_GPIO_SetMode(i2cgpio, HAL_GPIO_MODE_IN);
    hal_i2cio[i2c_x][0] = i2cgpio; // 保存I2C使用的IO口
}

/**
 * @brief 设置I2C模块的GPIO
 * @param i2c_x I2C模块编号
 * @param i2cgpio GPIO编号
 */
void HAL_I2C_SetGpioSda(HAL_I2C_x i2c_x, HAL_GPIO_Px i2cgpio)
{
    (void)i2c_x;
    HAL_GPIO_SetAf(i2cgpio, HAL_GPIO_AF_I2C);
    HAL_GPIO_SetMode(i2cgpio, HAL_GPIO_MODE_IN);
    hal_i2cio[i2c_x][1] = i2cgpio; // 保存I2C使用的IO口
}

/**
 * @brief 复位I2C总线
 * @param i2c_x I2C模块编号
 */
void HAL_I2C_BusReset(HAL_I2C_x i2c_x)
{
    uint32_t div;
    uint32_t i;
    uint32_t j;
    // 还原成普通IO口
    HAL_GPIO_SetAf(hal_i2cio[i2c_x][0], HAL_GPIO_AF_GPIO);
    HAL_GPIO_SetAf(hal_i2cio[i2c_x][1], HAL_GPIO_AF_GPIO);
    HAL_GPIO_SetMode(hal_i2cio[i2c_x][0], HAL_GPIO_MODE_INUPOUT_1);
    HAL_GPIO_SetMode(hal_i2cio[i2c_x][1], HAL_GPIO_MODE_INUP);
    // 翻转10次SCL
    div = (HAL_CLK_GetMcuFreq() / hal_baud[i2c_x]) >> 4;
    for (i = 0; i < 20; i++)
    {
        HAL_GPIO_Invert(hal_i2cio[i2c_x][0]);
        for (j = div; j--;) // 一个大于波特率的软件延迟
        {
            __NOP();
        }
    }
    // 复用回I2C
    HAL_GPIO_SetAf(hal_i2cio[i2c_x][0], HAL_GPIO_AF_I2C);
    HAL_GPIO_SetAf(hal_i2cio[i2c_x][1], HAL_GPIO_AF_I2C);
    HAL_GPIO_SetMode(hal_i2cio[i2c_x][0], HAL_GPIO_MODE_IN);
    HAL_GPIO_SetMode(hal_i2cio[i2c_x][1], HAL_GPIO_MODE_IN);
}
