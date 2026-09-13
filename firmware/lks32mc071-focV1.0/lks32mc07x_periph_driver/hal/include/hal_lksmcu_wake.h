
#ifndef __HAL_LKSMCU_WEAK_H__
#define __HAL_LKSMCU_WEAK_H__
#include "stdint.h"
typedef enum
{
    HAL_WAKE_UP_IO_P0_0_Low   = 0x0000,
    HAL_WAKE_UP_IO_P0_0_High  = 0x0100,
    HAL_WAKE_UP_IO_P0_2_Low   = 0x0001,
    HAL_WAKE_UP_IO_P0_2_High  = 0x0101,
    HAL_WAKE_UP_IO_P0_6_Low   = 0x0002,
    HAL_WAKE_UP_IO_P0_6_High  = 0x0102,
    HAL_WAKE_UP_IO_P0_11_Low  = 0x0003,
    HAL_WAKE_UP_IO_P0_11_High = 0x0103,
    HAL_WAKE_UP_IO_P0_14_Low  = 0x0004,
    HAL_WAKE_UP_IO_P0_14_High = 0x0104,
    HAL_WAKE_UP_IO_P2_4_Low   = 0x0005,
    HAL_WAKE_UP_IO_P2_4_High  = 0x0105,
    HAL_WAKE_UP_IO_P2_7_Low   = 0x0006,
    HAL_WAKE_UP_IO_P2_7_High  = 0x0106,
    HAL_WAKE_UP_IO_P2_15_Low  = 0x0007,
    HAL_WAKE_UP_IO_P2_15_High = 0x0107,

    HAL_WAKE_UP_IO_CLU0_Low  = 0x0008,
    HAL_WAKE_UP_IO_CLU0_High = 0x0108,
    HAL_WAKE_UP_IO_CLU1_Low  = 0x0009,
    HAL_WAKE_UP_IO_CLU1_High = 0x0109,
    HAL_WAKE_UP_IO_CLU2_Low  = 0x000a,
    HAL_WAKE_UP_IO_CLU2_High = 0x010a,
    HAL_WAKE_UP_IO_CLU3_Low  = 0x000b,
    HAL_WAKE_UP_IO_CLU3_High = 0x010b,

#ifdef HAL_TEST_NOT_SUPPORTED
    HAL_WAKE_UP_IO_P0_8_Low,   // 不支持
    HAL_WAKE_UP_IO_P0_8_High,  // 不支持
    HAL_WAKE_UP_IO_P0_9_Low,   // 不支持
    HAL_WAKE_UP_IO_P0_9_High,  // 不支持
    HAL_WAKE_UP_IO_P0_10_Low,  // 不支持
    HAL_WAKE_UP_IO_P0_10_High, // 不支持
    HAL_WAKE_UP_IO_P1_5_Low,   // 不支持
    HAL_WAKE_UP_IO_P1_5_High,  // 不支持
    HAL_WAKE_UP_IO_P1_8_Low,   // 不支持
    HAL_WAKE_UP_IO_P1_8_High,  // 不支持
    HAL_WAKE_UP_IO_P1_9_Low,   // 不支持
    HAL_WAKE_UP_IO_P1_9_High,  // 不支持
    HAL_WAKE_UP_IO_P0_1_Low,   // 不支持
    HAL_WAKE_UP_IO_P0_1_High,  // 不支持
    HAL_WAKE_UP_IO_P1_0_Low,   // 不支持
    HAL_WAKE_UP_IO_P1_0_High,  // 不支持
    HAL_WAKE_UP_IO_P1_1_Low,   // 不支持
    HAL_WAKE_UP_IO_P1_1_High,  // 不支持
    HAL_WAKE_UP_IO_P0_12_Low,  // 不支持
    HAL_WAKE_UP_IO_P0_12_High, // 不支持
    HAL_WAKE_UP_IO_P0_13_Low,  // 不支持
    HAL_WAKE_UP_IO_P0_13_High, // 不支持
    HAL_WAKE_UP_IO_P2_0_Low,   // 不支持
    HAL_WAKE_UP_IO_P2_0_High,  // 不支持
    HAL_WAKE_UP_IO_P0_3_Low,   // 不支持
    HAL_WAKE_UP_IO_P0_3_High,  // 不支持
    HAL_WAKE_UP_IO_P0_4_Low,   // 不支持
    HAL_WAKE_UP_IO_P0_4_High,  // 不支持
    HAL_WAKE_UP_IO_P0_5_Low,   // 不支持
    HAL_WAKE_UP_IO_P0_5_High,  // 不支持
    HAL_WAKE_UP_IO_P1_11_Low,  // 不支持
    HAL_WAKE_UP_IO_P1_11_High, // 不支持
    HAL_WAKE_UP_IO_P2_14_Low,  // 不支持
    HAL_WAKE_UP_IO_P2_14_High, // 不支持
    HAL_WAKE_UP_IO_P3_2_Low,   // 不支持
    HAL_WAKE_UP_IO_P3_2_High,  // 不支持
#endif

} HAL_WAKE_UP_IO_x;

void HAL_WAKE_DeepSleepIoWake(HAL_WAKE_UP_IO_x);
void HAL_WAKE_DeepSleepTimeWakeUp(uint32_t ms);
void HAL_WAKE_DeepSleepIoTimeWakeUp(HAL_WAKE_UP_IO_x, uint32_t ms);
#endif
