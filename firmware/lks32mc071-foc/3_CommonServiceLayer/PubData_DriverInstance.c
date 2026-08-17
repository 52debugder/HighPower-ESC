#include "project_config.h"
#include "PubData_DriverInstance.h"
#include "MC_Parameter_M0.h"
#include "string.h"


/*******************************************************************************/
//全局变量定义区

/*******************************************************************************/
//外部函数引用区

/*******************************************************************************/
//局部静态函数定义区


/*******************************************************************************/
#if (PARA_DOWNLOAD_ENBALE == FUNCTION_ON)
u8 gs_bDownReqCmd		__attribute__((at(ADDR_DOWNLOAD_WRITE_LOCATION))) = 0;
u8 gs_bDownAckStatus	__attribute__((at(ADDR_DOWNLOAD_READ_LOCATION))) = 0;
u8 gs_bDownloadStatus = 0;
u16 gs_timeCnt;
#endif

//局部静态变量定义区
	//	配置参数通过编译器伪指令放置在指定的FLASH空间

		const STR_DrvCfgPara		tS_DrvCfgPara[MAX_CFG_PARA_ID] __attribute__((at(ADDR_PARA_START_LOCATION))) = {
																DRV_CFG_PARA_TAB_M(0)
																};

//	全局配置参数通过编译器伪指令放置在指定的FLASH空间
volatile const STR_DrvCfgGlobal		tS_DrvCfgGlobal __attribute__((at(ADDR_PARA_LOCATION))) = DRV_CFG_GLOBAL_PARA_TAB;

															 

// FOC 控制对象传递参数数据结构
static bool 				tB_MotorFocParaIsValid 			= FALSE;
static STR_MotorFocParDef 	tS_MotorFocParM[MAX_DRV_MODULE_USED];			// FOC 参数数据结构体


// 物理控制对象
// 建议物理控制对象定义为局部静态变量，对外通过函数getCtrlObjectPtr()索引
// M0固定对应PWM0, M1固定对应PWM1,

const u8	gS_PWMObjDefined[MAX_DRV_MODULE_USED] = {
													DRV0_PWM_ID
												};



STR_ControlObject gS_PhyObjInstanceM[MAX_DRV_MODULE_USED];

// tS_DrvCfgPara[]与gS_PhyObjInstanceM[] 下标默认对应，应用中可代码重新映射

/*
对象映射对应关系
	gS_PhyObjInstanceM[n]
	
							tS_DrvCfgPara[m]
												   ----------	sS_UACtrlProc[id]	
												|
												|
							gS_PhyObjInstanceM[id]  ----------	commom layer
									|
									|
										----------				sS_MACtrProc[id]
									|
									|
										----------			     gS_FocObjM[id] 
									|						          |
									|						          |
									|
										----------				gS_MotorHalDrvHandleM[id] 驱动
														
*
*/



/*******************************************************************************/
/*****************************end***********************************************/

u8	getPWMIDUsed(u8 objID)
{
	#ifdef PWM_MODULE_DYNAMIC_CONFIG
	return tS_DrvCfgPara.mS_GlobalCfg.m_bPWMUsedID;
	#else
	return gS_PWMObjDefined[objID];
	#endif
}
/*****************************************************************************
 * 函数名   : bool initGlobalPhyObj(void)
 * 说明     : 共用控制对象配置初始化
 *			: m_bPWM_Id为当前的PWM配置 0 ---- PWM0 
 * 设计思路 ：变量配置
 *			：初始化gS_PhyObjInstanceM[]全局变量，tS_MotorFocParM内容由MA初始化
 * 参数     ：无
 * 返回值   ：
 * 修改时间 ：2022.10.27
 *****************************************************************************/
void initGlobalPhyObj(void)
{
	u8 t_nuObjID;
	for(t_nuObjID = 0;t_nuObjID < MAX_DRV_MODULE_USED; t_nuObjID++)
	{
		memset(&gS_PhyObjInstanceM[t_nuObjID],0,sizeof(STR_ControlObject));		
		gS_PhyObjInstanceM[t_nuObjID].m_pMotorFocPar	= &tS_MotorFocParM[t_nuObjID];	//	初始化FOC参数结构体指针
		gS_PhyObjInstanceM[t_nuObjID].m_pDrvCfgPara 	= &tS_DrvCfgPara[t_nuObjID];	//	初始化配置参数结构体指针
		gS_PhyObjInstanceM[t_nuObjID].m_bPWM_Id			= getPWMIDUsed(t_nuObjID);		//	初始化当前对象对应PWM的ID
	}
}

/*****************************************************************************
 * 函数名   : bool checkParaCfgValid(void)
 * 说明     : 校验配置参数是否有效
 *			:  
 * 设计思路 ：变量配置
 *			：
 * 参数     ：无
 * 返回值   ：
 * 修改时间 ：2023.01.29
 *****************************************************************************/
bool checkParaCfgValid(void)
{
	#if (PARA_CHECK_ENBALE == FUNCTION_ON)
	if((tS_DrvCfgGlobal.header == PARA_CFG_HEADER)
		&& (tS_DrvCfgGlobal.mainVersion == PARA_CFG_MAIN_VERSION)
		&& (tS_DrvCfgGlobal.version == PARA_CFG_VERSION)
		&& (tS_DrvCfgGlobal.subversion == PARA_CFG_SUB_VERSION)
		&& (tS_DrvCfgGlobal.length == PARA_CFG_LENGTH)
		&& (tS_DrvCfgGlobal.objNumber == PARA_CFG_NUMBER)
		)
	{
				//	校验配置参数的头、版本号、数据长度等信息
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	#else
	
		return TRUE;	
	#endif
}

/*****************************************************************************
 * 函数名   : bool ifMotorFOCParaIsValid (void)
 * 说明     : MD层库接口变量是否有效
 * 设计思路 ：变量配置
 * 参数     ：无
 * 返回值   ：TRUE OR FALSE
 * 修改时间 ：2022.09.16
 *****************************************************************************/

bool ifMotorFOCParaIsValid (void)
{
	return tB_MotorFocParaIsValid;
}
/*****************************************************************************
 * 函数名   : void updateMotorFocPara(void)
 * 说明     : MD层库接口变量配置
 * 设计思路 ：变量配置
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2022.09.16
 *****************************************************************************/
void updateMotorFocPara(void)
{
	// 信号量锁定 
	tB_MotorFocParaIsValid	= FALSE;

	// add 初始化MD层库接口变量配置

	// 配置完成设置为有效
	tB_MotorFocParaIsValid	= TRUE;
	// 信号量解锁
}

/*****************************************************************************
 * 函数名   : void BondingMotorDrvObject(void)
 * 说明     : 绑定 MD层库接口变量配置 和 参数配置
 * 设计思路 ：配置绑定
 *			绑定配置参数到物理控制对象，默认	配置参数0 --- 控制对象0
 *									配置参数1 --- 控制对象1
 *										..............
 *									配置参数n --- 控制对象n
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2022.09.16 V0.01 By Tonghua Li
 * 修改时间 ：2022.11.01 V0.02 By Tonghua Li
 *****************************************************************************/
void BondingMotorDrvObject(void)
{
	initGlobalPhyObj();	
}

/*****************************************************************************
 * 函数名   : bool reBondingMotorDriveParaDat(u8 objID, u8 objCfgID)
 * 说明     : 重绑定 参数配置
 * 设计思路 ：根据参数配置ID对对象ID进行配置绑定
 *			: 重绑定后需要进行参数初始化，由调用者实现
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2022.09.16 V0.01 By Tonghua Li
 * 修改时间 ：2022.11.01 V0.02 By Tonghua Li
 *****************************************************************************/

// 如果存在多对一的绑定时，如单板支持多个电机、只能运行单电机，初始化时重定义 

// 由于gS_PhyObjInstanceM[objID]与PWM_ID通过编译宏方式实现，MD/HD层不支持动态绑定
// 目前仅支持修改gS_PhyObjInstanceM[objID]与PWM_ID对应的参数配置组m_pDrvCfgPara
bool reBondingMotorDriveParaDat(u8 objID, u8 objCfgID)
{
	bool bResult = FALSE;
	if(objID >= MAX_DRV_MODULE_USED)
	{
		return bResult;
	}
	if(objCfgID < MAX_CFG_PARA_ID)
	{		
		gS_PhyObjInstanceM[objID].m_pDrvCfgPara		= &tS_DrvCfgPara[objCfgID];
	}

	return bResult;	
}

/*****************************************************************************
 * 函数名   : bool reBondingMotorDrvObject(u8 objID, u8 objCfgID)
 * 说明     : 重绑定 MD层库接口变量配置 和 参数配置
 * 设计思路 ：通过objID查找控制对象指针
 * 参数     ：objID
 * 返回值   ：控制对象指针
 * 修改时间 ：2022.09.16 V0.01 By Tonghua Li
 * 修改时间 ：2022.10.27 V0.02 By Tonghua Li
 *****************************************************************************/

PSTR_ControlObject getCtrlObjectPtr(u8 objID)
{
	if(objID >= MAX_DRV_MODULE_USED)
	{
		return NULL;
	}
	return &gS_PhyObjInstanceM[objID];
}


PSTR_DrvCfgPara getCfgParaPtr(u8 objID)
{
	if(objID >= MAX_DRV_MODULE_USED)
	{
		return NULL;
	}
	return gS_PhyObjInstanceM[objID].m_pDrvCfgPara;
}

u8 getCtrlObjectID(u8 PWM_ID)
{
	u8 t_nuObjID;
	for(t_nuObjID = 0;t_nuObjID < MAX_DRV_MODULE_USED; t_nuObjID++)
	{		
		if(gS_PhyObjInstanceM[t_nuObjID].m_bPWM_Id == PWM_ID)
		{
			return t_nuObjID;
		}
	}

	return t_nuObjID;	
}


s16 getParaVFCompCofig(u8 t_bObjId)
{
	PSTR_DrvCfgPara			t_pDrvCfgPara;
	t_pDrvCfgPara	= gS_PhyObjInstanceM[t_bObjId].m_pDrvCfgPara;
	return t_pDrvCfgPara->mS_FBSlvcCfg0.m_VFDeadZoneComp;
}

/*****************************************************************************
 * 函数名   : void downloadParaHandle(bool t_bMotorRunning)
 * 说明     : 检验是否能够下载
 * 设计思路 ：是否能够下载，电机静止时允许下载。通过约定的字节序进行判断
 * 参数     ：t_bMotorRunning
 * 返回值   ：void
 * 修改时间 ：2023.02.09 V0.01 By Tonghua Li
 * 修改时间 ：
 *****************************************************************************/
#if (PARA_DOWNLOAD_ENBALE == FUNCTION_ON)
void downloadParaHandle(bool t_bMotorRunning)
{
	switch (gs_bDownloadStatus)
	{
		case  0:			// Step 1
		{
			if(gs_bDownReqCmd == DOWNLOAD_WRITE_REQ1)
			{
				gs_bDownAckStatus = DOWNLOAD_READ_ACK1;
				gs_timeCnt++;
				if(gs_timeCnt >= DOWNLOAD_WRITE_REQ_TIME_OUT)
				{
					gs_timeCnt = 0;
				}
			}
			else
			{ 
				if((gs_bDownReqCmd == DOWNLOAD_WRITE_REQ2) && (gs_timeCnt != 0))
				{					
					gs_bDownloadStatus  = 1;
				}
				else
				{
					gs_bDownAckStatus = DOWNLOAD_READ_ACK_INVLAD;
				}
				gs_timeCnt			= 0;
			}
			break;
		}

		case  1:			// Step 2
		{
			if(gs_bDownReqCmd == DOWNLOAD_WRITE_REQ2)
			{
				gs_bDownAckStatus = DOWNLOAD_READ_ACK2;
				gs_timeCnt++;
				if(gs_timeCnt >= DOWNLOAD_WRITE_REQ_TIME_OUT)
				{
					gs_timeCnt = 0;
				}
			}
			else
			{				
				if((gs_bDownReqCmd == DOWNLOAD_WRITE_REQ3) && (gs_timeCnt != 0))
				{	
					if(!t_bMotorRunning)
					{
						gs_timeCnt			= DOWNLOAD_STOP_WAIT_MS;
					}
					gs_bDownloadStatus  = 2;
				}
				else
				{
					gs_bDownloadStatus	= 0;
					gs_timeCnt			= 0;
					gs_bDownAckStatus	= DOWNLOAD_READ_ACK_INVLAD;
				}				
			}
			break;
		}

		case  2:							// Step 3
		{
			if(gs_bDownReqCmd == DOWNLOAD_WRITE_REQ3)
			{
				if(!t_bMotorRunning)		// Can be downloaded
				{
					gs_timeCnt++;
					if(gs_timeCnt >= DOWNLOAD_STOP_WAIT_MS)		//等待时间到达
					{
						gs_bDownAckStatus = DOWNLOAD_READ_ACKOK;
					}
				}
				else						// Wait to stop
				{
					gs_timeCnt = 0;
					gs_bDownAckStatus = DOWNLOAD_READ_ACK_DOING;
				}
			}
			else
			{
				gs_bDownloadStatus	= 0;
				gs_bDownAckStatus	= DOWNLOAD_READ_ACK_INVLAD;
			}
			break;
		}

		default:
		{
			gs_bDownloadStatus  = 0;
			gs_timeCnt			= 0;
			gs_bDownAckStatus	= DOWNLOAD_READ_ACK_INVLAD;
			break;
		}
	}
}

bool checkIfDownload(void)
{
	return (gs_bDownloadStatus == 2);
}
#endif

///////////////////////
