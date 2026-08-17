///*******************************************************************************
// * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
// *
// * 文件名称： MA_Static_Variable.h
// * 文件标识：
// * 内容摘要： 全局变量声明文件
// * 其它说明： 无
// * 当前版本： V 1.0
// * 作    者： Tonghua Li
// * 完成日期： 2022年8月19日
// *
// *******************************************************************************/

#ifndef __MA_STATIC_VARIABLE__
#define __MA_STATIC_VARIABLE__

#include "basic.h"
#include "MC_Math.h"

#include "fault_detection.h"
#include "state_machine.h"

#include "PowerCalculation.h" 
#include "PubData_MA_UA.h" 
#include "PubData_MD_MA.h" 
#include "PubData_DriverInstance.h" 
#include "PID_regulators.h" 


// 定义支持的MA控制对象最大个数，与平台驱动单元个数对应
#define MA_OBJ_MAX_DEFINE	(PLANTFORM_DRV_MODULE_NUM)

typedef struct 
{
    s32 wSvcMinFreq;                //开环拖动频率

    u8  bChargeFlag;                //预充电标志位
    u8  bChargeEndFlag;             //预充电完成标志位
	s16 nChargePwmWidth;            //预充电脉宽

    s32 wDirTrackFreq;              //电机切入闭环频率
    s32 wDirEbreakFreq;             //电机刹车频率
    s16 nDCurFilFactor;             //电流加速调整值
    s16 nQCurFilFactor;             //电流减速调整值
    s32 wSpeedRef;                  //速度给定值
    
    s16 nLoopCntr;                  //环路计数
    s16 nLoopPeriod;                //环路周期
    u8  bLoopLmtEnable;				//环路输出限制使能

    u8  bOpenRunFlag;               //开环运行标志位
    s32 wThetaErr;                  //估算和给定角度误差
    s16 nMatchCnt;                  //估算角度匹配计数

    s16 nPowerFistFlag;             //第一次进入功率环标志位

    s16 nTempADC;                   //NTC采样AD值
    
    u16 nMotorRunDirPre;            //上次电机转向
}STR_CommData,*PSTR_CommData;


typedef struct
{
    s16 nChargeTime;			//充电时间，以1ms为单位
    s16 nChargePeriod;			//每相充电设定时间，以1ms为单位
    
    s16 nAlignTime;        		//定位时间，以1ms为单位
    s16 nAlignLowPeriod;        //定位低电流设定时间，以1ms为单位
    s16 nAlignAllPeriod;        //定位总设定时间，以1ms为单位
    
    s16 nDirCheckTime;     		//顺逆风时间，以1ms为单位
    s16 nDirCheckPeriod;		//顺逆风检测设定时间，以1ms为单位 
    
    s16 nLoopDelyTime;			//速度环延迟时间，以1ms为单位
    s16 nLoopDelyPeriod;		//速度环延迟设定时间，以1ms为单位
    
    s16 nStopDelayTime;			//电机停止延迟时间，以1ms为单位
    s16 nStopDelayTimePeriod;	//电机停止延迟设定时间，以1ms为单位
    
    s16 nStopDelayCntr;    		//电机停止滤波时间，即连续判断电机停止的时间，以1ms为单位
    s16 nStopDelayPeriod;		//电机停止滤波设定时间，即连续判断电机停止的时间，以1ms为单位
    
    s16 nOpenRunCntr;			//开环切闭环时间，以1ms为单位
    s16 nOpenRunPeriod;			//开环切闭环设定时间，以1ms为单位
    
}STR_Time_t, *PSTR_Time_t;


typedef struct {
	s32 wSpeedSet;						/* 速度设定 		core数据格式 */
	s32 wSpeedRef;						/* 速度给定值 		core数据格式 */
	
	s32 wSpeedfbk;						/* 速度反馈值 		core数据格式 */	
	s32 wSpeedfbkFilter;				/* 速度反馈值滤波	core数据格式 */
	
	s32 wSpeedEst;						/* 观测器角速度输出 core数据格式 */
	u16 nSpeedFiltTime;					/* 速度滤波时间系数	*/
	
	STR_RampGen32	STR_SpdRampGen;		// 速度指令斜坡规划数据结构

	#if (DRV0_CLOSE_LOOP == SPEED_LOOP)
	stru_SpeedPIRegulator mSpeedPI;		/* 速度环 PI */
	#endif

	s32 wSpeedRampACCStep;				/*速度爬坡加速值 Q16 core数据格式 */
	s32 wSpeedRampDECStep;				/*速度爬坡减速值 Q16 core数据格式 */

	s32 wPowerLimitSpeedChangeSet;		/*限功率转速变化值*/
	s32 wPowerLimitSpeedChangeSetInc;	/*限功率转速变化值增量 Q16*/
	s32 wPowerLimitValue;				/*限功率大小*/
	s16 nPowerLimitCntr;				/*限功率计算计数*/
	s16 nPowerLimitPeriod;				/*限功率计算周期*/
} STR_MechQuantity, *PSTR_MechQuantity;

typedef struct
{
    s32 nCurrentAccStep;   /* 电流增加步长 */
    s32 nCurrentDecStep;   /* 电流减小步长 */   
    s32 nStartCurSet;      /* 启动电流设定 */
    s32 nStartCurRef;      /* 启动电流参考 */   
    s32 wStartCurRamp;     /* 电流爬坡值 */
  
    s32 wOpen2CloseFreq;   /* 开环切闭环频率 */
    s16 nFreqAccStep;      /* 频率加速步长 */
    s16 nFreqDecStep;      /* 频率减速步长 */
    s32 wRampFreqRef;      /* 频率爬坡值 */
} STR_OpenForceRun, *pSTR_OpenForceRun; /* 角度开环强拖结构体 */

typedef struct
{
	u16 m_bMC_RunFlg		:1;					/* 电机启动指令 */
	u16 m_bMotorDirtion		:1;					/* 期望控制的电机运行方向 */
	u16 m_bEnableMOEInStop	:1;					/* 电机停止后MOE是否输出*/
	u16 m_bCalibFinish		:1;					/* 充电完成*/
	
	u16 m_bNeedTracking		:1;					/* 是否需要tracking*/
	u16 m_bTrackingFinish	:1;					/* tracking结束*/
	u16 m_bNeedIPD			:1;					/* 是否需要IPD*/
	u16 m_bIPDFinish		:1;					/* IPD完成标志*/

	u16 m_bNeedAlign		:1;					/* 是否需要对相*/
	u16 m_bAlignFinish		:1;					/* 对相完成标志*/	
	u16 m_bMotorStopped		:1;					/* 电机停止完成标志*/
	u16 m_bPostOK			:1;					/* 电机POST完成标志*/

	u16 m_bUAFault			:1; 				/* UA故障命令*/
	u16 m_bUAFaultClr		:1; 				/* UA故障命令清除*/
	u16 m_bUAReverse		:1; 				/* UA命令取反*/
	u16 m_bUAMOE			:1;					/* UA MOE是否使能*/

	u16 m_bObParaInitDone	:1; 				/* 参数初始化完成标志*/
	u16 m_bAcrInitDone		:1; 				/* FOC 参数初始化完成标志*/
	u16 m_bSVPWMInitDone	:1; 				/* SVPWM 参数初始化完成标志*/
	u16 m_bFaultInitDone	:1;					/* 预留*/

	u16 m_bObParaUpdate		:1;					/* 参数更新完成标志*/
	u16 m_bObParaReq		:1;					/* 参数更新请求标志*/
	u16 m_bAcrParaUpdate	:1;					/* 参数更新完成标志*/
	u16 m_bAcrParaReq		:1;					/* 参数更新请求标志*/

	u16 m_bSVPWMParaUpdate	:1;					/* 参数更新完成标志*/
	u16 m_bSVPWMParaReq		:1;					/* 参数更新请求标志*/

	u16 m_bFaultInitReq		:1;					/* FAULT检测需要初始化*/

	u16 m_bBreakInFault		:1;					/* BreakIn Fault 存在标志*/
	
	u16 m_bBreakInClrReq	:1;					/* BreakIn Clr 请求标志*/

	u16 m_bIPDInitReq		:1;					/* IPD Init 	请求标志*/
	u16 m_bIPDInitDone		:1;					/* IPD Done 	请求标志*/
	
	u16 m_bExceptionEnable	:1;					/* 异常处理 使能*/
	
}STR_MACtrBit,*pSTR_MACtrBit;		/* 控制标志位结构体 */



typedef struct
{
	/*---------------------------------------------------------------------------------------------*/
	// 绑定的控制对象
	u8						mg_nMACtrlProcID;			/* 控制对象 ID		*/
	PSTR_ControlObject		mg_pCtrlObj;				/* 控制对象			*/
	
	/*---------------------------------------------------------------------------------------------*/
	// FAULT 检测交换信息
	STR_FaultStatus			mg_UFault;					/* 故障标志 		*/
	ENUM_MotorBrakeMode		mg_eFaultStopMode;			/* 故障时停止模式 	*/
	ENU_FaultPrio			mg_eFaultPrio;				/* 故障级别			*/

	/*---------------------------------------------------------------------------------------------*/
	// 内部交换信息存储及刷新缓冲区,节省RAM时可以直接采用mg_pCtrlObj绑定的数据交换区
	STR_PubDatMDMA 			mMdToMa;					/* MD到MA 状态及信息 本地变量区	*/
	STR_PubDatMAMD 			mMaToMd;					/* MA到MD 状态及信息 本地变量区	*/
	
	STR_PubDatUAMA 			mUaToMa;					/* UA到MA 状态及信息 本地变量区	*/
	STR_PubDatMAUA			mMaToUa;					/* MA到UA 状态及信息 本地变量区	*/
	
	/*---------------------------------------------------------------------------------------------*/
	// 内部控制变量	(私有)
    volatile u16			m_nSys_TimerMA;				/* MA周期计数Cnt */
	
	STR_MACtrBit			m_SMACtrlBit;				/* 控制命令及当前状态寄存器，控制命令由UA和FAULT模块等影响*/	
	ENUM_MotorBrakeMode		m_eStopMode;				// 电机停止模式
	u8						m_nLoopMode;				/* 环路状态，速度、功率、电流环选择，ON后不能更改 */
	
    ENU_DRIVER_STATUS		m_eSysState;				/* 当前电机运行状态机 */
	ENU_DRIVER_STATUS		m_eNextSysState;			/* 下次电机运行状态机 */
	
    u16						m_nSetTimeLeftCnt;			/* 状态机等待时间计数器 */
	u16						m_nSetTimeLeftPrd;			/* 状态机等待时间周期 */

	s16						m_nInvTemp;					// 功率模块温度，根据需要选用
	
	s16						m_nBreakDuty;				// 制动PWM宽度

	s32						m_wPower001W;				// 功率实时值，0.01W,取自MD层估算数据，1个速度环刷新
	s64						m_wPower001WFil;			// 功率滤波值，0.01W,取自MD层估算数据后滤波，1个速度环刷新
	s16 					m_nPower001WFactor;			// 功率滤波系数，滤波时间10个速度环周期
	

	// motor info 变量及配置参数
	ENU_MOTOR_INFO_STATE	m_eMotorInfoState;			/* 电机信息检测 MOTOR INFO 状态*/
	ENU_TRAKING_RESULT		m_eTrackingResult;			/* 顺逆风检测 tracking结果*/

	
	/*---------------------------------------------------------------------------------------------*/
	// 各功能块数据空间 (私有)
	PSTR_CommData			m_pAppCommData;				/* 运行流程控制结构体 */
	PSTR_MechQuantity		m_pMotorSpeed;				/* 转速矢量结构体，core */
	
	pSTR_OnTheFlyDetectMA	m_pOnTheFlyDetect;			/* 顺逆风启动结构体 */

	#if (DRV0_UNDVOLT_PROT_ENABLE == 1)
	pSTR_MotorExceptionMA	m_pMotorException;			/* 顺逆风启动结构体 */
	#endif
	
    PSTR_Time_t            	m_pTime;					/*定位时间等 时间计时*/
	
	PSTR_RampGen32			m_pSTR_CurRampGen;			/*电流斜坡规划结构体*/

	#if ((DRV0_CLOSE_LOOP == POWER_LOOP) || ((DRV0_POWER_LIMIT_STATUS == TRUE) && (DRV0_CLOSE_LOOP == SPEED_LOOP)))
	pSTR_PowerDef			m_pPower;					//  功率计算结构体
	#endif
	
	/*---------------------------------------------------------------------------------------------*/
	// Fault 数据空间 (私有)
	STR_FaultStatus			*m_pFaults;					// 报警标志指针
	
	STR_FaultVariable		*m_pFaultValue;				// 报警变量结构体指针
	s16						t_nFlagCheck;				// 报警检测周期变量
	STR_CurrentAmplitude	*m_pstruCurrentAmplitude;	// 电流幅值结构体指针
	STR_VectorUVW			*m_pstruImaxCurrent;		// 电流最大值结构体指针
	
	STR_FaultTime			*m_pstruFaultVoltTime;		// 电压检测时间结构体指针
	STR_FaultTime			*m_pstruFaultEmptyTime;		// 空转检测时间结构体指针
	STR_FaultTime			*m_pstruFaultStallTime;		// 堵转检测时间结构体指针
	STR_FaultTime			*m_pstruFaultCurrentTime;	// 电流检测时间结构体指针
	STR_FaultTime			*m_pstruFaultTempTime;		// 温度检测时间结构体指针
	STR_FaultTime			*m_pstruFaultPhaseTime;		// 缺相检测时间结构体指针
	STR_FaultTime			*m_pstruFaultStartTime;		// 启动检测时间结构体指针

	/*---------------------------------------------------------------------------------------------*/
	s16						m_nQCur_Reference;			/* Q轴电流环参考给定 */
	s16						m_nDCur_Reference;			/* D轴电流环参考给定 */
	s16						m_nQCurrentSet;				/* Q轴电流设定值 */
	s16						m_nDCurrentSet;				/* D轴电流设定值 */	
	s32						m_wDCurFilter;				/* D轴电流滤波中间值 */	
	s32						m_wQCurFilter;				/* Q轴电流滤波中间值 */	
	
}STR_MACtrProc, *PSTR_MACtrProc;	/* MA数据结构体 */


typedef  struct
{
	STR_Time_t         		m_struTime;
	STR_CommData			m_struAppCommData;			/* 运行流程控制结构体 */
	STR_MechQuantity		m_struMotorSpeed;			/* 转速矢量结构体，core */
	//stru_PIRegulator		m_SpeedPI;					/* 速度环 */

	#if ((DRV0_CLOSE_LOOP == POWER_LOOP) || ((DRV0_POWER_LIMIT_STATUS == TRUE) && (DRV0_CLOSE_LOOP == SPEED_LOOP)))	
	STR_PowerDef			m_struPower;				/* 输入功率计算 */
	#endif

	STR_OnTheFlyDetectMA	m_OnTheFlyDetect;			//	顺逆风检测结构体

	#if(DRV0_UNDVOLT_PROT_ENABLE == 1)
	STR_MotorExceptionMA	m_MotorException;
	#endif

	STR_RampGen32			m_STR_CurRampGen;			//	ALLIGN对相电流指令斜坡规划结构体

	//
	STR_CurrentAmplitude	m_struCurrentAmplitude;		// 电流幅值结构体
	STR_VectorUVW			m_struImaxCurrent;			// 最大电流检测结构体
	STR_FaultVariable 		m_stru_FaultValue;			// 报警变量结构体
	STR_FaultStatus			m_stru_Faults;				// 报警标志结构体

	STR_FaultTime			m_struFaultVoltTime;		// 电压检测时间结构体
	STR_FaultTime 			m_struFaultEmptyTime;		// 空转检测时间结构体
	STR_FaultTime 			m_struFaultStallTime;		// 堵转检测时间结构体
	STR_FaultTime 			m_struFaultCurrentTime;		// 电流检测时间结构体
	STR_FaultTime 			m_struFaultTempTime;		// 温度检测时间结构体
	STR_FaultTime 			m_struFaultPhaseTime;		// 缺相检测时间结构体
	STR_FaultTime 			m_struFaultStartTime;		// 启动检测时间结构体
}STR_MASubBlock;

#endif
///* ********************** (C) COPYRIGHT LINKO SEMICONDUCTOR ******************** */
///* ------------------------------END OF FILE------------------------------------ */
