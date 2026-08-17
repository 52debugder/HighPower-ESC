
#ifndef _SWLIBS_TYPEDEFS_H
#define _SWLIBS_TYPEDEFS_H

/******************************************************************************
* Defines and macros            (scope: module-local)
******************************************************************************/
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#define NULL ((void*)0)
#endif
#endif

/******************************************************************************
* Typedefs and structures       (scope: module-local)
******************************************************************************/
typedef unsigned char       tBool;          /*!< basic boolean type */

#ifndef FALSE
#define FALSE ((tBool)0)                    /*!< Boolean type FALSE constant */
#endif

#ifndef TRUE
#define TRUE ((tBool)1)                     /*!< Boolean type TRUE constant */
#endif

typedef unsigned char       tU8;            /*!< unsigned 8-bit integer type */
typedef signed char         tS8;            /*!< signed 8-bit integer type */
typedef unsigned short      tU16;           /*!< unsigned 16-bit integer type */
typedef signed short        tS16;           /*!< signed 16-bit integer type */
typedef unsigned int        tU32;           /*!< unsigned 32-bit integer type */
typedef signed int          tS32;           /*!< signed 32-bit integer type */
typedef unsigned long long  tU64;           /*!< unsigned 64-bit integer type */
typedef signed long long    tS64;           /*!< signed 64-bit integer type */

typedef tS16                tFrac16;        /*!< 16-bit signed fractional 
                                            Q1.15 type */
typedef tS32                tFrac32;        /*!< 32-bit signed fractional 
                                            Q1.31 type */

/*------------------------------------------------------------------------*//*!
@struct SWLIBS_3Syst "\SWLIBS_Typedefs.h"

@brief  Structure data type for three axis input/output variables.
*//*-------------------------------------------------------------------------*/
typedef struct
{
    tFrac32 s32Arg1;   /*!< First argument, type signed 32-bit fractional */
    tFrac32 s32Arg2;   /*!< Second argument, type signed 32-bit fractional */
    tFrac32 s32Arg3;   /*!< Third argument, type signed 32-bit fractional */
} SWLIBS_3Syst;

/*------------------------------------------------------------------------*//*!
@struct SWLIBS_2Syst "\SWLIBS_Typedefs.h"

@brief  Structure data type for two axis input/output variables.
*//*-------------------------------------------------------------------------*/
typedef struct
{
    tFrac32 s32Arg1;   /*!< First argument, type signed 32-bit fractional */
    tFrac32 s32Arg2;   /*!< Second argument, type signed 32-bit fractional */
} SWLIBS_2Syst;

/******************************************************************************
* Exported variables
******************************************************************************/

/******************************************************************************
* Exported function prototypes
******************************************************************************/

/******************************************************************************
* Inline functions
******************************************************************************/

#endif /* _SWLIBS_TYPEDEFS_H */
