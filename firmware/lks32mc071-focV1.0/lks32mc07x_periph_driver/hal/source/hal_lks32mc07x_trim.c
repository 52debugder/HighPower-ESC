#include "../include/hal_lksmcu_trim.h"
#include "stdint.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"
#include "../include/hal_lksmcu_crc.h"
uint32_t HAL_TRIM_ReadMcu07(uint32_t);
// 地址 内容
// 0x00001420 ADC0_DC0 校准值,3.6V量程OFFSET
// 0x00001424 ADC0_AMC0 校准值,3.6V量程GAIN
// 0x00001428 ADC0_DC1 校准值,7.2V量程OFFSET
// 0x0000142C ADC0_AMC1 校准值,7.2V量程GAIN
// 0x00001430 ADC1_DC0 校准值,3.6V量程OFFSET
// 0x00001434 ADC1_AMC0 校准值,3.6V量程GAIN
// 0x00001438 ADC1_DC1 校准值,7.2V量程OFFSET
// 0x0000143C ADC1_AMC1 校准值,7.2V量程GAIN
// 0x00001450 DAC0 选择4.85V 档位,SYS_AFE_DAC_AMC 校准值(扩大512 倍结果)
// 0x00001454 DAC0 选择4.85V 档位,SYS_AFE_DAC_DC 校准值
// 0x00001458 DAC0 选择1.20V 档位,SYS_AFE_DAC_AMC 校准值(扩大512 倍结果)
// 0x0000145C DAC0 选择1.20V 档位,SYS_AFE_DAC_DC 校准值
// 0x00001460 DAC1 选择4.85V 档位,SYS_AFE_DAC_AMC 校准值(扩大512 倍结果)
// 0x00001464 DAC1 选择4.85V 档位,SYS_AFE_DAC_DC 校准值
// 0x00001468 DAC1 选择1.20V 档位,SYS_AFE_DAC_AMC 校准值(扩大512 倍结果)
// 0x0000146C DAC1 选择1.20V 档位,SYS_AFE_DAC_DC 校准值
// 0x00001480 OPA0,320K 欧姆 VS 10K 欧姆,GAIN 校准值(扩大1000 倍结果),R0为0欧姆。
// 0x00001484 OPA0,160K 欧姆 VS 10K 欧姆,GAIN 校准值(扩大1000 倍结果),R0为0欧姆。
// 0x00001488 OPA0,080K 欧姆 VS 10K 欧姆,GAIN 校准值(扩大1000 倍结果),R0为0欧姆。
// 0x0000148C OPA0,040K 欧姆 VS 10K 欧姆,GAIN 校准值(扩大1000 倍结果),R0为0欧姆。
// 0x00001490 OPA1,320K 欧姆 VS 10K 欧姆,GAIN 校准值(扩大1000 倍结果),R0为0欧姆。
// 0x00001494 OPA1,160K 欧姆 VS 10K 欧姆,GAIN 校准值(扩大1000 倍结果),R0为0欧姆。
// 0x00001498 OPA1,080K 欧姆 VS 10K 欧姆,GAIN 校准值(扩大1000 倍结果),R0为0欧姆。
// 0x0000149C OPA1,040K 欧姆 VS 10K 欧姆,GAIN 校准值(扩大1000 倍结果),R0为0欧姆。
// 0x000014A0 OPA2,320K 欧姆 VS 10K 欧姆,GAIN 校准值(扩大1000 倍结果),R0为0欧姆。
// 0x000014A4 OPA2,160K 欧姆 VS 10K 欧姆,GAIN 校准值(扩大1000 倍结果),R0为0欧姆。
// 0x000014A8 OPA2,080K 欧姆 VS 10K 欧姆,GAIN 校准值(扩大1000 倍结果),R0为0欧姆。
// 0x000014AC OPA2,040K 欧姆 VS 10K 欧姆,GAIN 校准值(扩大1000 倍结果),R0为0欧姆。
// 0x000014B0 OPA3,320K 欧姆 VS 10K 欧姆,GAIN 校准值(扩大1000 倍结果),R0为0欧姆。
// 0x000014B4 OPA3,160K 欧姆 VS 10K 欧姆,GAIN 校准值(扩大1000 倍结果),R0为0欧姆。
// 0x000014B8 OPA3,080K 欧姆 VS 10K 欧姆,GAIN 校准值(扩大1000 倍结果),R0为0欧姆。
// 0x000014BC OPA3,040K 欧姆 VS 10K 欧姆,GAIN 校准值(扩大1000 倍结果),R0为0欧姆。
// 0x000014C0 OPA0,共模电压(扩大10000 倍结果)
// 0x000014C4 OPA1,共模电压(扩大10000 倍结果)
// 0x000014C8 OPA2,共模电压(扩大10000 倍结果)
// 0x000014CC OPA3,共模电压(扩大10000 倍结果)
// 0x000014D0 温度传感器,斜率校准值
// 0x000014D4 温度传感器,偏置校准值
// 0x00001500 OPA0,320K 欧姆:10K 欧姆挡位。高16位存放R2实际阻值,低16位存放R1实际阻值(扩大100 倍结果)
// 0x00001504 OPA0,160K 欧姆:10K 欧姆挡位。高16位存放R2实际阻值,低16位存放R1实际阻值(扩大100 倍结果)
// 0x00001508 OPA0,080K 欧姆:10K 欧姆挡位。高16位存放R2实际阻值,低16位存放R1实际阻值(扩大100 倍结果)
// 0x0000150C OPA0,040K 欧姆:10K 欧姆挡位。高16位存放R2实际阻值,低16位存放R1实际阻值(扩大100 倍结果)
// 0x00001510 OPA1,320K 欧姆:10K 欧姆挡位。高16位存放R2实际阻值,低16位存放R1实际阻值(扩大100 倍结果)
// 0x00001514 OPA1,160K 欧姆:10K 欧姆挡位。高16位存放R2实际阻值,低16位存放R1实际阻值(扩大100 倍结果)
// 0x00001518 OPA1,080K 欧姆:10K 欧姆挡位。高16位存放R2实际阻值,低16位存放R1实际阻值(扩大100 倍结果)
// 0x0000151C OPA1,040K 欧姆:10K 欧姆挡位。高16位存放R2实际阻值,低16位存放R1实际阻值(扩大100 倍结果)
// 0x00001520 OPA2,320K 欧姆:10K 欧姆挡位。高16位存放R2实际阻值,低16位存放R1实际阻值(扩大100 倍结果)
// 0x00001524 OPA2,160K 欧姆:10K 欧姆挡位。高16位存放R2实际阻值,低16位存放R1实际阻值(扩大100 倍结果)
// 0x00001528 OPA2,080K 欧姆:10K 欧姆挡位。高16位存放R2实际阻值,低16位存放R1实际阻值(扩大100 倍结果)
// 0x0000152C OPA2,040K 欧姆:10K 欧姆挡位。高16位存放R2实际阻值,低16位存放R1实际阻值(扩大100 倍结果)
// 0x00001530 OPA3,320K 欧姆:10K 欧姆挡位。高16位存放R2实际阻值,低16位存放R1实际阻值(扩大100 倍结果)
// 0x00001534 OPA3,160K 欧姆:10K 欧姆挡位。高16位存放R2实际阻值,低16位存放R1实际阻值(扩大100 倍结果)
// 0x00001538 OPA3,080K 欧姆:10K 欧姆挡位。高16位存放R2实际阻值,低16位存放R1实际阻值(扩大100 倍结果)
// 0x0000153C OPA3,040K 欧姆:10K 欧姆挡位。高16位存放R2实际阻值,低16位存放R1实际阻值(扩大100 倍结果)

/**
 * @brief 读取MCU03的校准参数
 * @param addr 校准参数的地址
 */
uint32_t HAL_TRIM_Read(uint32_t addr)
{
    return HAL_TRIM_ReadMcu07(addr);
}

/**
 * @brief 读取芯片唯一ID
 * @param idx 0:ID0,1:ID1,2:ID2,3:ID3,4:ID4
 * @return 唯一ID
 */
uint32_t HAL_TRIM_ReadId(uint32_t idx)
{
    return HAL_TRIM_Read(0x00001E84 + idx * 4);
}

/**
 * @brief 读取芯片唯一ID的CRC32值
 * @return 唯一ID的CRC32值
 * @note 相较于HAL_TRIM_ReadId，更方便存储和判断，但理论上存在重复的可能（1/0xffffffff）
 */
uint32_t HAL_TRIM_ReadIdCrc32(void)
{
    uint32_t id[5];
    uint32_t i;
    for (i = 0; i < 5; i++)
    {
        id[i] = HAL_TRIM_Read(0x00001E84 + i * 4);
    }
    return HAL_CRC_Calc(HAL_CRC_0, HAL_CRC_MODEL_CRC32, (uint8_t *)id, sizeof(id));
}
