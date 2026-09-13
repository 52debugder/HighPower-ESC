#ifndef __HAL_LKSMCU_CRC_H__
#define __HAL_LKSMCU_CRC_H__

#include "stdint.h"
typedef enum
{
    HAL_CRC_0, ///< CRC模块0
} HAL_CRC_x;

typedef enum
{
    HAL_CRC_MODEL_CRC8,              ///< 8   07       00       00       false false
    HAL_CRC_MODEL_CRC8_ITU,          ///< 8   07       00       55       false false
    HAL_CRC_MODEL_CRC8_ROHC,         ///< 8   07       FF       00       true  true
    HAL_CRC_MODEL_CRC8_MAXIMx,       ///< 8   31       00       00       true  true
    HAL_CRC_MODEL_CRC16_IBMx1,       ///< 16  8005     0000     0000     true  true
    HAL_CRC_MODEL_CRC16_MAXIM,       ///< 16  8005     0000     FFFF     true  true
    HAL_CRC_MODEL_CRC16_USBx1,       ///< 16  8005     FFFF     FFFF     true  true
    HAL_CRC_MODEL_CRC16_MODBU,       ///< 16  8005     FFFF     0000     true  true
    HAL_CRC_MODEL_CRC16_CCITT,       ///< 16  1021     0000     0000     true  true
    HAL_CRC_MODEL_CRC16_CCITT_FALSE, ///< 16  1021     FFFF     0000     false false
    HAL_CRC_MODEL_CRC16_X25,         ///< 16  1021     FFFF     FFFF     true  true
    HAL_CRC_MODEL_CRC16_XMODEM,      ///< 16  1021     0000     0000     false false
    HAL_CRC_MODEL_CRC16_DNP,         ///< 16  3D65     0000     FFFF     true  true
    HAL_CRC_MODEL_CRC32,             ///< 32  04C11DB7 FFFFFFFF FFFFFFFF true  true
    HAL_CRC_MODEL_CRC32_MPEG_2,      ///< 32  04C11DB7 FFFFFFFF 00000000 false false
} HAL_CRC_MODEL_x;
// 初始化
void HAL_CRC_Reset(HAL_CRC_x);   // 模块复位
void HAL_CRC_Enable(HAL_CRC_x);  // 模块打开
void HAL_CRC_Disable(HAL_CRC_x); // 模块关闭
// 计算
uint32_t HAL_CRC_Calc(HAL_CRC_x, HAL_CRC_MODEL_x, uint8_t *data, uint32_t len); // 计算crc,03使用软件实现,其余芯片使用硬件实现
#endif
