
#include "PubData_DriverInstance.h" 
#include "PubData_MD_MA.h"
#include "MC_Math.h"


//STR_PubDatMAMD gS_PubDatMaToMd;
//STR_PubDatMDMA gS_PubDatMdToMa;

extern PSTR_ControlObject getCtrlObjectPtr(u8 objID);
///////////////////////
void Calc(void)
{
	//gPubDatMA2MD.MotorSts = E_MOTOR
}


/*****************************************************************************
 * 函数名   : void updateObParaMALayer(PSTR_ControlObject *pCtrlObj)
 * 说明     : 观测器控制对象初始化处理函数
 *          : 具体实现，变量初始化
 * 设计思路 ：
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2022.10.24
 *****************************************************************************/
void updateObParaMALayer(PSTR_ControlObject pCtrlObj)
{
	PSTR_FocObjPar	pFocObjPar;
	pFocObjPar = &(pCtrlObj->m_pMotorFocPar->mObjPar);

	pFocObjPar->bMotorType	= pCtrlObj->m_pDrvCfgPara->mS_Motorpara.m_bMotorType;
	pFocObjPar->bPolePairs	= pCtrlObj->m_pDrvCfgPara->mS_Motorpara.m_bPolePairs;
	//pFocObjPar->nRatedCur	= pCtrlObj->m_pDrvCfgPara->mS_Motorpara.m_nRatedCur;
	pFocObjPar->wRatedFreq	= pCtrlObj->m_pDrvCfgPara->mS_Motorpara.m_wRatedFreq;

	pFocObjPar->wMotorRs	= pCtrlObj->m_pDrvCfgPara->mS_Motorpara.m_wMotorRs;
	pFocObjPar->wMotorLd	= (s32)(pCtrlObj->m_pDrvCfgPara->mS_Motorpara.m_wMotorLd);
	pFocObjPar->wMotorLq	= (s32)(pCtrlObj->m_pDrvCfgPara->mS_Motorpara.m_wMotorLq);
	pFocObjPar->wFluxConst	= (s32)(pCtrlObj->m_pDrvCfgPara->mS_Motorpara.m_wFluxConst);

	//pFocObjPar->nRatedUdc	= (s16)(pCtrlObj->m_pDrvCfgPara->mS_Boardpara.m_nRatedUdc);
	pFocObjPar->nPWMFreq	= (u16)(pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_nuPWMFreq);

	pFocObjPar->wAdcSupplyVol		= pCtrlObj->m_pDrvCfgPara->mS_Boardpara.m_wAdcSupplyVol;
	pFocObjPar->wRShunt				= pCtrlObj->m_pDrvCfgPara->mS_Boardpara.m_wRShunt;
	pFocObjPar->wAmpGain			= pCtrlObj->m_pDrvCfgPara->mS_Boardpara.m_wAmpGain;
	pFocObjPar->wVolShuntRatio		= pCtrlObj->m_pDrvCfgPara->mS_Boardpara.m_wVolShuntRatio;
	pFocObjPar->wBemfShuntRatio		= pCtrlObj->m_pDrvCfgPara->mS_Boardpara.m_wBemfShuntRatio;

}

/*****************************************************************************
 * 函数名   : void updateAcrParaMALayer(PSTR_ControlObject *pCtrlObj)
 * 说明     : 电流环控制对象初始化处理函数
 *          : 具体实现，变量初始化
 * 设计思路 ：
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2022.10.24
 *****************************************************************************/
void updateAcrParaMALayer(PSTR_ControlObject pCtrlObj)
{
	PSTR_FocObsPar	pAcrObjPar;
	s16 t_nTmp;
	
	STR_TransCoefElement *pAppToCore = &(pCtrlObj->mTransCoef.mAppToCore);
	
	pAcrObjPar = &(pCtrlObj->m_pMotorFocPar->mObsPar);

	pAcrObjPar->nCurrLoopIniKP	= pCtrlObj->m_pDrvCfgPara->mS_FBCurLoop.Kp;
	pAcrObjPar->nCurrLoopIniKI	= pCtrlObj->m_pDrvCfgPara->mS_FBCurLoop.Ki;
	pAcrObjPar->nVqMax			= pCtrlObj->m_pDrvCfgPara->mS_FBCurLoop.nVqMax;
	pAcrObjPar->nVqMin			= pCtrlObj->m_pDrvCfgPara->mS_FBCurLoop.nVqMin;
	pAcrObjPar->nVdMax			= pCtrlObj->m_pDrvCfgPara->mS_FBCurLoop.nVdMax;
	pAcrObjPar->nVdMin			= pCtrlObj->m_pDrvCfgPara->mS_FBCurLoop.nVdMin;

	pAcrObjPar->nWeakenCurMax	= App2CoreCurTrans(pAppToCore,(s32)pCtrlObj->m_pDrvCfgPara->mS_FBCurLoop.nWeakenCurMax * 10);

	pAcrObjPar->wCloseFreq		= pCtrlObj->m_pDrvCfgPara->mS_FBSlvcCfg0.m_wCloseFreq ;
	
	pAcrObjPar->wMinRunFreq		= pCtrlObj->m_pDrvCfgPara->mS_FBSlvcCfg0.m_wOpenFreq;
	pAcrObjPar->wCurrentClosedFreq	= pCtrlObj->m_pDrvCfgPara->mS_FBSlvcCfg0.m_wCurCloseFreq;

	t_nTmp	= (s32)(pCtrlObj->m_pDrvCfgPara->mS_FBSlvcCfg0.m_wThetaFilTime * pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_nuPWMFreq)/1000;
	pAcrObjPar->nThetaFilTime	= 10240/(10 + t_nTmp);
	
	pAcrObjPar->nPLLKp0				= pCtrlObj->m_pDrvCfgPara->mS_FBSlvcCfg0.nPLLKp0;
	pAcrObjPar->nPLLKi0				= pCtrlObj->m_pDrvCfgPara->mS_FBSlvcCfg0.nPLLKi0;
	pAcrObjPar->nPLLFreq0			= pCtrlObj->m_pDrvCfgPara->mS_FBSlvcCfg0.nPLLFreq0;

	pAcrObjPar->nPLLKp1				= pCtrlObj->m_pDrvCfgPara->mS_FBSlvcCfg0.nPLLKp1;
	pAcrObjPar->nPLLKi1				= pCtrlObj->m_pDrvCfgPara->mS_FBSlvcCfg0.nPLLKi1;	
	pAcrObjPar->nPLLFreq1			= pCtrlObj->m_pDrvCfgPara->mS_FBSlvcCfg0.nPLLFreq1;

	#if 0
	pAcrObjPar->nVFStartValue		= pCtrlObj->m_pDrvCfgPara->mS_FBVF.nVFStartValue;
	pAcrObjPar->nVfVolRamp			= pCtrlObj->m_pDrvCfgPara->mS_FBVF.nVFVoltAcc;
	pAcrObjPar->nVF2CloseDelayTime	= pCtrlObj->m_pDrvCfgPara->mS_FBVF.nVF2CloseDelayTime;
	#endif

	pAcrObjPar->wIPD_PlusWidthSet	= (s32)pCtrlObj->m_pDrvCfgPara->mS_FBIPD.nuIPDPlusTime * pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_nMCUClkFreq;
	pAcrObjPar->wIPD_IdleWaitSet	= (s32)pCtrlObj->m_pDrvCfgPara->mS_FBIPD.nuIPDWaitTime * pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_nMCUClkFreq;
	pAcrObjPar->nuIPD_Comp			= (u16)pCtrlObj->m_pDrvCfgPara->mS_FBIPD.m_wuInitAngComp;
	
}

s16 getBemfAngComp(u8 t_objId)
{
	PSTR_ControlObject pObj = getCtrlObjectPtr(t_objId);
	PSTR_DrvCfgPara pDrvCfgPara = pObj->m_pDrvCfgPara;

	return pDrvCfgPara->mS_FBDirCheck.nBemfAngComp;
}

s16 getBemfTrackMinVolt(u8 t_objId)
{
	PSTR_ControlObject pObj = getCtrlObjectPtr(t_objId);
	PSTR_DrvCfgPara pDrvCfgPara = pObj->m_pDrvCfgPara;

	return pDrvCfgPara->mS_FBDirCheck.nBemfTrackMinVolt;
}


/*****************************************************************************
 * 函数名   : void updateSVPWMParaMALayer(PSTR_ControlObject *pCtrlObj)
 * 说明     : SVPWM控制对象初始化处理函数
 *          : 具体实现，变量初始化
 * 设计思路 ：
 * 参数     ：无
 * 返回值   ：无
 * 修改时间 ：2022.10.24
 *****************************************************************************/
u16 getPWMPrd(PSTR_DrvCfgPara pDrvCfgPara)
{
	s32 temp32;
	temp32 = pDrvCfgPara->mS_GlobalCfg.m_nuPWMFreq * 2 * ((0x01)<< (pDrvCfgPara->mS_GlobalCfg.m_nuPWMPrsc & 0x03));
	temp32 = ((s64)pDrvCfgPara->mS_GlobalCfg.m_nPWMClkFreq * 1000000)/temp32;
	return (u16)temp32;
}
u16 getDeadTime(PSTR_DrvCfgPara pDrvCfgPara)
{
	s32 t_Tmp32;
	t_Tmp32 = (s32)pDrvCfgPara->mS_GlobalCfg.m_nuDeadZone * pDrvCfgPara->mS_GlobalCfg.m_nPWMClkFreq/1000;
	return (u16)t_Tmp32;
}


void updateSVPWMParaMALayer(PSTR_ControlObject pCtrlObj)
{
	PSTR_FocSvpwmPar	pSVPWMObjPar;
	s32 t_wTmp32;	
	
	pSVPWMObjPar = &(pCtrlObj->m_pMotorFocPar->mSvpwmPar);

	pSVPWMObjPar->bSampType		= pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_bSampType;
	pSVPWMObjPar->bSVPWM_Type	= pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_bSVPWMType;		
	
	#if(DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_1SHUNT)	
	{
		pSVPWMObjPar->nuMinPwmSampTime3Shunt	= 0;
		pSVPWMObjPar->nuSampStableTime3Shunt	= 0;

		pSVPWMObjPar->nShiftSampTime3Shunt		= 0;
		pSVPWMObjPar->nSampWaitTime3Shunt		= 0;

		t_wTmp32 = pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_nuDeadZone			
					+ pCtrlObj->m_pDrvCfgPara->mS_FBCurSense.nCurSampStableTime
					+ pCtrlObj->m_pDrvCfgPara->mS_FBCurSense.nCurSampADConvTime ;	
		t_wTmp32 = (s64)t_wTmp32 * pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_nPWMClkFreq/1000;
		pSVPWMObjPar->nSampStableTime1Shunt		= (s16)t_wTmp32;
		
		t_wTmp32 = pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_nuDeadZone 
					+ pCtrlObj->m_pDrvCfgPara->mS_FBCurSense.nCurSampStableTime;
		t_wTmp32 = (s64)t_wTmp32 * pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_nPWMClkFreq/1000;
		pSVPWMObjPar->nuShiftSampTime1Shunt		= (s16)t_wTmp32;

		pSVPWMObjPar->nuPwmPrd		= getPWMPrd(pCtrlObj->m_pDrvCfgPara);
		pSVPWMObjPar->nDeadTime		= getDeadTime(pCtrlObj->m_pDrvCfgPara);
	}
	#elif (DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_2SHUNT)
	#if 0
	{
		pSVPWMObjPar->nuMinPwmSampTime3Shunt	= 0;
		pSVPWMObjPar->nuSampStableTime3Shunt	= 0;

		pSVPWMObjPar->nShiftSampTime3Shunt		= 0;
		pSVPWMObjPar->nSampWaitTime3Shunt		= 0;

		pSVPWMObjPar->nSampStableTime1Shunt		= 0;		
		pSVPWMObjPar->nuShiftSampTime1Shunt		= 0;

		pSVPWMObjPar->nuPwmPrd		= getPWMPrd(pCtrlObj->m_pDrvCfgPara);
		pSVPWMObjPar->nDeadTime		= getDeadTime(pCtrlObj->m_pDrvCfgPara);		
	}
	#else
	{
		s32 t_wTmp32_1;
		s32 t_wTmp32_2;
		// 预留采样时间 Tzero = (Tdead + Tstable) + Tadc >= 2Tadc
		// 最大占空比为 Tprd - Tzero/2
		// 采样点为:    Tzero/2 - Tadc - Tprd   一定大于(-Tprd)
		// 相间采样宽度 : (Tdead + Tstable) + Tadc
		
		pSVPWMObjPar->nuPwmPrd		= getPWMPrd(pCtrlObj->m_pDrvCfgPara);
		pSVPWMObjPar->nDeadTime		= getDeadTime(pCtrlObj->m_pDrvCfgPara);

		// (Tdead + Tstable)
		t_wTmp32_1 = pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_nuDeadZone			
					+ pCtrlObj->m_pDrvCfgPara->mS_FBCurSense.nCurSampStableTime;

		if(t_wTmp32_1 <= pCtrlObj->m_pDrvCfgPara->mS_FBCurSense.nCurSampADConvTime)
		{
			t_wTmp32 = pCtrlObj->m_pDrvCfgPara->mS_FBCurSense.nCurSampADConvTime;
		}
		else
		{
			t_wTmp32 = t_wTmp32_1;
		}

		// Tzero = (Tdead + Tstable) + Tadc >= 2Tadc
		t_wTmp32 += pCtrlObj->m_pDrvCfgPara->mS_FBCurSense.nCurSampADConvTime;
		
		t_wTmp32_2 = (s64)t_wTmp32 * pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_nPWMClkFreq/2000;

		// prd - Tzero/2 
		pSVPWMObjPar->nuMinPwmSampTime3Shunt	= pSVPWMObjPar->nuPwmPrd - (u16)t_wTmp32_2;

		//(Tdead + Tstable + Tadc)
		t_wTmp32_1 +=pCtrlObj->m_pDrvCfgPara->mS_FBCurSense.nCurSampADConvTime;
		t_wTmp32 = (s64)t_wTmp32_1 * pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_nPWMClkFreq/1000;
		pSVPWMObjPar->nuSampStableTime3Shunt	= (u16)(t_wTmp32);

		
		t_wTmp32 = pCtrlObj->m_pDrvCfgPara->mS_FBCurSense.nCurSampADConvTime;		
		t_wTmp32 = (s64)t_wTmp32 * pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_nPWMClkFreq/1000;

		// (Tdead + Tstable + Tadc) - Tadc
		pSVPWMObjPar->nSampWaitTime3Shunt		= pSVPWMObjPar->nuSampStableTime3Shunt - (s16)t_wTmp32;

		// (Tdead + Tstable + Tadc)/2 - Tadc - Tprd
		t_wTmp32 = t_wTmp32_2 - (s16)t_wTmp32 - pSVPWMObjPar->nuPwmPrd;
		pSVPWMObjPar->nShiftSampTime3Shunt		= (s16)t_wTmp32;	
		

		pSVPWMObjPar->nSampStableTime1Shunt		= 0;		
		pSVPWMObjPar->nuShiftSampTime1Shunt		= 0;
	}
	#endif
	#elif ( (DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_3SHUNT)||(DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_MOSFET) )
	{
		s32 t_wTmp32_1;
		s32 t_wTmp32_2;
		pSVPWMObjPar->nuPwmPrd		= getPWMPrd(pCtrlObj->m_pDrvCfgPara);
		pSVPWMObjPar->nDeadTime		= getDeadTime(pCtrlObj->m_pDrvCfgPara);

		// (Tdead + Tstable)
		t_wTmp32_1 = pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_nuDeadZone			
					+ pCtrlObj->m_pDrvCfgPara->mS_FBCurSense.nCurSampStableTime;

		if(t_wTmp32_1 <= pCtrlObj->m_pDrvCfgPara->mS_FBCurSense.nCurSampADConvTime)
		{
			t_wTmp32 = pCtrlObj->m_pDrvCfgPara->mS_FBCurSense.nCurSampADConvTime;
		}
		else
		{
			t_wTmp32 = t_wTmp32_1;
		}

		// Tzero = (Tdead + Tstable) + Tadc >= 2Tadc
		t_wTmp32 += pCtrlObj->m_pDrvCfgPara->mS_FBCurSense.nCurSampADConvTime;
		
		t_wTmp32_2 = (s64)t_wTmp32 * pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_nPWMClkFreq/2000;

		// prd - Tzero/2 
		pSVPWMObjPar->nuMinPwmSampTime3Shunt	= pSVPWMObjPar->nuPwmPrd - (u16)t_wTmp32_2;

		//(Tdead + Tstable + Tadc)
		t_wTmp32_1 +=pCtrlObj->m_pDrvCfgPara->mS_FBCurSense.nCurSampADConvTime;
		t_wTmp32 = (s64)t_wTmp32_1 * pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_nPWMClkFreq/1000;
		pSVPWMObjPar->nuSampStableTime3Shunt	= (u16)(t_wTmp32);

		
		t_wTmp32 = pCtrlObj->m_pDrvCfgPara->mS_FBCurSense.nCurSampADConvTime;		
		t_wTmp32 = (s64)t_wTmp32 * pCtrlObj->m_pDrvCfgPara->mS_GlobalCfg.m_nPWMClkFreq/1000;

		// (Tdead + Tstable + Tadc) - Tadc
		pSVPWMObjPar->nSampWaitTime3Shunt		= pSVPWMObjPar->nuSampStableTime3Shunt - (s16)t_wTmp32;

		// (Tdead + Tstable + Tadc)/2 - Tadc - Tprd
		t_wTmp32 = t_wTmp32_2 - (s16)t_wTmp32 - pSVPWMObjPar->nuPwmPrd;
		pSVPWMObjPar->nShiftSampTime3Shunt		= (s16)t_wTmp32;	
		

		pSVPWMObjPar->nSampStableTime1Shunt		= 0;		
		pSVPWMObjPar->nuShiftSampTime1Shunt		= 0;
	}
	
	#endif	
}


