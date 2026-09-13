
#ifndef __HAL_LKS32MC07X_REG_H__
#define __HAL_LKS32MC07X_REG_H__
#define HAL_LKS32MC07X_REG

#ifndef HAL_TEST_REG
#include "lks32mc07x.h"
#endif

#define HAL_MCPWM_STATE_SW_BIT              BIT0                                                   // 通道交换使能 0 交换 1 交换
#define HAL_MCPWM_STATE_H_MOS_EN_BIT        BIT1                                                   // 上管有效电平 0 上管低有效 1 上管高有效
#define HAL_MCPWM_STATE_L_MOS_EN_BIT        BIT2                                                   // 下管有效电平 0 下管低有效 1 下管高有效
#define HAL_MCPWM_STATE_H_DEFAULT_BIT       BIT3                                                   // 默认上管电平 0 关机后上管关闭 1 关机后上管打开
#define HAL_MCPWM_STATE_L_DEFAULT_BIT       BIT4                                                   // 默认下管电平 0 关机后下管关闭 1 关机后下管打开
#define HAL_MCPWM_STATE_STATE_MAX           ((uint32_t)0x7)                                        // HAL_MCPWM_STATE_STATE最大值
#define HAL_MCPWM_STATE_STATE_POS           5                                                      // HAL_MCPWM_STATE_STATE起始位
#define HAL_MCPWM_STATE_STATE_MASK          (uint32_t)((uint32_t)0x7 << HAL_MCPWM_STATE_STATE_POS) // HAL_MCPWM_STATE_STATE位掩码
#define HAL_MCPWM_STATE_STATE(x)            (uint32_t)(((x) & 0x7) << HAL_MCPWM_STATE_STATE_POS)   // 默认输出状态 枚举

#define HAL_ADC_TRIG_STATE_ADC0_EN          BIT0 // bit0 adc0使能
#define HAL_ADC_TRIG_STATE_ADC1_EN          BIT1 // bit1 adc1使能
#define HAL_ADC_TRIG_STATE_MCPWM_TRIG_EN    BIT2 // bit2 mcpwm触发
#define HAL_ADC_TRIG_STATE_MCPWM0_1_TRIG_EN BIT3 // bit3 mcpwm0_1触发
#define HAL_ADC_TRIG_STATE_TIMER0_TRIG_EN   BIT4 // bit4 timer0触发
#define HAL_ADC_TRIG_STATE_TIMER2_TRIG_EN   BIT5 // bit5 timer2触发
#define HAL_ADC_TRIG_STATE_TWO_SEG_TRIG_EN  BIT6 // bit6 两段式触发使能

/**
 * @brief SYS寄存器定义
 */
typedef struct
{
    volatile uint32_t ADC;      // 0x00
    volatile uint32_t INFO;     // 0x04
    volatile uint32_t DBG;      // 0x08
    volatile uint32_t null0;    // 0x0C
    volatile uint32_t REG0;     // 0x10
    volatile uint32_t REG1;     // 0x14
    volatile uint32_t REG2;     // 0x18
    volatile uint32_t REG3;     // 0x1C
    volatile uint32_t REG4;     // 0x20
    volatile uint32_t REG5;     // 0x24
    volatile uint32_t REG6;     // 0x28
    volatile uint32_t REG7;     // 0x2C
    volatile uint32_t REG8;     // 0x30
    volatile uint32_t REG9;     // 0x34
    volatile uint32_t REGA;     // 0x38
    volatile uint32_t REGB;     // 0x3C
    volatile uint32_t REGC;     // 0x40
    volatile uint32_t null1;    // 0x44
    volatile uint32_t null2;    // 0x48
    volatile uint32_t null3;    // 0x4C
    volatile uint32_t null4;    // 0x50
    volatile uint32_t null5;    // 0x54
    volatile uint32_t null6;    // 0x58
    volatile uint32_t DAC_CTRL; // 0x5C
    volatile uint32_t DAC0;     // 0x60
    volatile uint32_t DAC1;     // 0x64
    volatile uint32_t DAC0_AMC; // 0x68
    volatile uint32_t DAC0_DC;  // 0x6C
    volatile uint32_t DAC1_AMC; // 0x70
    volatile uint32_t DAC1_DC;  // 0x74

    volatile uint32_t null7; // 0x78
    volatile uint32_t null8; // 0x7C

    volatile uint32_t CLK_CFG;    // 0x80
    volatile uint32_t IO_CFG;     // 0x84
    volatile uint32_t DBG_CFG;    // 0x88
    volatile uint32_t null9;      // 0x8c
    volatile uint32_t CLK_DIV0;   // 0x90 I2C clock div
    volatile uint32_t CLK_DIV1;   // 0x94 保留
    volatile uint32_t CLK_DIV2;   // 0x98 UART0/1 clock div
    volatile uint32_t CLK_FEN;    // 0x9C perapheral clock enable
    volatile uint32_t TRIM;       // 0xA0
    volatile uint32_t SFT_RST;    // 0xA4
    volatile uint32_t WR_PROTECT; // 0xA8
    volatile uint32_t MBIST;      // 0xC0
    volatile uint32_t null10;     // 0xc4
    volatile uint32_t null11;     // 0xc8
    volatile uint32_t null12;     // 0xcc
    volatile uint32_t FLSE;       // 0xD0
    volatile uint32_t FLSP;       // 0xD4
    volatile uint32_t FLST;       // 0xD8
    volatile uint32_t null13;     // 0xDc
    volatile uint32_t SBIST;      // 0xE0
} HAL_SYS_TypeDef;

/**
 * @brief FLASH寄存器定义
 */
typedef struct
{
    volatile uint32_t CFG;     ///< 0x00 FLASH配置寄存器
    volatile uint32_t ADDR;    ///< 0x04 地址寄存器
    volatile uint32_t WDATA;   ///< 0x08 写数据寄存器
    volatile uint32_t RDATA;   ///< 0x0C 读数据寄存器
    volatile uint32_t ERASE;   ///< 0x10 擦除控制寄存器
    volatile uint32_t PROTECT; ///< 0x14 FLASH保护状态寄存器
    volatile uint32_t READY;   ///< 0x18 FLASH工作状态寄存器
    volatile uint32_t SIZE;    ///< 0x1C FLASH容量状态寄存器
    volatile uint32_t NCFG;    ///< 0x20 FLASH配置寄存器（保护状态下，针对NVR操作）
    volatile uint32_t NADDR;   ///< 0x24 地址寄存器（保护状态下，针对NVR操作）
    volatile uint32_t NWDATA;  ///< 0x28 写数据寄存器（保护状态下，针对NVR操作）
    volatile uint32_t NRDATA;  ///< 0x2C 读数据寄存器（保护状态下，针对NVR操作）
    volatile uint32_t NERASE;  ///< 0x30 擦除控制寄存器（保护状态下，针对NVR操作）
    volatile uint32_t NKEY;    ///< 0x34 FLASH密钥寄存器（保护状态下，针对NVR操作）
} HAL_FLASH_TypeDef;
/**
 * @brief SPI寄存器定义
 */
typedef struct
{
    volatile uint32_t CFG;    ///< 0x00 配置寄存器
    volatile uint32_t IE;     ///< 0x04 中断寄存器
    volatile uint32_t BAUD;   ///< 0x08 波特率寄存器
    volatile uint32_t TXDATA; ///< 0x0C 发送数据寄存器
    volatile uint32_t RXDATA; ///< 0x10 接收数据寄存器
    volatile uint32_t SIZE;   ///< 0x14 传输数据长度寄存器
} HAL_SPI_TypeDef;

/**
 * @brief I2C寄存器定义
 */
typedef struct
{
    volatile uint32_t ADDR;  ///< 0x00 I2C 地址寄存器
    volatile uint32_t CFG;   ///< 0x04 I2C 配置寄存器
    volatile uint32_t SCR;   ///< 0x08 I2C 状态寄存器
    volatile uint32_t DATA;  ///< 0x0C I2C 数据寄存器
    volatile uint32_t MSCR;  ///< 0x10 I2C 主模式寄存器
    volatile uint32_t BCR;   ///< 0x14 I2C 传输控制寄存器
    volatile uint32_t BSIZE; ///< 0x18 I2C 传输长度寄存器
} HAL_I2C_TypeDef;

/**
 * @brief CMP寄存器定义
 */
typedef struct
{
    volatile uint32_t IE;     ///< 0x00 中断使能寄存器
    volatile uint32_t IF;     ///< 0x04 中断标志寄存器
    volatile uint32_t TCLK;   ///< 0x08 时钟分频控制寄存器
    volatile uint32_t CFG;    ///< 0x0C 配置寄存器
    volatile uint32_t BLCWIN; ///< 0x10 黑窗口控制寄存器
    volatile uint32_t DATA;   ///< 0x14 数据寄存器
} HAL_CMP_TypeDef;

/**
 * @brief HALL寄存器定义
 */
typedef struct
{
    volatile uint32_t CFG;   ///< 0x00 配置寄存器
    volatile uint32_t INFO;  ///< 0x04 信息寄存器
    volatile uint32_t WIDTH; ///< 0x08 宽度寄存器
    volatile uint32_t TH;    ///< 0x0C 阈值寄存器
    volatile uint32_t CNT;   ///< 0x10 计数寄存器
} HAL_HALL_TypeDef;

/**
 * @brief ADC0寄存器定义
 */
typedef struct
{
    volatile uint32_t DAT[14];   ///< 第 0 次常规采样数据
    volatile uint32_t IDAT[2];   ///< 第 0 次空闲采样数据
    volatile uint32_t ICHN;      ///< 空闲采样通道配置
    volatile uint32_t null[3];   ///< 地址对齐,无意义
    volatile uint32_t CHN0;      ///< 第 0~ 3 次常规采样输入信号选择
    volatile uint32_t CHN1;      ///< 第 4~ 7 次常规采样输入信号选择
    volatile uint32_t CHN2;      ///< 第 8~11 次常规采样输入信号选择
    volatile uint32_t CHN3;      ///< 第 12~13 次常规采样输入信号选择
    volatile uint32_t CHNT;      ///< 各种触发模式下采样次数
    volatile uint32_t GAIN;      ///< 增益选择
    volatile uint32_t null2[3];  ///< 地址对齐,无意义
    volatile uint32_t CFG;       ///< 模式配置
    volatile uint32_t TRIG;      ///< 采样触发配置
    volatile uint32_t SWT;       ///< 软件触发
    volatile uint32_t DC0;       ///< 增益为 0 时 DC offset
    volatile uint32_t AMC0;      ///< 增益为 0 时增益校正系数
    volatile uint32_t DC1;       ///< 增益为 1 时 DC offset
    volatile uint32_t AMC1;      ///< 增益为 1 时增益校正系数
    volatile uint32_t IE;        ///< 中断使能
    volatile uint32_t IF;        ///< 中断标志
    volatile uint32_t null3[11]; ///< 地址对齐,无意义
    volatile uint32_t LTH;       ///< 数据低阈值
    volatile uint32_t HTH;       ///< 数据高阈值
    volatile uint32_t GEN;       ///< 阈值监测使能
} HAL_ADC_TypeDef;

/**
 * @brief TIMER寄存器定义
 */
typedef struct
{
    volatile uint32_t CFG;  ///< 定时器配置寄存器
    volatile uint32_t TH;   ///< 定时器计数门限寄存器
    volatile uint32_t CNT;  ///< 定时器计数值寄存器
    volatile uint32_t CMP0; ///< 定时器比较/捕获寄存器 0
    volatile uint32_t CMP1; ///< 定时器比较/捕获寄存器 1
    volatile uint32_t EVT;  ///< 定时器外部事件选择寄存器
    volatile uint32_t FLT;  ///< 定时器滤波控制寄存器
    volatile uint32_t IE;   ///< 定时器中断使能寄存器
    volatile uint32_t IF;   ///< 定时器中断标志寄存器
    volatile uint32_t IO;   ///< 定时器IO控制寄存器
} HAL_TIMER_TypeDef;

/**
 * @brief QEP寄存器定义
 */
typedef struct
{
    volatile uint32_t CFG; ///< 0x00 QEP0配置寄存器
    volatile uint32_t TH;  ///< 0x04 QEP0计数门限寄存器
    volatile uint32_t CNT; ///< 0x08 QEP0计数值寄存器
    volatile uint32_t IE;  ///< 0x0C QEP0中断使能寄存器
    volatile uint32_t IF;  ///< 0x10 QEP0中断标志寄存器
} HAL_QEP_TypeDef;
/**
 * @brief MCPWM寄存器定义
 */
typedef struct
{

    volatile uint32_t TH[12];    ///< 偏移地址: 0x00 MCPWM CH0_P 比较门限值寄存器
    volatile uint32_t TMR0;      ///< 偏移地址: 0x30 ADC 采样定时器比较门限 0 寄存器
    volatile uint32_t TMR1;      ///< 偏移地址: 0x34 ADC 采样定时器比较门限 1 寄存器
    volatile uint32_t TMR2;      ///< 偏移地址: 0x38 ADC 采样定时器比较门限 2 寄存器
    volatile uint32_t TMR3;      ///< 偏移地址: 0x3C ADC 采样定时器比较门限 3 寄存器
    volatile uint32_t TH0;       ///< 偏移地址: 0x40 MCPWM 时基 0 门限值寄存器
    volatile uint32_t TH1;       ///< 偏移地址: 0x44 MCPWM 时基 1 门限值寄存器
    volatile uint32_t CNT0;      ///< 偏移地址: 0x48 MCPWM 时基 0 计数器寄存器
    volatile uint32_t CNT1;      ///< 偏移地址: 0x4C MCPWM 时基 1 计数器寄存器
    volatile uint32_t UPDATE;    ///< 偏移地址: 0x50 MCPWM 加载控制寄存器
    volatile uint32_t FCNT;      ///< 偏移地址: 0x54 MCPWM FAIL 时刻 CNT 值
    volatile uint32_t EVT0;      ///< 偏移地址: 0x58 MCPWM 时基 0 外部触发
    volatile uint32_t EVT1;      ///< 偏移地址: 0x5C MCPWM 时基 1 外部触发
    volatile uint32_t DTH00;     ///< 偏移地址: 0x60 MCPWM CH0/1/2 N 通道死区宽度控制寄存器
    volatile uint32_t DTH01;     ///< 偏移地址: 0x64 MCPWM CH0/1/2 P 通道死区宽度控制寄存器
    volatile uint32_t DTH10;     ///< 偏移地址: 0x68 MCPWM CH3/4/5 N 通道死区宽度控制寄存器
    volatile uint32_t DTH11;     ///< 偏移地址: 0x6C MCPWM CH3/4/5 P 通道死区宽度控制寄存器
    volatile uint32_t FLT;       ///< 偏移地址: 0x70 MCPWM 滤波时钟分频寄存器
    volatile uint32_t SDCFG;     ///< 偏移地址: 0x74 MCPWM 加载配置寄存器
    volatile uint32_t AUEN;      ///< 偏移地址: 0x78 MCPWM 自动更新使能寄存器
    volatile uint32_t TCLK;      ///< 偏移地址: 0x7C MCPWM 时钟分频控制寄存器
    volatile uint32_t IE0;       ///< 偏移地址: 0x80 MCPWM 时基 0 中断控制寄存器
    volatile uint32_t IF0;       ///< 偏移地址: 0x84 MCPWM 时基 0 中断标志位寄存器
    volatile uint32_t IE1;       ///< 偏移地址: 0x88 MCPWM 中断控制寄存器
    volatile uint32_t IF1;       ///< 偏移地址: 0x8C MCPWM 中断标志位寄存器
    volatile uint32_t EIE;       ///< 偏移地址: 0x90 MCPWM 异常中断控制寄存器
    volatile uint32_t EIF;       ///< 偏移地址: 0x94 MCPWM 异常中断标志位寄存器
    volatile uint32_t RE;        ///< 偏移地址: 0x98 MCPWM DMA 请求控制寄存器
    volatile uint32_t PP;        ///< 偏移地址: 0x9C MCPWM 推挽模式使能寄存器
    volatile uint32_t IO01;      ///< 偏移地址: 0xA0 MCPWM CH0 CH1 IO 控制寄存器
    volatile uint32_t IO23;      ///< 偏移地址: 0xA4 MCPWM CH2 CH3 IO 控制寄存器
    volatile uint32_t IO45;      ///< 偏移地址: 0xA8 MCPWM CH4 CH5 IO 控制寄存器
    volatile uint32_t null;      ///< 偏移地址: 0xAC 地址对齐
    volatile uint32_t FAIL012;   ///< 偏移地址: 0xB0 MCPWM CH0 CH1 CH2 短路控制寄存器
    volatile uint32_t FAIL345;   ///< 偏移地址: 0xB4 MCPWM CH3 CH4 CH5 短路控制寄存器
    volatile uint32_t CH_DEF;    ///< 偏移地址: 0xB8 MCPWM 短路保护通道输出默认值
    volatile uint32_t CH_MSK;    ///< 偏移地址: 0xBC MCPWM 通道屏蔽寄存器
    volatile uint32_t PRT;       ///< 偏移地址: 0xC0 MCPWM 保护寄存器
    volatile uint32_t STT_HYST;  ///< 偏移地址: 0xC8 MCPWM 状态停留延时寄存器
    volatile uint32_t ZCS_DELAY; ///< 偏移地址: 0xCC MCPWM ZCS 状态延时寄存器
} HAL_MCPWM_TypeDef;

/**
 * @brief GPIO寄存器定义
 */
typedef struct
{
    volatile uint32_t PIE;   ///< 输入使能
    volatile uint32_t POE;   ///< 输出使能
    volatile uint32_t PDI;   ///< 输入数据
    volatile uint32_t PDO;   ///< 输出数据
    volatile uint32_t PUE;   ///< 上拉使能
    volatile uint32_t null1; // 地址对齐
    volatile uint32_t PODE;  ///< 开漏使能
    volatile uint32_t PFLT;  ///< 滤波使能
    volatile uint32_t F3210; ///< 功能选择 GPIO_Pin_0-3
    volatile uint32_t F7654; ///< 功能选择 GPIO_Pin_4-7
    volatile uint32_t FBA98; ///< 功能选择 GPIO_Pin_8-11
    volatile uint32_t FFEDC; ///< 功能选择 GPIO_Pin_12-15
    volatile uint32_t BSRR;  ///< 位置一操作
    volatile uint32_t BRR;   ///< 位清零操作
} HAL_GPIO_TypeDef;

/**
 * @brief CRC寄存器定义
 */
typedef struct
{
    volatile uint32_t DR;   ///< 0x00 CRC数据
    volatile uint32_t CR;   ///< 0x04 CRC控制
    volatile uint32_t INIT; ///< 0x08 CRC初始值
    volatile uint32_t POL;  ///< 0x0C CRC系数
} HAL_CRC_TypeDef;

/**
 * @brief UART寄存器定义
 */
typedef struct
{
    volatile uint32_t CTRL; ///< UART控制寄存器
    volatile uint32_t DIVH; ///< UART波特率设置高字节寄存器
    volatile uint32_t DIVL; ///< UART波特率设置低字节寄存器
    volatile uint32_t BUFF; ///< UART收发缓冲寄存器
    volatile uint32_t ADR;  ///< 485通信地址匹配寄存器
    volatile uint32_t STT;  ///< UART状态寄存器
    volatile uint32_t RE;   ///< UART DMA 请求使能寄存器
    volatile uint32_t IE;   ///< UART中断使能寄存器
    volatile uint32_t IF;   ///< UART中断标志寄存器
    volatile uint32_t IOC;  ///< UART IO翻转使能
} HAL_UART_TypeDef;

/**
 * @brief CAN寄存器定义
 */
typedef struct
{
    volatile uint32_t RBUF[4];   ///< 0x00~0x0C CAN Rx Buffer寄存器
    volatile uint32_t resv0[16]; ///< 0x10~0x4F

    volatile uint32_t TBUF[4];   ///< 0x50~0x5C CAN Tx Buffer寄存器
    volatile uint32_t resv1[16]; ///< 0x60~0x9F

    volatile uint8_t CFG_STAT; ///< 0xA0 CAN配置和状态寄存器
    volatile uint8_t TCMD;     ///< 0xA1 CAN发送命令寄存器
    volatile uint8_t TCTRL;    ///< 0xA2 CAN发送控制寄存器
    volatile uint8_t RCTRL;    ///< 0xA3 CAN接收控制寄存器

    volatile uint8_t RTIE;   ///< 0xA4 CAN发送接收中断控制寄存器
    volatile uint8_t RTIF;   ///< 0xA5 CAN发送接收中断标志寄存器
    volatile uint8_t ERRINT; ///< 0xA6 CAN错误中断使能和标志寄存器
    volatile uint8_t LIMIT;  ///< 0xA7 CAN警告寄存器
    volatile uint32_t SBAUD; ///< 0xA8 CAN波特率配置寄存器

    volatile uint32_t resv2; ///< 0xAC

    volatile uint8_t EALCAP; ///< 0xB0 CAN错误信息和丢失仲裁信息记录寄存器

    volatile uint8_t resv3; ///< 0xB1

    volatile uint8_t RECNT;   ///< 0xB2 CAN接收错误计数器寄存器
    volatile uint8_t TECNT;   ///< 0xB3 CAN发送错误计数器寄存器
    volatile uint8_t ACFCTRL; ///< 0xB4 CAN ID过滤器控制寄存器

    volatile uint8_t resv4; ///< 0xB5

    volatile uint16_t ACFEN; ///< 0xB6 CAN ID过滤器使能寄存器
    volatile uint32_t ACF;   ///< 0xB8 CAN ID过滤器选择寄存器
} HAL_CAN_TypeDef;

/**
 * @brief DSP寄存器定义
 */
typedef struct
{
    volatile uint32_t SC;     // 0x00
    volatile uint32_t THETA;  // 0x04
    volatile uint32_t X;      // 0x08
    volatile uint32_t Y;      // 0x0C
    volatile uint32_t SIN;    // 0x10
    volatile uint32_t COS;    // 0x14
    volatile uint32_t MOD;    // 0x18
    volatile uint32_t ARCTAN; // 0x1C
    volatile uint32_t DID;    // 0x20
    volatile uint32_t DIS;    // 0x24
    volatile uint32_t QUO;    // 0x28
    volatile uint32_t REM;    // 0x2C
    volatile uint32_t RAD;    // 0x30
    volatile uint32_t SQRT;   // 0x34
    volatile uint32_t PC;     // 0x38
} HAL_DSP_TypeDef;

typedef struct
{
    volatile uint32_t PSW; ///< 0x00 独立看门狗密码寄存器
    volatile uint32_t CFG; ///< 0x04 独立看门狗配置寄存器
    volatile uint32_t CLR; ///< 0x08 独立看门狗清零寄存器
    volatile uint32_t WTH; ///< 0x0C 独立看门狗计数器定时唤醒门限值寄存器
    volatile uint32_t RTH; ///< 0x10 独立看门狗计数器超时复位门限值寄存器
    volatile uint32_t CNT; ///< 0x14 独立看门狗计数器当前计数值寄存器
} HAL_IWDG_TypeDef;

typedef struct
{
    volatile uint32_t CCR;  /**< DMA 通道配置寄存器*/
    volatile uint32_t REN;  /**< DMA 请求使能寄存器*/
    volatile uint32_t CTMS; /**< DMA传输次数设置寄存器*/
    volatile uint32_t SADR; /**< DMA 源地址设置寄存器*/
    volatile uint32_t DADR; /**< DMA 目的地址设置*/
} HAL_DMA_TypeDef;

extern HAL_SYS_TypeDef *const HAL_SYS[];
extern HAL_FLASH_TypeDef *const HAL_FLASH[];
extern HAL_SPI_TypeDef *const HAL_SPI[];
extern HAL_I2C_TypeDef *const HAL_I2C[];
extern HAL_CMP_TypeDef *const HAL_CMP[];
extern HAL_HALL_TypeDef *const HAL_HALL[];
extern HAL_ADC_TypeDef *const HAL_ADC[];
extern HAL_TIMER_TypeDef *const HAL_TIMER[];
extern HAL_QEP_TypeDef *const HAL_QEP[];
extern HAL_MCPWM_TypeDef *const HAL_MCPWM[];
extern HAL_GPIO_TypeDef *const HAL_GPIO[];
extern HAL_CRC_TypeDef *const HAL_CRC[];
extern HAL_UART_TypeDef *const HAL_UART[];
extern HAL_CAN_TypeDef *const HAL_CAN[];
extern HAL_DSP_TypeDef *const HAL_DSP[];
extern HAL_IWDG_TypeDef *const HAL_IWDG[];
extern HAL_DMA_TypeDef *const HAL_DMA[];
#endif
