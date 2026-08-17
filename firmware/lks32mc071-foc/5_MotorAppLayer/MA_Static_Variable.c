/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： MA_Static_Variable.c
 * 文件标识：
 * 内容摘要： MA局部全局变量声明文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Tonghua Li
 * 完成日期： 2022年8月19日
 *
 *******************************************************************************/
#include "MA_Static_Variable.h"
#include "time_process.h"
#include "PowerCalculation.h" 
#include "string.h"


const char sVersion[10] = "Ver_1.0";        						/* 程序版本 */

STR_TaskScheduler		gS_TaskScheduler;    						/* 任务调度结构体 */

STR_MACtrProc			sS_MACtrProc[MA_OBJ_MAX_DEFINE];			/* MA 控制对象 */
STR_MASubBlock			sS_MASubBlock[MA_OBJ_MAX_DEFINE];			/* MA 控制结构体 */

extern PSTR_ControlObject getCtrlObjectPtr(u8 objID);				//	获得控制对象指针
extern void updateObParaMALayer(PSTR_ControlObject pCtrlObj);		//	MA层更新观测器参数, MD层根据MA层参数应用
extern void updateAcrParaMALayer(PSTR_ControlObject pCtrlObj);		//	MA层更新电流环参数，MD层根据MA层参数应用
extern void updateSVPWMParaMALayer(PSTR_ControlObject pCtrlObj);	//	MA层更新SVPWM参数，MD层根据MA层参数应用


PSTR_MACtrProc	getMACtrPtr(u8 ObjID)			//	获得MA层对相指针
{
	if(ObjID < MA_OBJ_MAX_DEFINE)				//	对相ID小于定义的对象数时返回指针，否则返回NULL空
	{
		return &sS_MACtrProc[ObjID];
	}
	else
	{
		return NULL;
	}
}

PSTR_MACtrProc	directGetMACtrPtr(u8 ObjID)		//	直接获得MA对象指针，不进行ID有效性判断
{
	return &sS_MACtrProc[ObjID];		
}


u8 getMaxMAObjNbr(void)							//	获得支持的最大对象个数
{
	return MA_OBJ_MAX_DEFINE;
}

/*******************************************************************************
 函数名称：    bool registerSubBlock2MACrtlProc(void)
 功能描述：    按控制对象进行注册子模块
 输入参数：    无
 输出参数：    无
 返 回 值：    操作结果 true ---- 初始化成功
 其它说明：    注册数据结构指针、控制对象等
 			   初始化全局配置，如速度环模式、是否顺逆风检测等 			   
 			   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
bool registerSubBlock2MACrtlProc(void)
{
	u8 objID = 0;
	bool returnResult = TRUE;
	
	memset(&sS_MACtrProc[objID], 0, sizeof(STR_MACtrProc));
	sS_MACtrProc[objID].mg_nMACtrlProcID		= objID;
	sS_MACtrProc[objID].m_eSysState				= E_DRIVER_INIT;							//	初始状态

	sS_MACtrProc[objID].m_pAppCommData			= &sS_MASubBlock[objID].m_struAppCommData;	//	运行流程控制结构体指针
	sS_MACtrProc[objID].m_pMotorSpeed			= &sS_MASubBlock[objID].m_struMotorSpeed;	//	转速矢量结构体指针初始化
	
	sS_MACtrProc[objID].m_pOnTheFlyDetect		= &sS_MASubBlock[objID].m_OnTheFlyDetect;	//	顺逆风结构体指针初始化
	
	#if(DRV0_UNDVOLT_PROT_ENABLE == 1)
	sS_MACtrProc[objID].m_pMotorException		= &sS_MASubBlock[objID].m_MotorException;	//	电压异常结构体指针初始化
	#endif
	
	sS_MACtrProc[objID].m_pTime					= &sS_MASubBlock[objID].m_struTime;			//	计时时间结构体指针初始化

	sS_MACtrProc[objID].m_pSTR_CurRampGen		= &sS_MASubBlock[objID].m_STR_CurRampGen;	//	电流指令规划结构体指针初始化

	
	#if ((DRV0_CLOSE_LOOP == POWER_LOOP) || ((DRV0_POWER_LIMIT_STATUS == TRUE) && (DRV0_CLOSE_LOOP == SPEED_LOOP)))		
	sS_MACtrProc[objID].m_pPower				= &sS_MASubBlock[objID].m_struPower;		//	功率结构体指针初始化
	#endif

	sS_MACtrProc[objID].m_pFaults				= &sS_MASubBlock[objID].m_stru_Faults;				//	报警标志结构体指针初始化
	sS_MACtrProc[objID].m_pFaultValue			= &sS_MASubBlock[objID].m_stru_FaultValue;			//	报警变量结构体指针初始化
	sS_MACtrProc[objID].m_pstruCurrentAmplitude	= &sS_MASubBlock[objID].m_struCurrentAmplitude;		//	电流幅值变量结构体指针初始化
	sS_MACtrProc[objID].m_pstruImaxCurrent		= &sS_MASubBlock[objID].m_struImaxCurrent;			//	电流最大值变量结构体指针初始化
	sS_MACtrProc[objID].m_pstruFaultVoltTime	= &sS_MASubBlock[objID].m_struFaultVoltTime;		//	电压检测时间结构体指针初始化
	sS_MACtrProc[objID].m_pstruFaultEmptyTime	= &sS_MASubBlock[objID].m_struFaultEmptyTime;		//	空转检测时间结构体指针初始化
	sS_MACtrProc[objID].m_pstruFaultStallTime	= &sS_MASubBlock[objID].m_struFaultStallTime;		//	堵转检测时间结构体指针初始化
	sS_MACtrProc[objID].m_pstruFaultCurrentTime	= &sS_MASubBlock[objID].m_struFaultCurrentTime;		//	电流检测时间结构体指针初始化
	sS_MACtrProc[objID].m_pstruFaultTempTime	= &sS_MASubBlock[objID].m_struFaultTempTime;		//	温度检测时间结构体指针初始化
	sS_MACtrProc[objID].m_pstruFaultPhaseTime	= &sS_MASubBlock[objID].m_struFaultPhaseTime;		//	缺相检测时间结构体指针初始化
	sS_MACtrProc[objID].m_pstruFaultStartTime	= &sS_MASubBlock[objID].m_struFaultStartTime;		//	启动检测时间结构体指针初始化

	
	sS_MACtrProc[objID].mg_pCtrlObj				= getCtrlObjectPtr(objID);					// 注册实际的控制对象，根据ID查找
	if(sS_MACtrProc[objID].mg_pCtrlObj == NULL)
	{
		returnResult = FALSE;
	}
	return returnResult;
}
/*******************************************************************************
 函数名称：    void initMACtrProc (u8 ObjID)
 功能描述：    按控制对象ID初始化
 输入参数：    u8 ObjID
 输出参数：    无
 返 回 值：    
 其它说明：    初始化全局变量			   
 			   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
void initMACtrProc (u8 ObjID)
{
	PSTR_DrvCfgPara pDrvCfgPara;
	pDrvCfgPara		= sS_MACtrProc[ObjID].mg_pCtrlObj->m_pDrvCfgPara;
	sS_MACtrProc[ObjID].m_SMACtrlBit.m_bAcrInitDone			= 0;		//	电流环初始化完成标志	0 ----- 未完成
	sS_MACtrProc[ObjID].m_SMACtrlBit.m_bAcrParaReq			= 1;		//	电流环初始化请求标志 	1 ----- 有初始化请求
	sS_MACtrProc[ObjID].m_SMACtrlBit.m_bAcrParaUpdate		= 1;		//	电流环参数需要更新标志	1 ----- 参数需要更新

	sS_MACtrProc[ObjID].m_SMACtrlBit.m_bSVPWMInitDone		= 0;		//	SVPWM初始化完成标志		0 ----- 未完成
	sS_MACtrProc[ObjID].m_SMACtrlBit.m_bSVPWMParaReq		= 1;		//	SVPWM初始化请求标志 	1 ----- 有初始化请求
	sS_MACtrProc[ObjID].m_SMACtrlBit.m_bSVPWMParaUpdate		= 1;		//	SVPWM参数需要更新标志	1 ----- 参数需要更新

	sS_MACtrProc[ObjID].m_SMACtrlBit.m_bObParaInitDone		= 0;		//	观测器初始化完成标志	0 ----- 未完成
	sS_MACtrProc[ObjID].m_SMACtrlBit.m_bObParaReq			= 1;		//	观测器初始化请求标志 	1 ----- 有初始化请求
	sS_MACtrProc[ObjID].m_SMACtrlBit.m_bObParaUpdate		= 1;		//	观测器参数需要更新标志	1 ----- 参数需要更新	

	sS_MACtrProc[ObjID].m_SMACtrlBit.m_bFaultInitDone		= 0;		//	报警模块初始化完成标志	0 ----- 未完成
	sS_MACtrProc[ObjID].m_SMACtrlBit.m_bFaultInitReq		= 1;		//	报警模块初始化请求标志 	1 ----- 有初始化请求

	sS_MACtrProc[ObjID].m_SMACtrlBit.m_bIPDFinish			= 0;		//	IPD模块初始化完成标志	0 ----- 未完成
	sS_MACtrProc[ObjID].m_SMACtrlBit.m_bIPDInitReq			= 0;		//	IPD模块初始化请求标志 	1 ----- 有初始化请求
	sS_MACtrProc[ObjID].m_SMACtrlBit.m_bIPDInitDone			= 0;		//	IPD模块初始化完成标志	0 ----- 未完成

	// update default configure data MA2MD
	updateObParaMALayer(sS_MACtrProc[ObjID].mg_pCtrlObj);				//	MA更新观测器参数，MD应用
	updateAcrParaMALayer(sS_MACtrProc[ObjID].mg_pCtrlObj);				//	MA更新电流环参数，MD应用
	updateSVPWMParaMALayer(sS_MACtrProc[ObjID].mg_pCtrlObj);			//	MA更新SVPWM参数，MD应用

	sS_MACtrProc[ObjID].m_SMACtrlBit.m_bNeedTracking	= pDrvCfgPara->mS_GlobalCfg.m_buDirCheckEnable || pDrvCfgPara->mS_GlobalCfg.m_buBemfDirEnable;
																	//	根据配置初始化是否需要顺逆风功能
	sS_MACtrProc[ObjID].m_SMACtrlBit.m_bNeedIPD			= pDrvCfgPara->mS_GlobalCfg.m_buIPDEnable;
																	//	根据配置初始化是否需要IPD功能

	sS_MACtrProc[ObjID].m_SMACtrlBit.m_bNeedAlign		= pDrvCfgPara->mS_GlobalCfg.m_buAllignEnable;
																	//	根据配置初始化是否需要对相ALLIGN功能

	sS_MACtrProc[ObjID].m_nLoopMode						= pDrvCfgPara->mS_GlobalCfg.m_buCtrLoopmode;
																	//	根据配置初始化选用控制模式: 0 -- 速度环  1 -- 电流环  2 -- 功率环

	if(sS_MACtrProc[ObjID].m_nLoopMode == SPEED_LOOP)				//	速度环模式时，根据配置初始化是否需要功率限制
	{
		sS_MACtrProc[ObjID].m_pAppCommData->bLoopLmtEnable	= pDrvCfgPara->mS_GlobalCfg.m_buPowerLmtInSpeedmode;
	}

	if(sS_MACtrProc[ObjID].m_nLoopMode == POWER_LOOP)				//	功率环模式时，根据配置初始化是否需要速度限制
	{
		sS_MACtrProc[ObjID].m_pAppCommData->bLoopLmtEnable	= pDrvCfgPara->mS_GlobalCfg.m_buSpdLmtInPowermode;
	}
}

/*******************************************************************************
 函数名称：    s16 getMAEstSpeed(u8 t_bObjId)
 功能描述：    根据ID读取MA层得到的MD观测速度
 输入参数：    u8 ObjID
 输出参数：    无
 返 回 值：    
 其它说明：    返回估算速度 ---- core数据格式			   
 			   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
s16 getMAEstSpeed(u8 t_bObjId)
{
	return (s16)(sS_MASubBlock[t_bObjId].m_struMotorSpeed.wSpeedEst);
}

/*******************************************************************************
 函数名称：    s16 getMARefSpeed(u8 t_bObjId)
 功能描述：    根据ID读取MA层速度设定指令
 输入参数：    u8 ObjID
 输出参数：    无
 返 回 值：    
 其它说明：    返回设定速度 ---- core数据格式			   
 			   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
s16 getMARefSpeed(u8 t_bObjId)
{
	return (s16)(sS_MASubBlock[t_bObjId].m_struMotorSpeed.wSpeedRef);
}

/*******************************************************************************
 函数名称：    s16 getMAFdbkSpeed(u8 t_bObjId)
 功能描述：    根据ID读取MA层得到的观测后滤波速度,滤波时间见配置
 输入参数：    u8 ObjID
 输出参数：    无
 返 回 值：    
 其它说明：    返回设定速度 ---- core数据格式			   
 			   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
s16 getMAFdbkSpeed(u8 t_bObjId)
{
	return (s16)(sS_MASubBlock[t_bObjId].m_struMotorSpeed.wSpeedfbk);
}

/*******************************************************************************
 函数名称：    s16 getMAIqref(u8 t_bObjId)
 功能描述：    根据ID读取MA层输出的滤波后Q轴电流指令值
 输入参数：    u8 ObjID
 输出参数：    无
 返 回 值：    
 其它说明：    返回滤波后指令值 ---- core数据格式			   
 			   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
s16 getMAIqref(u8 t_bObjId)
{
	return (s16)(sS_MACtrProc[t_bObjId].m_nQCur_Reference);
}
/*******************************************************************************
 函数名称：    s16 getMAIdref(u8 t_bObjId)
 功能描述：    根据ID读取MA层输出的滤波后D轴电流指令值
 输入参数：    u8 ObjID
 输出参数：    无
 返 回 值：    
 其它说明：    返回滤波后指令值 ---- core数据格式			   
 			   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
s16 getMAIdref(u8 t_bObjId)
{
	return (s16)(sS_MACtrProc[t_bObjId].m_nDCur_Reference);
}

/*******************************************************************************
 函数名称：    s16 getMAIqSet(u8 t_bObjId)
 功能描述：    根据ID读取MA层输出的Q轴电流指令设定值
 输入参数：    u8 ObjID
 输出参数：    无
 返 回 值：    
 其它说明：    返回Q轴指令值 ---- core数据格式			   
 			   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
s16 getMAIqSet(u8 t_bObjId)
{
	return (s16)(sS_MACtrProc[t_bObjId].m_nQCurrentSet);
}
/*******************************************************************************
 函数名称：    s16 getMAIdref(u8 t_bObjId)
 功能描述：    根据ID读取MA层输出的D轴电流指令设定值
 输入参数：    u8 ObjID
 输出参数：    无
 返 回 值：    
 其它说明：    返回D轴指令值 ---- core数据格式			   
 			   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
s16 getMAIdSet(u8 t_bObjId)
{
	return (s16)(sS_MACtrProc[t_bObjId].m_nDCurrentSet);
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
