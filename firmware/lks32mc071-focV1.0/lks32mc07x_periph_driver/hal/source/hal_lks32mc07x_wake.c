#include "../include/hal_lksmcu_iwdg.h"
#include "../include/hal_lksmcu_wake.h"
#include "../hal_lks32mc07x.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"

/**
 * @brief 进入深度休眠,并且使用IO唤醒
 * @param wake_up_io 指定唤醒IO引脚及其电平
 */
void HAL_WAKE_DeepSleepIoWake(HAL_WAKE_UP_IO_x wake_up_io)
{
    uint32_t t_cnt;
    uint32_t reg5;         // 模拟配置
    uint32_t clkcfg;       // 时钟配置
    uint32_t clk_fen;      // 模块使能配置
    uint32_t saved_enable; // 中断配置

    __disable_irq();                            // 关闭全局中断，确保执行休眠期间，不会进入其他任何中断
    reg5         = HAL_REG_READ(SYS_AFE_REG5);  // 保存模拟使能配置
    clkcfg       = HAL_REG_READ(SYS_CLK_CFG);   // 保存时钟配置
    clk_fen      = HAL_REG_READ(SYS_CLK_FEN);   // 保存模块时钟使能配置
    saved_enable = HAL_REG_READ(NVIC->ISER[0]); // 保存当前中断配置

    if (wake_up_io & 0x0100)
    {
        HAL_REG_SET(AON_IO_WAKE_POL, AON_IO_WAKE_POL_WK_POL_BIT);
    }
    else
    {
        HAL_REG_RESET(AON_IO_WAKE_POL, AON_IO_WAKE_POL_WK_POL_BIT);
    }
    HAL_REG_WRITE_BIT(AON_IO_WAKE_EN, AON_IO_WAKE_EN_CLUOUT3_EN_BIT | AON_IO_WAKE_EN_CLUOUT2_EN_BIT | AON_IO_WAKE_EN_CLUOUT1_EN_BIT | AON_IO_WAKE_EN_CLUOUT0_EN_BIT | AON_IO_WAKE_EN_P2_15_EN_BIT | AON_IO_WAKE_EN_P2_7_EN_BIT | AON_IO_WAKE_EN_P2_4_EN_BIT | AON_IO_WAKE_EN_P0_14_EN_BIT | AON_IO_WAKE_EN_P0_11_EN_BIT | AON_IO_WAKE_EN_P0_6_EN_BIT | AON_IO_WAKE_EN_P0_2_EN_BIT | AON_IO_WAKE_EN_P0_0_EN_BIT, 1 << (wake_up_io & 0xf));

    HAL_REG_WRITE(SYS_WR_PROTECT, 0x7a83);    // 开启寄存器写使能
    HAL_REG_WRITE(NVIC->ICER[0], 0xFFFFFFFF); // 关闭所有中断
    HAL_REG_WRITE(IWDG_PSW, 0xA6B4);          // 打开看门狗使能
    HAL_REG_WRITE(IWDG_CLR, 0x798D);          // 喂狗

    HAL_REG_WRITE(SYS_CLK_CFG, 0); // 切换到HRC时钟
    for (t_cnt = 0; t_cnt < 4000; t_cnt++)
    {
        __NOP();
    }
    HAL_REG_WRITE(SYS_CLK_FEN, 0);                                                // 关闭数字模块时钟
    HAL_REG_WRITE(SYS_AFE_REG5, SYS_AFE_REG5_RCHPD_BIT | SYS_AFE_REG5_BGPPD_BIT); // 准备关闭 PLL,BGP,以及其它模拟电路使能
    HAL_REG_WRITE(SYS_WR_PROTECT, 0x0);                                           // 关闭系统寄存器写使能

    HAL_IRQ_ModuleEnable(HAL_IRQ_MODULE_WAKE0, 0);

    __enable_irq();                    // 打开全局中断
    HAL_REG_SET(SCB->SCR, (1UL << 2)); // 使能深度休眠
    __WFI();                           // 休眠 wakeak

    __disable_irq(); // 唤醒后关闭全局中断
    HAL_IRQ_ModuleDisable(HAL_IRQ_MODULE_WAKE0);
    HAL_REG_WRITE(SYS_WR_PROTECT, 0x7a83); // 开启寄存器写使能
    HAL_REG_WRITE(SYS_AFE_REG5, reg5);     // 开启 PLL,BGP
    for (t_cnt = 0; t_cnt < 400; t_cnt++)
    {
        __NOP();
    }
    HAL_REG_WRITE(SYS_CLK_CFG, clkcfg);         // 恢复时钟配置
    HAL_REG_WRITE(NVIC->ISER[0], saved_enable); // 恢复中断使能
    HAL_REG_WRITE(SYS_CLK_FEN, clk_fen);        // 打开其他模块
    HAL_REG_WRITE(SYS_WR_PROTECT, 0x0);         // 打开写保护
    __enable_irq();                             // 使能全局中断
}

/**
 * @brief 进入深度休眠,并且使用定时唤醒
 * @param ms 指定定时唤醒的时间,单位为毫秒
 */
void HAL_WAKE_DeepSleepTimeWakeUp(uint32_t ms)
{
    uint32_t t_cnt;
    uint32_t reg5;         // 模拟配置
    uint32_t clkcfg;       // 时钟配置
    uint32_t clk_fen;      // 模块使能配置
    uint32_t saved_enable; // 中断配置

    __disable_irq();                            // 关闭全局中断，确保执行休眠期间，不会进入其他任何中断
    reg5         = HAL_REG_READ(SYS_AFE_REG5);  // 保存模拟使能配置
    clkcfg       = HAL_REG_READ(SYS_CLK_CFG);   // 保存时钟配置
    clk_fen      = HAL_REG_READ(SYS_CLK_FEN);   // 保存模块时钟使能配置
    saved_enable = HAL_REG_READ(NVIC->ISER[0]); // 保存当前中断配置

    HAL_REG_WRITE(SYS_WR_PROTECT, 0x7a83);    // 开启寄存器写使能
    HAL_REG_WRITE(NVIC->ICER[0], 0xFFFFFFFF); // 关闭所有中断
    HAL_IRQ_ModuleEnable(HAL_IRQ_MODULE_WAKE0, 0);
    {
        int32_t th;
        th = ((uint32_t)(32 * ms + 0x800) & 0x1ff000);
        th = HAL_REG_READ(HAL_IWDG[HAL_IWDG_0]->RTH) - th;
        if (th < 0)
        {
            th = 0;
        }
        HAL_REG_WRITE(HAL_IWDG[HAL_IWDG_0]->WTH, th);
    }
    HAL_IWDG_Feed(HAL_IWDG_0);     // 喂狗
    HAL_REG_WRITE(SYS_CLK_CFG, 0); // 切换到HRC时钟
    for (t_cnt = 0; t_cnt < 4000; t_cnt++)
    {
        __NOP();
    }
    HAL_REG_WRITE(SYS_CLK_FEN, 0);                                                // 关闭数字模块时钟
    HAL_REG_WRITE(SYS_AFE_REG5, SYS_AFE_REG5_RCHPD_BIT | SYS_AFE_REG5_BGPPD_BIT); // 准备关闭 PLL,BGP,以及其它模拟电路使能
    HAL_REG_WRITE(SYS_WR_PROTECT, 0x0);                                           // 关闭系统寄存器写使能

    __enable_irq();                    // 打开全局中断
    HAL_REG_SET(SCB->SCR, (1UL << 2)); // 使能深度休眠

    __WFI();         // 休眠 wakeak
    __disable_irq(); // 唤醒后关闭全局中断
    HAL_IRQ_ModuleDisable(HAL_IRQ_MODULE_WAKE0);

    HAL_REG_WRITE(SYS_WR_PROTECT, 0x7a83); // 开启寄存器写使能
    HAL_REG_WRITE(SYS_AFE_REG5, reg5);     // 开启 PLL,BGP

    for (t_cnt = 0; t_cnt < 400; t_cnt++)
    {
        __NOP();
    }
    HAL_REG_WRITE(SYS_CLK_CFG, clkcfg);         // 恢复时钟配置
    HAL_REG_WRITE(NVIC->ISER[0], saved_enable); // 恢复中断使能
    HAL_REG_WRITE(SYS_CLK_FEN, clk_fen);        // 打开其他模块
    HAL_REG_WRITE(SYS_WR_PROTECT, 0x0);         // 打开写保护
    __enable_irq();                             // 使能全局中断
}

/**
 * @brief 进入深度休眠,并且使用IO唤醒和定时唤醒
 * @param wake_up_io 指定唤醒IO引脚及其电平
 * @param ms 指定定时唤醒的时间,单位为毫秒
 */
void HAL_WAKE_DeepSleepIoTimeWakeUp(HAL_WAKE_UP_IO_x wake_up_io, uint32_t ms)
{
    uint32_t t_cnt;
    uint32_t reg5;         // 模拟配置
    uint32_t clkcfg;       // 时钟配置
    uint32_t clk_fen;      // 模块使能配置
    uint32_t saved_enable; // 中断配置

    __disable_irq();                            // 关闭全局中断，确保执行休眠期间，不会进入其他任何中断
    reg5         = HAL_REG_READ(SYS_AFE_REG5);  // 保存模拟使能配置
    clkcfg       = HAL_REG_READ(SYS_CLK_CFG);   // 保存时钟配置
    clk_fen      = HAL_REG_READ(SYS_CLK_FEN);   // 保存模块时钟使能配置
    saved_enable = HAL_REG_READ(NVIC->ISER[0]); // 保存当前中断配置

    HAL_REG_WRITE(SYS_WR_PROTECT, 0x7a83);    // 开启寄存器写使能
    HAL_REG_WRITE(NVIC->ICER[0], 0xFFFFFFFF); // 关闭所有中断
    HAL_IRQ_ModuleEnable(HAL_IRQ_MODULE_WAKE0, 0);
    {
        int32_t th;
        th = ((uint32_t)(64 * ms + 0x800) & 0x1ff000);
        th = HAL_REG_READ(HAL_IWDG[HAL_IWDG_0]->RTH) - th;
        if (th < 0)
        {
            th = 0;
        }
        HAL_REG_WRITE(HAL_IWDG[HAL_IWDG_0]->WTH, th);
    }
    HAL_IWDG_Feed(HAL_IWDG_0);     // 喂狗
    HAL_REG_WRITE(SYS_CLK_CFG, 0); // 切换到HRC时钟
    for (t_cnt = 0; t_cnt < 4000; t_cnt++)
    {
        __NOP();
    }
    HAL_REG_WRITE(SYS_CLK_FEN, 0); // 关闭数字模块时钟
    HAL_REG_WRITE(SYS_AFE_REG5, SYS_AFE_REG5_RCHPD_BIT | SYS_AFE_REG5_BGPPD_BIT);
    HAL_REG_WRITE(SYS_WR_PROTECT, 0x0); // 关闭系统寄存器写使能

    HAL_REG_WRITE(AON_IO_WAKE_POL, wake_up_io >> 8);  // 设置IO唤醒电平
    HAL_REG_WRITE(AON_IO_WAKE_EN, wake_up_io & 0xFF); // 设置IO唤醒引脚

    __enable_irq();                    // 打开全局中断
    HAL_REG_SET(SCB->SCR, (1UL << 2)); // 使能深度休眠

    __WFI();         // 休眠 wakeak
    __disable_irq(); // 唤醒后关闭全局中断
    HAL_IRQ_ModuleDisable(HAL_IRQ_MODULE_WAKE0);

    HAL_REG_WRITE(SYS_WR_PROTECT, 0x7a83); // 开启寄存器写使能
    HAL_REG_WRITE(SYS_AFE_REG5, reg5);     // 开启 PLL,BGP

    for (t_cnt = 0; t_cnt < 400; t_cnt++)
    {
        __NOP();
    }
    HAL_REG_WRITE(SYS_CLK_CFG, clkcfg);         // 恢复时钟配置
    HAL_REG_WRITE(NVIC->ISER[0], saved_enable); // 恢复中断使能
    HAL_REG_WRITE(SYS_CLK_FEN, clk_fen);        // 打开其他模块
    HAL_REG_WRITE(SYS_WR_PROTECT, 0x0);         // 打开写保护
    __enable_irq();                             // 使能全局中断
}
