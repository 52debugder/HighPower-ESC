
#ifndef __HAL_LKSMCU_TRIM_H__
#define __HAL_LKSMCU_TRIM_H__

#include "stdint.h"
uint32_t HAL_TRIM_Read(uint32_t addr);
uint32_t HAL_TRIM_ReadId(uint32_t idx);
uint32_t HAL_TRIM_ReadIdCrc32(void);

#endif
