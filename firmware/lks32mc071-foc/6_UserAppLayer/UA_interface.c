/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： USER_app.c
 * 文件标识：
 * 内容摘要： UA 接口及任务函数
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： Tonghua Li
 * 完成日期： 2022年08月19日
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
extern PSTR_ControlObject getCtrlObjectPtr(u8 objID);
extern void UA_StateMachine(pSTR_UACtrProc pObj);
extern void downloadParaHandle(bool t_bMotorRunning);

#ifdef UA_DEBUG
extern void updateM0DebugUA(pSTR_UACtrProc pObj);
extern void updateM1DebugUA(pSTR_UACtrProc pObj);
#endif


/*******************************************************************************/
//局部静态函数定义区
static bool init_UA_Crtl_Proc(pSTR_UACtrProc pObj);
static void handleUACtrlObj(u8 nuObjID);
static bool init_UA_Crtl_Proc(pSTR_UACtrProc pObj);
static bool initUACtrlObj(void);

/*******************************************************************************/
//局部静态变量定义区
STR_UACtrProc	sS_UACtrlProc[UA_OBJ_MAX_DEFINE];

#ifdef _POLLING_MODE
static u8 t_nuObjID = 0;
#endif


/*******************************************************************************/
/*****************************end***********************************************/


/*******************************************************************************
 函数名称：    u8 get_Max_UAObj_Nbr(void)
 功能描述：    查询控制对象个数
 输入参数：    无
 输出参数：    无
 返 回 值：    返回对象个数
 其它说明：    该函数被外部任务调用，
 			   该函数为对外直接调用函数

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
u8 get_Max_UAObj_Nbr(void)
{
	return UA_OBJ_MAX_DEFINE;
}

/*******************************************************************************
 函数名称：    static bool init_UA_Crtl_Proc(pSTR_UACtrProc pObj)
 功能描述：    按控制对象进行UA初始化处理
 输入参数：    控制对象指针
 输出参数：    无
 返 回 值：    无
 其它说明：    注册数据结构指针、控制对象等
 			   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
static bool init_UA_Crtl_Proc(pSTR_UACtrProc pObj)
{
	bool returnResult = TRUE;	

	// 注册实际的控制对象，根据ID查找
	pObj->mg_pCtrlObj			= getCtrlObjectPtr(pObj->mg_nUACtrlProcID);	
	if(pObj->mg_pCtrlObj == NULL)
	{
		returnResult = FALSE;
	}

	pObj->m_eUASysState			= E_UA_INIT;       // 初始化UA运行状态机
	pObj->m_bPWMStopMode		= pObj->mg_pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_buStopPWMEnable;	// 初始化PWM停止模式

	pObj->m_bFaultAutoClr		= pObj->mg_pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_buFaultAutoClr;	// 初始化故障自动清除
	pObj->m_nuFaultClrPeriod	= pObj->mg_pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_nuFaultClrPrd;	// 初始化故障清除周期
	
	pObj->m_bLoopMode			= pObj->mg_pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_buCtrLoopmode;	// 初始化运行模式
	pObj->m_bStopMode			= pObj->mg_pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_buStopMode;		// 初始化停止模式

	#if 0
	pObj->m_nuFaultClrCnt			= 0;		// 故障清除计数
	pObj->m_StruCmd.m_bFault		= 0;		// UA 故障标志
	pObj->m_StruCmd.m_bFaultClr		= 0;		// UA 故障清除命令
	pObj->m_StruCmd.m_bRunFlag		= 0			// UA 运行命令标志
	pObj->m_StruCmd.m_bMoeEnable	= 0;		// MOE 使能标志
	#endif
	pObj->m_StruCmd.m_bDirRevse		= CW;		// 方向取反命令标志
	
	return returnResult;
}

/*******************************************************************************
 函数名称：    pSTR_UACtrProc	get_UA_CtrPtr(u8 ObjID)
 功能描述：    按控制对象ID进行查询控制对象指针
 输入参数：    按控制对象ID
 输出参数：    无
 返 回 值：    无
 其它说明：    该函数被外部任务调用，
 			   该函数为对外直接调用函数

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
pSTR_UACtrProc	get_UA_CtrPtr(u8 ObjID)
{
	return &sS_UACtrlProc[0];	
}

/*******************************************************************************
 函数名称：    void handleUACtrlObj(u8 nuObjID)
 功能描述：    按控制对象ID进行UA任务处理
 输入参数：    按控制对象ID
 输出参数：    无
 返 回 值：    无
 其它说明：    该函数被外部任务调用，与MA数据交互在该函数内完成
 			   通过共享交互数据区实现
 			   该函数为对外直接调用函数

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
static void handleUACtrlObj(u8 nuObjID)
{
	pSTR_UACtrProc pObj = &sS_UACtrlProc[0];
	
	#ifdef UA_DEBUG
	updateM0DebugUA(pObj);		/* UA层调试指令传递 */
	#endif

	UA_StateMachine(pObj);		/* UA状态机调度 */
}
/*******************************************************************************
 函数名称：    initUACtrlObj()
 功能描述：    按控制对象进行UA任务处理
 输入参数：    控制对象指针
 输出参数：    无
 返 回 值：    无
 其它说明：    注册数据结构指针、控制对象等
 			   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 2022/10/29      V1.1          Tonghua Li          删除motor_ID
 *******************************************************************************/
static bool initUACtrlObj(void)
{
	pSTR_UACtrProc pObj = &sS_UACtrlProc[0];

	memset(pObj, 0, sizeof(STR_UACtrProc));	//全局配置初始化
	pObj->mg_nUACtrlProcID	= 0;
	init_UA_Crtl_Proc(pObj);					//按控制对象进行UA初始化处理

	return TRUE;
}

/*******************************************************************************
 函数名称：    bool checkifUARunning()
 功能描述：    检查是否运行状态
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    TRUE ----- 运行中
 			   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 2022/10/29      V1.1          Tonghua Li          删除motor_ID
 *******************************************************************************/
#if (PARA_DOWNLOAD_ENBALE == FUNCTION_ON)
bool checkifUARunning(void)
{
	pSTR_UACtrProc pObj;	
	pObj	= get_UA_CtrPtr(0);                 //按控制对象ID进行查询控制对象指针
	return (pObj->m_eUASysState == E_UA_RUN);
}
#endif	


/*******************************************************************************
 函数名称：    UACtrlObjTask(void)
 功能描述：    按控制对象进行UA任务处理
 输入参数：    控制对象指针
 输出参数：    无
 返 回 值：    无
 其它说明：    该函数被周期性任务调用，与MA数据交互在该函数内完成
 			   通过共享交互数据区实现
 			   该函数为对外直接调用函数
 			   POLLING_MODE: 	循环调用，每次调用一个
 			   非POLLING_MODE:	一次处理完所有对象
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
void UACtrlObjTask(void)
{
	handleUACtrlObj(0);        //按控制对象ID进行UA任务处理

	#if (PARA_DOWNLOAD_ENBALE == FUNCTION_ON)
	downloadParaHandle(checkifUARunning());    //检验是否能够下载
	#endif
}

/*******************************************************************************
 函数名称：    void InitUsrAppLayer(void)
 功能描述：    进行UA任务处理
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    MA层初始化函数
 			   
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 2022/10/29      V1.1          Tonghua Li          删除motor_ID
 *******************************************************************************/
void InitUsrAppLayer(void)
{
	initUACtrlObj();
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */



