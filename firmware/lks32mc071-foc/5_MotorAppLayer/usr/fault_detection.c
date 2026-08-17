/*******************************************************************************
 * 版权所有 (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： fault_detection.c
 * 文件标识：
 * 内容摘要： fault detectiong: volt ,current, temperature, stall, empty, phaseloss,\
 *
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： andrew kong
 * 完成日期： 2019年11月28日
 * 修改历史:
 *				2022-11-22 添加报警参数配置功能，修改部分报警代码，Li Tonghua
 *******************************************************************************/
#include "fault_detection.h"
#include "MC_type.h"
#include "MC_math.h"
#include "MA_Static_Variable.h"
#include "state_machine.h"

/*******************************************************************************/
//外部函数引用区
extern PSTR_MACtrProc	directGetMACtrPtr(u8 ObjID);
extern s16 getMotorCurFromObjId1ms(u8 t_bObjId);
extern s32 getVolt2FreqCalcPara(u8 t_bObjId);
extern s16 getMotorActVoltFromObjId1ms(u8 t_bObjId);


/*******************************************************************************/
//局部静态全局变量或函数定义区
static void CurrentAmplitudeCalc(STR_VectorUVW *pstruCurrPhaseUVW, STR_MACtrProc *pObj);

/*******************************************************************************/

static void updateFaultInfo2MACtrl(STR_MACtrProc *pObj)
{
	pObj->mg_UFault.R		= pObj->m_pFaults->R;		//	更新错误标志
	pObj->mg_eFaultPrio		= E_FAULT_PRIO_HIGH;		//	设置级别高
	pObj->mg_eFaultStopMode = E_STOP_MOE_OFF;			//	关闭MOE停止电机
}

/*****************************************************************************
 * 函数名   : FaultCurrentCheck(STR_VectorUVW *pstruCurrent, u8 t_bObj_ID)
 * 说明     : 软件过流检测
 * 设计思路 ：1. 如果三相电流绝对值超过设定的软件过流值，则判定为软件过流。
 * 参数     ：STR_VectorUVW *pstruCurrent, u8 t_bObj_ID
 * 返回值   ：无
 * 修改时间 ：2022.11.22
 * 修改时间 ：2023.09.04
 *             在AD中调用时，会花费查找MA指针的时间
 *			   如果对时限要求不严格，在1ms中调用执行FaultCurrentCheckMA()
 *****************************************************************************/
void FaultCurrentCheck(STR_VectorUVW *pstruCurrent, u8 t_bObj_ID)
{
	PSTR_MACtrProc pObj = directGetMACtrPtr(t_bObj_ID);
	PSTR_DrvCfgPara	pDrvCfgPara = pObj->mg_pCtrlObj->m_pDrvCfgPara;
	
    /*三相电流瞬时值大于设定阈值，累加一定时间后判断为软件过流*/
    if((ABS(pstruCurrent->nPhaseU) > pObj->m_pFaultValue->nOverCurrent) 
		|| (ABS(pstruCurrent->nPhaseV) > pObj->m_pFaultValue->nOverCurrent) 
		|| (ABS(pstruCurrent->nPhaseW) > pObj->m_pFaultValue->nOverCurrent)
		)
    {
    	if(pObj->m_pstruFaultCurrentTime->nCheckCnt1++ >= pDrvCfgPara->mS_FBCurSense.nSoftOvCurTimes)
    	{
            pObj->m_pFaults->B.SoftCurretError = 1;				/*软件过流标志置1*/
    	}
    }
	else
	{
		pObj->m_pstruFaultCurrentTime->nCheckCnt1 = 0;
	}
}

/*****************************************************************************
 * 函数名   : FaultCurrentCheckMA(STR_VectorUVW *pstruCurrent, PSTR_MACtrProc pObj)
 * 说明     : 软件过流检测
 * 设计思路 ：1. 如果三相电流绝对值超过设定的软件过流值，则判定为软件过流。
 * 参数     ：STR_VectorUVW *pstruCurrent, PSTR_MACtrProc pObj
 * 返回值   ：无
 * 修改时间 ：2022.11.22
 * 修改时间 ：2023.09.04
 *             在AD中调用时，会花费查找MA指针的时间
 *             如果对时限要求不严格，在1ms中调用执行FaultCurrentCheckMA()
 *****************************************************************************/
static void FaultCurrentCheckMA(STR_VectorUVW *pstruCurrent, PSTR_MACtrProc pObj)
{
	PSTR_DrvCfgPara	pDrvCfgPara = pObj->mg_pCtrlObj->m_pDrvCfgPara;
	
    /*三相电流瞬时值大于设定阈值，累加一定时间后判断为软件过流*/
    if((ABS(pstruCurrent->nPhaseU) > pObj->m_pFaultValue->nOverCurrent) 
		|| (ABS(pstruCurrent->nPhaseV) > pObj->m_pFaultValue->nOverCurrent) 
		|| (ABS(pstruCurrent->nPhaseW) > pObj->m_pFaultValue->nOverCurrent))
    {
        if(pObj->m_pstruFaultCurrentTime->nCheckCnt1++ >= pDrvCfgPara->mS_FBCurSense.nSoftOvCurTimes)         /*软件过流标志置1*/
    	{
			pObj->m_pFaults->B.SoftCurretError = 1;			/*软件过流标志置1*/
    	}
    }
	else
	{
		pObj->m_pstruFaultCurrentTime->nCheckCnt1 = 0;
	}
}

/*****************************************************************************
 * 函数名   : FaultVoltageCheck(STR_MACtrProc *pObj)
 * 说明     : 过欠压检测 
 * 设计思路 ：1.当母线电压大于过压设定值则判定为过压故障;当母线电压小于欠压设定值 \
 *              则判定为欠压故障。滤波时间为1s，这个可根据实际需求修改。
 * 参数     ：STR_MACtrProc *pObj
 * 返回值   ：无
 * 修改时间 ：2022.11.22
 * 修改时间 ：2023.09.04
 *****************************************************************************/
static void FaultVoltageCheck(STR_MACtrProc *pObj)
{
	PSTR_DrvCfgPara	pDrvCfgPara = pObj->mg_pCtrlObj->m_pDrvCfgPara;
	STR_FaultTime 			*pFaultVoltTime		= pObj->m_pstruFaultVoltTime;
	STR_FaultStatus			*t_pFaults			= pObj->m_pFaults;
	STR_FaultVariable		*t_pFaultValue		= pObj->m_pFaultValue;
	s16 					t_nVdc 				= pObj->mMdToMa.nVdc ;
	
	
    if(t_nVdc >= t_pFaultValue->nOverVoltage)    	/*母线电压大于过压设定值则时间累加*/
    {
        pFaultVoltTime->nCheckCnt1 += FAULT_DETECT_CYCLE;
    }
    else if(t_nVdc < t_pFaultValue->nUnderVoltage) /* 母线电压小于欠压设定值则时间累加*/
    {
        pFaultVoltTime->nCheckCnt2 += FAULT_DETECT_CYCLE;
    }
    else
    {
        pFaultVoltTime->nCheckCnt1 = 0;				// 电压正常清0
        pFaultVoltTime->nCheckCnt2 = 0;
    }	
	
    if(pFaultVoltTime->nCheckCnt1 >= pDrvCfgPara->mS_FBDcUnit0.nOvVoltageDetectTime)	/* 时间超过阈值则判定为过压 */ 
    {																					/* pDrvCfgPara->mS_FBDcUnit0.nOvVoltageDetectTime * 5ms */
        pFaultVoltTime->nCheckCnt1 = 0;
        t_pFaults->B.VoltOverError = 1;													/* 过压错误标志位置1 */
    }

    if(pFaultVoltTime->nCheckCnt2 >= pDrvCfgPara->mS_FBDcUnit0.nUndVoltageDetectTime)	/* 时间超过阈值则判定为欠压 */
    {																					/* pDrvCfgPara->mS_FBDcUnit0.nUndVoltageDetectTime * 5ms */
        pFaultVoltTime->nCheckCnt2 = 0;
        t_pFaults->B.VoltUnderError = 1;												/*欠压错误标志位置1 */
    }

	
                                                                                                 
	if(pDrvCfgPara->mS_FBDcUnit0.bUndVoltProtectEnbale == 0)							/* 欠压检测不使能则清零 */
	{
		pFaultVoltTime->nCheckCnt2	= 0;
		t_pFaults->B.VoltUnderError	= 0;
	}
	
	if(pDrvCfgPara->mS_FBDcUnit0.bOvVoltProtectEnbale == 0)								/* 过压检测不使能则清零 */
	{
		pFaultVoltTime->nCheckCnt1	= 0;
		t_pFaults->B.VoltOverError	= 0;
	}
}


/*****************************************************************************
 * 函数名   : FaultEmptyCheck(STR_MACtrProc *pObj)
 * 说明     : 离水空转检测，水泵应用，其他应用可以不使能
 * 设计思路 ：1.如果Iq小于空转电流设定值，并且转速大于空转转速设定值，则判定为离水空转。\
 *              滤波时间为1s，这个可根据实际需求修改。 
 * 参数     ：STR_MACtrProc *pObj
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 * 修改时间 ：2023.09.04
 *****************************************************************************/
static void FaultEmptyCheck(STR_MACtrProc *pObj)
{
	PSTR_DrvCfgPara	pDrvCfgPara = pObj->mg_pCtrlObj->m_pDrvCfgPara;
	STR_FaultTime		*pFaultEmptyTime 	= pObj->m_pstruFaultEmptyTime;
	
	if(pDrvCfgPara->mS_FBEmptyStall.bEmptyProtectEnable == 1)
	{
	    if((ABS(pObj->m_nQCur_Reference) < pObj->m_pFaultValue->nEmptyCurrent) 
			&& (ABS(pObj->mMdToMa.wFreq) > pObj->m_pFaultValue->wEmptySpeed))		/*如果Iq小于设定值，转速大于设定值则时间累加，否则时间清0 */
	    {
	       pFaultEmptyTime->nCheckCnt1 += FAULT_DETECT_CYCLE;
	    }
	    else
	    {
	        pFaultEmptyTime->nCheckCnt1 = 0;
	    }

		

	    if(pFaultEmptyTime->nCheckCnt1 >= pDrvCfgPara->mS_FBEmptyStall.nEmptyDetectTime)  //累加时间超过* 5ms 则判定为离水空转
	    {
	        pFaultEmptyTime->nCheckCnt1 = 0;
	        pObj->m_pFaults->B.EmptyError = 1;						//空转错误标志位置1
	    }
	}
	else
	{
		pFaultEmptyTime->nCheckCnt1 = 0;
		pObj->m_pFaults->B.EmptyError = 0;       					//空转错误标志位置0
	}
}

/*****************************************************************************
 * 函数名   : FaultStallCheck(STR_MACtrProc *pObj)
 * 说明     : 堵转&启动检测
 * 设计思路 ：
 *            1.转速和电压比例异常则判定为堵转 ;                 \
 *            2.在启动检测时效内判定为启动故障，否则判定为堵转   \
 * 参数     ：STR_MACtrProc *pObj
 * 返回值   ：无
 * 修改时间 ：2022.11.24
 * 修改时间 ：2023.09.04
 *****************************************************************************/
static void FaultStallCheck(STR_MACtrProc *pObj)
{
	PSTR_DrvCfgPara	pDrvCfgPara		= pObj->mg_pCtrlObj->m_pDrvCfgPara;
	STR_FaultTime		*pStallFaultTime 	= pObj->m_pstruFaultStallTime;
	STR_FaultVariable	*pFaultValue		= pObj->m_pFaultValue;

	s32 wSpeedfbkABS;
	s32 wSpeedfromVolt;
	s32 wSpeedfromVolt1;

	wSpeedfbkABS	= ABS(pObj->m_pMotorSpeed->wSpeedfbk);
	

	s16 t_nCurrent		= getMotorCurFromObjId1ms(pObj->mg_nMACtrlProcID);
	
	
	if(pDrvCfgPara->mS_FBEmptyStall.bStallProtectEnable== 1)
	{
	    if(pStallFaultTime->nStartDelay < pDrvCfgPara->mS_FBEmptyStall.nStallDelaytime ) //延时* 5ms，避开开环拖动的影响
	    {
	        pStallFaultTime->nStartDelay += FAULT_DETECT_CYCLE;
	    }
	    else
	    {
	    	// need to check. if necessary use?
	        if( t_nCurrent > pFaultValue->wStallCurMax )  			//电机电流大于堵转最大电流
	        {
	        	pFaultValue->nStallCurFlag = 1;	           
	        }
	        else
	        {
	        	if( t_nCurrent < pFaultValue->wStallCurMin )		//电机电流小于堵转消除电流
        		{
        			pFaultValue->nStallCurFlag = 0;        			
        		}	            
	        }

			if(pFaultValue->nStallCurFlag == 1)
	        {
	            if(pStallFaultTime->nCheckCnt1 < pDrvCfgPara->mS_FBEmptyStall.nStallDetectTime)      //滤波时间*5ms
	            {
	                pStallFaultTime->nCheckCnt1 += FAULT_DETECT_CYCLE;	//时间计时
	            }
	            else												//判定为电机堵转
	            {                                   
	                pStallFaultTime->nCheckCnt1 = 0;
	                pObj->m_pFaults->B.StallError		= 1;		//堵转错误标志位置1
	                pFaultValue->nStallFlag				= 1;		//堵转标志位为1，用于区分触发了哪种堵转
	            }
	        }
	        else
	        {
				pStallFaultTime->nCheckCnt1	-= FAULT_DETECT_CYCLE;	//时间减少
				if(pStallFaultTime->nCheckCnt1 < 0)
				{
	            pStallFaultTime->nCheckCnt1 = 0;
	        }
			}

			wSpeedfromVolt = (getVolt2FreqCalcPara(pObj->mg_nMACtrlProcID) * getMotorActVoltFromObjId1ms(pObj->mg_nMACtrlProcID)) >> 15;
			wSpeedfromVolt1 = (wSpeedfromVolt * pFaultValue->wStallSpeedfactor) >> 8;

	        if( wSpeedfbkABS > wSpeedfromVolt1 ) 					//电机电压和转速不匹配，电压小转速高，则判定为堵转。
	        {
	            if(pStallFaultTime->nCheckCnt2 < pDrvCfgPara->mS_FBEmptyStall.nStallDetectTime)      //滤波时间5ms 
	            {
	                pStallFaultTime->nCheckCnt2 += FAULT_DETECT_CYCLE;
	            }
	            else                                 //判定为电机堵转 
	            {
	                pStallFaultTime->nCheckCnt2			= 0;
	                pObj->m_pFaults->B.StallError		= 1;		//堵转错误标志位置1
	                pFaultValue->nStallFlag				= 2;		//堵转标志位为2，用于区分触发了哪种堵转
	            }
	        }
	        else
	        {
	            pStallFaultTime->nCheckCnt2 = 0;
	        }
			// need check end
	    }
	}
	else
	{		
		pObj->m_pFaults->B.StallError			= 0;		//堵转故障清零
		pFaultValue->nStallFlag					= 0;		//启动标志清零	
		pStallFaultTime->nCheckCnt1				= 0;
		pStallFaultTime->nCheckCnt2				= 0;
	}
}

/*****************************************************************************
 * 函数名   : FaultSencondStartCheck(STR_MACtrProc *pObj)
 * 说明     : 二次启动
 * 设计思路 ：二次启动，在进入启动5s内判断，时间根据实际修改
 *          ：1.进入open之后2.5s内还没进入闭环，时间要根据实际情况修改                 \
 *          ：2.转速过高或者过低，设定阈值和堵转检测相同                             \
 *          : 3.三相电流幅值大于电流设定值，设定值和堵转检测相同
 * 参数     ：s32 wSpeedFbk, s16 nIq, STR_CurrPhaseUVW *pstruIabcMax, STR_FaultTime *pstruFaultTime
 * 返回值   ：无
 * 修改时间 ：2022.11.23
 *****************************************************************************/
static void FaultStartCheck(STR_MACtrProc *pObj)
{
	//s32 wSpeedFbk								= pObj->m_pMotorSpeed->wSpeedfbk;
	//s16 nIq										= pObj->m_nQCur_Reference;
	STR_VectorUVW 		*pstruIabcMax			= pObj->m_pstruImaxCurrent;
	STR_FaultTime 		*pstruFaultTime			= pObj->m_pstruFaultStartTime;
	PSTR_DrvCfgPara		pDrvCfgPara 			= pObj->mg_pCtrlObj->m_pDrvCfgPara;
	
	if(pDrvCfgPara->mS_FBEmptyStall.bStartProtectEnable == 1)
	{
    	if(pstruFaultTime->nStartDelay < pDrvCfgPara->mS_FBEmptyStall.nStartFaultDetectTime)      //开环10s内检测，10s后不再检测  5ms*2000
	    {
	        pstruFaultTime->nStartDelay += FAULT_DETECT_CYCLE;

	        if((pstruIabcMax->nPhaseU > pObj->m_pFaultValue->nStallCurrent) 
				|| (pstruIabcMax->nPhaseV > pObj->m_pFaultValue->nStallCurrent) 
				|| (pstruIabcMax->nPhaseW > pObj->m_pFaultValue->nStallCurrent)
				)//三相电流幅值超过堵转电流设定值则判定为堵转
	        {
	            pObj->m_pFaults->B.StartError		= 1;				//启动错误标志位置1
	            pObj->m_pFaultValue->nStartFlag		= 3;             	//启动错误标志位为3
	        }
	        
	        if((pObj->m_pAppCommData->bOpenRunFlag == 0)
				&&(pstruFaultTime->nStartDelay > pDrvCfgPara->mS_FBEmptyStall.nStartClosedDetectTime)
				)     //开环600*5ms = 3s后还没切入闭环，则判断为启动失败，具体时间按照实际项目调整
	        {
	            pObj->m_pFaults->B.StartError		= 1;              //启动错误标志位置1
	            pObj->m_pFaultValue->nStartFlag		= 4;            //启动错误标志位为4
	        }
	    }
	}
	else
	{
		pstruFaultTime->nStartDelay					= 0;
		pObj->m_pFaults->B.StartError				= 0;				//启动错误标志位置0
		pObj->m_pFaultValue->nStartFlag				= 0;             	//启动错误标志位为0

	}
}

/***********************************************************************************
 * 函数名   : FaultPhaseCheck(STR_MACtrProc *pObj)
 * 说明     : 缺相检测 
 * 设计思路 ：1.三相电流幅值相差3倍，则判定为电机缺相，检测时间和检测倍数根据实际修改
 *            2.一定时间内电流幅值小于设定阈值，则判定为缺相， 检测时间和检测倍数根据实际修改
 * 参数     ：STR_MACtrProc *pObj
 * 返回值   ：无
 * 修改时间 ：2020.08.17

 * 修改时间 : 2023.09.04
 * 修改内容 ：调整函数传参
 ***********************************************************************************/
static void FaultPhaseCheck(STR_MACtrProc *pObj)
{
	STR_FaultTime 		*pstruFaultTime 		= pObj->m_pstruFaultPhaseTime;
	STR_VectorUVW	  	*pstruImaxCurrent		= pObj->m_pstruImaxCurrent;
	STR_CurrentAmplitude *pstruCurrentAmplitude	= pObj->m_pstruCurrentAmplitude;
	PSTR_DrvCfgPara		pDrvCfgPara 			= pObj->mg_pCtrlObj->m_pDrvCfgPara;

	if(pDrvCfgPara->mS_FBEmptyStall.bLossPHProtectEnable == 1)
	{
	    if(pstruFaultTime->nCheckCnt1 < pDrvCfgPara->mS_FBEmptyStall.nLossPHDetectTime)//*检测时间为 pDrvCfgPara->mS_FBEmptyStall.nLossPHDetectTime * 5ms */
	    {
	        pstruFaultTime->nCheckCnt1 += FAULT_DETECT_CYCLE;
	    }
	    else
	    {
	        pstruFaultTime->nCheckCnt1 = 0;
	        
	        if(((pstruImaxCurrent->nPhaseU >> 2) > pstruImaxCurrent->nPhaseV) || (((pstruImaxCurrent->nPhaseV >> 2) > pstruImaxCurrent->nPhaseW)) ||
	          (((pstruImaxCurrent->nPhaseW >> 2) > pstruImaxCurrent->nPhaseU)))				/*如果三相电流幅值相差3倍则判定为缺相，倍数需要根据实际负载调整*/
	        {
	            pObj->m_pFaults->B.PhaseLossError 		= 1;								/* 缺相错误标志位置1 */
	            pObj->m_pFaultValue->nPhaseLossFlag		= 1;								/* 第一种缺相保护 */
	        }
	        
	        pstruImaxCurrent->nPhaseU = 0;
	        pstruImaxCurrent->nPhaseV = 0;
	        pstruImaxCurrent->nPhaseW = 0;
	    }

	    if((pstruCurrentAmplitude->nPhA < pObj->m_pFaultValue->nPhaseLossCurrent)			/* 三相电流幅值小于设定阈值，累积时间小于设定阈值则判断为缺相*/
			||(pstruCurrentAmplitude->nPhB < pObj->m_pFaultValue->nPhaseLossCurrent)
			||(pstruCurrentAmplitude->nPhC < pObj->m_pFaultValue->nPhaseLossCurrent))
	    {
	        if(pstruFaultTime->nCheckCnt2 < pDrvCfgPara->mS_FBEmptyStall.nLossPHDetectTime)     /*检测时间为 pDrvCfgPara->mS_FBEmptyStall.nLossPHDetectTime * 5ms*/
	        {
	            pstruFaultTime->nCheckCnt2 += FAULT_DETECT_CYCLE;
	        }
	        else
	        {
	            pstruFaultTime->nCheckCnt2				= 0;
	            pObj->m_pFaults->B.PhaseLossError 		= 1;						/* 缺相错误标志位置1 */
	            pObj->m_pFaultValue->nPhaseLossFlag		= 2;						 /*第二种缺相保护   */
	        }
	    }
	    else
	    {
	        pstruFaultTime->nCheckCnt2					= 0;
	    }
	}
	else
    {                                                     /* 清零 */
		pstruFaultTime->nCheckCnt1				= 0;
		pstruFaultTime->nCheckCnt2				= 0;
		pObj->m_pFaults->B.PhaseLossError 		= 0;
		pObj->m_pFaultValue->nPhaseLossFlag		= 0;

	}
}

/***********************************************************************************
 * 函数名   : FaultTempCheck(STR_MACtrProc *pObj)
 * 说明     : 温度保护检测，针对NTC设计
 * 设计思路 ：1.根据NTC的阻值去判断是否发生过温故障,不做开路判断
 * 参数     ：pObj
 * 返回值   ：无
 * 修改时间 ：2022.11.22
 ***********************************************************************************/
static s16 getPowerUnitTemp (STR_MACtrProc *pObj)
{
	return 0;
}

static void FaultTempCheck(STR_MACtrProc *pObj)
{
	PSTR_DrvCfgPara	pDrvCfgPara = pObj->mg_pCtrlObj->m_pDrvCfgPara;

	pObj->m_nInvTemp = getPowerUnitTemp(pObj);

	if(pDrvCfgPara->mS_FBTempNTC.bOvTempProtectEnable == 1)
	{
		/* 温度大于设定值，则判定为过温故障; */
        /* 温度值小于一定值则判定为NTC开路   */
	    if( (pObj->m_nInvTemp  > (s16)pDrvCfgPara->mS_FBTempNTC.m_wMaxAllowedWorkTemp)
			|| (pObj->m_nInvTemp  < (s16)pDrvCfgPara->mS_FBTempNTC.m_wMinAllowedWorkTemp)
		  )
	    {
	        pObj->m_pstruFaultTempTime->nCheckCnt1 += FAULT_DETECT_CYCLE;
	    }
	    else
	    {
	        pObj->m_pstruFaultTempTime->nCheckCnt1 = 0;
	    }

	    if(pObj->m_pstruFaultTempTime->nCheckCnt1 > pDrvCfgPara->mS_FBTempNTC.nDetectionTime) /*滤波时间 pDrvCfgPara->mS_FBTempNTC.nDetectionTime * 5ms */
	    {
	        pObj->m_pFaults->B.TempOverError		= 1;				/*温度故障标志位置1*/
	        pObj->m_pstruFaultTempTime->nCheckCnt1	= 0;
	    }
	}
    else                                                                /* 清零 */
	{
		pObj->m_pFaults->B.TempOverError 			= 0;
		pObj->m_pstruFaultTempTime->nCheckCnt1 		= 0;
	}
}

/***********************************************************************************
 * 函数名   : VoltFaultInit(void)
 * 说明     : 电压检测错误检测变量初始化
 * 设计思路 ：检测时间变量不能清0
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 ***********************************************************************************/
void VoltFaultInit(STR_MACtrProc *pObj)
{
	PSTR_DrvCfgPara	pDrvCfgPara = pObj->mg_pCtrlObj->m_pDrvCfgPara;
	STR_TransCoefElement *pAppToCore	= &(pObj->mg_pCtrlObj->mTransCoef.mAppToCore);

    /******过欠压故障检测变量初始化*********/
    pObj->m_pstruFaultVoltTime->nCheckCnt1 = 0;
    pObj->m_pstruFaultVoltTime->nCheckCnt2 = 0;
    pObj->m_pFaultValue->nOverVoltage	= App2CoreVoltTrans(pAppToCore,pDrvCfgPara->mS_FBDcUnit0.m_wDCOverVoltage);
    pObj->m_pFaultValue->nUnderVoltage	= App2CoreVoltTrans(pAppToCore,pDrvCfgPara->mS_FBDcUnit0.m_wDCUnderVoltage);
}

/***********************************************************************************
 * 函数名   : FaultInitTask(void)
 * 说明     : 错误检测变量初始化任务
 * 设计思路 ：1.变量初始化
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 ***********************************************************************************/
void FaultInitTask(STR_MACtrProc *pObj)
{
	STR_TransCoefElement *pAppToCore = &(pObj->mg_pCtrlObj->mTransCoef.mAppToCore);

	PSTR_DrvCfgPara	pDrvCfgPara = pObj->mg_pCtrlObj->m_pDrvCfgPara;
	
    /********过流故障检测变量初始化*****/
	pObj->m_pFaultValue->nOverCurrent = App2CoreCurTrans(pAppToCore,pDrvCfgPara->mS_FBCurSense.m_wSoftOvCur);
    
    /******离水空转故障检测变量初始化********/
    pObj->m_pstruFaultEmptyTime->nCheckCnt1 = 0;
    pObj->m_pFaultValue->nEmptyCurrent = App2CoreCurTrans(pAppToCore,pDrvCfgPara->mS_FBEmptyStall.m_wEmptyCurrent);
    pObj->m_pFaultValue->wEmptySpeed = App2CoreFreqTrans(pAppToCore,pDrvCfgPara->mS_FBEmptyStall.m_wEmptySpeed);

    /******堵转故障检测变量初始化*********/
    pObj->m_pstruFaultStallTime->nCheckCnt1 = 0;
    pObj->m_pstruFaultStallTime->nCheckCnt2 = 0;
    pObj->m_pstruFaultStallTime->nStartDelay = 0;
    pObj->m_pFaultValue->nStallCurrent		= App2CoreCurTrans(pAppToCore,pDrvCfgPara->mS_FBEmptyStall.m_wStallPHCurrent);
    pObj->m_pFaultValue->wStallCurMax		= App2CoreCurTrans(pAppToCore,pDrvCfgPara->mS_FBEmptyStall.m_wStallCurMax);
    pObj->m_pFaultValue->wStallCurMin		= App2CoreCurTrans(pAppToCore,pDrvCfgPara->mS_FBEmptyStall.m_wStallCurMin);
    pObj->m_pFaultValue->wStallSpeedfactor	= pDrvCfgPara->mS_FBEmptyStall.m_wStallSpeedFactor;
    pObj->m_pFaultValue->nStallFlag = 0;
	pObj->m_pFaultValue->nStallCurFlag = 0;

    /******缺相故障检测变量初始化*********/
    pObj->m_pstruFaultPhaseTime->nCheckCnt1 = 0;
	pObj->m_pFaultValue->nPhaseLossCurrent	= App2CoreCurTrans(pAppToCore,pDrvCfgPara->mS_FBEmptyStall.m_wLosePhaseCurrent);
    
	memset(pObj->m_pstruCurrentAmplitude, 0, sizeof(STR_CurrentAmplitude));
	memset(pObj->m_pstruImaxCurrent, 0, sizeof(STR_VectorUVW));
    
    /*****温度故障检测变量初始化****/
    pObj->m_pstruFaultTempTime->nCheckCnt1 = 0;

    /*启动故障检测变量初始化*/ 
    //pObj->m_pstruFaultStartTime->nCheckCnt1 = 0;
    //pObj->m_pstruFaultStartTime->nCheckCnt2 = 0;
    //pObj->m_pstruFaultStartTime->nStartDelay = 0;
	memset(pObj->m_pstruFaultStartTime,0,sizeof(STR_FaultTime));
}


/***********************************************************************************
 * 函数名   : FaultInit(void)
 * 说明     : 错误检测变量初始化
 * 设计思路 ：1.变量初始化
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 ***********************************************************************************/
void FaultInit(STR_MACtrProc *pObj)
{
	VoltFaultInit(pObj);
	FaultInitTask(pObj);	
}


/***********************************************************************************
 * 函数名   : FaultCheck(void)
 * 说明     : 故障检测处理
 * 设计思路 ：1.每个故障检测的处理周期为5ms
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 ***********************************************************************************/
void FaultCheck(STR_MACtrProc *pObj)
{
	if(pObj->m_SMACtrlBit.m_bFaultInitDone == 0)	//	报警初始化才进行报警检测
	{
		return;
	}
    if(pObj->t_nFlagCheck < FAULT_DETECT_CYCLE)		//	报警轮询
    {
        pObj->t_nFlagCheck ++;
    }
    else
    {
        pObj->t_nFlagCheck = 1;
    }

	if(pObj->mMdToMa.bBreakInFault)					// 硬件过流报警
	{
		pObj->m_pFaults->B.HardCurretError		= 1;		//	报警标志置1
	}

	FaultCurrentCheckMA(&pObj->mMdToMa.mStatCurrUVW, pObj);		//	软件过流检测
	CurrentAmplitudeCalc(&pObj->mMdToMa.mStatCurrUVW, pObj);	//	电流幅值检测
	
    switch(pObj->t_nFlagCheck)
    {
        case 1:
        { 
            FaultVoltageCheck(pObj);  					//过欠压检测
            break;
        }
        case 2:
        {
            if(pObj->m_eSysState == E_DRIVER_RUN)          
            {
				FaultStallCheck(pObj);					//堵转检测  部分已测2022-1124
            }
            break;
        }
        case 3:
        {
            if(pObj->m_eSysState == E_DRIVER_RUN)
            {
                FaultEmptyCheck(pObj);  				//离水空转检测   已测2022-1124
            }
            
            //FaultTempCheck(pObj);						//过温检测
            break;
        }
        case 4:
        {
            if(pObj->m_eSysState == E_DRIVER_RUN)
            {
				FaultPhaseCheck(pObj);					//缺相检测		已测2022-1124
            }
            break;
        }
        case 5:
        {
 
            if((pObj->m_eSysState == E_DRIVER_RUN))
            {
			FaultStartCheck(pObj);						//二次启动检测	已测2022-1123
            }
            break;
        }
        default:
            break;
    }

	updateFaultInfo2MACtrl(pObj);
}

/***********************************************************************************
 * 函数名   : FaultRecoverInit(void)
 * 说明     : 故障恢复变量初始化
 * 设计思路 ：变量初始化
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 ***********************************************************************************/
void FaultRecoverInit(STR_MACtrProc *pObj)
{
	PSTR_DrvCfgPara	pDrvCfgPara = pObj->mg_pCtrlObj->m_pDrvCfgPara;
	STR_TransCoefElement 	*pAppToCore	= &(pObj->mg_pCtrlObj->mTransCoef.mAppToCore);
    pObj->m_pFaults->R = 0;
    pObj->m_pstruFaultEmptyTime->nRecoverCntr   = 0;
    pObj->m_pstruFaultStallTime->nRecoverCntr   = 0;
    pObj->m_pstruFaultCurrentTime->nRecoverCntr = 0;
    pObj->m_pstruFaultCurrentTime->nRecoverTime = 0;
    pObj->m_pstruFaultVoltTime->nRecoverCntr    = 0;
    pObj->m_pstruFaultTempTime->nRecoverCntr    = 0;
    pObj->m_pFaultValue->nOverVoltageRecover	= App2CoreVoltTrans(pAppToCore,pDrvCfgPara->mS_FBDcUnit0.m_wDCOverVoltageRecover);
    pObj->m_pFaultValue->nUnderVoltageRecover	= App2CoreVoltTrans(pAppToCore,pDrvCfgPara->mS_FBDcUnit0.m_wDCUnderVoltageRecover);
}

/***********************************************************************************
 * 函数名   : FaultRecover(void)
 * 说明     : 故障恢复程序处理
 * 设计思路 ：1.过欠压恢复：       母线电压在正常工作范围内，持续2s则清除过欠压故障标志位; \
 *            2.软件&硬件过流恢复：2s后清除过流故障标志位;                                 \
 *            3.堵转恢复：         2s后清除堵转故障标志位;                                 \
 *            4.缺相恢复：         2s后清除过流故障标志位;                                 \
 *            5.过温恢复：         NTC在正常工作范围内，持续2s则清除过温故障标志位; \
 *            6.启动恢复：         1s后重启
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2020.08.17
 ***********************************************************************************/
void FaultRecover(STR_MACtrProc *pObj)
{
	PSTR_DrvCfgPara	pDrvCfgPara = pObj->mg_pCtrlObj->m_pDrvCfgPara;
	STR_FaultStatus			*t_pFaults			= pObj->m_pFaults;
	STR_FaultVariable		*t_pFaultValue		= pObj->m_pFaultValue;
	s16 t_nTmp;
    /****************过欠压恢复****************/
    if((t_pFaults->B.VoltOverError == 1) || (t_pFaults->B.VoltUnderError == 1))
    {   //母线电压在欠压恢复值和过压恢复值之间则判定为正常状态
        if((pObj->mMdToMa.nVdc	>= t_pFaultValue->nUnderVoltageRecover) 
          && (pObj->mMdToMa.nVdc <= t_pFaultValue->nOverVoltageRecover))
        {
            if(pObj->m_pstruFaultVoltTime->nRecoverCntr < pDrvCfgPara->mS_FBDcUnit0.nVoltageRecoverTime)     /*电压恢复正常，超过设定时间清零过欠压故障标志位*/
            {
                pObj->m_pstruFaultVoltTime->nRecoverCntr ++;
            }
            else
            {
                t_pFaults->B.VoltOverError = 0;
                t_pFaults->B.VoltUnderError = 0;
                pObj->m_pstruFaultVoltTime->nRecoverCntr = 0;
            }
        }
        else
        {
            pObj->m_pstruFaultVoltTime->nRecoverCntr = 0;
        }
    }

    /****************过流恢复****************/
    if((t_pFaults->B.HardCurretError == 1) || (t_pFaults->B.SoftCurretError == 1))
    {
    	if(pDrvCfgPara->mS_FBCurSense.nOvCurRecoverTime != 0xFFFF)
    	{
	        if(pObj->m_pstruFaultCurrentTime->nRecoverCntr < pDrvCfgPara->mS_FBCurSense.nOvCurRecoverTime)	/*超过设定时间清零过流故障标志位*/
	        {
	            pObj->m_pstruFaultCurrentTime->nRecoverCntr ++;
	        }
	        else
	        {
	            if(t_pFaults->B.HardCurretError == 1)
	            {	            	
	                t_pFaults->B.HardCurretError = 0;
					pObj->m_SMACtrlBit.m_bBreakInClrReq = 1;		// 硬件过流报警清除，设置BreakIn清除请求
	            }

	            if(t_pFaults->B.SoftCurretError == 1)
	            {
	                t_pFaults->B.SoftCurretError = 0;
					pObj->m_pstruFaultCurrentTime->nCheckCnt1 = 0;
	            }

	            pObj->m_pstruFaultCurrentTime->nRecoverTime ++;
	            pObj->m_pstruFaultCurrentTime->nRecoverCntr = 0;
	        }
    	}
    }

    /****************堵转恢复****************/
    if(t_pFaults->B.StallError == 1)
    {
    	if(pDrvCfgPara->mS_FBEmptyStall.nStallRecoverTime != 0xFFFF)
    	{
	        if(pObj->m_pstruFaultStallTime->nRecoverCntr < pDrvCfgPara->mS_FBEmptyStall.nStallRecoverTime)		/*超过设定时间清零堵转故障标志位*/
	        {
	            pObj->m_pstruFaultStallTime->nRecoverCntr ++;
	        }
	        else
	        {
	            t_pFaults->B.StallError = 0;	            
	            t_pFaultValue->nStallFlag = 0;
				t_pFaultValue->nStallCurFlag = 0;
				memset(pObj->m_pstruFaultStallTime,0,sizeof(STR_FaultTime));
	        }
    	}
    }

    /****************离水空转恢复****************/
    if(t_pFaults->B.EmptyError == 1)
    {
    	if(pDrvCfgPara->mS_FBEmptyStall.nEmptyRecoverTime != 0xFFFF)
    	{
	        if(pObj->m_pstruFaultEmptyTime->nRecoverCntr < pDrvCfgPara->mS_FBEmptyStall.nEmptyRecoverTime)/*超过设定时间清零离水故障标志位*/
	        {
	            pObj->m_pstruFaultEmptyTime->nRecoverCntr ++;
	        }
	        else
	        {
	            pObj->m_pFaults->B.EmptyError				= 0;
	            pObj->m_pstruFaultEmptyTime->nRecoverCntr	= 0;
				pObj->m_pstruFaultEmptyTime->nCheckCnt1		= 0;
	        }
    	}
    }

    /****************缺相恢复****************/
    if(t_pFaults->B.PhaseLossError == 1)
    {
    	if(pDrvCfgPara->mS_FBEmptyStall.nLossPHRecoverTime != 0xFFFF)
    	{
	        if(pObj->m_pstruFaultPhaseTime->nRecoverCntr < pDrvCfgPara->mS_FBEmptyStall.nLossPHRecoverTime)/*超过设定时间清零缺相故障标志位*/
	        {
	            pObj->m_pstruFaultPhaseTime->nRecoverCntr ++;
	        }
	        else
	        {
	            t_pFaults->B.PhaseLossError = 0;
	            pObj->m_pstruFaultPhaseTime->nRecoverCntr = 0;
				pObj->m_pstruFaultPhaseTime->nCheckCnt1 = 0;
	        }
    	}
    }

    /****************过温恢复****************/
    if(t_pFaults->B.TempOverError == 1)
    {
    	t_nTmp	= (s16)(pDrvCfgPara->mS_FBTempNTC.m_wMaxAllowedWorkTemp) - pDrvCfgPara->mS_FBTempNTC.HysterTemp;
        if( pObj->m_nInvTemp <= t_nTmp )				// 温度小于max - hy 
        {
            if(pObj->m_pstruFaultTempTime->nRecoverCntr < pDrvCfgPara->mS_FBTempNTC.nFaultRecoverTime)/*超过设定时间清零温度故障标志位*/
            {
                pObj->m_pstruFaultTempTime->nRecoverCntr ++;
            }
            else
            {
                t_pFaults->B.TempOverError = 0;
                pObj->m_pstruFaultTempTime->nRecoverCntr = 0;
            }
        }
        else
        {
            pObj->m_pstruFaultTempTime->nRecoverCntr = 0;
        }
    }

    /****************启动失败恢复****************/
    if(t_pFaults->B.StartError == 1)
    {
    	if(pDrvCfgPara->mS_FBEmptyStall.nStartFaultRecoverTime != 0xFFFF)
    	{
	        if(pObj->m_pstruFaultStartTime->nRecoverCntr < pDrvCfgPara->mS_FBEmptyStall.nStartFaultRecoverTime)//START_FAULT_RECOVER_TIME) //1s后清零缺相故障标志位
	        {
	            pObj->m_pstruFaultStartTime->nRecoverCntr ++;
	        }
	        else
	        {
	            t_pFaults->B.StartError = 0;	            
	            t_pFaultValue->nStartFlag = 0;
				memset(pObj->m_pstruFaultStartTime,0,sizeof(STR_FaultTime));
	        }
		}
    }

}

/***********************************************************************************
 * 函数名   : static CurrentAmplitudeCalc(STR_CurrPhaseUVW *pstruCurrPhaseUVW,stru_SWLIBS_3wSyst *pCurrentAmplitude )
 * 说明     : 电流有效值计算， 
 * 设计思路 ：半个电流周期内对电流积分
 * 参数     ：STR_CurrPhaseUVW *pstruCurrPhaseUVW, stru_SWLIBS_3wSyst *pCurrentAmplitude
 * 返回值   ：无
 * 修改时间 ：2020.10.9
 ***********************************************************************************/
static void CurrentAmplitudeCalc(STR_VectorUVW *pstruCurrPhaseUVW, STR_MACtrProc *pObj)
{
	STR_VectorUVW	 		*pstruCurrentMAX 		= pObj->m_pstruImaxCurrent;
	STR_CurrentAmplitude 	*pstruCurrentAmplitude	= pObj->m_pstruCurrentAmplitude;

	s16 t_nPhaseU_ABS		= ABS(pstruCurrPhaseUVW->nPhaseU);
	s16 t_nPhaseV_ABS		= ABS(pstruCurrPhaseUVW->nPhaseV);
	s16 t_nPhaseW_ABS		= ABS(pstruCurrPhaseUVW->nPhaseW);
	
	/***********取三相电流最大值，缺相检测里面会用到************/
	
    if(t_nPhaseU_ABS > pstruCurrentMAX->nPhaseU)
    {
        pstruCurrentMAX->nPhaseU = t_nPhaseU_ABS;
    }

    if(t_nPhaseV_ABS > pstruCurrentMAX->nPhaseV)
    {
        pstruCurrentMAX->nPhaseV = t_nPhaseV_ABS;
    }

    if(t_nPhaseW_ABS > pstruCurrentMAX->nPhaseW)
    {
        pstruCurrentMAX->nPhaseW = t_nPhaseW_ABS;
    }

	// 检测周期1600个速度环周期，时间不合适时调整检测时间
	if(pstruCurrentAmplitude->nTheta <= 100 * 16)
	{
		pstruCurrentAmplitude->nTheta++;
		if(t_nPhaseU_ABS > pstruCurrentAmplitude->wPhATemp)
		{
			pstruCurrentAmplitude->wPhATemp = t_nPhaseU_ABS;
		}
		
		if(t_nPhaseV_ABS > pstruCurrentAmplitude->wPhBTemp)
		{
			pstruCurrentAmplitude->wPhBTemp = t_nPhaseV_ABS;
		}

		if(t_nPhaseW_ABS > pstruCurrentAmplitude->wPhCTemp)
		{
			pstruCurrentAmplitude->wPhCTemp = t_nPhaseW_ABS;
		}
	}
	else
	{
	pstruCurrentAmplitude->nPhA			= pstruCurrentAmplitude->wPhATemp;
	pstruCurrentAmplitude->nPhB			= pstruCurrentAmplitude->wPhBTemp;
	pstruCurrentAmplitude->nPhC			= pstruCurrentAmplitude->wPhCTemp;

	pstruCurrentAmplitude->wPhATemp		= 0;
	pstruCurrentAmplitude->wPhBTemp		= 0;
	pstruCurrentAmplitude->wPhCTemp		= 0;
	pstruCurrentAmplitude->nTheta		= 0;
	}
}
 

