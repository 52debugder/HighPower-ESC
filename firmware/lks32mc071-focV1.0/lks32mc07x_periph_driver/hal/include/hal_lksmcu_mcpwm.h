#ifndef __HAL_LKSMCU_MCPWM_H__
#define __HAL_LKSMCU_MCPWM_H__
#include "hal_lksmcu_gpio.h"
#include "stdint.h"

/**
 * @brief MCPWM模块
 */
typedef enum
{
    HAL_MCPWM_0   = 0x00, ///< 模块0 （模块0的时基0）
    HAL_MCPWM_0_1 = 0x10, ///< 模块01 （模块0的时基1）
#ifdef HAL_TEST_NOT_SUPPORTED
    HAL_MCPWM_1   = 0x01, ///< 模块1（模块1的时基0）
    HAL_MCPWM_1_1 = 0x11, ///< 模块11（模块1的时基1）
#endif
} HAL_MCPWM_x;
/**
 * @brief 输出端口
 */
typedef enum
{
    HAL_MCPWM_PORT_0, ///< 输出端口0
    HAL_MCPWM_PORT_1, ///< 输出端口1
    HAL_MCPWM_PORT_2, ///< 输出端口2
    HAL_MCPWM_PORT_3, ///< 输出端口3
    HAL_MCPWM_PORT_4, ///< 输出端口4
    HAL_MCPWM_PORT_5, ///< 输出端口5
} HAL_MCPWM_PORT_x;
/**
 * @brief 输出PN交换配置
 */
typedef enum
{
    HAL_MCPWM_SWAP_DISABLE = 0, ///< 取消交换PN通道
    HAL_MCPWM_SWAP_ENABLE,      ///< 交换PN通道
} HAL_MCPWM_SWAP_x;
/**
 * @brief 极性
 */
typedef enum
{
    HAL_MCPWM_POLARITY_PL_NL, ///< 上管低有效,下管低有效
    HAL_MCPWM_POLARITY_PH_NL, ///< 上管高有效,下管低有效
    HAL_MCPWM_POLARITY_PL_NH, ///< 上管低有效,下管高有效
    HAL_MCPWM_POLARITY_PH_NH, ///< 上管高有效,下管高有效
} HAL_MCPWM_POLARITY_x;
/**
 * 输出状态
 */
typedef enum
{
    HAL_MCPWM_OUTPUT_STATE_PWM,      ///< 上下管对称pwm
    HAL_MCPWM_OUTPUT_STATE_OFF,      ///< 关闭输出
    HAL_MCPWM_OUTPUT_STATE_LOW,      ///< 下管恒开
    HAL_MCPWM_OUTPUT_STATE_HIGH,     ///< 上管恒开
    HAL_MCPWM_OUTPUT_STATE_LOW_PWM,  ///< 下管pwm
    HAL_MCPWM_OUTPUT_STATE_HIGH_PWM, ///< 上管pwm
} HAL_MCPWM_OUTPUT_STATE_x;
/**
 * @brief 默认输出电平（触发FAIL或关闭输出后的状态）
 */
typedef enum
{
    HAL_MCPWM_DEFAULT_OUTPUT_STATE_OFF,  ///< 关闭输出
    HAL_MCPWM_DEFAULT_OUTPUT_STATE_LOW,  ///< 下管恒开
    HAL_MCPWM_DEFAULT_OUTPUT_STATE_HIGH, ///< 上管恒开
} HAL_MCPWM_DEFAULT_OUTPUT_STATE_x;

/**
 * @brief MCPWM模块FAIL通道
 */
typedef enum
{
    HAL_MCPWM_FAIL_0 = 0, ///< FAIL0
    HAL_MCPWM_FAIL_1 = 1, ///< FAIL1
    HAL_MCPWM_FAIL_2 = 0, ///< FAIL2
    HAL_MCPWM_FAIL_3 = 1, ///< FAIL3
} HAL_MCPWM_FAIL_x;

/**
 * @brief FAIL信号来源
 */
typedef enum
{
    HAL_MCPWM_FAIL_IN_IO_HIGH   = 0x01, ///< 外部FAIL信号为高电平后mcpwm关闭输出
    HAL_MCPWM_FAIL_IN_IO_LOW    = 0x02, ///< 外部FAIL信号为低电平后mcpwm关闭输出
    HAL_MCPWM_FAIL_IN_CMP0_HIGH = 0x03, ///< 仅FAIL0 FAIL2 CMP0为高电平后mcpwm关闭输出
    HAL_MCPWM_FAIL_IN_CMP0_LOW  = 0x04, ///< 仅FAIL0 FAIL2 CMP0为低电平后mcpwm关闭输出
    HAL_MCPWM_FAIL_IN_CMP1_HIGH = 0x03, ///< 仅FAIL1 FAIL3 CMP1为高电平后mcpwm关闭输出
    HAL_MCPWM_FAIL_IN_CMP1_LOW  = 0x04, ///< 仅FAIL1 FAIL3 CMP1为低电平后mcpwm关闭输出

    HAL_MCPWM_FAIL_IN_CLU0_HIGH = 0x05, ///< 仅FAIL0 FAIL2 CLU0输出为高电平后mcpwm关闭输出
    HAL_MCPWM_FAIL_IN_CLU0_LOW  = 0x06, ///< 仅FAIL0 FAIL2 CLU0输出为高电平后mcpwm关闭输出
    HAL_MCPWM_FAIL_IN_CLU1_HIGH = 0x07, ///< 仅FAIL0 FAIL2 CLU1输出为低电平后mcpwm关闭输出
    HAL_MCPWM_FAIL_IN_CLU1_LOW  = 0x08, ///< 仅FAIL0 FAIL2 CLU1输出为低电平后mcpwm关闭输出

    HAL_MCPWM_FAIL_IN_CLU2_HIGH = 0x05, ///< 仅FAIL1 FAIL3 CLU2输出为高电平后mcpwm关闭输出
    HAL_MCPWM_FAIL_IN_CLU2_LOW  = 0x06, ///< 仅FAIL1 FAIL3 CLU2输出为高电平后mcpwm关闭输出
    HAL_MCPWM_FAIL_IN_CLU3_HIGH = 0x07, ///< 仅FAIL1 FAIL3 CLU3输出为低电平后mcpwm关闭输出
    HAL_MCPWM_FAIL_IN_CLU3_LOW  = 0x08, ///< 仅FAIL1 FAIL3 CLU3输出为低电平后mcpwm关闭输出

#ifdef HAL_TEST_NOT_SUPPORTED
    HAL_MCPWM_FAIL_IN_CMP2_HIGH, ///< 仅 HAL_MCPWM_x_1 FAIL2 CMP0为高电平后mcpwm关闭输出 不支持
    HAL_MCPWM_FAIL_IN_CMP2_LOW,  ///< 仅 HAL_MCPWM_x_1 FAIL2 CMP0为低电平后mcpwm关闭输出 不支持
    HAL_MCPWM_FAIL_IN_CMP3_HIGH, ///< 仅 HAL_MCPWM_x_1 FAIL3 CMP1为高电平后mcpwm关闭输出 不支持
    HAL_MCPWM_FAIL_IN_CMP3_LOW,  ///< 仅 HAL_MCPWM_x_1 FAIL3 CMP1为低电平后mcpwm关闭输出 不支持
#endif
} HAL_MCPWM_FAIL_IN_x;

/**
 * @brief 影子寄存器自动更新事件
 */
typedef enum
{
    HAL_MCPWM_UPDATE_T0        = 0, ///< 起点更新(默认)
    HAL_MCPWM_UPDATE_T1        = 1, ///< 过零更新
    HAL_MCPWM_UPDATE_T0_AND_T1 = 2, ///< 起点和过零都更新
} HAL_MCPWM_UPDATE_x;

// 初始化
void HAL_MCPWM_Reset(HAL_MCPWM_x);   // 模块复位
void HAL_MCPWM_Enable(HAL_MCPWM_x);  // 模块打开
void HAL_MCPWM_Disable(HAL_MCPWM_x); // 模块关闭

void HAL_MCPWM_SetFreq(HAL_MCPWM_x, uint32_t freq);                           // 设置pwm频率
void HAL_MCPWM_SetThCnt(HAL_MCPWM_x, uint32_t th);                            // 设置计数器最大值
void HAL_MCPWM_SetUpdateMode(HAL_MCPWM_x, HAL_MCPWM_UPDATE_x, uint32_t intv); // 设置影子寄存器自动更新时刻
uint32_t HAL_MCPWM_GetFreq(HAL_MCPWM_x);                                      // 获取当前的pwm频率
uint32_t HAL_MCPWM_GetThCnt(HAL_MCPWM_x);                                     // 获取计数器最大值
void HAL_MCPWM_SetClockDiv(HAL_MCPWM_x mcpwm_x, uint32_t div);                // 设置时钟分频 div=1/2/4/8
uint32_t HAL_MCPWM_GetClockDiv(HAL_MCPWM_x mcpwm_x);                          // 获取时钟分频实际除数
uint32_t HAL_MCPWM_GetClockFreq(HAL_MCPWM_x mcpwm_x);                         // 获取分频后工作时钟(Hz)
void HAL_MCPWM_SetDead(HAL_MCPWM_x, uint32_t pdead_nS, uint32_t ndead_nS);    // 设置死区

void HAL_MCPWM_SetOutputDisable(HAL_MCPWM_x);                                                // 关闭输出
void HAL_MCPWM_SetOutputEnable(HAL_MCPWM_x);                                                 // 打开输出
void HAL_MCPWM_StartCounting(HAL_MCPWM_x);                                                   // 开始计数
void HAL_MCPWM_StopCounting(HAL_MCPWM_x);                                                    // 停止计数(同时计数器回到-th)
void HAL_MCPWM_StartCountingSync(HAL_MCPWM_x mcpwm1_x, HAL_MCPWM_x mcpwm2_x, int16_t phase); // 跟随另一个cnt启动，需要先启动mcpwm1_x
void HAL_MCPWM_SetPwm(HAL_MCPWM_x, HAL_MCPWM_PORT_x, int32_t t0, int32_t t1);                // 设置pwm波形
void HAL_MCPWM_SetPwmQ15(HAL_MCPWM_x, HAL_MCPWM_PORT_x, int16_t t0, int16_t t1);             // 设置pwm波形q15格式输入
void HAL_MCPWM_SetOutState(HAL_MCPWM_x, HAL_MCPWM_PORT_x, HAL_MCPWM_OUTPUT_STATE_x);         // 设置输出状态
void HAL_MCPWM_SetAdcTrig(HAL_MCPWM_x, int32_t t0, int32_t t1);                              // 设置pwm输出ADC采样时间
void HAL_MCPWM_SetAdcTrigQ15(HAL_MCPWM_x, int32_t t0, int32_t t1);                           // 设置pwm输出ADC采样时间q15格式输入

void HAL_MCPWM_SetDrivePolarity(HAL_MCPWM_x, HAL_MCPWM_POLARITY_x);                       // 设置pwm极性
void HAL_MCPWM_SetDrivePolarityPort(HAL_MCPWM_x, HAL_MCPWM_PORT_x, HAL_MCPWM_POLARITY_x); // 设置单个输出通道的pwm极性
void HAL_MCPWM_SetSwap(HAL_MCPWM_x, HAL_MCPWM_SWAP_x);                                    // 设置PN是否交换
void HAL_MCPWM_SetSwapPort(HAL_MCPWM_x, HAL_MCPWM_PORT_x, HAL_MCPWM_SWAP_x);              // 设置单个输出通道的PN是否交换
void HAL_MCPWM_SetRemap(HAL_MCPWM_x, uint8_t mode);
void HAL_MCPWM_SetDefaultState(HAL_MCPWM_x, HAL_MCPWM_DEFAULT_OUTPUT_STATE_x);    // 设置默认电平
void HAL_MCPWM_SetGpioOut(HAL_MCPWM_x, HAL_GPIO_Px);                              // 设置用于输出的gpio
void HAL_MCPWM_SetGpioFail(HAL_MCPWM_x, HAL_GPIO_Px);                             // 设置用于故障输入的gpio
void HAL_MCPWM_SetFailSignal(HAL_MCPWM_x, HAL_MCPWM_FAIL_x, HAL_MCPWM_FAIL_IN_x); // 设置FAIL信号来源
void HAL_MCPWM_SetFailFilter(HAL_MCPWM_x, uint32_t cnt);                          // 设置FAIL信号滤波宽度

#endif
