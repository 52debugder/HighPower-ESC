#include "../include/hal_lksmcu_opa.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"

// 模块复位
void HAL_OPA_Reset(HAL_OPA_x opa_x)
{
    (void)opa_x;
}
// 模块打开
void HAL_OPA_Enable(HAL_OPA_x opa_x)
{
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    switch (opa_x)
    {
        case HAL_OPA_0:
            HAL_REG_SET(SYS_AFE_REG5, SYS_AFE_REG5_OPA0PDN_BIT);
            break;
        case HAL_OPA_1:
            HAL_REG_SET(SYS_AFE_REG5, SYS_AFE_REG5_OPA1PDN_BIT);
            break;
        case HAL_OPA_2:
            HAL_REG_SET(SYS_AFE_REG5, SYS_AFE_REG5_OPA2PDN_BIT);
            break;
        case HAL_OPA_3:
            HAL_REG_SET(SYS_AFE_REG5, SYS_AFE_REG5_OPA3PDN_BIT);
            break;
        default:
            break;
    }
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}
// 模块关闭
void HAL_OPA_Disable(HAL_OPA_x opa_x)
{
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    switch (opa_x)
    {
        case HAL_OPA_0:
            HAL_REG_RESET(SYS_AFE_REG5, SYS_AFE_REG5_OPA0PDN_BIT);
            break;
        case HAL_OPA_1:
            HAL_REG_RESET(SYS_AFE_REG5, SYS_AFE_REG5_OPA1PDN_BIT);
            break;
        case HAL_OPA_2:
            HAL_REG_RESET(SYS_AFE_REG5, SYS_AFE_REG5_OPA2PDN_BIT);
            break;
        case HAL_OPA_3:
            HAL_REG_RESET(SYS_AFE_REG5, SYS_AFE_REG5_OPA3PDN_BIT);
            break;
        default:
            break;
    }
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}
// 设置增益
void HAL_OPA_SetGain(HAL_OPA_x opa_x, HAL_OPA_GAIN_x gain_x)
{
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    switch (opa_x)
    {
        case HAL_OPA_0:
            HAL_REG_WRITE_BIT_MASK_POS(SYS_AFE_REG0, SYS_AFE_REG0_RES_OPA0, gain_x);
            break;
        case HAL_OPA_1:
            HAL_REG_WRITE_BIT_MASK_POS(SYS_AFE_REG0, SYS_AFE_REG0_RES_OPA1, gain_x);
            break;
        case HAL_OPA_2:
            HAL_REG_WRITE_BIT_MASK_POS(SYS_AFE_REG0, SYS_AFE_REG0_RES_OPA2, gain_x);
            break;
        case HAL_OPA_3:
            HAL_REG_WRITE_BIT_MASK_POS(SYS_AFE_REG0, SYS_AFE_REG0_RES_OPA3, gain_x);
            break;
        default:
            break;
    }
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}

/**
 * @brief OPA输出到IO
 * @param opa_x 运放序号
 */
void HAL_OPA_Out2GpioEnable(HAL_OPA_x opa_x)
{
    // [2:0] 使能OPAx输出信号送至IO口p2_7 000:不输出; 001:输出OPA0信号到IO口; 010:输出OPA1信号到IO口; 011:输出OPA2信号到IO口; 100:输出OPA3信号到IO口; 101~111: 不允许此配置

    HAL_REG_SYS_UNLOCK();
    switch (opa_x)
    {
        case HAL_OPA_0:
            HAL_REG_WRITE_BIT_MASK_POS(SYS_AFE_REG2, SYS_AFE_REG2_OPAOUT_EN, 1);
            break;
        case HAL_OPA_1:
            HAL_REG_WRITE_BIT_MASK_POS(SYS_AFE_REG2, SYS_AFE_REG2_OPAOUT_EN, 2);
            break;
        case HAL_OPA_2:
            HAL_REG_WRITE_BIT_MASK_POS(SYS_AFE_REG2, SYS_AFE_REG2_OPAOUT_EN, 3);
            break;
        case HAL_OPA_3:
            HAL_REG_WRITE_BIT_MASK_POS(SYS_AFE_REG2, SYS_AFE_REG2_OPAOUT_EN, 4);
            break;
        default:
            break;
    }
    HAL_REG_SYS_LOCK();
}

/**
 * @brief OPA停止输出到IO
 * @param opa_x 运放序号
 */
void HAL_OPA_Out2GpioDisable(HAL_OPA_x opa_x)
{
    (void)opa_x;
    // [2:0] 使能OPAx输出信号送至IO口p2_7 000:不输出; 001:输出OPA0信号到IO口; 010:输出OPA1信号到IO口; 011:输出OPA2信号到IO口; 100:输出OPA3信号到IO口; 101~111: 不允许此配置

    HAL_REG_SYS_UNLOCK();
    HAL_REG_WRITE_BIT_MASK_POS(SYS_AFE_REG2, SYS_AFE_REG2_OPAOUT_EN, 0);
    HAL_REG_SYS_LOCK();
}

/**
 * @brief OPA设置IO输入
 * @param opa_x 运放序号
 * @param px IO序号
 */
void HAL_OPA_SetGpioIn(HAL_OPA_x opa_x, HAL_GPIO_Px px)
{
    (void)opa_x;
    HAL_GPIO_SetAf(px, HAL_GPIO_AF_OPA);
    HAL_GPIO_SetMode(px, HAL_GPIO_MODE_AFE);
}

/**
 * @brief OPA设置IO输出
 * @param opa_x 运放序号
 * @param px IO序号
 */
void HAL_OPA_SetGpioOut(HAL_OPA_x opa_x, HAL_GPIO_Px px)
{
    (void)opa_x;
    HAL_GPIO_SetAf(px, HAL_GPIO_AF_OPA);
    HAL_GPIO_SetMode(px, HAL_GPIO_MODE_AFE);
}
