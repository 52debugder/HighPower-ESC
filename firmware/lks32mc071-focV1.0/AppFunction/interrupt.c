#include "hardware_init.h"
#include "foc.h"

volatile uint32_t g_adc0_irq_count = 0U;
volatile uint32_t g_adc1_irq_count = 0U;
volatile uint32_t g_mcpwm0_irq_count = 0U;
volatile uint32_t g_fault_irq_count = 0U;

void ADC0_IRQHandler(void)
{
    if(ADC_GetIRQFlag(ADC0,ADC_SF1_IF))
	{
	    ADC_ClearIRQFlag(ADC0,ADC_SF1_IF);
        g_adc0_irq_count++;

        if (ESC_FocLoopIsEnabled() != 0U)
        {
            if (ESC_BoardFaultActive() == 0U)
            {
                GPIO_SetBits(BOARD_LED_GPIO, BOARD_LED_PIN);
                foc_handle_t *foc_motor = Foc_GetStruct(1);
                if (foc_motor->init_done == 1U)
                    foc_motor->hal.adc_get_value(1, &foc_motor->i_adc_u, &foc_motor->i_adc_v, &foc_motor->i_adc_w);
                Foc_Loop(1);
                GPIO_ResetBits(BOARD_LED_GPIO, BOARD_LED_PIN);
            }
            else
            {
                ESC_FocLoopEnable(0U);
                ESC_PWM_Disable();
            }
        }
	}
	else
	{
	    ADC_ClearIRQFlag(ADC0,ADC_ALL_IF);
	}
}

void ADC1_IRQHandler(void)
{
    ADC1_IF = ADC_ALL_IF;
    g_adc1_irq_count++;
}

void MCPWM0_IRQHandler(void)
{
    g_mcpwm0_irq_count++;
    if(MCPWM_GetIRQFlag(MCPWM0CNT0,MCPWM0CNT0_T1_IRQ_IF))
		{
			 //MCPWN0INTCnt ++;
			 MCPWM_ClearIRQFlag(MCPWM0CNT0,MCPWM0CNT0_T1_IRQ_IF);
		}
		if(MCPWM_GetIRQFlag(MCPWM0CNT0,MCPWM0_FAIL1_IRQ_IF))
		{
			 //MCPWN0INTCnt1 ++;
			 MCPWM_ClearIRQFlag(MCPWM0CNT0,MCPWM0_FAIL1_IRQ_IF);
		}
}

void HALL0_IRQHandler(void)
{
    HALL->INFO = HALL->INFO;
}

void TIMER0_IRQHandler(void)
{
    UTIMER0_IF = BIT2;
}

void TIMER1_IRQHandler(void)
{
}

void TIMER2_IRQHandler(void)
{
}

void TIMER3_IRQHandler(void)
{
}

void QEP0_IRQHandler(void)
{
}

void QEP1_IRQHandler(void)
{
}

void CMP_IRQHandler(void)
{
    CMP_IF = BIT0 | BIT1;
    ESC_FocLoopEnable(0U);
    ESC_PWM_Disable();
}

void UART0_IRQHandler(void)
{
}

void UART1_IRQHandler(void)
{
    UART1_IF = UART1_IF;
}

void SysTick_Handler(void)
{
}

void WAKE_IRQHandler(void)
{
    while (1)
    {
    }
}

void GPIO_IRQHandler(void)
{
}

void I2C0_IRQHandler(void)
{
}

void SPI0_IRQHandler(void)
{
    SPI0_IE = SPI_IF_TranDone | SPI_IF_SSErr | SPI_IF_DataOver;
}

void CAN0_IRQHandler(void)
{
    CAN_RTIF = 0xFFU;
    CAN_ERRINT = CAN_ERRINT;
}

void DSP0_IRQHandler(void)
{
}

void MCPWM1_IRQHandler(void)
{
}

void SIF0_IRQHandler(void)
{
}

void SW_IRQHandler(void)
{
}

void PWRDN_IRQHandler(void)
{
}

void CL0_IRQHandler(void)
{
}
