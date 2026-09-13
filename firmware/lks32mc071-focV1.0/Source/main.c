#include "hardware_init.h"
#include "drv8353.h"
#include "foc.h"
#include "foc_hal.h"

volatile uint32_t g_main_idle_count = 0U;

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
        GPIO_SetBits(BOARD_LED_GPIO, BOARD_LED_PIN);
        g_main_idle_count++;
        if (ESC_BoardFaultActive() != 0U)
        {
            ESC_FocLoopEnable(0U);
            ESC_PWM_Disable();
            DRV8353_Disable();
        }
    }
}