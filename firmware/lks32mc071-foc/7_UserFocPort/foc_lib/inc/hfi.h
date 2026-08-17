#ifndef __HFI_H
#define __HFI_H

#include "foc_types.h"
#include "foc_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#if HFI_ENABLE
void HFI_Init(foc_handle_t *motor);
void HFI_Enable(foc_handle_t *motor);
void HFI_Disable(foc_handle_t *motor);
void HFI_Reset_Angle(foc_handle_t *motor, float theta);
void HFI_Select_Angle(foc_handle_t *motor, float dt);
void HFI_Process_Current(foc_handle_t *motor, float dt);
void HFI_Add_Voltage(foc_handle_t *motor, float dt);
#endif

#ifdef __cplusplus
}
#endif

#endif
