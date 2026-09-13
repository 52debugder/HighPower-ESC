/**
 * @file foc_types.h
 * @author MING
 * @brief 结构体定义文件
 * @version 0.1
 * @date 2026-03-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */


#ifndef __FOC_TYPEDEF_H
#define __FOC_TYPEDEF_H

#include "stdint.h"
#include "foc_config.h"
#include "foc_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************* 数据结构定义 *************************/
typedef enum {
    MOTOR_STATE_IDLE = 0,  // ← 新增：空闲/停机等待
    MOTOR_STATE_ALIGN, // 转子定位
    MOTOR_STATE_OPEN,      // 开环强拉
    MOTOR_STATE_CLOSE      // 闭环运行
} foc_mode_t;

typedef enum {
    FOC_CONTROL_SPEED = 0,
    FOC_CONTROL_POSITION
} foc_control_mode_t;

typedef enum
{
    FOC_OK = 0,                 // 正常
    FOC_ERR_LOOP,               // 循环中断
    FOC_ERR_NOT_INIT,           // 尚未初始化
    FOC_ERR_OVERCURRENT,        // 过流
    FOC_ERR_OVERVOLTAGE,        // 过压
    FOC_ERR_UNDERVOLTAGE,       // 过压
    FOC_ERR_ENCODER,            // 编码器错误
    FOC_ERR_HAL_NULL,           // HAL模块为空
    FOC_ERR_INVALID_PARAM,      // 无效参数
}foc_state_t;

typedef struct
{
  int16_t hCos;
  int16_t hSin;
}foc_Trig_Components;

typedef int16_t foc_q15_t;
typedef int32_t foc_accum_t;
typedef int16_t foc_angle16_t;

typedef struct
{
    foc_q15_t u;
    foc_q15_t v;
    foc_q15_t w;
}foc_uvw_fx_t;

typedef struct
{
    foc_q15_t alpha;
    foc_q15_t beta;
}foc_ab_fx_t;

typedef struct
{
    foc_q15_t d;
    foc_q15_t q;
}foc_dq_fx_t;

typedef struct {
    foc_accum_t kp;
    foc_accum_t ki_dt;
    foc_q15_t target;
    foc_q15_t feedback;
    foc_q15_t output;
    foc_q15_t limit;
    foc_accum_t integral;
} foc_pid_fx_t;

typedef struct {
    foc_accum_t kp;
    foc_accum_t ki_dt;
    foc_accum_t target;
    foc_accum_t feedback;
    foc_accum_t output;
    foc_accum_t limit;
    foc_accum_t integral;
} foc_pid_q16_t;

typedef struct
{
    float u;
    float v;
    float w;
}foc_uvw_t;

typedef struct
{
    float alpha;
    float beta;
}foc_ab_t;

typedef struct
{
    float d;
    float q;
}foc_dq_t;

typedef struct
{
    float k;            // 滑膜增益
    float bemf_lfp;     // 反电动势低通滤波系数
    float comp;         // 偏移量
}foc_smo_t;

typedef struct
{
    float pairs;        // 极对数
    float rs;           // 相电阻
    float ls;           // 相电感
    float a_limit;      // 相电流限幅
}foc_motor_params_t; 

// PI调节器结构体
typedef struct {
    float kp;            // 比例系数
    float ki;            // 积分系数
    float target;        // 目标值
    float feedback;      // 反馈值
    float output;        // 输出值
    float integral;      // 积分项
    float limit;         // 输出限幅
} foc_pid_t;

typedef struct
{
    uint16_t duty_u;
    uint16_t duty_v;
    uint16_t duty_w;
}foc_pwm_t;

typedef struct
{
    float angle;                    // 转子机械角度（rad）
    float speed;                    // 电机机械转速（rpm）
    float vaild;                    // 有效标志
    uint8_t dir;                    // 转向标志
    float zero_offset;              // 零偏
    uint32_t sample_seq;            // 当前采样序号
    uint32_t align_prev_sample_seq; // 对齐逻辑上一次处理过的采样序号
    float align_prev_angle;         // 上一次用于对比的角度  
    uint16_t align_stable_count;    // 连续稳定采样计数
    uint8_t align_has_prev;         // 是否已经拿到过第一帧样本
    uint8_t zero_offset_locked;     // 零偏是否锁定
}foc_sensor_mech_t;

typedef struct
{
    foc_hal_t               hal;
    foc_state_t             state;              // 运行状态
    uint8_t                 num;                // 电机编号

    foc_mode_t              mode;               // 运行模式
    foc_control_mode_t      control_mode;       // 控制模式
    foc_motor_params_t      motor;              // 电机参数
    foc_smo_t               smo;                // 滑膜观测器
    foc_pwm_t               pwm;                // PWM输出
    foc_sensor_mech_t       sensor_mech;        // 编码器测出的数据

    foc_uvw_t               i_uvw;              // 三相电流(p.u.)
    foc_uvw_t               i_cali_uvw;         // 相电流零偏原始计数
    foc_ab_t                i_ab;               // clarke变换后的电流(p.u.)
    foc_ab_t                i_ab_pre;           // 上一拍电流
    foc_dq_t                i_dq;               // park变换后的电流(p.u.)
    foc_ab_t                u_ab;               // 反park后的电压(p.u.)
    foc_ab_t                e_ab;               // 观测器中的反电动势/切换项(p.u.)
    foc_ab_t                i_ab_hat;           // 观测器估计电流(p.u.)
    foc_dq_t                u_dq;               // dq轴电压(p.u.)
    foc_uvw_fx_t            i_uvw_fx;           // 三相电流(Q15)
    foc_ab_fx_t             i_ab_fx;            // clarke变换后的电流(Q15)
    foc_dq_fx_t             i_dq_fx;            // park变换后的电流(Q15)
    foc_ab_fx_t             u_ab_fx;            // 反park后的电压(Q15)
    foc_dq_fx_t             u_dq_fx;            // dq轴电压(Q15)

    /*pid参数*/
    foc_pid_t               pi_d;               // d轴电流PI（输入/输出均为p.u.）
    foc_pid_t               pi_q;               // q轴电流PI（输入/输出均为p.u.）
    foc_pid_fx_t            pi_d_fx;            // d轴电流PI（Q15）
    foc_pid_fx_t            pi_q_fx;            // q轴电流PI（Q15）
    foc_pid_t               pi_speed;           // 速度PI（rpm -> A）
    foc_pid_q16_t           pi_speed_fx;        // 速度PI（Q16.16, rpm -> A）
    foc_pid_t               pi_position;        // 位置PI（rad -> rpm）
    foc_pid_q16_t           pi_position_fx;     // 位置PI（Q16.16, rad -> rpm）
    foc_pid_t               pi_pll;             // 锁相环PI（电角rad/s）

    uint16_t                i_adc_u;            // ADC锁存后的相电流采样原始计数
    uint16_t                i_adc_v;            // ADC锁存后的相电流采样原始计数
    uint16_t                i_adc_w;            // ADC锁存后的相电流采样原始计数
    float                   theta;              // 转子电角度(rad)
    foc_angle16_t           theta_fx;           // 转子电角度(Q15 turn-domain)
    float                   speed;              // 电机机械转速(rpm)
    float                   theta_Observer;     // 观测器得到的转子电角度(rad)
    float                   theta_obs_prev;     // 上一拍观测角度，用于微分估速
    float                   speed_observer;     // 观测器得到的电角速度(rad/s)
    float                   speed_sign;         // 电机转子正转还是反转

    float                   id_fw;              // 弱磁注入的负id(p.u.)
    float                   fw_active;          // 弱磁激活标志（调试用）
    float                   fw_voltage;         // 弱磁电压矢量幅值(p.u.)

    /*目标值*/      
    float                   target_iq;          // q轴电流目标值(p.u.)
    float                   target_id;          // d轴电流目标值(p.u.)
    float                   target_speed;       // 电机目标速度(rpm)
    float                   speed_ramp_target;  // 电机爬坡目标速度(rpm)
    float                   target_position;    // 电机目标机械位置(rad)
    float                   position_raw;       // 未扣零点的累计机械位置(rad)
    float                   position;           // 扣零后的累计机械位置(rad)
    float                   position_offset;    // 位置零点偏移(rad)
    float                   position_dir;       // 本次位置运动方向

    foc_Trig_Components     trig;              // 三角函数
    foc_q15_t               sin_theta_fx;      // Q15 sin缓存
    foc_q15_t               cos_theta_fx;      // Q15 cos缓存
    float                   sin_theta;         // 浮点sin缓存
    float                   cos_theta;         // 浮点cos缓存
    uint32_t                trig_sample_seq;   // trig缓存对应的传感器采样序号
    uint8_t                 trig_sample_valid; // trig缓存是否有效

    uint8_t                 hfi_enable;         // 高频注入使能
    uint8_t                 hfi_valid;          // 高频注入角度有效
    uint16_t                hfi_warmup_cnt;     // HFI滤波预热计数
    float                   theta_hfi;          // HFI估计电角度(rad)
    float                   theta_hfi_prev;     // HFI上一拍电角度(rad)
    float                   speed_hfi_observer; // HFI估计电角速度(rad/s)
    float                   hfi_pll_integral;   // HFI PLL积分项
    float                   hfi_phase;          // 注入信号相位(rad)
    float                   hfi_v_inj;          // 当前注入电压(p.u.)
    float                   hfi_iq_lpf;         // q轴低频电流估计(p.u.)
    float                   hfi_iq_hf;          // q轴高频电流分量(p.u.)
    float                   hfi_demod;          // 同步解调低通结果
    float                   hfi_error;          // HFI角度误差
    float                   hfi_blend;          // HFI角度权重

    /*运行计数*/
    uint32_t                state_timer;         // 运行状态定时器
    uint8_t                 PI_Speed_cnt;        // 速度PI计数
    uint8_t                 PI_Position_cnt;    // 位置pi计数
    uint32_t                close_cnt;           // 闭环计数

    uint8_t                 init_done;            // 初始化标志位
}foc_handle_t;

#ifdef __cplusplus
}
#endif



#endif // !__FOC_TYPEDEF_H


