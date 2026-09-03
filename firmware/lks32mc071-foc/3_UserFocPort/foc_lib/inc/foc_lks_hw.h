#ifndef __FOC_LKS_HW_H
#define __FOC_LKS_HW_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void foc_lks_hw_init(uint8_t motor);
void foc_lks_hw_pwm_start(uint8_t motor);
void foc_lks_hw_pwm_disable(uint8_t motor);
void foc_lks_hw_pwm_set(uint8_t motor, uint16_t duty_u, uint16_t duty_v, uint16_t duty_w);
void foc_lks_hw_drv_enable(uint8_t motor);
void foc_lks_hw_drv_disable(uint8_t motor);
void foc_lks_hw_adc_get(uint8_t motor, uint16_t *adc_u, uint16_t *adc_v, uint16_t *adc_w);
uint8_t foc_lks_hw_fault_active(uint8_t motor);

#ifdef __cplusplus
}
#endif

#endif
