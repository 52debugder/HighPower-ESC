#include "../include/hal_lksmcu_iwdg.h"
#include "../hal_lks32mc07x.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"
/**
 * @brief 模块复位
 * @param iwdg 看门狗模块
 */
void HAL_IWDG_Reset(HAL_IWDG_x iwdg)
{
    HAL_IWDG_Disable(iwdg);
}

/**
 * @brief 模块打开
 * @param iwdg 看门狗模块
 */
void HAL_IWDG_Enable(HAL_IWDG_x iwdg)
{
    (void)iwdg;
    HAL_REG_WRITE(HAL_IWDG[0]->CFG, IWDG_CFG_WDG_EN_BIT);
}

/**
 * @brief 模块关闭
 * @param iwdg 看门狗模块
 */
void HAL_IWDG_Disable(HAL_IWDG_x iwdg)
{
    (void)iwdg;
    // 写0同时向[15:8]写入0x3C可清零
    HAL_REG_WRITE_BIT(IWDG_CFG, 0x3c00 | IWDG_CFG_WDG_EN_BIT, 0x3c00);
}

/**
 * @brief 设置看门狗超时复位时间
 * @param iwdg 看门狗模块
 * @param ms 超时复位时间,单位mS
 */
void HAL_IWDG_SetResetTimemS(HAL_IWDG_x iwdg, int32_t ms)
{
    uint32_t th;
    (void)iwdg;
    // IWDG_RTH_IWDG_RTH(1) - 1的作用是为了确保实际复位时间大于期望值(不考虑RCL的频率误差)，例如设定复位时间100mS，实际复位时间大于100mS
    th = ((uint32_t)(32 * ms + IWDG_RTH_IWDG_RTH(1) - 1) >> IWDG_RTH_IWDG_RTH_POS);
    HAL_REG_WRITE(HAL_IWDG[iwdg]->PSW, 0xA6B4);
    HAL_REG_WRITE_BIT_MASK_POS(IWDG_RTH, IWDG_RTH_IWDG_RTH, th);
}

/**
 * @brief 喂狗
 * @param iwdg 看门狗模块
 */
void HAL_IWDG_Feed(HAL_IWDG_x iwdg)
{
    (void)iwdg;
    if (HAL_REG_READ_BIT(HAL_SYS[0]->CLK_CFG, SYS_CLK_CFG_CLK_SEL_MASK | SYS_CLK_CFG_CLK_DIV_MASK) == 0x1ff)
    {
        // 全速运行时直接喂狗
        HAL_REG_WRITE(HAL_IWDG[iwdg]->PSW, 0xA6B4);
        HAL_REG_WRITE(HAL_IWDG[iwdg]->CLR, 0x798D);
    }
    else
    {
        int32_t flg = __get_PRIMASK();
        uint32_t clkcfg;
        __disable_irq();
        HAL_REG_SYS_UNLOCK();

        clkcfg = HAL_REG_READ(HAL_SYS[0]->CLK_CFG);

        HAL_REG_WRITE_BIT_MASK_POS(HAL_SYS[0]->CLK_CFG, SYS_CLK_CFG_CLK_DIV, 0xff);
        HAL_REG_WRITE(HAL_IWDG[iwdg]->PSW, 0xA6B4);
        HAL_REG_WRITE(HAL_IWDG[iwdg]->CLR, 0x798D);
        HAL_REG_WRITE(HAL_SYS[0]->CLK_CFG, clkcfg);

        HAL_REG_SYS_LOCK();

        __set_PRIMASK(flg);
    }
}
