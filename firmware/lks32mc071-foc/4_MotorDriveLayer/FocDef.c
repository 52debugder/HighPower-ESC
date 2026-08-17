/*******************************************************************************
 * 版权所有 (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： FocDef.c
 * 文件标识：
 * 内容摘要： Define the basic function of motor vector control
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： LKS/MC TEAM
 * 完成日期： 2022年8月11日
 *******************************************************************************/

/* Standard include ----------------------------------------------------------*/
#include "mc_declaration.h"
#include "MathLIB_Inlines.h"
#include "math.h"
#include "MC_type.h"
#include "MC_Math.h"
#include "hardware_config.h"
#include "PubData_DriverInstance.h"

// 各层控制对象下标对齐
// 编译宏静态实现

// 动态实现方式后续完善

/*******************************************************************************/
//全局变量定义区

STR_MotorFoc 						gS_FocObjM[MAX_DRV_MODULE_USED];			// FOC 控制对象定义
STR_MotorFocElement					gS_FocElementObjM[MAX_DRV_MODULE_USED];		// FOC 变量定义
u8									g_buMdPWMONDelay[MAX_DRV_MODULE_USED];		// PWM ON delay 计数

const STR_MotorFocHandle			gS_MotorFocHandleM[MAX_DRV_MODULE_USED] = {		// FOC 模块实现函数，目前仅为SVPWM函数
																	Motor_FocMethod_M0
																	};

extern const STR_HALDrvHandle	 	gS_MotorHalDrvHandleM[MAX_DRV_MODULE_USED];		//	硬件驱动实现函数数据结构

void SVPWM_1ShuntGetPhaseIcNIa(PSTR_CurSamplingRes this);
void SVPWM_2ShuntGetPhaseIaIb(PSTR_CurSamplingRes this);
void SVPWM_3ShuntGetPhaseIaIb(PSTR_CurSamplingRes this);


/*******************************************************************************/
//外部函数引用区
extern	PSTR_ControlObject	getCtrlObjectPtr(u8 objID);
extern	STR_ControlObject	gS_PhyObjInstanceM[MAX_DRV_MODULE_USED];

extern	void				RegisterObsDatStr(PSTR_MotorFoc tS_pMotorFoc);

extern	s16					Sqrt_Functions(s16 x,s16 y);
extern	void				setObserPLLKpKi(u8 t_bObjId,u16 Kp, u16 Ki);
extern	s32					User2AppFreqTrans(STR_TransCoefElement* pUser2App,float val);

extern	bool				getCurLoopCloseStatusFromOB(u8 t_bObjId);
extern	s16					getVdcCirCleLim(u8 tobjId);

/*******************************************************************************/
//静态局部函数区
/*****************************************************************************************/	 

/*******************************************************************************
 函数名称：    RegisterMdGlobal
 功能描述：    注册控制对象数据结构
 输入参数：    按控制对象指针tS_pMotorFoc，全局数据指针tS_pControlObject
 输出参数：    无
 返 回 值：    无
 其它说明：    MD层控制对象数据结构注册，数据交换区、标幺变换系数、FOC参数

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           WenCai Zhao          创建
 *******************************************************************************/
static void RegisterMdGlobal(PSTR_MotorFoc tS_pMotorFoc,PSTR_ControlObject tS_pControlObject)
{
	tS_pMotorFoc->m_bPWM_ID			= tS_pControlObject->m_bPWM_Id;							//PWM ID
	tS_pMotorFoc->m_bSampType		= (u8)tS_pControlObject->m_pDrvCfgPara->mS_GlobalCfg.m_bSampType; //电流采样方式
	tS_pMotorFoc->pHdToMd			= &tS_pControlObject->mGlobalDatPackage.mHdToMd;		//Hd层到Md层Data指针 赋值
	tS_pMotorFoc->pMdToHd			= &tS_pControlObject->mGlobalDatPackage.mMdToHd;		//Md层到Hd层Data指针 赋值
	
	tS_pMotorFoc->pMaToMd			= &tS_pControlObject->mGlobalDatPackage.mMaToMd;		//Ma层到Md层Data指针 赋值
	tS_pMotorFoc->pMdToMa			= &tS_pControlObject->mGlobalDatPackage.mMdToMa;		//Md层到Ma层Data指针 赋值
	
	tS_pMotorFoc->m_pTransCoef		= &tS_pControlObject->mTransCoef;						//标幺系数指针赋值
	
	tS_pMotorFoc->m_pMotorFocPar	= tS_pControlObject->m_pMotorFocPar;					//FOC参数指针赋值
		
}

/*******************************************************************************
 函数名称：    RegisterMethodHandle
 功能描述：    FOC控制实现方法指针函数
 输入参数：    按控制对象指针tS_pFocObj，全局数据指针tS_pMotorFocHandle
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           WenCai Zhao          创建
 *******************************************************************************/
static void RegisterMethodHandle(PSTR_MotorFoc tS_pFocObj, PSTR_MotorFocHandle tS_pMotorFocHandle)
{
	tS_pFocObj->m_pHandle		= tS_pMotorFocHandle;
}

/*******************************************************************************
 函数名称：    RegisterHalDrvHandle
 功能描述：    MD2HD驱动调用函数接口
 输入参数：    按控制对象指针tS_pFocObj，全局数据指针tS_pMotorHalDrvHandle
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           WenCai Zhao          创建
 *******************************************************************************/
static void RegisterHalDrvHandle(PSTR_MotorFoc tS_pFocObj, PSTR_HALDrvHandle tS_pMotorHalDrvHandle)
{
	tS_pFocObj->m_pHALHandle	= tS_pMotorHalDrvHandle;
}

/*******************************************************************************
 函数名称：    RegisterMdLocal
 功能描述：    注册控制对象本地数据结构
 输入参数：    按控制对象指针tS_pMotorFoc，local数据指针tS_pMotorFocElement
 输出参数：    无
 返 回 值：    无
 其它说明：    MD层控制对象数据结构注册，MD层FOC控制local数据

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           WenCai Zhao          创建
 *******************************************************************************/
static void RegisterMdLocal(PSTR_MotorFoc tS_pMotorFoc,PSTR_MotorFocElement tS_pMotorFocElement)
{
	tS_pMotorFoc->m_pStatCurrUVW	= &tS_pMotorFoc->pMdToMa->mStatCurrUVW;			//定子电流UVW
	tS_pMotorFoc->m_pStatCurrDQ		= &tS_pMotorFoc->pMdToMa->mStatCurDQ;			//定子电流DQ
	tS_pMotorFoc->m_pStatCurrDQRef	= &tS_pMotorFoc->pMaToMd->mStatCurDQCmd;		//定子电流反馈

	tS_pMotorFoc->m_pAcrD			= &tS_pMotorFocElement->mAcrD;					//d轴电流调节
	tS_pMotorFoc->m_pVolDQ			= &tS_pMotorFocElement->mAcrOutDQ;				//电流环输出
	tS_pMotorFoc->m_pAcrQ			= &tS_pMotorFocElement->mAcrQ;					//q轴电流调节
	tS_pMotorFoc->m_pMotorAngle		= &tS_pMotorFocElement->mMotorAngle;			//电机角度

	tS_pMotorFoc->m_pCmpr			= &tS_pMotorFoc->pMdToHd->mMcPwm;				//电机驱动层返回值
	tS_pMotorFoc->m_pTmr			= &tS_pMotorFoc->pMdToHd->mMcTmr;				//电机驱动层返回值

	tS_pMotorFoc->m_pMotorFocSpeed	= &tS_pMotorFocElement->mMotorSpeed;			//电机转速
	tS_pMotorFoc->m_pVectVolAB		= &tS_pMotorFocElement->mStatVolAB;				//定子角度
	tS_pMotorFoc->m_pFluxObsGain	= &tS_pMotorFocElement->mFluxObsGain;			//观测器参数变量定义
	
	tS_pMotorFoc->m_pSvpwmPar		= &tS_pMotorFoc->m_pMotorFocPar->mSvpwmPar;		//SvPwm参数
	tS_pMotorFoc->m_pFocObjPar		= &tS_pMotorFoc->m_pMotorFocPar->mObjPar;		//FOC硬件参数
	tS_pMotorFoc->m_pFocObsPar		= &tS_pMotorFoc->m_pMotorFocPar->mObsPar;		//FOC观测器参数
	
	tS_pMotorFoc->mCurSamplingRes.pAdcRes	= tS_pMotorFoc->pHdToMd;				//采样值
	tS_pMotorFoc->m_pStatCurrAB				= &tS_pMotorFocElement->mStatCurrAB;	//定子电流AB
	
}

/*******************************************************************************
 函数名称：    InitCmpr
 功能描述：    比较器数据初始化
 输入参数：    按控制对象指针tS_pMotorFoc
 输出参数：    无
 返 回 值：    无
 其它说明：    初始化PWM比较器数据为默认值

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           WenCai Zhao          创建
 *******************************************************************************/
static void InitCmpr(PSTR_MotorFoc tS_pFocObj)
{
	u16 t_cmpr;
	t_cmpr = tS_pFocObj->m_pSvpwmPar->nuPwmPrd>>1;
	tS_pFocObj->m_pCmpr->nuTimePhA  =  t_cmpr;    //PhA 赋值
	tS_pFocObj->m_pCmpr->nuTimePhB  =  t_cmpr;    //PhB 赋值
	tS_pFocObj->m_pCmpr->nuTimePhC  =  t_cmpr;    //PhC 赋值
	tS_pFocObj->m_pCmpr->nuTimePhAN = -t_cmpr;    //PhAN 赋值
	tS_pFocObj->m_pCmpr->nuTimePhBN = -t_cmpr;    //PhBN 赋值
	tS_pFocObj->m_pCmpr->nuTimePhCN = -t_cmpr;    //PhCN 赋值
}

/*******************************************************************************
 函数名称：    InitMotorDriveLayer
 功能描述：    MD电机驱动层初始化函数
 输入参数：    void
 输出参数：    无
 返 回 值：    无
 其它说明：    初始化MD层数据结构等

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0           WenCai Zhao          创建
 2023/2/19      V1.01          Tonghua Li           修改部分功能
 *******************************************************************************/
/* 单电机MD层初始化函数 */
void InitMotorDriveLayer(void)
{
	s16 factor;
	gS_FocObjM[0].m_bFOCObj_ID	= 0;
	RegisterMdGlobal(&gS_FocObjM[0],&gS_PhyObjInstanceM[0]); //注册控制对象全局数据结构
	#if (DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_1SHUNT)        //单电阻采样方式
		gS_FocObjM[0].mCurSamplingRes.mCurSamplingEvent.pAdcSamp = (ADCSampFunction)&SVPWM_1ShuntGetPhaseIcNIa;
	#elif (DRV0_CUR_SAMP_TYPE == CURRENT_SAMPLE_2SHUNT)	    //双电阻采样方式	
		gS_FocObjM[0].mCurSamplingRes.mCurSamplingEvent.pAdcSamp = (ADCSampFunction)&SVPWM_2ShuntGetPhaseIaIb;
	#else                                                   //三电阻或MOS内阻采样方式
		gS_FocObjM[0].mCurSamplingRes.mCurSamplingEvent.pAdcSamp = (ADCSampFunction)&SVPWM_3ShuntGetPhaseIaIb;
	#endif
	
	RegisterMdLocal(&gS_FocObjM[0],&gS_FocElementObjM[0]);  //注册控制对象本地数据结构
	RegisterMethodHandle(&gS_FocObjM[0],(PSTR_MotorFocHandle)&gS_MotorFocHandleM[0]);   //注册FOC控制实现方法指针函数

	RegisterObsDatStr(&gS_FocObjM[0]);                      //注册观测器数据指针

	RegisterHalDrvHandle(&gS_FocObjM[0],(PSTR_HALDrvHandle)&gS_MotorHalDrvHandleM[0]);  //注册MD2HD驱动调用函数接口

	factor = gS_PhyObjInstanceM[0].m_pDrvCfgPara->mS_GlobalCfg.m_nOverModuFactor;
	setOverModuFac(0, factor);
}

PSTR_MotorFoc getFocObject(u8 t_bPWMId)
{
	return &gS_FocObjM[0];	
}

/*******************************************************************************
 函数名称：    getAngleErrOpen2Close
 功能描述：    计算估算角度和强拖给定角度的误差
 输入参数：    t_bObjId
 输出参数：    无
 返 回 值：    无
 其它说明：    MA层调用该函数估算角度和强拖给定角度的误差

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/19     V1.0          Tonghua Li         修改部分功能
 *******************************************************************************/
s32 getAngleErrOpen2Close(u8 t_bObjId)
{
	PSTR_MotorFoc	tS_pMotorFoc;
	s32 tS_err;
	tS_pMotorFoc	= &gS_FocObjM[t_bObjId];
	if(tS_pMotorFoc != NULL)
	{
		tS_err		= tS_pMotorFoc->m_pMotorAngle->wElectAngleEst - tS_pMotorFoc->m_pMotorAngle->wElectAngleOpen;
		return tS_err;
	}
	else
	{
		return 0;		
	}	
}


/*****************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////
///////////////////init funcs glb///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*****************************************************************************************/	 



/*****************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////
///////////////////init funcs loc///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*****************************************************************************************/	 

/*******************************************************************************
 函数名称：    void setCurrentPIParameter(u8 t_ObjId, u16 Kp_D,u16 Ki_d, u16 Kp_Q,u16 Ki_Q)
 功能描述：    FOC电路环数据初始化
 输入参数：    按控制对象 t_ObjId
 输出参数：    无
 返 回 值：    无
 其它说明：    初始化电流环PI参数，需要执行在InitFocVar函数值之后

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/10/19     V1.1          Tonghua Li           修改部分功能 memset
 *******************************************************************************/
void setCurrentPIParameter(u8 t_ObjId, u16 Kp_D,u16 Ki_D, u16 Kp_Q,u16 Ki_Q)
{
	PSTR_MotorFoc tS_pFocObj	= &gS_FocObjM[t_ObjId];

	tS_pFocObj->m_pAcrD->KP		= Kp_D;  //d轴电流环Kp初始化
	tS_pFocObj->m_pAcrD->KI		= Ki_D;  //d轴电流环Ki初始化
	
	tS_pFocObj->m_pAcrQ->KP		= Kp_Q;  //q轴电流环Kp初始化
	tS_pFocObj->m_pAcrQ->KI		= Ki_Q;  //q轴电流环Ki初始化
}


/*******************************************************************************
 函数名称：    InitFocVar
 功能描述：    FOC数据初始化
 输入参数：    按控制对象指针tS_pMotorFoc
 输出参数：    无
 返 回 值：    无
 其它说明：    初始化PWM比较器数据为默认值

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/8/19      V1.0          WenCai Zhao          创建
 2023/10/19     V1.1          Tonghua Li           修改部分功能 memset
 *******************************************************************************/
void InitFocVar(PSTR_MotorFoc tS_pFocObj)
{
	tS_pFocObj->eMotorStatusAck			= E_MOTOR_RESET;		//初始化状态机
	
	STR_PIRegulator*	tS_pAcrD		= tS_pFocObj->m_pAcrD;  //d轴电流环指针传递
	STR_PIRegulator*	tS_pAcrQ		= tS_pFocObj->m_pAcrQ;  //q轴电流环指针传递



	memset(tS_pAcrD,0,sizeof(STR_PIRegulator));           //清空d轴PI调节器各变量
	// if necessary,	manual change currentloop PI parameter 
	tS_pAcrD->KP						= tS_pFocObj->m_pFluxObsGain->nD_CurrLoopKP;	//可重新赋值电流环PI
	tS_pAcrD->KI						= tS_pFocObj->m_pFluxObsGain->nD_CurrLoopKI;	
	tS_pAcrD->wLowerLimitOutput			=(s32)tS_pFocObj->m_pFocObsPar->nVdMin<<16;		//积分下限限幅
	tS_pAcrD->wUpperLimitOutput			=(s32)tS_pFocObj->m_pFocObsPar->nVdMax<<16;		//积分上限限幅
	
	
	memset(tS_pAcrQ,0,sizeof(STR_PIRegulator));           //清空q轴PI调节器各变量
	// if necessary,	manual change currentloop PI parameter 
	tS_pAcrQ->KP						= tS_pFocObj->m_pFluxObsGain->nQ_CurrLoopKP;	//可重新赋值电流环PI
	tS_pAcrQ->KI						= tS_pFocObj->m_pFluxObsGain->nQ_CurrLoopKI;
	tS_pAcrQ->wLowerLimitOutput			=(s32)tS_pFocObj->m_pFocObsPar->nVqMin<<16;		//积分下限限幅
	tS_pAcrQ->wUpperLimitOutput			=(s32)tS_pFocObj->m_pFocObsPar->nVqMax<<16;		//积分上限限幅
	


	tS_pFocObj->m_pVolDQ->nAxisD				= 0;				//d轴电压初始化
	tS_pFocObj->m_pVolDQ->nAxisQ				= 0;				//q轴电压初始化

	memset(tS_pFocObj->m_pMotorAngle,0,sizeof(STR_MotorFocAngle));	//清空电机角度变量


	tS_pFocObj->mSinCosFocAngle.hSin			= 0;				//角度sin值初始化
	tS_pFocObj->mSinCosFocAngle.hCos			= 32767;			//角度cos值初始化

	//tS_pFocObj->m_pStatCurrAB->nAlph			= 0;				//Alph轴电流初始化
	//tS_pFocObj->m_pStatCurrAB->nBeta			= 0;				//Beta轴电流初始化

	tS_pFocObj->m_pStatCurrDQ->nAxisD			= 0;				//d轴电流初始化
	tS_pFocObj->m_pStatCurrDQ->nAxisQ			= 0;				//q轴电流初始化
	
	tS_pFocObj->m_pMotorFocSpeed->wSpeedRef		= 0;				//给定转速初始化
	tS_pFocObj->m_pMotorFocSpeed->wSpeedEst		= 0;				//观测转速初始化
	
	tS_pFocObj->m_pStatCurrDQRef->nAxisD		= 0;				//给定d轴电流初始化
	tS_pFocObj->m_pStatCurrDQRef->nAxisQ		= 0;				//给定q轴电流初始化
	
	tS_pFocObj->m_pVectVolAB->nAlph				= 0;				//Alph轴电压初始化
	tS_pFocObj->m_pVectVolAB->nBeta				= 0;				//Beta轴电压初始化

	tS_pFocObj->m_bIPDFinsh						= 0;				//IPD标志位初始化

	InitCmpr(tS_pFocObj);                                  //比较器数据初始化
}


/*****************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////
///////////////////init funcs loc///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*****************************************************************************************/	 




	 
/*****************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////
///////////////////init funcs..end///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*****************************************************************************************/	 	 

/*******************************************************************************
 函数名称：    void SVPWM_GetPhaseCurrent(PSTR_CurSamplingRes this)
 功能描述：    电流采样函数
 输入参数：    PSTR_CurSamplingRes this  结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：	   优化为通过函数指针调用实现，缩小采样时间
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/03/23    V1.0           Tonghua Li          创建
 *******************************************************************************/
void SVPWM_GetPhaseCurrent(PSTR_CurSamplingRes this)
{
    this->mCurSamplingEvent.pAdcSamp(this);
}

/*******************************************************************************
 函数名称：    void SVPWM_1ShuntGetPhaseCurrentxx(PSTR_CurSamplingRes this)
 功能描述：    单电阻采样算法根据SVPWM调制扇区，得到U, V相电流
 输入参数：    PSTR_CurSamplingRes this  结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：	   优化为通过函数指针调用实现，缩小采样时间
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/03/23    V1.0           Tonghua Li          创建
 *******************************************************************************/
//sector 1 ic---Nia
void SVPWM_1ShuntGetPhaseIcNIa(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatW = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatU =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatV = -(this->pAdcRes->nSampDatW + this->pAdcRes->nSampDatU);
}

void SVPWM_1ShuntGetPhaseOldIcNIa(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatU =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatV = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseIcNOldIa(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatW = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatV = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseOldIcNOldIa(PSTR_CurSamplingRes this)
{
	return;
}

//sector 2 Ib NIa
void SVPWM_1ShuntGetPhaseIbNIa(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatV = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatU =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatW = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatV);
}

void SVPWM_1ShuntGetPhaseOldIbNIa(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatU =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatW = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatV);
}

void SVPWM_1ShuntGetPhaseIbNOldIa(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatV = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatW = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatV);
}

void SVPWM_1ShuntGetPhaseOldIbNOldIa(PSTR_CurSamplingRes this)
{
	return;
}

//sector 3 Ib NIc
void SVPWM_1ShuntGetPhaseIbNIc(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatV = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatW =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatU = -(this->pAdcRes->nSampDatV + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseOldIbNIc(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatW =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatU = -(this->pAdcRes->nSampDatV + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseIbNOldIc(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatV = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatU = -(this->pAdcRes->nSampDatV + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseOldIbNOldIc(PSTR_CurSamplingRes this)
{
	return;
}

//sector 4 Ic NIb
void SVPWM_1ShuntGetPhaseIcNIb(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatW = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatV =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatU = -(this->pAdcRes->nSampDatV + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseOldIcNIb(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatV =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatU = -(this->pAdcRes->nSampDatV + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseIcNOldIb(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatW = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatU = -(this->pAdcRes->nSampDatV + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseOldIcNOldIb(PSTR_CurSamplingRes this)
{
	return;
}

//sector 5 Ia NIb
void SVPWM_1ShuntGetPhaseIaNIb(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatU = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatV =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatW = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatV);
}

void SVPWM_1ShuntGetPhaseOldIaNIb(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatV =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatW = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatV);
}

void SVPWM_1ShuntGetPhaseIaNOldIb(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatU = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatW = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatV);
}

void SVPWM_1ShuntGetPhaseOldIaNOldIb(PSTR_CurSamplingRes this)
{
	return;
}

//sector 6 Ia NIc
void SVPWM_1ShuntGetPhaseIaNIc(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatU = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatW =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatV = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseOldIaNIc(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatW =(s32)(this->pAdcRes->nBusShuntOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatV = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseIaNOldIc(PSTR_CurSamplingRes this)
{
	this->pAdcRes->nSampDatU = this->pAdcRes->nSampCurDat0 - (s32)(this->pAdcRes->nBusShuntOffset);
	this->pAdcRes->nSampDatV = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatW);
}

void SVPWM_1ShuntGetPhaseOldIaNOldIc(PSTR_CurSamplingRes this)
{
	return;
}

/*******************************************************************************
 函数名称：    void SVPWM_2ShuntGetPhaseCurrent(PSTR_CurSamplingRes this)
 功能描述：    双电阻采样算法根据SVPWM调制扇区，得到U, V相电流
 输入参数：    PSTR_CurSamplingRes this  结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：    优化为通过函数指针调用实现，缩小采样时间
 修改日期	   版本号		   修改人			 修改内容
 -----------------------------------------------------------------------------
 2023/03/23    V1.0 		  Tonghua Li		  创建
 *******************************************************************************/
void SVPWM_2ShuntGetPhaseCurrent(PSTR_CurSamplingRes this)
{
    this->mCurSamplingEvent.pAdcSamp(this);
}

void SVPWM_2ShuntGetPhaseIaIb(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatU = (s32)(this->pAdcRes->nPhaseUOffset) - this->pAdcRes->nSampCurDat0;
	this->pAdcRes->nSampDatV = (s32)(this->pAdcRes->nPhaseVOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatW = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatV);
}


/*******************************************************************************
 函数名称：    void SVPWM_3ShuntGetPhasexx(PSTR_CurSamplingRes this)
 功能描述：    三电阻采样算法根据SVPWM调制扇区，得到U, V相电流
 输入参数：    PSTR_CurSamplingRes this  结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：    优化为通过函数指针调用实现，缩小采样时间
 修改日期	   版本号		   修改人			 修改内容
 -----------------------------------------------------------------------------
 2023/03/23    V1.0 		  Tonghua Li		  创建
 *******************************************************************************/
void SVPWM_3ShuntGetPhaseIaIb(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatU = (s32)(this->pAdcRes->nPhaseUOffset) - this->pAdcRes->nSampCurDat0;
	this->pAdcRes->nSampDatV = (s32)(this->pAdcRes->nPhaseVOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatW = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatV);
}

void SVPWM_3ShuntGetPhaseOldIaOldIb(PSTR_CurSamplingRes this)
{	
	return;
}


void SVPWM_3ShuntGetPhaseIaIc(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatU = (s32)(this->pAdcRes->nPhaseUOffset) - this->pAdcRes->nSampCurDat0;
	this->pAdcRes->nSampDatW = (s32)(this->pAdcRes->nPhaseWOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatV = -(this->pAdcRes->nSampDatU + this->pAdcRes->nSampDatW);
}

void SVPWM_3ShuntGetPhaseOldIaOldIc(PSTR_CurSamplingRes this)
{	
	return;
}

void SVPWM_3ShuntGetPhaseIbIc(PSTR_CurSamplingRes this)
{	
	this->pAdcRes->nSampDatV = (s32)(this->pAdcRes->nPhaseVOffset) - this->pAdcRes->nSampCurDat0;
	this->pAdcRes->nSampDatW = (s32)(this->pAdcRes->nPhaseWOffset) - this->pAdcRes->nSampCurDat1;
	this->pAdcRes->nSampDatU = -(this->pAdcRes->nSampDatV + this->pAdcRes->nSampDatW);
}

void SVPWM_3ShuntGetPhaseOldIbOldIc(PSTR_CurSamplingRes this)
{	
	return;
}

//////////////////////////////////
///////////////////////////////////////////////////

/*******************************************************************************
 函数名称：    void AdcSampleCal(stru_FOC_CtrProcDef *this)
 功能描述：    电流采样
 输入参数：    stru_FOC_CtrProcDef *this 结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：    1.电流采样，采集AB两相电流
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0            Wencai.Zhao Howlet Li          创建
 *******************************************************************************/
#if 0
void AdcCurSampleCalc(PSTR_MotorFoc tS_pFocObj)
{
    PSTR_CurSamplingRes this;
    this = &tS_pFocObj->mCurSamplingRes;  //指针

	tS_pFocObj->m_pHandle->ReConstructCurrent(&tS_pFocObj->mCurSamplingRes);
    /* 电流标幺化处理 */
	tS_pFocObj->m_pStatCurrUVW->nPhaseU = _IQ15mpy(this->pAdcRes->nSampDatU, tS_pFocObj->m_pFluxObsGain->CurrentPerUnitGAIN);
	tS_pFocObj->m_pStatCurrUVW->nPhaseV = _IQ15mpy(this->pAdcRes->nSampDatV, tS_pFocObj->m_pFluxObsGain->CurrentPerUnitGAIN);
	tS_pFocObj->m_pStatCurrUVW->nPhaseW = -(tS_pFocObj->m_pStatCurrUVW->nPhaseU + tS_pFocObj->m_pStatCurrUVW->nPhaseV);

    /* clark变换 */
	tS_pFocObj->m_pStatCurrAB->nBeta = _IQ15mpy(18919, (tS_pFocObj->m_pStatCurrUVW->nPhaseV - tS_pFocObj->m_pStatCurrUVW->nPhaseW));
	tS_pFocObj->m_pStatCurrAB->nAlph = tS_pFocObj->m_pStatCurrUVW->nPhaseU;
}
#endif

 /*******************************************************************************
 函数名称：    s16 CurrentPIRegulator(stru_PIRegulator *Regulator)
 功能描述：    电流环PI  增量式PI
 输入参数：    stru_PIRegulator *Regulator 结构体指针
 输出参数：    PI调节结果
 返 回 值：    无
 其它说明：		Ki -Q16 /Kp -Q12
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           WenCai Zhao          创建
 *******************************************************************************/
s16 CurrentPIRegulator(STR_PIRegulator* tS_pAcr)
{
    s32		ACC;
	s32		wTemp;
    s32		AX;
	
    ACC = (tS_pAcr->nError - tS_pAcr->nLastError) * tS_pAcr->KP;	/* 比例项计算 */
    ACC = (ACC << 4) + (s32)(tS_pAcr->nError) * tS_pAcr->KI;		/* 积分项计算 */
    tS_pAcr->wIntegral = ACC + tS_pAcr->wIntegral;
	
	wTemp					= (((s32)tS_pAcr->nComp) << 16) + tS_pAcr->wIntegral;
	
	if(wTemp > tS_pAcr->wUpperLimitOutput)                /* 输出最大值限幅 */
    {        
		wTemp				= tS_pAcr->wUpperLimitOutput;
		tS_pAcr->wIntegral	= tS_pAcr->wUpperLimitOutput - (((s32)tS_pAcr->nComp) << 16);
		
    }
    else if(wTemp < tS_pAcr->wLowerLimitOutput)         /* 输出最小值限幅 */
    {
        wTemp				= tS_pAcr->wLowerLimitOutput;
		tS_pAcr->wIntegral	= tS_pAcr->wLowerLimitOutput - (((s32)tS_pAcr->nComp) << 16);
    }
	AX = wTemp >> 16;

    tS_pAcr->nLastError = tS_pAcr->nError;				/* 记录上次误差值 */

    return(AX);                                                          
}


/*******************************************************************************
 函数名称：    RegMotorCurrentDQ(stru_FOC_CurrLoopDef *this)
 功能描述：    D、Q轴电流计算，输出Vd、Vq
 输入参数：    stru_FOC_CurrLoopDef *this  结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/08/05      V1.0           Howlet  Li          创建
 2023/03/23      V1.1           Tonghua Li          修改为可选择模式
 *******************************************************************************/
void RegMotorCurrentDQ(PSTR_MotorFoc tS_pFocObj)
{
	if(!tS_pFocObj->bObserWork)
	{

		#if (VF_START_FUNCTION_ENABLE == FUNCTION_ON)
		
		if(!getCurLoopCloseStatusFromOB(tS_pFocObj->m_bFOCObj_ID))	//电流环开环
		{
			tS_pFocObj->m_pAcrQ->nError = 0;
			tS_pFocObj->m_pAcrD->nError = 0;
		}
		else														//电流环闭环
		#endif
		{		
			tS_pFocObj->m_pAcrQ->nError = (s32)tS_pFocObj->m_pStatCurrDQRef->nAxisQ - tS_pFocObj->m_pStatCurrDQ->nAxisQ; /* Q轴输入误差 */
			tS_pFocObj->m_pAcrD->nError = (s32)tS_pFocObj->m_pStatCurrDQRef->nAxisD - tS_pFocObj->m_pStatCurrDQ->nAxisD;  /* D轴输入误差 */
		}
		
		tS_pFocObj->m_pVolDQ->nAxisQ = CurrentPIRegulator(tS_pFocObj->m_pAcrQ);		/* Q轴电流PI计算，输出Vq */
		tS_pFocObj->m_pVolDQ->nAxisD = CurrentPIRegulator(tS_pFocObj->m_pAcrD);		/* D轴电流PI计算，输出Vd */
	}

	//@call:
	CalcVolCircle(tS_pFocObj->m_bFOCObj_ID,tS_pFocObj->m_pVolDQ,tS_pFocObj->m_pVectVolAB);
}

/*******************************************************************************
 函数名称：    void SetCmprDuty(PSTR_McpwmCmpr tS_Cmpr,u16 nuTime)
 功能描述：    设置PWM比较装在数值
 输入参数：    PSTR_McpwmCmpr tS_Cmpr  结构体指针
 			   u16 nuTime
 			   
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/10/15      V1.0          			          创建
 *******************************************************************************/
void SetCmprDuty(PSTR_McpwmCmpr tS_Cmpr,u16 nuTime)
{
	tS_Cmpr->nuTimePhA		= nuTime;
	tS_Cmpr->nuTimePhB		= nuTime;
	tS_Cmpr->nuTimePhC		= nuTime;
	
	tS_Cmpr->nuTimePhAN		= -nuTime;
	tS_Cmpr->nuTimePhBN		= -nuTime;
	tS_Cmpr->nuTimePhCN		= -nuTime;
}

/*******************************************************************************
 函数名称：    updateObserPLLVar1msLoop(PSTR_MotorFoc tS_pMotorFoc)
 功能描述：    PLL Kp Ki计算
 输入参数：    PSTR_MotorFoc tS_pMotorFoc  结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2023/1/20      V1.0           Li Tonghua          创建
 *******************************************************************************/
void updateObserPLLVar1msLoop(PSTR_MotorFoc tS_pMotorFoc)
{
	s16 PLLKp;
	s16 PLLKi;

	s32 FreqStart;
	s32 FreqRef;	
	s32 deltHz;
	s32 deltFreq;
	
	STR_TransCoefElement *PCoreToApp	= &(tS_pMotorFoc->m_pTransCoef->mCoreToApp);  //标幺化系数CoreToApp指针传递
	PSTR_FocObsPar			 t_pFocObsPar = tS_pMotorFoc->m_pFocObsPar;                 //观测器变量指针传递

	// 数据格式0.1Hz
	deltFreq	= (s32)t_pFocObsPar->nPLLFreq1 - t_pFocObsPar->nPLLFreq0;
	FreqStart	= t_pFocObsPar->nPLLFreq0;
	
	PLLKp		= t_pFocObsPar->nPLLKp1 - t_pFocObsPar->nPLLKp0;
	PLLKi		= t_pFocObsPar->nPLLKi1 - t_pFocObsPar->nPLLKi0;

	// user to app 表示为0.01Hz      ------> 0.1Hz
	FreqRef			= Core2AppFreqTrans(PCoreToApp,tS_pMotorFoc->m_pMotorFocSpeed->wSpeedRef);
	FreqRef			= (FreqRef * _IQ15(0.1)) >> 15;
	FreqRef			= ABS(FreqRef);
	
	if(FreqRef >= FreqStart)
	{
		deltHz		= (FreqRef - FreqStart);
		deltHz		= deltHz << 15;
	
		deltFreq	= deltHz/deltFreq;
		
		PLLKp		= (deltFreq  * PLLKp) >> 15;		
		PLLKi		= (deltFreq  * PLLKi) >> 15;
	}
	else
	{
		PLLKp		= 0;
		PLLKi		= 0;
	}

	/* 分段式PI计算函数 */
	PLLKp		= t_pFocObsPar->nPLLKp0 + PLLKp;
	PLLKi		= t_pFocObsPar->nPLLKi0 + PLLKi;	

	PLLKp		= PLLKp > t_pFocObsPar->nPLLKp1 ? t_pFocObsPar->nPLLKp1: PLLKp;
	PLLKp		= PLLKp < t_pFocObsPar->nPLLKp0 ? t_pFocObsPar->nPLLKp0: PLLKp;

	PLLKi		= PLLKi > t_pFocObsPar->nPLLKi1 ? t_pFocObsPar->nPLLKi1: PLLKi;
	PLLKi		= PLLKi < t_pFocObsPar->nPLLKi0 ? t_pFocObsPar->nPLLKi0: PLLKi;

	setObserPLLKpKi(tS_pMotorFoc->m_bFOCObj_ID,PLLKp,PLLKi);
}

/*******************************************************************************
 函数名称：    bool	getIPD_CW_AngComp(PSTR_MotorFoc tS_pFocObj)
 			   bool	getIPD_CCW_AngComp(PSTR_MotorFoc tS_pFocObj)
 功能描述：    IPD 补偿角度 CW/CCW判断
 输入参数：    PSTR_MotorFoc tS_pMotorFoc  结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：    库函数调用
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/12/20      V1.0           Li Tonghua          创建
 *******************************************************************************/
bool	getIPD_CW_AngComp(PSTR_MotorFoc tS_pFocObj)
{
	return (tS_pFocObj->pMaToMd->nuFineCmd == E_FC_IPD_CW_START);    //  CW IPD 补偿角度判断
}

bool	getIPD_CCW_AngComp(PSTR_MotorFoc tS_pFocObj)
{
	return (tS_pFocObj->pMaToMd->nuFineCmd == E_FC_IPD_CCW_START);   // CCW IPD 补偿角度判断
}

/*******************************************************************************
 函数名称：    s16 getMotorCurFromObjId(u8 t_bObjId)
 			   s16 getPhaseCur_U(u8 t_bObjId)
 			   s16 getPhaseCur_V(u8 t_bObjId)
 			   s16 getPhaseRawCur_U(u8 t_bObjId)
 			   s16 getPhaseRawCur_V(u8 t_bObjId)
 			   
 功能描述：    读取电流封装函数
 输入参数：    u8 t_bObjId      控制对象ID
 输出参数：    无
 返 回 值：    无
 其它说明：    库函数调用
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/12/10      V1.0           Li Tonghua          创建
 *******************************************************************************/
s16 getMotorCurFromObjId(u8 t_bObjId)
{
	s16 t_nTmp;
	t_nTmp = Sqrt_Functions(gS_FocObjM[t_bObjId].m_pStatCurrAB->nAlph,gS_FocObjM[t_bObjId].m_pStatCurrAB->nBeta);
	return t_nTmp;
}

s16 getMotorCurFromObjId1ms(u8 t_bObjId)			// return Q15
{	
	s32 t_nTmp;
	t_nTmp	= (s32)gS_FocObjM[t_bObjId].m_pStatCurrAB->nAlph * gS_FocObjM[t_bObjId].m_pStatCurrAB->nAlph
				+ (s32)gS_FocObjM[t_bObjId].m_pStatCurrAB->nBeta * gS_FocObjM[t_bObjId].m_pStatCurrAB->nBeta;

	t_nTmp = IQ15SqrtIQ31(t_nTmp);

	t_nTmp = (t_nTmp * 23170) >> 14;			// 1.414

	if(t_nTmp > 32767)
	{
		t_nTmp = 32767;
	}
	
	return (s16)t_nTmp;
}

s16 getMotorActVoltFromObjId1ms(u8 t_bObjId)		// return Q15
{
	s32 t_nTmp;
	t_nTmp	= (s32)getMotorDaxisVoltFormObjId(t_bObjId) * getMotorDaxisVoltFormObjId(t_bObjId) 
					+ (s32)getMotorQaxisVoltFormObjId(t_bObjId) * getMotorQaxisVoltFormObjId(t_bObjId);

	t_nTmp = IQ15SqrtIQ31(t_nTmp);

	t_nTmp = (t_nTmp * 23170) >> 14;			// 1.414

	if(t_nTmp > 32767)
	{
		t_nTmp = 32767;
	}
	
	return (s16)t_nTmp;
}




s16 getPhaseCur_U(u8 t_bObjId)   //获取U相电流值
{
	return (s16)(gS_FocObjM[t_bObjId].m_pStatCurrUVW->nPhaseU);
}

s16 getPhaseCur_V(u8 t_bObjId)   //获取V相电流值
{
	return (s16)(gS_FocObjM[t_bObjId].m_pStatCurrUVW->nPhaseV);
}

s16 getPhaseCur_W(u8 t_bObjId)   //获取W相电流值
{
	return (s16)(gS_FocObjM[t_bObjId].m_pStatCurrUVW->nPhaseW);
}

s16 getiq_ref(u8 t_bObjId)   //获取U相电流值
{
	return (s16)(gS_FocObjM[t_bObjId].m_pStatCurrDQRef->nAxisQ);
}
 s16 getid_ref(u8 t_bObjId)   //获取U相电流值
{
	return (s16)(gS_FocObjM[t_bObjId].m_pStatCurrDQRef->nAxisD);
}


s16 getPWMstatus(u8 t_bObjId)   
{
	return (s16)gS_PhyObjInstanceM[t_bObjId].mGlobalDatPackage.mMdToMa.ePwmStatus;
}

s16 getUd(u8 t_bObjId)   //获取Ud
{
	return (s16)(gS_FocObjM[t_bObjId].m_pVolDQ->nAxisD);
}

s16 getUq(u8 t_bObjId)   //获取Uq
{
	return (s16)(gS_FocObjM[t_bObjId].m_pVolDQ->nAxisQ);
}

s16 getVdc(u8 t_bObjId)   //获取Vdc
{
	return (s16)(gS_PhyObjInstanceM[t_bObjId].mGlobalDatPackage.mMaToUa.wVdcDec);
}

s16 getid(u8 t_bObjId)   //获取id
{
	return (s16)(gS_FocObjM[t_bObjId].m_pStatCurrDQ->nAxisD);
}

s16 getiq(u8 t_bObjId)   //获取iq
{
	return (s16)(gS_FocObjM[t_bObjId].m_pStatCurrDQ->nAxisQ);
}

s16 getPhaseRawCur_U(u8 t_bObjId) //获取U相电流采样原始值
{
	return (s16)(gS_FocObjM[t_bObjId].pHdToMd->nSampCurDat0);
}

s16 getPhaseRawCur_V(u8 t_bObjId) //获取V相电流采样原始值
{
	return (s16)(gS_FocObjM[t_bObjId].pHdToMd->nSampCurDat1);
}
s16 getMotorStatus(u8 t_bObjId) 
{
  return (s16)(gS_FocObjM[t_bObjId].pMaToMd->eMotorStatus);
}
/*******************************************************************************
 函数名称：    s16 getEstSpeed(u8 t_bObjId)
 			         s16 getRefSpeed(u8 t_bObjId)
 功能描述：    读取转速封装函数
 输入参数：    u8 t_bObjId      控制对象ID
 输出参数：    无
 返 回 值：    无
 其它说明：    库函数调用
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/12/10      V1.0           Li Tonghua          创建
 *******************************************************************************/
s16 getEstSpeed(u8 t_bObjId)    //获取观测转速
{
	return (s16)(gS_FocObjM[t_bObjId].m_pMotorFocSpeed->wSpeedEst);
}

s16 getRefSpeed(u8 t_bObjId)    //获取给定转速
{
	return (s16)(gS_FocObjM[t_bObjId].m_pMotorFocSpeed->wSpeedRef);
}

u16 getFocObjStatus(u8 t_bObjId)
{
	return (s16)(gS_FocObjM[t_bObjId].eMotorStatusAck);
}
/******************** (C) COPYRIGHT 2019, Bright Power Semiconductor Co.ltd*******************/


