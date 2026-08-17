/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： MC_type.c
 * 文件标识：
 * 内容摘要： 电机控制相关结构体声明
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MC_TYPE_H
#define __MC_TYPE_H

/* Includes ------------------------------------------------------------------*/
#include "basic.h"
#include "string.h"


#define FUNCTION_ON                  1
#define FUNCTION_OFF                 0



/* Exported types ------------------------------------------------------------*/
/*! Macro converting a signed fractional [-1,1) number into a fixed point 16-bit
 * number in the format Q1.15. */
 
#define S16FRACT_MAX                   (0.999969482421875)
#define S16FRACT_MIN                   (-1.0)

#define S32FRACT_MAX                   (0.9999999995343387126922607421875)
#define S32FRACT_MIN                   (-1.0)

#define FRAC16(x)                      ((s16) ((x) < (S16FRACT_MAX) ? ((x) >= S16FRACT_MIN ? (x)*0x8000 : 0x8000) : 0x7fff))

/*! Macro converting a signed fractional [-1,1) number into a fixed point 32-bit
 * number in the format Q1.31. */
#define FRAC32(x)                      ((s32) ((x) < (S32FRACT_MAX) ? ((x) >= S32FRACT_MIN ? (x)*0x80000000 : 0x80000000) : 0x7fffffff))

#define ABS(X)              ( ( (X) >= 0 ) ? (X) : -(X) )

#define sat(x,ll,ul) ( (x) > (ul) ) ? (ul) : ( ( (x) < (ll) ) ? (ll) : (x) )


#define   _IQ15mpy(A,B)                (((s32)A*B)>>15)  /* ??Q15???? */
#define   _IQ12mpy(A,B)                (((s32)A*B)>>12)  /* ??Q12???? */

#define		_IQ15(A)					(s32)(32767.0 * A)

#define		SQRT_2    					(1.414213562373095)


/* ----------------------------direction const define----------------------- */
#define CW                             (0)                /* motor dir:cw */ 
#define CCW                            (1)                /* motor dir:ccw*/


#define CURRENT_LOOP                   (0)                /* current run */
#define SPEED_LOOP                     (1)                /* speed run */
#define POWER_LOOP                     (2)                /* power run */

#define MAX_MODULE_VALUE                (18919)





#define CURRENT_SAMPLE_1SHUNT          1                  /* ?????????????? */
#define CURRENT_SAMPLE_2SHUNT          2                  /* ?????????????? */
#define CURRENT_SAMPLE_3SHUNT          3                  /* ?????????????? */
#define CURRENT_SAMPLE_MOSFET          4                  /* ????????????MOS?????? */

#define ROTOR_HALL_SENSOR              1                  /* ??????????HALL */
#define ROTOR_SENSORLESS               2                  /* ??????????HALL */
#define ROTOR_HALL2SENSORLESS          3                  /* ??????????HALL + ???Sensorless */

typedef struct
{
    s16 nAxisQ;
    s16 nAxisD;
} STR_VectorDQ,*PSTR_VectorDQ;//DQ;

typedef struct
{
    s16 nAlph;
    s16 nBeta;
} STR_VectorAB,*PSTR_VectorAB;//AlphBeta;

typedef struct
{
    s16 nPhaseU;
    s16 nPhaseV;
    s16 nPhaseW;
} STR_VectorUVW;

typedef enum
{
    E_MOTOR_RESET,
	E_MOTOR_TRACKING,
	E_MOTOR_BEMF_TRACKING,
	E_MOTOR_ALIGN,
	E_MOTOR_ASYN,
	E_MOTOR_PRE_SYN,
	E_MOTOR_SYN,
	E_MOTOR_BRAKE,
	E_MOTOR_IPD,
	E_MOTOR_OFFLINE_ID
} ENUM_MotorStatus;//MOTOR_STATUS;

typedef struct
{
    s16 hCos;
    s16 hSin;
} STR_TrigComponents;


typedef struct
{
    s32 yk_1;
    u16 coef;
} stru_RC_Def,*pstru_RC_Def;

typedef struct
{
    s16 nData0;
    s16 nData1;
} stru_Array_Def;










/* Exported constants --------------------------------------------------------*/
#define U8_MAX     ((u8)255)
#define S8_MAX     ((s8)127)
#define S8_MIN     ((s8)-128)
#define U16_MAX    ((u16)65535u)
#define S16_MAX    ((s16)32767)
#define S16_MIN    ((s16)-32768)
#define U32_MAX    ((u32)4294967295uL)
#define S32_MAX    ((s32)2147483647)
#define S32_MIN    ((s32)-2147483648)


#define S16P80     ((s16)26213)
#define S16P65     ((s16)25000)
#define S16P50     ((s16)13000)
#define S16P95     ((s16)30000)





/**
* Not initialized pointer
*/
#define MC_NULL    (uint16_t)(0x0000u)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MC_TYPE_H */
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

