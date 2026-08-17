#ifndef _PUBDATA_MD_MA_H_
#define _PUBDATA_MD_MA_H_

#include "basic.h"
#include "MC_type.h"

typedef enum
{
    E_PWM_RESET = 0,E_PWM_ON,E_PWM_OFF
} ENUM_PWMStatus;				//	PWM命令及状态(MOE)


typedef enum
{
	E_FC_NON = 0x00,										//	无操作
	E_FC_RESET_INIT_ACR = (E_MOTOR_RESET<<8)+0x01,			//	RESET状态 初始化电流环
	E_FC_RESET_INIT_OBS = (E_MOTOR_RESET<<8)+0x0002,		//	RESET状态 初始化观测器
	E_FC_RESET_INIT_SVPWM = (E_MOTOR_RESET<<8)+0x03,		//	RESET状态 初始化SVPWM
	E_FC_RESET_INIT_IPD = (E_MOTOR_RESET<<8)+0x04,			//	RESET状态 初始化IPD
	E_FC_RESET_CHARGE_A = (E_MOTOR_RESET<<8)+0x05,			//	RESET状态 A相预充电
	E_FC_RESET_CHARGE_B = (E_MOTOR_RESET<<8)+0x06,			//	RESET状态 B相预充电
	E_FC_RESET_CHARGE_C = (E_MOTOR_RESET<<8)+0x07,			//	RESET状态 C相预充电
	E_FC_RESET_CHARGE_DONE_INIT = (E_MOTOR_RESET<<8)+0x08,	//	RESET状态 预充电结束
	E_FC_RESET_CLR_BREAKIN_FAULT = (E_MOTOR_RESET<<8)+0x09,	//	RESET状态 清除Breakin
	

	E_FC_TRACKING_FWD = (E_MOTOR_TRACKING<<8)+0x01,			//	预留
	E_FC_TRACKING_REV = (E_MOTOR_TRACKING<<8)+0x02,			//	预留
	E_FC_TRACKING_FWS = (E_MOTOR_TRACKING<<8)+0x03,			//	预留
	E_FC_TRACKING_UPS = (E_MOTOR_TRACKING<<8)+0x04,			//	预留
	E_FC_TRACKING_WAIT = (E_MOTOR_TRACKING<<8)+0x05,		//	预留

	E_FC_IPD_CW_START = (E_MOTOR_IPD<<8)+0x01,				//	IPD CW
	E_FC_IPD_CCW_START = (E_MOTOR_IPD<<8)+0x02,				//	IPD CCW
	E_FC_IPD_DOING = (E_MOTOR_IPD<<8)+0x03,					//	IPD 检测中
	E_FC_IPD_DONE  = (E_MOTOR_IPD<<8)+0x04,					//	IPD 结束
	  
	E_FC_ALIGN_SetUp = (E_MOTOR_ALIGN<<8)+0x01,				//	预留
	E_FC_ALIGN_WAIT = (E_MOTOR_ALIGN<<8)+0x02,				//	预留
	
	E_FC_BRAKE_SetUp = (E_MOTOR_BRAKE<<8)+0x01,				//	预留
	E_FC_BRAKE_WAIT = (E_MOTOR_BRAKE<<8)+0x02,				//	预留
} ENUM_FineCmd;					//	MA操作命令，MD回复命令



typedef struct {	
	int32_t wRs;
	int32_t wLd;
	int32_t wLq;
	int32_t wFlux;
	int16_t nPllKp;
	int16_t nPllKi;
	int16_t nFilterCoeff;
}STR_MotorObsParOnLine;			//	观测器实时设置参数	预留


typedef struct {	
	int16_t					gWrFlag;				//互斥变量
	ENUM_MotorStatus		eMotorStatus;			//MD层状态指令
	STR_VectorDQ			mStatCurDQCmd;			//DQ电流指令
	int32_t					wMotorSpeedRef;			//速度指令值
	
	ENUM_PWMStatus			ePwmCmd;				//PWM操作命令 ON---MOE使能
	int16_t					nMoeActionBlankTime;	//消隐时间5ms..	
	STR_MotorObsParOnLine 	mMotorParRT;	
	uint8_t					bIpdStart;				//IPD使能
	int16_t					nMotorBrakePwmDuty;		//制动宽度 q12
	ENUM_FineCmd			nuFineCmd;				//0:none
													//E_MOTOR_RESET: 0x01: init Acr   0x02: init obs   0x03:init svpwm  0x04:init ipd ...
													//E_MOTOR_TRACKING E_MOTOR_ALIGN,E_MOTOR_ASYN,E_MOTOR_PRE_SYN,E_MOTOR_SYN:
													//0xF0:    0xF1:       ...
													//E_MOTOR_BRAKE,E_MOTOR_IPD
													//0x0100:Duty brake    0x0101:short brake       ...
}STR_PubDatMAMD, *PSTR_PubDatMAMD;			//	MA命令数据结构(发送给 MD)


typedef struct {	
	int16_t					gWrFlag;				//互斥标志
	ENUM_PWMStatus			ePwmStatus;				//moe状态
	bool					bBreakInFault;			//BreakIn标志 
	
	int32_t					wFreq;					//反馈频率值澹(复用为反电势检测的频率值)
	int16_t					nVdc;					//母线电压
	STR_VectorDQ			mStatCurDQ;				//DQ电流值
	STR_VectorDQ			mStatVolDQ;				//DQ电压值
	STR_VectorUVW			mStatCurrUVW;			//定子电流UVW
	int16_t					nMotorCur;				//电机相电流有效值
	int16_t					nMotorVol;				//电机电压(复用为反电势检测的峰值)，正常为SQRT(Ud^2+Uq^2)
	int16_t					nPowerDec;				//估算功率
	int16_t					nTemp;					//温度

	ENUM_MotorStatus		eMotorStatusAck;		//MD层状态
	
	ENUM_FineCmd			nuFineStatus;			//0:none 													
}STR_PubDatMDMA;								//	MD状态数据结构(返回给 MA)

typedef struct
{   /* 顺风逆风启动，转子速度位置方向检测 */
    s32 wFreqAvg;				/* 转子电频率平均值 */
	s16 nMotorVolMagAvg;		/* 当前反电势滤波后电压平均值 */
    s16 nMotorStopCurrentThd;	/* 电机停转电流检测阈值 */
    s16 nMotorStopCurDifThd;	/* 电机停转电流差值检测阈值 */
	u8  bMotorStopDecFlag;		/* 电机停转标志 */
	s32 s32MotorCurrentMagfilt;
	s32 s32MotorCurrentMagfilt1;
	s32 s32MotorCurrentMagDifAvg;	
} STR_OnTheFlyDetectMA,*pSTR_OnTheFlyDetectMA;	//	MA顺逆风检测结构体

typedef enum
{
	E_SLVC_RUN_NORMAL = 0,
	E_SLVC_RUN_2_STOP,
	E_SLVC_RUN_2_CHARGE
}ENUM_Run_Status;

typedef struct
{
	ENUM_Run_Status 	eRunStatus;				//运行状态
	s16 				brakeCurrent;			//制动电流
	
	s16 				chargeStartVoltage;		//充电起始电压
	s16 				chargeFinishVoltage;	//充电终止电压
	s16 				ChargeRestoreVoltage;	//充电恢复电压

	s16 				nBusVoltage;			//当前母线电压
	s32 				*pwSpeedRef;			//速度给定值
	s32 				*pwSpeedfbk;			//速度反馈值
	
}STR_MotorExceptionMA,*pSTR_MotorExceptionMA;		//	电压异常处理结构体


// handle function from MA 2 MD : MA write function
static __inline void	SetPWMCmdMA2MD(STR_PubDatMAMD *pMA2MD, ENUM_PWMStatus cmd)	//	MA设置MD层PWM操作
{
	pMA2MD->ePwmCmd	= cmd;
}

static __inline void	SetMotorCmdMA2MD(STR_PubDatMAMD *pMA2MD, ENUM_MotorStatus cmd)	//	MA设置MD层电机状态
{
	pMA2MD->eMotorStatus	= cmd;
}
static __inline void	SetIPDStartCmdMA2MD(STR_PubDatMAMD *pMA2MD, bool start)			//	MA设置MD层IPD操作
{
	pMA2MD->bIpdStart	= start;
}


static __inline void	SetBrakePWMDutyMA2MD(STR_PubDatMAMD *pMA2MD, int16_t duty)		//	MA设置MD层制动宽度
{
	pMA2MD->nMotorBrakePwmDuty	= duty;
}

static __inline void	SetSpeedRefMA2MD(STR_PubDatMAMD *pMA2MD, int32_t speedRef)		//	MA设置MD层速度指令值
{
	pMA2MD->wMotorSpeedRef	= speedRef;
}

static __inline void	SetCurRefMA2MD(STR_PubDatMAMD *pMA2MD, int16_t IdRef,int16_t IqRef)	//	MA设置MD层DQ电流指令值
{
	pMA2MD->mStatCurDQCmd.nAxisD	= IdRef;
	pMA2MD->mStatCurDQCmd.nAxisQ	= IqRef;
}

static __inline void	SetMoeBlankTimeMA2MD(STR_PubDatMAMD *pMA2MD, int16_t blankTimeMs)	//	MA设置MD层指令消隐时间
{
	pMA2MD->nMoeActionBlankTime		= blankTimeMs;
}

static __inline void	SetIPDEnableMA2MD(STR_PubDatMAMD *pMA2MD, uint8_t start)			//	MA设置MD层IPD操作	
{
	pMA2MD->bIpdStart	= start;
}

static __inline void	setDefaultCmdMA2MD(STR_PubDatMAMD *pMA2MD)			//	MA设置MD层默认指令(无操作)
{
	pMA2MD->nuFineCmd	= E_FC_NON;
}


static __inline void	setObsevInitFCmdMA2MD(STR_PubDatMAMD *pMA2MD)		//	MA设置MD层观测器初始化指令
{
	pMA2MD->nuFineCmd	= E_FC_RESET_INIT_OBS;
}

static __inline void	setAcrInitFCmdMA2MD(STR_PubDatMAMD *pMA2MD)			//	MA设置MD层电流环初始化指令
{
	pMA2MD->nuFineCmd	= E_FC_RESET_INIT_ACR;
}

static __inline void	setSVPWMInitFCmdMA2MD(STR_PubDatMAMD *pMA2MD)		//	MA设置MD层SVPWM初始化指令
{
	pMA2MD->nuFineCmd	= E_FC_RESET_INIT_SVPWM;
}

static __inline void	setChargeAFCmdMA2MD(STR_PubDatMAMD *pMA2MD)			//	MA设置MD层A相预充电指令
{
	pMA2MD->nuFineCmd	= E_FC_RESET_CHARGE_A;
}
static __inline void	setChargeBFCmdMA2MD(STR_PubDatMAMD *pMA2MD)			//	MA设置MD层B相预充电指令
{
	pMA2MD->nuFineCmd	= E_FC_RESET_CHARGE_B;
}
static __inline void	setChargeCFCmdMA2MD(STR_PubDatMAMD *pMA2MD)			//	MA设置MD层C相预充电指令
{
	pMA2MD->nuFineCmd	= E_FC_RESET_CHARGE_C;
}

static __inline void	setChargeDoneInitFCmdMA2MD(STR_PubDatMAMD *pMA2MD)	//	MA设置MD层预充电完成指令
{
	pMA2MD->nuFineCmd	= E_FC_RESET_CHARGE_DONE_INIT;
}

static __inline void	setClrBreakInFaultFCmdMA2MD(STR_PubDatMAMD *pMA2MD)	//	MA设置MD层清除BreakIn指令
{
	pMA2MD->nuFineCmd	= E_FC_RESET_CLR_BREAKIN_FAULT;
}

static __inline void	setIPDInitFCmdMA2MD(STR_PubDatMAMD *pMA2MD)			//	MA设置MD层IPD初始化指令
{
	pMA2MD->nuFineCmd	= E_FC_RESET_INIT_IPD;
}

static __inline void	setIPDCWStartFCmdMA2MD(STR_PubDatMAMD *pMA2MD)		//	MA设置MD层IPD初始化CW指令
{
	pMA2MD->nuFineCmd	= E_FC_IPD_CW_START;
}

static __inline void	setIPDCCWStartFCmdMA2MD(STR_PubDatMAMD *pMA2MD)		//	MA设置MD层IPD初始化CCW指令
{
	pMA2MD->nuFineCmd	= E_FC_IPD_CCW_START;
}











// handle function from MD 2 MA :  MA read function
static __inline ENUM_PWMStatus	getPWMStatMD2MA(STR_PubDatMDMA *pMD2MA)			//	MA读取MD层PWM状态
{
	return pMD2MA->ePwmStatus;
}

static __inline ENUM_MotorStatus getMotorAckStatMD2MA(STR_PubDatMDMA *pMD2MA)	//	MA读取MD层电机状态
{
	return pMD2MA->eMotorStatusAck;
}

static __inline bool getObsevInitResultMD2MA(STR_PubDatMDMA *pMD2MA)			//	MA读取MD层观测器初始化结果
{
	return (pMD2MA->nuFineStatus == E_FC_RESET_INIT_OBS);
}

static __inline bool getAcrInitResultMD2MA(STR_PubDatMDMA *pMD2MA)				//	MA读取MD层电流环初始化结果
{
	return (pMD2MA->nuFineStatus == E_FC_RESET_INIT_ACR);
}

static __inline bool getSVPWMInitResultMD2MA(STR_PubDatMDMA *pMD2MA)			//	MA读取MD层SVPWM初始化结果
{
	return (pMD2MA->nuFineStatus == E_FC_RESET_INIT_SVPWM);
}

static __inline bool getNonInitResultMD2MA(STR_PubDatMDMA *pMD2MA)				//	MA读取MD层空闲状态
{
	return (pMD2MA->nuFineStatus == E_FC_NON);
}

static __inline bool getIPDDoneResultMD2MA(STR_PubDatMDMA *pMD2MA)				//	MA读取MD层IPD完成结果
{
	return (pMD2MA->nuFineStatus == E_FC_IPD_DONE);
}

static __inline bool getBreakInClrResultMD2MA(STR_PubDatMDMA *pMD2MA)			//	MA读取MD层清除清除BreakIn指令结果
{
	return (pMD2MA->nuFineStatus == E_FC_RESET_CLR_BREAKIN_FAULT);
}

static __inline bool getIPDInitResultMD2MA(STR_PubDatMDMA *pMD2MA)				//	MA读取MD层IPD初始化结果
{
	return (pMD2MA->nuFineStatus == E_FC_RESET_INIT_IPD);
}




#endif // _PUBDATA_MD_MA_H_
/////////////////////
