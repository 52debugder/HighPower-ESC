#ifndef __FOC_H
#define __FOC_H

// #include "main.h"
#include "foc_types.h"
#include "smo.h"
#include "foc_config.h"
#include "foc_utils.h"
#include "foc_math.h"
#include "field_weakening.h"
#include "hfi.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct
{
    float speed;
    float speed_target;
    float speed_feedback;
    float id;
    float id_target;
    float id_feedback;
    float ud_output;
    float iq;
    float iq_target;
    float iq_feedback;
    float uq_output;
    float Sensor_zero_offset_locked;
} foc_current_loop_debug_t;

foc_state_t Foc_Init(uint8_t motor_num, const foc_hal_t *hal_interface);
foc_state_t Foc_ParamInit(foc_handle_t *motor, const foc_hal_t *hal_interface);
foc_state_t Foc_Deinit(foc_handle_t *motor);
foc_state_t Foc_Loop(uint8_t motor_num);
uint8_t Foc_Safe_Protect(float speed);
foc_state_t Foc_Align_Loop(foc_handle_t *motor, float dt);
foc_state_t Foc_Open_Loop(foc_handle_t *motor, float dt);
foc_state_t Foc_Close_Loop(foc_handle_t *motor, float dt);
void Foc_Update_SpeedLoop(uint8_t motor_num, float dt);
foc_state_t Foc_Stop(uint8_t motor_num);
foc_state_t Foc_Set_Speed(uint8_t motor_num, float speed);
foc_state_t Foc_Set_Position(uint8_t motor_num, float position_rad);
foc_state_t Foc_Set_Control_Mode(uint8_t motor_num, foc_control_mode_t mode);
foc_state_t Foc_Zero_Position(uint8_t motor_num);
float Foc_Get_Position(uint8_t motor_num);
foc_state_t Foc_GetCurrentLoopDebug(uint8_t motor_num, foc_current_loop_debug_t *debug);
foc_handle_t *Foc_GetStruct(uint8_t motor_num);
#if HFI_ENABLE
foc_state_t Foc_HFI_Enable(uint8_t motor_num);
foc_state_t Foc_HFI_Disable(uint8_t motor_num);
uint8_t Foc_HFI_Is_Valid(uint8_t motor_num);
float Foc_HFI_Get_Angle(uint8_t motor_num);
#endif



#ifdef __cplusplus
}
#endif

#endif // !__FOC_H


