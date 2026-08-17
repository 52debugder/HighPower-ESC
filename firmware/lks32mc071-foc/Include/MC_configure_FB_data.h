/*******************************************************************************
 * 版权所有 (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： config_data.h
 * 文件标识：
 * 内容摘要： config data
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： Tonghua Li
 * 完成日期： 2022年6月28日
 *
 *******************************************************************************/
 
/*------------------------------prevent recursive inclusion -------------------*/ 
#ifndef __MC_CONFIG_FB_DATA_H
#define __MC_CONFIG_FB_DATA_H

#include "basic.h"
#include "MC_Type.h"

//////////////////////////////////////////////
//内部下载握手命令数据，不可修改
#define DOWNLOAD_WRITE_REQ1				(0x43)
#define DOWNLOAD_WRITE_REQ2				(0x54)
#define DOWNLOAD_WRITE_REQ3				(0x59)


#define DOWNLOAD_READ_ACK_INVLAD		(0x00)
#define DOWNLOAD_READ_ACK1				(0x44)
#define DOWNLOAD_READ_ACK2				(0x53)
#define DOWNLOAD_READ_ACK_DOING			(0x64)
#define DOWNLOAD_READ_ACKOK				(0x65)
//////////////////////////////////////////////

/*---------------------------------FB定义------------------------------------*/
// Function Block ID definition, 
// Don't modify FB ID, which is matched with PC configure tool.
// FB descriptor should be matched with PC configure tool
#define ID_FB_BOARD							(0)
#define ID_FB_MOTOR							(1)
#define ID_FB_SLVCCFG						(2)
#define ID_FB_CURLOOP						(3)
#define ID_FB_SPDLOOP						(4)
#define ID_FB_PWRLOOP						(5)
#define ID_FB_DIRCHECK						(6)
#define ID_FB_IPD							(7)
#define ID_FB_ALLIGN						(8)
#define ID_FB_VF							(9)
#define ID_FB_DCUNIT						(10)
#define ID_FB_CURSENSOR						(11)
#define ID_FB_TEMPER						(12)
#define ID_FB_EMPTY_STALL					(13)
#define ID_FB_ACUNIT						(14)

#define ID_FB_GLOBAL						(0xFE)


#if 0
typedef struct
{
	u8		FBID;
	u8		FBMode;
	u16		FBSize;
}stru_FB_PRE_DEF;
#endif



/////////////////////应用数据/////////////////////////
#define NOT_APPLICABLE                 (0)               /* 未采用 */


///////////////////////////////////////////////////////////////////////////////
////////////////////Global config para   //////////////////////////////////////
typedef const struct
{   /* 全局配置 */
    s16	  m_nMCUClkFreq;            	/* MCU CLOCK主频					*/
    s16	  m_nPWMClkFreq;              	/* PWM模块 CLOCK 频率				*/
	
	u16   m_nuPWMFreq;              	/* PWM输出 载波 频率				*/
	u16	  m_nuPWMPrsc;              	/* PWM模块预分频					*/
	
	u16   m_nuSpdloopFreq;				/* 速度环执行频率					*/
	s16   m_nOverModuFactor;            /* 电压调制系数						*/
	
	u16	  m_nuDeadZone;              	/* 死区时间  ns						*/
	u8	  m_bSampType;              	/* 电流采样方式 1 --- 单电阻.....	*/
	u8	  m_bSVPWMType;					/* SVPWM方式 0 -- 7Seg  1 --- 5Seg 	*/
	u8    m_bPWMUsedID;					/* 选用的PWM及AD端口 0--- PWM0  	*/
	u8	  m_bOPAValue;					/* 电流采样OPA选择					*/	
    u8	  m_buBemfDirEnable;      		/* 使能反电势顺逆风检测				*/
	u8    m_buChargeEnale;				/* 使能预充电功能					*/
	
    u8	  m_buIPDEnable;      			/* 使能IPD							*/	
    u8	  m_buDirCheckEnable;      		/* 使能顺逆风检测					*/
	u8	  m_buAllignEnable;      		/* 使能对相							*/	
    u8	  m_buVFStartEnable;      		/* 使能VF启动						*/
	
	u8	  m_buACDetectEnable;      		/* 使能AC检测						*/	
	u8	  m_buCtrLoopmode;      		/* 控制模式 0 速度环 1-				*/
	u8	  m_buPowerLmtInSpeedmode;		/* 速度环 限制功率					*/	
	u8	  m_buSpdLmtInPowermode;		/* 功率环 限制速度					*/
	
	u8	  m_buWeaenFluxEnable;			/* 弱磁控制使能						*/	
	u8	  m_buStopPWMEnable;			/* 停止时PWM使能 					*/
	u8	  m_buFaultAutoClr;				/* 故障自动清除使能					*/

	u8	  m_buStopMode;					/* 停止方式							*/
	
	u16   m_nuADCCaliTimes;				/* AD校正次数						*/	
	u16   m_nuADCOffsetError;			/* AD校正允许偏差					*/	
	u16   m_nuChargeTime;				/* 充电时间							*/
	u16   m_nuFaultClrPrd;				/* 故障清除周期						*/
	
} STR_GlobalCfg,*PSTR_GlobalCfg;

#define GLOBAL_CFG_TAB_M(ID)											\
{  		/* 全局配置 参数 */												\
	(s16)(MCU_MCLK_M##ID),				/* MCU CLOCK主频MHZ		*/		\
	(s16)(PWM_MCLK_M##ID),				/* PWM 模块CLOCK MHZ	*/		\
	(u16)PWM_FREQ_M##ID,				/* PWM输出 载波 频率 	*/		\
	(u16)PWM_PRSC_M##ID,				/* PWM模块预分频		*/		\
	(u16)SPD_LOOP_FREQUENCY_M##ID,		/* 速度环执行频率		*/		\
	(u16)OVER_MODU_FACTOR_M##ID,		/* 电压调制系数			*/		\
	(u16)DEADTIME_NS_M##ID,				/* 死区时间  ns			*/		\
	(u8)CURRENT_SAMPLE_TYPE_M##ID,		/* 电流采样方式			*/		\
	(u8)SVPWM_TYPE_M##ID,				/* SVPWM方式			*/		\
																		\
	(u8)PWM_USED_ID_M##ID,				/* 选用的PWM及AD端口	*/		\
	(u8)OPA_SELECT_M##ID,				/* 选用的OPA放大选项	*/		\
	(u8)DIR_EMF_CHECK_ENABLE_M##ID,		/* 使能反电势顺逆风检测	*/		\
	(u8)CHARGE_STATUS_M##ID,			/* 使能预充电功能		*/		\
																		\
	(u8)SEEK_POSITION_STATUS_M##ID,		/* 使能IPD				*/		\
	(u8)DIR_CHECK_STATUS_M##ID,			/* 使能顺逆风检测		*/		\
	(u8)ALLIGN_STATUS_M##ID,			/* 使能对相				*/		\
	(u8)VF_START_STATUS_M##ID,			/* 使能VF启动			*/		\
																		\
	(u8)AC_SENOR_PROTECT_STATUS_M##ID,	/* 使能AC检测			*/		\
	(u8)CLOSE_LOOP_M##ID,				/* 控制模式				*/		\
	(u8)POWER_LIMIT_STATUS_M##ID,		/* 速度环 限制功率		*/		\
	(u8)SPPED_LIMIT_STATUS_M##ID,		/* 功率环 限制速度		*/		\
																		\
	(u8)WEAKEN_FLUX_STATUS_M##ID,		/* 弱磁控制使能			*/		\
	(u8)PWM_ENABLE_STOP_M##ID,			/* 停止时PWM使能		*/		\
	(u8)FAULT_AUTO_CLR_M##ID,			/* 故障自动清除使能		*/		\
	(u8)STOP_MODE_M##ID,				/* 停止方式				*/		\
																		\
	(u16)CALIB_SAMPLES_M##ID,			/* AD校正次数			*/		\
	(u16)ADC_OFFSET_ERROR_M##ID,		/* AD校正允许偏差		*/		\
																		\
	(u16)CHARGE_TIME_M##ID,				/* 充电时间				*/		\
	(u16)FAULT_CLR_PRIOD_M##ID			/* 故障清除周期			*/		\
}





//////////////////////////////////////////////////////////////////////
////////////////////Board para   /////////////////////////////////////

typedef const struct
{   /* 功率板硬件电路特性与配置参数 */
    s16 m_nRatedUdc;            		/* 额定直流母线电压  0.1V	*/
    s16 m_nMaxUdc;              		/* 最大直流母线电压 		*/			// 0
    s32 m_nMaxCur;              		/* 最大相电流 单位：0.1A 	*/			// 0
  
	//HD  硬件驱动层
    s32	  m_wAdcSupplyVol;      		/* ADC参考电压 	单位：0.001伏特 	*/ 
    s32	  m_wRShunt;            		/* 分压电阻 	单位：0.001毫欧姆	*/
    s32	  m_wAmpGain;           		/* 放大器放大倍数 单位：0.000001倍	*/ 
    s32	  m_wVolShuntRatio;     		/* 母线电压采样分压比 	0.000001倍 	*/ 
    s32	  m_wBemfShuntRatio;    		/* 反电势电压采样分压比 0.000001倍 	*/
} STR_BoardParameter,*PSTR_BoardParameter;//stru_BoardParameterDef, *pStru_BoardParameterDef;

#define BOARD_PARAMETER_TAB_M(ID)									\
{  		/* 功率板硬件电路特性参数表 */								\
	(s16)(NOT_APPLICABLE),			/* 额定直流母线电压 0.1V		*/	\
	(s16)NOT_APPLICABLE,				/* 最大直流母线电压 			*/	\
	(s32)NOT_APPLICABLE,				/* 最大相电流 单位：A			*/	\
	(s32)(1000*1000*ADC_SUPPLY_VOLTAGE_M##ID),	/* ADC参考电压  单位：0.000001伏特 */	\
	(s32)(1000*1000*RSHUNT_M##ID),				/* 分压电阻     单位：0.001毫欧姆*/	\
	(s32)(1000*1000*AMPLIFICATION_GAIN_M##ID),	/* 放大器放大倍数 单位：0.000001倍 */	\
	(s32)(1000*1000*VOLTAGE_SHUNT_RATIO_M##ID),	/* 母线电压采样分压比 	0.000001倍  */	\
	(s32)(1000*1000*BEMF_SHUNT_RATIO_M##ID)		/* 反电势电压采样分压比 0.000001倍  */	\
}

//////////////////////////////////////////////////////////////////////
////////////////////Motor para   /////////////////////////////////////

typedef const struct
{   /* 电机参数结构体 */
    s8  m_bMotorType;           		/* 0:im,1:spm,2:ipm,3...*/
	s8  m_bPolePairs;					/* 电机磁极对数 */
	u16  m_nuReserved;	
	
    s32		m_wRatedFreq;				/* 额定频率 单位：0.01Hz*/
    s32		m_nRatedCur;				/* 额定电流 单位：0.1A */
    s32		m_wMotorRs;					/* 电机内阻 单位：0.0001欧姆 */
    s32		m_wMotorLd;					/* 电机D轴电感 单位：uH */
    s32		m_wMotorLq;             	/* 电机Q轴电感 单位：uH */
    s32		m_wFluxConst;           	/* 电机磁链常数 WB */	
}STR_MotorParameter, *PSTR_MotorParameter;

#define MOTOR_PARAMETER_TAB_M(ID)									\
{																	\
	NOT_APPLICABLE,					/* 0:im,1:spm,2:ipm,3...*/		\
	U_MOTOR_PP_M##ID,				/* 电机磁极对数 */				\
	NOT_APPLICABLE,					/* 预留       */				\
	(s32)(100*U_MAX_FREQ_M##ID),			/* 额定频率 单位：0.01Hz*/		\
	(s32)(NOT_APPLICABLE),					/* 额定电流 单位：0.1A */		\
	(s32)(10000*U_MOTOR_RS_M##ID),			/* 电机内阻 单位：0.0001欧姆 */	\
	(s32)U_MOTOR_LD_M##ID,					/* 电机D轴电感 单位：uH */		\
	(s32)U_MOTOR_LQ_M##ID,					/* 电机Q轴电感 单位：uH */		\
	(s32)(100000*U_MOTOR_FLUX_CONST_M##ID),	/* 电机磁链常数 WB */			\
}

//////////////////////////////////////////////////////////////////////
////////////////////SLVC0 para   /////////////////////////////////////

typedef struct
{	
	s32		m_wCloseFreq;						//开环拖动最终频率				1 0.01Hz
	s32		m_wOpenFreq;						//开环运行频率					1 0.01Hz
	s32		m_wMinRunFreq;						//最低运行频率					1 0.01Hz
	s32		m_wCurCloseFreq;					//电流闭环频率					1 0.01Hz
	s32		m_wFreq_Acc;						//开环拖动频率加速调整值		1 0.01Hz
	s32		m_wFreq_Dec;						//开环拖动频率减速调整值		1
	s32		m_wDQCurRatioOpen2Close;			//开闭环切换时DQ轴变化率		1 0.001A/s
	u16		MatchTimes2Close;					//闭环时估算和电流匹配次数		0
	u16		TransTime2Close;					//开环闭环过渡时间				0

	s32		m_wImax;							//最大工作电流					1 0.001A
	s32		m_wIdStartSet;						//D轴电流设定					1 0.001A
	s32		m_wIqStartSet;						//Q轴电流设定					1 0.001A	
	s32		m_wIqBrake;							//Q轴制动电流设定				1 0.001A
	s32		m_wBusVoltStart;					//母线电压保护电压值			1
	s32		m_wBusVoltEnd;						//母线电压保护结束值			1
	s32		m_wBusVoltRestore;					//母线电压保护恢复值			1
	u8		bVoltageProtectionEnable;			//电压保护模式开启				1
	u8		StopModeInVoltProtect;				//电压保护模式时电机停止方式	1
	s16		m_VFDeadZoneComp;					//VF启动死区补偿系数			1 0~32767
	
	s32		m_wThetaFilTime;					//角度滤波时间					1 0.1ms
	s32		m_wSpeedFilTime;					//速度滤波时间					1 0.1ms
	s16		nPLLKp0;							//PLL_Kp 估算器Kp0				1
	s16		nPLLKi0;							//PLL_Kp 估算器Ki0				1
	s16		nPLLFreq0;							//PLL频率点0					1
	s16		nPLLKp1;							//PLL_Kp 估算器Kp1				1
	s16		nPLLKi1;							//PLL_Kp 估算器Ki1				1
	s16		nPLLFreq1;							//PLL频率点1					1
	u16		Reseved1;							//预留							0
	u16		Reseved2;							//预留							0
}STR_FB_SLVC_CFG0;

#define SLVC0_PARAMETER_TAB_M(ID)										\
{																		\
	(s32)(100*OPEN_ANGLE_TAG_FREQ_M##ID),		/* 开环拖动最终频率*/	\
	(s32)(100*CLOSE2OPEN_FREQ_M##ID),			/* 开环运行频率 */		\
	(s32)(100*MIN_RUN_FREQ_M##ID),				/* 最低运行频率 */		\
	(s32)(100*CURRENTLOOP_CLOSE_FREQ_M##ID),	/* 电流闭环频率 */		\
	(s32)(100*FREQ_ACC_M##ID),					/* 开环频率加速调整值*/	\
	(s32)(100*FREQ_DEC_M##ID),					/* 开环频率减速调整值*/	\
	(s32)(1000*OPEN2CLOSE_RUN_CURRENT_RAMP_M##ID),	/* DQ轴变化率*/			\
	(u16)MATCH_TIME_M##ID,						/* 匹配次数*/			\
	(u16)OPEN2CLOSE_RUN_COV_TIME_M##ID,			/* 过渡时间*/			\
	(s32)(1000*IQMAX_M##ID),					/* 最大工作电流 */		\
	(s32)(1000*ID_START_M##ID),					/* D轴电流设定 */		\
	(s32)(1000*IQ_START_M##ID),					/* Q轴电流设定 */		\
	(s32)(1000*IQ_BRAKE_SET_M##ID),				/* Q轴制动电流 */		\
	(s32)(100* U_UNDVOLT_START_M##ID),			/* 电压保护电压值 */	\
	(s32)(100* U_UNDVOLT_STOP_M##ID),			/* 电压保护结束值 */	\
	(s32)(100* U_UNDVOLT_RECOVER_M##ID),		/* 电压保护恢复值 */	\
	(u8)U_UNDVOLT_PROT_ENABLE_M##ID,			/* 电压保护模式开启 */	\
	(u8)NOT_APPLICABLE,							/* 电压保护停止方式*/	\
	(s16)VF_DEADZONE_COMP_FACTOR_M##ID,			/* VF启动死区补偿系数*/	\
	(s32)(10*THETA_FIL_TIME_M##ID),				/* 角度滤波时间 */		\
	(s32)(10*SPEED_FIL_TIME_M##ID),				/* 速度滤波时间 */		\
	(s16)PLL_KP_GAIN_M##ID,						/* PLL_Kp0*/			\
	(s16)PLL_KI_GAIN_M##ID,						/* PLL_Ki0*/			\
	(s16)(10* PLL_K_FREQ0_M##ID),				/* PLL频率点0 0.1Hz*/	\
	(s16)PLL_KP_RUN_M##ID,						/* PLL_Kp1*/			\
	(s16)PLL_KI_RUN_M##ID,						/* PLL_Ki1*/			\
	(s16)(10* PLL_K_FREQ1_M##ID),				/* PLL频率点1 0.1Hz*/	\
	(u16)NOT_APPLICABLE,						/* 预留	0*/				\
	(u16)NOT_APPLICABLE							/* 预留	0*/				\
}

//////////////////////////////////////////////////////////////////////
////////////////////Cur loop para   /////////////////////////////////////

typedef struct
{	
	s32		m_wIqSet;							//Q轴电流设定值	1		0.001A
	s16		nVqMax;								//Q轴电压最大值	1
	s16 	nVqMin;								//Q轴电压最小 1
	s16 	nVdMax;								//d轴电压最大值	1
	s16 	nVdMin;								//d轴电压最小 1
	u16		Kp;									//Kp	1
	u16		Ki;									//Ki	1
	s16		nWeakenCurMax;						//最大弱磁电流	1		0.01A
	s16		Reserved;							//保留	0
	s32		m_wDCurFilTimeSet;					//电流指令滤波时间	1	0.1ms
	s32		m_wQCurFilTimeSet;					//电流指令滤波时间	1	0.1ms
}STR_FB_CUR_LOOP;


#define CURLOOP_PARAMETER_TAB_M(ID)										\
{																		\
	(s32)(1000*IQ_SET_M##ID),					/*Q轴电流设定值*/		\
	(s16)(32767.0 * VQMAX_M##ID),				/*Q轴电压最大值*/		\
	(s16)(32767.0 * VQMIN_M##ID),				/*Q轴电压最小值*/		\
	(s16)(32767.0 * VDMAX_M##ID),				/*D轴电压最大值*/		\
	(s16)(32767.0 * VDMIN_M##ID),				/*D轴电压最小值*/		\
	(u16)P_CURRENT_KP_M##ID,					/*Kp			*/		\
	(u16)P_CURRENT_KI_M##ID,					/*Ki			*/		\
	(u16)(100*AUTO_FW_LIM_M##ID),				/*最大弱磁电流	*/		\
	(u16)NOT_APPLICABLE,						/* 预留	0*/				\
	(s32)(10*D_CURRENT_REF_FIL_TIME_M##ID),		/* 电流指令滤波时间*/	\
	(s32)(10*Q_CURRENT_REF_FIL_TIME_M##ID)		/* 电流指令滤波时间*/	\
}

#define CURLOOP_PARAMETER_TAB_RSVD_M(ID)								\
{																		\
	(s32)NOT_APPLICABLE,						/*Q轴电流设定值*/		\
	(s16)NOT_APPLICABLE,						/*Q轴电压最大值*/		\
	(s16)NOT_APPLICABLE,						/*Q轴电压最小值*/		\
	(s16)NOT_APPLICABLE,						/*D轴电压最大值*/		\
	(s16)NOT_APPLICABLE,						/*D轴电压最小值*/		\
	(u16)NOT_APPLICABLE,						/*Kp			*/		\
	(u16)NOT_APPLICABLE,						/*Ki			*/		\
	(u16)NOT_APPLICABLE,						/*最大弱磁电流	*/		\
	(u16)NOT_APPLICABLE,						/* 预留	0*/				\
	(s32)NOT_APPLICABLE,						/* 电流加速调整值*/		\
	(s32)NOT_APPLICABLE							/* 电流减速调整值*/		\
}


//////////////////////////////////////////////////////////////////////
////////////////////Speed loop para   /////////////////////////////////////

typedef struct
{	
	s32		m_wPowerLmtValue;					//限制功率大小		1	0.01W
	s16		nPowerLmtCalcCycle;					//限制功率计算周期	1
	s16		Reserved;							//保留	0
	s32		m_wPowerLmtSpdValue;				//限功率转速给定	1	0.01Hz
	s16		nSpeedLoopCycle;					//速度环计算周期	1
	s16		nState04WaitTime;					//速度变量初始化时间	1
	u16		PASRKp;								//速度环Kp	1
	u16		PASRKi;								//速度环Ki	1
	s32		m_wIqMax;							//速度环输出最大值	1	0.001A
	s32		m_wIqMin;							//速度环输出最小值	1	0.001A
	s32		m_wSpdRunAcc;						//速度加速调整值	1	0.01Hz
	s32		m_wSpdRunDec;						//速度减速调整值	1	0.01Hz	
}STR_FB_SPD_LOOP;

#define SPDLOOP_PARAMETER_TAB_M(ID)										\
{																		\
	(s32)(100*POWER_LIMIT_VALUE_M##ID),			/*限制功率大小*/		\
	(s16)POWER_LIMIT_TIME_M##ID,				/*限制功率计算周期*/	\
	(s16)NOT_APPLICABLE,						/* 预留	0*/				\
	(s32)(100*POWER_LIMIT_SPEED_M##ID),			/*限功率转速给定*/		\
	(s16)SPEED_LOOP_CNTR_M##ID,					/*速度环计算周期*/		\
	(s16)STATE04_WAITE_TIME_M##ID,				/*速度变量初始化时间*/	\
	(u16)P_ASR_KP_M##ID,						/*速度环Kp		*/		\
	(u16)P_ASR_KI_M##ID,						/*速度环Ki		*/		\
	(s32)(1000*IQMAX_M##ID),					/*速度环输出最大值*/	\
	(s32)(1000*IQMIN_M##ID),					/*速度环输出最小值*/	\
	(s32)(100*SPEED_RUN_ACC_M##ID),				/*速度加速调整值*/		\
	(s32)(100*SPEED_RUN_DEC_M##ID)				/*速度减速调整值*/		\
}

#define SPDLOOP_PARAMETER_TAB_RSVD_M(ID)										\
{																		\
	(s16)NOT_APPLICABLE,						/*限制功率大小*/		\
	(s16)NOT_APPLICABLE,						/*限制功率计算周期*/	\
	(s16)NOT_APPLICABLE,						/* 预留	0*/				\
	(s32)NOT_APPLICABLE,						/*限功率转速给定*/		\
	(s16)NOT_APPLICABLE,						/*速度环计算周期*/		\
	(s16)NOT_APPLICABLE,						/*速度变量初始化时间*/	\
	(u16)NOT_APPLICABLE,						/*速度环Kp		*/		\
	(u16)NOT_APPLICABLE,						/*速度环Ki		*/		\
	(s32)NOT_APPLICABLE,						/*速度环输出最大值*/	\
	(s32)NOT_APPLICABLE,						/*速度环输出最小值*/	\
	(s32)NOT_APPLICABLE,						/*速度加速调整值*/		\
	(s32)NOT_APPLICABLE							/*速度减速调整值*/		\
}


//////////////////////////////////////////////////////////////////////
////////////////////Power loop para   /////////////////////////////////////


typedef struct
{	
	
	s32		m_wSpdLmtValue;						//限制转速大小	1			0.01Hz
	s16		nPLoopSpdLmtCalcCycle;				//功率环限转速计算周期	1
	s16		nPLoopCalcCycle;					//功率环计算周期	1
	s32		m_wLmdSpdPowerSetting;				//限转速功率给定	1		0.01W
	s32		m_wPowerSetting;					//功率给定	1				0.01W	
	u16		nPowerKp;							//功率环Kp	1
	u16 	nPowerKi;							//功率环Ki	1
	s32		m_wPLoopIqMax;						//功率环输出Iq最大值	1
	s32		m_wPLoopIqMin;						//功率环输出Iq最小值	1
	s32		m_wPowerRunAcc;						//功率加速调整值	1
	s32		m_wPowerRunDec;						//功率减速调整值	1
		
	s32		m_wPowerFacA0;						//功率计算修正系数a0	1
	s32		m_wPowerFacA1;						//功率计算修正系数a1	1
	s32		m_wPowerFacA2;						//功率计算修正系数a2	1
		
}STR_FB_POWER_LOOP;

#define PWRLOOP_PARAMETER_TAB_M(ID)										\
{																		\
	(s32)(100*SPEED_LIMIT_VALUE_M##ID),			/*限制转速大小*/		\
	(s16)SPEED_LIMIT_TIME_M##ID,				/*限转速计算周期*/		\
	(s16)POWER_LOOP_CNTR_M##ID,					/*功率环计算周期*/		\
	(s32)(100*SPEED_LIMIT_POWER_VALUE_M##ID),	/*限转速功率给定*/		\
	(s32)(100*POWER_SET_M##ID),					/*功率给定*/			\
	(u16)POWER_KP_M##ID,						/*功率环Kp		*/		\
	(u16)POWER_KI_M##ID,						/*功率环Ki		*/		\
	(s32)(1000*POWER_IQMAX_M##ID),				/*功率环输出Iq最大值*/	\
	(s32)(1000*POWER_IQMIN_M##ID),				/*功率环输出Iq最小值*/	\
	(s32)(100*POWER_RUN_ACC_M##ID),				/*功率加速调整值*/		\
	(s32)(100*POWER_RUN_DEC_M##ID),				/*功率减速调整值*/		\
	(s32)(4096*POWER_FAC_A0_M##ID),				/*功率计算修正系数a0*/	\
	(s32)(4096*POWER_FAC_A1_M##ID),				/*功率计算修正系数a1*/	\
	(s32)(4096*POWER_FAC_A2_M##ID)				/*功率计算修正系数a2*/	\
}

#define PWRLOOP_PARAMETER_TAB_RSVD_M(ID)								\
{																		\
	(s32)NOT_APPLICABLE,						/*限制转速大小*/		\
	(s16)NOT_APPLICABLE,						/*限转速计算周期*/		\
	(s16)NOT_APPLICABLE,						/*功率环计算周期*/		\
	(s32)NOT_APPLICABLE,						/*限转速功率给定*/		\
	(s32)NOT_APPLICABLE,						/*功率给定*/			\
	(u16)NOT_APPLICABLE,						/*功率环Kp		*/		\
	(u16)NOT_APPLICABLE,						/*功率环Ki		*/		\
	(s32)NOT_APPLICABLE,						/*功率环输出Iq最大值*/	\
	(s32)NOT_APPLICABLE,						/*功率环输出Iq最小值*/	\
	(s32)NOT_APPLICABLE,						/*功率加速调整值*/		\
	(s32)NOT_APPLICABLE,						/*功率减速调整值*/		\
	(s32)NOT_APPLICABLE,						/*功率计算修正系数a0*/	\
	(s32)NOT_APPLICABLE,						/*功率计算修正系数a1*/	\
	(s32)NOT_APPLICABLE							/*功率计算修正系数a2*/	\
}


//////////////////////////////////////////////////////////////////////
////////////////////顺逆风 para   /////////////////////////////////////


typedef struct
{
	s16		nSpdTrackDelayTime;					//顺逆风检测时间	1
	s16		Reserved;							//		0
	s32		m_wSpdTrackOnFreq;					//顺风切闭环频率	1		0.01Hz
	s32		m_wBrakeFreqAntiDirec;				//逆风刹车频率		1		0.01Hz
	s32		m_wMotorStopCurrentThd;				//电机停转电流检测阈值	1	0.001A
	s32		m_wMotorStopCurDifThd;				//电机停转电流差值检测阈值	1
	s16		nMotorStopTime;						//电机停止检测滤波时间	1
	s16		nMotorStopDelayTime;				//电机停止后延迟时间	1
	s16		nBemfAngComp;						//反电势角度补偿 度		1
	s16		nBemfTrackMinVolt;					//反电势检测最小电压	1
}STR_FB_DIR_CHECK;

#define DIR_CHECK_PARAMETER_TAB_M(ID)									\
{																		\
	(s16)SPEED_TRACK_DELAYTIME_M##ID,			/*顺逆风检测时间*/		\
	(s16)NOT_APPLICABLE,						/* 预留	0*/				\
	(s32)(100*SPEED_TRACK_ON_FREQ_THH_M##ID),	/*顺风切闭环频率*/		\
	(s32)(100*EBRK_ON_FREQ_THH_M##ID),			/*逆风刹车频率  */		\
	(s32)(1000*MOTOR_STOP_CUR_THD_M##ID),		/*停转电流检测阈值*/	\
	(s32)(1000*MOTOR_STOP_CUR_DIF_THD_M##ID),	/*停转电流差值检测阈值*/\
	(s16)STOP_TIME_M##ID,						/*停止检测滤波时间*/	\
	(s16)STOP_DELAY_TIME_M##ID,					/*停止后延迟时间*/		\
	(s16)BEMF_ANG_COMP_M##ID,					/*反电势角度补偿 度*/	\
	(s16)BEMF_TRACK_MIN_VOLT_M##ID				/*反电势检测最小电压*/	\
}

#define DIR_CHECK_PARAMETER_TAB_RSVD_M(ID)								\
{																		\
	(s16)NOT_APPLICABLE,						/*顺逆风检测时间*/		\
	(s16)NOT_APPLICABLE,						/* 预留	0*/				\
	(s32)NOT_APPLICABLE,						/*顺风切闭环频率*/		\
	(s32)NOT_APPLICABLE,						/*逆风刹车频率  */		\
	(s32)NOT_APPLICABLE,						/*停转电流检测阈值*/	\
	(s32)NOT_APPLICABLE,						/*停转电流差值检测阈值*/\
	(s16)NOT_APPLICABLE,						/*停止检测滤波时间*/	\
	(s16)NOT_APPLICABLE,						/*停止后延迟时间*/		\
	(s16)NOT_APPLICABLE,						/*反电势角度补偿 度*/	\
	(s16)NOT_APPLICABLE							/*反电势检测最小电压*/	\
}



//////////////////////////////////////////////////////////////////////
////////////////////IPD para   /////////////////////////////////////

typedef struct
{
	u32		m_wuInitAngComp;					//初始位置检测补偿角度	1		65536 ---360
	u16		nuIPDPlusTime;						//脉冲注入时间宽度设置	1
	u16		nuIPDWaitTime;						//脉冲空闲等待时间宽度设置	1
}STR_FB_IPD;

#define IPD_PARAMETER_TAB_M(ID)												\
{																			\
	(u32)(182*U_START_ANGLE_COMP_M##ID),		/*初始位置检测补偿角度*/	\
	(u16)IPD_PLUS_TIME_SETTING_M##ID,			/*注入时间宽度设置*/		\
	(u16)IPD_WAIT_TIME_SETTING_M##ID,			/*空闲等待时间宽度设置*/	\
}

#define IPD_PARAMETER_TAB_RSVD_M(ID)										\
{																			\
	(u32)NOT_APPLICABLE,						/*初始位置检测补偿角度*/	\
	(u16)NOT_APPLICABLE,						/*注入时间宽度设置*/		\
	(u16)NOT_APPLICABLE,						/*空闲等待时间宽度设置*/	\
}


//////////////////////////////////////////////////////////////////////
////////////////////Allign para   /////////////////////////////////////

typedef struct
{
	u32		m_wuAlignAngle;						//预定位角度	1
	s32		m_wPlat1Cur;						//第一段定位电流	1	0.001A
	s32		m_wPlat2Cur;						//第二段定位电流	1	0.001A
	s16		nPlat1Time;							//第一段定位时间	1
	s16		nPlat2Time;							//第二段定位时间	1
	s32		nAlignTotalTime;					//定位总时长	1
	s32		m_wAlignCurAcc;						//定位电流加速调整值	1	0.001A/s
	s32		m_wAlignCurDec;						//定位电流减速调整值	1	0.001A/s	
}STR_FB_ALLIGN;

#define ALLIGN_PARAMETER_TAB_M(ID)											\
{																			\
	(u32)(182*ALIGN_ANGLE_M##ID),				/*预定位角度     */			\
	(s32)(1000*U_START_CUR_SET_F_M##ID),		/*第一段定位电流 */			\
	(s32)(1000*U_START_CUR_SET_S_M##ID),		/*第二段定位电流 */			\
	(s16)DC_HOLDTIME_TIME_LENTH_M##ID,			/*第一段定位时间 */			\
	(s16)DC_HOLDTIME_TIME_LENTH_STAGE1_M##ID,	/*第二段定位时间 */			\
	(s32)DC_ALIGN_TOTAL_LENTH_M##ID,			/*定位总时长	 */			\
	(s32)(1000*ALIGN_CURRENT_ACC_M##ID),		/*电流加速调整值 */			\
	(s32)(1000*ALIGN_CURRENT_DEC_M##ID)			/*电流减速调整值 */			\
}

#define ALLIGN_PARAMETER_TAB_RSVD_M(ID)										\
{																			\
	(u32)NOT_APPLICABLE,						/*预定位角度     */			\
	(s32)NOT_APPLICABLE,						/*第一段定位电流 */			\
	(s32)NOT_APPLICABLE,						/*第二段定位电流 */			\
	(s16)NOT_APPLICABLE,						/*第一段定位时间 */			\
	(s16)NOT_APPLICABLE,						/*第二段定位时间 */			\
	(s32)NOT_APPLICABLE,						/*定位总时长	 */			\
	(s32)NOT_APPLICABLE,						/*电流加速调整值 */			\
	(s32)NOT_APPLICABLE							/*电流减速调整值 */			\
}


//////////////////////////////////////////////////////////////////////
////////////////////VF para   /////////////////////////////////////

typedef struct
{	
	s16		nVFStartValue;						//VF启动电压值	0.01V		1
	u16		nVF2CloseDelayTime;					//启动开环延时时间	1
	s16		nVFVoltAcc;							//VF电压加速调整值	0.01V/s 1
	s16		nVFVoltDec;							//VF电压减速调整值	0.01V/s 1	
}STR_FB_VF;

#define VF_START_PARAMETER_TAB_M(ID)										\
{																			\
	(s16)(100*VF_START_VALUE_M##ID),			/*VF启动电压值 0.01V   */			\
	(u16)VF_OPEN2CLOSE_TIME_M##ID,				/*启动开闭环延时时间 */		\
	(s16)(100*VF_VOLT_ACC_M##ID),				/*VF电压加速调整值 0.01V/s */		\
	(s16)(100*VF_VOLT_DEC_M##ID)				/*VF电压减速调整值 0.01V/s */		\
}

#define VF_START_PARAMETER_TAB_RSVD_M(ID)									\
{																			\
	(s16)NOT_APPLICABLE,						/*VF启动电压值   */			\
	(u16)NOT_APPLICABLE,						/*启动开闭环延时时间 */		\
	(s16)NOT_APPLICABLE,						/*VF电压加速调整值 */		\
	(s16)NOT_APPLICABLE							/*VF电压减速调整值 */		\
}


//////////////////////////////////////////////////////////////////////
////////////////////DC UNIT para   /////////////////////////////////////

typedef struct
{	
	s32		m_wDCOverVoltage;					//	过压保护阈值	1
	s32		m_wDCOverVoltageRecover;			//	过压恢复电压值	1
	s32		m_wDCUnderVoltage;					//  低压保护阈值	1
	s32		m_wDCUnderVoltageRecover;			//	低压消除恢复电压值	1
	u16		nOvVoltageDetectTime;				//	过压检测时间	1
	u16		nUndVoltageDetectTime;				//	欠压检测时间	1
	u16		nVoltageRecoverTime;				//  电压恢复正常等待时间	1
	s8		bOvVoltProtectEnbale;				//	使能过压保护	1
	s8		bUndVoltProtectEnbale;				//	使能低压保护	1		
}STR_FB_DC_UNIT0;

#define DC_UNIT0_PARAMETER_TAB_M(ID)										\
{																			\
	(s32)(100*U_OVERVOLTAGE_FAULT_M##ID),		/*过压保护阈值		*/		\
	(s32)(100*U_OVERVOLTAGE_RECOVER_M##ID),		/*过压恢复电压值	*/		\
	(s32)(100*U_UNDERVOLTAGE_FAULT_M##ID),		/*低压保护阈值		*/		\
	(s32)(100*U_UNDERVOLTAGE_RECOVER_M##ID),	/*低压消除恢复电压值*/		\
	(u16)U_OVER_VOLT_DETECT_TIME_M##ID,			/*过压检测时间		*/		\
	(u16)U_UNDE_VOLT_DETECT_TIME_M##ID,			/*欠压检测时间		*/		\
	(u16)VOLT_FAULT_RECOVER_TIME_M##ID,			/*电压恢复正常等待时间*/	\
	(u8)U_OV_VOLT_PROTECT_ENABLE_M##ID,			/*使能过压保护		*/		\
	(u8)U_UND_VOLT_PROTECT_ENABLE_M##ID			/*使能低压保护		*/		\
}

#define DC_UNIT0_PARAMETER_TAB_RSVD_M(ID)									\
{																			\
	(s32)NOT_APPLICABLE,						/*过压保护阈值		*/		\
	(s32)NOT_APPLICABLE,						/*过压恢复电压值	*/		\
	(s32)NOT_APPLICABLE,						/*低压保护阈值		*/		\
	(s32)NOT_APPLICABLE,						/*低压消除恢复电压值*/		\
	(u16)NOT_APPLICABLE,						/*过压检测时间		*/		\
	(u16)NOT_APPLICABLE,						/*欠压检测时间		*/		\
	(u16)NOT_APPLICABLE,						/*电压恢复正常等待时间*/	\
	(u8)NOT_APPLICABLE,							/*使能过压保护		*/		\
	(u8)NOT_APPLICABLE							/*使能低压保护		*/		\
}


//DC_UNIT1 预留给后续应用，需要相应配置参数
typedef struct
{	
	s32		m_wDCOverVoltage;					//	过压保护阈值	1
	s32		m_wDCOverVoltageRecover;			//	过压恢复电压值	1
	s32		m_wDCUnderVoltage;					//  低压保护阈值	1
	s32		m_wDCUnderVoltageRecover;			//	低压消除恢复电压值	1
	u16		nOvVoltageDetectTime;				//	过压检测时间	1
	u16		nUndVoltageDetectTime;				//	欠压检测时间	1
	u16		nVoltageRecoverTime;				//  电压恢复正常等待时间	1
	s8		bOvVoltProtectEnbale;				//	使能过压保护	1
	s8		bUndVoltProtectEnbale;				//	使能低压保护	1
	
	s32		m_wUndVoltChargeVolt;				//	低压控制电压值	1
	s32		m_wUndVoltChargeStopVolt;			//	低压控制停止电压值	1
	s32		m_wUndVoltChargeRecoverVolt;		//	退出低压控制电压值	1
	s32		m_wOvVoltChargeVolt;				//	高压控制电压值	1
	s32		m_wOvVoltChargeStopVolt;			//	高压控制停止电压值	1
	s32		m_wOvVoltChargeRecoverVolt;			//	退出高压控制电压值	1
}STR_FB_DC_UNIT1;

#define DC_UNIT1_PARAMETER_TAB_M(ID)										\
{																			\
	(s32)(100*U_OVERVOLTAGE_FAULT_M##ID),		/*过压保护阈值		*/		\
	(s32)(100*U_OVERVOLTAGE_RECOVER_M##ID),		/*过压恢复电压值	*/		\
	(s32)(100*U_UNDERVOLTAGE_FAULT_M##ID),		/*低压保护阈值		*/		\
	(s32)(100*U_UNDERVOLTAGE_RECOVER_M##ID),	/*低压消除恢复电压值*/		\
	(u16)U_OVER_VOLT_DETECT_TIME_M##ID,			/*过压检测时间		*/		\
	(u16)U_UNDE_VOLT_DETECT_TIME_M##ID,			/*欠压检测时间		*/		\
	(u16)VOLT_FAULT_RECOVER_TIME_M##ID,			/*电压恢复正常等待时间*/	\
	(u16)U_OV_VOLT_PROTECT_ENABLE_M##ID,		/*使能过压保护		*/		\
	(u16)U_UND_VOLT_PROTECT_ENABLE_M##ID，		/*使能低压保护		*/		\
																			\
	(s32)NOT_APPLICABLE,						/*低压控制电压值	*/		\
	(s32)NOT_APPLICABLE,						/*低压控制停止值	*/		\
	(s32)NOT_APPLICABLE,						/*退出低压控制电压值*/		\
	(s32)NOT_APPLICABLE,						/*高压控制电压值	*/		\
	(s32)NOT_APPLICABLE,						/*高压控制停止电压值*/		\
	(s32)NOT_APPLICABLE							/*退出高压控制电压值*/		\
}

#define DC_UNIT1_PARAMETER_TAB_RSVD_M(ID)									\
{																			\
	(s32)NOT_APPLICABLE,						/*过压保护阈值		*/		\
	(s32)NOT_APPLICABLE,						/*过压恢复电压值	*/		\
	(s32)NOT_APPLICABLE,						/*低压保护阈值		*/		\
	(s32)NOT_APPLICABLE,						/*低压消除恢复电压值*/		\
	(u16)NOT_APPLICABLE,						/*过压检测时间		*/		\
	(u16)NOT_APPLICABLE,						/*欠压检测时间		*/		\
	(u16)NOT_APPLICABLE,						/*电压恢复正常等待时间*/	\
	(u16)NOT_APPLICABLE,						/*使能过压保护		*/		\
	(u16)NOT_APPLICABLE,						/*使能低压保护		*/		\
																			\
	(s32)NOT_APPLICABLE,						/*低压控制电压值	*/		\
	(s32)NOT_APPLICABLE,						/*低压控制停止值	*/		\
	(s32)NOT_APPLICABLE,						/*退出低压控制电压值*/		\
	(s32)NOT_APPLICABLE,						/*高压控制电压值	*/		\
	(s32)NOT_APPLICABLE,						/*高压控制停止电压值*/		\
	(s32)NOT_APPLICABLE							/*退出高压控制电压值*/		\
}


//////////////////////////////////////////////////////////////////////
////////////////////CUR SENSOR UNIT para   /////////////////////////////////////

typedef struct
{	
	s16		nHardOvCurVolt;						//	硬件过流保护比较电压值	1
	s16		nReserved;							//	预留	1
	s32		m_wSoftOvCur;						//	软件过流保护电流值	1	0.001A
	u16		nSoftOvCurTimes;					//  连续软件过流次数	1
	u16		nOvCurRecoverTime;					//	过流恢复时间		1
	u16 	nCurSampADConvTime;					//	电流采样转换时间	1
	u16 	nCurSampStableTime;					//	电流采样稳定时间	1	
}STR_FB_CUR_SENSE_UNIT;

#define CUR_SENSOR_PARA_TAB_M(ID)											\
{																			\
	(s16)I_PH_HARD_OC_FAULT_CMP_VOLT_M##ID,		/*硬件过流保护比较电压值*/	\
	(s16)NOT_APPLICABLE,						/*预留				*/		\
	(s32)(1000*I_PH_OVERCURRENT_FAULT_M##ID),	/*软件过流保护电流值*/		\
	(u16)I_PH_OVERCURRENT_FAULT_TIMES_M##ID,	/*连续软件过流次数	*/		\
	(u16)CURRENT_FAULT_RECOVER_TIME_M##ID,		/*过流恢复时间		*/		\
	(u16)ADC_COV_TIME_M##ID,					/*电流采样转换时间	*/		\
	(u16)SAMP_STABLE_TIME_SHUNT_M##ID			/*电流采样稳定时间	*/		\
}

//////////////////////////////////////////////////////////////////////
////////////////////TEMP SENSOR UNIT para   /////////////////////////////////////

typedef struct
{
	s32		m_wVotBaseTemp;						//	基准温度	1
	s32		m_wVotBaseVolt;						//	基准VOT电压 1
	s32		m_wVotSlope;						//	斜率	1
	s32		m_wMaxAllowedWorkTemp;				//  允许最高工作温度	1
	s32		m_wMinAllowedWorkTemp;				//	允许最低工作温度	1
	s32		m_wMaxCurInMaxTemp;					//	最高温度允许电流	1
	u8		HysterTemp;							//	温度报警滞回温度	1
	u8		bOvTempProtectEnable;				//	使能过温保护	1
	u16		nDetectionTime;						//	故障检测时间	
	u16		nFaultRecoverTime;					//	故障恢复时间	
	u16		Reserved;							//		0	
}STR_FB_TEMPER_VOT_UNIT;


typedef struct
{
	s32		m_wNTCBaseTemp;						//	NTC基准温度 1
	s32		m_wNTCBaseVolt;						//	NTC分压后基准电压	1
	s32		m_wNTCBFactor;						//	NTC温度系数B	1
	s32		m_wMaxAllowedWorkTemp;				//	允许最高工作温度	1
	s32		m_wMinAllowedWorkTemp;				//	允许最低工作温度	1
	s32		m_wMaxCurInMaxTemp;					//	最高温度允许电流	1	
	u8		HysterTemp;							//	温度报警滞回温度	1
	u8		bOvTempProtectEnable;				//	使能过温保护	1
	u16		nDetectionTime;						//	故障检测时间	
	u16		nFaultRecoverTime;					//	故障恢复时间
	u16		nreserved;							//	故障恢复时间
}STR_FB_TEMPER_NTC_UNIT;

#define TEMPER_NTC_PARA_TAB_M(ID)											\
{																			\
	(s32)TEMP_BASED_M##ID,						/*基准温度			*/		\
	(s32)TEMP_BASED_VOLT_M##ID,					/*NTC分压后基准电压 */		\
	(s32)TEMP_B_FACTOR_M##ID,					/*NTC温度系数B		*/		\
	(s32)TEMP_MAX_ALLOWED_M##ID,				/*允许最高工作温度	*/		\
	(s32)TEMP_MIN_ALLOWED_M##ID,				/*允许最低工作温度	*/		\
	(s32)PH_CUR_ALLOWED_MAXTEMP_M##ID,			/*最高温度允许电流	*/		\
	(u8)TEMP_HYP_ALLOWED_M##ID,					/*温度报警滞回温度	*/		\
	(u8)TEMP_PROTECT_ENABLE_M##ID,				/*使能过温保护		*/		\
	(u16)TEMP_FAULT_DETECT_TIME_M##ID,			/*故障检测时间		*/		\
	(u16)TEMP_FAULT_RECOVER_TIME_M##ID，		/*故障恢复时间		*/		\
	(u16)NOT_APPLICABLE							/*故障恢复时间		*/		\
}

#define TEMPER_NTC_PARA_TAB_RSVD_M(ID)										\
{																			\
	(s32)NOT_APPLICABLE,						/*基准温度			*/		\
	(s32)NOT_APPLICABLE,						/*NTC分压后基准电压 */		\
	(s32)NOT_APPLICABLE,						/*NTC温度系数B		*/		\
	(s32)NOT_APPLICABLE,						/*允许最高工作温度	*/		\
	(s32)NOT_APPLICABLE,						/*最高温度允许电流	*/		\
	(s32)NOT_APPLICABLE,						/*允许最低工作温度	*/		\
	(u8)NOT_APPLICABLE,							/*使能过温保护		*/		\
	(u8)NOT_APPLICABLE,							/*温度报警滞回温度	*/		\
	(u16)NOT_APPLICABLE,						/*故障检测时间		*/		\
	(u16)NOT_APPLICABLE,						/*故障恢复时间		*/		\
	(u16)NOT_APPLICABLE							/*故障恢复时间		*/		\
}


typedef struct
{	
	s32		m_wStallPHCurrent;					//	堵转检测相电流			1 0.001A
	s32		m_wStallCurMax;						//	堵转检测转速最大值		1 0.001A
	s32		m_wStallCurMin;						//	堵转检测转速最小值		1 0.001A	
	s32		m_wStallSpeedFactor;				//  堵转检测转速设定值		1 IQ8
	s32		m_wStallIqCurrent;					//  堵转检测Iq设定值预留	0												
		
	u16		nStallDelaytime;					//	堵转检测延时时间	1
	u16		nStallDetectTime;					//	堵转故障检测时间	1
	u16		nStallRecoverTime;					//	堵转故障恢复时间	1
	u16		nStallRecvd;						//	预留				0

	s32		m_wEmptyCurrent;					//	空转检测电流		1
	s32		m_wEmptySpeed;						//	空转检测转速		1
	u16		nEmptyDetectTime;					//	空转故障检测时间	1
	u16		nEmptyRecoverTime;					//	空转故障恢复时间	1

	s32		m_wLosePhaseCurrent;				//  缺相电流检测设定值	1	
	u16 	nLossPHDetectTime;					//	缺相故障检测时间	1
	u16 	nLossPHRecoverTime;					//	缺相故障恢复时间	1

	u16 	nStartFaultDetectTime;				//	启动故障检测时间	1
	u16 	nStartClosedDetectTime;				//	启动闭环检测时间	1	
	u16 	nStartFaultRecoverTime;				//	启动故障恢复时间	1
	u16 	nReserved;							//	预留		1

	u8		bEmptyProtectEnable;				//	使能空转保护		1
	u8		bStallProtectEnable;				//	使能堵转保护		1
	u8		bStartProtectEnable;				//	使能启动保护		1
	u8		bLossPHProtectEnable;				//	使能缺相保护		1
	
}STR_FB_EMPTY_STALL;

#define EMPTY_STALL_PARA_TAB_M(ID)											\
{																			\
	(s32)(1000*I_PH_STALL_FAULT_M##ID),			/*堵转检测相电流	*/		\
	(s32)(1000*CUR_STALL_MAX_FAULT_M##ID),		/*堵转检测电流最大值*/		\
	(s32)(1000*CUR_STALL_MIN_FAULT_M##ID),		/*堵转检测电流最小值*/		\
	(s32)(256*SPEED_FAC_STALL_FAULT_M##ID),		/*堵转检测转速系数设定值*/	\
	(s32)(1000*IQ_STALL_FAULT_M##ID),			/*堵转检测Iq设定值	*/		\
	(u16)SPEED_STALL_DELAY_TIME_M##ID,			/*堵转检测延时时间	*/		\
	(u16)STALL_FAULT_DETECT_TIME_M##ID,			/*堵转故障检测时间	*/		\
	(u16)STALL_FAULT_RECOVER_TIME_M##ID,		/*堵转故障恢复时间	*/		\
	(u16)NOT_APPLICABLE,						/*堵转预留			*/		\
	(s32)(1000*I_PH_EMPTY_FAULT_M##ID),			/*空转检测电流		*/		\
	(s32)(100*SPEED_EMPTY_FAULT_M##ID),			/*空转检测转速		*/		\
	(u16)EMPTY_FAULT_DETECT_TIME_M##ID,			/*空转故障检测时间	*/		\
	(u16)EMPTY_FAULT_RECOVER_TIME_M##ID,		/*空转故障恢复时间	*/		\
	(s32)(1000*I_PHASE_LOSS_FAULT_M##ID),		/*缺相电流检测设定值*/		\
	(u16)LOSS_PH_FAULT_DETECT_TIME_M##ID,		/*缺相故障检测时间	*/		\
	(u16)LOSS_PH_FAULT_RECOVER_TIME_M##ID,		/*缺相故障恢复时间	*/		\
	(u16)START_DETECT_PERIOD_M##ID,				/*启动故障检测时间	*/		\
	(u16)START_DETECT_CLOSED_TIME_M##ID,		/*启动闭环检测时间	*/		\
	(u16)START_FAULT_RECOVER_TIME_M##ID,		/*启动故障恢复时间	*/		\
	(u16)NOT_APPLICABLE,						/*预留				*/		\
	(u8)EMPTY_PROTECTION_ENABLE_M##ID,			/*使能空转保护		*/		\
	(u8)STALL_PROTECTION_ENABLE_M##ID,			/*使能堵转保护		*/		\
	(u8)START_PROTECTION_ENABLE_M##ID,			/*使能启动保护		*/		\
	(u8)LOSS_PH_PROTECTION_ENABLE_M##ID			/*使能缺相保护		*/		\
}

#define EMPTY_STALL_PARA_TAB_RSVD_M(ID)										\
{																			\
	(s32)NOT_APPLICABLE,						/*堵转检测相电流	*/		\
	(s32)NOT_APPLICABLE,						/*堵转检测转速最大值*/		\
	(s32)NOT_APPLICABLE,						/*堵转检测转速最小值*/		\
	(s32)NOT_APPLICABLE,						/*堵转检测转速设定值*/		\
	(s32)NOT_APPLICABLE,						/*堵转检测Iq设定值	*/		\
	(u16)NOT_APPLICABLE,						/*堵转检测延时时间	*/		\
	(u16)NOT_APPLICABLE							/*堵转故障检测时间	*/		\
	(u16)NOT_APPLICABLE,						/*堵转故障恢复时间	*/		\
	(u16)NOT_APPLICABLE,						/*堵转预留			*/		\
	(s32)NOT_APPLICABLE,						/*空转检测电流		*/		\
	(s32)NOT_APPLICABLE,						/*空转检测转速		*/		\
	(u16)NOT_APPLICABLE,						/*空转故障检测时间	*/		\
	(u16)NOT_APPLICABLE,						/*空转故障恢复时间	*/		\
	(s32)NOT_APPLICABLE,						/*缺相电流检测设定值*/		\
	(u16)NOT_APPLICABLE,						/*缺相故障检测时间	*/		\
	(u16)NOT_APPLICABLE,						/*缺相故障恢复时间	*/		\
	(u16)NOT_APPLICABLE,						/*启动故障检测时间	*/		\
	(u16)NOT_APPLICABLE,						/*启动闭环检测时间	*/		\
	(u16)NOT_APPLICABLE,						/*启动故障恢复时间	*/		\
	(u16)NOT_APPLICABLE,						/*使能启动保护		*/		\
	(u8)NOT_APPLICABLE,							/*使能空转保护		*/		\
	(u8)NOT_APPLICABLE,							/*使能堵转保护		*/		\
	(u8)NOT_APPLICABLE,							/*使能启动保护		*/		\
	(u8)NOT_APPLICABLE							/*使能缺相保护		*/		\
}




//////////////////////////////////////////////////////////////////////
////////////////////AC SENSOR UNIT para   /////////////////////////////////////

typedef struct
{
	s32		m_wACUndVoltage;					//	最小值(低压报警监测值)	1
	s32		m_wACOvVoltage;						//	最大值(高压报警监测值)	1
	s32		m_wAcRateVoltage;					//	额定值	1
	s32		m_wACVolShuntRatio;					//	电压检测放大倍数	1
	s32		m_wAdcSupplyVol;					//	AD参考电压	1
	u16		nACRateFreq;						//  AC额定频率	1
	s8		bACFreqDectEnable;					//	使能频率检测	1
	s8		HysterFreq;							//	允许频率偏差范围	1	
}STR_FB_AC_UNIT0;

#define AC_UNIT0_PARA_TAB_M(ID)												\
{																			\
	(s32)NOT_APPLICABLE,						/*最小值			*/		\
	(s32)NOT_APPLICABLE,						/*最大值			*/		\
	(s32)NOT_APPLICABLE,						/*额定值			*/		\
	(s32)NOT_APPLICABLE,						/*电压检测放大倍数	*/		\
	(s32)NOT_APPLICABLE,						/*AD参考电压		*/		\
	(u16)NOT_APPLICABLE,						/*AC额定频率		*/		\
	(u8)NOT_APPLICABLE,							/*使能频率检测		*/		\
	(u8)NOT_APPLICABLE							/*允许频率偏差范围	*/		\
}

#define AC_UNIT0_PARA_TAB_RSVD_M(ID)										\
{																			\
	(s32)NOT_APPLICABLE,						/*最小值			*/		\
	(s32)NOT_APPLICABLE,						/*最大值			*/		\
	(s32)NOT_APPLICABLE,						/*额定值			*/		\
	(s32)NOT_APPLICABLE,						/*电压检测放大倍数	*/		\
	(s32)NOT_APPLICABLE,						/*AD参考电压		*/		\
	(u16)NOT_APPLICABLE,						/*AC额定频率		*/		\
	(u8)NOT_APPLICABLE,							/*使能频率检测		*/		\
	(u8)NOT_APPLICABLE							/*允许频率偏差范围	*/		\
}

typedef struct
{
	s32		m_wACUndVoltage;						//	最小值(低压报警监测值)	1
	s32		m_wACOvVoltage;						//	最大值(高压报警监测值)	1
	s32		m_wAcRateVoltage;						//	额定值	1
	s32		m_wACVolShuntRatio;					//	电压检测放大倍数	1
	s32		m_wAdcSupplyVol;						//	AD参考电压	1
	u16		nACRateFreq;						//  AC额定频率	1
	s8		bACFreqDectEnable;					//	使能频率检测	1
	s8		HysterFreq;							//	允许频率偏差范围	1	
	
	u16		nACOvVoltTime;						//	过压检测时间	1
	u16		nACUndVoltTime;						//	低压检测时间	1
	u16		nACVoltRecoverTime;					//	电压恢复正常等待时间	1
	s8		bACOvVoltDectEnable;				//  使能过压保护	1
	s8		bACUndVoltDectEnable;				//	使能低压保护	1
}STR_FB_AC_UNIT1;

#define AC_UNIT1_PARA_TAB_M(ID)												\
{																			\
	(s32)NOT_APPLICABLE,						/*最小值			*/		\
	(s32)NOT_APPLICABLE,						/*最大值			*/		\
	(s32)NOT_APPLICABLE,						/*额定值			*/		\
	(s32)NOT_APPLICABLE,						/*电压检测放大倍数	*/		\
	(s32)NOT_APPLICABLE,						/*AD参考电压		*/		\
	(u16)NOT_APPLICABLE,						/*AC额定频率		*/		\
	(u8)NOT_APPLICABLE,							/*使能频率检测		*/		\
	(u8)NOT_APPLICABLE							/*允许频率偏差范围	*/		\
	(u16)NOT_APPLICABLE,						/*过压检测时间		*/		\
	(u16)NOT_APPLICABLE,						/*低压检测时间		*/		\
	(u16)NOT_APPLICABLE,						/*电压恢复正常等待时间*/	\
	(u8)NOT_APPLICABLE,							/*使能过压保护		*/		\
	(u8)NOT_APPLICABLE							/*使能低压保护		*/		\
}

#define AC_UNIT1_PARA_TAB_RSVD_M(ID)										\
{																			\
	(s32)NOT_APPLICABLE,						/*最小值			*/		\
	(s32)NOT_APPLICABLE,						/*最大值			*/		\
	(s32)NOT_APPLICABLE,						/*额定值			*/		\
	(s32)NOT_APPLICABLE,						/*电压检测放大倍数	*/		\
	(s32)NOT_APPLICABLE,						/*AD参考电压		*/		\
	(u16)NOT_APPLICABLE,						/*AC额定频率		*/		\
	(u8)NOT_APPLICABLE,							/*使能频率检测		*/		\
	(u8)NOT_APPLICABLE							/*允许频率偏差范围	*/		\
	(u16)NOT_APPLICABLE,						/*过压检测时间		*/		\
	(u16)NOT_APPLICABLE,						/*低压检测时间		*/		\
	(u16)NOT_APPLICABLE,						/*电压恢复正常等待时间*/	\
	(u8)NOT_APPLICABLE,							/*使能过压保护		*/		\
	(u8)NOT_APPLICABLE							/*使能低压保护		*/		\
}



//////////////////////////////////////////////////////////////////////

#define DRV_CFG_GLOBAL_PARA_TAB									\
{																\
	(u8)PARA_CFG_HEADER,			/* 文件头			*/		\
	(u8)PARA_CFG_MAIN_VERSION,		/* 主版本			*/		\
	(u8)PARA_CFG_VERSION,			/* 版本				*/		\
	(u8)PARA_CFG_SUB_VERSION,		/* 子版本			*/		\
	(u8)0x00,						/* 大小端			*/		\
	(u8)NOT_APPLICABLE,				/* 预留				*/		\
	(u8)PARA_CFG_LENGTH,			/* 长度				*/		\
	(u8)PARA_CFG_NUMBER				/* 参数组个数		*/		\
}

////////////////////FB block package /////////////////////////////////////
typedef struct
{
	u8 header;						// 文件头
	u8 mainVersion;					// 主版本
	u8 version;						// 版本
	u8 subversion;					// 子版本
	u8 dataFormat;					// 大小端
	u8 reserved;					// 预留
	u8 length;						// 长度
	u8 objNumber;					// 参数组个数	
}STR_DrvCfgGlobal, *PSTR_DrvCfgGlobal;


typedef const struct
{
	STR_GlobalCfg			mS_GlobalCfg;
	STR_BoardParameter		mS_Boardpara;
	STR_MotorParameter		mS_Motorpara;
	STR_FB_SLVC_CFG0		mS_FBSlvcCfg0;
	STR_FB_CUR_LOOP			mS_FBCurLoop;
	STR_FB_SPD_LOOP			mS_FBSpdLoop;
	STR_FB_POWER_LOOP		mS_FBPwrLoop;
	STR_FB_DIR_CHECK		mS_FBDirCheck;
	STR_FB_IPD				mS_FBIPD;
	STR_FB_ALLIGN			mS_FBAllign;
	STR_FB_VF				mS_FBVF;
	STR_FB_DC_UNIT0			mS_FBDcUnit0;
	STR_FB_CUR_SENSE_UNIT	mS_FBCurSense;
	STR_FB_TEMPER_NTC_UNIT	mS_FBTempNTC;
	STR_FB_EMPTY_STALL		mS_FBEmptyStall;
}STR_DrvCfgPara, *PSTR_DrvCfgPara;

#define DRV_CFG_PARA_TAB_M(ID)											\
{																		\
	GLOBAL_CFG_TAB_M(ID),												\
	BOARD_PARAMETER_TAB_M(ID),											\
	MOTOR_PARAMETER_TAB_M(ID),											\
	SLVC0_PARAMETER_TAB_M(ID),											\
	CURLOOP_PARAMETER_TAB_M(ID),										\
	SPDLOOP_PARAMETER_TAB_M(ID),										\
	PWRLOOP_PARAMETER_TAB_M(ID),										\
	DIR_CHECK_PARAMETER_TAB_M(ID),										\
	IPD_PARAMETER_TAB_M(ID),											\
	ALLIGN_PARAMETER_TAB_M(ID),											\
	VF_START_PARAMETER_TAB_RSVD_M(ID),									\
	DC_UNIT0_PARAMETER_TAB_M(ID),										\
	CUR_SENSOR_PARA_TAB_M(ID),											\
	TEMPER_NTC_PARA_TAB_RSVD_M(ID),										\
	EMPTY_STALL_PARA_TAB_M(ID)											\
}

/*---------------------------------------------------------------------------*/

#endif

