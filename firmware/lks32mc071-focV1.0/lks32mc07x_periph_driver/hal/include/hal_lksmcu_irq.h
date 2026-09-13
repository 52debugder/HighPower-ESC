#ifndef __HAL_LKSMCU_IRQ_H__
#define __HAL_LKSMCU_IRQ_H__

#include "stdint.h"
#include "../hal_lks32mc07x.h"

/**
 * @brief 中断序号
 */
typedef enum
{
    // 来自arm内核的模块
    HAL_IRQ_MODULE_NonMaskableInt = -14,
    HAL_IRQ_MODULE_HardFault      = -13,
    HAL_IRQ_MODULE_SVCall         = -5,
    HAL_IRQ_MODULE_PendSV         = -2,
    HAL_IRQ_MODULE_SysTick        = -1,
    // 芯片外设

    HAL_IRQ_MODULE_TIMER0   = 0,
    HAL_IRQ_MODULE_TIMER1   = 1,
    HAL_IRQ_MODULE_TIMER2   = 2,
    HAL_IRQ_MODULE_TIMER3   = 3,
    HAL_IRQ_MODULE_MCPWM0   = 16,
    HAL_IRQ_MODULE_MCPWM0_1 = 17,
    HAL_IRQ_MODULE_I2C0     = 6,
    HAL_IRQ_MODULE_SPI0     = 7,
    HAL_IRQ_MODULE_GPIO0    = 8,
    HAL_IRQ_MODULE_HALL0    = 9,
    HAL_IRQ_MODULE_UART0    = 10,
    HAL_IRQ_MODULE_UART1    = 11,
    HAL_IRQ_MODULE_CMP0     = 13,
    HAL_IRQ_MODULE_ADC0     = 14,
    HAL_IRQ_MODULE_ADC1     = 15,
    HAL_IRQ_MODULE_WAKE0    = 21,
    HAL_IRQ_MODULE_QEP0     = 4,
    HAL_IRQ_MODULE_QEP1     = 5,
    HAL_IRQ_MODULE_DMA0     = 18,
    HAL_IRQ_MODULE_SIF0     = 20,
    HAL_IRQ_MODULE_SW0      = 22,
    HAL_IRQ_MODULE_INIT0    = 23,
    HAL_IRQ_MODULE_CL0      = 24,
    HAL_IRQ_MODULE_DSP0     = 12,
    HAL_IRQ_MODULE_CAN0     = 19,

#ifdef HAL_TEST_NOT_SUPPORTED
    HAL_IRQ_MODULE_TIMER4,   // 不支持
    HAL_IRQ_MODULE_MCPWM1,   // 不支持
    HAL_IRQ_MODULE_MCPWM1_1, // 不支持
    HAL_IRQ_MODULE_I2C1,     // 不支持
    HAL_IRQ_MODULE_SPI1,     // 不支持
    HAL_IRQ_MODULE_HALL1,    // 不支持
    HAL_IRQ_MODULE_UART2,    // 不支持
    HAL_IRQ_MODULE_CMP1,     // 不支持
    HAL_IRQ_MODULE_CMP2,     // 不支持
    HAL_IRQ_MODULE_CMP3,     // 不支持
    HAL_IRQ_MODULE_CMP4,     // 不支持
    HAL_IRQ_MODULE_CMP5,     // 不支持
    HAL_IRQ_MODULE_ADC2,     // 不支持
    HAL_IRQ_MODULE_QEP2,     // 不支持
    HAL_IRQ_MODULE_QEP3,     // 不支持
    HAL_IRQ_MODULE_FMAC0,    // 不支持
    HAL_IRQ_MODULE_WWDG0,    // 不支持
#endif
} HAL_IRQ_MODULE_x;

/**
 * @brief 中断函数名
 */
#define HAL_IRQHandler_TIMER0   TIMER0_IRQHandler
#define HAL_IRQHandler_TIMER1   TIMER1_IRQHandler
#define HAL_IRQHandler_TIMER2   TIMER2_IRQHandler
#define HAL_IRQHandler_TIMER3   TIMER3_IRQHandler
#define HAL_IRQHandler_MCPWM0   MCPWM0_IRQHandler
#define HAL_IRQHandler_MCPWM0_1 MCPWM1_IRQHandler
#define HAL_IRQHandler_I2C0     I2C0_IRQHandler
#define HAL_IRQHandler_SPI0     SPI0_IRQHandler
#define HAL_IRQHandler_GPIO0    GPIO_IRQHandler
#define HAL_IRQHandler_HALL0    HALL0_IRQHandler
#define HAL_IRQHandler_UART0    UART0_IRQHandler
#define HAL_IRQHandler_UART1    UART1_IRQHandler
#define HAL_IRQHandler_CMP0     CMP_IRQHandler
#define HAL_IRQHandler_ADC0     ADC0_IRQHandler
#define HAL_IRQHandler_ADC1     ADC1_IRQHandler
#define HAL_IRQHandler_WAKE0    WAKE_IRQHandler
#define HAL_IRQHandler_QEP0     QEP0_IRQHandler
#define HAL_IRQHandler_QEP1     QEP1_IRQHandler
#define HAL_IRQHandler_DSP0     DSP0_IRQHandler
#define HAL_IRQHandler_DMA0     DMA0_IRQHandler
#define HAL_IRQHandler_CAN0     CAN0_IRQHandler
#define HAL_IRQHandler_SIF0     SIF0_IRQHandler
#define HAL_IRQHandler_SW0      SW_IRQHandler
#define HAL_IRQHandler_PWRDN0   PWRDN_IRQHandler
#define HAL_IRQHandler_CL0      CL0_IRQHandler
#define HAL_IRQHandler_INIT0    PWRDN_IRQHandler

#ifdef HAL_TEST_NOT_SUPPORTED
#define HAL_IRQHandler_UART2    HAL_IRQHandler_UART2_Null    // 不支持
#define HAL_IRQHandler_CMP1     HAL_IRQHandler_CMP1_Null     // 不支持
#define HAL_IRQHandler_I2C1     HAL_IRQHandler_I2C1_Null     // 不支持
#define HAL_IRQHandler_HALL1    HAL_IRQHandler_HALL1_Null    // 不支持
#define HAL_IRQHandler_CMP2     HAL_IRQHandler_CMP2_Null     // 不支持
#define HAL_IRQHandler_CMP3     HAL_IRQHandler_CMP3_Null     // 不支持
#define HAL_IRQHandler_CMP4     HAL_IRQHandler_CMP4_Null     // 不支持
#define HAL_IRQHandler_CMP5     HAL_IRQHandler_CMP5_Null     // 不支持
#define HAL_IRQHandler_MCPWM1   HAL_IRQHandler_MCPWM1_Null   // 不支持
#define HAL_IRQHandler_MCPWM1_1 HAL_IRQHandler_MCPWM1_1_Null // 不支持
#define HAL_IRQHandler_TIMER4   HAL_IRQHandler_TIMER4_Null   // 不支持
#define HAL_IRQHandler_QEP2     HAL_IRQHandler_QEP2_Null     // 不支持
#define HAL_IRQHandler_QEP3     HAL_IRQHandler_QEP3_Null     // 不支持
#define HAL_IRQHandler_ADC2     HAL_IRQHandler_ADC2_Null     // 不支持
#define HAL_IRQHandler_SPI1     HAL_IRQHandler_SPI1_Null     // 不支持
#define HAL_IRQHandler_WWDG0    HAL_IRQHandler_WWDG0_Null    // 不支持
#define HAL_IRQHandler_FMAC0    HAL_IRQHandler_FMAC0_Null    // 不支持
#endif

void HAL_IRQ_Reset(void);   // 重置中断(等效于关闭中断)
void HAL_IRQ_Enable(void);  // 使能全局中断
void HAL_IRQ_Disable(void); // 关闭全局中断

void HAL_IRQ_ModuleEnable(HAL_IRQ_MODULE_x, uint8_t priority); // 使能某个模块的中断
void HAL_IRQ_ModuleDisable(HAL_IRQ_MODULE_x);                  // 关闭某个模块的中断

void HAL_IRQ_ModuleClear(HAL_IRQ_MODULE_x);
#endif
