#include "../include/hal_lksmcu_gpio.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"
/**
 * @brief 模块复位,执行后恢复所有的GPIO为悬空状态(SWD、JTAG和RST口为默认状态)
 */
void HAL_GPIO_Reset()
{
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    HAL_REG_SET(SYS_SFT_RST, SYS_SFT_RST_GPIO_SFT_RST_BIT);
    HAL_REG_RESET(SYS_SFT_RST, SYS_SFT_RST_GPIO_SFT_RST_BIT);
    HAL_REG_RESET(SYS_IO_CFG, SYS_IO_CFG_SWDMUX_BIT);
    HAL_REG_RESET(SYS_IO_CFG, SYS_IO_CFG_RST_IO_BIT);
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 启用GPIO模块,使能GPIO时钟和必要的资源
 */
void HAL_GPIO_Enable()
{
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    // GPIO_CLK_EN[11] GPIO 模块时钟控制信号,默认关闭 GPIO 模块时钟
    HAL_REG_SET(SYS_CLK_FEN, SYS_CLK_FEN_GPIO_CLK_EN_BIT);
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 禁用GPIO模块,关闭GPIO时钟和释放资源
 */
void HAL_GPIO_Disable()
{
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    // GPIO_CLK_EN[11] GPIO 模块时钟控制信号,默认关闭 GPIO 模块时钟
    HAL_REG_RESET(SYS_CLK_FEN, SYS_CLK_FEN_GPIO_CLK_EN_BIT);
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 设置指定GPIO的工作模式
 * @param px: 指定的GPIO端口
 * @param mode: 要设置的工作模式
 */
void HAL_GPIO_SetMode(HAL_GPIO_Px px, HAL_GPIO_MODE_x mode)
{
    uint8_t p     = (px >> 8) & 0xff;
    uint8_t x     = (px >> 0) & 0xff;
    uint16_t bitx = 1 << x;
    // 默认电平设置
    if (HAL_REG_READ_BIT(mode, HAL_GPIO_MODE_DEFAULT_0))
    {
        HAL_REG_WRITE(HAL_GPIO[p]->BRR, bitx);
    }
    else if (HAL_REG_READ_BIT(mode, HAL_GPIO_MODE_DEFAULT_1))
    {
        HAL_REG_WRITE(HAL_GPIO[p]->BSRR, bitx);
    }
    else
    {
    }
    // 开漏设置
    if (HAL_REG_READ_BIT(mode, HAL_GPIO_MODE_PODE_EN))
    {
        HAL_REG_SET(HAL_GPIO[p]->PODE, bitx);
    }
    else
    {
        HAL_REG_RESET(HAL_GPIO[p]->PODE, bitx);
    }
    // 上拉设置
    if (HAL_REG_READ_BIT(mode, HAL_GPIO_MODE_UP_EN))
    {
        HAL_REG_SET(HAL_GPIO[p]->PUE, bitx);
    }
    else
    {
        HAL_REG_RESET(HAL_GPIO[p]->PUE, bitx);
    }
    // 输出设置
    if (HAL_REG_READ_BIT(mode, HAL_GPIO_MODE_OUT_EN))
    {
        HAL_REG_SET(HAL_GPIO[p]->POE, bitx);
    }
    else
    {
        HAL_REG_RESET(HAL_GPIO[p]->POE, bitx);
    }
    // 输入使能
    if (HAL_REG_READ_BIT(mode, HAL_GPIO_MODE_IN_EN))
    {
        HAL_REG_SET(HAL_GPIO[p]->PIE, bitx);
    }
    else
    {
        HAL_REG_RESET(HAL_GPIO[p]->PIE, bitx);
    }
}

/**
 * @brief 将指定的GPIO端口输出高电平(1)
 * @param px: 指定的GPIO端口
 * @note 在INOUT模式下设为悬空,INUPOUT模式下设为上拉
 */
void HAL_GPIO_SetHigh(HAL_GPIO_Px px)
{
    uint8_t p     = (px >> 8) & 0xff;
    uint8_t x     = (px >> 0) & 0xff;
    uint32_t bitx = 1 << x;
    HAL_REG_WRITE(HAL_GPIO[p]->BSRR, bitx);
}

/**
 * @brief 将指定的GPIO端口输出低电平(0)
 * @param px: 指定的GPIO端口
 */
void HAL_GPIO_SetLow(HAL_GPIO_Px px)
{
    uint8_t p     = (px >> 8) & 0xff;
    uint8_t x     = (px >> 0) & 0xff;
    uint32_t bitx = 1 << x;
    HAL_REG_WRITE(HAL_GPIO[p]->BRR, bitx);
}

/**
 * @brief 向指定的GPIO端口写入0或1
 * @param px: 指定的GPIO端口
 * @param value: 要写入的值(0或1)
 */
void HAL_GPIO_Write(HAL_GPIO_Px px, uint8_t value)
{
    uint8_t p     = (px >> 8) & 0xff;
    uint8_t x     = (px >> 0) & 0xff;
    uint32_t bitx = 1 << x;
    uint32_t valx = value << x;
    HAL_REG_WRITE_BIT(HAL_GPIO[p]->PDO, bitx, valx);
}

/**
 * @brief 翻转指定的GPIO端口的输出状态
 * @param px: 指定的GPIO端口
 */
void HAL_GPIO_Invert(HAL_GPIO_Px px)
{
    uint8_t p     = (px >> 8) & 0xff;
    uint8_t x     = (px >> 0) & 0xff;
    uint32_t bitx = 1 << x;
    if (HAL_REG_READ_BIT(HAL_GPIO[p]->PDO, bitx))
    {
        HAL_REG_WRITE(HAL_GPIO[p]->BRR, bitx);
    }
    else
    {
        HAL_REG_WRITE(HAL_GPIO[p]->BSRR, bitx);
    }
}

/**
 * @brief 获取当前指定GPIO端口的输出值
 * @param px: 指定的GPIO端口
 * @return 当前GPIO端口的输出值(0或1)
 */
uint8_t HAL_GPIO_GetOutData(HAL_GPIO_Px px)
{
    uint8_t p     = (px >> 8) & 0xff;
    uint8_t x     = (px >> 0) & 0xff;
    uint32_t bitx = 1 << x;
    uint32_t valx = HAL_REG_READ_BIT(HAL_GPIO[p]->PDO, bitx);
    uint8_t result;
    if (valx)
    {
        result = 1;
    }
    else
    {
        result = 0;
    }
    return result;
}

/**
 * @brief 获取当前指定GPIO端口的输入值
 * @param px: 指定的GPIO端口
 * @return 当前GPIO端口的输入值(0或1)
 */
uint8_t HAL_GPIO_GetInData(HAL_GPIO_Px px)
{
    uint8_t p     = (px >> 8) & 0xff;
    uint8_t x     = (px >> 0) & 0xff;
    uint32_t bitx = 1 << x;
    uint32_t valx = HAL_REG_READ_BIT(HAL_GPIO[p]->PDI, bitx);
    uint8_t result;
    if (valx)
    {
        result = 1;
    }
    else
    {
        result = 0;
    }
    return result;
}

/**
 * @brief 配置GPIO的特殊功能,如UART、I2C、SPI等
 * @param px: 指定的GPIO端口
 * @param af: 要配置的特殊功能代码
 */
void HAL_GPIO_SetAf(HAL_GPIO_Px px, HAL_GPIO_AFx af)
{
    uint8_t p = (px >> 8) & 0xff;
    uint8_t x = (px >> 0) & 0xff;
    af &= 0xf; // 限制af的取值范围为0-15
    switch (x)
    {
        case 0:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_GPIO[p]->F3210, GPIOx_F3210_F0, af);
            break;
        case 1:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_GPIO[p]->F3210, GPIOx_F3210_F1, af);
            break;
        case 2:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_GPIO[p]->F3210, GPIOx_F3210_F2, af);
            break;
        case 3:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_GPIO[p]->F3210, GPIOx_F3210_F3, af);
            break;
        case 4:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_GPIO[p]->F7654, GPIOx_F7654_F4, af);
            break;
        case 5:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_GPIO[p]->F7654, GPIOx_F7654_F5, af);
            break;
        case 6:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_GPIO[p]->F7654, GPIOx_F7654_F6, af);
            break;
        case 7:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_GPIO[p]->F7654, GPIOx_F7654_F7, af);
            break;
        case 8:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_GPIO[p]->FBA98, GPIOx_FBA98_F8, af);
            break;
        case 9:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_GPIO[p]->FBA98, GPIOx_FBA98_F9, af);
            break;
        case 10:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_GPIO[p]->FBA98, GPIOx_FBA98_F10, af);
            break;
        case 11:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_GPIO[p]->FBA98, GPIOx_FBA98_F11, af);
            break;
        case 12:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_GPIO[p]->FFEDC, GPIOx_FFEDC_F12, af);
            break;
        case 13:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_GPIO[p]->FFEDC, GPIOx_FFEDC_F13, af);
            break;
        case 14:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_GPIO[p]->FFEDC, GPIOx_FFEDC_F14, af);
            break;
        case 15:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_GPIO[p]->FFEDC, GPIOx_FFEDC_F15, af);
            break;
    }
}

/**
 * @brief 将SWD接口配置为普通GPIO口
 */
void HAL_GPIO_SwdReuseGpioEnable(void)
{
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    // SYS_IO_CFG[6] SWD 复用控制信号,默认配置为 SWD 1:P1.8 复用为 SWCLK,P1.9 复用为 SWDIO
    HAL_REG_RESET(SYS_IO_CFG, SYS_IO_CFG_SWDMUX_BIT);
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 将SWD接口恢复为SWD功能
 */
void HAL_GPIO_SwdReuseGpioDisable(void)
{
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    // SYS_IO_CFG[6] SWD 复用控制信号,默认配置为 SWD 1:P1.8 复用为 SWCLK,P1.9 复用为 SWDIO
    HAL_REG_SET(SYS_IO_CFG, SYS_IO_CFG_SWDMUX_BIT);
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 将RST接口配置为普通GPIO口
 */
void HAL_GPIO_RstReuseGpioEnable(void)
{
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    // SYS_IO_CFG[5] RSTn/P0.2 复用控制信号,默认配置为 RSTn 0:RSTn
    HAL_REG_SET(SYS_IO_CFG, SYS_IO_CFG_RST_IO_BIT);
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 将RST接口恢复为RST功能
 */
void HAL_GPIO_RstReuseGpioDisable(void)
{
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    // SYS_IO_CFG[5] RSTn/P0.2 复用控制信号,默认配置为 RSTn 0:RSTn
    HAL_REG_RESET(SYS_IO_CFG, SYS_IO_CFG_RST_IO_BIT);
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}
