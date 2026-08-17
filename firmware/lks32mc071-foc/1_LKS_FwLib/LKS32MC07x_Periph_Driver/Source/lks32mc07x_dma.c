/**
 * @file 
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： LKS32MC07x_dma.c\n
 * 文件标识： 无 \n
 * 内容摘要： DMA外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2020年8月1日 <td>1.0     <td>Howlet      <td>创建
 * </table>
 *@par 修改日志:修改dma初始化相关函数
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月11日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
#include "lks32mc07x_dma.h"
#include "string.h"

/*******************************************************************************
 函数名称：    void DMA_StructInit(DMA_InitTypeDef *DMAInitStruct)
 功能描述：    DMA结构体初始化
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.08.1      V1.0           howlet              创建
 *******************************************************************************/
/**
 *@brief @b 函数名称:   void DMA_StructInit(DMA_InitTypeDef *DMAInitStruct)
 *@brief @b 功能描述:   DMA结构体初始化
 *@see被引用内容：       无
 *@param输入参数：       DMA_InitTypeDef
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无   
 *@par 示例代码：
 *@code    
           DMA_InitTypeDef DMA_InitStructure;
		   DMA_StructInit(&DMA_InitStructure); //初始化结构体
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月11日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void DMA_StructInit(DMA_InitTypeDef *DMAInitStruct)
{
    memset(DMAInitStruct, 0, sizeof(DMA_InitTypeDef));
}

/**
 *@brief @b 函数名称:   void DMA_Init(DMA_RegTypeDef *DMAx, DMA_InitTypeDef *DMAInitStruct)
 *@brief @b 功能描述:   DMA初始化函数
 *@see被引用内容：       无
 *@param输入参数：       ADCx：ADC0 , ADC_InitTypeDef
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              无
 *@par 示例代码：
 *@code    
			u8 memaddr[25] ={0x11,0x12,0x13};//发送数据缓冲区

			DMA_InitTypeDef DMA_InitStruct;
			DMA_StructInit(&DMA_InitStruct);
			DMA_InitStruct.DMA_IRQ_EN = DMA_TCIE;           // DMA 传输完成中断使能 
			DMA_InitStruct.DMA_DIR = MEMORY2PERI;           // 内存至外设 
			DMA_InitStruct.DMA_CIRC = DISABLE;              // 关闭循环传输模式 
			DMA_InitStruct.DMA_PINC = ENABLE;               // 外设地址每轮内是否递增,高有效 
			DMA_InitStruct.DMA_MINC = ENABLE;               // 内存地址第二轮是否在第一轮地址的基础上递增（轮内地址一定递增）,高有效 
			DMA_InitStruct.DMA_PBTW = DMA_BYTE_TRANS;       // 外设访问位宽， 0:byte, 1:half-word, 2:word 
			DMA_InitStruct.DMA_MBTW = DMA_BYTE_TRANS;       // 内存访问位宽， 0:byte, 1:half-word, 2:word 
			DMA_InitStruct.DMA_REQ_EN = DMA_CH3_CAN_REQ_EN; // CAN DMA请求使能，高有效 
			DMA_InitStruct.DMA_TIMES = 5;                   // DMA 通道 x 每轮数据搬运次数 1~511 
			DMA_InitStruct.DMA_ROUND = 5;                   // DMA 通道 x 采样轮数 1~255 
			DMA_InitStruct.DMA_CPAR = (u32)&CAN_TXRX0;      // DMA 通道 x 外设地址
			DMA_InitStruct.DMA_CMAR = (u32)memaddr;         // DMA 通道 x 内存地址 
			DMA_Init(DMA_CH3, &DMA_InitStruct);
			DMA_CHx_EN(DMA_CH3,ENABLE);                     //使能DMA_CH3通道
  @endcode   
 *@par 修改日志:   
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2015年11月26日 <td>1.0     <td>Howlet Li       <td>创建
 * </table>
 *@par 修改日志:去除初始化使能DMA通道，改为DMA_CHx_EN（）函数使能DMA通道
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月11日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void DMA_Init(DMA_RegTypeDef *DMAx, DMA_InitTypeDef *this)
{
    // DMA0_CTRL  = 0x0001;  // DMA整体使能
    DMA_Enable();
    /* 通道配置寄存器 斌值 */
    DMAx->CCR = 0;
    DMAx->CTMS  =   this->TMS;
    DMAx->SADR  =   this->SADR;
    DMAx->DADR  =   this->DADR;
    DMAx->REN   =   this->REN.R;
    DMAx->CCR   =   (this->SBTW     <<  10) | (this->DBTW   <<  8 ) |
                    (this->SINC     <<  6 ) | (this->DINC   <<  4 ) |
                    (this->CIRC     <<  3 ) | (this->RMODE  <<  1 ) |
                    (this->EN);
    if (this->IRQ_EN)
        switch ((u32)DMAx)
        {
        case DMA0_BASE:
            DMA0_IE |= BIT0;
            break;
        case DMA0_BASE + 0x20:
            DMA0_IE |= BIT1;
            break;
        case DMA0_BASE + 0x40:
            DMA0_IE |= BIT2;
            break;
        case DMA0_BASE + 0x60:
            DMA0_IE |= BIT3;
            break;
        }
    DMA0_CTRL = 0x0001; /*enable dma, mcu has higher priorit */
}  

/**
 *@brief @b 函数名称:   uint32_t DMA_GetIRQFlag(DMA_RegTypeDef *DMAx  , u32 timer_if)
 *@brief @b 功能描述:   获取DMA中断标志
 *@see被引用内容：       DMAx可选： DMA_CH0 ， DMA_CH1 ， DMA_CH2 ， DMA_CH3
 *@param输入参数：       DMAx：DMA通道选择  \n
                        timer_if参数可选： 
 * <table>              <tr><td> 宏定义          <td>说明
                        <tr><th> DMA_CH0_FIF    <td>通道 0 完成中断标志
 *					    <tr><th> DMA_CH1_FIF    <td>通道 1 完成中断标志
 *						<tr><th> DMA_CH2_FIF	<td>通道 2 完成中断标志
 *						<tr><th> DMA_CH3_FIF    <td>通道 3 完成中断标志
 *						<tr><th> DMA_CH0_EIF    <td>通道 0 错误中断标志
 *						<tr><th> DMA_CH1_EIF    <td>通道 1 错误中断标志
 *						<tr><th> DMA_CH2_EIF    <td>通道 2 错误中断标志
 *						<tr><th> DMA_CH3_EIF    <td>通道 3 错误中断标志
 * </table>  
 *@see 
 *@param输出参数：       无
 *@return返 回 值：      无
 *@note其它说明：        无
 *@warning              只有对应中断使能后，改为才能读取，如果对应中断未使能，读取结果一直为0   
 *@par 示例代码：
 *@code    
           if(DMA_GetIRQFlag(DMA_CH0,DMA_CH0_FIF))//获取DMA通道0完成中断标志
		   {	
		   }
  @endcode    
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月11日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
u32 DMA_GetIRQFlag(u32 DMA_IF_x)
{
    if (DMA0_IF & DMA_IF_x & DMA0_IE)
    {
        return 1;
    }
    return 0;
}

/**
 *@brief @b 函数名称:   void DMA_ClearIRQFlag(DMA_RegTypeDef *DMAx , uint32_t tempFlag)
 *@brief @b 功能描述:   清除DMA中断标志
 *@see 被引用内容：      DMAx可选： DMA_CH0 ， DMA_CH1 ， DMA_CH2 ， DMA_CH3
 *@param 输入参数：      DMAx：DMA通道选择  \n 
                        timer_if参数可选： 
 * <table>              <tr><td> 宏定义          <td>说明
                        <tr><th> DMA_CH0_FIF    <td>通道 0 完成中断标志
 *					    <tr><th> DMA_CH1_FIF    <td>通道 1 完成中断标志
 *						<tr><th> DMA_CH2_FIF	<td>通道 2 完成中断标志
 *						<tr><th> DMA_CH3_FIF    <td>通道 3 完成中断标志
 *						<tr><th> DMA_CH0_EIF    <td>通道 0 错误中断标志
 *						<tr><th> DMA_CH1_EIF    <td>通道 1 错误中断标志
 *						<tr><th> DMA_CH2_EIF    <td>通道 2 错误中断标志
 *						<tr><th> DMA_CH3_EIF    <td>通道 3 错误中断标志
 * </table>   
 * 
 *@param 输出参数：   无
 *@return 返 回 值：  无
 *@note 其它说明：    无
 *@warning           无
 *@par 示例代码：
 *@code    
           if(DMA_GetIRQFlag(DMA_CH0,DMA_CH0_FIF))//获取DMA通道0完成中断标志
		   {	
			  DMA_ClearIRQFlag(DMA_CH0,DMA_CH0_FIF)//清除DMA通道0完成中断标志
		   }
  @endcode 
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author    <th>Description
 * <tr><td>2023年2月11日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void DMA_ClearIRQFlag(u32 DMA_IF_x)
{
    DMA0_IF = DMA_IF_x;
}

/**
 *@brief @b 函数名称:   void DMA_Enable(void)
 *@brief @b 功能描述:   DMA模块 使能函数
 *@see 被引用内容：      DMAx可选： DMA_CH0 ， DMA_CH1 ， DMA_CH2 ， DMA_CH3
 *@param 输入参数：   无
 *@param 输出参数：   无
 *@return 返 回 值：  无
 *@note 其它说明：    无
 *@warning           无
 *@par 示例代码：
 *@code    
  @endcode 
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author    <th>Description
 * <tr><td>2023年2月11日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void DMA_Enable(void)
{
    DMA_TOP->CTRL = 1;
}
/**
 *@brief @b 函数名称:   void DMA_Enable(void)
 *@brief @b 功能描述:   DMA模块 关闭函数
 *@see 被引用内容：   
 *@param 输入参数：   无
 *@param 输出参数：   无
 *@return 返 回 值：  无
 *@note 其它说明：    无
 *@warning           无
 *@par 示例代码：
 *@code    
  @endcode 
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author    <th>Description
 * <tr><td>2023年2月11日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void DMA_Disable(void)
{
    DMA_TOP->CTRL = 0;
}

/**
 *@brief @b 函数名称:   void DMA_SetAddr(DMA_RegTypeDef *DMA_CHx, u32 addr1, u32 addr2)
 *@brief @b 功能描述:   DMA传输地址设置
 *@see 被引用内容：    
 *@param 输入参数：   
 *                      DMA_CHX :DMA 通道选择 DMA_CH0 ， DMA_CH1 ， DMA_CH2 ， DMA_CH3
 *                      addr1 : 源地址设置
 *                      addr2 ：目的地址设置
 *@param 输出参数：   无
 *@return 返 回 值：  无
 *@note 其它说明：    无
 *@warning           无
 *@par 示例代码：
 *@code    
  @endcode 
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author    <th>Description
 * <tr><td>2023年2月11日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void DMA_SetAddr(DMA_RegTypeDef *DMA_CHx, u32 addr1, u32 addr2)
{
    DMA_CHx->CCR = DMA_CHx->CCR & ~BIT0;
    DMA_CHx->SADR = addr1;
    DMA_CHx->DADR = addr2;
    DMA_CHx->CCR = DMA_CHx->CCR | BIT0;
}

/**
 *@brief @b 函数名称:   void DMA_SetLength(DMA_RegTypeDef *DMA_CHx, u32 len)
 *@brief @b 功能描述:   DMA传输长度设置
 *@see 被引用内容：     
 *@param 输入参数：   
 *                      DMA_CHX :DMA 通道选择 DMA_CH0 ， DMA_CH1 ， DMA_CH2 ， DMA_CH3
 *                      len : 传输长度设置
 *@param 输出参数：   无
 *@return 返 回 值：  无
 *@note 其它说明：    无
 *@warning           无
 *@par 示例代码：
 *@code    
  @endcode 
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author    <th>Description
 * <tr><td>2023年2月11日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void DMA_SetLength(DMA_RegTypeDef *DMA_CHx, u32 len)
{
    DMA_CHx->CCR = DMA_CHx->CCR & ~BIT0;
    DMA_CHx->CTMS = len;
    DMA_CHx->CCR = DMA_CHx->CCR | BIT0;
}

/**
 *@brief @b 函数名称:   void DMA_Trigger(DMA_RegTypeDef *DMA_CHx)
 *@brief @b 功能描述:   DMA 软件触发设置
 *@see 被引用内容：     
 *@param 输入参数：   
 *                      DMA_CHX :DMA 通道选择 DMA_CH0 ， DMA_CH1 ， DMA_CH2 ， DMA_CH3
 *@param 输出参数：   无
 *@return 返 回 值：  无
 *@note 其它说明：    无
 *@warning           无
 *@par 示例代码：
 *@code    
  @endcode 
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author    <th>Description
 * <tr><td>2023年2月11日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void DMA_Trigger(DMA_RegTypeDef *DMA_CHx)
{
    DMA_CHx->REN |= BIT31;
}

/**
 *@brief @b 函数名称:   void DMA_SetRequest(DMA_RegTypeDef *DMA_CHx, u32 DMA_REQ_x)
 *@brief @b 功能描述:   DMA 外设请求使能
 *@see 被引用内容：     
 *@param 输入参数：   
 *                      DMA_CHX :DMA 通道选择 DMA_CH0 ， DMA_CH1 ， DMA_CH2 ， DMA_CH3
 *                      DMA_REQ_x ：参数可选: \n
 * <table> 
 *                       <tr><td> 宏定义                   <td>原始值   <td>说明
 *                      <tr><th> DMA_REQ_UART1_TX <td> BIT19
 *                      <tr><th> DMA_REQ_UART1_RX <td> BIT18
 *                      <tr><th> DMA_REQ_UART0_TX <td> BIT17
 *                      <tr><th> DMA_REQ_UART0_RX <td> BIT16
 *                      <tr><th> DMA_REQ_I2C0_TX  <td>  BIT15 
 *                      <tr><th> DMA_REQ_I2C0_RX  <td>  BIT14 
 *                      <tr><th> DMA_REQ_MCPWM1   <td> BIT13  
 *                      <tr><th> DMA_REQ_MCPWM0   <td> BIT12  
 *                      <tr><th> DMA_REQ_SPI_TX   <td> BIT11  
 *                      <tr><th> DMA_REQ_SPI_RX    <td> BIT10  
 *                      <tr><th> DMA_REQ_TIMER4   <td> BIT7   
 *                      <tr><th> DMA_REQ_TIMER3    <td> BIT6   
 *                      <tr><th> DMA_REQ_TIMER2    <td> BIT5   
 *                      <tr><th> DMA_REQ_TIMER1    <td> BIT4   
 *                      <tr><th> DMA_REQ_TIMER0    <td> BIT3   
 *                      <tr><th> DMA_REQ_DSP    <td> BIT2      
 *                      <tr><th> DMA_REQ_ADC1   <td> BIT1     
 *                      <tr><th> DMA_REQ_ADC0   <td> BIT0      
 * </table>
 *@param 输出参数：   无
 *@return 返 回 值：  无
 *@note 其它说明：    无
 *@warning           无
 *@par 示例代码：
 *@code    
  @endcode 
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author    <th>Description
 * <tr><td>2023年2月11日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void DMA_SetRequest(DMA_RegTypeDef *DMA_CHx, u32 DMA_REQ_x)
{
    DMA_CHx->REN = DMA_REQ_x;
}


/**
 *@brief @b 函数名称:  void DMA_CHx_EN(DMA_RegTypeDef *DMAx,u32 Channel_EN)
 *@brief @b 功能描述:   DMA通道使能
 *@see 被引用内容：     
 *@param 输入参数：   
 *                      DMA_CHX :DMA 通道选择 DMA_CH0 ， DMA_CH1 ， DMA_CH2 ， DMA_CH3
 *                      Channel_EN : ENABLE/DISABLE
 *@param 输出参数：   无
 *@return 返 回 值：  无
 *@note 其它说明：    无
 *@warning           无
 *@par 示例代码：
 *@code    
  @endcode 
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author    <th>Description
 * <tr><td>2023年2月11日 <td>1.1     <td>ywx   <td>修改
 * </table>
 */
void DMA_CHx_EN(DMA_RegTypeDef *DMAx,u32 Channel_EN)
{
   if(Channel_EN)
	 {
	   DMAx->CCR  |= BIT0;/*使能DMA搬运*/
	 }else{
	   DMAx->CCR  &= ~BIT0; /*关闭通道使能*/
	 }
}

