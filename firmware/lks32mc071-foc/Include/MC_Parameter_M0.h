/*******************************************************************************
 * 版权所有 (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： parameter.h
 * 文件标识：
 * 内容摘要： parameter config
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： Lizy, Howlet Li
 * 完成日期： 2022年5月18日
 *******************************************************************************/
 
/*------------------------------prevent recursive inclusion -------------------*/ 
#ifndef __PARAMETER0_H
#define __PARAMETER0_H

#include "basic.h"
#include "MC_Type.h"
#include "MC_GlobalDef_M0.h"


/* -----------------------------Hardware Parameter---------------------------- */
#define ADC_SUPPLY_VOLTAGE_M0             (3.6)              /* 单位: V  ADC基准电压，3.6或者2.4,大部分应用选择3.6 */
//双电阻采样范围:101.25A
//电阻40K欧 320/(5+20*2)=7.11111111111   当前40K欧姆

//单电阻采样范围:99.0A
//电阻1K欧 80/(10+1)=7.2727272            当前1K欧姆 //  17.5439 14.5454545

 //选择320：10k，外接的是两个20k 放大倍数320/50 = 6.4
#define AMPLIFICATION_GAIN_M0			(6.4)             /*运放放大倍数*/  // 3.6/(6.4 * 0.03)= 18.75
#define RSHUNT_M0						(0.03)                /* 单位: Ω  采样电阻阻值 */
#if 1
#define VOLTAGE_SHUNT_RATIO_M0			(1.0/(20.0 * 2 + 1.0)) /* 母线电压分压比 */
#define BEMF_SHUNT_RATIO_M0				(1.0/(20.0 * 2 + 1.0)) /* 反电势电压分压比 */
#else

#define VOLTAGE_SHUNT_RATIO_M0			(1.0/(14.3 + 1.0)) /* 母线电压分压比 */
#define BEMF_SHUNT_RATIO_M0				(1.0/(14.3 + 1.0)) /* 反电势电压分压比 */


#endif

/* ------------------------------Rated Parameter------------------------------ */
#define U_MAX_FREQ_M0						(600.0)				/* 单位:Hz,  电机最高运行电频率 */

/* ------------------------------Motor Parameter------------------------------ */
#if 0
#define U_MOTOR_PP_M0						(7.0)			/* 电机极对数 */
#define U_MOTOR_RS_M0						(1.537)		/* 单位: Ω 电机相电阻 */
#define U_MOTOR_LD_M0						(2269.0)		/* 单位: uH 电机d轴电感 (343.893)*/
#define U_MOTOR_LQ_M0						(2500.0)		/* 单位: uH 电机q轴电感 (234.4485)*/

/* 电机磁链常数 计算公式：Vpp/2/sqrt(3)/(2*PI)/f，其中Vpp为电压峰峰值，f为电频率 
   此参数仅影响顺逆风启动的速度检测，角度估算不使用些参数 */
#define U_MOTOR_FLUX_CONST_M0				(0.0687364598)  
#else

#define U_MOTOR_PP_M0                     (5.0)             /* 电机极对数 */
#define U_MOTOR_RS_M0                     (0.444273)             /* 单位: Ω 电机相电阻 */
#define U_MOTOR_LD_M0                     (234.4485)//(8000.0)          /* 单位: uH 电机d轴电感 */
#define U_MOTOR_LQ_M0                     (343.893)//(10000.0)         /* 单位: uH 电机q轴电感 */

/* 电机磁链常数 计算公式：Vpp/2/sqrt(3)/(2*PI)/f，其中Vpp为电压峰峰值，f为电频率 
   此参数仅影响顺逆风启动的速度检测，角度估算不使用些参数 */
#define U_MOTOR_FLUX_CONST_M0             (0.017)   


#endif



/* ----------------------IPD 转子初始位置检测 脉冲注入时间设置---------------- */
#define U_START_ANGLE_COMP_M0				(0)				/* 单位:度 初始位置检测补偿角度 */

#define IPD_PLUS_TIME_SETTING_M0			(30)			/* 脉冲注入时间宽度设置 单位us */
#define IPD_WAIT_TIME_SETTING_M0			(35)			/* 脉冲空闲等待时间宽度设置 单位us 最短一个PWM周期*/

#define IPD_PLUS_TIME_WIDTH_M0            (u32)(IPD_PLUS_TIME_SETTING_M0*(MCU_MCLK_M0))   /* 脉冲注入时间宽度设置 单位clk */
#define IPD_PLUS_WAIT_TIME_M0             (u32)(IPD_WAIT_TIME_SETTING_M0*(MCU_MCLK_M0))   /* 脉冲空闲等待时间宽度设置 单位clk */


/* -------------------------------- 顺逆风检测参数------------------------------ */
#define SPEED_TRACK_DELAYTIME_M0			(500)			/* 单位: ms 顺逆风检测时间  */
#define SPEED_TRACK_ON_FREQ_THH_M0			(15.0)			/* 单位: Hz 顺风切闭环频率 */
#define EBRK_ON_FREQ_THH_M0					(15.0)			/* 单位: Hz 逆风刹车频率 */

#define MOTOR_STOP_CUR_THD_M0				(0.3)			/* 单位: A  电机停止检测电流阈值   */
#define MOTOR_STOP_CUR_DIF_THD_M0			(0.3)			/* 单位: A  电机停止检测电流差阈值 */

#define STOP_TIME_M0						(200)			/* 单位：ms 电机停止检测滤波时间，根据实际负载修改 */
#define STOP_DELAY_TIME_M0					(200)			/* 单位: ms 电机停止后延迟时间，根据实际负载修改。修改依据：电机在判定为停止后还在转动就加大延迟时间 */


#define BEMF_ANG_COMP_M0					(0)				/* 单位：度 反电势检测角度补偿，根据实际负载修改 */
#define BEMF_TRACK_MIN_VOLT_M0				(200)			/* 单位: 0.01V 反电势检测最小电压，根据实际负载修改。修改依据：电机在判定为停止后还在转动就加大延迟时间 */


/*------------------------------------预定位参数---------------------------------*/
#define ALIGN_ANGLE_M0						(0.0)			/* 单位:度 预定位角度 */
#define U_START_CUR_SET_F_M0				(1.2)			/* 单位: A 第一段定位电流 */
#define U_START_CUR_SET_S_M0				(1.4)			/* 单位: A 第二段定位电流 */
#define DC_HOLDTIME_TIME_LENTH_M0			(100)			/* 单位: ms 第一段定位时间 */
#define DC_HOLDTIME_TIME_LENTH_STAGE1_M0	(100)			/* 单位: ms 第二段定位时间 */
#define DC_ALIGN_TOTAL_LENTH_M0            \
       (DC_HOLDTIME_TIME_LENTH_M0 + DC_HOLDTIME_TIME_LENTH_STAGE1_M0)/* 定位总时长 */

#define ALIGN_CURRENT_ACC_M0				(10)			/* 单位: A/s  定位电流加速调整值  初始位置检测使能后给到最大值，不能超过30，否则数据会溢出。 */
#define ALIGN_CURRENT_DEC_M0				(10)			/* 单位: A/s  定位电流减速调整值  初始位置检测使能后给到最大值，不能超过30，否则数据会溢出。 */


/*------------------------------------VF启动参数---------------------------------*/
								/* 当前未用，预留 */
#define VF_START_VALUE_M0					(1)				/* VF启动电压值 VF_START_VALUE/VF_VOLT_ACC = 800/50 = 16 DC_ALIGN_TOTAL_LENTH */   
#define VF_OPEN2CLOSE_TIME_M0				(1)				/* VF启动开环延时时间 */   //20
#define VF_VOLT_ACC_M0						(1)				/* VF电压加速调整值*/
#define VF_VOLT_DEC_M0						(1)				/* VF电压减速调整值*/

/*---------------------------------开环参数------------------------------------*/
#define OPEN_ANGLE_TAG_FREQ_M0				(30.0)			/* 单位：Hz 开环拖动最终频率 */
#define FREQ_ACC_M0							(20.0)			/* 单位：Hz/s 开环拖动频率加速调整值 */
#define FREQ_DEC_M0							(20.0)			/* 单位：Hz/s 开环拖动频率减速调整值 */
  
#define MATCH_TIME_M0						(5)				/* 估算和给定电流匹配次数, 当前未用，预留 */

#define MIN_RUN_FREQ_M0						(30.0)			/* 单位：Hz 最低速度 */
#define CLOSE2OPEN_FREQ_M0					(2.0)			/* 单位：Hz 切换为开环拖动频率 */
#define CURRENTLOOP_CLOSE_FREQ_M0			(20.0)			/* 单位：Hz 电流环闭环频率 */

/*---------------------- -----开环闭环切换过渡参数------------------------------*/
#define OPEN2CLOSE_RUN_COV_TIME_M0 			(300)			/* 开环闭环切换过渡时间：单位：mS 30*/
#define OPEN2CLOSE_RUN_CURRENT_RAMP_M0		(0.05)			/* 开环闭环切换过渡内，D,Q轴电流变化斜率。单位：A/ms */
															/* 当前未用，预留 */

#define ID_START_M0							(1.0)			/* 单位:A, D轴电流设定值 */
#define IQ_START_M0							(1.0)			/* 单位:A, Q轴电流设定值 */

#define U_UNDVOLT_PROT_ENABLE_M0			(0)
#define U_UNDVOLT_START_M0					(16)			/* 单位：V 欠压恢复设定值 */     /* AC175 */
#define U_UNDVOLT_STOP_M0					(20)			/* 单位：V 欠压恢复设定值 */     /* AC175 */
#define U_UNDVOLT_RECOVER_M0				(22)			/* 单位：V 欠压恢复设定值 */     /* AC160 */
#define IQ_BRAKE_SET_M0						(1.5)			/* 单位：A IqRef，Iq制动给定值 */



/* ------------------------------观测器PLL PI参数----------------------------- */
#define PLL_KP_GAIN_M0						(16 * 32)		/* PLL_Kp 估算器Kp 50 16  扩大32倍*/
#define PLL_KI_GAIN_M0						(8 * 256)		/* PLL_Ki 估算器Ki 10  4  扩大256倍*/
#define PLL_K_FREQ0_M0						(50.0)			/* 单位: PLL_K 估算器频率0 */

#define PLL_KP_RUN_M0						(20 * 32)		/* 单位: PLL_Kp 估算器Kp1 */
#define PLL_KI_RUN_M0						(8 * 256)		/* 单位: PLL_Ki 估算器Ki1 */
#define PLL_K_FREQ1_M0						(70.0)			/* 单位: PLL_K 估算器频率1 */


#define THETA_FIL_TIME_M0					(2.0)			/* 单位:ms, 滤波时间 */
#define SPEED_FIL_TIME_M0					(6.0)			/* 单位:ms, 滤波时间 */


#define SLVC_MIN_VOLTAGE_M0					(300)				// 0.01V
#define SLVC_MIN_VOLTAGE_SPD_M0				(MIN_RUN_FREQ_M0)			//	10.00Hz


/*----------------------------------电流环参数---------------------------------*/
#define IQ_SET_M0							(1.0)			/* 单位：A IqRef，Iq给定值 */
 
#define VQMAX_M0							(0.8)			/* Q轴最大输出限制*/
#define VQMIN_M0							(-0.8)			/* Q轴最小输出限制*/

#define VDMAX_M0							(0.8)			/* D轴最大输出限制*/
#define VDMIN_M0							(-0.8)			/* D轴最小输出限制*/

#define P_CURRENT_KP_M0						(0)			/* 电流环Kp，实际运用的Kp会根据这个值和电机参数计算出最终的Kp */
															/* 0 --- 自动计算参数    非0 --- 设定值*/
#define P_CURRENT_KI_M0						(1500)			/* 电流环Ki，实际运用的Kp会根据这个值和电机参数计算出最终的Ki */

#define P_CUURENT_KP_RUN_M0					(1500)			/* 运行时的电流环Kp*/ /* 当前未用，可用于动态调整PI参数 */
#define P_CUURENT_KI_RUN_M0					(780)			/* 运行时的电流环Ki*/ /* 当前未用，可用于动态调整PI参数 */

#define AUTO_FW_LIM_M0						(0.00)			/* 自动弱磁D轴电流限制 A*/

#define D_CURRENT_REF_FIL_TIME_M0			(2.0)			/* 单位：ms D轴电流指令滤波时间常数 */
#define Q_CURRENT_REF_FIL_TIME_M0			(2.0)			/* 单位：ms Q轴电流指令滤波时间常数 */


/*----------------------------------速度环参数-------------------------------*/
#define POWER_LIMIT_VALUE_M0				(10.0)			/* 单位：W   限制功率的大小 */
#define POWER_LIMIT_TIME_M0					(5)				/* 单位：速度环周期，  限功率计算周期 */
#define POWER_LIMIT_SPEED_M0				(150)			/* 单位：Hz  限功率转速给定，根据实际应用来设置， */

#define SPEED_LOOP_CNTR_M0					(0)				/* 单位：ms  速度环路计算周期 */

#define STATE04_WAITE_TIME_M0				(100)			/* Unit: ms 速度变量初始化时间100--10 */ /* 当前未用，预留 */ 

#define P_ASR_KP_M0							(6000)			/* 速度环Kp */
#define P_ASR_KI_M0							(4000)			/* 速度环Ki */

#define IQMAX_M0							(1.0)			/* 单位:A, 速度环输出最大值 */
#define IQMIN_M0							(-1.0)			/* 单位:A, 速度环输出最小值 */

#define SPEED_RUN_ACC_M0					(50.00)			/* 单位 Hz/s 速度加速调整值 */
#define SPEED_RUN_DEC_M0					(50.00)			/* 单位 Hz/s 速度减速调整值 */

/*------------------------------------功率环参数-------------------------------*/
#define SPEED_LIMIT_VALUE_M0				(150.0)            /* 单位：Hz  限制转速的大小 */
#define SPEED_LIMIT_TIME_M0					(5)                /* 单位：ms  功率环周期， 限转速计算周期 */
#define POWER_LOOP_CNTR_M0					(1)                /* 单位：ms  功率环路计算周期 */

#define SPEED_LIMIT_POWER_VALUE_M0			(15.00)               /* 单位：W   限转速功率给定 */
#define POWER_SET_M0						(10.00)               /* 单位：W  功率给定值 */

                                                                  
#define POWER_KP_M0							(1000)             /* 功率环Kp */
#define POWER_KI_M0							(500)              /* 功率环Ki */

#define POWER_IQMAX_M0						(2.0)              /* 单位:A, 功率环输出最大值 */
#define POWER_IQMIN_M0						(-2.0)             /* 单位:A, 功率环输出最小值 */
                                                                   
#define POWER_RUN_ACC_M0					(0.01)              /* 单位 w 功率加速调整值 注意POWER_RUN_ACC和POWER_RUN_DEC不能太小，结合拟合参数设置，实际程序中的加减速值不能能小于0. */
#define POWER_RUN_DEC_M0					(0.01)              /* 单位 w 功率减速调整值 */

#define POWER_FAC_A0_M0						(0.0)				/* 功率校正系数 */
#define POWER_FAC_A1_M0						(1.0)				/* 功率校正系数 */
#define POWER_FAC_A2_M0						(0.0)				/* 功率校正系数 */

/*------------------------------------FaultDetection---------------------------*/
/* 过流检测参数 */
#define I_PH_HARD_OC_FAULT_CMP_VOLT_M0		(30)               /* 单位：mV 硬件过流保护比较电压值 */
#define I_PH_OVERCURRENT_FAULT_M0			(6)				/* 单位：A 软件过流检测设定值 */
#define I_PH_OVERCURRENT_FAULT_TIMES_M0		(5)					/* 单位：软件过流检测次数 */

#define CURRENT_FAULT_RECOVER_TIME_M0		(1000)				/* 单位：ms  过流恢复时间 */

///* 过欠压检测参数 */
#define U_OVERVOLTAGE_FAULT_M0				(30)				/* 单位：V 过压检测设定值 */
#define U_OVERVOLTAGE_RECOVER_M0			(26)				/* 单位：V 过压恢复设定值 */
#define U_UNDERVOLTAGE_FAULT_M0				(12)				/* 单位：V 欠压检测设定值 */
#define U_UNDERVOLTAGE_RECOVER_M0			(22)				/* 单位：V 欠压恢复设定值 */

#define U_OVER_VOLT_DETECT_TIME_M0 			(1000)				/* 过压报警检测时间 1ms*/
#define U_UNDE_VOLT_DETECT_TIME_M0 			(1000)				/* 低压报警检测时间 1ms*/
#define VOLT_FAULT_RECOVER_TIME_M0 			(1000)				/* 过欠压恢复时间 1ms*/

#define U_OV_VOLT_PROTECT_ENABLE_M0 		(1)					/* 过压报警保护使能 */
#define U_UND_VOLT_PROTECT_ENABLE_M0 		(1)					/* 低压报警保护使能 */


///* 离水空转参数 */
#define I_PH_EMPTY_FAULT_M0					(0.3)				/* 单位：A 空转检测电流设定值 */
#define SPEED_EMPTY_FAULT_M0				(50.0)				/* 单位：Hz 空转检测转速设定值  */

#define EMPTY_FAULT_DETECT_TIME_M0       	(2000)				/* 单位：ms  离水空转检测时间 */
#define EMPTY_FAULT_RECOVER_TIME_M0			(2000)				/* 单位：ms  离水空转恢复时间 */
#define EMPTY_PROTECTION_ENABLE_M0			(0)					/* 离水空转保护使能 */



///* 温度检测参数 */
#define TEMP_BASED_M0						(25.0)				/* 单位：° 基准温度 */
#define TEMP_BASED_VOLT_M0					(2.0)				/* 单位：V  基准电压 */
#define TEMP_B_FACTOR_M0					(25.0)				/* 基准温度 */

#define TEMP_MAX_ALLOWED_M0					(100.0)				/* 最高工作温度 */
#define TEMP_MIN_ALLOWED_M0					(10.0)				/* 最低工作温度 */
#define PH_CUR_ALLOWED_MAXTEMP_M0			(1.5)				/* 最高工作温度允许电流 */
#define TEMP_HYP_ALLOWED_M0					(10.0)				/* 滞回温度 */

#define TEMP_PROTECT_ENABLE_M0				(1)					/* 温度保护使能 */

#define TEMP_FAULT_DETECT_TIME_M0			(1000)				/* 单位：1ms  过温检测时间 */
#define TEMP_FAULT_RECOVER_TIME_M0			(2000)              /* 单位：ms  过温恢复时间 */
//                                                                  
///* 堵转检测参数 */
#define SPEED_STALL_DELAY_TIME_M0			(500.0)				/* 单位：1ms 堵转检测延迟时间 */

#define CUR_STALL_MAX_FAULT_M0				(1.8)				/* 单位：A  堵转检测电流偏差最大值 */
#define CUR_STALL_MIN_FAULT_M0				(1.2)				/* 单位：Hz 堵转检测退出电流最小值 */

#define I_PH_STALL_FAULT_M0					(1.5)				/* 单位：A 堵转检测电流设定值 */
#define SPEED_FAC_STALL_FAULT_M0			(4.0)				/* 单位：倍 堵转检测转速偏差倍数 */

#define IQ_STALL_FAULT_M0					(0.2)				/* 单位：A 堵转检测电流设定值 */ /*未用，预留*/

#define STALL_FAULT_DETECT_TIME_M0       	(2000)				/* 单位：1ms  堵转检测时间 */
#define STALL_FAULT_RECOVER_TIME_M0			(2000)				/* 单位：1ms  堵转恢复时间 */

#define STALL_PROTECTION_ENABLE_M0			(0)					/* 堵转保护使能 */


//  启动异常检测

#define START_DETECT_CLOSED_TIME_M0			(3000)				/* 单位：1ms  闭环异常检测时间 */

#define START_DETECT_PERIOD_M0				(2000)				/* 单位：1ms  启动异常检测时间 */
#define START_FAULT_RECOVER_TIME_M0			(1000)				/* 单位：ms  二次启动恢复时间 */
#define START_PROTECTION_ENABLE_M0			(0)					/* 启动异常保护使能 */



///* 缺相检测参数 */
#define I_PHASE_LOSS_FAULT_M0             	(0.1)				/* 单位：A  缺相检测电流设定值 */
#define LOSS_PH_FAULT_DETECT_TIME_M0		(400)				/* 单位：ms 缺相检测周期设定值 */
#define LOSS_PH_FAULT_RECOVER_TIME_M0		(2000)				/* 单位：ms  缺相恢复时间 */
#define LOSS_PH_PROTECTION_ENABLE_M0		(0)					/* 缺相异常保护使能 */

#endif  /* __PARAMETER0_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* -----------------------------------END OF FILE------------------------------- */

