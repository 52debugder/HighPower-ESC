#include "hardware_init.h"
#include "drv8323.h"
#include "foc.h"
#include "foc_hal.h"

volatile uint32_t g_main_idle_count = 0U;
uint32_t cnt;

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
//        ADC_SoftTrgEN(ADC0, ENABLE); // �� ADC0_SWT д�� 0x5AA5������һ�ε�һ��ɨ��
        UART_SendData(UART1, 0x12); // 发送数据
        
        g_main_idle_count++;
        Foc_Set_Speed(1, 300);
        SoftDelay(10);
        if (ESC_BoardFaultActive() != 0U)
        {
            ESC_FocLoopEnable(0U);
            ESC_PWM_Disable();
            DRV8323_Disable();
        }
    }
}