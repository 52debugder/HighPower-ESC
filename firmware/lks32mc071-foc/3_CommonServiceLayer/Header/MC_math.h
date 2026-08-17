/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： MC_math.h
 * 文件标识：
 * 内容摘要： 电机控制相关数学计算函数
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet Li
 * 完成日期： 2020年8月16日
 *
 * 修改记录1：
 * 修改日期：2020年8月16日
 * 版 本 号：V 1.0
 * 修 改 人：Howlet Li
 * 修改内容：创建
 *
 *******************************************************************************/
 /*------------------------------prevent recursive inclusion -------------------*/
#ifndef __MC_MATCH_H
#define __MC_MATCH_H

#include "basic.h"
#include "PubData_MA_UA.h" 
#include "PubData_MD_MA.h" 
#include "PubData_DriverInstance.h"


#define DivSQRT_3               (s16)0x49E6     /* 1/sqrt(3) in q1.15 format=0.5773315*/
#define SIN_MASK                0x0300
#define U0_90                   0x0200
#define U90_180                 0x0300
#define U180_270                0x0000
#define U270_360                0x0100

typedef struct
{
    s32 wRampIn;
    s32 wRampTmp;
    s32 wRampIncrease;
	s32 wRampDecrease;
    s32 wRampOut;
} STR_RampGen32, *PSTR_RampGen32;



s16 wGet_Atan(s32 x, s32 y);
extern s32 User2AppCurTrans(STR_TransCoefElement* pUser2AppCur,float val);
extern s32 User2AppFreqTrans(STR_TransCoefElement* pUser2App,float val);
extern s32 User2AppVolTrans(PSTR_TransCoefElement pUser2AppVolt,float val);

extern s32 App2CoreCurTrans(STR_TransCoefElement* pApp2CoreCur,s32 val);
extern s32 App2CoreFreqTrans(STR_TransCoefElement* pApp2CoreFreq,s32 val);
extern s32 App2CoreVoltTrans(PSTR_TransCoefElement pApp2CoreVolt,s32 val);

extern s32 Core2AppCurTrans(STR_TransCoefElement* pCore2AppCur,s32 val);
extern s32 Core2AppFreqTrans(STR_TransCoefElement* pCore2AppFreq,s32 val);
extern s32 Core2AppVolTrans(STR_TransCoefElement* pCore2AppVol,s32 val);
extern s32 Core2AppPowerTrans(PSTR_TransCoefElement pCore2AppPower,s16 val);


extern s16 App2UsrFreqTrans(PSTR_TransCoefElement pUsr2AppFreq,s32 val);


extern void Trig_Functions(s16 hAngle,STR_TrigComponents *t_pTrigComponents);


#define macro_Sqrt_function(x,y)	((s16)(__sqrtf(((s32)(x)) * (x) + ((s32)(y))  * (y) )))

extern void ramp32GenInit(PSTR_RampGen32 this);
extern void ramp32GenCalc(PSTR_RampGen32 this);

#endif
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */
