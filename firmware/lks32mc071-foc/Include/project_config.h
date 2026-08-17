/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： project_config.h
 * 文件标识：
 * 内容摘要： 工程相关文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Tonghua Li
 * 完成日期： 2022年12月20日
 *
 * 修改记录1：
 * 修改日期： 2022年12月20日
 * 版 本 号： V 1.0
 * 修 改 人： Tonghua Li
 * 修改内容： 创建
 *
 *******************************************************************************/

#ifndef __PROJECT_CONFIG_H_
#define __PROJECT_CONFIG_H_

#include "project_mcu.h"
#include "MC_Type.h"
#include "MC_configure_FB_data.h"
#include "MC_Parameter_M0.h"


/*********************************************************************************
*
* 平台硬件信息定义，部分内容在hardware_config.h中详细定义
*
*		MCU时钟
*		PWM个数及ID定义
*
* 其他配置文件应用这些共同的信息
**********************************************************************************/
#define MCU_MCLK_192M                   (192LL) 
#define MCU_MCLK_96M                    (96LL) 
#define MCU_MCLK_48M                    (48LL) 

/*-------------------------------------------------------------------------------*/
#define PLANTFORM_EPWM0					(0)			// 固定为EPWM0
#define PLANTFORM_EPWM1					(1)			// 固定为EPWM1

/*********************************************************************************/


/*********************************************************************************
* 用户配置信息区
*	根据选择的MCU信号及硬件电路拓扑图进行设置
**********************************************************************************/
// 支持的PWM通道数据，即可支持驱动单元数目
// 目前MCU最多支持双PWM，即最大为2
// 可以根据MCU chipNumber 自动进行宏定义
// 45x/07xx 	--- 2组PWM，
// 08x/03x/05x	--- 1组PWM

#define PLANTFORM_MAX_PWM_MODULE_NUM	(2)			// 07xMCU 2组PWM

/*********************************************************************************
* 平台支持的电流采样方式
* 当前45xEVM板不支持三电阻采样: 	
*				EPWM0对应的AD支持 单电阻/双电阻
*				EPWM1对应的AD支持 单电阻
* 08xEVM板:
*				EPWM0对应的AD支持 单电阻/双电阻/三电阻
*
* 03xEVM板:
*				EPWM0对应的AD支持 单电阻/双电阻
*
*
* 更改时需要校验硬件配置是否支持，进行相应硬件配置
* 目前   EPWM0对应的AD支持 单电阻/双电阻
*        EPWM1对应的AD支持 单电阻
**********************************************************************************/
#define EPWM0_CURRENT_SAMPLE_TYPE		(CURRENT_SAMPLE_2SHUNT)		// 单电机平台电流采样方式配置

/*********************************************************************************/
	
#define MCU_MCLK_USED                   (MCU_MCLK_96M)				// 当前MCU主频，根据MCU修改



/*********************************************************************************
*
* Drive Unit驱动单元模块(DU) 个数配置
*
*		驱动单元模块个数配置    ------  支持驱动单元DU个数，实际的电机数目可大于驱动单元
*		电机参数组				------  参数配置组个数，即电机个数
*										可大于驱动单元模块个数
*										实现多电机配置
*										参数组在 PubData_DriverInstance.c 中定义实例
*
*				默认驱动单元0   ----- 参数组0  的对应关系
*				参数组个数 需大于等于驱动单元个数
*				当参数组个数大于驱动单元个数时，由用户添加代码进行参数重新绑定到驱动单元
*
**********************************************************************************/
#define PLANTFORM_DRV_MODULE_NUM		(1)					// 驱动单元数目，单电机固定为1，不需要修改
#define PLANTFORM_MAX_CFG_PARA_ID		(1)					// 参数组数目，可修改为多组参数后自行调用函数维护
															// 初始化配置

//配置的电机模块数目需要小于最大的PWM模块个数
#if (PLANTFORM_DRV_MODULE_NUM > PLANTFORM_MAX_PWM_MODULE_NUM)
#error "Don't support Driver Module MUM"
#endif

//配置的电机模块数目需要小于最大的PWM模块个数
#if (PLANTFORM_DRV_MODULE_NUM > PLANTFORM_MAX_CFG_PARA_ID)
#error "Check parameter num and Driver Module MUM"
#endif


/*********************************************************************************
* 当前硬件选择的EPWM通道配置
*
* 驱动单元  EPWM通道、参数组及采样方式配置
*
* 驱动单元模块个数为1时: 仅驱动单元0可用
*		默认为EPWM0和参数M0配置
*			对单EPWM的MCU,仅EPWM0可用,MA、UA层等的编译宏默认为M0的配置。
*			对多EPWM的MCU,DU可设置DRV0_PWM_ID(EPWM0或者EPWM1),并选择配置参数DRV0_PARA_ID。
*				并需要更改DRV0_PARA_ID对应的MC_GlobalDef_Mx.h中的相应配置,
*				CURRENT_SAMPLE_TYPE_Mx 和 PWM_USED_ID_Mx 为 DRV0_CUR_SAMP_TYPE/DRV0_PWM_ID。
*				
*
**********************************************************************************/
#if (PLANTFORM_DRV_MODULE_NUM == 1)		//驱动单元模块个数为1
#define EPWM0_USED						(FUNCTION_ON)		//   应用EPWM0
#define EPWM1_USED						(FUNCTION_OFF)		// 不应用EPWM1

// 驱动单元0配置
#define DRV0_PWM_ID						(PLANTFORM_EPWM0)	//  选用EPWM0
#define DRV0_PARA_ID					(0)					//  选用参数组0，即M0参数配置
#define DRV0_CUR_SAMP_TYPE				(EPWM0_CURRENT_SAMPLE_TYPE)

#define DRV0_BEMF_CHECK_EABLE			(FUNCTION_OFF)


/*-------------------------------------------------------------------------------*/

#elif (PLANTFORM_DRV_MODULE_NUM == 2)	//驱动单元模块个数为2
#error "Only Support single motor! "
#endif

/*********************************************************************************
* 单驱动单元时，代码空间编译优化，仅支持驱动单元0
* 根据设定的参数组，设置编译宏选项
* 多驱动单元时，根据配置参数选择，无需进行宏选择编译
**********************************************************************************/
#if (DRV0_PARA_ID == 0)
	#define DRV0_CLOSE_LOOP				(CLOSE_LOOP_M0)
	#define DRV0_POWER_LIMIT_STATUS		(POWER_LIMIT_STATUS_M0)
	#define DRV0_SPPED_LIMIT_STATUS		(SPPED_LIMIT_STATUS_M0)
	#define DRV0_WEAKEN_FLUX_STATUS		(WEAKEN_FLUX_STATUS_M0)
	#define DRV0_PWM_ENABLE_STOP		(PWM_ENABLE_STOP_M0)
	#define DRV0_STOP_MODE				(STOP_MODE_M0)
	#define DRV0_UNDVOLT_PROT_ENABLE	(U_UNDVOLT_PROT_ENABLE_M0)
	#define DRV0_DIR_CHECK_ENABLE		(DIR_CHECK_STATUS_M0)
	#define DRV0_POS_SEEK_ENABLE		(SEEK_POSITION_STATUS_M0)
	#define DRV0_ALLIGN_CUR_ENABLE		(ALLIGN_STATUS_M0)
	#define DRV0_CHARGE_ENABLE			(CHARGE_STATUS_M0)
#else
	#error "Check parameter num in 1 DRV Unit mode"
#endif

/*********************************************************************************
* 其他配置及调试信息
*
**********************************************************************************/

#define QUICK_CURRENTKLOOP_FUNCTION		(FUNCTION_ON)		// 快速电流环模式，缩短电流环执行时间

#define OBSERVER_PLL_CHANGE_ENABLE		(FUNCTION_ON)		// 观测器PLL调整使能

#define VF_START_FUNCTION_ENABLE		(FUNCTION_ON)		// VF启动使能

#define MCPWM_DEBUG                     (FUNCTION_OFF)      //DEBUG

#if (VF_START_FUNCTION_ENABLE == FUNCTION_ON)
#define VECTOR_VF_COMP_ENABLE			(FUNCTION_ON)		// VF启动使能时，VECTOR VF补偿自动使能
#else
#define VECTOR_VF_COMP_ENABLE			(FUNCTION_OFF)		// VECTOR VF补偿使能
#endif

#define POWER_CALC_CALIB_FUNCTION_ENABLE	(FUNCTION_ON)		// 功率校正使能 y=a2 * x^2 +a1 * x + a0


#define RTT_FUNCTION                   (FUNCTION_ON)		/* RTT 调试功能 */

/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************
*参数配置 以下用于LKSMotor 配置
*
*定义参数的存储位置，在工程rom分配中已经根据FLASH大小进行定义，此处需要根据配置
*设置ADDR_PARA_LOCATION地址
*
*
**********************************************************************************/
#define DOWNLOAD_STOP_WAIT_MS			(8000)		// 电机运行状态下载时强制等待时间，根据项目设置合适时间刻度
													// 电机不运行状态时，直接下载

#define DOWNLOAD_WRITE_REQ_TIME_OUT		(100)	// ms


// ATTENTION:
/********************************************************************************************/
// The fowwing is used in Keil V5 compiler
// In Keil AC6 compiler, as _at_ is changed, the address is directly used in 
//		__attribute__((section(".ARM.__at_0xFE00")))
// sizeof(STR_DrvCfgGlobal) = 8
// IN different MCU, the address is different

#define ADDR_DOWNLOAD_WRITE_LOCATION	(0x20001000)
#define ADDR_DOWNLOAD_READ_LOCATION		(0x20001001)

#define ADDR_PARA_LOCATION				(0x1FE00)
#define ADDR_PARA_START_LOCATION		(ADDR_PARA_LOCATION + sizeof(STR_DrvCfgGlobal))

// ATTENTION END
/*********************************************************************************************/

#define PARA_CFG_HEADER					(0x80)
#define PARA_CFG_MAIN_VERSION			(0x0A)
#define PARA_CFG_VERSION				(0x04)
#define PARA_CFG_SUB_VERSION			(0x01)

#define PARA_CFG_LENGTH					(0x01)
#define PARA_CFG_NUMBER					(PLANTFORM_MAX_CFG_PARA_ID)


#define PARA_DOWNLOAD_ENBALE			(FUNCTION_ON)		//使能参数配置下载握手校验

#define PARA_CHECK_ENBALE				(FUNCTION_ON)		//使能参数配置校验，校验版本号等

#endif  /* __PROJECT_CONFIG_H_ */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

