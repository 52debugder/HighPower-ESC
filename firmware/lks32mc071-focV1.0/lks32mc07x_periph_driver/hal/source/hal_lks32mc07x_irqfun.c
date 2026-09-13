

#include "../hal_lks32mc07x.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"
#include "../include/hal_lksmcu_irqfun.h"

/**
 * @brief 中断处理函数
 * @param hall 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_HALL_IrqChange(HAL_HALL_x hall)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_HALL[hall]->CFG);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_HALL[hall]->INFO);
    if ((HAL_REG_READ_BIT(*addr_ie, HALL0_CFG_CHG_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, HALL0_INFO_CHG_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_HALL_IrqChange 的区别是不判断中断使能）
 * @param hall 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_HALL_IrqChangeFlg(HAL_HALL_x hall)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_HALL[hall]->INFO);
    if (HAL_REG_READ_BIT(*addr, HALL0_INFO_CHG_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param hall 模块编号
 */
void HAL_HALL_IrqChangeEnable(HAL_HALL_x hall)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_HALL[hall]->CFG);
    HAL_REG_SET(*addr, HALL0_CFG_CHG_IE_BIT);
}

/**
 * @brief 中断禁止
 * @param hall 模块编号
 */
void HAL_HALL_IrqChangeDisable(HAL_HALL_x hall)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_HALL[hall]->CFG);
    HAL_REG_RESET(*addr, HALL0_CFG_CHG_IE_BIT);
}

/**
 * @brief 中断清除
 * @param hall 模块编号
 */
void HAL_HALL_IrqChangeClear(HAL_HALL_x hall)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_HALL[hall]->INFO);
    HAL_REG_WRITE(*addr, HALL0_INFO_CHG_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param hall 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_HALL_IrqOver(HAL_HALL_x hall)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_HALL[hall]->CFG);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_HALL[hall]->INFO);
    if ((HAL_REG_READ_BIT(*addr_ie, HALL0_CFG_CHG_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, HALL0_INFO_OV_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_HALL_IrqOver 的区别是不判断中断使能）
 * @param hall 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_HALL_IrqOverFlg(HAL_HALL_x hall)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_HALL[hall]->INFO);
    if (HAL_REG_READ_BIT(*addr, HALL0_INFO_OV_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param hall 模块编号
 */
void HAL_HALL_IrqOverEnable(HAL_HALL_x hall)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_HALL[hall]->CFG);
    HAL_REG_SET(*addr, HALL0_CFG_CHG_IE_BIT);
}

/**
 * @brief 中断禁止
 * @param hall 模块编号
 */
void HAL_HALL_IrqOverDisable(HAL_HALL_x hall)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_HALL[hall]->CFG);
    HAL_REG_RESET(*addr, HALL0_CFG_CHG_IE_BIT);
}

/**
 * @brief 中断清除
 * @param hall 模块编号
 */
void HAL_HALL_IrqOverClear(HAL_HALL_x hall)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_HALL[hall]->INFO);
    HAL_REG_WRITE(*addr, HALL0_INFO_OV_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param adc 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_ADC_IrqSamp1(HAL_ADC_x adc)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IF);
    if ((HAL_REG_READ_BIT(*addr_ie, ADCx_IE_SF1_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, ADCx_IF_SF1_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_ADC_IrqSamp1 的区别是不判断中断使能）
 * @param adc 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_ADC_IrqSamp1Flg(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IF);
    if (HAL_REG_READ_BIT(*addr, ADCx_IF_SF1_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param adc 模块编号
 */
void HAL_ADC_IrqSamp1Enable(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IE);
    HAL_REG_SET(*addr, ADCx_IE_SF1_IE_BIT);
}

/**
 * @brief 中断禁止
 * @param adc 模块编号
 */
void HAL_ADC_IrqSamp1Disable(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IE);
    HAL_REG_RESET(*addr, ADCx_IE_SF1_IE_BIT);
}

/**
 * @brief 中断清除
 * @param adc 模块编号
 */
void HAL_ADC_IrqSamp1Clear(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IF);
    HAL_REG_WRITE(*addr, ADCx_IF_SF1_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param adc 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_ADC_IrqSamp2(HAL_ADC_x adc)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IF);
    if ((HAL_REG_READ_BIT(*addr_ie, ADCx_IE_SF2_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, ADCx_IF_SF2_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_ADC_IrqSamp2 的区别是不判断中断使能）
 * @param adc 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_ADC_IrqSamp2Flg(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IF);
    if (HAL_REG_READ_BIT(*addr, ADCx_IF_SF2_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param adc 模块编号
 */
void HAL_ADC_IrqSamp2Enable(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IE);
    HAL_REG_SET(*addr, ADCx_IE_SF2_IE_BIT);
}

/**
 * @brief 中断禁止
 * @param adc 模块编号
 */
void HAL_ADC_IrqSamp2Disable(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IE);
    HAL_REG_RESET(*addr, ADCx_IE_SF2_IE_BIT);
}

/**
 * @brief 中断清除
 * @param adc 模块编号
 */
void HAL_ADC_IrqSamp2Clear(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IF);
    HAL_REG_WRITE(*addr, ADCx_IF_SF2_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqOverflow(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    addr_if = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    if ((HAL_REG_READ_BIT(*addr_ie, MCPWM0_IE0_T0_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, MCPWM0_IF0_T0_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqOverflow 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqOverflowFlg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    if (HAL_REG_READ_BIT(*addr, MCPWM0_IF0_T0_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqOverflowEnable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, MCPWM0_IE0_T0_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqOverflowDisable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, MCPWM0_IE0_T0_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqOverflowClear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    HAL_REG_WRITE(*addr, MCPWM0_IF0_T0_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqZeroCross(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    addr_if = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    if ((HAL_REG_READ_BIT(*addr_ie, MCPWM0_IE0_T1_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, MCPWM0_IF0_T1_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqZeroCross 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqZeroCrossFlg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    if (HAL_REG_READ_BIT(*addr, MCPWM0_IF0_T1_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqZeroCrossEnable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, MCPWM0_IE0_T1_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqZeroCrossDisable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, MCPWM0_IE0_T1_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqZeroCrossClear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    HAL_REG_WRITE(*addr, MCPWM0_IF0_T1_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqFail0(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->EIE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->EIF);
    if ((HAL_REG_READ_BIT(*addr_ie, ((mcpwmx & 0xf0) == 0) ? MCPWM0_EIE_FAIL0_IE_BIT : MCPWM0_EIE_FAIL2_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, ((mcpwmx & 0xf0) == 0) ? MCPWM0_EIF_FAIL0_IF_BIT : MCPWM0_EIF_FAIL2_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqFail0 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqFail0Flg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->EIF);
    if (HAL_REG_READ_BIT(*addr, ((mcpwmx & 0xf0) == 0) ? MCPWM0_EIF_FAIL0_IF_BIT : MCPWM0_EIF_FAIL2_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqFail0Enable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->EIE);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, ((mcpwmx & 0xf0) == 0) ? MCPWM0_EIE_FAIL0_IE_BIT : MCPWM0_EIE_FAIL2_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqFail0Disable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->EIE);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, ((mcpwmx & 0xf0) == 0) ? MCPWM0_EIE_FAIL0_IE_BIT : MCPWM0_EIE_FAIL2_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqFail0Clear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->EIF);
    HAL_REG_WRITE(*addr, ((mcpwmx & 0xf0) == 0) ? MCPWM0_EIF_FAIL0_IF_BIT : MCPWM0_EIF_FAIL2_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqFail1(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->EIE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->EIF);
    if ((HAL_REG_READ_BIT(*addr_ie, ((mcpwmx & 0xf0) == 0) ? MCPWM0_EIE_FAIL1_IE_BIT : MCPWM0_EIE_FAIL3_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, ((mcpwmx & 0xf0) == 0) ? MCPWM0_EIF_FAIL1_IF_BIT : MCPWM0_EIF_FAIL3_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqFail1 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqFail1Flg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->EIF);
    if (HAL_REG_READ_BIT(*addr, ((mcpwmx & 0xf0) == 0) ? MCPWM0_EIF_FAIL1_IF_BIT : MCPWM0_EIF_FAIL3_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqFail1Enable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->EIE);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, ((mcpwmx & 0xf0) == 0) ? MCPWM0_EIE_FAIL1_IE_BIT : MCPWM0_EIE_FAIL3_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqFail1Disable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->EIE);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, ((mcpwmx & 0xf0) == 0) ? MCPWM0_EIE_FAIL1_IE_BIT : MCPWM0_EIE_FAIL3_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqFail1Clear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->EIF);
    HAL_REG_WRITE(*addr, ((mcpwmx & 0xf0) == 0) ? MCPWM0_EIF_FAIL1_IF_BIT : MCPWM0_EIF_FAIL3_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqFail(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->EIE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->EIF);
    if ((HAL_REG_READ_BIT(*addr_ie, ((mcpwmx & 0xf0) == 0) ? MCPWM0_EIE_FAIL0_IE_BIT | MCPWM0_EIE_FAIL1_IE_BIT : MCPWM0_EIE_FAIL2_IE_BIT | MCPWM0_EIE_FAIL3_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, ((mcpwmx & 0xf0) == 0) ? MCPWM0_EIF_FAIL0_IF_BIT | MCPWM0_EIF_FAIL1_IF_BIT : MCPWM0_EIF_FAIL2_IF_BIT | MCPWM0_EIF_FAIL3_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqFail 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqFailFlg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->EIF);
    if (HAL_REG_READ_BIT(*addr, ((mcpwmx & 0xf0) == 0) ? MCPWM0_EIF_FAIL0_IF_BIT | MCPWM0_EIF_FAIL1_IF_BIT : MCPWM0_EIF_FAIL2_IF_BIT | MCPWM0_EIF_FAIL3_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqFailEnable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->EIE);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, ((mcpwmx & 0xf0) == 0) ? MCPWM0_EIE_FAIL0_IE_BIT | MCPWM0_EIE_FAIL1_IE_BIT : MCPWM0_EIE_FAIL2_IE_BIT | MCPWM0_EIE_FAIL3_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqFailDisable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->EIE);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, ((mcpwmx & 0xf0) == 0) ? MCPWM0_EIE_FAIL0_IE_BIT | MCPWM0_EIE_FAIL1_IE_BIT : MCPWM0_EIE_FAIL2_IE_BIT | MCPWM0_EIE_FAIL3_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqFailClear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->EIF);
    HAL_REG_WRITE(*addr, ((mcpwmx & 0xf0) == 0) ? MCPWM0_EIF_FAIL0_IF_BIT | MCPWM0_EIF_FAIL1_IF_BIT : MCPWM0_EIF_FAIL2_IF_BIT | MCPWM0_EIF_FAIL3_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param cmp_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_CMP_IrqCompare(HAL_CMP_x cmp_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_CMP[0]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_CMP[0]->IF);
    if ((HAL_REG_READ_BIT(*addr_ie, CMP_IE_CMP0_IE_BIT << (cmp_x))) && (HAL_REG_READ_BIT(*addr_if, CMP_IF_CMP0_IF_BIT << (cmp_x))))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_CMP_IrqCompare 的区别是不判断中断使能）
 * @param cmp_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_CMP_IrqCompareFlg(HAL_CMP_x cmp_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_CMP[0]->IF);
    if (HAL_REG_READ_BIT(*addr, CMP_IF_CMP0_IF_BIT << (cmp_x)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param cmp_x 模块编号
 */
void HAL_CMP_IrqCompareEnable(HAL_CMP_x cmp_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_CMP[0]->IE);
    HAL_REG_SET(*addr, CMP_IE_CMP0_IE_BIT << (cmp_x));
}

/**
 * @brief 中断禁止
 * @param cmp_x 模块编号
 */
void HAL_CMP_IrqCompareDisable(HAL_CMP_x cmp_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_CMP[0]->IE);
    HAL_REG_RESET(*addr, CMP_IE_CMP0_IE_BIT << (cmp_x));
}

/**
 * @brief 中断清除
 * @param cmp_x 模块编号
 */
void HAL_CMP_IrqCompareClear(HAL_CMP_x cmp_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_CMP[0]->IF);
    HAL_REG_WRITE(*addr, CMP_IF_CMP0_IF_BIT << (cmp_x));
}

/**
 * @brief 中断处理函数
 * @param timer_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_TIMER_IrqOverflow(HAL_TIMER_x timer_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_TIMER[timer_x]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_TIMER[timer_x]->IF);
    if ((HAL_REG_READ_BIT(*addr_ie, TIMER0_IE_ZC_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, TIMER0_IF_ZC_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_TIMER_IrqOverflow 的区别是不判断中断使能）
 * @param timer_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_TIMER_IrqOverflowFlg(HAL_TIMER_x timer_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_TIMER[timer_x]->IF);
    if (HAL_REG_READ_BIT(*addr, TIMER0_IF_ZC_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param timer_x 模块编号
 */
void HAL_TIMER_IrqOverflowEnable(HAL_TIMER_x timer_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_TIMER[timer_x]->IE);
    HAL_REG_SET(*addr, TIMER0_IE_ZC_IE_BIT);
}

/**
 * @brief 中断禁止
 * @param timer_x 模块编号
 */
void HAL_TIMER_IrqOverflowDisable(HAL_TIMER_x timer_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_TIMER[timer_x]->IE);
    HAL_REG_RESET(*addr, TIMER0_IE_ZC_IE_BIT);
}

/**
 * @brief 中断清除
 * @param timer_x 模块编号
 */
void HAL_TIMER_IrqOverflowClear(HAL_TIMER_x timer_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_TIMER[timer_x]->IF);
    HAL_REG_WRITE(*addr, TIMER0_IF_ZC_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param timer_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_TIMER_IrqCompare0(HAL_TIMER_x timer_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_TIMER[timer_x]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_TIMER[timer_x]->IF);
    if ((HAL_REG_READ_BIT(*addr_ie, TIMER0_IE_CH0_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, TIMER0_IF_CH0_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_TIMER_IrqCompare0 的区别是不判断中断使能）
 * @param timer_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_TIMER_IrqCompare0Flg(HAL_TIMER_x timer_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_TIMER[timer_x]->IF);
    if (HAL_REG_READ_BIT(*addr, TIMER0_IF_CH0_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param timer_x 模块编号
 */
void HAL_TIMER_IrqCompare0Enable(HAL_TIMER_x timer_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_TIMER[timer_x]->IE);
    HAL_REG_SET(*addr, TIMER0_IE_CH0_IE_BIT);
}

/**
 * @brief 中断禁止
 * @param timer_x 模块编号
 */
void HAL_TIMER_IrqCompare0Disable(HAL_TIMER_x timer_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_TIMER[timer_x]->IE);
    HAL_REG_RESET(*addr, TIMER0_IE_CH0_IE_BIT);
}

/**
 * @brief 中断清除
 * @param timer_x 模块编号
 */
void HAL_TIMER_IrqCompare0Clear(HAL_TIMER_x timer_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_TIMER[timer_x]->IF);
    HAL_REG_WRITE(*addr, TIMER0_IF_CH0_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param timer_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_TIMER_IrqCompare1(HAL_TIMER_x timer_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_TIMER[timer_x]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_TIMER[timer_x]->IF);
    if ((HAL_REG_READ_BIT(*addr_ie, TIMER0_IE_CH1_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, TIMER0_IF_CH1_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_TIMER_IrqCompare1 的区别是不判断中断使能）
 * @param timer_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_TIMER_IrqCompare1Flg(HAL_TIMER_x timer_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_TIMER[timer_x]->IF);
    if (HAL_REG_READ_BIT(*addr, TIMER0_IF_CH1_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param timer_x 模块编号
 */
void HAL_TIMER_IrqCompare1Enable(HAL_TIMER_x timer_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_TIMER[timer_x]->IE);
    HAL_REG_SET(*addr, TIMER0_IE_CH1_IE_BIT);
}

/**
 * @brief 中断禁止
 * @param timer_x 模块编号
 */
void HAL_TIMER_IrqCompare1Disable(HAL_TIMER_x timer_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_TIMER[timer_x]->IE);
    HAL_REG_RESET(*addr, TIMER0_IE_CH1_IE_BIT);
}

/**
 * @brief 中断清除
 * @param timer_x 模块编号
 */
void HAL_TIMER_IrqCompare1Clear(HAL_TIMER_x timer_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_TIMER[timer_x]->IF);
    HAL_REG_WRITE(*addr, TIMER0_IF_CH1_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param uart_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_UART_IrqTxDone(HAL_UART_x uart_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    if ((HAL_REG_READ_BIT(*addr_ie, UARTx_IE_TX_DONE_BIT)) && (HAL_REG_READ_BIT(*addr_if, UARTx_IF_TX_DONE_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_UART_IrqTxDone 的区别是不判断中断使能）
 * @param uart_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_UART_IrqTxDoneFlg(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    if (HAL_REG_READ_BIT(*addr, UARTx_IF_TX_DONE_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param uart_x 模块编号
 */
void HAL_UART_IrqTxDoneEnable(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    HAL_REG_SET(*addr, UARTx_IE_TX_DONE_BIT);
}

/**
 * @brief 中断禁止
 * @param uart_x 模块编号
 */
void HAL_UART_IrqTxDoneDisable(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    HAL_REG_RESET(*addr, UARTx_IE_TX_DONE_BIT);
}

/**
 * @brief 中断清除
 * @param uart_x 模块编号
 */
void HAL_UART_IrqTxDoneClear(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    HAL_REG_WRITE(*addr, UARTx_IF_TX_DONE_BIT);
}

/**
 * @brief 中断处理函数
 * @param uart_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_UART_IrqRxDone(HAL_UART_x uart_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    if ((HAL_REG_READ_BIT(*addr_ie, UARTx_IE_RX_DONE_BIT)) && (HAL_REG_READ_BIT(*addr_if, UARTx_IF_RX_DONE_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_UART_IrqRxDone 的区别是不判断中断使能）
 * @param uart_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_UART_IrqRxDoneFlg(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    if (HAL_REG_READ_BIT(*addr, UARTx_IF_RX_DONE_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param uart_x 模块编号
 */
void HAL_UART_IrqRxDoneEnable(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    HAL_REG_SET(*addr, UARTx_IE_RX_DONE_BIT);
}

/**
 * @brief 中断禁止
 * @param uart_x 模块编号
 */
void HAL_UART_IrqRxDoneDisable(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    HAL_REG_RESET(*addr, UARTx_IE_RX_DONE_BIT);
}

/**
 * @brief 中断清除
 * @param uart_x 模块编号
 */
void HAL_UART_IrqRxDoneClear(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    HAL_REG_WRITE(*addr, UARTx_IF_RX_DONE_BIT);
}

/**
 * @brief 中断处理函数
 * @param uart_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_UART_IrqStopErr(HAL_UART_x uart_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    if ((HAL_REG_READ_BIT(*addr_ie, UARTx_IE_STOP_ERR_BIT)) && (HAL_REG_READ_BIT(*addr_if, UARTx_IF_STOP_ERR_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_UART_IrqStopErr 的区别是不判断中断使能）
 * @param uart_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_UART_IrqStopErrFlg(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    if (HAL_REG_READ_BIT(*addr, UARTx_IF_STOP_ERR_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param uart_x 模块编号
 */
void HAL_UART_IrqStopErrEnable(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    HAL_REG_SET(*addr, UARTx_IE_STOP_ERR_BIT);
}

/**
 * @brief 中断禁止
 * @param uart_x 模块编号
 */
void HAL_UART_IrqStopErrDisable(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    HAL_REG_RESET(*addr, UARTx_IE_STOP_ERR_BIT);
}

/**
 * @brief 中断清除
 * @param uart_x 模块编号
 */
void HAL_UART_IrqStopErrClear(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    HAL_REG_WRITE(*addr, UARTx_IF_STOP_ERR_BIT);
}

/**
 * @brief 中断处理函数
 * @param uart_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_UART_IrqCheckErr(HAL_UART_x uart_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    if ((HAL_REG_READ_BIT(*addr_ie, UARTx_IE_CK_ERR_BIT)) && (HAL_REG_READ_BIT(*addr_if, UARTx_IF_CK_ERR_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_UART_IrqCheckErr 的区别是不判断中断使能）
 * @param uart_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_UART_IrqCheckErrFlg(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    if (HAL_REG_READ_BIT(*addr, UARTx_IF_CK_ERR_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param uart_x 模块编号
 */
void HAL_UART_IrqCheckErrEnable(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    HAL_REG_SET(*addr, UARTx_IE_CK_ERR_BIT);
}

/**
 * @brief 中断禁止
 * @param uart_x 模块编号
 */
void HAL_UART_IrqCheckErrDisable(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    HAL_REG_RESET(*addr, UARTx_IE_CK_ERR_BIT);
}

/**
 * @brief 中断清除
 * @param uart_x 模块编号
 */
void HAL_UART_IrqCheckErrClear(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    HAL_REG_WRITE(*addr, UARTx_IF_CK_ERR_BIT);
}

/**
 * @brief 中断处理函数
 * @param can_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_CAN_IrqRxDone(HAL_CAN_x can_x)
{
    volatile uint8_t *addr_if;
    volatile uint8_t *addr_ie;
    addr_ie = (volatile uint8_t *)HAL_REG_READ_ADDR(HAL_CAN[can_x]->RTIE);
    addr_if = (volatile uint8_t *)HAL_REG_READ_ADDR(HAL_CAN[can_x]->RTIF);
    if ((HAL_REG_READ_BIT(*addr_ie, CAN_RTIE_RIE_BIT)) && (HAL_REG_READ_BIT(*addr_if, CAN_RTIF_RIF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_CAN_IrqRxDone 的区别是不判断中断使能）
 * @param can_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_CAN_IrqRxDoneFlg(HAL_CAN_x can_x)
{
    volatile uint8_t *addr;
    addr = (volatile uint8_t *)HAL_REG_READ_ADDR(HAL_CAN[can_x]->RTIF);
    if (HAL_REG_READ_BIT(*addr, CAN_RTIF_RIF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param can_x 模块编号
 */
void HAL_CAN_IrqRxDoneEnable(HAL_CAN_x can_x)
{
    volatile uint8_t *addr;
    addr = (volatile uint8_t *)HAL_REG_READ_ADDR(HAL_CAN[can_x]->RTIE);
    HAL_REG_SET(*addr, CAN_RTIE_RIE_BIT);
}

/**
 * @brief 中断禁止
 * @param can_x 模块编号
 */
void HAL_CAN_IrqRxDoneDisable(HAL_CAN_x can_x)
{
    volatile uint8_t *addr;
    addr = (volatile uint8_t *)HAL_REG_READ_ADDR(HAL_CAN[can_x]->RTIE);
    HAL_REG_RESET(*addr, CAN_RTIE_RIE_BIT);
}

/**
 * @brief 中断清除
 * @param can_x 模块编号
 */
void HAL_CAN_IrqRxDoneClear(HAL_CAN_x can_x)
{
    volatile uint8_t *addr;
    addr = (volatile uint8_t *)HAL_REG_READ_ADDR(HAL_CAN[can_x]->RTIF);
    HAL_REG_WRITE(*addr, CAN_RTIF_RIF_BIT);
}

/**
 * @brief 中断处理函数
 * @param can_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_CAN_IrqTxDone(HAL_CAN_x can_x)
{
    volatile uint8_t *addr_if;
    volatile uint8_t *addr_ie;
    addr_ie = (volatile uint8_t *)HAL_REG_READ_ADDR(HAL_CAN[can_x]->RTIE);
    addr_if = (volatile uint8_t *)HAL_REG_READ_ADDR(HAL_CAN[can_x]->RTIF);
    if ((HAL_REG_READ_BIT(*addr_ie, CAN_RTIE_TPIE_BIT | CAN_RTIE_TSIE_BIT)) && (HAL_REG_READ_BIT(*addr_if, CAN_RTIF_TPIF_BIT | CAN_RTIF_TSIF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_CAN_IrqTxDone 的区别是不判断中断使能）
 * @param can_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_CAN_IrqTxDoneFlg(HAL_CAN_x can_x)
{
    volatile uint8_t *addr;
    addr = (volatile uint8_t *)HAL_REG_READ_ADDR(HAL_CAN[can_x]->RTIF);
    if (HAL_REG_READ_BIT(*addr, CAN_RTIF_TPIF_BIT | CAN_RTIF_TSIF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param can_x 模块编号
 */
void HAL_CAN_IrqTxDoneEnable(HAL_CAN_x can_x)
{
    volatile uint8_t *addr;
    addr = (volatile uint8_t *)HAL_REG_READ_ADDR(HAL_CAN[can_x]->RTIE);
    HAL_REG_SET(*addr, CAN_RTIE_TPIE_BIT | CAN_RTIE_TSIE_BIT);
}

/**
 * @brief 中断禁止
 * @param can_x 模块编号
 */
void HAL_CAN_IrqTxDoneDisable(HAL_CAN_x can_x)
{
    volatile uint8_t *addr;
    addr = (volatile uint8_t *)HAL_REG_READ_ADDR(HAL_CAN[can_x]->RTIE);
    HAL_REG_RESET(*addr, CAN_RTIE_TPIE_BIT | CAN_RTIE_TSIE_BIT);
}

/**
 * @brief 中断清除
 * @param can_x 模块编号
 */
void HAL_CAN_IrqTxDoneClear(HAL_CAN_x can_x)
{
    volatile uint8_t *addr;
    addr = (volatile uint8_t *)HAL_REG_READ_ADDR(HAL_CAN[can_x]->RTIF);
    HAL_REG_WRITE(*addr, CAN_RTIF_TPIF_BIT | CAN_RTIF_TSIF_BIT);
}

/**
 * @brief 中断处理函数
 * @param can_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_CAN_IrqAll(HAL_CAN_x can_x)
{
    volatile uint8_t *addr_if;
    volatile uint8_t *addr_ie;
    addr_ie = (volatile uint8_t *)HAL_REG_READ_ADDR(HAL_CAN[can_x]->RTIE);
    addr_if = (volatile uint8_t *)HAL_REG_READ_ADDR(HAL_CAN[can_x]->RTIF);
    if ((HAL_REG_READ_BIT(*addr_ie, CAN_RTIE_RIE_BIT | CAN_RTIE_ROIE_BIT | CAN_RTIE_RFIE_BIT | CAN_RTIE_RAFIE_BIT | CAN_RTIE_TPIE_BIT | CAN_RTIE_TSIE_BIT | CAN_RTIE_EIE_BIT | CAN_RTIE_TSFF_BIT)) && (HAL_REG_READ_BIT(*addr_if, CAN_RTIF_RIF_BIT | CAN_RTIF_ROIF_BIT | CAN_RTIF_RFIF_BIT | CAN_RTIF_RAFIF_BIT | CAN_RTIF_TPIF_BIT | CAN_RTIF_TSIF_BIT | CAN_RTIF_EIF_BIT | CAN_RTIF_AIF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_CAN_IrqAll 的区别是不判断中断使能）
 * @param can_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_CAN_IrqAllFlg(HAL_CAN_x can_x)
{
    volatile uint8_t *addr;
    addr = (volatile uint8_t *)HAL_REG_READ_ADDR(HAL_CAN[can_x]->RTIF);
    if (HAL_REG_READ_BIT(*addr, CAN_RTIF_RIF_BIT | CAN_RTIF_ROIF_BIT | CAN_RTIF_RFIF_BIT | CAN_RTIF_RAFIF_BIT | CAN_RTIF_TPIF_BIT | CAN_RTIF_TSIF_BIT | CAN_RTIF_EIF_BIT | CAN_RTIF_AIF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param can_x 模块编号
 */
void HAL_CAN_IrqAllEnable(HAL_CAN_x can_x)
{
    volatile uint8_t *addr;
    addr = (volatile uint8_t *)HAL_REG_READ_ADDR(HAL_CAN[can_x]->RTIE);
    HAL_REG_SET(*addr, CAN_RTIE_RIE_BIT | CAN_RTIE_ROIE_BIT | CAN_RTIE_RFIE_BIT | CAN_RTIE_RAFIE_BIT | CAN_RTIE_TPIE_BIT | CAN_RTIE_TSIE_BIT | CAN_RTIE_EIE_BIT | CAN_RTIE_TSFF_BIT);
}

/**
 * @brief 中断禁止
 * @param can_x 模块编号
 */
void HAL_CAN_IrqAllDisable(HAL_CAN_x can_x)
{
    volatile uint8_t *addr;
    addr = (volatile uint8_t *)HAL_REG_READ_ADDR(HAL_CAN[can_x]->RTIE);
    HAL_REG_RESET(*addr, CAN_RTIE_RIE_BIT | CAN_RTIE_ROIE_BIT | CAN_RTIE_RFIE_BIT | CAN_RTIE_RAFIE_BIT | CAN_RTIE_TPIE_BIT | CAN_RTIE_TSIE_BIT | CAN_RTIE_EIE_BIT | CAN_RTIE_TSFF_BIT);
}

/**
 * @brief 中断清除
 * @param can_x 模块编号
 */
void HAL_CAN_IrqAllClear(HAL_CAN_x can_x)
{
    volatile uint8_t *addr;
    addr = (volatile uint8_t *)HAL_REG_READ_ADDR(HAL_CAN[can_x]->RTIF);
    HAL_REG_WRITE(*addr, CAN_RTIF_RIF_BIT | CAN_RTIF_ROIF_BIT | CAN_RTIF_RFIF_BIT | CAN_RTIF_RAFIF_BIT | CAN_RTIF_TPIF_BIT | CAN_RTIF_TSIF_BIT | CAN_RTIF_EIF_BIT | CAN_RTIF_AIF_BIT);
}

/**
 * @brief 中断处理函数
 * @param uart_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_UART_IrqTxBufEmpty(HAL_UART_x uart_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    if ((HAL_REG_READ_BIT(*addr_ie, UARTx_IE_TX_BUF_EMPTY_BIT)) && (HAL_REG_READ_BIT(*addr_if, UARTx_IF_TX_BUF_EMPTY_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_UART_IrqTxBufEmpty 的区别是不判断中断使能）
 * @param uart_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_UART_IrqTxBufEmptyFlg(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    if (HAL_REG_READ_BIT(*addr, UARTx_IF_TX_BUF_EMPTY_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param uart_x 模块编号
 */
void HAL_UART_IrqTxBufEmptyEnable(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    HAL_REG_SET(*addr, UARTx_IE_TX_BUF_EMPTY_BIT);
}

/**
 * @brief 中断禁止
 * @param uart_x 模块编号
 */
void HAL_UART_IrqTxBufEmptyDisable(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    HAL_REG_RESET(*addr, UARTx_IE_TX_BUF_EMPTY_BIT);
}

/**
 * @brief 中断清除
 * @param uart_x 模块编号
 */
void HAL_UART_IrqTxBufEmptyClear(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    HAL_REG_WRITE(*addr, UARTx_IF_TX_BUF_EMPTY_BIT);
}

/**
 * @brief 中断处理函数
 * @param uart_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_UART_IrqTxOv(HAL_UART_x uart_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    if ((HAL_REG_READ_BIT(*addr_ie, UARTx_IE_TX_OV_BIT)) && (HAL_REG_READ_BIT(*addr_if, UARTx_IF_TX_OV_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_UART_IrqTxOv 的区别是不判断中断使能）
 * @param uart_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_UART_IrqTxOvFlg(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    if (HAL_REG_READ_BIT(*addr, UARTx_IF_TX_OV_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param uart_x 模块编号
 */
void HAL_UART_IrqTxOvEnable(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    HAL_REG_SET(*addr, UARTx_IE_TX_OV_BIT);
}

/**
 * @brief 中断禁止
 * @param uart_x 模块编号
 */
void HAL_UART_IrqTxOvDisable(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    HAL_REG_RESET(*addr, UARTx_IE_TX_OV_BIT);
}

/**
 * @brief 中断清除
 * @param uart_x 模块编号
 */
void HAL_UART_IrqTxOvClear(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    HAL_REG_WRITE(*addr, UARTx_IF_TX_OV_BIT);
}

/**
 * @brief 中断处理函数
 * @param uart_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_UART_IrqRxOv(HAL_UART_x uart_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    if ((HAL_REG_READ_BIT(*addr_ie, UARTx_IE_RX_OV_BIT)) && (HAL_REG_READ_BIT(*addr_if, UARTx_IF_RX_OV_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_UART_IrqRxOv 的区别是不判断中断使能）
 * @param uart_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_UART_IrqRxOvFlg(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    if (HAL_REG_READ_BIT(*addr, UARTx_IF_RX_OV_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param uart_x 模块编号
 */
void HAL_UART_IrqRxOvEnable(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    HAL_REG_SET(*addr, UARTx_IE_RX_OV_BIT);
}

/**
 * @brief 中断禁止
 * @param uart_x 模块编号
 */
void HAL_UART_IrqRxOvDisable(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    HAL_REG_RESET(*addr, UARTx_IE_RX_OV_BIT);
}

/**
 * @brief 中断清除
 * @param uart_x 模块编号
 */
void HAL_UART_IrqRxOvClear(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    HAL_REG_WRITE(*addr, UARTx_IF_RX_OV_BIT);
}

/**
 * @brief 中断处理函数
 * @param uart_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_UART_IrqLbd(HAL_UART_x uart_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    if ((HAL_REG_READ_BIT(*addr_ie, UARTx_IE_LBD_BIT)) && (HAL_REG_READ_BIT(*addr_if, UARTx_IF_LBD_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_UART_IrqLbd 的区别是不判断中断使能）
 * @param uart_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_UART_IrqLbdFlg(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    if (HAL_REG_READ_BIT(*addr, UARTx_IF_LBD_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param uart_x 模块编号
 */
void HAL_UART_IrqLbdEnable(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    HAL_REG_SET(*addr, UARTx_IE_LBD_BIT);
}

/**
 * @brief 中断禁止
 * @param uart_x 模块编号
 */
void HAL_UART_IrqLbdDisable(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    HAL_REG_RESET(*addr, UARTx_IE_LBD_BIT);
}

/**
 * @brief 中断清除
 * @param uart_x 模块编号
 */
void HAL_UART_IrqLbdClear(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    HAL_REG_WRITE(*addr, UARTx_IF_LBD_BIT);
}

/**
 * @brief 中断处理函数
 * @param uart_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_UART_IrqIdle(HAL_UART_x uart_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    if ((HAL_REG_READ_BIT(*addr_ie, UARTx_IE_IDLE_BIT)) && (HAL_REG_READ_BIT(*addr_if, UARTx_IF_IDLE_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_UART_IrqIdle 的区别是不判断中断使能）
 * @param uart_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_UART_IrqIdleFlg(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    if (HAL_REG_READ_BIT(*addr, UARTx_IF_IDLE_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param uart_x 模块编号
 */
void HAL_UART_IrqIdleEnable(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    HAL_REG_SET(*addr, UARTx_IE_IDLE_BIT);
}

/**
 * @brief 中断禁止
 * @param uart_x 模块编号
 */
void HAL_UART_IrqIdleDisable(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IE);
    HAL_REG_RESET(*addr, UARTx_IE_IDLE_BIT);
}

/**
 * @brief 中断清除
 * @param uart_x 模块编号
 */
void HAL_UART_IrqIdleClear(HAL_UART_x uart_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_UART[uart_x]->IF);
    HAL_REG_WRITE(*addr, UARTx_IF_IDLE_BIT);
}

/**
 * @brief 中断处理函数
 * @param adc 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_ADC_IrqWatchdog(HAL_ADC_x adc)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IF);
    if ((HAL_REG_READ_BIT(*addr_ie, ADCx_IE_AWD0_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, ADCx_IF_AWD0_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_ADC_IrqWatchdog 的区别是不判断中断使能）
 * @param adc 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_ADC_IrqWatchdogFlg(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IF);
    if (HAL_REG_READ_BIT(*addr, ADCx_IF_AWD0_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param adc 模块编号
 */
void HAL_ADC_IrqWatchdogEnable(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IE);
    HAL_REG_SET(*addr, ADCx_IE_AWD0_IE_BIT);
}

/**
 * @brief 中断禁止
 * @param adc 模块编号
 */
void HAL_ADC_IrqWatchdogDisable(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IE);
    HAL_REG_RESET(*addr, ADCx_IE_AWD0_IE_BIT);
}

/**
 * @brief 中断清除
 * @param adc 模块编号
 */
void HAL_ADC_IrqWatchdogClear(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IF);
    HAL_REG_WRITE(*addr, ADCx_IF_AWD0_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param adc 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_ADC_IrqHardErr(HAL_ADC_x adc)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IF);
    if ((HAL_REG_READ_BIT(*addr_ie, ADCx_IE_HERR_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, ADCx_IF_HERR_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_ADC_IrqHardErr 的区别是不判断中断使能）
 * @param adc 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_ADC_IrqHardErrFlg(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IF);
    if (HAL_REG_READ_BIT(*addr, ADCx_IF_HERR_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param adc 模块编号
 */
void HAL_ADC_IrqHardErrEnable(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IE);
    HAL_REG_SET(*addr, ADCx_IE_HERR_IE_BIT);
}

/**
 * @brief 中断禁止
 * @param adc 模块编号
 */
void HAL_ADC_IrqHardErrDisable(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IE);
    HAL_REG_RESET(*addr, ADCx_IE_HERR_IE_BIT);
}

/**
 * @brief 中断清除
 * @param adc 模块编号
 */
void HAL_ADC_IrqHardErrClear(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IF);
    HAL_REG_WRITE(*addr, ADCx_IF_HERR_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param adc 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_ADC_IrqSoftErr(HAL_ADC_x adc)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IF);
    if ((HAL_REG_READ_BIT(*addr_ie, ADCx_IE_SERR_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, ADCx_IF_SERR_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_ADC_IrqSoftErr 的区别是不判断中断使能）
 * @param adc 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_ADC_IrqSoftErrFlg(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IF);
    if (HAL_REG_READ_BIT(*addr, ADCx_IF_SERR_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param adc 模块编号
 */
void HAL_ADC_IrqSoftErrEnable(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IE);
    HAL_REG_SET(*addr, ADCx_IE_SERR_IE_BIT);
}

/**
 * @brief 中断禁止
 * @param adc 模块编号
 */
void HAL_ADC_IrqSoftErrDisable(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IE);
    HAL_REG_RESET(*addr, ADCx_IE_SERR_IE_BIT);
}

/**
 * @brief 中断清除
 * @param adc 模块编号
 */
void HAL_ADC_IrqSoftErrClear(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IF);
    HAL_REG_WRITE(*addr, ADCx_IF_SERR_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param adc 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_ADC_IrqIdleSamp(HAL_ADC_x adc)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IF);
    if ((HAL_REG_READ_BIT(*addr_ie, ADCx_IE_ISF_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, ADCx_IF_ISF_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_ADC_IrqIdleSamp 的区别是不判断中断使能）
 * @param adc 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_ADC_IrqIdleSampFlg(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IF);
    if (HAL_REG_READ_BIT(*addr, ADCx_IF_ISF_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param adc 模块编号
 */
void HAL_ADC_IrqIdleSampEnable(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IE);
    HAL_REG_SET(*addr, ADCx_IE_ISF_IE_BIT);
}

/**
 * @brief 中断禁止
 * @param adc 模块编号
 */
void HAL_ADC_IrqIdleSampDisable(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IE);
    HAL_REG_RESET(*addr, ADCx_IE_ISF_IE_BIT);
}

/**
 * @brief 中断清除
 * @param adc 模块编号
 */
void HAL_ADC_IrqIdleSampClear(HAL_ADC_x adc)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_ADC[adc]->IF);
    HAL_REG_WRITE(*addr, ADCx_IF_ISF_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqUpdate(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    addr_if = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    if ((HAL_REG_READ_BIT(*addr_ie, MCPWM0_IE0_UP_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, MCPWM0_IF0_UP_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqUpdate 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqUpdateFlg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    if (HAL_REG_READ_BIT(*addr, MCPWM0_IF0_UP_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqUpdateEnable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, MCPWM0_IE0_UP_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqUpdateDisable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, MCPWM0_IE0_UP_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqUpdateClear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    HAL_REG_WRITE(*addr, MCPWM0_IF0_UP_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTmr0(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    addr_if = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    if ((HAL_REG_READ_BIT(*addr_ie, MCPWM0_IE0_TMR0_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, MCPWM0_IF0_TMR0_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqTmr0 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTmr0Flg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    if (HAL_REG_READ_BIT(*addr, MCPWM0_IF0_TMR0_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTmr0Enable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, MCPWM0_IE0_TMR0_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTmr0Disable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, MCPWM0_IE0_TMR0_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTmr0Clear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    HAL_REG_WRITE(*addr, MCPWM0_IF0_TMR0_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTmr1(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    addr_if = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    if ((HAL_REG_READ_BIT(*addr_ie, MCPWM0_IE0_TMR1_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, MCPWM0_IF0_TMR1_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqTmr1 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTmr1Flg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    if (HAL_REG_READ_BIT(*addr, MCPWM0_IF0_TMR1_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTmr1Enable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, MCPWM0_IE0_TMR1_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTmr1Disable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, MCPWM0_IE0_TMR1_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTmr1Clear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    HAL_REG_WRITE(*addr, MCPWM0_IF0_TMR1_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTmr2(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    addr_if = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    if ((HAL_REG_READ_BIT(*addr_ie, MCPWM0_IE0_TMR2_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, MCPWM0_IF0_TMR2_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqTmr2 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTmr2Flg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    if (HAL_REG_READ_BIT(*addr, MCPWM0_IF0_TMR2_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTmr2Enable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, MCPWM0_IE0_TMR2_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTmr2Disable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, MCPWM0_IE0_TMR2_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTmr2Clear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    HAL_REG_WRITE(*addr, MCPWM0_IF0_TMR2_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTmr3(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    addr_if = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    if ((HAL_REG_READ_BIT(*addr_ie, MCPWM0_IE0_TMR3_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, MCPWM0_IF0_TMR3_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqTmr3 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTmr3Flg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    if (HAL_REG_READ_BIT(*addr, MCPWM0_IF0_TMR3_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTmr3Enable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, MCPWM0_IE0_TMR3_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTmr3Disable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1));
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, MCPWM0_IE0_TMR3_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTmr3Clear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)(((mcpwmx & 0xf0) == 0) ? HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0) : HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1));
    HAL_REG_WRITE(*addr, MCPWM0_IF0_TMR3_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH00(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0);
    if ((HAL_REG_READ_BIT(*addr_ie, MCPWM0_IE0_TH00_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, MCPWM0_IF0_TH00_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqTH00 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH00Flg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0);
    if (HAL_REG_READ_BIT(*addr, MCPWM0_IF0_TH00_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH00Enable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, MCPWM0_IE0_TH00_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH00Disable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, MCPWM0_IE0_TH00_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH00Clear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0);
    HAL_REG_WRITE(*addr, MCPWM0_IF0_TH00_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH01(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0);
    if ((HAL_REG_READ_BIT(*addr_ie, MCPWM0_IE0_TH01_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, MCPWM0_IF0_TH01_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqTH01 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH01Flg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0);
    if (HAL_REG_READ_BIT(*addr, MCPWM0_IF0_TH01_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH01Enable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, MCPWM0_IE0_TH01_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH01Disable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, MCPWM0_IE0_TH01_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH01Clear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0);
    HAL_REG_WRITE(*addr, MCPWM0_IF0_TH01_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH10(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0);
    if ((HAL_REG_READ_BIT(*addr_ie, MCPWM0_IE0_TH10_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, MCPWM0_IF0_TH10_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqTH10 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH10Flg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0);
    if (HAL_REG_READ_BIT(*addr, MCPWM0_IF0_TH10_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH10Enable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, MCPWM0_IE0_TH10_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH10Disable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, MCPWM0_IE0_TH10_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH10Clear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0);
    HAL_REG_WRITE(*addr, MCPWM0_IF0_TH10_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH11(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0);
    if ((HAL_REG_READ_BIT(*addr_ie, MCPWM0_IE0_TH11_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, MCPWM0_IF0_TH11_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqTH11 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH11Flg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0);
    if (HAL_REG_READ_BIT(*addr, MCPWM0_IF0_TH11_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH11Enable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, MCPWM0_IE0_TH11_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH11Disable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, MCPWM0_IE0_TH11_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH11Clear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0);
    HAL_REG_WRITE(*addr, MCPWM0_IF0_TH11_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH20(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0);
    if ((HAL_REG_READ_BIT(*addr_ie, MCPWM0_IE0_TH20_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, MCPWM0_IF0_TH20_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqTH20 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH20Flg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0);
    if (HAL_REG_READ_BIT(*addr, MCPWM0_IF0_TH20_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH20Enable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, MCPWM0_IE0_TH20_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH20Disable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, MCPWM0_IE0_TH20_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH20Clear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0);
    HAL_REG_WRITE(*addr, MCPWM0_IF0_TH20_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH21(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0);
    if ((HAL_REG_READ_BIT(*addr_ie, MCPWM0_IE0_TH21_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, MCPWM0_IF0_TH21_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqTH21 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH21Flg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0);
    if (HAL_REG_READ_BIT(*addr, MCPWM0_IF0_TH21_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH21Enable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, MCPWM0_IE0_TH21_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH21Disable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE0);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, MCPWM0_IE0_TH21_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH21Clear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF0);
    HAL_REG_WRITE(*addr, MCPWM0_IF0_TH21_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH30(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1);
    if ((HAL_REG_READ_BIT(*addr_ie, MCPWM0_IE1_TH30_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, MCPWM0_IF1_TH30_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqTH30 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH30Flg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1);
    if (HAL_REG_READ_BIT(*addr, MCPWM0_IF1_TH30_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH30Enable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, MCPWM0_IE1_TH30_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH30Disable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, MCPWM0_IE1_TH30_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH30Clear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1);
    HAL_REG_WRITE(*addr, MCPWM0_IF1_TH30_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH31(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1);
    if ((HAL_REG_READ_BIT(*addr_ie, MCPWM0_IE1_TH31_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, MCPWM0_IF1_TH31_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqTH31 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH31Flg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1);
    if (HAL_REG_READ_BIT(*addr, MCPWM0_IF1_TH31_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH31Enable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, MCPWM0_IE1_TH31_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH31Disable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, MCPWM0_IE1_TH31_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH31Clear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1);
    HAL_REG_WRITE(*addr, MCPWM0_IF1_TH31_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH40(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1);
    if ((HAL_REG_READ_BIT(*addr_ie, MCPWM0_IE1_TH40_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, MCPWM0_IF1_TH40_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqTH40 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH40Flg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1);
    if (HAL_REG_READ_BIT(*addr, MCPWM0_IF1_TH40_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH40Enable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, MCPWM0_IE1_TH40_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH40Disable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, MCPWM0_IE1_TH40_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH40Clear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1);
    HAL_REG_WRITE(*addr, MCPWM0_IF1_TH40_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH41(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1);
    if ((HAL_REG_READ_BIT(*addr_ie, MCPWM0_IE1_TH41_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, MCPWM0_IF1_TH41_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqTH41 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH41Flg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1);
    if (HAL_REG_READ_BIT(*addr, MCPWM0_IF1_TH41_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH41Enable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, MCPWM0_IE1_TH41_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH41Disable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, MCPWM0_IE1_TH41_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH41Clear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1);
    HAL_REG_WRITE(*addr, MCPWM0_IF1_TH41_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH50(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1);
    if ((HAL_REG_READ_BIT(*addr_ie, MCPWM0_IE1_TH50_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, MCPWM0_IF1_TH50_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqTH50 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH50Flg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1);
    if (HAL_REG_READ_BIT(*addr, MCPWM0_IF1_TH50_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH50Enable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, MCPWM0_IE1_TH50_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH50Disable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, MCPWM0_IE1_TH50_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH50Clear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1);
    HAL_REG_WRITE(*addr, MCPWM0_IF1_TH50_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH51(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1);
    if ((HAL_REG_READ_BIT(*addr_ie, MCPWM0_IE1_TH51_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, MCPWM0_IF1_TH51_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_MCPWM_IrqTH51 的区别是不判断中断使能）
 * @param mcpwmx 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_MCPWM_IrqTH51Flg(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1);
    if (HAL_REG_READ_BIT(*addr, MCPWM0_IF1_TH51_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH51Enable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_SET(*addr, MCPWM0_IE1_TH51_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断禁止
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH51Disable(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IE1);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0xDEAD);
    HAL_REG_RESET(*addr, MCPWM0_IE1_TH51_IE_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwmx & 0xf]->PRT, 0);
}

/**
 * @brief 中断清除
 * @param mcpwmx 模块编号
 */
void HAL_MCPWM_IrqTH51Clear(HAL_MCPWM_x mcpwmx)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_MCPWM[mcpwmx & 0xf]->IF1);
    HAL_REG_WRITE(*addr, MCPWM0_IF1_TH51_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param i2c_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_I2C_IrqDone(HAL_I2C_x i2c_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_I2C[i2c_x]->CFG);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_I2C[i2c_x]->SCR);
    if ((HAL_REG_READ_BIT(*addr_ie, I2C0_CFG_IE_BIT | I2C0_CFG_TC_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, I2C0_SCR_Done_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_I2C_IrqDone 的区别是不判断中断使能）
 * @param i2c_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_I2C_IrqDoneFlg(HAL_I2C_x i2c_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_I2C[i2c_x]->SCR);
    if (HAL_REG_READ_BIT(*addr, I2C0_SCR_Done_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param i2c_x 模块编号
 */
void HAL_I2C_IrqDoneEnable(HAL_I2C_x i2c_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_I2C[i2c_x]->CFG);
    HAL_REG_SET(*addr, I2C0_CFG_IE_BIT | I2C0_CFG_TC_IE_BIT);
}

/**
 * @brief 中断禁止
 * @param i2c_x 模块编号
 */
void HAL_I2C_IrqDoneDisable(HAL_I2C_x i2c_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_I2C[i2c_x]->CFG);
    HAL_REG_RESET(*addr, I2C0_CFG_TC_IE_BIT);
}

/**
 * @brief 中断清除
 * @param i2c_x 模块编号
 */
void HAL_I2C_IrqDoneClear(HAL_I2C_x i2c_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_I2C[i2c_x]->SCR);
    HAL_REG_RESET(*addr, I2C0_SCR_Done_BIT);
}

/**
 * @brief 中断处理函数
 * @param i2c_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_I2C_IrqBusErr(HAL_I2C_x i2c_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_I2C[i2c_x]->CFG);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_I2C[i2c_x]->SCR);
    if ((HAL_REG_READ_BIT(*addr_ie, I2C0_CFG_IE_BIT | I2C0_CFG_BUS_ERR_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, I2C0_SCR_STT_ERR_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_I2C_IrqBusErr 的区别是不判断中断使能）
 * @param i2c_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_I2C_IrqBusErrFlg(HAL_I2C_x i2c_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_I2C[i2c_x]->SCR);
    if (HAL_REG_READ_BIT(*addr, I2C0_SCR_STT_ERR_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param i2c_x 模块编号
 */
void HAL_I2C_IrqBusErrEnable(HAL_I2C_x i2c_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_I2C[i2c_x]->CFG);
    HAL_REG_SET(*addr, I2C0_CFG_IE_BIT | I2C0_CFG_BUS_ERR_IE_BIT);
}

/**
 * @brief 中断禁止
 * @param i2c_x 模块编号
 */
void HAL_I2C_IrqBusErrDisable(HAL_I2C_x i2c_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_I2C[i2c_x]->CFG);
    HAL_REG_RESET(*addr, I2C0_CFG_BUS_ERR_IE_BIT);
}

/**
 * @brief 中断清除
 * @param i2c_x 模块编号
 */
void HAL_I2C_IrqBusErrClear(HAL_I2C_x i2c_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_I2C[i2c_x]->SCR);
    HAL_REG_RESET(*addr, I2C0_SCR_STT_ERR_BIT);
}

/**
 * @brief 中断处理函数
 * @param i2c_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_I2C_IrqStop(HAL_I2C_x i2c_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_I2C[i2c_x]->CFG);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_I2C[i2c_x]->SCR);
    if ((HAL_REG_READ_BIT(*addr_ie, I2C0_CFG_IE_BIT | I2C0_CFG_STOP_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, I2C0_SCR_STOP_EVT_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_I2C_IrqStop 的区别是不判断中断使能）
 * @param i2c_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_I2C_IrqStopFlg(HAL_I2C_x i2c_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_I2C[i2c_x]->SCR);
    if (HAL_REG_READ_BIT(*addr, I2C0_SCR_STOP_EVT_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param i2c_x 模块编号
 */
void HAL_I2C_IrqStopEnable(HAL_I2C_x i2c_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_I2C[i2c_x]->CFG);
    HAL_REG_SET(*addr, I2C0_CFG_IE_BIT | I2C0_CFG_STOP_IE_BIT);
}

/**
 * @brief 中断禁止
 * @param i2c_x 模块编号
 */
void HAL_I2C_IrqStopDisable(HAL_I2C_x i2c_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_I2C[i2c_x]->CFG);
    HAL_REG_RESET(*addr, I2C0_CFG_STOP_IE_BIT);
}

/**
 * @brief 中断清除
 * @param i2c_x 模块编号
 */
void HAL_I2C_IrqStopClear(HAL_I2C_x i2c_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_I2C[i2c_x]->SCR);
    HAL_REG_RESET(*addr, I2C0_SCR_STOP_EVT_BIT);
}

/**
 * @brief 中断处理函数
 * @param spi_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_SPI_IrqDone(HAL_SPI_x spi_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SPI[spi_x]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SPI[spi_x]->IE);
    if ((HAL_REG_READ_BIT(*addr_ie, SPI0_IE_IE_BIT | SPI0_IE_CMPLT_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, SPI0_IE_CMPLT_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_SPI_IrqDone 的区别是不判断中断使能）
 * @param spi_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_SPI_IrqDoneFlg(HAL_SPI_x spi_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SPI[spi_x]->IE);
    if (HAL_REG_READ_BIT(*addr, SPI0_IE_CMPLT_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param spi_x 模块编号
 */
void HAL_SPI_IrqDoneEnable(HAL_SPI_x spi_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SPI[spi_x]->IE);
    HAL_REG_SET(*addr, SPI0_IE_IE_BIT | SPI0_IE_CMPLT_IE_BIT);
}

/**
 * @brief 中断禁止
 * @param spi_x 模块编号
 */
void HAL_SPI_IrqDoneDisable(HAL_SPI_x spi_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SPI[spi_x]->IE);
    HAL_REG_RESET(*addr, SPI0_IE_CMPLT_IE_BIT);
}

/**
 * @brief 中断清除
 * @param spi_x 模块编号
 */
void HAL_SPI_IrqDoneClear(HAL_SPI_x spi_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SPI[spi_x]->IE);
    HAL_REG_SET(*addr, SPI0_IE_CMPLT_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param spi_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_SPI_IrqErr(HAL_SPI_x spi_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SPI[spi_x]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SPI[spi_x]->IE);
    if ((HAL_REG_READ_BIT(*addr_ie, SPI0_IE_IE_BIT | SPI0_IE_AB_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, SPI0_IE_AB_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_SPI_IrqErr 的区别是不判断中断使能）
 * @param spi_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_SPI_IrqErrFlg(HAL_SPI_x spi_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SPI[spi_x]->IE);
    if (HAL_REG_READ_BIT(*addr, SPI0_IE_AB_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param spi_x 模块编号
 */
void HAL_SPI_IrqErrEnable(HAL_SPI_x spi_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SPI[spi_x]->IE);
    HAL_REG_SET(*addr, SPI0_IE_IE_BIT | SPI0_IE_AB_IE_BIT);
}

/**
 * @brief 中断禁止
 * @param spi_x 模块编号
 */
void HAL_SPI_IrqErrDisable(HAL_SPI_x spi_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SPI[spi_x]->IE);
    HAL_REG_RESET(*addr, SPI0_IE_AB_IE_BIT);
}

/**
 * @brief 中断清除
 * @param spi_x 模块编号
 */
void HAL_SPI_IrqErrClear(HAL_SPI_x spi_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SPI[spi_x]->IE);
    HAL_REG_SET(*addr, SPI0_IE_AB_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param spi_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_SPI_IrqOverflow(HAL_SPI_x spi_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SPI[spi_x]->IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SPI[spi_x]->IE);
    if ((HAL_REG_READ_BIT(*addr_ie, SPI0_IE_IE_BIT | SPI0_IE_OV_IE_BIT)) && (HAL_REG_READ_BIT(*addr_if, SPI0_IE_OV_IF_BIT)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_SPI_IrqOverflow 的区别是不判断中断使能）
 * @param spi_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_SPI_IrqOverflowFlg(HAL_SPI_x spi_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SPI[spi_x]->IE);
    if (HAL_REG_READ_BIT(*addr, SPI0_IE_OV_IF_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param spi_x 模块编号
 */
void HAL_SPI_IrqOverflowEnable(HAL_SPI_x spi_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SPI[spi_x]->IE);
    HAL_REG_SET(*addr, SPI0_IE_IE_BIT | SPI0_IE_OV_IE_BIT);
}

/**
 * @brief 中断禁止
 * @param spi_x 模块编号
 */
void HAL_SPI_IrqOverflowDisable(HAL_SPI_x spi_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SPI[spi_x]->IE);
    HAL_REG_RESET(*addr, SPI0_IE_OV_IE_BIT);
}

/**
 * @brief 中断清除
 * @param spi_x 模块编号
 */
void HAL_SPI_IrqOverflowClear(HAL_SPI_x spi_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SPI[spi_x]->IE);
    HAL_REG_SET(*addr, SPI0_IE_OV_IF_BIT);
}

/**
 * @brief 中断处理函数
 * @param dma_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_DMA_IrqDone(HAL_DMA_x dma_x)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(DMA0_IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(DMA0_IF);
    if ((HAL_REG_READ_BIT(*addr_ie, DMA0_IE_CH0_FIE_BIT << (dma_x))) && (HAL_REG_READ_BIT(*addr_if, DMA0_IF_CH0_FIF_BIT << (dma_x))))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_DMA_IrqDone 的区别是不判断中断使能）
 * @param dma_x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_DMA_IrqDoneFlg(HAL_DMA_x dma_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(DMA0_IF);
    if (HAL_REG_READ_BIT(*addr, DMA0_IF_CH0_FIF_BIT << (dma_x)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param dma_x 模块编号
 */
void HAL_DMA_IrqDoneEnable(HAL_DMA_x dma_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(DMA0_IE);
    HAL_REG_SET(*addr, DMA0_IE_CH0_FIE_BIT << (dma_x));
}

/**
 * @brief 中断禁止
 * @param dma_x 模块编号
 */
void HAL_DMA_IrqDoneDisable(HAL_DMA_x dma_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(DMA0_IE);
    HAL_REG_RESET(*addr, DMA0_IE_CH0_FIE_BIT << (dma_x));
}

/**
 * @brief 中断清除
 * @param dma_x 模块编号
 */
void HAL_DMA_IrqDoneClear(HAL_DMA_x dma_x)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(DMA0_IF);
    HAL_REG_WRITE(*addr, DMA0_IF_CH0_FIF_BIT << (dma_x));
}

/**
 * @brief 中断处理函数
 * @param line 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_GPIO_Irq(uint8_t line)
{
    volatile uint32_t *addr_if;
    volatile uint32_t *addr_ie;
    addr_ie = (volatile uint32_t *)HAL_REG_READ_ADDR(EXTI_IE);
    addr_if = (volatile uint32_t *)HAL_REG_READ_ADDR(EXTI_IF);
    if ((HAL_REG_READ_BIT(*addr_ie, ((line) < 8 ? EXTI_IE_EXTI0_IE_BIT : ((line) < 11 ? EXTI_IE_EXTI1_IE_BIT : EXTI_IE_EXTI2_IE_BIT)))) && (HAL_REG_READ_BIT(*addr_if, EXTI_IF_IF0_BIT << (line))))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（和 HAL_GPIO_Irq 的区别是不判断中断使能）
 * @param line 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_GPIO_IrqFlg(uint8_t line)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(EXTI_IF);
    if (HAL_REG_READ_BIT(*addr, EXTI_IF_IF0_BIT << (line)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能
 * @param line 模块编号
 */
void HAL_GPIO_IrqEnable(uint8_t line)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(EXTI_IE);
    HAL_REG_SET(*addr, ((line) < 8 ? EXTI_IE_EXTI0_IE_BIT : ((line) < 11 ? EXTI_IE_EXTI1_IE_BIT : EXTI_IE_EXTI2_IE_BIT)));
}

/**
 * @brief 中断禁止
 * @param line 模块编号
 */
void HAL_GPIO_IrqDisable(uint8_t line)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(EXTI_IE);
    HAL_REG_RESET(*addr, ((line) < 8 ? EXTI_IE_EXTI0_IE_BIT : ((line) < 11 ? EXTI_IE_EXTI1_IE_BIT : EXTI_IE_EXTI2_IE_BIT)));
}

/**
 * @brief 中断清除
 * @param line 模块编号
 */
void HAL_GPIO_IrqClear(uint8_t line)
{
    volatile uint32_t *addr;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(EXTI_IF);
    HAL_REG_WRITE(*addr, EXTI_IF_IF0_BIT << (line));
}

/**
 * @brief 中断处理函数
 * @param x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_SW_Irq(uint8_t x)
{
    volatile uint32_t *addr;
    (void)x;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SYS[0]->DBG_CFG);
    if (HAL_REG_READ_BIT(*addr, SYS_DBG_CFG_SW_IRQ_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断信号（同 HAL_SW_Irq）
 * @param x 模块编号
 * @return 1表示中断发生，0表示没有中断发生
 */
uint8_t HAL_SW_IrqFlg(uint8_t x)
{
    volatile uint32_t *addr;
    (void)x;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SYS[0]->DBG_CFG);
    if (HAL_REG_READ_BIT(*addr, SYS_DBG_CFG_SW_IRQ_BIT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief 中断使能（本模块无独立使能位，由NVIC控制）
 * @param x 模块编号
 */
void HAL_SW_IrqEnable(uint8_t x)
{
    (void)x;
}

/**
 * @brief 中断禁止（本模块无独立使能位，由NVIC控制）
 * @param x 模块编号
 */
void HAL_SW_IrqDisable(uint8_t x)
{
    (void)x;
}

/**
 * @brief 中断清除
 * @param x 模块编号
 */
void HAL_SW_IrqClear(uint8_t x)
{
    volatile uint32_t *addr;
    (void)x;
    addr = (volatile uint32_t *)HAL_REG_READ_ADDR(HAL_SYS[0]->DBG_CFG);
    HAL_REG_SYS_UNLOCK();
    HAL_REG_SET(*addr, SYS_DBG_CFG_SW_IRQ_BIT);
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 软件触发中断
 * @param x 模块编号
 */
void HAL_SW_IrqTrig(uint8_t x)
{
    (void)x;
    HAL_REG_SYS_UNLOCK();
    HAL_REG_WRITE_BIT(HAL_SYS[0]->DBG_CFG, SYS_DBG_CFG_SW_IRQ_TRIG_MASK, SYS_DBG_CFG_SW_IRQ_TRIG(0x5AA5));
    HAL_REG_SYS_LOCK();
}

// 硬件不支持的中断(空实现)

uint8_t HAL_ADC_IrqSamp3(HAL_ADC_x adc)
{
    (void)adc;
    return 0;
}
uint8_t HAL_ADC_IrqSamp3Flg(HAL_ADC_x adc)
{
    (void)adc;
    return 0;
}
void HAL_ADC_IrqSamp3Enable(HAL_ADC_x adc)
{
    (void)adc;
}
void HAL_ADC_IrqSamp3Disable(HAL_ADC_x adc)
{
    (void)adc;
}
void HAL_ADC_IrqSamp3Clear(HAL_ADC_x adc)
{
    (void)adc;
}

uint8_t HAL_ADC_IrqSamp4(HAL_ADC_x adc)
{
    (void)adc;
    return 0;
}
uint8_t HAL_ADC_IrqSamp4Flg(HAL_ADC_x adc)
{
    (void)adc;
    return 0;
}
void HAL_ADC_IrqSamp4Enable(HAL_ADC_x adc)
{
    (void)adc;
}
void HAL_ADC_IrqSamp4Disable(HAL_ADC_x adc)
{
    (void)adc;
}
void HAL_ADC_IrqSamp4Clear(HAL_ADC_x adc)
{
    (void)adc;
}

uint8_t HAL_ADC_IrqWatchdog1(HAL_ADC_x adc)
{
    (void)adc;
    return 0;
}
uint8_t HAL_ADC_IrqWatchdog1Flg(HAL_ADC_x adc)
{
    (void)adc;
    return 0;
}
void HAL_ADC_IrqWatchdog1Enable(HAL_ADC_x adc)
{
    (void)adc;
}
void HAL_ADC_IrqWatchdog1Disable(HAL_ADC_x adc)
{
    (void)adc;
}
void HAL_ADC_IrqWatchdog1Clear(HAL_ADC_x adc)
{
    (void)adc;
}

uint8_t HAL_DMA_IrqErr(HAL_DMA_x dma_x)
{
    (void)dma_x;
    return 0;
}
uint8_t HAL_DMA_IrqErrFlg(HAL_DMA_x dma_x)
{
    (void)dma_x;
    return 0;
}
void HAL_DMA_IrqErrEnable(HAL_DMA_x dma_x)
{
    (void)dma_x;
}
void HAL_DMA_IrqErrDisable(HAL_DMA_x dma_x)
{
    (void)dma_x;
}
void HAL_DMA_IrqErrClear(HAL_DMA_x dma_x)
{
    (void)dma_x;
}

void HAL_DMA_IrqErrTrig(HAL_DMA_x dma_x)
{
    (void)dma_x;
}

void HAL_DMA_IrqDoneTrig(HAL_DMA_x dma_x)
{
    (void)dma_x;
}

void HAL_GPIO_IrqTrig(uint8_t line)
{
    (void)line;
}

uint8_t HAL_MCPWM_IrqShort(HAL_MCPWM_x mcpwmx)
{
    (void)mcpwmx;
    return 0;
}
uint8_t HAL_MCPWM_IrqShortFlg(HAL_MCPWM_x mcpwmx)
{
    (void)mcpwmx;
    return 0;
}
void HAL_MCPWM_IrqShortEnable(HAL_MCPWM_x mcpwmx)
{
    (void)mcpwmx;
}
void HAL_MCPWM_IrqShortDisable(HAL_MCPWM_x mcpwmx)
{
    (void)mcpwmx;
}
void HAL_MCPWM_IrqShortClear(HAL_MCPWM_x mcpwmx)
{
    (void)mcpwmx;
}

uint8_t HAL_UART_IrqAbd(HAL_UART_x uart_x)
{
    (void)uart_x;
    return 0;
}
uint8_t HAL_UART_IrqAbdFlg(HAL_UART_x uart_x)
{
    (void)uart_x;
    return 0;
}
void HAL_UART_IrqAbdEnable(HAL_UART_x uart_x)
{
    (void)uart_x;
}
void HAL_UART_IrqAbdDisable(HAL_UART_x uart_x)
{
    (void)uart_x;
}
void HAL_UART_IrqAbdClear(HAL_UART_x uart_x)
{
    (void)uart_x;
}
