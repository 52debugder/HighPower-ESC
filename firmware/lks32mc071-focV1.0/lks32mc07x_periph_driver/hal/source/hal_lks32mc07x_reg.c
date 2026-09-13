#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"

#ifdef HAL_LKS32MC07X_REG
HAL_SYS_TypeDef *const HAL_SYS[]     = {(HAL_SYS_TypeDef *)SYS_BASE};
HAL_FLASH_TypeDef *const HAL_FLASH[] = {(HAL_FLASH_TypeDef *)FLASH_BASE};
HAL_SPI_TypeDef *const HAL_SPI[]     = {(HAL_SPI_TypeDef *)SPI0_BASE};
HAL_I2C_TypeDef *const HAL_I2C[]     = {(HAL_I2C_TypeDef *)I2C0_BASE};
HAL_CMP_TypeDef *const HAL_CMP[]     = {(HAL_CMP_TypeDef *)CMP_BASE};
HAL_HALL_TypeDef *const HAL_HALL[]   = {(HAL_HALL_TypeDef *)HALL0_BASE};
HAL_ADC_TypeDef *const HAL_ADC[]     = {(HAL_ADC_TypeDef *)ADC0_BASE, (HAL_ADC_TypeDef *)ADC1_BASE};
HAL_TIMER_TypeDef *const HAL_TIMER[] = {(HAL_TIMER_TypeDef *)TIMER0_BASE, (HAL_TIMER_TypeDef *)TIMER1_BASE, (HAL_TIMER_TypeDef *)TIMER2_BASE, (HAL_TIMER_TypeDef *)TIMER3_BASE};
HAL_QEP_TypeDef *const HAL_QEP[]     = {(HAL_QEP_TypeDef *)QEP0_BASE, (HAL_QEP_TypeDef *)QEP1_BASE};
HAL_MCPWM_TypeDef *const HAL_MCPWM[] = {(HAL_MCPWM_TypeDef *)MCPWM0_BASE};
HAL_GPIO_TypeDef *const HAL_GPIO[]   = {(HAL_GPIO_TypeDef *)GPIO0_BASE, (HAL_GPIO_TypeDef *)GPIO1_BASE, (HAL_GPIO_TypeDef *)GPIO2_BASE, (HAL_GPIO_TypeDef *)GPIO3_BASE};
HAL_CRC_TypeDef *const HAL_CRC[]     = {(HAL_CRC_TypeDef *)CRC0_BASE};
HAL_UART_TypeDef *const HAL_UART[]   = {(HAL_UART_TypeDef *)UART0_BASE, (HAL_UART_TypeDef *)UART1_BASE};
HAL_CAN_TypeDef *const HAL_CAN[]     = {(HAL_CAN_TypeDef *)CAN0_BASE};
HAL_DSP_TypeDef *const HAL_DSP[]     = {(HAL_DSP_TypeDef *)DSP0_BASE};
HAL_IWDG_TypeDef *const HAL_IWDG[]   = {(HAL_IWDG_TypeDef *)IWDG_BASE};
HAL_DMA_TypeDef *const HAL_DMA[]     = {(HAL_DMA_TypeDef *)(DMA0_BASE + 0), (HAL_DMA_TypeDef *)(DMA0_BASE + 0x20), (HAL_DMA_TypeDef *)(DMA0_BASE + 0x40), (HAL_DMA_TypeDef *)(DMA0_BASE + 0x60)};
#endif
