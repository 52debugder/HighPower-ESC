/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： AppFunction.c
 * 文件标识：
 * 内容摘要： UA状态机管理及状态机函数调用
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： Tonghua Li
 * 完成日期： 2022年08月19日
 *
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "project_config.h"
#include "PubData_MA_UA.h"
#include "MC_Math.h"
#include "MC_type.h"
#include "Time_Process.h"
#include "UA_Data.h"
#include "string.h"


/*******************************************************************************/
//全局变量定义区



/*******************************************************************************/
//外部函数引用区
extern pSTR_UACtrProc getUACtrlProcPtr(u8 uaID);
#if (PARA_DOWNLOAD_ENBALE == FUNCTION_ON)
extern bool checkIfDownload(void);
#endif
extern void updateUASetpoint(pSTR_UACtrProc pObj);
extern ENUM_MotorBrakeMode getFaultBrakeMode4UA(pSTR_UACtrProc pObj);
extern ENUM_MotorBrakeMode getBrakeMode4UA(pSTR_UACtrProc pObj);
extern s16 getGearRatio4UA(pSTR_UACtrProc pObj);

/*******************************************************************************/
//局部静态函数定义区
#if  (UA_CFG_DONT_USED == FALSE)
static void UAConfig(pSTR_UACtrProc pObj);
#endif
static void UARunCmdHandle(pSTR_UACtrProc pObj);
static void UAStopCmdHandle(pSTR_UACtrProc pObj);
static void UAStoppingCmdHandle(pSTR_UACtrProc pObj);
static void UAClrFaultCmdHandle(pSTR_UACtrProc pObj);
static void UAFaultStopHandle(pSTR_UACtrProc pObj);
static bool IfUARunCmd(pSTR_UACtrProc pObj);
static bool IfUAStopCmd(pSTR_UACtrProc pObj);


/*******************************************************************************/
//局部静态变量定义区


/*******************************************************************************/
/*****************************end***********************************************/


/*******************************************************************************
 函数名称：    UA_StateMachine_Handle(u8 uaID)
 功能描述：    UA状态机
 输入参数：    pSTR_UACtrProc pObj
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
void UA_StateMachine(pSTR_UACtrProc pObj)
{
	STR_PubDatMAUA			*pMA2UA = &pObj->mMaToUa;
	
  pObj->mg_pCtrlObj->mGlobalDatPackage.mMaToUa.SR.Bit.locked = 1;	   //应用标志锁定
	memcpy(pMA2UA,&pObj->mg_pCtrlObj->mGlobalDatPackage.mMaToUa,sizeof(STR_PubDatMAUA));
	pObj->mg_pCtrlObj->mGlobalDatPackage.mMaToUa.SR.Bit.locked = 0;    //应用标志解除

    if( HasFaultFromMA(pMA2UA) || (pObj->m_StruCmd.m_bFault == 1) )
    {
        pObj->m_eUASysState	= E_UA_FAULT;			//	设置为FAULT状态
    }
	else
	{
		if( !IfPostFinishFromMA(pMA2UA) )
	 	{
			pObj->m_eUASysState	= E_UA_INIT;		//	MA层POST未完成时为INIT状态
	 	}
	}

	switch ( pObj->m_eUASysState)					//	UA状态机任务调度
	{
	    case E_UA_INIT:
	    {  /* UA状态机初始状态 */ 
			
			#if  (UA_CFG_DONT_USED == TRUE)
			if(IfPostFinishFromMA(pMA2UA))
            {
                pObj->m_eUASysState			= E_UA_STOP;    /* UA状态机停止状态 */
            }
			#else			
            if(IfWaitCfgFromMA(pMA2UA))			//	需要参数配置时，根据应用添加参数配置逻辑处理
            {
                UAConfig(pObj);
            }

            if(IfCfgFinishFromMA(pMA2UA) && IfPostFinishFromMA(pMA2UA))
            {
                pObj->m_eUASysState			= E_UA_STOP;
            }
			#endif
	        break;
	    } 
		
	    case E_UA_STOP:
	    {   /* UA状态机停止状态 */
            if(IfUARunCmd(pObj))	
			{
				UARunCmdHandle(pObj);					//	运行指令传递
				if(IsRunningFromMA(pMA2UA))				//	MA层回传running状态
				{
					pObj->m_eUASysState	= E_UA_RUN;		/* UA状态机运行状态 */
				}
			}
            else
			{
				UAStopCmdHandle(pObj);          		//	UA层停止命令处理
			}
	        break;
		}

	    case E_UA_RUN:
	    {  /* UA状态机运行状态 */
			#if (PARA_DOWNLOAD_ENBALE == FUNCTION_ON)
			if(checkIfDownload())			// 参数下载时，停机 
			{
				pObj->m_StruCmd.m_bDownLoadStart = 1;
				pObj->m_StruCmd.m_bRunFlag = 0;
			}
			#endif

			if(IfUAStopCmd(pObj))						//	停止指令
			{
				UAStoppingCmdHandle(pObj);

				if( IsStoppedFromMA(pMA2UA) )
				{
					pObj->m_eUASysState	= E_UA_STOP;	/* UA状态机停止状态 */
				}
			}
			else					 //运行指令
			{
				UARunCmdHandle(pObj);					//运行指令处理
			}
	        break;
	    }

	    case E_UA_FAULT:
	    {  /* UA状态机故障状态 */
			if(pObj->m_StruCmd.m_bFault == 1)			//	存在报警故障
	    {
				UAFaultStopHandle(pObj);				//	故障停止处理
			}
			else
			{			 
				if( NoFaultCodeFromMA(pMA2UA) ) 			//	MA层故障解除，开始故障清除计数，准备清除故障标志位
				{
					if(HasFaultBitFromMA(pMA2UA))
		            {
		                if( IsStoppedFromMA(pMA2UA) )
		                {
		                	if((pObj->m_bFaultAutoClr == 1) || (pObj->m_StruCmd.m_bFaultClr == 1))
		                	{
			                    pObj->m_nuFaultClrCnt++;
			                    if(pObj->m_nuFaultClrCnt >= pObj->m_nuFaultClrPeriod)
			                    {
			                        pObj->m_nuFaultClrCnt	= pObj->m_nuFaultClrPeriod;
						            UAClrFaultCmdHandle(pObj); //故障清除函数
			                    }
		                	}
		                }
		                else
		                {
							pObj->m_nuFaultClrCnt		= 0;   /*故障清除计数*/
		                }
					}
					else
		            {
		            	pObj->m_nuFaultClrCnt			= 0;
						pObj->m_eUASysState				= E_UA_STOP;	                
		            }
				}
				else 			 //MA层故障存在，进行故障处理
				{
					UAFaultStopHandle(pObj);
				}
			}
	        break;
	    }

	    default:
		{
			pObj->m_eUASysState				= E_UA_INIT;    //状态机默认初始状态
			break;
		}
	}

	pObj->mg_pCtrlObj->mGlobalDatPackage.mUaToMa.gWrFlag = 1;
	memcpy(&pObj->mg_pCtrlObj->mGlobalDatPackage.mUaToMa,&pObj->mUaToMa,sizeof(STR_PubDatUAMA));
	pObj->mg_pCtrlObj->mGlobalDatPackage.mUaToMa.gWrFlag = 0;
}


/*******************************************************************************
 函数名称：    static void UAConfig(pSTR_UACtrProc pObj)
 功能描述：    静态函数
 输入参数：    pSTR_UACtrProc pObj
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
#if  (UA_CFG_DONT_USED == FALSE)
static void UAConfig(pSTR_UACtrProc pObj)
{
	pObj->mUaToMa.nGearRatio	= getGearRatio4UA(pObj);	 //UA指令处理函数
}
#endif



/***********************************单电机指令处理*****************************************/
/*******************************************************************************
 函数名称：    static void UARunCmdHandle(pSTR_UACtrProc pObj)		 
 功能描述：    运行指令处理函数
 输入参数：    pSTR_UACtrProc pObj
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
static void UARunCmdHandle(pSTR_UACtrProc pObj)
{
	#if (DRV0_CLOSE_LOOP == SPEED_LOOP)      //转速环控制
	{
		if(pObj->m_StruCmd.m_bDirRevse == 1)
		{
			pObj->mUaToMa.eAppCmd	= E_CMD_MOTOR_SPEED_RUN_REV;  // 运行电机, 速度模式，转动方向与设定方向相反
		}
		else
		{
			pObj->mUaToMa.eAppCmd	= E_CMD_MOTOR_SPEED_RUN;     // 运行电机, 速度模式，转动方向与设定方向相同
		}
	}
	#elif (DRV0_CLOSE_LOOP == CURRENT_LOOP)  //电流环控制
	{
		if(pObj->m_StruCmd.m_bDirRevse == 1)
		{
			pObj->mUaToMa.eAppCmd	= E_CMD_MOTOR_TORQUE_RUN_REV; // 运行电机, 转矩模式，转动方向与设定方向相反
		}
		else
		{
			pObj->mUaToMa.eAppCmd	= E_CMD_MOTOR_TORQUE_RUN;     // 运行电机, 转矩模式，转动方向与设定方向相同
		}
	}
	#elif (DRV0_CLOSE_LOOP == POWER_LOOP)   //功率环控制
	{
		if(pObj->m_StruCmd.m_bDirRevse == 1)
		{
			pObj->mUaToMa.eAppCmd	= E_CMD_MOTOR_POWER_RUN_REV;  // 运行电机, 功率模式，转动方向与设定方向相反
		}
		else
		{
			pObj->mUaToMa.eAppCmd	= E_CMD_MOTOR_POWER_RUN;      // 运行电机, 功率模式，转动方向与设定方向相同
		}
	}
	#else
		#if (DRV0_PWM_ENABLE_STOP == TRUE)
			pObj->mUaToMa.eAppCmd	= E_CMD_MOTOR_STOP;          // 停止电机
		#else
			pObj->mUaToMa.eAppCmd	= E_CMD_MOTOR_STOP_MOE_OFF;  // 关闭MOE
		#endif	
	#endif
	
	updateUASetpoint(pObj);                                //UA指令处理函数
	pObj->mUaToMa.nGearRatio	= getGearRatio4UA(pObj);
}

/*******************************************************************************
 函数名称：    static void UAStopCmdHandle(pSTR_UACtrProc pObj)		 
 功能描述：    运行指令处理函数
 输入参数：    pSTR_UACtrProc pObj
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
static void UAStopCmdHandle(pSTR_UACtrProc pObj)
{
	#if (DRV0_PWM_ENABLE_STOP == TRUE)
		pObj->mUaToMa.eAppCmd	= E_CMD_MOTOR_STOP;			//	停止电机
	#else
		pObj->mUaToMa.eAppCmd	= E_CMD_MOTOR_STOP_MOE_OFF;	//	关闭MOE
	#endif
	
	updateUASetpoint(pObj);									//	UA指令处理函数
	pObj->mUaToMa.eBrakeMode	= getBrakeMode4UA(pObj);	//	UA刹车指令处理函数
	
}

/*******************************************************************************
 函数名称：    static void UAClrFaultCmdHandle(pSTR_UACtrProc pObj)		 
 功能描述：    故障清除处理函数
 输入参数：    pSTR_UACtrProc pObj
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
static void UAClrFaultCmdHandle(pSTR_UACtrProc pObj)
{
	#if (DRV0_PWM_ENABLE_STOP == TRUE)
	{
		pObj->mUaToMa.eAppCmd	= E_CMD_MOTOR_FAULT_CLR_ENMOE;		// 报警清除 MOE使能
	}
	#else
	{
		pObj->mUaToMa.eAppCmd	= E_CMD_MOTOR_FAULT_CLR_DIMOE;		// 报警清除 MOE关闭
	}
	#endif
	updateUASetpoint(pObj);											//UA指令处理函数
	pObj->mUaToMa.eBrakeMode	= getFaultBrakeMode4UA(pObj);		//UA故障刹车指令处理函数
}

/*******************************************************************************
 函数名称：    static void UAStoppingCmdHandle(pSTR_UACtrProc pObj)		 
 功能描述：    停止指令处理函数
 输入参数：    pSTR_UACtrProc pObj
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
static void UAStoppingCmdHandle(pSTR_UACtrProc pObj)
{
	pObj->mUaToMa.eBrakeMode	= getFaultBrakeMode4UA(pObj);	//	UA故障刹车指令处理函数

	#if (DRV0_STOP_MODE == 0)
		pObj->mUaToMa.eAppCmd	= E_CMD_MOTOR_STOP_MOE_OFF;		//	关闭MOE
	#else
		pObj->mUaToMa.eAppCmd	= E_CMD_MOTOR_STOP;				//	停止电机
	#endif
	
	updateUASetpoint(pObj);										//	UA指令处理函数
}

/*******************************************************************************
 函数名称：    static void UAFaultStopHandle(pSTR_UACtrProc pObj)		 
 功能描述：    故障指令处理函数
 输入参数：    pSTR_UACtrProc pObj
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           Tonghua Li          创建
 *******************************************************************************/
static void UAFaultStopHandle(pSTR_UACtrProc pObj)
{
	pObj->mUaToMa.eBrakeMode	= getFaultBrakeMode4UA(pObj);	//UA故障刹车指令处理函数
	
	#if (DRV0_STOP_MODE == 0)
		pObj->mUaToMa.eAppCmd	= E_CMD_MOTOR_STOP_MOE_OFF;		// 关闭MOE
	#else
		pObj->mUaToMa.eAppCmd	= E_CMD_MOTOR_STOP;				// 停止电机
	#endif
	
	updateUASetpoint(pObj);										//UA指令处理函数
}

/*******************************************************************************
 函数名称：    IfUARunCmd(pSTR_UACtrProc pObj) 
 功能描述：    UA层运行指令传递
 输入参数：    pSTR_UACtrProc 
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/16      V1.0       Wencai.Zhao				创建
 *******************************************************************************/
static bool IfUARunCmd(pSTR_UACtrProc pObj)
{
	if( pObj->m_StruCmd.m_bMoeEnable)
	{
		return pObj->m_StruCmd.m_bRunFlag;
	}
	else
	{
		return FALSE;
	}
}

/*******************************************************************************
 函数名称：    UAFaultStopHandle(pSTR_UACtrProc pObj) 
 功能描述：    UA层停止指令传递
 输入参数：    pSTR_UACtrProc 
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/16      V1.0       Wencai.Zhao				创建
 *******************************************************************************/
static bool IfUAStopCmd(pSTR_UACtrProc pObj)
{
	if( pObj->m_StruCmd.m_bMoeEnable)
	{
		return (pObj->m_StruCmd.m_bRunFlag == 0);
	}
	else
	{
		return TRUE;
	}
}

///////////////////////////////////////////////////
/************************ (C) Bright Power Semiconductor Co.ltd *****END OF FILE****/
