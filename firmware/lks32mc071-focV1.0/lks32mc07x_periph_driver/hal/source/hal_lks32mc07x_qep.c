#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lksmcu_qep.h"
#include "../include/hal_lksmcu_timer.h"
#include "../hal_lks32mc07x.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"

/**
 * @brief 模块复位
 * @param qep QEP模块
 */
void HAL_QEP_Reset(HAL_QEP_x qep)
{
    switch (qep)
    {
        case HAL_QEP_0:
            HAL_REG_SYS_UNLOCK();
            HAL_REG_SET(SYS_SFT_RST, SYS_SFT_RST_QEP0_SFT_RST_BIT);
            HAL_REG_RESET(SYS_SFT_RST, SYS_SFT_RST_QEP0_SFT_RST_BIT);
            HAL_REG_SYS_LOCK();
            break;
        case HAL_QEP_1:
            HAL_REG_SYS_UNLOCK();
            HAL_REG_SET(SYS_SFT_RST, SYS_SFT_RST_QEP1_SFT_RST_BIT);
            HAL_REG_RESET(SYS_SFT_RST, SYS_SFT_RST_QEP1_SFT_RST_BIT);
            HAL_REG_SYS_LOCK();
            break;
        default:
            break;
    }
}

/**
 * @brief 模块打开
 * @param qep QEP模块
 */
void HAL_QEP_Enable(HAL_QEP_x qep)
{
    switch (qep)
    {
        case HAL_QEP_0:
            HAL_REG_SYS_UNLOCK();
            HAL_REG_SET(SYS_CLK_FEN, SYS_CLK_FEN_QEP0_CLK_EN_BIT);
            HAL_REG_SYS_LOCK();
            HAL_TIMER_Enable(HAL_TIMER_2); // qep0使用时必须使能TIMER2
            break;
        case HAL_QEP_1:
            HAL_REG_SYS_UNLOCK();
            HAL_REG_SET(SYS_CLK_FEN, SYS_CLK_FEN_QEP1_CLK_EN_BIT);
            HAL_REG_SYS_LOCK();
            HAL_TIMER_Enable(HAL_TIMER_3); // qep1使用时必须使能TIMER3
            break;
        default:
            break;
    }
    HAL_REG_SET(HAL_QEP[qep]->CFG, QEP0_CFG_EN_BIT);
}

/**
 * @brief 模块关闭
 * @param qep QEP模块
 */
void HAL_QEP_Disable(HAL_QEP_x qep)
{
    switch (qep)
    {
        case HAL_QEP_0:
            HAL_REG_SYS_UNLOCK();
            HAL_REG_RESET(SYS_CLK_FEN, SYS_CLK_FEN_QEP0_CLK_EN_BIT);
            HAL_REG_SYS_LOCK();
            break;
        case HAL_QEP_1:
            HAL_REG_SYS_UNLOCK();
            HAL_REG_RESET(SYS_CLK_FEN, SYS_CLK_FEN_QEP1_CLK_EN_BIT);
            HAL_REG_SYS_LOCK();
            break;
        default:
            break;
    }
    HAL_REG_RESET(HAL_QEP[qep]->CFG, QEP0_CFG_EN_BIT);
}

/**
 * @brief 设置最大计数值
 * @param qep QEP模块
 * @param th 最大计数值
 */
void HAL_QEP_SetTh(HAL_QEP_x qep, uint32_t th)
{
    HAL_REG_WRITE(HAL_QEP[qep]->TH, th);
}

/**
 * @brief 设置计数模式
 * @param qep QEP模块
 * @param mode 计数模式
 */
void HAL_QEP_SetMode(HAL_QEP_x qep, HAL_QEP_MODE_x mode)
{
    switch (mode)
    {
        case HAL_QEP_MODE_QUADRATURE:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_QEP[qep]->CFG, QEP0_CFG_MODE, 1);
            break;
        case HAL_QEP_MODE_SYMBOL_PULSE:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_QEP[qep]->CFG, QEP0_CFG_MODE, 2);
            break;
        case HAL_QEP_MODE_DUAL_PULSE:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_QEP[qep]->CFG, QEP0_CFG_MODE, 3);
            break;
        default:
            break;
    }
}

/**
 * @brief 获取当前的计数值
 * @param qep QEP模块
 * @return 当前的计数值
 */
uint32_t HAL_QEP_ReadCnt(HAL_QEP_x qep)
{
    return HAL_REG_READ(HAL_QEP[qep]->CNT);
}

/**
 * @brief 复位计数值到0
 * @param qep QEP模块
 */
void HAL_QEP_ResetCnt(HAL_QEP_x qep)
{
    HAL_REG_WRITE(HAL_QEP[qep]->CNT, 0);
}

// 设置时钟分频 (QEP复用TIMER2/3的CLK_DIV)
void HAL_QEP_SetClockDiv(HAL_QEP_x qep_x, uint32_t div)
{
    HAL_TIMER_SetClockDiv((qep_x == HAL_QEP_0) ? HAL_TIMER_2 : HAL_TIMER_3, div);
}

// 获取时钟分频实际除数
uint32_t HAL_QEP_GetClockDiv(HAL_QEP_x qep_x)
{
    return HAL_TIMER_GetClockDiv((qep_x == HAL_QEP_0) ? HAL_TIMER_2 : HAL_TIMER_3);
}

// 获取分频后工作时钟
uint32_t HAL_QEP_GetClockFreq(HAL_QEP_x qep_x)
{
    return HAL_CLK_GetMcuFreq() / HAL_QEP_GetClockDiv(qep_x);
}

/**
 * @brief 设置QEP模块的引脚
 * @param qepx QEP模块
 * @param px 引脚
 */
void HAL_QEP_SetGpio(HAL_QEP_x qepx, HAL_GPIO_Px px)
{
    (void)qepx;
    HAL_GPIO_SetMode(px, HAL_GPIO_MODE_IN);
    HAL_GPIO_SetAf(px, HAL_GPIO_AF_QEP0);
}
