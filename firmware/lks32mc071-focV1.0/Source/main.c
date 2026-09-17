#include "hardware_init.h"
#include "drv8353.h"
#include "foc.h"
#include "foc_hal.h"

volatile uint32_t g_main_idle_count = 0U;
uint32_t cnt;

int main(void)
{
    __disable_irq();
    Hardware_init();

    (void)Foc_Init(ESC_MOTOR_ID, &foc_hal);
    if (g_drv8353_config_status == DRV8353_CONFIG_OK)
    {
        ESC_FocLoopEnable(1U);
    }
    else
    {
        ESC_PWM_Disable();
        ESC_FocLoopEnable(0U);
    }
    
    __enable_irq();

    for (;;)
    {
        cnt++;
        if(cnt < 20000)
        {
            GPIO_SetBits(BOARD_LED_GPIO, BOARD_LED_PIN);
        }
        else if(cnt < 40000)
        {
            GPIO_ResetBits(BOARD_LED_GPIO, BOARD_LED_PIN);
        }
        else 
        {
            cnt = 0;
        }
//        ADC_SoftTrgEN(ADC0, ENABLE); // 向 ADC0_SWT 写入 0x5AA5，触发一次第一段扫描
        
        g_main_idle_count++;
        if (ESC_BoardFaultActive() != 0U)
        {
            ESC_FocLoopEnable(0U);
            ESC_PWM_Disable();
            //DRV8353_Disable();
        }
    }
}