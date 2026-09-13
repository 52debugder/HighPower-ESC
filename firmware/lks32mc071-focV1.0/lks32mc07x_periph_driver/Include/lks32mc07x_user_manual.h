/**
 * @file lks32mc07x_user_manual
 * @brief 从手册创建的头文件
 * @details 基于文件 lks32mc07x_user_manual.pdf
 * @note 本文件由自动化系统创建，请勿手动修改
 * @date 2026-08-04 03:00:24
 */
#ifndef __LKS32MC07X_USER_MANUAL__
#define __LKS32MC07X_USER_MANUAL__
#include "stdint.h"

/* SYS_AFE_INFO 芯片版本信息寄存器 */
#define SYS_AFE_INFO_Series_MAX   ((uint32_t)0xF)                                               // SYS_AFE_INFO_Series最大值
#define SYS_AFE_INFO_Series_POS   4                                                             // SYS_AFE_INFO_Series起始位
#define SYS_AFE_INFO_Series_MASK  (uint32_t)((uint32_t)0xF << SYS_AFE_INFO_Series_POS)          // SYS_AFE_INFO_Series位掩码
#define SYS_AFE_INFO_Series(x)    (uint32_t)((uint32_t)((x) & 0xF) << SYS_AFE_INFO_Series_POS)  // [7:4] 芯片型号信息
#define SYS_AFE_INFO_Version_MAX  ((uint32_t)0xF)                                               // SYS_AFE_INFO_Version最大值
#define SYS_AFE_INFO_Version_POS  0                                                             // SYS_AFE_INFO_Version起始位
#define SYS_AFE_INFO_Version_MASK (uint32_t)((uint32_t)0xF << SYS_AFE_INFO_Version_POS)         // SYS_AFE_INFO_Version位掩码
#define SYS_AFE_INFO_Version(x)   (uint32_t)((uint32_t)((x) & 0xF) << SYS_AFE_INFO_Version_POS) // [3:0] 芯片版本信息

/* SYS_AFE_DBG 调试寄存器 */
#define SYS_AFE_DBG_PWR_WEAK_BIT BIT15 // [15] 供电低于掉电监测阈值

/* SYS_AFE_REG0 模拟配置寄存器0 */
#define SYS_AFE_REG0_IT_OPA_MAX    ((uint32_t)0x3)                                                // SYS_AFE_REG0_IT_OPA最大值
#define SYS_AFE_REG0_IT_OPA_POS    8                                                              // SYS_AFE_REG0_IT_OPA起始位
#define SYS_AFE_REG0_IT_OPA_MASK   (uint32_t)((uint32_t)0x3 << SYS_AFE_REG0_IT_OPA_POS)           // SYS_AFE_REG0_IT_OPA位掩码
#define SYS_AFE_REG0_IT_OPA(x)     (uint32_t)((uint32_t)((x) & 0x3) << SYS_AFE_REG0_IT_OPA_POS)   // [9:8] OPA偏置电流调节，默认配置000: ×1，建议RES_OPAx选择非最大放大倍数时，选用此配置01: ×1.210: ×1.5，建议RES_OPAx选择00最大放大倍数时，选用此配置11: ×2
#define SYS_AFE_REG0_RES_OPA3_MAX  ((uint32_t)0x3)                                                // SYS_AFE_REG0_RES_OPA3最大值
#define SYS_AFE_REG0_RES_OPA3_POS  6                                                              // SYS_AFE_REG0_RES_OPA3起始位
#define SYS_AFE_REG0_RES_OPA3_MASK (uint32_t)((uint32_t)0x3 << SYS_AFE_REG0_RES_OPA3_POS)         // SYS_AFE_REG0_RES_OPA3位掩码
#define SYS_AFE_REG0_RES_OPA3(x)   (uint32_t)((uint32_t)((x) & 0x3) << SYS_AFE_REG0_RES_OPA3_POS) // [7:6] 运放3反馈电阻00: 320k:10k01: 160k:10k10: 80k:10k11: 40k:10k
#define SYS_AFE_REG0_RES_OPA2_MAX  ((uint32_t)0x3)                                                // SYS_AFE_REG0_RES_OPA2最大值
#define SYS_AFE_REG0_RES_OPA2_POS  4                                                              // SYS_AFE_REG0_RES_OPA2起始位
#define SYS_AFE_REG0_RES_OPA2_MASK (uint32_t)((uint32_t)0x3 << SYS_AFE_REG0_RES_OPA2_POS)         // SYS_AFE_REG0_RES_OPA2位掩码
#define SYS_AFE_REG0_RES_OPA2(x)   (uint32_t)((uint32_t)((x) & 0x3) << SYS_AFE_REG0_RES_OPA2_POS) // [5:4] 运放2反馈电阻00: 320k:10k01: 160k:10k10: 80k:10k11: 40k:10k
#define SYS_AFE_REG0_RES_OPA1_MAX  ((uint32_t)0x3)                                                // SYS_AFE_REG0_RES_OPA1最大值
#define SYS_AFE_REG0_RES_OPA1_POS  2                                                              // SYS_AFE_REG0_RES_OPA1起始位
#define SYS_AFE_REG0_RES_OPA1_MASK (uint32_t)((uint32_t)0x3 << SYS_AFE_REG0_RES_OPA1_POS)         // SYS_AFE_REG0_RES_OPA1位掩码
#define SYS_AFE_REG0_RES_OPA1(x)   (uint32_t)((uint32_t)((x) & 0x3) << SYS_AFE_REG0_RES_OPA1_POS) // [3:2] 运放1反馈电阻00: 320k:10k01: 160k:10k10: 80k:10k11: 40k:10k
#define SYS_AFE_REG0_RES_OPA0_MAX  ((uint32_t)0x3)                                                // SYS_AFE_REG0_RES_OPA0最大值
#define SYS_AFE_REG0_RES_OPA0_POS  0                                                              // SYS_AFE_REG0_RES_OPA0起始位
#define SYS_AFE_REG0_RES_OPA0_MASK (uint32_t)((uint32_t)0x3 << SYS_AFE_REG0_RES_OPA0_POS)         // SYS_AFE_REG0_RES_OPA0位掩码
#define SYS_AFE_REG0_RES_OPA0(x)   (uint32_t)((uint32_t)((x) & 0x3) << SYS_AFE_REG0_RES_OPA0_POS) // [1:0] 运放0反馈电阻00: 320k:10k01: 160k:10k10: 80k:10k11: 40k:10k

/* SYS_AFE_REG1 模拟配置寄存器1 */
#define SYS_AFE_REG1_DAC1_GAIN_BIT BIT7 // [7] DAC1输出档位配置0:满量程为4.85V; 1:满量程为1.2V
#define SYS_AFE_REG1_DAC0_GAIN_BIT BIT6 // [6] DAC0输出档位配置0:满量程为4.85V; 1:满量程为1.2V
#define SYS_AFE_REG1_REF2VDD_BIT   BIT4 // [4] ADC基准选择1: 使用外部输入电源作为ADC基准;0: 使用默认内部REF 2.4V作为ADC基准源
#define SYS_AFE_REG1_CMP_FT_BIT    BIT0 // [0] 比较器快速比较1:使能，比较速度小于50ns0: 不使能，比较速度小于200ns

/* SYS_AFE_REG2 模拟配置寄存器2 */
#define SYS_AFE_REG2_CMP2_SELP_MAX  ((uint32_t)0x3)                                                 // SYS_AFE_REG2_CMP2_SELP最大值
#define SYS_AFE_REG2_CMP2_SELP_POS  14                                                              // SYS_AFE_REG2_CMP2_SELP起始位
#define SYS_AFE_REG2_CMP2_SELP_MASK (uint32_t)((uint32_t)0x3 << SYS_AFE_REG2_CMP2_SELP_POS)         // SYS_AFE_REG2_CMP2_SELP位掩码
#define SYS_AFE_REG2_CMP2_SELP(x)   (uint32_t)((uint32_t)((x) & 0x3) << SYS_AFE_REG2_CMP2_SELP_POS) // [15:14] 比较器2信号正端选择00: 连CMP2_IP001: 连 CMP2_IP110: 连OPA2_OUT11: 连OPA3_OUT
#define SYS_AFE_REG2_XTRSEL_BIT     BIT8                                                            // [8] 晶体起振电路电阻调节XTRSEL=1: P端电阻增加一倍，从而降低晶振起振速度
#define SYS_AFE_REG2_REF_AD_EN_BIT  BIT4                                                            // [4] 输出1.2V Reference到P2.7
#define SYS_AFE_REG2_LDOOUT_EN_BIT  BIT3                                                            // [3] 输出LDO15到P2.7
#define SYS_AFE_REG2_OPAOUT_EN_MAX  ((uint32_t)0x7)                                                 // SYS_AFE_REG2_OPAOUT_EN最大值
#define SYS_AFE_REG2_OPAOUT_EN_POS  0                                                               // SYS_AFE_REG2_OPAOUT_EN起始位
#define SYS_AFE_REG2_OPAOUT_EN_MASK (uint32_t)((uint32_t)0x7 << SYS_AFE_REG2_OPAOUT_EN_POS)         // SYS_AFE_REG2_OPAOUT_EN位掩码
#define SYS_AFE_REG2_OPAOUT_EN(x)   (uint32_t)((uint32_t)((x) & 0x7) << SYS_AFE_REG2_OPAOUT_EN_POS) // [2:0] 使能OPAx输出信号送至IO口p2_7000:不输出; 001:输出OPA0信号到IO口;010:输出OPA1信号到IO口; 011:输出OPA2信号到IO口;100:输出OPA3信号到IO口;101~111: 不允许此配置

/* SYS_AFE_REG3 模拟配置寄存器3 */
#define SYS_AFE_REG3_DAC1OUT_EN_BIT BIT15                                                           // [15] DAC1输出到IO使能0: 不使能1:使能输出到IO P0[0]
#define SYS_AFE_REG3_CMP1_SELP_MAX  ((uint32_t)0x7)                                                 // SYS_AFE_REG3_CMP1_SELP最大值
#define SYS_AFE_REG3_CMP1_SELP_POS  12                                                              // SYS_AFE_REG3_CMP1_SELP起始位
#define SYS_AFE_REG3_CMP1_SELP_MASK (uint32_t)((uint32_t)0x7 << SYS_AFE_REG3_CMP1_SELP_POS)         // SYS_AFE_REG3_CMP1_SELP位掩码
#define SYS_AFE_REG3_CMP1_SELP(x)   (uint32_t)((uint32_t)((x) & 0x7) << SYS_AFE_REG3_CMP1_SELP_POS) // [14:12] 比较器1信号正端选择000: CMP1_IP0001: OPA3_IP010: OPA2_OUT011: OPA3_OUT100: CMP1_IP1101: CMP1_IP2110: CMP1_IP3111: DAC0输出说明:上述除AVSS/OPA2_OUT/OPA3_OUT外都为管脚名称，请参看datasheet里管脚定义章节
#define SYS_AFE_REG3_DAC0OUT_EN_BIT BIT11                                                           // [11] DAC0输出到IO使能0: 不使能1:使能输出到IO P0[0]
#define SYS_AFE_REG3_CMP0_SELP_MAX  ((uint32_t)0x7)                                                 // SYS_AFE_REG3_CMP0_SELP最大值
#define SYS_AFE_REG3_CMP0_SELP_POS  8                                                               // SYS_AFE_REG3_CMP0_SELP起始位
#define SYS_AFE_REG3_CMP0_SELP_MASK (uint32_t)((uint32_t)0x7 << SYS_AFE_REG3_CMP0_SELP_POS)         // SYS_AFE_REG3_CMP0_SELP位掩码
#define SYS_AFE_REG3_CMP0_SELP(x)   (uint32_t)((uint32_t)((x) & 0x7) << SYS_AFE_REG3_CMP0_SELP_POS) // [10:8] 比较器0信号正端选择000: CMP0_IP0001: OPA0_IP010: OPA0_OUT011: OPA1_OUT100: CMP0_IP1101: CMP0_IP2110: CMP0_IP3111: CMP0_IP4说明:上述除OPA0_OUT/OPA1_OUT外都为管脚名称，请参看datasheet里管脚定义章节
#define SYS_AFE_REG3_CMP_HYS_BIT    BIT7                                                            // [7] 比较器回差选择，采用默认配置0: 20mv;1: 0mv
#define SYS_AFE_REG3_CMP1_SELN_MAX  ((uint32_t)0x3)                                                 // SYS_AFE_REG3_CMP1_SELN最大值
#define SYS_AFE_REG3_CMP1_SELN_POS  4                                                               // SYS_AFE_REG3_CMP1_SELN起始位
#define SYS_AFE_REG3_CMP1_SELN_MASK (uint32_t)((uint32_t)0x3 << SYS_AFE_REG3_CMP1_SELN_POS)         // SYS_AFE_REG3_CMP1_SELN位掩码
#define SYS_AFE_REG3_CMP1_SELN(x)   (uint32_t)((uint32_t)((x) & 0x3) << SYS_AFE_REG3_CMP1_SELN_POS) // [5:4] 比较器1信号负端选择00: CMP1_IN01: REF10: DAC0输出11: BEMF1_MID说明:上述CMP1_IN为管脚名称，请参看datasheet里管脚定义章节；REF为芯片内部1.2V BANDGAP基准源；DAC输出即为芯片内部DAC模块输出模拟信号；BEMF1_MID为CMP1_IP1, CMP1_IP2, CMP1_IP3信号经电阻星形连接后得到的平均值
#define SYS_AFE_REG3_CMP0_SELN_MAX  ((uint32_t)0x3)                                                 // SYS_AFE_REG3_CMP0_SELN最大值
#define SYS_AFE_REG3_CMP0_SELN_POS  2                                                               // SYS_AFE_REG3_CMP0_SELN起始位
#define SYS_AFE_REG3_CMP0_SELN_MASK (uint32_t)((uint32_t)0x3 << SYS_AFE_REG3_CMP0_SELN_POS)         // SYS_AFE_REG3_CMP0_SELN位掩码
#define SYS_AFE_REG3_CMP0_SELN(x)   (uint32_t)((uint32_t)((x) & 0x3) << SYS_AFE_REG3_CMP0_SELN_POS) // [3:2] 比较器0信号负端选择00: CMP0_IN01: REF 10: DAC0输出11: BEMF0_MID说明:上述CMP0_IN为管脚名称，请参看datasheet里管脚定义章节；REF为芯片内部1.2V BANDGAP基准源；DAC输出即为芯片内部DAC模块输出模拟信号；BEMF0_MID为CMP0_IP1, CMP0_IP2, CMP0_IP3信号经电阻星形连接后得到的平均值
#define SYS_AFE_REG3_CMP2_SELN_MAX  ((uint32_t)0x3)                                                 // SYS_AFE_REG3_CMP2_SELN最大值
#define SYS_AFE_REG3_CMP2_SELN_POS  0                                                               // SYS_AFE_REG3_CMP2_SELN起始位
#define SYS_AFE_REG3_CMP2_SELN_MASK (uint32_t)((uint32_t)0x3 << SYS_AFE_REG3_CMP2_SELN_POS)         // SYS_AFE_REG3_CMP2_SELN位掩码
#define SYS_AFE_REG3_CMP2_SELN(x)   (uint32_t)((uint32_t)((x) & 0x3) << SYS_AFE_REG3_CMP2_SELN_POS) // [1:0] 比较器2信号负端选择00: CMP2_IN01: REF10: DAC0输出11: DAC1输出

/* SYS_AFE_REG4 模拟配置寄存器4 */

/* SYS_AFE_REG5 模拟配置寄存器5 */
#define SYS_AFE_REG5_PLLPDN_BIT  BIT15 // [15] PLL关闭控制0:关闭PLL（默认）1:开启PLL
#define SYS_AFE_REG5_XTALPDN_BIT BIT14 // [14] 晶体起振电路开关0:关闭（默认）1:开启
#define SYS_AFE_REG5_TMPPDN_BIT  BIT13 // [13] 温度传感器开关0:关闭（默认）1:开启
#define SYS_AFE_REG5_DAC0PDN_BIT BIT12 // [12] DAC0开关0:关闭（默认）1:开启
#define SYS_AFE_REG5_CMP2PDN_BIT BIT11 // [11] CMP2开启使能0:关闭（默认）1:开启
#define SYS_AFE_REG5_RCHPD_BIT   BIT10 // [10] RCH时钟关闭使能0:开启（默认）1:关闭
#define SYS_AFE_REG5_DAC1PDN_BIT BIT9  // [9] DAC1开关0:关闭（默认）1:开启
#define SYS_AFE_REG5_BGPPD_BIT   BIT8  // [8] BGP关闭使能0:开启（默认）1:关闭
#define SYS_AFE_REG5_CMP1PDN_BIT BIT7  // [7] CMP1开启使能0:关闭（默认）1:开启
#define SYS_AFE_REG5_CMP0PDN_BIT BIT6  // [6] CMP0开启使能0:关闭（默认）1:开启
#define SYS_AFE_REG5_OPA3PDN_BIT BIT5  // [5] OPA3 开启使能0:关闭（默认）1:开启
#define SYS_AFE_REG5_OPA2PDN_BIT BIT4  // [4] OPA2 开启使能0:关闭（默认）1:开启
#define SYS_AFE_REG5_OPA1PDN_BIT BIT3  // [3] OPA1 开启使能0:关闭（默认）1:开启
#define SYS_AFE_REG5_OPA0PDN_BIT BIT2  // [2] OPA0 开启使能0:关闭（默认）1:开启
#define SYS_AFE_REG5_ADCPDN_BIT  BIT0  // [0] ADC 开启使能0:关闭（默认）1:开启

/* SYS_AFE_REG6 模拟配置寄存器6 */
#define SYS_AFE_REG6_PLLSR_SEL_BIT BIT15                                                        // [15] PLL时钟源选择0: 使用RCH作为输入时钟源; 1: 使用XTAL OSC作为输入时钟源
#define SYS_AFE_REG6_PVDSEL_MAX    ((uint32_t)0x3)                                              // SYS_AFE_REG6_PVDSEL最大值
#define SYS_AFE_REG6_PVDSEL_POS    8                                                            // SYS_AFE_REG6_PVDSEL起始位
#define SYS_AFE_REG6_PVDSEL_MASK   (uint32_t)((uint32_t)0x3 << SYS_AFE_REG6_PVDSEL_POS)         // SYS_AFE_REG6_PVDSEL位掩码
#define SYS_AFE_REG6_PVDSEL(x)     (uint32_t)((uint32_t)((x) & 0x3) << SYS_AFE_REG6_PVDSEL_POS) // [9:8] 电源掉电监测阈值Vth选择00: 4.00V01: 3.75V10: 3.50V11: 3.25V (SYS_AFE_INFO.VERSION\<=3)2.50V (SYS_AFE_INFO.VERSION=4)以上阈值为VSR_PDT=0，即选择低功耗基准源VBGP时的设定值；如果VSR_PDT=1，选择DAC输出作为基准，则阈值相应调整为Vth\*DAC0_OUT/VBGP
#define SYS_AFE_REG6_VSR_PDT_BIT   BIT1                                                         // [1] 掉电检测基准源选择，其中低功耗基准源VBGP为1.3V左右，DAC输出则可以通过软件配置0: 选择低功耗基准源VBGP; 1: 选择DAC0输出
#define SYS_AFE_REG6_PD_PDT_BIT    BIT0                                                         // [0] 关闭掉电检测电路0: 开启1: 关闭

/* SYS_AFE_REG7 模拟配置寄存器7 */
#define SYS_AFE_REG7_ADCLKSEL_BIT BIT4 // [4] ADC时钟频率选择0: 48MHz1: 24MHz

/* SYS_AFE_DAC_CTRL DAC控制寄存器 */
#define SYS_AFE_DAC_CTRL_DAC1_STEP_MAX        ((uint32_t)0x7)                                                     // SYS_AFE_DAC_CTRL_DAC1_STEP最大值
#define SYS_AFE_DAC_CTRL_DAC1_STEP_POS        12                                                                  // SYS_AFE_DAC_CTRL_DAC1_STEP起始位
#define SYS_AFE_DAC_CTRL_DAC1_STEP_MASK       (uint32_t)((uint32_t)0x7 << SYS_AFE_DAC_CTRL_DAC1_STEP_POS)         // SYS_AFE_DAC_CTRL_DAC1_STEP位掩码
#define SYS_AFE_DAC_CTRL_DAC1_STEP(x)         (uint32_t)((uint32_t)((x) & 0x7) << SYS_AFE_DAC_CTRL_DAC1_STEP_POS) // [14:12] SYS_AFE_DAC1步进值，3bit有符号数，范围-4~3
#define SYS_AFE_DAC_CTRL_TIMER3_TRIG_DAC1_BIT BIT11                                                               // [11] TIMER3过零事件触发DAC1步进使能，高有效
#define SYS_AFE_DAC_CTRL_TIMER2_TRIG_DAC1_BIT BIT10                                                               // [10] TIMER2过零事件触发DAC1步进使能，高有效
#define SYS_AFE_DAC_CTRL_TIMER1_TRIG_DAC1_BIT BIT9                                                                // [9] TIMER1过零事件触发DAC1步进使能，高有效
#define SYS_AFE_DAC_CTRL_TIMER0_TRIG_DAC1_BIT BIT8                                                                // [8] TIMER0过零事件触发DAC1步进使能，高有效
#define SYS_AFE_DAC_CTRL_DAC0_STEP_MAX        ((uint32_t)0x7)                                                     // SYS_AFE_DAC_CTRL_DAC0_STEP最大值
#define SYS_AFE_DAC_CTRL_DAC0_STEP_POS        4                                                                   // SYS_AFE_DAC_CTRL_DAC0_STEP起始位
#define SYS_AFE_DAC_CTRL_DAC0_STEP_MASK       (uint32_t)((uint32_t)0x7 << SYS_AFE_DAC_CTRL_DAC0_STEP_POS)         // SYS_AFE_DAC_CTRL_DAC0_STEP位掩码
#define SYS_AFE_DAC_CTRL_DAC0_STEP(x)         (uint32_t)((uint32_t)((x) & 0x7) << SYS_AFE_DAC_CTRL_DAC0_STEP_POS) // [6:4] SYS_AFE_DAC0步进值，3bit有符号数，范围-4~3
#define SYS_AFE_DAC_CTRL_TIMER3_TRIG_DAC0_BIT BIT3                                                                // [3] TIMER3过零事件触发DAC0步进使能，高有效
#define SYS_AFE_DAC_CTRL_TIMER2_TRIG_DAC0_BIT BIT2                                                                // [2] TIMER2过零事件触发DAC0步进使能，高有效
#define SYS_AFE_DAC_CTRL_TIMER1_TRIG_DAC0_BIT BIT1                                                                // [1] TIMER1过零事件触发DAC0步进使能，高有效
#define SYS_AFE_DAC_CTRL_TIMER0_TRIG_DAC0_BIT BIT0                                                                // [0] TIMER0过零事件触发DAC0步进使能，高有效

/* SYS_AFE_DAC0 DAC0数字量寄存器 */
#define SYS_AFE_DAC0_DAC_IN_MAX  ((uint32_t)0xFFF)                                              // SYS_AFE_DAC0_DAC_IN最大值
#define SYS_AFE_DAC0_DAC_IN_POS  0                                                              // SYS_AFE_DAC0_DAC_IN起始位
#define SYS_AFE_DAC0_DAC_IN_MASK (uint32_t)((uint32_t)0xFFF << SYS_AFE_DAC0_DAC_IN_POS)         // SYS_AFE_DAC0_DAC_IN位掩码
#define SYS_AFE_DAC0_DAC_IN(x)   (uint32_t)((uint32_t)((x) & 0xFFF) << SYS_AFE_DAC0_DAC_IN_POS) // [11:0] DAC待转换的数字量输入

/* SYS_AFE_DAC1 DAC1数字量寄存器 */
#define SYS_AFE_DAC1_DAC_IN_MAX  ((uint32_t)0xFFF)                                              // SYS_AFE_DAC1_DAC_IN最大值
#define SYS_AFE_DAC1_DAC_IN_POS  0                                                              // SYS_AFE_DAC1_DAC_IN起始位
#define SYS_AFE_DAC1_DAC_IN_MASK (uint32_t)((uint32_t)0xFFF << SYS_AFE_DAC1_DAC_IN_POS)         // SYS_AFE_DAC1_DAC_IN位掩码
#define SYS_AFE_DAC1_DAC_IN(x)   (uint32_t)((uint32_t)((x) & 0xFFF) << SYS_AFE_DAC1_DAC_IN_POS) // [11:0] DAC待转换的数字量输入

/* SYS_AFE_DAC0_AMC DAC0增益校正寄存器 */
#define SYS_AFE_DAC0_AMC_AMC_MAX  ((uint32_t)0x3FF)                                               // SYS_AFE_DAC0_AMC_AMC最大值
#define SYS_AFE_DAC0_AMC_AMC_POS  0                                                               // SYS_AFE_DAC0_AMC_AMC起始位
#define SYS_AFE_DAC0_AMC_AMC_MASK (uint32_t)((uint32_t)0x3FF << SYS_AFE_DAC0_AMC_AMC_POS)         // SYS_AFE_DAC0_AMC_AMC位掩码
#define SYS_AFE_DAC0_AMC_AMC(x)   (uint32_t)((uint32_t)((x) & 0x3FF) << SYS_AFE_DAC0_AMC_AMC_POS) // [9:0] DAC0增益校正值，10bit无符号定点数，B[9]为整数，B[8:0]为小数

/* SYS_AFE_DAC0_DC DAC0直流偏置寄存器 */
#define SYS_AFE_DAC0_DC_DC_MAX  ((uint32_t)0x3FF)                                             // SYS_AFE_DAC0_DC_DC最大值
#define SYS_AFE_DAC0_DC_DC_POS  0                                                             // SYS_AFE_DAC0_DC_DC起始位
#define SYS_AFE_DAC0_DC_DC_MASK (uint32_t)((uint32_t)0x3FF << SYS_AFE_DAC0_DC_DC_POS)         // SYS_AFE_DAC0_DC_DC位掩码
#define SYS_AFE_DAC0_DC_DC(x)   (uint32_t)((uint32_t)((x) & 0x3FF) << SYS_AFE_DAC0_DC_DC_POS) // [9:0] DAC0直流偏置，10bit有符号数，B[9]为符号位

/* SYS_AFE_DAC1_AMC DAC1增益校正寄存器 */
#define SYS_AFE_DAC1_AMC_AMC_MAX  ((uint32_t)0x3FF)                                               // SYS_AFE_DAC1_AMC_AMC最大值
#define SYS_AFE_DAC1_AMC_AMC_POS  0                                                               // SYS_AFE_DAC1_AMC_AMC起始位
#define SYS_AFE_DAC1_AMC_AMC_MASK (uint32_t)((uint32_t)0x3FF << SYS_AFE_DAC1_AMC_AMC_POS)         // SYS_AFE_DAC1_AMC_AMC位掩码
#define SYS_AFE_DAC1_AMC_AMC(x)   (uint32_t)((uint32_t)((x) & 0x3FF) << SYS_AFE_DAC1_AMC_AMC_POS) // [9:0] DAC1增益校正值，10bit无符号定点数，B[9]为整数，B[8:0]为小数

/* SYS_AFE_DAC1_DC DAC1直流偏置寄存器 */
#define SYS_AFE_DAC1_DC_DC_MAX  ((uint32_t)0x3FF)                                             // SYS_AFE_DAC1_DC_DC最大值
#define SYS_AFE_DAC1_DC_DC_POS  0                                                             // SYS_AFE_DAC1_DC_DC起始位
#define SYS_AFE_DAC1_DC_DC_MASK (uint32_t)((uint32_t)0x3FF << SYS_AFE_DAC1_DC_DC_POS)         // SYS_AFE_DAC1_DC_DC位掩码
#define SYS_AFE_DAC1_DC_DC(x)   (uint32_t)((uint32_t)((x) & 0x3FF) << SYS_AFE_DAC1_DC_DC_POS) // [9:0] DAC1直流偏置，10bit有符号数，B[9]为符号位

/* SYS_CLK_CFG 时钟控制寄存器 */
#define SYS_CLK_CFG_HSE_FAILED_BIT BIT13                                                         // [13] 晶振时钟在被开启后是否停振过如果晶振有停振情况，则该位置位，即使晶体后续恢复振荡，仍保持记录为1。写1清零
#define SYS_CLK_CFG_HSE_FAIL_BIT   BIT12                                                         // [12] 晶振时钟当前是否已经停振0：外部晶体当前正常工作1：外部晶体当前已经停振
#define SYS_CLK_CFG_CLK_SEL_MAX    ((uint32_t)0x3)                                               // SYS_CLK_CFG_CLK_SEL最大值
#define SYS_CLK_CFG_CLK_SEL_POS    8                                                             // SYS_CLK_CFG_CLK_SEL起始位
#define SYS_CLK_CFG_CLK_SEL_MASK   (uint32_t)((uint32_t)0x3 << SYS_CLK_CFG_CLK_SEL_POS)          // SYS_CLK_CFG_CLK_SEL位掩码
#define SYS_CLK_CFG_CLK_SEL(x)     (uint32_t)((uint32_t)((x) & 0x3) << SYS_CLK_CFG_CLK_SEL_POS)  // [9:8] 系统时钟MCLK的来源选择信号。默认选择HRC0: HRC1: PLL2: LRC3: XTAL注意，PLL/XTAL在上电后默认关闭，需要软件来开启。
#define SYS_CLK_CFG_CLK_DIV_MAX    ((uint32_t)0xFF)                                              // SYS_CLK_CFG_CLK_DIV最大值
#define SYS_CLK_CFG_CLK_DIV_POS    0                                                             // SYS_CLK_CFG_CLK_DIV起始位
#define SYS_CLK_CFG_CLK_DIV_MASK   (uint32_t)((uint32_t)0xFF << SYS_CLK_CFG_CLK_DIV_POS)         // SYS_CLK_CFG_CLK_DIV位掩码
#define SYS_CLK_CFG_CLK_DIV(x)     (uint32_t)((uint32_t)((x) & 0xFF) << SYS_CLK_CFG_CLK_DIV_POS) // [7:0] PLL输出分频控制，默认为0x00: 1/8分频0x01: 1/8分频0x11: 1/4分频0x55: 1/2分频0xFF: 1/1分频不推荐其它配置值。

/* SYS_IO_CFG IO 控制寄存器 */
#define SYS_IO_CFG_SWDMUX_BIT BIT6 // [6] SWD复用控制信号，默认配置为SWD0:P2.14复用为SWCLK，P2.15 复用为SWDIO1:P2.14, P2.15作为正常GPIO使用
#define SYS_IO_CFG_RST_IO_BIT BIT5 // [5] RSTn/P0.2复用控制信号，默认配置为RSTn0:RSTn1:P0.2注意，上电后默认是RSTn，后续软件可使能此位，RSTn功能失效

/* SYS_DBG_CFG Debug 控制寄存器 */
#define SYS_DBG_CFG_SW_IRQ_TRIG_MAX   ((uint32_t)0xFFFF)                                                  // SYS_DBG_CFG_SW_IRQ_TRIG最大值
#define SYS_DBG_CFG_SW_IRQ_TRIG_POS   16                                                                  // SYS_DBG_CFG_SW_IRQ_TRIG起始位
#define SYS_DBG_CFG_SW_IRQ_TRIG_MASK  (uint32_t)((uint32_t)0xFFFF << SYS_DBG_CFG_SW_IRQ_TRIG_POS)         // SYS_DBG_CFG_SW_IRQ_TRIG位掩码
#define SYS_DBG_CFG_SW_IRQ_TRIG(x)    (uint32_t)((uint32_t)((x) & 0xFFFF) << SYS_DBG_CFG_SW_IRQ_TRIG_POS) // [31:16] 向此位段写入0x5AA5 触发软件中断，SW_IRQ置1
#define SYS_DBG_CFG_SW_IRQ_BIT        BIT15                                                               // [15] 软件中断标志，对应中断号30，写1清零。
#define SYS_DBG_CFG_SFT_RST_PERI_BIT  BIT14                                                               // [14] Debug软复位是否复位除Flash/SYS_AFE以外的外设寄存器
#define SYS_DBG_CFG_DBG_TIM3_STOP_BIT BIT11                                                               // [11] 调试模式下CPU halt状态Timer3停止1:Timer3在CPU halt状态时停止计数0:Timer3在CPU halt状态时继续计数
#define SYS_DBG_CFG_DBG_TIM2_STOP_BIT BIT10                                                               // [10] 调试模式下CPU halt状态Timer2停止1:Timer2在CPU halt状态时停止计数0:Timer2在CPU halt状态时继续计数
#define SYS_DBG_CFG_DBG_TIM1_STOP_BIT BIT9                                                                // [9] 调试模式下CPU halt状态Timer1停止1:Timer1在CPU halt状态时停止计数0:Timer1在CPU halt状态时继续计数
#define SYS_DBG_CFG_DBG_TIM0_STOP_BIT BIT8                                                                // [8] 调试模式下CPU halt状态Timer0停止1:Timer0在CPU halt状态时停止计数0:Timer0在CPU halt状态时继续计数
#define SYS_DBG_CFG_DBG_IWDG_STOP_BIT BIT5                                                                // [5] 调试模式下CPU halt状态独立看门狗停止1:独立看门狗在CPU halt状态时停止计数0:独立看门狗在CPU halt状态时继续计数
#define SYS_DBG_CFG_DBG_STOP_BIT      BIT1                                                                // [1] 调试STOP模式0: (FCLK=Off, HCLK=Off) 在STOP模式下，时钟管理模块关闭HCLK和FCLK，即处理器时钟和所有外设时钟。当退出STOP模式时，时钟管理模块不经历复位，并保持原有配置，可以恢复到STOP模式前的时钟设置。在STOP模式中，所有外设寄存器均保持，因此退出后无需重新配置。1: (FCLK=On, HCLK=On) 如果设置DBG_STOP为1，进入STOP模式后HCLK和FCLK均不被关闭。通过设置SCB-\>SCR = (1UL\<\<2)，然后使用__WFI()/___WFE()指令进入STOP模式。
#define SYS_DBG_CFG_DBG_SLP_BIT       BIT0                                                                // [0] 调试睡眠(SLEEP)模式0: (FCLK=On, HCLK=Off) 在睡眠模式中，FCLK作为所有外设时钟，不关闭； HCLK作为CPU时钟，被关闭。在睡眠模式中，只有CPU时钟被暂时挂起，而所有外设包括系统时钟管理模块均保持原有配置状态。因此退出睡眠模式时，软件无需重新配置外设寄存器。1: (FCLK=On, HCLK=On) 如果配置DBG_SLP为1，则当进入睡眠模式时，HCLK不会关闭。通过__WFI()/___WFE()指令可以令处理器进入睡眠模式

/* SYS_CLK_DIV0 外设时钟分频寄存器0 */
#define SYS_CLK_DIV0_DIV0_MAX  ((uint32_t)0xFFFF)                                            // SYS_CLK_DIV0_DIV0最大值
#define SYS_CLK_DIV0_DIV0_POS  0                                                             // SYS_CLK_DIV0_DIV0起始位
#define SYS_CLK_DIV0_DIV0_MASK (uint32_t)((uint32_t)0xFFFF << SYS_CLK_DIV0_DIV0_POS)         // SYS_CLK_DIV0_DIV0位掩码
#define SYS_CLK_DIV0_DIV0(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << SYS_CLK_DIV0_DIV0_POS) // [15:0] I2C工作时钟=MCLK/(CLK_DIV0+1)。其中MCLK由SYS_CLK_CFG分频系数决定

/* SYS_CLK_DIV2 外设时钟分频寄存器2 */
#define SYS_CLK_DIV2_DIV2_MAX  ((uint32_t)0xFFFF)                                            // SYS_CLK_DIV2_DIV2最大值
#define SYS_CLK_DIV2_DIV2_POS  0                                                             // SYS_CLK_DIV2_DIV2起始位
#define SYS_CLK_DIV2_DIV2_MASK (uint32_t)((uint32_t)0xFFFF << SYS_CLK_DIV2_DIV2_POS)         // SYS_CLK_DIV2_DIV2位掩码
#define SYS_CLK_DIV2_DIV2(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << SYS_CLK_DIV2_DIV2_POS) // [15:0] UART工作时钟=MCLK/(CLK_DIV2+1)。UART0/UART1共享此分频配置，波特率根据UART波特率寄存器进一步分频，其中MCLK由SYS_CLK_CFG分频系数决定。

/* SYS_CLK_FEN 外设时钟门控寄存器 */
#define SYS_CLK_FEN_CL0_CLK_EN_BIT    BIT21 // [21] CL0模块时钟控制信号，默认关闭CL0模块时钟1:使能CL0模块时钟0:关闭CL0模块时钟
#define SYS_CLK_FEN_SIF0_CLK_EN_BIT   BIT20 // [20] SIF0模块时钟控制信号，默认关闭SIF0模块时钟1:使能SIF0模块时钟0:关闭SIF0模块时钟
#define SYS_CLK_FEN_CAN0_CLK_EN_BIT   BIT19 // [19] CAN0模块时钟控制信号，默认关闭CAN0模块时钟1:使能CAN0模块时钟0:关闭CAN0模块时钟
#define SYS_CLK_FEN_DSP0_CLK_EN_BIT   BIT17 // [17] DSP0模块时钟控制信号，默认关闭DSP0模块时钟1:使能DSP0模块时钟0:关闭DSP0模块时钟
#define SYS_CLK_FEN_CRC0_CLK_EN_BIT   BIT16 // [16] CRC0模块时钟控制信号，默认关闭CRC0模块时钟1:使能CRC0模块时钟0:关闭CRC0模块时钟
#define SYS_CLK_FEN_UART1_CLK_EN_BIT  BIT15 // [15] UART1模块时钟控制信号，默认关闭UART1模块时钟1:使能UART1模块时钟0:关闭UART1模块时钟
#define SYS_CLK_FEN_UART0_CLK_EN_BIT  BIT14 // [14] UART0模块时钟控制信号，默认关闭UART0模块时钟1:使能UART0模块时钟0:关闭UART0模块时钟
#define SYS_CLK_FEN_GPIO_CLK_EN_BIT   BIT11 // [11] GPIO模块时钟控制信号，默认关闭GPIO模块时钟1:使能GPIO模块时钟0:关闭GPIO模块时钟
#define SYS_CLK_FEN_MCPWM0_CLK_EN_BIT BIT10 // [10] MCPWM0模块时钟控制信号，默认关闭MCPWM0模块时钟1:使能MCPWM0模块时钟0:关闭MCPWM0模块时钟
#define SYS_CLK_FEN_QEP1_CLK_EN_BIT   BIT9  // [9] QEP1模块时钟控制信号，默认关闭QEP1模块时钟1:使能QEP1模块时钟0:关闭QEP1模块时钟
#define SYS_CLK_FEN_QEP0_CLK_EN_BIT   BIT8  // [8] QEP0模块时钟控制信号，默认关闭QEP0模块时钟1:使能QEP0模块时钟0:关闭QEP0模块时钟
#define SYS_CLK_FEN_TIMER3_CLK_EN_BIT BIT7  // [7] TIMER3模块时钟控制信号，默认关闭TIMER3模块时钟1:使能TIMER3模块时钟0:关闭TIMER3模块时钟
#define SYS_CLK_FEN_TIMER2_CLK_EN_BIT BIT6  // [6] TIMER2模块时钟控制信号，默认关闭TIMER2模块时钟1:使能TIMER2模块时钟0:关闭TIMER2模块时钟
#define SYS_CLK_FEN_TIMER1_CLK_EN_BIT BIT5  // [5] TIMER1模块时钟控制信号，默认关闭TIMER1模块时钟1:使能TIMER1模块时钟0:关闭TIMER1模块时钟
#define SYS_CLK_FEN_TIMER0_CLK_EN_BIT BIT4  // [4] TIMER0模块时钟控制信号，默认关闭TIMER0模块时钟1:使能TIMER0模块时钟0:关闭TIMER0模块时钟
#define SYS_CLK_FEN_HALL0_CLK_EN_BIT  BIT3  // [3] HALL0模块时钟控制信号，默认关闭HALL0模块时钟1:使能HALL0模块时钟0:关闭HALL0模块时钟
#define SYS_CLK_FEN_CMP_CLK_EN_BIT    BIT2  // [2] CMP模块时钟控制信号，默认关闭CMP模块时钟1:使能CMP模块时钟0:关闭CMP模块时钟
#define SYS_CLK_FEN_I2C0_CLK_EN_BIT   BIT1  // [1] I2C0模块时钟控制信号，默认关闭I2C0模块时钟1:使能I2C0模块时钟0:关闭I2C0模块时钟
#define SYS_CLK_FEN_SPI0_CLK_EN_BIT   BIT0  // [0] SPI0模块时钟控制信号，默认关闭SPI0模块时钟1:使能SPI0模块时钟0:关闭SPI0模块时钟

/* SYS_SFT_RST 软复位寄存器 */
#define SYS_SFT_RST_CL0_SFT_RST_BIT    BIT21 // [21] CL0模块软复位信号，默认不复位CL0模块1:复位CL0模块0:释放CL0模块
#define SYS_SFT_RST_SIF0_SFT_RST_BIT   BIT20 // [20] SIF0模块软复位信号，默认不复位SIF0模块1:复位SIF0模块0:释放SIF0模块
#define SYS_SFT_RST_CAN0_SFT_RST_BIT   BIT19 // [19] CAN0模块软复位信号，默认不复位CAN0模块1:复位CAN0模块0:释放CAN0模块
#define SYS_SFT_RST_DMA0_SFT_RST_BIT   BIT18 // [18] DMA0模块软复位信号，默认不复位DMA0模块1:复位DMA0模块0:释放DMA0模块
#define SYS_SFT_RST_DSP0_SFT_RST_BIT   BIT17 // [17] DSP0模块软复位信号，默认不复位DSP0模块1:复位DSP0模块0:释放DSP0模块
#define SYS_SFT_RST_CRC0_SFT_RST_BIT   BIT16 // [16] CRC0数字接口模块软复位信号，默认不复位CRC0模块1:复位CRC0数字接口模块0:释放CRC0数字接口模块
#define SYS_SFT_RST_UART1_SFT_RST_BIT  BIT15 // [15] UART1模块软复位信号，默认不复位UART1模块1:复位UART1模块0:释放UART1模块
#define SYS_SFT_RST_UART0_SFT_RST_BIT  BIT14 // [14] UART0模块软复位信号，默认不复位UART0模块1:复位UART0模块0:释放UART0模块
#define SYS_SFT_RST_ADC1_SFT_RST_BIT   BIT13 // [13] ADC1数字接口模块软复位信号，默认不复位ADC1模块1:复位ADC1数字接口模块0:释放ADC1数字接口模块
#define SYS_SFT_RST_ADC0_SFT_RST_BIT   BIT12 // [12] ADC0数字接口模块软复位信号，默认不复位ADC0模块1:复位ADC0数字接口模块0:释放ADC0数字接口模块
#define SYS_SFT_RST_GPIO_SFT_RST_BIT   BIT11 // [11] GPIO模块软复位信号，默认不复位GPIO模块1:复位GPIO模块0:释放GPIO模块
#define SYS_SFT_RST_MCPWM0_SFT_RST_BIT BIT10 // [10] MCPWM0模块软复位信号，默认不复位MCPWM0模块1:复位MCPWM0模块0:释放MCPWM0模块
#define SYS_SFT_RST_QEP1_SFT_RST_BIT   BIT9  // [9] QEP1模块软复位信号，默认不复位QEP1模块1:复位QEP1模块0:释放QEP1模块
#define SYS_SFT_RST_QEP0_SFT_RST_BIT   BIT8  // [8] QEP0模块软复位信号，默认不复位QEP0模块1:复位QEP0模块0:释放QEP0模块
#define SYS_SFT_RST_TIMER3_SFT_RST_BIT BIT7  // [7] TIMER3模块软复位信号，默认不复位TIMER3模块1:复位TIMER3模块0:释放TIMER3模块
#define SYS_SFT_RST_TIMER2_SFT_RST_BIT BIT6  // [6] TIMER2模块软复位信号，默认不复位TIMER2模块1:复位TIMER2模块0:释放TIMER2模块
#define SYS_SFT_RST_TIMER1_SFT_RST_BIT BIT5  // [5] TIMER1模块软复位信号，默认不复位TIMER1模块1:复位TIMER1模块0:释放TIMER1模块
#define SYS_SFT_RST_TIMER0_SFT_RST_BIT BIT4  // [4] TIMER0模块软复位信号，默认不复位TIMER0模块1:复位TIMER0模块0:释放TIMER0模块
#define SYS_SFT_RST_HALL0_SFT_RST_BIT  BIT3  // [3] HALL0模块软复位信号，默认不复位HALL0模块1:复位HALL0模块0:释放HALL0模块
#define SYS_SFT_RST_CMP_SFT_RST_BIT    BIT2  // [2] CMP模块软复位信号，默认不复位CMP模块1:复位CMP模块0:释放CMP模块
#define SYS_SFT_RST_I2C_0SFT_RST_BIT   BIT1  // [1] I2C0模块软复位信号，默认不复位I2C0模块1:复位I2C0模块0:释放I2C0模块
#define SYS_SFT_RST_SPI0_SFT_RST_BIT   BIT0  // [0] SPI0模块软复位信号，默认不复位SPI0模块1:复位SPI0模块0:释放SPI0模块

/* SYS_PROTECT 写保护寄存器 */
#define SYS_PROTECT_PSW_MAX  ((uint32_t)0xFFFF)                                          // SYS_PROTECT_PSW最大值
#define SYS_PROTECT_PSW_POS  0                                                           // SYS_PROTECT_PSW起始位
#define SYS_PROTECT_PSW_MASK (uint32_t)((uint32_t)0xFFFF << SYS_PROTECT_PSW_POS)         // SYS_PROTECT_PSW位掩码
#define SYS_PROTECT_PSW(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << SYS_PROTECT_PSW_POS) // [15:0] 除SYS_AFE_DAC0、SYS_AFE_DAC0_AMC、SYS_AFE_DAC0_DC、SYS_AFE_DAC1、SYS_AFE_DAC1_AMC、SYS_AFE_DAC1_DC外，其他系统寄存器(SYS_开头的寄存器，包括时钟复位管理以及模拟寄存器)受写保护，写入前需先写入密码解除写保护写入0x7A83，解除写保护，使能寄存器写操作写入其它值，开启写保护，禁止寄存器写操作读回恒为0

/* SYS_FLSE 擦除保护寄存器 */
#define SYS_FLSE_FLSE_MAX  ((uint32_t)0xFFFF)                                        // SYS_FLSE_FLSE最大值
#define SYS_FLSE_FLSE_POS  0                                                         // SYS_FLSE_FLSE起始位
#define SYS_FLSE_FLSE_MASK (uint32_t)((uint32_t)0xFFFF << SYS_FLSE_FLSE_POS)         // SYS_FLSE_FLSE位掩码
#define SYS_FLSE_FLSE(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << SYS_FLSE_FLSE_POS) // [15:0] FLASH擦除保护寄存器。本寄存器写入0x8FCA，FLASH的擦除功能才能最终生效。写入其他值，FLASH的擦除功能均无法生效。为防止误擦除，建议不使用擦除功能时，不生效此寄存器。

/* SYS_FLSP 编程保护寄存器 */
#define SYS_FLSP_FLSP_MAX  ((uint32_t)0xFFFF)                                        // SYS_FLSP_FLSP最大值
#define SYS_FLSP_FLSP_POS  0                                                         // SYS_FLSP_FLSP起始位
#define SYS_FLSP_FLSP_MASK (uint32_t)((uint32_t)0xFFFF << SYS_FLSP_FLSP_POS)         // SYS_FLSP_FLSP位掩码
#define SYS_FLSP_FLSP(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << SYS_FLSP_FLSP_POS) // [15:0] FLASH编程保护寄存器。本寄存器写入0x8F35，FLASH的编程功能才能最终生效。写入其他值，FLASH的编程功能均无法生效。为防止误编程，建议不使用编程功能时，不生效此寄存器。

/* FLASH在线升级(IAP) */

/* FLASH_CFG 配置寄存器（推荐先读回，按或/与方式修改） */
#define FLASH_CFG_ERS_EN_BIT   BIT31                                                   // [31] FLASH擦除使能。默认为0。0:关闭擦除1:开启擦除
#define FLASH_CFG_PRG_EN_BIT   BIT27                                                   // [27] FLASH编程使能。默认为0。0:关闭编程1:开启编程
#define FLASH_CFG_ADR_INC_BIT  BIT23                                                   // [23] FLASH地址递增使能。默认为0。0:关闭递增使能1:开启递增使能当执行FLASH连续读写访问时，可以开启此功能减少对地址的操作。
#define FLASH_CFG_PREF_BIT     BIT19                                                   // [19] FLASH预取加速使能。默认为0。0:关闭加速1:开启加速
#define FLASH_CFG_ERS_TYPE_BIT BIT15                                                   // [15] FLASH擦除类型选择。默认为0。0:Sector1:FULL
#define FLASH_CFG_REGION_BIT   BIT11                                                   // [11] 访问FLASH区域选择。默认为0。0:MAIN1:NVR
#define FLASH_CFG_WAIT_BIT     BIT7                                                    // [7] 读取FLASH数据，等待开关。默认为1。0:读取，等待一个周期1:读取，等待两个周期
#define FLASH_CFG_TBS_MAX      ((uint32_t)0x7F)                                        // FLASH_CFG_TBS最大值
#define FLASH_CFG_TBS_POS      0                                                       // FLASH_CFG_TBS起始位
#define FLASH_CFG_TBS_MASK     (uint32_t)((uint32_t)0x7F << FLASH_CFG_TBS_POS)         // FLASH_CFG_TBS位掩码
#define FLASH_CFG_TBS(x)       (uint32_t)((uint32_t)((x) & 0x7F) << FLASH_CFG_TBS_POS) // [6:0] 编程/擦除时间基数寄存器,默认值为0x60。只能配成如下几个值0x60:96Mhz系统频率下，FLASH编程/擦除时间基数配置值。0x30:48Mhz系统频率下，FLASH编程/擦除时间基数配置值。0x17:24Mhz系统频率下，FLASH编程/擦除时间基数配置值。

/* FLASH_ADDR 地址寄存器 */
#define FLASH_ADDR_ADDR_MAX  ((uint32_t)0x7FFF)                                          // FLASH_ADDR_ADDR最大值
#define FLASH_ADDR_ADDR_POS  0                                                           // FLASH_ADDR_ADDR起始位
#define FLASH_ADDR_ADDR_MASK (uint32_t)((uint32_t)0x7FFF << FLASH_ADDR_ADDR_POS)         // FLASH_ADDR_ADDR位掩码
#define FLASH_ADDR_ADDR(x)   (uint32_t)((uint32_t)((x) & 0x7FFF) << FLASH_ADDR_ADDR_POS) // [14:0] 地址寄存器。读/写/擦除操作对应的地址寄存器。因按照WORD操作，最低两位会被FLASH控制器忽略。执行擦除操作时，需要根据擦除类型，地址需要对齐。一个Sector是512-Byte。若执行Sector擦除，地址需要是512的整数倍（若带偏移，偏移量会被忽略）。全芯片擦除，不会参考这个寄存器的值

/* FLASH_WDATA 写数据寄存器 */
#define FLASH_WDATA_WDATA_MAX  ((uint32_t)0xFFFFFFFF)                                            // FLASH_WDATA_WDATA最大值
#define FLASH_WDATA_WDATA_POS  0                                                                 // FLASH_WDATA_WDATA起始位
#define FLASH_WDATA_WDATA_MASK (uint32_t)((uint32_t)0xFFFFFFFF << FLASH_WDATA_WDATA_POS)         // FLASH_WDATA_WDATA位掩码
#define FLASH_WDATA_WDATA(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << FLASH_WDATA_WDATA_POS) // [31:0] 执行写入操作，写入FLASH的值

/* FLASH_RDATA 读数据寄存器 */
#define FLASH_RDATA_RDATA_MAX  ((uint32_t)0xFFFFFFFF)                                            // FLASH_RDATA_RDATA最大值
#define FLASH_RDATA_RDATA_POS  0                                                                 // FLASH_RDATA_RDATA起始位
#define FLASH_RDATA_RDATA_MASK (uint32_t)((uint32_t)0xFFFFFFFF << FLASH_RDATA_RDATA_POS)         // FLASH_RDATA_RDATA位掩码
#define FLASH_RDATA_RDATA(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << FLASH_RDATA_RDATA_POS) // [31:0] 执行读取操作，读出FLASH的值

/* FLASH_ERASE 擦除控制寄存器 */
#define FLASH_ERASE_ERASE_MAX  ((uint32_t)0xFFFFFFFF)                                            // FLASH_ERASE_ERASE最大值
#define FLASH_ERASE_ERASE_POS  0                                                                 // FLASH_ERASE_ERASE起始位
#define FLASH_ERASE_ERASE_MASK (uint32_t)((uint32_t)0xFFFFFFFF << FLASH_ERASE_ERASE_POS)         // FLASH_ERASE_ERASE位掩码
#define FLASH_ERASE_ERASE(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << FLASH_ERASE_ERASE_POS) // [31:0] 写入0x7654DCBA，触发擦除操作

/* FLASH_PROTECT 保护状态寄存器 */
#define FLASH_PROTECT_PROTECT_MAX  ((uint32_t)0xFFFFFFFF)                                                // FLASH_PROTECT_PROTECT最大值
#define FLASH_PROTECT_PROTECT_POS  0                                                                     // FLASH_PROTECT_PROTECT起始位
#define FLASH_PROTECT_PROTECT_MASK (uint32_t)((uint32_t)0xFFFFFFFF << FLASH_PROTECT_PROTECT_POS)         // FLASH_PROTECT_PROTECT位掩码
#define FLASH_PROTECT_PROTECT(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << FLASH_PROTECT_PROTECT_POS) // [31:0] 读取该寄存器，更新加密/解密状态读取返回值无参考意义。

/* FLASH_READY */
#define FLASH_READY_READY_BIT BIT0 // [0] 1:FLASH处于Idle状态；0:FLASH处于Busy状态

/* FLASH_SIZE 容量寄存器 */
#define FLASH_SIZE_FLASH_SIZE_MAX  ((uint32_t)0x3)                                                // FLASH_SIZE_FLASH_SIZE最大值
#define FLASH_SIZE_FLASH_SIZE_POS  6                                                              // FLASH_SIZE_FLASH_SIZE起始位
#define FLASH_SIZE_FLASH_SIZE_MASK (uint32_t)((uint32_t)0x3 << FLASH_SIZE_FLASH_SIZE_POS)         // FLASH_SIZE_FLASH_SIZE位掩码
#define FLASH_SIZE_FLASH_SIZE(x)   (uint32_t)((uint32_t)((x) & 0x3) << FLASH_SIZE_FLASH_SIZE_POS) // [7:6] FLASH容量寄存器，仅可读0：32KB1：64KB2：128KB3：128KB
#define FLASH_SIZE_ROM_SIZE_MAX    ((uint32_t)0x3)                                                // FLASH_SIZE_ROM_SIZE最大值
#define FLASH_SIZE_ROM_SIZE_POS    2                                                              // FLASH_SIZE_ROM_SIZE起始位
#define FLASH_SIZE_ROM_SIZE_MASK   (uint32_t)((uint32_t)0x3 << FLASH_SIZE_ROM_SIZE_POS)           // FLASH_SIZE_ROM_SIZE位掩码
#define FLASH_SIZE_ROM_SIZE(x)     (uint32_t)((uint32_t)((x) & 0x3) << FLASH_SIZE_ROM_SIZE_POS)   // [3:2] ROM容量寄存器，仅可读0：0KB1：32KB2：64KB3：0KB

/* FLASH_NCFG 配置寄存器（推荐先读回，按或/与方式修改） */
#define FLASH_NCFG_ERS_EN_BIT   BIT31                                                    // [31] FLASH擦除使能。默认为0。0:关闭擦除1:开启擦除
#define FLASH_NCFG_PRG_EN_BIT   BIT27                                                    // [27] FLASH编程使能。默认为0。0:关闭编程1:开启编程
#define FLASH_NCFG_ADR_INC_BIT  BIT23                                                    // [23] FLASH地址递增使能。默认为0。此寄存器，只能读取不能修改。0:关闭递增使能1:开启递增使能当执行FLASH连续读写访问时，可以开启此功能减少对地址的操作。
#define FLASH_NCFG_PREF_BIT     BIT19                                                    // [19] FLASH预取加速使能。默认为0。0:关闭加速1:开启加速
#define FLASH_NCFG_ERS_TYPE_BIT BIT15                                                    // [15] FLASH擦除类型选择。默认为0。此寄存器，只能读取不能修改。0:Sector1:FULL
#define FLASH_NCFG_REGION_BIT   BIT11                                                    // [11] 访问FLASH区域选择。默认为0。修改此寄存器，无论写入值是0还是1，最终，只能被强制写成1。0:MAIN1:NVR
#define FLASH_NCFG_WAIT_BIT     BIT7                                                     // [7] 读取FLASH数据，等待开关。默认为1。此寄存器，只能读取不能修改。0:读取，等待一个周期1:读取，等待两个周期
#define FLASH_NCFG_TBS_MAX      ((uint32_t)0x7F)                                         // FLASH_NCFG_TBS最大值
#define FLASH_NCFG_TBS_POS      0                                                        // FLASH_NCFG_TBS起始位
#define FLASH_NCFG_TBS_MASK     (uint32_t)((uint32_t)0x7F << FLASH_NCFG_TBS_POS)         // FLASH_NCFG_TBS位掩码
#define FLASH_NCFG_TBS(x)       (uint32_t)((uint32_t)((x) & 0x7F) << FLASH_NCFG_TBS_POS) // [6:0] 编程/擦除时间基数寄存器,默认值为0x60。只能配成如下几个值。此寄存器，只能读取不能修改。0x60:96Mhz系统频率下，FLASH编程/擦除时间基数配置值。0x30:48Mhz系统频率下，FLASH编程/擦除时间基数配置值。0x17:24Mhz系统频率下，FLASH编程/擦除时间基数配置值。

/* FLASH_NADDR 地址寄存器 */
#define FLASH_NADDR_ADDR_MAX  ((uint32_t)0x7FFF)                                           // FLASH_NADDR_ADDR最大值
#define FLASH_NADDR_ADDR_POS  0                                                            // FLASH_NADDR_ADDR起始位
#define FLASH_NADDR_ADDR_MASK (uint32_t)((uint32_t)0x7FFF << FLASH_NADDR_ADDR_POS)         // FLASH_NADDR_ADDR位掩码
#define FLASH_NADDR_ADDR(x)   (uint32_t)((uint32_t)((x) & 0x7FFF) << FLASH_NADDR_ADDR_POS) // [14:0] 地址寄存器。读/写/擦除操作对应的地址寄存器。因按照WORD操作，最低两位会被FLASH控制器忽略。执行擦除操作时，需要根据擦除类型，地址需要对齐。一个Sector是512-Byte。若执行Sector擦除，地址需要是512的整数倍（若带偏移，偏移量会被忽略）。全芯片擦除，不会参考这个寄存器的值

/* FLASH_NWDATA 写数据寄存器 */
#define FLASH_NWDATA_WDATA_MAX  ((uint32_t)0xFFFFFFFF)                                             // FLASH_NWDATA_WDATA最大值
#define FLASH_NWDATA_WDATA_POS  0                                                                  // FLASH_NWDATA_WDATA起始位
#define FLASH_NWDATA_WDATA_MASK (uint32_t)((uint32_t)0xFFFFFFFF << FLASH_NWDATA_WDATA_POS)         // FLASH_NWDATA_WDATA位掩码
#define FLASH_NWDATA_WDATA(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << FLASH_NWDATA_WDATA_POS) // [31:0] 执行写入操作，写入FLASH的值

/* FLASH_NRDATA 读数据寄存器 */
#define FLASH_NRDATA_RDATA_MAX  ((uint32_t)0xFFFFFFFF)                                             // FLASH_NRDATA_RDATA最大值
#define FLASH_NRDATA_RDATA_POS  0                                                                  // FLASH_NRDATA_RDATA起始位
#define FLASH_NRDATA_RDATA_MASK (uint32_t)((uint32_t)0xFFFFFFFF << FLASH_NRDATA_RDATA_POS)         // FLASH_NRDATA_RDATA位掩码
#define FLASH_NRDATA_RDATA(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << FLASH_NRDATA_RDATA_POS) // [31:0] 执行读取操作，读出FLASH的值

/* FLASH_NERASE 擦除控制寄存器 */
#define FLASH_NERASE_ERASE_MAX  ((uint32_t)0xFFFFFFFF)                                             // FLASH_NERASE_ERASE最大值
#define FLASH_NERASE_ERASE_POS  0                                                                  // FLASH_NERASE_ERASE起始位
#define FLASH_NERASE_ERASE_MASK (uint32_t)((uint32_t)0xFFFFFFFF << FLASH_NERASE_ERASE_POS)         // FLASH_NERASE_ERASE位掩码
#define FLASH_NERASE_ERASE(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << FLASH_NERASE_ERASE_POS) // [31:0] 写入0x7654DCBA，触发擦除操作

/* FLASH_NKEY 密钥寄存器 */
#define FLASH_NKEY_KEY_MAX  ((uint32_t)0xF)                                         // FLASH_NKEY_KEY最大值
#define FLASH_NKEY_KEY_POS  0                                                       // FLASH_NKEY_KEY起始位
#define FLASH_NKEY_KEY_MASK (uint32_t)((uint32_t)0xF << FLASH_NKEY_KEY_POS)         // FLASH_NKEY_KEY位掩码
#define FLASH_NKEY_KEY(x)   (uint32_t)((uint32_t)((x) & 0xF) << FLASH_NKEY_KEY_POS) // [3:0] 当FLASH处于保护状态时，无法通过SWD读取，编程和擦除FLASH。此时，用户可以对此寄存器写入特殊值（0x0000_000F），使能开关，配置FLASH_NCFG/NADDR/NWDATA/NRDATA/NERASE寄存器，对NVR Sector 2进行读取，编程和擦除。

/* SPI0_CFG SPI 控制寄存器 */
#define SPI0_CFG_DUPLEX_MAX  ((uint32_t)0x3)                                          // SPI0_CFG_DUPLEX最大值
#define SPI0_CFG_DUPLEX_POS  6                                                        // SPI0_CFG_DUPLEX起始位
#define SPI0_CFG_DUPLEX_MASK (uint32_t)((uint32_t)0x3 << SPI0_CFG_DUPLEX_POS)         // SPI0_CFG_DUPLEX位掩码
#define SPI0_CFG_DUPLEX(x)   (uint32_t)((uint32_t)((x) & 0x3) << SPI0_CFG_DUPLEX_POS) // [7:6] 半双工模式设置0X:关闭半双工模式10:开启半双工模式，仅发送11:开启半双工模式，仅接收
#define SPI0_CFG_CS_BIT      BIT5                                                     // [5] SPI从设备下，片选信号来源。默认值为1。0:Slave模式下，片选信号恒为有效值--01:Slave模式下，片选信号来自Master设备
#define SPI0_CFG_MS_BIT      BIT4                                                     // [4] SPI主从模式选择。默认值为0。0:Slave模式1:Master模式
#define SPI0_CFG_CPHA_BIT    BIT3                                                     // [3] SPI相位选择。默认值为0。0:Phase为01:Phase为1
#define SPI0_CFG_CPOL_BIT    BIT2                                                     // [2] SPI极性选择。默认值为0。0:Polarity为01:Polarity为1
#define SPI0_CFG_ENDIAN_BIT  BIT1                                                     // [1] SPI模块传输顺序。默认值为0。0:MSB，高位先传输1:LSB，低位先传输
#define SPI0_CFG_EN_BIT      BIT0                                                     // [0] SPI模块使能信号。默认值为0。0:关闭SPI模块1:开启SPI模块

/* SPI0_IE SPI 中断寄存器 */
#define SPI0_IE_IE_BIT         BIT7 // [7] SPI中断使能开关。默认值为0。0:关闭SPI中断1:使能SPI中断
#define SPI0_IE_CMPLT_IE_BIT   BIT6 // [6] SPI传输，完成事件中断使能信号。0:屏蔽此中断源1:使能此中断源
#define SPI0_IE_AB_IE_BIT      BIT5 // [5] SPI传输，异常事件中断使能信号。0:屏蔽此中断源1:使能此中断源
#define SPI0_IE_OV_IE_BIT      BIT4 // [4] SPI传输，溢出事件中断使能信号。默认值为0。0:屏蔽此中断源1:使能此中断源
#define SPI0_IE_TRANS_TRIG_BIT BIT3 // [3] 传输触发选择。1：外部触发0：内部自动执行。仅主模式有效
#define SPI0_IE_CMPLT_IF_BIT   BIT2 // [2] SPI传输，完成事件。高电平有效，写1清除。
#define SPI0_IE_AB_IF_BIT      BIT1 // [1] SPI传输，异常事件。Slave模式下，传输未完成，发生片选信号无效事件。高电平有效，写1清除。
#define SPI0_IE_OV_IF_BIT      BIT0 // [0] SPI传输，溢出事件。前次接收的旧数据没有被取得走，本次接收的新数据已经到达。高电平有效，写1清除。

/* SPI0_BAUD SPI 波特率寄存器 */
#define SPI0_BAUD_TRANS_MODE_BIT BIT15                                                     // [15] SPI数据搬移方式。默认为0，DMA方式。0：SPI接口支持DMA搬移数据到SPI接口，完成发送和接收。1：SPI接口支持MCU搬移数据到SPI接口，完成发送和接收。
#define SPI0_BAUD_BAUD_MAX       ((uint32_t)0xFFF)                                         // SPI0_BAUD_BAUD最大值
#define SPI0_BAUD_BAUD_POS       0                                                         // SPI0_BAUD_BAUD起始位
#define SPI0_BAUD_BAUD_MASK      (uint32_t)((uint32_t)0xFFF << SPI0_BAUD_BAUD_POS)         // SPI0_BAUD_BAUD位掩码
#define SPI0_BAUD_BAUD(x)        (uint32_t)((uint32_t)((x) & 0xFFF) << SPI0_BAUD_BAUD_POS) // [11:0] SPI传输波特率配置，SPI实际传输速度计算公式为:SPI传输速度 = 系统时钟 / (2\*(BAUD + 1))切记，BAUD的配置值不能小于3。

/* SPI0_TXDATA SPI 数据发送寄存器 */
#define SPI0_TXDATA_TX_DATA_MAX  ((uint32_t)0xFFFF)                                              // SPI0_TXDATA_TX_DATA最大值
#define SPI0_TXDATA_TX_DATA_POS  0                                                               // SPI0_TXDATA_TX_DATA起始位
#define SPI0_TXDATA_TX_DATA_MASK (uint32_t)((uint32_t)0xFFFF << SPI0_TXDATA_TX_DATA_POS)         // SPI0_TXDATA_TX_DATA位掩码
#define SPI0_TXDATA_TX_DATA(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << SPI0_TXDATA_TX_DATA_POS) // [15:0] SPI数据发送寄存器

/* SPI0_RXDATA SPI 数据接收寄存器 */
#define SPI0_RXDATA_RX_DATA_MAX  ((uint32_t)0xFFFF)                                              // SPI0_RXDATA_RX_DATA最大值
#define SPI0_RXDATA_RX_DATA_POS  0                                                               // SPI0_RXDATA_RX_DATA起始位
#define SPI0_RXDATA_RX_DATA_MASK (uint32_t)((uint32_t)0xFFFF << SPI0_RXDATA_RX_DATA_POS)         // SPI0_RXDATA_RX_DATA位掩码
#define SPI0_RXDATA_RX_DATA(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << SPI0_RXDATA_RX_DATA_POS) // [15:0] SPI数据接收寄存器

/* SPI0_SIZE SPI 数据传输长度寄存器 */
#define SPI0_SIZE_BITSIZE_MAX  ((uint32_t)0x1F)                                            // SPI0_SIZE_BITSIZE最大值
#define SPI0_SIZE_BITSIZE_POS  0                                                           // SPI0_SIZE_BITSIZE起始位
#define SPI0_SIZE_BITSIZE_MASK (uint32_t)((uint32_t)0x1F << SPI0_SIZE_BITSIZE_POS)         // SPI0_SIZE_BITSIZE位掩码
#define SPI0_SIZE_BITSIZE(x)   (uint32_t)((uint32_t)((x) & 0x1F) << SPI0_SIZE_BITSIZE_POS) // [4:0] 字节长度寄存器。0x00:非法值0x07:非法值0x08:8-Bit0x09:9-Bit…0x0E:14-Bit0x0F:15-Bit0x10:16-Bit

/* I2C0_ADDR 地址寄存器 */
#define I2C0_ADDR_ADDR_CMP_BIT BIT7                                                     // [7] I2C硬件地址比较使能开关，默认值为0。0:关闭1:开启
#define I2C0_ADDR_ADDR_MAX     ((uint32_t)0x7F)                                         // I2C0_ADDR_ADDR最大值
#define I2C0_ADDR_ADDR_POS     0                                                        // I2C0_ADDR_ADDR起始位
#define I2C0_ADDR_ADDR_MASK    (uint32_t)((uint32_t)0x7F << I2C0_ADDR_ADDR_POS)         // I2C0_ADDR_ADDR位掩码
#define I2C0_ADDR_ADDR(x)      (uint32_t)((uint32_t)((x) & 0x7F) << I2C0_ADDR_ADDR_POS) // [6:0] 仅用于从模式下，I2C设备硬件地址。主模式下，从设备地址写入I2C_DATA寄存器。

/* I2C0_CFG 系统控制寄存器 */
#define I2C0_CFG_IE_BIT         BIT7 // [7] I2C中断使能信号。默认值为0。1:使能I2C中断0:关闭I2C中断
#define I2C0_CFG_TC_IE_BIT      BIT6 // [6] I2C数据传输完成中断使能信号。默认值为0。1:使能此中断源0:屏蔽此中断源
#define I2C0_CFG_BUS_ERR_IE_BIT BIT5 // [5] I2C总线错误事件中断使能信号。默认值为0。1:使能此中断源0:屏蔽此中断源
#define I2C0_CFG_STOP_IE_BIT    BIT4 // [4] I2CSTOP事件中断使能信号。默认值为0。1:使能此中断源0:屏蔽此中断源
#define I2C0_CFG_MST_MODE_BIT   BIT1 // [1] I2C主模式使能信号。默认值为0。1:使能主模式0:关闭主模式
#define I2C0_CFG_SLV_MODE_BIT   BIT0 // [0] I2C从模式使能信号。默认值为0。1:使能从模式0:关闭从模式

/* I2C0_SCR 状态控制寄存器 */
#define I2C0_SCR_STT_ERR_BIT    BIT7 // [7] 总线错误状态标志位，用于主模式发送/主模式接收，写0清除。0:无START/STOP总线错误1:有START/STOP总线错误
#define I2C0_SCR_LOST_ARB_BIT   BIT6 // [6] 总线仲裁丢失状态标志位，用于主模式发送/主模式接收，发生总线仲裁丢失事件将此位置1，无中断事件产生，在字节完成中断中需查此位。总线上任何START事件将导致硬件清除此位。0:无总线仲裁丢失错误发生1:有总线仲裁丢失错误发生
#define I2C0_SCR_STOP_EVT_BIT   BIT5 // [5] STOP事件状态标志位，用于主模式发送/从模式发送/主模式接收/从模式接收。写0清除。0:无STOP事件1:有STOP事件
#define I2C0_SCR_BYTE_CMPLT_BIT BIT4 // [4] ACK控制位，用于主模式接收/从模式接收。发送方发送完毕当前字节，接收方对此的响应。若是发送方，此位保留0值。接收方，根据实际情况配置。0:字节发送完成，返回NACK回应，表示接收方不能接收更多数据1:字节发送完成，返回ACK回应，表示接收方可以继续接收数据
#define I2C0_SCR_ADDR_DATA_BIT  BIT3 // [3] 地址数据标志位，用于主模式发送/从模式发送/主模式接收/从模式接收。START后，第一个字节为地址数据，此位是一个提示位。写0清除。0:当前传输的数据非地址数据。1:当前传输的数据是地址数据。
#define I2C0_SCR_DATA_DIR_BIT   BIT2 // [2] 发送或接收控制位，主模式发送/从模式发送，此位置1，触发发送，硬件自动清零；主模式接收/从模式接收，此位置0，等待接收。0:接收1:触发发送
#define I2C0_SCR_RX_ACK_BIT     BIT1 // [1] 接收响应标志位，用于主模式发送/从模式发送，告知发送方，接收方的反馈。发送方收到反馈后，对该位执行清零操作。0:本I2C接口发送数据，接收到ACK响应。1:本I2C接口发送数据，接收到NACK响应。
#define I2C0_SCR_Done_BIT       BIT0 // [0] 传输完成状态标志位，用于主模式发送/从模式发送/主模式接收/从模式接收。写0清除。0:传输未完成1:传输已完成

/* I2C0_DATA 数据寄存器 */
#define I2C0_DATA_DATA_MAX  ((uint32_t)0xFF)                                         // I2C0_DATA_DATA最大值
#define I2C0_DATA_DATA_POS  0                                                        // I2C0_DATA_DATA起始位
#define I2C0_DATA_DATA_MASK (uint32_t)((uint32_t)0xFF << I2C0_DATA_DATA_POS)         // I2C0_DATA_DATA位掩码
#define I2C0_DATA_DATA(x)   (uint32_t)((uint32_t)((x) & 0xFF) << I2C0_DATA_DATA_POS) // [7:0] 数据寄存器，用于主模式发送/从模式发送/主模式接收/从模式接收。发送方，写入发送数据；接收方，读取接收数据。注意，地址数据也是数据，主模式只能将要发送地址数据写入此寄存器。

/* I2C0_MSCR 主模式寄存器 */
#define I2C0_MSCR_BUSY_BIT      BIT3 // [3] I2C总线，闲忙状态。0:检测到STOP事件，空闲。1:检测到START事件，忙碌。
#define I2C0_MSCR_MST_CHECK_BIT BIT2 // [2] 主模式争抢总线标志位。争抢到总线，置1；STOP事件或者发生总线冲突本模块释放总线，置0。
#define I2C0_MSCR_RESTART_BIT   BIT1 // [1] 再次触发START事件，写1有效。发送START完毕，硬件清0。I2C_CFG[1]置1，才能实现写1操作。
#define I2C0_MSCR_START_BIT     BIT0 // [0] 触发START事件并发送地址数据至总线，写1有效。I2C_CFG[1]置1，才能实现写1操作。

/* I2C0_BCR I2C传输控制寄存器 */
#define I2C0_BCR_BURST_NACK_BIT     BIT7 // [7] I2C传输，NACK事件中断使能信号。1：使能此中断源0：屏蔽此中断源
#define I2C0_BCR_BURST_ADDR_CMP_BIT BIT6 // [6] I2C传输，硬件地址匹配中断使能信号。1：使能此中断源0：屏蔽此中断源
#define I2C0_BCR_BUSRT_EN_BIT       BIT5 // [5] I2C多数据传输使能，需要采用DMA方式。1：使能0：关闭
#define I2C0_BCR_SLV_DMA_PREF_BIT   BIT4 // [4] I2C多数据传输。从模式执行DMA方式发送，触发硬件预取第一个字节。硬件自动清零。1：使能0：关闭

/* CMP_IE 中断使能寄存器 */
#define CMP_IE_CMP2_RE_BIT BIT10 // [10] 比较器2 DMA请求使能，高有效
#define CMP_IE_CMP1_RE_BIT BIT9  // [9] 比较器1 DMA请求使能，高有效
#define CMP_IE_CMP0_RE_BIT BIT8  // [8] 比较器0 DMA请求使能，高有效
#define CMP_IE_CMP2_IE_BIT BIT2  // [2] 比较器2中断使能，高有效
#define CMP_IE_CMP1_IE_BIT BIT1  // [1] 比较器1中断使能，高有效
#define CMP_IE_CMP0_IE_BIT BIT0  // [0] 比较器0中断使能，高有效

/* CMP_IF 中断标志寄存器 */
#define CMP_IF_CMP2_IF_BIT BIT2 // [2] 比较器2中断标志，高有效，写1清零
#define CMP_IF_CMP1_IF_BIT BIT1 // [1] 比较器1中断标志，高有效，写1清零
#define CMP_IF_CMP0_IF_BIT BIT0 // [0] 比较器0中断标志，高有效，写1清零

/* CMP_TCLK 分频时钟控制寄存器 */
#define CMP_TCLK_COMM_DIV_MAX        ((uint32_t)0x7)                                                  // CMP_TCLK_COMM_DIV最大值
#define CMP_TCLK_COMM_DIV_POS        24                                                               // CMP_TCLK_COMM_DIV起始位
#define CMP_TCLK_COMM_DIV_MASK       (uint32_t)((uint32_t)0x7 << CMP_TCLK_COMM_DIV_POS)               // CMP_TCLK_COMM_DIV位掩码
#define CMP_TCLK_COMM_DIV(x)         (uint32_t)((uint32_t)((x) & 0x7) << CMP_TCLK_COMM_DIV_POS)       // [26:24] 比较器0/1/2共用滤波时钟分频系数，影响进入比较器中断的时间，最大支持到4
#define CMP_TCLK_FIL2_CLK_DIV16_MAX  ((uint32_t)0xF)                                                  // CMP_TCLK_FIL2_CLK_DIV16最大值
#define CMP_TCLK_FIL2_CLK_DIV16_POS  20                                                               // CMP_TCLK_FIL2_CLK_DIV16起始位
#define CMP_TCLK_FIL2_CLK_DIV16_MASK (uint32_t)((uint32_t)0xF << CMP_TCLK_FIL2_CLK_DIV16_POS)         // CMP_TCLK_FIL2_CLK_DIV16位掩码
#define CMP_TCLK_FIL2_CLK_DIV16(x)   (uint32_t)((uint32_t)((x) & 0xF) << CMP_TCLK_FIL2_CLK_DIV16_POS) // [23:20] 比较器2滤波时钟分频，基于MCLK进行1~16分频，影响进入比较器中断的时间
#define CMP_TCLK_CLK2_EN_BIT         BIT19                                                            // [19] 比较器2滤波时钟使能，高有效
#define CMP_TCLK_FIL2_CLK_DIV2_MAX   ((uint32_t)0x7)                                                  // CMP_TCLK_FIL2_CLK_DIV2最大值
#define CMP_TCLK_FIL2_CLK_DIV2_POS   16                                                               // CMP_TCLK_FIL2_CLK_DIV2起始位
#define CMP_TCLK_FIL2_CLK_DIV2_MASK  (uint32_t)((uint32_t)0x7 << CMP_TCLK_FIL2_CLK_DIV2_POS)          // CMP_TCLK_FIL2_CLK_DIV2位掩码
#define CMP_TCLK_FIL2_CLK_DIV2(x)    (uint32_t)((uint32_t)((x) & 0x7) << CMP_TCLK_FIL2_CLK_DIV2_POS)  // [18:16] 比较器2滤波时钟分频0:1分频1:2分频2:4分频3:8分频4:16分频5:32分频,6:64分频7:128分频
#define CMP_TCLK_FIL1_CLK_DIV16_MAX  ((uint32_t)0xF)                                                  // CMP_TCLK_FIL1_CLK_DIV16最大值
#define CMP_TCLK_FIL1_CLK_DIV16_POS  12                                                               // CMP_TCLK_FIL1_CLK_DIV16起始位
#define CMP_TCLK_FIL1_CLK_DIV16_MASK (uint32_t)((uint32_t)0xF << CMP_TCLK_FIL1_CLK_DIV16_POS)         // CMP_TCLK_FIL1_CLK_DIV16位掩码
#define CMP_TCLK_FIL1_CLK_DIV16(x)   (uint32_t)((uint32_t)((x) & 0xF) << CMP_TCLK_FIL1_CLK_DIV16_POS) // [15:12] 比较器1滤波时钟分频，基于MCLK进行1~16分频，影响进入比较器中断的时间
#define CMP_TCLK_CLK1_EN_BIT         BIT11                                                            // [11] 比较器1滤波时钟使能，高有效
#define CMP_TCLK_FIL1_CLK_DIV2_MAX   ((uint32_t)0x7)                                                  // CMP_TCLK_FIL1_CLK_DIV2最大值
#define CMP_TCLK_FIL1_CLK_DIV2_POS   8                                                                // CMP_TCLK_FIL1_CLK_DIV2起始位
#define CMP_TCLK_FIL1_CLK_DIV2_MASK  (uint32_t)((uint32_t)0x7 << CMP_TCLK_FIL1_CLK_DIV2_POS)          // CMP_TCLK_FIL1_CLK_DIV2位掩码
#define CMP_TCLK_FIL1_CLK_DIV2(x)    (uint32_t)((uint32_t)((x) & 0x7) << CMP_TCLK_FIL1_CLK_DIV2_POS)  // [10:8] 比较器1滤波时钟分频0:1分频1:2分频2:4分频3:8分频4:16分频5:32分频,6:64分频7:128分频
#define CMP_TCLK_FIL0_CLK_DIV16_MAX  ((uint32_t)0xF)                                                  // CMP_TCLK_FIL0_CLK_DIV16最大值
#define CMP_TCLK_FIL0_CLK_DIV16_POS  4                                                                // CMP_TCLK_FIL0_CLK_DIV16起始位
#define CMP_TCLK_FIL0_CLK_DIV16_MASK (uint32_t)((uint32_t)0xF << CMP_TCLK_FIL0_CLK_DIV16_POS)         // CMP_TCLK_FIL0_CLK_DIV16位掩码
#define CMP_TCLK_FIL0_CLK_DIV16(x)   (uint32_t)((uint32_t)((x) & 0xF) << CMP_TCLK_FIL0_CLK_DIV16_POS) // [7:4] 比较器0滤波时钟分频，基于MCLK进行1~16分频，影响进入比较器中断的时间
#define CMP_TCLK_CLK0_EN_BIT         BIT3                                                             // [3] 比较器0滤波时钟使能，高有效
#define CMP_TCLK_FIL0_CLK_DIV2_MAX   ((uint32_t)0x7)                                                  // CMP_TCLK_FIL0_CLK_DIV2最大值
#define CMP_TCLK_FIL0_CLK_DIV2_POS   0                                                                // CMP_TCLK_FIL0_CLK_DIV2起始位
#define CMP_TCLK_FIL0_CLK_DIV2_MASK  (uint32_t)((uint32_t)0x7 << CMP_TCLK_FIL0_CLK_DIV2_POS)          // CMP_TCLK_FIL0_CLK_DIV2位掩码
#define CMP_TCLK_FIL0_CLK_DIV2(x)    (uint32_t)((uint32_t)((x) & 0x7) << CMP_TCLK_FIL0_CLK_DIV2_POS)  // [2:0] 比较器0滤波时钟分频0:1分频1:2分频2:4分频3:8分频4:16分频5:32分频,6:64分频7:128分频

/* CMP_CFG 控制寄存器 */
#define CMP_CFG_CMP2_IRQ_TRIG_BIT  BIT10 // [10] 比较器2中断触发类型，0:电平触发，1:边沿触发
#define CMP_CFG_CMP2_IN_EN_BIT     BIT9  // [9] 比较器2信号输入使能
#define CMP_CFG_CMP2_POL_BIT       BIT8  // [8] 比较器2极性选择，0:高电平有效；1:低电平有效
#define CMP_CFG_CMP1_W_PWM_POL_BIT BIT7  // [7] 比较器1开窗PWM信号极性选择，在CMP_BLCWIN1使能情况下使用
#define CMP_CFG_CMP1_IRQ_TRIG_BIT  BIT6  // [6] 比较器1中断触发类型，0:电平触发，1:边沿触发
#define CMP_CFG_CMP1_IN_EN_BIT     BIT5  // [5] 比较器1信号输入使能
#define CMP_CFG_CMP1_POL_BIT       BIT4  // [4] 比较器1极性选择，0:高电平有效；1:低电平有效
#define CMP_CFG_CMP0_W_PWM_POL_BIT BIT3  // [3] 比较器0开窗PWM信号极性选择，在CMP_BLCWIN0使能情况下使用
#define CMP_CFG_CMP0_IRQ_TRIG_BIT  BIT2  // [2] 比较器0中断触发类型，0:电平触发，1:边沿触发
#define CMP_CFG_CMP0_IN_EN_BIT     BIT1  // [1] 比较器0信号输入使能
#define CMP_CFG_CMP0_POL_BIT       BIT0  // [0] 比较器0极性选择，0:高电平有效；1:低电平有效

/* CMP_BLCWIN 开窗控制寄存器 */
#define CMP_BLCWIN_CMP1_CHN3P_WIN_EN_BIT BIT7 // [7] 使用MCPWM模块CHN3_P通道输出的P管开关控制信号作为比较器1开窗使能
#define CMP_BLCWIN_CMP1_CHN2P_WIN_EN_BIT BIT6 // [6] 使用MCPWM模块CHN2_P通道输出的P管开关控制信号作为比较器1开窗使能
#define CMP_BLCWIN_CMP1_CHN1P_WIN_EN_BIT BIT5 // [5] 使用MCPWM模块CHN1_P通道输出的P管开关控制信号作为比较器1开窗使能
#define CMP_BLCWIN_CMP1_CHN0P_WIN_EN_BIT BIT4 // [4] 使用MCPWM模块CHN0_P通道输出的P管开关控制信号作为比较器1开窗使能
#define CMP_BLCWIN_CMP0_CHN3P_WIN_EN_BIT BIT3 // [3] 使用MCPWM模块CHN3_P通道输出的P管开关控制信号作为比较器0开窗使能
#define CMP_BLCWIN_CMP0_CHN2P_WIN_EN_BIT BIT2 // [2] 使用MCPWM模块CHN2_P通道输出的P管开关控制信号作为比较器0开窗使能
#define CMP_BLCWIN_CMP0_CHN1P_WIN_EN_BIT BIT1 // [1] 使用MCPWM模块CHN1_P通道输出的P管开关控制信号作为比较器0开窗使能
#define CMP_BLCWIN_CMP0_CHN0P_WIN_EN_BIT BIT0 // [0] 使用MCPWM模块CHN0_P通道输出的P管开关控制信号作为比较器0开窗使能

/* CMP_DATA 输出数据寄存器 */
#define CMP_DATA_CMP2_FLT_DATA_BIT BIT10 // [10] 比较器2经过滤波后的信号
#define CMP_DATA_CMP1_FLT_DATA_BIT BIT9  // [9] 比较器1经过滤波后的信号
#define CMP_DATA_CMP0_FLT_DATA_BIT BIT8  // [8] 比较器0经过滤波后的信号
#define CMP_DATA_CMP2_RAW_DATA_BIT BIT2  // [2] 比较器2原始输出信号，直接来自模拟比较器2
#define CMP_DATA_CMP1_RAW_DATA_BIT BIT1  // [1] 比较器1原始输出信号，直接来自模拟比较器1
#define CMP_DATA_CMP0_RAW_DATA_BIT BIT0  // [0] 比较器0原始输出信号，直接来自模拟比较器0

/* HALL0_CFG HALL模块配置寄存器 */
#define HALL0_CFG_SW_IE_BIT    BIT30                                                         // [30] 软件触发HALL信号变化中断使能，高电平有效。当SW_IE=1时，软件向HALL_INFO.SW_IF写1，可以手动产生HALL信号变化中断，并令HALL_INFO.CHG_IF置位。
#define HALL0_CFG_OV_IE_BIT    BIT29                                                         // [29] HALL计数器溢出中断使能开关。默认关闭。0: 关闭1: 使能
#define HALL0_CFG_CHG_IE_BIT   BIT28                                                         // [28] HALL信号变化中断使能开关。默认关闭。0: 关闭1: 使能
#define HALL0_CFG_OV_RE_BIT    BIT26                                                         // [26] HALL计数器溢出DMA请求使能开关。默认关闭。0: 关闭1: 使能
#define HALL0_CFG_CHG_RE_BIT   BIT25                                                         // [25] HALL信号变化DMA请求使能开关。默认关闭。0: 关闭1: 使能
#define HALL0_CFG_HALL_EN_BIT  BIT24                                                         // [24] HALL模块使能开关。默认关闭。0: 关闭1: 使能
#define HALL0_CFG_FIL_75_BIT   BIT20                                                         // [20] 7/5滤波开关（连续采样7次，5次值一致）。默认关闭。0: 关闭1: 使能
#define HALL0_CFG_CLK_DIV_MAX  ((uint32_t)0x3)                                               // HALL0_CFG_CLK_DIV最大值
#define HALL0_CFG_CLK_DIV_POS  16                                                            // HALL0_CFG_CLK_DIV起始位
#define HALL0_CFG_CLK_DIV_MASK (uint32_t)((uint32_t)0x3 << HALL0_CFG_CLK_DIV_POS)            // HALL0_CFG_CLK_DIV位掩码
#define HALL0_CFG_CLK_DIV(x)   (uint32_t)((uint32_t)((x) & 0x3) << HALL0_CFG_CLK_DIV_POS)    // [17:16] HALL时钟分频系数。默认不分频。00:不分频01:2分频10:4分频11:8分频
#define HALL0_CFG_FIL_LEN_MAX  ((uint32_t)0x7FFF)                                            // HALL0_CFG_FIL_LEN最大值
#define HALL0_CFG_FIL_LEN_POS  0                                                             // HALL0_CFG_FIL_LEN起始位
#define HALL0_CFG_FIL_LEN_MASK (uint32_t)((uint32_t)0x7FFF << HALL0_CFG_FIL_LEN_POS)         // HALL0_CFG_FIL_LEN位掩码
#define HALL0_CFG_FIL_LEN(x)   (uint32_t)((uint32_t)((x) & 0x7FFF) << HALL0_CFG_FIL_LEN_POS) // [14:0] 滤波宽度，低于对应脉冲宽度的信号将被硬件自动过滤掉。滤波宽度的计算公式为[14:0]+ 1。

/* HALL0_INFO HALL模块信息寄存器 */
#define HALL0_INFO_SW_IF_BIT     BIT18                                                        // [18] 软件触发HALL信号变化中断。写1触发，自动清零。
#define HALL0_INFO_OV_IF_BIT     BIT17                                                        // [17] HALL计数器溢出事件标志，写1清空
#define HALL0_INFO_CHG_IF_BIT    BIT16                                                        // [16] HALL信号变化事件标志，写1清空
#define HALL0_INFO_RAW_DATA_MAX  ((uint32_t)0x7)                                              // HALL0_INFO_RAW_DATA最大值
#define HALL0_INFO_RAW_DATA_POS  8                                                            // HALL0_INFO_RAW_DATA起始位
#define HALL0_INFO_RAW_DATA_MASK (uint32_t)((uint32_t)0x7 << HALL0_INFO_RAW_DATA_POS)         // HALL0_INFO_RAW_DATA位掩码
#define HALL0_INFO_RAW_DATA(x)   (uint32_t)((uint32_t)((x) & 0x7) << HALL0_INFO_RAW_DATA_POS) // [10:8] HALL值，未滤波结果
#define HALL0_INFO_FLT_DATA_MAX  ((uint32_t)0x7)                                              // HALL0_INFO_FLT_DATA最大值
#define HALL0_INFO_FLT_DATA_POS  0                                                            // HALL0_INFO_FLT_DATA起始位
#define HALL0_INFO_FLT_DATA_MASK (uint32_t)((uint32_t)0x7 << HALL0_INFO_FLT_DATA_POS)         // HALL0_INFO_FLT_DATA位掩码
#define HALL0_INFO_FLT_DATA(x)   (uint32_t)((uint32_t)((x) & 0x7) << HALL0_INFO_FLT_DATA_POS) // [2:0] HALL值，滤波结果

/* HALL0_WIDTH HALL宽度计数值寄存器 */
#define HALL0_WIDTH_CAP_CNT_MAX  ((uint32_t)0xFFFFFF)                                              // HALL0_WIDTH_CAP_CNT最大值
#define HALL0_WIDTH_CAP_CNT_POS  0                                                                 // HALL0_WIDTH_CAP_CNT起始位
#define HALL0_WIDTH_CAP_CNT_MASK (uint32_t)((uint32_t)0xFFFFFF << HALL0_WIDTH_CAP_CNT_POS)         // HALL0_WIDTH_CAP_CNT位掩码
#define HALL0_WIDTH_CAP_CNT(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFF) << HALL0_WIDTH_CAP_CNT_POS) // [23:0] HALL 宽度计数器值

/* HALL0_TH HALL模块计数器门限值寄存器 */
#define HALL0_TH_TH_MAX  ((uint32_t)0xFFFFFF)                                      // HALL0_TH_TH最大值
#define HALL0_TH_TH_POS  0                                                         // HALL0_TH_TH起始位
#define HALL0_TH_TH_MASK (uint32_t)((uint32_t)0xFFFFFF << HALL0_TH_TH_POS)         // HALL0_TH_TH位掩码
#define HALL0_TH_TH(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFF) << HALL0_TH_TH_POS) // [23:0] HALL计数器门限值

/* HALL0_CNT HALL计数寄存器 */
#define HALL0_CNT_CNT_MAX  ((uint32_t)0xFFFFFF)                                        // HALL0_CNT_CNT最大值
#define HALL0_CNT_CNT_POS  0                                                           // HALL0_CNT_CNT起始位
#define HALL0_CNT_CNT_MASK (uint32_t)((uint32_t)0xFFFFFF << HALL0_CNT_CNT_POS)         // HALL0_CNT_CNT位掩码
#define HALL0_CNT_CNT(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFF) << HALL0_CNT_CNT_POS) // [23:0] HALL计数值，写入任意值可清零

/* ADCx_DAT0(x = 0,1) */
#define ADCx_DAT0_DAT0_MAX  ((uint32_t)0xFFFF)                                         // ADCx_DAT0_DAT0最大值
#define ADCx_DAT0_DAT0_POS  0                                                          // ADCx_DAT0_DAT0起始位
#define ADCx_DAT0_DAT0_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_DAT0_DAT0_POS)         // ADCx_DAT0_DAT0位掩码
#define ADCx_DAT0_DAT0(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_DAT0_DAT0_POS) // [15:0] ADCx第0次采样数据

/* ADCx_DAT1(x = 0,1) */
#define ADCx_DAT1_DAT1_MAX  ((uint32_t)0xFFFF)                                         // ADCx_DAT1_DAT1最大值
#define ADCx_DAT1_DAT1_POS  0                                                          // ADCx_DAT1_DAT1起始位
#define ADCx_DAT1_DAT1_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_DAT1_DAT1_POS)         // ADCx_DAT1_DAT1位掩码
#define ADCx_DAT1_DAT1(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_DAT1_DAT1_POS) // [15:0] ADCx第1次采样数据

/* ADCx_DAT2(x = 0,1) */
#define ADCx_DAT2_DAT2_MAX  ((uint32_t)0xFFFF)                                         // ADCx_DAT2_DAT2最大值
#define ADCx_DAT2_DAT2_POS  0                                                          // ADCx_DAT2_DAT2起始位
#define ADCx_DAT2_DAT2_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_DAT2_DAT2_POS)         // ADCx_DAT2_DAT2位掩码
#define ADCx_DAT2_DAT2(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_DAT2_DAT2_POS) // [15:0] ADCx第2次采样数据

/* ADCx_DAT3(x = 0,1) */
#define ADCx_DAT3_DAT3_MAX  ((uint32_t)0xFFFF)                                         // ADCx_DAT3_DAT3最大值
#define ADCx_DAT3_DAT3_POS  0                                                          // ADCx_DAT3_DAT3起始位
#define ADCx_DAT3_DAT3_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_DAT3_DAT3_POS)         // ADCx_DAT3_DAT3位掩码
#define ADCx_DAT3_DAT3(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_DAT3_DAT3_POS) // [15:0] ADCx第3次采样数据

/* ADCx_DAT4(x = 0,1) */
#define ADCx_DAT4_DAT4_MAX  ((uint32_t)0xFFFF)                                         // ADCx_DAT4_DAT4最大值
#define ADCx_DAT4_DAT4_POS  0                                                          // ADCx_DAT4_DAT4起始位
#define ADCx_DAT4_DAT4_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_DAT4_DAT4_POS)         // ADCx_DAT4_DAT4位掩码
#define ADCx_DAT4_DAT4(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_DAT4_DAT4_POS) // [15:0] ADCx第4次采样数据

/* ADCx_DAT5(x = 0,1) */
#define ADCx_DAT5_DAT5_MAX  ((uint32_t)0xFFFF)                                         // ADCx_DAT5_DAT5最大值
#define ADCx_DAT5_DAT5_POS  0                                                          // ADCx_DAT5_DAT5起始位
#define ADCx_DAT5_DAT5_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_DAT5_DAT5_POS)         // ADCx_DAT5_DAT5位掩码
#define ADCx_DAT5_DAT5(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_DAT5_DAT5_POS) // [15:0] ADCx第5次采样数据

/* ADCx_DAT6(x = 0,1) */
#define ADCx_DAT6_DAT6_MAX  ((uint32_t)0xFFFF)                                         // ADCx_DAT6_DAT6最大值
#define ADCx_DAT6_DAT6_POS  0                                                          // ADCx_DAT6_DAT6起始位
#define ADCx_DAT6_DAT6_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_DAT6_DAT6_POS)         // ADCx_DAT6_DAT6位掩码
#define ADCx_DAT6_DAT6(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_DAT6_DAT6_POS) // [15:0] ADCx第6次采样数据

/* ADCx_DAT7(x = 0,1) */
#define ADCx_DAT7_DAT7_MAX  ((uint32_t)0xFFFF)                                         // ADCx_DAT7_DAT7最大值
#define ADCx_DAT7_DAT7_POS  0                                                          // ADCx_DAT7_DAT7起始位
#define ADCx_DAT7_DAT7_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_DAT7_DAT7_POS)         // ADCx_DAT7_DAT7位掩码
#define ADCx_DAT7_DAT7(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_DAT7_DAT7_POS) // [15:0] ADCx第7次采样数据

/* ADCx_DAT8(x = 0,1) */
#define ADCx_DAT8_DAT8_MAX  ((uint32_t)0xFFFF)                                         // ADCx_DAT8_DAT8最大值
#define ADCx_DAT8_DAT8_POS  0                                                          // ADCx_DAT8_DAT8起始位
#define ADCx_DAT8_DAT8_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_DAT8_DAT8_POS)         // ADCx_DAT8_DAT8位掩码
#define ADCx_DAT8_DAT8(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_DAT8_DAT8_POS) // [15:0] ADCx第8次采样数据

/* ADCx_DAT9(x = 0,1) */
#define ADCx_DAT9_DAT9_MAX  ((uint32_t)0xFFFF)                                         // ADCx_DAT9_DAT9最大值
#define ADCx_DAT9_DAT9_POS  0                                                          // ADCx_DAT9_DAT9起始位
#define ADCx_DAT9_DAT9_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_DAT9_DAT9_POS)         // ADCx_DAT9_DAT9位掩码
#define ADCx_DAT9_DAT9(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_DAT9_DAT9_POS) // [15:0] ADCx第9次采样数据

/* ADCx_DAT10(x = 0,1) */
#define ADCx_DAT10_DAT10_MAX  ((uint32_t)0xFFFF)                                           // ADCx_DAT10_DAT10最大值
#define ADCx_DAT10_DAT10_POS  0                                                            // ADCx_DAT10_DAT10起始位
#define ADCx_DAT10_DAT10_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_DAT10_DAT10_POS)         // ADCx_DAT10_DAT10位掩码
#define ADCx_DAT10_DAT10(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_DAT10_DAT10_POS) // [15:0] ADCx第10次采样数据

/* ADCx_DAT11(x = 0,1) */
#define ADCx_DAT11_DAT11_MAX  ((uint32_t)0xFFFF)                                           // ADCx_DAT11_DAT11最大值
#define ADCx_DAT11_DAT11_POS  0                                                            // ADCx_DAT11_DAT11起始位
#define ADCx_DAT11_DAT11_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_DAT11_DAT11_POS)         // ADCx_DAT11_DAT11位掩码
#define ADCx_DAT11_DAT11(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_DAT11_DAT11_POS) // [15:0] ADCx第11次采样数据

/* ADCx_DAT12(x = 0,1) */
#define ADCx_DAT12_DAT12_MAX  ((uint32_t)0xFFFF)                                           // ADCx_DAT12_DAT12最大值
#define ADCx_DAT12_DAT12_POS  0                                                            // ADCx_DAT12_DAT12起始位
#define ADCx_DAT12_DAT12_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_DAT12_DAT12_POS)         // ADCx_DAT12_DAT12位掩码
#define ADCx_DAT12_DAT12(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_DAT12_DAT12_POS) // [15:0] ADCx第12次采样数据

/* ADCx_DAT13(x = 0,1) */
#define ADCx_DAT13_DAT13_MAX  ((uint32_t)0xFFFF)                                           // ADCx_DAT13_DAT13最大值
#define ADCx_DAT13_DAT13_POS  0                                                            // ADCx_DAT13_DAT13起始位
#define ADCx_DAT13_DAT13_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_DAT13_DAT13_POS)         // ADCx_DAT13_DAT13位掩码
#define ADCx_DAT13_DAT13(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_DAT13_DAT13_POS) // [15:0] ADCx第13次采样数据

/* ADCx_IDAT0(x = 0,1) */
#define ADCx_IDAT0_IDAT0_MAX  ((uint32_t)0xFFFF)                                           // ADCx_IDAT0_IDAT0最大值
#define ADCx_IDAT0_IDAT0_POS  0                                                            // ADCx_IDAT0_IDAT0起始位
#define ADCx_IDAT0_IDAT0_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_IDAT0_IDAT0_POS)         // ADCx_IDAT0_IDAT0位掩码
#define ADCx_IDAT0_IDAT0(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_IDAT0_IDAT0_POS) // [15:0] ADCx第0次空闲采样数据

/* ADCx_IDAT1(x = 0,1) */
#define ADCx_IDAT1_IDAT15_MAX  ((uint32_t)0xFFFF)                                            // ADCx_IDAT1_IDAT15最大值
#define ADCx_IDAT1_IDAT15_POS  0                                                             // ADCx_IDAT1_IDAT15起始位
#define ADCx_IDAT1_IDAT15_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_IDAT1_IDAT15_POS)         // ADCx_IDAT1_IDAT15位掩码
#define ADCx_IDAT1_IDAT15(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_IDAT1_IDAT15_POS) // [15:0] ADCx第1次空闲采样数据

/* ADCx_CHN0(x = 0,1) */
#define ADCx_CHN0_PDS3_MAX  ((uint32_t)0xF)                                         // ADCx_CHN0_PDS3最大值
#define ADCx_CHN0_PDS3_POS  12                                                      // ADCx_CHN0_PDS3起始位
#define ADCx_CHN0_PDS3_MASK (uint32_t)((uint32_t)0xF << ADCx_CHN0_PDS3_POS)         // ADCx_CHN0_PDS3位掩码
#define ADCx_CHN0_PDS3(x)   (uint32_t)((uint32_t)((x) & 0xF) << ADCx_CHN0_PDS3_POS) // [15:12] ADCx第3次采样正端输入信号选择
#define ADCx_CHN0_PDS2_MAX  ((uint32_t)0xF)                                         // ADCx_CHN0_PDS2最大值
#define ADCx_CHN0_PDS2_POS  8                                                       // ADCx_CHN0_PDS2起始位
#define ADCx_CHN0_PDS2_MASK (uint32_t)((uint32_t)0xF << ADCx_CHN0_PDS2_POS)         // ADCx_CHN0_PDS2位掩码
#define ADCx_CHN0_PDS2(x)   (uint32_t)((uint32_t)((x) & 0xF) << ADCx_CHN0_PDS2_POS) // [11:8] ADCx第2次采样正端输入信号选择
#define ADCx_CHN0_PDS1_MAX  ((uint32_t)0xF)                                         // ADCx_CHN0_PDS1最大值
#define ADCx_CHN0_PDS1_POS  4                                                       // ADCx_CHN0_PDS1起始位
#define ADCx_CHN0_PDS1_MASK (uint32_t)((uint32_t)0xF << ADCx_CHN0_PDS1_POS)         // ADCx_CHN0_PDS1位掩码
#define ADCx_CHN0_PDS1(x)   (uint32_t)((uint32_t)((x) & 0xF) << ADCx_CHN0_PDS1_POS) // [7:4] ADCx第1次采样正端输入信号选择
#define ADCx_CHN0_PDS0_MAX  ((uint32_t)0xF)                                         // ADCx_CHN0_PDS0最大值
#define ADCx_CHN0_PDS0_POS  0                                                       // ADCx_CHN0_PDS0起始位
#define ADCx_CHN0_PDS0_MASK (uint32_t)((uint32_t)0xF << ADCx_CHN0_PDS0_POS)         // ADCx_CHN0_PDS0位掩码
#define ADCx_CHN0_PDS0(x)   (uint32_t)((uint32_t)((x) & 0xF) << ADCx_CHN0_PDS0_POS) // [3:0] ADCx第0次采样正端输入信号选择

/* ADCx_CHN1(x = 0,1) */
#define ADCx_CHN1_PDS7_MAX  ((uint32_t)0xF)                                         // ADCx_CHN1_PDS7最大值
#define ADCx_CHN1_PDS7_POS  12                                                      // ADCx_CHN1_PDS7起始位
#define ADCx_CHN1_PDS7_MASK (uint32_t)((uint32_t)0xF << ADCx_CHN1_PDS7_POS)         // ADCx_CHN1_PDS7位掩码
#define ADCx_CHN1_PDS7(x)   (uint32_t)((uint32_t)((x) & 0xF) << ADCx_CHN1_PDS7_POS) // [15:12] ADCx第7次采样正端输入信号选择
#define ADCx_CHN1_PDS6_MAX  ((uint32_t)0xF)                                         // ADCx_CHN1_PDS6最大值
#define ADCx_CHN1_PDS6_POS  8                                                       // ADCx_CHN1_PDS6起始位
#define ADCx_CHN1_PDS6_MASK (uint32_t)((uint32_t)0xF << ADCx_CHN1_PDS6_POS)         // ADCx_CHN1_PDS6位掩码
#define ADCx_CHN1_PDS6(x)   (uint32_t)((uint32_t)((x) & 0xF) << ADCx_CHN1_PDS6_POS) // [11:8] ADCx第6次采样正端输入信号选择
#define ADCx_CHN1_PDS5_MAX  ((uint32_t)0xF)                                         // ADCx_CHN1_PDS5最大值
#define ADCx_CHN1_PDS5_POS  4                                                       // ADCx_CHN1_PDS5起始位
#define ADCx_CHN1_PDS5_MASK (uint32_t)((uint32_t)0xF << ADCx_CHN1_PDS5_POS)         // ADCx_CHN1_PDS5位掩码
#define ADCx_CHN1_PDS5(x)   (uint32_t)((uint32_t)((x) & 0xF) << ADCx_CHN1_PDS5_POS) // [7:4] ADCx第5次采样正端输入信号选择
#define ADCx_CHN1_PDS4_MAX  ((uint32_t)0xF)                                         // ADCx_CHN1_PDS4最大值
#define ADCx_CHN1_PDS4_POS  0                                                       // ADCx_CHN1_PDS4起始位
#define ADCx_CHN1_PDS4_MASK (uint32_t)((uint32_t)0xF << ADCx_CHN1_PDS4_POS)         // ADCx_CHN1_PDS4位掩码
#define ADCx_CHN1_PDS4(x)   (uint32_t)((uint32_t)((x) & 0xF) << ADCx_CHN1_PDS4_POS) // [3:0] ADCx第4次采样正端输入信号选择

/* ADCx_CHN2(x = 0,1) */
#define ADCx_CHN2_PDS11_MAX  ((uint32_t)0xF)                                          // ADCx_CHN2_PDS11最大值
#define ADCx_CHN2_PDS11_POS  12                                                       // ADCx_CHN2_PDS11起始位
#define ADCx_CHN2_PDS11_MASK (uint32_t)((uint32_t)0xF << ADCx_CHN2_PDS11_POS)         // ADCx_CHN2_PDS11位掩码
#define ADCx_CHN2_PDS11(x)   (uint32_t)((uint32_t)((x) & 0xF) << ADCx_CHN2_PDS11_POS) // [15:12] ADCx第11次采样正端输入信号选择
#define ADCx_CHN2_PDS10_MAX  ((uint32_t)0xF)                                          // ADCx_CHN2_PDS10最大值
#define ADCx_CHN2_PDS10_POS  8                                                        // ADCx_CHN2_PDS10起始位
#define ADCx_CHN2_PDS10_MASK (uint32_t)((uint32_t)0xF << ADCx_CHN2_PDS10_POS)         // ADCx_CHN2_PDS10位掩码
#define ADCx_CHN2_PDS10(x)   (uint32_t)((uint32_t)((x) & 0xF) << ADCx_CHN2_PDS10_POS) // [11:8] ADCx第10次采样正端输入信号选择
#define ADCx_CHN2_PDS9_MAX   ((uint32_t)0xF)                                          // ADCx_CHN2_PDS9最大值
#define ADCx_CHN2_PDS9_POS   4                                                        // ADCx_CHN2_PDS9起始位
#define ADCx_CHN2_PDS9_MASK  (uint32_t)((uint32_t)0xF << ADCx_CHN2_PDS9_POS)          // ADCx_CHN2_PDS9位掩码
#define ADCx_CHN2_PDS9(x)    (uint32_t)((uint32_t)((x) & 0xF) << ADCx_CHN2_PDS9_POS)  // [7:4] ADCx第9次采样正端输入信号选择
#define ADCx_CHN2_PDS8_MAX   ((uint32_t)0xF)                                          // ADCx_CHN2_PDS8最大值
#define ADCx_CHN2_PDS8_POS   0                                                        // ADCx_CHN2_PDS8起始位
#define ADCx_CHN2_PDS8_MASK  (uint32_t)((uint32_t)0xF << ADCx_CHN2_PDS8_POS)          // ADCx_CHN2_PDS8位掩码
#define ADCx_CHN2_PDS8(x)    (uint32_t)((uint32_t)((x) & 0xF) << ADCx_CHN2_PDS8_POS)  // [3:0] ADCx第8次采样正端输入信号选择

/* ADCx_CHN3(x = 0,1) */
#define ADCx_CHN3_PDS13_MAX  ((uint32_t)0xF)                                          // ADCx_CHN3_PDS13最大值
#define ADCx_CHN3_PDS13_POS  4                                                        // ADCx_CHN3_PDS13起始位
#define ADCx_CHN3_PDS13_MASK (uint32_t)((uint32_t)0xF << ADCx_CHN3_PDS13_POS)         // ADCx_CHN3_PDS13位掩码
#define ADCx_CHN3_PDS13(x)   (uint32_t)((uint32_t)((x) & 0xF) << ADCx_CHN3_PDS13_POS) // [7:4] ADCx第13次采样正端输入信号选择
#define ADCx_CHN3_PDS12_MAX  ((uint32_t)0xF)                                          // ADCx_CHN3_PDS12最大值
#define ADCx_CHN3_PDS12_POS  0                                                        // ADCx_CHN3_PDS12起始位
#define ADCx_CHN3_PDS12_MASK (uint32_t)((uint32_t)0xF << ADCx_CHN3_PDS12_POS)         // ADCx_CHN3_PDS12位掩码
#define ADCx_CHN3_PDS12(x)   (uint32_t)((uint32_t)((x) & 0xF) << ADCx_CHN3_PDS12_POS) // [3:0] ADCx第12次采样正端输入信号选择

/* ADCx_ICHN(x = 0,1) */
#define ADCx_ICHN_IDS1_MAX  ((uint32_t)0xF)                                         // ADCx_ICHN_IDS1最大值
#define ADCx_ICHN_IDS1_POS  4                                                       // ADCx_ICHN_IDS1起始位
#define ADCx_ICHN_IDS1_MASK (uint32_t)((uint32_t)0xF << ADCx_ICHN_IDS1_POS)         // ADCx_ICHN_IDS1位掩码
#define ADCx_ICHN_IDS1(x)   (uint32_t)((uint32_t)((x) & 0xF) << ADCx_ICHN_IDS1_POS) // [7:4] ADCx第1次空闲采样输入信号选择
#define ADCx_ICHN_IDS0_MAX  ((uint32_t)0xF)                                         // ADCx_ICHN_IDS0最大值
#define ADCx_ICHN_IDS0_POS  0                                                       // ADCx_ICHN_IDS0起始位
#define ADCx_ICHN_IDS0_MASK (uint32_t)((uint32_t)0xF << ADCx_ICHN_IDS0_POS)         // ADCx_ICHN_IDS0位掩码
#define ADCx_ICHN_IDS0(x)   (uint32_t)((uint32_t)((x) & 0xF) << ADCx_ICHN_IDS0_POS) // [3:0] ADCx第0次空闲采样输入信号选择

/* ADCx_CHNT(x = 0,1) */
#define ADCx_CHNT_IS1_MAX  ((uint32_t)0x3)                                        // ADCx_CHNT_IS1最大值
#define ADCx_CHNT_IS1_POS  8                                                      // ADCx_CHNT_IS1起始位
#define ADCx_CHNT_IS1_MASK (uint32_t)((uint32_t)0x3 << ADCx_CHNT_IS1_POS)         // ADCx_CHNT_IS1位掩码
#define ADCx_CHNT_IS1(x)   (uint32_t)((uint32_t)((x) & 0x3) << ADCx_CHNT_IS1_POS) // [9:8] 空闲采样次数
#define ADCx_CHNT_S2_MAX   ((uint32_t)0xF)                                        // ADCx_CHNT_S2最大值
#define ADCx_CHNT_S2_POS   4                                                      // ADCx_CHNT_S2起始位
#define ADCx_CHNT_S2_MASK  (uint32_t)((uint32_t)0xF << ADCx_CHNT_S2_POS)          // ADCx_CHNT_S2位掩码
#define ADCx_CHNT_S2(x)    (uint32_t)((uint32_t)((x) & 0xF) << ADCx_CHNT_S2_POS)  // [7:4] 第二段常规采样次数
#define ADCx_CHNT_S1_MAX   ((uint32_t)0xF)                                        // ADCx_CHNT_S1最大值
#define ADCx_CHNT_S1_POS   0                                                      // ADCx_CHNT_S1起始位
#define ADCx_CHNT_S1_MASK  (uint32_t)((uint32_t)0xF << ADCx_CHNT_S1_POS)          // ADCx_CHNT_S1位掩码
#define ADCx_CHNT_S1(x)    (uint32_t)((uint32_t)((x) & 0xF) << ADCx_CHNT_S1_POS)  // [3:0] 第一段常规采样次数

/* ADCx_GAIN(x = 0,1) */
#define ADCx_GAIN_IG1_BIT BIT15 // [15] IDAT1增益选择，0:±3.6V量程，1:±7.2V量程
#define ADCx_GAIN_IG0_BIT BIT14 // [14] IDAT0增益选择，0:±3.6V量程，1:±7.2V量程
#define ADCx_GAIN_G13_BIT BIT13 // [13] DAT13增益选择，0:±3.6V量程，1:±7.2V量程
#define ADCx_GAIN_G12_BIT BIT12 // [12] DAT12增益选择，0:±3.6V量程，1:±7.2V量程
#define ADCx_GAIN_G11_BIT BIT11 // [11] DAT11增益选择，0:±3.6V量程，1:±7.2V量程
#define ADCx_GAIN_G10_BIT BIT10 // [10] DAT10增益选择，0:±3.6V量程，1:±7.2V量程
#define ADCx_GAIN_G9_BIT  BIT9  // [9] DAT9增益选择，0:±3.6V量程，1:±7.2V量程
#define ADCx_GAIN_G8_BIT  BIT8  // [8] DAT8增益选择，0:±3.6V量程，1:±7.2V量程
#define ADCx_GAIN_G7_BIT  BIT7  // [7] DAT7增益选择，0:±3.6V量程，1:±7.2V量程
#define ADCx_GAIN_G6_BIT  BIT6  // [6] DAT6增益选择，0:±3.6V量程，1:±7.2V量程
#define ADCx_GAIN_G5_BIT  BIT5  // [5] DAT5增益选择，0:±3.6V量程，1:±7.2V量程
#define ADCx_GAIN_G4_BIT  BIT4  // [4] DAT4增益选择，0:±3.6V量程，1:±7.2V量程
#define ADCx_GAIN_G3_BIT  BIT3  // [3] DAT3增益选择，0:±3.6V量程，1:±7.2V量程
#define ADCx_GAIN_G2_BIT  BIT2  // [2] DAT2增益选择，0:±3.6V量程，1:±7.2V量程
#define ADCx_GAIN_G1_BIT  BIT1  // [1] DAT1增益选择，0:±3.6V量程，1:±7.2V量程
#define ADCx_GAIN_G0_BIT  BIT0  // [0] DAT0增益选择，0:±3.6V量程，1:±7.2V量程

/* ADCx_CFG (x = 0,1) */
#define ADCx_CFG_NSMP_BIT       BIT12                                                  // [12] 0:单段采样，1:两段采样
#define ADCx_CFG_FSM_RS_BIT     BIT11                                                  // [11] 状态机复位控制信号。软件写入1产生复位，将ADC内部状态机回到初始状态，完成后自动回到0。该复位控制，不影响ADC其它寄存器的配置值。读取该位返回ADC当前状态，1表示ADC目前正在采样转换工作中，0表示空闲。
#define ADCx_CFG_DATA_ALIGN_BIT BIT10                                                  // [10] ADC_DAT对齐方式0：左对齐，右端补4’h0，1：右对齐，左端补4bit符号位
#define ADCx_CFG_CSMP_BIT       BIT8                                                   // [8] 连续采样模式0：不开启1：开启连续采样模式，触发到来后，ADC即开始采样转换，完成所有信号的转换后，无需等待触发立即从第0个信号开始新一轮的采样转换
#define ADCx_CFG_TCNT_MAX       ((uint32_t)0xF)                                        // ADCx_CFG_TCNT最大值
#define ADCx_CFG_TCNT_POS       4                                                      // ADCx_CFG_TCNT起始位
#define ADCx_CFG_TCNT_MASK      (uint32_t)((uint32_t)0xF << ADCx_CFG_TCNT_POS)         // ADCx_CFG_TCNT位掩码
#define ADCx_CFG_TCNT(x)        (uint32_t)((uint32_t)((x) & 0xF) << ADCx_CFG_TCNT_POS) // [7:4] 触发一次采样所需的事件数。0：表示需要发生1次事件才能触发一次采样1：表示需要发生2次事件才能触发一次采样……15：表示需要发生16次事件才能触发一次采样
#define ADCx_CFG_TROVS_BIT      BIT3                                                   // [3] 过采样触发模式0：一次触发即连续过采样多次至OVSR，并将数据平均后存入，可以配置采样多个通道，每个通道都采样OVSR次后才进行下一个通道的采样。1：一次触发只进行一次采样转换，需要OVSR次触发才完成足够数据的采集并进行平均，而后存入数据寄存器。受到累加器个数限制，在此种配置下，ADCx_CHNT只能配置采样一个通道。
#define ADCx_CFG_OVSR_MAX       ((uint32_t)0x7)                                        // ADCx_CFG_OVSR最大值
#define ADCx_CFG_OVSR_POS       0                                                      // ADCx_CFG_OVSR起始位
#define ADCx_CFG_OVSR_MASK      (uint32_t)((uint32_t)0x7 << ADCx_CFG_OVSR_POS)         // ADCx_CFG_OVSR位掩码
#define ADCx_CFG_OVSR(x)        (uint32_t)((uint32_t)((x) & 0x7) << ADCx_CFG_OVSR_POS) // [2:0] 过采样率0：1，默认1次采样即存入数据1：2次采样后存入数据2：4次采样后存入数据3：8次采样后存入数据4：16次采样后存入数据5：32次采样后存入数据6：64次采样后存入数据7：128次采样后存入数据过采样率设置为非0值时需要保证ADC0和ADC1不会同时工作。即其中一个ADC采样转换过程中，另外一个ADC的采样触发事件不能发生。

/* ADC0_TRIG */
#define ADC0_TRIG_CL_IT3_EN_BIT      BIT15 // [15] CL_OUTPUT[3]触发ADC空闲采样使能，高有效
#define ADC0_TRIG_CL_IT2_EN_BIT      BIT14 // [14] CL_OUTPUT[2]触发ADC空闲采样使能，高有效
#define ADC0_TRIG_CL_IT1_EN_BIT      BIT13 // [13] CL_OUTPUT[1]触发ADC空闲采样使能，高有效
#define ADC0_TRIG_CL_IT0_EN_BIT      BIT12 // [12] CL_OUTPUT[0]触发ADC空闲采样使能，高有效
#define ADC0_TRIG_CL_NT3_EN_BIT      BIT11 // [11] CL_OUTPUT[3]触发ADC常规采样使能，高有效
#define ADC0_TRIG_CL_NT2_EN_BIT      BIT10 // [10] CL_OUTPUT[2]触发ADC常规采样使能，高有效
#define ADC0_TRIG_CL_NT1_EN_BIT      BIT9  // [9] CL_OUTPUT[1]触发ADC常规采样使能，高有效
#define ADC0_TRIG_CL_NT0_EN_BIT      BIT8  // [8] CL_OUTPUT[0]触发ADC常规采样使能，高有效
#define ADC0_TRIG_TIMER2_CMP1_EN_BIT BIT7  // [7] TIMER2比较事件1触发ADC常规采样使能，高有效
#define ADC0_TRIG_TIMER2_CMP0_EN_BIT BIT6  // [6] TIMER2比较事件0触发ADC常规采样使能，高有效
#define ADC0_TRIG_TIMER0_CMP1_EN_BIT BIT5  // [5] TIMER0比较事件1触发ADC常规采样使能，高有效
#define ADC0_TRIG_TIMER0_CMP0_EN_BIT BIT4  // [4] TIMER0比较事件0触发ADC常规采样使能，高有效
#define ADC0_TRIG_MCPWM0_T3_EN_BIT   BIT3  // [3] MCPWM0 T3事件触发ADC常规采样使能，高有效
#define ADC0_TRIG_MCPWM0_T2_EN_BIT   BIT2  // [2] MCPWM0 T2事件触发ADC常规采样使能，高有效
#define ADC0_TRIG_MCPWM0_T1_EN_BIT   BIT1  // [1] MCPWM0 T1事件触发ADC常规采样使能，高有效
#define ADC0_TRIG_MCPWM0_T0_EN_BIT   BIT0  // [0] MCPWM0 T0事件触发ADC常规采样使能，高有效

/* ADC1_TRIG */
#define ADC1_TRIG_CL_IT3_EN_BIT      BIT15 // [15] CL_OUTPUT[3]触发ADC空闲采样使能，高有效
#define ADC1_TRIG_CL_IT2_EN_BIT      BIT14 // [14] CL_OUTPUT[2]触发ADC空闲采样使能，高有效
#define ADC1_TRIG_CL_IT1_EN_BIT      BIT13 // [13] CL_OUTPUT[1]触发ADC空闲采样使能，高有效
#define ADC1_TRIG_CL_IT0_EN_BIT      BIT12 // [12] CL_OUTPUT[0]触发ADC空闲采样使能，高有效
#define ADC1_TRIG_CL_NT3_EN_BIT      BIT11 // [11] CL_OUTPUT[3]触发ADC常规采样使能，高有效
#define ADC1_TRIG_CL_NT2_EN_BIT      BIT10 // [10] CL_OUTPUT[2]触发ADC常规采样使能，高有效
#define ADC1_TRIG_CL_NT1_EN_BIT      BIT9  // [9] CL_OUTPUT[1]触发ADC常规采样使能，高有效
#define ADC1_TRIG_CL_NT0_EN_BIT      BIT8  // [8] CL_OUTPUT[0]触发ADC常规采样使能，高有效
#define ADC1_TRIG_TIMER3_CMP1_EN_BIT BIT7  // [7] TIMER3比较事件1触发ADC常规采样使能，高有效
#define ADC1_TRIG_TIMER3_CMP0_EN_BIT BIT6  // [6] TIMER3比较事件0触发ADC常规采样使能，高有效
#define ADC1_TRIG_TIMER1_CMP1_EN_BIT BIT5  // [5] TIMER1比较事件1触发ADC常规采样使能，高有效
#define ADC1_TRIG_TIMER1_CMP0_EN_BIT BIT4  // [4] TIMER1比较事件0触发ADC常规采样使能，高有效
#define ADC1_TRIG_MCPWM0_T3_EN_BIT   BIT3  // [3] MCPWM0 T3事件触发ADC常规采样使能，高有效
#define ADC1_TRIG_MCPWM0_T2_EN_BIT   BIT2  // [2] MCPWM0 T2事件触发ADC常规采样使能，高有效
#define ADC1_TRIG_MCPWM0_T1_EN_BIT   BIT1  // [1] MCPWM0 T1事件触发ADC常规采样使能，高有效
#define ADC1_TRIG_MCPWM0_T0_EN_BIT   BIT0  // [0] MCPWM0 T0事件触发ADC常规采样使能，高有效

/* ADCx_SWT(x = 0,1) */
#define ADCx_SWT_SWT_MAX  ((uint32_t)0xFFFF)                                       // ADCx_SWT_SWT最大值
#define ADCx_SWT_SWT_POS  0                                                        // ADCx_SWT_SWT起始位
#define ADCx_SWT_SWT_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_SWT_SWT_POS)         // ADCx_SWT_SWT位掩码
#define ADCx_SWT_SWT(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_SWT_SWT_POS) // [15:0] 写入数据为0x5AA5时，产生一次常规触发写入数据位0xF00F时，产生一次空闲触发

/* ADCx_DC0(x = 0,1) */
#define ADCx_DC0_DC_OFFSET_MAX  ((uint32_t)0xFFFF)                                             // ADCx_DC0_DC_OFFSET最大值
#define ADCx_DC0_DC_OFFSET_POS  0                                                              // ADCx_DC0_DC_OFFSET起始位
#define ADCx_DC0_DC_OFFSET_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_DC0_DC_OFFSET_POS)         // ADCx_DC0_DC_OFFSET位掩码
#define ADCx_DC0_DC_OFFSET(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_DC0_DC_OFFSET_POS) // [15:0] ADC采样电路DC offset

/* ADCx_AMC0(x = 0,1) */
#define ADCx_AMC0_AM_CALI_MAX  ((uint32_t)0x3FF)                                            // ADCx_AMC0_AM_CALI最大值
#define ADCx_AMC0_AM_CALI_POS  0                                                            // ADCx_AMC0_AM_CALI起始位
#define ADCx_AMC0_AM_CALI_MASK (uint32_t)((uint32_t)0x3FF << ADCx_AMC0_AM_CALI_POS)         // ADCx_AMC0_AM_CALI位掩码
#define ADCx_AMC0_AM_CALI(x)   (uint32_t)((uint32_t)((x) & 0x3FF) << ADCx_AMC0_AM_CALI_POS) // [9:0] ADC 采样电路增益校正系数

/* ADCx_DC1(x = 0,1) */
#define ADCx_DC1_DC_OFFSET_MAX  ((uint32_t)0xFFFF)                                             // ADCx_DC1_DC_OFFSET最大值
#define ADCx_DC1_DC_OFFSET_POS  0                                                              // ADCx_DC1_DC_OFFSET起始位
#define ADCx_DC1_DC_OFFSET_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_DC1_DC_OFFSET_POS)         // ADCx_DC1_DC_OFFSET位掩码
#define ADCx_DC1_DC_OFFSET(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_DC1_DC_OFFSET_POS) // [15:0] ADC采样电路DC offset

/* ADCx_AMC1(x = 0,1) */
#define ADCx_AMC1_AM_CALI_MAX  ((uint32_t)0x3FF)                                            // ADCx_AMC1_AM_CALI最大值
#define ADCx_AMC1_AM_CALI_POS  0                                                            // ADCx_AMC1_AM_CALI起始位
#define ADCx_AMC1_AM_CALI_MASK (uint32_t)((uint32_t)0x3FF << ADCx_AMC1_AM_CALI_POS)         // ADCx_AMC1_AM_CALI位掩码
#define ADCx_AMC1_AM_CALI(x)   (uint32_t)((uint32_t)((x) & 0x3FF) << ADCx_AMC1_AM_CALI_POS) // [9:0] ADC 采样电路增益校正系数

/* ADCx_IE(x = 0,1) */
#define ADCx_IE_ISF_RE_BIT  BIT15 // [15] 空闲采样完成DMA请求使能
#define ADCx_IE_HERR_RE_BIT BIT14 // [14] 硬件触发发生在非空闲状态DMA请求使能
#define ADCx_IE_SERR_RE_BIT BIT13 // [13] 软件触发发生在非空闲状态DMA请求使能
#define ADCx_IE_AWD0_RE_BIT BIT10 // [10] 阈值监测0超限DMA请求使能
#define ADCx_IE_SF2_RE_BIT  BIT9  // [9] 第二段采样完成DMA请求使能
#define ADCx_IE_SF1_RE_BIT  BIT8  // [8] 第一段采样完成DMA请求使能
#define ADCx_IE_ISF_IE_BIT  BIT7  // [7] 空闲采样完成中断使能
#define ADCx_IE_HERR_IE_BIT BIT6  // [6] 硬件触发发生在非空闲状态中断使能
#define ADCx_IE_SERR_IE_BIT BIT5  // [5] 软件触发发生在非空闲状态中断使能
#define ADCx_IE_AWD0_IE_BIT BIT2  // [2] 阈值监测0超限中断使能
#define ADCx_IE_SF2_IE_BIT  BIT1  // [1] 第二段常规采样完成中断使能
#define ADCx_IE_SF1_IE_BIT  BIT0  // [0] 第一段常规采样完成中断使能

/* ADCx_IF(x = 0,1) */
#define ADCx_IF_ISF_IF_BIT  BIT7 // [7] 空闲采样完成中断标志
#define ADCx_IF_HERR_IF_BIT BIT6 // [6] 硬件触发发生在非空闲状态中断标志
#define ADCx_IF_SERR_IF_BIT BIT5 // [5] 软件触发发生在非空闲状态中断标志
#define ADCx_IF_AWD0_IF_BIT BIT2 // [2] 阈值监测0超限中断标志
#define ADCx_IF_SF2_IF_BIT  BIT1 // [1] 第二段常规采样完成中断标志
#define ADCx_IF_SF1_IF_BIT  BIT0 // [0] 第一段常规采样完成中断标志

/* ADCx_LTH(x = 0,1) */
#define ADCx_LTH_LTH_MAX  ((uint32_t)0xFFF)                                       // ADCx_LTH_LTH最大值
#define ADCx_LTH_LTH_POS  0                                                       // ADCx_LTH_LTH起始位
#define ADCx_LTH_LTH_MASK (uint32_t)((uint32_t)0xFFF << ADCx_LTH_LTH_POS)         // ADCx_LTH_LTH位掩码
#define ADCx_LTH_LTH(x)   (uint32_t)((uint32_t)((x) & 0xFFF) << ADCx_LTH_LTH_POS) // [11:0] ADC模拟看门狗0下阈值

/* ADCx_HTH(x = 0,1) */
#define ADCx_HTH_HTH_MAX  ((uint32_t)0xFFF)                                       // ADCx_HTH_HTH最大值
#define ADCx_HTH_HTH_POS  0                                                       // ADCx_HTH_HTH起始位
#define ADCx_HTH_HTH_MASK (uint32_t)((uint32_t)0xFFF << ADCx_HTH_HTH_POS)         // ADCx_HTH_HTH位掩码
#define ADCx_HTH_HTH(x)   (uint32_t)((uint32_t)((x) & 0xFFF) << ADCx_HTH_HTH_POS) // [11:0] ADC模拟看门狗0上阈值

/* ADCx_GEN(x = 0,1) */
#define ADCx_GEN_GEN_MAX  ((uint32_t)0xFFFF)                                       // ADCx_GEN_GEN最大值
#define ADCx_GEN_GEN_POS  0                                                        // ADCx_GEN_GEN起始位
#define ADCx_GEN_GEN_MASK (uint32_t)((uint32_t)0xFFFF << ADCx_GEN_GEN_POS)         // ADCx_GEN_GEN位掩码
#define ADCx_GEN_GEN(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << ADCx_GEN_GEN_POS) // [15:0] ADC模拟看门狗0对应使能位BIT0: DAT0看门狗监测使能BIT1: DAT1看门狗监测使能……BIT13: DAT13看门狗监测使能BIT14: IDAT0看门狗监测使能BIT15: IDAT1看门狗监测使能

/* TIMER0_CFG Timer0 配置寄存器 */
#define TIMER0_CFG_EN_BIT            BIT31                                                       // [31] Timer模块整体使能，高有效
#define TIMER0_CFG_CAP1_CLR_EN_BIT   BIT29                                                       // [29] 当发生CAP1捕获事件时，清零Timer计数器，高有效
#define TIMER0_CFG_CAP0_CLR_EN_BIT   BIT28                                                       // [28] 当发生CAP0捕获事件时，清零Timer计数器，高有效
#define TIMER0_CFG_UPDATE_BIT        BIT27                                                       // [27] 软件更新启用影子寄存器时，向UPDATE写1将TH/CMP0/CMP1的预装载值加载到影子寄存器STH/SCMP0/SCMP1之中。自动清零，读回恒为0。写0无作用。推荐使用TIMER0_CFG\ =BIT27;的方式进行手动更新影子寄存器的操作，防止手动更新时误将其他配置清零。
#define TIMER0_CFG_SHADOW_BIT        BIT26                                                       // [26] 0: 不启用影子寄存器，软件写入TH/CMP0/CMP1时直接更新对应的影子寄存器1: 启用影子寄存器，软件写入TH/CMP0/CMP1时进仅仅更新预装载值，当Timer发生过零事件时才将预装载值写入影子寄存器
#define TIMER0_CFG_ONE_TRIG_BIT      BIT25                                                       // [25] 单次发送模式，此位需要在Timer比较模式下使用，且EN需设置为0ETON为0时，软件向ONE_TRIG写1触发Timer发送一个周期的特定占空比的脉冲，Timer计数一个周期后停止。此位在Timer计数的当前周期内读为1，Timer停止后，自动清零。ETON为1时，即使软件配置ONE_TRIG=1，也需要等待外部事件触发，Timer计数一个周期后停止。ONE_TRIG位在外部触发Timer计数一个周期停止后被硬件清零。
#define TIMER0_CFG_CENTER_BIT        BIT24                                                       // [24] 中心计数模式使能0: Timer向上从0计数至TH，然后回0，或Timer向下从TH计数至0，然后回到TH1: Timer向上从0计数至TH，然后向下计数至0
#define TIMER0_CFG_DIR_BIT           BIT23                                                       // [23] 0: 0-\>TH递增计数，1：TH-\>递减计数此位在CENTER=1时只读，用于指示当前计数方向
#define TIMER0_CFG_CLK_DIV_MAX       ((uint32_t)0x7)                                             // TIMER0_CFG_CLK_DIV最大值
#define TIMER0_CFG_CLK_DIV_POS       20                                                          // TIMER0_CFG_CLK_DIV起始位
#define TIMER0_CFG_CLK_DIV_MASK      (uint32_t)((uint32_t)0x7 << TIMER0_CFG_CLK_DIV_POS)         // TIMER0_CFG_CLK_DIV位掩码
#define TIMER0_CFG_CLK_DIV(x)        (uint32_t)((uint32_t)((x) & 0x7) << TIMER0_CFG_CLK_DIV_POS) // [22:20] Timer计数器频率配置，计数器计数频率是系统主时钟频率的2CLK_DIV分频。默认值为0，不分频。0: 1分频1: 2分频2: 4分频3: 8分频4: 16分频5: 32分频6: 64分频7: 128分频
#define TIMER0_CFG_ETON_BIT          BIT19                                                       // [19] Timer计数器外部启动使能0: 自动运行1:等待外部事件触发计数，外部触发信号根据TIMER0_EVT.EVT_SRC进行选择需要注意的是，使用外部触发也需要设置TIMERx_CFG.EN=1，除非是外部信号进行的单次触发，即TIMERx_CFG.ONE_TRIG=1。
#define TIMER0_CFG_GATE_EN_BIT       BIT18                                                       // [18] Timer暂停使能0：不暂停1：当外部信号为低时，Timer暂停计数，外部信号根据TIMER0_EVT.EVT_SRC进行选择
#define TIMER0_CFG_RL_EN_BIT         BIT17                                                       // [17] Timer重装使能0：禁用外部事件重装，Timer向上计数至TH回0，或向下计数值0回到TH1：使能外部事件重装，重装信号根据TIMER0_EVT.EVT_SRC进行选择，当向上计数时，发生外部事件，Timer重装为0,；当向下计数时，发生外部事件，Timer重装为TH。
#define TIMER0_CFG_XCLK_EN_BIT       BIT16                                                       // [16] Timer 时钟源0: 芯片内部时钟1: 外部时钟，时钟源根据TIMER0_EVT.EVT_SRC进行选择，当使用外部时钟时，CLK_DIV不再起作用，即时钟不再进行分频
#define TIMER0_CFG_SRC1_MAX          ((uint32_t)0xF)                                             // TIMER0_CFG_SRC1最大值
#define TIMER0_CFG_SRC1_POS          12                                                          // TIMER0_CFG_SRC1起始位
#define TIMER0_CFG_SRC1_MASK         (uint32_t)((uint32_t)0xF << TIMER0_CFG_SRC1_POS)            // TIMER0_CFG_SRC1位掩码
#define TIMER0_CFG_SRC1(x)           (uint32_t)((uint32_t)((x) & 0xF) << TIMER0_CFG_SRC1_POS)    // [15:12] Timer捕获模式通道1信号来源。默认为3’h1。0: Timer通道0，来自芯片GPIO（参见Datasheet及应用配置）1: Timer通道1，来自芯片GPIO（参见Datasheet及应用配置）2: CLU0输出3: CLU1输出4: CLU2输出5: CLU3输出6: 比较器0的输出7: 比较器1的输出8: 比较器2的输出9: Timer通道0和1的异或
#define TIMER0_CFG_CH1_POL_BIT       BIT11                                                       // [11] Timer通道1在比较模式下的输出极性控制，当计数器CNT\<CMP1时的输出值。
#define TIMER0_CFG_CH1_MODE_BIT      BIT10                                                       // [10] Timer通道1的工作模式选择，默认值为0。0: 比较模式。输出方波，在Timer通道1计数器计数值等于0或等于Timer比较捕获寄存器值时，IO发生翻转。1: 捕获模式。当Timer通道1输入信号发生捕获事件时，将计数器计数值存入Timer通道1比较捕获寄存器。
#define TIMER0_CFG_CH1_FE_CAP_EN_BIT BIT9                                                        // [9] Timer通道1下降沿捕获事件使能。1:使能；0:关闭。Timer通道1输入信号发生1?0跳变被视为捕获事件。下降沿事件使能可以与上升沿事件使能并存。
#define TIMER0_CFG_CH1_RE_CAP_EN_BIT BIT8                                                        // [8] Timer通道1上升沿捕获事件使能。1:使能；0:关闭。Timer通道1输入信号发生0?1跳变被视为捕获事件。上升沿事件使能可以与下降沿事件使能并存。
#define TIMER0_CFG_SRC0_MAX          ((uint32_t)0xF)                                             // TIMER0_CFG_SRC0最大值
#define TIMER0_CFG_SRC0_POS          4                                                           // TIMER0_CFG_SRC0起始位
#define TIMER0_CFG_SRC0_MASK         (uint32_t)((uint32_t)0xF << TIMER0_CFG_SRC0_POS)            // TIMER0_CFG_SRC0位掩码
#define TIMER0_CFG_SRC0(x)           (uint32_t)((uint32_t)((x) & 0xF) << TIMER0_CFG_SRC0_POS)    // [7:4] Timer捕获模式通道0信号来源。默认为3’h0。0: Timer通道0，来自芯片GPIO（参见Datasheet及应用配置）1: Timer通道1，来自芯片GPIO（参见Datasheet及应用配置）2: CLU0输出3: CLU1输出4: CLU2输出5: CLU3输出6: 比较器0的输出7: 比较器1的输出8: 比较器2的输出9: Timer通道0和1的异或
#define TIMER0_CFG_CH0_POL_BIT       BIT3                                                        // [3] Timer通道0在比较模式下的输出极性控制:当计数器CNT\<CMP0时的输出值。时的输出值。
#define TIMER0_CFG_CH0_MODE_BIT      BIT2                                                        // [2] Timer通道0的工作模式选择，默认值为0。0: 比较模式。输出方波，在Timer通道0计数器计数值等于0或等于Timer比较捕获寄存器值时，IO发生翻转。1: 捕获模式。当Timer通道0输入信号发生捕获事件时，将计数器计数值存入Timer通道0比较捕获寄存器。
#define TIMER0_CFG_CH0_FE_CAP_EN_BIT BIT1                                                        // [1] Timer通道0下降沿捕获事件使能。1:使能；0:关闭。Timer通道0输入信号发生1?0跳变被视为捕获事件。下降沿事件使能可以与上升沿事件使能并存。
#define TIMER0_CFG_CH0_RE_CAP_EN_BIT BIT0                                                        // [0] Timer通道0上升沿捕获事件使能。1:使能；0:关闭。Timer通道0输入信号发生0?1跳变被视为捕获事件。上升沿事件使能可以与下降沿事件使能并存。

/* TIMER0_TH Timer0 门限寄存器 */
#define TIMER0_TH_TH_MAX  ((uint32_t)0xFFFF)                                       // TIMER0_TH_TH最大值
#define TIMER0_TH_TH_POS  0                                                        // TIMER0_TH_TH起始位
#define TIMER0_TH_TH_MASK (uint32_t)((uint32_t)0xFFFF << TIMER0_TH_TH_POS)         // TIMER0_TH_TH位掩码
#define TIMER0_TH_TH(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << TIMER0_TH_TH_POS) // [15:0] Timer 计数器计数门限。向上计数从0计数到TH值后回0，或向下计数从TH计数到0后回到TH

/* TIMER0_CNT Timer0 计数寄存器 */
#define TIMER0_CNT_CNT_MAX  ((uint32_t)0xFFFF)                                         // TIMER0_CNT_CNT最大值
#define TIMER0_CNT_CNT_POS  0                                                          // TIMER0_CNT_CNT起始位
#define TIMER0_CNT_CNT_MASK (uint32_t)((uint32_t)0xFFFF << TIMER0_CNT_CNT_POS)         // TIMER0_CNT_CNT位掩码
#define TIMER0_CNT_CNT(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << TIMER0_CNT_CNT_POS) // [15:0] Timer 0计数器当前计数值。写操作可以写入新的计数值。

/* TIMER0_CMP0 Timer0 通道0比较捕获寄存器 */
#define TIMER0_CMP0_CMP0_MAX  ((uint32_t)0xFFFF)                                           // TIMER0_CMP0_CMP0最大值
#define TIMER0_CMP0_CMP0_POS  0                                                            // TIMER0_CMP0_CMP0起始位
#define TIMER0_CMP0_CMP0_MASK (uint32_t)((uint32_t)0xFFFF << TIMER0_CMP0_CMP0_POS)         // TIMER0_CMP0_CMP0位掩码
#define TIMER0_CMP0_CMP0(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << TIMER0_CMP0_CMP0_POS) // [15:0] Timer 通道0工作在比较模式时，当计数器计数值等于CMP0时，发生比较事件。Timer 通道0工作在捕获模式时，发生捕获事件时的计数器计数值存入CMP0寄存器。

/* TIMER0_CMP1 Timer0 通道1比较捕获寄存器 */
#define TIMER0_CMP1_CMP1_MAX  ((uint32_t)0xFFFF)                                           // TIMER0_CMP1_CMP1最大值
#define TIMER0_CMP1_CMP1_POS  0                                                            // TIMER0_CMP1_CMP1起始位
#define TIMER0_CMP1_CMP1_MASK (uint32_t)((uint32_t)0xFFFF << TIMER0_CMP1_CMP1_POS)         // TIMER0_CMP1_CMP1位掩码
#define TIMER0_CMP1_CMP1(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << TIMER0_CMP1_CMP1_POS) // [15:0] Timer 通道1工作在比较模式时，当计数器计数值等于CMP1时，发生比较事件。Timer 通道1工作在捕获模式时，发生捕获事件时的计数器计数值存入CMP1寄存器。

/* TIMER0_EVT Timer0 外部事件选择寄存器 */
#define TIMER0_EVT_EVT_SRC_MAX  ((uint32_t)0xF)                                             // TIMER0_EVT_EVT_SRC最大值
#define TIMER0_EVT_EVT_SRC_POS  0                                                           // TIMER0_EVT_EVT_SRC起始位
#define TIMER0_EVT_EVT_SRC_MASK (uint32_t)((uint32_t)0xF << TIMER0_EVT_EVT_SRC_POS)         // TIMER0_EVT_EVT_SRC位掩码
#define TIMER0_EVT_EVT_SRC(x)   (uint32_t)((uint32_t)((x) & 0xF) << TIMER0_EVT_EVT_SRC_POS) // [3:0] Timer外部事件选择寄存器，本寄存器需要配合TIMER0_CFG.ETON，TIMER0_CFG.GATE_EN，TIMER0_CFG.RL_EN，TIMER0_CFG.XCLK_EN使用。通常4个设置位不同时使用。当设置ETON=1时，根据本寄存器选择触发Timer计数的事件。需要注意的是，Timer自身的比较事件无法触发Timer进行计数。当ETON=1时，触发信号的上升沿触发Timer开始计数，用作触发源的Timer需要工作在比较模式，无须从外部输入信号至Timer通道0:不可用1:不可用2:TIMER1 通道0比较/捕获事件3:TIMER1 通道1比较/捕获事件4:TIMER2 通道0比较/捕获事件5:TIMER2 通道1比较/捕获事件6:TIMER3 通道0比较/捕获事件7:TIMER3 通道1比较/捕获事件8:CLU0输出上升沿9:CLU1输出上升沿10:CLU2输出上升沿11:CLU3输出上升沿12:MCPWM TADC[0]比较事件13:MCPWM TADC[1]比较事件14:MCPWM TADC[2]比较事件15:MCPWM TADC[3]比较事件当GATE_EN=1，且外部信号为高时Timer计数，外部信号为低时，Timer暂停，当GATE_EN=1时，Timer使用对应外部信号的电平信号作为计数门控。GATE_EN仅支持配合0~11的外部事件使用，当EVT_SRC选择为0~7时，外部信号为Timer通道输入信号经过对应Timer滤波后的信号，作为门控信号的Timer通道需要配置为输入使能。0:TIMER0 通道0滤波后输入信号1:TIMER0 通道1滤波后输入信号2:TIMER1 通道0滤波后输入信号3:TIMER1 通道1滤波后输入信号4:TIMER2 通道0滤波后输入信号5:TIMER2 通道1滤波后输入信号6:TIMER3 通道0滤波后输入信号7:TIMER3 通道1滤波后输入信号8:CLU0输出信号9:CLU1输出信号10:CLU2输出信号11:CLU3输出信号当RL_EN为高时，Timer使用外部信号作为重装载信号作为重装载信号的Timer通道需要配置为输入使能0:TIMER0 通道0比较/捕获事件1:TIMER0 通道1比较/捕获事件2:TIMER1 通道0比较/捕获事件3:TIMER1 通道1比较/捕获事件4:TIMER2 通道0比较/捕获事件5:TIMER2 通道1比较/捕获事件6:TIMER3 通道0比较/捕获事件7:TIMER3 通道1比较/捕获事件8:CLU0输出9:CLU1输出10:CLU2输出11:CLU3输出12:MCPWM TADC[0]比较事件13:MCPWM TADC[1]比较事件14:MCPWM TADC[2]比较事件15:MCPWM TADC[3]比较事件当XCLK_EN为高时，Timer使用外部信号作为Timer外部时钟，Timer在时钟上升沿进行计数动作。如果使用Timer通道作为外部时钟，通道信号受到对应Timer滤波设置影响。0:TIMER0 通道0输入信号1:TIMER0 通道1输入信号2:TIMER1 通道0输入信号3:TIMER1 通道1输入信号4:TIMER2 通道0输入信号5:TIMER2 通道1输入信号6:TIMER3 通道0输入信号7:TIMER3 通道1输入信号8:CLU0输出9:CLU1输出10:CLU2输出11:CLU3输出12:MCPWM TADC[0]比较事件13:MCPWM TADC[1]比较事件14:MCPWM TADC[2]比较事件15:MCPWM TADC[3]比较事件

/* TIMER0_FLT Timer0 滤波控制寄存器 */
#define TIMER0_FLT_FLT_MAX  ((uint32_t)0xFF)                                         // TIMER0_FLT_FLT最大值
#define TIMER0_FLT_FLT_POS  0                                                        // TIMER0_FLT_FLT起始位
#define TIMER0_FLT_FLT_MASK (uint32_t)((uint32_t)0xFF << TIMER0_FLT_FLT_POS)         // TIMER0_FLT_FLT位掩码
#define TIMER0_FLT_FLT(x)   (uint32_t)((uint32_t)((x) & 0xFF) << TIMER0_FLT_FLT_POS) // [7:0] 通道0/1信号滤波宽度选择。取值范围0~255。FLT为0时，不对通道进行滤波。FLT不为0时，对通道信号进行滤波:滤波宽度为FLT×8。当通道信号电平稳定超过FLT×8个系统时钟周期宽度时，滤波器输出更新；否则，滤波器保持当前的输出不变。

/* TIMER0_IE Timer0 中断使能寄存器 */
#define TIMER0_IE_FAIL_RE_BIT BIT11 // [11] Timer FAIL事件 DMA请求使能，高电平有效。
#define TIMER0_IE_ZC_RE_BIT   BIT10 // [10] Timer计数器过0 DMA请求使能，高电平有效。
#define TIMER0_IE_CH1_RE_BIT  BIT9  // [9] Timer通道1比较/捕获 DMA请求使能，高电平有效。
#define TIMER0_IE_CH0_RE_BIT  BIT8  // [8] Timer通道0比较/捕获 DMA请求使能，高电平有效。
#define TIMER0_IE_FAIL_IE_BIT BIT3  // [3] Timer FAIL事件中断使能，高电平有效。
#define TIMER0_IE_ZC_IE_BIT   BIT2  // [2] Timer计数器过0中断使能，高电平有效。
#define TIMER0_IE_CH1_IE_BIT  BIT1  // [1] Timer通道1比较/捕获中断使能，高电平有效。
#define TIMER0_IE_CH0_IE_BIT  BIT0  // [0] Timer通道0比较/捕获中断使能，高电平有效。

/* TIMER0_IF Timer0 中断标志寄存器 */
#define TIMER0_IF_FAIL_IF_BIT BIT3 // [3] Timer Fail事件中断标志。高电平有效，写1清0
#define TIMER0_IF_ZC_IF_BIT   BIT2 // [2] Timer计数器过0中断标志。高电平有效，写1清0
#define TIMER0_IF_CH1_IF_BIT  BIT1 // [1] Timer通道1比较/捕获中断标志。高电平有效，写1清0
#define TIMER0_IF_CH0_IF_BIT  BIT0 // [0] Timer通道0比较/捕获中断标志。高电平有效，写1清0

/* TIMER0_IO Timer0 IO 控制寄存器 */
#define TIMER0_IO_CH1_DEFAULT_BIT BIT9 // [9] 发生Fail事件MOE清零后，CH1通道输出值
#define TIMER0_IO_CH0_DEFAULT_BIT BIT8 // [8] 发生Fail事件MOE清零后，CH0通道输出值
#define TIMER0_IO_HALT_PRT_BIT    BIT7 // [7] MCU进入HALT状态，Timer输出值选择。1: 输出CH1_DEFAULT和CH0_DEFAULT；0:正常输出
#define TIMER0_IO_MOE_BIT         BIT6 // [6] 当TIMER0_CFG.CENTER=1时，Timer通道0/1输出使能1:输出正常信号0:输出CH0_DEFAULT和CH1_DEFAULT默认值TIMER0_IF.FAIL_IF变1将触发MOE变成0，通道输出默认值。若要恢复输出正常信号，需要先将FAIL_IF清零，然后软件设置MOE=1
#define TIMER0_IO_FAIL_SEL_BIT    BIT2 // [2] FAIL信号选择0：TIMER0_FAIL，来自GPIO1：CLU0输出
#define TIMER0_IO_FAIL_POL_BIT    BIT1 // [1] FAIL信号极性0：高电平FAIL1：低电平FAIL
#define TIMER0_IO_FAIL_EN_BIT     BIT0 // [0] FAIL信号使能 0：禁用FAIL1：使能FAIL

/* TIMER1_CFG Timer1 配置寄存器 */
#define TIMER1_CFG_EN_BIT            BIT31                                                       // [31] Timer模块整体使能，高有效
#define TIMER1_CFG_CAP1_CLR_EN_BIT   BIT29                                                       // [29] 当发生CAP1捕获事件时，清零Timer计数器，高有效
#define TIMER1_CFG_CAP0_CLR_EN_BIT   BIT28                                                       // [28] 当发生CAP0捕获事件时，清零Timer计数器，高有效
#define TIMER1_CFG_ONE_TRIG_BIT      BIT25                                                       // [25] 单次发送模式，此位需要在Timer比较模式下使用，且EN需设置为0ETON为0时，软件向ONE_TRIG写1触发Timer发送一个周期的特定占空比的脉冲，Timer计数一个周期后停止。此位在Timer计数的当前周期内读为1，Timer停止后，自动清零。ETON为1时，即使软件配置ONE_TRIG=1，也需要等待外部事件触发，Timer计数一个周期后停止。ONE_TRIG位在外部触发Timer计数一个周期停止后被硬件清零。
#define TIMER1_CFG_CENTER_BIT        BIT24                                                       // [24] 中心计数模式使能0: Timer向上从0计数至TH，然后回0，或Timer向下从TH计数至0，然后回到TH1: Timer向上从0计数至TH，然后向下计数至0
#define TIMER1_CFG_DIR_BIT           BIT23                                                       // [23] 0: 0-\>TH递增计数，1：TH-\>递减计数此位在CENTER=1时只读，用于指示当前计数方向
#define TIMER1_CFG_CLK_DIV_MAX       ((uint32_t)0x7)                                             // TIMER1_CFG_CLK_DIV最大值
#define TIMER1_CFG_CLK_DIV_POS       20                                                          // TIMER1_CFG_CLK_DIV起始位
#define TIMER1_CFG_CLK_DIV_MASK      (uint32_t)((uint32_t)0x7 << TIMER1_CFG_CLK_DIV_POS)         // TIMER1_CFG_CLK_DIV位掩码
#define TIMER1_CFG_CLK_DIV(x)        (uint32_t)((uint32_t)((x) & 0x7) << TIMER1_CFG_CLK_DIV_POS) // [22:20] Timer计数器频率配置，计数器计数频率是系统主时钟频率的2CLK_DIV分频。默认值为0，不分频。0: 1分频1: 2分频2: 4分频3: 8分频4: 16分频5: 32分频6: 64分频7: 128分频
#define TIMER1_CFG_ETON_BIT          BIT19                                                       // [19] Timer计数器计数外部启动使能0: 自动运行1: 等待外部事件触发计数，外部触发信号根据TIMER1_EVT.EVT_SRC进行选择需要注意的是，使用外部触发也需要设置TIMER1_CFG.EN=1，除非是外部信号进行的单次触发，即TIMER1_CFG.ONE_TRIG=1。
#define TIMER1_CFG_GATE_EN_BIT       BIT18                                                       // [18] Timer暂停使能0：不暂停1：当外部信号为低时，Timer暂停计数，外部信号根据TIMER1_EVT.EVT_SRC进行选择
#define TIMER1_CFG_RL_EN_BIT         BIT17                                                       // [17] Timer重装使能0：禁用外部事件重装，Timer向上计数至TH回0，或向下计数值0回到TH1：使能外部事件重装，重装信号根据TIMER1_EVT.EVT_SRC进行选择，当向上计数时，发生外部事件，Timer重装为0,；当向下计数时，发生外部事件，Timer重装为TH。
#define TIMER1_CFG_XCLK_EN_BIT       BIT16                                                       // [16] Timer 时钟源0: 芯片内部时钟1: 外部时钟，时钟源根据TIMER1_EVT.EVT_SRC进行选择，当使用外部时钟时，CLK_DIV不再起作用，即时钟不再进行分频
#define TIMER1_CFG_SRC1_MAX          ((uint32_t)0xF)                                             // TIMER1_CFG_SRC1最大值
#define TIMER1_CFG_SRC1_POS          12                                                          // TIMER1_CFG_SRC1起始位
#define TIMER1_CFG_SRC1_MASK         (uint32_t)((uint32_t)0xF << TIMER1_CFG_SRC1_POS)            // TIMER1_CFG_SRC1位掩码
#define TIMER1_CFG_SRC1(x)           (uint32_t)((uint32_t)((x) & 0xF) << TIMER1_CFG_SRC1_POS)    // [15:12] Timer捕获模式通道1信号来源。默认为3’h1。0: Timer通道0，来自芯片GPIO（参见Datasheet及应用配置）1: Timer通道1，来自芯片GPIO（参见Datasheet及应用配置）2: CLU0输出3: CLU1输出4: CLU2输出5: CLU3输出6: 比较器0的输出7: 比较器1的输出8: 比较器2的输出9: Timer通道0和1的异或
#define TIMER1_CFG_CH1_POL_BIT       BIT11                                                       // [11] Timer通道1在比较模式下的输出极性控制，当计数器CNT\<CMP1时的输出值。
#define TIMER1_CFG_CH1_MODE_BIT      BIT10                                                       // [10] Timer通道1的工作模式选择，默认值为0。0: 比较模式。输出方波，在Timer通道1计数器计数值等于0或等于Timer比较捕获寄存器值时，IO发生翻转。1: 捕获模式。当Timer通道1输入信号发生捕获事件时，将计数器计数值存入Timer通道1比较捕获寄存器。
#define TIMER1_CFG_CH1_FE_CAP_EN_BIT BIT9                                                        // [9] Timer通道1下降沿捕获事件使能。1:使能；0:关闭。Timer通道1输入信号发生1?0跳变被视为捕获事件。下降沿事件使能可以与上升沿事件使能并存。
#define TIMER1_CFG_CH1_RE_CAP_EN_BIT BIT8                                                        // [8] Timer通道1上升沿捕获事件使能。1:使能；0:关闭。Timer通道1输入信号发生0?1跳变被视为捕获事件。上升沿事件使能可以与下降沿事件使能并存。
#define TIMER1_CFG_SRC0_MAX          ((uint32_t)0xF)                                             // TIMER1_CFG_SRC0最大值
#define TIMER1_CFG_SRC0_POS          4                                                           // TIMER1_CFG_SRC0起始位
#define TIMER1_CFG_SRC0_MASK         (uint32_t)((uint32_t)0xF << TIMER1_CFG_SRC0_POS)            // TIMER1_CFG_SRC0位掩码
#define TIMER1_CFG_SRC0(x)           (uint32_t)((uint32_t)((x) & 0xF) << TIMER1_CFG_SRC0_POS)    // [7:4] Timer捕获模式通道0信号来源。默认为3’h0。0: Timer通道0，来自芯片GPIO（参见Datasheet及应用配置）1: Timer通道1，来自芯片GPIO（参见Datasheet及应用配置）2: CLU0输出3: CLU1输出4: CLU2输出5: CLU3输出6: 比较器0的输出7: 比较器1的输出8: 比较器2的输出9: Timer通道0和1的异或
#define TIMER1_CFG_CH0_POL_BIT       BIT3                                                        // [3] Timer通道0在比较模式下的输出极性控制:当计数器CNT\<CMP0时的输出值。
#define TIMER1_CFG_CH0_MODE_BIT      BIT2                                                        // [2] Timer通道0的工作模式选择，默认值为0。0: 比较模式。输出方波，在Timer通道0计数器计数值等于0或等于Timer比较捕获寄存器值时，IO发生翻转。1: 捕获模式。当Timer通道0输入信号发生捕获事件时，将计数器计数值存入Timer通道0比较捕获寄存器。
#define TIMER1_CFG_CH0_FE_CAP_EN_BIT BIT1                                                        // [1] Timer通道0下降沿捕获事件使能。1:使能；0:关闭。Timer通道0输入信号发生1?0跳变被视为捕获事件。下降沿事件使能可以与上升沿事件使能并存。
#define TIMER1_CFG_CH0_RE_CAP_EN_BIT BIT0                                                        // [0] Timer通道0上升沿捕获事件使能。1:使能；0:关闭。Timer通道0输入信号发生0?1跳变被视为捕获事件。上升沿事件使能可以与下降沿事件使能并存。

/* TIMER1_TH Timer1 门限寄存器 */
#define TIMER1_TH_TH_MAX  ((uint32_t)0xFFFF)                                       // TIMER1_TH_TH最大值
#define TIMER1_TH_TH_POS  0                                                        // TIMER1_TH_TH起始位
#define TIMER1_TH_TH_MASK (uint32_t)((uint32_t)0xFFFF << TIMER1_TH_TH_POS)         // TIMER1_TH_TH位掩码
#define TIMER1_TH_TH(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << TIMER1_TH_TH_POS) // [15:0] Timer 计数器计数门限。向上计数从0计数到TH值后回0，或向下计数从TH计数到0后回到TH

/* TIMER1_CNT Timer1 计数寄存器 */
#define TIMER1_CNT_CNT_MAX  ((uint32_t)0xFFFF)                                         // TIMER1_CNT_CNT最大值
#define TIMER1_CNT_CNT_POS  0                                                          // TIMER1_CNT_CNT起始位
#define TIMER1_CNT_CNT_MASK (uint32_t)((uint32_t)0xFFFF << TIMER1_CNT_CNT_POS)         // TIMER1_CNT_CNT位掩码
#define TIMER1_CNT_CNT(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << TIMER1_CNT_CNT_POS) // [15:0] Timer 0计数器当前计数值。写操作可以写入新的计数值。

/* TIMER1_CMP0 Timer1 通道0比较捕获寄存器 */
#define TIMER1_CMP0_CMP0_MAX  ((uint32_t)0xFFFF)                                           // TIMER1_CMP0_CMP0最大值
#define TIMER1_CMP0_CMP0_POS  0                                                            // TIMER1_CMP0_CMP0起始位
#define TIMER1_CMP0_CMP0_MASK (uint32_t)((uint32_t)0xFFFF << TIMER1_CMP0_CMP0_POS)         // TIMER1_CMP0_CMP0位掩码
#define TIMER1_CMP0_CMP0(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << TIMER1_CMP0_CMP0_POS) // [15:0] Timer 通道0工作在比较模式时，当计数器计数值等于CMP0时，发生比较事件。Timer 通道0工作在捕获模式时，发生捕获事件时的计数器计数值存入CMP0寄存器。

/* TIMER1_CMP1 Timer1 通道1比较捕获寄存器 */
#define TIMER1_CMP1_CMP1_MAX  ((uint32_t)0xFFFF)                                           // TIMER1_CMP1_CMP1最大值
#define TIMER1_CMP1_CMP1_POS  0                                                            // TIMER1_CMP1_CMP1起始位
#define TIMER1_CMP1_CMP1_MASK (uint32_t)((uint32_t)0xFFFF << TIMER1_CMP1_CMP1_POS)         // TIMER1_CMP1_CMP1位掩码
#define TIMER1_CMP1_CMP1(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << TIMER1_CMP1_CMP1_POS) // [15:0] Timer 通道1工作在比较模式时，当计数器计数值等于CMP1时，发生比较事件。Timer 通道1工作在捕获模式时，发生捕获事件时的计数器计数值存入CMP1寄存器。

/* TIMER1_EVT Timer1 外部事件选择寄存器 */
#define TIMER1_EVT_EVT_SRC_MAX  ((uint32_t)0xF)                                             // TIMER1_EVT_EVT_SRC最大值
#define TIMER1_EVT_EVT_SRC_POS  0                                                           // TIMER1_EVT_EVT_SRC起始位
#define TIMER1_EVT_EVT_SRC_MASK (uint32_t)((uint32_t)0xF << TIMER1_EVT_EVT_SRC_POS)         // TIMER1_EVT_EVT_SRC位掩码
#define TIMER1_EVT_EVT_SRC(x)   (uint32_t)((uint32_t)((x) & 0xF) << TIMER1_EVT_EVT_SRC_POS) // [3:0] Timer外部事件选择寄存器，本寄存器需要配合TIMER1_CFG.ETON，TIMER1_CFG.GATE_EN，TIMER1_CFG.RL_EN，TIMER1_CFG.XCLK_EN使用。通常4个设置位不同时使用。当设置ETON=1时，根据本寄存器选择触发Timer计数的事件。需要注意的是，Timer自身的比较事件无法触发Timer进行计数。当ETON=1时，触发信号的上升沿触发Timer开始计数，用作触发源的Timer需要工作在比较模式，无须从外部输入信号至Timer通道0:TIMER0 通道0比较/捕获事件1:TIMER0 通道1比较/捕获事件2:不可用3:不可用4:TIMER2 通道0比较/捕获事件5:TIMER2 通道1比较/捕获事件6:TIMER3 通道0比较/捕获事件7:TIMER3 通道1比较/捕获事件8:CLU0输出上升沿9:CLU1输出上升沿10:CLU2输出上升沿11:CLU3输出上升沿12:MCPWM TADC[0]比较事件13:MCPWM TADC[1]比较事件14:MCPWM TADC[2]比较事件15:MCPWM TADC[3]比较事件当GATE_EN=1，且外部信号为高时Timer计数，外部信号为低时，Timer暂停，当GATE_EN=1时，Timer使用对应外部信号的电平信号作为计数门控。GATE_EN仅支持配合0~11的外部事件使用，当EVT_SRC选择为0~7时，外部信号为Timer通道输入信号经过对应Timer滤波后的信号，作为门控信号的Timer通道需要配置为输入使能0:TIMER0 通道0滤波后输入信号1:TIMER0 通道1滤波后输入信号2:TIMER1 通道0滤波后输入信号3:TIMER1 通道1滤波后输入信号4:TIMER2 通道0滤波后输入信号5:TIMER2 通道1滤波后输入信号6:TIMER3 通道0滤波后输入信号7:TIMER3 通道1滤波后输入信号8:CLU0输出信号9:CLU1输出信号10:CLU2输出信号11:CLU3输出信号当RL_EN为高时，Timer使用外部信号作为重装载信号作为重装载信号的Timer通道需要配置为输入使能0:TIMER0 通道0比较/捕获事件1:TIMER0 通道1比较/捕获事件2:TIMER1 通道0比较/捕获事件3:TIMER1 通道1比较/捕获事件4:TIMER2 通道0比较/捕获事件5:TIMER2 通道1比较/捕获事件6:TIMER3 通道0比较/捕获事件7:TIMER3 通道1比较/捕获事件8:CLU0输出9:CLU1输出10:CLU2输出11:CLU3输出12:MCPWM TADC[0]比较事件13:MCPWM TADC[1]比较事件14:MCPWM TADC[2]比较事件15:MCPWM TADC[3]比较事件当XCLK_EN为高时，Timer使用外部信号作为Timer外部时钟，Timer在时钟上升沿进行计数动作。如果使用Timer通道作为外部时钟，通道信号受到对应Timer滤波设置影响。0:TIMER0 通道0输入信号1:TIMER0 通道1输入信号2:TIMER1 通道0输入信号3:TIMER1 通道1输入信号4:TIMER2 通道0输入信号5:TIMER2 通道1输入信号6:TIMER3 通道0输入信号7:TIMER3 通道1输入信号8:CLU0输出9:CLU1输出10:CLU2输出11:CLU3输出12:MCPWM TADC[0]比较事件13:MCPWM TADC[1]比较事件14:MCPWM TADC[2]比较事件15:MCPWM TADC[3]比较事件

/* TIMER1_FLT Timer1 滤波控制寄存器 */
#define TIMER1_FLT_FLT_MAX  ((uint32_t)0xFF)                                         // TIMER1_FLT_FLT最大值
#define TIMER1_FLT_FLT_POS  0                                                        // TIMER1_FLT_FLT起始位
#define TIMER1_FLT_FLT_MASK (uint32_t)((uint32_t)0xFF << TIMER1_FLT_FLT_POS)         // TIMER1_FLT_FLT位掩码
#define TIMER1_FLT_FLT(x)   (uint32_t)((uint32_t)((x) & 0xFF) << TIMER1_FLT_FLT_POS) // [7:0] 通道0/1信号滤波宽度选择。取值范围0~255。FLT为0时，不对通道进行滤波。FLT不为0时，对通道信号进行滤波:滤波宽度为FLT×8。当通道信号电平稳定超过FLT×8个系统时钟周期宽度时，滤波器输出更新；否则，滤波器保持当前的输出不变。

/* TIMER1_IE Timer1 中断使能寄存器 */
#define TIMER1_IE_ZC_RE_BIT  BIT10 // [10] Timer计数器过0 DMA请求使能，高电平有效。
#define TIMER1_IE_CH1_RE_BIT BIT9  // [9] Timer通道1比较/捕获 DMA请求使能，高电平有效。
#define TIMER1_IE_CH0_RE_BIT BIT8  // [8] Timer通道0比较/捕获 DMA请求使能，高电平有效。
#define TIMER1_IE_ZC_IE_BIT  BIT2  // [2] Timer计数器过0中断使能，高电平有效。
#define TIMER1_IE_CH1_IE_BIT BIT1  // [1] Timer通道1比较/捕获中断使能，高电平有效。
#define TIMER1_IE_CH0_IE_BIT BIT0  // [0] Timer通道0比较/捕获中断使能，高电平有效。

/* TIMER1_IF Timer1 中断标志寄存器 */
#define TIMER1_IF_ZC_IF_BIT  BIT2 // [2] Timer计数器过0中断标志。高电平有效，写1清0
#define TIMER1_IF_CH1_IF_BIT BIT1 // [1] Timer通道1比较/捕获中断标志。高电平有效，写1清0
#define TIMER1_IF_CH0_IF_BIT BIT0 // [0] Timer通道0比较/捕获中断标志。高电平有效，写1清0

/* TIMER2_CFG Timer2 配置寄存器 */
#define TIMER2_CFG_EN_BIT            BIT31                                                       // [31] Timer模块整体使能，高有效
#define TIMER2_CFG_CAP1_CLR_EN_BIT   BIT29                                                       // [29] 当发生CAP1捕获事件时，清零Timer计数器，高有效
#define TIMER2_CFG_CAP0_CLR_EN_BIT   BIT28                                                       // [28] 当发生CAP0捕获事件时，清零Timer计数器，高有效
#define TIMER2_CFG_ONE_TRIG_BIT      BIT25                                                       // [25] 单次发送模式，此位需要在Timer比较模式下使用，且EN需设置为0ETON为0时，软件向ONE_TRIG写1触发Timer发送一个周期的特定占空比的脉冲，Timer计数一个周期后停止。此位在Timer计数的当前周期内读为1，Timer停止后，自动清零。ETON为1时，即使软件配置ONE_TRIG=1，也需要等待外部事件触发，Timer计数一个周期后停止。ONE_TRIG位在外部触发Timer计数一个周期停止后被硬件清零。
#define TIMER2_CFG_CENTER_BIT        BIT24                                                       // [24] 中心计数模式使能0: Timer向上从0计数至TH，然后回0，或Timer向下从TH计数至0，然后回到TH1: Timer向上从0计数至TH，然后向下计数至0
#define TIMER2_CFG_DIR_BIT           BIT23                                                       // [23] 0: 0-\>TH递增计数，1：TH-\>递减计数此位在CENTER=1时只读，用于指示当前计数方向
#define TIMER2_CFG_CLK_DIV_MAX       ((uint32_t)0x7)                                             // TIMER2_CFG_CLK_DIV最大值
#define TIMER2_CFG_CLK_DIV_POS       20                                                          // TIMER2_CFG_CLK_DIV起始位
#define TIMER2_CFG_CLK_DIV_MASK      (uint32_t)((uint32_t)0x7 << TIMER2_CFG_CLK_DIV_POS)         // TIMER2_CFG_CLK_DIV位掩码
#define TIMER2_CFG_CLK_DIV(x)        (uint32_t)((uint32_t)((x) & 0x7) << TIMER2_CFG_CLK_DIV_POS) // [22:20] Timer计数器频率配置，计数器计数频率是系统主时钟频率的2CLK_DIV分频。默认值为0，不分频。0: 1分频1: 2分频2: 4分频3: 8分频4: 16分频5: 32分频6: 64分频7: 128分频
#define TIMER2_CFG_ETON_BIT          BIT19                                                       // [19] Timer计数器外部启动使能0: 自动运行1: 等待外部事件触发计数，外部触发信号根据TIMER2_EVT.EVT_SRC进行选择需要注意的是，使用外部触发也需要设置TIMER2_CFG.EN=1，除非是外部信号进行的单次触发，即TIMER2_CFG.ONE_TRIG=1。
#define TIMER2_CFG_GATE_EN_BIT       BIT18                                                       // [18] Timer暂停使能0：不暂停1：当外部信号为低时，Timer暂停计数，外部信号根据TIMER2_EVT.EVT_SRC进行选择
#define TIMER2_CFG_RL_EN_BIT         BIT17                                                       // [17] Timer重装使能0：禁用外部事件重装，Timer向上计数至TH回0，或向下计数值0回到TH1：使能外部事件重装，重装信号根据TIMER2_EVT.EVT_SRC进行选择，当向上计数时，发生外部事件，Timer重装为0,；当向下计数时，发生外部事件，Timer重装为TH。
#define TIMER2_CFG_XCLK_EN_BIT       BIT16                                                       // [16] Timer 时钟源0: 芯片内部时钟1: 外部时钟，时钟源根据TIMER2_EVT.EVT_SRC进行选择，当使用外部时钟时，CLK_DIV不再起作用，即时钟不再进行分频
#define TIMER2_CFG_SRC1_MAX          ((uint32_t)0xF)                                             // TIMER2_CFG_SRC1最大值
#define TIMER2_CFG_SRC1_POS          12                                                          // TIMER2_CFG_SRC1起始位
#define TIMER2_CFG_SRC1_MASK         (uint32_t)((uint32_t)0xF << TIMER2_CFG_SRC1_POS)            // TIMER2_CFG_SRC1位掩码
#define TIMER2_CFG_SRC1(x)           (uint32_t)((uint32_t)((x) & 0xF) << TIMER2_CFG_SRC1_POS)    // [15:12] Timer捕获模式通道1信号来源。默认为3’h1。0: Timer通道0，来自芯片GPIO（参见Datasheet及应用配置）1: Timer通道1，来自芯片GPIO（参见Datasheet及应用配置）2: CLU0输出3: CLU1输出4: CLU2输出5: CLU3输出6: 比较器0的输出7: 比较器1的输出8: 比较器2的输出9: Timer通道0和1的异或
#define TIMER2_CFG_CH1_POL_BIT       BIT11                                                       // [11] Timer通道1在比较模式下的输出极性控制，当计数器CNT\<CMP1时的输出值。
#define TIMER2_CFG_CH1_MODE_BIT      BIT10                                                       // [10] Timer通道1的工作模式选择，默认值为0。0: 比较模式。输出方波，在Timer通道1计数器计数值等于0或等于Timer比较捕获寄存器值时，IO发生翻转。1: 捕获模式。当Timer通道1输入信号发生捕获事件时，将计数器计数值存入Timer通道1比较捕获寄存器
#define TIMER2_CFG_CH1_FE_CAP_EN_BIT BIT9                                                        // [9] Timer通道1下降沿捕获事件使能。1:使能；0:关闭。Timer通道1输入信号发生1?0跳变被视为捕获事件。下降沿事件使能可以与上升沿事件使能并存。
#define TIMER2_CFG_CH1_RE_CAP_EN_BIT BIT8                                                        // [8] Timer通道1上升沿捕获事件使能。1:使能；0:关闭。Timer通道1输入信号发生0?1跳变被视为捕获事件。上升沿事件使能可以与下降沿事件使能并存。
#define TIMER2_CFG_SRC0_MAX          ((uint32_t)0xF)                                             // TIMER2_CFG_SRC0最大值
#define TIMER2_CFG_SRC0_POS          4                                                           // TIMER2_CFG_SRC0起始位
#define TIMER2_CFG_SRC0_MASK         (uint32_t)((uint32_t)0xF << TIMER2_CFG_SRC0_POS)            // TIMER2_CFG_SRC0位掩码
#define TIMER2_CFG_SRC0(x)           (uint32_t)((uint32_t)((x) & 0xF) << TIMER2_CFG_SRC0_POS)    // [7:4] Timer捕获模式通道0信号来源。默认为3’h0。0: Timer通道0，来自芯片GPIO（参见Datasheet及应用配置）1: Timer通道1，来自芯片GPIO（参见Datasheet及应用配置）2: CLU0输出3: CLU1输出4: CLU2输出5: CLU3输出6: 比较器0的输出7: 比较器1的输出8: 比较器2的输出9: Timer通道0和1的异或
#define TIMER2_CFG_CH0_POL_BIT       BIT3                                                        // [3] Timer通道0在比较模式下的输出极性控制:当计数器CNT\<CMP0时的输出值。
#define TIMER2_CFG_CH0_MODE_BIT      BIT2                                                        // [2] Timer通道0的工作模式选择，默认值为0。0: 比较模式。输出方波，在Timer通道0计数器计数值等于0或等于Timer比较捕获寄存器值时，IO发生翻转。1: 捕获模式。当Timer通道0输入信号发生捕获事件时，将计数器计数值存入Timer通道0比较捕获寄存器。
#define TIMER2_CFG_CH0_FE_CAP_EN_BIT BIT1                                                        // [1] Timer通道0下降沿捕获事件使能。1:使能；0:关闭。Timer通道0输入信号发生1?0跳变被视为捕获事件。下降沿事件使能可以与上升沿事件使能并存。
#define TIMER2_CFG_CH0_RE_CAP_EN_BIT BIT0                                                        // [0] Timer通道0上升沿捕获事件使能。1:使能；0:关闭。Timer通道0输入信号发生0?1跳变被视为捕获事件。上升沿事件使能可以与下降沿事件使能并存。

/* TIMER2_TH Timer2 门限寄存器 */
#define TIMER2_TH_TH_MAX  ((uint32_t)0xFFFFFFFF)                                       // TIMER2_TH_TH最大值
#define TIMER2_TH_TH_POS  0                                                            // TIMER2_TH_TH起始位
#define TIMER2_TH_TH_MASK (uint32_t)((uint32_t)0xFFFFFFFF << TIMER2_TH_TH_POS)         // TIMER2_TH_TH位掩码
#define TIMER2_TH_TH(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << TIMER2_TH_TH_POS) // [31:0] Timer计数器计数门限。向上计数从0计数到TH值后回0，或向下计数从TH计数到0后回到TH

/* TIMER2_CNT Timer2 计数寄存器 */
#define TIMER2_CNT_CNT_MAX  ((uint32_t)0xFFFFFFFF)                                         // TIMER2_CNT_CNT最大值
#define TIMER2_CNT_CNT_POS  0                                                              // TIMER2_CNT_CNT起始位
#define TIMER2_CNT_CNT_MASK (uint32_t)((uint32_t)0xFFFFFFFF << TIMER2_CNT_CNT_POS)         // TIMER2_CNT_CNT位掩码
#define TIMER2_CNT_CNT(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << TIMER2_CNT_CNT_POS) // [31:0] Timer2计数器当前计数值。写操作可以写入新的计数值。

/* TIMER2_CMP0 Timer2 通道0比较捕获寄存器 */
#define TIMER2_CMP0_CMP0_MAX  ((uint32_t)0xFFFFFFFF)                                           // TIMER2_CMP0_CMP0最大值
#define TIMER2_CMP0_CMP0_POS  0                                                                // TIMER2_CMP0_CMP0起始位
#define TIMER2_CMP0_CMP0_MASK (uint32_t)((uint32_t)0xFFFFFFFF << TIMER2_CMP0_CMP0_POS)         // TIMER2_CMP0_CMP0位掩码
#define TIMER2_CMP0_CMP0(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << TIMER2_CMP0_CMP0_POS) // [31:0] Time通道0工作在比较模式时，当计数器计数值等于CMP0时，发生比较事件。Timer通道0工作在捕获模式时，发生捕获事件时的计数器计数值存入CMP0寄存器。

/* TIMER2_CMP1 Timer2 通道1比较捕获寄存器 */
#define TIMER2_CMP1_CMP1_MAX  ((uint32_t)0xFFFFFFFF)                                           // TIMER2_CMP1_CMP1最大值
#define TIMER2_CMP1_CMP1_POS  0                                                                // TIMER2_CMP1_CMP1起始位
#define TIMER2_CMP1_CMP1_MASK (uint32_t)((uint32_t)0xFFFFFFFF << TIMER2_CMP1_CMP1_POS)         // TIMER2_CMP1_CMP1位掩码
#define TIMER2_CMP1_CMP1(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << TIMER2_CMP1_CMP1_POS) // [31:0] Timer通道1工作在比较模式时，当计数器计数值等于CMP1时，发生比较事件。Timer通道1工作在捕获模式时，发生捕获事件时的计数器计数值存入CMP1寄存器。

/* TIMER2_EVT Timer2 外部事件选择寄存器 */
#define TIMER2_EVT_EVT_SRC_MAX  ((uint32_t)0xF)                                             // TIMER2_EVT_EVT_SRC最大值
#define TIMER2_EVT_EVT_SRC_POS  0                                                           // TIMER2_EVT_EVT_SRC起始位
#define TIMER2_EVT_EVT_SRC_MASK (uint32_t)((uint32_t)0xF << TIMER2_EVT_EVT_SRC_POS)         // TIMER2_EVT_EVT_SRC位掩码
#define TIMER2_EVT_EVT_SRC(x)   (uint32_t)((uint32_t)((x) & 0xF) << TIMER2_EVT_EVT_SRC_POS) // [3:0] Timer外部事件选择寄存器，本寄存器需要配合TIMER2_CFG.ETON，TIMER2_CFG.GATE_EN，TIMER2_CFG.RL_EN，TIMER2_CFG.XCLK_EN使用。通常4个设置位不同时使用。当设置ETON=1时，根据本寄存器选择触发Timer计数的事件。需要注意的是，Timer自身的比较事件无法触发Timer进行计数。当ETON=1时，触发信号的上升沿触发Timer开始计数，用作触发源的Timer需要工作在比较模式，无须从外部输入信号至Timer通道0:TIMER0 通道0比较/捕获事件1:TIMER0 通道1比较/捕获事件2:TIMER1 通道0比较/捕获事件3:TIMER1 通道1比较/捕获事件4:不可用5:不可用6:TIMER3 通道0比较/捕获事件7:TIMER3 通道1比较/捕获事件8:CLU0输出上升沿9:CLU1输出上升沿10:CLU2输出上升沿11:CLU3输出上升沿12:MCPWM TADC[0]比较事件13:MCPWM TADC[1]比较事件14:MCPWM TADC[2]比较事件15:MCPWM TADC[3]比较事件当GATE_EN=1，且外部信号为高时Timer计数，外部信号为低时，Timer暂停，当GATE_EN=1时，Timer使用对应外部信号的电平信号作为计数门控。GATE_EN仅支持配合0~11的外部事件使用，当EVT_SRC选择为0~7时，外部信号为Timer通道输入信号经过对应Timer滤波后的信号，作为门控信号的Timer通道需要配置为输入使能0:TIMER0 通道0滤波后输入信号1:TIMER0 通道1滤波后输入信号2:TIMER1 通道0滤波后输入信号3:TIMER1 通道1滤波后输入信号4:TIMER2 通道0滤波后输入信号5:TIMER2 通道1滤波后输入信号6:TIMER3 通道0滤波后输入信号7:TIMER3 通道1滤波后输入信号8:CLU0输出信号9:CLU1输出信号10:CLU2输出信号11:CLU3输出信号当RL_EN为高时，Timer使用外部信号作为重装载信号作为重装载信号的Timer通道需要配置为输入使能0:TIMER0 通道0比较/捕获事件1:TIMER0 通道1比较/捕获事件2:TIMER1 通道0比较/捕获事件3:TIMER1 通道1比较/捕获事件4:TIMER2 通道0比较/捕获事件5:TIMER2 通道1比较/捕获事件6:TIMER3 通道0比较/捕获事件7:TIMER3 通道1比较/捕获事件8:CLU0输出9:CLU1输出10:CLU2输出11:CLU3输出12:MCPWM TADC[0]比较事件13:MCPWM TADC[1]比较事件14:MCPWM TADC[2]比较事件15:MCPWM TADC[3]比较事件当XCLK_EN为高时，Timer使用外部信号作为Timer外部时钟，Timer在时钟上升沿进行计数动作。如果使用Timer通道作为外部时钟，通道信号受到对应Timer滤波设置影响。0:TIMER0 通道0输入信号1:TIMER0 通道1输入信号2:TIMER1 通道0输入信号3:TIMER1 通道1输入信号4:TIMER2 通道0输入信号5:TIMER2 通道1输入信号6:TIMER3 通道0输入信号7:TIMER3 通道1输入信号8:CLU0输出9:CLU1输出10:CLU2输出11:CLU3输出12:MCPWM TADC[0]比较事件13:MCPWM TADC[1]比较事件14:MCPWM TADC[2]比较事件15:MCPWM TADC[3]比较事件

/* TIMER2_FLT Timer2 滤波控制寄存器 */
#define TIMER2_FLT_FLT_MAX  ((uint32_t)0xFF)                                         // TIMER2_FLT_FLT最大值
#define TIMER2_FLT_FLT_POS  0                                                        // TIMER2_FLT_FLT起始位
#define TIMER2_FLT_FLT_MASK (uint32_t)((uint32_t)0xFF << TIMER2_FLT_FLT_POS)         // TIMER2_FLT_FLT位掩码
#define TIMER2_FLT_FLT(x)   (uint32_t)((uint32_t)((x) & 0xFF) << TIMER2_FLT_FLT_POS) // [7:0] 通道0/1信号滤波宽度选择。取值范围0~255。FLT为0时，不对通道进行滤波。FLT不为0时，对通道信号进行滤波:滤波宽度为FLT×8。当通道信号电平稳定超过FLT×8个系统时钟周期宽度时，滤波器输出更新；否则，滤波器保持当前的输出不变。

/* TIMER2_IE Timer2 中断使能寄存器 */
#define TIMER2_IE_ZC_RE_BIT  BIT10 // [10] Timer计数器过0 DMA请求使能，高电平有效。
#define TIMER2_IE_CH1_RE_BIT BIT9  // [9] Timer通道1比较/捕获 DMA请求使能，高电平有效。
#define TIMER2_IE_CH0_RE_BIT BIT8  // [8] Timer通道0比较/捕获 DMA请求使能，高电平有效。
#define TIMER2_IE_ZC_IE_BIT  BIT2  // [2] Timer计数器过0中断使能，高电平有效。
#define TIMER2_IE_CH1_IE_BIT BIT1  // [1] Timer通道1比较/捕获中断使能，高电平有效。
#define TIMER2_IE_CH0_IE_BIT BIT0  // [0] Timer通道0比较/捕获中断使能，高电平有效。

/* TIMER2_IF Timer2 中断标志寄存器 */
#define TIMER2_IF_ZC_IF_BIT  BIT2 // [2] Timer计数器过0中断标志。高电平有效，写1清0
#define TIMER2_IF_CH1_IF_BIT BIT1 // [1] Timer通道1比较/捕获中断标志。高电平有效，写1清0
#define TIMER2_IF_CH0_IF_BIT BIT0 // [0] Timer通道0比较/捕获中断标志。高电平有效，写1清0

/* TIMER3_CFG Timer3 配置寄存器 */
#define TIMER3_CFG_EN_BIT            BIT31                                                       // [31] Timer模块整体使能，高有效
#define TIMER3_CFG_CAP1_CLR_EN_BIT   BIT29                                                       // [29] 当发生CAP1捕获事件时，清零Timer计数器，高有效
#define TIMER3_CFG_CAP0_CLR_EN_BIT   BIT28                                                       // [28] 当发生CAP0捕获事件时，清零Timer计数器，高有效
#define TIMER3_CFG_ONE_TRIG_BIT      BIT25                                                       // [25] 单次发送模式，此位需要在Timer比较模式下使用，且EN需设置为0ETON为0时，软件向ONE_TRIG写1触发Timer发送一个周期的特定占空比的脉冲，Timer计数一个周期后停止。此位在Timer计数的当前周期内读为1，Timer停止后，自动清零。ETON为1时，即使软件配置ONE_TRIG=1，也需要等待外部事件触发，Timer计数一个周期后停止。ONE_TRIG位在外部触发Timer计数一个周期停止后被硬件清零。
#define TIMER3_CFG_CENTER_BIT        BIT24                                                       // [24] 中心计数模式使能0: Timer向上从0计数至TH，然后回0，或Timer向下从TH计数至0，然后回到TH1: Timer向上从0计数至TH，然后向下计数至0
#define TIMER3_CFG_DIR_BIT           BIT23                                                       // [23] 0: 0-\>TH递增计数，1：TH-\>递减计数此位在CENTER=1时只读，用于指示当前计数方向
#define TIMER3_CFG_CLK_DIV_MAX       ((uint32_t)0x7)                                             // TIMER3_CFG_CLK_DIV最大值
#define TIMER3_CFG_CLK_DIV_POS       20                                                          // TIMER3_CFG_CLK_DIV起始位
#define TIMER3_CFG_CLK_DIV_MASK      (uint32_t)((uint32_t)0x7 << TIMER3_CFG_CLK_DIV_POS)         // TIMER3_CFG_CLK_DIV位掩码
#define TIMER3_CFG_CLK_DIV(x)        (uint32_t)((uint32_t)((x) & 0x7) << TIMER3_CFG_CLK_DIV_POS) // [22:20] Timer计数器频率配置，计数器计数频率是系统主时钟频率的2CLK_DIV分频。默认值为0，不分频。0: 1分频1: 2分频2: 4分频3: 8分频4: 16分频5: 32分频6: 64分频7: 128分频
#define TIMER3_CFG_ETON_BIT          BIT19                                                       // [19] Timer计数器外部启动使能0: 自动运行1: 等待外部事件触发计数，外部触发信号根据TIMER3_EVT.EVT_SRC进行选择需要注意的是，使用外部触发也需要设置TIMER3_CFG.EN=1，除非是外部信号进行的单次触发，即TIMER3_CFG.ONE_TRIG=1。
#define TIMER3_CFG_GATE_EN_BIT       BIT18                                                       // [18] Timer暂停使能0：不暂停1：当外部信号为低时，Timer暂停计数，外部信号根据TIMER3_EVT.EVT_SRC进行选择
#define TIMER3_CFG_RL_EN_BIT         BIT17                                                       // [17] Timer重装使能0：禁用外部事件重装，Timer向上计数至TH回0，或向下计数值0回到TH1：使能外部事件重装，重装信号根据TIMER3_EVT.EVT_SRC进行选择，当向上计数时，发生外部事件，Timer重装为0,；当向下计数时，发生外部事件，Timer重装为TH。
#define TIMER3_CFG_XCLK_EN_BIT       BIT16                                                       // [16] Timer 时钟源0: 芯片内部时钟1: 外部时钟，时钟源根据TIMER3_EVT.EVT_SRC进行选择，当使用外部时钟时，CLK_DIV不再起作用，即时钟不再进行分频
#define TIMER3_CFG_SRC1_MAX          ((uint32_t)0xF)                                             // TIMER3_CFG_SRC1最大值
#define TIMER3_CFG_SRC1_POS          12                                                          // TIMER3_CFG_SRC1起始位
#define TIMER3_CFG_SRC1_MASK         (uint32_t)((uint32_t)0xF << TIMER3_CFG_SRC1_POS)            // TIMER3_CFG_SRC1位掩码
#define TIMER3_CFG_SRC1(x)           (uint32_t)((uint32_t)((x) & 0xF) << TIMER3_CFG_SRC1_POS)    // [15:12] Timer捕获模式通道1信号来源。默认为3’h1。0: Timer通道0，来自芯片GPIO（参见Datasheet及应用配置）1: Timer通道1，来自芯片GPIO（参见Datasheet及应用配置）2: CLU0输出3: CLU1输出4: CLU2输出5: CLU3输出6: 比较器0的输出7: 比较器1的输出8: 比较器2的输出9: Timer通道0和1的异或
#define TIMER3_CFG_CH1_POL_BIT       BIT11                                                       // [11] Timer通道1在比较模式下的输出极性控制，当计数器CNT\<CMP1时的输出值。
#define TIMER3_CFG_CH1_MODE_BIT      BIT10                                                       // [10] Timer通道1的工作模式选择，默认值为0。0: 比较模式。输出方波，在Timer通道1计数器计数值等于0或等于Timer比较捕获寄存器值时，IO发生翻转。1: 捕获模式。当Timer通道1输入信号发生捕获事件时，将计数器计数值存入Timer通道1比较捕获寄存器
#define TIMER3_CFG_CH1_FE_CAP_EN_BIT BIT9                                                        // [9] Timer通道1下降沿捕获事件使能。1:使能；0:关闭。Timer通道1输入信号发生1?0跳变被视为捕获事件。下降沿事件使能可以与上升沿事件使能并存。
#define TIMER3_CFG_CH1_RE_CAP_EN_BIT BIT8                                                        // [8] Timer通道1上升沿捕获事件使能。1:使能；0:关闭。Timer通道1输入信号发生0?1跳变被视为捕获事件。上升沿事件使能可以与下降沿事件使能并存。
#define TIMER3_CFG_SRC0_MAX          ((uint32_t)0xF)                                             // TIMER3_CFG_SRC0最大值
#define TIMER3_CFG_SRC0_POS          4                                                           // TIMER3_CFG_SRC0起始位
#define TIMER3_CFG_SRC0_MASK         (uint32_t)((uint32_t)0xF << TIMER3_CFG_SRC0_POS)            // TIMER3_CFG_SRC0位掩码
#define TIMER3_CFG_SRC0(x)           (uint32_t)((uint32_t)((x) & 0xF) << TIMER3_CFG_SRC0_POS)    // [7:4] Timer捕获模式通道0信号来源。默认为3’h0。0: Timer通道0，来自芯片GPIO（参见Datasheet及应用配置）1: Timer通道1，来自芯片GPIO（参见Datasheet及应用配置）2: CLU0输出3: CLU1输出4: CLU2输出5: CLU3输出6: 比较器0的输出7: 比较器1的输出8: 比较器2的输出9: Timer通道0和1的异或
#define TIMER3_CFG_CH0_POL_BIT       BIT3                                                        // [3] Timer通道0在比较模式下的输出极性控制:当计数器CNT\<CMP0时的输出值。
#define TIMER3_CFG_CH0_MODE_BIT      BIT2                                                        // [2] Timer通道0的工作模式选择，默认值为0。0: 比较模式。输出方波，在Timer通道0计数器计数值等于0或等于Timer比较捕获寄存器值时，IO发生翻转。1: 捕获模式。当Timer通道0输入信号发生捕获事件时，将计数器计数值存入Timer通道0比较捕获寄存器。
#define TIMER3_CFG_CH0_FE_CAP_EN_BIT BIT1                                                        // [1] Timer通道0下降沿捕获事件使能。1:使能；0:关闭。Timer通道0输入信号发生1?0跳变被视为捕获事件。下降沿事件使能可以与上升沿事件使能并存。
#define TIMER3_CFG_CH0_RE_CAP_EN_BIT BIT0                                                        // [0] Timer通道0上升沿捕获事件使能。1:使能；0:关闭。Timer通道0输入信号发生0?1跳变被视为捕获事件。上升沿事件使能可以与下降沿事件使能并存。

/* TIMER3_TH Timer3 门限寄存器 */
#define TIMER3_TH_TH_MAX  ((uint32_t)0xFFFFFFFF)                                       // TIMER3_TH_TH最大值
#define TIMER3_TH_TH_POS  0                                                            // TIMER3_TH_TH起始位
#define TIMER3_TH_TH_MASK (uint32_t)((uint32_t)0xFFFFFFFF << TIMER3_TH_TH_POS)         // TIMER3_TH_TH位掩码
#define TIMER3_TH_TH(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << TIMER3_TH_TH_POS) // [31:0] Timer计数器计数门限。向上计数从0计数到TH值后回0，或向下计数从TH计数到0后回到TH

/* TIMER3_CNT Timer3 计数寄存器 */
#define TIMER3_CNT_CNT_MAX  ((uint32_t)0xFFFFFFFF)                                         // TIMER3_CNT_CNT最大值
#define TIMER3_CNT_CNT_POS  0                                                              // TIMER3_CNT_CNT起始位
#define TIMER3_CNT_CNT_MASK (uint32_t)((uint32_t)0xFFFFFFFF << TIMER3_CNT_CNT_POS)         // TIMER3_CNT_CNT位掩码
#define TIMER3_CNT_CNT(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << TIMER3_CNT_CNT_POS) // [31:0] Timer3计数器当前计数值。写操作可以写入新的计数值。

/* TIMER3_CMP0 Timer3 通道0比较捕获寄存器 */
#define TIMER3_CMP0_CMP0_MAX  ((uint32_t)0xFFFFFFFF)                                           // TIMER3_CMP0_CMP0最大值
#define TIMER3_CMP0_CMP0_POS  0                                                                // TIMER3_CMP0_CMP0起始位
#define TIMER3_CMP0_CMP0_MASK (uint32_t)((uint32_t)0xFFFFFFFF << TIMER3_CMP0_CMP0_POS)         // TIMER3_CMP0_CMP0位掩码
#define TIMER3_CMP0_CMP0(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << TIMER3_CMP0_CMP0_POS) // [31:0] Time通道0工作在比较模式时，当计数器计数值等于CMP0时，发生比较事件。Timer通道0工作在捕获模式时，发生捕获事件时的计数器计数值存入CMP0寄存器。

/* TIMER3_CMP1 Timer3 通道1比较捕获寄存器 */
#define TIMER3_CMP1_CMP1_MAX  ((uint32_t)0xFFFFFFFF)                                           // TIMER3_CMP1_CMP1最大值
#define TIMER3_CMP1_CMP1_POS  0                                                                // TIMER3_CMP1_CMP1起始位
#define TIMER3_CMP1_CMP1_MASK (uint32_t)((uint32_t)0xFFFFFFFF << TIMER3_CMP1_CMP1_POS)         // TIMER3_CMP1_CMP1位掩码
#define TIMER3_CMP1_CMP1(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << TIMER3_CMP1_CMP1_POS) // [31:0] Timer通道1工作在比较模式时，当计数器计数值等于CMP1时，发生比较事件。Timer通道1工作在捕获模式时，发生捕获事件时的计数器计数值存入CMP1寄存器。

/* TIMER3_EVT Timer3 外部事件选择寄存器 */
#define TIMER3_EVT_EVT_SRC_MAX  ((uint32_t)0xF)                                             // TIMER3_EVT_EVT_SRC最大值
#define TIMER3_EVT_EVT_SRC_POS  0                                                           // TIMER3_EVT_EVT_SRC起始位
#define TIMER3_EVT_EVT_SRC_MASK (uint32_t)((uint32_t)0xF << TIMER3_EVT_EVT_SRC_POS)         // TIMER3_EVT_EVT_SRC位掩码
#define TIMER3_EVT_EVT_SRC(x)   (uint32_t)((uint32_t)((x) & 0xF) << TIMER3_EVT_EVT_SRC_POS) // [3:0] Timer外部事件选择寄存器，本寄存器需要配合TIMER3_CFG.ETON，TIMER3_CFG.GATE_EN，TIMER3_CFG.RL_EN，TIMER3_CFG.XCLK_EN使用。通常4个设置位不同时使用。当设置ETON=1时，根据本寄存器选择触发Timer计数的事件。需要注意的是，Timer自身的比较事件无法触发Timer进行计数。当ETON=1时，触发信号的上升沿触发Timer开始计数，用作触发源的Timer需要工作在比较模式，无须从外部输入信号至Timer通道0:TIMER0 通道0比较/捕获事件1:TIMER0 通道1比较/捕获事件2:TIMER1 通道0比较/捕获事件3:TIMER1 通道1比较/捕获事件4:TIMER2 通道0比较/捕获事件5:TIMER2 通道1比较/捕获事件6:不可用7:不可用8:CLU0输出上升沿9:CLU1输出上升沿10:CLU2输出上升沿11:CLU3输出上升沿12:MCPWM TADC[0]比较事件13:MCPWM TADC[1]比较事件14:MCPWM TADC[2]比较事件15:MCPWM TADC[3]比较事件当GATE_EN=1，且外部信号为高时Timer计数，外部信号为低时，Timer暂停，当GATE_EN=1时，Timer使用对应外部信号的电平信号作为计数门控。GATE_EN仅支持配合0~11的外部事件使用，当EVT_SRC选择为0~7时，外部信号为Timer通道输入信号经过对应Timer滤波后的信号，作为门控信号的Timer通道需要配置为输入使能。0:TIMER0 通道0滤波后输入信号1:TIMER0 通道1滤波后输入信号2:TIMER1 通道0滤波后输入信号3:TIMER1 通道1滤波后输入信号4:TIMER2 通道0滤波后输入信号5:TIMER2 通道1滤波后输入信号6:TIMER3 通道0滤波后输入信号7:TIMER3 通道1滤波后输入信号8:CLU0输出信号9:CLU1输出信号10:CLU2输出信号11:CLU3输出信号当RL_EN为高时，Timer使用外部信号作为重装载信号作为重装载信号的Timer通道需要配置为输入使能0:TIMER0 通道0比较/捕获事件1:TIMER0 通道1比较/捕获事件2:TIMER1 通道0比较/捕获事件3:TIMER1 通道1比较/捕获事件4:TIMER2 通道0比较/捕获事件5:TIMER2 通道1比较/捕获事件6:TIMER3 通道0比较/捕获事件7:TIMER3 通道1比较/捕获事件8:CLU0输出9:CLU1输出10:CLU2输出11:CLU3输出12:MCPWM TADC[0]比较事件13:MCPWM TADC[1]比较事件14:MCPWM TADC[2]比较事件15:MCPWM TADC[3]比较事件当XCLK_EN为高时，Timer使用外部信号作为Timer外部时钟，Timer在时钟上升沿进行计数动作。如果使用Timer通道作为外部时钟，通道信号受到对应Timer滤波设置影响。0:TIMER0 通道0输入信号1:TIMER0 通道1输入信号2:TIMER1 通道0输入信号3:TIMER1 通道1输入信号4:TIMER2 通道0输入信号5:TIMER2 通道1输入信号6:TIMER3 通道0输入信号7:TIMER3 通道1输入信号8:CLU0输出9:CLU1输出10:CLU2输出11:CLU3输出12:MCPWM TADC[0]比较事件13:MCPWM TADC[1]比较事件14:MCPWM TADC[2]比较事件15:MCPWM TADC[3]比较事件

/* TIMER3_FLT Timer3 滤波控制寄存器 */
#define TIMER3_FLT_FLT_MAX  ((uint32_t)0xFF)                                         // TIMER3_FLT_FLT最大值
#define TIMER3_FLT_FLT_POS  0                                                        // TIMER3_FLT_FLT起始位
#define TIMER3_FLT_FLT_MASK (uint32_t)((uint32_t)0xFF << TIMER3_FLT_FLT_POS)         // TIMER3_FLT_FLT位掩码
#define TIMER3_FLT_FLT(x)   (uint32_t)((uint32_t)((x) & 0xFF) << TIMER3_FLT_FLT_POS) // [7:0] 通道0/1信号滤波宽度选择。取值范围0~255。FLT为0时，不对通道进行滤波。FLT不为0时，对通道信号进行滤波:滤波宽度为FLT×8。当通道信号电平稳定超过FLT×8个系统时钟周期宽度时，滤波器输出更新；否则，滤波器保持当前的输出不变。

/* TIMER3_IE Timer3 中断使能寄存器 */
#define TIMER3_IE_ZC_RE_BIT  BIT10 // [10] Timer计数器过0 DMA请求使能，高电平有效。
#define TIMER3_IE_CH1_RE_BIT BIT9  // [9] Timer通道1比较/捕获 DMA请求使能，高电平有效。
#define TIMER3_IE_CH0_RE_BIT BIT8  // [8] Timer通道0比较/捕获 DMA请求使能，高电平有效。
#define TIMER3_IE_ZC_IE_BIT  BIT2  // [2] Timer计数器过0中断使能，高电平有效。
#define TIMER3_IE_CH1_IE_BIT BIT1  // [1] Timer通道1比较/捕获中断使能，高电平有效。
#define TIMER3_IE_CH0_IE_BIT BIT0  // [0] Timer通道0比较/捕获中断使能，高电平有效。

/* TIMER3_IF Timer3 中断标志寄存器 */
#define TIMER3_IF_ZC_IF_BIT  BIT2 // [2] Timer计数器过0中断标志。高电平有效，写1清0
#define TIMER3_IF_CH1_IF_BIT BIT1 // [1] Timer通道1比较/捕获中断标志。高电平有效，写1清0
#define TIMER3_IF_CH0_IF_BIT BIT0 // [0] Timer通道0比较/捕获中断标志。高电平有效，写1清0

/* QEP0_CFG QEP0 配置寄存器 */
#define QEP0_CFG_EN_BIT        BIT15                                                  // [15] QEP模块整体使能
#define QEP0_CFG_FE_CNT_EN_BIT BIT10                                                  // [10] CCW+SIGN/CCW+CW两种模式下，是否在下降沿进行计数（上升沿总是计数）
#define QEP0_CFG_MODE_MAX      ((uint32_t)0x3)                                        // QEP0_CFG_MODE最大值
#define QEP0_CFG_MODE_POS      8                                                      // QEP0_CFG_MODE起始位
#define QEP0_CFG_MODE_MASK     (uint32_t)((uint32_t)0x3 << QEP0_CFG_MODE_POS)         // QEP0_CFG_MODE位掩码
#define QEP0_CFG_MODE(x)       (uint32_t)((uint32_t)((x) & 0x3) << QEP0_CFG_MODE_POS) // [9:8] 编码器模式选择00：counting on T1，01：counting on T1 & T2以上两种模式都为正交编码信号计数模式10：CCW+SIGN，符号加脉冲信号计数模式11：CCW+CW，CCW+CW双脉冲信号计数模式
#define QEP0_CFG_ZNC_BIT       BIT3                                                   // [3] Z信号清零极性选择：低电平/下降沿清零使能
#define QEP0_CFG_ZPC_BIT       BIT2                                                   // [2] Z信号清零极性选择：高电平/上升沿清零使能
#define QEP0_CFG_ZLC_BIT       BIT1                                                   // [1] Z信号电平清零QEP计数器使能
#define QEP0_CFG_ZEC_BIT       BIT0                                                   // [0] Z信号边沿清零QEP计数器使能

/* QEP0_TH QEP0 计数门限寄存器 */
#define QEP0_TH_TH_MAX  ((uint32_t)0xFFFF)                                     // QEP0_TH_TH最大值
#define QEP0_TH_TH_POS  0                                                      // QEP0_TH_TH起始位
#define QEP0_TH_TH_MASK (uint32_t)((uint32_t)0xFFFF << QEP0_TH_TH_POS)         // QEP0_TH_TH位掩码
#define QEP0_TH_TH(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << QEP0_TH_TH_POS) // [15:0] 计数门限TH。编码器向上计数（增）到TH值后，再次向上计数会导致计数器回到0。编码器向下计数（减）到0值后，再次向下计数会导致计数器回到TH。

/* QEP0_CNT QEP0 计数值寄存器 */
#define QEP0_CNT_CNT_MAX  ((uint32_t)0xFFFF)                                       // QEP0_CNT_CNT最大值
#define QEP0_CNT_CNT_POS  0                                                        // QEP0_CNT_CNT起始位
#define QEP0_CNT_CNT_MASK (uint32_t)((uint32_t)0xFFFF << QEP0_CNT_CNT_POS)         // QEP0_CNT_CNT位掩码
#define QEP0_CNT_CNT(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << QEP0_CNT_CNT_POS) // [15:0] QEP0计数值。

/* QEP0_IE QEP0 中断使能寄存器 */
#define QEP0_IE_OF_IE_BIT BIT1 // [1] 上溢出中断使能，高电平有效。
#define QEP0_IE_UF_IE_BIT BIT0 // [0] 下溢出中断使能，高电平有效。

/* QEP0_IF QEP0 中断标志寄存器 */
#define QEP0_IF_OF_IF_BIT BIT1 // [1] 上溢出中断标志。高电平有效，写1清0。当计数器计数达到计数门限时，上计数事件触发上溢出中断。
#define QEP0_IF_UF_IF_BIT BIT0 // [0] 下溢出中断标志。高电平有效，写1清0。当计数器计数达到0时，下计数事件触发下溢出中断。

/* QEP1_CFG QEP1 配置寄存器 */
#define QEP1_CFG_FE_CNT_EN_BIT BIT10                                                  // [10] CCW+SIGN/CCW+CW两种模式下，是否在下降沿进行计数（上升沿总是计数）
#define QEP1_CFG_MODE_MAX      ((uint32_t)0x3)                                        // QEP1_CFG_MODE最大值
#define QEP1_CFG_MODE_POS      8                                                      // QEP1_CFG_MODE起始位
#define QEP1_CFG_MODE_MASK     (uint32_t)((uint32_t)0x3 << QEP1_CFG_MODE_POS)         // QEP1_CFG_MODE位掩码
#define QEP1_CFG_MODE(x)       (uint32_t)((uint32_t)((x) & 0x3) << QEP1_CFG_MODE_POS) // [9:8] 编码器模式选择00：counting on T1，01：counting on T1 & T2以上两种模式都为正交编码信号计数模式10：CCW+SIGN，符号加脉冲信号计数模式11：CCW+CW，CCW+CW双脉冲信号计数模式
#define QEP1_CFG_ZNC_BIT       BIT3                                                   // [3] Z信号清零极性选择：低电平/下降沿清零使能
#define QEP1_CFG_ZPC_BIT       BIT2                                                   // [2] Z信号清零极性选择：高电平/上升沿清零使能
#define QEP1_CFG_ZLC_BIT       BIT1                                                   // [1] Z信号电平清零QEP计数器使能
#define QEP1_CFG_ZEC_BIT       BIT0                                                   // [0] Z信号边沿清零QEP计数器使能

/* QEP1_TH QEP1 计数门限寄存器 */
#define QEP1_TH_TH_MAX  ((uint32_t)0xFFFF)                                     // QEP1_TH_TH最大值
#define QEP1_TH_TH_POS  0                                                      // QEP1_TH_TH起始位
#define QEP1_TH_TH_MASK (uint32_t)((uint32_t)0xFFFF << QEP1_TH_TH_POS)         // QEP1_TH_TH位掩码
#define QEP1_TH_TH(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << QEP1_TH_TH_POS) // [15:0] QEP计数门限TH。编码器向上计数（增）到TH值后，再次向上计数会导致计数器回到0。编码器向下计数（减）到0值后，再次向下计数会导致计数器回到TH。

/* QEP1_CNT QEP1 计数值寄存器 */
#define QEP1_CNT_CNT_MAX  ((uint32_t)0xFFFF)                                       // QEP1_CNT_CNT最大值
#define QEP1_CNT_CNT_POS  0                                                        // QEP1_CNT_CNT起始位
#define QEP1_CNT_CNT_MASK (uint32_t)((uint32_t)0xFFFF << QEP1_CNT_CNT_POS)         // QEP1_CNT_CNT位掩码
#define QEP1_CNT_CNT(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << QEP1_CNT_CNT_POS) // [15:0] QEP计数值。

/* QEP1_IE QEP1 中断使能寄存器 */
#define QEP1_IE_OF_IE_BIT BIT1 // [1] 上溢出中断使能，高电平有效。
#define QEP1_IE_UF_IE_BIT BIT0 // [0] 下溢出中断使能，高电平有效。

/* QEP1_IF QEP1 中断标志寄存器 */
#define QEP1_IF_OF_IF_BIT BIT1 // [1] 上溢出中断标志。高电平有效，写1清0。当计数器计数达到计数门限时，上计数事件触发上溢出中断。
#define QEP1_IF_UF_IF_BIT BIT0 // [0] 下溢出中断标志。高电平有效，写1清0。当计数器计数达到0时，下计数事件触发下溢出中断。

/* MCPWM0_TH00 */
#define MCPWM0_TH00_TH00_MAX  ((uint32_t)0xFFFF)                                           // MCPWM0_TH00_TH00最大值
#define MCPWM0_TH00_TH00_POS  0                                                            // MCPWM0_TH00_TH00起始位
#define MCPWM0_TH00_TH00_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_TH00_TH00_POS)         // MCPWM0_TH00_TH00位掩码
#define MCPWM0_TH00_TH00(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_TH00_TH00_POS) // [15:0] MCPWM CH0_P比较门限值，16位有符号数；发生更新事件时，本寄存器加载到MCPWM实际运行系统中。写入的是预装载寄存器，更新事件发生时才会把预装载寄存器值写入影子寄存器，读出时读出的是影子寄存器的值。

/* MCPWM0_TH01 */
#define MCPWM0_TH01_TH01_MAX  ((uint32_t)0xFFFF)                                           // MCPWM0_TH01_TH01最大值
#define MCPWM0_TH01_TH01_POS  0                                                            // MCPWM0_TH01_TH01起始位
#define MCPWM0_TH01_TH01_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_TH01_TH01_POS)         // MCPWM0_TH01_TH01位掩码
#define MCPWM0_TH01_TH01(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_TH01_TH01_POS) // [15:0] MCPWM CH0_N比较门限值，16位有符号数；发生更新事件时，本寄存器加载到MCPWM实际运行系统中。

/* MCPWM0_TH10 */
#define MCPWM0_TH10_TH10_MAX  ((uint32_t)0xFFFF)                                           // MCPWM0_TH10_TH10最大值
#define MCPWM0_TH10_TH10_POS  0                                                            // MCPWM0_TH10_TH10起始位
#define MCPWM0_TH10_TH10_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_TH10_TH10_POS)         // MCPWM0_TH10_TH10位掩码
#define MCPWM0_TH10_TH10(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_TH10_TH10_POS) // 15:0] MCPWM CH1_P比较门限值，16位有符号数；发生更新事件时，本寄存器加载到MCPWM实际运行系统中。

/* MCPWM0_TH11 */
#define MCPWM0_TH11_TH11_MAX  ((uint32_t)0xFFFF)                                           // MCPWM0_TH11_TH11最大值
#define MCPWM0_TH11_TH11_POS  0                                                            // MCPWM0_TH11_TH11起始位
#define MCPWM0_TH11_TH11_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_TH11_TH11_POS)         // MCPWM0_TH11_TH11位掩码
#define MCPWM0_TH11_TH11(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_TH11_TH11_POS) // [15:0] MCPWM CH1_N比较门限值，16位有符号数；发生更新事件时，本寄存器加载到MCPWM实际运行系统中。

/* MCPWM0_TH20 */
#define MCPWM0_TH20_TH20_MAX  ((uint32_t)0xFFFF)                                           // MCPWM0_TH20_TH20最大值
#define MCPWM0_TH20_TH20_POS  0                                                            // MCPWM0_TH20_TH20起始位
#define MCPWM0_TH20_TH20_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_TH20_TH20_POS)         // MCPWM0_TH20_TH20位掩码
#define MCPWM0_TH20_TH20(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_TH20_TH20_POS) // [15:0] MCPWM CH2_P比较门限值，16位有符号数；发生更新事件时，本寄存器加载到MCPWM实际运行系统中。

/* MCPWM0_TH21 */
#define MCPWM0_TH21_TH21_MAX  ((uint32_t)0xFFFF)                                           // MCPWM0_TH21_TH21最大值
#define MCPWM0_TH21_TH21_POS  0                                                            // MCPWM0_TH21_TH21起始位
#define MCPWM0_TH21_TH21_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_TH21_TH21_POS)         // MCPWM0_TH21_TH21位掩码
#define MCPWM0_TH21_TH21(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_TH21_TH21_POS) // [15:0] MCPWM CH2_N比较门限值，16位有符号数；发生更新事件时，本寄存器加载到MCPWM实际运行系统中。

/* MCPWM0_TH30 */
#define MCPWM0_TH30_TH30_MAX  ((uint32_t)0xFFFF)                                           // MCPWM0_TH30_TH30最大值
#define MCPWM0_TH30_TH30_POS  0                                                            // MCPWM0_TH30_TH30起始位
#define MCPWM0_TH30_TH30_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_TH30_TH30_POS)         // MCPWM0_TH30_TH30位掩码
#define MCPWM0_TH30_TH30(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_TH30_TH30_POS) // [15:0] MCPWM CH3_P比较门限值，16位有符号数；发生更新事件时，本寄存器加载到MCPWM实际运行系统中。

/* MCPWM0_TH31 */
#define MCPWM0_TH31_TH31_MAX  ((uint32_t)0xFFFF)                                           // MCPWM0_TH31_TH31最大值
#define MCPWM0_TH31_TH31_POS  0                                                            // MCPWM0_TH31_TH31起始位
#define MCPWM0_TH31_TH31_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_TH31_TH31_POS)         // MCPWM0_TH31_TH31位掩码
#define MCPWM0_TH31_TH31(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_TH31_TH31_POS) // [15:0] MCPWM CH3_N比较门限值，16位有符号数；发生更新事件时，本寄存器加载到MCPWM实际运行系统中。

/* MCPWM0_TH40 */
#define MCPWM0_TH40_TH40_MAX  ((uint32_t)0xFFFF)                                           // MCPWM0_TH40_TH40最大值
#define MCPWM0_TH40_TH40_POS  0                                                            // MCPWM0_TH40_TH40起始位
#define MCPWM0_TH40_TH40_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_TH40_TH40_POS)         // MCPWM0_TH40_TH40位掩码
#define MCPWM0_TH40_TH40(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_TH40_TH40_POS) // [15:0] MCPWM CH4_P比较门限值，16位有符号数；发生更新事件时，本寄存器加载到MCPWM实际运行系统中。

/* MCPWM0_TH41 */
#define MCPWM0_TH41_TH41_MAX  ((uint32_t)0xFFFF)                                           // MCPWM0_TH41_TH41最大值
#define MCPWM0_TH41_TH41_POS  0                                                            // MCPWM0_TH41_TH41起始位
#define MCPWM0_TH41_TH41_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_TH41_TH41_POS)         // MCPWM0_TH41_TH41位掩码
#define MCPWM0_TH41_TH41(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_TH41_TH41_POS) // [15:0] MCPWM CH4_N比较门限值，16位有符号数；发生更新事件时，本寄存器加载到MCPWM实际运行系统中。

/* MCPWM0_TH50 */
#define MCPWM0_TH50_TH50_MAX  ((uint32_t)0xFFFF)                                           // MCPWM0_TH50_TH50最大值
#define MCPWM0_TH50_TH50_POS  0                                                            // MCPWM0_TH50_TH50起始位
#define MCPWM0_TH50_TH50_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_TH50_TH50_POS)         // MCPWM0_TH50_TH50位掩码
#define MCPWM0_TH50_TH50(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_TH50_TH50_POS) // [15:0] MCPWM CH5_P比较门限值，16位有符号数；发生更新事件时，本寄存器加载到MCPWM实际运行系统中。

/* MCPWM0_TH51 */
#define MCPWM0_TH51_TH51_MAX  ((uint32_t)0xFFFF)                                           // MCPWM0_TH51_TH51最大值
#define MCPWM0_TH51_TH51_POS  0                                                            // MCPWM0_TH51_TH51起始位
#define MCPWM0_TH51_TH51_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_TH51_TH51_POS)         // MCPWM0_TH51_TH51位掩码
#define MCPWM0_TH51_TH51(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_TH51_TH51_POS) // [15:0] MCPWM CH5_N比较门限值，16位有符号数；发生更新事件时，本寄存器加载到MCPWM实际运行系统中。

/* MCPWM0_TMR0 */
#define MCPWM0_TMR0_TMR0_MAX  ((uint32_t)0xFFFF)                                           // MCPWM0_TMR0_TMR0最大值
#define MCPWM0_TMR0_TMR0_POS  0                                                            // MCPWM0_TMR0_TMR0起始位
#define MCPWM0_TMR0_TMR0_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_TMR0_TMR0_POS)         // MCPWM0_TMR0_TMR0位掩码
#define MCPWM0_TMR0_TMR0(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_TMR0_TMR0_POS) // [15:0] ADC采样定时器比较门限0寄存器，16位有符号数；当MCPWM0_CNT0=TMR0时产生TADC[0]事件触发ADC进行采样。MCPWM发生更新事件后，本寄存器加载到MCPWM实际运行系统中。

/* MCPWM0_TMR1 */
#define MCPWM0_TMR1_TMR1_MAX  ((uint32_t)0xFFFF)                                           // MCPWM0_TMR1_TMR1最大值
#define MCPWM0_TMR1_TMR1_POS  0                                                            // MCPWM0_TMR1_TMR1起始位
#define MCPWM0_TMR1_TMR1_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_TMR1_TMR1_POS)         // MCPWM0_TMR1_TMR1位掩码
#define MCPWM0_TMR1_TMR1(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_TMR1_TMR1_POS) // [15:0] ADC采样定时器比较门限1寄存器，16位有符号数；当MCPWM0_CNT=TMR1时产生TADC[1]事件触发ADC进行采样。MCPWM发生更新事件后，本寄存器加载到MCPWM实际运行系统中。

/* MCPWM0_TMR2 */
#define MCPWM0_TMR2_TMR2_MAX  ((uint32_t)0xFFFF)                                           // MCPWM0_TMR2_TMR2最大值
#define MCPWM0_TMR2_TMR2_POS  0                                                            // MCPWM0_TMR2_TMR2起始位
#define MCPWM0_TMR2_TMR2_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_TMR2_TMR2_POS)         // MCPWM0_TMR2_TMR2位掩码
#define MCPWM0_TMR2_TMR2(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_TMR2_TMR2_POS) // [15:0] ADC采样定时器比较门限2寄存器，16位有符号数；发生更新事件后，本寄存器加载到MCPWM实际运行系统中。

/* MCPWM0_TMR3 */
#define MCPWM0_TMR3_TMR3_MAX  ((uint32_t)0xFFFF)                                           // MCPWM0_TMR3_TMR3最大值
#define MCPWM0_TMR3_TMR3_POS  0                                                            // MCPWM0_TMR3_TMR3起始位
#define MCPWM0_TMR3_TMR3_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_TMR3_TMR3_POS)         // MCPWM0_TMR3_TMR3位掩码
#define MCPWM0_TMR3_TMR3(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_TMR3_TMR3_POS) // [15:0] ADC采样定时器比较门限3寄存器，16位有符号数；发生更新事件后，本寄存器加载到MCPWM实际运行系统中。。

/* MCPWM0_TH0 */
#define MCPWM0_TH0_TH_MAX  ((uint32_t)0x7FFF)                                        // MCPWM0_TH0_TH最大值
#define MCPWM0_TH0_TH_POS  0                                                         // MCPWM0_TH0_TH起始位
#define MCPWM0_TH0_TH_MASK (uint32_t)((uint32_t)0x7FFF << MCPWM0_TH0_TH_POS)         // MCPWM0_TH0_TH位掩码
#define MCPWM0_TH0_TH(x)   (uint32_t)((uint32_t)((x) & 0x7FFF) << MCPWM0_TH0_TH_POS) // [14:0] MCPWM时基0计数器门限值，15位无符号数，MCPWM实际运行系统中的时基0计数器从-TH计数到TH；发生更新事件后，本寄存器加载到MCPWM实际运行系统中。

/* MCPWM0_TH1 */
#define MCPWM0_TH1_TH_MAX  ((uint32_t)0x7FFF)                                        // MCPWM0_TH1_TH最大值
#define MCPWM0_TH1_TH_POS  0                                                         // MCPWM0_TH1_TH起始位
#define MCPWM0_TH1_TH_MASK (uint32_t)((uint32_t)0x7FFF << MCPWM0_TH1_TH_POS)         // MCPWM0_TH1_TH位掩码
#define MCPWM0_TH1_TH(x)   (uint32_t)((uint32_t)((x) & 0x7FFF) << MCPWM0_TH1_TH_POS) // [14:0] MCPWM时基1计数器门限值，15位无符号数，MCPWM实际运行系统中的时基1计数器从-TH计数到TH；发生更新事件后，本寄存器加载到MCPWM实际运行系统中。。

/* MCPWM0_CNT0 */
#define MCPWM0_CNT0_CNT_MAX  ((uint32_t)0xFFFF)                                          // MCPWM0_CNT0_CNT最大值
#define MCPWM0_CNT0_CNT_POS  0                                                           // MCPWM0_CNT0_CNT起始位
#define MCPWM0_CNT0_CNT_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_CNT0_CNT_POS)         // MCPWM0_CNT0_CNT位掩码
#define MCPWM0_CNT0_CNT(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_CNT0_CNT_POS) // [15:0] 向此寄存器写入，更改时基0计数器的设定值，发生更新事件后，本寄存器加载到MCPWM实际运行系统的时基0 CNT中。读出的数据为MCPWM实际运行系统中时基0计数器的值。实际读出的计数范围为-TH ~ +TH

/* MCPWM0_CNT1 */
#define MCPWM0_CNT1_CNT_MAX  ((uint32_t)0xFFFF)                                          // MCPWM0_CNT1_CNT最大值
#define MCPWM0_CNT1_CNT_POS  0                                                           // MCPWM0_CNT1_CNT起始位
#define MCPWM0_CNT1_CNT_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_CNT1_CNT_POS)         // MCPWM0_CNT1_CNT位掩码
#define MCPWM0_CNT1_CNT(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_CNT1_CNT_POS) // [15:0] 向此寄存器写入，更改时基1计数器的设定值，发生更新事件后，本寄存器加载到MCPWM实际运行系统的时基1 CNT中。读出的数据为MCPWM实际运行系统中时基1计数器的值。实际读出的计数范围为-TH ~ +TH

/* MCPWM0_UPDATE */
#define MCPWM0_UPDATE_CNT1_UPDATE_BIT BIT27 // [27] 写1产生软件（手动）触发，将MCPWM0_CNT1由预装载寄存器加载到MCPWM运行所使用的影子寄存器
#define MCPWM0_UPDATE_TH1_UPDATE_BIT  BIT26 // [26] 写1产生软件（手动）触发，将MCPWM0_TH1由预装载寄存器加载到MCPWM运行所使用的影子寄存器
#define MCPWM0_UPDATE_TMR3_UPDATE_BIT BIT25 // [25] 写1产生软件（手动）触发，将MCPWM0_TMR3由预装载寄存器加载到MCPWM运行所使用的影子寄存器
#define MCPWM0_UPDATE_TMR2_UPDATE_BIT BIT24 // [24] 写1产生软件（手动）触发，将MCPWM0_TMR2由预装载寄存器加载到MCPWM运行所使用的影子寄存器
#define MCPWM0_UPDATE_TH51_UPDATE_BIT BIT21 // [21] 写1产生软件（手动）触发，将MCPWM0_TH51由预装载寄存器加载到MCPWM运行所使用的影子寄存器
#define MCPWM0_UPDATE_TH50_UPDATE_BIT BIT20 // [20] 写1产生软件（手动）触发，将MCPWM0_TH50由预装载寄存器加载到MCPWM运行所使用的影子寄存器
#define MCPWM0_UPDATE_TH41_UPDATE_BIT BIT19 // [19] 写1产生软件（手动）触发，将MCPWM0_TH41由预装载寄存器加载到MCPWM运行所使用的影子寄存器
#define MCPWM0_UPDATE_TH40_UPDATE_BIT BIT18 // [18] 写1产生软件（手动）触发，将MCPWM0_TH40由预装载寄存器加载到MCPWM运行所使用的影子寄存器
#define MCPWM0_UPDATE_TH31_UPDATE_BIT BIT17 // [17] 写1产生软件（手动）触发，将MCPWM0_TH31由预装载寄存器加载到MCPWM运行所使用的影子寄存器
#define MCPWM0_UPDATE_TH30_UPDATE_BIT BIT16 // [16] 写1产生软件（手动）触发，将MCPWM0_TH30由预装载寄存器加载到MCPWM运行所使用的影子寄存器
#define MCPWM0_UPDATE_CNT0_UPDATE_BIT BIT11 // [11] 写1产生软件（手动）触发，将MCPWM0_CNT0由预装载寄存器加载到MCPWM运行所使用的影子寄存器
#define MCPWM0_UPDATE_TH0_UPDATE_BIT  BIT10 // [10] 写1产生软件（手动）触发，将MCPWM0_TH0由预装载寄存器加载到MCPWM运行所使用的影子寄存器
#define MCPWM0_UPDATE_TMR1_UPDATE_BIT BIT9  // [9] 写1产生软件（手动）触发，将MCPWM0_TMR1由预装载寄存器加载到MCPWM运行所使用的影子寄存器
#define MCPWM0_UPDATE_TMR0_UPDATE_BIT BIT8  // [8] 写1产生软件（手动）触发，将MCPWM0_TMR0由预装载寄存器加载到MCPWM运行所使用的影子寄存器
#define MCPWM0_UPDATE_TH21_UPDATE_BIT BIT5  // [5] 写1产生软件（手动）触发，将MCPWM0_TH21由预装载寄存器加载到MCPWM运行所使用的影子寄存器
#define MCPWM0_UPDATE_TH20_UPDATE_BIT BIT4  // [4] 写1产生软件（手动）触发，将MCPWM0_TH20由预装载寄存器加载到MCPWM运行所使用的影子寄存器
#define MCPWM0_UPDATE_TH11_UPDATE_BIT BIT3  // [3] 写1产生软件（手动）触发，将MCPWM0_TH11由预装载寄存器加载到MCPWM运行所使用的影子寄存器
#define MCPWM0_UPDATE_TH10_UPDATE_BIT BIT2  // [2] 写1产生软件（手动）触发，将MCPWM0_TH10由预装载寄存器加载到MCPWM运行所使用的影子寄存器
#define MCPWM0_UPDATE_TH01_UPDATE_BIT BIT1  // [1] 写1产生软件（手动）触发，将MCPWM0_TH01由预装载寄存器加载到MCPWM运行所使用的影子寄存器
#define MCPWM0_UPDATE_TH00_UPDATE_BIT BIT0  // [0] 写1产生软件（手动）触发，将MCPWM0_TH00由预装载寄存器加载到MCPWM运行所使用的影子寄存器

/* MCPWM0_FCNT */
#define MCPWM0_FCNT_FCNT_MAX  ((uint32_t)0xFFFF)                                           // MCPWM0_FCNT_FCNT最大值
#define MCPWM0_FCNT_FCNT_POS  0                                                            // MCPWM0_FCNT_FCNT起始位
#define MCPWM0_FCNT_FCNT_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_FCNT_FCNT_POS)         // MCPWM0_FCNT_FCNT位掩码
#define MCPWM0_FCNT_FCNT(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_FCNT_FCNT_POS) // [15:0] 若MCPWM0_FAIL012[15]=1，当发生fail0/1事件时，记录MCPWM0_CNT0值，存入MCPWM0_FCNT；若MCPWM0_FAIL345[15]=1，当发生fail2/3事件时，记录MCPWM0_CNT1值，存入MCPWM0_FCNT

/* MCPWM0_EVT0 */
#define MCPWM0_EVT0_TIM3_CMP1_BIT BIT15 // [15] TIMER3 CMP1事件触发时基0开始计数
#define MCPWM0_EVT0_TIM3_CMP0_BIT BIT14 // [14] TIMER3 CMP0事件触发时基0开始计数
#define MCPWM0_EVT0_TIM2_CMP1_BIT BIT13 // [13] TIMER2 CMP1事件触发时基0开始计数
#define MCPWM0_EVT0_TIM2_CMP0_BIT BIT12 // [12] TIMER2 CMP0事件触发时基0开始计数
#define MCPWM0_EVT0_TIM1_CMP1_BIT BIT11 // [11] TIMER1 CMP1事件触发时基0开始计数
#define MCPWM0_EVT0_TIM1_CMP0_BIT BIT10 // [10] TIMER1 CMP0事件触发时基0开始计数
#define MCPWM0_EVT0_TIM0_CMP1_BIT BIT9  // [9] TIMER0 CMP1事件触发时基0开始计数
#define MCPWM0_EVT0_TIM0_CMP0_BIT BIT8  // [8] TIMER0 CMP0事件触发时基0开始计数
#define MCPWM0_EVT0_PWM0_TMR3_BIT BIT3  // [3] MCPWM0 TMR3事件触发时基0开始计数
#define MCPWM0_EVT0_PWM0_TMR2_BIT BIT2  // [2] MCPWM0 TMR2事件触发时基0开始计数
#define MCPWM0_EVT0_PWM0_TMR1_BIT BIT1  // [1] MCPWM0 TMR1事件触发时基0开始计数
#define MCPWM0_EVT0_PWM0_TMR0_BIT BIT0  // [0] MCPWM0 TMR0事件触发时基0开始计数

/* MCPWM0_EVT1 */
#define MCPWM0_EVT1_TIM3_CMP1_BIT BIT15 // [15] TIMER3CMP1事件触发时基1开始计数
#define MCPWM0_EVT1_TIM3_CMP0_BIT BIT14 // [14] TIMER3 CMP0事件触发时基1开始计数
#define MCPWM0_EVT1_TIM2_CMP1_BIT BIT13 // [13] TIMER2 CMP1事件触发时基1开始计数
#define MCPWM0_EVT1_TIM2_CMP0_BIT BIT12 // [12] TIMER2 CMP0事件触发时基1开始计数
#define MCPWM0_EVT1_TIM1_CMP1_BIT BIT11 // [11] TIMER1 CMP1事件触发时基1开始计数
#define MCPWM0_EVT1_TIM1_CMP0_BIT BIT10 // [10] TIMER1 CMP0事件触发时基1开始计数
#define MCPWM0_EVT1_TIM0_CMP1_BIT BIT9  // [9] TIMER0 CMP1事件触发时基1开始计数
#define MCPWM0_EVT1_TIM0_CMP0_BIT BIT8  // [8] TIMER0 CMP0事件触发时基1开始计数
#define MCPWM0_EVT1_PWM0_TMR3_BIT BIT3  // [3] MCPWM0 TMR3事件触发时基1开始计数
#define MCPWM0_EVT1_PWM0_TMR2_BIT BIT2  // [2] MCPWM0 TMR2事件触发时基1开始计数
#define MCPWM0_EVT1_PWM0_TMR1_BIT BIT1  // [1] MCPWM0 TMR1事件触发时基1开始计数
#define MCPWM0_EVT1_PWM0_TMR0_BIT BIT0  // [0] MCPWM0 TMR0事件触发时基1开始计数

/* MCPWM0_DTH00 */
#define MCPWM0_DTH00_DTH00_MAX  ((uint32_t)0x3FF)                                             // MCPWM0_DTH00_DTH00最大值
#define MCPWM0_DTH00_DTH00_POS  0                                                             // MCPWM0_DTH00_DTH00起始位
#define MCPWM0_DTH00_DTH00_MASK (uint32_t)((uint32_t)0x3FF << MCPWM0_DTH00_DTH00_POS)         // MCPWM0_DTH00_DTH00位掩码
#define MCPWM0_DTH00_DTH00(x)   (uint32_t)((uint32_t)((x) & 0x3FF) << MCPWM0_DTH00_DTH00_POS) // [9:0] MCPWM CH0/1/2 N通道死区宽度控制寄存器，10bit无符号数

/* MCPWM0_DTH01 */
#define MCPWM0_DTH01_DTH01_MAX  ((uint32_t)0x3FF)                                             // MCPWM0_DTH01_DTH01最大值
#define MCPWM0_DTH01_DTH01_POS  0                                                             // MCPWM0_DTH01_DTH01起始位
#define MCPWM0_DTH01_DTH01_MASK (uint32_t)((uint32_t)0x3FF << MCPWM0_DTH01_DTH01_POS)         // MCPWM0_DTH01_DTH01位掩码
#define MCPWM0_DTH01_DTH01(x)   (uint32_t)((uint32_t)((x) & 0x3FF) << MCPWM0_DTH01_DTH01_POS) // [9:0] MCPWM CH0/1/2 P通道死区宽度控制寄存器，10bit无符号数

/* MCPWM0_DTH10 */
#define MCPWM0_DTH10_DTH10_MAX  ((uint32_t)0x3FF)                                             // MCPWM0_DTH10_DTH10最大值
#define MCPWM0_DTH10_DTH10_POS  0                                                             // MCPWM0_DTH10_DTH10起始位
#define MCPWM0_DTH10_DTH10_MASK (uint32_t)((uint32_t)0x3FF << MCPWM0_DTH10_DTH10_POS)         // MCPWM0_DTH10_DTH10位掩码
#define MCPWM0_DTH10_DTH10(x)   (uint32_t)((uint32_t)((x) & 0x3FF) << MCPWM0_DTH10_DTH10_POS) // [9:0] MCPWM CH3/4/5 N通道死区宽度控制寄存器，10bit无符号数

/* MCPWM0_DTH11 */
#define MCPWM0_DTH11_DTH11_MAX  ((uint32_t)0x3FF)                                             // MCPWM0_DTH11_DTH11最大值
#define MCPWM0_DTH11_DTH11_POS  0                                                             // MCPWM0_DTH11_DTH11起始位
#define MCPWM0_DTH11_DTH11_MASK (uint32_t)((uint32_t)0x3FF << MCPWM0_DTH11_DTH11_POS)         // MCPWM0_DTH11_DTH11位掩码
#define MCPWM0_DTH11_DTH11(x)   (uint32_t)((uint32_t)((x) & 0x3FF) << MCPWM0_DTH11_DTH11_POS) // [9:0] MCPWM CH3/4/5 P通道死区宽度控制寄存器，10bit无符号数

/* MCPWM0_FLT */
#define MCPWM0_FLT_FLT_CLKDIV_MAX  ((uint32_t)0xFF)                                                // MCPWM0_FLT_FLT_CLKDIV最大值
#define MCPWM0_FLT_FLT_CLKDIV_POS  0                                                               // MCPWM0_FLT_FLT_CLKDIV起始位
#define MCPWM0_FLT_FLT_CLKDIV_MASK (uint32_t)((uint32_t)0xFF << MCPWM0_FLT_FLT_CLKDIV_POS)         // MCPWM0_FLT_FLT_CLKDIV位掩码
#define MCPWM0_FLT_FLT_CLKDIV(x)   (uint32_t)((uint32_t)((x) & 0xFF) << MCPWM0_FLT_FLT_CLKDIV_POS) // [7:0] FAIL信号输入的滤波时钟分频寄存器，基于系统时钟分频，影响MCPWM0_FAIL[1:0]。计算公式如下:系统时钟 / (FLT_CLKDIV + 1)。分频范围是1-256。

/* MCPWM0_SDCFG */
#define MCPWM0_SDCFG_TR1_AEC_BIT      BIT14                                                             // [14] 更新事件是否自动清除MCPWM0_EIF[7:6]并置位MCPWM0_FAIL345.MOE，恢复MCPWM通道3/4/5信号输出。1:使能自动故障清除功能；0:关闭自动故障清除功能。
#define MCPWM0_SDCFG_TR1_T1_UEN_BIT   BIT13                                                             // [13] 时基1 t1（过零）事件更新使能。1:使能；0，关闭。
#define MCPWM0_SDCFG_TR1_T0_UEN_BIT   BIT12                                                             // [12] 时基1 t0（起点）事件更新使能。1:使能；0，关闭。
#define MCPWM0_SDCFG_TR1_UP_INTV_MAX  ((uint32_t)0xF)                                                   // MCPWM0_SDCFG_TR1_UP_INTV最大值
#define MCPWM0_SDCFG_TR1_UP_INTV_POS  8                                                                 // MCPWM0_SDCFG_TR1_UP_INTV起始位
#define MCPWM0_SDCFG_TR1_UP_INTV_MASK (uint32_t)((uint32_t)0xF << MCPWM0_SDCFG_TR1_UP_INTV_POS)         // MCPWM0_SDCFG_TR1_UP_INTV位掩码
#define MCPWM0_SDCFG_TR1_UP_INTV(x)   (uint32_t)((uint32_t)((x) & 0xF) << MCPWM0_SDCFG_TR1_UP_INTV_POS) // [11:8] 时基1更新间隔。一旦t0和t1事件发生次数同TR0_UP_INTV+1相等，MCPWM系统自动触发MCPWM0_TH1，TH30~TH51和MCPWM0_TMR寄存器加载到MCPWM运行系统的操作。若TR1_T1_UEN和TR1_T0_UEN均关闭，将不会触发此类型加载，只能手动触发加载。
#define MCPWM0_SDCFG_TR0_AEC_BIT      BIT6                                                              // [6] 更新事件是否自动清除MCPWM0_EIF[5:4]并置位MCPWM0_FAIL012.MOE，恢复MCPWM通道0/1/2信号输出。1:使能自动故障清除功能；0:关闭自动故障清除功能。
#define MCPWM0_SDCFG_TR0_T1_UEN_BIT   BIT5                                                              // [5] 时基0 t1（过零）事件更新使能。1:使能；0，关闭。
#define MCPWM0_SDCFG_TR0_T0_UEN_BIT   BIT4                                                              // [4] 时基0 t0（起点）事件更新使能。1:使能；0，关闭。
#define MCPWM0_SDCFG_TR0_UP_INTV_MAX  ((uint32_t)0xF)                                                   // MCPWM0_SDCFG_TR0_UP_INTV最大值
#define MCPWM0_SDCFG_TR0_UP_INTV_POS  0                                                                 // MCPWM0_SDCFG_TR0_UP_INTV起始位
#define MCPWM0_SDCFG_TR0_UP_INTV_MASK (uint32_t)((uint32_t)0xF << MCPWM0_SDCFG_TR0_UP_INTV_POS)         // MCPWM0_SDCFG_TR0_UP_INTV位掩码
#define MCPWM0_SDCFG_TR0_UP_INTV(x)   (uint32_t)((uint32_t)((x) & 0xF) << MCPWM0_SDCFG_TR0_UP_INTV_POS) // [3:0] 时基0更新间隔。一旦t0和t1事件发生次数同TR0_UP_INTV+1相等，MCPWM系统自动触发MCPWM0_TH0，MCPWM0_TH00~TH21和MCPWM0_TMR寄存器加载到MCPWM运行系统的操作。若TR0_T1_UEN和TR0_T0_UEN均关闭，将不会触发此类型加载，只能手动触发加载。

/* MCPWM0_AUEN */
#define MCPWM0_AUEN_CNT1_AUPDATE_BIT BIT27 // [27] MCPWM0_CNT1自动加载使能。1:加载；0:不加载。
#define MCPWM0_AUEN_TH1_AUPDATE_BIT  BIT26 // [26] MCPWM0_TH1自动加载使能。1:加载；0:不加载。
#define MCPWM0_AUEN_TMR3_AUPDATE_BIT BIT25 // [25] MCPWM0_TMR3自动加载使能。1:加载；0:不加载。
#define MCPWM0_AUEN_TMR2_AUPDATE_BIT BIT24 // [24] MCPWM0_TMR2自动加载使能。1:加载；0:不加载。
#define MCPWM0_AUEN_TH51_AUPDATE_BIT BIT21 // [21] MCPWM0_TH51自动加载使能。1:加载；0:不加载。
#define MCPWM0_AUEN_TH50_AUPDATE_BIT BIT20 // [20] MCPWM0_TH50自动加载使能。1:加载；0:不加载。
#define MCPWM0_AUEN_TH41_AUPDATE_BIT BIT19 // [19] MCPWM0_TH41自动加载使能。1:加载；0:不加载。
#define MCPWM0_AUEN_TH40_AUPDATE_BIT BIT18 // [18] MCPWM0_TH40自动加载使能。1:加载；0:不加载。
#define MCPWM0_AUEN_TH31_AUPDATE_BIT BIT17 // [17] MCPWM0_TH31自动加载使能。1:加载；0:不加载。
#define MCPWM0_AUEN_TH30_AUPDATE_BIT BIT16 // [16] MCPWM0_TH30自动加载使能。1:加载；0:不加载。
#define MCPWM0_AUEN_CNT0_AUPDATE_BIT BIT11 // [11] MCPWM0_CNT0自动加载使能。1:加载；0:不加载。
#define MCPWM0_AUEN_TH0_AUPDATE_BIT  BIT10 // [10] MCPWM0_TH0自动加载使能。1:加载；0:不加载。
#define MCPWM0_AUEN_TMR1_AUPDATE_BIT BIT9  // [9] MCPWM0_TMR1自动加载使能。1:加载；0:不加载。
#define MCPWM0_AUEN_TMR0_AUPDATE_BIT BIT8  // [8] MCPWM0_TMR0自动加载使能。1:加载；0:不加载。
#define MCPWM0_AUEN_TH21_AUPDATE_BIT BIT5  // [5] MCPWM0_TH21自动加载使能。1:加载；0:不加载。
#define MCPWM0_AUEN_TH20_AUPDATE_BIT BIT4  // [4] MCPWM0_TH20自动加载使能。1:加载；0:不加载。
#define MCPWM0_AUEN_TH11_AUPDATE_BIT BIT3  // [3] MCPWM0_TH11自动加载使能。1:加载；0:不加载。
#define MCPWM0_AUEN_TH10_AUPDATE_BIT BIT2  // [2] MCPWM0_TH10自动加载使能。1:加载；0:不加载。
#define MCPWM0_AUEN_TH01_AUPDATE_BIT BIT1  // [1] MCPWM0_TH01自动加载使能。1:加载；0:不加载。
#define MCPWM0_AUEN_TH00_AUPDATE_BIT BIT0  // [0] MCPWM0_TH00自动加载使能。1:加载；0:不加载。

/* MCPWM0_TCLK */
#define MCPWM0_TCLK_CMP_CTRL_CNT1_BIT BIT11                                                        // [11] 比较器控制MCPWM0_CNT1计数
#define MCPWM0_TCLK_CMP_CTRL_CNT0_BIT BIT10                                                        // [10] 比较器控制MCPWM0_CNT0计数
#define MCPWM0_TCLK_EVT_CNT1_EN_BIT   BIT9                                                         // [9] 时基1外部触发使能
#define MCPWM0_TCLK_EVT_CNT0_EN_BIT   BIT8                                                         // [8] 时基0外部触发使能
#define MCPWM0_TCLK_BASE_CNT1_EN_BIT  BIT7                                                         // [7] MCPWM时基1计数器使能开关。1:使能；0:关闭。
#define MCPWM0_TCLK_BASE_CNT0_EN_BIT  BIT6                                                         // [6] MCPWM时基0计数器使能开关。1:使能；0:关闭。
#define MCPWM0_TCLK_TMR3_TB_BIT       BIT5                                                         // [5] TMR3时基选择，0:时基0，1:时基1
#define MCPWM0_TCLK_TMR2_TB_BIT       BIT4                                                         // [4] TMR2时基选择，0:时基0，1:时基1
#define MCPWM0_TCLK_ZCS_EN_BIT        BIT3                                                         // [3] 使能ZCS事件检测，高有效。当ZCS_EN=1，发生ZCS事件时，将P/N通道同时关断，并延时MCPWM0_ZCS_DELAY后切换状态；当ZCS_EN=0时，发生ZCS事件不延时也不进行状态切换。
#define MCPWM0_TCLK_CLK_EN_BIT        BIT2                                                         // [2] MCPWM工作时钟使能。1:使能；0:关闭。
#define MCPWM0_TCLK_CLK_DIV_MAX       ((uint32_t)0x3)                                              // MCPWM0_TCLK_CLK_DIV最大值
#define MCPWM0_TCLK_CLK_DIV_POS       0                                                            // MCPWM0_TCLK_CLK_DIV起始位
#define MCPWM0_TCLK_CLK_DIV_MASK      (uint32_t)((uint32_t)0x3 << MCPWM0_TCLK_CLK_DIV_POS)         // MCPWM0_TCLK_CLK_DIV位掩码
#define MCPWM0_TCLK_CLK_DIV(x)        (uint32_t)((uint32_t)((x) & 0x3) << MCPWM0_TCLK_CLK_DIV_POS) // [1:0] MCPWM工作时钟分频寄存器。0:系统时钟1:系统时钟/22:系统时钟/43:系统时钟/8

/* MCPWM0_IE0 */
#define MCPWM0_IE0_UP_IE_BIT   BIT14 // [14] 时基0更新事件中断源使能。1，使能；0，关闭。
#define MCPWM0_IE0_TMR3_IE_BIT BIT13 // [13] MCPWM0_CNT0等于MCPWM0_TMR3中断源使能。1，使能；0，关闭。
#define MCPWM0_IE0_TMR2_IE_BIT BIT12 // [12] MCPWM0_CNT0等于MCPWM0_TMR2中断源使能。1，使能；0，关闭。
#define MCPWM0_IE0_TMR1_IE_BIT BIT11 // [11] MCPWM0_CNT0等于MCPWM0_TMR1中断源使能。1，使能；0，关闭。
#define MCPWM0_IE0_TMR0_IE_BIT BIT10 // [10] MCPWM0_CNT0等于MCPWM0_TMR0中断源使能。1，使能；0，关闭。
#define MCPWM0_IE0_TH21_IE_BIT BIT7  // [7] MCPWM0_CNT0等于MCPWM0_TH21中断源使能。1，使能；0，关闭。
#define MCPWM0_IE0_TH20_IE_BIT BIT6  // [6] MCPWM0_CNT0等于MCPWM0_TH20中断源使能。1，使能；0，关闭。
#define MCPWM0_IE0_TH11_IE_BIT BIT5  // [5] MCPWM0_CNT0等于MCPWM0_TH11中断源使能。1，使能；0，关闭。
#define MCPWM0_IE0_TH10_IE_BIT BIT4  // [4] MCPWM0_CNT0等于MCPWM0_TH10中断源使能。1，使能；0，关闭。
#define MCPWM0_IE0_TH01_IE_BIT BIT3  // [3] MCPWM0_CNT0等于MCPWM0_TH01中断源使能。1，使能；0，关闭。
#define MCPWM0_IE0_TH00_IE_BIT BIT2  // [2] MCPWM0_CNT0等于MCPWM0_TH00中断源使能。1，使能；0，关闭。
#define MCPWM0_IE0_T1_IE_BIT   BIT1  // [1] 时基0 T1事件，MCPWM0_CNT0的计数值回0中断源使能。1，使能；0，关闭。
#define MCPWM0_IE0_T0_IE_BIT   BIT0  // [0] 时基0 T0事件，MCPWM0_CNT0的计数值等于MCPWM0_TH0中断源使能。1，使能；0，关闭。

/* MCPWM0_IF0 */
#define MCPWM0_IF0_UP_IF_BIT   BIT14 // [14] 时基0更新事件MCPWM0_TH0/MCPWM0_TH00~MCPWM0_TH21/MCPWM0_TMR等寄存器更新到MCPWM实际运行系统的中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF0_TMR3_IF_BIT BIT13 // [13] MCPWM0_CNT0等于MCPWM0_TMR3中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF0_TMR2_IF_BIT BIT12 // [12] MCPWM0_CNT0等于MCPWM0_TMR2中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF0_TMR1_IF_BIT BIT11 // [11] MCPWM0_CNT0等于MCPWM0_TMR1中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF0_TMR0_IF_BIT BIT10 // [10] MCPWM0_CNT0等于MCPWM0_TMR0中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF0_TH21_IF_BIT BIT7  // [7] MCPWM0_CNT0等于MCPWM0_TH21中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF0_TH20_IF_BIT BIT6  // [6] MCPWM0_CNT0等于MCPWM0_TH20中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF0_TH11_IF_BIT BIT5  // [5] MCPWM0_CNT0等于MCPWM0_TH11中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF0_TH10_IF_BIT BIT4  // [4] MCPWM0_CNT0等于MCPWM0_TH10中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF0_TH01_IF_BIT BIT3  // [3] MCPWM0_CNT0等于MCPWM0_TH01中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF0_TH00_IF_BIT BIT2  // [2] MCPWM0_CNT0等于MCPWM0_TH00中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF0_T1_IF_BIT   BIT1  // [1] t1事件，MCPWM0_CNT0等于0中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF0_T0_IF_BIT   BIT0  // [0] t0事件，MCPWM0_CNT0等于MCPWM0_TH中断事件。1，发生；0，没发生。写1清零。

/* MCPWM0_IE1 */
#define MCPWM0_IE1_UP_IE_BIT   BIT14 // [14] 时基1更新事件MCPWM0_TH1/MCPWM0_TH30~MCPWM0_TH51/MCPWM0_TMR2~MCPWM0_TMR3等寄存器更新到MCPWM实际运行系统的中断使能。1，使能；0，关闭。
#define MCPWM0_IE1_TMR3_IE_BIT BIT13 // [13] MCPWM0_CNT1等于MCPWM0_TMR3中断使能。1，使能；0，关闭。
#define MCPWM0_IE1_TMR2_IE_BIT BIT12 // [12] MCPWM0_CNT1等于MCPWM0_TMR2中断使能。1，使能；0，关闭。
#define MCPWM0_IE1_TH51_IE_BIT BIT7  // [7] MCPWM0_CNT1等于MCPWM0_TH51中断使能。1，使能；0，关闭。
#define MCPWM0_IE1_TH50_IE_BIT BIT6  // [6] MCPWM0_CNT1等于MCPWM0_TH50中断使能。1，使能；0，关闭。
#define MCPWM0_IE1_TH41_IE_BIT BIT5  // [5] MCPWM0_CNT1等于MCPWM0_TH41中断使能。1，使能；0，关闭。
#define MCPWM0_IE1_TH40_IE_BIT BIT4  // [4] MCPWM0_CNT1等于MCPWM0_TH40中断使能。1，使能；0，关闭。
#define MCPWM0_IE1_TH31_IE_BIT BIT3  // [3] MCPWM0_CNT1等于MCPWM0_TH31中断使能。1，使能；0，关闭。
#define MCPWM0_IE1_TH30_IE_BIT BIT2  // [2] MCPWM0_CNT1等于MCPWM0_TH30中断使能。1，使能；0，关闭。
#define MCPWM0_IE1_T1_IE_BIT   BIT1  // [1] T1事件，MCPWM0_CNT1等于0中断使能。1，使能；0，关闭。
#define MCPWM0_IE1_T0_IE_BIT   BIT0  // [0] T0事件，MCPWM0_CNT1等于MCPWM0_TH1中断使能。1，使能；0，关闭。

/* MCPWM0_IF1 */
#define MCPWM0_IF1_UP_IF_BIT   BIT14 // [14] 时基1更新事件MCPWM0_TH1/MCPWM0_TH30~MCPWM0_TH51/MCPWM0_TMR等寄存器更新到MCPWM实际运行系统的中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF1_TMR3_IF_BIT BIT13 // [13] MCPWM0_CNT1等于MCPWM0_TMR3中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF1_TMR2_IF_BIT BIT12 // [12] MCPWM0_CNT1等于MCPWM0_TMR2中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF1_TH51_IF_BIT BIT7  // [7] MCPWM0_CNT1等于MCPWM0_TH51中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF1_TH50_IF_BIT BIT6  // [6] MCPWM0_CNT1等于MCPWM0_TH50中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF1_TH41_IF_BIT BIT5  // [5] MCPWM0_CNT1等于MCPWM0_TH41中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF1_TH40_IF_BIT BIT4  // [4] MCPWM0_CNT1等于MCPWM0_TH40中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF1_TH31_IF_BIT BIT3  // [3] MCPWM0_CNT1等于MCPWM0_TH31中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF1_TH30_IF_BIT BIT2  // [2] MCPWM0_CNT1等于MCPWM0_TH30中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF1_T1_IF_BIT   BIT1  // [1] T1事件，MCPWM0_CNT1等于0中断事件。1，发生；0，没发生。写1清零。
#define MCPWM0_IF1_T0_IF_BIT   BIT0  // [0] T0事件，MCPWM0_CNT1等于MCPWM0_TH中断事件。1，发生；0，没发生。写1清零。

/* MCPWM0_EIE */
#define MCPWM0_EIE_ZCS1_IE_BIT  BIT9 // [9] 时基1 ZCS事件中断源使能。1，使能；0，关闭。
#define MCPWM0_EIE_ZCS0_IE_BIT  BIT8 // [8] 时基0 ZCS事件中断源使能。1，使能；0，关闭。
#define MCPWM0_EIE_FAIL3_IE_BIT BIT7 // [7] FAIL3中断源使能。1，使能；0，关闭。
#define MCPWM0_EIE_FAIL2_IE_BIT BIT6 // [6] FAIL2中断源使能。1，使能；0，关闭。
#define MCPWM0_EIE_FAIL1_IE_BIT BIT5 // [5] FAIL1中断源使能。1，使能；0，关闭。
#define MCPWM0_EIE_FAIL0_IE_BIT BIT4 // [4] FAIL0中断源使能。1，使能；0，关闭。

/* MCPWM0_EIF */
#define MCPWM0_EIF_ZCS1_IF_BIT  BIT9 // [9] 时基1 ZCS中断源事件。1，发生；0，没发生。写1清零。
#define MCPWM0_EIF_ZCS0_IF_BIT  BIT8 // [8] 时基0 ZCS中断源事件。1，发生；0，没发生。写1清零。
#define MCPWM0_EIF_FAIL3_IF_BIT BIT7 // [7] FAIL3中断源事件。1，发生；0，没发生。写1清零。
#define MCPWM0_EIF_FAIL2_IF_BIT BIT6 // [6] FAIL2中断源事件。1，发生；0，没发生。写1清零。
#define MCPWM0_EIF_FAIL1_IF_BIT BIT5 // [5] FAIL1中断源事件。1，发生；0，没发生。写1清零。
#define MCPWM0_EIF_FAIL0_IF_BIT BIT4 // [4] FAIL0中断源事件。1，发生；0，没发生。写1清零。

/* MCPWM0_RE */
#define MCPWM0_RE_TR1_T1_RE1_BIT BIT15 // [15] 时基1 T1事件DMA请求1使能。1:使能；0:关闭。
#define MCPWM0_RE_TR1_T0_RE1_BIT BIT14 // [14] 时基1 T0事件DMA请求1使能。1:使能；0:关闭。
#define MCPWM0_RE_TR0_T1_RE1_BIT BIT13 // [13] 时基0 T1事件DMA请求1使能。1:使能；0:关闭。
#define MCPWM0_RE_TR0_T0_RE1_BIT BIT12 // [12] 时基0 T0事件DMA请求1使能。1:使能；0:关闭。
#define MCPWM0_RE_TMR3_RE1_BIT   BIT11 // [11] MCPWM计数器命中TMR3，DMA请求1使能。1:使能；0:关闭。
#define MCPWM0_RE_TMR2_RE1_BIT   BIT10 // [10] MCPWM计数器命中TMR2，DMA请求1使能。1:使能；0:关闭。
#define MCPWM0_RE_TMR1_RE1_BIT   BIT9  // [9] MCPWM计数器命中TMR1，DMA请求1使能。1:使能；0:关闭。
#define MCPWM0_RE_TMR0_RE1_BIT   BIT8  // [8] MCPWM计数器命中TMR0，DMA请求1使能。1:使能；0:关闭。
#define MCPWM0_RE_TR1_T1_RE0_BIT BIT7  // [7] 时基1 T1事件DMA请求0使能。1:使能；0:关闭。
#define MCPWM0_RE_TR1_T0_RE0_BIT BIT6  // [6] 时基1 T0事件DMA请求0使能。1:使能；0:关闭。
#define MCPWM0_RE_TR0_T1_RE0_BIT BIT5  // [5] 时基0 T1事件DMA请求0使能。1:使能；0:关闭。
#define MCPWM0_RE_TR0_T0_RE0_BIT BIT4  // [4] 时基0 T0事件DMA请求0使能。1:使能；0:关闭。
#define MCPWM0_RE_TMR3_RE0_BIT   BIT3  // [3] MCPWM计数器命中TMR3，DMA请求0使能。1:使能；0:关闭。
#define MCPWM0_RE_TMR2_RE0_BIT   BIT2  // [2] MCPWM计数器命中TMR2，DMA请求0使能。1:使能；0:关闭。
#define MCPWM0_RE_TMR1_RE0_BIT   BIT1  // [1] MCPWM计数器命中TMR1，DMA请求0使能。1:使能；0:关闭。
#define MCPWM0_RE_TMR0_RE0_BIT   BIT0  // [0] MCPWM计数器命中TMR0，DMA请求0使能。1:使能；0:关闭。

/* MCPWM0_PP */
#define MCPWM0_PP_IO5_PPE_BIT BIT5 // [5] IO5推挽模式使能信号。写1，使能；写0，关闭。
#define MCPWM0_PP_IO4_PPE_BIT BIT4 // [4] IO4推挽模式使能信号。写1，使能；写0，关闭。
#define MCPWM0_PP_IO3_PPE_BIT BIT3 // [3] IO3推挽模式使能信号。写1，使能；写0，关闭。
#define MCPWM0_PP_IO2_PPE_BIT BIT2 // [2] IO2推挽模式使能信号。写1，使能；写0，关闭。
#define MCPWM0_PP_IO1_PPE_BIT BIT1 // [1] IO1推挽模式使能信号。写1，使能；写0，关闭。
#define MCPWM0_PP_IO0_PPE_BIT BIT0 // [0] IO0推挽模式使能信号。写1，使能；写0，关闭。

/* MCPWM0_IO01 */
#define MCPWM0_IO01_CH1_WM_BIT     BIT15 // [15] CH1工作模式选择。1:边沿模式；0:互补模式。
#define MCPWM0_IO01_CH1_PN_SW_BIT  BIT14 // [14] CH1的P和N通道输出互换选择。即P通道信号最后从N通道输出，N通道的信号最后从P通道输出。1:互换；0:不互换。
#define MCPWM0_IO01_CH1_SCTRLP_BIT BIT13 // [13] 当CH1_PS=1时，输出到CH1 P通道的值。
#define MCPWM0_IO01_CH1_SCTRLN_BIT BIT12 // [12] 当CH1_NS=1时，输出到CH1 N通道的值。
#define MCPWM0_IO01_CH1_PS_BIT     BIT11 // [11] CH1 P来源。1:来自CH1_SCTRLP；0:MCPWM内部计数器产生。
#define MCPWM0_IO01_CH1_NS_BIT     BIT10 // [10] CH1 N来源。1:来自CH1_SCTRLN；0:MCPWM内部计数器产生。
#define MCPWM0_IO01_CH1_PP_BIT     BIT9  // [9] CH1 P极性选择。1:CH1 P信号取反输出；0:CH1 P信号正常输出。
#define MCPWM0_IO01_CH1_NP_BIT     BIT8  // [8] CH1 N极性选择。1:CH1 N信号取反输出；0:CH1 N信号正常输出。
#define MCPWM0_IO01_CH0_WM_BIT     BIT7  // [7] CH0工作模式选择。1:边沿模式；0:互补模式。
#define MCPWM0_IO01_CH0_PN_SW_BIT  BIT6  // [6] CH0的P和N通道输出互换选择。即P通道信号最后从N通道输出，N通道的信号最后从P通道输出。1:互换；0:不互换。
#define MCPWM0_IO01_CH0_SCTRLP_BIT BIT5  // [5] 当CH0_PS =1时，输出到CH0 P通道的值。
#define MCPWM0_IO01_CH0_SCTRLN_BIT BIT4  // [4] 当CH0_NS =1时，输出到CH0 N通道的值。
#define MCPWM0_IO01_CH0_PS_BIT     BIT3  // [3] CH0 P来源。1:来自CH0_SCTRLP；0:MCPWM实际运行系统中计数器产生。
#define MCPWM0_IO01_CH0_NS_BIT     BIT2  // [2] CH0 N来源。1:来自CH0_SCTRLN；0:MCPWM实际运行系统中计数器产生。
#define MCPWM0_IO01_CH0_PP_BIT     BIT1  // [1] CH0 P极性选择。1:CH0 P信号取反输出；0:CH0 P信号正常输出。
#define MCPWM0_IO01_CH0_NP_BIT     BIT0  // [0] CH0 N极性选择。1:CH0 N信号取反输出；0:CH0 N信号正常输出。极性选择跟随通道交换，例如CH0 N选择取反输出，同时选择了通道交换，则交换后的CH0 N仍是取反输出。

/* MCPWM0_IO23 */
#define MCPWM0_IO23_CH3_WM_BIT     BIT15 // [15] CH3工作模式选择。1:Edge模式；0:互补模式。
#define MCPWM0_IO23_CH3_PN_SW_BIT  BIT14 // [14] CH3的P和N通道输出互换选择。即P通道信号最后从N通道输出，N通道的信号最后从P通道输出。1:互换；0:不互换。
#define MCPWM0_IO23_CH3_SCTRLP_BIT BIT13 // [13] 当CH3_PS =1时，输出到CH3 P通道的值。
#define MCPWM0_IO23_CH3_SCTRLN_BIT BIT12 // [12] 当CH3_NS =1时，输出到CH3 N通道的值。
#define MCPWM0_IO23_CH3_PS_BIT     BIT11 // [11] CH3 P来源。1:来自CH3_SCTRLP；0:MCPWM实际运行系统中计数器产生。
#define MCPWM0_IO23_CH3_NS_BIT     BIT10 // [10] CH3 N来源。1:来自CH3_SCTRLN；0:MCPWM实际运行系统中计数器产生。
#define MCPWM0_IO23_CH3_PP_BIT     BIT9  // [9] CH3 P极性选择。1:CH3 P信号取反输出；0:CH3 P信号正常输出。
#define MCPWM0_IO23_CH3_NP_BIT     BIT8  // [8] CH3 N极性选择。1:CH3 N信号取反输出；0:CH3 N信号正常输出。
#define MCPWM0_IO23_CH2_WM_BIT     BIT7  // [7] CH2工作模式选择。1:Edge模式；0:互补模式。
#define MCPWM0_IO23_CH2_PN_SW_BIT  BIT6  // [6] CH2的P和N通道输出互换选择。即P通道信号最后从N通道输出，N通道的信号最后从P通道输出。1:互换；0:不互换。
#define MCPWM0_IO23_CH2_SCTRLP_BIT BIT5  // [5] 当CH2_PS =1时，输出到CH2 P通道的值。
#define MCPWM0_IO23_CH2_SCTRLN_BIT BIT4  // [4] 当CH2_NS =1时，输出到CH2 N通道的值。
#define MCPWM0_IO23_CH2_PS_BIT     BIT3  // [3] CH2 P来源。1:来自CH2_SCTRLP；0:MCPWM实际运行系统中计数器产生。
#define MCPWM0_IO23_CH2_NS_BIT     BIT2  // [2] CH2 N来源。1:来自CH2_SCTRLN；0:MCPWM实际运行系统中计数器产生。
#define MCPWM0_IO23_CH20_PP_BIT    BIT1  // [1] CH2 P极性选择。1:CH2 P信号取反输出；0:CH2 P信号正常输出。
#define MCPWM0_IO23_CH2_NP_BIT     BIT0  // [0] CH2 N极性选择。1:CH2 N信号取反输出；0:CH2 N信号正常输出。极性选择跟随通道交换，例如CH2 N选择取反输出，同时选择了通道交换，则交换后的CH2 N仍是取反输出。

/* MCPWM0_IO45 */
#define MCPWM0_IO45_CH5_WM_BIT     BIT15 // [15] CH5工作模式选择。1:Edge模式；0:互补模式。
#define MCPWM0_IO45_CH5_PN_SW_BIT  BIT14 // [14] CH5的P和N通道输出互换选择。即P通道信号最后从N通道输出，N通道的信号最后从P通道输出。1:互换；0:不互换。
#define MCPWM0_IO45_CH5_SCTRLP_BIT BIT13 // [13] 当CH5_PS =1时，输出到CH5 P通道的值。
#define MCPWM0_IO45_CH5_SCTRLN_BIT BIT12 // [12] 当CH5_NS =1时，输出到CH5 N通道的值。
#define MCPWM0_IO45_CH5_PS_BIT     BIT11 // [11] CH5 P来源。1:来自CH5_SCTRLP；0:MCPWM实际运行系统中计数器产生。
#define MCPWM0_IO45_CH5_NS_BIT     BIT10 // [10] CH5 N来源。1:来自CH5_SCTRLN；0:MCPWM实际运行系统中计数器产生。
#define MCPWM0_IO45_CH5_PP_BIT     BIT9  // [9] CH5 P极性选择。1:CH5 P信号取反输出；0:CH5 P信号正常输出。
#define MCPWM0_IO45_CH5_NP_BIT     BIT8  // [8] CH5 N极性选择。1:CH5 N信号取反输出；0:CH5 N信号正常输出。
#define MCPWM0_IO45_CH4_WM_BIT     BIT7  // [7] CH4工作模式选择。1:Edge模式；0:互补模式。
#define MCPWM0_IO45_CH4_PN_SW_BIT  BIT6  // [6] CH4的P和N通道输出互换选择。即P通道信号最后从N通道输出，N通道的信号最后从P通道输出。1:互换；0:不互换。
#define MCPWM0_IO45_CH4_SCTRLP_BIT BIT5  // [5] 当CH4_PS =1时，输出到CH4 P通道的值。
#define MCPWM0_IO45_CH4_SCTRLN_BIT BIT4  // [4] 当CH4_NS =1时，输出到CH4 N通道的值。
#define MCPWM0_IO45_CH4_PS_BIT     BIT3  // [3] CH4 P来源。1:来自CH4_SCTRLP；0:MCPWM实际运行系统中计数器产生。
#define MCPWM0_IO45_CH4_NS_BIT     BIT2  // [2] CH4 N来源。1:来自CH4_SCTRLN；0:MCPWM实际运行系统中计数器产生。
#define MCPWM0_IO45_CH40_PP_BIT    BIT1  // [1] CH4 P极性选择。1:CH4 P信号取反输出；0:CH4 P信号正常输出。
#define MCPWM0_IO45_CH4_NP_BIT     BIT0  // [0] CH4 N极性选择。1:CH4 N信号取反输出；0:CH4 N信号正常输出。极性选择跟随通道交换，例如CH4 N选择取反输出，同时选择了通道交换，则交换后的CH4 N仍是取反输出。

/* MCPWM0_FAIL012 */
#define MCPWM0_FAIL012_FAIL_0CAP_BIT  BIT15                                                             // [15] 当发生fail0/1事件时，将MCPWM0_CNT0值存入MCPWM0_FCNT
#define MCPWM0_FAIL012_FAIL1_SEL_MAX  ((uint32_t)0x3)                                                   // MCPWM0_FAIL012_FAIL1_SEL最大值
#define MCPWM0_FAIL012_FAIL1_SEL_POS  10                                                                // MCPWM0_FAIL012_FAIL1_SEL起始位
#define MCPWM0_FAIL012_FAIL1_SEL_MASK (uint32_t)((uint32_t)0x3 << MCPWM0_FAIL012_FAIL1_SEL_POS)         // MCPWM0_FAIL012_FAIL1_SEL位掩码
#define MCPWM0_FAIL012_FAIL1_SEL(x)   (uint32_t)((uint32_t)((x) & 0x3) << MCPWM0_FAIL012_FAIL1_SEL_POS) // [11:10] FAIL1来源选择0: IO MCPWM0_BKIN11: 比较器1原始输出2: CLUOUT23: CLUOUT3
#define MCPWM0_FAIL012_FAIL0_SEL_MAX  ((uint32_t)0x3)                                                   // MCPWM0_FAIL012_FAIL0_SEL最大值
#define MCPWM0_FAIL012_FAIL0_SEL_POS  8                                                                 // MCPWM0_FAIL012_FAIL0_SEL起始位
#define MCPWM0_FAIL012_FAIL0_SEL_MASK (uint32_t)((uint32_t)0x3 << MCPWM0_FAIL012_FAIL0_SEL_POS)         // MCPWM0_FAIL012_FAIL0_SEL位掩码
#define MCPWM0_FAIL012_FAIL0_SEL(x)   (uint32_t)((uint32_t)((x) & 0x3) << MCPWM0_FAIL012_FAIL0_SEL_POS) // [9:8] FAIL0来源选择0: IO MCPWM0_BKIN01: 比较器0原始输出2: CLUOUT03: CLUOUT1
#define MCPWM0_FAIL012_HALT_PRT_BIT   BIT7                                                              // [7] MCU进入HALT状态，MCPWM输出值选择。1:正常输出；0:强制MCPWM输出保护值。
#define MCPWM0_FAIL012_MOE_BIT        BIT6                                                              // [6] MOE控制MCPWM CH0/CH1/CH2通道P和N输出值。1:输出MCPWM产生的正常信号0:输出MCPWM0_CH_DEF设置的CHxN_DEFAULT和CHxP_DEFAULT默认值，此默认值不受极性/通道选择等控制。MCPWM0_EIF.FAIL1_IF和MCPWM0_EIF.FAIL0_IF任意一位变1将触发MOE变成0，输出默认值。
#define MCPWM0_FAIL012_FAIL1_EN_BIT   BIT5                                                              // [5] FAIL1输入使能。1:使能；0:关闭。
#define MCPWM0_FAIL012_FAIL0_EN_BIT   BIT4                                                              // [4] FAIL0输入使能。1:使能；0:关闭。
#define MCPWM0_FAIL012_FAIL1_POL_BIT  BIT3                                                              // [3] FAIL1极性选择。1:信号极性取反输入，信号输入低为有效电平；0:信号极性正常输入，信号输入高为有效电平。
#define MCPWM0_FAIL012_FAIL0_POL_BIT  BIT2                                                              // [2] FAIL0极性选择。1:信号极性取反输入，信号输入低为有效电平；0:信号极性正常输入，信号输入高为有效电平。

/* MCPWM0_FAIL345 */
#define MCPWM0_FAIL345_FAIL_1CAP_BIT  BIT15                                                             // [15] 当发生fail2/3事件时，将MCPWM0_CNT1值存入MCPWM0_FCNT
#define MCPWM0_FAIL345_FAIL3_SEL_MAX  ((uint32_t)0x3)                                                   // MCPWM0_FAIL345_FAIL3_SEL最大值
#define MCPWM0_FAIL345_FAIL3_SEL_POS  10                                                                // MCPWM0_FAIL345_FAIL3_SEL起始位
#define MCPWM0_FAIL345_FAIL3_SEL_MASK (uint32_t)((uint32_t)0x3 << MCPWM0_FAIL345_FAIL3_SEL_POS)         // MCPWM0_FAIL345_FAIL3_SEL位掩码
#define MCPWM0_FAIL345_FAIL3_SEL(x)   (uint32_t)((uint32_t)((x) & 0x3) << MCPWM0_FAIL345_FAIL3_SEL_POS) // [11:10] FAIL3来源选择0: IO MCPWM0_BKIN11:比较器1的结果2: CLUOUT23: CLUOUT3
#define MCPWM0_FAIL345_FAIL2_SEL_MAX  ((uint32_t)0x3)                                                   // MCPWM0_FAIL345_FAIL2_SEL最大值
#define MCPWM0_FAIL345_FAIL2_SEL_POS  8                                                                 // MCPWM0_FAIL345_FAIL2_SEL起始位
#define MCPWM0_FAIL345_FAIL2_SEL_MASK (uint32_t)((uint32_t)0x3 << MCPWM0_FAIL345_FAIL2_SEL_POS)         // MCPWM0_FAIL345_FAIL2_SEL位掩码
#define MCPWM0_FAIL345_FAIL2_SEL(x)   (uint32_t)((uint32_t)((x) & 0x3) << MCPWM0_FAIL345_FAIL2_SEL_POS) // [9:8] FAIL2来源选择0: IO MCPWM0_BKIN01:比较器0的结果2: CLUOUT03: CLUOUT1
#define MCPWM0_FAIL345_HALT_PRT_BIT   BIT7                                                              // [7] MCU进入HALT状态，MCPWM输出值选择。1:正常输出；0:强制MCPWM输出保护值。
#define MCPWM0_FAIL345_MOE_BIT        BIT6                                                              // [6] MOE控制MCPWM CH3/CH4/CH5通道P和N输出值。1:输出MCPWM产生的正常信号0:输出CH3N_DEFAULT和CH3P_DEFAULT默认值，此默认值不受极性/通道选择等控制。MCPWM0_EIF.FAIL2_IF和MCPWM0_EIF.FAIL3_IF任意一位变1将触发MOE变成0，输出默认值。
#define MCPWM0_FAIL345_FAIL3_EN_BIT   BIT5                                                              // [5] FAIL3输入使能。1:使能；0:关闭。
#define MCPWM0_FAIL345_FAIL2_EN_BIT   BIT4                                                              // [4] FAIL2输入使能。1:使能；0:关闭。
#define MCPWM0_FAIL345_FAIL3_POL_BIT  BIT3                                                              // [3] FAIL3极性选择。1:信号极性取反输入，信号输入低为有效电平；0:信号极性正常输入，信号输入高为有效电平。
#define MCPWM0_FAIL345_FAIL2_POL_BIT  BIT2                                                              // [2] FAIL2极性选择。1:信号极性取反输入，信号输入低为有效电平；0:信号极性正常输入，信号输入高为有效电平。

/* MCPWM0_CH_DEF */
#define MCPWM0_CH_DEF_CH5P_DEFAULT_BIT BIT11 // [11] CH5_P通道默认值
#define MCPWM0_CH_DEF_CH5N_DEFAULT_BIT BIT10 // [10] CH5_N通道默认值
#define MCPWM0_CH_DEF_CH4P_DEFAULT_BIT BIT9  // [9] CH4_P通道默认值
#define MCPWM0_CH_DEF_CH4N_DEFAULT_BIT BIT8  // [8] CH4_N通道默认值
#define MCPWM0_CH_DEF_CH3P_DEFAULT_BIT BIT7  // [7] CH3 P通道默认值
#define MCPWM0_CH_DEF_CH3N_DEFAULT_BIT BIT6  // [6] CH3 N通道默认值。当发生FAIL事件或MOE为0时，相应通道输出默认电平。默认电平输出不受MCPWM0_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14通道交换和极性控制的影响，直接控制通道输出。
#define MCPWM0_CH_DEF_CH2P_DEFAULT_BIT BIT5  // [5] CH2_P通道默认值
#define MCPWM0_CH_DEF_CH2N_DEFAULT_BIT BIT4  // [4] CH2_N通道默认值
#define MCPWM0_CH_DEF_CH1P_DEFAULT_BIT BIT3  // [3] CH1_P通道默认值
#define MCPWM0_CH_DEF_CH1N_DEFAULT_BIT BIT2  // [2] CH1_N通道默认值
#define MCPWM0_CH_DEF_CH0P_DEFAULT_BIT BIT1  // [1] CH0_P通道默认值
#define MCPWM0_CH_DEF_CH0N_DEFAULT_BIT BIT0  // [0] CH0_N通道默认值。当发生FAIL事件或MOE为0时，相应通道输出默认电平。默认电平输出不受MCPWM0_IO01和MCPWM0_IO23的 BIT0、BIT1、BIT8、BIT9、BIT6、BIT14通道交换和极性控制的影响，直接控制通道输出。

/* MCPWM0_CH_MASK */
#define MCPWM0_CH_MASK_CH5P_FAIL_EN_BIT BIT11 // [11] CH5_P 通道FAIL事件使能，高有效，默认开启
#define MCPWM0_CH_MASK_CH5N_FAIL_EN_BIT BIT10 // [10] CH5_N通道 FAIL事件使能，高有效，默认开启
#define MCPWM0_CH_MASK_CH4P_FAIL_EN_BIT BIT9  // [9] CH4_P 通道FAIL事件使能，高有效，默认开启
#define MCPWM0_CH_MASK_CH4N_FAIL_EN_BIT BIT8  // [8] CH4_N通道 FAIL事件使能，高有效，默认开启
#define MCPWM0_CH_MASK_CH3P_FAIL_EN_BIT BIT7  // [7] CH3_P 通道FAIL事件使能，高有效，默认开启
#define MCPWM0_CH_MASK_CH3N_FAIL_EN_BIT BIT6  // [6] CH3_N 通道FAIL事件使能，高有效，默认开启
#define MCPWM0_CH_MASK_CH2P_FAIL_EN_BIT BIT5  // [5] CH2_P 通道FAIL事件使能，高有效，默认开启
#define MCPWM0_CH_MASK_CH2N_FAIL_EN_BIT BIT4  // [4] CH2_N 通道FAIL事件使能，高有效，默认开启
#define MCPWM0_CH_MASK_CH1P_FAIL_EN_BIT BIT3  // [3] CH1_P 通道FAIL事件使能，高有效，默认开启
#define MCPWM0_CH_MASK_CH1N_FAIL_EN_BIT BIT2  // [2] CH1_N通道 FAIL事件使能，高有效，默认开启
#define MCPWM0_CH_MASK_CH0P_FAIL_EN_BIT BIT1  // [1] CH0_P 通道FAIL事件使能，高有效，默认开启
#define MCPWM0_CH_MASK_CH0N_FAIL_EN_BIT BIT0  // [0] CH0_N 通道FAIL事件使能，1：发生FAIL事件或MCPWM0_FAIL012.MOE=0时，CH0_N通道电平输出为默认值，0：发生FAIL事件或MCPWM0_FAIL012.MOE=0时，CH0_N通道电平不受影响，仍由MCPWM内部硬件控制。默认开启FAIL使能

/* MCPWM0_PRT */
#define MCPWM0_PRT_PRT_MAX  ((uint32_t)0xFFFF)                                         // MCPWM0_PRT_PRT最大值
#define MCPWM0_PRT_PRT_POS  0                                                          // MCPWM0_PRT_PRT起始位
#define MCPWM0_PRT_PRT_MASK (uint32_t)((uint32_t)0xFFFF << MCPWM0_PRT_PRT_POS)         // MCPWM0_PRT_PRT位掩码
#define MCPWM0_PRT_PRT(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << MCPWM0_PRT_PRT_POS) // [15:0] 写入0xDEAD，解除MCPWM寄存器写保护；写入其它值，MCPWM寄存器进入写保护。此寄存器读出恒为0。

/* MCPWM0_STT_HYST */
#define MCPWM0_STT_HYST_STT_HYST_MAX  ((uint32_t)0xFFF)                                                   // MCPWM0_STT_HYST_STT_HYST最大值
#define MCPWM0_STT_HYST_STT_HYST_POS  0                                                                   // MCPWM0_STT_HYST_STT_HYST起始位
#define MCPWM0_STT_HYST_STT_HYST_MASK (uint32_t)((uint32_t)0xFFF << MCPWM0_STT_HYST_STT_HYST_POS)         // MCPWM0_STT_HYST_STT_HYST位掩码
#define MCPWM0_STT_HYST_STT_HYST(x)   (uint32_t)((uint32_t)((x) & 0xFFF) << MCPWM0_STT_HYST_STT_HYST_POS) // [11:0] 状态切换延时，仅在MCPWM0_TCLK.CMP_CTRL_CNT0=1或MCPWM0_TCLK.CMP_CTRL_CNT1=1时起作用。12bit无符号数

/* MCPWM0_ZCS_DELAY */
#define MCPWM0_ZCS_DELAY_ZCS_DELAY_MAX  ((uint32_t)0x7FFF)                                                     // MCPWM0_ZCS_DELAY_ZCS_DELAY最大值
#define MCPWM0_ZCS_DELAY_ZCS_DELAY_POS  0                                                                      // MCPWM0_ZCS_DELAY_ZCS_DELAY起始位
#define MCPWM0_ZCS_DELAY_ZCS_DELAY_MASK (uint32_t)((uint32_t)0x7FFF << MCPWM0_ZCS_DELAY_ZCS_DELAY_POS)         // MCPWM0_ZCS_DELAY_ZCS_DELAY位掩码
#define MCPWM0_ZCS_DELAY_ZCS_DELAY(x)   (uint32_t)((uint32_t)((x) & 0x7FFF) << MCPWM0_ZCS_DELAY_ZCS_DELAY_POS) // [14:0] ZCS状态停留时间，仅在MCPWM0_TCLK.CMP_CTRL_CNT0=1或MCPWM0_TCLK.CMP_CTRL_CNT1=1时起作用。15bit无符号数。ZCS_DELAY必须大于STT_HYST

/* GPIOx_PIE ( x = 0,1,2,3) */
#define GPIOx_PIE_PIE15_BIT BIT15 // [15] GPIO x[15]/ Px[15]输入使能
#define GPIOx_PIE_PIE14_BIT BIT14 // [14] GPIO x[14]/ Px[14]输入使能
#define GPIOx_PIE_PIE13_BIT BIT13 // [13] GPIO x[13]/ Px[13]输入使能
#define GPIOx_PIE_PIE12_BIT BIT12 // [12] GPIO x[12]/ Px[12]输入使能
#define GPIOx_PIE_PIE11_BIT BIT11 // [11] GPIO x[11]/ Px[11]输入使能
#define GPIOx_PIE_PIE10_BIT BIT10 // [10] GPIO x[10]/ Px[10]输入使能
#define GPIOx_PIE_PIE9_BIT  BIT9  // [9] GPIO x[9]/ Px[9]输入使能
#define GPIOx_PIE_PIE8_BIT  BIT8  // [8] GPIO x[8]/ Px[8]输入使能
#define GPIOx_PIE_PIE7_BIT  BIT7  // [7] GPIO x[7]/ Px[7]输入使能
#define GPIOx_PIE_PIE6_BIT  BIT6  // [6] GPIO x[6]/ Px[6]输入使能
#define GPIOx_PIE_PIE5_BIT  BIT5  // [5] GPIO x[5]/ Px[5]输入使能
#define GPIOx_PIE_PIE4_BIT  BIT4  // [4] GPIO x[4]/ Px[4]输入使能
#define GPIOx_PIE_PIE3_BIT  BIT3  // [3] GPIO x[3]/ Px[3]输入使能
#define GPIOx_PIE_PIE2_BIT  BIT2  // [2] GPIO x[2]/ Px[2]输入使能
#define GPIOx_PIE_PIE1_BIT  BIT1  // [1] GPIO x[1]/ Px[1]输入使能
#define GPIOx_PIE_PIE0_BIT  BIT0  // [0] GPIO x[0]/ Px[0]输入使能

/* GPIOx_POE ( x = 0,1,2,3) */
#define GPIOx_POE_POE15_BIT BIT15 // [15] GPIO x[15]/ Px[15]输出使能
#define GPIOx_POE_POE14_BIT BIT14 // [14] GPIO x[14]/ Px[14]输出使能
#define GPIOx_POE_POE13_BIT BIT13 // [13] GPIO x[13]/ Px[13]输出使能
#define GPIOx_POE_POE12_BIT BIT12 // [12] GPIO x[12]/ Px[12]输出使能
#define GPIOx_POE_POE11_BIT BIT11 // [11] GPIO x[11]/ Px[11]输出使能
#define GPIOx_POE_POE10_BIT BIT10 // [10] GPIO x[10]/ Px[10]输出使能
#define GPIOx_POE_POE9_BIT  BIT9  // [9] GPIO x[9]/ Px[9]输出使能
#define GPIOx_POE_POE8_BIT  BIT8  // [8] GPIO x[8]/ Px[8]输出使能
#define GPIOx_POE_POE7_BIT  BIT7  // [7] GPIO x[7]/ Px[7]输出使能
#define GPIOx_POE_POE6_BIT  BIT6  // [6] GPIO x[6]/ Px[6]输出使能
#define GPIOx_POE_POE5_BIT  BIT5  // [5] GPIO x[5]/ Px[5]输出使能
#define GPIOx_POE_POE4_BIT  BIT4  // [4] GPIO x[4]/ Px[4]输出使能
#define GPIOx_POE_POE3_BIT  BIT3  // [3] GPIO x[3]/ Px[3]输出使能
#define GPIOx_POE_POE2_BIT  BIT2  // [2] GPIO x[2]/ Px[2]输出使能
#define GPIOx_POE_POE1_BIT  BIT1  // [1] GPIO x[1]/ Px[1]输出使能
#define GPIOx_POE_POE0_BIT  BIT0  // [0] GPIO x[0]/ Px[0]输出使能

/* GPIOx_PDI ( x = 0,1,2,3) */
#define GPIOx_PDI_PDI_MAX  ((uint32_t)0xFFFF)                                        // GPIOx_PDI_PDI最大值
#define GPIOx_PDI_PDI_POS  0                                                         // GPIOx_PDI_PDI起始位
#define GPIOx_PDI_PDI_MASK (uint32_t)((uint32_t)0xFFFF << GPIOx_PDI_PDI_POS)         // GPIOx_PDI_PDI位掩码
#define GPIOx_PDI_PDI(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << GPIOx_PDI_PDI_POS) // [15:0] GPIO x输入数据

/* GPIOx_PDO ( x = 0,1,2,3) */
#define GPIOx_PDO_PDO_MAX  ((uint32_t)0xFFFF)                                        // GPIOx_PDO_PDO最大值
#define GPIOx_PDO_PDO_POS  0                                                         // GPIOx_PDO_PDO起始位
#define GPIOx_PDO_PDO_MASK (uint32_t)((uint32_t)0xFFFF << GPIOx_PDO_PDO_POS)         // GPIOx_PDO_PDO位掩码
#define GPIOx_PDO_PDO(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << GPIOx_PDO_PDO_POS) // [15:0] GPIO x输出数据

/* GPIOx_PUE ( x = 0,1,2,3) */
#define GPIOx_PUE_PUE15_BIT BIT15 // [15] GPIO x[15]/ Px[15]上拉使能
#define GPIOx_PUE_PUE14_BIT BIT14 // [14] GPIO x[14]/ Px[14]上拉使能
#define GPIOx_PUE_PUE13_BIT BIT13 // [13] GPIO x[13]/ Px[13]上拉使能
#define GPIOx_PUE_PUE12_BIT BIT12 // [12] GPIO x[12]/ Px[12]上拉使能
#define GPIOx_PUE_PUE11_BIT BIT11 // [11] GPIO x[11]/ Px[11]上拉使能
#define GPIOx_PUE_PUE10_BIT BIT10 // [10] GPIO x[10]/ Px[10]上拉使能
#define GPIOx_PUE_PUE9_BIT  BIT9  // [9] GPIO x[9]/ Px[9]上拉使能
#define GPIOx_PUE_PUE8_BIT  BIT8  // [8] GPIO x[8]/ Px[8]上拉使能
#define GPIOx_PUE_PUE7_BIT  BIT7  // [7] GPIO x[7]/ Px[7]上拉使能
#define GPIOx_PUE_PUE6_BIT  BIT6  // [6] GPIO x[6]/ Px[6]上拉使能
#define GPIOx_PUE_PUE5_BIT  BIT5  // [5] GPIO x[5]/ Px[5]上拉使能
#define GPIOx_PUE_PUE4_BIT  BIT4  // [4] GPIO x[4]/ Px[4]上拉使能
#define GPIOx_PUE_PUE3_BIT  BIT3  // [3] GPIO x[3]/ Px[3]上拉使能
#define GPIOx_PUE_PUE2_BIT  BIT2  // [2] GPIO x[2]/ Px[2]上拉使能
#define GPIOx_PUE_PUE1_BIT  BIT1  // [1] GPIO x[1]/ Px[1]上拉使能
#define GPIOx_PUE_PUE0_BIT  BIT0  // [0] GPIO x[0]/ Px[0]上拉使能

/* GPIOx_PODE ( x = 0,1,2,3) */
#define GPIOx_PODE_PODE15_BIT BIT15 // [15] GPIO x[15]/ Px[15]开漏使能
#define GPIOx_PODE_PODE14_BIT BIT14 // [14] GPIO x[14]/ Px[14]开漏使能
#define GPIOx_PODE_PODE13_BIT BIT13 // [13] GPIO x[13]/ Px[13]开漏使能
#define GPIOx_PODE_PODE12_BIT BIT12 // [12] GPIO x[12]/ Px[12]开漏使能
#define GPIOx_PODE_PODE11_BIT BIT11 // [11] GPIO x[11]/ Px[11]开漏使能
#define GPIOx_PODE_PODE10_BIT BIT10 // [10] GPIO x[10]/ Px[10]开漏使能
#define GPIOx_PODE_PODE9_BIT  BIT9  // [9] GPIO x[9]/ Px[9]开漏使能
#define GPIOx_PODE_PODE8_BIT  BIT8  // [8] GPIO x[8]/ Px[8]开漏使能
#define GPIOx_PODE_PODE7_BIT  BIT7  // [7] GPIO x[7]/ Px[7]开漏使能
#define GPIOx_PODE_PODE6_BIT  BIT6  // [6] GPIO x[6]/ Px[6]开漏使能
#define GPIOx_PODE_PODE5_BIT  BIT5  // [5] GPIO x[5]/ Px[5]开漏使能
#define GPIOx_PODE_PODE4_BIT  BIT4  // [4] GPIO x[4]/ Px[4]开漏使能
#define GPIOx_PODE_PODE3_BIT  BIT3  // [3] GPIO x[3]/ Px[3]开漏使能
#define GPIOx_PODE_PODE2_BIT  BIT2  // [2] GPIO x[2]/ Px[2]开漏使能
#define GPIOx_PODE_PODE1_BIT  BIT1  // [1] GPIO x[1]/ Px[1]开漏使能
#define GPIOx_PODE_PODE0_BIT  BIT0  // [0] GPIO x[0]/ Px[0]开漏使能

/* GPIOx_PFLT ( x = 0,1,2,3) */
#define GPIOx_PFLT_PFLT15_BIT BIT15 // [15] GPIO x[15]/ Px[15]滤波使能
#define GPIOx_PFLT_PFLT14_BIT BIT14 // [14] GPIO x[14]/ Px[14]滤波使能
#define GPIOx_PFLT_PFLT13_BIT BIT13 // [13] GPIO x[13]/ Px[13]滤波使能
#define GPIOx_PFLT_PFLT12_BIT BIT12 // [12] GPIO x[12]/ Px[12]滤波使能
#define GPIOx_PFLT_PFLT11_BIT BIT11 // [11] GPIO x[11]/ Px[11]滤波使能
#define GPIOx_PFLT_PFLT10_BIT BIT10 // [10] GPIO x[10]/ Px[10]滤波使能
#define GPIOx_PFLT_PFLT9_BIT  BIT9  // [9] GPIO x[9]/ Px[9]滤波使能
#define GPIOx_PFLT_PFLT8_BIT  BIT8  // [8] GPIO x[8]/ Px[8]滤波使能
#define GPIOx_PFLT_PFLT7_BIT  BIT7  // [7] GPIO x[7]/ Px[7]滤波使能
#define GPIOx_PFLT_PFLT6_BIT  BIT6  // [6] GPIO x[6]/ Px[6]滤波使能
#define GPIOx_PFLT_PFLT5_BIT  BIT5  // [5] GPIO x[5]/ Px[5]滤波使能
#define GPIOx_PFLT_PFLT4_BIT  BIT4  // [4] GPIO x[4]/ Px[4]滤波使能
#define GPIOx_PFLT_PFLT3_BIT  BIT3  // [3] GPIO x[3]/ Px[3]滤波使能
#define GPIOx_PFLT_PFLT2_BIT  BIT2  // [2] GPIO x[2]/ Px[2]滤波使能
#define GPIOx_PFLT_PFLT1_BIT  BIT1  // [1] GPIO x[1]/ Px[1]滤波使能
#define GPIOx_PFLT_PFLT0_BIT  BIT0  // [0] GPIO x[0]/ Px[0]滤波使能

/* GPIOx_F3210 ( x = 0,1,2,3) */
#define GPIOx_F3210_F3_MAX  ((uint32_t)0xF)                                         // GPIOx_F3210_F3最大值
#define GPIOx_F3210_F3_POS  12                                                      // GPIOx_F3210_F3起始位
#define GPIOx_F3210_F3_MASK (uint32_t)((uint32_t)0xF << GPIOx_F3210_F3_POS)         // GPIOx_F3210_F3位掩码
#define GPIOx_F3210_F3(x)   (uint32_t)((uint32_t)((x) & 0xF) << GPIOx_F3210_F3_POS) // [15:12] GPIO x[3]/ Px[3]功能选择
#define GPIOx_F3210_F2_MAX  ((uint32_t)0xF)                                         // GPIOx_F3210_F2最大值
#define GPIOx_F3210_F2_POS  8                                                       // GPIOx_F3210_F2起始位
#define GPIOx_F3210_F2_MASK (uint32_t)((uint32_t)0xF << GPIOx_F3210_F2_POS)         // GPIOx_F3210_F2位掩码
#define GPIOx_F3210_F2(x)   (uint32_t)((uint32_t)((x) & 0xF) << GPIOx_F3210_F2_POS) // [11:8] GPIO x[2]/ Px[2]功能选择
#define GPIOx_F3210_F1_MAX  ((uint32_t)0xF)                                         // GPIOx_F3210_F1最大值
#define GPIOx_F3210_F1_POS  4                                                       // GPIOx_F3210_F1起始位
#define GPIOx_F3210_F1_MASK (uint32_t)((uint32_t)0xF << GPIOx_F3210_F1_POS)         // GPIOx_F3210_F1位掩码
#define GPIOx_F3210_F1(x)   (uint32_t)((uint32_t)((x) & 0xF) << GPIOx_F3210_F1_POS) // [7:4] GPIO x[1]/ Px[1]功能选择
#define GPIOx_F3210_F0_MAX  ((uint32_t)0xF)                                         // GPIOx_F3210_F0最大值
#define GPIOx_F3210_F0_POS  0                                                       // GPIOx_F3210_F0起始位
#define GPIOx_F3210_F0_MASK (uint32_t)((uint32_t)0xF << GPIOx_F3210_F0_POS)         // GPIOx_F3210_F0位掩码
#define GPIOx_F3210_F0(x)   (uint32_t)((uint32_t)((x) & 0xF) << GPIOx_F3210_F0_POS) // [3:0] GPIO x[0]/ Px[0]功能选择

/* GPIOx_F7654 ( x = 0,1,2,3) */
#define GPIOx_F7654_F7_MAX  ((uint32_t)0xF)                                         // GPIOx_F7654_F7最大值
#define GPIOx_F7654_F7_POS  12                                                      // GPIOx_F7654_F7起始位
#define GPIOx_F7654_F7_MASK (uint32_t)((uint32_t)0xF << GPIOx_F7654_F7_POS)         // GPIOx_F7654_F7位掩码
#define GPIOx_F7654_F7(x)   (uint32_t)((uint32_t)((x) & 0xF) << GPIOx_F7654_F7_POS) // [15:12] GPIO x[7]/ Px[7]功能选择
#define GPIOx_F7654_F6_MAX  ((uint32_t)0xF)                                         // GPIOx_F7654_F6最大值
#define GPIOx_F7654_F6_POS  8                                                       // GPIOx_F7654_F6起始位
#define GPIOx_F7654_F6_MASK (uint32_t)((uint32_t)0xF << GPIOx_F7654_F6_POS)         // GPIOx_F7654_F6位掩码
#define GPIOx_F7654_F6(x)   (uint32_t)((uint32_t)((x) & 0xF) << GPIOx_F7654_F6_POS) // [11:8] GPIO x[6]/ Px[6]功能选择
#define GPIOx_F7654_F5_MAX  ((uint32_t)0xF)                                         // GPIOx_F7654_F5最大值
#define GPIOx_F7654_F5_POS  4                                                       // GPIOx_F7654_F5起始位
#define GPIOx_F7654_F5_MASK (uint32_t)((uint32_t)0xF << GPIOx_F7654_F5_POS)         // GPIOx_F7654_F5位掩码
#define GPIOx_F7654_F5(x)   (uint32_t)((uint32_t)((x) & 0xF) << GPIOx_F7654_F5_POS) // [7:4] GPIO x[5]/ Px[5]功能选择
#define GPIOx_F7654_F4_MAX  ((uint32_t)0xF)                                         // GPIOx_F7654_F4最大值
#define GPIOx_F7654_F4_POS  0                                                       // GPIOx_F7654_F4起始位
#define GPIOx_F7654_F4_MASK (uint32_t)((uint32_t)0xF << GPIOx_F7654_F4_POS)         // GPIOx_F7654_F4位掩码
#define GPIOx_F7654_F4(x)   (uint32_t)((uint32_t)((x) & 0xF) << GPIOx_F7654_F4_POS) // [3:0] GPIO x[4]/ Px[4]功能选择

/* GPIOx_FBA98 ( x = 0,1,2,3) */
#define GPIOx_FBA98_F11_MAX  ((uint32_t)0xF)                                          // GPIOx_FBA98_F11最大值
#define GPIOx_FBA98_F11_POS  12                                                       // GPIOx_FBA98_F11起始位
#define GPIOx_FBA98_F11_MASK (uint32_t)((uint32_t)0xF << GPIOx_FBA98_F11_POS)         // GPIOx_FBA98_F11位掩码
#define GPIOx_FBA98_F11(x)   (uint32_t)((uint32_t)((x) & 0xF) << GPIOx_FBA98_F11_POS) // [15:12] GPIO x[11]/ Px[11]功能选择
#define GPIOx_FBA98_F10_MAX  ((uint32_t)0xF)                                          // GPIOx_FBA98_F10最大值
#define GPIOx_FBA98_F10_POS  8                                                        // GPIOx_FBA98_F10起始位
#define GPIOx_FBA98_F10_MASK (uint32_t)((uint32_t)0xF << GPIOx_FBA98_F10_POS)         // GPIOx_FBA98_F10位掩码
#define GPIOx_FBA98_F10(x)   (uint32_t)((uint32_t)((x) & 0xF) << GPIOx_FBA98_F10_POS) // [11:8] GPIO x[10]/ Px[10]功能选择
#define GPIOx_FBA98_F9_MAX   ((uint32_t)0xF)                                          // GPIOx_FBA98_F9最大值
#define GPIOx_FBA98_F9_POS   4                                                        // GPIOx_FBA98_F9起始位
#define GPIOx_FBA98_F9_MASK  (uint32_t)((uint32_t)0xF << GPIOx_FBA98_F9_POS)          // GPIOx_FBA98_F9位掩码
#define GPIOx_FBA98_F9(x)    (uint32_t)((uint32_t)((x) & 0xF) << GPIOx_FBA98_F9_POS)  // [7:4] GPIO x[9]/ Px[9]功能选择
#define GPIOx_FBA98_F8_MAX   ((uint32_t)0xF)                                          // GPIOx_FBA98_F8最大值
#define GPIOx_FBA98_F8_POS   0                                                        // GPIOx_FBA98_F8起始位
#define GPIOx_FBA98_F8_MASK  (uint32_t)((uint32_t)0xF << GPIOx_FBA98_F8_POS)          // GPIOx_FBA98_F8位掩码
#define GPIOx_FBA98_F8(x)    (uint32_t)((uint32_t)((x) & 0xF) << GPIOx_FBA98_F8_POS)  // [3:0] GPIO x[8]/ Px[8]功能选择

/* GPIOx_FFEDC ( x = 0,1,2,3) */
#define GPIOx_FFEDC_F15_MAX  ((uint32_t)0xF)                                          // GPIOx_FFEDC_F15最大值
#define GPIOx_FFEDC_F15_POS  12                                                       // GPIOx_FFEDC_F15起始位
#define GPIOx_FFEDC_F15_MASK (uint32_t)((uint32_t)0xF << GPIOx_FFEDC_F15_POS)         // GPIOx_FFEDC_F15位掩码
#define GPIOx_FFEDC_F15(x)   (uint32_t)((uint32_t)((x) & 0xF) << GPIOx_FFEDC_F15_POS) // [15:12] GPIO x[15]/ Px[15]功能选择
#define GPIOx_FFEDC_F14_MAX  ((uint32_t)0xF)                                          // GPIOx_FFEDC_F14最大值
#define GPIOx_FFEDC_F14_POS  8                                                        // GPIOx_FFEDC_F14起始位
#define GPIOx_FFEDC_F14_MASK (uint32_t)((uint32_t)0xF << GPIOx_FFEDC_F14_POS)         // GPIOx_FFEDC_F14位掩码
#define GPIOx_FFEDC_F14(x)   (uint32_t)((uint32_t)((x) & 0xF) << GPIOx_FFEDC_F14_POS) // [11:8] GPIO x[14]/ Px[14]功能选择
#define GPIOx_FFEDC_F13_MAX  ((uint32_t)0xF)                                          // GPIOx_FFEDC_F13最大值
#define GPIOx_FFEDC_F13_POS  4                                                        // GPIOx_FFEDC_F13起始位
#define GPIOx_FFEDC_F13_MASK (uint32_t)((uint32_t)0xF << GPIOx_FFEDC_F13_POS)         // GPIOx_FFEDC_F13位掩码
#define GPIOx_FFEDC_F13(x)   (uint32_t)((uint32_t)((x) & 0xF) << GPIOx_FFEDC_F13_POS) // [7:4] GPIO x[13]/ Px[13]功能选择
#define GPIOx_FFEDC_F12_MAX  ((uint32_t)0xF)                                          // GPIOx_FFEDC_F12最大值
#define GPIOx_FFEDC_F12_POS  0                                                        // GPIOx_FFEDC_F12起始位
#define GPIOx_FFEDC_F12_MASK (uint32_t)((uint32_t)0xF << GPIOx_FFEDC_F12_POS)         // GPIOx_FFEDC_F12位掩码
#define GPIOx_FFEDC_F12(x)   (uint32_t)((uint32_t)((x) & 0xF) << GPIOx_FFEDC_F12_POS) // [3:0] GPIO x[12]/ Px[12]功能选择

/* GPIOx_BSRR ( x = 0,1,2,3) */
#define GPIOx_BSRR_CLR15_BIT BIT31 // [31] 写1将GPIO x[15]清零，写0无作用
#define GPIOx_BSRR_CLR14_BIT BIT30 // [30] 写1将GPIO x[14]清零，写0无作用
#define GPIOx_BSRR_CLR13_BIT BIT29 // [29] 写1将GPIO x[13]清零，写0无作用
#define GPIOx_BSRR_CLR12_BIT BIT28 // [28] 写1将GPIO x[12]清零，写0无作用
#define GPIOx_BSRR_CLR11_BIT BIT27 // [27] 写1将GPIO x[11]清零，写0无作用
#define GPIOx_BSRR_CLR10_BIT BIT26 // [26] 写1将GPIO x[10]清零，写0无作用
#define GPIOx_BSRR_CLR9_BIT  BIT25 // [25] 写1将GPIO x[9]清零，写0无作用
#define GPIOx_BSRR_CLR8_BIT  BIT24 // [24] 写1将GPIO x[8]清零，写0无作用
#define GPIOx_BSRR_CLR7_BIT  BIT23 // [23] 写1将GPIO x[7]清零，写0无作用
#define GPIOx_BSRR_CLR6_BIT  BIT22 // [22] 写1将GPIO x[6]清零，写0无作用
#define GPIOx_BSRR_CLR5_BIT  BIT21 // [21] 写1将GPIO x[5]清零，写0无作用
#define GPIOx_BSRR_CLR4_BIT  BIT20 // [20] 写1将GPIO x[4]清零，写0无作用
#define GPIOx_BSRR_CLR3_BIT  BIT19 // [19] 写1将GPIO x[3]清零，写0无作用
#define GPIOx_BSRR_CLR2_BIT  BIT18 // [18] 写1将GPIO x[2]清零，写0无作用
#define GPIOx_BSRR_CLR1_BIT  BIT17 // [17] 写1将GPIO x[1]清零，写0无作用
#define GPIOx_BSRR_CLR0_BIT  BIT16 // [16] 写1将GPIO x[0]清零，写0无作用
#define GPIOx_BSRR_SET15_BIT BIT15 // [15] 写1将GPIO x[15]置1，写0无作用
#define GPIOx_BSRR_SET14_BIT BIT14 // [14] 写1将GPIO x[14]置1，写0无作用
#define GPIOx_BSRR_SET13_BIT BIT13 // [13] 写1将GPIO x[13]置1，写0无作用
#define GPIOx_BSRR_SET12_BIT BIT12 // [12] 写1将GPIO x[12]置1，写0无作用
#define GPIOx_BSRR_SET11_BIT BIT11 // [11] 写1将GPIO x[11]置1，写0无作用
#define GPIOx_BSRR_SET10_BIT BIT10 // [10] 写1将GPIO x[10]置1，写0无作用
#define GPIOx_BSRR_SET9_BIT  BIT9  // [9] 写1将GPIO x[9]置1，写0无作用
#define GPIOx_BSRR_SET8_BIT  BIT8  // [8] 写1将GPIO x[8]置1，写0无作用
#define GPIOx_BSRR_SET7_BIT  BIT7  // [7] 写1将GPIO x[7]置1，写0无作用
#define GPIOx_BSRR_SET6_BIT  BIT6  // [6] 写1将GPIO x[6]置1，写0无作用
#define GPIOx_BSRR_SET5_BIT  BIT5  // [5] 写1将GPIO x[5]置1，写0无作用
#define GPIOx_BSRR_SET4_BIT  BIT4  // [4] 写1将GPIO x[4]置1，写0无作用
#define GPIOx_BSRR_SET3_BIT  BIT3  // [3] 写1将GPIO x[3]置1，写0无作用
#define GPIOx_BSRR_SET2_BIT  BIT2  // [2] 写1将GPIO x[2]置1，写0无作用
#define GPIOx_BSRR_SET1_BIT  BIT1  // [1] 写1将GPIO x[1]置1，写0无作用
#define GPIOx_BSRR_SET0_BIT  BIT0  // [0] 写1将GPIO x[0]置1，写0无作用

/* GPIOx_BRR ( x = 0,1,2,3) */
#define GPIOx_BRR_CLR15_BIT BIT15 // [15] 写1将GPIO x[15]清零，写0无作用
#define GPIOx_BRR_CLR14_BIT BIT14 // [14] 写1将GPIO x[14]清零，写0无作用
#define GPIOx_BRR_CLR13_BIT BIT13 // [13] 写1将GPIO x[13]清零，写0无作用
#define GPIOx_BRR_CLR12_BIT BIT12 // [12] 写1将GPIO x[12]清零，写0无作用
#define GPIOx_BRR_CLR11_BIT BIT11 // [11] 写1将GPIO x[11]清零，写0无作用
#define GPIOx_BRR_CLR10_BIT BIT10 // [10] 写1将GPIO x[10]清零，写0无作用
#define GPIOx_BRR_CLR9_BIT  BIT9  // [9] 写1将GPIO x[9]清零，写0无作用
#define GPIOx_BRR_CLR8_BIT  BIT8  // [8] 写1将GPIO x[8]清零，写0无作用
#define GPIOx_BRR_CLR7_BIT  BIT7  // [7] 写1将GPIO x[7]清零，写0无作用
#define GPIOx_BRR_CLR6_BIT  BIT6  // [6] 写1将GPIO x[6]清零，写0无作用
#define GPIOx_BRR_CLR5_BIT  BIT5  // [5] 写1将GPIO x[5]清零，写0无作用
#define GPIOx_BRR_CLR4_BIT  BIT4  // [4] 写1将GPIO x[4]清零，写0无作用
#define GPIOx_BRR_CLR3_BIT  BIT3  // [3] 写1将GPIO x[3]清零，写0无作用
#define GPIOx_BRR_CLR2_BIT  BIT2  // [2] 写1将GPIO x[2]清零，写0无作用
#define GPIOx_BRR_CLR1_BIT  BIT1  // [1] 写1将GPIO x[1]清零，写0无作用
#define GPIOx_BRR_CLR0_BIT  BIT0  // [0] 写1将GPIO x[0]清零，写0无作用

/* EXTI_CR0 */
#define EXTI_CR0_T7_MAX  ((uint32_t)0x3)                                      // EXTI_CR0_T7最大值
#define EXTI_CR0_T7_POS  14                                                   // EXTI_CR0_T7起始位
#define EXTI_CR0_T7_MASK (uint32_t)((uint32_t)0x3 << EXTI_CR0_T7_POS)         // EXTI_CR0_T7位掩码
#define EXTI_CR0_T7(x)   (uint32_t)((uint32_t)((x) & 0x3) << EXTI_CR0_T7_POS) // [15:14] GPIO 0[15]/ P0[15]外部触发类型选择00:不触发01:下降沿触发10:上升沿触发11:上升沿、下降沿均触发
#define EXTI_CR0_T6_MAX  ((uint32_t)0x3)                                      // EXTI_CR0_T6最大值
#define EXTI_CR0_T6_POS  12                                                   // EXTI_CR0_T6起始位
#define EXTI_CR0_T6_MASK (uint32_t)((uint32_t)0x3 << EXTI_CR0_T6_POS)         // EXTI_CR0_T6位掩码
#define EXTI_CR0_T6(x)   (uint32_t)((uint32_t)((x) & 0x3) << EXTI_CR0_T6_POS) // [13:12] GPIO 0[14]/ P0[14]外部触发类型选择00:不触发01:下降沿触发10:上升沿触发11:上升沿、下降沿均触发
#define EXTI_CR0_T5_MAX  ((uint32_t)0x3)                                      // EXTI_CR0_T5最大值
#define EXTI_CR0_T5_POS  10                                                   // EXTI_CR0_T5起始位
#define EXTI_CR0_T5_MASK (uint32_t)((uint32_t)0x3 << EXTI_CR0_T5_POS)         // EXTI_CR0_T5位掩码
#define EXTI_CR0_T5(x)   (uint32_t)((uint32_t)((x) & 0x3) << EXTI_CR0_T5_POS) // [11:10] GPIO 0[11]/ P0[11]外部触发类型选择00:不触发01:下降沿触发10:上升沿触发11:上升沿、下降沿均触发
#define EXTI_CR0_T4_MAX  ((uint32_t)0x3)                                      // EXTI_CR0_T4最大值
#define EXTI_CR0_T4_POS  8                                                    // EXTI_CR0_T4起始位
#define EXTI_CR0_T4_MASK (uint32_t)((uint32_t)0x3 << EXTI_CR0_T4_POS)         // EXTI_CR0_T4位掩码
#define EXTI_CR0_T4(x)   (uint32_t)((uint32_t)((x) & 0x3) << EXTI_CR0_T4_POS) // [9:8] GPIO 0[6]/ P0[6]外部触发类型选择00:不触发01:下降沿触发10:上升沿触发11:上升沿、下降沿均触发
#define EXTI_CR0_T3_MAX  ((uint32_t)0x3)                                      // EXTI_CR0_T3最大值
#define EXTI_CR0_T3_POS  6                                                    // EXTI_CR0_T3起始位
#define EXTI_CR0_T3_MASK (uint32_t)((uint32_t)0x3 << EXTI_CR0_T3_POS)         // EXTI_CR0_T3位掩码
#define EXTI_CR0_T3(x)   (uint32_t)((uint32_t)((x) & 0x3) << EXTI_CR0_T3_POS) // [7:6] GPIO 0[3]/ P0[3]外部触发类型选择00:不触发01:下降沿触发10:上升沿触发11:上升沿、下降沿均触发
#define EXTI_CR0_T2_MAX  ((uint32_t)0x3)                                      // EXTI_CR0_T2最大值
#define EXTI_CR0_T2_POS  4                                                    // EXTI_CR0_T2起始位
#define EXTI_CR0_T2_MASK (uint32_t)((uint32_t)0x3 << EXTI_CR0_T2_POS)         // EXTI_CR0_T2位掩码
#define EXTI_CR0_T2(x)   (uint32_t)((uint32_t)((x) & 0x3) << EXTI_CR0_T2_POS) // [5:4] GPIO 0[2]/ P0[2]外部触发类型选择00:不触发01:下降沿触发10:上升沿触发11:上升沿、下降沿均触发
#define EXTI_CR0_T1_MAX  ((uint32_t)0x3)                                      // EXTI_CR0_T1最大值
#define EXTI_CR0_T1_POS  2                                                    // EXTI_CR0_T1起始位
#define EXTI_CR0_T1_MASK (uint32_t)((uint32_t)0x3 << EXTI_CR0_T1_POS)         // EXTI_CR0_T1位掩码
#define EXTI_CR0_T1(x)   (uint32_t)((uint32_t)((x) & 0x3) << EXTI_CR0_T1_POS) // [3:2] GPIO 0[1]/ P0[1]外部触发类型选择00:不触发01:下降沿触发10:上升沿触发11:上升沿、下降沿均触发
#define EXTI_CR0_T0_MAX  ((uint32_t)0x3)                                      // EXTI_CR0_T0最大值
#define EXTI_CR0_T0_POS  0                                                    // EXTI_CR0_T0起始位
#define EXTI_CR0_T0_MASK (uint32_t)((uint32_t)0x3 << EXTI_CR0_T0_POS)         // EXTI_CR0_T0位掩码
#define EXTI_CR0_T0(x)   (uint32_t)((uint32_t)((x) & 0x3) << EXTI_CR0_T0_POS) // [1:0] GPIO 0[0]/ P0[0]外部触发类型选择00:不触发01:下降沿触发10:上升沿触发11:上升沿、下降沿均触发

/* EXTI_CR1 */
#define EXTI_CR1_T15_MAX  ((uint32_t)0x3)                                       // EXTI_CR1_T15最大值
#define EXTI_CR1_T15_POS  14                                                    // EXTI_CR1_T15起始位
#define EXTI_CR1_T15_MASK (uint32_t)((uint32_t)0x3 << EXTI_CR1_T15_POS)         // EXTI_CR1_T15位掩码
#define EXTI_CR1_T15(x)   (uint32_t)((uint32_t)((x) & 0x3) << EXTI_CR1_T15_POS) // [15:14] GPIO 2[15]/P2[15]外部触发类型选择00:不触发01:下降沿触发10:上升沿触发11:上升沿、下降沿均触发
#define EXTI_CR1_T14_MAX  ((uint32_t)0x3)                                       // EXTI_CR1_T14最大值
#define EXTI_CR1_T14_POS  12                                                    // EXTI_CR1_T14起始位
#define EXTI_CR1_T14_MASK (uint32_t)((uint32_t)0x3 << EXTI_CR1_T14_POS)         // EXTI_CR1_T14位掩码
#define EXTI_CR1_T14(x)   (uint32_t)((uint32_t)((x) & 0x3) << EXTI_CR1_T14_POS) // [13:12] GPIO 2[12]/P2[12]外部触发类型选择00:不触发01:下降沿触发10:上升沿触发11:上升沿、下降沿均触发
#define EXTI_CR1_T13_MAX  ((uint32_t)0x3)                                       // EXTI_CR1_T13最大值
#define EXTI_CR1_T13_POS  10                                                    // EXTI_CR1_T13起始位
#define EXTI_CR1_T13_MASK (uint32_t)((uint32_t)0x3 << EXTI_CR1_T13_POS)         // EXTI_CR1_T13位掩码
#define EXTI_CR1_T13(x)   (uint32_t)((uint32_t)((x) & 0x3) << EXTI_CR1_T13_POS) // [11:10] GPIO 2[7]/P2[7]外部触发类型选择00:不触发01:下降沿触发10:上升沿触发11:上升沿、下降沿均触发
#define EXTI_CR1_T12_MAX  ((uint32_t)0x3)                                       // EXTI_CR1_T12最大值
#define EXTI_CR1_T12_POS  8                                                     // EXTI_CR1_T12起始位
#define EXTI_CR1_T12_MASK (uint32_t)((uint32_t)0x3 << EXTI_CR1_T12_POS)         // EXTI_CR1_T12位掩码
#define EXTI_CR1_T12(x)   (uint32_t)((uint32_t)((x) & 0x3) << EXTI_CR1_T12_POS) // [9:8] GPIO 2[4]/P2[4]外部触发类型选择00:不触发01:下降沿触发10:上升沿触发11:上升沿、下降沿均触发
#define EXTI_CR1_T11_MAX  ((uint32_t)0x3)                                       // EXTI_CR1_T11最大值
#define EXTI_CR1_T11_POS  6                                                     // EXTI_CR1_T11起始位
#define EXTI_CR1_T11_MASK (uint32_t)((uint32_t)0x3 << EXTI_CR1_T11_POS)         // EXTI_CR1_T11位掩码
#define EXTI_CR1_T11(x)   (uint32_t)((uint32_t)((x) & 0x3) << EXTI_CR1_T11_POS) // [7:6] GPIO 2[3]/P2[3]外部触发类型选择00:不触发01:下降沿触发10:上升沿触发11:上升沿、下降沿均触发
#define EXTI_CR1_T10_MAX  ((uint32_t)0x3)                                       // EXTI_CR1_T10最大值
#define EXTI_CR1_T10_POS  4                                                     // EXTI_CR1_T10起始位
#define EXTI_CR1_T10_MASK (uint32_t)((uint32_t)0x3 << EXTI_CR1_T10_POS)         // EXTI_CR1_T10位掩码
#define EXTI_CR1_T10(x)   (uint32_t)((uint32_t)((x) & 0x3) << EXTI_CR1_T10_POS) // [5:4] GPIO 1[10]/P1[10]外部触发类型选择00:不触发01:下降沿触发10:上升沿触发11:上升沿、下降沿均触发
#define EXTI_CR1_T9_MAX   ((uint32_t)0x3)                                       // EXTI_CR1_T9最大值
#define EXTI_CR1_T9_POS   2                                                     // EXTI_CR1_T9起始位
#define EXTI_CR1_T9_MASK  (uint32_t)((uint32_t)0x3 << EXTI_CR1_T9_POS)          // EXTI_CR1_T9位掩码
#define EXTI_CR1_T9(x)    (uint32_t)((uint32_t)((x) & 0x3) << EXTI_CR1_T9_POS)  // [3:2] GPIO 1[1]/P1[1]外部触发类型选择00:不触发01:下降沿触发10:上升沿触发11:上升沿、下降沿均触发
#define EXTI_CR1_T8_MAX   ((uint32_t)0x3)                                       // EXTI_CR1_T8最大值
#define EXTI_CR1_T8_POS   0                                                     // EXTI_CR1_T8起始位
#define EXTI_CR1_T8_MASK  (uint32_t)((uint32_t)0x3 << EXTI_CR1_T8_POS)          // EXTI_CR1_T8位掩码
#define EXTI_CR1_T8(x)    (uint32_t)((uint32_t)((x) & 0x3) << EXTI_CR1_T8_POS)  // [1:0] GPIO 1[0]/P1[0]外部触发类型选择00:不触发01:下降沿触发10:上升沿触发11:上升沿、下降沿均触发

/* EXTI_IE */
#define EXTI_IE_EXTI2_RE_BIT BIT10 // [10] GPIO2 DMA 请求使能，需要配合EXTI_CR0/1使用
#define EXTI_IE_EXTI1_RE_BIT BIT9  // [9] GPIO1 DMA 请求使能，需要配合EXTI_CR0/1使用
#define EXTI_IE_EXTI0_RE_BIT BIT8  // [8] GPIO0 DMA 请求使能，需要配合EXTI_CR0/1使用
#define EXTI_IE_EXTI2_IE_BIT BIT2  // [2] GPIO2中断使能，需要配合EXTI_CR0/1使用
#define EXTI_IE_EXTI1_IE_BIT BIT1  // [1] GPIO1中断使能，需要配合EXTI_CR0/1使用
#define EXTI_IE_EXTI0_IE_BIT BIT0  // [0] GPIO0中断使能，需要配合EXTI_CR0/1使用

/* EXTI_IF */
#define EXTI_IF_IF15_BIT BIT15 // [15] GPIO 2[15]/ P2[15]外部中断标志。中断标志高有效，写1清零
#define EXTI_IF_IF14_BIT BIT14 // [14] GPIO 2[12]/ P2[12]外部中断标志。中断标志高有效，写1清零
#define EXTI_IF_IF13_BIT BIT13 // [13] GPIO 2[7]/ P2[7]外部中断标志。中断标志高有效，写1清零
#define EXTI_IF_IF12_BIT BIT12 // [12] GPIO 2[4]/ P2[4]外部中断标志。中断标志高有效，写1清零
#define EXTI_IF_IF11_BIT BIT11 // [11] GPIO 2[3]/ P2[3]外部中断标志。中断标志高有效，写1清零
#define EXTI_IF_IF10_BIT BIT10 // [10] GPIO 1[10]/ P1[10]外部中断标志。中断标志高有效，写1清零
#define EXTI_IF_IF9_BIT  BIT9  // [9] GPIO 1[1]/ P1[1]外部中断标志。中断标志高有效，写1清零
#define EXTI_IF_IF8_BIT  BIT8  // [8] GPIO 1[0]/ P1[0]外部中断标志。中断标志高有效，写1清零
#define EXTI_IF_IF7_BIT  BIT7  // [7] GPIO 0[15]/ P0[15]外部中断标志。中断标志高有效，写1清零
#define EXTI_IF_IF6_BIT  BIT6  // [6] GPIO 0[14]/ P0[14]外部中断标志。中断标志高有效，写1清零
#define EXTI_IF_IF5_BIT  BIT5  // [5] GPIO 0[11]/ P0[11]外部中断标志。中断标志高有效，写1清零
#define EXTI_IF_IF4_BIT  BIT4  // [4] GPIO 0[6]/ P0[6]外部中断标志。中断标志高有效，写1清零
#define EXTI_IF_IF3_BIT  BIT3  // [3] GPIO 0[3]/ P0[3]外部中断标志。中断标志高有效，写1清零
#define EXTI_IF_IF2_BIT  BIT2  // [2] GPIO 0[2]/ P0[2]外部中断标志。中断标志高有效，写1清零
#define EXTI_IF_IF1_BIT  BIT1  // [1] GPIO 0[1]/ P0[1]外部中断标志。中断标志高有效，写1清零
#define EXTI_IF_IF0_BIT  BIT0  // [0] GPIO 0[0]/ P0[0]外部中断标志。中断标志高有效，写1清零

/* CLKO_SEL */
#define CLKO_SEL_HSE_OE_BIT BIT4 // [4] 晶振时钟输出使能。1:使能；0:禁用。
#define CLKO_SEL_ADC_OE_BIT BIT3 // [3] ADC时钟输出使能。1:使能；0:禁用。
#define CLKO_SEL_PLL_OE_BIT BIT2 // [2] PLL输出使能。1:使能；0:禁用。
#define CLKO_SEL_HSI_OE_BIT BIT1 // [1] HRC输出使能。1:使能；0:禁用。
#define CLKO_SEL_LSI_OE_BIT BIT0 // [0] LRC输出使能。1:使能；0:禁用。

/* PWM_SWAP */
#define PWM_SWAP_SWAP_MAX  ((uint32_t)0x3)                                        // PWM_SWAP_SWAP最大值
#define PWM_SWAP_SWAP_POS  0                                                      // PWM_SWAP_SWAP起始位
#define PWM_SWAP_SWAP_MASK (uint32_t)((uint32_t)0x3 << PWM_SWAP_SWAP_POS)         // PWM_SWAP_SWAP位掩码
#define PWM_SWAP_SWAP(x)   (uint32_t)((uint32_t)((x) & 0x3) << PWM_SWAP_SWAP_POS) // [1:0] 向此寄存器写入0x67可将BIT[1:0]写为1，写入0x69可将BIT[1:0]写为2，写其他值则将BIT[1:0]写为0

/* CRC0_DR CRC 信息码寄存器 */
#define CRC0_DR_DR_MAX  ((uint32_t)0xFFFFFFFF)                                     // CRC0_DR_DR最大值
#define CRC0_DR_DR_POS  0                                                          // CRC0_DR_DR起始位
#define CRC0_DR_DR_MASK (uint32_t)((uint32_t)0xFFFFFFFF << CRC0_DR_DR_POS)         // CRC0_DR_DR位掩码
#define CRC0_DR_DR(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << CRC0_DR_DR_POS) // [31:0] 存放待编码的信息码和经CRC校验后的编码

/* CRC0_CR CRC 控制寄存器 */
#define CRC0_CR_REV_OUT_TYPE_BIT BIT12                                                        // [12] 是否将CRC校验后的编码反转后输出，即b[31]=b[0], b[30]=b[1],… [b0]=b[31]
#define CRC0_CR_REV_IN_TYPE_MAX  ((uint32_t)0x3)                                              // CRC0_CR_REV_IN_TYPE最大值
#define CRC0_CR_REV_IN_TYPE_POS  8                                                            // CRC0_CR_REV_IN_TYPE起始位
#define CRC0_CR_REV_IN_TYPE_MASK (uint32_t)((uint32_t)0x3 << CRC0_CR_REV_IN_TYPE_POS)         // CRC0_CR_REV_IN_TYPE位掩码
#define CRC0_CR_REV_IN_TYPE(x)   (uint32_t)((uint32_t)((x) & 0x3) << CRC0_CR_REV_IN_TYPE_POS) // [9:8] 待编码数据反转类型00:不反转01:按字节反转，即b[31]=b[24], b[30]=b[25], …, b[24]=b[31], …, b[7]=b[0], b[6]=b[1], …, b[0]=b[7]10:按半字（16bit）反转，即b[31]=b[16], b[30]=b[17], …, b[16]=b[31], …, b[15]=b[0], b[14]=b[1], …, b[0]=b[15]11:按字反转，即b[31]=b[0], b[30]=b[1],… [b0]=b[31]
#define CRC0_CR_POLY_SIZE_MAX    ((uint32_t)0x3)                                              // CRC0_CR_POLY_SIZE最大值
#define CRC0_CR_POLY_SIZE_POS    4                                                            // CRC0_CR_POLY_SIZE起始位
#define CRC0_CR_POLY_SIZE_MASK   (uint32_t)((uint32_t)0x3 << CRC0_CR_POLY_SIZE_POS)           // CRC0_CR_POLY_SIZE位掩码
#define CRC0_CR_POLY_SIZE(x)     (uint32_t)((uint32_t)((x) & 0x3) << CRC0_CR_POLY_SIZE_POS)   // [5:4] 输出编码（多项式）位宽00: 32bits01: 16bits10: 8bits11: 7bits
#define CRC0_CR_RESET_BIT        BIT0                                                         // [0] 与输入信息码进行CRC计算的数据来源0:来自于上一次的计算结果1:来自于CRC0_INIT写入1实现CRC数据重置并自动清零，读回恒为0.

/* CRC0_INIT CRC 初始码寄存器 */
#define CRC0_INIT_INIT_MAX  ((uint32_t)0xFFFFFFFF)                                         // CRC0_INIT_INIT最大值
#define CRC0_INIT_INIT_POS  0                                                              // CRC0_INIT_INIT起始位
#define CRC0_INIT_INIT_MASK (uint32_t)((uint32_t)0xFFFFFFFF << CRC0_INIT_INIT_POS)         // CRC0_INIT_INIT位掩码
#define CRC0_INIT_INIT(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << CRC0_INIT_INIT_POS) // [31:0] 存放初始码

/* CRC0_POL CRC 生成码寄存器 */
#define CRC0_POL_POL_MAX  ((uint32_t)0xFFFFFFFF)                                       // CRC0_POL_POL最大值
#define CRC0_POL_POL_POS  0                                                            // CRC0_POL_POL起始位
#define CRC0_POL_POL_MASK (uint32_t)((uint32_t)0xFFFFFFFF << CRC0_POL_POL_POS)         // CRC0_POL_POL位掩码
#define CRC0_POL_POL(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << CRC0_POL_POL_POS) // [31:0] 存放生成多项式对应的生成码

/* UARTx_CTRL UARTx 控制寄存器 (x = 0,1) */
#define UARTx_CTRL_DUPLEX_BIT    BIT7 // [7] 双工，默认值为0。0:全双工；1:半双工
#define UARTx_CTRL_LIN_EN_BIT    BIT6 // [6] LIN模式使能，默认值为0。0:关闭；1:开启
#define UARTx_CTRL_MD_EN_BIT     BIT5 // [5] 使能Multi-drop，默认值为0。0:关闭；1:开启
#define UARTx_CTRL_CK_EN_BIT     BIT4 // [4] 数据校验开关，默认值为0。0:关闭；1:开启
#define UARTx_CTRL_CK_TYPE_BIT   BIT3 // [3] 奇偶校验配置，默认值为0。0:偶校验（EVEN）；1: 奇校验（ODD）
#define UARTx_CTRL_BIT_ORDER_BIT BIT2 // [2] 数据发送顺序配置，默认值为0。0:LSB；1:MSB
#define UARTx_CTRL_STOP_LEN_BIT  BIT1 // [1] 停止位长度配置，默认值为0。0:1-Bit；1:2-Bit
#define UARTx_CTRL_BYTE_LEN_BIT  BIT0 // [0] 数据长度配置，默认值为0。0:8-Bit；1:9-Bit

/* UARTx_DIVH UARTx 波特率设置高字节寄存器 (x = 0,1) */
#define UARTx_DIVH_DIVH_MAX  ((uint32_t)0xFF)                                          // UARTx_DIVH_DIVH最大值
#define UARTx_DIVH_DIVH_POS  0                                                         // UARTx_DIVH_DIVH起始位
#define UARTx_DIVH_DIVH_MASK (uint32_t)((uint32_t)0xFF << UARTx_DIVH_DIVH_POS)         // UARTx_DIVH_DIVH位掩码
#define UARTx_DIVH_DIVH(x)   (uint32_t)((uint32_t)((x) & 0xFF) << UARTx_DIVH_DIVH_POS) // [7:0] 波特率设置高字节BAUDRATE =主时钟/(1+256\* UART_DIVH+UART_DIVL)

/* UARTx_DIVL UARTx 波特率设置低字节寄存器 (x = 0,1) */
#define UARTx_DIVL_DIVL_MAX  ((uint32_t)0xFF)                                          // UARTx_DIVL_DIVL最大值
#define UARTx_DIVL_DIVL_POS  0                                                         // UARTx_DIVL_DIVL起始位
#define UARTx_DIVL_DIVL_MASK (uint32_t)((uint32_t)0xFF << UARTx_DIVL_DIVL_POS)         // UARTx_DIVL_DIVL位掩码
#define UARTx_DIVL_DIVL(x)   (uint32_t)((uint32_t)((x) & 0xFF) << UARTx_DIVL_DIVL_POS) // [7:0] 波特率设置低字节BAUDRATE =主时钟/(1+256\* UART_DIVH+UART_DIVL)

/* UARTx_BUFF UARTx 收发缓冲寄存器 (x = 0,1) */
#define UARTx_BUFF_BUFF_MAX  ((uint32_t)0x1FF)                                          // UARTx_BUFF_BUFF最大值
#define UARTx_BUFF_BUFF_POS  0                                                          // UARTx_BUFF_BUFF起始位
#define UARTx_BUFF_BUFF_MASK (uint32_t)((uint32_t)0x1FF << UARTx_BUFF_BUFF_POS)         // UARTx_BUFF_BUFF位掩码
#define UARTx_BUFF_BUFF(x)   (uint32_t)((uint32_t)((x) & 0x1FF) << UARTx_BUFF_BUFF_POS) // [8:0] 写:发送数据缓存；读:接收数据寄存器

/* UARTx_ADR UARTx 地址匹配寄存器 (x = 0,1) */
#define UARTx_ADR_ADR_MAX  ((uint32_t)0xFF)                                        // UARTx_ADR_ADR最大值
#define UARTx_ADR_ADR_POS  0                                                       // UARTx_ADR_ADR起始位
#define UARTx_ADR_ADR_MASK (uint32_t)((uint32_t)0xFF << UARTx_ADR_ADR_POS)         // UARTx_ADR_ADR位掩码
#define UARTx_ADR_ADR(x)   (uint32_t)((uint32_t)((x) & 0xFF) << UARTx_ADR_ADR_POS) // [7:0] 多机通讯时的从机地址

/* UARTx_STT UARTx 状态寄存器 (x = 0,1) */
#define UARTx_STT_RX_BUSY_BIT      BIT3 // [3] 1:UART已检测到起始符并正处于接收状态0:UART接收端空闲此状态位只读，置位与清零均由硬件完成
#define UARTx_STT_ADR_MATCH_BIT    BIT2 // [2] Multi-drop模式下，地址匹配标志位。1:匹配；0:未匹配。
#define UARTx_STT_TX_DONE_BIT      BIT1 // [1] 发送完成标志位。1:完成；0:未完成。
#define UARTx_STT_TX_BUF_EMPTY_BIT BIT0 // [0] 发送缓存状态位。1:空；0:非空。

/* UARTx_RE UARTx DMA 请求使能寄存器 (x = 0,1) */
#define UARTx_RE_TX_BUF_EMPTY_BIT BIT2 // [2] 发送缓冲区空DMA请求开关，默认值为0。0:关闭；1:开启。
#define UARTx_RE_RX_DONE_BIT      BIT1 // [1] 接收完成DMA请求开关，默认值为0。0:关闭；1:开启。
#define UARTx_RE_TX_DONE_BIT      BIT0 // [0] 发送完成DMA请求开关，默认值为0。0:关闭；1:开启。

/* UARTx_IE UARTx 中断使能寄存器 (x = 0,1) */
#define UARTx_IE_IDLE_BIT         BIT8 // [8] 空闲帧中断使能0:关闭；1:开启
#define UARTx_IE_LBD_BIT          BIT7 // [7] LIN break character检测中断使能0:关闭；1:开启
#define UARTx_IE_RX_OV_BIT        BIT6 // [6] 接收缓冲区溢出中断使能0:关闭；1:开启
#define UARTx_IE_TX_OV_BIT        BIT5 // [5] 发送缓冲区溢出中断使能0:关闭；1:开启
#define UARTx_IE_CK_ERR_BIT       BIT4 // [4] 校验错误中断开关，默认值为0。0:关闭；1:开启
#define UARTx_IE_STOP_ERR_BIT     BIT3 // [3] 停止位错误中断开关，默认值为0。0:关闭；1:开启
#define UARTx_IE_TX_BUF_EMPTY_BIT BIT2 // [2] 发送缓冲区空中断开关，默认值为0。0:关闭；1:开启
#define UARTx_IE_RX_DONE_BIT      BIT1 // [1] 接收完成中断开关，默认值为0。0:关闭；1:开启
#define UARTx_IE_TX_DONE_BIT      BIT0 // [0] 发送完成中断开关，默认值为0。0:关闭；1:开启

/* UARTx_IF UARTx 中断标志寄存器 (x = 0,1) */
#define UARTx_IF_IDLE_BIT         BIT8 // [8] 空闲帧中断标志，高有效，写1清零当UART检测到空闲帧后，硬件置位这一标志，如果UARTx_IE.IDLE_IE=1，则产生中断请求；写1清零后，只有待RX_DONE_IF标志再次置位后，IDLE_IF标志才会置位。在多从机（Multi-drop）场景中，只有从机地址命中时，即UARTx_STT.ADR_MATCH=1时，表示主机此时欲与本从机通讯，IDLE_IF才会置位，否则即使UARTx_RX信号为常高，IDLE_IF也不会置位。
#define UARTx_IF_LBD_BIT          BIT7 // [7] LIN break character检测中断标志，高有效，写1清零
#define UARTx_IF_RX_OV_BIT        BIT6 // [6] 接收缓冲区溢出中断标志，高有效，写1清零
#define UARTx_IF_TX_OV_BIT        BIT5 // [5] 发送缓冲区溢出中断标志，高有效，写1清零
#define UARTx_IF_CK_ERR_BIT       BIT4 // [4] 校验错误中断标志，高有效，写1清零
#define UARTx_IF_STOP_ERR_BIT     BIT3 // [3] 停止位错误中断标志，高有效，写1清零
#define UARTx_IF_TX_BUF_EMPTY_BIT BIT2 // [2] 发送缓冲区空中断标志，高有效，写1清零
#define UARTx_IF_RX_DONE_BIT      BIT1 // [1] 接收完成中断标志，高有效，写1清零
#define UARTx_IF_TX_DONE_BIT      BIT0 // [0] 发送完成中断标志，高有效，写1清零

/* UARTx_IOC UARTx IO 控制寄存器 (x = 0,1) */
#define UARTx_IOC_SBK_BIT     BIT7 // [7] LIN模式下，写1发送一次break character，即连续13个0，完成后自动清零，未完成时读回为1，向此位写1之前需要先配置UARTx_CTRL.LIN_EN=1，否则无法进行break character的发送
#define UARTx_IOC_LBDL_BIT    BIT6 // [6] LIN break character检测长度，10/11个00:10bits，1:11bits
#define UARTx_IOC_AUTO_BIT    BIT4 // [4] 波特率自适应IO端口使能开关。0:关闭；1:开启
#define UARTx_IOC_TXD_INV_BIT BIT1 // [1] TXD输出极性使能开关，默认值为0。0:正常输出；1:取反输出。正常输出极性，即软件发送1，硬件发送1；取反输出极性，即应用发送1，硬件发送0。
#define UARTx_IOC_RXD_INV_BIT BIT0 // [0] RXD输入极性使能开关，默认值为0。0:正常输入；1:取反输入。正常输入极性，即硬件接收到1，软件接收的是1；取反输入极性，即硬件接收1，软件接收的是0。

/* DMA0_CTRL DMA控制寄存器 */
#define DMA0_CTRL_EN_BIT BIT0 // [0] DMA整体使能

/* DMA0_IE DMA中断使能寄存器 */
#define DMA0_IE_CH3_FIE_BIT BIT3 // [3] 通道3完成中断使能
#define DMA0_IE_CH2_FIE_BIT BIT2 // [2] 通道2完成中断使能
#define DMA0_IE_CH1_FIE_BIT BIT1 // [1] 通道1完成中断使能
#define DMA0_IE_CH0_FIE_BIT BIT0 // [0] 通道0完成中断使能

/* DMA0_IF DMA中断标志寄存器 */
#define DMA0_IF_CH3_FIF_BIT BIT3 // [3] 通道3完成中断标志，高有效，写1清零
#define DMA0_IF_CH2_FIF_BIT BIT2 // [2] 通道2完成中断标志，高有效，写1清零
#define DMA0_IF_CH1_FIF_BIT BIT1 // [1] 通道1完成中断标志，高有效，写1清零
#define DMA0_IF_CH0_FIF_BIT BIT0 // [0] 通道0完成中断标志，高有效，写1清零

/* DMA0_CCRx ( x =0,1,2,3) */
#define DMA0_CCRx_SBTW_MAX  ((uint32_t)0x3)                                         // DMA0_CCRx_SBTW最大值
#define DMA0_CCRx_SBTW_POS  10                                                      // DMA0_CCRx_SBTW起始位
#define DMA0_CCRx_SBTW_MASK (uint32_t)((uint32_t)0x3 << DMA0_CCRx_SBTW_POS)         // DMA0_CCRx_SBTW位掩码
#define DMA0_CCRx_SBTW(x)   (uint32_t)((uint32_t)((x) & 0x3) << DMA0_CCRx_SBTW_POS) // [11:10] 源地址访问位宽0: Byte1: Halfword2: Word3: 保留
#define DMA0_CCRx_DBTW_MAX  ((uint32_t)0x3)                                         // DMA0_CCRx_DBTW最大值
#define DMA0_CCRx_DBTW_POS  8                                                       // DMA0_CCRx_DBTW起始位
#define DMA0_CCRx_DBTW_MASK (uint32_t)((uint32_t)0x3 << DMA0_CCRx_DBTW_POS)         // DMA0_CCRx_DBTW位掩码
#define DMA0_CCRx_DBTW(x)   (uint32_t)((uint32_t)((x) & 0x3) << DMA0_CCRx_DBTW_POS) // [9:8] 目的地址访问位宽0: Byte1: Halfword2: Word3: 保留
#define DMA0_CCRx_SINC_BIT  BIT6                                                    // [6] 源地址递增方式0:不递增1:每传输一次，地址按照SBTW对应大小递增1/2/4
#define DMA0_CCRx_DINC_BIT  BIT4                                                    // [4] 目的地址递增方式0:不递增1:每传输一次，地址按照DBTW对应大小递增1/2/4
#define DMA0_CCRx_CIRC_BIT  BIT3                                                    // [3] 循环模式，高有效
#define DMA0_CCRx_RMODE_BIT BIT1                                                    // [1] 0:单轮传输，一轮连续传输多次，每收到DMA请求传输一轮，一个DMA请求即传输完毕1:多轮，每轮进行一次数据传输，每收到DMA请求传输一轮，多个DMA请求才传输完毕不支持多轮×多次传输
#define DMA0_CCRx_EN_BIT    BIT0                                                    // [0] 通道使能，高有效，软件置1开启通道进行DMA搬运操作，搬运完成后DMA硬件将此位清零

/* DMA0_RENx ( x = 0,1,2,3) */
#define DMA0_RENx_SW_REN_BIT       BIT31 // [31] 软复位读请求使能
#define DMA0_RENx_GPIO_REN_BIT     BIT29 // [29] GPIO读请求使能
#define DMA0_RENx_CMP_REN_BIT      BIT26 // [26] 比较器读请求使能
#define DMA0_RENx_SIF_REN_BIT      BIT25 // [25] SIF模块读请求使能
#define DMA0_RENx_HALL_REN_BIT     BIT24 // [24] HALL模块读请求使能
#define DMA0_RENx_UART1_TX_REN_BIT BIT19 // [19] UART1发送读请求使能
#define DMA0_RENx_UART1_RX_REN_BIT BIT18 // [18] UART1接收读请求使能
#define DMA0_RENx_UART0_TX_REN_BIT BIT17 // [17] UART0发送读请求使能
#define DMA0_RENx_UART0_RX_REN_BIT BIT16 // [16] UART0接收读请求使能
#define DMA0_RENx_I2C0_TX_REN_BIT  BIT15 // [15] I2C0发送读请求使能
#define DMA0_RENx_I2C0_RX_REN_BIT  BIT14 // [14] I2C0接收读请求使能
#define DMA0_RENx_MCPWM1_REN_BIT   BIT13 // [13] MCPWM1读请求使能
#define DMA0_RENx_MCPWM0_REN_BIT   BIT12 // [12] MCPWM0读请求使能
#define DMA0_RENx_SPI_TX_REN_BIT   BIT11 // [11] SPI发送读请求使能
#define DMA0_RENx_SPI_RX_REN_BIT   BIT10 // [10] SPI接收读请求使能
#define DMA0_RENx_TIMER3_REN_BIT   BIT7  // [7] TIMER3读请求使能
#define DMA0_RENx_TIMER2_REN_BIT   BIT6  // [6] TIMER2读请求使能
#define DMA0_RENx_TIMER1_REN_BIT   BIT5  // [5] TIMER1读请求使能
#define DMA0_RENx_TIMER0_REN_BIT   BIT4  // [4] TIMER0读请求使能
#define DMA0_RENx_DSP_REN_BIT      BIT3  // [3] DSP读请求使能
#define DMA0_RENx_ADC1_REN_BIT     BIT1  // [1] ADC1读请求使能
#define DMA0_RENx_ADC0_REN_BIT     BIT0  // [0] ADC0读请求使能

/* DMA0_CTMSx ( x = 0,1,2,3) */
#define DMA0_CTMSx_TMS_MAX  ((uint32_t)0xFF)                                         // DMA0_CTMSx_TMS最大值
#define DMA0_CTMSx_TMS_POS  0                                                        // DMA0_CTMSx_TMS起始位
#define DMA0_CTMSx_TMS_MASK (uint32_t)((uint32_t)0xFF << DMA0_CTMSx_TMS_POS)         // DMA0_CTMSx_TMS位掩码
#define DMA0_CTMSx_TMS(x)   (uint32_t)((uint32_t)((x) & 0xFF) << DMA0_CTMSx_TMS_POS) // [7:0] DMA通道x数据搬运次数。此寄存器在该通道使能后变为只读。

/* DMA0_SADRx ( x = 0,1,2,3) */
#define DMA0_SADRx_ADDR_MAX  ((uint32_t)0xFFFFFFFF)                                          // DMA0_SADRx_ADDR最大值
#define DMA0_SADRx_ADDR_POS  0                                                               // DMA0_SADRx_ADDR起始位
#define DMA0_SADRx_ADDR_MASK (uint32_t)((uint32_t)0xFFFFFFFF << DMA0_SADRx_ADDR_POS)         // DMA0_SADRx_ADDR位掩码
#define DMA0_SADRx_ADDR(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << DMA0_SADRx_ADDR_POS) // [31:0] DMA通道x源地址

/* DMA0_DADRx ( x = 0,1,2,3) */
#define DMA0_DADRx_ADDR_MAX  ((uint32_t)0xFFFFFFFF)                                          // DMA0_DADRx_ADDR最大值
#define DMA0_DADRx_ADDR_POS  0                                                               // DMA0_DADRx_ADDR起始位
#define DMA0_DADRx_ADDR_MASK (uint32_t)((uint32_t)0xFFFFFFFF << DMA0_DADRx_ADDR_POS)         // DMA0_DADRx_ADDR位掩码
#define DMA0_DADRx_ADDR(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << DMA0_DADRx_ADDR_POS) // [31:0] DMA通道x目的地址

/* DSP0_SC */
#define DSP0_SC_DMA_ACC_EN_BIT  BIT10 // [10] RE=1时，DMA在清零IF的同时，是否清零PAUSED，并RESET_PC。0：禁用，DMA收到请求后只清零IF1：使能，DMA收到请求后清零IF，PAUSED，并RESET_PCDMA_ACC_EN=1通常用于DSP软件模拟串行通讯接口的收发
#define DSP0_SC_RE_BIT          BIT9  // [9] DSP DMA请求使能，高有效，当RE=1，且IF =1时，产生DMA请求DMA接收到请求并受理开始数据搬运，并将IF标志清零，不再需要软件清零IF。
#define DSP0_SC_IE_BIT          BIT8  // [8] DSP中断使能，高有效，当IE=1，且IF =1时，产生中断请求，即使IE=0，当DSP执行到IRQ指令时，IF仍会置位。
#define DSP0_SC_RESET_PC_BIT    BIT3  // [3] 当DSP暂停时，写1重置DSP PC到0地址
#define DSP0_SC_CORDIC_MODE_BIT BIT2  // [2] CORDIC mode, 0: arctan, 1: sin/cos
#define DSP0_SC_PAUSED_BIT      BIT1  // [1] 指示DSP是否处于暂停状态，当DSP执行到IRQ指令时此bit置1，软件写可以将此bit置1。软件将此bit清零可以启动DSP运行0：DSP正读取CODE MEM和DATA MEM自主运行DSP程序1：DSP暂停取指令，允许ARM软件通过寄存器访问DSP内部算术单元，向寄存器写入操作数触发运算，读取寄存器取得运算结果对于不编写DSP CODE MEM程序的用户，PASUED需保持为1
#define DSP0_SC_IF_BIT          BIT0  // [0] DSP中断标志，写1清零

/* DSP0_THETA */
#define DSP0_THETA_THETA_MAX  ((uint32_t)0xFFFF)                                           // DSP0_THETA_THETA最大值
#define DSP0_THETA_THETA_POS  0                                                            // DSP0_THETA_THETA起始位
#define DSP0_THETA_THETA_MASK (uint32_t)((uint32_t)0xFFFF << DSP0_THETA_THETA_POS)         // DSP0_THETA_THETA位掩码
#define DSP0_THETA_THETA(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << DSP0_THETA_THETA_POS) // [15:0] DSP sin/cos输入角度寄存器

/* DSP0_SIN */
#define DSP0_SIN_SIN_MAX  ((uint32_t)0xFFFF)                                       // DSP0_SIN_SIN最大值
#define DSP0_SIN_SIN_POS  0                                                        // DSP0_SIN_SIN起始位
#define DSP0_SIN_SIN_MASK (uint32_t)((uint32_t)0xFFFF << DSP0_SIN_SIN_POS)         // DSP0_SIN_SIN位掩码
#define DSP0_SIN_SIN(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << DSP0_SIN_SIN_POS) // [15:0] DSP sin/cos计算结果sin寄存器

/* DSP0_COS */
#define DSP0_COS_COS_MAX  ((uint32_t)0xFFFF)                                       // DSP0_COS_COS最大值
#define DSP0_COS_COS_POS  0                                                        // DSP0_COS_COS起始位
#define DSP0_COS_COS_MASK (uint32_t)((uint32_t)0xFFFF << DSP0_COS_COS_POS)         // DSP0_COS_COS位掩码
#define DSP0_COS_COS(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << DSP0_COS_COS_POS) // [15:0] DSP sin/cos计算结果cos寄存器

/* DSP0_X */
#define DSP0_X_X_MAX  ((uint32_t)0xFFFF)                                   // DSP0_X_X最大值
#define DSP0_X_X_POS  0                                                    // DSP0_X_X起始位
#define DSP0_X_X_MASK (uint32_t)((uint32_t)0xFFFF << DSP0_X_X_POS)         // DSP0_X_X位掩码
#define DSP0_X_X(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << DSP0_X_X_POS) // [15:0] DSP arctan/module计算输入坐标X寄存器

/* DSP0_Y */
#define DSP0_Y_Y_MAX  ((uint32_t)0xFFFF)                                   // DSP0_Y_Y最大值
#define DSP0_Y_Y_POS  0                                                    // DSP0_Y_Y起始位
#define DSP0_Y_Y_MASK (uint32_t)((uint32_t)0xFFFF << DSP0_Y_Y_POS)         // DSP0_Y_Y位掩码
#define DSP0_Y_Y(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << DSP0_Y_Y_POS) // [15:0] DSP arctan/module计算输入坐标Y寄存器

/* DSP0_MOD */
#define DSP0_MOD_MOD_MAX  ((uint32_t)0xFFFF)                                       // DSP0_MOD_MOD最大值
#define DSP0_MOD_MOD_POS  0                                                        // DSP0_MOD_MOD起始位
#define DSP0_MOD_MOD_MASK (uint32_t)((uint32_t)0xFFFF << DSP0_MOD_MOD_POS)         // DSP0_MOD_MOD位掩码
#define DSP0_MOD_MOD(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << DSP0_MOD_MOD_POS) // [15:0] DSP arctan计算结果 sqrt(X2+Y2) 寄存器

/* **DSP0_ARCTAN** */
#define DSP0_ARCTAN_ARCTAN_MAX  ((uint32_t)0xFFFF)                                             // DSP0_ARCTAN_ARCTAN最大值
#define DSP0_ARCTAN_ARCTAN_POS  0                                                              // DSP0_ARCTAN_ARCTAN起始位
#define DSP0_ARCTAN_ARCTAN_MASK (uint32_t)((uint32_t)0xFFFF << DSP0_ARCTAN_ARCTAN_POS)         // DSP0_ARCTAN_ARCTAN位掩码
#define DSP0_ARCTAN_ARCTAN(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << DSP0_ARCTAN_ARCTAN_POS) // [15:0] DSP arctan计算结果arctan(Y/X) 角度寄存器

/* DSP0_DID */
#define DSP0_DID_DID_MAX  ((uint32_t)0xFFFFFFFF)                                       // DSP0_DID_DID最大值
#define DSP0_DID_DID_POS  0                                                            // DSP0_DID_DID起始位
#define DSP0_DID_DID_MASK (uint32_t)((uint32_t)0xFFFFFFFF << DSP0_DID_DID_POS)         // DSP0_DID_DID位掩码
#define DSP0_DID_DID(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << DSP0_DID_DID_POS) // [31:0] DSP 除法被除数寄存器

/* DSP0_DIS */
#define DSP0_DIS_DIS_MAX  ((uint32_t)0xFFFFFFFF)                                       // DSP0_DIS_DIS最大值
#define DSP0_DIS_DIS_POS  0                                                            // DSP0_DIS_DIS起始位
#define DSP0_DIS_DIS_MASK (uint32_t)((uint32_t)0xFFFFFFFF << DSP0_DIS_DIS_POS)         // DSP0_DIS_DIS位掩码
#define DSP0_DIS_DIS(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << DSP0_DIS_DIS_POS) // [31:0] DSP 除法除数寄存器

/* DSP0_QUO */
#define DSP0_QUO_QUO_MAX  ((uint32_t)0xFFFFFFFF)                                       // DSP0_QUO_QUO最大值
#define DSP0_QUO_QUO_POS  0                                                            // DSP0_QUO_QUO起始位
#define DSP0_QUO_QUO_MASK (uint32_t)((uint32_t)0xFFFFFFFF << DSP0_QUO_QUO_POS)         // DSP0_QUO_QUO位掩码
#define DSP0_QUO_QUO(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << DSP0_QUO_QUO_POS) // [31:0] DSP 商寄存器

/* DSP0_RAD */
#define DSP0_RAD_RAD_MAX  ((uint32_t)0xFFFFFFFF)                                       // DSP0_RAD_RAD最大值
#define DSP0_RAD_RAD_POS  0                                                            // DSP0_RAD_RAD起始位
#define DSP0_RAD_RAD_MASK (uint32_t)((uint32_t)0xFFFFFFFF << DSP0_RAD_RAD_POS)         // DSP0_RAD_RAD位掩码
#define DSP0_RAD_RAD(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << DSP0_RAD_RAD_POS) // [31:0] DSP 被开方数寄存器

/* DSP0_SQRT */
#define DSP0_SQRT_SQRT_MAX  ((uint32_t)0xFFFF)                                         // DSP0_SQRT_SQRT最大值
#define DSP0_SQRT_SQRT_POS  0                                                          // DSP0_SQRT_SQRT起始位
#define DSP0_SQRT_SQRT_MASK (uint32_t)((uint32_t)0xFFFF << DSP0_SQRT_SQRT_POS)         // DSP0_SQRT_SQRT位掩码
#define DSP0_SQRT_SQRT(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << DSP0_SQRT_SQRT_POS) // [15:0] DSP 平方根寄存器

/* DSP0_PC */
#define DSP0_PC_PC_MAX  ((uint32_t)0x1FF)                                     // DSP0_PC_PC最大值
#define DSP0_PC_PC_POS  0                                                     // DSP0_PC_PC起始位
#define DSP0_PC_PC_MASK (uint32_t)((uint32_t)0x1FF << DSP0_PC_PC_POS)         // DSP0_PC_PC位掩码
#define DSP0_PC_PC(x)   (uint32_t)((uint32_t)((x) & 0x1FF) << DSP0_PC_PC_POS) // [8:0] 当DSP出于暂停状态时，允许软件直接写入PC值。无论DSP是否出于暂停状态，PC寄存器均可读

/* DSP0_PDI */
#define DSP0_PDI_P2_14_BIT BIT15 // [15] GPIO2_PDI[14]
#define DSP0_PDI_P2_7_BIT  BIT14 // [14] GPIO2_PDI[7]
#define DSP0_PDI_P2_6_BIT  BIT13 // [13] GPIO2_PDI[6]
#define DSP0_PDI_P2_5_BIT  BIT12 // [12] GPIO2_PDI[5]
#define DSP0_PDI_P2_4_BIT  BIT11 // [11] GPIO2_PDI[4]
#define DSP0_PDI_P2_3_BIT  BIT10 // [10] GPIO2_PDI[3]
#define DSP0_PDI_P1_0_BIT  BIT9  // [9] GPIO1_PDI[0]
#define DSP0_PDI_P0_15_BIT BIT8  // [8] GPIO0_PDI[15]
#define DSP0_PDI_P0_14_BIT BIT7  // [7] GPIO0_PDI[14]
#define DSP0_PDI_P0_13_BIT BIT6  // [6] GPIO0_PDI[13]
#define DSP0_PDI_P0_12_BIT BIT5  // [5] GPIO0_PDI[12]
#define DSP0_PDI_P0_11_BIT BIT4  // [4] GPIO0_PDI[11]
#define DSP0_PDI_P0_4_BIT  BIT3  // [3] GPIO0_PDI[4]
#define DSP0_PDI_P0_3_BIT  BIT2  // [2] GPIO0_PDI[3]
#define DSP0_PDI_P0_2_BIT  BIT1  // [1] GPIO0_PDI[2]
#define DSP0_PDI_P0_0_BIT  BIT0  // [0] GPIO0_PDI[0]

/* DSP0_BSRR */
#define DSP0_BSRR_P2_14_BIT BIT15 // [15] GPIO2_BSRR[14]
#define DSP0_BSRR_P2_7_BIT  BIT14 // [14] GPIO2_BSRR[7]
#define DSP0_BSRR_P2_6_BIT  BIT13 // [13] GPIO2_BSRR[6]
#define DSP0_BSRR_P2_5_BIT  BIT12 // [12] GPIO2_BSRR[5]
#define DSP0_BSRR_P2_4_BIT  BIT11 // [11] GPIO2_BSRR[4]
#define DSP0_BSRR_P2_3_BIT  BIT10 // [10] GPIO2_BSRR[3]
#define DSP0_BSRR_P1_0_BIT  BIT9  // [9] GPIO1_BSRR[0]
#define DSP0_BSRR_P0_15_BIT BIT8  // [8] GPIO0_BSRR[15]
#define DSP0_BSRR_P0_14_BIT BIT7  // [7] GPIO0_BSRR[14]
#define DSP0_BSRR_P0_13_BIT BIT6  // [6] GPIO0_BSRR[13]
#define DSP0_BSRR_P0_12_BIT BIT5  // [5] GPIO0_BSRR[12]
#define DSP0_BSRR_P0_11_BIT BIT4  // [4] GPIO0_BSRR[11]
#define DSP0_BSRR_P0_4_BIT  BIT3  // [3] GPIO0_BSRR[4]
#define DSP0_BSRR_P0_3_BIT  BIT2  // [2] GPIO0_BSRR[3]
#define DSP0_BSRR_P0_2_BIT  BIT1  // [1] GPIO0_BSRR[2]
#define DSP0_BSRR_P0_0_BIT  BIT0  // [0] GPIO0_BSRR[0]

/* DSP0_BRR */
#define DSP0_BRR_P2_14_BIT BIT15 // [15] GPIO2_BRR[14]
#define DSP0_BRR_P2_7_BIT  BIT14 // [14] GPIO2_BRR[7]
#define DSP0_BRR_P2_6_BIT  BIT13 // [13] GPIO2_BRR[6]
#define DSP0_BRR_P2_5_BIT  BIT12 // [12] GPIO2_BRR[5]
#define DSP0_BRR_P2_4_BIT  BIT11 // [11] GPIO2_BRR[4]
#define DSP0_BRR_P2_3_BIT  BIT10 // [10] GPIO2_BRR[3]
#define DSP0_BRR_P1_0_BIT  BIT9  // [9] GPIO1_BRR[0]
#define DSP0_BRR_P0_15_BIT BIT8  // [8] GPIO0_BRR[15]
#define DSP0_BRR_P0_14_BIT BIT7  // [7] GPIO0_BRR[14]
#define DSP0_BRR_P0_13_BIT BIT6  // [6] GPIO0_BRR[13]
#define DSP0_BRR_P0_12_BIT BIT5  // [5] GPIO0_BRR[12]
#define DSP0_BRR_P0_11_BIT BIT4  // [4] GPIO0_BRR[11]
#define DSP0_BRR_P0_4_BIT  BIT3  // [3] GPIO0_BRR[4]
#define DSP0_BRR_P0_3_BIT  BIT2  // [2] GPIO0_BRR[3]
#define DSP0_BRR_P0_2_BIT  BIT1  // [1] GPIO0_BRR[2]
#define DSP0_BRR_P0_0_BIT  BIT0  // [0] GPIO0_BRR[0]

/* DSP0_CL */
#define DSP0_CL_CL_OUTPUT3_BIT BIT3 // [3] GPIO0_BRR[4]
#define DSP0_CL_CL_OUTPUT2_BIT BIT2 // [2] GPIO0_BRR[3]
#define DSP0_CL_CL_OUTPUT1_BIT BIT1 // [1] GPIO0_BRR[2]
#define DSP0_CL_CL_OUTPUT0_BIT BIT0 // [0] GPIO0_BRR[0]

/* DSP0_OP */
#define DSP0_OP_OPERAND_MAX  ((uint32_t)0xFFFFFFFF)                                          // DSP0_OP_OPERAND最大值
#define DSP0_OP_OPERAND_POS  0                                                               // DSP0_OP_OPERAND起始位
#define DSP0_OP_OPERAND_MASK (uint32_t)((uint32_t)0xFFFFFFFF << DSP0_OP_OPERAND_POS)         // DSP0_OP_OPERAND位掩码
#define DSP0_OP_OPERAND(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << DSP0_OP_OPERAND_POS) // [31:0] DSP操作数寄存器

/* DSP0_RES */
#define DSP0_RES_RESULT_MAX  ((uint32_t)0xFFFFFFFF)                                          // DSP0_RES_RESULT最大值
#define DSP0_RES_RESULT_POS  0                                                               // DSP0_RES_RESULT起始位
#define DSP0_RES_RESULT_MASK (uint32_t)((uint32_t)0xFFFFFFFF << DSP0_RES_RESULT_POS)         // DSP0_RES_RESULT位掩码
#define DSP0_RES_RESULT(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << DSP0_RES_RESULT_POS) // [31:0] DSP运行结果寄存器

/* IWDG_PSW 独立看门狗密码寄存器 */
#define IWDG_PSW_PSW_MAX  ((uint32_t)0xFFFF)                                       // IWDG_PSW_PSW最大值
#define IWDG_PSW_PSW_POS  0                                                        // IWDG_PSW_PSW起始位
#define IWDG_PSW_PSW_MASK (uint32_t)((uint32_t)0xFFFF << IWDG_PSW_PSW_POS)         // IWDG_PSW_PSW位掩码
#define IWDG_PSW_PSW(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << IWDG_PSW_PSW_POS) // [15:0] 写入0xA6B4，才能对IWDG_CLR/ IWDG_RTH等进行写操作，对IWDG_CLR或IWDG_RTH的写操作会将密码清空，因此每次对看门狗IWDG_CLR/ IWDG_RTH寄存器进行写操作前都需要重新写入密码

/* IWDG_CFG 独立看门狗配置寄存器 */
#define IWDG_CFG_DWK_EN_BIT BIT4 // [4] 深度休眠定时唤醒使能，0:禁用，1:使能
#define IWDG_CFG_WDG_EN_BIT BIT0 // [0] 独立看门狗使能，0:禁用，1:使能。默认使能，写1置位，写0同时向[15:8]写入0x3C可清零。当看门狗被禁用时，不再产生复位信号，但仍可计数并产生定时唤醒信号

/* IWDG_CLR 独立看门狗清零寄存器 */
#define IWDG_CLR_IWDG_CLR_MAX  ((uint32_t)0xFFFF)                                            // IWDG_CLR_IWDG_CLR最大值
#define IWDG_CLR_IWDG_CLR_POS  0                                                             // IWDG_CLR_IWDG_CLR起始位
#define IWDG_CLR_IWDG_CLR_MASK (uint32_t)((uint32_t)0xFFFF << IWDG_CLR_IWDG_CLR_POS)         // IWDG_CLR_IWDG_CLR位掩码
#define IWDG_CLR_IWDG_CLR(x)   (uint32_t)((uint32_t)((x) & 0xFFFF) << IWDG_CLR_IWDG_CLR_POS) // [15:0] 写入字节 16’b0111_1001_1000_110B0，高15位为密码，密码正确时，B[0]才能写入B[0]写入1，则重置WDT计数器为TH，且该bit写入后自动清零，写入0无效

/* IWDG_WTH 独立看门狗定时唤醒门限寄存器 */
#define IWDG_WTH_IWDG_WTH_MAX  ((uint32_t)0x1FF)                                            // IWDG_WTH_IWDG_WTH最大值
#define IWDG_WTH_IWDG_WTH_POS  12                                                           // IWDG_WTH_IWDG_WTH起始位
#define IWDG_WTH_IWDG_WTH_MASK (uint32_t)((uint32_t)0x1FF << IWDG_WTH_IWDG_WTH_POS)         // IWDG_WTH_IWDG_WTH位掩码
#define IWDG_WTH_IWDG_WTH(x)   (uint32_t)((uint32_t)((x) & 0x1FF) << IWDG_WTH_IWDG_WTH_POS) // [20:12] 看门狗定时唤醒门限值，看门狗使用32kHz LRC时钟从IWDG_RTH开始计数，递减计数至IWDG_WTH产生唤醒信号。

/* IWDG_RTH 独立看门狗超时复位门限寄存器 */
#define IWDG_RTH_IWDG_RTH_MAX  ((uint32_t)0x1FF)                                            // IWDG_RTH_IWDG_RTH最大值
#define IWDG_RTH_IWDG_RTH_POS  12                                                           // IWDG_RTH_IWDG_RTH起始位
#define IWDG_RTH_IWDG_RTH_MASK (uint32_t)((uint32_t)0x1FF << IWDG_RTH_IWDG_RTH_POS)         // IWDG_RTH_IWDG_RTH位掩码
#define IWDG_RTH_IWDG_RTH(x)   (uint32_t)((uint32_t)((x) & 0x1FF) << IWDG_RTH_IWDG_RTH_POS) // [20:12] 看门狗超时复位门限值，也是重新装载值。看门狗使用32kHz LRC时钟从IWDG_RTH开始计数，计数至0x7产生复位。向该寄存器写入0x0，会被硬件强制改写为0x1000。先向IWDG_PSW写入正确密码才能改写IWDG_RTH寄存器。改写IWDG_RTH同样具有重置看门狗计数器的作用，看门狗会从新的IWDG_RTH开始计数。

/* IWDG_CNT 独立看门狗当前计数值寄存器 */
#define IWDG_CNT_IWDG_CNT_MAX  ((uint32_t)0x1FFFFF)                                            // IWDG_CNT_IWDG_CNT最大值
#define IWDG_CNT_IWDG_CNT_POS  0                                                               // IWDG_CNT_IWDG_CNT起始位
#define IWDG_CNT_IWDG_CNT_MASK (uint32_t)((uint32_t)0x1FFFFF << IWDG_CNT_IWDG_CNT_POS)         // IWDG_CNT_IWDG_CNT位掩码
#define IWDG_CNT_IWDG_CNT(x)   (uint32_t)((uint32_t)((x) & 0x1FFFFF) << IWDG_CNT_IWDG_CNT_POS) // [20:0] 看门狗当前计数值，此数值≤IWDG_TH

/* AON_PWR_CFG 功耗管理配置寄存器 */
#define AON_PWR_CFG_IOWK_FLT_BIT BIT1 // [1] IO唤醒信号滤波使能，默认使能

/* AON_EVT_RCD 事件记录寄存器 */
#define AON_EVT_RCD_DEEPSLEEP_BIT   BIT13 // [13] 深度休眠记录，高表示发生过
#define AON_EVT_RCD_SLEEP_BIT       BIT12 // [12] 休眠记录，高表示发生过
#define AON_EVT_RCD_IWDG_WK_BIT     BIT9  // [9] IWDG定时唤醒记录，高表示Deep Sleep休眠被IWDG定时唤醒
#define AON_EVT_RCD_EVT_WK_BIT      BIT8  // [8] IO唤醒或CLU唤醒记录，高表示Deep Sleep休眠被AON_IO_WAKE_EN中对应的使能信号唤醒
#define AON_EVT_RCD_IWDG_RST_BIT    BIT3  // [3] 独立看门狗复位发生记录，高表示发生过
#define AON_EVT_RCD_KEY_RST_RCD_BIT BIT2  // [2] 按键复位发生记录，高表示发生过
#define AON_EVT_RCD_POR_RST_RCD_BIT BIT0  // [0] POR复位发生记录，高表示发生过

/* AON_IO_WAKE_POL IO 唤醒极性寄存器 */
#define AON_IO_WAKE_POL_WK_POL_BIT BIT0 // [0] IO外部唤醒触发电平选择。1:高电平；0:低电平

/* AON_IO_WAKE_EN IO 唤醒使能寄存器 */
#define AON_IO_WAKE_EN_CLUOUT3_EN_BIT BIT11 // [11] CLUOUT3作为唤醒使能
#define AON_IO_WAKE_EN_CLUOUT2_EN_BIT BIT10 // [10] CLUOUT2作为唤醒使能
#define AON_IO_WAKE_EN_CLUOUT1_EN_BIT BIT9  // [9] CLUOUT1作为唤醒使能
#define AON_IO_WAKE_EN_CLUOUT0_EN_BIT BIT8  // [8] CLUOUT0作为唤醒使能
#define AON_IO_WAKE_EN_P2_15_EN_BIT   BIT7  // [7] P2[15]外部唤醒使能
#define AON_IO_WAKE_EN_P2_7_EN_BIT    BIT6  // [6] P2[7]外部唤醒使能
#define AON_IO_WAKE_EN_P2_4_EN_BIT    BIT5  // [5] P2[4]外部唤醒使能
#define AON_IO_WAKE_EN_P0_14_EN_BIT   BIT4  // [4] P0[14]外部唤醒使能
#define AON_IO_WAKE_EN_P0_11_EN_BIT   BIT3  // [3] P0[11]外部唤醒使能
#define AON_IO_WAKE_EN_P0_6_EN_BIT    BIT2  // [2] P0[6]外部唤醒使能
#define AON_IO_WAKE_EN_P0_2_EN_BIT    BIT1  // [1] P0[2]外部唤醒使能
#define AON_IO_WAKE_EN_P0_0_EN_BIT    BIT0  // [0] P0[0]外部唤醒使能

/* SIF0_CFG 配置寄存器 */
#define SIF0_CFG_DONE_BIT       BIT7 // [7] SIF模块数据传输，完成信号默认电平1：默认高电平0：默认低电平
#define SIF0_CFG_SYNC_BIT       BIT6 // [6] SIF模块数据传输，同步信号默认电平1：默认高电平0：默认低电平
#define SIF0_CFG_SYNC_PULSE_BIT BIT5 // [5] SIF模块数据传输，同步信号是否产生脉冲信号1：同步信号有脉冲信号0：同步信号无脉冲信号
#define SIF0_CFG_DONE_VLD_BIT   BIT4 // [4] SIF模块数据传输，结束信号控制位1：有结束信号0：无结束信号
#define SIF0_CFG_SYNC_VLD_BIT   BIT3 // [3] SIF模块数据传输，同步信号控制位1：有同步信号0：无同步信号
#define SIF0_CFG_RATIO_BIT      BIT2 // [2] SIF模块数据占空比控制位1：3:10：2:1
#define SIF0_CFG_MSB_BIT        BIT1 // [1] SIF模块数据大小头控制位1：MSB0：LSB
#define SIF0_CFG_EN_BIT         BIT0 // [0] SIF模块使能位1：SIF模块使能0：SIF模块关闭

/* SIF0_TOSC 时基寄存器 */
#define SIF0_TOSC_OSC_TH_MAX  ((uint32_t)0xFFF)                                           // SIF0_TOSC_OSC_TH最大值
#define SIF0_TOSC_OSC_TH_POS  0                                                           // SIF0_TOSC_OSC_TH起始位
#define SIF0_TOSC_OSC_TH_MASK (uint32_t)((uint32_t)0xFFF << SIF0_TOSC_OSC_TH_POS)         // SIF0_TOSC_OSC_TH位掩码
#define SIF0_TOSC_OSC_TH(x)   (uint32_t)((uint32_t)((x) & 0xFFF) << SIF0_TOSC_OSC_TH_POS) // [11:0] SIF模块的时基Tosc设置时基Tosc= (OSC_TH+1)×(系统时钟周期×32)

/* SIF0_TSTH1 同步时间寄存器 */
#define SIF0_TSTH1_TSTH1_MAX  ((uint32_t)0x3FF)                                           // SIF0_TSTH1_TSTH1最大值
#define SIF0_TSTH1_TSTH1_POS  0                                                           // SIF0_TSTH1_TSTH1起始位
#define SIF0_TSTH1_TSTH1_MASK (uint32_t)((uint32_t)0x3FF << SIF0_TSTH1_TSTH1_POS)         // SIF0_TSTH1_TSTH1位掩码
#define SIF0_TSTH1_TSTH1(x)   (uint32_t)((uint32_t)((x) & 0x3FF) << SIF0_TSTH1_TSTH1_POS) // [9:0] SIF模块同步信号周期当SYNC无脉冲时，此周期即为整个SYNC时间宽度当SYNC有脉冲时，此周期为SYNC脉冲前的时间宽度，SYNC脉冲宽度固定为32×ToscTime = (TSTH1+1)×Tosc

/* SIF0_TDTH1 结束时间寄存器 */
#define SIF0_TDTH1_TDTH1_MAX  ((uint32_t)0xF)                                           // SIF0_TDTH1_TDTH1最大值
#define SIF0_TDTH1_TDTH1_POS  0                                                         // SIF0_TDTH1_TDTH1起始位
#define SIF0_TDTH1_TDTH1_MASK (uint32_t)((uint32_t)0xF << SIF0_TDTH1_TDTH1_POS)         // SIF0_TDTH1_TDTH1位掩码
#define SIF0_TDTH1_TDTH1(x)   (uint32_t)((uint32_t)((x) & 0xF) << SIF0_TDTH1_TDTH1_POS) // [3:0] SIF模块结束信号周期Time = (TDTH1+1)×1ms

/* SIF0_IRQ 中断寄存器 */
#define SIF0_IRQ_IRQ_IF_BIT BIT4 // [4] SIF模块中断标志位，写1清零。1：有SIF中断标志位0：无SIF中断标志位
#define SIF0_IRQ_DMA_EN_BIT BIT1 // [1] SIF模块DMA使能控制位1：使能0：关闭
#define SIF0_IRQ_IRQ_EN_BIT BIT0 // [0] SIF模块中断使能控制位1：使能中断0：关闭中断

/* SIF0_WDATA 数据寄存器 */
#define SIF0_WDATA_WDATA_MAX  ((uint32_t)0xFF)                                           // SIF0_WDATA_WDATA最大值
#define SIF0_WDATA_WDATA_POS  0                                                          // SIF0_WDATA_WDATA起始位
#define SIF0_WDATA_WDATA_MASK (uint32_t)((uint32_t)0xFF << SIF0_WDATA_WDATA_POS)         // SIF0_WDATA_WDATA位掩码
#define SIF0_WDATA_WDATA(x)   (uint32_t)((uint32_t)((x) & 0xFF) << SIF0_WDATA_WDATA_POS) // [7:0] SIF模块数据寄存器

/* CL0_EN0 CL0 使能寄存器 */
#define CL0_EN0_C3EN_BIT BIT3 // [3] CLU3使能。默认关闭。0: 关闭1: 使能
#define CL0_EN0_C2EN_BIT BIT2 // [2] CLU2使能。默认关闭。0: 关闭1: 使能
#define CL0_EN0_C1EN_BIT BIT1 // [1] CLU1使能。默认关闭。0: 关闭1: 使能
#define CL0_EN0_C0EN_BIT BIT0 // [0] CLU0使能。默认关闭。0: 关闭1: 使能

/* CL0_IE0 CL0 中断使能寄存器 */
#define CL0_IE0_C3RIE_BIT BIT7 // [7] CLU3上升沿触发中断使能。默认关闭。0: 关闭1: 使能
#define CL0_IE0_C3FIE_BIT BIT6 // [6] CLU3下降沿触发中断使能。默认关闭。0: 关闭1: 使能
#define CL0_IE0_C2RIE_BIT BIT5 // [5] CLU2上升沿触发中断使能。默认关闭。0: 关闭1: 使能
#define CL0_IE0_C2FIE_BIT BIT4 // [4] CLU2下降沿触发中断使能。默认关闭。0: 关闭1: 使能
#define CL0_IE0_C1RIE_BIT BIT3 // [3] CLU1上升沿触发中断使能。默认关闭。0: 关闭1: 使能
#define CL0_IE0_C1FIE_BIT BIT2 // [2] CLU1下降沿触发中断使能。默认关闭。0: 关闭1: 使能
#define CL0_IE0_C0RIE_BIT BIT1 // [1] CLU0上升沿触发中断使能。默认关闭。0: 关闭1: 使能
#define CL0_IE0_C0FIE_BIT BIT0 // [0] CLU0下降沿触发中断使能。默认关闭。0: 关闭1: 使能

/* CL0_IF0 CL0 中断标志寄存器 */
#define CL0_IF0_C3RIF_BIT BIT7 // [7] CLU3上升沿中断标志位。中断标志高有效，写1清零。
#define CL0_IF0_C3FIF_BIT BIT6 // [6] CLU3下降沿中断标志位。中断标志高有效，写1清零。
#define CL0_IF0_C2RIF_BIT BIT5 // [5] CLU2上升沿中断标志位。中断标志高有效，写1清零。
#define CL0_IF0_C2FIF_BIT BIT4 // [4] CLU2下降沿中断标志位。中断标志高有效，写1清零。
#define CL0_IF0_C1RIF_BIT BIT3 // [3] CLU1上升沿中断标志位。中断标志高有效，写1清零。
#define CL0_IF0_C1FIF_BIT BIT2 // [2] CLU1下降沿中断标志位。中断标志高有效，写1清零。
#define CL0_IF0_C0RIF_BIT BIT1 // [1] CLU0上升沿中断标志位。中断标志高有效，写1清零。
#define CL0_IF0_C0FIF_BIT BIT0 // [0] CLU0下降沿中断标志位。中断标志高有效，写1清零。

/* CL0_OUT0 CL0 输出寄存器 */
#define CL0_OUT0_C3OUT_BIT BIT3 // [3] CLU3输出状态，与系统时钟同步。
#define CL0_OUT0_C2OUT_BIT BIT2 // [2] CLU2输出状态，与系统时钟同步。
#define CL0_OUT0_C1OUT_BIT BIT1 // [1] CLU1输出状态，与系统时钟同步。
#define CL0_OUT0_C0OUT_BIT BIT0 // [0] CLU0输出状态，与系统时钟同步。

/* CL0_MX0 CL0 输入多路复选寄存器 */
#define CL0_MX0_C3MXA_MAX  ((uint32_t)0xF)                                        // CL0_MX0_C3MXA最大值
#define CL0_MX0_C3MXA_POS  28                                                     // CL0_MX0_C3MXA起始位
#define CL0_MX0_C3MXA_MASK (uint32_t)((uint32_t)0xF << CL0_MX0_C3MXA_POS)         // CL0_MX0_C3MXA位掩码
#define CL0_MX0_C3MXA(x)   (uint32_t)((uint32_t)((x) & 0xF) << CL0_MX0_C3MXA_POS) // [31:28] CLU3 A输入多路复用选择
#define CL0_MX0_C3MXB_MAX  ((uint32_t)0xF)                                        // CL0_MX0_C3MXB最大值
#define CL0_MX0_C3MXB_POS  24                                                     // CL0_MX0_C3MXB起始位
#define CL0_MX0_C3MXB_MASK (uint32_t)((uint32_t)0xF << CL0_MX0_C3MXB_POS)         // CL0_MX0_C3MXB位掩码
#define CL0_MX0_C3MXB(x)   (uint32_t)((uint32_t)((x) & 0xF) << CL0_MX0_C3MXB_POS) // [27:24] CLU3 B输入多路复用选择
#define CL0_MX0_C2MXA_MAX  ((uint32_t)0xF)                                        // CL0_MX0_C2MXA最大值
#define CL0_MX0_C2MXA_POS  20                                                     // CL0_MX0_C2MXA起始位
#define CL0_MX0_C2MXA_MASK (uint32_t)((uint32_t)0xF << CL0_MX0_C2MXA_POS)         // CL0_MX0_C2MXA位掩码
#define CL0_MX0_C2MXA(x)   (uint32_t)((uint32_t)((x) & 0xF) << CL0_MX0_C2MXA_POS) // [23:20] CLU2 A输入多路复用选择
#define CL0_MX0_C2MXB_MAX  ((uint32_t)0xF)                                        // CL0_MX0_C2MXB最大值
#define CL0_MX0_C2MXB_POS  16                                                     // CL0_MX0_C2MXB起始位
#define CL0_MX0_C2MXB_MASK (uint32_t)((uint32_t)0xF << CL0_MX0_C2MXB_POS)         // CL0_MX0_C2MXB位掩码
#define CL0_MX0_C2MXB(x)   (uint32_t)((uint32_t)((x) & 0xF) << CL0_MX0_C2MXB_POS) // [19:16] CLU2 B输入多路复用选择
#define CL0_MX0_C1MXA_MAX  ((uint32_t)0xF)                                        // CL0_MX0_C1MXA最大值
#define CL0_MX0_C1MXA_POS  12                                                     // CL0_MX0_C1MXA起始位
#define CL0_MX0_C1MXA_MASK (uint32_t)((uint32_t)0xF << CL0_MX0_C1MXA_POS)         // CL0_MX0_C1MXA位掩码
#define CL0_MX0_C1MXA(x)   (uint32_t)((uint32_t)((x) & 0xF) << CL0_MX0_C1MXA_POS) // [15:12] CLU1 A输入多路复用选择
#define CL0_MX0_C1MXB_MAX  ((uint32_t)0xF)                                        // CL0_MX0_C1MXB最大值
#define CL0_MX0_C1MXB_POS  8                                                      // CL0_MX0_C1MXB起始位
#define CL0_MX0_C1MXB_MASK (uint32_t)((uint32_t)0xF << CL0_MX0_C1MXB_POS)         // CL0_MX0_C1MXB位掩码
#define CL0_MX0_C1MXB(x)   (uint32_t)((uint32_t)((x) & 0xF) << CL0_MX0_C1MXB_POS) // [11:8] CLU1 B输入多路复用选择
#define CL0_MX0_C0MXA_MAX  ((uint32_t)0xF)                                        // CL0_MX0_C0MXA最大值
#define CL0_MX0_C0MXA_POS  4                                                      // CL0_MX0_C0MXA起始位
#define CL0_MX0_C0MXA_MASK (uint32_t)((uint32_t)0xF << CL0_MX0_C0MXA_POS)         // CL0_MX0_C0MXA位掩码
#define CL0_MX0_C0MXA(x)   (uint32_t)((uint32_t)((x) & 0xF) << CL0_MX0_C0MXA_POS) // [7:4] CLU0 A输入多路复用选择
#define CL0_MX0_C0MXB_MAX  ((uint32_t)0xF)                                        // CL0_MX0_C0MXB最大值
#define CL0_MX0_C0MXB_POS  0                                                      // CL0_MX0_C0MXB起始位
#define CL0_MX0_C0MXB_MASK (uint32_t)((uint32_t)0xF << CL0_MX0_C0MXB_POS)         // CL0_MX0_C0MXB位掩码
#define CL0_MX0_C0MXB(x)   (uint32_t)((uint32_t)((x) & 0xF) << CL0_MX0_C0MXB_POS) // [3:0] CLU0 B输入多路复用选择

/* CL0_FN0 CL0 功能选择寄存器 */
#define CL0_FN0_C3FN_MAX  ((uint32_t)0xFF)                                       // CL0_FN0_C3FN最大值
#define CL0_FN0_C3FN_POS  24                                                     // CL0_FN0_C3FN起始位
#define CL0_FN0_C3FN_MASK (uint32_t)((uint32_t)0xFF << CL0_FN0_C3FN_POS)         // CL0_FN0_C3FN位掩码
#define CL0_FN0_C3FN(x)   (uint32_t)((uint32_t)((x) & 0xFF) << CL0_FN0_C3FN_POS) // [31:24] CLU3 查找表功能选择。
#define CL0_FN0_C2FN_MAX  ((uint32_t)0xFF)                                       // CL0_FN0_C2FN最大值
#define CL0_FN0_C2FN_POS  16                                                     // CL0_FN0_C2FN起始位
#define CL0_FN0_C2FN_MASK (uint32_t)((uint32_t)0xFF << CL0_FN0_C2FN_POS)         // CL0_FN0_C2FN位掩码
#define CL0_FN0_C2FN(x)   (uint32_t)((uint32_t)((x) & 0xFF) << CL0_FN0_C2FN_POS) // [23:16] CLU2 查找表功能选择。
#define CL0_FN0_C1FN_MAX  ((uint32_t)0xFF)                                       // CL0_FN0_C1FN最大值
#define CL0_FN0_C1FN_POS  8                                                      // CL0_FN0_C1FN起始位
#define CL0_FN0_C1FN_MASK (uint32_t)((uint32_t)0xFF << CL0_FN0_C1FN_POS)         // CL0_FN0_C1FN位掩码
#define CL0_FN0_C1FN(x)   (uint32_t)((uint32_t)((x) & 0xFF) << CL0_FN0_C1FN_POS) // [15:8] CLU1查找表功能选择。
#define CL0_FN0_C0FN_MAX  ((uint32_t)0xFF)                                       // CL0_FN0_C0FN最大值
#define CL0_FN0_C0FN_POS  0                                                      // CL0_FN0_C0FN起始位
#define CL0_FN0_C0FN_MASK (uint32_t)((uint32_t)0xFF << CL0_FN0_C0FN_POS)         // CL0_FN0_C0FN位掩码
#define CL0_FN0_C0FN(x)   (uint32_t)((uint32_t)((x) & 0xFF) << CL0_FN0_C0FN_POS) // [7:0] CLU0查找表功能选择。

/* CL0_CF0 CL0 配置寄存器 */
#define CL0_CF0_C3OUTSEL_BIT  BIT31                                                     // [31] CLU3输出选取0: D触发器输出1: LUT输出
#define CL0_CF0_C3OEN_BIT     BIT30                                                     // [30] CLU3输出使能。默认关闭。0: 关闭1: 使能
#define CL0_CF0_C3RST_BIT     BIT27                                                     // [27] CLU3 D触发器复位。该位写1复位。读取恒为0。
#define CL0_CF0_C3CLKINV_BIT  BIT26                                                     // [26] CLU3 D触发器时钟电平反向。0: 关闭1: 使能
#define CL0_CF0_C3CLKSEL_MAX  ((uint32_t)0x3)                                           // CL0_CF0_C3CLKSEL最大值
#define CL0_CF0_C3CLKSEL_POS  24                                                        // CL0_CF0_C3CLKSEL起始位
#define CL0_CF0_C3CLKSEL_MASK (uint32_t)((uint32_t)0x3 << CL0_CF0_C3CLKSEL_POS)         // CL0_CF0_C3CLKSEL位掩码
#define CL0_CF0_C3CLKSEL(x)   (uint32_t)((uint32_t)((x) & 0x3) << CL0_CF0_C3CLKSEL_POS) // [25:24] CLU3 D触发器时钟选择。0x0: 进位输入0x1: MXA输入0x2: ALTCLK00x3: ALTCLK1
#define CL0_CF0_C2OUTSEL_BIT  BIT23                                                     // [23] CLU2输出选取0: D触发器输出1: LUT输出
#define CL0_CF0_C2OEN_BIT     BIT22                                                     // [22] CLU2输出使能。默认关闭。0: 关闭1: 使能
#define CL0_CF0_C2RST_BIT     BIT19                                                     // [19] CLU2 D触发器复位。该位写1复位。读取恒为0。
#define CL0_CF0_C2CLKINV_BIT  BIT18                                                     // [18] CLU2 D触发器时钟电平反向。0: 关闭1: 使能
#define CL0_CF0_C2CLKSEL_MAX  ((uint32_t)0x3)                                           // CL0_CF0_C2CLKSEL最大值
#define CL0_CF0_C2CLKSEL_POS  16                                                        // CL0_CF0_C2CLKSEL起始位
#define CL0_CF0_C2CLKSEL_MASK (uint32_t)((uint32_t)0x3 << CL0_CF0_C2CLKSEL_POS)         // CL0_CF0_C2CLKSEL位掩码
#define CL0_CF0_C2CLKSEL(x)   (uint32_t)((uint32_t)((x) & 0x3) << CL0_CF0_C2CLKSEL_POS) // [17:16] CLU2 D触发器时钟选择 。0x0: 进位输入0x1: MXA输入0x2: ALTCLK00x3: ALTCLK1
#define CL0_CF0_C1OUTSEL_BIT  BIT15                                                     // [15] CLU1输出选取0: D触发器输出1: LUT输出
#define CL0_CF0_C1OEN_BIT     BIT14                                                     // [14] CLU1输出使能。默认关闭。0: 关闭1: 使能
#define CL0_CF0_C1RST_BIT     BIT11                                                     // [11] CLU1 D触发器复位。该位写1复位。读取恒为0。
#define CL0_CF0_C1CLKINV_BIT  BIT10                                                     // [10] CLU1 D触发器时钟电平反向。0: 关闭1: 使能
#define CL0_CF0_C1CLKSEL_MAX  ((uint32_t)0x3)                                           // CL0_CF0_C1CLKSEL最大值
#define CL0_CF0_C1CLKSEL_POS  8                                                         // CL0_CF0_C1CLKSEL起始位
#define CL0_CF0_C1CLKSEL_MASK (uint32_t)((uint32_t)0x3 << CL0_CF0_C1CLKSEL_POS)         // CL0_CF0_C1CLKSEL位掩码
#define CL0_CF0_C1CLKSEL(x)   (uint32_t)((uint32_t)((x) & 0x3) << CL0_CF0_C1CLKSEL_POS) // [9:8] CLU1 D触发器时钟选择 。0x0: 进位输入0x1: MXA输入0x2: ALTCLK00x3: ALTCLK1
#define CL0_CF0_C0OUTSEL_BIT  BIT7                                                      // [7] CLU0输出选取0: D触发器输出1: LUT输出
#define CL0_CF0_C0OEN_BIT     BIT6                                                      // [6] CLU0输出使能。默认关闭。0: 关闭1: 使能
#define CL0_CF0_C0RST_BIT     BIT3                                                      // [3] CLU0 D触发器复位。该位写1复位。读取恒为0。
#define CL0_CF0_C0CLKINV_BIT  BIT2                                                      // [2] CLU0 D触发器时钟电平反向。0: 关闭1: 使能
#define CL0_CF0_C0CLKSEL_MAX  ((uint32_t)0x3)                                           // CL0_CF0_C0CLKSEL最大值
#define CL0_CF0_C0CLKSEL_POS  0                                                         // CL0_CF0_C0CLKSEL起始位
#define CL0_CF0_C0CLKSEL_MASK (uint32_t)((uint32_t)0x3 << CL0_CF0_C0CLKSEL_POS)         // CL0_CF0_C0CLKSEL位掩码
#define CL0_CF0_C0CLKSEL(x)   (uint32_t)((uint32_t)((x) & 0x3) << CL0_CF0_C0CLKSEL_POS) // [1:0] CLU0 D触发器时钟选择 。0x0: 进位输入0x1: MXA输入0x2: ALTCLK00x3: ALTCLK1

/* CAN_RBUF0/1/2/3 寄存器 */
#define CAN_RBUF0_RDATA_MAX  ((uint32_t)0xFFFFFFFF)                                          // CAN_RBUF0_RDATA最大值
#define CAN_RBUF0_RDATA_POS  0                                                               // CAN_RBUF0_RDATA起始位
#define CAN_RBUF0_RDATA_MASK (uint32_t)((uint32_t)0xFFFFFFFF << CAN_RBUF0_RDATA_POS)         // CAN_RBUF0_RDATA位掩码
#define CAN_RBUF0_RDATA(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << CAN_RBUF0_RDATA_POS) // [31:0] 接收寄存器，从Rx Buffer Slot中读出CAN帧的数据

/* CAN_TBUF0/1/2/3 寄存器 */
#define CAN_TBUF0_WDATA_MAX  ((uint32_t)0xFFFFFFFF)                                          // CAN_TBUF0_WDATA最大值
#define CAN_TBUF0_WDATA_POS  0                                                               // CAN_TBUF0_WDATA起始位
#define CAN_TBUF0_WDATA_MASK (uint32_t)((uint32_t)0xFFFFFFFF << CAN_TBUF0_WDATA_POS)         // CAN_TBUF0_WDATA位掩码
#define CAN_TBUF0_WDATA(x)   (uint32_t)((uint32_t)((x) & 0xFFFFFFFF) << CAN_TBUF0_WDATA_POS) // [31:0] 发送寄存器，写入数据到Tx Buffer Slot中（PTB或者STB）

/* CAN_CFG_STAT 配置和状态寄存器 */
#define CAN_CFG_STAT_RESET_BIT   BIT7 // [7] 1：CAN模块，复位模式0：CAN模块，正常工作模式复位模式下，CAN模块部分电路处于复位状态，部分寄存器只能在复位模式下配置；正常工作模式下，可以收发CAN帧。注意，从复位模式切换到正常工作模式，需要等待11个CAN Bit Time的时间（例如波特率为500K，一个Bit Time就是2us，需要等待22us才能发送或者接收CAN帧）
#define CAN_CFG_STAT_LBME_BIT    BIT6 // [6] 外部回环模式使能位1：使能0：关闭注意：正常通信中，禁止使能该位
#define CAN_CFG_STAT_LBMI_BIT    BIT5 // [5] 内部回环模式使能位1：使能0：关闭注意：正常通信中，禁止使能该位
#define CAN_CFG_STAT_TPSS_BIT    BIT4 // [4] PTB单次传输模式使能位1：使能0：关闭
#define CAN_CFG_STAT_TSSS_BIT    BIT3 // [3] STB单次传输模式使能位1：使能0：关闭
#define CAN_CFG_STAT_RACTIVE_BIT BIT2 // [2] 接收状态标志位0：本CAN设备，接收空闲，总线空闲1：本CAN设备，正在接收CAN帧
#define CAN_CFG_STAT_TACTIVE_BIT BIT1 // [1] 发送状态标志位0：本CAN设备，发送空闲1：本CAN设备，正在发送CAN帧
#define CAN_CFG_STAT_BUSOFF_BIT  BIT0 // [0] 本CAN设备总线关闭状态位（Bus Off）0：本CAN设备，不在总线关闭状态位1：本CAN设备，处于总线关闭状态位注意：BUSOFF写1可以清零TECNT和RECNT寄存器，但仅限于项目调试。正常使用时需要禁止对CANx_CFG_STAT.BUSOFF写1。软件操作 CANx_CFG_STAT 寄存器时需要避免使用或等于（\ =）以及与等于符号（&=），因为使用这两个符号操作 CANx_CFG_STAT 寄存器时可能会将 CANx_CFG_STAT.BUSOFF 字段误写 1，从而导致将 BUSOFF 误清零，导致BUSOFF提前恢复。

/* CAN_TCMD 发送命令寄存器 */
#define CAN_TCMD_TBSEL_BIT BIT7 // [7] Tx Buffer选择位，通过CAN_TBUF写入到对应Buffer中1：STB0：PTB注意在写入CAN_TBUF过程中，TBSEL的值不能改变；同时，在写入STB的时候，完成一帧的写入，需要更新TSNEXT。
#define CAN_TCMD_LOM_BIT   BIT6 // [6] 监听模式使能位1：使能0：关闭如果设置了TPE、TSONE或TSALL，则无法设置LOM。如果LOM启用且LBME禁用，则无法启动传输。LOM=1和LBME=0禁止所有传输。LOM=1和LBME=1禁止应答相应接收到的帧和错误帧，但可以发送本CAN设备的帧注意：正常通信中，禁止使能该位
#define CAN_TCMD_TPE_BIT   BIT4 // [4] PTB发送使能位1：触发PTB发送0：不触发PTB发送配置TPE，在下一个可以发送的窗口，优先STB发送PTB的数据（除非当前已经在发送STB，否则先发PTB）。该位写1后将保持为1直到PTB发送完成或者通过TPA取消发送。软件不能通过写0清除该位。TPE可以被清除的另外几种情况：CAN_CFG_STAT.RESET=1CAN_TCMD.LOM=1同时CAN_CFG_STAT.LBME=0
#define CAN_TCMD_TPA_BIT   BIT3 // [3] PTB发送取消位1：取消已经通过TPE置1请求但还未开始的PTB发送0：不取消软件置位，硬件自动清零。设置TPA会自动清零TPE，一般TPA和TPE不同时置位。CAN_CFG_STAT.RESET=1可清零TPA。
#define CAN_TCMD_TSONE_BIT BIT2 // [2] 发送一帧STB数据控制位（Transmit Secondary ONE Frame）1：发送一帧STB数据0：不发送TSONE配置为1，触发发送，成功发送或者TSA终止发送可实现硬件清零，否则一直保持1。CAN_CFG_STAT.RESET=1，也可清零。
#define CAN_TCMD_TSALL_BIT BIT1 // [1] 发送多帧STB数据控制位（Transmit Secondary All Frames）1：发送多帧STB数据0：不发送TSALL配置为1，触发发送，成功发送或者TSA终止发送可实现硬件清零，否则一直保持1。CAN_CFG_STAT.RESET=1，也可清零。
#define CAN_TCMD_TSA_BIT   BIT0 // [0] STB发送取消位1：取消已经通过TSONE或者TSALL置1请求但还未开始的STB发送，软件写1，硬件清零。写1可以清零TSONE或者TSALL位0：不取消一般TSA和TSONE/TSALL，不同时置位。CAN_CFG_STAT.RESET=1可清零TSA

/* CAN_TCTRL 发送控制寄存器 */
#define CAN_TCTRL_TSNEXT_BIT  BIT6                                                      // [6] 更新STB Slot位置1：更新0：不更新当前的STB Slot填满数据后，软件置位TSNEXT，硬件自动指向下一个STB Slot，此时，TSONE/TSALL置位，即可发送被填满的STB Slot。可以同时设置TSNEXT和TSONE或TSALL。如果TBSEL=0，则设置TSNEXT没有意义，TSNEXT的配置将被忽略并自动清除。如果STB的所有Slot都已填满，则TSNEXT将保持置位状态，直到Slot有空闲，才会被硬件清零。
#define CAN_TCTRL_TSSTAT_MAX  ((uint32_t)0x3)                                           // CAN_TCTRL_TSSTAT最大值
#define CAN_TCTRL_TSSTAT_POS  0                                                         // CAN_TCTRL_TSSTAT起始位
#define CAN_TCTRL_TSSTAT_MASK (uint32_t)((uint32_t)0x3 << CAN_TCTRL_TSSTAT_POS)         // CAN_TCTRL_TSSTAT位掩码
#define CAN_TCTRL_TSSTAT(x)   (uint32_t)((uint32_t)((x) & 0x3) << CAN_TCTRL_TSSTAT_POS) // [1:0] STB状态位3：STB满2：STB大于半满1：STB小于等于半满0：STB空

/* CAN_RCTRL 接收控制寄存器 */
#define CAN_RCTRL_SACK_BIT   BIT7                                                     // [7] 自应答1：LBME=1时，使能自应答功能0：无自应答
#define CAN_RCTRL_ROM_BIT    BIT6                                                     // [6] Rx Buffer满，溢出控制位1：新接收到的数据不被存储0：最早接收到的数据被覆盖
#define CAN_RCTRL_ROV_BIT    BIT5                                                     // [5] Rx Buffer溢出标志位1：溢出，最少有一帧数据丢失。通过写RREL为1清零0：无溢出
#define CAN_RCTRL_RREL_BIT   BIT4                                                     // [4] 释放Rx Buffer Slot1：软件已经取走当前Rx Buffer Slot数据，可释放当前Rx Buffer Slot，硬件指向下一个Rx Buffer Slot0：无释放操作
#define CAN_RCTRL_RBALL_BIT  BIT3                                                     // [3] 接收Rx Buffer存储通过ID滤波的帧1：存储所有的CAN帧，包括错误的帧0：正常模式，仅存储正确的CAN帧
#define CAN_RCTRL_RSTAT_MAX  ((uint32_t)0x3)                                          // CAN_RCTRL_RSTAT最大值
#define CAN_RCTRL_RSTAT_POS  0                                                        // CAN_RCTRL_RSTAT起始位
#define CAN_RCTRL_RSTAT_MASK (uint32_t)((uint32_t)0x3 << CAN_RCTRL_RSTAT_POS)         // CAN_RCTRL_RSTAT位掩码
#define CAN_RCTRL_RSTAT(x)   (uint32_t)((uint32_t)((x) & 0x3) << CAN_RCTRL_RSTAT_POS) // [1:0] Rx Buffer状态位3：满（溢出状态下，保持此值）2：Rx Buffer已经接收的帧的数量大于等于AFWL的值，但未满1：Rx Buffer已经接收的帧的数量小于AFWL的值0：Rx Buffer已经接收的帧的数量为0，空

/* CAN_RTIE 发送接收中断控制寄存器 */
#define CAN_RTIE_RIE_BIT   BIT7 // [7] 接收中断使能（Receive Interrupt Enable）1：使能0：禁止
#define CAN_RTIE_ROIE_BIT  BIT6 // [6] 接收溢出中断使能（Receive Overrun Interrupt Enable）1：使能0：禁止
#define CAN_RTIE_RFIE_BIT  BIT5 // [5] Rx Buffer满中断使能（Rx Buffer Full Interrupt Enable）1：使能0：禁止
#define CAN_RTIE_RAFIE_BIT BIT4 // [4] Rx Buffer将满中断使能（Rx Buffer Almost Full Interrupt Enable）1：使能0：禁止
#define CAN_RTIE_TPIE_BIT  BIT3 // [3] PTB发送中断使能（Transmission Primary Interrupt Enable）1：使能0：禁止
#define CAN_RTIE_TSIE_BIT  BIT2 // [2] STB发送中断使能（Transmission Secondary Interrupt Enable）1：使能0：禁止
#define CAN_RTIE_EIE_BIT   BIT1 // [1] 错误中断使能（Error Interrupt Enable）1：使能0：禁止
#define CAN_RTIE_TSFF_BIT  BIT0 // [0] Tx Buffer标志位1：STB Slot被全部填满0：STB Slot没有被全部填满

/* CAN_RTIF 发送接收中断标志寄存器 */
#define CAN_RTIF_RIF_BIT   BIT7 // [7] 接收中断标志位（Receive Interrupt Flag）1：接收到有效帧（数据帧或者远程帧），写1清零0：没有接收到有效帧
#define CAN_RTIF_ROIF_BIT  BIT6 // [6] 接收溢出中断标志位（Receive Overrun Interrupt Flag）1：Rx Buffer至少有一帧未读走的数据被覆盖0：Rx Buffer无覆盖溢出时ROIF和RFIF同时置1，写1清零
#define CAN_RTIF_RFIF_BIT  BIT5 // [5] Rx Buffer满中断标志位（Rx Buffer Full Interrupt Flag）1：Rx Buffer满，写1清零0：Rx Buffer未满
#define CAN_RTIF_RAFIF_BIT BIT4 // [4] Rx Buffer将满中断标志位（Rx Buffer Almost Full Interrupt Flag）1：被填充的Rx Buffer Slot数目大于等于AFWL设定值0：被填充的Rx Buffer Slot数目小于AFWL设定值
#define CAN_RTIF_TPIF_BIT  BIT3 // [3] PTB发送中断标志（Transmission Primary Interrupt Flag）1：触发PTB发送，发送成功完成。写1清零0：无PTB发送请求，无完成标志
#define CAN_RTIF_TSIF_BIT  BIT2 // [2] STB发送中断标志（Transmission Secondary Interrupt Flag）1：触发STB发送，发送成功完成。写1清零0：无STB发送请求，无完成标志
#define CAN_RTIF_EIF_BIT   BIT1 // [1] 错误中断标志（Error Interrupt Flag）1：错误计数器的值发生变化，大于或者小于错误警告寄存器的设定值。写1清零0：无错误计数器的值从小于错误警告寄存器的设定值变为大于设定值，或者从大于设定值变为小于设定值，均会触发中断标志。另外，进入Bus Off或从Bus Off退出，也会触发。
#define CAN_RTIF_AIF_BIT   BIT0 // [0] 取消发送中断标志（Abort Interrupt Flag）1：通过TPA和TSA请求的发送消息被成功取消。写1清零0：未取消发送数据AIF没有对应的使能寄存器

/* CAN_ERRINT 错误中断使能和标志寄存器 */
#define CAN_ERRINT_EWARN_BIT BIT7 // [7] 错误计数值超限中断标志位1：RECNT或者TECNT大于等于EWL设定值，写1清零0：RECNT或者TECNT小于EWL设定值
#define CAN_ERRINT_EPASS_BIT BIT6 // [6] CAN设备处于被动错误状态1：CAN设备处于被动错误状态0：CAN设备处于主动错误状态
#define CAN_ERRINT_EPIE_BIT  BIT5 // [5] 被动错误中断使能（Error Passive Interrupt Enable）1：使能0：禁止
#define CAN_ERRINT_EPIF_BIT  BIT4 // [4] 被动错误中断标志（Error Passive Interrupt Flag） 1：发生主动错误到被动错误（或者相反）的改变，写1清零0：未发生
#define CAN_ERRINT_ALIE_BIT  BIT3 // [3] 仲裁失败中断使能（Arbitration Lost Interrupt Enable）1：使能0：禁止
#define CAN_ERRINT_ALIF_BIT  BIT2 // [2] 仲裁失败中断标志位（Arbitration Lost Interrupt Flag）1：仲裁失败，写1清零0：仲裁成功
#define CAN_ERRINT_BEIE_BIT  BIT1 // [1] 总线错误中断使能（Bus Error Interrupt Enable）1：使能0：禁止
#define CAN_ERRINT_BEIF_BIT  BIT0 // [0] 总线错误中断标志（Bus Error Interrupt Flag）1：总线错误，写1清零0：无总线错误

/* CAN_LIMIT 错误&警告门限值寄存器 */
#define CAN_LIMIT_AFWL_MAX  ((uint32_t)0xF)                                         // CAN_LIMIT_AFWL最大值
#define CAN_LIMIT_AFWL_POS  4                                                       // CAN_LIMIT_AFWL起始位
#define CAN_LIMIT_AFWL_MASK (uint32_t)((uint32_t)0xF << CAN_LIMIT_AFWL_POS)         // CAN_LIMIT_AFWL位掩码
#define CAN_LIMIT_AFWL(x)   (uint32_t)((uint32_t)((x) & 0xF) << CAN_LIMIT_AFWL_POS) // [7:4] Rx Buffer快满警告配置值AFWL同Rx Buffer实际接收到的数量进行比对，实际数量超过AFWL，触发RAFIF。AFWL=0，无意义，硬件强制配置为1；AFWL超过Rx Buffer实际容量，无意义，硬件强制配置为Rx Buffer实际容量
#define CAN_LIMIT_EWL_MAX   ((uint32_t)0xF)                                         // CAN_LIMIT_EWL最大值
#define CAN_LIMIT_EWL_POS   0                                                       // CAN_LIMIT_EWL起始位
#define CAN_LIMIT_EWL_MASK  (uint32_t)((uint32_t)0xF << CAN_LIMIT_EWL_POS)          // CAN_LIMIT_EWL位掩码
#define CAN_LIMIT_EWL(x)    (uint32_t)((uint32_t)((x) & 0xF) << CAN_LIMIT_EWL_POS)  // [3:0] 可编程错误警告限值=（EWL+1）\*8。可能的极限值：8，16，…128。EWL的值控制EIF。

/* CAN_SBAUD 波特率配置寄存器 */
#define CAN_SBAUD_S_PRESC_MAX  ((uint32_t)0xFF)                                            // CAN_SBAUD_S_PRESC最大值
#define CAN_SBAUD_S_PRESC_POS  24                                                          // CAN_SBAUD_S_PRESC起始位
#define CAN_SBAUD_S_PRESC_MASK (uint32_t)((uint32_t)0xFF << CAN_SBAUD_S_PRESC_POS)         // CAN_SBAUD_S_PRESC位掩码
#define CAN_SBAUD_S_PRESC(x)   (uint32_t)((uint32_t)((x) & 0xFF) << CAN_SBAUD_S_PRESC_POS) // [31:24] TQ预分频率设定值（S_Prescaler），主要配置TQ的大小。TQ = system clock period \*(S_PRESC+1)
#define CAN_SBAUD_S_SJW_MAX    ((uint32_t)0x7F)                                            // CAN_SBAUD_S_SJW最大值
#define CAN_SBAUD_S_SJW_POS    16                                                          // CAN_SBAUD_S_SJW起始位
#define CAN_SBAUD_S_SJW_MASK   (uint32_t)((uint32_t)0x7F << CAN_SBAUD_S_SJW_POS)           // CAN_SBAUD_S_SJW位掩码
#define CAN_SBAUD_S_SJW(x)     (uint32_t)((uint32_t)((x) & 0x7F) << CAN_SBAUD_S_SJW_POS)   // [22:16] 再同步补偿宽度时间设定（Bit Timing Segment 2） 再同步补偿宽度时间=(S_SJW+1)\*TQ
#define CAN_SBAUD_S_SEG_2_MAX  ((uint32_t)0x7F)                                            // CAN_SBAUD_S_SEG_2最大值
#define CAN_SBAUD_S_SEG_2_POS  8                                                           // CAN_SBAUD_S_SEG_2起始位
#define CAN_SBAUD_S_SEG_2_MASK (uint32_t)((uint32_t)0x7F << CAN_SBAUD_S_SEG_2_POS)         // CAN_SBAUD_S_SEG_2位掩码
#define CAN_SBAUD_S_SEG_2(x)   (uint32_t)((uint32_t)((x) & 0x7F) << CAN_SBAUD_S_SEG_2_POS) // [14:08] 段2时间单元设定（Bit Timing Segment 2）段2时间=(S_SEG_2+1)\*TQ
#define CAN_SBAUD_S_SEG_1_MAX  ((uint32_t)0xFF)                                            // CAN_SBAUD_S_SEG_1最大值
#define CAN_SBAUD_S_SEG_1_POS  0                                                           // CAN_SBAUD_S_SEG_1起始位
#define CAN_SBAUD_S_SEG_1_MASK (uint32_t)((uint32_t)0xFF << CAN_SBAUD_S_SEG_1_POS)         // CAN_SBAUD_S_SEG_1位掩码
#define CAN_SBAUD_S_SEG_1(x)   (uint32_t)((uint32_t)((x) & 0xFF) << CAN_SBAUD_S_SEG_1_POS) // [07:00] 段1时间单元设定（Bit Timing Segment 1）段1时间=(S_SEG_1+2)\*TQ

/* CAN_EALCAP 错误信息和丢失仲裁信息记录寄存器 */
#define CAN_EALCAP_KOER_MAX  ((uint32_t)0x7)                                          // CAN_EALCAP_KOER最大值
#define CAN_EALCAP_KOER_POS  5                                                        // CAN_EALCAP_KOER起始位
#define CAN_EALCAP_KOER_MASK (uint32_t)((uint32_t)0x7 << CAN_EALCAP_KOER_POS)         // CAN_EALCAP_KOER位掩码
#define CAN_EALCAP_KOER(x)   (uint32_t)((uint32_t)((x) & 0x7) << CAN_EALCAP_KOER_POS) // [7:5] 错误类别（Kind Of Error）0：无错误1：位错误2：形式错误3：填充错误4：应答错误5：CRC错误6：其他错误7：保留有错误时KOER位更新，正常发送接收时KOER位保持不变。
#define CAN_EALCAP_ALC_MAX   ((uint32_t)0x1F)                                         // CAN_EALCAP_ALC最大值
#define CAN_EALCAP_ALC_POS   0                                                        // CAN_EALCAP_ALC起始位
#define CAN_EALCAP_ALC_MASK  (uint32_t)((uint32_t)0x1F << CAN_EALCAP_ALC_POS)         // CAN_EALCAP_ALC位掩码
#define CAN_EALCAP_ALC(x)    (uint32_t)((uint32_t)((x) & 0x1F) << CAN_EALCAP_ALC_POS) // [4:0] 仲裁失败位置捕捉（Arbitration Lost Capture）仲裁失败时ALC记录一帧数据中仲裁失败时的位置

/* CAN_RECNT 接收错误计数器寄存器 */
#define CAN_RECNT_RECNT_MAX  ((uint32_t)0xFF)                                          // CAN_RECNT_RECNT最大值
#define CAN_RECNT_RECNT_POS  0                                                         // CAN_RECNT_RECNT起始位
#define CAN_RECNT_RECNT_MASK (uint32_t)((uint32_t)0xFF << CAN_RECNT_RECNT_POS)         // CAN_RECNT_RECNT位掩码
#define CAN_RECNT_RECNT(x)   (uint32_t)((uint32_t)((x) & 0xFF) << CAN_RECNT_RECNT_POS) // [7:0] 接收错误计数器（Receive Error Count）接收错误计数器根据CAN协议规定的错误计数增加或者减少。该计数器不存在上溢，255为最大值

/* CAN_TECNT 发送错误计数器寄存器 */
#define CAN_TECNT_TECNT_MAX  ((uint32_t)0xFF)                                          // CAN_TECNT_TECNT最大值
#define CAN_TECNT_TECNT_POS  0                                                         // CAN_TECNT_TECNT起始位
#define CAN_TECNT_TECNT_MASK (uint32_t)((uint32_t)0xFF << CAN_TECNT_TECNT_POS)         // CAN_TECNT_TECNT位掩码
#define CAN_TECNT_TECNT(x)   (uint32_t)((uint32_t)((x) & 0xFF) << CAN_TECNT_TECNT_POS) // [7:0] 发送错误计数器（Transmit Error Count）发送错误计数器根据CAN协议规定的错误计数增加或者减少。该计数器不存在上溢，255为最大值

/* CAN_ACFCTRL ID 滤波器控制寄存器 */
#define CAN_ACFCTRL_SELMASK_BIT BIT5                                                        // [5] 选择ID滤波器的屏蔽寄存器（Select Acceptance MASK） 1：ACF指向ID滤波器AMR寄存器（MASK）0：ACF指向ID滤波器ACR寄存器通过ACFADR选择具体的筛选寄存器组
#define CAN_ACFCTRL_ACFADR_MAX  ((uint32_t)0xF)                                             // CAN_ACFCTRL_ACFADR最大值
#define CAN_ACFCTRL_ACFADR_POS  0                                                           // CAN_ACFCTRL_ACFADR起始位
#define CAN_ACFCTRL_ACFADR_MASK (uint32_t)((uint32_t)0xF << CAN_ACFCTRL_ACFADR_POS)         // CAN_ACFCTRL_ACFADR位掩码
#define CAN_ACFCTRL_ACFADR(x)   (uint32_t)((uint32_t)((x) & 0xF) << CAN_ACFCTRL_ACFADR_POS) // [3:0] ID滤波器地址（Acceptance Filter Address）ACFADR指向具体的ID滤波器器，通过SELMASK去区分ACR和AMR。 0：指向ACF_01：指向ACF_12：指向ACF_23：指向ACF_3其它值，无效

/* CAN_ACFEN ID 滤波器使能寄存器 */
#define CAN_ACFEN_AE_3_BIT BIT3 // [3] ACF_3使能（Acceptance Filter 4 Enable）1：使能0：禁止
#define CAN_ACFEN_AE_2_BIT BIT2 // [2] ACF_2使能（Acceptance Filter 3 Enable）1：使能0：禁止
#define CAN_ACFEN_AE_1_BIT BIT1 // [1] ACF_1使能（Acceptance Filter 2 Enable）1：使能0：禁止
#define CAN_ACFEN_AE_0_BIT BIT0 // [0] ACF_0使能（Acceptance Filter 1 Enable）1：使能0：禁止

/* CAN_ACF ID 滤波器选择寄存器 */
#define CAN_ACF_IDCMP_BIT        BIT30                                                               // [30] SELMASK=1时有效，ID AMR（MASK）选择作用范围1：ID滤波器接收MASK按照标准帧格式或者扩展帧格式处理0：ID滤波器接收MASK兼容标准帧格式和扩展帧格式两种格式
#define CAN_ACF_IDMASK_BIT       BIT29                                                               // [29] IDCMP位为1时，MASK选择哪种帧格式1：ID滤波器仅接收扩展帧格式0：ID滤波器仅接收标准帧格式
#define CAN_ACF_IDCODE_MASK_MAX  ((uint32_t)0x1FFFFFFF)                                              // CAN_ACF_IDCODE_MASK最大值
#define CAN_ACF_IDCODE_MASK_POS  0                                                                   // CAN_ACF_IDCODE_MASK起始位
#define CAN_ACF_IDCODE_MASK_MASK (uint32_t)((uint32_t)0x1FFFFFFF << CAN_ACF_IDCODE_MASK_POS)         // CAN_ACF_IDCODE_MASK位掩码
#define CAN_ACF_IDCODE_MASK(x)   (uint32_t)((uint32_t)((x) & 0x1FFFFFFF) << CAN_ACF_IDCODE_MASK_POS) // [28:00] ACFADR选择是那一组ID滤波器SELMASK=0，表示ID滤波器选择的是ID ACRSELMASK=1，表示ID滤波器选择的是AMR标准帧格式时ID ACR/AMR的范围是Bit10-Bit0，扩展帧格式时的范围是Bit28-Bit0
#endif
