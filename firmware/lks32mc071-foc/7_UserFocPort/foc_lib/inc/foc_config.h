#ifndef __FOC_CONFIG_H
#define __FOC_CONFIG_H

#include "math.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FOC_SENSOR_EN               1      // 使能传感器
#define FOC_CLOSE_LOOP_EN           1         // 使能闭环
#define FOC_POSITION_PI_EN          0
#define FOC_SPEED_PI_EN             1        // 使能速度环
#define FOC_PLL_ENABLE              1        // 使能锁相环
#define HFI_ENABLE                  0          // 使能高频注入低速角度估计
#define FOC_SMO_EN                  0        // 使能观测器
#define FOC_CLOSE_I_DEBUG_EN        0
#define FOC_OPEN_I_DEBUG_EN         0
#define FW_ENABLE                   0        // 使能弱磁


// PWM参数
#define PWM_ARR                 3000         // 自动重载值
#define PWM_SCALE               3.3f            // ADC参考电压
#define PWM_VBUS                12.0f           // VBUS母线电压
#define ADC_RESOLUTION          4096        // 12位ADC分辨率
// #define TS                      0.0001176f     // 采样时间间隔
#define TS                      0.0000625f        // 采样时间间隔 (16kHz ISR)

#define FOC_CURRENT_BASE_A      CURRENT_LIMIT       // 电流基值
#define FOC_VOLTAGE_BASE_V      CURRENT_PI_LIMIT    // 电压基值

// 电机通用参数（根据电机修改）
// #define POLE_PAIRS              7.0f            // 电机极对数（示例：7对极）
// #define CURRENT_LIMIT           20.0f           // 最大相电流(A)
// #define MOTOR_R                 0.095f           // 相电阻含系统阻抗 (Ohm，电机0.095+PCB+FET)
// #define MOTOR_L_Q               0.000361353f   // Q轴电感
// #define MOTOR_L_D               0.000335029f   // D轴电感
// #define MOTOR_L                 0.000348191f    // 相电感 (Henry)
// #define MAX_MOTOR_NUM           2               // 最大电机数量
#define POLE_PAIRS              7               // 电机极对数（示例：7对极）
#define CURRENT_LIMIT           20.0f           // 最大相电流(A)
#define MOTOR_R                 2.55f           // 相电阻含系统阻抗 (Ohm，电机0.095+PCB+FET)
#define MOTOR_L                 0.00086f    // 相电感 (Henry)
#define MAX_MOTOR_NUM           2               // 最大电机数量

// INA240参数   
#define INA240_GAIN             50             // INA240A2增益50V/V
#define SAMPLE_RESISTOR         0.01f         // 采样电阻10mΩ

// 开环参数
#define OPEN_LOOP_UQ            (PWM_VBUS * 0.45f) // 开环q轴强拉力度

// 观测器参数   
#define SMO_K                   15.0f            // 滑模增益 (根据实际效果调试)
#define BEMF_LPF                0.1f           // 反电动势低通滤波系数
#define SPEED_OBSERBER_LPF      0.05f           // 观测器求得的速度的低通滤波系数
#define COMP                    0.0f            // 偏移量
#define OB_SPEED_LIMIT          10000.0f         // 观测速度限幅
#define PLL_INIT_LIMIT          1500.0f         // PLL积分限幅4,673.521850899743
#define SAT_BOUNDARY            0.9f            // sat函数饱和边界

// 弱磁控制参数
#define CURRENT_PI_LIMIT        (PWM_VBUS * 0.95f / 1.732050807f) // 电流环电压输出限幅(V)
#define CURRENT_REF_LIMIT       (CURRENT_PI_LIMIT * 0.85f / MOTOR_R) // 当前母线电压和相电阻下建议的电流指令上限(A)
#define CURRENT_DEBUG_LIMIT     2.5f
#define CURRENT_TARGET_LIMIT    ((CURRENT_REF_LIMIT < CURRENT_DEBUG_LIMIT) ? CURRENT_REF_LIMIT : CURRENT_DEBUG_LIMIT)
#define FW_VOLTAGE_THRESHOLD    0.96f       // 触发弱磁的电压利用率（建议0.93~0.97）
#define FW_VOLTAGE_EXIT_THRESHOLD 0.88f     // 退出弱磁的电压利用率，低于进入阈值形成滞回
#define FW_KI                   1.0f       // 弱磁积分增益（越大响应越快，但可能振荡）
#define FW_EXIT_RATE            0.3f       // 退出弱磁时id恢复速率倍数（相对FW_KI）
#define FW_SPEED_MARGIN_RPM     150.0f      // 超过目标转速该余量后不再继续加深弱磁
#define FW_ID_MAX               (CURRENT_TARGET_LIMIT * 0.47f)        // 最大弱磁电流限幅（A）
#define FW_TARGET_HOLD_MARGIN_RPM 50.0f
#define FW_HOLD_KI_SCALE        0.10f

// PLL参数
#define PLL_KP                  170.0f      
#define PLL_KI                  5000.0f    
#define BTN7960_DEAD_TIME_S     0.0000005f 

// 电流环参数
#define CURRENT_LOOP_BANDWIDTH_HZ 700.0f       // 电流环带宽
#define CURRENT_LOOP_WC          (6.283185307f * CURRENT_LOOP_BANDWIDTH_HZ)
#define CURRENT_LOOP_STEP_LOW_A  0.2f                           // 电流环阶跃响应的低响应
#define CURRENT_LOOP_STEP_HIGH_A 2.0f                           // 电流环阶跃响应的高响应
#define PI_KP_D                 (MOTOR_L * CURRENT_LOOP_WC)
#define PI_KI_D                 (MOTOR_R * CURRENT_LOOP_WC)
#define PI_KP_Q                 (MOTOR_L * CURRENT_LOOP_WC)
#define PI_KI_Q                 (MOTOR_R * CURRENT_LOOP_WC)

// 速度环参数
#define FOC_SPEED_BASE_RPM      3000.0f        // 速度基值(rpm)，速度环标幺化用
#define PI_KP_SPEED             0.001f         // 速度PI比例系数(A/rpm，物理量)
#define PI_KI_SPEED             0.0084f          // 速度PI积分系数(A/rpm/s，物理量)
#define PI_LIMIT_SPEED          CURRENT_TARGET_LIMIT // 速度PI输出限幅(A)

// 位置环参数
#define PI_KP_POSITION          30.0f          // 位置PI比例系数(RPM/rad)
#define PI_KI_POSITION          1.0f           // 位置PI积分系数(RPM/rad/s)
#define PI_LIMIT_POSITION_RPM   100.0f         // 位置环输出速度限幅(RPM)
#define POSITION_DEADBAND_RAD   0.03f          // 位置到位死区(rad)
#define POSITION_OVERSPEED_RPM  600.0f         // 位置模式超速保护(RPM)

#define FOC_ELECTRICAL_ANGLE_OFFSET (-2.0f)    // 电角度偏移量，用于补偿编码器校准误差

// 高频注入参数
#define HFI_INJECTION_VOLTAGE   0.1f           // d轴高频注入电压(V)
#define HFI_INJECTION_FREQ      800.0f         // 高频注入频率(Hz)
#define HFI_IQ_LPF_ALPHA        0.05f          // q轴基波电流低通系数
#define HFI_DEMOD_LPF_ALPHA     0.03f          // 同步解调低通系数
#define HFI_PLL_KP              30.0f          // HFI角度PLL比例
#define HFI_PLL_KI              200.0f         // HFI角度PLL积分
#define HFI_PLL_LIMIT           120.0f         // HFI电角速度限幅(rad/s)
#define HFI_USE_SPEED_RPM       120.0f         // 低于该速度优先使用HFI角度
#define HFI_BLEND_END_RPM       250.0f         // 高于该速度回到SMO角度
#define HFI_MIN_RESPONSE        0.002f         // HFI解调响应有效阈值
#define HFI_WARMUP_CYCLES       1000           // HFI进入闭环后的滤波预热周期
#define HFI_ERROR_SIGN          1.0f           // 若角度越调越偏，改为-1.0f
#define HFI_IQ_HF_LIMIT         0.3f           // 高频电流保护阈值(A)

// 速度定义（分离开环和闭环）
// #define TARGET_SPEED            2000.0f         // 闭环最终目标(RPM)
#define OPEN_LOOP_SPEED_RPM     300.0f          // 开环启动速度(RPM)，必须是电机能跟上的
#define SPEED_RAMP_RATE         1000.0f          // 闭环加速斜率(RPM/s)
#define SPEED_START_THRESHOLD   50.0f   // RPM，低于此值视为停机指令

#ifdef __cplusplus
}
#endif

#endif 

