/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： hardware_config.h
 * 文件标识：
 * 内容摘要： 硬件相关文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet
 * 完成日期： 2020年8月20日
 *
 * 修改记录1：
 * 修改日期： 2020年8月20日
 * 版 本 号： V 2.0
 * 修 改 人： Howlet
 * 修改内容： 创建
 *
 *******************************************************************************/

#ifndef __HARDWARE_CONFIG_H_
#define __HARDWARE_CONFIG_H_

#include "project_mcu.h"
#include "project_config.h"
#include "MC_Parameter_M0.h"
#include "PubData_DriverInstance.h"


/*电源掉电监测阈值*/
#define POWER_4V5   0x00    /*电源掉电监测阈值为4.5V*/       
#define POWER_4V2   0x01    /*电源掉电监测阈值为4.2V*/ 
#define POWER_3V9   0x02    /*电源掉电监测阈值为3.9V*/ 
#define POWER_3V6   0x03    /*电源掉电监测阈值为3.6V*/ 



#define LKS32MC070   0x01    /*芯片型号*/ 
#define LKS32MC071   0x02    /*芯片型号*/ 
#define LKS32MC072   0x03    /*芯片型号*/ 


#define P_HIGH__N_HIGH                   0                 /* 预驱预动极性设置 上管高电平有效，下管高电平有效 */
#define P_HIGH__N_LOW                    1                 /* 预驱预动极性设置 上管高电平有效，下管低电平有效 */

#define  CHIP_PART_NUMBER              LKS32MC071         /* 芯片型号选择，选择不正确将影响芯片模块的初始化 */

#if ((CHIP_PART_NUMBER == LKS32MC074D)||(CHIP_PART_NUMBER == LKS32MC076D)||(CHIP_PART_NUMBER == LKS32MC077D)) 
#define  MCPWM_SWAP_FUNCTION           1
#define  PRE_DRIVER_POLARITY           P_HIGH__N_HIGH     /* 预驱预动极性设置 上管高电平有效，下管高电平有效 */
#else
#define  PRE_DRIVER_POLARITY           P_HIGH__N_LOW      /* 预驱预动极性设置 上管高电平有效，下管低电平有效 */
#endif

/* ----------------------应用PWM 模块定义----------------------------------- */



/* --------------------------------ADC通道号定义------------------------------ */
#define ADC0_CHANNEL_OPA0              ADC_CHANNEL_0
#define ADC0_CHANNEL_OPA1              ADC_CHANNEL_1
#define ADC0_CHANNEL_OPA2              ADC_CHANNEL_2
#define ADC0_CHANNEL_OPA3              ADC_CHANNEL_3

#define ADC1_CHANNEL_OPA0              ADC_CHANNEL_0
#define ADC1_CHANNEL_OPA1              ADC_CHANNEL_1
#define ADC1_CHANNEL_OPA2              ADC_CHANNEL_2
#define ADC1_CHANNEL_OPA3              ADC_CHANNEL_3

/* ADC相电流采样时序，硬件相关 ------------------------------------------------ */
/* Porting Application Notice 注意采样序列 ------------------------------------ */
#define ADC0_CURRETN_A_CHANNEL         (ADC0_CHANNEL_OPA1)//2
#define ADC0_CURRETN_B_CHANNEL         (ADC0_CHANNEL_OPA2)//1
#define ADC0_CURRETN_C_CHANNEL         (ADC0_CHANNEL_OPA0)

#define ADC_1SHUNT_CURR_CH             (ADC0_CHANNEL_OPA3)  /* 单电阻采样电流通道 */

#define ADC_BUS_VOL_CHANNEL            (ADC_CHANNEL_12)      /* 母线电压ADC采样通道 */
#define M0_ADC_BUS_CURR_CH             (ADC0_CHANNEL_OPA3)  /* 母线电流ADC采样通道 */

#define ADC0_TEMP_CHANNEL              (ADC_CHANNEL_7)      /* 温度检测 */
#define ADC0_VSP_CHANNEL               (ADC_CHANNEL_9)      /*电位器VSP检测通道*/


#define BEMF_CH_A                      ADC_CHANNEL_13       /* A相反电势检测ADC通道号 */
#define BEMF_CH_B                      ADC_CHANNEL_12       /* B相反电势检测ADC通道号 */
#define BEMF_CH_C                      ADC_CHANNEL_11       /* C相反电势检测ADC通道号 */

/* 电流内环相电流采样，ADC通道采样结果宏定义 */
#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
//M0 第一个采样数据，第二个采样数据
#define GET_ADC0_DATA_M0					(ADC0_DAT0)   
#define GET_ADC1_DATA_M0					(ADC0_DAT2)
#else
#define GET_ADC0_DATA_M0					(ADC0_DAT0)
#define GET_ADC1_DATA_M0					(ADC0_DAT1)
#endif



/* 母线电压ADC通道采样结果宏定义 */
#define GET_M0_BUS_VOL_ADC_RESULT			(ADC0_DAT4)

#define GET_M0_TEMP_DATA_A					(ADC0_DAT6)
#define GET_M0_BEMF_DATA_A					(ADC0_DAT8)
#define GET_M0_BEMF_DATA_B					(ADC0_DAT9)
#define GET_M0_BEMF_DATA_C					(ADC0_DAT10)




#define ADC_STATE_RESET()              {ADC0_CFG |= BIT11; ADC1_CFG |= BIT11;}   /* ADC0 状态机复位,用以极限情况下确定ADC工作状态 */
#define ADC0_STATE_RESET()              {ADC0_CFG |= BIT11; }   /* ADC0 状态机复位,用以极限情况下确定ADC工作状态 */
#define ADC1_STATE_RESET()              {ADC1_CFG |= BIT11; }  

#define ADC_SOFTWARE_TRIG_ONLY()       {ADC0_TRIG = 0;}      /* ADC设置为仅软件触发 */

/* ------------------------------PGA操作相关定义 ------------------------------ */
//#define PGA_GAIN_20                    0                   /* 反馈电阻200:10 */
//#define PGA_GAIN_9P5                   1                   /* 反馈电阻190:20 */
//#define PGA_GAIN_6                     2                   /* 反馈电阻180:30 */
//#define PGA_GAIN_4P25                  3                   /* 反馈电阻170:40 */

#endif  /* __HARDWARE_CONFIG_H_ */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

