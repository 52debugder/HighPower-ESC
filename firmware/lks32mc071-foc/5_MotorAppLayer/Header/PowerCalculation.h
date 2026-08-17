/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： PowerCalculation.h
 * 文件标识：
 * 内容摘要： 功率处理
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： andrew kong
 * 完成日期： 2020年10月9日
 *
 *******************************************************************************/
#ifndef __POWER_H
#define __POWER_H

#include "basic.h"
#include "mc_type.h"
#include "PID_regulators.h"


#define POWER_LOWPASS_SCALE   (5)     //功率计算滤波系数
#define POWER_SHIFT           (7)     //功率计算移位系数，根据实际计算数值来修改此参数，如果数值小则适当减小此参数，否则适当加大

//***********************曲线拟合参数*******************//
#define POWER_SLOPE                     (100)  	//曲线斜率  //(694.1)  //曲线斜率
#define POWER_DIFF                      (0) 	//曲线差值  //(1140.6) //曲线差值
#define POWER_CALC(val)                 (POWER_SLOPE * val - POWER_DIFF)


typedef struct                        //低通
{
    s32 wInput;                       //输入量
    s32 wOutput;                      //输出量
    s16 nK1;                          //系数
    s64 lTemp;                        //中间值
} stru_LowPass_t;

typedef struct
{
    s32 wRef;                        //给定值
    s32 wSet;                        //设定值
    s16 nACCStep;                    //加速值
    s16 nDECStep;                    //减速值
} stru_Ramp_t;


typedef struct                      
{
    s32 wPowerValue;                  //功率实际值
    
    stru_Ramp_t  struPowerRamp;       //功率斜坡结构体
    
    stru_PIRegulator struPowerPI;     //功率环PI结构体
    
    s16 nSpeedLimitCntr;              //限转速周期计数
    s16 nSpeedLimitPeriod;            //限转速周期
    s32 wSpeedLimitValue;             //功率运行时转速限制值    
    s32 wSpeedLimitPowerRef;          //限转速功率给定值		//0.01W
    
	s32 wSpeedLimitPowerChangeSet;		//限转速功率调整变化值	//0.01W
    
    s32 wPowerRef;                    //功率ramp给定值			//0.01W
    s32 wPowerSet;                    //功率指令设定值			//0.01W
    s16 nQCurrentSet;                 //功率环输出电流iq
} STR_PowerDef,*pSTR_PowerDef;


extern s32 RampControl(stru_Ramp_t *pstruRamp);

#endif
