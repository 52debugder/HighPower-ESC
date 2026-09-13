/**
 * @file
 * @brief 虚拟实现,用来在芯片之外约束函数运行效果
 */
#include "../include/hal_lksmcu_adc.h"
#include "../hal_lks32mc07x.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"

static volatile uint8_t HAL_ADC_TRIG_STATE[2] = {0, 0}; // bit0 adc0使能 bit1 adc1使能 bit2 mcpwm触发 bit3 timer触发 bit4 两段式触发使能

/**
 * @brief 内部使用,更新HAL_ADC_TRIG_STATE描述的触发配置
 * @param adc_x 使用的ADC模块编号
 */
static void HAL_ADC_UpdateTrig(HAL_ADC_x adc_x)
{
    uint32_t mask =
        ADC0_TRIG_TIMER2_CMP1_EN_BIT |
        ADC0_TRIG_TIMER2_CMP0_EN_BIT |
        ADC0_TRIG_TIMER0_CMP1_EN_BIT |
        ADC0_TRIG_TIMER0_CMP0_EN_BIT |
        ADC0_TRIG_MCPWM0_T3_EN_BIT |
        ADC0_TRIG_MCPWM0_T2_EN_BIT |
        ADC0_TRIG_MCPWM0_T1_EN_BIT |
        ADC0_TRIG_MCPWM0_T0_EN_BIT;
    // bit2 mcpwm触发 bit3 timer触发 bit4 两段式触发使能
    if (HAL_REG_READ_BIT(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_TWO_SEG_TRIG_EN))
    {
        HAL_REG_SET(HAL_ADC[adc_x]->CFG, ADCx_CFG_NSMP_BIT);
        if (HAL_REG_READ_BIT(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_MCPWM_TRIG_EN)) // 两段 mcpwm触发
        {
            HAL_REG_WRITE_BIT(HAL_ADC[adc_x]->TRIG, mask, ADC0_TRIG_MCPWM0_T0_EN_BIT | ADC0_TRIG_MCPWM0_T1_EN_BIT);
        }
        else if (HAL_REG_READ_BIT(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_MCPWM0_1_TRIG_EN)) // 两段 mcpwm0_1触发
        {
            HAL_REG_WRITE_BIT(HAL_ADC[adc_x]->TRIG, mask, ADC0_TRIG_MCPWM0_T2_EN_BIT | ADC0_TRIG_MCPWM0_T3_EN_BIT);
        }
        else if (HAL_REG_READ_BIT(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_TIMER0_TRIG_EN)) // 两段 timer触发
        {
            HAL_REG_WRITE_BIT(HAL_ADC[adc_x]->TRIG, mask, ADC0_TRIG_TIMER0_CMP0_EN_BIT | ADC0_TRIG_TIMER0_CMP1_EN_BIT);
        }
        else if (HAL_REG_READ_BIT(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_TIMER2_TRIG_EN)) // 两段 timer触发
        {
            HAL_REG_WRITE_BIT(HAL_ADC[adc_x]->TRIG, mask, ADC0_TRIG_TIMER2_CMP0_EN_BIT | ADC0_TRIG_TIMER2_CMP1_EN_BIT);
        }
        else // 两段 软件触发
        {
            HAL_REG_WRITE_BIT(HAL_ADC[adc_x]->TRIG, mask, 0);
        }
    }
    else
    {
        HAL_REG_RESET(HAL_ADC[adc_x]->CFG, ADCx_CFG_NSMP_BIT);
        if (HAL_REG_READ_BIT(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_MCPWM_TRIG_EN)) // 一段 mcpwm触发
        {
            HAL_REG_WRITE_BIT(HAL_ADC[adc_x]->TRIG, mask, ADC0_TRIG_MCPWM0_T0_EN_BIT);
        }
        else if (HAL_REG_READ_BIT(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_MCPWM0_1_TRIG_EN)) // 一段 mcpwm0_1触发
        {
            HAL_REG_WRITE_BIT(HAL_ADC[adc_x]->TRIG, mask, ADC0_TRIG_MCPWM0_T2_EN_BIT);
        }
        else if (HAL_REG_READ_BIT(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_TIMER0_TRIG_EN)) // 一段 timer触发
        {
            HAL_REG_WRITE_BIT(HAL_ADC[adc_x]->TRIG, mask, ADC0_TRIG_TIMER0_CMP0_EN_BIT);
        }
        else if (HAL_REG_READ_BIT(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_TIMER2_TRIG_EN)) // 一段 timer触发
        {
            HAL_REG_WRITE_BIT(HAL_ADC[adc_x]->TRIG, mask, ADC0_TRIG_TIMER2_CMP0_EN_BIT);
        }
        else // 一段 软件触发
        {
            HAL_REG_WRITE_BIT(HAL_ADC[adc_x]->TRIG, mask, 0);
        }
    }
}

/**
 * @brief 初始化指定的ADC模块
 * @param adc_x 要初始化的ADC模块编号
 */
void HAL_ADC_Reset(HAL_ADC_x adc_x)
{
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    switch (adc_x)
    {
        case HAL_ADC_0:
            HAL_REG_SET(SYS_SFT_RST, SYS_SFT_RST_ADC0_SFT_RST_BIT);
            HAL_REG_RESET(SYS_SFT_RST, SYS_SFT_RST_ADC0_SFT_RST_BIT);
            break;
        case HAL_ADC_1:
            HAL_REG_SET(SYS_SFT_RST, SYS_SFT_RST_ADC1_SFT_RST_BIT);
            HAL_REG_RESET(SYS_SFT_RST, SYS_SFT_RST_ADC1_SFT_RST_BIT);
            break;
        default:
            break;
    }
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 启用指定的ADC模块
 * @param adc_x 要启用的ADC模块编号
 */
void HAL_ADC_Enable(HAL_ADC_x adc_x)
{
    switch (adc_x)
    {
        case HAL_ADC_0:
            HAL_REG_SET(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_ADC0_EN);
            HAL_REG_RESET(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_ADC0_EN);
            break;
        case HAL_ADC_1:
            HAL_REG_SET(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_ADC1_EN);
            HAL_REG_RESET(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_ADC1_EN);
            break;
        default:
            break;
    }
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    // SYS_AFE_REG5[0] ADC 开启使能
    HAL_REG_SET(SYS_AFE_REG5, SYS_AFE_REG5_ADCPDN_BIT);
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 禁用指定的ADC模块
 * @param adc_x 要禁用的ADC模块编号
 */
void HAL_ADC_Disable(HAL_ADC_x adc_x)
{
    switch (adc_x)
    {
        case HAL_ADC_0:
            HAL_REG_SET(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_ADC0_EN);
            HAL_REG_RESET(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_ADC0_EN);
            break;
        case HAL_ADC_1:
            HAL_REG_SET(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_ADC1_EN);
            HAL_REG_RESET(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_ADC1_EN);
            break;
        default:
            break;
    }
    // 因为adc只有一个使能位,所以
    // 只在两个adc同时关闭时才关闭adc
    if (HAL_REG_READ_BIT(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_ADC0_EN | HAL_ADC_TRIG_STATE_ADC1_EN) == 0)
    {
        // 系统寄存器解锁
        HAL_REG_SYS_UNLOCK();
        HAL_REG_RESET(SYS_AFE_REG5, SYS_AFE_REG5_ADCPDN_BIT);
        // 系统寄存器上锁
        HAL_REG_SYS_LOCK();
    }
}

/**
 * @brief 获取指定序列号的采样值
 * @param adc_x ADC模块编号
 * @param sequence_x 采样序列号
 * @return 返回对应序列号的采样值
 */
int16_t HAL_ADC_GetSamplingValues(HAL_ADC_x adc_x, HAL_ADC_SAMP_SEQUENCE_x sequence_x)
{
    return HAL_REG_READ(HAL_ADC[adc_x]->DAT[sequence_x]);
}

/**
 * @brief 设置指定序列号的采样通道
 * @param adc_x ADC模块编号
 * @param sequence_x 采样序列号
 * @param channel_x 采样通道端口
 */
void HAL_ADC_SetSamplingChannel(HAL_ADC_x adc_x, HAL_ADC_SAMP_SEQUENCE_x sequence_x, HAL_ADC_CHANNEL_x channel_x)
{
    switch (sequence_x)
    {
        case HAL_ADC_SAMP_SEQUENCE_0:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_ADC[adc_x]->CHN0, ADCx_CHN0_PDS0, channel_x);
            break;
        case HAL_ADC_SAMP_SEQUENCE_1:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_ADC[adc_x]->CHN0, ADCx_CHN0_PDS1, channel_x);
            break;
        case HAL_ADC_SAMP_SEQUENCE_2:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_ADC[adc_x]->CHN0, ADCx_CHN0_PDS2, channel_x);
            break;
        case HAL_ADC_SAMP_SEQUENCE_3:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_ADC[adc_x]->CHN0, ADCx_CHN0_PDS3, channel_x);
            break;
        case HAL_ADC_SAMP_SEQUENCE_4:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_ADC[adc_x]->CHN1, ADCx_CHN1_PDS4, channel_x);
            break;
        case HAL_ADC_SAMP_SEQUENCE_5:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_ADC[adc_x]->CHN1, ADCx_CHN1_PDS5, channel_x);
            break;
        case HAL_ADC_SAMP_SEQUENCE_6:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_ADC[adc_x]->CHN1, ADCx_CHN1_PDS6, channel_x);
            break;
        case HAL_ADC_SAMP_SEQUENCE_7:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_ADC[adc_x]->CHN1, ADCx_CHN1_PDS7, channel_x);
            break;
        case HAL_ADC_SAMP_SEQUENCE_8:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_ADC[adc_x]->CHN2, ADCx_CHN2_PDS8, channel_x);
            break;
        case HAL_ADC_SAMP_SEQUENCE_9:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_ADC[adc_x]->CHN2, ADCx_CHN2_PDS9, channel_x);
            break;
        case HAL_ADC_SAMP_SEQUENCE_10:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_ADC[adc_x]->CHN2, ADCx_CHN2_PDS10, channel_x);
            break;
        case HAL_ADC_SAMP_SEQUENCE_11:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_ADC[adc_x]->CHN2, ADCx_CHN2_PDS11, channel_x);
            break;
        case HAL_ADC_SAMP_SEQUENCE_12:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_ADC[adc_x]->CHN3, ADCx_CHN3_PDS12, channel_x);
            break;
        case HAL_ADC_SAMP_SEQUENCE_13:
            HAL_REG_WRITE_BIT_MASK_POS(HAL_ADC[adc_x]->CHN3, ADCx_CHN3_PDS13, channel_x);
            break;
        default:
            break;
    }
}

/**
 * @brief 设置采样数量
 * @param adc_x ADC模块编号
 * @param sample_number 采样数量
 */
void HAL_ADC_SetSamplingQuantity(HAL_ADC_x adc_x, HAL_ADC_SAMP_NUMBER_x sample1_number, HAL_ADC_SAMP_NUMBER_x sample2_number)
{
    // 第一段采样数量为0时,芯片不进行采样
    if (sample1_number == HAL_ADC_SAMP_NUMBER_0)
    {
        sample2_number = HAL_ADC_SAMP_NUMBER_0;
    }
    // 两段采样数量之和不能大于10个
    if (sample1_number + sample2_number > 14)
    {
        sample2_number = (HAL_ADC_SAMP_NUMBER_x)(14 - sample1_number);
    }
    HAL_REG_WRITE_BIT(HAL_ADC[adc_x]->CHNT, ADCx_CHNT_S1_MASK, sample1_number);
    HAL_REG_WRITE_BIT(HAL_ADC[adc_x]->CHNT, ADCx_CHNT_S2_MASK, sample2_number << 4);
    if (sample2_number)
    {
        HAL_REG_SET(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_TWO_SEG_TRIG_EN);
    }
    else
    {
        HAL_REG_RESET(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_TWO_SEG_TRIG_EN);
    }
    HAL_ADC_UpdateTrig(adc_x);
}

/**
 * @brief 设置触发信号
 * @param adc_x ADC模块编号
 * @param trigger 触发信号类型
 */
void HAL_ADC_SetTriggerSignal(HAL_ADC_x adc_x, HAL_ADC_TRIGGER_x trigger)
{
    switch (trigger)
    {
        case HAL_ADC_TRIGGER_MCPWM0: ///< 使用MCPWM触发ADC采样
            HAL_REG_WRITE_BIT(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_MCPWM_TRIG_EN | HAL_ADC_TRIG_STATE_TIMER0_TRIG_EN | HAL_ADC_TRIG_STATE_TIMER2_TRIG_EN | HAL_ADC_TRIG_STATE_MCPWM0_1_TRIG_EN, HAL_ADC_TRIG_STATE_MCPWM_TRIG_EN);
            break;
        case HAL_ADC_TRIGGER_MCPWM0_1: ///< 使用MCPWM时基1触发ADC采样
            HAL_REG_WRITE_BIT(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_MCPWM_TRIG_EN | HAL_ADC_TRIG_STATE_TIMER0_TRIG_EN | HAL_ADC_TRIG_STATE_TIMER2_TRIG_EN | HAL_ADC_TRIG_STATE_MCPWM0_1_TRIG_EN, HAL_ADC_TRIG_STATE_MCPWM0_1_TRIG_EN);
            break;
        case HAL_ADC_TRIGGER_TIMER0: ///< 使用TIMER触发ADC采样
            HAL_REG_WRITE_BIT(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_MCPWM_TRIG_EN | HAL_ADC_TRIG_STATE_TIMER0_TRIG_EN | HAL_ADC_TRIG_STATE_TIMER2_TRIG_EN | HAL_ADC_TRIG_STATE_MCPWM0_1_TRIG_EN, HAL_ADC_TRIG_STATE_TIMER0_TRIG_EN);
            break;
        case HAL_ADC_TRIGGER_TIMER2: ///< 使用TIMER触发ADC采样
            HAL_REG_WRITE_BIT(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_MCPWM_TRIG_EN | HAL_ADC_TRIG_STATE_TIMER0_TRIG_EN | HAL_ADC_TRIG_STATE_TIMER2_TRIG_EN | HAL_ADC_TRIG_STATE_MCPWM0_1_TRIG_EN, HAL_ADC_TRIG_STATE_TIMER2_TRIG_EN);
            break;
        case HAL_ADC_TRIGGER_SOFT: ///< 使用软件触发ADC采样
            HAL_REG_WRITE_BIT(HAL_ADC_TRIG_STATE[adc_x], HAL_ADC_TRIG_STATE_MCPWM_TRIG_EN | HAL_ADC_TRIG_STATE_TIMER0_TRIG_EN | HAL_ADC_TRIG_STATE_TIMER2_TRIG_EN | HAL_ADC_TRIG_STATE_MCPWM0_1_TRIG_EN, 0);
            break;
        default:
            break;
    }
    HAL_ADC_UpdateTrig(adc_x);
}

/**
 * @brief 结束采样
 * @param adc_x ADC模块编号
 */
void HAL_ADC_EndSampling(HAL_ADC_x adc_x)
{
    HAL_REG_SET(HAL_ADC[adc_x]->CFG, ADCx_CFG_FSM_RS_BIT);
}

/**
 * @brief 软件触发ADC开始采样
 * @param adc_x ADC模块编号
 */
void HAL_ADC_SoftTrigger(HAL_ADC_x adc_x)
{
    HAL_REG_WRITE(HAL_ADC[adc_x]->SWT, 0x5aa5);
}

/**
 * @brief 手动采样
 * @param n 采样通道编号
 * @return 示例返回值,实际应返回采样值
 */
int16_t HAL_ADC_ManualSampling(HAL_ADC_x adc_x, HAL_ADC_CHANNEL_x channel_x) // 手动采样 需要先设置采样通道为软件触发
{
    int16_t data;
    uint32_t i;
    HAL_ADC_SetTriggerSignal(adc_x, HAL_ADC_TRIGGER_SOFT);
    HAL_ADC_EndSampling(adc_x);
    HAL_ADC_SetSamplingQuantity(adc_x, HAL_ADC_SAMP_NUMBER_1, HAL_ADC_SAMP_NUMBER_0);
    HAL_ADC_SetSamplingChannel(adc_x, HAL_ADC_SAMP_SEQUENCE_0, channel_x);
    HAL_REG_WRITE(HAL_ADC[adc_x]->IE, 0);
    HAL_REG_WRITE(HAL_ADC[adc_x]->IF, 0xffff);
    HAL_ADC_SoftTrigger(adc_x);
    i = 3000;
    while (HAL_REG_READ(HAL_ADC[adc_x]->IF) == 0)
    {
        i--;
        __NOP();
        if (i == 0)
        {
            break;
        }
    }
    HAL_REG_WRITE(HAL_ADC[adc_x]->IF, 0xffff);
    data = HAL_REG_READ(HAL_ADC[adc_x]->DAT[0]);
    return data;
}

/**
 * @brief 设置ADC基准源
 * @param adc_x ADC模块编号
 * @param reference_x 基准源
 */
void HAL_ADC_SetReference(HAL_ADC_x adc_x, HAL_ADC_REFERENCE_x reference_x)
{
    (void)adc_x;
    switch (reference_x)
    {
        case HAL_ADC_REFERENCE_INTERNAL: // 使用内部基准源作为adc基准

            // 系统寄存器解锁
            HAL_REG_SYS_UNLOCK();
            // SYS_AFE_REG1[4] ADC 基准选择
            HAL_REG_WRITE_BIT(SYS_AFE_REG1, SYS_AFE_REG0_RES_OPA2_POS, 0);
            // 系统寄存器上锁
            HAL_REG_SYS_LOCK();

            break;
        case HAL_ADC_REFERENCE_EXTERNAL:
            // 系统寄存器解锁
            HAL_REG_SYS_UNLOCK();
            // SYS_AFE_REG1[4] ADC 基准选择
            HAL_REG_WRITE_BIT(SYS_AFE_REG1, SYS_AFE_REG0_RES_OPA2_POS, SYS_AFE_REG0_RES_OPA2_POS);
            // 系统寄存器上锁
            HAL_REG_SYS_LOCK();
            break;
        default:
            break;
    }
    HAL_REG_WRITE(ADC0_DC0, HAL_TRIM_Read(0x00001420));
    HAL_REG_WRITE(ADC0_AMC0, HAL_TRIM_Read(0x00001424));
    HAL_REG_WRITE(ADC0_DC1, HAL_TRIM_Read(0x00001428));
    HAL_REG_WRITE(ADC0_AMC1, HAL_TRIM_Read(0x0000142C));
    HAL_REG_WRITE(ADC1_DC0, HAL_TRIM_Read(0x00001430));
    HAL_REG_WRITE(ADC1_AMC0, HAL_TRIM_Read(0x00001434));
    HAL_REG_WRITE(ADC1_DC1, HAL_TRIM_Read(0x00001438));
    HAL_REG_WRITE(ADC1_AMC1, HAL_TRIM_Read(0x0000143C));
}

/**
 * @brief 重置ADC状态
 * @param adc_x ADC模块编号
 */
void HAL_ADC_StateReset(HAL_ADC_x adc_x)
{
    HAL_REG_SET(HAL_ADC[adc_x]->CFG, ADCx_CFG_FSM_RS_BIT);
}

/**
 * @brief 获取adc量程,使用芯片供电作为adc基准时固定返回5.0
 * @param adc_x ADC模块编号
 * @return ADC量程
 */
float HAL_ADC_GetRange(HAL_ADC_x adc_x)
{
    uint32_t val;
    float range = 5.0f;
    (void)adc_x;
    val = HAL_REG_READ_BIT(SYS_AFE_REG1, SYS_AFE_REG0_RES_OPA2_POS);
    val >>= 4;
    switch (val)
    {
        case 0:
            range = 3.6f;
            break;
        case 1:
            range = 5.0f;
            break;
        default:
            break;
    }

    return range;
}

/**
 * @brief 获取采样值单位
 * @param adc_x ADC模块编号
 * @return 采样值单位
 */
float HAL_ADC_GetValuesUnit(HAL_ADC_x adc_x)
{
    if (HAL_REG_READ_BIT(HAL_ADC[adc_x]->CFG, ADCx_CFG_DATA_ALIGN_BIT))
    {
        return HAL_ADC_GetRange(adc_x) / 0x07ff;
    }
    else
    {
        return HAL_ADC_GetRange(adc_x) / 0x7ff0;
    }
}

/**
 * @brief 设置指定的GPIO为ADC输入
 * @param adc_x ADC模块编号
 * @param pin_x GPIO编号
 */
void HAL_ADC_SetGpioIn(HAL_ADC_x adc_x, HAL_GPIO_Px pin_x)
{
    (void)adc_x;
    HAL_GPIO_SetAf(pin_x, HAL_GPIO_AF_ADC);
    HAL_GPIO_SetMode(pin_x, HAL_GPIO_MODE_AFE);
}

/**
 * @brief 设置指定的GPIO为ADC触发信号输出
 * @param adc_x ADC模块编号
 * @param pin_x GPIO编号
 */
void HAL_ADC_SetGpioTriggerOut(HAL_ADC_x adc_x, HAL_GPIO_Px pin_x)
{
    (void)adc_x;
    HAL_GPIO_SetAf(pin_x, HAL_GPIO_AF_ADC_TRIG);
    HAL_GPIO_SetMode(pin_x, HAL_GPIO_MODE_OUT);
}
