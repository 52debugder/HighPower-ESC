
#include "../include/hal_lksmcu_tmp.h"
#include "../include/hal_lksmcu_trim.h"
#include "../hal_lks32mc07x.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"
static int32_t tmp_coef_a = 0;
static int32_t tmp_coef_b = 0;
/**
 * @brief 模块复位
 * @param TMP_x 模块编号
 */
void HAL_TMP_Reset(HAL_TMP_x TMP_x)
{
    HAL_TMP_Disable(TMP_x);
}

/**
 * @brief 模块打开
 * @param TMP_x 模块编号
 */
void HAL_TMP_Enable(HAL_TMP_x TMP_x)
{
    (void)TMP_x;
    HAL_REG_SYS_UNLOCK();
    HAL_REG_SET(SYS_AFE_REG5, SYS_AFE_REG5_TMPPDN_BIT);
    HAL_REG_SYS_LOCK();
    tmp_coef_a = -HAL_TRIM_Read(0x000014D0);
    tmp_coef_b = HAL_TRIM_Read(0x000014D4);
}

/**
 * @brief 模块关闭
 * @param TMP_x 模块编号
 */
void HAL_TMP_Disable(HAL_TMP_x TMP_x)
{
    (void)TMP_x;
    HAL_REG_SYS_UNLOCK();
    HAL_REG_RESET(SYS_AFE_REG5, SYS_AFE_REG5_TMPPDN_BIT);
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 获取当前芯片内部温度传感器测到的温度,单位摄氏度
 * @param TMP_x 模块编号
 * @param adc ADC编号
 * @param sequence ADC采样序列
 * @return 当前温度,单位摄氏度
 */
int32_t HAL_TMP_GetTemperature(HAL_TMP_x TMP_x, HAL_ADC_x adc, HAL_ADC_SAMP_SEQUENCE_x sequence)
{
    // 实现获取温度的代码,单位摄氏度
    int32_t adc_data;
    int32_t tmp;
    adc_data = HAL_ADC_GetSamplingValues(adc, sequence);
    tmp      = HAL_TMP_Adc2Temperature(TMP_x, adc_data);
    return tmp; // 返回温度值
}

/**
 * @brief 获取当前芯片内部温度传感器测到的温度,单位0.1摄氏度
 * @param TMP_x 模块编号
 * @param adc ADC编号
 * @param sequence ADC采样序列
 * @return 当前温度,单位0.1摄氏度
 */
int32_t HAL_TMP_GetTemperature01(HAL_TMP_x TMP_x, HAL_ADC_x adc, HAL_ADC_SAMP_SEQUENCE_x sequence)
{
    // 实现获取温度的代码,单位0.1摄氏度
    int32_t adc_data;
    int32_t tmp;
    adc_data = HAL_ADC_GetSamplingValues(adc, sequence);
    tmp      = HAL_TMP_Adc2Temperature01(TMP_x, adc_data);
    return tmp; // 返回温度值
}

/**
 * @brief adc值转温度
 * @param TMP_x 模块编号
 * @param adc_value ADC值，左对齐（-32767 到32767）
 * @return 当前温度,单位摄氏度
 */
int32_t HAL_TMP_Adc2Temperature(HAL_TMP_x TMP_x, int32_t adc_value)
{
    return HAL_TMP_Adc2Temperature01(TMP_x, adc_value) / 10;
}

/**
 * @brief adc值转温度
 * @param TMP_x 模块编号
 * @param adc_value ADC值，左对齐（-32767 到32767）
 * @return 当前温度,单位0.1摄氏度
 */
int32_t HAL_TMP_Adc2Temperature01(HAL_TMP_x TMP_x, int32_t adc_value)
{
    int32_t tmp;
    (void)TMP_x;
    tmp = (int32_t)tmp_coef_a * (adc_value >> 4) / 1000 + (int32_t)tmp_coef_b;
    return tmp; // 返回温度值
}
