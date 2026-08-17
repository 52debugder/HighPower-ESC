/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： interrupt.c
 * 文件标识：
 * 内容摘要： 中断服务程序文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet
 * 完成日期： 2020年8月5日
 *
 * 修改记录1：
 * 修改日期：2020年8月5日
 * 版 本 号：V 1.0
 * 修 改 人：Howlet
 * 修改内容：创建
 *
 *******************************************************************************/

#include "project_mcu.h"
#include "hardware_config.h"
#include "hardware_init.h"
#include "MC_Parameter_M0.h"
#include "PubData_DriverInstance.h"
#include "mc_declaration.h"
#include "MA_Static_Variable.h"


#include "segger_rtt.h"

#if (RTT_FUNCTION == FUNCTION_ON)
struct {
    s16 data0;
    s16 data1;
    s16 data2;
    s16 data3;
} Rttstru;
#endif

#define	_TIME_TEST_DEFINED
#ifdef _TIME_TEST_DEFINED
volatile s16 DebugT0;
volatile s16 DebugT1;
volatile s16 DebugT2;
volatile s16 DebugTmax;



volatile s16 Debug1MsTimes;
volatile s16 Debug1MsTimesRecord;
extern STR_ControlObject gS_PhyObjInstanceM[MAX_DRV_MODULE_USED];

#endif

extern void AdcEocIsrDRV0(void);
extern void AdcEocIsrDRV1(void);

extern STR_TaskScheduler		gS_TaskScheduler;

/*******************************************************************************
 函数名称：    void ADC1_IRQHandler(void)
 功能描述：    ADC1中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
#if ((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
void ADC0_IRQHandler(void)
{
    ADC0_IF |= BIT1 | BIT0;

	#ifdef _TIME_TEST_DEFINED
	Debug1MsTimes++;
	HALL0_CNT = 0;
	#endif
	
    AdcEocIsrDRV0();

	#ifdef _TIME_TEST_DEFINED
	DebugT1		= HALL0_CNT;

	DebugT2		= DebugT1;
    DebugTmax	= DebugTmax < DebugT2 ? DebugT2 : DebugTmax;
	#endif

	
	#if(RTT_FUNCTION == FUNCTION_ON)
	Rttstru.data0 = getElectSpdEst(0);
	Rttstru.data1 = getElectAngleEst(0);
	Rttstru.data2 = getPhaseCur_U(0);
	Rttstru.data3 = getPhaseCur_V(0);	
	SEGGER_RTT_Write(1, &Rttstru, 8);
	#endif

}

#endif

void ADC1_IRQHandler(void)
{
	ADC1_IF |= BIT1 | BIT0;

	#ifdef _TIME_TEST_DEFINED
	Debug1MsTimes++;
	#endif
}
/*******************************************************************************
 函数名称：    void MCPWM0_BASE0_IRQHandler(void)
 功能描述：    MCPWM0中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
#if ( (EPWM0_USED == FUNCTION_ON) && (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT))
void MCPWM0_IRQHandler(void)
{
	//PWM0_时基0中断标志
	MCPWM0_IF0 = BIT1 | BIT0;  //T1事件|T0事件   注意，触发了ADC0 通道采样
	//ADC0_STATE_RESET();

	ADC0_IF |= BIT1 | BIT0;
	#ifdef _TIME_TEST_DEFINED
	HALL0_CNT		= 0;
	Debug1MsTimes++;
	#endif

    AdcEocIsrDRV0();
	
	#ifdef _TIME_TEST_DEFINED
	DebugT1		= HALL0_CNT;

	DebugT2		= DebugT1 - DebugT0;
	DebugTmax	= DebugTmax < DebugT2 ? DebugT2 : DebugTmax;
	#endif


	#if(RTT_FUNCTION == FUNCTION_ON)
	Rttstru.data0 = getElectSpdEst(0);
	Rttstru.data1 = getElectAngleEst(0);
	Rttstru.data2 = getPhaseCur_U(0);
	Rttstru.data3 = getPhaseCur_V(0);	
	SEGGER_RTT_Write(1, &Rttstru, 8);
	#endif
}

#endif


/*******************************************************************************
 函数名称：    void GPIO_IRQHandler(void)
 功能描述：    GPIO中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void HALL_IRQHandler(void)
{
#if (ROTOR_SENSOR_TYPE == ROTOR_HALL_SENSOR)    
    HALL_IRQProcess(HALL, &struHallProcess);
#endif  

}


/*******************************************************************************
 函数名称：    void TIMER0_IRQHandler(void)
 功能描述：    TIMER0中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void TIMER0_IRQHandler(void)
{
    /* 时基500us */
    UTIMER0_IF |= TIMER_IF_ZERO;

	gS_TaskScheduler.bTimeCnt1ms++;
    gS_TaskScheduler.nTimeCnt10ms ++;
    gS_TaskScheduler.nTimeCnt500ms++;
}

/*******************************************************************************
 函数名称：    void TIMER1_IRQHandler(void)
 功能描述：    TIMER1中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UTIMER1_IRQHandler(void)
{

}



/*******************************************************************************
 函数名称：    void TIMER2_IRQHandler(void)
 功能描述：    TIMER2中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UTIMER2_IRQHandler(void)
{

}


/*******************************************************************************
 函数名称：    void HALL0_IRQHandler(void)
 功能描述：    HALL0中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void HALL0_IRQHandler(void)
{
//    HALL_IRQProcess(HALL0, &struHallProcess0);

}

/*******************************************************************************
 函数名称：    void HALL1_IRQHandler(void)
 功能描述：    HALL0中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void HALL1_IRQHandler(void)
{
    //  HALL_IRQProcess(HALL1, &struHallProcess1);

}


/*******************************************************************************
 函数名称：    void TIMER1_IRQHandler(void)
 功能描述：    TIMER1中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void TIMER1_IRQHandler(void)
{

}

/*******************************************************************************
 函数名称：    void TIMER2_IRQHandler(void)
 功能描述：    TIMER2中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void TIMER2_IRQHandler(void)
{

}

/*******************************************************************************
 函数名称：    void TIMER3_IRQHandler(void)
 功能描述：    TIMER3中断
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void TIMER3_IRQHandler(void)
{

}


/*******************************************************************************
 函数名称：    void CMP_IRQHandler(void)
 功能描述：    比较器中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void CMP_IRQHandler(void)
{

}

/*******************************************************************************
 函数名称：    void UART0_IRQHandler(void)
 功能描述：    UART0中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UART0_IRQHandler(void)
{



}

/*******************************************************************************
 函数名称：    void UART1_IRQHandler(void)
 功能描述：    UART1中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UART1_IRQHandler(void)
{
    if(UART1_IF & 0x10)
    {
        UART1_IF |= 0x10;
    }
    else if(UART1_IF & 0x20)
    {
        UART1_IF |= 0x20;
    }
}

/*******************************************************************************
 函数名称：    void UART2_IRQHandler(void)
 功能描述：    UART2中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UART2_IRQHandler(void)
{

}

/*******************************************************************************
 函数名称：    void SysTick_Handler(void)
 功能描述：    系统节拍定时器中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void SysTick_Handler(void)
{
    //GPIO0_PDO |= BIT2;                  //TP3
    //SysTick->VAL = 0; // VAL是个24 位的寄存器，读取时返回当前倒计数的值，写它则使之清零，同
    //时还会清除在 SysTick 控制及状态寄存器中的 COUNTFLAG 标志
    //GPIO0_PDO &= ~BIT2;
}


/*******************************************************************************
 函数名称：    void HardFault_Handler(void)
 功能描述：    硬件故障中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void HardFault_Handler(void)
{

}

void MemManageFault_Handler(void)
{

}

void BusFault_Handler(void)
{

}

void UsageFault_Handler(void)
{

}

void SPI0_IRQHandler(void)
{

}

void DSP0_IRQHandler(void)
{
}


void SIF0_IRQHandler  (void)
{
}
void WAKE_IRQHandler  (void)
{
}
void SW_IRQHandler    (void)
{
}
void PWRDN_IRQHandler (void)
{
}
void CL0_IRQHandler   (void)
{
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/


