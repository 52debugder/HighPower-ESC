/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： PowerCalculation.c
 * 文件标识：
 * 内容摘要： 功率环处理
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： andrew kong
 * 完成日期： 2020年10月9日
 *
 *******************************************************************************/

#include "PowerCalculation.h"
#include "MA_Static_Variable.h"
#include "MC_math.h"


stru_Ramp_t PowerRamp;

/*******************************************************************************
 函数名称：    void PowerLimitCalc(STR_MechQuantity *pstruMotorSpeed, s32 PowerValue)
 功能描述：    限功率计算
 设计思路：    1.如果实际功率超过限制值，则减低速度环的速度参考值，一般是在速度环的时候限功率处理
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.08.17      V1.0           Tonghua Li           创建
 2020.10.09      V2.0           Tonghua Li         调整变量结构
 ********************************************************************/
#if (DRV0_POWER_LIMIT_STATUS==TRUE) 
void PowerLimitCalc(STR_MechQuantity *pstruMotorSpeed, s32 PowerValue)
{
	if(++pstruMotorSpeed->nPowerLimitCntr >= pstruMotorSpeed->nPowerLimitPeriod)			//限功率计算周期
	{
        pstruMotorSpeed->nPowerLimitCntr  = 0;
        if(PowerValue > pstruMotorSpeed->wPowerLimitValue)                           //实际功率大于限制功率则减小速度给定值
        {
        	//	ATTENTION:
        	//	
        	//	wSpeedRampACCStep取自闭环后的速度环加减速设定值
        	//	速度环加减速设定值设置过大时(速度环快速加减速的需要)，需要修改代码减少速度的增量
        	//		防止引起速度设定值的过大波动或震荡
        	
            if(pstruMotorSpeed->wPowerLimitSpeedChangeSet < pstruMotorSpeed->wSpeedSet)    //功率超出限制后，增加限功率输出
            {
            	pstruMotorSpeed->wPowerLimitSpeedChangeSetInc += pstruMotorSpeed->wSpeedRampACCStep;
                pstruMotorSpeed->wPowerLimitSpeedChangeSet	+= pstruMotorSpeed->wPowerLimitSpeedChangeSetInc >> 16;
				pstruMotorSpeed->wPowerLimitSpeedChangeSetInc &= 0xFFFF0000;
            }
            else
            {
            	pstruMotorSpeed->wPowerLimitSpeedChangeSetInc	= 0;
                pstruMotorSpeed->wPowerLimitSpeedChangeSet = pstruMotorSpeed->wSpeedSet;
            }
        }
        else                                                                  //功率恢复正常后，减小限功率输出
        {
            if(pstruMotorSpeed->wPowerLimitSpeedChangeSet > 0)
            {
            	pstruMotorSpeed->wPowerLimitSpeedChangeSetInc += pstruMotorSpeed->wSpeedRampDECStep;
                pstruMotorSpeed->wPowerLimitSpeedChangeSet -= pstruMotorSpeed->wPowerLimitSpeedChangeSetInc >> 16;
				pstruMotorSpeed->wPowerLimitSpeedChangeSetInc &= 0xFFFF0000;
            }
            else
            {
            	pstruMotorSpeed->wPowerLimitSpeedChangeSetInc	= 0;
                pstruMotorSpeed->wPowerLimitSpeedChangeSet = 0;
            }
        }
    }
}
#endif
/*******************************************************************************
 函数名称：   void SpeedLimitCalc(s32 wSpeedFbk, stru_PowerBasic_t *pstruPower)
 功能描述：    限转速计算
 设计思路：    1.如果实际转速超过限制值，则减低功率环的功率参考值 
 操作的表：    无
 输入参数：    s32 wSpeedFbk, stru_PowerBasic_t *pstruPower
 输出参数：    无
 返 回 值：    wSpeedLimitPowerChangeSet    ------减小的功率设定值
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.08.17      V1.0           Tonghua Li           创建
 2020.10.09      V2.0           Tonghua Li         调整变量结构
 2023.03.28      V3.0           Tonghua Li         修改
 ********************************************************************/
#if (DRV0_SPPED_LIMIT_STATUS==TRUE)
void SpeedLimitCalc(s32 wSpeedFbk, pSTR_PowerDef pstruPower)
{
	if(++pstruPower->nSpeedLimitCntr >= pstruPower->nSpeedLimitPeriod)		//限转速计算周期
	{
		pstruPower->nSpeedLimitCntr  = 0;
		if(wSpeedFbk >= pstruPower->wSpeedLimitValue)						 //实际转速大于限制转速则减小功率给定值
		{
			if(pstruPower->wSpeedLimitPowerChangeSet < pstruPower->wPowerSet) 	 //转速超出限制后，增加限速输出
			{
				pstruPower->wSpeedLimitPowerChangeSet += pstruPower->struPowerRamp.nACCStep;
			}
			else
			{
				pstruPower->wSpeedLimitPowerChangeSet = pstruPower->wPowerSet;
			}
		}
		else																  //转速恢复正常后，减小限转速输出
		{
			if(pstruPower->wSpeedLimitPowerChangeSet > 0)
			{
				pstruPower->wSpeedLimitPowerChangeSet -= pstruPower->struPowerRamp.nDECStep;
			}
			else
			{
				pstruPower->wSpeedLimitPowerChangeSet = 0;
			}
		}
	}
}
#endif

/*******************************************************************************
 函数名称：   void SpeedLimitCalc(s32 wSpeedFbk, stru_PowerBasic_t *pstruPower)
 功能描述：    限转速计算
 设计思路：    1.爬坡计算
 操作的表：    无
 输入参数：    stru_Ramp_t *pstruRamp ------爬坡结构体成员
 输出参数：    无
 返 回 值：    pstruRamp->wRef -------爬坡输出值
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.08.17      V1.0           Tonghua Li           创建
 ********************************************************************/
s32 RampControl(stru_Ramp_t *pstruRamp)
{
    if(pstruRamp->wRef < pstruRamp->wSet)
    {
        if((pstruRamp->wRef + pstruRamp->nACCStep) <= pstruRamp->wSet)  //给定值小于设定值则增加
        {
            pstruRamp->wRef += pstruRamp->nACCStep;
        }
        else
        {
            pstruRamp->wRef = pstruRamp->wSet;
        }
    }
    else if(pstruRamp->wRef > pstruRamp->wSet)                         //给定值大于设定值则减小
    {
        if((pstruRamp->wRef - pstruRamp->nDECStep) >= pstruRamp->wSet)
        {
            pstruRamp->wRef -= pstruRamp->nDECStep;
        }
        else
        {
            pstruRamp->wRef = pstruRamp->wSet;
        }
    }

    return(pstruRamp->wRef);
}

/*******************************************************************************
函数名称：    s16 PowerPIRegulator(stru_PIRegulator *Regulator)
功能描述：    功率环PI  增量式PI
 设计思路：    增量式PI设计
 操作的表：    无
输入参数：    stru_PIRegulator *Regulator 结构体指针
输出参数：    PI调节结果
 返 回 值：    PI调节结果
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：    无
修改日期      版本号          修改人            修改内容
-----------------------------------------------------------------------------
2020/8/5      V1.0           WenCai Zhao          创建
 ********************************************************************/
s16 PowerPIRegulator(stru_PIRegulator *Reg)
{
    long    ACC;
    int AX;

    ACC = (long)(Reg->wInError - Reg->wLastError) * Reg->KP;   /* 比例项计算 */
    ACC = (ACC << 0) + (long)(Reg->wInError) * Reg->KI;        /* 积分项计算 */
    Reg->wIntegral = ACC + Reg->wIntegral;

    if(Reg->wIntegral > Reg->wUpperLimitOutput)                /* 输出最大值限幅 */
    {
        Reg->wIntegral = Reg->wUpperLimitOutput;
    }
    else if(Reg->wIntegral < Reg->wLowerLimitOutput)         /* 输出最小值限幅 */
    {
        Reg->wIntegral = Reg->wLowerLimitOutput;
    }

    AX = Reg->wIntegral >> 16;

    Reg->wLastError = Reg->wInError;                           /* 记录上次误差值 */

    return(AX);
}

/*******************************************************************************
 函数名称：  void PowerLoopReg(pSTR_PowerDef pstru_Power)
功能描述：    功率环计算
 设计思路：    功率环计算
 操作的表：    无
输入参数：    stru_PowerBasic_t *this  结构体指针
输出参数：    无
返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：    无
修改日期      版本号          修改人            修改内容
-----------------------------------------------------------------------------
 2020.08.17      V1.0           Tonghua Li           创建
 ********************************************************************/
void PowerLoopReg(pSTR_PowerDef pstru_Power)
{
    pstru_Power->struPowerPI.wInError = pstru_Power->wPowerRef - pstru_Power->wPowerValue;
	
	// 0.1W
	//pstru_Power->struPowerPI.wInError = (s32)(pstru_Power->struPowerPI.wInError/10);

    /* 误差限幅，可根据实际负载调整，影响PI响应的快慢 */
    //pstru_Power->struPowerPI.wInError = sat(pstru_Power->struPowerPI.wInError, -1000, 1000);
		//功率环输出Iq
    pstru_Power->nQCurrentSet = PowerPIRegulator(&pstru_Power->struPowerPI);
}

/*******************************************************************************
 函数名称：  void PowerLoopInit(void)
 功能描述：    功率计算变量初始化
 设计思路：    1.变量初始化
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 多任务访问:   该函数涉及全局表项操作，不可重入
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020.10.09     V1.0           Tonghua Li           修改
 ********************************************************************/
#if (DRV0_CLOSE_LOOP==POWER_LOOP)
void PowerLoopInit(STR_MACtrProc *pObj)
{
	
    //局部指针
    pSTR_PowerDef			pstru_Power ;
    PSTR_TransCoefElement	pApp2Core;
	PSTR_DrvCfgPara	pDrvCfgPara = pObj->mg_pCtrlObj->m_pDrvCfgPara;

    //赋值
    pstru_Power = pObj->m_pPower;
    pApp2Core = &pObj->mg_pCtrlObj->mTransCoef.mAppToCore;


    /*功率环PI参数初始化*/
    pstru_Power->struPowerPI.KP = pDrvCfgPara->mS_FBPwrLoop.nPowerKp;       //功率环 Kp POWER_KP_M0
    pstru_Power->struPowerPI.KI = pDrvCfgPara->mS_FBPwrLoop.nPowerKi;		//功率环 Ki POWER_KI_M0
    pstru_Power->struPowerPI.wInError = 0;
    pstru_Power->struPowerPI.wIntegral = 0;
    pstru_Power->struPowerPI.wLastError = 0;
    pstru_Power->struPowerPI.wUpperLimitOutput = (App2CoreCurTrans(pApp2Core, pDrvCfgPara->mS_FBPwrLoop.m_wPLoopIqMax) << 16); //功率环输出最大值 POWER_IQMAX_M0
    pstru_Power->struPowerPI.wLowerLimitOutput = (App2CoreCurTrans(pApp2Core, pDrvCfgPara->mS_FBPwrLoop.m_wPLoopIqMin) << 16); //功率环输出最小值 POWER_IQMIN_M0

    /*功率环计算参数初始化*/

    pstru_Power->nSpeedLimitCntr = 0;
	pstru_Power->nSpeedLimitPeriod = pDrvCfgPara->mS_FBPwrLoop.nPLoopSpdLmtCalcCycle;
    pstru_Power->wPowerRef = 0;
    pstru_Power->wPowerSet 			 = pDrvCfgPara->mS_FBPwrLoop.m_wPowerSetting;
    pstru_Power->wSpeedLimitPowerRef = pDrvCfgPara->mS_FBPwrLoop.m_wLmdSpdPowerSetting;	//SPEED_LIMIT_POWER_VALUE_M0
    pstru_Power->wSpeedLimitPowerChangeSet = 0;
    pstru_Power->wSpeedLimitValue	= App2CoreFreqTrans(pApp2Core, pDrvCfgPara->mS_FBPwrLoop.m_wSpdLmtValue);//SPEED_LIMIT_VALUE_M0
    pstru_Power->nQCurrentSet=0;   //功率环输出

    pObj->m_pAppCommData->nPowerFistFlag=0;
    /*功率计算参数初始化*/
    pstru_Power->wPowerValue = 0;   

    /*功率爬坡参数初始化*/
    pstru_Power->struPowerRamp.nACCStep = (s16)(pDrvCfgPara->mS_FBPwrLoop.m_wPowerRunAcc);	//POWER_RUN_ACC_M0
    pstru_Power->struPowerRamp.nDECStep = (s16)(pDrvCfgPara->mS_FBPwrLoop.m_wPowerRunDec);	//POWER_RUN_DEC_M0
    pstru_Power->struPowerRamp.wRef = 0;
    pstru_Power->struPowerRamp.wSet = 0;
}
#endif

