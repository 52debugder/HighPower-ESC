/*******************************************************************************
 * ��Ȩ���� (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� hardware_init.c
 * �ļ���ʶ��
 * ����ժҪ�� Ӳ����ʼ������
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� HuangMG
 * ������ڣ� 2023��3��2��
 *
 *******************************************************************************/
#include "basic.h"
#include "hardware_config.h"
#include "MC_Parameter_M0.h"
#include "drv8353.h"


void UART_init(void);
void HALL_Perip_Init(void);
void SoftDelay(u32 cnt);
void TempSensor_Init(void);

void DAC_init(void);
void CMP_init(void);
void UTimer_init(void);
void GPIO_init(void);
void UART1_init(void);
void ADC0_init(void);
void ADC1_init(void);
void get_ic_temp_init(void);
void Clock_Init(void);
void Hardware_init(void);
void HALL_init(void);

extern void registerEPWM0_DrvLevel(void);
extern void registerEPWM1_DrvLevel(void);
extern void ADC_1Shunt_NormalModeCFG(void);
extern void ADC_2Shunt_NormalModeCFG(void);
extern void ADC_3Shunt_NormalModeCFG(void);

void PGA_init(void);
void MCPWM_ch012_init(void);
void MCPWM_ch345_init(void);

extern	PSTR_DrvCfgPara getCfgParaPtr(u8 objID);
extern	u16 getPWMPrd(PSTR_DrvCfgPara pDrvCfgPara);
extern	u16 getDeadTime(PSTR_DrvCfgPara pDrvCfgPara);

/*******************************************************************************
 �������ƣ�    void SoftDelay(void)
 ����������    ������ʱ����
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;

    for(t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }

}

/*******************************************************************************
 �������ƣ�    void Hardware_init(void)
 ����������    Ӳ�����ֳ�ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/3/2      V1.0          HuangMG            ����
 *******************************************************************************/
void Hardware_init(void)
{
	__disable_irq();					/* �ر��ж� �ж��ܿ��� */
	SYS_WR_PROTECT = 0x7a83;
	SYS_DBG_CFG |= BIT14;				/* ������λͨ�üĴ���*/
	
	FLASH_CFG |= 0x00080000;			/* enable prefetch */
    IWDG_DISABLE();						/* �رտ��Ź�*/

	// DSP_Init();							/* DSPģ���ʼ��*/
	// UART_init();						/* ���ڳ�ʼ��UART0*/
	ADC0_init();						/* ADC��ʼ�� */
	ADC1_init();						/* ADC��ʼ�� */
	GPIO_init();					  	/* GPIO��ʼ�� */	
	
	#if	(EPWM0_USED == FUNCTION_ON)
	MCPWM_ch012_init();					/* PWM��ʼ�� */
	#endif
	
	#if	(EPWM1_USED == FUNCTION_ON)
	MCPWM_ch345_init();					/* PWM��ʼ�� */
	#endif

	UTimer_init();						/* ͨ�ü�������ʼ�� */
	
	// DAC_init();							/* DAC ��ʼ�� */
	// PGA_init();							/* PGA ��ʼ�� */
	// CMP_init();							/* �Ƚ�����ʼ�� */
    // HALL_init();						/* HALLģ���ʼ�� */
	// TempSensor_Init();					/* �¶ȴ�������ʼ�� */
    SoftDelay(100);						/* �ȴ�Ӳ����ʼ�����*/

	//�ж����ȼ�����
    NVIC_SetPriority(TIMER0_IRQn, 2);	/*TIMER0�ж����ȼ�����*/
    NVIC_SetPriority(HALL0_IRQn, 2);	/*HALL0_IRQn�ж����ȼ�����*/
    NVIC_SetPriority(ADC0_IRQn, 1);		/*ADC0�ж����ȼ�����*/
	NVIC_SetPriority(ADC1_IRQn, 1); 	/*ADC0�ж����ȼ�����*/

    NVIC_SetPriority(MCPWM0_IRQn, 1);	/*MCPWM0�ж����ȼ�����*/

#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)	
	NVIC_EnableIRQ (MCPWM0_IRQn);		//�ж�ʹ������
#else
	NVIC_EnableIRQ(ADC0_IRQn);		  /* enable the ADC0 interrupt */
#endif

	//NVIC_EnableIRQ(ADC1_IRQn);
	NVIC_EnableIRQ (TIMER0_IRQn);
	
    SYS_WR_PROTECT = 0;               /* �ر�ϵͳ�Ĵ���д����*/
    DRV8353_Init();
    DRV8353_Enable();

    //__enable_irq();                   /* �������ж� */
}


/*******************************************************************************
 �������ƣ�    void Clock_Init(void)
 ����������    ʱ������
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/3/2      V1.0          HuangMG            ����
 *******************************************************************************/
void Clock_Init(void)
{
	SYS_WR_PROTECT = 0x7a83;		 /* ���ϵͳ�Ĵ���д���� */
	SYS_SFT_RST = 0xffffffff;	
	SYS_SFT_RST = 0;
	SYS_AFE_REG5 = BIT15;			 /* BIT15:PLLPDN ��PLL */
	SYS_AFE_REG6 &= ~0300;			 /* ����Ϊ4.0V��أ��ɸ���ʵ������������λ��3.25V/3.5V/3.75V/4.0V */
	while(SYS_AFE_DBG & BIT15) {;}	 /*  �ȴ��ⲿ5VOK */
	SoftDelay(100); 				 /* ��ʱ100us, �ȴ�PLL�ȶ� 21.4.17*/
	SYS_CLK_CFG = 0x000011ff;		 /* BIT8:0: CLK_HS,1:PLL  | BIT[7:0]CLK_DIV  | 1ff��Ӧ96Mʱ�� */
	SYS_WR_PROTECT = 0; 			 /* �ر�ϵͳ�Ĵ���д����*/
}

/*******************************************************************************
 �������ƣ�    void Reg_Clr(void)
 ����������    �Ĵ�������
 ���������    addr ����Ҫ����Ĵ�������ʼ��ַ 
               nSize����Ҫ����ļĴ�������
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/3/2      V1.0          HuangMG            ����
 *******************************************************************************/
void Reg_Clr(u32 addr, u8 nSize)
{
   while(nSize --)
   {
      REG32(addr) = 0;
      addr += 4;
   }
}


/*******************************************************************************
 �������ƣ�    void SystemInit(void)
 ����������    Ӳ��ϵͳ��ʼ��������ʱ�ӳ�ʼ������
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/3/2      V1.0          HuangMG            ����
 *******************************************************************************/
void SystemInit (void)
{
    Clock_Init();  /* ʱ�ӳ�ʼ�� */
}

/*******************************************************************************
 �������ƣ�    void PGA_init(void)
 ����������    �������ý���PGA��ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/1/15      V1.0           Li Tonghua          ����
 *******************************************************************************/
void PGA_init(void)
{
	u16 OPA_mode;
	PSTR_DrvCfgPara	pParaPtr;

	OPA_InitTypeDef OPA_InitStruct;
    OPA_StructInit(&OPA_InitStruct);

	pParaPtr	= getCfgParaPtr(0);
	OPA_mode	= pParaPtr->mS_GlobalCfg.m_bOPAValue;

	OPA_InitStruct.OPA_IT		= PGA_IT_1;			/*opaƫ�õ�������*/
    OPA_InitStruct.OPA_CLEna	= ENABLE;			/*ʹ��OPA*/
    //ѡ��160��10k����ӵ�������1k �Ŵ���160/12 = 13.3333
	OPA_InitStruct.OPA_Gain		= OPA_mode;
	
	OPA_Init(OPA0, &OPA_InitStruct);
	OPA_Init(OPA1, &OPA_InitStruct);
	OPA_Init(OPA2, &OPA_InitStruct);
	OPA_Init(OPA3, &OPA_InitStruct); 
}

/*******************************************************************************
 �������ƣ�    void CMP_init(void)
 ����������    CMP��ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
2023/02/22      V1.0           Olive Wang          ����
 *******************************************************************************/
void CMP_init(void)
{
    CMP_InitTypeDef CMP_InitStre;
    CMP_StructInit(&CMP_InitStre);

    //����ģ��ʱ��ʹ��
    SYS_ModuleClockCmd(SYS_Module_CMP, ENABLE);   //add


    CMP_InitStre.CLK_COM_DIV	= 0;					/* �Ƚ��������˲�ʱ�ӷ�Ƶ*/
    CMP_InitStre.FT				= DISABLE;				/* �Ƚ������ٱȽ� 30ns*/
    CMP_InitStre.HYS			= CMP_HYS_0mV; //CMP_HYS_20mV;	/* �Ƚ����ͻص�ѹ*/


    //CMP0 config
    CMP_InitStre.CMP0.SELP			= CMP0_SELP_IP1;			/* �Ƚ���0�����ź�ѡ�� */
    CMP_InitStre.CMP0.SELN			= CMP_SELN_REF; 			/* �Ƚ���0�����ź�ѡ�� */
    CMP_InitStre.CMP0.RE			= DISABLE;					/* �Ƚ���0DMAʧ��*/
    CMP_InitStre.CMP0.POL			= CMP_HIGH_LEVEL;			/* �Ƚ���0�ߵ�ƽ�����Ч*/
    CMP_InitStre.CMP0.IRQ_TRIG		= IRQ_LEVEL_TRIG_MODE;		/* �Ƚ���0��ƽ�����ж�ģʽ*/
    CMP_InitStre.CMP0.IN_EN			= DISABLE;					/* �Ƚ���0�ź�����ʹ�� */
    CMP_InitStre.CMP0.IE			= DISABLE;					/* �Ƚ���0�ź��ж�ʹ�� */
    CMP_InitStre.CMP0.FIL_CLK_DIV16 = 2; 						/* ���˲�����=tclk ����*16*CMP_FltCnt (CMP_FltCnt��Ƶϵ��,0~15)*/
    CMP_InitStre.CMP0.FIL_CLK_DIV2	= 2;  						/* �Ƚ��� 2/1/0 �˲�ʱ��ʹ�� */
    CMP_InitStre.CMP0.CLK_EN		= DISABLE;					/* �Ƚ���ʱ��ʹ��*/
    CMP_InitStre.CMP0.EN			= DISABLE;					/* �Ƚ���0���� ����SYS_AFE_REG5 */

    //CMP1 config
    CMP_InitStre.CMP1.SELP			= CMP1_SELP_IP0;			/* �Ƚ���1�����ź�ѡ�� */
    CMP_InitStre.CMP1.SELN			= CMP_SELN_DAC0;			/* �Ƚ���1�����ź�ѡ�� */
    CMP_InitStre.CMP0.RE			= DISABLE;					/* �Ƚ���1DMAʧ��*/
    CMP_InitStre.CMP1.POL			= CMP_HIGH_LEVEL;			/* �Ƚ���1�ߵ�ƽ�����Ч*/
    CMP_InitStre.CMP1.IRQ_TRIG		= IRQ_LEVEL_TRIG_MODE;		/* �Ƚ���1��ƽ�����ж�ģʽ*/
    CMP_InitStre.CMP1.IN_EN			= DISABLE;					/* �Ƚ���1�ź�����ʹ�� */
    CMP_InitStre.CMP1.IE			= DISABLE;					/* �Ƚ���1�ź��ж�ʹ�� */
    CMP_InitStre.CMP1.FIL_CLK_DIV16	= 2; 						/* ���˲�����=tclk ����*16*CMP_FltCnt (CMP_FltCnt��Ƶϵ��,0~15)*/
    CMP_InitStre.CMP1.FIL_CLK_DIV2	= 2;  						/* �Ƚ��� 2/1/0 �˲�ʱ��ʹ�� */
    CMP_InitStre.CMP1.CLK_EN		= ENABLE;					/* �Ƚ���ʱ��ʹ��*/
    CMP_InitStre.CMP1.EN			= ENABLE;					/* �Ƚ���0���� ����SYS_AFE_REG5 */

    CMP_Init(&CMP_InitStre);									/* �Ƚ�����ʼ�� */
    //CMP_Cmd(CMP_CHN_0, ENABLE); /* �Ƚ���0ʱ��ʹ��*/
    CMP_Cmd(CMP_CHN_1, ENABLE); /* �Ƚ���1ʱ��ʹ��*/
}

/*******************************************************************************
 �������ƣ�    void DAC_init(void)
 ����������    DAC��ʼ��(ͨ������ͬʱ��� DAC0 �� DAC1����������źž�����)
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
2023/02/22      V1.0           Olive Wang          ����
 *******************************************************************************/
void DAC_init(void)
{
	s16 nDACRef;
	s32 wDACCmp;
	PSTR_DrvCfgPara	pParaPtr;

	DAC_InitTypeDef DAC_InitStre;
    DAC_StructInit(&DAC_InitStre);				/* DAC�ṹ���ʼ�� */
	
	//Ĭ�� epwm0 ----- dac0
	//˫����������ù���

	pParaPtr	= getCfgParaPtr(0);
	wDACCmp	= (s32)pParaPtr->mS_FBCurSense.nHardOvCurVolt;	

	DAC_InitStre.DAC_GAIN = DAC_RANGE_1V2;		/*DAC�������Ϊ1.20V*/
    DAC_InitStre.DACOUT_EN = DISABLE;			/*ʹ��DAC���*/
    DAC_InitStre.TIG_CH_EN = DISABLE;			/*�Ƿ�ʹ��UTIMER��������*/
    DAC_InitStre.DAC_STEP = 0;					/*����ֵΪ0*/
    DAC_Init(DAC_Channel_0, &DAC_InitStre);		/* DAC��ʼ�� */
  
    if(DAC_InitStre.DAC_GAIN 		== DAC_RANGE_1V2)
    {/* ����DAC 1.2V����У��ֵ */
		nDACRef			= 1200;
    }   
    else if(DAC_InitStre.DAC_GAIN	== DAC_RANGE_4V85)
    { /* ����DAC 4.85V����У��ֵ */
		nDACRef			= 4850;
	}

	wDACCmp		= (wDACCmp * 4096)/nDACRef;
	wDACCmp		= sat(wDACCmp,0,4095);

	//����DAC����ֵ
    DAC_OutputValue(DAC_Channel_0, wDACCmp) ;	/* ����ĸ�߲���������㱣��ֵ*/

    DAC_Cmd(DAC_Channel_0, ENABLE);				/*ʹ��DACʱ��*/
}

/*******************************************************************************
 �������ƣ�    void UART_init(void)
 ����������    UART0�Ĵ�������
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void UART_init(void)
{

    UART_InitTypeDef UART_InitStruct;

    UART_StructInit(&UART_InitStruct);
    UART_InitStruct.BaudRate = 115200;                 /* ���ò�����38400 */
    UART_InitStruct.WordLength = UART_WORDLENGTH_8b;  /* �������ݳ���8λ */
    UART_InitStruct.StopBits = UART_STOPBITS_1b;
    UART_InitStruct.FirstSend = UART_FIRSTSEND_LSB;   /* �ȷ���LSB */
    UART_InitStruct.ParityMode = UART_Parity_NO;      /* ����żУ�� */
    UART_InitStruct.IRQEna = UART_IF_RcvOver;
    UART_Init(UART0, &UART_InitStruct);

}

/*******************************************************************************
 �������ƣ�    void UART0_SENDDATA(void)
 ����������    UART0���ͳ���
 ���������    n����Ҫ���͵�ֵ
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void UART0_SENDDATA(UINT8 n)
{
    UART0_BUFF = n;
}

/*******************************************************************************
 �������ƣ�    void UART0_init(void)
 ����������    UART1�Ĵ�������
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void UART1_init(void)
{
    UART_InitTypeDef UART_InitStruct;
    
    UART_StructInit(&UART_InitStruct);
    UART_InitStruct.BaudRate = 38400;                 /* ���ò�����38400 */
    UART_InitStruct.WordLength = UART_WORDLENGTH_8b;  /* �������ݳ���8λ */
    UART_InitStruct.StopBits = UART_STOPBITS_1b;
    UART_InitStruct.FirstSend = UART_FIRSTSEND_LSB;   /* �ȷ���LSB */
    UART_InitStruct.ParityMode = UART_Parity_NO;      /* ����żУ�� */
    UART_InitStruct.IRQEna = 0;
    UART_Init(UART1, &UART_InitStruct);
}


/*******************************************************************************
 �������ƣ�    void UART1_SENDDATA(void)
 ����������    UART1���ͳ���
 ���������    n����Ҫ���͵�ֵ
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void UART1_SENDDATA(UINT8 n)
{
    UART1_BUFF = n;
}

/*******************************************************************************
 �������ƣ�    void ADC0_init(void)
 ����������    ADC0Ӳ����ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void ADC0_init(void)
{
    ADC_InitTypeDef ADC_InitStructure;

    //ADC0����
    ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.RE         = 0;                   // DMA����ʹ��
    ADC_InitStructure.DATA_ALIGN = DISABLE;             // DAT�Ҷ���ʹ��
    ADC_InitStructure.CSMP       = DISABLE;             // ��������ʹ��
    ADC_InitStructure.TCNT       = 0;                   // ����һ�β���������¼��� 0����ʾ��Ҫ���� 1 ���¼����ܴ���һ�β���  8KHZ
    //                          1����ʾ��Ҫ���� 2 ���¼����ܴ���һ�β���  16KHZ
    ADC_InitStructure.TROVS      = DISABLE;             // �ֶ�����������ʹ�ܣ�������һ�β�����Ҫ��δ���
    ADC_InitStructure.OVSR       = 0;                   // ��������

#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    ADC_InitStructure.TRIG       = ADC_TRIG_MCPWM0_T0 | ADC_TRIG_MCPWM0_T1; // �Ƚϵ�t0 ,t1�����ź�
    ADC_InitStructure.NSMP       = 1;                    // 0:���β����� 1:���β���
    ADC_InitStructure.IE         = 0;                    // �ڶ��γ����������ж�ʹ��  ��ʹ��ADC0

    ADC_InitStructure.S1         = 2;                   // ��һ�γ���������� 2
    ADC_InitStructure.S2         = 4;                   // �ڶ��γ���������� 4
    ADC_InitStructure.IS1        = 0;                   // ���в�������

#else
#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
    ADC_InitStructure.TRIG       = ADC_TRIG_MCPWM0_T0;  // �����ź�
    ADC_InitStructure.NSMP       = 0;                    // 0:���β����� 1:���β���
    ADC_InitStructure.IE		 = ADC_SF1_IE;         // ��һ�γ����������ж�ʹ��
    ADC_InitStructure.S1         = 6;                   // ��һ�γ����������
    ADC_InitStructure.S2         = 0;                   // �ڶ��γ����������
    ADC_InitStructure.IS1        = 0;                   // ���в�������

#else
#if ((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
    ADC_InitStructure.TRIG       = ADC_TRIG_MCPWM0_T0;  // �����ź�
    ADC_InitStructure.NSMP       = 0;                    // 0:���β����� 1:���β���
    ADC_InitStructure.IE          = ADC_SF1_IE;          // ��һ�γ����������ж�ʹ��
    ADC_InitStructure.S1         = 7;                   // ��һ�γ����������
    ADC_InitStructure.S2         = 0;                   // �ڶ��γ����������
    ADC_InitStructure.IS1        = 0;                   // ���в�������
#endif
#endif
#endif
    ADC_InitStructure.LTH        = 0;                   // ADC ģ�⿴�Ź� 0 ����ֵ
    ADC_InitStructure.HTH        = 0;                   // ADC ģ�⿴�Ź� 0 ����ֵ
    ADC_InitStructure.GEN        = DISABLE;             // ADC ģ�⿴�Ź� 0 ��Ӧʹ��λ
    ADC_Init(ADC0, &ADC_InitStructure);

    ADC_ClearIRQFlag(ADC0, ADC_ALL_IF);//��������жϱ�־λ
	

    #if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    ADC_1Shunt_NormalModeCFG();
	#elif (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
	ADC_2Shunt_NormalModeCFG();
	#elif ((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET)) 
	ADC_3Shunt_NormalModeCFG();
	#endif

    ADC0_STATE_RESET();  //��λһ��
}

/*******************************************************************************
 �������ƣ�    void ADC0_init(void)
 ����������    ADC0Ӳ����ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void ADC1_init(void)
{
    ADC_InitTypeDef ADC_InitStructure;

    //ADC0����
    ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.RE         = 0;                   // DMA����ʹ��
    ADC_InitStructure.DATA_ALIGN = DISABLE;              // DAT�Ҷ���ʹ��
    ADC_InitStructure.CSMP       = DISABLE;             // ��������ʹ��
    ADC_InitStructure.TCNT       = 0;                   // ����һ�β���������¼��� 0����ʾ��Ҫ���� 1 ���¼����ܴ���һ�β���  8KHZ
    //                          							1����ʾ��Ҫ���� 2 ���¼����ܴ���һ�β���  16KHZ
    ADC_InitStructure.TROVS      = DISABLE;             // �ֶ�����������ʹ�ܣ�������һ�β�����Ҫ��δ���
    ADC_InitStructure.OVSR       = 0;                   // ��������
	

    ADC_InitStructure.TRIG       = ADC_TRIG_MCPWM0_T0;  // �����ź�
    ADC_InitStructure.NSMP       = 0;                    // 0:���β����� 1:���β���
    ADC_InitStructure.IE         = ADC_SF1_IE;			// ��һ�γ����������ж�ʹ��
    ADC_InitStructure.S1         = 4;                   // ��һ�γ����������
    ADC_InitStructure.S2         = 0;                   // �ڶ��γ����������
    ADC_InitStructure.IS1        = 0;                   // ���в�������

    ADC_InitStructure.LTH        = 0;                   // ADC ģ�⿴�Ź� 0 ����ֵ
    ADC_InitStructure.HTH        = 0;                   // ADC ģ�⿴�Ź� 0 ����ֵ
    ADC_InitStructure.GEN        = DISABLE;             // ADC ģ�⿴�Ź� 0 ��Ӧʹ��λ
    ADC_Init(ADC1, &ADC_InitStructure);
	
    ADC_ClearIRQFlag(ADC1, ADC_ALL_IF);
	

    #if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
    ADC_1Shunt_NormalModeCFG();
	#elif (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
	ADC_2Shunt_NormalModeCFG();
	#elif ((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET)) 
	ADC_3Shunt_NormalModeCFG();
	#endif

    ADC1_STATE_RESET();  //��λһ��
}
/*******************************************************************************
 �������ƣ�    void HALL_init(void)
 ����������    HALL��ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
2023/02/22      V1.0           Olive Wang          ����
 *******************************************************************************/
void HALL_init(void)
{
    HALL_InitTypeDef HALL_InitStruct;

    HALL_StructInit(&HALL_InitStruct);

    HALL_InitStruct.FilterLen = 512;                /* Hall�ź������˲����� 512��ʱ������ */
    HALL_InitStruct.ClockDivision = HALL_CLK_DIV1;  /* ����Hallģ��ʱ�ӷ�Ƶϵ�� */
    HALL_InitStruct.Filter75_Ena = DISABLE;         /* Hall�ź��˲���ʽ��7��5ģʽ����ȫ1��Чģʽ */
    HALL_InitStruct.HALL_Ena = ENABLE;              /* ģ��ʹ�� */

    HALL_InitStruct.Capture_IRQ_Ena = ENABLE;		/* ��׽�ж�ʹ�� */
    HALL_InitStruct.OverFlow_IRQ_Ena = ENABLE;		/* ��ʱ�ж�ʹ�� */
    HALL_InitStruct.softIE = DISABLE;               /* �����ж�ʧ�� */

    HALL_InitStruct.CountTH = 9600000;				/* Hallģ�����ģֵ����������ģֵ�������ʱ�ж� */

    HALL_Init(&HALL_InitStruct);/* HALL���� */
    HALL_Cmd(ENABLE);/* HALLʹ�� */
}

/*******************************************************************************
 �������ƣ�    void GPIO_init(void)
 ����������    GPIOӲ����ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/3/2      V1.0          HuangMG            ����
 *******************************************************************************/
void GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct);

	/*���� MCPWM   ch0~ch2 P1.4~P1.9 */
	#if	(EPWM0_USED == FUNCTION_ON)
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_4, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_5, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_6, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_7, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_8, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_9, AF3_MCPWM);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_Init(GPIO1, &GPIO_InitStruct);
	#endif

	/*���� MCPWM  ch3~ch5 */
	
    /* ADC���룺�¶�P0.0��A/B/C�����P0.3/P0.4/P0.5��ĸ�ߵ�ѹP1.3 */
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_ANA;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIO1, &GPIO_InitStruct);

    /* DRV8353S�弶�������ţ��ϵ�Ĭ�Ϲر�������ƬѡĬ������ */
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Pin = DRV8353_EN_PIN;
    GPIO_Init(DRV8353_EN_GPIO, &GPIO_InitStruct);
    GPIO_ResetBits(DRV8353_EN_GPIO, DRV8353_EN_PIN);

    GPIO_InitStruct.GPIO_Pin = DRV8353_NSCS_PIN;
    GPIO_Init(DRV8353_NSCS_GPIO, &GPIO_InitStruct);
    GPIO_SetBits(DRV8353_NSCS_GPIO, DRV8353_NSCS_PIN);

    GPIO_InitStruct.GPIO_Pin = BOARD_LED_PIN;
    GPIO_Init(BOARD_LED_GPIO, &GPIO_InitStruct);
    GPIO_ResetBits(BOARD_LED_GPIO, BOARD_LED_PIN);

    /* nFAULTΪ����Ч��©�źţ��ڲ������������ⲿ����ʱ�Ļ������� */
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Pin = DRV8353_NFAULT_PIN;
    GPIO_Init(DRV8353_NFAULT_GPIO, &GPIO_InitStruct);

    /* DRV8353S SPI��P2.9=SDO/SPI_DI��P2.10=SDI/SPI_DO��P2.1=SCLK��nSCS�ֶ�GPIO���� */
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_9, AF5_SPI);
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIO2, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_10, AF5_SPI);
    GPIO_PinAFConfig(GPIO2, GPIO_PinSource_1, AF5_SPI);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_1;
    GPIO_Init(GPIO2, &GPIO_InitStruct);

    /* UART1��P0.6=RX��P0.7=TX */
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_6, AF4_UART);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_7, AF4_UART);
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    /* CAN��P0.12=RXD��P0.13=TXD������ֻ�������ţ������ʳ�ʼ�����浥���� */
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_12, AF10_CAN);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_13, AF10_CAN);
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIO0, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIO0, &GPIO_InitStruct);

    /* �ⲿPWM���룺P2.11�ӱȽ���2��������1����ģ�����뱣�� */
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_ANA;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIO2, &GPIO_InitStruct);
	#if	(EPWM1_USED == FUNCTION_ON)
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_10, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO1, GPIO_PinSource_11, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_3, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_4, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_5, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_6, AF3_MCPWM);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 ;
    GPIO_Init(GPIO1, &GPIO_InitStruct);
		
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 ;
	GPIO_Init(GPIO0, &GPIO_InitStruct);
	#endif

//	//����P2.7 UTIMER0_CH0
//	GPIO_StructInit(&GPIO_InitStruct); //��ʼ���ṹ��
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; //GPIO���ģʽ
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
//	GPIO_Init(GPIO2, &GPIO_InitStruct);
//	GPIO_PinAFConfig(GPIO2, GPIO_PinSource_7, AF7_TIMER01); //P2.7����Ϊtimer0�����ģʽ



//	/* P1.10-RX0, P1.11-TX0  UART0 */
//	GPIO_StructInit(&GPIO_InitStruct);
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_10 ;
//	GPIO_Init(GPIO1, &GPIO_InitStruct);

//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_11;
//	GPIO_Init(GPIO1, &GPIO_InitStruct);

//	GPIO_PinAFConfig(GPIO1, GPIO_PinSource_10, AF4_UART);
//	GPIO_PinAFConfig(GPIO1, GPIO_PinSource_11, AF4_UART);


//	GPIO_StructInit(&GPIO_InitStruct);
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_8 ;
//	GPIO_Init(GPIO2, &GPIO_InitStruct);

//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_9;
//	GPIO_Init(GPIO3, &GPIO_InitStruct);

//	GPIO_PinAFConfig(GPIO2, GPIO_PinSource_8, AF4_UART);
//	GPIO_PinAFConfig(GPIO3, GPIO_PinSource_9, AF4_UART);

//	/* P0.6-LED1  P0.7-LED2*/
//	GPIO_StructInit(&GPIO_InitStruct);
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 ;
//	GPIO_Init(GPIO0, &GPIO_InitStruct);

//	/* P0.15-RX0, P1.0-TX0  UART0 */
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_0;//RX0
//	GPIO_Init(GPIO1, &GPIO_InitStruct);

//	/* P0.15-RX0, P1.0-TX0  UART0 */
//	GPIO_PinAFConfig(GPIO0, GPIO_PinSource_15, AF4_UART);
//	GPIO_PinAFConfig(GPIO1, GPIO_PinSource_0, AF4_UART);

//	/*UART1 IO�ڳ�ʼ��*/
//	GPIO_StructInit(&GPIO_InitStruct);
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_8 ;//RX1
//	GPIO_Init(GPIO2, &GPIO_InitStruct);

//	GPIO_StructInit(&GPIO_InitStruct);
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_9 ;//TX1
//	GPIO_Init(GPIO3, &GPIO_InitStruct);
//	GPIO_PinAFConfig(GPIO2, GPIO_PinSource_8, AF4_UART);
//	GPIO_PinAFConfig(GPIO3, GPIO_PinSource_9, AF4_UART);

//	#if (ROTOR_SENSOR_TYPE == ROTOR_HALL_SENSOR) 
//	GPIO_StructInit(&GPIO_InitStruct);
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
//	GPIO_Init(GPIO2, &GPIO_InitStruct);
//	GPIO_PinAFConfig(GPIO2, GPIO_PinSource_4, AF2_HALL);
//	GPIO_PinAFConfig(GPIO2, GPIO_PinSource_5, AF2_HALL);
//	GPIO_PinAFConfig(GPIO2, GPIO_PinSource_6, AF2_HALL);
//	#endif

//	/* PWMռ�ձȵ��ټ�� */
//	GPIO_StructInit(&GPIO_InitStruct);
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_8 ;
//	GPIO_Init(GPIO2, &GPIO_InitStruct);
//	GPIO_PinAFConfig(GPIO2, GPIO_PinSource_8, AF8_TIMER23);		
}

/*******************************************************************************
 �������ƣ�    void UTimer_init(void)
 ����������    UTimerӲ����ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/3/2      V1.0          HuangMG            ����
 *******************************************************************************/
void UTimer_init(void)
{
    TIM_TimerInitTypeDef TIM_InitStruct;

    TIM_TimerStrutInit(&TIM_InitStruct);                  /* Timer�ṹ���ʼ��*/
    TIM_InitStruct.Timer_CH0_WorkMode = TIMER_OPMode_CMP; /* ����Timer CH0 Ϊ�Ƚ�ģʽ */
    TIM_InitStruct.Timer_CH0Output = 0;                   /* ����������ʱ���Ƚ�ģʽ������Կ��� */
    TIM_InitStruct.Timer_CH1_WorkMode = TIMER_OPMode_CMP; /* ����Timer CH1 Ϊ�Ƚ�ģʽ */
    TIM_InitStruct.Timer_CH1Output = 0;                   /* ����������ʱ���Ƚ�ģʽ������Կ��� */
    TIM_InitStruct.Timer_TH = 48000;    									/* ��ʱ���������޳�ʼֵ48000*/
    TIM_InitStruct.Timer_CMP0 = 24000;  									/* ���ñȽ�ģʽ��CH0�Ƚϳ�ʼֵ24000 */
    TIM_InitStruct.Timer_CMP1 = 24000;  									/* ���ñȽ�ģʽ��CH1�Ƚϳ�ʼֵ24000 */
    TIM_InitStruct.Timer_FLT = 0;  										    /* ���ò�׽ģʽ�������ģʽ�¶�Ӧͨ���������˲�ֵ */
    TIM_InitStruct.Timer_ClockDiv = TIMER_CLK_DIV1;       /* ����Timerģ��ʱ��2��Ƶϵ�� */
    TIM_InitStruct.Timer_IRQEna = Timer_IRQEna_ZC;		  /* ����Timerģ��Ƚ��жϺ͹����ж� Timer_IRQEna_CH0 | Timer_IRQEna_CH1 | */
    TIM_TimerInit(UTIMER0, &TIM_InitStruct);
    TIM_TimerCmd(UTIMER0, ENABLE);                        /* Timer0 ģ��ʹ�� */

}

/*******************************************************************************
 �������ƣ�    void MCPWM_ch012_init(void)
 ����������    MCPWM��ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/11/5      V1.0           Li Tonghua          ����
 *******************************************************************************/
#if	(EPWM0_USED == FUNCTION_ON)
void MCPWM_ch012_init(void)
{
    MCPWM_InitTypeDef MCPWM_InitStructure;

	u16 prd;
	u16 deadTime;
	u8  clockDiv;
	PSTR_DrvCfgPara	pParaPtr;

	pParaPtr	= getCfgParaPtr(0);
	prd			= getPWMPrd(pParaPtr);
	deadTime	= getDeadTime(pParaPtr);
	clockDiv	= pParaPtr->mS_GlobalCfg.m_nuPWMPrsc & 0x03;


    MCPWM_StructInit(&MCPWM_InitStructure);

    MCPWM_InitStructure.CLK_DIV = clockDiv;				/* MCPWMʱ�ӷ�Ƶ���� */
    MCPWM_InitStructure.MCLK_EN = ENABLE;				/* ģ��ʱ�ӿ��� */
	MCPWM_InitStructure.IO_FLT_CLKDIV  = 12;			/* ��ͣ�¼�(����IO���ź�)�����˲���ʱ������ */
	MCPWM_InitStructure.CMP_FLT_CLKDIV = 12;			/* ��ͣ�¼�(���ԱȽ����ź�)�����˲���ʱ������ */

	MCPWM_InitStructure.AUEN = MCPWM0_ALL_AUPDAT;		/*�Զ�����ʹ��*/

	/* MCPWM0_CNT0	 ��һ��PWM����*/

	MCPWM_InitStructure.BASE_CNT0_EN	= ENABLE;		/* ����������ʼ����ʹ�ܿ��� */
	MCPWM_InitStructure.TH0				= prd;			/* �����������ü�MCPWM�������*/

	MCPWM_InitStructure.MCPWM_WorkModeCH0 = MCPWM0_CENTRAL_PWM_MODE; /* MCPWM CH0����ģʽ�����Ķ���PWMģʽ */
	MCPWM_InitStructure.MCPWM_WorkModeCH1 = MCPWM0_CENTRAL_PWM_MODE; /* ͨ������ģʽ���ã����Ķ������ض��� */
	MCPWM_InitStructure.MCPWM_WorkModeCH2 = MCPWM0_CENTRAL_PWM_MODE;
	MCPWM_InitStructure.DeadTimeCH012N = deadTime;		/* ����ʱ������ */
	MCPWM_InitStructure.DeadTimeCH012P = deadTime;	

	MCPWM_InitStructure.CMP_CTRL_CNT0  = DISABLE ;		/* CMP����CNT0����ʹ��λ */
	MCPWM_InitStructure.EVT_CNT0_EN    = DISABLE ; 		/* MCPWM_CNT1�ⲿ����ʹ��λ */
	MCPWM_InitStructure.EVT0		   = DISABLE ;		/* �ⲿ���� */

	MCPWM_InitStructure.TR0_UP_INTV 	= DISABLE;
	MCPWM_InitStructure.TR0_T0_UpdateEN = DISABLE ;		/*T0ʱ�̸���ʹ��*/
	MCPWM_InitStructure.TR0_T1_UpdateEN = ENABLE ;
	MCPWM_InitStructure.TR0_AEC 		= DISABLE;		/*�Զ����MCPWM0_EIF��־λ*/

	MCPWM_InitStructure.TMR0 = (u16)(40 - prd);			/* MCPWM_TMR0  ���ò����� */
	MCPWM_InitStructure.TMR1 = (u16)(prd - 1);			/* MCPWM_TMR1 ���� */
 

#if (PRE_DRIVER_POLARITY == P_HIGH__N_LOW)                    /* CHxP ����Ч�� CHxN�͵�ƽ��Ч */
    MCPWM_InitStructure.CH0N_Polarity_INV = ENABLE;           /* CH0Nͨ������������� | ���������ȡ�����*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE;          /* CH0Pͨ������������� | ���������ȡ����� */
    MCPWM_InitStructure.CH1N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P =  DISABLE;           /* ͨ������ѡ������ | CH0P��CH0N�Ƿ�ѡ���źŽ��� */
    MCPWM_InitStructure.Switch_CH1N_CH1P =  DISABLE;           /* ͨ������ѡ������ */
    MCPWM_InitStructure.Switch_CH2N_CH2P =  DISABLE;           /* ͨ������ѡ������ */

    /* Ĭ�ϵ�ƽ���� Ĭ�ϵ�ƽ�������MCPWM_IO01��MCPWM_IO23�� BIT0��BIT1��BIT8��BIT9��BIT6��BIT14
                                                     ͨ�������ͼ��Կ��Ƶ�Ӱ�죬ֱ�ӿ���ͨ����� */
    MCPWM_InitStructure.CH0P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = MCPWM0_HIGH_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = MCPWM0_LOW_LEVEL;      /* CH1P��Ӧ�����ڿ���״̬����͵�ƽ */
    MCPWM_InitStructure.CH1N_default_output = MCPWM0_HIGH_LEVEL;     /* CH1N��Ӧ�����ڿ���״̬����ߵ�ƽ */
    MCPWM_InitStructure.CH2P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = MCPWM0_HIGH_LEVEL;
	#else
#if (PRE_DRIVER_POLARITY == P_HIGH__N_HIGH)                    /* CHxP ����Ч�� CHxN�ߵ�ƽ��Ч */
    MCPWM_InitStructure.CH0N_Polarity_INV = DISABLE;           /* CH0Nͨ������������� | ���������ȡ�����*/
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE;          /* CH0Pͨ������������� | ���������ȡ����� */
    MCPWM_InitStructure.CH1N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P = DISABLE;           /* ͨ������ѡ������ | CH0P��CH0N�Ƿ�ѡ���źŽ��� */
    MCPWM_InitStructure.Switch_CH1N_CH1P = DISABLE;           /* ͨ������ѡ������ */
    MCPWM_InitStructure.Switch_CH2N_CH2P = DISABLE;           /* ͨ������ѡ������ */

    /* Ĭ�ϵ�ƽ���� Ĭ�ϵ�ƽ�������MCPWM_IO01��MCPWM_IO23�� BIT0��BIT1��BIT8��BIT9��BIT6��BIT14
                                                     ͨ�������ͼ��Կ��Ƶ�Ӱ�죬ֱ�ӿ���ͨ����� */
    MCPWM_InitStructure.CH0P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = MCPWM0_LOW_LEVEL;      /* CH1P��Ӧ�����ڿ���״̬����͵�ƽ */
    MCPWM_InitStructure.CH1N_default_output = MCPWM0_LOW_LEVEL;     /* CH1N��Ӧ�����ڿ���״̬����ߵ�ƽ */
    MCPWM_InitStructure.CH2P_default_output = MCPWM0_LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = MCPWM0_LOW_LEVEL;
#endif
	#endif

	
#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
			MCPWM_InitStructure.T0_Update0_INT_EN = DISABLE;   /* T0�����¼� �ж�ʹ��λ */
			MCPWM_InitStructure.T1_Update0_INT_EN = ENABLE ;   /* T1�����¼� �ж�ʹ��λ*/
			MCPWM_InitStructure.Update0_INT_EN = DISABLE;	   /* CNT0 �����¼� �ж�ʹ��  */
#else
#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
			MCPWM_InitStructure.T0_Update0_INT_EN = DISABLE;   /* T0�����¼� �ж�ʹ��λ */
			MCPWM_InitStructure.T1_Update0_INT_EN = DISABLE ;  /* T1�����¼� �ж�ʹ��λ*/
			MCPWM_InitStructure.Update0_INT_EN = DISABLE;	   /* CNT0�����¼��ж�ʹ��	˫���費ʹ��PWM�ж�  */
#else
#if ((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
			MCPWM_InitStructure.T0_Update0_INT_EN = DISABLE;   /* T0�����¼� �ж�ʹ��λ */
			MCPWM_InitStructure.T1_Update0_INT_EN = DISABLE ;  /* T1�����¼� �ж�ʹ��λ*/
			MCPWM_InitStructure.Update0_INT_EN = DISABLE;	   /* CNT0 �����¼� �ж�ʹ��  ˫���費ʹ��PWM�ж�  */
#endif
#endif
#endif

	MCPWM_InitStructure.CH0N_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH0P_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH1N_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH1P_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH2N_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH2P_FAIL_EN = ENABLE ;


	MCPWM_InitStructure.FAIL0_INPUT_EN	 = DISABLE ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL0_INT_EN	 = DISABLE;
	MCPWM_InitStructure.FAIL0_Signal_Sel = MCPWM0_FAIL_SEL_CMP ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL0_Polarity	 = MCPWM0_HIGH_LEVEL_ACTIVE ;

	MCPWM_InitStructure.FAIL1_INPUT_EN	 = ENABLE ;//FAIL_1CAP����CAP1
	MCPWM_InitStructure.FAIL1_INT_EN	 = DISABLE;//fail�ж�
	MCPWM_InitStructure.FAIL1_Signal_Sel = MCPWM0_FAIL_SEL_CMP ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL1_Polarity	 = MCPWM0_HIGH_LEVEL_ACTIVE ;

	
	MCPWM_InitStructure.HALT_PRT0		 = ENABLE ;   /* �ڽ��Ϸ�����debug����ʱ����ͣMCU����ʱ��ѡ���PWMͨ��������������ź�
																	 �������Ĭ�ϵ�ƽ�������������� ENABLE:������� DISABLE:���Ĭ�ϵ�ƽ*/
	MCPWM_InitStructure.FAIL_0CAP		 = ENABLE ;   //FAIL01�¼�����ʱ ��MCPWM0_CNT0ֵ����MCPWM0_FCNT ʹ��

	
    MCPWM_Init(&MCPWM_InitStructure);
	
	registerEPWM0_DrvLevel();
}
#endif

/*******************************************************************************
 �������ƣ�    void MCPWM_ch345_init(void)
 ����������    MCPWM��ʼ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2023/11/5      V1.0           Li Tonghua          ����
 *******************************************************************************/
#if	(EPWM1_USED == FUNCTION_ON)
void MCPWM_ch345_init(void)
{
    MCPWM_InitTypeDef MCPWM_InitStructure;

	u16 prd;
	u16 deadTime;
	u8  clockDiv;
	PSTR_DrvCfgPara	pParaPtr;


	pParaPtr	= getCfgParaPtr(0);
	prd			= getPWMPrd(pParaPtr);
	deadTime	= getDeadTime(pParaPtr);
	clockDiv	= pParaPtr->mS_GlobalCfg.m_nuPWMPrsc & 0x03;


	MCPWM_StructInit(&MCPWM_InitStructure);

    MCPWM_InitStructure.CLK_DIV = clockDiv;				/* MCPWMʱ�ӷ�Ƶ���� */
    MCPWM_InitStructure.MCLK_EN = ENABLE;				/* ģ��ʱ�ӿ��� */
	MCPWM_InitStructure.IO_FLT_CLKDIV  = 12;			/* ��ͣ�¼�(����IO���ź�)�����˲���ʱ������ */
	MCPWM_InitStructure.CMP_FLT_CLKDIV = 12;			/* ��ͣ�¼�(���ԱȽ����ź�)�����˲���ʱ������ */

	MCPWM_InitStructure.AUEN = MCPWM0_ALL_AUPDAT;		/*�Զ�����ʹ��*/


/* MCPWM0_CNT1	 �ڶ���PWM����*/	

	/* MCPWM0_CNT1 */
	MCPWM_InitStructure.BASE_CNT1_EN = DISABLE;				  /* ����������ʼ����ʹ�ܿ��� */
	MCPWM_InitStructure.TH1 = prd;			  /* �����������ü�MCPWM�������*/

	MCPWM_InitStructure.MCPWM_WorkModeCH3 = MCPWM0_CENTRAL_PWM_MODE; /* MCPWM CH0����ģʽ�����Ķ���PWMģʽ */
	MCPWM_InitStructure.MCPWM_WorkModeCH4 = MCPWM0_CENTRAL_PWM_MODE; /* ͨ������ģʽ���ã����Ķ������ض��� */
	MCPWM_InitStructure.MCPWM_WorkModeCH5 = MCPWM0_CENTRAL_PWM_MODE;

	MCPWM_InitStructure.DeadTimeCH345N = deadTime;
	MCPWM_InitStructure.DeadTimeCH345P = deadTime;

	MCPWM_InitStructure.CMP_CTRL_CNT1  = DISABLE ;		/* CMP����CNT0����ʹ��λ */
	MCPWM_InitStructure.EVT_CNT1_EN    = DISABLE ; 		/* MCPWM_CNT1�ⲿ����ʹ��λ */
	MCPWM_InitStructure.EVT1		   = DISABLE ;		/* �ⲿ���� */	

	MCPWM_InitStructure.TR1_UP_INTV 	= DISABLE;
	MCPWM_InitStructure.TR1_T0_UpdateEN = ENABLE ;		/*T0ʱ�̸���ʹ��*/
	MCPWM_InitStructure.TR1_T1_UpdateEN = DISABLE ;
	MCPWM_InitStructure.TR1_AEC 		= DISABLE;		/*T0ʱ�̸���ʹ��*/

	MCPWM_InitStructure.TMR2 = (u16)(40 - prd);			/* MCPWM_TMR2  ���� */
	MCPWM_InitStructure.TMR3 = (u16)(prd - 1);			/* MCPWM_TMR3  ���� */

#if (PRE_DRIVER_POLARITY == P_HIGH__N_LOW)					/* CHxP ����Ч�� CHxN�͵�ƽ��Ч */
	MCPWM_InitStructure.CH3N_Polarity_INV = ENABLE; 		  /* CH0Nͨ������������� | ���������ȡ�����*/
	MCPWM_InitStructure.CH3P_Polarity_INV = DISABLE;		  /* CH0Pͨ������������� | ���������ȡ����� */
	MCPWM_InitStructure.CH4N_Polarity_INV = ENABLE;
	MCPWM_InitStructure.CH4P_Polarity_INV = DISABLE;
	MCPWM_InitStructure.CH5N_Polarity_INV = ENABLE;
	MCPWM_InitStructure.CH5P_Polarity_INV = DISABLE;

	MCPWM_InitStructure.Switch_CH3N_CH3P =	DISABLE;		   /* ͨ������ѡ������ | CH0P��CH0N�Ƿ�ѡ���źŽ��� */
	MCPWM_InitStructure.Switch_CH4N_CH4P =	DISABLE;		   /* ͨ������ѡ������ */
	MCPWM_InitStructure.Switch_CH5N_CH5P =	DISABLE;		   /* ͨ������ѡ������ */

	/* Ĭ�ϵ�ƽ���� Ĭ�ϵ�ƽ�������MCPWM_IO01��MCPWM_IO23�� BIT0��BIT1��BIT8��BIT9��BIT6��BIT14
													 ͨ�������ͼ��Կ��Ƶ�Ӱ�죬ֱ�ӿ���ͨ����� */
	MCPWM_InitStructure.CH3P_default_output = MCPWM0_LOW_LEVEL;
	MCPWM_InitStructure.CH3N_default_output = MCPWM0_HIGH_LEVEL;
	MCPWM_InitStructure.CH4P_default_output = MCPWM0_LOW_LEVEL; 	 /* CH1P��Ӧ�����ڿ���״̬����͵�ƽ */
	MCPWM_InitStructure.CH4N_default_output = MCPWM0_HIGH_LEVEL;	 /* CH1N��Ӧ�����ڿ���״̬����ߵ�ƽ */
	MCPWM_InitStructure.CH5P_default_output = MCPWM0_LOW_LEVEL;
	MCPWM_InitStructure.CH5N_default_output = MCPWM0_HIGH_LEVEL;
#else
#if (PRE_DRIVER_POLARITY == P_HIGH__N_HIGH)                    /* CHxP ����Ч�� CHxN�ߵ�ƽ��Ч */
	MCPWM_InitStructure.CH3N_Polarity_INV = DISABLE;		   /* CH0Nͨ������������� | ���������ȡ�����*/
	MCPWM_InitStructure.CH3P_Polarity_INV = DISABLE;		  /* CH0Pͨ������������� | ���������ȡ����� */
	MCPWM_InitStructure.CH4N_Polarity_INV = DISABLE;
	MCPWM_InitStructure.CH4P_Polarity_INV = DISABLE;
	MCPWM_InitStructure.CH5N_Polarity_INV = DISABLE;
	MCPWM_InitStructure.CH5P_Polarity_INV = DISABLE;

	MCPWM_InitStructure.Switch_CH3N_CH3P =	DISABLE;		   /* ͨ������ѡ������ | CH0P��CH0N�Ƿ�ѡ���źŽ��� */
	MCPWM_InitStructure.Switch_CH4N_CH4P =	DISABLE;		   /* ͨ������ѡ������ */
	MCPWM_InitStructure.Switch_CH5N_CH5P =	DISABLE;		   /* ͨ������ѡ������ */

	/* Ĭ�ϵ�ƽ���� Ĭ�ϵ�ƽ�������MCPWM_IO01��MCPWM_IO23�� BIT0��BIT1��BIT8��BIT9��BIT6��BIT14
													 ͨ�������ͼ��Կ��Ƶ�Ӱ�죬ֱ�ӿ���ͨ����� */
	MCPWM_InitStructure.CH3P_default_output = MCPWM0_LOW_LEVEL;
	MCPWM_InitStructure.CH3N_default_output = MCPWM0_LOW_LEVEL;
	MCPWM_InitStructure.CH4P_default_output = MCPWM0_LOW_LEVEL; 	 /* CH1P��Ӧ�����ڿ���״̬����͵�ƽ */
	MCPWM_InitStructure.CH4N_default_output = MCPWM0_LOW_LEVEL; 	  /* CH1N��Ӧ�����ڿ���״̬����ߵ�ƽ */
	MCPWM_InitStructure.CH5P_default_output = MCPWM0_LOW_LEVEL;
	MCPWM_InitStructure.CH5N_default_output = MCPWM0_LOW_LEVEL;
#endif
#endif

#if (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
	MCPWM_InitStructure.T2_Update1_INT_EN = DISABLE;   /* T0�����¼� �ж�ʹ��λ */
	MCPWM_InitStructure.T1_Update1_INT_EN = ENABLE ;   /* T1�����¼� �ж�ʹ��λ*/
	MCPWM_InitStructure.Update1_INT_EN = DISABLE;	   /* CNT0 �����¼� �ж�ʹ��  */
#elif (EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
	MCPWM_InitStructure.T0_Update1_INT_EN = DISABLE;   /* T0�����¼� �ж�ʹ��λ */
	MCPWM_InitStructure.T1_Update1_INT_EN = DISABLE ;  /* T1�����¼� �ж�ʹ��λ*/
	MCPWM_InitStructure.Update0_INT_EN = DISABLE;	   /* CNT0�����¼��ж�ʹ��	˫���費ʹ��PWM�ж�  */
#elif ((EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(EPWM0_CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
	MCPWM_InitStructure.T0_Update1_INT_EN = DISABLE;   /* T0�����¼� �ж�ʹ��λ */
	MCPWM_InitStructure.T1_Update1_INT_EN = DISABLE ;  /* T1�����¼� �ж�ʹ��λ*/
	MCPWM_InitStructure.Update1_INT_EN = DISABLE;	   /* CNT0 �����¼� �ж�ʹ��  ˫���費ʹ��PWM�ж�  */
#endif

	MCPWM_InitStructure.CH3N_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH3P_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH4N_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH4P_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH5N_FAIL_EN = ENABLE ;
	MCPWM_InitStructure.CH5P_FAIL_EN = ENABLE ;

	MCPWM_InitStructure.FAIL2_INPUT_EN		= DISABLE ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL2_INT_EN		= DISABLE;
	MCPWM_InitStructure.FAIL2_Signal_Sel	= MCPWM0_FAIL_SEL_CMP ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL2_Polarity		= MCPWM0_HIGH_LEVEL_ACTIVE ;

	MCPWM_InitStructure.FAIL3_INPUT_EN		= DISABLE ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL3_INT_EN		= DISABLE;
	MCPWM_InitStructure.FAIL3_Signal_Sel	= MCPWM0_FAIL_SEL_CMP ;//FAIL_0CAP
	MCPWM_InitStructure.FAIL3_Polarity		= MCPWM0_HIGH_LEVEL_ACTIVE ;

	MCPWM_InitStructure.HALT_PRT1			= DISABLE ;
	MCPWM_InitStructure.FAIL_1CAP			= DISABLE ;
	
	//TMR2 TMR3ѡ��ʱ������ʱ��0����1���Ƚ���������ϳ�ԭ�����Ķ�ʽ����
	MCPWM_InitStructure.TMR2_TB 	   = 0;/* MCPWM TMR2ʱ������������ѡ�� 0��ʱ��0��1��ʱ��1 */
	MCPWM_InitStructure.TMR3_TB 	   = 0;/* MCPWM TMR3ʱ������������ѡ�� 0��ʱ��0��1��ʱ��1 */
	
    MCPWM_Init(&MCPWM_InitStructure);
	
	registerEPWM1_DrvLevel();
}
#endif
/*******************************************************************************
 �������ƣ�    void DebugPWM_OutputFunction(void)
 ����������    PWM������ܵ���   ���25%ռ�ձ�
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2017/11/5      V1.0           Howlet Li          ����
 *******************************************************************************/
void DebugPWM_OutputFunction(void)
{
    MCPWM0_TH00 = (s16)(-(PWM_PERIOD_M0 >> 2));
    MCPWM0_TH01 = (PWM_PERIOD_M0 >> 2);
    MCPWM0_TH10 = (s16)(-(PWM_PERIOD_M0 >> 2));
    MCPWM0_TH11 = (PWM_PERIOD_M0 >> 2);
    MCPWM0_TH20 = (s16)(-(PWM_PERIOD_M0 >> 2));
    MCPWM0_TH21 = (PWM_PERIOD_M0 >> 2);

    PWMOutputs(ENABLE);
    while(1)
    {
    }
}


