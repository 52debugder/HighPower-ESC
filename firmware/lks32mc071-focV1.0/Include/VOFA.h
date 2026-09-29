#ifndef __HARDWARE_INIT_H
#define __HARDWARE_INIT_H

#include <stdint.h>
#include "basic.h"
#include "lks32mc07x_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

void Print1_Motor_To_VOFA(float data, uint8_t length);
void Print2_Motor_To_VOFA(float data1, float data2);
void Print3_Motor_To_VOFA(float data1, float data2, float data3);
void Print4_Motor_To_VOFA(float data1, float data2, float data3, float data4);
void Print5_Motor_To_VOFA(float data1, float data2, float data3, float data4, float data5);
void Print8_Motor_To_VOFA(float d1, float d2, float d3, float d4, float d5, float d6, float d7, float d8);

#ifdef __cplusplus
}
#endif

#endif


