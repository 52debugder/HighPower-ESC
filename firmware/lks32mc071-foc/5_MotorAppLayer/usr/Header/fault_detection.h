/*******************************************************************************
 * 版权所有 (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： fault_detection.h
 * 文件标识：
 * 内容摘要： fault detectiong: volt ,current, temperature, stall, empty, phaseloss,\
 *
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： andrew kong
 * 完成日期： 2019年11月28日
 * 修改历史:
 *              2022-11-22 添加报警参数配置功能，修改部分报警代码，Li Tonghua
 *******************************************************************************/
#ifndef __FAULT_DETECTION_H
#define __FAULT_DETECTION_H

#include "basic.h"
#include "mc_type.h"
#include "state_machine.h"

#define FAULT_DETECT_CYCLE		(5)
typedef struct
{
    s16 nCheckCnt1;
    s16 nCheckCnt2;
    s16 nRecoverCntr;
    s16 nStartDelay;
    s16 nRecoverTime;
} STR_FaultTime;

typedef struct
{
    s16 nOverCurrent;            //软件过流值
    s16 nOverVoltage;            //过压值
    s16 nUnderVoltage;           //欠压值
    s16 nOverVoltageRecover;     //过压恢复值
    s16 nUnderVoltageRecover;    //欠压恢复值
    s16 nEmptyCurrent;           //离水空转电流值
    s32 wEmptySpeed;             //离水空转转速值
	s16 nStallCurrent;           //堵转检测电流
	s32 wStallCurMax;			 //堵转检测高电流
	s32 wStallCurMin;			 //堵转检测低电流
	s32 wStallSpeedfactor;       //堵转检测速度系数
	s16 nStallCurFlag;           //堵转故障标志
	s16 nStallFlag;              //堵转故障标志
    s16 nStartFlag;              //启动故障标志
    s16 nPhaseLossCurrent;       //缺相电流设定值
    s16 nPhaseLossFlag;          //缺相标志位，区分不同的缺相方式
} STR_FaultVariable;

typedef union
{
    u16 R;
    struct
    {
        u16 SoftCurretError : 1;//软件过流标志  0x0001 
        u16 HardCurretError : 1;//硬件过流标志  0x0002 
        u16 VoltOverError   : 1;//过压故障标志  0x0004
        u16 VoltUnderError  : 1;//欠压故障标志  0x0008 
        u16 StallError      : 1;//堵转故障标志  0x0010 
        u16 EmptyError      : 1;//空转故障标志  0x0020 
        u16 PhaseLossError  : 1;//缺相故障标志  0x0040 
        u16 TempOverError   : 1;//温度故障标志  0x0080
        u16 OffsetError     : 1;//偏置故障标志  0x0100
        u16 StartError      : 1;//启动故障标志  0x0200
        u16                 : 6;//预留
    } B;
} STR_FaultStatus;

typedef enum
{
    E_FAULT_PRIO_HIGH = 0,				// 故障优先
	E_FAULT_PRIO_BELOW_UA = 1,			// UA设定优先
	E_FAULT_PRIO_LOW = 2				// 最低级别
	
} ENU_FaultPrio;


typedef struct
{
    u8  bFlag;					//缺相检测标志位
    u16 nTheta;					//电流幅值检测计数
    u32 wPhATemp;               //A相电流幅值中间值
    u32 wPhBTemp;				//B相电流幅值中间值
    u32 wPhCTemp;				//C相电流幅值中间值
    u16 nPhA;					//A相电流幅值
    u16 nPhB;   				//B相电流幅值
    u16 nPhC;					//C相电流幅值
}STR_CurrentAmplitude;
                
extern volatile STR_FaultStatus stru_Faults;
extern STR_FaultVariable        stru_FaultValue;
extern STR_CurrentAmplitude     struCurrentAmplitude;
extern STR_VectorUVW			struImaxCurrent;

extern STR_FaultTime struFaultEmptyTime;
extern STR_FaultTime struFaultStallTime;
extern STR_FaultTime struFaultCurrentTime;
extern STR_FaultTime struFaultTempTime;
extern STR_FaultTime struFaultPhaseTime;

#endif

