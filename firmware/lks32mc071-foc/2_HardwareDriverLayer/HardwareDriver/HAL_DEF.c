/*******************************************************************************
 * 版权所有 (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： HAL_DEF.c
 * 文件标识：
 * 内容摘要： 电机控制MCU硬件接口层，定义硬件操作的共用函数
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： LKS/MC TEAM
 * 完成日期： 2022年12月13日
 *******************************************************************************/
#include "project_config.h"
#include "PubData_DriverInstance.h"
#include "hardware_config.h"
#include "HALDrv.h"

extern void MCPWM_ch012_init(void);
extern void MCPWM_ch345_init(void);
extern void ADC0_init(void);
extern void ADC1_init(void);
const STR_HALDrvHandle	 gS_MotorHalDrvHandleM[MAX_DRV_MODULE_USED] = {Motor_HALDrv_EPWM0};																   


u16		g_hDriverPolarity[MAX_DRV_MODULE_USED];		
// MAX_DRV_MODULE_USED > 1时  0 --- EPWM0， 1 --- EPWM0
// MAX_DRV_MODULE_USED = 1时  0 --- 为所用的EPWM

/*******************************************************************************
 函数名称：    void ADC_1Shunt_NormalModeCFG(void)
 功能描述：    ADC正常工作模式通道配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void ADC_1Shunt_NormalModeCFG(void)
{
    ADC_CHN_GAIN_CFG(ADC0, CHN0, ADC_1SHUNT_CURR_CH, ADC_GAIN3V6);      /*ADC第0次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN1, ADC_1SHUNT_CURR_CH, ADC_GAIN3V6);      /*ADC第1次采样通道配置*/

    ADC_CHN_GAIN_CFG(ADC0, CHN2, ADC_1SHUNT_CURR_CH, ADC_GAIN3V6);      /*ADC第2次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN3, ADC_1SHUNT_CURR_CH, ADC_GAIN3V6);      /*ADC第3次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN4, ADC_BUS_VOL_CHANNEL, ADC_GAIN3V6);     /*ADC第4次采样通道配置*/
	ADC_CHN_GAIN_CFG(ADC0, CHN5, ADC_BUS_VOL_CHANNEL, ADC_GAIN3V6);		/*ADC第5次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN6, ADC0_TEMP_CHANNEL, ADC_GAIN3V6);		/*ADC第6次采样通道配置*/
    //ADC1
    ADC_CHN_GAIN_CFG(ADC1, CHN0, BEMF_CH_A, ADC_GAIN3V6);              /*ADC第0次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN1, BEMF_CH_A, ADC_GAIN3V6);              /*ADC第1次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN2, BEMF_CH_B, ADC_GAIN3V6);              /*ADC第2次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN3, BEMF_CH_C, ADC_GAIN3V6);              /*ADC第3次采样通道配置*/
	
}

/*******************************************************************************
 函数名称：    void ADC_2Shunt_NormalModeCFG(void)
 功能描述：    双电阻ADC正常工作模式通道配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void ADC_2Shunt_NormalModeCFG(void)
{
	//ADC0
    ADC_CHN_GAIN_CFG(ADC0, CHN0, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN1, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN2, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN3, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN4, ADC_BUS_VOL_CHANNEL, ADC_GAIN3V6);     /*ADC第4次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN5, ADC_BUS_VOL_CHANNEL, ADC_GAIN3V6);		/*ADC第5次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN6, ADC0_TEMP_CHANNEL, ADC_GAIN3V6);		/*ADC第6次采样通道配置*/
	
	//ADC1
    ADC_CHN_GAIN_CFG(ADC1, CHN0, BEMF_CH_A, ADC_GAIN3V6);              /*ADC第0次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN1, BEMF_CH_A, ADC_GAIN3V6);              /*ADC第1次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN2, BEMF_CH_B, ADC_GAIN3V6);              /*ADC第2次采样通道配置*/
	ADC_CHN_GAIN_CFG(ADC1, CHN3, BEMF_CH_C, ADC_GAIN3V6);              /*ADC第3次采样通道配置*/

	MCPWM0_TMR0 = (s16)(100-PWM_PERIOD_M0); 			// 100-PWM_PERIOD
}

/*******************************************************************************
 函数名称：    void ADC_3Shunt_NormalModeCFG(void)
 功能描述：    三电阻ADC正常工作模式通道配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void ADC_3Shunt_NormalModeCFG(void)
{
    ADC_CHN_GAIN_CFG(ADC0, CHN0, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);  /*ADC第0次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN1, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);	/*ADC第1次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN2, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);	/*ADC第2次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN3, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);	/*ADC第3次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN4, ADC_BUS_VOL_CHANNEL, ADC_GAIN3V6);     /*ADC第4次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN5, M0_ADC_BUS_CURR_CH, ADC_GAIN3V6);		/*ADC第5次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC0, CHN6, ADC0_TEMP_CHANNEL, ADC_GAIN3V6);		/*ADC第6次采样通道配置*/

	//ADC1
    ADC_CHN_GAIN_CFG(ADC1, CHN0, BEMF_CH_A, ADC_GAIN3V6);              /*ADC第0次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN1, BEMF_CH_A, ADC_GAIN3V6);              /*ADC第1次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN2, BEMF_CH_B, ADC_GAIN3V6);              /*ADC第2次采样通道配置*/
    ADC_CHN_GAIN_CFG(ADC1, CHN3, BEMF_CH_C, ADC_GAIN3V6);              /*ADC第3次采样通道配置*/
}

/*******************************************************************************
 函数名称：    void AcquireCurSamplingResultsM0(STR_PubDatHDMD* tS_pCurAdcRes)
 			   void AcquireVdcSamplingResultsM0(STR_PubDatHDMD* tS_pCurAdcRes)
 			   void AcquireNTCSamplingResultsM0(STR_PubDatHDMD* tS_pAdcRes)
 			   void AcquireBmefSamplingResultsM0(STR_PubDatHDMD* tS_pAdcRes) 			   
 功能描述：    get adc sample result
 输入参数：    
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void AcquireCurSamplingResultsM0(STR_PubDatHDMD* tS_pCurAdcRes)
{
	tS_pCurAdcRes->nSampCurDat0 = GET_ADC0_DATA_M0;
	tS_pCurAdcRes->nSampCurDat1 = GET_ADC1_DATA_M0;
}


void AcquireVdcSamplingResultsM0(STR_PubDatHDMD* tS_pCurAdcRes)
{
	tS_pCurAdcRes->nDcVolAdcDat = GET_M0_BUS_VOL_ADC_RESULT;
}


void AcquireNTCSamplingResultsM0(STR_PubDatHDMD* tS_pAdcRes)
{
	tS_pAdcRes->nNTCVolAdcDat	= GET_M0_TEMP_DATA_A;	
}


void AcquireBmefSamplingResultsM0(STR_PubDatHDMD* tS_pAdcRes)
{
	#if (DRV0_BEMF_CHECK_EABLE==FUNCTION_ON)
	tS_pAdcRes->nBmefUVolAdcDat = GET_M0_BEMF_DATA_A - tS_pAdcRes->nBmefUOffset;
	tS_pAdcRes->nBmefVVolAdcDat = GET_M0_BEMF_DATA_B - tS_pAdcRes->nBmefVOffset;
	tS_pAdcRes->nBmefWVolAdcDat = GET_M0_BEMF_DATA_C - tS_pAdcRes->nBmefWOffset;
	#endif
}

/*******************************************************************************
 函数名称：    void ChangeADChanelCFGM0(STR_PubDatMDHD* tS_pMdToHd)		   
 功能描述：    adc 通道动态调整
 输入参数：    
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
#if (DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_1SHUNT)
void ChangeADChanelCFGM0(STR_PubDatMDHD* tS_pMdToHd)
{

}
#elif (DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_2SHUNT)
void ChangeADChanelCFGM0(STR_PubDatMDHD* tS_pMdToHd)
{

}

#else

void ChangeADChanelCFGM0(STR_PubDatMDHD* tS_pMdToHd)
{
	if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_A_B)
	{
		ADC_CHN_GAIN_CFG(ADC0, CHN0, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);  /*ADC第0次采样通道配置*/
    	ADC_CHN_GAIN_CFG(ADC0, CHN1, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);	/*ADC第1次采样通道配置*/
    	ADC_CHN_GAIN_CFG(ADC0, CHN2, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);	/*ADC第2次采样通道配置*/
    	ADC_CHN_GAIN_CFG(ADC0, CHN3, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);	/*ADC第3次采样通道配置*/
	}
	else if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_B_C)
	{
		ADC_CHN_GAIN_CFG(ADC0, CHN0, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);  /*ADC第0次采样通道配置*/
    	ADC_CHN_GAIN_CFG(ADC0, CHN1, ADC0_CURRETN_C_CHANNEL, ADC_GAIN3V6);	/*ADC第1次采样通道配置*/
    	ADC_CHN_GAIN_CFG(ADC0, CHN2, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);	/*ADC第2次采样通道配置*/
    	ADC_CHN_GAIN_CFG(ADC0, CHN3, ADC0_CURRETN_C_CHANNEL, ADC_GAIN3V6);	/*ADC第3次采样通道配置*/
	}
	else if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_A_C)
	{
		ADC_CHN_GAIN_CFG(ADC0, CHN0, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);  /*ADC第0次采样通道配置*/
    	ADC_CHN_GAIN_CFG(ADC0, CHN1, ADC0_CURRETN_C_CHANNEL, ADC_GAIN3V6);	/*ADC第1次采样通道配置*/
    	ADC_CHN_GAIN_CFG(ADC0, CHN2, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);	/*ADC第2次采样通道配置*/
    	ADC_CHN_GAIN_CFG(ADC0, CHN3, ADC0_CURRETN_C_CHANNEL, ADC_GAIN3V6);	/*ADC第3次采样通道配置*/		
	}
}
#endif

/*******************************************************************************
 函数名称：    void AcquireCurSamplingResultsM1(STR_PubDatHDMD* tS_pCurAdcRes)
 			   void AcquireVdcSamplingResultsM1(STR_PubDatHDMD* tS_pCurAdcRes)
 			   void AcquireNTCSamplingResultsM1(STR_PubDatHDMD* tS_pAdcRes)
 			   void AcquireBmefSamplingResultsM1(STR_PubDatHDMD* tS_pAdcRes) 			   
 功能描述：    get adc sample result
 输入参数：    
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void AcquireCurSamplingResultsM1(STR_PubDatHDMD* tS_pCurAdcRes)
{
	tS_pCurAdcRes->nSampCurDat0 = GET_ADC0_DATA_M0;
	tS_pCurAdcRes->nSampCurDat1 = GET_ADC1_DATA_M0;
}

void AcquireVdcSamplingResultsM1(STR_PubDatHDMD* tS_pCurAdcRes)
{
	tS_pCurAdcRes->nDcVolAdcDat = GET_M0_BUS_VOL_ADC_RESULT;
}

void AcquireNTCSamplingResultsM1(STR_PubDatHDMD* tS_pAdcRes)
{
	tS_pAdcRes->nNTCVolAdcDat	= GET_M0_TEMP_DATA_A;
}

void AcquireBmefSamplingResultsM1(STR_PubDatHDMD* tS_pAdcRes)
{
	#if (DRV0_BEMF_CHECK_EABLE==FUNCTION_ON)
	tS_pAdcRes->nBmefUVolAdcDat = GET_M0_BEMF_DATA_A - tS_pAdcRes->nBmefUOffset;
	tS_pAdcRes->nBmefVVolAdcDat = GET_M0_BEMF_DATA_B - tS_pAdcRes->nBmefVOffset;
	tS_pAdcRes->nBmefWVolAdcDat = GET_M0_BEMF_DATA_C - tS_pAdcRes->nBmefWOffset;
	#endif

}
/*******************************************************************************
 函数名称：    void ChangeADChanelCFGM1(STR_PubDatMDHD* tS_pMdToHd)		   
 功能描述：    adc 通道动态调整
 输入参数：    
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
#if (DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_1SHUNT)
void ChangeADChanelCFGM1(STR_PubDatMDHD* tS_pMdToHd)
{

}
#elif (DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_2SHUNT)
void ChangeADChanelCFGM1(STR_PubDatMDHD* tS_pMdToHd)
{

}
#else
void ChangeADChanelCFGM1(STR_PubDatMDHD* tS_pMdToHd)
{
	if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_A_B)
	{
		ADC_CHN_GAIN_CFG(ADC0, CHN0, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);	/*ADC第0次采样通道配置*/
		ADC_CHN_GAIN_CFG(ADC0, CHN1, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);	/*ADC第1次采样通道配置*/
		ADC_CHN_GAIN_CFG(ADC0, CHN2, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);	/*ADC第2次采样通道配置*/
		ADC_CHN_GAIN_CFG(ADC0, CHN3, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);	/*ADC第3次采样通道配置*/
	}
	else if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_B_C)
	{
		ADC_CHN_GAIN_CFG(ADC0, CHN0, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);	/*ADC第0次采样通道配置*/
		ADC_CHN_GAIN_CFG(ADC0, CHN1, ADC0_CURRETN_C_CHANNEL, ADC_GAIN3V6);	/*ADC第1次采样通道配置*/
		ADC_CHN_GAIN_CFG(ADC0, CHN2, ADC0_CURRETN_B_CHANNEL, ADC_GAIN3V6);	/*ADC第2次采样通道配置*/
		ADC_CHN_GAIN_CFG(ADC0, CHN3, ADC0_CURRETN_C_CHANNEL, ADC_GAIN3V6);	/*ADC第3次采样通道配置*/
	}
	else if(tS_pMdToHd->mMcTmr.eChannel == E_PHASE_A_C)
	{
		ADC_CHN_GAIN_CFG(ADC0, CHN0, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);	/*ADC第0次采样通道配置*/
		ADC_CHN_GAIN_CFG(ADC0, CHN1, ADC0_CURRETN_C_CHANNEL, ADC_GAIN3V6);	/*ADC第1次采样通道配置*/
		ADC_CHN_GAIN_CFG(ADC0, CHN2, ADC0_CURRETN_A_CHANNEL, ADC_GAIN3V6);	/*ADC第2次采样通道配置*/
		ADC_CHN_GAIN_CFG(ADC0, CHN3, ADC0_CURRETN_C_CHANNEL, ADC_GAIN3V6);	/*ADC第3次采样通道配置*/		
	}
}
#endif

#if	(EPWM0_USED == FUNCTION_ON)
/*******************************************************************************
 函数名称：    void GetEPWM0_breakInStatus(STR_PubDatHDMD* tS_pHd2Md)
 功能描述：    读取breakin信号
 输入参数：    tS_pHd2Md
 输出参数：    无
 返 回 值：    无
 其它说明：	   查看是否存在过流事件
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void GetEPWM0_breakInStatus(STR_PubDatHDMD* tS_pHd2Md)
{
    tS_pHd2Md->bBreakInStatus = (MCPWM0_EIF & BIT5);
}

/*******************************************************************************
 函数名称：    void ClrEPWM0_breakInStatus(void)
 功能描述：    清除breakin信号
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void ClrEPWM0_breakInStatus(void)
{
    MCPWM0_EIF = (MCPWM0_EIF | BIT5);
}

/*******************************************************************************
 函数名称：    void registerEPWM0_DrvLevel(void)
 功能描述：    记录驱动极性
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void registerEPWM0_DrvLevel(void)
{
	g_hDriverPolarity[0] = MCPWM0_IO01;		/* 读出驱动极性 */
}

/*******************************************************************************
 函数名称：    void EPWM0_OutPut(FuncState t_state) 
 功能描述：    MOE操作函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   TRUE---- 使能
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void EPWM0_OutPut(FuncState t_state)
{
	MCPWM0_PRT = 0xDEAD;
    if(t_state == DISABLE)
    {
        MCPWM0_FAIL012 &= ~BIT6;
    }
    else
    {
        MCPWM0_FAIL012 |= BIT6;
    }
    MCPWM0_PRT = 0;
}

/*******************************************************************************
 函数名称：    void EPWM0_Charge(u8 t_bPhaseABC) 
 功能描述：    预充电极性控制
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   TRUE---- 使能
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void EPWM0_Charge(u8 t_bPhaseABC)
{
	MCPWM0_PRT		= 0x0000DEAD;
	
	if(t_bPhaseABC == 1)			//A相下桥PWM
	{
		MCPWM0_IO01		= 0x0C08 | g_hDriverPolarity[0];
		MCPWM0_IO23		= 0x000C | g_hDriverPolarity[0];
	}
	else if(t_bPhaseABC == 2)		//B相下桥PWM
	{
		MCPWM0_IO01		= 0x080C | g_hDriverPolarity[0];
	}
	else if(t_bPhaseABC == 3)		//C相下桥PWM
	{
		MCPWM0_IO23		= 0x08 | g_hDriverPolarity[0];;
	}

	MCPWM0_PRT		= 0x0000;
}

/*******************************************************************************
 函数名称：    void InitEPWM0ChargeEnd(void) 
 功能描述：    预充电完成后初始化硬件(PWM和ADC)
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   TRUE---- 使能
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void InitEPWM0ChargeEnd(void)
{
	__disable_irq();
	ADC0_init();
	ADC1_init();
	MCPWM_ch012_init();					/* PWM初始化 */
	ADC_STATE_RESET();
	__enable_irq();
}

/*******************************************************************************
 函数名称：    void MCPWM0_RegUpdate(void)
 功能描述：    加载MCPWM模块占空比值，加载MCPWM模块ADC触发点寄存器值
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void MCPWM0_RegUpdate(STR_PubDatMDHD* tS_pMdToHd)
{
	MCPWM0_TH00 = tS_pMdToHd->mMcPwm.nuTimePhBN;
    MCPWM0_TH01 = tS_pMdToHd->mMcPwm.nuTimePhB;
    
    MCPWM0_TH10 = tS_pMdToHd->mMcPwm.nuTimePhAN;
    MCPWM0_TH11 = tS_pMdToHd->mMcPwm.nuTimePhA;

    MCPWM0_TH20 = tS_pMdToHd->mMcPwm.nuTimePhCN;
    MCPWM0_TH21 = tS_pMdToHd->mMcPwm.nuTimePhC;

    MCPWM0_TMR0 = tS_pMdToHd->mMcTmr.nuPoint0;	// 第一个采样点
    MCPWM0_TMR1 = tS_pMdToHd->mMcTmr.nuPoint1;	// 第二个采样点	
}

#endif


#if	(EPWM1_USED == FUNCTION_ON)
/*******************************************************************************
 函数名称：    void GetEPWM0_breakInStatus(STR_PubDatHDMD* tS_pHd2Md)
 功能描述：    读取breakin信号
 输入参数：    tS_pHd2Md
 输出参数：    无
 返 回 值：    无
 其它说明：	   查看是否存在过流事件
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void GetEPWM1_breakInStatus(STR_PubDatHDMD* tS_pHd2Md)
{
    tS_pHd2Md->bBreakInStatus = (MCPWM0_EIF & BIT7);
}

/*******************************************************************************
 函数名称：    void ClrEPWM1_breakInStatus(void)
 功能描述：    清除breakin信号
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void ClrEPWM1_breakInStatus(void)
{
    MCPWM0_EIF = (MCPWM0_EIF | BIT7);
}

/*******************************************************************************
 函数名称：    void registerEPWM1_DrvLevel(void)
 功能描述：    记录驱动极性
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void registerEPWM1_DrvLevel(void)
{
	g_hDriverPolarity[0] = MCPWM0_IO45;		/* 读出驱动极性 */
}

/*******************************************************************************
 函数名称：    void EPWM1_OutPut(FuncState t_state) 
 功能描述：    MOE操作函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   TRUE---- 使能
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void EPWM1_OutPut(FuncState t_state)
{
	MCPWM0_PRT = 0xDEAD;
    if(t_state == DISABLE)
    {
        MCPWM0_FAIL345 &= ~BIT6;
    }
    else
    {
        MCPWM0_FAIL345 |= BIT6;
    }
    MCPWM0_PRT = 0; 
}

/*******************************************************************************
 函数名称：    void EPWM1_Charge(u8 t_bPhaseABC) 
 功能描述：    预充电极性控制
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   TRUE---- 使能
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void EPWM1_Charge(u8 t_bPhaseABC)
{
	MCPWM0_PRT		= 0x0000DEAD;
	
	if(t_bPhaseABC == 1)			//A相下桥PWM
	{
		MCPWM0_IO23		= 0x080C | g_hDriverPolarity[1];
		MCPWM0_IO45		= 0x0C0C | g_hDriverPolarity[1];
	}
	else if(t_bPhaseABC == 2)		//B相下桥PWM
	{
		MCPWM0_IO23		= 0x0C0C | g_hDriverPolarity[1];
		MCPWM0_IO45		= 0x0C08 | g_hDriverPolarity[1];
	}
	else if(t_bPhaseABC == 3)		//C相下桥PWM
	{
		MCPWM0_IO23		= 0x0C0C | g_hDriverPolarity[1];
		MCPWM0_IO45		= 0x080C | g_hDriverPolarity[1];
	}

	MCPWM0_PRT		= 0x0000;
}

/*******************************************************************************
 函数名称：    void InitEPWM1ChargeEnd(void) 
 功能描述：    预充电完成后初始化硬件(PWM和ADC)
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：	   TRUE---- 使能
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2024/5/27     V1.1           TongHua Li         整理
 *******************************************************************************/
void InitEPWM1ChargeEnd(void)
{
	__disable_irq();
	ADC0_init();
	ADC1_init();
    MCPWM_ch345_init();						/* PWM初始化 */
	ADC_STATE_RESET();
	__enable_irq();
}

/*******************************************************************************
 函数名称：    void MCPWM1_RegUpdate(void)
 功能描述：    加载MCPWM模块占空比值，加载MCPWM模块ADC触发点寄存器值
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void MCPWM1_RegUpdate(STR_PubDatMDHD* tS_pMdToHd)
{
	MCPWM0_TH30 = tS_pMdToHd->mMcPwm.nuTimePhBN;
    MCPWM0_TH31 = tS_pMdToHd->mMcPwm.nuTimePhB;
    
    MCPWM0_TH40 = tS_pMdToHd->mMcPwm.nuTimePhAN;
    MCPWM0_TH41 = tS_pMdToHd->mMcPwm.nuTimePhA;

    MCPWM0_TH50 = tS_pMdToHd->mMcPwm.nuTimePhCN;
    MCPWM0_TH51 = tS_pMdToHd->mMcPwm.nuTimePhC;

    MCPWM0_TMR2 = tS_pMdToHd->mMcTmr.nuPoint0;		// 第一个采样点
    MCPWM0_TMR3 = tS_pMdToHd->mMcTmr.nuPoint1;		// 第二个采样点
}
#endif

