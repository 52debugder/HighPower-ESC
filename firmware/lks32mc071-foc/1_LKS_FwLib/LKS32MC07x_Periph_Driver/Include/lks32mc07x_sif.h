 /**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_sif.h\n
 * 文件标识： 无 \n
 * 内容摘要： SIF驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>myx   <td>修改
 * </table>
 */
#ifndef _CONNIE_SIF_H_
#define _CONNIE_SIF_H_

#include "lks32mc07x_lib.h"

 /** 
 *@brief SIF 寄存器定义
 */
typedef struct 
{
    /* data */
    __IO u32 CFG       ;     //0x00
    __IO u32 TOSC      ;     //0x04
    __IO u32 STH1     ;     //0x08
    __IO u32 DTH1     ;     //0x0C
    __IO u32 IRQ       ;     //0x10
    __IO u32 WDATA     ;     //0x14

} STF_Typedef;

 /** 
 *@brief SIF模块基地址定义
 */
#define SIF ((STF_Typedef*)(SIF0_BASE + 0x00))
#define SIF0 ((STF_Typedef *)SIF0_BASE)

 /** 
 *@brief SPI初始化结构体句柄，初始化时请定义该句柄，并用其它地址来传参
 */
typedef struct
{
    u8 EN;          ///<  SIF模块使能：0，关闭；1，开启
    u8 MSB;        ///<  数据块大小端定义
    u8 RATIO;        ///<  模块数据占空比设置
    u8 SYS_VLD;  ///<  有无同步信号
    u16 DONE_VLD;   ///<  有无结束信号
    u16 SYS_PLUSE;  ///<  同步信号有无脉冲信号
    u16 SYSD;     ///<  同步信号默认电平
    u16 DONED;       ///< 结束信号默认电平
} SIF_InitTypeDef;

/*中断使能定义*/
#define SIF_IE_Enable BIT0   ///< SIF中断使能开关。默认值为0
#define SIF_DMA_Enable BIT1   ///< SIF DMA请求使能开关。默认值为0

/*中断标志定义*/
#define SPI_IF_CLEAR BIT4 ///< SPI传输，完成事件。高电平有效，写1清除。

void SIF_Init(STF_Typedef* SIFx ,SIF_InitTypeDef* SIF_InitStruct);
void SIF_StructInit(SIF_InitTypeDef* SPI_InitStruct);
void SIF_Timebase_set(u32 tosc);
void SIF_TH_set(u32 tsh,u32 tdh);
void SIF_Senddata(u8 Data);
void SIF_DMA_IsEnable(u8 state);
void SIF_Irq_IsEnable(u8 state);
void SIF_Clear_Irq(void);

#endif


