/*******************************************************************************
 * 版权所有 (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： state_machine.h
 * 内容摘要： state machine
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： Tonghua Li
 * 完成日期： 2022年8月19日
 *
 *******************************************************************************/
#ifndef __STATE_MACHINE_H
#define __STATE_MACHINE_H

#include "basic.h"
#include "mc_type.h"

typedef enum 
{
	MOTOR_INFO_TRACKING,				//	顺逆风检测中
	MOTOR_INFO_TRACKING_RESULT,			//	等待顺逆风检测结果
	MOTOR_INFO_TRACKING_BRAKE,			//	顺逆风检测后制动
	MOTOR_INFO_TRACKING_RUN,			//	顺逆风检测后运行
	MOTOR_INFO_IPD,						//	初始位置IPD检测
	MOTOR_INFO_IPD_RESULT,				//	初始位置IPD检测结果
	MOTOR_INFO_ILLEGE					//	非法状态
}ENU_MOTOR_INFO_STATE;				// 电机信息检测状态

typedef enum 
{
	TRACKING,							//	检测中
	TRACKING_2_RUN,						//	检测后可以运行
	TRACKING_2_BRAKE,					//	检测后需要制动
	TRACKING_ILLEGE						//	无效结果
}ENU_TRAKING_RESULT;				//	顺逆风检测结果


typedef enum						//  电机驱动MA状态
{
	E_DRIVER_INIT			= 0,		//	初始状态
	E_DRIVER_POWER_ON_WAIT	= 1,		//	上电等待状态
	E_DRIVER_POWER_OFF		= 2,		//	掉电状态
	E_DRIVER_CALIB			= 3,		//	检测电路校正状态
	E_DRIVER_STOP			= 4,		//	STOP状态
	E_DRIVER_CHARGE			= 5,		//	预充电状态
	E_DRIVER_MOTOR_INFO		= 6,		//	电机信息检测状态(顺逆风和IPD检测)
	E_DRIVER_READY_RUN		= 7,		//	对相ALLIGN状态
	E_DRIVER_RUN			= 8,		//	运行状态
	E_DRIVER_READY_STOP		= 9,		//	准备停止状态
	E_DRIVER_FAULT			= 10		//	FAULT报警状态
}ENU_DRIVER_STATUS;

#endif

///* ********************** (C) COPYRIGHT LINKO SEMICONDUCTOR ******************** */
///* ------------------------------END OF FILE------------------------------------ */


