/*!
 *-----------------------------------------------------------------------------
 * 	Copyright (c) Lks Corp., Ltd. All Rights Reserved. \n
 *  
 *
 *  @file    mc_declaration.h
 *
 *  @brief   MC_control declaration
 * 		  
 *		  
 *
 *  @author  zhao wencai
 *
 *  @version  v1.0
 * 
 *  @date    2019-11-07 23:25:30
 *  
 *-----------------------------------------------------------------------------
 */
#ifndef __MC_DECLARATION_H
#define __MC_DECLARATION_H

#include "basic.h"
#include "PubData_DriverInstance.h"

/*电机驱动层FOC定义：电流环、电压极限园、空间矢量调制、估算器、初始位置检测*/
//marco define. use for motor drive layer.

///debug marco.
#define MOTOR_CTRL_SVC		(0)
#define MOTOR_CTRL_IF		(1)
#define MOTOR_CTRL_VF		(2)
#define MOTOR_CTRL_MODE		(MOTOR_CTRL_IF)

#define SAMP_NO               0
#define SAMP_IA               1
#define SAMP_IB               2
#define SAMP_IC               3
#define SAMP_NIA              4
#define SAMP_NIB              5
#define SAMP_NIC              6
#define SAMP_OLDA             7
#define SAMP_OLDB             8
#define SAMP_OLDC             9

typedef void (*ADCSampFunction)(void *this);		//AD采样结果读取函数指针

//新增的结构体
typedef struct
{
    s16 nPhaseU;
    s16 nPhaseV;
} STR_CurrPhaseUV;

/*****************************************************************************
 * 结构体名 : STR_PIRegulator,*PSTR_PIRegulator
 * 说明     : 电流环PI控制数据结构
 *          : 
 * 			:
 * 修改时间 ：2022.08.17
 *****************************************************************************/
typedef struct 
{
	s32 wUpperLimitOutput;			/* Lower Limit for Output limitation */
	s32 wLowerLimitOutput;			/* Lower Limit for Output limitation */
	u16 KP;							/* 比例系数 */
	u16 KI;							/* 积分系数 */
	s32 nError;						/* 输入误差 */
	s32 nLastError;					/* 上次输入误差 */
	s16 nComp;
	s16 nOut;						/* 输出 */
	s32 wIntegral;					/* 积分器 */
}STR_PIRegulator,*PSTR_PIRegulator;

/*****************************************************************************
 * 结构体名 : STR_MotorLdqId
 * 说明     : Ld/Lq变参数数据结构
 *          : 预留
 * 			:
 * 修改时间 ：2022.08.17
 *****************************************************************************/
typedef struct {
	int16_t nCurSet;
	int16_t nFreqSet;
	int16_t nCurStep;
	//uint16_t Ld;
	//uint16_t Lq;
	
	int16_t nLdCoef2Od;
	int16_t nLdCoef1OD;
	int16_t nLdCoef0;
	
	int16_t nLqCoef2Od;
	int16_t nLqCoef1Od;
	int16_t nLqCoef0;
	
	uint16_t nuSts;	
}STR_MotorLdqId;


/*****************************************************************************
 * 结构体名 : STR_CurSamplingRes,*PSTR_CurSamplingRes
 * 说明     : AD采样 采样点及采样数据 数据结构定义
 *          : 
 * 			:
 * 修改时间 ：2022.08.17
 *****************************************************************************/
typedef struct
{
	u8 bSamplingEv1;
	u8 bSamplingEv2;
	ADCSampFunction pAdcSamp;						/* AD采样读取函数 */
} STR_CurSamplingEvent,*PSTR_CurSamplingEvent;

typedef struct
{
	STR_CurSamplingEvent		mCurSamplingEvent;	/* 采样事件及读取函数指针 	*/
	STR_PubDatHDMD* 			pAdcRes;			/* 采样存储指针				*/
} STR_CurSamplingRes,*PSTR_CurSamplingRes;

/*****************************************************************************
 * 结构体名 : STR_MotorFocHandle,*PSTR_MotorFocHandle
 * 说明     : FOC控制实现方法指针函数
 *          : 
 * 			:
 * 修改时间 ：2022.08.17
 *****************************************************************************/
typedef struct{
	void (*Svpwm)(u8 t_bObjId,PSTR_VectorAB tS_pVolAB);		/* SVPWM函数指针	*/
}STR_MotorFocHandle,*PSTR_MotorFocHandle;

/*****************************************************************************
 * 结构体名 : STR_FluxObsGainCoefDef, *PSTR_FluxObsGainCoefDef
 * 说明     : 观测器参数数据结构，库函数会引用
 *          : 修改时确保不会影响到库函数寻址
 * 			:
 * 修改时间 ：2022.08.17
 *****************************************************************************/
typedef struct
{   /* 观测器参数变量定义 */
	u16 nD_CurrLoopKP;         /* D轴电流环KP修正值 */
	u16 nD_CurrLoopKI;         /* D轴电流环KI修正值 */
	u16 nQ_CurrLoopKP;         /* Q轴电流环KP修正值 */
	u16 nQ_CurrLoopKI;         /* Q轴电流环KI修正值 */

	u16 nSTO_KP;               /* 观测器PLL KP值 */
	u16 nSTO_KI;               /* 观测器PLL KP值 */

	s32 CurrentPerUnitGAIN;    /* 电流标幺化处处理增益 */
	s32 VDC_PerUnitGAIN;       /* 电压采样标幺化处理增益 */
	s32 FREQ_PerUnit_GAIN;     /* 频率标幺化处理增益 */
	s32 BEMF_PerUnit_GAIN;     /* 反电势标幺化处理增益 */
}STR_FluxObsGainCoefDef, *PSTR_FluxObsGainCoefDef;		//	观测器参数数据结构


/*****************************************************************************
 * 结构体名 : STR_MotorFocElement,*PSTR_MotorFocElement
 * 说明     : FOC控制数据
 *          : 
 * 			:
 * 修改时间 ：2022.08.17
 *****************************************************************************/
typedef struct {
	uint32_t	wElectAngle;			/* 实际使用场定向角 */
	uint32_t	wElectAngleEst; 		/* 估算器角度 */
	uint32_t	wSensorAngle;			/* 编码器检测角度 */
	uint32_t	wElectAngleOpen;		/* 开环角度 */
}STR_MotorFocAngle,*PSTR_MotorFocAngle;

typedef struct {
	int32_t wSpeedEst;					/* 观测速度 */
	int32_t wSpeedRef;					/* 指令速度 */
}STR_MotorFocSpeed,*PSTR_MotorFocSpeed;

typedef struct {
	int16_t nFluxEst;
	uint32_t wuAngleEst;
	int16_t nSpdEst;
	int16_t nTorqEst;
	int16_t nPower;
	int16_t nEff;	
}STR_MotorObsResult;

typedef struct{
	//s16 nUdc;
	STR_VectorUVW			mStatCurrUVW;	/*定子电流UVW	*/
	STR_VectorAB			mStatCurrAB;	/*定子电流AB	*/
	STR_VectorDQ			mStatCurrDQ;	/*定子电流dq	*/
	STR_MotorFocAngle		mMotorAngle;	/*角度结构体	*/
	STR_MotorFocSpeed		mMotorSpeed;	/*速度结构体	*/
	STR_PIRegulator			mAcrD;			/*d轴电流调节	*/
	STR_PIRegulator			mAcrQ;			/*q轴电流调节	*/
	STR_VectorDQ			mAcrOutDQ;		/*电流环输出	*/
	STR_VectorAB			mStatVolAB;		/*定子电压AB	*/	
	STR_FluxObsGainCoefDef	mFluxObsGain;
}STR_MotorFocElement,*PSTR_MotorFocElement;;

/*****************************************************************************
 * 结构体名 : STR_MotorFoc,*PSTR_MotorFoc
 * 说明     : FOC控制数据结构，库函数会引用
 *          : 修改时确保不会影响到库函数寻址
 * 			:
 * 修改时间 ：2022.08.17
 *****************************************************************************/
typedef struct{
	u8						m_bFOCObj_ID;		//当前对象ID
	u8						m_bPWM_ID;			//当前应用的PWM ID
	u8						m_bSampType;		//电流采样类型
	u8						m_bIPDFinsh;		//IPD操作结束
	u16						nuIPDAng;			//IPD角度结果
	u16						nuSysTimerPWM;
	bool					bObserWork;			//观测器工作标志  true  ----- 观测器工作
	STR_PubDatHDMD*			pHdToMd;			//HD传递到MD信息交换区指针
	STR_PubDatMDMA*			pMdToMa;			//MD传递到MA信息交换区指针
	STR_PubDatMAMD*			pMaToMd;			//MA传递到MD信息交换区指针
	STR_PubDatMDHD*			pMdToHd;			//MD传递到HD信息交换区指针

	PSTR_TransCoef			m_pTransCoef;		//数据标幺区指针

	PSTR_FluxObsGainCoefDef	m_pFluxObsGain;		//观测器内部参数数据结构指针

	PSTR_MotorFocParDef		m_pMotorFocPar;		//观测器配置参数指针

	ENUM_MotorStatus		eMotorStatusAck;	//电机状态
	ENUM_PWMStatus			ePWMStatusAck;		//PWM(MOE)状态
	STR_CurSamplingRes		mCurSamplingRes;	//AD采样事件等指针

	STR_TrigComponents		mSinCosFocAngle;	//FOC角度正余弦值
	STR_VectorUVW*			m_pStatCurrUVW;		//定子电流UVW		指针
	STR_VectorAB*			m_pStatCurrAB;		//定子电流AB		指针
	STR_VectorDQ*			m_pStatCurrDQ;		//定子电流dq		指针
	STR_VectorDQ*			m_pStatCurrDQRef;	//dq电流指令值		指针
	STR_MotorFocAngle*		m_pMotorAngle;		//电机角度			指针

	STR_PIRegulator*		m_pAcrD;			//d轴电流调节		指针
	STR_PIRegulator*		m_pAcrQ;			//q轴电流调节		指针

	PSTR_VectorDQ			m_pVolDQ;			//电流环输出dq电压	指针
	PSTR_VectorAB			m_pVectVolAB;		//AB电压			指针

	PSTR_FocSvpwmPar		m_pSvpwmPar;		//SVPWM参数			指针
	PSTR_FocObjPar			m_pFocObjPar;		//控制对象参数		指针
	PSTR_FocObsPar			m_pFocObsPar;		//FOC参数			指针

	PSTR_MotorFocSpeed		m_pMotorFocSpeed;	//FOC速度			指针

	PSTR_McpwmCmpr			m_pCmpr;			//MCPWM 脉宽			指针	
	PSTR_McpwmTmr			m_pTmr;				//AD采样点及通道配置	指针
	PSTR_MotorFocHandle		m_pHandle;			//FOC处理				函数指针
	PSTR_HALDrvHandle		m_pHALHandle;		//HD硬件处理函数		函数指针

}STR_MotorFoc,*PSTR_MotorFoc;		//	FOC控制对象数据结构

// 观测器参数初始化
extern void InitPmFluxOB(u8 t_bObjId);

// 电压极限圆控制，内部包含自动过调制功能
extern void CalcVolCircle(u8 t_bObjId,PSTR_VectorDQ tS_pVolDq,PSTR_VectorAB tS_pVolAB);

// 母线电压计算及标幺化
extern void CalcDcVoltPerUnit(u8 t_bObjId,s16 t_nUdcAdcRes);

extern void SVPWM_1Shunt(u8 t_bObjId,PSTR_VectorAB tS_pVolAB);
extern void SVPWM_2Shunt_En1(u8 t_bObjId,PSTR_VectorAB tS_pVolAB); 	//双电阻增强1
extern void SVPWM_2Shunt_En2(u8 t_bObjId,PSTR_VectorAB tS_pVolAB); 	//双电阻增强2
extern void SVPWM_3Shunt(u8 t_bObjId,PSTR_VectorAB tS_pVolAB);
extern void SVPWM_3Shunt_En(u8 t_bObjId,PSTR_VectorAB tS_pVolAB);

extern void SVPWM_2Shunt_En1_5Seg(u8 t_bObjId,PSTR_VectorAB tS_pVolAB); 	//双电阻增强1
extern void SVPWM_2Shunt_En2_5Seg(u8 t_bObjId,PSTR_VectorAB tS_pVolAB); 	//双电阻增强2
extern void SVPWM_3Shunt_5Seg(u8 t_bObjId,PSTR_VectorAB tS_pVolAB);
extern void SVPWM_3Shunt_En_5Seg(u8 t_bObjId,PSTR_VectorAB tS_pVolAB);


// 观测器参数初始化
extern void FluxObserveParaCalc(u8 t_bObjId);
//
// 简化代码、低速要求低
extern void PmsmFluxObserveIDSimply(u8 t_bObjId,PSTR_VectorDQ tS_pCurDq);

// 简化代码、低速要求高
extern void PmsmFluxObserveSimply_Full(u8 t_bObjId,PSTR_VectorDQ tS_pCurDq);

// 简化代码、低速要求高，大范围弱磁
extern void PmsmFluxObserveSimplyWeaken(u8 t_bObjId,PSTR_VectorDQ tS_pCurDq);

// 低速要求低，执行时间略短
extern void PmsmFluxObserve(u8 t_bObjId,PSTR_VectorDQ tS_pCurDq);

// 低速要求高，执行时间略长
void PmsmFluxObserve_Full(u8 t_bObjId,PSTR_VectorDQ tS_pCurDq);

// 低速要求高，大范围弱磁，执行时间长
void PmsmFluxObserveWeaken(u8 t_bObjId,PSTR_VectorDQ tS_pCurDq);

// 基于PmsmFluxObserve_Full，堵转处理
void PmsmFluxObserve_Full_En(u8 t_bObjId,PSTR_VectorDQ tS_pCurDq);


// 顺逆风变量初始化
extern void OnTheFlyDetectInit(u8 t_bObjId);

// 顺逆风检测计算函数 
extern void OnTheFlyDetectPro(u8 t_bObjId);

// 多电机应用 IPD参数初始化函数
extern void InitIPD(u8 t_bObjId);
// 多电机应用 IPD检测函数
extern void IPDEst_DMotor(u8 t_bObjId);

// 单电机应用 IPD检测函数
extern void IPDEst_SMotor(u8 t_bObjId);				//	单电机IPD函数


extern void SVPWM_GetPhaseCurrent(PSTR_CurSamplingRes this);


#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
#define Motor_FocMethod_M0   \
{  /* FOC Methods */									\
	SVPWM_2Shunt_En1,				/* SVPWM调制	*/	\
}
#elif (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
#define Motor_FocMethod_M0   \
{  /* FOC Methods */									\
	SVPWM_1Shunt,					/* SVPWM调制	*/	\
}
#else
#define Motor_FocMethod_M0   \
{  /* FOC Methods */									\
	SVPWM_3Shunt,					/* SVPWM调制	*/	\
}

#endif

#if (EPWM1_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
#define Motor_FocMethod_M1								\
{  /* FOC Methods */									\
	SVPWM_2Shunt_En1,				/* SVPWM调制	*/	\
}

#elif (EPWM1_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
#define Motor_FocMethod_M1								\
{  /* FOC Methods */									\
	SVPWM_1Shunt,					/* SVPWM调制	*/	\
}
#else
#define Motor_FocMethod_M1								\
{  /* FOC Methods */									\
	SVPWM_3Shunt,					/* SVPWM调制	*/	\
}

#endif


extern u16 getElectAngle(u8 t_bObjId);
extern u16 getElectAngleEst(u8 t_bObjId);


extern u32  Read_NVR(u32 addr);

//////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//库封装功能函数

//库支持最多控制对象数目
extern u8 getLibMaxObjNumber(void);


//运行异常处理函数
extern bool motorStopOrExceptionHandle(u8 RunStop,pSTR_MotorExceptionMA this,s16 *PReturnCurSet);

//DQ轴电流指令初始化函数 ------ 不带弱磁控制
extern void InitDQCurRefGen(u8 t_bObjId, s16 dCurSet,s16 qCurSet, s16 TransTime);

//DQ轴电流指令初始化函数 ------ 带弱磁控制
extern void InitDQCurRefGenWithWeakenFlux(u8 t_bObjId, s16 dCurSet, s16 qCurSet,s16 TransTime);

//D轴电流指令处理函数   ------ 不带弱磁控制
extern s16 getDCurRefGen(u8 t_bObjId);

//D轴电流指令处理函数   ------ 带增强弱磁控制,根据母线实际值进行弱磁处理
extern s16 getDCurRefGenWithEnWeakenFlux(u8 t_bObjId);

//设定D轴电流指令初始值 
extern void SetDCurRefInitValue(u8 t_bObjId, s16 dCurref);

//Q轴电流指令处理函数
extern void QCurRefGenValue(u8 t_bObjId, s64 *pValue,u8 QFormat,s32 spdSet);

//设置弱磁控制PI参数
extern void setFieldWeakenPara(u8 t_bObjId, u16 Kp, u16 Ki);

//设置PLL控制PI参数
extern void setObserPLLKpKi(u8 t_bObjId,u16 Kp, u16 Ki);

//是否使能顺逆风观测功能
extern void setTrakingMode(u8 t_bObjId, bool bEnable);
extern	void	setTrakingModeEnable(u8 t_bObjId);
extern	void	setTrakingModeDisable(u8 t_bObjId);


//查看是否进入速度闭环状态
extern bool getRunStatus(u8 t_bObjId);

//查看是否进入电流闭环状态
extern bool getCurLoopCloseStatusFromOB(u8 t_bObjId);

//DQ电压补偿系数计算
extern void CalcVectorVFPara(u8 t_bObjId);

//DQ电压补偿功能
extern void vectorVFcontrol(u8 t_bObjId,s16 *pUd, s16 *pUq);

//死区电压补偿系数  1-----32767
extern void setDeadCompFactor(u8 t_bObjId, s16 factor);

//速度PI参数自动计算
// t_bObjId ---- 对象 ID
// KpFactor ---- 设置的速度PI扩大或缩小系数， 1000 ------- 1.0倍
// Ton		---- 速度滤波时间 0.1ms
// s32 *pKp	---- 回写Kp地址  Q9格式
// s32 *pKi	---- 回写Ki地址  Q14格式    根据需要转换为合适的Q格式

extern void SpeedPIAutoTunning(u8 t_bObjId,s16 KpFactor, s16 Ton, s32 *pKp, s32 *pKi);

//电流PI参数自动计算
// t_bObjId		---- 对象 ID
// s32 *pKpd	---- 回写Kp地址  Q12格式
// s32 *pKid	---- 回写Ki地址  Q16格式    根据需要转换为合适的Q格式
extern void CurPIAutoTunning(u8 t_bObjId,s32 *pKpd, s32 *pKid,s32 *pKpq, s32 *pKiq);


//设置观测器PI参数
// t_bObjId		---- 对象 ID
// s32 Kpd		---- Kp			Q12格式
// s32 Kid		---- Ki			Q16格式
extern void SetCurPIPara(u8 t_bObjId,s32 Kpd, s32 Kid,s32 Kpq, s32 Kiq);


//观测器等是否工作选择
// TRUE  ------ 工作
extern void setLibWorkMode(u8 t_bObjId, bool bwork);
//观测器1ms任务
extern void PmsmFluxObserve1ms(u8 t_bObjId);

//反电势检测初始化
//	nCompAngle   	----- 补偿角度，1度
//  nBemfTrackVolt	----- 最小检测电压，0.01V
extern void Bemf_CheckInit(u8 objId , u16 nCompAngle, u16 nBemfTrackVolt);

//反电势检测
extern void Bemf_CheckProcess(u8 objId, s16 phaseC, s16 phaseB, s16 phaseA);
//  phaseC   ------  AD原始值

//反电势切换到正常运行, isWeakenUsed  TRUE ---- 弱磁观测器
extern void BemfSwitch(u8 objId, bool isWeakenUsed);

//初始化观测器角度
extern void setOBElectAngleEst(u8 t_bObjId, u32 theta);

//设置过调制电压系数
// 最大为		21845
// 内切圆时为	18918
extern void setOverModuFac(u8 t_bObjId, s16 factor);

//设置弱磁控制电压利用率
// 100%  -------  4096
// 默认95%，即预留5%电压
extern void setFieldWeakenVoltFac(u8 t_bObjId, s16 factor);

extern s32 getVolt2FreqCalcPara(u8 t_bObjId);		// 电机电压到频率计算系数 Q12
													// 根据反电势系数计算当前电压下大概对应频率值

extern	s16 IQ15SqrtIQ31(s32 x);					// 平方根函数，可重入

extern	s16 getElectSpdEst(u8 t_bObjId);
extern	s16 getPhaseCur_U(u8 t_bObjId);
extern	s16 getPhaseCur_V(u8 t_bObjId);
extern	s16		getMotorDaxisVoltFormObjId(u8 t_bObjId);
extern	s16		getMotorQaxisVoltFormObjId(u8 t_bObjId);

///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////new mc define/ end//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
