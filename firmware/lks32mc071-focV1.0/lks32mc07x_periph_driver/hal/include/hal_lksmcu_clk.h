#ifndef __HAL_LKSMCU_CLK_H__
#define __HAL_LKSMCU_CLK_H__
#include "stdint.h"

/// @brief 主频
typedef enum
{
    HAL_CLK_FREQ_RC_8MHZ,  ///< 主频8Mhz
    HAL_CLK_FREQ_RC_12MHZ, ///< 主频12Mhz
    HAL_CLK_FREQ_RC_24MHZ, ///< 主频24Mhz
    HAL_CLK_FREQ_RC_48MHZ, ///< 主频48Mhz
    HAL_CLK_FREQ_RC_96MHZ, ///< 主频96Mhz

#ifdef HAL_TEST_NOT_SUPPORTED
    HAL_CLK_FREQ_XTAL_6MHZ,  ///< 主频6Mhz 不支持
    HAL_CLK_FREQ_XTAL_12MHZ, ///< 主频12Mhz 不支持
    HAL_CLK_FREQ_XTAL_24MHZ, ///< 主频24Mhz 不支持
    HAL_CLK_FREQ_XTAL_48MHZ, ///< 主频48Mhz 不支持
    HAL_CLK_FREQ_XTAL_96MHZ, ///< 主频96Mhz 不支持

    HAL_CLK_FREQ_RC_4MHZ,     ///< 主频4Mhz 不支持
    HAL_CLK_FREQ_RC_6MHZ,     ///< 主频6Mhz 不支持
    HAL_CLK_FREQ_RC_9MHZ,     ///< 主频9Mhz 不支持
    HAL_CLK_FREQ_RC_16MHZ,    ///< 主频16Mhz 不支持
    HAL_CLK_FREQ_RC_18MHZ,    ///< 主频18Mhz 不支持
    HAL_CLK_FREQ_RC_32MHZ,    ///< 主频32Mhz 不支持
    HAL_CLK_FREQ_RC_36MHZ,    ///< 主频36Mhz 不支持
    HAL_CLK_FREQ_RC_64MHZ,    ///< 主频64Mhz 不支持
    HAL_CLK_FREQ_RC_72MHZ,    ///< 主频72Mhz 不支持
    HAL_CLK_FREQ_RC_192MHZ,   ///< 主频192Mhz 不支持
    HAL_CLK_FREQ_XTAL_192MHZ, ///< 主频192Mhz 不支持
#endif
} HAL_CLK_FREQ_x;
void HAL_CLK_SetMcuFreq(HAL_CLK_FREQ_x);
uint32_t HAL_CLK_GetMcuFreq(void);
#endif
