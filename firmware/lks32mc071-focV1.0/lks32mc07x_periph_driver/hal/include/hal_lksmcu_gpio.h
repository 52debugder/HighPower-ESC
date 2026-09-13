#ifndef __HAL_LKSMCU_GPIO_H__
#define __HAL_LKSMCU_GPIO_H__
#include "basic.h"
#include "stdint.h"
/** GPIO口定义 */
typedef enum
{
    HAL_GPIO_P0_0  = 0x0000, ///< P0.0
    HAL_GPIO_P0_1  = 0x0001, ///< P0.1
    HAL_GPIO_P0_2  = 0x0002, ///< P0.2
    HAL_GPIO_P0_3  = 0x0003, ///< P0.3
    HAL_GPIO_P0_4  = 0x0004, ///< P0.4
    HAL_GPIO_P0_5  = 0x0005, ///< P0.5
    HAL_GPIO_P0_6  = 0x0006, ///< P0.6
    HAL_GPIO_P0_7  = 0x0007, ///< P0.7
    HAL_GPIO_P0_8  = 0x0008, ///< P0.8
    HAL_GPIO_P0_9  = 0x0009, ///< P0.9
    HAL_GPIO_P0_10 = 0x000a, ///< P0.10
    HAL_GPIO_P0_11 = 0x000b, ///< P0.11
    HAL_GPIO_P0_12 = 0x000c, ///< P0.12
    HAL_GPIO_P0_13 = 0x000d, ///< P0.13
    HAL_GPIO_P0_14 = 0x000e, ///< P0.14
    HAL_GPIO_P0_15 = 0x000f, ///< P0.15
    HAL_GPIO_P1_0  = 0x0100, ///< P1.0
    HAL_GPIO_P1_1  = 0x0101, ///< P1.1
    HAL_GPIO_P1_2  = 0x0102, ///< P1.2
    HAL_GPIO_P1_3  = 0x0103, ///< P1.3
    HAL_GPIO_P1_4  = 0x0104, ///< P1.4
    HAL_GPIO_P1_5  = 0x0105, ///< P1.5
    HAL_GPIO_P1_6  = 0x0106, ///< P1.6
    HAL_GPIO_P1_7  = 0x0107, ///< P1.7
    HAL_GPIO_P1_8  = 0x0108, ///< P1.8
    HAL_GPIO_P1_9  = 0x0109, ///< P1.9
    HAL_GPIO_P1_10 = 0x010a, ///< P1.10
    HAL_GPIO_P1_11 = 0x010b, ///< P1.11
    HAL_GPIO_P1_12 = 0x010c, ///< P1.12
    HAL_GPIO_P1_13 = 0x010d, ///< P1.13
    HAL_GPIO_P1_14 = 0x010e, ///< P1.14
    HAL_GPIO_P1_15 = 0x010f, ///< P1.15
    HAL_GPIO_P2_0  = 0x0200, ///< P2.0
    HAL_GPIO_P2_1  = 0x0201, ///< P2.1
    HAL_GPIO_P2_2  = 0x0202, ///< P2.2
    HAL_GPIO_P2_3  = 0x0203, ///< P2.3
    HAL_GPIO_P2_4  = 0x0204, ///< P2.4
    HAL_GPIO_P2_5  = 0x0205, ///< P2.5
    HAL_GPIO_P2_6  = 0x0206, ///< P2.6
    HAL_GPIO_P2_7  = 0x0207, ///< P2.7
    HAL_GPIO_P2_8  = 0x0208, ///< P2.8
    HAL_GPIO_P2_9  = 0x0209, ///< P2.9
    HAL_GPIO_P2_10 = 0x020a, ///< P2.10
    HAL_GPIO_P2_11 = 0x020b, ///< P2.11
    HAL_GPIO_P2_12 = 0x020c, ///< P2.12
    HAL_GPIO_P2_13 = 0x020d, ///< P2.13
    HAL_GPIO_P2_14 = 0x020e, ///< P2.14
    HAL_GPIO_P2_15 = 0x020f, ///< P2.15
    HAL_GPIO_P3_0  = 0x0300, ///< P3.0
    HAL_GPIO_P3_1  = 0x0301, ///< P3.1
    HAL_GPIO_P3_2  = 0x0302, ///< P3.2
    HAL_GPIO_P3_3  = 0x0303, ///< P3.3
    HAL_GPIO_P3_4  = 0x0304, ///< P3.4
    HAL_GPIO_P3_5  = 0x0305, ///< P3.5
    HAL_GPIO_P3_6  = 0x0306, ///< P3.6
    HAL_GPIO_P3_7  = 0x0307, ///< P3.7
    HAL_GPIO_P3_8  = 0x0308, ///< P3.8
    HAL_GPIO_P3_9  = 0x0309, ///< P3.9
    HAL_GPIO_P3_10 = 0x030a, ///< P3.10
    HAL_GPIO_P3_11 = 0x030b, ///< P3.11
    HAL_GPIO_P3_12 = 0x030c, ///< P3.12
    HAL_GPIO_P3_13 = 0x030d, ///< P3.13
    HAL_GPIO_P3_14 = 0x030e, ///< P3.14
    HAL_GPIO_P3_15 = 0x030f, ///< P3.15
    HAL_GPIO_P4_0  = 0x0400, ///< P4.0
    HAL_GPIO_P4_1  = 0x0401, ///< P4.1
    HAL_GPIO_P4_2  = 0x0402, ///< P4.2
    HAL_GPIO_P4_3  = 0x0403, ///< P4.3
    HAL_GPIO_P4_4  = 0x0404, ///< P4.4
    HAL_GPIO_P4_5  = 0x0405, ///< P4.5
    HAL_GPIO_P4_6  = 0x0406, ///< P4.6
    HAL_GPIO_P4_7  = 0x0407, ///< P4.7
    HAL_GPIO_P4_8  = 0x0408, ///< P4.8
    HAL_GPIO_P4_9  = 0x0409, ///< P4.9
    HAL_GPIO_P4_10 = 0x040a, ///< P4.10
    HAL_GPIO_P4_11 = 0x040b, ///< P4.11
    HAL_GPIO_P4_12 = 0x040c, ///< P4.12
    HAL_GPIO_P4_13 = 0x040d, ///< P4.13
    HAL_GPIO_P4_14 = 0x040e, ///< P4.14
    HAL_GPIO_P4_15 = 0x040f, ///< P4.15
    HAL_GPIO_P5_0  = 0x0500, ///< P5.0
    HAL_GPIO_P5_1  = 0x0501, ///< P5.1
    HAL_GPIO_P5_2  = 0x0502, ///< P5.2
    HAL_GPIO_P5_3  = 0x0503, ///< P5.3
    HAL_GPIO_P5_4  = 0x0504, ///< P5.4
    HAL_GPIO_P5_5  = 0x0505, ///< P5.5
    HAL_GPIO_P5_6  = 0x0506, ///< P5.6
    HAL_GPIO_P5_7  = 0x0507, ///< P5.7
    HAL_GPIO_P5_8  = 0x0508, ///< P5.8
    HAL_GPIO_P5_9  = 0x0509, ///< P5.9
    HAL_GPIO_P5_10 = 0x050a, ///< P5.10
    HAL_GPIO_P5_11 = 0x050b, ///< P5.11
    HAL_GPIO_P5_12 = 0x050c, ///< P5.12
    HAL_GPIO_P5_13 = 0x050d, ///< P5.13
    HAL_GPIO_P5_14 = 0x050e, ///< P5.14
    HAL_GPIO_P5_15 = 0x050f, ///< P5.15
} HAL_GPIO_Px;

typedef enum
{
    HAL_GPIO_AF_ADC     = 0, // ADC输入
    HAL_GPIO_AF_OPA     = 0, // 运放输入
    HAL_GPIO_AF_OPA_OUT = 0, // 运放输出
    HAL_GPIO_AF_CMP     = 0, // 比较器输入
    HAL_GPIO_AF_DAC     = 0, // DAC输出,需要DAC同步设置DAC输出使能
    HAL_GPIO_AF_GPIO    = 0, // GPIO功能
    HAL_GPIO_AF_CLK     = 0, // 时钟输入

    HAL_GPIO_AF_CMP_OUT = 1, // 比较器比较输出
    HAL_GPIO_AF_CLK_OUT = 1, // 时钟输出

    HAL_GPIO_AF_HALL   = 2, // 霍尔输入
    HAL_GPIO_AF_MCPWM  = 3, // MCPWMFAIL输入 MCPWM输出
    HAL_GPIO_AF_UART   = 4, // UART输入输出
    HAL_GPIO_AF_SPI    = 5, // CS CLK MOSI MISO
    HAL_GPIO_AF_I2C    = 6, // SCL和SDA
    HAL_GPIO_AF_TIMER0 = 7, // TIMER0输入或输出
    HAL_GPIO_AF_TIMER1 = 7, // TIMER1输入或输出
    HAL_GPIO_AF_TIMER2 = 8, // TIMER2输入或输出
    HAL_GPIO_AF_TIMER3 = 8, // TIMER3输入或输出
    HAL_GPIO_AF_QEP0   = 8, // 编码器输入
    HAL_GPIO_AF_QEP1   = 8, // 编码器输入

    HAL_GPIO_AF_ADC_TRIG = 9,  // adc触发信号输出
    HAL_GPIO_AF_CAN      = 10, // CAN输入输出
    HAL_GPIO_AF_SIF      = 11, // SIF信号输出
    HAL_GPIO_AF_CL       = 12, // CL输出

#ifdef HAL_TEST_NOT_SUPPORTED
    HAL_GPIO_AF_QEP2   = 0, // 编码器输入 不支持
    HAL_GPIO_AF_QEP3   = 0, // 编码器输入 不支持
    HAL_GPIO_AF_TIMER4 = 0, // TIMER4输入或输出 不支持
    HAL_GPIO_AF_TIMER5 = 0, // TIMER5输入或输出 不支持
#endif
} HAL_GPIO_AFx;
/**
 * @brief GPIO工作模式定义
 */
typedef enum
{
    HAL_GPIO_MODE_IN_EN     = BIT0, // 输入使能
    HAL_GPIO_MODE_OUT_EN    = BIT1, // 输出使能
    HAL_GPIO_MODE_UP_EN     = BIT2, // 上拉使能
    HAL_GPIO_MODE_PODE_EN   = BIT3, // 开漏使能
    HAL_GPIO_MODE_DEFAULT_0 = BIT4, // 初始化输出为低电平
    HAL_GPIO_MODE_DEFAULT_1 = BIT5, // 初始化输出为高电平

    HAL_GPIO_MODE_AFE       = 0,                                                                 ///< GPIO设置为模拟接口
    HAL_GPIO_MODE_NONE      = HAL_GPIO_MODE_AFE,                                                 ///< GPIO设置为不使用 输出输出均关闭
    HAL_GPIO_MODE_IN        = HAL_GPIO_MODE_IN_EN,                                               ///< GPIO设置为输入模式
    HAL_GPIO_MODE_INUP      = HAL_GPIO_MODE_IN | HAL_GPIO_MODE_UP_EN,                            ///< GPIO设置为上拉输入模式(输入模式,打开上拉电阻)
    HAL_GPIO_MODE_OUT       = HAL_GPIO_MODE_OUT_EN,                                              ///< GPIO设置为输出模式
    HAL_GPIO_MODE_INOUT     = HAL_GPIO_MODE_IN | HAL_GPIO_MODE_OUT | HAL_GPIO_MODE_PODE_EN,      ///< GPIO设置为输入输出模式(可以输出为0或悬空,悬空时输入有效)
    HAL_GPIO_MODE_INUPOUT   = HAL_GPIO_MODE_INOUT | HAL_GPIO_MODE_UP_EN | HAL_GPIO_MODE_PODE_EN, ///< GPIO设置为上拉输入输出模式(可以输出为0或上拉,上拉时输入有效,线与模式)
    HAL_GPIO_MODE_OUT_0     = HAL_GPIO_MODE_OUT | HAL_GPIO_MODE_DEFAULT_0,                       ///< GPIO设置为输出模式 初始化完成后io状态为低电平
    HAL_GPIO_MODE_INOUT_0   = HAL_GPIO_MODE_INOUT | HAL_GPIO_MODE_DEFAULT_0,                     ///< GPIO设置为输入输出模式(可以输出为0或悬空,悬空时输入有效) 初始化完成后io状态为低电平
    HAL_GPIO_MODE_INUPOUT_0 = HAL_GPIO_MODE_INUPOUT | HAL_GPIO_MODE_DEFAULT_0,                   ///< GPIO设置为上拉输入输出模式(可以输出为0或上拉,上拉时输入有效,线与模式) 初始化完成后io状态为低电平
    HAL_GPIO_MODE_OUT_1     = HAL_GPIO_MODE_OUT | HAL_GPIO_MODE_DEFAULT_1,                       ///< GPIO设置为输出模式 初始化完成后io状态为高电平
    HAL_GPIO_MODE_INOUT_1   = HAL_GPIO_MODE_INOUT | HAL_GPIO_MODE_DEFAULT_1,                     ///< GPIO设置为输入输出模式(可以输出为0或悬空,悬空时输入有效) 初始化完成后io状态为悬空
    HAL_GPIO_MODE_INUPOUT_1 = HAL_GPIO_MODE_INUPOUT | HAL_GPIO_MODE_DEFAULT_1,                   ///< GPIO设置为上拉输入输出模式(可以输出为0或上拉,上拉时输入有效,线与模式) 初始化完成后io状态为上拉
} HAL_GPIO_MODE_x;
// 模块初始化
void HAL_GPIO_Reset(void);   // 模块复位,执行后恢复所有的GPIO为悬空状态(SWD、JTAG和RST口为默认状态)
void HAL_GPIO_Enable(void);  // 模块打开
void HAL_GPIO_Disable(void); // 模块关闭

// 输入输出
void HAL_GPIO_SetMode(HAL_GPIO_Px, HAL_GPIO_MODE_x); // 设置指定GPIO的工作模式
void HAL_GPIO_SetHigh(HAL_GPIO_Px);                  // 输出1(INOUT和INUPOUT模式下分别为悬空和上拉)
void HAL_GPIO_SetLow(HAL_GPIO_Px);                   // 输出0
void HAL_GPIO_Write(HAL_GPIO_Px, uint8_t);           // 输出0或1
void HAL_GPIO_Invert(HAL_GPIO_Px);                   // 翻转指定的GPIO
uint8_t HAL_GPIO_GetOutData(HAL_GPIO_Px);            // 获取当前GPIO的输出值,返回值0或1
uint8_t HAL_GPIO_GetInData(HAL_GPIO_Px);             // 获取当前GPIO的输入值,返回值0或1

// 内部使用
void HAL_GPIO_SetAf(HAL_GPIO_Px, HAL_GPIO_AFx); // 配置GPIO的特殊功能(UART、I2C、SPI等,由对应模块的初始化调用)
// 特殊GPIO口配置
void HAL_GPIO_SwdReuseGpioEnable(void);  // 设置SWD接口为普通GPIO口
void HAL_GPIO_SwdReuseGpioDisable(void); // 设置SWD接口为SWD功能
void HAL_GPIO_RstReuseGpioEnable(void);  // 设置RST接口为普通GPIO口
void HAL_GPIO_RstReuseGpioDisable(void); // 设置RST接口为RST功能
#endif
