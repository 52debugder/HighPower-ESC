#include "hardware_init.h"
#include "lks32mc07x_adc.h"
#include "lks32mc07x_can.h"
#include "lks32mc07x_gpio.h"
#include "lks32mc07x_mcpwm.h"
#include "lks32mc07x_sys.h"
#include "lks32mc07x_uart.h"

static volatile uint8_t g_esc_foc_loop_enabled = 0U;

static uint16_t esc_limit_pwm_duty(uint16_t duty)
{
    return (duty > ESC_PWM_PERIOD) ? ESC_PWM_PERIOD : duty;
}

void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;

    for (t_cnt = 0U; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }
}

void Clock_Init(void)
{
    SYS_WR_PROTECT = 0x7a83;
    SYS_SFT_RST = 0xffffffff;
    SYS_SFT_RST = 0U;
    SYS_AFE_REG6 = (SYS_AFE_REG6 & ~(0x3U << 8)) | (0x3U << 8);
    SYS_MclkChoice(SYS_MCLK_96M_XTAL);
    SoftDelay(100U);
    SYS_WR_PROTECT = 0U;
}

void SystemInit(void)
{
    Clock_Init();
}

void GPIO_init(void)
{
    GPIO_InitTypeDef gpio;

    SYS_ModuleClockCmd(SYS_Module_GPIO, ENABLE);

    GPIO_StructInit(&gpio);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_4, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_5, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_6, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_7, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_8, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_9, AF3_MCPWM);
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_Init(GPIO1, &gpio);

    GPIO_StructInit(&gpio);
    gpio.GPIO_Mode = GPIO_Mode_ANA;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Init(GPIO0, &gpio);
    gpio.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIO1, &gpio);
    gpio.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIO2, &gpio);

    GPIO_StructInit(&gpio);
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio.GPIO_Pin = DRV8353_EN_PIN;
    GPIO_Init(DRV8353_EN_GPIO, &gpio);
    GPIO_ResetBits(DRV8353_EN_GPIO, DRV8353_EN_PIN);

    gpio.GPIO_Pin = DRV8353_NSCS_PIN;
    GPIO_Init(DRV8353_NSCS_GPIO, &gpio);
    GPIO_SetBits(DRV8353_NSCS_GPIO, DRV8353_NSCS_PIN);

    gpio.GPIO_Pin = BOARD_LED_PIN;
    GPIO_Init(BOARD_LED_GPIO, &gpio);
    GPIO_ResetBits(BOARD_LED_GPIO, BOARD_LED_PIN);

    GPIO_StructInit(&gpio);
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    gpio.GPIO_Pin = DRV8353_NFAULT_PIN;
    GPIO_Init(DRV8353_NFAULT_GPIO, &gpio);

    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_9, AF5_SPI);
    GPIO_StructInit(&gpio);
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    gpio.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIO2, &gpio);

    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_10, AF5_SPI);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_1, AF5_SPI);
    GPIO_StructInit(&gpio);
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_1;
    GPIO_Init(GPIO2, &gpio);

    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_6, AF4_UART);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_7, AF4_UART);
    GPIO_StructInit(&gpio);
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    gpio.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIO0, &gpio);
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIO0, &gpio);

    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_12, AF10_CAN);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_13, AF10_CAN);
    GPIO_StructInit(&gpio);
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    gpio.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIO0, &gpio);
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIO0, &gpio);
}

void ADC0_init(void)
{
    ADC_InitTypeDef adc;

    ADC_StructInit(&adc);
    adc.RE = 0U;
    adc.DATA_ALIGN = DISABLE;
    adc.CSMP = DISABLE;
    adc.TCNT = 0U;
    adc.TROVS = DISABLE;
    adc.OVSR = 0U;
    adc.TRIG = ADC_TRIG_MCPWM0_T0;
    adc.NSMP = 0U;
    adc.IE = ADC_SF1_IE;
    adc.S1 = 7U;
    adc.S2 = 0U;
    adc.IS1 = 0U;
    adc.LTH = 0U;
    adc.HTH = 0U;
    adc.GEN = DISABLE;
    ADC_Init(ADC0, &adc);

    ADC_ClearIRQFlag(ADC0, ADC_ALL_IF);
    ADC_CHN_GAIN_CFG(ADC0, CHN0, ESC_ADC_CURRENT_U_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN1, ESC_ADC_CURRENT_V_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN2, ESC_ADC_CURRENT_W_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN3, ESC_ADC_CURRENT_V_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN4, ESC_ADC_BUS_VOLTAGE_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN5, ESC_ADC_BUS_CURRENT_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC0, CHN6, ESC_ADC_TEMP_CHANNEL, ADC_GAIN3V6);
    ADC0_CFG |= BIT11;
}

void ADC1_init(void)
{
    ADC_InitTypeDef adc;

    ADC_StructInit(&adc);
    adc.RE = 0U;
    adc.DATA_ALIGN = DISABLE;
    adc.CSMP = DISABLE;
    adc.TCNT = 0U;
    adc.TROVS = DISABLE;
    adc.OVSR = 0U;
    adc.TRIG = ADC_TRIG_MCPWM0_T0;
    adc.NSMP = 0U;
    adc.IE = 0U;
    adc.S1 = 4U;
    adc.S2 = 0U;
    adc.IS1 = 0U;
    adc.LTH = 0U;
    adc.HTH = 0U;
    adc.GEN = DISABLE;
    ADC_Init(ADC1, &adc);

    ADC_ClearIRQFlag(ADC1, ADC_ALL_IF);
    ADC_CHN_GAIN_CFG(ADC1, CHN0, ESC_ADC_BEMF_U_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC1, CHN1, ESC_ADC_BEMF_U_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC1, CHN2, ESC_ADC_BEMF_V_CHANNEL, ADC_GAIN3V6);
    ADC_CHN_GAIN_CFG(ADC1, CHN3, ESC_ADC_BEMF_W_CHANNEL, ADC_GAIN3V6);
    ADC1_CFG |= BIT11;
}

void MCPWM_init(void)
{
    MCPWM_InitTypeDef pwm;

    MCPWM_StructInit(&pwm);
    pwm.MCLK_EN = ENABLE;
    pwm.CLK_DIV = ESC_PWM_PRSC;
    pwm.IO_CMP_FLT_CLKDIV = 12U;
    pwm.AUEN = MCPWM0_ALL_AUPDAT;

    pwm.BASE_CNT0_EN = ENABLE;
    pwm.TH0 = ESC_PWM_PERIOD;
    pwm.TH00 = (u16)(-(s16)ESC_PWM_SAFE_DUTY);
    pwm.TH01 = ESC_PWM_SAFE_DUTY;
    pwm.TH10 = (u16)(-(s16)ESC_PWM_SAFE_DUTY);
    pwm.TH11 = ESC_PWM_SAFE_DUTY;
    pwm.TH20 = (u16)(-(s16)ESC_PWM_SAFE_DUTY);
    pwm.TH21 = ESC_PWM_SAFE_DUTY;
    pwm.MCPWM_WorkModeCH0 = MCPWM0_CENTRAL_PWM_MODE;
    pwm.MCPWM_WorkModeCH1 = MCPWM0_CENTRAL_PWM_MODE;
    pwm.MCPWM_WorkModeCH2 = MCPWM0_CENTRAL_PWM_MODE;
    pwm.DeadTimeCH012N = ESC_DEADTIME_TICKS;
    pwm.DeadTimeCH012P = ESC_DEADTIME_TICKS;

    pwm.CMP_CTRL_CNT0 = DISABLE;
    pwm.EVT_CNT0_EN = DISABLE;
    pwm.EVT0 = DISABLE;
    pwm.TR0_UP_INTV = DISABLE;
    pwm.TR0_T0_UpdateEN = ENABLE;
    pwm.TR0_T1_UpdateEN = DISABLE;
    pwm.TR0_AEC = DISABLE;
    pwm.T0_Update0_INT_EN = DISABLE;
    pwm.T1_Update0_INT_EN = DISABLE;
    pwm.Update0_INT_EN = DISABLE;
    pwm.TMR0 = (u16)(40U - ESC_PWM_PERIOD);
    pwm.TMR1 = (u16)(ESC_PWM_PERIOD - 1U);

    pwm.CH0N_Polarity_INV = ENABLE;
    pwm.CH0P_Polarity_INV = DISABLE;
    pwm.CH1N_Polarity_INV = ENABLE;
    pwm.CH1P_Polarity_INV = DISABLE;
    pwm.CH2N_Polarity_INV = ENABLE;
    pwm.CH2P_Polarity_INV = DISABLE;
    pwm.Switch_CH0N_CH0P = DISABLE;
    pwm.Switch_CH1N_CH1P = DISABLE;
    pwm.Switch_CH2N_CH2P = DISABLE;
    pwm.CH0P_default_output = MCPWM0_LOW_LEVEL;
    pwm.CH0N_default_output = MCPWM0_LOW_LEVEL;
    pwm.CH1P_default_output = MCPWM0_LOW_LEVEL;
    pwm.CH1N_default_output = MCPWM0_LOW_LEVEL;
    pwm.CH2P_default_output = MCPWM0_LOW_LEVEL;
    pwm.CH2N_default_output = MCPWM0_LOW_LEVEL;
    pwm.CH0N_FAIL_EN = ENABLE;
    pwm.CH0P_FAIL_EN = ENABLE;
    pwm.CH1N_FAIL_EN = ENABLE;
    pwm.CH1P_FAIL_EN = ENABLE;
    pwm.CH2N_FAIL_EN = ENABLE;
    pwm.CH2P_FAIL_EN = ENABLE;
    pwm.FAIL0_INPUT_EN = DISABLE;
    pwm.FAIL0_INT_EN = DISABLE;
    pwm.FAIL0_Signal_Sel = MCPWM0_FAIL_SEL_CMP;
    pwm.FAIL0_Polarity = MCPWM0_HIGH_LEVEL_ACTIVE;
    pwm.FAIL1_INPUT_EN = DISABLE;
    pwm.FAIL1_INT_EN = DISABLE;
    pwm.FAIL1_Signal_Sel = MCPWM0_FAIL_SEL_CMP;
    pwm.FAIL1_Polarity = MCPWM0_HIGH_LEVEL_ACTIVE;
    pwm.HALT_PRT0 = ENABLE;
    pwm.FAIL_0CAP = DISABLE;

    pwm.BASE_CNT1_EN = DISABLE;
    pwm.TH1 = ESC_PWM_PERIOD;

    MCPWM_Init(&pwm);
    ESC_PWM_Disable();
}

void UART1_init(void)
{
    UART_InitTypeDef uart;

    UART_StructInit(&uart);
    uart.BaudRate = 38400U;
    uart.WordLength = UART_WORDLENGTH_8b;
    uart.StopBits = UART_STOPBITS_1b;
    uart.FirstSend = UART_FIRSTSEND_LSB;
    uart.ParityMode = UART_Parity_NO;
    uart.IRQEna = 0U;
    UART_Init(UART1, &uart);
}

void CAN0_init(void)
{
    CAN_InitTypeDef can;

    CAN_StructInit(&can);
    can.SBaud = 500U;
    can.IE = 0U;
    can.ERRINT_IE = 0U;
    CAN_Init1(&can);
    IDx_Filter(0U, 0x00000000U, 0x1FFFFFFFU, IDEFilter_St_Ex);
}

void DMA_init(void)
{
    /* DMA is intentionally left idle for the first FOC bring-up. */
}

void Hardware_init(void)
{
    __disable_irq();
    SYS_WR_PROTECT = 0x7a83;
    SYS_DBG_CFG |= BIT14;
    FLASH_CFG |= 0x00080000;
    IWDG_DISABLE();

    GPIO_init();
    ADC0_init();
    ADC1_init();
    MCPWM_init();
    DMA_init();
    UART1_init();
    CAN0_init();
    ESC_PWM_Disable();
    ESC_FocLoopEnable(0U);
    SoftDelay(100U);

    NVIC_SetPriority(ADC0_IRQn, 1U);
    NVIC_SetPriority(ADC1_IRQn, 2U);
    NVIC_SetPriority(MCPWM0_IRQn, 1U);
    NVIC_EnableIRQ(ADC0_IRQn);
    NVIC_EnableIRQ(ADC1_IRQn);
    NVIC_EnableIRQ(MCPWM0_IRQn);
    SYS_WR_PROTECT = 0U;
}

void ESC_PWM_Enable(void)
{
    if (ESC_BoardFaultActive() != 0U)
    {
        PWMOutputs(DISABLE);
        return;
    }

    PWMOutputs(ENABLE);
}

void ESC_PWM_Disable(void)
{
    PWMOutputs(DISABLE);
}

void ESC_PWM_SetDuty(uint16_t duty_u, uint16_t duty_v, uint16_t duty_w)
{
    duty_u = esc_limit_pwm_duty(duty_u);
    duty_v = esc_limit_pwm_duty(duty_v);
    duty_w = esc_limit_pwm_duty(duty_w);

    MCPWM0_PRT = 0x0000DEADU;
    MCPWM0_TH00 = (s16)(-((s16)duty_u));
    MCPWM0_TH01 = duty_u;
    MCPWM0_TH10 = (s16)(-((s16)duty_v));
    MCPWM0_TH11 = duty_v;
    MCPWM0_TH20 = (s16)(-((s16)duty_w));
    MCPWM0_TH21 = duty_w;
    MCPWM0_UPDATE = 0xFFU;
    MCPWM0_PRT = 0U;
}

void ESC_PWM_SetSafeDuty(void)
{
    ESC_PWM_SetDuty(ESC_PWM_SAFE_DUTY, ESC_PWM_SAFE_DUTY, ESC_PWM_SAFE_DUTY);
}

void ESC_ADC_GetPhaseRaw(uint16_t *adc_u, uint16_t *adc_v, uint16_t *adc_w)
{
    if (adc_u != 0)
        *adc_u = (uint16_t)ADC0_DAT0;
    if (adc_v != 0)
        *adc_v = (uint16_t)ADC0_DAT1;
    if (adc_w != 0)
        *adc_w = (uint16_t)ADC0_DAT2;
}

uint16_t ESC_ADC_GetBusVoltageRaw(void)
{
    return (uint16_t)ADC0_DAT4;
}

uint16_t ESC_ADC_GetTempRaw(void)
{
    return (uint16_t)ADC0_DAT6;
}

uint8_t ESC_BoardFaultActive(void)
{
    if (GPIO_ReadInputDataBit(DRV8353_NFAULT_GPIO, DRV8353_NFAULT_PIN) == 0U)
        return 1U;

    if ((MCPWM0_EIF & (MCPWM_EIF_FAIL0 | MCPWM_EIF_FAIL1)) != 0U)
        return 1U;

    return 0U;
}

void ESC_FocLoopEnable(uint8_t enable)
{
    g_esc_foc_loop_enabled = (enable != 0U) ? 1U : 0U;
}

uint8_t ESC_FocLoopIsEnabled(void)
{
    return g_esc_foc_loop_enabled;
}
