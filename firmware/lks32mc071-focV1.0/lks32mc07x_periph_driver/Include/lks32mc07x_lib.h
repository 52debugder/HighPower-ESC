/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_lib.h\n
 * 文件标识： 无 \n
 * 内容摘要： 库函数头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月12日 <td>1.1     <td>HuangMG  <td>修改
 * </table>
 */
#ifndef __lks32mc07x_LIB_H
#define __lks32mc07x_LIB_H

/* Includes ------------------------------------------------------------------*/
// typedef enum {DISABLE = 0, ENABLE = 1} FuncState;

#include "lks32mc07x.h"
#include "lks32mc07x_user_manual.h"
#include "lks32mc07x_adc.h"
#include "lks32mc07x_cmp.h"
#include "lks32mc07x_clu.h"
#include "lks32mc07x_crc.h"
#include "lks32mc07x_can.h"
#include "lks32mc07x_dma.h"
#include "lks32mc07x_dac.h"
#include "lks32mc07x_dsp.h"
#include "lks32mc07x_exti.h"
#include "lks32mc07x_flash.h"
#include "lks32mc07x_gpio.h"
#include "lks32mc07x_hall.h"
#include "lks32mc07x_i2c.h"
#include "lks32mc07x_mcpwm.h"
#include "lks32mc07x_nvr.h"
#include "lks32mc07x_opa.h"
#include "lks32mc07x_qep.h"
#include "lks32mc07x_sif.h"
#include "lks32mc07x_spi.h"
#include "lks32mc07x_sys.h"
#include "lks32mc07x_tim.h"
#include "lks32mc07x_tmp.h"
#include "lks32mc07x_uart.h"
#include "lks32mc07x_wake.h"

#define REG_WRITE(reg, mask)                   reg = (mask)                                             // 写寄存器
#define REG_READ(reg)                          (reg)                                                    // 读寄存器
#define REG_WRITE_BIT(reg, mask, val)          reg = ((reg) & ~(mask)) | (val)                          // 按位写
#define REG_READ_BIT(reg, mask)                ((reg) & (mask))                                         // 按位读
#define REG_IF_WRITE_BIT(reg, mask, condition) reg = (condition) ? ((reg) | (mask)) : ((reg) & ~(mask)) // 条件写
#define REG_READ_BIT_POS_MASK(reg, name)       (((reg) & (name##_MASK)) >> name##_POS)                  // 读取寄存器中指定掩码位的值
#define REG_WRITE_BIT_POS_MASK(reg, name, val) REG_WRITE_BIT(reg, name##_MASK, name(val))               // 写寄存器中指定掩码位的值
#define REG_SET(reg, mask)                     reg |= (mask)                                            // 写1
#define REG_RESET(reg, mask)                   reg &= ~(mask)                                           // 写0

#endif /*__lks32mc07x_UART_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
