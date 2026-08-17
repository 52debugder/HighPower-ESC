/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： Time_Process.c
 * 文件标识：
 * 内容摘要： 定时相关函数
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet Li
 * 完成日期： 2020年8月16日
 *
 * 修改记录1：
 * 修改日期：2020年8月16日
 * 版 本 号：V 1.0
 * 修 改 人：Howlet Li
 * 修改内容：创建
 *
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "basic.h"
#include "project_mcu.h"
#include "hardware_config.h"

#include "MC_Parameter_M0.h"

#include "math.h"
#include "hardware_init.h"
#include "PubData_DriverInstance.h"
#include "segger_rtt.h"

void ADC_1Shunt_NormalModeCFG(void);
void CurrentOffsetCalibration(void);
#if (DEBUG_PWM_OUTPUT == TEST_ON)
void DebugPWM_OutputFunction(void); /* 调试的时候输出50%的PWM波形 */
#endif

extern PSTR_ControlObject getCtrlObjectPtr(u8 objID);
extern void ADC0_init(void);
extern void ADC1_init(void);
extern u8 getLibMaxObjNumber(void);
extern void DebugPWM_OutputFunction(void);

/*******************************************************************************
 函数名称：    bool ConfigData_check(void)
 功能描述：    配置数据及支持库检查
 输入参数：    无
 输出参数：    无
 返 回 值：    TRUE ------- 匹配   FALSE ----- 不匹配
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/1/15      V1.0           Li Tonghua          创建
 *******************************************************************************/
bool ConfigData_check(void)
{
	if(checkParaCfgValid())				//	检查配置参数版本号等是否有效，主要用于LMSMotor下载参数校验
	{
		BondingMotorDrvObject();		//	校验通过，绑定控制对象
	}
	else
	{
		return FALSE;					//	参数无效，调用函数需要进行出错处理
	}

	//	校验库是否匹配?
	if(getLibMaxObjNumber() < PLANTFORM_DRV_MODULE_NUM)
	{
		return FALSE;					//	库对象数小于当前代码的对象个数，库不支持
	}	
	return TRUE;
}


/*******************************************************************************
 函数名称：    int sys_init(void)
 功能描述：    系统变量初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void sys_init(void)
{
	InitMotorDriveLayer();
	InitMotorAppLayer();
	InitUsrAppLayer();

	CurrentOffsetCalibration();                 /* 读取电流采样通道偏置 */
	
	//gS_TaskScheduler.sVersion = &sVersion[0];/* 初始化版本号 */
    
    #if(MCPWM_DEBUG == FUNCTION_ON)
    DebugPWM_OutputFunction();
    	// debug 固定PWM 输出波形，用于测试硬件
		// 也可以采用VF测试
		// 测试时确保硬件过流等起作用	
    #endif
    
	#if (RTT_FUNCTION == FUNCTION_ON)
    /* JScope RTT模式初始化 */
    SEGGER_RTT_ConfigUpBuffer(1, "JScope_i2i2i2i2", bRttBuf, 2048, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
	#endif
}

/*******************************************************************************
 函数名称：    static void CurrentOffsetReadPWM0(STR_PubDatHDMD* tS_pHdToMd, u16 t_nuCalPeriod)
 功能描述：    读PWM0模块对应的电流Offset值
 操作的表：    无
 输入参数：    操作结果指针
 输出参数：    操作结果指针回传
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：    涉及硬件操作，须根据硬件配置
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/11/01 	 V1.0			Tonghua Li		  据历史版本更新
 *******************************************************************************/
#if (DRV0_PWM_ID == PLANTFORM_EPWM0)
static void CurrentOffsetReadPWM0(STR_PubDatHDMD* tS_pHdToMd, u16 t_nuCalPeriod)
{
    volatile s32 t_offset1, t_offset2, t_offset3;
    volatile s32 t_offset4;

    volatile u32 t_dlay;

    __disable_irq();


    MCPWM0_PRT = 0x0000DEAD; /* enter password to unlock write protection */
    MCPWM0_TH00 = 0x00;
    MCPWM0_TH01 = 0x00;
    MCPWM0_TH10 = 0x00;
    MCPWM0_TH11 = 0x00;
    MCPWM0_TH20 = 0x00;
    MCPWM0_TH21 = 0x00;
    MCPWM0_UPDATE = 0xff;    /* write whatever value to trigger update */
    MCPWM0_PRT = 0x0000CAFE; //write any value other than 0xDEAD to enable write protection

    PWMOutputs(DISABLE);	//对于非MOS内阻采样，可使能也可不使能

    ADC0_TRIG = 0;

	ADC_SOFTWARE_TRIG_ONLY();//数据左对齐
    ADC0_CHN0 = 4; //采样4个通道

	ADC0_STATE_RESET();

    //延时后进行offset采样
    for(t_dlay = 0; t_dlay < 0x7ffff; t_dlay++);
	

    //单电阻Offset
	#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
	ADC_CHN_GAIN_CFG(ADC0, CHN0, ADC_1SHUNT_CURR_CH, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN1, ADC_1SHUNT_CURR_CH, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN2, ADC_BUS_VOL_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN3, M0_ADC_BUS_CURR_CH, ADC_GAIN3V6);
	#elif (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
	ADC0_CHN0 = ADC0_CURRETN_A_CHANNEL | (ADC0_CURRETN_B_CHANNEL << 4) | (ADC_BUS_VOL_CHANNEL<<8) | (M0_ADC_BUS_CURR_CH << 12);
	#elif  (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)
	ADC0_CHN0 = ADC0_CURRETN_A_CHANNEL | (ADC0_CURRETN_B_CHANNEL << 4) | (ADC0_CURRETN_C_CHANNEL<<8) | (M0_ADC_BUS_CURR_CH << 12);
	#endif

    t_offset1 = 0;
    t_offset2 = 0;
    t_offset3 = 0;
    t_offset4 = 0;

	for(t_dlay = 0; t_dlay < (t_nuCalPeriod); t_dlay++)
    {
        /* Clear the ADC0 JEOC pending flag */
        //ADC0_SWT = 0x00005AA5;
		ADC_SoftTrgEN(ADC0, ENABLE);   //软件触发 内部需要区分

        while(!(ADC0_IF & BIT0));

        ADC0_IF |= BIT1 | BIT0;
		ADC0_STATE_RESET();

        t_offset1 +=  (s16)((ADC0_DAT0));
        t_offset2 +=  (s16)((ADC0_DAT1));
        t_offset3 += (s16)((ADC0_DAT2));
        t_offset4 += (s16)(ADC0_DAT3);
    }

	ADC0_init();

	#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
	tS_pHdToMd->nBusShuntOffset = (s16)(t_offset1/t_nuCalPeriod);
	#elif (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
	tS_pHdToMd->nPhaseUOffset=(s16)(t_offset1/t_nuCalPeriod);
	tS_pHdToMd->nPhaseVOffset=(s16)(t_offset2/t_nuCalPeriod);
	#elif((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
	tS_pHdToMd->nPhaseUOffset=(s16)(t_offset1/t_nuCalPeriod);
	tS_pHdToMd->nPhaseVOffset=(s16)(t_offset2/t_nuCalPeriod);
	tS_pHdToMd->nPhaseWOffset=(s16)(t_offset3/t_nuCalPeriod);
	#endif
}

#elif (DRV0_PWM_ID == PLANTFORM_EPWM1)
/*******************************************************************************
 函数名称：    static void CurrentOffsetReadPWM1(void)
 功能描述：    读PWM1模块对应的电流Offset值
 操作的表：    无
 输入参数：    操作结果指针
 输出参数：    操作结果指针回传
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：	   涉及硬件操作，须根据硬件配置
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/11/01 	 V1.0			Tonghua Li		  据历史版本更新
 *******************************************************************************/
static void CurrentOffsetReadPWM1(STR_PubDatHDMD* tS_pHdToMd,u16 t_nuCalPeriod)
{

    volatile s32 t_offset1, t_offset2, t_offset3;
    volatile s32 t_offset4;

    volatile u32 t_dlay;

    __disable_irq();

	MCPWM0_PRT = 0x0000DEAD; /* enter password to unlock write protection */
	MCPWM0_TH30 = 0x00;
	MCPWM0_TH31 = 0x00;
	MCPWM0_TH40 = 0x00;
	MCPWM0_TH41 = 0x00;
	MCPWM0_TH50 = 0x00;
	MCPWM0_TH51 = 0x00;

	MCPWM0_UPDATE = 0xff;	 /* write whatever value to trigger update */
	MCPWM0_PRT = 0x0000CAFE; //write any value other than 0xDEAD to enable write protection

    PWMOutputs(DISABLE);	//对于非MOS内阻采样，可使能也可不使能

	
    ADC0_TRIG = 0;

	ADC_SOFTWARE_TRIG_ONLY();//数据左对齐
    ADC0_CHN0 = 4; //采样4个通道

	ADC0_STATE_RESET();

    //延时后进行offset采样
    for(t_dlay = 0; t_dlay < 0x7ffff; t_dlay++);
	

    //单电阻Offset
#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
	ADC_CHN_GAIN_CFG(ADC0, CHN0, ADC_1SHUNT_CURR_CH, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN1, ADC_1SHUNT_CURR_CH, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN2, ADC_BUS_VOL_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN3, M0_ADC_BUS_CURR_CH, ADC_GAIN3V6);
#elif (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
	ADC0_CHN0 = ADC0_CURRETN_A_CHANNEL | (ADC0_CURRETN_B_CHANNEL << 4) | (ADC_BUS_VOL_CHANNEL<<8) | (M0_ADC_BUS_CURR_CH << 12);
#elif  (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)
	ADC0_CHN0 = ADC0_CURRETN_A_CHANNEL | (ADC0_CURRETN_B_CHANNEL << 4) | (ADC0_CURRETN_C_CHANNEL<<8) | (M0_ADC_BUS_CURR_CH << 12);
#endif

    t_offset1 = 0;
    t_offset2 = 0;
    t_offset3 = 0;
    t_offset4 = 0;

	for(t_dlay = 0; t_dlay < (t_nuCalPeriod); t_dlay++)
    {
        /* Clear the ADC0 JEOC pending flag */
        //ADC0_SWT = 0x00005AA5;
		ADC_SoftTrgEN(ADC0, ENABLE);   //软件触发 内部需要区分

        while(!(ADC0_IF & BIT0));

        ADC0_IF |= BIT1 | BIT0;
		ADC0_STATE_RESET();

        t_offset1 += (s16)((ADC0_DAT0));
        t_offset2 += (s16)((ADC0_DAT1));
        t_offset3 += (s16)((ADC0_DAT2));
        t_offset4 += (s16)(ADC0_DAT3);
    }

	ADC0_init();

#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
	tS_pHdToMd->nBusShuntOffset = (s16)(t_offset1/t_nuCalPeriod);//

#elif (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
	tS_pHdToMd->nPhaseUOffset=(s16)(t_offset1/t_nuCalPeriod);
	tS_pHdToMd->nPhaseVOffset=(s16)(t_offset2/t_nuCalPeriod);
#elif((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
	tS_pHdToMd->nPhaseUOffset=(s16)(t_offset1/t_nuCalPeriod);
	tS_pHdToMd->nPhaseVOffset=(s16)(t_offset2/t_nuCalPeriod);
	tS_pHdToMd->nPhaseWOffset=(s16)(t_offset3/t_nuCalPeriod);
#endif		
}

#endif

/*******************************************************************************
 函数名称：    static void CurrentOffsetCalibrationPWM_ID(u8 t_bPwmId,STR_PubDatHDMD* tS_pHdToMd)
 功能描述：    根据PWM的ID号读电流Offset值
 输入参数：    t_bPwmId  PWM的ID号
 			   STR_PubDatHDMD* tS_pHdToMd  回传指针
 输出参数：    操作结果指针回传
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/11/1      V1.0           Tonghua Li          据历史版本更新
 *******************************************************************************/
#if (DRV0_PWM_ID == PLANTFORM_EPWM0)
static void CurrentOffsetCalibrationPWM_ID(u8 t_bPwmId,STR_PubDatHDMD* tS_pHdToMd,u16 t_nuCalPeriod)
{
	CurrentOffsetReadPWM0(tS_pHdToMd,t_nuCalPeriod);	
}
#elif (DRV0_PWM_ID == PLANTFORM_EPWM1)
static void CurrentOffsetCalibrationPWM_ID(u8 t_bPwmId,STR_PubDatHDMD* tS_pHdToMd,u16 t_nuCalPeriod)
{
	CurrentOffsetReadPWM1(tS_pHdToMd,t_nuCalPeriod);	
}
#endif



static void CurrentOffsetCalibrationPWM(void)
{
	PSTR_ControlObject	t_pObj;
	u16 t_nuCalPeriod;
	t_pObj		= getCtrlObjectPtr(0);
	t_nuCalPeriod	= t_pObj->m_pDrvCfgPara->mS_GlobalCfg.m_nuADCCaliTimes;
	CurrentOffsetCalibrationPWM_ID(t_pObj->m_bPWM_Id,&t_pObj->mGlobalDatPackage.mHdToMd,t_nuCalPeriod);
}

/*******************************************************************************
 函数名称：    void CurrentOffsetCalibration(void)
 功能描述：    进行电流AD采样校正
 输入参数：    无
 输出参数：    操作结果指针回传到对应的数据结构中
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/11/1      V1.0           Tonghua Li          据历史版本更新
 *******************************************************************************/
void CurrentOffsetCalibration(void)
{
    volatile u32 t_dlay;

    //延时时间
    for(t_dlay = 0; t_dlay < 0x6ffff; t_dlay++);

	CurrentOffsetCalibrationPWM();
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
