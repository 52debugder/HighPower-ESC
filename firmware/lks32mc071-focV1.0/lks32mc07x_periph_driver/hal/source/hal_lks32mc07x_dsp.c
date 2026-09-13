#include "../include/hal_lksmcu_dsp.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"

/**
 * @brief  DSP复位
 * @param  dsp_x DSP选择
 */
void HAL_DSP_Reset(HAL_DSP_x dsp_x)
{
    (void)dsp_x;
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    HAL_REG_SET(SYS_SFT_RST, SYS_SFT_RST_DSP0_SFT_RST_BIT);
    HAL_REG_RESET(SYS_SFT_RST, SYS_SFT_RST_DSP0_SFT_RST_BIT);
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}

/**
 * @brief  DSP使能
 * @param  dsp_x DSP选择
 */
void HAL_DSP_Enable(HAL_DSP_x dsp_x)
{
    (void)dsp_x;
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    HAL_REG_SET(SYS_CLK_FEN, SYS_CLK_FEN_DSP0_CLK_EN_BIT);
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}

/**
 * @brief  DSP复位
 * @param  dsp_x DSP选择
 */
void HAL_DSP_Disable(HAL_DSP_x dsp_x)
{
    (void)dsp_x;
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    HAL_REG_RESET(SYS_CLK_FEN, SYS_CLK_FEN_DSP0_CLK_EN_BIT);
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}

/**
 * @brief  DSP正弦计算
 * @param  dsp_x DSP选择
 * @param  angle 角度
 * @retval 正弦结果
 */
int16_t HAL_DSP_Sin(HAL_DSP_x dsp_x, int16_t angle)
{
    (void)dsp_x;
    HAL_REG_WRITE(DSP0_SC, DSP0_SC_PAUSED_BIT | DSP0_SC_CORDIC_MODE_BIT);
    HAL_REG_WRITE(DSP0_THETA, angle);
    return HAL_REG_READ(DSP0_SIN);
}

/**
 * @brief  DSP余弦计算
 * @param  dsp_x DSP选择
 * @param  angle 角度
 * @retval 余弦结果
 */
int16_t HAL_DSP_Cos(HAL_DSP_x dsp_x, int16_t angle)
{
    (void)dsp_x;
    HAL_REG_WRITE(DSP0_SC, DSP0_SC_PAUSED_BIT | DSP0_SC_CORDIC_MODE_BIT);
    HAL_REG_WRITE(DSP0_THETA, angle);
    return HAL_REG_READ(DSP0_COS);
}

/**
 * @brief  DSP正弦余弦计算
 * @param  dsp_x DSP选择
 * @param  angle 角度
 * @param  sin 正弦结果
 * @param  cos 余弦结果
 */
void HAL_DSP_SinCos(HAL_DSP_x dsp_x, int16_t angle, int16_t *sin, int16_t *cos)
{
    (void)dsp_x;
    HAL_REG_WRITE(DSP0_SC, DSP0_SC_PAUSED_BIT | DSP0_SC_CORDIC_MODE_BIT);
    HAL_REG_WRITE(DSP0_THETA, angle);
    *sin = HAL_REG_READ(DSP0_SIN);
    *cos = HAL_REG_READ(DSP0_COS);
}
/**
 * @brief  DSP开方
 * @param  dsp_x DSP选择
 * @param  x 输入
 * @retval 开方结果
 */
uint16_t HAL_DSP_Sqrt(HAL_DSP_x dsp_x, uint32_t x)
{
    (void)dsp_x;
    HAL_REG_WRITE(DSP0_RAD, x);
    return HAL_REG_READ(DSP0_SQRT);
}

/**
 * @brief  DSP除法
 * @param  dsp_x DSP选择
 * @param  a 被除数
 * @param  b 除数
 * @retval 商
 */
int32_t HAL_DSP_Div(HAL_DSP_x dsp_x, int32_t a, int32_t b)
{
    (void)dsp_x;
    HAL_REG_WRITE(DSP0_DID, a);
    HAL_REG_WRITE(DSP0_DIS, b);
    return HAL_REG_READ(DSP0_QUO);
}
