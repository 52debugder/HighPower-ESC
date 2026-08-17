/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： USER_usrApp.c
 * 文件标识：
 * 内容摘要： UA 用户函数文件
 * 其它说明： 用户的程序可以在该文件添加
 * 当前版本： V1.0
 * 作    者： Tonghua Li
 * 完成日期： 2023年03月29日
 *
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "PubData_MA_UA.h"
#include "MC_Math.h"
#include "MC_type.h"
#include "Time_Process.h"
#include "UA_Data.h"
#include "PubData_DriverInstance.h" 
#include "string.h"



/*******************************************************************************/
//全局变量定义区


/*******************************************************************************/
//外部函数引用区


/*******************************************************************************/
//局部静态函数定义区

/*******************************************************************************/
//局部静态变量定义区
extern STR_UACtrProc	sS_UACtrlProc[UA_OBJ_MAX_DEFINE];


#ifdef UA_DEBUG
volatile bool runM0UaCmd = FALSE;
bool runM0UaCmdAuto = FALSE;
volatile s32 runM0SpdSetpoint = 50*100;
s16 runM0Period = 0;

bool runM1UaCmd = FALSE;
bool runM1UaCmdAuto = FALSE;
s32 runM1SpdSetpoint = 100*100;
s16 runM1Period = 0;

/*******************************************************************************
 函数名称：    void updateM0DebugUA(pSTR_UACtrProc pObj)
 功能描述：    UA控制命令，用户可以在此函数下编写控制逻辑，
               通过UA指令的修改逐层下发到MD层实现电机控制
 输入参数：    pSTR_UACtrProc pObj
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 2022/3/29      V1.1           Tonghua Li          更新
 *******************************************************************************/

void updateM0DebugUA(pSTR_UACtrProc pObj)
{
/**************定时自动启停功能***************/		
	if(runM0UaCmdAuto)
	{
		runM0Period++;
		if(runM0Period >= 10000)
		{
			if(runM0UaCmd == FALSE)
			{
				runM0UaCmd = TRUE;
			}
			else
			{
				runM0UaCmd = FALSE;
			}
			runM0Period = 0;
		}
	}
	else
	{
		runM0Period	= 0;
	}
/**************定时自动启停功能***************/

	
	pObj->m_wSetpoint					= runM0SpdSetpoint;  //转速设定值
	
	if(runM0UaCmd)                                 //UA层启动控制标志置1
	{
		pObj->m_StruCmd.m_bMoeEnable	= 1;
		pObj->m_StruCmd.m_bRunFlag		= 1;
	}
	else                                          //UA层启动控制标志置0
	{
		pObj->m_StruCmd.m_bMoeEnable	= 0;
		pObj->m_StruCmd.m_bRunFlag		= 0;
	}

	if(pObj->m_StruCmd.m_bDownLoadStart == 1)     //程序下载期间运行标志清0
	{
		pObj->m_StruCmd.m_bMoeEnable	= 0;
		pObj->m_StruCmd.m_bRunFlag		= 0;
	}
}

/*******************************************************************************
 函数名称：    void updateM1DebugUA(pSTR_UACtrProc pObj)
 功能描述：    UA控制命令，用户可以在此函数下编写控制逻辑，
               通过UA指令的修改逐层下发到MD层实现电机控制
 输入参数：    pSTR_UACtrProc pObj
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 2022/3/29      V1.1           Tonghua Li          更新
 *******************************************************************************/
void updateM1DebugUA(pSTR_UACtrProc pObj)
{
/**************定时自动启停功能***************/
	if(runM1UaCmdAuto)
	{
		runM1Period++;
		if(runM1Period >= 10000)
		{
			if(runM1UaCmd == FALSE)
			{
				runM1UaCmd = TRUE;
			}
			else
			{
				runM1UaCmd = FALSE;
			}
			runM1Period = 0;
		}
	}
	else
	{
		runM1Period	= 0;
	}
/**************定时自动启停功能***************/
	
	
	pObj->m_wSetpoint					= runM1SpdSetpoint;    //转速设定值
	
	if(runM1UaCmd)                                   //UA层启动控制标志置1
	{
		pObj->m_StruCmd.m_bMoeEnable	= 1;
		pObj->m_StruCmd.m_bRunFlag		= 1;
	}
	else                                            //UA层启动控制标志置0
	{
		pObj->m_StruCmd.m_bMoeEnable	= 0;
		pObj->m_StruCmd.m_bRunFlag		= 0;
	}
}

#endif

/*******************************************************************************
 函数名称：    void updateUASetpoint(pSTR_UACtrProc pObj)
 功能描述：    单电机UA指令处理函数
 输入参数：    pSTR_UACtrProc pObj
 输出参数：    无
 返 回 值：    无
 其它说明：		用户可根据需要添加相应的处理函数或者处理方式
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 2022/3/29      V1.1           Tonghua Li          更新
 *******************************************************************************/
void updateUASetpoint(pSTR_UACtrProc pObj)
{	
	PSTR_DrvCfgPara	pDrvCfgPara = pObj->mg_pCtrlObj->m_pDrvCfgPara;
	
	#if (DRV0_CLOSE_LOOP == SPEED_LOOP)			//速度环

	#if (DRV0_POWER_LIMIT_STATUS == TRUE)		//速度环限功率
		pObj->m_wSetpoint		= pDrvCfgPara->mS_FBSpdLoop.m_wPowerLmtSpdValue;
		pObj->m_wPowerSetpoint	= pDrvCfgPara->mS_FBSpdLoop.m_wPowerLmtValue;
		#endif
		
	pObj->m_wTqSetpoint = pDrvCfgPara->mS_FBCurLoop.m_wIqSet;

	#elif (DRV0_CLOSE_LOOP == CURRENT_LOOP)		//电流环
	pObj->m_wTqSetpoint = pDrvCfgPara->mS_FBCurLoop.m_wIqSet;
	
	#elif (DRV0_CLOSE_LOOP == POWER_LOOP)		//功率环
	
		#if(DRV0_SPPED_LIMIT_STATUS == TRUE)   //功率环限速度
		pObj->m_wPowerSetpoint	= pDrvCfgPara->mS_FBPwrLoop.m_wLmdSpdPowerSetting;
		pObj->m_wSetpoint		= pDrvCfgPara->mS_FBPwrLoop.m_wSpdLmtValue;
		#else
		pObj->m_wPowerSetpoint	= pDrvCfgPara->mS_FBPwrLoop.m_wPowerSetting;
		#endif
		
	pObj->m_wTqSetpoint = pDrvCfgPara->mS_FBCurLoop.m_wIqSet;
	#endif
	
	pObj->mUaToMa.wFreqCmd		= pObj->m_wSetpoint;            //转速指令设定
	pObj->mUaToMa.wPowerCmd 	= pObj->m_wPowerSetpoint;       //功率指令设定
	pObj->mUaToMa.wTorqCmd		= pObj->m_wTqSetpoint;          //电流指令设定
}

/*******************************************************************************
 函数名称：    void getGearRatio4UA(pSTR_UACtrProc pObj)
 功能描述：    UA指令处理函数，传递传动比系数（预留）
 输入参数：    pSTR_UACtrProc pObj
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 2022/3/29      V1.1           Tonghua Li          更新
 *******************************************************************************/
s16 getGearRatio4UA(pSTR_UACtrProc pObj)
{
	return 200;	
}

/*******************************************************************************
 函数名称：    ENUM_MotorBrakeMode getBrakeMode4UA(pSTR_UACtrProc pObj)
 功能描述：    单电机UA刹车指令处理函数
 输入参数：    pSTR_UACtrProc pObj
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 2022/3/29      V1.1           Tonghua Li          更新
 *******************************************************************************/
ENUM_MotorBrakeMode getBrakeMode4UA(pSTR_UACtrProc pObj)
{
	#if (DRV0_STOP_MODE == 1)
		return E_STOP_ZERO_CUR;    //零电流关断
	#elif (DRV0_STOP_MODE == 2)
		return E_STOP_SHORT;       //下桥臂短接
	#else
		return E_STOP_MOE_OFF;     //MOE关断
	#endif	
}


/*******************************************************************************
 函数名称：    ENUM_MotorBrakeMode getFaultBrakeMode4UA(pSTR_UACtrProc pObj)
 功能描述：    UA故障指令处理函数
 输入参数：    pSTR_UACtrProc pObj
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 2022/3/29      V1.1           Tonghua Li          更新
 *******************************************************************************/
ENUM_MotorBrakeMode getFaultBrakeMode4UA(pSTR_UACtrProc pObj)
{
	return getBrakeMode4UA(pObj);
}

/*******************************************************************************/
/*****************************end***********************************************/

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */



