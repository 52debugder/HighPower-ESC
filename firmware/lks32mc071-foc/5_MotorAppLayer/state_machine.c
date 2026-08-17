/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： state_machine.c
 * 文件标识：
 * 内容摘要： state machine，状态机管理及状态机函数调用，以及接口数据维护
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： Tonghua Li
 * 完成日期： 2022年08月19日
 *
 *******************************************************************************/
#include "state_machine.h"
#include "MA_Static_Variable.h"
#include "Time_Process.h"
#include "MC_Math.h"
#include "string.h"

/*******************************************************************************/
//全局变量定义区


/*******************************************************************************/
//外部函数引用区

extern void MotorFaultMain(STR_MACtrProc *pObj);					//	电机故障控制函数
extern bool InitDriverMain(STR_MACtrProc *pObj);					//	驱动初始化处理函数
extern bool PowerOnOffDriverMain(STR_MACtrProc *pObj, bool t_bOn);	//	功率板上下电处理函数
extern bool StopMotorMain(STR_MACtrProc *pObj);						//	电机stop状态处理函数
extern void ChargeDriverMain(STR_MACtrProc *pObj);					//	功率板预充电函数
extern void MotorTrakingMain(STR_MACtrProc *pObj);					//	顺逆风检测函数 
extern void MotorTracking2Run(STR_MACtrProc *pObj);					//	电机顺逆风检测后运行函数
extern void MotorTracking2Brake(STR_MACtrProc *pObj);				//	电机顺逆风检测后制动函数
extern void MotorIPDMain(STR_MACtrProc *pObj);						//	电机初始位置检测函数
extern void MotorAlignMain(STR_MACtrProc *pObj);					//	电机对相函数
extern void MotorCloseMain(STR_MACtrProc *pObj);					//	电机run状态处理程序
extern void MotorBreakMain(STR_MACtrProc *pObj);					//	电机制动控制函数
extern void MotorFaultMain(STR_MACtrProc *pObj);					//	电机故障控制函数
extern bool MotorInitIPDMain(STR_MACtrProc *pObj);					//	电机初始位置检测初始化函数
extern void updateMAInfo2UALocal(STR_MACtrProc *pObj);				//	MA信息到UA层更新函数


extern	void ActionMainRelayOn(void);								//	继电器闭合函数
extern  void ActionMainRelayOff(void);								//	继电器断开函数
extern  void setInitAcrParaReq(STR_MACtrProc *pObj);				//	设置电流环初始化请求函数

extern	void BrakeStateCheckInit(u32 t_CurrentSqrt,pSTR_OnTheFlyDetectMA this);
																	//	制动状态检测初始化函数


/*******************************************************************************/
//局部静态函数定义区

/*******************************************************************************/
//局部静态变量定义区


/*******************************************************************************/
/*****************************end***********************************************/

/*******************************************************************************
 函数名称：  GetUA2MACmd(STR_MACtrProc *pObj)
 功能描述：    获取电机运行控制字
 设计思路：    1.从UA to MA 的数据结构中获取运行控制字
 操作的表：    无
 输入参数：    STR_MACtrProc *pObj ------结构体指针
 输出参数：    电机运行当前控制字
 返 回 值：    电机运行当前控制字
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
ENUM_MotorCmdWord GetUA2MACmd(STR_MACtrProc *pObj)
{
	return pObj->mUaToMa.eAppCmd;
}
/*******************************************************************************
 函数名称：  static bool	IsMotorRunCmd(STR_MACtrProc *pObj)
 功能描述：    判断电机是否运行
 设计思路：    1.判断运行标志且UA层下发启动命令
 操作的表：    无
 输入参数：    STR_MACtrProc *pObj ------结构体指针
 输出参数：    bool  True：电机启动运行 False： 电机未运行
 返 回 值：    bool  True：电机启动运行 False： 电机未运行
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
static bool	IsMotorRunCmd(STR_MACtrProc *pObj)
{
			// m_bUAMOE使能且m_bMC_RunFlg有效时，允许电机运行
	return (pObj->m_SMACtrlBit.m_bMC_RunFlg == 1) && (pObj->m_SMACtrlBit.m_bUAMOE == 1);
}
/*******************************************************************************
 函数名称：  static bool	IsPOSTFinish(STR_MACtrProc *pObj)
 功能描述：    判断电机定位是否完成
 设计思路：    1.判断运行标志且UA层下发启动命令
 操作的表：    无
 输入参数：    STR_MACtrProc *pObj ------结构体指针
 输出参数：    bool  True：post完成 False： post未完成
 返 回 值：    bool  True：post完成 False： post未完成
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
static bool	IsPOSTFinish(STR_MACtrProc *pObj)
{
	return (pObj->m_SMACtrlBit.m_bPostOK == 1);				//	TRUE : 上电 完成
}
/*******************************************************************************
 函数名称：  static bool WaitPowerOnFinish(STR_MACtrProc *pObj)
 功能描述：    判断上电是否完成
 设计思路：    1.判断vdc值 是否大于等于欠压恢复值
 操作的表：    无
 输入参数：    STR_MACtrProc *pObj ------结构体指针
 输出参数：    bool  True：post完成 False： post未完成
 返 回 值：    bool  True：post完成 False： post未完成
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
static bool WaitPowerOnFinish(STR_MACtrProc *pObj)
{
	s16 t_nVdc;
	PSTR_DrvCfgPara			t_pDrvCfgPara = pObj->mg_pCtrlObj->m_pDrvCfgPara; 
	STR_TransCoefElement 	*pAppToCore	= &(pObj->mg_pCtrlObj->mTransCoef.mAppToCore);
	
	//判断当前电压是否大于低压报警恢复值
	t_nVdc = App2CoreVoltTrans(pAppToCore,t_pDrvCfgPara->mS_FBDcUnit0.m_wDCUnderVoltageRecover);
	return (pObj->mMdToMa.nVdc >= t_nVdc);
}

/*******************************************************************************
 函数名称：  static bool IsDriveChargeFinish(STR_MACtrProc *pObj)
 功能描述：    判断预充电是否完成
 设计思路：    1.判断预充电结束标志
 操作的表：    无
 输入参数：    STR_MACtrProc *pObj ------结构体指针
 输出参数：    bool  True：预充电完成 False： 预充电未完成
 返 回 值：    bool  True：预充电完成 False： 预充电未完成
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
static bool IsDriveChargeFinish(STR_MACtrProc *pObj)
{
	return (pObj->m_pAppCommData->bChargeEndFlag == 4);		//	TRUE : 预充电过程 完成
}
// Check if calib finish
#if 0
static bool IsCalibDriveFinish(STR_MACtrProc *pObj)
{
	return (pObj->m_SMACtrlBit.m_bCalibFinish);
}
#endif
/*******************************************************************************
 函数名称：  static bool	IsFaultExists(STR_MACtrProc *pObj)
 功能描述：    判断故障是否存在
 设计思路：    1.判断故障标志
 操作的表：    无
 输入参数：    STR_MACtrProc *pObj ------结构体指针
 输出参数：    bool  True：故障存在 False： 故障不存在
 返 回 值：    bool  True：故障存在 False： 故障不存在
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
static bool	IsFaultExists(STR_MACtrProc *pObj)
{
					// m_bUAFault 	: UA层故障标志
					// mg_UFault.R	: MA层故障信息
	return ((pObj->mg_UFault.R!= 0) || (pObj->m_SMACtrlBit.m_bUAFault == 1));
}

// motor info function
/*******************************************************************************
 函数名称：  static void	SetMotorInfoSubStatus(STR_MACtrProc *pObj, ENU_MOTOR_INFO_STATE status)
 功能描述：    设定下一级状态
 设计思路：    
 操作的表：    无
 输入参数：    	STR_MACtrProc *pObj ------结构体指针 
 				ENU_MOTOR_INFO_STATE status ------设定的状态
 输出参数：    无
 返 回 值：    无
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
static void	SetMotorInfoSubStatus(STR_MACtrProc *pObj, ENU_MOTOR_INFO_STATE status)
{
	pObj->m_eMotorInfoState	= status;
}
/*******************************************************************************
 函数名称：  static ENU_MOTOR_INFO_STATE	GetMotorInfoSubStatus(STR_MACtrProc *pObj)
 功能描述：   获取电机设定的状态
 设计思路：    
 操作的表：    无
 输入参数：    STR_MACtrProc *pObj ------结构体指针 
 输出参数：    ENU_MOTOR_INFO_STATE status ------设定的状态
 返 回 值：    ENU_MOTOR_INFO_STATE status ------设定的状态
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
static ENU_MOTOR_INFO_STATE	GetMotorInfoSubStatus(STR_MACtrProc *pObj)
{
	return pObj->m_eMotorInfoState;
}
/*******************************************************************************
 函数名称：  static bool	IsNeedTracking(STR_MACtrProc *pObj)
 功能描述：   是否需要顺逆风
 设计思路：    
 操作的表：    无
 输入参数：    STR_MACtrProc *pObj ------结构体指针 
 输出参数：    无
 返 回 值：    bool True：顺逆风使能 
 					False：顺逆风关闭
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
static bool	IsNeedTracking(STR_MACtrProc *pObj)
{
	return pObj->m_SMACtrlBit.m_bNeedTracking;		//	TRUE : 需要顺逆风检测
}
/*******************************************************************************
 函数名称：  bool	IsNeedIPD(STR_MACtrProc *pObj)
 功能描述：   是否需要脉冲注入
 设计思路：    
 操作的表：    无
 输入参数：    STR_MACtrProc *pObj ------结构体指针 
 输出参数：    无
 返 回 值：    bool True：脉冲注入(IPD检测)使能 
 					False：脉冲注入(IPD检测)关闭
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
bool	IsNeedIPD(STR_MACtrProc *pObj)
{
	return pObj->m_SMACtrlBit.m_bNeedIPD;			//	TRUE : 需要IPD
}
/*******************************************************************************
 函数名称：  static bool	IsIPDFinish(STR_MACtrProc *pObj)
 功能描述：   脉冲输入是否完成
 设计思路：    
 操作的表：    无
 输入参数：    STR_MACtrProc *pObj ------结构体指针 
 输出参数：    无
 返 回 值：    bool True：脉冲注入(IPD检测)完成 
 					False：脉冲注入(IPD检测)未完成
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
static bool	IsIPDFinish(STR_MACtrProc *pObj)
{
	return pObj->m_SMACtrlBit.m_bIPDFinish;			//	TRUE : IPD过程 完成
}

// motor Align function
/*******************************************************************************
 函数名称：  static bool	IsNeedAllign(STR_MACtrProc *pObj)
 功能描述：   是否需要对相
 设计思路：    
 操作的表：    无
 输入参数：    STR_MACtrProc *pObj ------结构体指针 
 输出参数：    无
 返 回 值：    bool True：需要对相 
 					False：不需要对相
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
static bool	IsNeedAllign(STR_MACtrProc *pObj)
{
	return pObj->m_SMACtrlBit.m_bNeedAlign;			//	TRUE : 需要ALLIGN
}
/*******************************************************************************
 函数名称：  static bool	IsAllignFinish(STR_MACtrProc *pObj)
 功能描述：   对相是否完成
 设计思路：    
 操作的表：    无
 输入参数：    STR_MACtrProc *pObj ------结构体指针 
 输出参数：    无
 返 回 值：    bool True：对相完成 
 					False：对相未完成
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
static bool	IsAllignFinish(STR_MACtrProc *pObj)
{
	return pObj->m_SMACtrlBit.m_bAlignFinish;		//	TRUE : ALLIGN过程 完成
}

// motor brake function
/*******************************************************************************
 函数名称：  static bool	IsCanRestore2Run(STR_MACtrProc *pObj)
 功能描述：   是否能重新启动
 设计思路：    
 操作的表：    无
 输入参数：    STR_MACtrProc *pObj ------结构体指针 
 输出参数：    无
 返 回 值：    bool True：可以恢复启动 
 					False：不能恢复启动
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
static bool	IsCanRestore2Run(STR_MACtrProc *pObj)
{
				// 可添加相应的代码进行是否需要重复恢复运行的处理
				// 返回 TRUE 表示可以恢复运行
	#if (DRV0_STOP_MODE == 1)
		return TRUE;
	#else
		return FALSE;
	#endif
}

// Fault handle
/*******************************************************************************
 函数名称：  static bool	IsFaultClrCmd(STR_MACtrProc *pObj)
 功能描述：   故障是否清零
 设计思路：    
 操作的表：    无
 输入参数：    STR_MACtrProc *pObj ------结构体指针 
 输出参数：    无
 返 回 值：    bool True：有故障清零指令
 					False：没有故障清零指令
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
static bool	IsFaultClrCmd(STR_MACtrProc *pObj)
{
					//UA层不存在报警且发送报警清除命令时，MA层可得到清除报警命令
	return (pObj->m_SMACtrlBit.m_bUAFaultClr == 1) && (pObj->m_SMACtrlBit.m_bUAFault == 0);

}
/*******************************************************************************
 函数名称：  static bool IsBreakInClrReq(STR_MACtrProc *pObj)
 功能描述：   是否有BREAK_IN清除请求
 设计思路：    
 操作的表：    无
 输入参数：    STR_MACtrProc *pObj ------结构体指针 
 输出参数：    无
 返 回 值：    	True：有BREAK_IN清除请求 
 				False：没有BREAK_IN清除请求 
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
static bool IsBreakInClrReq(STR_MACtrProc *pObj)
{
	return (pObj->m_SMACtrlBit.m_bBreakInClrReq == 1);		//	TRUE : BREAK_IN 清除请求
}
/*******************************************************************************
 函数名称： static void ClrBreakInClrReq(STR_MACtrProc *pObj)
 功能描述：   清零刹车清零请求
 设计思路：    
 操作的表：    无
 输入参数：    STR_MACtrProc *pObj ------结构体指针 
 输出参数：    无
 返 回 值：    bool True：故障清零 False：故障没有清零
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
static void ClrBreakInClrReq(STR_MACtrProc *pObj)
{
	pObj->m_SMACtrlBit.m_bBreakInClrReq = 0;				//	清除 BreakIn清除请求
}


static bool IsBreakInFault(STR_MACtrProc *pObj)
{
	return (pObj->m_SMACtrlBit.m_bBreakInFault == 1);		//	是否存在BreakIn故障信号 ?
}

static void ClrBreakInFault(STR_MACtrProc *pObj)
{
	pObj->m_SMACtrlBit.m_bBreakInFault = 0;					//	清除BreakIn故障信号标志
}
/*******************************************************************************
 函数名称： static void UARunCmd2MA(STR_MACtrProc *pObj,bool dirRev)
 功能描述：   UA层运行命令传到MA层
 设计思路：    1.UA的运行启动的命令传到MA层
 操作的表：    无
 输入参数：    STR_MACtrProc *pObj ------结构体指针 bool dirRev ------方向是否相反
 输出参数：    无
 返 回 值：    无
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
static void UARunCmd2MA(STR_MACtrProc *pObj,bool dirRev)
{
	pObj->m_SMACtrlBit.m_bUAMOE			= 1;				//	使能MOE标志
	pObj->m_SMACtrlBit.m_bMC_RunFlg		= 1;				//	使能run命令标志
	pObj->m_SMACtrlBit.m_bUAFaultClr	= 0;				//	UA报警清除标志清0
	if(dirRev)
	{
		pObj->m_SMACtrlBit.m_bUAReverse	= 1;				//	设置电机反转运行标志
	}
	else
	{
		pObj->m_SMACtrlBit.m_bUAReverse	= 0;				//	维持电机当前设定的运转方向
	}

	pObj->m_eStopMode					= pObj->mUaToMa.eBrakeMode;		// 更新 电机STOP模式
}

/*******************************************************************************
 函数名称： static void parseUACmdAndSetpoint(STR_MACtrProc *pObj)
 功能描述：   根据UA层参数设定MA层相关指令
 设计思路：    1.
 操作的表：    无
 输入参数：    STR_MACtrProc *pObj ------结构体指针 bool dirRev ------方向是否相反
 输出参数：    无
 返 回 值：    无
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
static void parseUACmdAndSetpoint(STR_MACtrProc *pObj)
{
	STR_PubDatUAMA *pUa2Ma = &pObj->mUaToMa;
	
	#if (DRV0_CLOSE_LOOP != CURRENT_LOOP)
	PSTR_DrvCfgPara pDrvCfgPara;
	pDrvCfgPara		= pObj->mg_pCtrlObj->m_pDrvCfgPara;						// 配置参数 指针
	#endif
	
	switch (pUa2Ma->eAppCmd)												// 解析UA层的控制命令
	{
		case E_CMD_MOTOR_STOP_MOE_OFF:		// 关闭MOE停止电机
		{
			pObj->m_SMACtrlBit.m_bMC_RunFlg		= 0;						// 清除run标志
			pObj->m_SMACtrlBit.m_bUAMOE			= 0;						// 清除MOE使能标志
			pObj->m_eStopMode					= E_STOP_MOE_OFF;			// 设置停止模式为关闭MOE
			break;
		}
		case E_CMD_MOTOR_STOP:				// 使能MOE停止电机
		{
			pObj->m_SMACtrlBit.m_bUAMOE			= 1;						// 设置MOE使能标志
			pObj->m_SMACtrlBit.m_bMC_RunFlg		= 0;						// 清除run标志
			pObj->m_eStopMode					= pUa2Ma->eBrakeMode;		// 设置停止模式为选择的相应制动模式				
			break;
		}

		#if (DRV0_CLOSE_LOOP == SPEED_LOOP)	//单电机速度环模式
		case E_CMD_MOTOR_SPEED_RUN:			//运行电机，转动方向为设定方向
		{		
			pObj->m_nLoopMode					= SPEED_LOOP;			
			UARunCmd2MA(pObj, FALSE);									// 解析UA层发送给MA层的控制命令
			break;
		}

		case E_CMD_MOTOR_SPEED_RUN_REV:		//运行电机，转动方向为设定方向相反方向
		{			
			pObj->m_nLoopMode					= SPEED_LOOP;			
			UARunCmd2MA(pObj, TRUE);									// 解析UA层发送给MA层的控制命令，速度方向取反
			break;
		}
		#elif (DRV0_CLOSE_LOOP == CURRENT_LOOP)		//单电机电流环模式

		case E_CMD_MOTOR_TORQUE_RUN:		//运行电机，转动方向为设定方向
		{
			pObj->m_nLoopMode					= CURRENT_LOOP;			
			UARunCmd2MA(pObj, FALSE);									// 解析UA层发送给MA层的控制命令
			break;
		}

		case E_CMD_MOTOR_TORQUE_RUN_REV:	//运行电机，转动方向为设定方向相反方向
		{
			pObj->m_nLoopMode					= CURRENT_LOOP;			
			UARunCmd2MA(pObj, TRUE);									// 解析UA层发送给MA层的控制命令，速度方向取反
			break;
		}

		#elif (DRV0_CLOSE_LOOP == POWER_LOOP)
		case E_CMD_MOTOR_POWER_RUN:			//运行电机，转动方向为设定方向
		{
			pObj->m_nLoopMode					= POWER_LOOP;
			UARunCmd2MA(pObj, FALSE);									// 解析UA层发送给MA层的控制命令
			break;
		}

		case E_CMD_MOTOR_POWER_RUN_REV:		//运行电机，转动方向为设定方向相反方向
		{
			pObj->m_nLoopMode					= POWER_LOOP;			
			UARunCmd2MA(pObj, TRUE);									// 解析UA层发送给MA层的控制命令，速度方向取反
			break;
		}
		#endif

		#if (DRV0_STOP_MODE == 0)
		case E_CMD_MOTOR_FAULT_DIMOE:		// UA存在FAULT停止电机,MOE关闭
		{
			pObj->m_SMACtrlBit.m_bUAMOE			= 0;					// 清除MOE使能标志
			pObj->m_SMACtrlBit.m_bUAFault		= 1;					// 设置UA故障有效标志
			pObj->m_SMACtrlBit.m_bUAFaultClr	= 0;					// UA故障清除标志清0
			pObj->m_SMACtrlBit.m_bMC_RunFlg		= 0;					// 清除run标志
			pObj->m_eStopMode					= pUa2Ma->eBrakeMode;
			break;
		}
		#else
		case E_CMD_MOTOR_FAULT_ENMOE:		// UA存在FAULT停止电机,MOE使能
		{
			pObj->m_SMACtrlBit.m_bUAMOE			= 1;					// 设置MOE使能标志
			pObj->m_SMACtrlBit.m_bUAFault		= 1;					// 设置UA故障有效标志
			pObj->m_SMACtrlBit.m_bUAFaultClr	= 0;					// UA故障标志清0
			pObj->m_SMACtrlBit.m_bMC_RunFlg		= 0;					// 清除run标志
			pObj->m_eStopMode					= pUa2Ma->eBrakeMode;	// 设置停止模式为选择的相应制动模式				
			break;
		}
		#endif

		#if (DRV0_PWM_ENABLE_STOP == FALSE)	
		case E_CMD_MOTOR_FAULT_CLR_DIMOE:	// 报警清除后 MOE不使能
		{
			pObj->m_SMACtrlBit.m_bUAMOE			= 0;					// 清除MOE使能标志
			pObj->m_SMACtrlBit.m_bUAFault		= 0;					// 清除肬A故障有效标志
			pObj->m_SMACtrlBit.m_bUAFaultClr	= 1;					// 设置UA故障清除标志
			pObj->m_SMACtrlBit.m_bMC_RunFlg		= 0;					// 清除run标志
			pObj->m_eStopMode					= pUa2Ma->eBrakeMode;				
			break;
		}
		#else
		case E_CMD_MOTOR_FAULT_CLR_ENMOE:	// 报警清除 MOE使能
		{
			pObj->m_SMACtrlBit.m_bUAMOE			= 1;					// 使能MOE有效标志
			pObj->m_SMACtrlBit.m_bUAFault		= 0;					// 清除肬A故障有效标志
			pObj->m_SMACtrlBit.m_bUAFaultClr	= 1;					// 设置UA故障清除标志
			pObj->m_SMACtrlBit.m_bMC_RunFlg		= 0;					// 清除run标志
			pObj->m_eStopMode					= pUa2Ma->eBrakeMode;				
			break;
		}
		#endif
		
		default:
		{
			pObj->m_SMACtrlBit.m_bUAMOE			= 0;					// 清除MOE使能标志
			pObj->m_SMACtrlBit.m_bUAFault		= 0;					// 清除肬A故障有效标志
			pObj->m_SMACtrlBit.m_bUAFaultClr	= 1;					// 设置UA故障清除标志
			pObj->m_SMACtrlBit.m_bMC_RunFlg		= 0;					// 清除run标志
			pObj->m_eStopMode					= pUa2Ma->eBrakeMode;				
			break;
		}
	}

	// 设置限值标志
	#if (DRV0_CLOSE_LOOP == SPEED_LOOP)	
		pObj->m_pAppCommData->bLoopLmtEnable	= pDrvCfgPara->mS_GlobalCfg.m_buPowerLmtInSpeedmode;
	#endif

	#if (DRV0_CLOSE_LOOP == POWER_LOOP)	
		pObj->m_pAppCommData->bLoopLmtEnable	= pDrvCfgPara->mS_GlobalCfg.m_buSpdLmtInPowermode;
	#endif
}
/*******************************************************************************
 函数名称： static void parseMD2MAInfor(STR_MACtrProc *pObj)
 功能描述：   MD层参数传到MA层
 设计思路：    1.UA的运行启动的命令传到MA层
 操作的表：    无
 输入参数：    STR_MACtrProc *pObj ------结构体指针 bool dirRev ------方向是否相反
 输出参数：    无
 返 回 值：    无
 多任务访问:   
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
static void parseMD2MAInfor(STR_MACtrProc *pObj)
{
	STR_PubDatMDMA*	pMd2Ma = &pObj->mMdToMa;
	PSTR_DrvCfgPara pDrvCfgPara		= pObj->mg_pCtrlObj->m_pDrvCfgPara;
	STR_TransCoefElement *pCoreToApp= &(pObj->mg_pCtrlObj->mTransCoef.mCoreToApp);

	s32 t_wTmp32;

	pObj->m_pMotorSpeed->wSpeedEst	= pMd2Ma->wFreq;		//获取MD层频率反馈

	//	按照设定的速度滤波时间进行速度滤波 
	//  滤波时间系数 nSpeedFiltTime 在StateInit()中初始化
	#if 0
	s16 t_nfreqFilt;
	t_nfreqFilt = 1024 - pObj->m_pMotorSpeed->nSpeedFiltTime;
	t_wTmp32 = (s32)pObj->m_pMotorSpeed->wSpeedfbk * t_nfreqFilt + (s32)pObj->m_pMotorSpeed->wSpeedEst * pObj->m_pMotorSpeed->nSpeedFiltTime;
	pObj->m_pMotorSpeed->wSpeedfbk = t_wTmp32 >> 10;
	#else
	t_wTmp32								= pObj->m_pMotorSpeed->wSpeedEst - (pObj->m_pMotorSpeed->wSpeedfbkFilter >>10);
	pObj->m_pMotorSpeed->wSpeedfbkFilter	+= t_wTmp32 * pObj->m_pMotorSpeed->nSpeedFiltTime;
	pObj->m_pMotorSpeed->wSpeedfbk			= (pObj->m_pMotorSpeed->wSpeedfbkFilter >> 10);
	#endif
	
	//pObj->m_pMotorSpeed->wSpeedfbk = pObj->m_pMotorSpeed->wSpeedEst;

	// 功率计算
	// 功率数据不需要时可屏蔽当前代码，节约FLASH空间
	// 功率滤波时间为10个当前环路周期，1ms周期时，滤波时间为10ms
	// m_nPower001WFactor			= 1024/(1+10);  Q10数据格式
	
	t_wTmp32 = Core2AppPowerTrans(pCoreToApp, pMd2Ma->nPowerDec);
	t_wTmp32				= t_wTmp32 - (pObj->m_wPower001WFil >> 10);
	pObj->m_wPower001WFil	+= ((s64)t_wTmp32 * pObj->m_nPower001WFactor);


	// 使能功率计算校正宏时，进行功率校正
	
	#if (POWER_CALC_CALIB_FUNCTION_ENABLE == FUNCTION_ON)
	s64 t_lTmp;
	t_wTmp32				= (pObj->m_wPower001WFil >> 10);

	t_lTmp = ((s64)pDrvCfgPara->mS_FBPwrLoop.m_wPowerFacA2 * t_wTmp32 * t_wTmp32)/100;
	t_lTmp += ((s64)pDrvCfgPara->mS_FBPwrLoop.m_wPowerFacA1 * t_wTmp32);
	t_lTmp += pDrvCfgPara->mS_FBPwrLoop.m_wPowerFacA0;	

	// Pcal = m_wPowerFacA0 + m_wPowerFacA1 * Power + m_wPowerFacA2 * Power^2
	// m_wPowerFacAx   Q12数据格式
	pObj->m_wPower001W		= (s32)(t_lTmp>>12);

	#else
	
	pObj->m_wPower001W		= (pObj->m_wPower001WFil >> 10);
	#endif
}

/*******************************************************************************
 函数名称：    static void parseFaultDetection(STR_MACtrProc *pObj)
 功能描述：    根据 故障检测模块 和 UA 模块停止方式，决定电机stop mode
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：		
 			   当UA存在故障信息
 			   		采用关闭MOE停止时，故障检测模块即便为高优先级也不能更改停止模式
 			   		采用其他方式停止时 故障检测模块为高优先级时，故障检测模块停止模式优先
 			   		
 			   当UA不存在故障信息
 			   		停止模式由故障检测模块决定
 			   		
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
static void parseFaultDetection(STR_MACtrProc *pObj)
{
	if(pObj->mg_UFault.R != 0)										//	存在报警等故障信息
	{
		if(pObj->m_SMACtrlBit.m_bUAFault == 1)						//  存在UA层故障	
		{
			if(pObj->m_eStopMode != E_STOP_MOE_OFF)					//  停止模式不为MOE关闭模式时
			{
				if(pObj->mg_eFaultPrio == E_FAULT_PRIO_HIGH)		//  故障模式为高优先级时
				{
					pObj->m_eStopMode	= pObj->mg_eFaultStopMode;	//  按照高优先级故障停止
				}
			}
		}
		else
		{
			pObj->m_eStopMode				= pObj->mg_eFaultStopMode;
		}		
	}

	if(pObj->mg_UFault.B.HardCurretError == 1)					// 存在硬件过流故障
	{
		pObj->m_SMACtrlBit.m_bBreakInFault		= 1;			// 设置硬件过流标志
	}
	else
	{															// 没有硬件过流故障时,
		if(pObj->m_SMACtrlBit.m_bBreakInFault == 1)				// 如果存在硬件过流标志，冗余判断
	{
			pObj->m_SMACtrlBit.m_bBreakInClrReq = 1;			// 设置硬件过流清除标志，后续进行故障清除操作
		}
	}
}

/*******************************************************************************
 函数名称：    void handleMAStateMachine(STR_MACtrProc *pObj)
 功能描述：    系统状态机 电机状态各状态切换调度
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
void handleMAStateMachine(STR_MACtrProc *pObj)
{
	memset(&pObj->mMaToUa, 0, sizeof(STR_PubDatMAUA));
	memset(&pObj->mMaToMd, 0, sizeof(STR_PubDatMAMD));	

	pObj->mg_pCtrlObj->mGlobalDatPackage.mMdToMa.gWrFlag = 1;		//	写保护操作
	
		//copy至私有便令空间，防止操作时存在数据变更情况
	memcpy(&pObj->mMdToMa, &pObj->mg_pCtrlObj->mGlobalDatPackage.mMdToMa, sizeof(STR_PubDatMDMA));

	pObj->mg_pCtrlObj->mGlobalDatPackage.mMdToMa.gWrFlag = 0;		//  关闭写保护

	if(pObj->mg_pCtrlObj->mGlobalDatPackage.mUaToMa.gWrFlag == 0)	//  UA到MA命令数据不在写状态，当前信息完整
	{
		memcpy(&pObj->mUaToMa, &pObj->mg_pCtrlObj->mGlobalDatPackage.mUaToMa, sizeof(STR_PubDatUAMA));
		//copy至私有便令空间，防止操作时存在数据变更情况
	}

	parseUACmdAndSetpoint(pObj);				//	从copy到本地的mUaToMa中解析 UA控制命令
	parseMD2MAInfor(pObj);						//	从copy到本地的mMdToMa中解析 MD信息及状态
	parseFaultDetection(pObj);					//	解析 报警单元的报警信息及状态
	
	if(IsFaultExists(pObj))						//	存在报警?
	{		
		if(pObj->m_SMACtrlBit.m_bMotorStopped)	// 电机已停止进入 E_DRIVER_FAULT 状态
		{
			pObj->m_eNextSysState	= E_DRIVER_FAULT;
		}
		else									// 电机未停止进入 E_DRIVER_READY_STOP 状态，控制或等待电机停止
		{
			pObj->m_eNextSysState	= E_DRIVER_READY_STOP;
		}
	}

	pObj->m_eSysState = pObj->m_eNextSysState;	//状态机更新
	
    switch (pObj->m_eSysState)
   	{
		case E_DRIVER_INIT:						/* 上电初始状态 */
    	{
			if(InitDriverMain(pObj))			// 初始化变量及报警处理信息
			{
				if(WaitPowerOnFinish(pObj))		// 上电完成?
				{
					// 根据实际添加必要的处理 如继电器吸合等
					//需要校正时进入校正
					//pObj->m_eNextSysState = E_DRIVER_CALIB;

					//进入STOP状态
					setInitAcrParaReq(pObj);	// 设置电流环参数初始化请求标志
					pObj->m_eNextSysState = E_DRIVER_STOP;
				}
			}
		}
		break;

		case E_DRIVER_STOP:						/* 停止STOP状态 */
		{
			if(StopMotorMain(pObj))				// 停止STOP状态任务函数，初始化完成时返回TRUE
			{
				if( IsMotorRunCmd(pObj))		// 存在run命令?
				{	// 预充电使能时，进行预充电处理
					// 预充电未使能时
						// 顺逆风   使能  ----->  顺逆风处理
						//        未使能  ----->  IPD判断   ------ 使能   运行IPD
						//                                  ------ 未使能 运行对相处理
					#if (DRV0_CHARGE_ENABLE==FUNCTION_ON)
					pObj->m_eNextSysState = E_DRIVER_CHARGE;
					#else
						#if (DRV0_DIR_CHECK_ENABLE==FUNCTION_ON)		
						SetMotorInfoSubStatus(pObj, MOTOR_INFO_TRACKING);
						pObj->m_eNextSysState = E_DRIVER_MOTOR_INFO;
						#elif (DRV0_POS_SEEK_ENABLE==FUNCTION_ON)
						SetMotorInfoSubStatus(pObj, MOTOR_INFO_IPD);
						pObj->m_eNextSysState = E_DRIVER_MOTOR_INFO;
						#else
						pObj->m_eNextSysState = E_DRIVER_READY_RUN;
						#endif

					#endif
				}
				else
				{
                    setInitAcrParaReq(pObj);	// 设置电流环参数初始化请求标志
				}
			}
		}
		break;

		#if (DRV0_CHARGE_ENABLE==FUNCTION_ON)
											/* 单电机使能预充电功能时才编入预充电状态*/
		case E_DRIVER_CHARGE:
		{	
			ChargeDriverMain(pObj);			//	预充电处理函数
											//	预充电时间配置为0时，相当于没有预充电功能
			if( IsMotorRunCmd(pObj))
			{
				if(IsDriveChargeFinish(pObj))
				{						
					// 顺逆风   使能  ----->  顺逆风处理
					//        未使能  ----->  IPD判断   ------ 使能   运行IPD
					//                                  ------ 未使能 运行对相处理
					#if (DRV0_DIR_CHECK_ENABLE==FUNCTION_ON)		
					SetMotorInfoSubStatus(pObj, MOTOR_INFO_TRACKING);
					pObj->m_eNextSysState = E_DRIVER_MOTOR_INFO;
					#elif (DRV0_POS_SEEK_ENABLE==FUNCTION_ON)
					SetMotorInfoSubStatus(pObj, MOTOR_INFO_IPD);
					pObj->m_eNextSysState = E_DRIVER_MOTOR_INFO;
					#else
					pObj->m_eNextSysState = E_DRIVER_READY_RUN;
					#endif					
				}
			}
			else
			{
				pObj->m_eNextSysState = E_DRIVER_STOP;
			}
		}
		break;
		#endif

		case E_DRIVER_MOTOR_INFO:					/* 电机信息检测状态 */
		{
			switch (GetMotorInfoSubStatus(pObj))
			{
				// 单驱动单元时预编译
				#if (DRV0_DIR_CHECK_ENABLE==FUNCTION_ON)	
				case MOTOR_INFO_TRACKING:			//	顺逆风判断
				{
					if(IsNeedTracking(pObj))		//	需要顺逆风?
					{
						MotorTrakingMain(pObj);		//	顺逆风处理

						if(pObj->m_eTrackingResult == TRACKING_2_RUN)			//	顺逆风结果为运行状态
						{							
							SetMotorInfoSubStatus(pObj, MOTOR_INFO_TRACKING_RUN);
						}
						else if(pObj->m_eTrackingResult == TRACKING_2_BRAKE)	//	顺逆风结果为制动状态
						{
							BrakeStateCheckInit(pObj->mMdToMa.nMotorCur,pObj->m_pOnTheFlyDetect);
							SetMotorInfoSubStatus(pObj, MOTOR_INFO_TRACKING_BRAKE);
						}
					}
					else
					{
						// 单驱动单元时预编译 IPD判断   ------ 使能   运行IPD
						//  		 					------ 未使能 运行对相处理
						#if (DRV0_POS_SEEK_ENABLE==FUNCTION_ON)					
						SetMotorInfoSubStatus(pObj, MOTOR_INFO_IPD);
						#else
						pObj->m_eNextSysState = E_DRIVER_READY_RUN;
						#endif
					}
				}
				break;

				case MOTOR_INFO_TRACKING_RUN:		//	顺逆风结果为运行状态
				{
					// handle motor run
					MotorTracking2Run(pObj);		//	顺逆风切换为RUN的处理			
					pObj->m_eNextSysState = E_DRIVER_RUN;
				}
				break;

				case MOTOR_INFO_TRACKING_BRAKE:		//	顺逆风结果为制动状态
				{
					// handle motor brake
					MotorTracking2Brake(pObj);		//  制动停止电机处理
					if(pObj->m_SMACtrlBit.m_bMotorStopped)		//	电机已停止?
					{
						// 单驱动单元时预编译 IPD判断   ------ 使能   运行IPD
						//  		 					------ 未使能 运行对相处理
						#if (DRV0_POS_SEEK_ENABLE==FUNCTION_ON)					
						SetMotorInfoSubStatus(pObj, MOTOR_INFO_IPD);
						#else
						pObj->m_eNextSysState = E_DRIVER_READY_RUN;
						#endif
					}					
				}
				break;
				#endif

				#if (DRV0_POS_SEEK_ENABLE==FUNCTION_ON)
				case MOTOR_INFO_IPD:		//单电机 初始位置检测状态IPD
				{
					if(IsNeedIPD(pObj))			//	需要IPD检测?
					{
						SetMotorInfoSubStatus(pObj, MOTOR_INFO_IPD_RESULT);	//	设置IPD结果等待状态
					}
					else
					{
						pObj->m_eNextSysState = E_DRIVER_READY_RUN;
					}
				}
				break;

				case MOTOR_INFO_IPD_RESULT:		//	IPD结果等待状态
				{
					MotorIPDMain(pObj);			// 	IPD检测函数
					if(IsIPDFinish(pObj))		//	IPD检测完成?
					{
						pObj->m_eNextSysState = E_DRIVER_READY_RUN;
					}						
				}
				
				#endif

				default:
				{
					//SetMotorInfoSubStatus(pObj, MOTOR_INFO_TRACKING);
				}
				break;
			
			}

			if( !IsMotorRunCmd(pObj))			//	STOP命令时，进入STOP状态，停止当前的运行检测
			{
				setInitAcrParaReq(pObj);
				pObj->m_eNextSysState = E_DRIVER_STOP;
			}			
		}
		break;
			

		case E_DRIVER_READY_RUN:				//	电机准备运行状态，电机对相
		{
			#if (DRV0_ALLIGN_CUR_ENABLE==FUNCTION_ON)	
			if(IsNeedAllign(pObj))
			{
				MotorAlignMain(pObj);			//	对相处理函数
				if(IsAllignFinish(pObj))		//	如果对相结束，进入RUN运行状态
				{
					pObj->m_eNextSysState = E_DRIVER_RUN;						
				}
			}
			else
			{									//	不需要对相操作时，直接进入RUN运行状态
				pObj->m_eNextSysState = E_DRIVER_RUN;
			}
			#else
			pObj->m_eNextSysState = E_DRIVER_RUN;
			#endif

			if( !IsMotorRunCmd(pObj))			//	STOP命令时，进入STOP状态，停止当前状态机运行
			{
				setInitAcrParaReq(pObj);		//	设置电流环初始化请求标志
				pObj->m_eNextSysState = E_DRIVER_STOP;
			}
		}
		break;
		

		case E_DRIVER_RUN:						//	电机RUN运行状态
		{
			MotorCloseMain(pObj);				//	电机RUN运行控制函数
			if( !IsMotorRunCmd(pObj) || (pObj->m_SMACtrlBit.m_bExceptionEnable == 1))
			{
				//	接收到停机命令，或者运行异常标志置位
				SetTimeOut_Counter(pObj->m_nSetTimeLeftCnt, pObj->m_nSetTimeLeftPrd);	//	设置停机等待时间
				BrakeStateCheckInit(pObj->mMdToMa.nMotorCur,pObj->m_pOnTheFlyDetect);	//	制动检测初始化函数
				pObj->m_eNextSysState = E_DRIVER_READY_STOP;							//	进入准备停止状态机
			}

		}
		break;

		case E_DRIVER_READY_STOP:				//	电机停止过程状态
		{
			MotorBreakMain(pObj);						//	电机制动处理函数
			if(pObj->m_SMACtrlBit.m_bMotorStopped)		//	电机是否已经停止?
			{
				setInitAcrParaReq(pObj);				//	设置电流环参数初始请求标志
				pObj->m_eNextSysState = E_DRIVER_STOP;	//	进入STOP状态
			}
			else
			{
				if(IsMotorRunCmd(pObj))					//	电机未停止，接收到RUN标志
				{
					if(IsCanRestore2Run(pObj))			//	是否满足可恢复情况澹?
					{
						pObj->m_eNextSysState = E_DRIVER_RUN;	//	可恢复则设置为RUN状态
					}
				}
			}				
		}
		break;

		case E_DRIVER_FAULT:					//	报警状态
		{
			MotorFaultMain(pObj);						//	报警处理函数
			if(WaitPowerOnFinish(pObj))					//	当前硬件版是否上电完成?
			{
				if(!IsFaultExists(pObj))				//	上电完完成且不存在报警信息
				{
					if(IsFaultClrCmd(pObj))				//	是否存在报警清除标志
					{
						if(IsPOSTFinish(pObj))			//	是否上电完成 ?
						{
							setInitAcrParaReq(pObj);	//	上电完成后，设置电流环参数初始请求标志，并进入STOP状态
							pObj->m_eNextSysState = E_DRIVER_STOP;
						}
						else
						{								//	上电未完成后，进入上电初始状态，继续后续检测
							pObj->m_eNextSysState = E_DRIVER_INIT;
						}
					}
				}
				else
				{
					if(IsBreakInClrReq(pObj))			//	存在硬件过流状态清除标志。硬件过流标志清除时，会设置BreakInClr请求
					{
						if(IsBreakInFault(pObj))		//	当前存在breakIn故障标志?
						{
							if(!getBreakInClrResultMD2MA(&pObj->mMdToMa))
							{			//	当前存在breakIn故障标志，但breakIn故障清除未完成
								setClrBreakInFaultFCmdMA2MD(&pObj->mMaToMd);	//	设置清除标志，后续经过共享交换区到MD层
						}
						else
							{			//	当前存在breakIn故障标志，但breakIn故障清除已完成
								ClrBreakInFault(pObj);							//	清除breakIn故障标志
								ClrBreakInClrReq(pObj);							//	清除硬件过流状态清除标志
								setDefaultCmdMA2MD(&pObj->mMaToMd);				//	设置默认操作命令给MD
							}
						}
						else
						{				//	当前不存在breakIn故障标志	冗余处理
							ClrBreakInClrReq(pObj);								//	清除硬件过流状态清除标志
							setDefaultCmdMA2MD(&pObj->mMaToMd);					//	设置默认操作命令给MD				
						}
					}
				}
			}
		}
		break;

		default:
		{
		pObj->m_eNextSysState	= E_DRIVER_FAULT;
		}
		break;
	}

	// Update local data zone of MA2UA
	// some SR bit  of MA2UA is updated in state task.
	updateMAInfo2UALocal(pObj);
	
	// Update data swap zone for MA2MD and MA2UA
	//	更新MA2MD信息至共享交换区
	pObj->mg_pCtrlObj->mGlobalDatPackage.mMaToMd.gWrFlag = 1;
	memcpy(&pObj->mg_pCtrlObj->mGlobalDatPackage.mMaToMd,&pObj->mMaToMd,sizeof(STR_PubDatMAMD));
	pObj->mg_pCtrlObj->mGlobalDatPackage.mMaToMd.gWrFlag = 0;
	
	//	更新MA2UA信息至共享交换区
	if(pObj->mg_pCtrlObj->mGlobalDatPackage.mMaToUa.SR.Bit.locked == 0)
	{
		memcpy(&pObj->mg_pCtrlObj->mGlobalDatPackage.mMaToUa,&pObj->mMaToUa,sizeof(STR_PubDatMAUA));
	}
}


//************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */



