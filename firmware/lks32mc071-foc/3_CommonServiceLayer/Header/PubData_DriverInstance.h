#ifndef _PubData_DriverInstance_H_
#define _PubData_DriverInstance_H_

#include "basic.h"
#include "project_config.h"
#include "PubData_HD_MD.h"
#include "PubData_MD_MA.h"
#include "PubData_MA_UA.h"
#include "MC_configure_FB_data.h"
#include "MC_Parameter_M0.h"


										// 常量FB配置参数结构体组数
#define MAX_CFG_PARA_ID					(PLANTFORM_MAX_CFG_PARA_ID)

										// 支持的PWM通道数据，即可支持驱动单元数目
#define MAX_DRV_MODULE_USED				(PLANTFORM_DRV_MODULE_NUM)


//define PWM_MODULE_DYNAMIC_CONFIG

typedef struct {
    u16 nuCur;
    s16 nCurShftNum;
    u16 nuVol;
    s16 nVolShftNum;
    u16 nuFreq;
    s16 nFreqShftNum;
    u16 nuSpeed;
    s16 nSpeedShftNum;
    u32 nuPower;
    s16 nPowerShftNum;
    u16 nuTorque;
    s16 nTorqueShftNum;
    u16 nuAngle;
    s16 nAngleShftNum;
    u16 nuVdc;
    s16 nVdcShftNum;
} STR_TransCoefElement,*PSTR_TransCoefElement;


typedef struct {
		STR_TransCoefElement mUserToApp;		//USR2APP 标幺转换
		STR_TransCoefElement mUserToCore;		//USR2CORE 标幺转换
		STR_TransCoefElement mCoreToApp;		//CORE2APP 标幺转换
		STR_TransCoefElement mAppToCore;		//APP2CORE 标幺转换
} STR_TransCoef,*PSTR_TransCoef;


//////////////////////////////////////////////////////////////////////
////////////////******Motor Drive Layer para define*****//////////////
//////////////////////////////////////////////////////////////////////
typedef struct {
		s8  bMotorType;           /* 0:im,1:spm,2:ipm,3...*/
		s8  bPolePairs;           /* 电机磁极对数 */
		s16 nRatedCur;            /* 额定电流 单位：0.1A */
		s32 wRatedFreq;           /* 额定频率 单位：0.01Hz*/
		s32 wMotorRs;             /* 电机内阻 单位：0.0001欧姆 */
		s32 wMotorLd;             /* 电机D轴电感 单位：uH */
		s32 wMotorLq;             /* 电机Q轴电感 单位：uH */
		s32 wFluxConst;           /* 电机磁链常数 0.00001WB */
		/////////////////////////////////////////////////////////////////////////////////////////////////
		s16 nRatedUdc;            /* 额定电压 单位：0.1V */
		u16 nPWMFreq;             /* PWM载频,hz */
		//HD  硬件驱动层
		s32 wAdcSupplyVol;			/* ADC参考电压 单位：0.000001伏特  max */
		s32 wRShunt;				/* 分压电阻 单位：0.001毫欧姆*/
		s32 wAmpGain;				/* 放大器放大倍数 单位：0.000001倍 */ 
		s32 wVolShuntRatio;			/* 母线电压采样分压比 0.000001倍*/ 
		s32 wBemfShuntRatio;		/* 反电势电压采样分压比 0.000001倍*/
} STR_FocObjPar,*PSTR_FocObjPar;

typedef struct {
		u16 nuMinPwmSampTime3Shunt;    	/* 下桥电阻采样时,三相中最大占空比相,满足ADC可靠采样的最小的PWM值 */
		u16 nuSampStableTime3Shunt;     /* 下桥电阻采样时,需要保证ADC有正确采样窗口，判断两相PWM占空之间的差值是否满足采样条件 */
		s16 nShiftSampTime3Shunt;      	/* 三电阻采样移位时间 */
		s16 nSampWaitTime3Shunt;       	/* 三电阻采样等待时间 */
		s16 nSampStableTime1Shunt;     	/* 单电阻采样，信号上升沿时间 */
		u16 nuShiftSampTime1Shunt;      /* 单电阻采样移相时间 */
		u16 nuPwmPrd;              		/* PWM周期值 */
		u16 nDeadTime;            		/* 死区值 */
		u8 bSampType;					/* shunt type */
		u8 bSVPWM_Type;					/* svpwm type 0 ---- 7Seg, 1----- 5 Seg*/
} STR_FocSvpwmPar,*PSTR_FocSvpwmPar;

typedef struct {
		u16		nCurrLoopIniKP;        /* 电流环KP初始值, 程序会根据电机电感电阻修正此参数 */
		u16		nCurrLoopIniKI;        /* 电流环KI初始值, 程序会根据电机电感电阻修正此参数 */
		s16		nVqMax;					//Q轴电压最大值	1
		s16		nVqMin;					//Q轴电压最小 1
		s16		nVdMax;					//d轴电压最大值	1
		s16		nVdMin;					//d轴电压最小 1
		s16		nWeakenCurMax;			//最大弱磁电流	1

		u16		nuObsMode;//obs slvc1 or slvc2，or vf,,or vf+Slvc
		s32		wCloseFreq;				//开环拖动最终频率	0.01hz
		u32		wMinRunFreq;			/* 最小运行频率		0.01hz	*/
		u32		wCurrentClosedFreq;     /* 电流闭环频率		0.01hz	预留*/
		u16		nThetaFilTime;      	/* 角度滤波系数		Q10*/
		
		s16		nPLLKp0;				//PLL_Kp 估算器Kp0				1
		s16		nPLLKi0;				//PLL_Kp 估算器Ki0				1
		s16	  	nPLLFreq0;				//PLL频率点		0.1hz			1
		s16		nPLLKp1;				//PLL_Kp 估算器Kp1				1
		s16		nPLLKi1;				//PLL_Kp 估算器Ki1				1
		s16	 	nPLLFreq1;				//PLL频率点1	0.1hz			1

		s16 	nVFStartValue;			//VF启动电压值		0.01V  			可删除
		s16 	nVfVolRamp;				//电压ramp值 		0.01V/s			可删除
		s16 	nVF2CloseDelayTime;		//启动开环延时时间					可删除

		s32     wIPD_PlusWidthSet;		//IPD宽度
		s32     wIPD_IdleWaitSet;		//IPD空闲
		u16     nuIPD_Comp;				//IPD补偿角度
} STR_FocObsPar,*PSTR_FocObsPar;

typedef struct {	
	STR_FocObjPar		mObjPar;		//控制对象参数
	STR_FocSvpwmPar		mSvpwmPar;		//SVPWM参数
	STR_FocObsPar		mObsPar;		//观测器参数
}STR_MotorFocParDef,*PSTR_MotorFocParDef;


typedef struct {
  	STR_PubDatHDMD mHdToMd;
	STR_PubDatMDHD mMdToHd;
	STR_PubDatMDMA mMdToMa;
	STR_PubDatMAMD mMaToMd;
	STR_PubDatUAMA mUaToMa;
	STR_PubDatMAUA mMaToUa;
} STR_GlobalDatPackage,*PSTR_GlobalDatPackage;	//数据交换区

typedef struct {

	u8						m_bPWM_Id;			//实际的PWM物理端口号，0  ------ EPWM0

	/*********************************************************************************/
	// MA2MD FOC参数
	PSTR_MotorFocParDef		m_pMotorFocPar;

	/*********************************************************************************/
	// 添加参数配置结构体指针,配置参数与控制对象绑定，const数据类型
	PSTR_DrvCfgPara			m_pDrvCfgPara; 

	/*********************************************************************************/
	// Trans Coef for application, Used by all layer
	 STR_TransCoef			mTransCoef;
	/*********************************************************************************/

	/*********************************************************************************/
	// Definiation about global data structure  interface between MA and MD
	STR_GlobalDatPackage	mGlobalDatPackage;
	/*********************************************************************************/
 
}STR_ControlObject,*PSTR_ControlObject;


typedef struct
{
    u16 nTimeBaseFlg;        /* Timer 中断标记，取值 0或1 */
    u8  bPWM_UpdateFlg;      /* PWM周期更新标志，一次间隔为一个PWM周期 */
    u8  bTimeCnt1ms;         /* 1mS计数器 */
    u16 nTimeCnt10ms;        /* 10mS计数器 */
    u16 nTimeCnt500ms;       /* 500mS计数器 */
    const char* sVersion;    /* 程序版本号 */
} STR_TaskScheduler;

extern void InitMotorDriveLayer(void);
extern void BondingMotorDrvObject(void);
extern void InitMotorAppLayer(void);
extern void InitUsrAppLayer(void);
extern bool checkParaCfgValid(void);

#endif // _PubData_DriverInstance_H_
/////////////////////

