/*******************************************************************************
 * 版权所有 (C)2016, LINKO Semiconduct
 *
 * 文件名称： FOC.Drive.c
 * 文件标识：
 * 内容摘要： 电机矢量控制电流内环及关键控制算法
 * 其它说明： 无
 * 当前版本： V 2.0
 * 作    者： WhenCai Zhao Howlet Li
 * 完成日期： 2020年9月10日
 *
 * 修改记录2：
 *    修改日期：2020年9月10日
 *    版 本 号：V2.0
 *    修 改 人：Howlet Li
 *    修改内容：格式整理
 *
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "project_config.h"
#include "hardware_config.h"
#include "mc_math.h"
#include "MC_Parameter_M0.h"
#include "mc_declaration.h"
#include "MC_type.h"
#include "HALDrv.h"


extern STR_MotorFoc gS_FocObjM[MAX_DRV_MODULE_USED];
extern u8			g_buMdPWMONDelay[MAX_DRV_MODULE_USED];
/*******************************************************************************/
//外部函数引用区

extern	void	InitFocVar(PSTR_MotorFoc tS_pFocObj);

static inline void	AdcCurSampleCalc(PSTR_MotorFoc tS_pFocObj);

extern	void	FaultCurrentCheck(STR_VectorUVW *pstruCurrent, u8 t_bPWM_ID);
extern	void	SetCmprDuty(PSTR_McpwmCmpr tS_Cmpr,u16 nuTime);

extern	s16		getMotorDaxisVoltFormObjId(u8 t_bObjId);
extern	s16		getMotorQaxisVoltFormObjId(u8 t_bObjId);

extern	s16		getMotorVoltFromObjId(u8 t_bObjId);
extern	s16		getMotorPowerFromObjId(u8 t_bObjId);

extern	s32		getOnFlyFreqResultFromObjId(u8 t_bObjId);
extern	s16		getMotorCurFromObjId(u8 t_bObjId);
extern	void	setTrakingMode(u8 t_bObjId, bool bEnable);

extern	s32		getOnFlyBemfFreqResultFromObjId(u8 t_bObjId);


extern	void	updateObserPLLVar1msLoop(PSTR_MotorFoc tS_pMotorFoc);
extern	void	vectorVFcontrol(u8 t_bObjId,s16 *pUd, s16 *pUq);
extern	s16		getDAxisVolt(u8 t_bObjId);
extern	s16		getQAxisVolt(u8 t_bObjId);
extern	void	SVPWM_3ShuntGetPhaseIaIb(PSTR_CurSamplingRes this);

extern	s16		getBemfAngComp(u8 t_objId);
extern	s16		getBemfTrackMinVolt(u8 t_objId);

extern	void	setTrakingModeEnable(u8 t_bObjId);
extern	void	setTrakingModeDisable(u8 t_bObjId);

extern	s16		getMotorActVoltFromObjId(u8 t_bObjId);
extern	s16		CurrentPIRegulator(STR_PIRegulator* tS_pAcr);

extern	s16 getMotorCurFromObjId1ms(u8 t_bObjId);
extern	s16 getMotorActVoltFromObjId1ms(u8 t_bObjId);

extern	s16		getParaVFCompCofig(u8 t_bObjId);

/*******************************************************************************
 函数名称：    void AdcSampleCal(stru_FOC_CtrProcDef *this)
 功能描述：    电流采样
 输入参数：    PSTR_MotorFoc tS_pFocObj
 输出参数：    无
 返 回 值：    无
 其它说明：    1.电流采样，采集AB两相电流，原始值作为标幺后数值
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0            Wencai.Zhao Howlet Li          创建
 2023/8/5      V1.1            Tonghua.Li          			  修改数据标幺格式
 *******************************************************************************/
static inline void AdcCurSampleCalc(PSTR_MotorFoc tS_pFocObj)
{
    PSTR_CurSamplingRes this;
    this = &tS_pFocObj->mCurSamplingRes;  //指针
    STR_VectorUVW*	t_pStatCurrUVW = tS_pFocObj->m_pStatCurrUVW;

	this->mCurSamplingEvent.pAdcSamp(this);
    /* 电流标幺化处理,采用AD原始值的Q15格式*/
	t_pStatCurrUVW->nPhaseU = this->pAdcRes->nSampDatU;
	t_pStatCurrUVW->nPhaseV = this->pAdcRes->nSampDatV;
	t_pStatCurrUVW->nPhaseW = this->pAdcRes->nSampDatW;

    /* clark变换 */
	tS_pFocObj->m_pStatCurrAB->nBeta = _IQ15mpy(18919, (t_pStatCurrUVW->nPhaseV - t_pStatCurrUVW->nPhaseW));
	tS_pFocObj->m_pStatCurrAB->nAlph = t_pStatCurrUVW->nPhaseU;
}

/*******************************************************************************
 函数名称：    static inline void RespondPwmCmd(PSTR_MotorFoc tS_pMotorFoc)
 功能描述：    处理MA层发送的MOE命令
 输入参数：    PSTR_MotorFoc tS_pMotorFoc
 输出参数：    无
 返 回 值：    无
 其它说明：    1.IPD时，IPD程序可自由控制MOE
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0            Wencai.Zhao Howlet Li          创建
 2023/8/5      V1.1            Tonghua.Li          			  修改注释
 *******************************************************************************/
static inline void RespondPwmCmd(PSTR_MotorFoc tS_pMotorFoc)
{
	/* 根据MA到MD层的MOE操作命令，调用硬件驱动函数操作MOE */
	if(E_PWM_ON == tS_pMotorFoc->pMaToMd->ePwmCmd)
	{
		if(++g_buMdPWMONDelay[tS_pMotorFoc->m_bFOCObj_ID] >= 2)
		{
			if(tS_pMotorFoc->pMaToMd->bIpdStart == 0)
			{
				
				tS_pMotorFoc->m_pHALHandle->PwmOutEnable(ENABLE);	//使能MOE
			}
			tS_pMotorFoc->ePWMStatusAck		= E_PWM_ON;
			g_buMdPWMONDelay[tS_pMotorFoc->m_bFOCObj_ID] = 2;
		}
	}
	else
	{
		if(tS_pMotorFoc->pMaToMd->bIpdStart == 0)
		{
			tS_pMotorFoc->m_pHALHandle->PwmOutEnable(DISABLE);	//关闭MOE
		}
		tS_pMotorFoc->ePWMStatusAck		= E_PWM_OFF;
		g_buMdPWMONDelay[tS_pMotorFoc->m_bFOCObj_ID] = 0;
	}
}

/*******************************************************************************
 函数名称：    static inline void RespondPWMStatus(PSTR_MotorFoc tS_pMotorFoc )
 功能描述：    发送MD层PWM状态到MA层
 输入参数：    PSTR_MotorFoc tS_pMotorFoc
 输出参数：    无
 返 回 值：    无
 其它说明：    
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/15      V1.0            Tonghua.Li          			  创建
 2023/9/05      V1.1            Tonghua.Li          			  修改注释
 *******************************************************************************/
static inline void RespondPWMStatus(PSTR_MotorFoc tS_pMotorFoc )
{
	/* MD层返回到MA层MOE状态 */
	tS_pMotorFoc->pMdToMa->ePwmStatus		= tS_pMotorFoc->ePWMStatusAck;
}

/*******************************************************************************
 函数名称：    static inline void RespondMotorStatus(PSTR_MotorFoc tS_pMotorFoc)		
 功能描述：    发送MD层电机状态机变量到MA层
 输入参数：    PSTR_MotorFoc tS_pMotorFoc
 输出参数：    无
 返 回 值：    无
 其它说明：    
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/15      V1.0            Tonghua.Li          			  创建
 2023/9/05      V1.1            Tonghua.Li          			  修改注释
 *******************************************************************************/
static inline void RespondMotorStatus(PSTR_MotorFoc tS_pMotorFoc)
{
	/* MD层返回到MA层电机状态 */
	tS_pMotorFoc->pMdToMa->eMotorStatusAck	= tS_pMotorFoc->eMotorStatusAck;
}

/*******************************************************************************
 函数名称：    static inline void updateMd2MaVar(PSTR_MotorFoc tS_pMotorFoc)
 功能描述：    发送MD层电机控制变量到MA层
 输入参数：    PSTR_MotorFoc tS_pMotorFoc
 输出参数：    无
 返 回 值：    无
 其它说明：    
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/15      V1.0            Tonghua.Li          			  创建
 2023/9/05      V1.1            Tonghua.Li          			  修改注释
 *******************************************************************************/
static inline void updateMd2MaVar(PSTR_MotorFoc tS_pMotorFoc)
{
	u8 t_bObjId = tS_pMotorFoc->m_bFOCObj_ID;
	tS_pMotorFoc->pMdToMa->wFreq	= tS_pMotorFoc->m_pMotorFocSpeed->wSpeedEst;		//	估算转速(频率)
	tS_pMotorFoc->pMdToMa->nVdc		= tS_pMotorFoc->pHdToMd->nDcVolAdcDat;				//	直流电压采样值

	tS_pMotorFoc->pMdToMa->mStatVolDQ.nAxisD = getMotorDaxisVoltFormObjId(t_bObjId);	//	d轴电压
	tS_pMotorFoc->pMdToMa->mStatVolDQ.nAxisQ = getMotorQaxisVoltFormObjId(t_bObjId);	//	q轴电压

	#if (QUICK_CURRENTKLOOP_FUNCTION == FUNCTION_ON)
	tS_pMotorFoc->pMdToMa->nMotorCur	= getMotorCurFromObjId1ms(t_bObjId);			//	电机相电流峰值
	tS_pMotorFoc->pMdToMa->nMotorVol	= getMotorActVoltFromObjId1ms(t_bObjId);		//	实际施加到电机电压 SQRT(Ud^2 + Uq^2)
	#else
	tS_pMotorFoc->pMdToMa->nMotorCur	= getMotorCurFromObjId(t_bObjId);				//	电机相电流峰值
	tS_pMotorFoc->pMdToMa->nMotorVol	= getMotorActVoltFromObjId(t_bObjId);		//	实际施加到电机电压 SQRT(Ud^2 + Uq^2)
	#endif

	
	tS_pMotorFoc->pMdToMa->nPowerDec	= getMotorPowerFromObjId(t_bObjId);			//	估算的电机功率
	
	if(tS_pMotorFoc->eMotorStatusAck == E_MOTOR_TRACKING)
	{
		tS_pMotorFoc->pMdToMa->wFreq	= getOnFlyFreqResultFromObjId(t_bObjId);	//	顺逆风频率
	}
	
	#if (DRV0_BEMF_CHECK_EABLE==FUNCTION_ON)
	if(tS_pMotorFoc->eMotorStatusAck == E_MOTOR_BEMF_TRACKING)		//	反电势电路顺逆风
	{
		tS_pMotorFoc->pMdToMa->wFreq	= getOnFlyBemfFreqResultFromObjId(t_bObjId);	//	Bemf顺逆风检测转速
	}
	#endif
	
	tS_pMotorFoc->pMdToMa->bBreakInFault	= tS_pMotorFoc->pHdToMd->bBreakInStatus;	//	BreakIn信号(硬件过流)
}

/*******************************************************************************
 函数名称：    static inline void updateMa2MdVar(PSTR_MotorFoc tS_pMotorFoc)
 功能描述：    处理MA层发送的MD的命令及状态
 输入参数：    PSTR_MotorFoc tS_pMotorFoc
 输出参数：    无
 返 回 值：    无
 其它说明：    
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/15      V1.0            Tonghua.Li          			  创建
 2023/9/05      V1.1            Tonghua.Li          			  修改注释
 *******************************************************************************/
static inline void updateMa2MdVar(PSTR_MotorFoc tS_pMotorFoc)
{
	tS_pMotorFoc->m_pMotorFocSpeed->wSpeedRef	= tS_pMotorFoc->pMaToMd->wMotorSpeedRef;   /* 转速指令 */
}

/*******************************************************************************
 函数名称：    static inline void RegMotorCurrentDQInline(PSTR_MotorFoc tS_pFocObj)
 功能描述：    电流环PI调节内联函数
 输入参数：    PSTR_MotorFoc tS_pMotorFoc
 输出参数：    无
 返 回 值：    无
 其它说明：    内联函数用于减少函数调用时间
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/15      V1.0            Tonghua.Li          			  创建
 2023/9/05      V1.1            Tonghua.Li          			  修改注释
 *******************************************************************************/
s16 QV = 0;
static inline void RegMotorCurrentDQInline(PSTR_MotorFoc tS_pFocObj)
{
	if(!tS_pFocObj->bObserWork)
	{
		#if (VF_START_FUNCTION_ENABLE == FUNCTION_ON)		
		if(!getCurLoopCloseStatusFromOB(tS_pFocObj->m_bFOCObj_ID))	//电流环开环
		{
			tS_pFocObj->m_pAcrQ->nError = 0;
			tS_pFocObj->m_pAcrD->nError = 0;
		}
		else														//电流环闭环
		#endif
		{		
			tS_pFocObj->m_pAcrQ->nError = (s32)tS_pFocObj->m_pStatCurrDQRef->nAxisQ - tS_pFocObj->m_pStatCurrDQ->nAxisQ; /* Q轴输入误差 */
			tS_pFocObj->m_pAcrD->nError = (s32)tS_pFocObj->m_pStatCurrDQRef->nAxisD - tS_pFocObj->m_pStatCurrDQ->nAxisD;  /* D轴输入误差 */
		}

		tS_pFocObj->m_pVolDQ->nAxisQ = CurrentPIRegulator(tS_pFocObj->m_pAcrQ);		/* Q轴电流PI计算，输出Vq */
		tS_pFocObj->m_pVolDQ->nAxisD = CurrentPIRegulator(tS_pFocObj->m_pAcrD);		/* D轴电流PI计算，输出Vd */
     //   tS_pFocObj->m_pVolDQ->nAxisQ = QV;		/* Q轴电流PI计算，输出Vq */
		//tS_pFocObj->m_pVolDQ->nAxisD = 0;		/* D轴电流PI计算，输出Vd */
	}

	//	电压极限圆控制，内部包含自动过调制功能
	CalcVolCircle(tS_pFocObj->m_bFOCObj_ID,tS_pFocObj->m_pVolDQ,tS_pFocObj->m_pVectVolAB);
}


/*******************************************************************************
 函数名称：    static void MDHandleCmdIn1msLoop(PSTR_MotorFoc tS_pMotorFoc) 
 功能描述：    MA到MD命令处理
 输入参数：    PSTR_MotorFoc tS_pMotorFoc    FOC对象结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：		用于1ms任务进行MA/MD命令处理
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/07/15      V1.1       Tonghua Li			更改为1ms任务处理，缩短中断时间
 *******************************************************************************/
static void MDHandleCmdIn1msLoop(PSTR_MotorFoc tS_pMotorFoc)
{	
	u8	t_bObjId = tS_pMotorFoc->m_bFOCObj_ID;
	s16 t_compFactor = 0;
	
	if((E_FC_RESET_INIT_OBS == tS_pMotorFoc->pMaToMd->nuFineCmd) 
		&& (E_FC_RESET_INIT_OBS != tS_pMotorFoc->pMdToMa->nuFineStatus))
	{
		FluxObserveParaCalc(t_bObjId);				//观测器参数初始化
		#if (VECTOR_VF_COMP_ENABLE == FUNCTION_ON)
		CalcVectorVFPara(t_bObjId);						//VF参数初始化

		t_compFactor = getParaVFCompCofig(t_bObjId);
		if(t_compFactor != 0)
		{
			setDeadCompFactor(t_bObjId, t_compFactor);	// 补偿系数
		}
		#endif

		tS_pMotorFoc->pMdToMa->nuFineStatus = E_FC_RESET_INIT_OBS;
	}
	else if((E_FC_RESET_INIT_ACR == tS_pMotorFoc->pMaToMd->nuFineCmd) 
			&& (E_FC_RESET_INIT_ACR != tS_pMotorFoc->pMdToMa->nuFineStatus))
	{
		InitFocVar(tS_pMotorFoc);						//电流环变量初始化
		InitPmFluxOB(t_bObjId);							//观测器变量初始化
		#if (DRV0_DIR_CHECK_ENABLE==FUNCTION_ON)	
		OnTheFlyDetectInit(t_bObjId);					//顺逆风变量初始化
		#endif
				
		#if (DRV0_BEMF_CHECK_EABLE==FUNCTION_ON)
		Bemf_CheckInit(t_bObjId,getBemfAngComp(t_bObjId),getBemfTrackMinVolt(t_bObjId));   /*反电势检测变量初始化*/
		#endif
		
		tS_pMotorFoc->pMdToMa->nuFineStatus = E_FC_RESET_INIT_ACR;
	}
	else if((E_FC_RESET_INIT_SVPWM == tS_pMotorFoc->pMaToMd->nuFineCmd) 
		&& (E_FC_RESET_INIT_SVPWM != tS_pMotorFoc->pMdToMa->nuFineStatus))
	{
		InitFocVar(tS_pMotorFoc);						//电流环变量初始化
		InitPmFluxOB(t_bObjId);							//观测器变量初始化
		tS_pMotorFoc->pMdToMa->nuFineStatus = E_FC_RESET_INIT_SVPWM;
	}
	
	else if((E_FC_RESET_INIT_IPD == tS_pMotorFoc->pMaToMd->nuFineCmd) 
		&& (E_FC_RESET_INIT_IPD != tS_pMotorFoc->pMdToMa->nuFineStatus))
	{
		InitIPD(t_bObjId);                /*IPD初始化*/
		tS_pMotorFoc->pMdToMa->nuFineStatus = E_FC_RESET_INIT_IPD;
	}
	
	else if((E_FC_IPD_CW_START == tS_pMotorFoc->pMaToMd->nuFineCmd) 
		&& (E_FC_IPD_CCW_START != tS_pMotorFoc->pMdToMa->nuFineStatus))
	{
		tS_pMotorFoc->pMdToMa->nuFineStatus = tS_pMotorFoc->pMdToMa->nuFineStatus;
	}	
	
	else if((E_FC_RESET_CHARGE_A == tS_pMotorFoc->pMaToMd->nuFineCmd) 
		&& (E_FC_RESET_CHARGE_A != tS_pMotorFoc->pMdToMa->nuFineStatus))
	{
		tS_pMotorFoc->m_pHALHandle->PwmCharge(1);		//A相预充电
		tS_pMotorFoc->pMdToMa->nuFineStatus = E_FC_RESET_CHARGE_A;
	}
	else if((E_FC_RESET_CHARGE_B == tS_pMotorFoc->pMaToMd->nuFineCmd) 
		&& (E_FC_RESET_CHARGE_B != tS_pMotorFoc->pMdToMa->nuFineStatus))
	{
		tS_pMotorFoc->m_pHALHandle->PwmCharge(2);		//B相预充电
		tS_pMotorFoc->pMdToMa->nuFineStatus = E_FC_RESET_CHARGE_B;
	}
	else if((E_FC_RESET_CHARGE_C == tS_pMotorFoc->pMaToMd->nuFineCmd) 
		&& (E_FC_RESET_CHARGE_C != tS_pMotorFoc->pMdToMa->nuFineStatus))
	{
		tS_pMotorFoc->m_pHALHandle->PwmCharge(3);		//C相预充电
		tS_pMotorFoc->pMdToMa->nuFineStatus = E_FC_RESET_CHARGE_C;
	}
	else if((E_FC_RESET_CHARGE_DONE_INIT == tS_pMotorFoc->pMaToMd->nuFineCmd) 
		&& (E_FC_RESET_CHARGE_DONE_INIT != tS_pMotorFoc->pMdToMa->nuFineStatus))
	{
		tS_pMotorFoc->m_pHALHandle->InitPwmChargeEnd();	//预充电结束后，初始化变量
		tS_pMotorFoc->pMdToMa->nuFineStatus = E_FC_RESET_CHARGE_DONE_INIT;
	}
	else if((E_FC_RESET_CLR_BREAKIN_FAULT == tS_pMotorFoc->pMaToMd->nuFineCmd) 
		&& (E_FC_RESET_CLR_BREAKIN_FAULT != tS_pMotorFoc->pMdToMa->nuFineStatus))
	{
		tS_pMotorFoc->m_pHALHandle->ClrEPWMBreakIn();						//清除breakin信号
		tS_pMotorFoc->m_pHALHandle->GetEPWMBreakIn(tS_pMotorFoc->pHdToMd);	//读取breakin信号
		if(!tS_pMotorFoc->pHdToMd->bBreakInStatus)
		{				
			tS_pMotorFoc->pMdToMa->nuFineStatus = E_FC_RESET_CLR_BREAKIN_FAULT;
		}
	}
	else
	{
		tS_pMotorFoc->pMdToMa->nuFineStatus = tS_pMotorFoc->pMaToMd->nuFineCmd;
	}
			
	if(E_FC_NON == tS_pMotorFoc->pMaToMd->nuFineCmd)
	{
		tS_pMotorFoc->pMdToMa->nuFineStatus		= E_FC_NON;			//默认命令状态
	}
}
/*******************************************************************************
 函数名称：    static void FOC_Model(PSTR_MotorFoc tS_pMotorFoc) 
 功能描述：    PMSM电机Q轴转矩控制，D轴电流控制处理，实现FOC控制的核心电流环
 输入参数：    PSTR_MotorFoc tS_pMotorFoc    FOC对象结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/16      V1.0       Wencai.Zhao				创建
 2020/12/15      V1.1       Tonghua Li				完善TRAKING/IPD及命令交换处理
 *******************************************************************************/
static inline void FOC_Model(PSTR_MotorFoc tS_pMotorFoc)
{	
	ENUM_MotorStatus t_eMotorStatus = E_MOTOR_RESET;

	s16 t_nTmp;
	u8					t_bObjId		= tS_pMotorFoc->m_bFOCObj_ID;
	PSTR_VectorAB		t_pStatCurrAB	=  tS_pMotorFoc->m_pStatCurrAB;		//传递电流AB指针
	STR_TrigComponents	*t_pSinCos		= &tS_pMotorFoc->mSinCosFocAngle;	//sin cos查表计算
	STR_PubDatMAMD*		t_pMaToMd		 =  tS_pMotorFoc->pMaToMd;			//传递FOC变量指针

	AdcCurSampleCalc(tS_pMotorFoc);            /*电流采样函数计算*/

	if(tS_pMotorFoc->bObserWork)
	{
		tS_pMotorFoc->bObserWork = FALSE;
		CalcDcVoltPerUnit(t_bObjId,tS_pMotorFoc->pHdToMd->nDcVolAdcDat);
	}
	else
	{
		tS_pMotorFoc->bObserWork = TRUE;
	}
	
	setLibWorkMode(t_bObjId, tS_pMotorFoc->bObserWork);
	
	t_eMotorStatus = t_pMaToMd->eMotorStatus;

	switch(t_eMotorStatus)
	{
		case E_MOTOR_RESET:    /* 电机复位等待 */
		{			
			t_nTmp		= ((s32)t_pMaToMd->nMotorBrakePwmDuty * tS_pMotorFoc->m_pSvpwmPar->nuPwmPrd)>>12;
			SetCmprDuty(tS_pMotorFoc->m_pCmpr,t_nTmp);      /* 设置PWM比较装载数值 */
			
			tS_pMotorFoc->m_pHALHandle->MCPWMx_RegUpdate(tS_pMotorFoc->pMdToHd);  /* 加载PWM模块占空比值 */

			#if ((DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_3SHUNT) || (DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_MOSFET))
			tS_pMotorFoc->pMdToHd->mMcTmr.eChannel = E_PHASE_A_B;	/* 设置采样通道为AB */
			tS_pMotorFoc->m_pHALHandle->AD_ChannelUpdate(tS_pMotorFoc->pMdToHd);
			#endif

			break;
		}

		#if (DRV0_BEMF_CHECK_EABLE==FUNCTION_ON)
		case E_MOTOR_BEMF_TRACKING:     /* 反电势顺逆风检测 */
		{
			tS_pMotorFoc->m_pHALHandle->PwmOutEnable(DISABLE);	//关闭MOE,采样反电势电压

			
			Bemf_CheckProcess(t_bObjId, 
								tS_pMotorFoc->pHdToMd->nBmefWVolAdcDat, 
								tS_pMotorFoc->pHdToMd->nBmefVVolAdcDat, 
								tS_pMotorFoc->pHdToMd->nBmefUVolAdcDat);    //C相 B相 A相
			

			BemfSwitch(t_bObjId,FALSE);   //切换赋值
			break;
		}
		#endif
			
		#if (DRV0_DIR_CHECK_ENABLE==FUNCTION_ON)		
		case E_MOTOR_TRACKING:        /* 观测器顺逆风检测 */
		{
			setTrakingModeEnable(t_bObjId);			/* 使能顺逆风检测 */
			if(!tS_pMotorFoc->bObserWork)
			{
				OnTheFlyDetectPro(t_bObjId);		/* 顺逆风检测计算函数 */
			}
			/*此处不加break，顺逆风检测需要用到电流环计算*/
		}
		#endif
		case E_MOTOR_ASYN:
		case E_MOTOR_ALIGN:           /* 对相 */
		case E_MOTOR_PRE_SYN:
		case E_MOTOR_SYN:
		{			
			if(t_eMotorStatus != E_MOTOR_TRACKING)
			{
				setTrakingModeDisable(t_bObjId);
			}
			//if(E_PWM_ON == tS_pMotorFoc->ePWMStatusAck)
			{
				tS_pMotorFoc->m_pMotorAngle->wElectAngle = tS_pMotorFoc->m_pMotorAngle->wElectAngleEst;          /* 观测器角度传递 */

				#if (MCU_DSP_SINCOS == FUNCTION_OFF)
				Trig_Functions((tS_pMotorFoc->m_pMotorAngle->wElectAngle >> 16),&tS_pMotorFoc->mSinCosFocAngle); /* sincos查表 */
				#else
				DSP0_SC |= BIT2;
    			DSP0_THETA = (tS_pMotorFoc->m_pMotorAngle->wElectAngle >> 16);                           /* sincos通过DSP计算 */
				tS_pMotorFoc->mSinCosFocAngle.hCos	= DSP0_COS;
				tS_pMotorFoc->mSinCosFocAngle.hSin	= DSP0_SIN;				
				#endif

				// alph/beta to dq 坐标变换		
				tS_pMotorFoc->m_pStatCurrDQ->nAxisQ  = (((s32)t_pStatCurrAB->nBeta * t_pSinCos->hCos) -
				                        ((s32)t_pStatCurrAB->nAlph * t_pSinCos->hSin)) >> 15;
				tS_pMotorFoc->m_pStatCurrDQ->nAxisD  = (((s32)t_pStatCurrAB->nAlph* t_pSinCos->hCos) +
				                        ((s32)t_pStatCurrAB->nBeta * t_pSinCos->hSin)) >> 15;

				// dq电流环 PI 计算
				RegMotorCurrentDQInline(tS_pMotorFoc);

				// SVPWM 调制
				tS_pMotorFoc->m_pHandle->Svpwm(t_bObjId,tS_pMotorFoc->m_pVectVolAB);

				// PWM 占空比更新			
				tS_pMotorFoc->m_pHALHandle->MCPWMx_RegUpdate(tS_pMotorFoc->pMdToHd);
							
				//  AD 通道更新
				#if ((DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_3SHUNT) || (DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_MOSFET))
				tS_pMotorFoc->m_pHALHandle->AD_ChannelUpdate(tS_pMotorFoc->pMdToHd);
				#endif
				

				// 观测器计算函数
				PmsmFluxObserve_Full(t_bObjId,tS_pMotorFoc->m_pStatCurrDQ);
				//PmsmFluxObserveIDSimply(t_bObjId,tS_pMotorFoc->m_pStatCurrDQ);
			}			
		break;
		}
		
		case E_MOTOR_BRAKE:
		{   /* PWM brake */

			// handle PWM brake duty
			t_nTmp		= ((s32)t_pMaToMd->nMotorBrakePwmDuty * tS_pMotorFoc->m_pSvpwmPar->nuPwmPrd)>>12;
			if(t_nTmp >= tS_pMotorFoc->m_pSvpwmPar->nuPwmPrd)
			{
				t_nTmp	= tS_pMotorFoc->m_pSvpwmPar->nuPwmPrd;    /* 占空比限幅处理 */
			}
			SetCmprDuty(tS_pMotorFoc->m_pCmpr,t_nTmp);          /* 占空比数值加载 */
			
			// PWM 占空比更新	 
			tS_pMotorFoc->m_pHALHandle->MCPWMx_RegUpdate(tS_pMotorFoc->pMdToHd);
			
			// 根据采样方式设置默认采样状态
			#if ((DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_3SHUNT) || (DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_MOSFET))
			tS_pMotorFoc->pMdToHd->mMcTmr.eChannel = E_PHASE_A_B;						/* 采样模式选择 */
			tS_pMotorFoc->mCurSamplingRes.mCurSamplingEvent.bSamplingEv1 = SAMP_IA;		/* A相电流采样  */
			tS_pMotorFoc->mCurSamplingRes.mCurSamplingEvent.bSamplingEv2 = SAMP_IB;		/* B相电流采样  */
			tS_pMotorFoc->m_pHALHandle->AD_ChannelUpdate(tS_pMotorFoc->pMdToHd);		/* AD通道更新   */	
			tS_pMotorFoc->mCurSamplingRes.mCurSamplingEvent.pAdcSamp	 = (ADCSampFunction)&SVPWM_3ShuntGetPhaseIaIb;
			#endif

			InitFocVar(tS_pMotorFoc);           /* FOC参数初始化 */
			InitPmFluxOB(t_bObjId);				/* 观测器参数初始化 */
			break;
		}
		
		#if (DRV0_POS_SEEK_ENABLE==FUNCTION_ON)    /* 单电机IPD处理 */
		#if 1
		case E_MOTOR_IPD:         /*IPD初始位置检测*/
		{
			if( (E_FC_IPD_CW_START == t_pMaToMd->nuFineCmd)
				||(E_FC_IPD_CCW_START == t_pMaToMd->nuFineCmd)
			  )
			{
				if(tS_pMotorFoc->m_bIPDFinsh == 0)
				{
					__disable_irq();                  /* 关闭中断 中断总开关 */
					ADC_SOFTWARE_TRIG_ONLY();
    				ADC_STATE_RESET();
					IPDEst_SMotor(t_bObjId);
					tS_pMotorFoc->m_pHALHandle->InitPwmChargeEnd();
					__enable_irq();                   /* 开启总中断 */

					tS_pMotorFoc->pMdToMa->nuFineStatus = E_FC_IPD_DOING;
				}
				else
				{
					// 角度初始化函数已在IPD完成
					tS_pMotorFoc->pMdToMa->nuFineStatus = E_FC_IPD_DONE;
				}
			}
			break;
		}
		#else									/* 双电机IPD处理 */
		case E_MOTOR_IPD:          				/*IPD初始位置检测*/
		{
			IPDEst_DMotor(t_bObjId);			//	双电机IPD
			tS_pMotorFoc->m_pHALHandle->MCPWMx_RegUpdate(tS_pMotorFoc->pMdToHd);
			if( (E_FC_IPD_CW_START == tS_pMotorFoc->pMaToMd->nuFineCmd)
				||(E_FC_IPD_CCW_START == tS_pMotorFoc->pMaToMd->nuFineCmd)
			  )
			{
				if(tS_pMotorFoc->m_bIPDFinsh == 1)
				{
					// 角度初始化函数已在IPD完成
					tS_pMotorFoc->pMdToMa->nuFineStatus = E_FC_IPD_DONE;    /* 状态机IPD_DONE */
				}
				else
				{
					tS_pMotorFoc->pMdToMa->nuFineStatus = E_FC_IPD_DOING;   /* 状态机IPD_DOING */
				}
			}
			break;
		}
		#endif
		#endif
		
		default:
			
        break;
	}

	#if (QUICK_CURRENTKLOOP_FUNCTION == FUNCTION_ON)		//快速电流环模式
		tS_pMotorFoc->eMotorStatusAck	= t_eMotorStatus;					//电机状态机传递
		tS_pMotorFoc->m_pHALHandle->GetEPWMBreakIn(tS_pMotorFoc->pHdToMd);  //PWMbreakin状态传递
		RespondPwmCmd(tS_pMotorFoc);
	#else													//慢速电流环模式，所有处理在电流环完成
		if(E_FC_NON == t_pMaToMd->nuFineCmd)
		{
			tS_pMotorFoc->pMdToMa->nuFineStatus		= E_FC_NON;
		}
		updateMa2MdVar(tS_pMotorFoc);										//更新MA to MD 状态及电压速度等信息
		
		tS_pMotorFoc->m_pHALHandle->GetEPWMBreakIn(tS_pMotorFoc->pHdToMd);	//PWMbreakin状态传递
		RespondPwmCmd(tS_pMotorFoc);										//处理 MOE命令
		tS_pMotorFoc->eMotorStatusAck	= t_eMotorStatus;					//电机状态机传递
		RespondPWMStatus(tS_pMotorFoc);										// 反馈MA层MOE状态
		RespondMotorStatus(tS_pMotorFoc);									// 反馈MA层电机状态
		updateMd2MaVar(tS_pMotorFoc);										// 更新MD到MA层电机状态及信息
		PmsmFluxObserve1ms(t_bObjId);										// 观测器慢速处理函数，可放到1ms中
	#endif
}

/*******************************************************************************
 函数名称：    void MDtaskHandleIn1msLoop(void)
 功能描述：    MD层1ms任务
 输入参数：    void
 输出参数：    无
 返 回 值：    无
 其它说明：	   执行1ms任务处理
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/02/15      V1.1       Tonghua Li				创建
 *******************************************************************************/
#if (QUICK_CURRENTKLOOP_FUNCTION == FUNCTION_ON)        //快速电流环模式

void MDtaskHandleIn1msLoop(void)
{
	PSTR_MotorFoc tS_pMotorFoc = &gS_FocObjM[0];

	MDHandleCmdIn1msLoop(tS_pMotorFoc);   //1ms任务调度

	/* 数据指针传递 */
	updateMa2MdVar(tS_pMotorFoc);					//更新MA to MD 状态及电压速度等信息
		
	RespondPWMStatus(tS_pMotorFoc);					// 反馈MA层MOE状态
	RespondMotorStatus(tS_pMotorFoc);				// 反馈MA层电机状态
	updateMd2MaVar(tS_pMotorFoc);					// 更新MD到MA层电机状态及信息

	PmsmFluxObserve1ms(0);							// 观测器慢速1ms处理函数
		
	#if (OBSERVER_PLL_CHANGE_ENABLE == FUNCTION_ON)
	updateObserPLLVar1msLoop(tS_pMotorFoc);		// 观测器PLL参数处理函数
	#endif
		
	#if (VECTOR_VF_COMP_ENABLE == FUNCTION_ON)		// 电压处理函数
			vectorVFcontrol(0,&tS_pMotorFoc->m_pAcrD->nComp,&tS_pMotorFoc->m_pAcrQ->nComp);
		#endif
}

#else   //慢速电流环模式
	/* 单电机1ms任务处理函数 */
void MDtaskHandleIn1msLoop(void)
{
	PSTR_MotorFoc tS_pMotorFoc = &gS_FocObjM[0];		
	
	MDHandleCmdIn1msLoop(tS_pMotorFoc);     //1ms任务调度
	
	#if (OBSERVER_PLL_CHANGE_ENABLE == FUNCTION_ON)
	updateObserPLLVar1msLoop(tS_pMotorFoc);			// 观测器PLL参数处理函数
	#endif
	
	#if (VECTOR_VF_COMP_ENABLE == FUNCTION_ON)		// 电压处理函数
	vectorVFcontrol(0,&tS_pMotorFoc->m_pAcrD->nComp,&tS_pMotorFoc->m_pAcrQ->nComp);
	#endif
}

#endif

/*******************************************************************************
 函数名称：    void AdcEocIsrDRV0(void) 
 功能描述：    PMSM PWM0 FOC控制
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/16      V1.0       Wencai.Zhao				创建
 2020/12/15      V1.1       Tonghua Li				完善HAL层驱动接口
 *******************************************************************************/
void AdcEocIsrDRV0(void)
{
	PSTR_MotorFoc tS_pMotorFoc;
	STR_PubDatHDMD* tS_pCurAdcRes;
	tS_pMotorFoc = &gS_FocObjM[0];

	// 传递电压、电流的AD采样数据
	tS_pCurAdcRes = tS_pMotorFoc->pHdToMd;
	#if 0   //指针传递AD数值，速度慢
	tS_pMotorFoc->m_pHALHandle->AcquireCurrent(tS_pCurAdcRes);
	tS_pMotorFoc->m_pHALHandle->AcquireVdc(tS_pCurAdcRes);
	#else   //内联函数读取AD数值，速度快
	AcquireCurSamplingResultsDRV0(tS_pCurAdcRes);
	AcquireVdcSamplingResultsDRV0(tS_pCurAdcRes);	
	#endif
	
	FOC_Model(tS_pMotorFoc);    /* FOC矢量控制 */

	#if 0
	// 时限要求不严格时，在1ms任务中时限相同的功能
	if(tS_pMotorFoc->pMaToMd->eMotorStatus == E_MOTOR_SYN)
	{
		FaultCurrentCheck(tS_pMotorFoc->m_pStatCurrUVW, tS_pMotorFoc->m_bFOCObj_ID);
	}
	#endif
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

