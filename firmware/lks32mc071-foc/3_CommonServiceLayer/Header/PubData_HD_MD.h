
/*硬件驱动层--电机驱动层*/

#ifndef _PUBDATA_HD_MD_H_
#define _PUBDATA_HD_MD_H_

#include "basic.h"
#include "MC_type.h"
#include "project_config.h"


typedef enum{
	E_PHASE_A_B = 0,
	E_PHASE_B_C = 1,
	E_PHASE_A_C = 2,
	E_PHASE_UNUSED
}ENU_ADChannelCFG;					//	三电阻采样通道配置


typedef struct {
	uint16_t  nuTimePhAN;
	uint16_t  nuTimePhA;
	uint16_t  nuTimePhBN;
	uint16_t  nuTimePhB;
	uint16_t  nuTimePhC;
	uint16_t  nuTimePhCN;
}STR_McpwmCmpr,*PSTR_McpwmCmpr;		//	MCPWM 比较值


typedef struct {
	uint16_t  			nuPoint0;	//采样点0
	uint16_t  			nuPoint1;	//采样点1
	ENU_ADChannelCFG	eChannel;	//通道配置
}STR_McpwmTmr,*PSTR_McpwmTmr;		//	AD采样点及通道


typedef struct {	
	STR_McpwmTmr		mMcTmr;		//采样点配置
	STR_McpwmCmpr		mMcPwm;		//PWM宽度
}STR_PubDatMDHD;						// MD 到 HD数据交互信息


typedef struct {
	bool	bBreakInStatus;		// 是否存在过流
	
	int16_t nSampCurDat0;		//电流采样值0
	int16_t nSampCurDat1;		//电流采样值1
	
	int16_t nPhaseUOffset;		//U相电流偏置
	int16_t nPhaseVOffset;		//V相电流偏置
	int16_t nPhaseWOffset;		//W相电流偏置
	int16_t nBusShuntOffset;	//母线电流偏置
	
	int16_t nDcVolAdcDat;		//母线采样值  	

	int16_t nSampDatU;			// iu			
	int16_t nSampDatV;			// iv
	int16_t nSampDatW;			// iw

	/*反电动势检测*/  			//条件编译
	
	
	int16_t nNTCVolAdcDat;		//NTC采样值
	#if (DRV0_BEMF_CHECK_EABLE==FUNCTION_ON)
	int16_t nBmefUVolAdcDat;	//U反电势
	int16_t nBmefVVolAdcDat;	//V反电势
	int16_t nBmefWVolAdcDat;	//W反电势
	int16_t nBmefUOffset;		//U相反电势电压偏置
	int16_t nBmefVOffset;		//V相反电势电压偏置
	int16_t nBmefWOffset;		//W相反电势电压偏置
	#endif	
}STR_PubDatHDMD;				//	HD到MD数据交互信息结构体

//定义MD ---->HD 驱动调用函数接口 
typedef struct{
	void (*AcquireCurrent)(STR_PubDatHDMD* tS_pCurAdcRes);	//电流采样函数指针
	void (*AcquireVdc)(STR_PubDatHDMD* tS_pCurAdcRes);		//母线采样函数指针
	void (*AcquireNTC)(STR_PubDatHDMD* tS_pAdcRes);			//NTC采样函数指针
	void (*AcquireBemf)(STR_PubDatHDMD* tS_pAdcRes);		//反电势采样函数指针
	void (*AD_ChannelUpdate)(STR_PubDatMDHD* tS_pMdToHd);	//AD采样通道更新函数指针
	void (*MCPWMx_RegUpdate)(STR_PubDatMDHD* tS_pMdToHd);	//PWM脉宽更新函数指针
	void (*PwmOutEnable)(FuncState t_state);				//MOE操作函数指针
	void (*PwmCharge)(u8 t_bphaseABC);						//预充电操作函数指针
	void (*InitPwmChargeEnd)(void);							//预充电操作结束初始化函数指针
	void (*GetEPWMBreakIn)(STR_PubDatHDMD* tS_pHd2Md);		//读取Breakin函数指针
	void (*ClrEPWMBreakIn)(void);							//清除Breakin函数指针
}STR_HALDrvHandle,*PSTR_HALDrvHandle;		//	硬件驱动函数指针


#endif // _PUBDATA_HD_MD_H_
/////////////////////

