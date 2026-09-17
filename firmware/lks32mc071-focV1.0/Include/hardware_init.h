#ifndef __HARDWARE_INIT_H
#define __HARDWARE_INIT_H

#include <stdint.h>
#include "basic.h"
#include "lks32mc07x_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define P_HIGH__N_HIGH                   0U
#define P_HIGH__N_LOW                    1U

#define ESC_MOTOR_ID                     1U
#define ESC_MCU_MCLK_HZ                  96000000UL
#define ESC_PWM_MCLK_HZ                  ESC_MCU_MCLK_HZ
#define ESC_PWM_PRSC                     0U
#define ESC_PWM_FREQ_HZ                  20000U
#define ESC_PWM_PERIOD                   ((u16)(ESC_PWM_MCLK_HZ / (2UL * ESC_PWM_FREQ_HZ * (1UL << ESC_PWM_PRSC))))
#define ESC_PWM_SAFE_DUTY                (ESC_PWM_PERIOD >> 2)
#define ESC_DEADTIME_NS                  500U
#define ESC_DEADTIME_TICKS               ((u16)(((unsigned long long)ESC_PWM_MCLK_HZ * (unsigned long long)ESC_DEADTIME_NS) / 1000000000ULL))
#define ESC_PRE_DRIVER_POLARITY          P_HIGH__N_LOW

#define ESC_ADC_RESOLUTION               4096U
#define ESC_ADC_MAX                      (ESC_ADC_RESOLUTION - 1U)
#define ESC_ADC_MIDPOINT                 (ESC_ADC_RESOLUTION / 2U)

#define ESC_CURRENT_SAMPLE_1SHUNT        1U
#define ESC_CURRENT_SAMPLE_2SHUNT        2U
#define ESC_CURRENT_SAMPLE_3SHUNT        3U
#define ESC_CURRENT_SAMPLE_TYPE          ESC_CURRENT_SAMPLE_3SHUNT

#define ESC_ADC_CURRENT_U_CHANNEL        ADC_CHANNEL_7
#define ESC_ADC_CURRENT_V_CHANNEL        ADC_CHANNEL_8
#define ESC_ADC_CURRENT_W_CHANNEL        ADC_CHANNEL_9
#define ESC_ADC_BUS_VOLTAGE_CHANNEL      ADC_CHANNEL_5
#define ESC_ADC_BUS_CURRENT_CHANNEL      ADC_CHANNEL_3
#define ESC_ADC_TEMP_CHANNEL             ADC_CHANNEL_4
#define ESC_ADC_BEMF_U_CHANNEL           ADC_CHANNEL_13
#define ESC_ADC_BEMF_V_CHANNEL           ADC_CHANNEL_12
#define ESC_ADC_BEMF_W_CHANNEL           ADC_CHANNEL_11

#define DRV8353_EN_GPIO                  GPIO1
#define DRV8353_EN_PIN                   GPIO_Pin_10
#define DRV8353_NSCS_GPIO                GPIO2
#define DRV8353_NSCS_PIN                 GPIO_Pin_12
#define DRV8353_NFAULT_GPIO              GPIO2
#define DRV8353_NFAULT_PIN               GPIO_Pin_3

#define BOARD_LED_GPIO                   GPIO3
#define BOARD_LED_PIN                    GPIO_Pin_1

void SoftDelay(u32 cnt);
void Clock_Init(void);
void Hardware_init(void);
void GPIO_init(void);
void ADC0_init(void);
void ADC1_init(void);
void MCPWM_init(void);
void UART1_init(void);
void CAN0_init(void);
void DMA_init(void);

void ESC_PWM_Enable(void);
void ESC_PWM_Disable(void);
void ESC_PWM_SetDuty(uint16_t duty_u, uint16_t duty_v, uint16_t duty_w);
void ESC_PWM_SetSafeDuty(void);
void ESC_ADC_GetPhaseRaw(uint16_t *adc_u, uint16_t *adc_v, uint16_t *adc_w);
uint16_t ESC_ADC_GetBusVoltageRaw(void);
uint16_t ESC_ADC_GetTempRaw(void);
uint8_t ESC_BoardFaultActive(void);
void ESC_FocLoopEnable(uint8_t enable);
uint8_t ESC_FocLoopIsEnabled(void);

#ifdef __cplusplus
}
#endif

#endif