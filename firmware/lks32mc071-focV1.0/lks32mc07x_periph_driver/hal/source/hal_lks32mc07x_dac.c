#include "../include/hal_lksmcu_dac.h"
#include "../include/hal_lksmcu_trim.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"
/**
 * @brief DAC模块复位
 * @param dac_x DAC模块
 */
void HAL_DAC_Reset(HAL_DAC_x dac_x)
{
    HAL_DAC_Disable(dac_x);
}
/**
 * @brief DAC模块使能
 * @param dac_x DAC模块
 */
void HAL_DAC_Enable(HAL_DAC_x dac_x)
{
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    switch (dac_x)
    {
        case HAL_DAC_0:
            HAL_REG_SET(SYS_AFE_REG5, SYS_AFE_REG5_DAC0PDN_BIT);
            break;
        case HAL_DAC_1:
            HAL_REG_SET(SYS_AFE_REG5, SYS_AFE_REG5_DAC1PDN_BIT);
            break;
        default:
            break;
    }
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}
/**
 * @brief DAC模块失能
 * @param dac_x DAC模块
 */
void HAL_DAC_Disable(HAL_DAC_x dac_x)
{
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    switch (dac_x)
    {
        case HAL_DAC_0:
            HAL_REG_RESET(SYS_AFE_REG5, SYS_AFE_REG5_DAC0PDN_BIT);
            break;
        case HAL_DAC_1:
            HAL_REG_RESET(SYS_AFE_REG5, SYS_AFE_REG5_DAC1PDN_BIT);
            break;
        default:
            break;
    }
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}
/**
 * @brief 获取DAC模块输出最大值
 * @param dac_x DAC模块
 * @return uint16_t 最大值
 */
uint16_t HAL_DAC_GetOutValMax(HAL_DAC_x dac_x)
{
    (void)dac_x;
    return SYS_AFE_DAC0_DAC_IN_MAX;
}
/**
 * @brief 设置DAC模块输出值
 * @param dac_x DAC模块
 * @param val 输出值
 */
void HAL_DAC_SetOutVal(HAL_DAC_x dac_x, uint16_t val)
{
    switch (dac_x)
    {
        case HAL_DAC_0:
            HAL_REG_WRITE(SYS_AFE_DAC0, val);
            break;
        case HAL_DAC_1:
            HAL_REG_WRITE(SYS_AFE_DAC1, val);
            break;
        default:
            break;
    }
}
/**
 * @brief 设置DAC模块输出量程
 * @param dac_x DAC模块
 * @param range 输出量程
 */
void HAL_DAC_SetRange(HAL_DAC_x dac_x, HAL_DAC_RANGE_x range)
{
    HAL_REG_SYS_UNLOCK();
    switch (dac_x)
    {
        case HAL_DAC_0:
            if (range == HAL_DAC_RANGE_1_2)
            {
                HAL_REG_WRITE(SYS_AFE_DAC0_DC, HAL_TRIM_Read(0x0000145C));
                HAL_REG_WRITE(SYS_AFE_DAC0_AMC, HAL_TRIM_Read(0x00001458));
                HAL_REG_SET(SYS_AFE_REG1, SYS_AFE_REG1_DAC0_GAIN_BIT);
            }
            else
            {
                HAL_REG_WRITE(SYS_AFE_DAC0_DC, HAL_TRIM_Read(0x00001454));
                HAL_REG_WRITE(SYS_AFE_DAC0_AMC, HAL_TRIM_Read(0x00001450));
                HAL_REG_RESET(SYS_AFE_REG1, SYS_AFE_REG1_DAC0_GAIN_BIT);
            }
            break;
        case HAL_DAC_1:
            if (range == HAL_DAC_RANGE_1_2)
            {
                HAL_REG_WRITE(SYS_AFE_DAC1_DC, HAL_TRIM_Read(0x0000146C));
                HAL_REG_WRITE(SYS_AFE_DAC1_AMC, HAL_TRIM_Read(0x00001468));
                HAL_REG_SET(SYS_AFE_REG1, SYS_AFE_REG1_DAC1_GAIN_BIT);
            }
            else
            {
                HAL_REG_WRITE(SYS_AFE_DAC1_DC, HAL_TRIM_Read(0x00001464));
                HAL_REG_WRITE(SYS_AFE_DAC1_AMC, HAL_TRIM_Read(0x00001460));
                HAL_REG_RESET(SYS_AFE_REG1, SYS_AFE_REG1_DAC1_GAIN_BIT);
            }
            break;
        default:
            break;
    }
    HAL_REG_SYS_UNLOCK();
}
/**
 * @brief 获取DAC模块输出量程
 * @param dac_x DAC模块
 * @return 输出量程
 */
float HAL_DAC_GetRange(HAL_DAC_x dac_x)
{
    float val = 0;
    switch (dac_x)
    {
        case HAL_DAC_0:
            if (HAL_REG_READ_BIT(SYS_AFE_REG1, SYS_AFE_REG1_DAC0_GAIN_BIT))
            {
                val = 1.2;
            }
            else
            {
                val = 4.85;
            }
            break;
        case HAL_DAC_1:
            if (HAL_REG_READ_BIT(SYS_AFE_REG1, SYS_AFE_REG1_DAC1_GAIN_BIT))
            {
                val = 1.2;
            }
            else
            {
                val = 4.85;
            }
            break;
        default:
            break;
    }
    return val;
}
/**
 * @brief 设置DAC模块输出电压
 * @param dac_x DAC模块
 * @param vol_mV 输出电压，单位mV
 */
void HAL_DAC_SetOutVoltagemV(HAL_DAC_x dac_x, uint16_t vol_mV)
{
    uint32_t val;
    if (vol_mV < 1000)
    {
        val = vol_mV;
        val = val * SYS_AFE_DAC0_DAC_IN_MAX / 1200;
        if (val > SYS_AFE_DAC0_DAC_IN_MAX)
        {
            val = SYS_AFE_DAC0_DAC_IN_MAX;
        }
        HAL_DAC_SetRange(dac_x, HAL_DAC_RANGE_1_2);
        HAL_DAC_SetOutVal(dac_x, val);
    }
    else
    {
        val = vol_mV;
        val = val * SYS_AFE_DAC0_DAC_IN_MAX / 4850;
        if (val > SYS_AFE_DAC0_DAC_IN_MAX)
        {
            val = SYS_AFE_DAC0_DAC_IN_MAX;
        }
        HAL_DAC_SetRange(dac_x, HAL_DAC_RANGE_4_85V);
        HAL_DAC_SetOutVal(dac_x, val);
    }
}
/**
 * @brief 输出到GPIO使能
 * @param dac_x DAC模块
 */
void HAL_DAC_Out2GpioEnable(HAL_DAC_x dac_x)
{
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    switch (dac_x)
    {
        case HAL_DAC_0:
            HAL_REG_SET(SYS_AFE_REG3, SYS_AFE_REG3_DAC0OUT_EN_BIT);
            break;
        case HAL_DAC_1:
            HAL_REG_SET(SYS_AFE_REG3, SYS_AFE_REG3_DAC1OUT_EN_BIT);
            break;
        default:
            break;
    }
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}
/**
 * @brief 输出到GPIO关闭
 * @param dac_x DAC模块
 */
void HAL_DAC_Out2GpioDisable(HAL_DAC_x dac_x)
{
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    switch (dac_x)
    {
        case HAL_DAC_0:
            HAL_REG_RESET(SYS_AFE_REG3, SYS_AFE_REG3_DAC0OUT_EN_BIT);
            break;
        case HAL_DAC_1:
            HAL_REG_RESET(SYS_AFE_REG3, SYS_AFE_REG3_DAC1OUT_EN_BIT);
            break;
        default:
            break;
    }
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 设置DAC输出到GPIO
 * @param dac_x DAC模块
 * @param px GPIO
 */
void HAL_DAC_SetGpioOut(HAL_DAC_x dac_x, HAL_GPIO_Px px)
{
    (void)dac_x;

    HAL_GPIO_SetAf(px, HAL_GPIO_AF_DAC);
    HAL_GPIO_SetMode(px, HAL_GPIO_MODE_AFE);
}
