#ifndef _PUBDATA_MA_UA_H_
#define _PUBDATA_MA_UA_H_

#include "basic.h"

#define UA_FREQ_CMD_FORMAT						100			// 1Hz



//
/********************************************************************************************/
/* 
   bit07  |  bit06 | bit05 | bit04 | bit03 | bit02 | bit01 | bit00|
          |        |       |       |       |       |       |      |
--------------------------------------------------------------------------------------
 |   MOE  |   故障 |  故障 |  预留 |    运行模式   |  反向 |ON/OFF|
 |  有效  |   测试 |  清除 |                       |       |      |
    
                                                           |      |
                                                           |   1  |
-------------------------------------------------------------------------------------------------------------   
速度模式
     1        0        0   |    0   |   0       0       0       1        0x81 ------- RUN 速度模式
     1        0        0   |    0       0       0       1       1        0x83 ------- RUN,速度模式，命令值取反
-------------------------------------------------------------------------------------------------------------   

转矩模式
     1        0        0   |    0   |   0       1       0       1        0x85 ------- RUN 转矩模式
     1        0        0   |    0       0       1       1       1        0x87------- RUN 转矩模式，命令值取反
-------------------------------------------------------------------------------------------------------------   

功率模式
     1        0        0   |    0   |   1       0       0       1        0x89 ------- RUN 功率模式  速度命令值
     1        0        0   |    0       1       0       1       1        0x8B ------- RUN 功率模式  设定速度命令值取反
-------------------------------------------------------------------------------------------------------------   

位置模式
	 1        0        0   |    0   |   1       1       0       1        0x8D ------- RUN 位置模式  速度命令值
	 1        0        0   |    0       1       1       1       1        0x8F ------- RUN 位置模式  设定速度命令值取反
-------------------------------------------------------------------------------------------------------------   

停止方式
                                                            |  0  |
-------------------------------------------------------------------------------------------------------------   
     0        x        x   |    x       x       x       x       x        0x00 ------- 关闭MOE 停止
     
-------------------------------------------------------------------------------------------------------------   
     1        1        0   |    x       x       x       x       x        0xC0 ------- FAULT 停止

-------------------------------------------------------------------------------------------------------------   
     1        0        0   |    x       x       x       x       0        0x80 -------  停止


报警清除方式															 
--------------------------------------------------------------------------------------
     0        0        1   |    x       x       x       x       0        0xA0 -------  清除
     1        0        1   |    x       x       x       x       0        0xA0 -------  清除


********************************************************************************************/

typedef enum {	
	E_CMD_MOTOR_STOP_MOE_OFF	= 0x00,		// 关闭MOE, 其余命令可以不发送
	E_CMD_MOTOR_STOP			= 0x80,		// 停止电机
	
	E_CMD_MOTOR_SPEED_RUN		= 0x81,		// 运行电机, 速度模式，转动方向为设定方向
	E_CMD_MOTOR_SPEED_RUN_REV	= 0x83,		// 运行电机, 速度模式，转动方向与设定方向相反

	E_CMD_MOTOR_TORQUE_RUN		= 0x85,		// 运行电机, 转矩模式，转动方向为设定方向
	E_CMD_MOTOR_TORQUE_RUN_REV	= 0x87,		// 运行电机, 转矩模式，转动方向与设定方向相反

	E_CMD_MOTOR_POWER_RUN		= 0x89,		// 运行电机, 功率模式，转动方向为设定方向
	E_CMD_MOTOR_POWER_RUN_REV	= 0x8B,		// 运行电机, 功率模式，转动方向与设定方向相反

	E_CMD_MOTOR_POS_RUN			= 0x8D,		// 运行电机, 功率模式，转动方向为设定方向 		预留 ---- 暂不支持
	E_CMD_MOTOR_POS_RUN_REV		= 0x8F,		// 运行电机, 功率模式，转动方向与设定方向相反	预留 ---- 暂不支持
	
	E_CMD_MOTOR_FAULT_DIMOE		= 0x40,		// FAULT停止电机,MOE关闭
	E_CMD_MOTOR_FAULT_ENMOE		= 0xC0,		// FAULT停止电机,MOE使能
	E_CMD_MOTOR_FAULT_CLR_DIMOE	= 0x20,		// 报警清除 MOE关闭
	E_CMD_MOTOR_FAULT_CLR_ENMOE	= 0xA0,		// 报警清除 MOE使能
}ENUM_MotorCmdWord;


typedef enum {
	E_STOP_MOE_OFF = 0,			//关闭MOE停止
	E_STOP_ZERO_CUR,			//零电流停止
	E_STOP_SHORT,				//短接停止
	E_STOP_DONT_SUPPORT	
}ENUM_MotorBrakeMode;			//	电机停止方式


typedef struct {
	int16_t gWrFlag;
	ENUM_MotorCmdWord	eAppCmd;
	ENUM_MotorBrakeMode	eBrakeMode;
	int32_t		wFreqCmd;			// 负值为反向  0.01Hz
	int32_t		wPowerCmd;			// 	0.001W
	int32_t		wTorqCmd;           //	0.001A
	int16_t		nGearRatio;
	int16_t		nMotorId;
	int16_t		nInvId;				//RSVD

}STR_PubDatUAMA;


typedef union
{
    u16 Reg;
    struct
    	{        
		u16 locked			: 1;	// 应用标志					0x0001
		u16 Fault			: 1;	// 存在故障					0x0002
		u16 Running			: 1;	// 电机运行中		
		u16 PWMStatus		: 1;	// MA PWM使能状态		
		
		u16 waitCfg			: 1;	// 等待配置
		u16 CfgDone			: 1;	// 配置完成
		u16 POST			: 1;	// 上电完成

		u16 reserved	 	: 9;	// 预留		
		}Bit;
} UNION_Mot_Status_SR;


typedef struct {
	UNION_Mot_Status_SR		SR;
	ENUM_MotorCmdWord eMotorStsAck;

	int32_t			wVdcDec;			// 0.01V 
	int32_t			wCurDec;			// 0.001A
	int32_t			wVolDec;			// 0.01V 
	int32_t			wSpeedDec;			// 0.01Hz
	int16_t			nMotorTemp;			// 
	int16_t			nInvTemp;
	uint32_t		uFault;				//
}STR_PubDatMAUA, *pSTR_PubDatMAUA;		//PUB_DATA_UA2MA_STR;



// handle function from UA 2 MA : UA write function

static __inline void	SetAppCmdUA2MA(STR_PubDatUAMA*pUA2MA, ENUM_MotorCmdWord cmd)	//	UA设置PWM操作到MA
{
	pUA2MA->eAppCmd		= cmd;
}

static __inline void	SetAppBrakeModeUA2MA(STR_PubDatUAMA*pUA2MA, ENUM_MotorBrakeMode mode) //	UA设置停止模式到MA
{
	pUA2MA->eBrakeMode	= mode;
}


static __inline void	SetAppFreqCmdUA2MA(STR_PubDatUAMA *pUA2MA, int32_t wFreqCmd)	//	UA设置频率指令值到MA
{
	pUA2MA->wFreqCmd	= wFreqCmd;
}

static __inline void	SetAppPowerCmdUA2MA(STR_PubDatUAMA *pUA2MA, int32_t wPowerCmd)	//	UA设置功率指令值到MA
{
	pUA2MA->wPowerCmd	= wPowerCmd;
}

static __inline void	SetAppTorqCmdUA2MA(STR_PubDatUAMA *pUA2MA, int32_t wTorqCmd)	//	UA设置转矩指令值到MA
{
	pUA2MA->wTorqCmd	= wTorqCmd;
}

static __inline void	SetAppGearRatioUA2MA(STR_PubDatUAMA *pUA2MA, int16_t nGearRatio)	//	UA设置传动比到MA，预留
{
	pUA2MA->nGearRatio	= nGearRatio;
}

static __inline void	SetAppMotorIDUA2MA(STR_PubDatUAMA *pUA2MA, int16_t nMotorId)	//	UA设置电机ID值到MA,预留
{
	pUA2MA->nMotorId	= nMotorId;
}

static __inline void	SetAppInvIDUA2MA(STR_PubDatUAMA *pUA2MA, int16_t nInvId)		//	UA设置功率器件ID值到MA,预留
{
	pUA2MA->nInvId	= nInvId;
}


// handle function from MA 2 UA :  UA read function
static __inline ENUM_MotorCmdWord getMotorStatMD2MA(STR_PubDatMAUA*	pMA2UA)	//	UA读取MA电机状态
{
	return pMA2UA->eMotorStsAck;
}

static __inline int32_t getVdcDecMAUA(STR_PubDatMAUA*	pMA2UA)				//	UA读取MA母线电压值 0.01V
{
	return pMA2UA->wVdcDec;
}

static __inline int32_t getCurDecMAUA(STR_PubDatMAUA*	pMA2UA)				//	UA读取MA相电流有效值 0.001A
{
	return pMA2UA->wCurDec;
}

static __inline int32_t getSpeedDecMAUA(STR_PubDatMAUA*	pMA2UA)				//	UA读取MA速度值 0.01Hz
{
	return pMA2UA->wSpeedDec;
}

static __inline int16_t getMotorTempDecMAUA(STR_PubDatMAUA*	pMA2UA)			//	UA读取MA电机温度，预留
{
	return pMA2UA->nMotorTemp;
}

static __inline int16_t getInvTempDecMAUA(STR_PubDatMAUA*	pMA2UA)			//	UA读取MA功率器件温度 根据需要实现
{
	return pMA2UA->nInvTemp;
}

static __inline bool NoFaultCodeFromMA(STR_PubDatMAUA*	pMA2UA)				//	MA不存在报警 TRUE --- 不存在
{
	return (pMA2UA->uFault == 0);
}

static __inline bool HasFaultBitFromMA(STR_PubDatMAUA*	pMA2UA)				//	MA存在报警标志位 TRUE --- 存在
{
	return (pMA2UA->SR.Bit.Fault);
}


static __inline bool HasFaultFromMA(STR_PubDatMAUA*	pMA2UA)					//	MA存在报警 TRUE --- 存在
{
	return (pMA2UA->uFault) ||(pMA2UA->SR.Bit.Fault);
}

static __inline bool IfPostFinishFromMA(STR_PubDatMAUA*	pMA2UA)				//	MA POST结束 TRUE --- 完成
{
	return (pMA2UA->SR.Bit.POST);
}

static __inline bool IfWaitCfgFromMA(STR_PubDatMAUA*	pMA2UA)				//	MA 等待参数配置 TRUE --- 等待
{
	return (pMA2UA->SR.Bit.waitCfg);
}

static __inline bool IfCfgFinishFromMA(STR_PubDatMAUA*	pMA2UA)				//	MA 参数配置结束 TRUE --- 完成
{
	return (pMA2UA->SR.Bit.CfgDone);
}

static __inline bool IsRunningFromMA(STR_PubDatMAUA*	pMA2UA)				//	MA 电机是否运行 TRUE --- 运行
{
	return (pMA2UA->SR.Bit.Running);
}

static __inline bool IsStoppedFromMA(STR_PubDatMAUA*	pMA2UA)				//	MA 电机是否停止 TRUE --- 停止
{
	return (pMA2UA->SR.Bit.Running == 0);
}



// handle function from MA 2 UA :  MA write function
static __inline void setFaultStatMA2UA(STR_PubDatMAUA* pMA2UA, bool isFault )	//	MA设置报警到UA
{
	pMA2UA->SR.Bit.Fault = isFault;
}

static __inline void setRunningStatMA2UA(STR_PubDatMAUA* pMA2UA, bool isRunning )	//	MA设置运行标志到UA
{
	pMA2UA->SR.Bit.Running = isRunning;
}

static __inline void setPWMStatMA2UA(STR_PubDatMAUA* pMA2UA, bool isEnable )	//	MA设置PWM状态到UA
{
	pMA2UA->SR.Bit.PWMStatus = isEnable;
}



static __inline void setWaitCfgStatMA2UA(STR_PubDatMAUA* pMA2UA, bool isWaitPara)	//	MA设置等待参数配置到UA
{
	pMA2UA->SR.Bit.waitCfg = isWaitPara;
}

static __inline void setCfgFinishMA2UA(STR_PubDatMAUA* pMA2UA, bool isDone)			//	MA设置参数配置完成到UA
{
	pMA2UA->SR.Bit.CfgDone = isDone;
}

static __inline void setPostStatMA2UA(STR_PubDatMAUA* pMA2UA, bool isDone)			//	MA设置POST完成到UA
{
	pMA2UA->SR.Bit.POST = isDone;
}




#endif // _PUBDATA_MA_UA_H_
/////////////////////
