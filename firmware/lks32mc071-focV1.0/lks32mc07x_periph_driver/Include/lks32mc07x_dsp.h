/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_dsp.h\n
 * 文件标识： 无 \n
 * 内容摘要： DSP驱动头文件 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2018年07月25日 <td>1.0     <td>Howlet      <td>创建
 * </table>
 */

#ifndef _CONNIE_DSP_H_
#define _CONNIE_DSP_H_

/* Includes ------------------------------------------------------------------*/
#include "lks32mc07x_lib.h"

/**
 *@brief DSP寄存器结构体句柄
 */

typedef struct
{
    __IO u32 SC;     // 0x00)
    __IO u32 THETA;  // 0x04)
    __IO u32 X;      // 0x08)
    __IO u32 Y;      // 0x0C)
    __IO u32 SIN;    // 0x10)
    __IO u32 COS;    // 0x14)
    __IO u32 MOD;    // 0x18)
    __IO u32 ARCTAN; // 0x1C)
    __IO u32 DID;    // 0x20)
    __IO u32 DIS;    // 0x24)
    __IO u32 QUO;    // 0x28)
    __IO u32 REM;    // 0x2C)
    __IO u32 RAD;    // 0x30)
    __IO u32 SQRT;   // 0x34)
    __IO u32 PC;     // 0x38)
} DSP_Typedef;
/**
 *@brief DSP基地址
 */
#define DSP_REG ((DSP_Typedef *)(DSP0_REG_BASE + 0x00))

void DSP_Init(void);
s16 DSP_arctan(s16 x, s16 y);
s32 DSP_div(s32 a, s32 b);
s16 DSP_sin(s16 angle);
s16 DSP_cos(s16 angle);
s32 DSP_rms(s32 a, s32 b);
u16 DSP_mod(s16 x, s16 y);
u16 DSP_sqrt(u32 val);
void DSP_SinCosMode(void);
void DSP_ArctanMode(void);

// 命名由DSP0_div更新为DSP_div，使用下面的宏以兼容之前的代码
#define DSP0_arctan DSP_arctan
#define DSP0_div    DSP_div
#define DSP0_sin    DSP_sin
#define DSP0_cos    DSP_cos
#define DSP0_rms    DSP_rms
#define DSP0_mod    DSP_mod
#define DSP0_sqrt   DSP_sqrt

#define DSP_SIN_COS_MODE()         \
    {                              \
        DSP_REG->SC = BIT2 | BIT1; \
    }
#define DSP_ARCTAN_MODE()   \
    {                       \
        DSP_REG->SC = BIT1; \
    }
// 增加DSP_CALC系列的接口，以降低参数传递带来的时间损耗
#define DSP_CALC_SIN(sin, angle)       \
    {                                  \
        int32_t flg = __get_PRIMASK(); \
        __disable_irq();               \
        DSP_SIN_COS_MODE();            \
        DSP_REG->THETA = (u16)angle;   \
        sin            = DSP_REG->SIN; \
        __set_PRIMASK(flg);            \
    }
#define DSP_CALC_COS(cos, angle)       \
    {                                  \
        int32_t flg = __get_PRIMASK(); \
        __disable_irq();               \
        DSP_SIN_COS_MODE();            \
        DSP_REG->THETA = (u16)angle;   \
        cos            = DSP_REG->COS; \
        __set_PRIMASK(flg);            \
    }
#define DSP_CALC_RMS(rms, a, b)        \
    {                                  \
        int32_t flg = __get_PRIMASK(); \
        __disable_irq();               \
        DSP_REG->DID = a;              \
        DSP_REG->DIS = b;              \
        rms          = DSP_REG->REM;   \
        __set_PRIMASK(flg);            \
    }

#define DSP_CALC_ARCTAN(arctan, x, y)  \
    {                                  \
        int32_t flg = __get_PRIMASK(); \
        __disable_irq();               \
        DSP_ARCTAN_MODE();             \
        DSP_REG->X = x;                \
        DSP_REG->Y = y;                \
        arctan     = DSP_REG->ARCTAN;  \
        __set_PRIMASK(flg);            \
    }
#define DSP_CALC_DIV(c, a, b)           \
    {                                   \
        int32_t _flg = __get_PRIMASK(); \
        __disable_irq();                \
        DSP_REG->DID = (a);             \
        DSP_REG->DIS = (b);             \
        c            = DSP_REG->QUO;    \
        __set_PRIMASK(_flg);            \
    }
#define DSP_CALC_MOD(mod, x, y)        \
    {                                  \
        int32_t flg = __get_PRIMASK(); \
        __disable_irq();               \
        DSP_ARCTAN_MODE();             \
        DSP_REG->X = x;                \
        DSP_REG->Y = y;                \
        mod        = DSP_REG->MOD;     \
        __set_PRIMASK(flg);            \
    }
#define DSP_CALC_SQRT(sqrt, val)       \
    {                                  \
        int32_t flg = __get_PRIMASK(); \
        __disable_irq();               \
        DSP_REG->RAD = val;            \
        sqrt         = DSP_REG->SQRT;  \
        __set_PRIMASK(flg);            \
    }

#endif
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
