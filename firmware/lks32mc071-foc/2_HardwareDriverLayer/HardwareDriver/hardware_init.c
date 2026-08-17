/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： hardware_init.c
 * 文件标识：
 * 内容摘要： 硬件初始化代码
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： HuangMG
 * 完成日期： 2023年3月2日
 *
 *******************************************************************************/
#include "basic.h"
#include "hardware_config.h"
#include "MC_Parameter_M0.h"


void UART_init(void);
void HALL_Perip_Init(void);
void SoftDelay(u32 cnt);
void TempSensor_Init(void);

void DAC_init(void);
void CMP_init(void);
void UTimer_init(void);
void GPIO_init(void);
void UART1_init(void);
void ADC0_init(void);
void ADC1_init(void);
void get_ic_temp_init(void);
void Clock_Init(void);
void Hardware_init(void);
void HALL_init(void);

extern void registerEPWM0_DrvLevel(void);
extern void registerEPWM1_DrvLevel(void);
extern void ADC_1Shunt_NormalModeCFG(void);
extern void ADC_2Shunt_NormalModeCFG(void);
extern void ADC_3Shunt_NormalModeCFG(void);

void PGA_init(void);
void MCPWM_ch012_init(void);
void MCPWM_ch345_init(void);

extern	PSTR_DrvCfgPara getCfgParaPtr(u8 objID);
extern	u16 getPWMPrd(PSTR_DrvCfgPara pDrvCfgPara);
extern	u16 getDeadTime(PSTR_DrvCfgPara pDrvCfgPara);

/*******************************************************************************
 函数名称：    void SoftDelay(void)
 功能描述：    软件延时函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;

    for(t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }

}

/*******************************************************************************
 函数名称：    void Hardware_init(void)
 功能描述：    硬件部分初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/3/2      V1.0          HuangMG            创建
 *******************************************************************************/
void Hardware_init(void)
{
	__disable_irq();					/* 关闭中断 中断总开关 */
	SYS_WR_PROTECT = 0x7a83;
	SYS_DBG_CFG |= BIT14;				/* 软件复位通用寄存器*/
	
	FLASH_CFG |= 0x00080000;			/* enable prefetch */
    IWDG_DISABLE();						/* 关闭看门狗*/

	DSP_Init();							/* DSP模块初始化*/
	UART_init();						/* 串口初始化UART0*/
	ADC0_init();						/* ADC初始化 */
	ADC1_init();						/* ADC初始化 */
	GPIO_init();					  	/* GPIO初始化 */	
	
	#if	(EPWM0_USED == FUNCTION_ON)
	MCPWM_ch012_init();					/* PWM初始化 */
	#endif
	
	#if	(EPWM1_USED == FUNCTION_ON)
	MCPWM_ch345_init();					/* PWM初始化 */
	#endif

	UTimer_init();						/* 通用计数器初始化 */
	
	DAC_init();							/* DAC 初始化 */
	PGA_init();							/* PGA 初始化 */
	CMP_init();							/* 比较器初始化 */
    HALL_init();						/* HALL模块初始化 */
	TempSensor_Init();					/* 温度传感器初始化 */
    SoftDelay(100);						/* 等待硬件初始化完毕*/

	//中断优先级设置
    NVIC_SetPriority(TIMER0_IRQn, 2);	/*TIMER0中断优先级配置*/
    NVIC_SetPriority(HALL0_IRQn, 2);	/*HALL0_IRQn中断优先级配置*/
    NVIC_SetPriority(ADC0_IRQn, 1);		/*ADC0中断优先级配置*/
	NVIC_SetPriority(ADC1_IRQn, 1); 	/*ADC0中断优先级配置*/

    NVIC_SetPriority(MCPWM0_IRQn, 1);	/*MCPWM0中断优先级配置*/

#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)	
	NVIC_EnableIRQ (MCPWM0_IRQn);		//中断使能设置
#else
	NVIC_EnableIRQ(ADC0_IRQn);		  /* enable the ADC0 interrupt */
#endif

	//NVIC_EnableIRQ(ADC1_IRQn);
	NVIC_EnableIRQ (TIMER0_IRQn);
	
    SYS_WR_PROTECT = 0;               /* 关闭系统寄存器写操作*/

    //__enable_irq();                   /* 开启总中断 */
}


/*******************************************************************************
 函数名称：    void Clock_Init(void)
 功能描述：    时钟配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/3/2      V1.0          HuangMG            创建
 *******************************************************************************/
void Clock_Init(void)
{
	SYS_WR_PROTECT = 0x7a83;		 /* 解除系统寄存器写保护 */
	SYS_SFT_RST = 0xffffffff;	
	SYS_SFT_RST = 0;
	SYS_AFE_REG5 = BIT15;			 /* BIT15:PLLPDN 开PLL */
	SYS_AFE_REG6 &= ~0300;			 /* 配置为4.0V监控，可根据实际配置其它档位：3.25V/3.5V/3.75V/4.0V */
	while(SYS_AFE_DBG & BIT15) {;}	 /*  等待外部5VOK */
	SoftDelay(100); 				 /* 延时100us, 等待PLL稳定 21.4.17*/
	SYS_CLK_CFG = 0x000011ff;		 /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff对应96M时钟 */
	SYS_WR_PROTECT = 0; 			 /* 关闭系统寄存器写操作*/
}

/*******************************************************************************
 函数名称：    void Reg_Clr(void)
 功能描述：    寄存器清零
 输入参数：    addr ：需要清零寄存器的起始地址 
               nSize：需要清零的寄存器个数
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/3/2      V1.0          HuangMG            创建
 *******************************************************************************/
void Reg_Clr(u32 addr, u8 nSize)
{
   while(nSize --)
   {
      REG32(addr) = 0;
      addr += 4;
   }
}


/*******************************************************************************
 函数名称：    void SystemInit(void)
 功能描述：    硬件系统初始化，调用时钟初始化函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/3/2      V1.0          HuangMG            创建
 *******************************************************************************/
void SystemInit (void)
{
    Clock_Init();  /* 时钟初始化 */
}

/*******************************************************************************
 函数名称：    void PGA_init(void)
 功能描述：    根据配置进行PGA初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/1/15      V1.0           Li Tonghua          创建
 *******************************************************************************/
void PGA_init(void)
{
	u16 OPA_mode;
	PSTR_DrvCfgPara	pParaPtr;

	OPA_InitTypeDef OPA_InitStruct;
    OPA_StructInit(&OPA_InitStruct);

	pParaPtr	= getCfgParaPtr(0);
	OPA_mode	= pParaPtr->mS_GlobalCfg.m_bOPAValue;

	OPA_InitStruct.OPA_IT		= PGA_IT_1;			/*opa偏置电流调节*/
    OPA_InitStruct.OPA_CLEna	= ENABLE;			/*使能OPA*/
    //选择160：10k，外接的是两个1k 放大倍数160/12 = 13.3333
	OPA_InitStruct.OPA_Gain		= OPA_mode;
	
	OPA_Init(OPA0, &OPA_InitStruct);
	OPA_Init(OPA1, &OPA_InitStruct);
	OPA_Init(OPA2, &OPA_InitStruct);
	OPA_Init(OPA3, &OPA_InitStruct); 
}

/*******************************************************************************
 函数名称：    void CMP_init(void)
 功能描述：    CMP初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
2023/02/22      V1.0           Olive Wang          创建
 *******************************************************************************/
void CMP_init(void)
{
    CMP_InitTypeDef CMP_InitStre;
    CMP_StructInit(&CMP_InitStre);

    //数字模块时钟使能
    SYS_ModuleClockCmd(SYS_Module_CMP, ENABLE);   //add


    CMP_InitStre.CLK_COM_DIV	= 0;					/* 比较器共用滤波时钟分频*/
    CMP_InitStre.FT				= DISABLE;				/* 比较器快速比较 30ns*/
    CMP_InitStre.HYS			= CMP_HYS_0mV; //CMP_HYS_20mV;	/* 比较器滞回电压*/


    //CMP0 config
    CMP_InitStre.CMP0.SELP			= CMP0_SELP_IP1;			/* 比较器0正端信号选择 */
    CMP_InitStre.CMP0.SELN			= CMP_SELN_REF; 			/* 比较器0负端信号选择 */
    CMP_InitStre.CMP0.RE			= DISABLE;					/* 比较器0DMA失能*/
    CMP_InitStre.CMP0.POL			= CMP_HIGH_LEVEL;			/* 比较器0高电平输出有效*/
    CMP_InitStre.CMP0.IRQ_TRIG		= IRQ_LEVEL_TRIG_MODE;		/* 比较器0电平触发中断模式*/
    CMP_InitStre.CMP0.IN_EN			= DISABLE;					/* 比较器0信号输入使能 */
    CMP_InitStre.CMP0.IE			= DISABLE;					/* 比较器0信号中断使能 */
    CMP_InitStre.CMP0.FIL_CLK_DIV16 = 2; 						/* 即滤波宽度=tclk 周期*16*CMP_FltCnt (CMP_FltCnt分频系数,0~15)*/
    CMP_InitStre.CMP0.FIL_CLK_DIV2	= 2;  						/* 比较器 2/1/0 滤波时钟使能 */
    CMP_InitStre.CMP0.CLK_EN		= DISABLE;					/* 比较器时钟使能*/
    CMP_InitStre.CMP0.EN			= DISABLE;					/* 比较器0开关 操作SYS_AFE_REG5 */

    //CMP1 config
    CMP_InitStre.CMP1.SELP			= CMP1_SELP_IP0;			/* 比较器1正端信号选择 */
    CMP_InitStre.CMP1.SELN			= CMP_SELN_DAC0;			/* 比较器1负端信号选择 */
    CMP_InitStre.CMP0.RE			= DISABLE;					/* 比较器1DMA失能*/
    CMP_InitStre.CMP1.POL			= CMP_HIGH_LEVEL;			/* 比较器1高电平输出有效*/
    CMP_InitStre.CMP1.IRQ_TRIG		= IRQ_LEVEL_TRIG_MODE;		/* 比较器1电平触发中断模式*/
    CMP_InitStre.CMP1.IN_EN			= DISABLE;					/* 比较器1信号输入使能 */
    CMP_InitStre.CMP1.IE			= DISABLE;					/* 比较器1信号中断使能 */
    CMP_InitStre.CMP1.FIL_CLK_DIV16	= 2; 						/* 即滤波宽度=tclk 周期*16*CMP_FltCnt (CMP_FltCnt分频系数,0~15)*/
    CMP_InitStre.CMP1.FIL_CLK_DIV2	= 2;  						/* 比较器 2/1/0 滤波时钟使能 */
    CMP_InitStre.CMP1.CLK_EN		= ENABLE;					/* 比较器时钟使能*/
    CMP_InitStre.CMP1.EN			= ENABLE;					/* 比较器0开关 操作SYS_AFE_REG5 */

    CMP_Init(&CMP_InitStre);									/* 比较器初始化 */
    //CMP_Cmd(CMP_CHN_0, ENABLE); /* 比较器0时钟使能*/
    CMP_Cmd(CMP_CHN_1, ENABLE); /* 比较器1时钟使能*/
}

/*******************************************************************************
 函数名称：    void DAC_init(void)
 功能描述：    DAC初始化(通常不会同时输出 DAC0 和 DAC1，以免造成信号竞争。)
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
2023/02/22      V1.0           Olive Wang          创建
 *******************************************************************************/
void DAC_init(void)
{
	s16 nDACRef;
	s32 wDACCmp;
	PSTR_DrvCfgPara	pParaPtr;

	DAC_InitTypeDef DAC_InitStre;
    DAC_StructInit(&DAC_InitStre);				/* DAC结构体初始化 */
	
	//默认 epwm0 ----- dac0
	//双电机添加配置功能

	pParaPtr	= getCfgParaPtr(0);
	wDACCmp	= (s32)pParaPtr->mS_FBCurSense.nHardOvCurVolt;	

	DAC_InitStre.DAC_GAIN = DAC_RANGE_1V2;		/*DAC输出量程为1.20V*/
    DAC_InitStre.DACOUT_EN = DISABLE;			/*使能DAC输出*/
    DAC_InitStre.TIG_CH_EN = DISABLE;			/*是否使能UTIMER触发步进*/
    DAC_InitStre.DAC_STEP = 0;					/*步进值为0*/
    DAC_Init(DAC_Channel_0, &DAC_InitStre);		/* DAC初始化 */
  
    if(DAC_InitStre.DAC_GAIN 		== DAC_RANGE_1V2)
    {/* 加载DAC 1.2V量程校正值 */
		nDACRef			= 1200;
    }   
    else if(DAC_InitStre.DAC_GAIN	== DAC_RANGE_4V85)
    { /* 加载DAC 4.85V量程校正值 */
		nDACRef			= 4850;
	}

	wDACCmp		= (wDACCmp * 4096)/nDACRef;
	wDACCmp		= sat(wDACCmp,0,4095);

	//设置DAC的数值
    DAC_OutputValue(DAC_Channel_0, wDACCmp) ;	/* 根据母线采样电阻计算保护值*/

    DAC_Cmd(DAC_Channel_0, ENABLE);				/*使能DAC时钟*/
}

/*******************************************************************************
 函数名称：    void UART_init(void)
 功能描述：    UART0寄存器配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UART_init(void)
{

    UART_InitTypeDef UART_InitStruct;

    UART_StructInit(&UART_InitStruct);
    UART_InitStruct.BaudRate = 115200;                 /* 设置波特率38400 */
    UART_InitStruct.WordLength = UART_WORDLENGTH_8b;  /* 发送数据长度8位 */
    UART_InitStruct.StopBits = UART_STOPBITS_1b;
    UART_InitStruct.FirstSend = UART_FIRSTSEND_LSB;   /* 先发送LSB */
    UART_InitStruct.ParityMode = UART_Parity_NO;      /* 无奇偶校验 */
    UART_InitStruct.IRQEna = UART_IF_RcvOver;
    UART_Init(UART0, &UART_InitStruct);

}

/*******************************************************************************
 函数名称：    void UART0_SENDDATA(void)
 功能描述：    UART0发送程序
 输入参数：    n：需要发送的值
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UART0_SENDDATA(UINT8 n)
{
    UART0_BUFF = n;
}

/*******************************************************************************
 函数名称：    void UART0_init(void)
 功能描述：    UART1寄存器配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UART1_init(void)
{
    UART_InitTypeDef UART_InitStruct;
    
    UART_StructInit(&UART_InitStruct);
    UART_InitStruct.BaudRate = 38400;                 /* 设置波特率38400 */
    UART_InitStruct.WordLength = UART_WORDLENGTH_8b;  /* 发送数据长度8位 */
    UART_InitStruct.StopBits = UART_STOPBITS_1b;
    UART_InitStruct.FirstSend = UART_FIRSTSEND_LSB;   /* 先发送LSB */
    UART_InitStruct.ParityMode = UART_Parity_NO;      /* 无奇偶校验 */
    UART_InitStruct.IRQEna = 0;
    UART_Init(UART1, &UART_InitStruct);
}


/*******************************************************************************
 函数名称：    void UART1_SENDDATA(void)
 功能描述：    UART1发送程序
 输入参数：    n：需要发送的值
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UART1_SENDDATA(UINT8 n)
{
    UART1_BUFF = n;
}

/*******************************************************************************
 函数名称：    void ADC0_init(void)
 功能描述：    ADC0硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void ADC0_init(void)
{
    ADC_InitTypeDef ADC_InitStructure;

    //ADC0设置
    ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.RE         = 0;                   // DMA请求使能
    ADC_InitStructure.DATA_ALIGN = DISABLE;             // DAT右对齐使能
    ADC_InitStructure.CSMP       = DISABLE;             // 连续采样使能
    ADC_InitStructure.TCNT       = 0;                   // 触发一次采样所需的事件数 0：表示需要发生 1 次事件才能触发一次采样  8KHZ
    //                          1：表示需要发生 2 次事件才能触发一次采样  16KHZ
    ADC_InitStructure.TROVS      = DISABLE;             // 手动触发过采样使能，开启后一次采样需要多次触发
    ADC_InitStructure.OVSR       = 0;                   // 过采样率

#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    ADC_InitStructure.TRIG       = ADC_TRIG_MCPWM0_T0 | ADC_TRIG_MCPWM0_T1; // 比较点t0 ,t1触发信号
    ADC_InitStructure.NSMP       = 1;                    // 0:单段采样， 1:两段采样
    ADC_InitStructure.IE         = 0;                    // 第二段常规采样完成中断使能  不使能ADC0

    ADC_InitStructure.S1         = 2;                   // 第一段常规采样次数 2
    ADC_InitStructure.S2         = 4;                   // 第二段常规采样次数 4
    ADC_InitStructure.IS1        = 0;                   // 空闲采样次数

#else
#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
    ADC_InitStructure.TRIG       = ADC_TRIG_MCPWM0_T0;  // 触发信号
    ADC_InitStructure.NSMP       = 0;                    // 0:单段采样， 1:两段采样
    ADC_InitStructure.IE		 = ADC_SF1_IE;         // 第一段常规采样完成中断使能
    ADC_InitStructure.S1         = 6;                   // 第一段常规采样次数
    ADC_InitStructure.S2         = 0;                   // 第二段常规采样次数
    ADC_InitStructure.IS1        = 0;                   // 空闲采样次数

#else
#if ((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
    ADC_InitStructure.TRIG       = ADC_TRIG_MCPWM0_T0;  // 触发信号
    ADC_InitStructure.NSMP       = 0;                    // 0:单段采样， 1:两段采样
    ADC_InitStructure.IE          = ADC_SF1_IE;          // 第一段常规采样完成中断使能
    ADC_InitStructure.S1         = 6;                   // 第一段常规采样次数
    ADC_InitStructure.S2         = 0;                   // 第二段常规采样次数
    ADC_InitStructure.IS1        = 0;                   // 空闲采样次数
#endif
#endif
#endif
    ADC_InitStructure.LTH        = 0;                   // ADC 模拟看门狗 0 下阈值
    ADC_InitStructure.HTH        = 0;                   // ADC 模拟看门狗 0 上阈值
    ADC_InitStructure.GEN        = DISABLE;             // ADC 模拟看门狗 0 对应使能位
    ADC_Init(ADC0, &ADC_InitStructure);

    ADC_ClearIRQFlag(ADC0, ADC_ALL_IF);//清除所有中断标志位
	

    #if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    ADC_1Shunt_NormalModeCFG();
	#elif (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
	ADC_2Shunt_NormalModeCFG();
	#elif ((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET)) 
	ADC_3Shunt_NormalModeCFG();
	#endif

    ADC0_STATE_RESET();  //复位一下
}

/*******************************************************************************
 函数名称：    void ADC0_init(void)
 功能描述：    ADC0硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void ADC1_init(void)
{
    ADC_InitTypeDef ADC_InitStructure;

    //ADC0设置
    ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.RE         = 0;                   // DMA请求使能
    ADC_InitStructure.DATA_ALIGN = DISABLE;              // DAT右对齐使能
    ADC_InitStructure.CSMP       = DISABLE;             // 连续采样使能
    ADC_InitStructure.TCNT       = 0;                   // 触发一次采样所需的事件数 0：表示需要发生 1 次事件才能触发一次采样  8KHZ
    //                          							1：表示需要发生 2 次事件才能触发一次采样  16KHZ
    ADC_InitStructure.TROVS      = DISABLE;             // 手动触发过采样使能，开启后一次采样需要多次触发
    ADC_InitStructure.OVSR       = 0;                   // 过采样率
	

    ADC_InitStructure.TRIG       = ADC_TRIG_MCPWM0_T0;  // 触发信号
    ADC_InitStructure.NSMP       = 0;                    // 0:单段采样， 1:两段采样
    ADC_InitStructure.IE         = ADC_SF1_IE;			// 第一段常规采样完成中断使能
    ADC_InitStructure.S1         = 4;                   // 第一段常规采样次数
    ADC_InitStructure.S2         = 0;                   // 第二段常规采样次数
    ADC_InitStructure.IS1        = 0;                   // 空闲采样次数

    ADC_InitStructure.LTH        = 0;                   // ADC 模拟看门狗 0 下阈值
    ADC_InitStructure.HTH        = 0;                   // ADC 模拟看门狗 0 上阈值
    ADC_InitStructure.GEN        = DISABLE;             // ADC 模拟看门狗 0 对应使能位
    ADC_Init(ADC1, &ADC_InitStructure);
	
    ADC_ClearIRQFlag(ADC1, ADC_ALL_IF);
	

    #if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    ADC_1Shunt_NormalModeCFG();
	#elif (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
	ADC_2Shunt_NormalModeCFG();
	#elif ((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET)) 
	ADC_3Shunt_NormalModeCFG();
	#endif

    ADC1_STATE_RESET();  //复位一下
}
/*******************************************************************************
 函数名称：    void HALL_init(void)
 功能描述：    HALL初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
2023/02/22      V1.0           Olive Wang          创建
 *******************************************************************************/
void HALL_init(void)
{
    HALL_InitTypeDef HALL_InitStruct;

    HALL_StructInit(&HALL_InitStruct);

    HALL_InitStruct.FilterLen = 512;                /* Hall信号数字滤波长度 512个时钟周期 */
    HALL_InitStruct.ClockDivision = HALL_CLK_DIV1;  /* 设置Hall模块时钟分频系数 */
    HALL_InitStruct.Filter75_Ena = DISABLE;         /* Hall信号滤波方式，7判5模式或者全1有效模式 */
    HALL_InitStruct.HALL_Ena = ENABLE;              /* 模块使能 */

    HALL_InitStruct.Capture_IRQ_Ena = ENABLE;		/* 捕捉中断使能 */
    HALL_InitStruct.OverFlow_IRQ_Ena = ENABLE;		/* 超时中断使能 */
    HALL_InitStruct.softIE = DISABLE;               /* 软件中断失能 */

    HALL_InitStruct.CountTH = 9600000;				/* Hall模块计数模值，计数超过模值会产生超时中断 */

    HALL_Init(&HALL_InitStruct);/* HALL初化 */
    HALL_Cmd(ENABLE);/* HALL使能 */
}

/*******************************************************************************
 函数名称：    void GPIO_init(void)
 功能描述：    GPIO硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/3/2      V1.0          HuangMG            创建
 *******************************************************************************/
void GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct);

	/*配置 MCPWM   ch0~ch2 P1.4~P1.9 */
	#if	(EPWM0_USED == FUNCTION_ON)
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_4, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_5, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_6, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_7, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_8, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_9, AF3_MCPWM);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_Init(GPIO1, &GPIO_InitStruct);
	#endif

	/*配置 MCPWM  ch3~ch5 */
	#if	(EPWM1_USED == FUNCTION_ON)
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_10, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_11, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_3, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_4, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_5, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_6, AF3_MCPWM);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 ;
    GPIO_Init(GPIO1, &GPIO_InitStruct);
		
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 ;
	GPIO_Init(GPIO0, &GPIO_InitStruct);
	#endif

//	//配置P2.7 UTIMER0_CH0
//	GPIO_StructInit(&GPIO_InitStruct); //初始化结构体
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO输出模式
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
//	GPIO_Init(GPIO2, &GPIO_InitStruct);
//	GPIO_PinAFConfig(GPIO2, GPIO_PinSource_7, AF7_TIMER01); //P2.7复用为timer0的输出模式



//	/* P1.10-RX0, P1.11-TX0  UART0 */
//	GPIO_StructInit(&GPIO_InitStruct);
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_10 ;
//	GPIO_Init(GPIO1, &GPIO_InitStruct);

//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_11;
//	GPIO_Init(GPIO1, &GPIO_InitStruct);

//	GPIO_PinAFConfig(GPIO1, GPIO_PinSource_10, AF4_UART);
//	GPIO_PinAFConfig(GPIO1, GPIO_PinSource_11, AF4_UART);


//	GPIO_StructInit(&GPIO_InitStruct);
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_8 ;
//	GPIO_Init(GPIO2, &GPIO_InitStruct);

//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_9;
//	GPIO_Init(GPIO3, &GPIO_InitStruct);

//	GPIO_PinAFConfig(GPIO2, GPIO_PinSource_8, AF4_UART);
//	GPIO_PinAFConfig(GPIO3, GPIO_PinSource_9, AF4_UART);

//	/* P0.6-LED1  P0.7-LED2*/
//	GPIO_StructInit(&GPIO_InitStruct);
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 ;
//	GPIO_Init(GPIO0, &GPIO_InitStruct);

//	/* P0.15-RX0, P1.0-TX0  UART0 */
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_0;//RX0
//	GPIO_Init(GPIO1, &GPIO_InitStruct);

//	/* P0.15-RX0, P1.0-TX0  UART0 */
//	GPIO_PinAFConfig(GPIO0, GPIO_PinSource_15, AF4_UART);
//	GPIO_PinAFConfig(GPIO1, GPIO_PinSource_0, AF4_UART);

//	/*UART1 IO口初始化*/
//	GPIO_StructInit(&GPIO_InitStruct);
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_8 ;//RX1
//	GPIO_Init(GPIO2, &GPIO_InitStruct);

//	GPIO_StructInit(&GPIO_InitStruct);
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_9 ;//TX1
//	GPIO_Init(GPIO3, &GPIO_InitStruct);
//	GPIO_PinAFConfig(GPIO2, GPIO_PinSource_8, AF4_UART);
//	GPIO_PinAFConfig(GPIO3, GPIO_PinSource_9, AF4_UART);

//	#if (ROTOR_SENSOR_TYPE == ROTOR_HALL_SENSOR) 
//	GPIO_StructInit(&GPIO_InitStruct);
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
//	GPIO_Init(GPIO2, &GPIO_InitStruct);
//	GPIO_PinAFConfig(GPIO2, GPIO_PinSource_4, AF2_HALL);
//	GPIO_PinAFConfig(GPIO2, GPIO_PinSource_5, AF2_HALL);
//	GPIO_PinAFConfig(GPIO2, GPIO_PinSource_6, AF2_HALL);
//	#endif

//	/* PWM占空比调速检测 */
//	GPIO_StructInit(&GPIO_InitStruct);
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_8 ;
//	GPIO_Init(GPIO2, &GPIO_InitStruct);
//	GPIO_PinAFConfig(GPIO2, GPIO_PinSource_8, AF8_TIMER23);		
}

/*******************************************************************************
 函数名称：    void UTimer_init(void)
 功能描述：    UTimer硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/3/2      V1.0          HuangMG            创建
 *******************************************************************************/
void UTimer_init(void)
{
    TIM_TimerInitTypeDef TIM_InitStruct;

    TIM_TimerStrutInit(&TIM_InitStruct);                  /* Timer结构体初始化*/
    TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CMP; /* 设置Timer CH0 为比较模式 */
    TIM_InitStruct.Timer_CH0Output = 0;                   /* 计数器回零时，比较模式输出极性控制 */
    TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CMP; /* 设置Timer CH1 为比较模式 */
    TIM_InitStruct.Timer_CH1Output = 0;                   /* 计数器回零时，比较模式输出极性控制 */
    TIM_InitStruct.Timer_TH = 48000;    									/* 定时器计数门限初始值48000*/
    TIM_InitStruct.Timer_CMP0 = 24000;  									/* 设置比较模式的CH0比较初始值24000 */
    TIM_InitStruct.Timer_CMP1 = 24000;  									/* 设置比较模式的CH1比较初始值24000 */
    TIM_InitStruct.Timer_FLT = 0;  										    /* 设置捕捉模式或编码器模式下对应通道的数字滤波值 */
    TIM_InitStruct.Timer_ClockDiv = TIMER_CLK_DIV1;       /* 设置Timer模块时钟2分频系数 */
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_ZC;		  /* 开启Timer模块比较中断和过零中断 Timer_IRQEna_CH0 | Timer_IRQEna_CH1 | */
    TIM_TimerInit(UTIMER0, &TIM_InitStruct);
    TIM_TimerCmd(UTIMER0, ENABLE);                        /* Timer0 模块使能 */

}

/*******************************************************************************
 函数名称：    void MCPWM_ch012_init(void)
 功能描述：    MCPWM初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/11/5      V1.0           Li Tonghua          创建
 *******************************************************************************/
#if	(EPWM0_USED == FUNCTION_ON)
void MCPWM_ch012_init(void)
{
    MCPWM_InitTypeDef MCPWM_InitStructure;

	u16 prd;
	u16 deadTime;
	u8  clockDiv;
	PSTR_DrvCfgPara	pParaPtr;

	pParaPtr	= getCfgParaPtr(0);
	prd			= getPWMPrd(pParaPtr);
	deadTime	= getDeadTime(pParaPtr);
	clockDiv	= pParaPtr->mS_GlobalCfg.m_nuPWMPrsc & 0x03;


    MCPWM_StructInit(&MCPWM_InitStructure);

    MCPWM_InitStructure.CLK_DIV = clockDiv;				/* MCPWM时钟分频设置 */
    MCPWM_InitStructure.MCLK_EN = ENABLE;				/* 模块时钟开启 */
	MCPWM_InitStructure.IO_FLT_CLKDIV  = 12;			/* 急停事件(来自IO口信号)数字滤波器时间设置 */
	MCPWM_InitStructure.CMP_FLT_CLKDIV = 12;			/* 急停事件(来自比较器信号)数字滤波器时间设置 */

	MCPWM_InitStructure.AUEN = MCPWM0_ALL_AUPDAT;		/*自动加载使能*/

	/* MCPWM0_CNT0	 第一组PWM设置*/

	MCPWM_InitStructure.BASE_CNT0_EN	= ENABLE;		/* 主计数器开始计数使能开关 */
	MCPWM_InitStructure.TH0				= prd;			/* 计数周期设置即MCPWM输出周期*/

	MCPWM_InitStructure.MCPWM_WorkModeCH0 = MCPWM0_CENTRAL_PWM_MODE; /* MCPWM CH0工作模式：中心对齐PWM模式 */
	MCPWM_InitStructure.MCPWM_WorkModeCH1 = MCPWM0_CENTRAL_PWM_MODE; /* 通道工作模式设置，中心对齐或边沿对齐 */
	MCPWM_InitStructure.MCPWM_WorkModeCH2 = MCPWM0_CENTRAL_PWM_MODE;
	MCPWM_InitStructure.DeadTimeCH012N = deadTime;		/* 死区时间设置 */
	MCPWM_InitStructure.DeadTimeCH012P = deadTime;	

	MCPWM_InitStructure.CMP_CTRL_CNT0  = DISABLE ;		/* CMP控制CNT0计数使能位 */
	MCPWM_InitStructure.EVT_CNT0_EN    = DISABLE ; 		/* MCPWM_CNT1外部触发使能位 */
	MCPWM_InitStructure.EVT0		   = DISABLE ;		/* 外部触发 */

	MCPWM_InitStructure.TR0_UP_INTV 	= DISABLE;
	MCPWM_InitStructure.TR0_T0_UpdateEN = ENABLE ;		/*T0时刻更新使能*/
	MCPWM_InitStructure.TR0_T1_UpdateEN = DISABLE ;
	MCPWM_InitStructure.TR0_AEC 		= DISABLE;		/*自动清除MCPWM0_EIF标志位*/

	MCPWM_InitStructure.TMR0 = (u16)(40 - prd);			/* MCPWM_TMR0  设置采样点 */
	MCPWM_InitStructure.TMR1 = (u16)(prd - 1);			/* MCPWM_TMR1 设置 */
 

#if (PRE_DRIVER_POLARITY == P_HIGH__N_LOW)                    /* CHxP 高有效， CHxN低电平有效 */
    MCPWM_InitStructure.CH0N_Polarity_INV = ENABLE;           /* CH0N通道输出极性设置 | 正常输出或取反输出*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE;          /* CH0P通道输出极性设置 | 正常输出或取反输出 */
    MCPWM_InitStructure.CH1N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P =  DISABLE;           /* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
    MCPWM_InitStructure.Switch_CH1N_CH1P =  DISABLE;           /* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH2N_CH2P =  DISABLE;           /* 通道交换选择设置 */

    /* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
    MCPWM_InitStructure.CH0P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = MCPWM0_HIGH_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = MCPWM0_LOW_LEVEL;      /* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH1N_default_output = MCPWM0_HIGH_LEVEL;     /* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH2P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = MCPWM0_HIGH_LEVEL;
	#else
#if (PRE_DRIVER_POLARITY == P_HIGH__N_HIGH)                    /* CHxP 高有效， CHxN高电平有效 */
    MCPWM_InitStructure.CH0N_Polarity_INV = DISABLE;           /* CH0N通道输出极性设置 | 正常输出或取反输出*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE;          /* CH0P通道输出极性设置 | 正常输出或取反输出 */
    MCPWM_InitStructure.CH1N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P = DISABLE;           /* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
    MCPWM_InitStructure.Switch_CH1N_CH1P = DISABLE;           /* 通道交换选择设置 */
    MCPWM_InitStructure.Switch_CH2N_CH2P = DISABLE;           /* 通道交换选择设置 */

    /* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
                                                     通道交换和极性控制的影响，直接控制通道输出 */
    MCPWM_InitStructure.CH0P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = MCPWM0_LOW_LEVEL;      /* CH1P对应引脚在空闲状态输出低电平 */
    MCPWM_InitStructure.CH1N_default_output = MCPWM0_LOW_LEVEL;     /* CH1N对应引脚在空闲状态输出高电平 */
    MCPWM_InitStructure.CH2P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = MCPWM0_LOW_LEVEL;
#endif
	#endif

	
#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
			MCPWM_InitStructure.T0_Update0_INT_EN = DISABLE;   /* T0更新事件 中断使能位 */
			MCPWM_InitStructure.T1_Update0_INT_EN = ENABLE ;   /* T1更新事件 中断使能位*/
			MCPWM_InitStructure.Update0_INT_EN = DISABLE;	   /* CNT0 更新事件 中断使能  */
#else
#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
			MCPWM_InitStructure.T0_Update0_INT_EN = DISABLE;   /* T0更新事件 中断使能位 */
			MCPWM_InitStructure.T1_Update0_INT_EN = DISABLE ;  /* T1更新事件 中断使能位*/
			MCPWM_InitStructure.Update0_INT_EN = DISABLE;	   /* CNT0更新事件中断使能	双电阻不使用PWM中断  */
#else
#if ((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
			MCPWM_InitStructure.T0_Update0_INT_EN = DISABLE;   /* T0更新事件 中断使能位 */
			MCPWM_InitStructure.T1_Update0_INT_EN = DISABLE ;  /* T1更新事件 中断使能位*/
			MCPWM_InitStructure.Update0_INT_EN = DISABLE;	   /* CNT0 更新事件 中断使能  双电阻不使用PWM中断  */
#endif
#endif
#endif

	MCPWM_InitStructure.CH0N_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH0P_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH1N_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH1P_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH2N_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH2P_FAIL_EN = ENABLE ;


	MCPWM_InitStructure.FAIL0_INPUT_EN	 = DISABLE ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL0_INT_EN	 = DISABLE;
	MCPWM_InitStructure.FAIL0_Signal_Sel = MCPWM0_FAIL_SEL_CMP ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL0_Polarity	 = MCPWM0_HIGH_LEVEL_ACTIVE ;

	MCPWM_InitStructure.FAIL1_INPUT_EN	 = ENABLE ;//FAIL_1CAP，打开CAP1
	MCPWM_InitStructure.FAIL1_INT_EN	 = DISABLE;//fail中断
	MCPWM_InitStructure.FAIL1_Signal_Sel = MCPWM0_FAIL_SEL_CMP ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL1_Polarity	 = MCPWM0_HIGH_LEVEL_ACTIVE ;

	
	MCPWM_InitStructure.HALT_PRT0		 = ENABLE ;   /* 在接上仿真器debug程序时，暂停MCU运行时，选择各PWM通道正常输出调制信号
																	 还是输出默认电平，保护功率器件 ENABLE:正常输出 DISABLE:输出默认电平*/
	MCPWM_InitStructure.FAIL_0CAP		 = ENABLE ;   //FAIL01事件发生时 将MCPWM0_CNT0值存入MCPWM0_FCNT 使能

	
    MCPWM_Init(&MCPWM_InitStructure);
	
	registerEPWM0_DrvLevel();
}
#endif

/*******************************************************************************
 函数名称：    void MCPWM_ch345_init(void)
 功能描述：    MCPWM初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/11/5      V1.0           Li Tonghua          创建
 *******************************************************************************/
#if	(EPWM1_USED == FUNCTION_ON)
void MCPWM_ch345_init(void)
{
    MCPWM_InitTypeDef MCPWM_InitStructure;

	u16 prd;
	u16 deadTime;
	u8  clockDiv;
	PSTR_DrvCfgPara	pParaPtr;


	pParaPtr	= getCfgParaPtr(0);
	prd			= getPWMPrd(pParaPtr);
	deadTime	= getDeadTime(pParaPtr);
	clockDiv	= pParaPtr->mS_GlobalCfg.m_nuPWMPrsc & 0x03;


	MCPWM_StructInit(&MCPWM_InitStructure);

    MCPWM_InitStructure.CLK_DIV = clockDiv;				/* MCPWM时钟分频设置 */
    MCPWM_InitStructure.MCLK_EN = ENABLE;				/* 模块时钟开启 */
	MCPWM_InitStructure.IO_FLT_CLKDIV  = 12;			/* 急停事件(来自IO口信号)数字滤波器时间设置 */
	MCPWM_InitStructure.CMP_FLT_CLKDIV = 12;			/* 急停事件(来自比较器信号)数字滤波器时间设置 */

	MCPWM_InitStructure.AUEN = MCPWM0_ALL_AUPDAT;		/*自动加载使能*/


/* MCPWM0_CNT1	 第二组PWM设置*/	

	/* MCPWM0_CNT1 */
	MCPWM_InitStructure.BASE_CNT1_EN = DISABLE;				  /* 主计数器开始计数使能开关 */
	MCPWM_InitStructure.TH1 = prd;			  /* 计数周期设置即MCPWM输出周期*/

	MCPWM_InitStructure.MCPWM_WorkModeCH3 = MCPWM0_CENTRAL_PWM_MODE; /* MCPWM CH0工作模式：中心对齐PWM模式 */
	MCPWM_InitStructure.MCPWM_WorkModeCH4 = MCPWM0_CENTRAL_PWM_MODE; /* 通道工作模式设置，中心对齐或边沿对齐 */
	MCPWM_InitStructure.MCPWM_WorkModeCH5 = MCPWM0_CENTRAL_PWM_MODE;

	MCPWM_InitStructure.DeadTimeCH345N = deadTime;
	MCPWM_InitStructure.DeadTimeCH345P = deadTime;

	MCPWM_InitStructure.CMP_CTRL_CNT1  = DISABLE ;		/* CMP控制CNT0计数使能位 */
	MCPWM_InitStructure.EVT_CNT1_EN    = DISABLE ; 		/* MCPWM_CNT1外部触发使能位 */
	MCPWM_InitStructure.EVT1		   = DISABLE ;		/* 外部触发 */	

	MCPWM_InitStructure.TR1_UP_INTV 	= DISABLE;
	MCPWM_InitStructure.TR1_T0_UpdateEN = ENABLE ;		/*T0时刻更新使能*/
	MCPWM_InitStructure.TR1_T1_UpdateEN = DISABLE ;
	MCPWM_InitStructure.TR1_AEC 		= DISABLE;		/*T0时刻更新使能*/

	MCPWM_InitStructure.TMR2 = (u16)(40 - prd);			/* MCPWM_TMR2  设置 */
	MCPWM_InitStructure.TMR3 = (u16)(prd - 1);			/* MCPWM_TMR3  设置 */

#if (PRE_DRIVER_POLARITY == P_HIGH__N_LOW)					/* CHxP 高有效， CHxN低电平有效 */
	MCPWM_InitStructure.CH3N_Polarity_INV = ENABLE; 		  /* CH0N通道输出极性设置 | 正常输出或取反输出*/
	MCPWM_InitStructure.CH3P_Polarity_INV = DISABLE;		  /* CH0P通道输出极性设置 | 正常输出或取反输出 */
	MCPWM_InitStructure.CH4N_Polarity_INV = ENABLE;
	MCPWM_InitStructure.CH4P_Polarity_INV = DISABLE;
	MCPWM_InitStructure.CH5N_Polarity_INV = ENABLE;
	MCPWM_InitStructure.CH5P_Polarity_INV = DISABLE;

	MCPWM_InitStructure.Switch_CH3N_CH3P =	DISABLE;		   /* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
	MCPWM_InitStructure.Switch_CH4N_CH4P =	DISABLE;		   /* 通道交换选择设置 */
	MCPWM_InitStructure.Switch_CH5N_CH5P =	DISABLE;		   /* 通道交换选择设置 */

	/* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
													 通道交换和极性控制的影响，直接控制通道输出 */
	MCPWM_InitStructure.CH3P_default_output = MCPWM0_LOW_LEVEL;
	MCPWM_InitStructure.CH3N_default_output = MCPWM0_HIGH_LEVEL;
	MCPWM_InitStructure.CH4P_default_output = MCPWM0_LOW_LEVEL; 	 /* CH1P对应引脚在空闲状态输出低电平 */
	MCPWM_InitStructure.CH4N_default_output = MCPWM0_HIGH_LEVEL;	 /* CH1N对应引脚在空闲状态输出高电平 */
	MCPWM_InitStructure.CH5P_default_output = MCPWM0_LOW_LEVEL;
	MCPWM_InitStructure.CH5N_default_output = MCPWM0_HIGH_LEVEL;
#else
#if (PRE_DRIVER_POLARITY == P_HIGH__N_HIGH)                    /* CHxP 高有效， CHxN高电平有效 */
	MCPWM_InitStructure.CH3N_Polarity_INV = DISABLE;		   /* CH0N通道输出极性设置 | 正常输出或取反输出*/
	MCPWM_InitStructure.CH3P_Polarity_INV = DISABLE;		  /* CH0P通道输出极性设置 | 正常输出或取反输出 */
	MCPWM_InitStructure.CH4N_Polarity_INV = DISABLE;
	MCPWM_InitStructure.CH4P_Polarity_INV = DISABLE;
	MCPWM_InitStructure.CH5N_Polarity_INV = DISABLE;
	MCPWM_InitStructure.CH5P_Polarity_INV = DISABLE;

	MCPWM_InitStructure.Switch_CH3N_CH3P =	DISABLE;		   /* 通道交换选择设置 | CH0P和CH0N是否选择信号交换 */
	MCPWM_InitStructure.Switch_CH4N_CH4P =	DISABLE;		   /* 通道交换选择设置 */
	MCPWM_InitStructure.Switch_CH5N_CH5P =	DISABLE;		   /* 通道交换选择设置 */

	/* 默认电平设置 默认电平输出不受MCPWM_IO01和MCPWM_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14
													 通道交换和极性控制的影响，直接控制通道输出 */
	MCPWM_InitStructure.CH3P_default_output = MCPWM0_LOW_LEVEL;
	MCPWM_InitStructure.CH3N_default_output = MCPWM0_LOW_LEVEL;
	MCPWM_InitStructure.CH4P_default_output = MCPWM0_LOW_LEVEL; 	 /* CH1P对应引脚在空闲状态输出低电平 */
	MCPWM_InitStructure.CH4N_default_output = MCPWM0_LOW_LEVEL; 	  /* CH1N对应引脚在空闲状态输出高电平 */
	MCPWM_InitStructure.CH5P_default_output = MCPWM0_LOW_LEVEL;
	MCPWM_InitStructure.CH5N_default_output = MCPWM0_LOW_LEVEL;
#endif
#endif

#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
	MCPWM_InitStructure.T2_Update1_INT_EN = DISABLE;   /* T0更新事件 中断使能位 */
	MCPWM_InitStructure.T1_Update1_INT_EN = ENABLE ;   /* T1更新事件 中断使能位*/
	MCPWM_InitStructure.Update1_INT_EN = DISABLE;	   /* CNT0 更新事件 中断使能  */
#elif (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
	MCPWM_InitStructure.T0_Update1_INT_EN = DISABLE;   /* T0更新事件 中断使能位 */
	MCPWM_InitStructure.T1_Update1_INT_EN = DISABLE ;  /* T1更新事件 中断使能位*/
	MCPWM_InitStructure.Update0_INT_EN = DISABLE;	   /* CNT0更新事件中断使能	双电阻不使用PWM中断  */
#elif ((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
	MCPWM_InitStructure.T0_Update1_INT_EN = DISABLE;   /* T0更新事件 中断使能位 */
	MCPWM_InitStructure.T1_Update1_INT_EN = DISABLE ;  /* T1更新事件 中断使能位*/
	MCPWM_InitStructure.Update1_INT_EN = DISABLE;	   /* CNT0 更新事件 中断使能  双电阻不使用PWM中断  */
#endif

	MCPWM_InitStructure.CH3N_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH3P_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH4N_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH4P_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH5N_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH5P_FAIL_EN = ENABLE ;

	MCPWM_InitStructure.FAIL2_INPUT_EN		= DISABLE ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL2_INT_EN		= DISABLE;
	MCPWM_InitStructure.FAIL2_Signal_Sel	= MCPWM0_FAIL_SEL_CMP ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL2_Polarity		= MCPWM0_HIGH_LEVEL_ACTIVE ;

	MCPWM_InitStructure.FAIL3_INPUT_EN		= DISABLE ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL3_INT_EN		= DISABLE;
	MCPWM_InitStructure.FAIL3_Signal_Sel	= MCPWM0_FAIL_SEL_CMP ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL3_Polarity		= MCPWM0_HIGH_LEVEL_ACTIVE ;

	MCPWM_InitStructure.HALT_PRT1			= DISABLE ;
	MCPWM_InitStructure.FAIL_1CAP			= DISABLE ;
	
	//TMR2 TMR3选择时间点可以时基0或者1，比较灵活，可以组合成原来的四段式采样
	MCPWM_InitStructure.TMR2_TB 	   = 0;/* MCPWM TMR2时基（计数器）选择 0：时基0；1：时基1 */
	MCPWM_InitStructure.TMR3_TB 	   = 0;/* MCPWM TMR3时基（计数器）选择 0：时基0；1：时基1 */
	
    MCPWM_Init(&MCPWM_InitStructure);
	
	registerEPWM1_DrvLevel();
}
#endif
/*******************************************************************************
 函数名称：    void DebugPWM_OutputFunction(void)
 功能描述：    PWM输出功能调试   输出25%占空比
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2017/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void DebugPWM_OutputFunction(void)
{
    MCPWM0_TH00 = (s16)(-(PWM_PERIOD_M0 >> 2));
    MCPWM0_TH01 = (PWM_PERIOD_M0 >> 2);
    MCPWM0_TH10 = (s16)(-(PWM_PERIOD_M0 >> 2));
    MCPWM0_TH11 = (PWM_PERIOD_M0 >> 2);
    MCPWM0_TH20 = (s16)(-(PWM_PERIOD_M0 >> 2));
    MCPWM0_TH21 = (PWM_PERIOD_M0 >> 2);

    PWMOutputs(ENABLE);
    while(1)
    {
    }
}


