/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： LKS32MC07x_sif.c\n
 * 文件标识： 无 \n
 * 内容摘要： SIF外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>myx   <td>修改
 * </table>
 */
#include "lks32mc07x_sif.h"

/**
 *@brief @b 函数名称:   void SIF_Init(STF_Typedef* SIFx ,SIF_InitTypeDef* SIF_InitStruct)
 *@brief @b 功能描述:   SIF初始化函数
 *@see被引用内容：       
 *@param输入参数：       SIFx：SIF , SIF_InitTypeDef *SIF_InitStruct
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
		SIF_InitTypeDef SIF_InitStruct;

		SIF_StructInit(&SIF_InitStruct);
		SIF_InitStruct.EN = 1;
		SIF_InitStruct.MSB = 0;
		SIF_InitStruct.RATIO = 0;
		SIF_InitStruct.SYS_VLD = 1;
		SIF_InitStruct.DONE_VLD = 1;
		SIF_InitStruct.SYSD = 0;
		SIF_InitStruct.DONED =0;
		SIF_InitStruct.SYS_PLUSE = 0;
		SIF_Init(SIF0,&SIF_InitStruct);
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void SIF_Init(STF_Typedef* SIFx ,SIF_InitTypeDef* SIF_InitStruct)
{
    SYS_ModuleClockCmd(SYS_Module_SIF0,ENABLE);
    SIFx-> CFG = (SIF_InitStruct->EN | SIF_InitStruct->MSB <<1 \
                 | SIF_InitStruct->RATIO <<2                    \
                 | SIF_InitStruct->SYS_VLD <<3                 \
                 | SIF_InitStruct->DONE_VLD    <<4              \
                 | SIF_InitStruct->SYSD   <<5                  \
                 | SIF_InitStruct->DONED   <<6               \
                 | SIF_InitStruct->SYS_PLUSE << 7);               
}

/**
 *@brief @b 函数名称:    void SIF_StructInit(SIF_InitTypeDef* SIF_InitStruct)
 *@brief @b 功能描述:    SIF结构体初始化
 *@see被引用内容：       无
 *@param输入参数：       SIF_InitTypeDef *SIF_InitStruct
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code
			SIF_InitTypeDef SIF_InitStruct;
            SIF_StructInit(&SIF_InitStruct);              //SIF结构体初始化
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void SIF_StructInit(SIF_InitTypeDef* SIF_InitStruct)
{
    SIF_InitStruct-> EN   = 0;
    SIF_InitStruct-> MSB  = 0;
    SIF_InitStruct->RATIO = 0;
    SIF_InitStruct->SYS_VLD = 0;
    SIF_InitStruct->DONE_VLD = 0;
    SIF_InitStruct->SYSD  = 0;
    SIF_InitStruct->DONED = 0;
    SIF_InitStruct->SYS_PLUSE = 0;
}

/**
 *@brief @b 函数名称:  void SIF_Timebase_set(u32 tosc)
 *@brief @b 功能描述:   设置SIF传输时基
 *@see被引用内容：       
 *@param输入参数：       tosc  ：时基系数   
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void SIF_Timebase_set(u32 tosc)
{
    SIF->TOSC = tosc;
}

/**
 *@brief @b 函数名称:  void SIF_Timebase_set(u32 tosc)
 *@brief @b 功能描述:   设置信号通信方式
 *@see被引用内容：       
 *@param输入参数：       tsh tsl ：同步信号周期
 *                      tdh tdl ：结束信号周期   
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void SIF_TH_set(u32 tsh,u32 tdh)
{
    SIF-> STH1 = tsh;
    SIF-> DTH1 = tdh;
}

/**
 *@brief @b 函数名称:  void SIF_Senddata(u8 Data)
 *@brief @b 功能描述:   传输数据设置
 *@see被引用内容：       
 *@param输入参数：       Data :传输的数据   
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void SIF_Senddata(u8 Data)
{
    REG32(SIF0_BASE + 0x14) = Data;
}

/**
 *@brief @b 函数名称:  void SIF_DMA_Enable(void)
 *@brief @b 功能描述:   SIF DMA传输请求使能
 *@see被引用内容：       
*@param输入参数：       state : ENABLE/DIABLE   
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void SIF_DMA_IsEnable(u8 state)
{
	if(state == ENABLE)
	{
			SIF->IRQ |= SIF_DMA_Enable;
	}
	else
	{
			SIF->IRQ &= ~SIF_DMA_Enable;
	}

}

/**
 *@brief @b 函数名称:  void SIF_DMA_Enable(void)
 *@brief @b 功能描述:   SIF DMA传输请求使能
 *@see被引用内容：       
*@param输入参数：       state : ENABLE/DIABLE   
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void SIF_Irq_IsEnable(u8 state)
{
	if(state == ENABLE)
	{
			SIF->IRQ |= SIF_IE_Enable;
	}
	else
	{
			SIF->IRQ &= ~SIF_IE_Enable;
	}
}

/**
 *@brief @b 函数名称:  void SIF_Clear_Irq()
 *@brief @b 功能描述:   清除SIF模块标志位
 *@see被引用内容：       
*@param输入参数：        无 
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void SIF_Clear_Irq(void)
{
	SIF->IRQ |= BIT4;
}


