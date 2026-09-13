#include "../include/hal_lksmcu_clk.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"
static volatile uint32_t HAL_CLK_mclk = 96000000;
/**
 * @brief 设置主频
 * @param FREQ_x 主频
 */
void HAL_CLK_SetMcuFreq(HAL_CLK_FREQ_x FREQ_x)
{
    uint32_t t_cnt;
    HAL_REG_SYS_UNLOCK();
    switch (FREQ_x)
    {
        case HAL_CLK_FREQ_RC_8MHZ: ///< 主频8Mhz
            HAL_CLK_mclk = 8000000;
            HAL_REG_WRITE_BIT_MASK_POS(SYS_CLK_CFG, SYS_CLK_CFG_CLK_DIV, 0);
            HAL_REG_WRITE_BIT_MASK_POS(SYS_CLK_CFG, SYS_CLK_CFG_CLK_SEL, 0);
            for (t_cnt = 0; t_cnt < 4000; t_cnt++)
            {
                __NOP();
            }
            HAL_REG_RESET(SYS_AFE_REG5, SYS_AFE_REG5_PLLPDN_BIT);
            break;
        case HAL_CLK_FREQ_RC_12MHZ: ///< 主频12Mhz
            HAL_CLK_mclk = 12000000;
            HAL_REG_SET(SYS_AFE_REG5, SYS_AFE_REG5_PLLPDN_BIT);
            for (t_cnt = 0; t_cnt < 200; t_cnt++)
            {
                __NOP();
            }
            HAL_REG_WRITE_BIT_MASK_POS(SYS_CLK_CFG, SYS_CLK_CFG_CLK_SEL, 0x01);
            HAL_REG_WRITE_BIT_MASK_POS(SYS_CLK_CFG, SYS_CLK_CFG_CLK_DIV, 0x01);
            break;
        case HAL_CLK_FREQ_RC_24MHZ: ///< 主频24Mhz
            HAL_CLK_mclk = 24000000;
            HAL_REG_SET(SYS_AFE_REG5, SYS_AFE_REG5_PLLPDN_BIT);
            for (t_cnt = 0; t_cnt < 200; t_cnt++)
            {
                __NOP();
            }
            HAL_REG_WRITE_BIT_MASK_POS(SYS_CLK_CFG, SYS_CLK_CFG_CLK_SEL, 0x01);
            HAL_REG_WRITE_BIT_MASK_POS(SYS_CLK_CFG, SYS_CLK_CFG_CLK_DIV, 0x11);
            break;
        case HAL_CLK_FREQ_RC_48MHZ: ///< 主频48Mhz
            HAL_CLK_mclk = 48000000;
            HAL_REG_SET(SYS_AFE_REG5, SYS_AFE_REG5_PLLPDN_BIT);
            for (t_cnt = 0; t_cnt < 200; t_cnt++)
            {
                __NOP();
            }
            HAL_REG_WRITE_BIT_MASK_POS(SYS_CLK_CFG, SYS_CLK_CFG_CLK_SEL, 0x01);
            HAL_REG_WRITE_BIT_MASK_POS(SYS_CLK_CFG, SYS_CLK_CFG_CLK_DIV, 0x55);
            break;
        case HAL_CLK_FREQ_RC_96MHZ: ///< 主频96Mhz
        default:
            HAL_CLK_mclk = 96000000;
            HAL_REG_SET(SYS_AFE_REG5, SYS_AFE_REG5_PLLPDN_BIT);
            for (t_cnt = 0; t_cnt < 200; t_cnt++)
            {
                __NOP();
            }
            HAL_REG_WRITE_BIT_MASK_POS(SYS_CLK_CFG, SYS_CLK_CFG_CLK_SEL, 0x01);
            HAL_REG_WRITE_BIT_MASK_POS(SYS_CLK_CFG, SYS_CLK_CFG_CLK_DIV, 0xff);
            break;
    }
    for (t_cnt = 0; t_cnt < 200; t_cnt++)
    {
        __NOP();
    }
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 获取主频
 * @return 主频
 */
uint32_t HAL_CLK_GetMcuFreq(void)
{
    return HAL_CLK_mclk;
}
