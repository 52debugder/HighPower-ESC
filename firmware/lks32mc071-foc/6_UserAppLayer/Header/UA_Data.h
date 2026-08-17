/*******************************************************************************
 * 版权所有 (C)2022, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： UA_Data.h
 * 文件标识：
 * 内容摘要： UA_Data
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： Tonghua Li
 * 完成日期： 2022年8月25日
 *******************************************************************************/
 
/*------------------------------prevent recursive inclusion -------------------*/ 
#ifndef __UA_DATA_H__
#define __UA_DATA_H__

#include "basic.h"
#include "PubData_MA_UA.h"
#include "MC_Math.h"
#include "MC_type.h"
#include "Time_Process.h"
#include "PubData_DriverInstance.h" 
#include "string.h"


#define UA_DEBUG


#define UA_OBJ_MAX_DEFINE	(PLANTFORM_DRV_MODULE_NUM)
#define UA_CFG_DONT_USED	(TRUE)

typedef enum
{
    E_UA_INIT			= 0,	/* UA状态机初始状态 */ 
    E_UA_STOP			= 1,	/* UA状态机停止状态 */
    E_UA_RUN			= 2,	/* UA状态机运行状态 */
    E_UA_FAULT			= 3,	/* UA状态机故障状态 */    
    E_UA_ILLG			= 4		/* UA状态机非法状态	*/     
} ENUM_UACtrlState;


typedef struct
{
	u8 m_bRunFlag		:1;		/* UA 运行命令标志*/
	u8 m_bDirRevse		:1;		/* 方向取反命令标志*/
	u8 m_bFault			:1;		/* UA 故障标志*/
	u8 m_bFaultClr		:1;		/* UA 故障清除命令*/
	u8 m_bMoeEnable		:1;		/* MOE 使能标志*/
	u8 m_bDownLoadStart	:1;		/* 开始下载*/

	u8 m_bResvd			:2;
}STR_UA_CtrCMD,*pSTR_UA_CtrCMD;


typedef struct
{
	// 绑定的控制对象
	u8						mg_nUACtrlProcID;	/*当前UA控制对象 ID*/
	PSTR_ControlObject		mg_pCtrlObj;		/*控制对象*/

	// 内部交换信息存储及刷新
	STR_PubDatUAMA 			mUaToMa;
	STR_PubDatMAUA			mMaToUa;

	ENUM_UACtrlState		m_eUASysState;		/* 当前UA运行状态机 */
	STR_UA_CtrCMD			m_StruCmd;

	u8						m_bStopMode;		/*电机停止模式*/
	u8						m_bPWMStopMode;
	u8						m_bLoopMode;		/*运行模式*/

	s32						m_wSetpoint;		// 负值为反向 0.01Hz
	s32						m_wTqSetpoint;		// 负值为反向 0.001A
	s32						m_wPowerSetpoint;	// 0.01W

	u8						m_bFaultAutoClr;
	u16						m_nuFaultClrCnt;	/*故障清除计数*/
	u16						m_nuFaultClrPeriod;	/*故障清除周期*/
}STR_UACtrProc, *pSTR_UACtrProc;

#endif  /* __UA_DATA_H__*/

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* -----------------------------------END OF FILE------------------------------- */

