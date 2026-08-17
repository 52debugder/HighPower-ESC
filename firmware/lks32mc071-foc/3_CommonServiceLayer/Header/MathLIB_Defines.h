
/******************************************************************************/
#ifndef _SWLIBS_DEFINES_H
#define _SWLIBS_DEFINES_H

#include "MathLIB_Typedefs.h"

/******************************************************************************
* Defines and macros            (scope: module-local)
******************************************************************************/
/*! If USE_ASM macro is enabled then, if existing, an assembly version of
* the functions are used */
//#define USE_ASM

/*! If USE_FRAC32_ARITHMETIC macro is enabled then, 32bit arithmetic is used
* for intermediate calculations, achieving best possible calculation accuracy.*/
#define USE_FRAC32_ARITHMETIC

/*! Constant representing the maximal negative value of a signed fixed point 16-bit fractional
 * number eq -1.0 */
#define SFRACT_MIN          (-1.0)

/*! Constant representing the maximal positive value of a signed fixed point 16-bit fractional
 * number eq 0.999969482421875 */
#define SFRACT_MAX          (0.999969482421875)

/*! Constant representing the maximal negative value of a signed fixed point 32-bit fractional
 * number eq -1.0 */
#define FRACT_MIN           (-1.0)

/*! Constant representing the maximal positive value of a signed fixed point 32-bit fractional
 * number eq 0.9999999995343387126922607421875 */
#define FRACT_MAX           (0.9999999995343387126922607421875)

/*! Constant representing the maximal positive value of a signed fixed point 16-bit integer
 * number eq \f$ 2^{16-1}-1 = \f$ 0x7fff. */
#ifndef INT16_MAX
#define INT16_MAX           ((tS16) 0x7fff)
#endif

/*! Constant representing the maximal negative value of a signed fixed point 16-bit integer
 * number eq \f$ -2^{16-1} = \f$ 0x8000. */
#ifndef INT16_MIN
#define INT16_MIN           ((tS16) 0x8000)
#endif

/*! Constant representing the maximal positive value of a signed fixed point 32-bit integer
 * number eq \f$ 2^{32-1}-1 = \f$ 0x7fff ffff. */
#ifndef INT32_MAX
#define INT32_MAX           ((tS32) 0x7fffffff)
#endif

/*! Constant representing the maximal negative value of a signed fixed point 32-bit integer
 * number eq \f$ -2^{32-1} = \f$ 0x8000 0000. */
#ifndef INT32_MIN
#define INT32_MIN           ((tS32) 0x80000000)
#endif



/*! Type casting - a signed 16-bit fractional value cast as a signed 16-bit integer */
#define F16TOINT16(x)       ((tS16) (x))

/*! Type casting - the lower 16 bits of a signed fractional 32-bit fractional value cast
 * as a signed integer 16-bit integer */
#define F32TOINT16(x)       ((tS16) (x))

/*! Type casting - the lower 16 bits of a signed fractional 64-bit fractional value cast
 * as a signed integer 16-bit integer */
#define F64TOINT16(x)       ((tS16) (x))

/*! Type casting - a signed 16-bit fractional value cast as a signed 32-bit 
 * integer, the value placed at the lower 16 bits of the 32-bit result */
#define F16TOINT32(x)       ((tS32) (x))

/*! Type casting - a signed 32-bit fractional value cast as a signed
 * 32-bit integer */
#define F32TOINT32(x)       ((tS32) (x))

/*! Type casting - lower 32 bits of a signed 64-bit fractional value cast as a
 * signed 32-bit integer */
#define F64TOINT32(x)       ((tS32) (x))

/*! Type casting - a signed 16-bit fractional value cast as a signed 64-bit
 * integer, the value placed at the lower 16 bits of the 64-bit result */
#define F16TOINT64(x)       ((tS64) (x))

/*! Type casting - a signed 32-bit fractional value cast as a signed 64-bit integer,
 *  the value placed at the lower 32 bits of the 64-bit result */
#define F32TOINT64(x)       ((tS64) (x))

/*! Type casting - a signed 64-bit fractional value cast as a signed
 * 64-bit integer */
#define F64TOINT64(x)       ((tS64) (x))

/*! Type casting - a signed 16-bit integer value cast as a signed
 * 16-bit fractional */
#define INT16TOF16(x)       ((tFrac16) (x))

/*! Type casting - a signed 16-bit integer value cast as a signed 32-bit 
 * fractional, the value placed at the lower 16 bits of the 32-bit result */
#define INT16TOF32(x)       ((tFrac32) (x))

/*! Type casting - the lower 16 bits of a signed 32-bit integer value cast as a
 * signed 16-bit fractional */
#define INT32TOF16(x)       ((tFrac16) (x))

/*! Type casting - a signed 32-bit integer value cast as a signed fractional
 * 32-bit fractional */
#define INT32TOF32(x)       ((tFrac32) (x))

/*! Type casting - the lower 16 bits of a signed 64-bit integer value cast as a
 * signed 16-bit fractional */
#define INT64TOF16(x)       ((tFrac16) (x))

/*! Type casting - the lower 32 bits of a signed 64-bit integer value cast as a
 * signed 32-bit fractional */
#define INT64TOF32(x)       ((tFrac32) (x))

/*! One over sqrt(3) with a 16-bit result, the result rounded for a better
 * precision, i.e. \f$ round(1/sqrt(3)*2^{15}) \f$ */
#define F16_1_DIVBY_SQRT3   ((tFrac16) 0x49E7)

/*! One over sqrt(3) with a 32-bit result, the result rounded for a better
 *  precision, i.e. \f$ round(1/sqrt(3)*2^{31}) \f$ */
#define F32_1_DIVBY_SQRT3   ((tFrac32) 0x49E69D16)

/*! Sqrt(3) divided by two with a 16-bit result, the result rounded for a better
 * precision, i.e. \f$ round(sqrt(3)/2*2^{15}) \f$ */
#define F16_SQRT3_DIVBY_2   ((tFrac16) 0x6EDA)

/*! Sqrt(3) divided by two with a 32-bit result, the result rounded for a better
 * precision, i.e. \f$ round(sqrt(3)/2*2^{31}) \f$ */
#define F32_SQRT3_DIVBY_2   ((tFrac32) 0x6ED9EBA1)

/******************************************************************************
* Typedefs and structures       (scope: module-local)
******************************************************************************/

/******************************************************************************
* Exported variables
******************************************************************************/

/******************************************************************************
* Exported function prototypes
******************************************************************************/

/******************************************************************************
* Inline functions
******************************************************************************/

#endif /* _SWLIBS_DEFINES_H */

