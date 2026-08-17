/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： MA_interface.c
 * 文件标识：
 * 内容摘要： MA对外接口调用及访问函数
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet Li
 * 完成日期： 2020年8月16日
 *
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "basic.h"
#include "MA_Static_Variable.h"
#include "math.h"
#include "Time_Process.h"
#include "state_machine.h"



//#define _POLLING_MODE

/*******************************************************************************/
//外部函数引用区
extern bool				registerSubBlock2MACrtlProc(void);
extern u8				getMaxMAObjNbr(void);
extern PSTR_MACtrProc	getMACtrPtr(u8 ObjID);
extern void				FaultCheck(STR_MACtrProc *pObj);
extern void				handleMAStateMachine(STR_MACtrProc *pObj);
extern void				initMACtrProc (u8 ObjID);
extern PSTR_MACtrProc	directGetMACtrPtr(u8 ObjID);

/*******************************************************************************/
//局部静态全局变量定义区
#ifdef _POLLING_MODE
static u8 t_nuObjID = 0;
#endif

extern STR_MACtrProc			sS_MACtrProc[MA_OBJ_MAX_DEFINE];

/*******************************************************************************
 函数名称：    void handleMACtrlObj(u8 nuObjID)
 功能描述：    按控制对象ID进行MA任务处理
 输入参数：    按控制对象ID
 输出参数：    无
 返 回 值：    无
 其它说明：    该函数被任务调用，与MD/UA数据交互在该函数内完成
 			   通过共享交互数据区实现

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
static void handleMACtrlObj(u8 nuObjID)
{
	PSTR_MACtrProc pObj = &sS_MACtrProc[0];
	SetTime_CountDown(pObj);			/* 倒计数函数计时处理	*/
	FaultCheck(pObj);					/* 故障检测及报警处理	*/
	handleMAStateMachine(pObj); 		/* 电机状态机调度		*/
}


/*******************************************************************************
 函数名称：    MACtrlObjTask(void)
 功能描述：    按控制对象进行MA任务处理
 输入参数：    控制对象指针
 输出参数：    无
 返 回 值：    无
 其它说明：    该函数被周期性任务调用，与MD/UA数据交互在该函数内完成
 			   通过共享交互数据区实现
 			   该函数为对外直接调用函数
 			   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
void MACtrlObjTask(void)
{
	handleMACtrlObj(0);					//	MA层任务
}

/*******************************************************************************
 函数名称：    initMACtrlObj()
 功能描述：    按控制对象进行MA任务处理
 输入参数：    控制对象指针
 输出参数：    无
 返 回 值：    操作结果 true ---- 初始化成功
 其它说明：    注册数据结构指针、控制对象等
 			   初始化全局配置，如速度环模式、是否顺逆风检测等
 			   
 			   该函数为可以对外直接调用函数，注意初始化顺序
 			   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/

bool initMACtrlObj(void)
{
	bool result;	
	result = registerSubBlock2MACrtlProc();		//	注册内部变量及指针、初始化内部变量
	if(result)
	{
		initMACtrProc(0);						//	配置初始化
	}
	return result;
}

/*******************************************************************************
 函数名称：    void InitMotorAppLayer(void)
 功能描述：    MA层初始化函数
 输入参数：    void
 输出参数：    无
 返 回 值：    
 其它说明：    注册数据结构指针、控制对象等
 			   初始化全局配置，如速度环模式、是否顺逆风检测等
 			   
 			   该函数为对外直接调用函数
 			   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
void InitMotorAppLayer(void)
{
	initMACtrlObj();
}

/*******************************************************************************
 函数名称：    void setMADQCurref(s16 dRef, s16 qRef,u8 t_bObjId)
 功能描述：    设置MA层DQ电流指令值函数
 输入参数：    s16 dRef, s16 qRef,u8 t_bObjId
 输出参数：    无
 返 回 值：    
 其它说明：    设置DQ电流指令参考值
 				有必要时设置指令值以及电流滤波中间值
 			  
 			   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
void setMADQCurref(s16 dRef, s16 qRef,u8 t_bObjId)
{
	PSTR_MACtrProc pObj;

	pObj	= getMACtrPtr(t_bObjId);

	pObj->m_nDCur_Reference	= dRef;
	pObj->m_nQCur_Reference	= qRef;
	#if (DRV0_CLOSE_LOOP == SPEED_LOOP)
	pObj->m_pMotorSpeed->mSpeedPI.wIntegral	= (s64)qRef << 22;
	#endif

	pObj->mg_pCtrlObj->mGlobalDatPackage.mMaToMd.mStatCurDQCmd.nAxisD = pObj->m_nDCur_Reference;
	pObj->mg_pCtrlObj->mGlobalDatPackage.mMaToMd.mStatCurDQCmd.nAxisQ = pObj->m_nQCur_Reference;
	
}

/*******************************************************************************
 函数名称：    void setMADQCurrefInit(s16 dRef, s16 qRef,u8 t_bObjId)
 功能描述：    设置MA层DQ电流指令值函数
 输入参数：    s16 dRef, s16 qRef,u8 t_bObjId
 输出参数：    无
 返 回 值：    
 其它说明：    设置DQ电流指令参考值
 				有必要时设置指令值以及电流滤波中间值
 			  
 			   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
void setMADQCurrefInit(s16 dRef, s16 qRef,u8 t_bObjId)
{
	PSTR_MACtrProc pObj;
	
	pObj	= getMACtrPtr(t_bObjId);
		
	pObj->m_nQCur_Reference		= dRef;
	pObj->m_nDCur_Reference		= pObj->m_nDCurrentSet;

	pObj->mg_pCtrlObj->mGlobalDatPackage.mMaToMd.mStatCurDQCmd.nAxisD = pObj->m_nDCur_Reference;
	pObj->mg_pCtrlObj->mGlobalDatPackage.mMaToMd.mStatCurDQCmd.nAxisQ = pObj->m_nQCur_Reference;
}

/*******************************************************************************
 函数名称：    void setMAEst2Ref(u8 t_bObjId)
 功能描述：    设置MA层速度反馈值
 输入参数：    u8 t_bObjId
 输出参数：    无
 返 回 值：    
 其它说明：    设置wSpeedRef
 				
 			  
 			   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
void setMAEst2Ref(u8 t_bObjId)
{
	PSTR_MACtrProc pObj;
	pObj	= getMACtrPtr(t_bObjId);
	pObj->m_pMotorSpeed->wSpeedRef	= pObj->m_pMotorSpeed->wSpeedEst;	
}

u16 getMAStatus(u8 t_bObjId)
{
	PSTR_MACtrProc pObj;
	pObj	= getMACtrPtr(t_bObjId);
	return (u16)pObj->m_eSysState;
}

u16 getMAMotorInfoStatus(u8 t_bObjId)
{
	PSTR_MACtrProc pObj;
	pObj	= getMACtrPtr(t_bObjId);
	return (u16)pObj->m_eMotorInfoState;
}

s32 minSpd2CoreData[MA_OBJ_MAX_DEFINE];
s32 minVolt2CoreData[MA_OBJ_MAX_DEFINE];


void MinMotorVoltSpd2Core(u8 tObjId)
{
	STR_MACtrProc *pObj						= getMACtrPtr(tObjId);
	PSTR_DrvCfgPara			t_pDrvCfgPara = pObj->mg_pCtrlObj->m_pDrvCfgPara;
	STR_TransCoefElement 	*pAppToCore = &(pObj->mg_pCtrlObj->mTransCoef.mAppToCore);

	minSpd2CoreData[tObjId]	= App2CoreFreqTrans(pAppToCore,t_pDrvCfgPara->mS_FBSlvcCfg0.m_wMinRunFreq);	
	if(tObjId == 0)
	{
		minVolt2CoreData[tObjId]= App2CoreVoltTrans(pAppToCore,SLVC_MIN_VOLTAGE_M0);	
	}
	else
	{
		minVolt2CoreData[tObjId]= App2CoreVoltTrans(pAppToCore,SLVC_MIN_VOLTAGE_M0);
	}
}


s16 getMinQVoltSetting(u8 tObj)
{
	return minVolt2CoreData[tObj];
}

s16 getMinQSpdSetting(u8 tObj)
{
	return minSpd2CoreData[tObj];
}


s16 getMA_SpeedRef(u8 t_bObjId)    //获取MA给定转速
{
	return (s16)(sS_MACtrProc[t_bObjId].m_pMotorSpeed->wSpeedRef);
}

s16 getMA_Speedfbk(u8 t_bObjId)    //获取MA反馈转速
{	
	return (s16)(sS_MACtrProc[t_bObjId].m_pMotorSpeed->wSpeedfbk);
}
s16 getMA_Speedest(u8 t_bObjId)    //获取MA反馈转速
{	
	return (s16)(sS_MACtrProc[t_bObjId].m_pMotorSpeed->wSpeedEst);
}

s16 getMA_iqset(u8 t_bObjId)    //获取MA iqset
{	
	return (s16)(sS_MACtrProc[t_bObjId].m_nQCurrentSet);
}
s16 getMA_idset(u8 t_bObjId)    //获取MA idset
{	
	return (s16)(sS_MACtrProc[t_bObjId].m_nDCurrentSet);
}
s16 getMA_iqRef(u8 t_bObjId)    //获取MA iqRef
{	
	return (s16)(sS_MACtrProc[t_bObjId].m_nQCur_Reference);
}
s16 getMA_idRef(u8 t_bObjId)    //获取MA idRef
{	
	return (s16)(sS_MACtrProc[t_bObjId].m_nDCur_Reference);
}



/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */



