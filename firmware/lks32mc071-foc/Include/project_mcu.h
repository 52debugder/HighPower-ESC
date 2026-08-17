/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： project_mcu.h
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

#ifndef __PROJECT_MCU_H_
#define __PROJECT_MCU_H_

#include "basic.h"
#include "MC_Type.h"

#include "lks32mc07x.h"
#include "lks32mc07x_mcpwm.h"
#include "lks32mc07x_sys.h"
#include "lks32mc07x_adc.h"
#include "lks32mc07x_flash.h"
#include "lks32mc07x_Gpio.h"
#include "lks32mc07x_cmp.h"
#include "lks32mc07x_uart.h"
#include "lks32mc07x_hall.h"
#include "lks32mc07x_tim.h"
#include "lks32mc07x_NVR.h"

// MCU function select
#define MCU_DSP_SINCOS				(FUNCTION_ON)
#define MCU_DSP_DIV					(FUNCTION_ON)


#endif  /* __PROJECT_CONFIG_H_ */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

