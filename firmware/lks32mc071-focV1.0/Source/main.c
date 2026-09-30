#include "hardware_init.h"
#include "drv8323.h"
#include "foc.h"
#include "foc_hal.h"
#include "VOFA.h"

volatile uint32_t g_main_idle_count = 0U;
uint32_t cnt;
volatile uint32_t baud;

int main(void)
{
    //__disable_irq();
    Hardware_init();
    //PWMOutputs(ENABLE);

    Foc_Init(ESC_MOTOR_ID, &foc_hal);
    if (g_drv8323_config_status == DRV8323_CONFIG_OK)
    {
        ESC_FocLoopEnable(1U);
    }
    else
    {
        ESC_PWM_Disable();
        ESC_FocLoopEnable(0U);
    }
    
    //__enable_irq();

    for (;;)
    {
    //    cnt = cnt + 1;
    //    if(cnt < 10000)
    //    {
    //        GPIO_SetBits(BOARD_LED_GPIO, BOARD_LED_PIN);
    //    }
    //    else if(cnt < 20000)
    //    {
    //        GPIO_ResetBits(BOARD_LED_GPIO, BOARD_LED_PIN);
    //    }
    //    else 
    //    {
    //        cnt = 0;
    //    }
        // foc_handle_t *foc_motor = Foc_GetStruct(1);
        // Print3_Motor_To_VOFA(foc_motor->i_adc_u, foc_motor->i_adc_v, foc_motor->i_adc_w);
        UART_SendData(UART1, 0x01);
        
        //baud = SYS_ReadMcuClk() / (SYS_CLK_DIV2 + 1) / (1 + 256 * UART1->DIVH + UART1->DIVL);
        
        g_main_idle_count++;
        Foc_Set_Speed(1, 300);
        if (ESC_BoardFaultActive() != 0U)
        {
            ESC_FocLoopEnable(0U);
            ESC_PWM_Disable();
            DRV8323_Disable();
        }
    }
}