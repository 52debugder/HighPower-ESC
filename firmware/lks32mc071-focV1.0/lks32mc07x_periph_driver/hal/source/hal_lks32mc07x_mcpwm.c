#include "../include/hal_lksmcu_mcpwm.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_clk.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"

static uint16_t HAL_MCPWM_STATE[1][6]          = {{0, 0, 0, 0, 0, 0}};
static uint16_t HAL_MCPWM_STATE_INIT_FLG[1][6] = {{0, 0, 0, 0}}; // 初始化状态，只有对所有位都初始化完成后，才允许写入到IO中

static uint32_t HAL_MCPWM_FERQ[2] = {0};

/**
 * @brief 设置FAIL信号来源
 * @param mcpwm_x 操作的模块编号
 * @param fail_x FAIL通道
 * @param fail_in_x FAIL信号来源
 */
void HAL_MCPWM_UpdatePolarityState(HAL_MCPWM_x mcpwm_x, HAL_MCPWM_PORT_x mcpwm_port_x)
{
    uint8_t tmp[6]  = {0, 0, 0, 0, 0, 0};
    uint8_t tmp1[6] = {0, 0, 0, 0, 0, 0};
    uint32_t io_mask;

    HAL_MCPWM_OUTPUT_STATE_x out_state;

    if (HAL_REG_READ_BIT(HAL_MCPWM_STATE_INIT_FLG[0][mcpwm_port_x], HAL_MCPWM_STATE_SW_BIT) == 0)
    {
        return;
    }
    if (HAL_REG_READ_BIT(HAL_MCPWM_STATE_INIT_FLG[0][mcpwm_port_x], HAL_MCPWM_STATE_H_MOS_EN_BIT) == 0)
    {
        return;
    }
    if (HAL_REG_READ_BIT(HAL_MCPWM_STATE_INIT_FLG[0][mcpwm_port_x], HAL_MCPWM_STATE_L_MOS_EN_BIT) == 0)
    {
        return;
    }
    if (HAL_REG_READ_BIT(HAL_MCPWM_STATE_INIT_FLG[0][mcpwm_port_x], HAL_MCPWM_STATE_H_DEFAULT_BIT) == 0)
    {
        return;
    }
    if (HAL_REG_READ_BIT(HAL_MCPWM_STATE_INIT_FLG[0][mcpwm_port_x], HAL_MCPWM_STATE_L_DEFAULT_BIT) == 0)
    {
        return;
    }
    // 输出默认状态可以不配置，这里不对HAL_MCPWM_STATE_STATE_MASK进行判断，默认上下管上下管对称pwm
    // if (HAL_REG_READ_BIT(HAL_MCPWM_STATE_INIT_FLG[0][mcpwm_port_x], HAL_MCPWM_STATE_STATE_MASK) == 0)
    // {
    //     return;
    // }
    //  MCPWMx_IO01_CH0_PP_BIT MCPWMx_IO01_CH0_NP_BIT 是负逻辑
    HAL_REG_IF_WRITE(tmp1[mcpwm_port_x], MCPWM0_IO01_CH0_PN_SW_BIT, (HAL_MCPWM_STATE[0][mcpwm_port_x] & HAL_MCPWM_STATE_SW_BIT));     // 打开通道交换
    HAL_REG_IF_WRITE(tmp1[mcpwm_port_x], MCPWM0_IO01_CH0_PP_BIT, !(HAL_MCPWM_STATE[0][mcpwm_port_x] & HAL_MCPWM_STATE_H_MOS_EN_BIT)); // 上管高有效
    HAL_REG_IF_WRITE(tmp1[mcpwm_port_x], MCPWM0_IO01_CH0_NP_BIT, !(HAL_MCPWM_STATE[0][mcpwm_port_x] & HAL_MCPWM_STATE_L_MOS_EN_BIT)); // 下管高有效

    out_state = (HAL_MCPWM_OUTPUT_STATE_x)HAL_REG_READ_BIT_MASK_POS(HAL_MCPWM_STATE[0][mcpwm_port_x], HAL_MCPWM_STATE_STATE);
    switch (out_state)
    {
        case HAL_MCPWM_OUTPUT_STATE_PWM: ///< 上下管对称pwm
            tmp1[mcpwm_port_x] |= 0;
            break;
        case HAL_MCPWM_OUTPUT_STATE_OFF: ///< 关闭输出
            tmp1[mcpwm_port_x] |= MCPWM0_IO23_CH2_NS_BIT | MCPWM0_IO23_CH2_PS_BIT;
            break;
        case HAL_MCPWM_OUTPUT_STATE_LOW: ///< 下管恒开
            tmp1[mcpwm_port_x] |= MCPWM0_IO23_CH2_NS_BIT | MCPWM0_IO23_CH2_PS_BIT | MCPWM0_IO23_CH2_SCTRLN_BIT;
            break;
        case HAL_MCPWM_OUTPUT_STATE_HIGH: ///< 上管恒开
            tmp1[mcpwm_port_x] |= MCPWM0_IO23_CH2_NS_BIT | MCPWM0_IO23_CH2_PS_BIT | MCPWM0_IO23_CH2_SCTRLP_BIT;
            break;
        case HAL_MCPWM_OUTPUT_STATE_LOW_PWM: ///< 下管pwm
            tmp1[mcpwm_port_x] |= MCPWM0_IO23_CH2_PS_BIT;
            break;
        case HAL_MCPWM_OUTPUT_STATE_HIGH_PWM: ///< 上管pwm
            tmp1[mcpwm_port_x] |= MCPWM0_IO23_CH2_NS_BIT;
            break;
    }
    if (HAL_REG_READ_BIT(HAL_MCPWM_STATE[0][mcpwm_port_x], HAL_MCPWM_STATE_L_DEFAULT_BIT))
    {
        // 关机后上管打开
        if (HAL_REG_READ_BIT(HAL_MCPWM_STATE[0][mcpwm_port_x], HAL_MCPWM_STATE_SW_BIT)) // gpio交换使能
        {
            HAL_REG_IF_WRITE(tmp[mcpwm_port_x], MCPWM0_IO01_CH0_NP_BIT, (HAL_MCPWM_STATE[0][mcpwm_port_x] & HAL_MCPWM_STATE_H_MOS_EN_BIT));  // CH0 N 通道默认值
            HAL_REG_IF_WRITE(tmp[mcpwm_port_x], MCPWM0_IO01_CH0_PP_BIT, !(HAL_MCPWM_STATE[0][mcpwm_port_x] & HAL_MCPWM_STATE_L_MOS_EN_BIT)); // CH0 P 通道默认值
        }
        else
        {
            HAL_REG_IF_WRITE(tmp[mcpwm_port_x], MCPWM0_IO01_CH0_NP_BIT, !(HAL_MCPWM_STATE[0][mcpwm_port_x] & HAL_MCPWM_STATE_L_MOS_EN_BIT)); // CH0 N 通道默认值
            HAL_REG_IF_WRITE(tmp[mcpwm_port_x], MCPWM0_IO01_CH0_PP_BIT, (HAL_MCPWM_STATE[0][mcpwm_port_x] & HAL_MCPWM_STATE_H_MOS_EN_BIT));  // CH0 P 通道默认值
        }
    }
    else if (HAL_REG_READ_BIT(HAL_MCPWM_STATE[0][mcpwm_port_x], HAL_MCPWM_STATE_H_DEFAULT_BIT))
    {
        // 关机后下管打开
        if (HAL_REG_READ_BIT(HAL_MCPWM_STATE[0][mcpwm_port_x], HAL_MCPWM_STATE_SW_BIT)) // gpio交换使能
        {
            HAL_REG_IF_WRITE(tmp[mcpwm_port_x], MCPWM0_IO01_CH0_NP_BIT, !(HAL_MCPWM_STATE[0][mcpwm_port_x] & HAL_MCPWM_STATE_H_MOS_EN_BIT)); // CH0 N 通道默认值
            HAL_REG_IF_WRITE(tmp[mcpwm_port_x], MCPWM0_IO01_CH0_PP_BIT, (HAL_MCPWM_STATE[0][mcpwm_port_x] & HAL_MCPWM_STATE_L_MOS_EN_BIT));  // CH0 P 通道默认值
        }
        else
        {
            HAL_REG_IF_WRITE(tmp[mcpwm_port_x], MCPWM0_IO01_CH0_NP_BIT, (HAL_MCPWM_STATE[0][mcpwm_port_x] & HAL_MCPWM_STATE_L_MOS_EN_BIT));  // CH0 N 通道默认值
            HAL_REG_IF_WRITE(tmp[mcpwm_port_x], MCPWM0_IO01_CH0_PP_BIT, !(HAL_MCPWM_STATE[0][mcpwm_port_x] & HAL_MCPWM_STATE_H_MOS_EN_BIT)); // CH0 P 通道默认值
        }
    }
    else
    {
        // 关机后gpio悬空
        // 关机后下管打开
        if (HAL_REG_READ_BIT(HAL_MCPWM_STATE[0][mcpwm_port_x], HAL_MCPWM_STATE_SW_BIT)) // gpio交换使能
        {
            HAL_REG_IF_WRITE(tmp[mcpwm_port_x], MCPWM0_IO01_CH0_NP_BIT, !(HAL_MCPWM_STATE[0][mcpwm_port_x] & HAL_MCPWM_STATE_H_MOS_EN_BIT)); // CH0 N 通道默认值
            HAL_REG_IF_WRITE(tmp[mcpwm_port_x], MCPWM0_IO01_CH0_PP_BIT, !(HAL_MCPWM_STATE[0][mcpwm_port_x] & HAL_MCPWM_STATE_L_MOS_EN_BIT)); // CH0 P 通道默认值
        }
        else
        {
            HAL_REG_IF_WRITE(tmp[mcpwm_port_x], MCPWM0_IO01_CH0_NP_BIT, !(HAL_MCPWM_STATE[0][mcpwm_port_x] & HAL_MCPWM_STATE_L_MOS_EN_BIT)); // CH0 N 通道默认值
            HAL_REG_IF_WRITE(tmp[mcpwm_port_x], MCPWM0_IO01_CH0_PP_BIT, !(HAL_MCPWM_STATE[0][mcpwm_port_x] & HAL_MCPWM_STATE_H_MOS_EN_BIT)); // CH0 P 通道默认值
        }
    }

    io_mask = MCPWM0_IO01_CH0_PN_SW_BIT |
              MCPWM0_IO01_CH0_SCTRLP_BIT |
              MCPWM0_IO01_CH0_SCTRLN_BIT |
              MCPWM0_IO01_CH0_PS_BIT |
              MCPWM0_IO01_CH0_NS_BIT |
              MCPWM0_IO01_CH0_PP_BIT |
              MCPWM0_IO01_CH0_NP_BIT;

    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0xdead);
    switch (mcpwm_port_x)
    {
        case HAL_MCPWM_PORT_0:
            HAL_REG_IF_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->CH_DEF, MCPWM0_CH_DEF_CH0N_DEFAULT_BIT, tmp[0] & MCPWM0_IO01_CH0_NP_BIT); // 默认输出电平
            HAL_REG_IF_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->CH_DEF, MCPWM0_CH_DEF_CH0P_DEFAULT_BIT, tmp[0] & MCPWM0_IO01_CH0_PP_BIT); // 默认输出电平

            HAL_REG_WRITE_BIT(HAL_MCPWM[mcpwm_x & 0xf]->IO01, io_mask, tmp1[0]);
            break;
        case HAL_MCPWM_PORT_1:
            HAL_REG_IF_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->CH_DEF, MCPWM0_CH_DEF_CH1N_DEFAULT_BIT, tmp[1] & MCPWM0_IO01_CH0_NP_BIT); // 默认输出电平
            HAL_REG_IF_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->CH_DEF, MCPWM0_CH_DEF_CH1P_DEFAULT_BIT, tmp[1] & MCPWM0_IO01_CH0_PP_BIT); // 默认输出电平
            HAL_REG_WRITE_BIT(HAL_MCPWM[mcpwm_x & 0xf]->IO01, io_mask << 8, tmp1[1] << 8);
            break;
        case HAL_MCPWM_PORT_2:
            HAL_REG_IF_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->CH_DEF, MCPWM0_CH_DEF_CH2N_DEFAULT_BIT, tmp[2] & MCPWM0_IO01_CH0_NP_BIT); // 默认输出电平
            HAL_REG_IF_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->CH_DEF, MCPWM0_CH_DEF_CH2P_DEFAULT_BIT, tmp[2] & MCPWM0_IO01_CH0_PP_BIT); // 默认输出电平
            HAL_REG_WRITE_BIT(HAL_MCPWM[mcpwm_x & 0xf]->IO23, io_mask, tmp1[2]);
            break;
        case HAL_MCPWM_PORT_3:
            HAL_REG_IF_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->CH_DEF, MCPWM0_CH_DEF_CH3N_DEFAULT_BIT, tmp[3] & MCPWM0_IO01_CH0_NP_BIT); // 默认输出电平
            HAL_REG_IF_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->CH_DEF, MCPWM0_CH_DEF_CH3P_DEFAULT_BIT, tmp[3] & MCPWM0_IO01_CH0_PP_BIT); // 默认输出电平
            HAL_REG_WRITE_BIT(HAL_MCPWM[mcpwm_x & 0xf]->IO23, io_mask << 8, tmp1[3] << 8);
            break;
        case HAL_MCPWM_PORT_4:
            HAL_REG_IF_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->CH_DEF, MCPWM0_CH_DEF_CH4N_DEFAULT_BIT, tmp[4] & MCPWM0_IO01_CH0_NP_BIT); // 默认输出电平
            HAL_REG_IF_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->CH_DEF, MCPWM0_CH_DEF_CH4P_DEFAULT_BIT, tmp[4] & MCPWM0_IO01_CH0_PP_BIT); // 默认输出电平
            HAL_REG_WRITE_BIT(HAL_MCPWM[mcpwm_x & 0xf]->IO45, io_mask, tmp1[4]);
            break;
        case HAL_MCPWM_PORT_5:
            HAL_REG_IF_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->CH_DEF, MCPWM0_CH_DEF_CH5N_DEFAULT_BIT, tmp[5] & MCPWM0_IO01_CH0_NP_BIT); // 默认输出电平
            HAL_REG_IF_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->CH_DEF, MCPWM0_CH_DEF_CH5P_DEFAULT_BIT, tmp[5] & MCPWM0_IO01_CH0_PP_BIT); // 默认输出电平
            HAL_REG_WRITE_BIT(HAL_MCPWM[mcpwm_x & 0xf]->IO45, io_mask << 8, tmp1[5] << 8);
            break;
        default:
            break;
    }
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0);
}

/**
 * @brief 复位mcpwm模块
 * @param mcpwm_x 操作的模块编号
 */
void HAL_MCPWM_Reset(HAL_MCPWM_x mcpwm_x)
{
    (void)mcpwm_x;
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    HAL_REG_SET(SYS_SFT_RST, SYS_SFT_RST_MCPWM0_SFT_RST_BIT);
    HAL_REG_RESET(SYS_SFT_RST, SYS_SFT_RST_MCPWM0_SFT_RST_BIT);
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}

/**
 * @brief mcpwm模块使能
 * @param mcpwm_x 操作的模块编号
 */
void HAL_MCPWM_Enable(HAL_MCPWM_x mcpwm_x)
{
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    // SYS_CLK_FEN[4] MCPWM 模块整体时钟控制信号
    HAL_REG_SET(SYS_CLK_FEN, SYS_CLK_FEN_MCPWM0_CLK_EN_BIT);
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();

    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0xdead);
    HAL_REG_SET(HAL_MCPWM[mcpwm_x & 0xf]->TCLK, MCPWM0_TCLK_CLK_EN_BIT | MCPWM0_TCLK_TMR2_TB_BIT | MCPWM0_TCLK_TMR3_TB_BIT);
    HAL_REG_SET(HAL_MCPWM[mcpwm_x & 0xf]->AUEN, MCPWM0_AUEN_TH1_AUPDATE_BIT |
                                                    MCPWM0_AUEN_TMR3_AUPDATE_BIT |
                                                    MCPWM0_AUEN_TMR2_AUPDATE_BIT |
                                                    MCPWM0_AUEN_TH51_AUPDATE_BIT |
                                                    MCPWM0_AUEN_TH50_AUPDATE_BIT |
                                                    MCPWM0_AUEN_TH41_AUPDATE_BIT |
                                                    MCPWM0_AUEN_TH40_AUPDATE_BIT |
                                                    MCPWM0_AUEN_TH31_AUPDATE_BIT |
                                                    MCPWM0_AUEN_TH30_AUPDATE_BIT |
                                                    MCPWM0_AUEN_TH0_AUPDATE_BIT |
                                                    MCPWM0_AUEN_TMR1_AUPDATE_BIT |
                                                    MCPWM0_AUEN_TMR0_AUPDATE_BIT |
                                                    MCPWM0_AUEN_TH21_AUPDATE_BIT |
                                                    MCPWM0_AUEN_TH20_AUPDATE_BIT |
                                                    MCPWM0_AUEN_TH11_AUPDATE_BIT |
                                                    MCPWM0_AUEN_TH10_AUPDATE_BIT |
                                                    MCPWM0_AUEN_TH01_AUPDATE_BIT |
                                                    MCPWM0_AUEN_TH00_AUPDATE_BIT);
    HAL_REG_SET(HAL_MCPWM[mcpwm_x & 0xf]->SDCFG, MCPWM0_SDCFG_TR0_T0_UEN_BIT | MCPWM0_SDCFG_TR1_T0_UEN_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0);
}

/**
 * @brief mcpwm模块关闭
 * @param mcpwm_x 操作的模块编号
 */
void HAL_MCPWM_Disable(HAL_MCPWM_x mcpwm_x)
{
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0xdead);
    HAL_REG_RESET(HAL_MCPWM[mcpwm_x & 0xf]->TCLK, MCPWM0_TCLK_CLK_EN_BIT);
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0);
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    // SYS_CLK_FEN[4] MCPWM 模块整体时钟控制信号
    HAL_REG_RESET(SYS_CLK_FEN, SYS_CLK_FEN_MCPWM0_CLK_EN_BIT);
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 设置计数器最大值
 * @param mcpwm_x 操作的模块编号
 * @param th 最大值
 */
void HAL_MCPWM_SetThCnt(HAL_MCPWM_x mcpwm_x, uint32_t th)
{
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0xdead);

    if ((mcpwm_x & 0xf0) == HAL_MCPWM_0)
    {
        HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->TH0, th);
        HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->UPDATE, MCPWM0_UPDATE_TH0_UPDATE_BIT);
    }
    else
    {
        HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->TH1, th);
        HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->UPDATE, MCPWM0_UPDATE_TH1_UPDATE_BIT);
    }

    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0);
}
/**
 * @brief 设置pwm频率
 * @param mcpwm_x 操作的模块编号
 */
void HAL_MCPWM_SetFreq(HAL_MCPWM_x mcpwm_x, uint32_t freq)
{
    uint32_t mclk = HAL_MCPWM_GetClockFreq(mcpwm_x);
    uint32_t th0  = 0;
    uint32_t th1  = 0;
    uint32_t div  = 0;

    if ((mcpwm_x & 0xf0) == HAL_MCPWM_0)
    {
        HAL_MCPWM_FERQ[0] = freq;
    }
    else
    {
        HAL_MCPWM_FERQ[1] = freq;
    }
    if (HAL_MCPWM_FERQ[0] != 0)
    {
        th0 = ((mclk / HAL_MCPWM_FERQ[0]) - 1) / 2;
    }
    if (HAL_MCPWM_FERQ[1] != 0)
    {
        th1 = ((mclk / HAL_MCPWM_FERQ[1]) - 1) / 2;
    }

    for (; (th0 > MCPWM0_TH0_TH_MAX) || (th1 > MCPWM0_TH0_TH_MAX);)
    {
        th0 = th0 >> 1;
        th1 = th1 >> 1;
        div += 1;
        if (div > MCPWM0_TCLK_CLK_DIV_MAX)
        {
            div = MCPWM0_TCLK_CLK_DIV_MAX;
        }
    }

    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0xdead);
    HAL_REG_WRITE_BIT_MASK_POS(HAL_MCPWM[mcpwm_x & 0xf]->TCLK, MCPWM0_TCLK_CLK_DIV, div);

    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->TH0, th0);
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->TH1, th1);

    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->UPDATE, MCPWM0_UPDATE_TH0_UPDATE_BIT | MCPWM0_UPDATE_TH1_UPDATE_BIT);

    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0);
}

/**
 * @brief 获取pwm频率
 * @param mcpwm_x 操作的模块编号
 * @return 当前pwm的频率
 */
uint32_t HAL_MCPWM_GetFreq(HAL_MCPWM_x mcpwm_x)
{
    uint32_t mclk = HAL_MCPWM_GetClockFreq(mcpwm_x);
    uint16_t th;
    uint32_t freq;
    uint32_t div = HAL_REG_READ_BIT_MASK_POS(HAL_MCPWM[mcpwm_x & 0xf]->TCLK, MCPWM0_TCLK_CLK_DIV);
    if (mcpwm_x == HAL_MCPWM_0)
    {
        th = HAL_REG_READ(HAL_MCPWM[mcpwm_x & 0xf]->TH0);
    }
    else
    {
        th = HAL_REG_READ(HAL_MCPWM[mcpwm_x & 0xf]->TH1);
    }
    freq = (mclk >> div) / (th * 2 + 1);
    return freq;
}

// 设置时钟分频
void HAL_MCPWM_SetClockDiv(HAL_MCPWM_x mcpwm_x, uint32_t div)
{
    uint32_t shift = 0;
    while ((1u << shift) < div && shift < MCPWM0_TCLK_CLK_DIV_MAX)
    {
        shift++;
    }
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0xdead);
    HAL_REG_WRITE_BIT_MASK_POS(HAL_MCPWM[mcpwm_x & 0xf]->TCLK, MCPWM0_TCLK_CLK_DIV, shift);
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0);
}

// 获取时钟分频实际除数
uint32_t HAL_MCPWM_GetClockDiv(HAL_MCPWM_x mcpwm_x)
{
    return 1u << HAL_REG_READ_BIT_MASK_POS(HAL_MCPWM[mcpwm_x & 0xf]->TCLK, MCPWM0_TCLK_CLK_DIV);
}

// 获取分频后工作时钟
uint32_t HAL_MCPWM_GetClockFreq(HAL_MCPWM_x mcpwm_x)
{
    return HAL_CLK_GetMcuFreq() / HAL_MCPWM_GetClockDiv(mcpwm_x);
}

/**
 * @brief 获取计数器最大值
 * @param mcpwm_x 操作的模块编号
 */
uint32_t HAL_MCPWM_GetThCnt(HAL_MCPWM_x mcpwm_x)
{
    uint16_t th;
    if (mcpwm_x == HAL_MCPWM_0)
    {
        th = HAL_REG_READ(HAL_MCPWM[mcpwm_x & 0xf]->TH0);
    }
    else
    {
        th = HAL_REG_READ(HAL_MCPWM[mcpwm_x & 0xf]->TH1);
    }
    return th;
}

/**
 * @brief 设置死区
 * @param mcpwm_x 操作的模块编号
 * @param pdead_nS 下管关闭上管打开的死区宽度,单位nS
 * @param ndead_nS 上管关闭下管打开的死区宽度,单位nS
 */
void HAL_MCPWM_SetDead(HAL_MCPWM_x mcpwm_x, uint32_t pdead_nS, uint32_t ndead_nS)
{
    uint32_t mclk  = HAL_MCPWM_GetClockFreq(mcpwm_x);
    uint16_t pdead = (int64_t)pdead_nS * mclk / 1000000000;
    uint16_t ndead = (int64_t)ndead_nS * mclk / 1000000000;
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0xdead);
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->DTH00, pdead);
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->DTH01, ndead);
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->DTH10, pdead);
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->DTH11, ndead);
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0);
}

/**
 * @brief 关闭输出
 * @param mcpwm_x 操作的模块编号
 */
void HAL_MCPWM_SetOutputDisable(HAL_MCPWM_x mcpwm_x)
{
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0xdead);
    if (mcpwm_x == HAL_MCPWM_0)
    {
        HAL_REG_RESET(HAL_MCPWM[mcpwm_x & 0xf]->FAIL012, MCPWM0_FAIL012_MOE_BIT);
    }
    else
    {
        HAL_REG_RESET(HAL_MCPWM[mcpwm_x & 0xf]->FAIL345, MCPWM0_FAIL345_MOE_BIT);
    }
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0);
}

/**
 * @brief 打开输出
 * @param mcpwm_x 操作的模块编号
 */
void HAL_MCPWM_SetOutputEnable(HAL_MCPWM_x mcpwm_x)
{
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0xdead);
    if (mcpwm_x == HAL_MCPWM_0)
    {
        HAL_REG_SET(HAL_MCPWM[mcpwm_x & 0xf]->FAIL012, MCPWM0_FAIL012_MOE_BIT);
    }
    else
    {
        HAL_REG_SET(HAL_MCPWM[mcpwm_x & 0xf]->FAIL345, MCPWM0_FAIL345_MOE_BIT);
    }
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0);
}

/**
 * @brief 开始计数
 * @param mcpwm_x 操作的模块编号
 */
void HAL_MCPWM_StartCounting(HAL_MCPWM_x mcpwm_x)
{
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0xdead);
    if (mcpwm_x == HAL_MCPWM_0)
    {
        HAL_REG_SET(HAL_MCPWM[mcpwm_x & 0xf]->TCLK, MCPWM0_TCLK_BASE_CNT0_EN_BIT);
    }
    else
    {
        HAL_REG_SET(HAL_MCPWM[mcpwm_x & 0xf]->TCLK, MCPWM0_TCLK_BASE_CNT1_EN_BIT);
    }
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0);
}

/**
 * @brief 停止计数(同时计数器回到-th)
 * @param mcpwm_x 操作的模块编号
 */
void HAL_MCPWM_StopCounting(HAL_MCPWM_x mcpwm_x)
{
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0xdead);
    if (mcpwm_x == HAL_MCPWM_0)
    {
        HAL_REG_RESET(HAL_MCPWM[mcpwm_x & 0xf]->TCLK, MCPWM0_TCLK_BASE_CNT0_EN_BIT);
    }
    else
    {
        HAL_REG_RESET(HAL_MCPWM[mcpwm_x & 0xf]->TCLK, MCPWM0_TCLK_BASE_CNT1_EN_BIT);
    }
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0);
}

/**
 * @brief 跟随另一个计数器启动，周期不同时会自动映射相位差
 * @param mcpwm_x 操作的模块编号
 * @param mcpwm_x_followed 被跟随的模块编号
 * @param phase 相位差，0表示同相位，-32768或32767对应正交（执行时所有mcpwm都会暂停）
 */
void HAL_MCPWM_StartCountingSync(HAL_MCPWM_x mcpwm1_x, HAL_MCPWM_x mcpwm2_x, int16_t phase)
{
    HAL_MCPWM_StartCounting(mcpwm1_x);
    if (mcpwm1_x == mcpwm2_x)
    {
        return;
    }
    HAL_REG_WRITE(HAL_MCPWM[mcpwm1_x & 0xf]->PRT, 0xdead);
    if ((mcpwm1_x == HAL_MCPWM_0) && (mcpwm2_x == HAL_MCPWM_0_1))
    {
        uint32_t th0, th1, cnt0, phase0;
        HAL_REG_RESET(HAL_MCPWM[0]->TCLK, MCPWM0_TCLK_BASE_CNT0_EN_BIT | MCPWM0_TCLK_BASE_CNT1_EN_BIT);

        th0    = HAL_REG_READ(HAL_MCPWM[0]->CNT0);
        th1    = HAL_REG_READ(HAL_MCPWM[0]->CNT1);
        cnt0   = HAL_REG_READ(HAL_MCPWM[0]->CNT0);
        phase0 = cnt0 * 32768 / th0;
        phase  = (int16_t)(phase + phase0);

        HAL_REG_WRITE(HAL_MCPWM[0]->CNT1, (phase * th1) >> 15);
        HAL_REG_WRITE(HAL_MCPWM[0]->UPDATE, MCPWM0_UPDATE_CNT1_UPDATE_BIT);
        HAL_REG_RESET(HAL_MCPWM[0]->TCLK, MCPWM0_TCLK_BASE_CNT0_EN_BIT | MCPWM0_TCLK_BASE_CNT1_EN_BIT);
    }
    else if ((mcpwm1_x == HAL_MCPWM_0_1) && (mcpwm2_x == HAL_MCPWM_0))
    {
        uint32_t th0, th1, cnt1, phase1;
        HAL_REG_RESET(HAL_MCPWM[0]->TCLK, MCPWM0_TCLK_BASE_CNT0_EN_BIT | MCPWM0_TCLK_BASE_CNT1_EN_BIT);
        th0    = HAL_REG_READ(HAL_MCPWM[0]->CNT0);
        th1    = HAL_REG_READ(HAL_MCPWM[0]->CNT1);
        cnt1   = HAL_REG_READ(HAL_MCPWM[0]->CNT1);
        phase1 = cnt1 * 32768 / th1;
        phase  = (int16_t)(phase + phase1);
        HAL_REG_WRITE(HAL_MCPWM[0]->CNT0, (phase * th0) >> 15);
        HAL_REG_WRITE(HAL_MCPWM[0]->UPDATE, MCPWM0_UPDATE_CNT0_UPDATE_BIT);
        HAL_REG_RESET(HAL_MCPWM[0]->TCLK, MCPWM0_TCLK_BASE_CNT0_EN_BIT | MCPWM0_TCLK_BASE_CNT1_EN_BIT);
    }

    HAL_REG_WRITE(HAL_MCPWM[mcpwm2_x & 0xf]->PRT, 0);
}
/**
 * @brief 设置占空比
 * @param mcpwm_x 操作的模块编号
 * @param mcpwm_port_x 第x个pwm输出端口
 * @param t0 pwm打开时刻
 * @param t1 pwm关闭时刻
 */
void HAL_MCPWM_SetPwm(HAL_MCPWM_x mcpwm_x, HAL_MCPWM_PORT_x mcpwm_port_x, int32_t t0, int32_t t1)
{
    // 使用公式写可以在内联的情况下,实现和直接配置寄存器一样的效果
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->TH[mcpwm_port_x * 2], t0);
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->TH[mcpwm_port_x * 2 + 1], t1);
}
void HAL_MCPWM_SetPwmQ15(HAL_MCPWM_x mcpwm_x, HAL_MCPWM_PORT_x mcpwm_port_x, int16_t t0, int16_t t1)
{
    uint32_t th  = HAL_MCPWM_GetThCnt(mcpwm_x);
    int32_t cnt0 = (t0 * th) >> 15;
    int32_t cnt1 = (t1 * th) >> 15;
    HAL_MCPWM_SetPwm(mcpwm_x, mcpwm_port_x, cnt0, cnt1);
}

/**
 * @brief 设置输出状态
 * @param mcpwm_x 操作的模块编号
 * @param mcpwm_port_x 第x个pwm输出端口
 * @param mcpwm_output_state_x 输出状态
 */
void HAL_MCPWM_SetOutState(HAL_MCPWM_x mcpwm_x, HAL_MCPWM_PORT_x mcpwm_port_x, HAL_MCPWM_OUTPUT_STATE_x mcpwm_output_state_x)
{
    HAL_REG_WRITE_BIT_MASK_POS(HAL_MCPWM_STATE[mcpwm_x & 0xf][mcpwm_port_x], HAL_MCPWM_STATE_STATE, mcpwm_output_state_x);
    HAL_REG_SET(HAL_MCPWM_STATE_INIT_FLG[mcpwm_x & 0xf][mcpwm_port_x], HAL_MCPWM_STATE_STATE_MASK);

    HAL_MCPWM_UpdatePolarityState(mcpwm_x, mcpwm_port_x);
}

/**
 * @brief 设置pwm极性
 * @param mcpwm_x 操作的模块编号
 * @param mcpwm_polarity_x 第x个pwm输出端口
 */
void HAL_MCPWM_SetDrivePolarity(HAL_MCPWM_x mcpwm_x, HAL_MCPWM_POLARITY_x mcpwm_polarity_x)
{
    if (mcpwm_x == HAL_MCPWM_0)
    {
        HAL_MCPWM_SetDrivePolarityPort(mcpwm_x, HAL_MCPWM_PORT_0, mcpwm_polarity_x);
        HAL_MCPWM_SetDrivePolarityPort(mcpwm_x, HAL_MCPWM_PORT_1, mcpwm_polarity_x);
        HAL_MCPWM_SetDrivePolarityPort(mcpwm_x, HAL_MCPWM_PORT_2, mcpwm_polarity_x);
    }
    else
    {
        HAL_MCPWM_SetDrivePolarityPort(mcpwm_x, HAL_MCPWM_PORT_3, mcpwm_polarity_x);
        HAL_MCPWM_SetDrivePolarityPort(mcpwm_x, HAL_MCPWM_PORT_4, mcpwm_polarity_x);
        HAL_MCPWM_SetDrivePolarityPort(mcpwm_x, HAL_MCPWM_PORT_5, mcpwm_polarity_x);
    }
}
/**
 * @brief 设置单个输出通道的pwm极性
 * @param mcpwm_x 操作的模块编号
 * @param mcpwm_port_x 第x个pwm输出端口
 * @param mcpwm_polarity_x 输出极性
 */
void HAL_MCPWM_SetDrivePolarityPort(HAL_MCPWM_x mcpwm_x, HAL_MCPWM_PORT_x mcpwm_port_x, HAL_MCPWM_POLARITY_x mcpwm_polarity_x)
{
    HAL_REG_WRITE_BIT(HAL_MCPWM_STATE[mcpwm_x & 0xf][mcpwm_port_x], HAL_MCPWM_STATE_H_MOS_EN_BIT | HAL_MCPWM_STATE_L_MOS_EN_BIT, mcpwm_polarity_x << 1);
    HAL_REG_SET(HAL_MCPWM_STATE_INIT_FLG[mcpwm_x & 0xf][mcpwm_port_x], HAL_MCPWM_STATE_H_MOS_EN_BIT | HAL_MCPWM_STATE_L_MOS_EN_BIT);
    HAL_MCPWM_UpdatePolarityState(mcpwm_x, mcpwm_port_x);
}
/**
 * @brief 设置PN是否交换
 * @param mcpwm_x 操作的模块编号
 * @param mcpwm_swap_x PN是否交换
 */
void HAL_MCPWM_SetSwap(HAL_MCPWM_x mcpwm_x, HAL_MCPWM_SWAP_x mcpwm_swap_x)
{
    if (mcpwm_x == HAL_MCPWM_0)
    {
        HAL_MCPWM_SetSwapPort(mcpwm_x, HAL_MCPWM_PORT_0, mcpwm_swap_x);
        HAL_MCPWM_SetSwapPort(mcpwm_x, HAL_MCPWM_PORT_1, mcpwm_swap_x);
        HAL_MCPWM_SetSwapPort(mcpwm_x, HAL_MCPWM_PORT_2, mcpwm_swap_x);
    }
    else
    {
        HAL_MCPWM_SetSwapPort(mcpwm_x, HAL_MCPWM_PORT_3, mcpwm_swap_x);
        HAL_MCPWM_SetSwapPort(mcpwm_x, HAL_MCPWM_PORT_4, mcpwm_swap_x);
        HAL_MCPWM_SetSwapPort(mcpwm_x, HAL_MCPWM_PORT_5, mcpwm_swap_x);
    }
}
/**
 * @brief 设置单个输出通道的PN是否交换
 * @param mcpwm_x 操作的模块编号
 * @param mcpwm_port_x 第x个pwm输出端口
 * @param mcpwm_swap_x PN是否交换
 */
void HAL_MCPWM_SetSwapPort(HAL_MCPWM_x mcpwm_x, HAL_MCPWM_PORT_x mcpwm_port_x, HAL_MCPWM_SWAP_x mcpwm_swap_x)
{
    HAL_REG_IF_WRITE(HAL_MCPWM_STATE[mcpwm_x & 0xf][mcpwm_port_x], HAL_MCPWM_STATE_SW_BIT, mcpwm_swap_x);
    HAL_REG_SET(HAL_MCPWM_STATE_INIT_FLG[mcpwm_x & 0xf][mcpwm_port_x], HAL_MCPWM_STATE_SW_BIT);
    HAL_MCPWM_UpdatePolarityState(mcpwm_x, mcpwm_port_x);
}
/**
 * @brief MCPWM通道重映射(通道输出到GPIO的路由重排,与HAL_MCPWM_SetSwap的PN交换无关)
 * @param mcpwm_x 操作的模块编号
 * @param mode 0:片外预驱(默认排布) 1:封装排布1 2:封装排布2
 * @note mode 1适用型号(内置6N预驱): LKS32MC070FLRBT8、071DOC8T8、074FF8Q8、074DF8Q8、074DOF8Q8、076FNBQ8、078KUBQ8
 *       mode 2适用型号: LKS32MC072KBT8(兼容RX13T排布)
 *       其余型号用mode 0; 新增型号以最新数据手册为准
 */
void HAL_MCPWM_SetRemap(HAL_MCPWM_x mcpwm_x, uint8_t mode)
{
    (void)mcpwm_x;
    HAL_REG_WRITE(PWM_SWAP, (mode == 1) ? 0x67 : ((mode == 2) ? 0x69 : 0));
}

/**
 * @brief 设置默认状态
 * @param mcpwm_x 操作的模块编号
 * @param mcpwm_default_output_state_x 默认输出状态
 */
void HAL_MCPWM_SetDefaultState(HAL_MCPWM_x mcpwm_x, HAL_MCPWM_DEFAULT_OUTPUT_STATE_x mcpwm_default_output_state_x)
{
    uint32_t val = 0;
    switch (mcpwm_default_output_state_x)
    {
        case HAL_MCPWM_DEFAULT_OUTPUT_STATE_OFF:
            break;
        case HAL_MCPWM_DEFAULT_OUTPUT_STATE_LOW:
            HAL_REG_SET(val, HAL_MCPWM_STATE_L_DEFAULT_BIT);
            break;
        case HAL_MCPWM_DEFAULT_OUTPUT_STATE_HIGH:
            HAL_REG_SET(val, HAL_MCPWM_STATE_H_DEFAULT_BIT);
            break;
    }
    if (mcpwm_x == HAL_MCPWM_0)
    {
        HAL_REG_WRITE_BIT(HAL_MCPWM_STATE[mcpwm_x & 0xf][HAL_MCPWM_PORT_0], HAL_MCPWM_STATE_H_DEFAULT_BIT | HAL_MCPWM_STATE_L_DEFAULT_BIT, val);
        HAL_REG_WRITE_BIT(HAL_MCPWM_STATE[mcpwm_x & 0xf][HAL_MCPWM_PORT_1], HAL_MCPWM_STATE_H_DEFAULT_BIT | HAL_MCPWM_STATE_L_DEFAULT_BIT, val);
        HAL_REG_WRITE_BIT(HAL_MCPWM_STATE[mcpwm_x & 0xf][HAL_MCPWM_PORT_2], HAL_MCPWM_STATE_H_DEFAULT_BIT | HAL_MCPWM_STATE_L_DEFAULT_BIT, val);

        HAL_REG_SET(HAL_MCPWM_STATE_INIT_FLG[mcpwm_x & 0xf][HAL_MCPWM_PORT_0], HAL_MCPWM_STATE_H_DEFAULT_BIT | HAL_MCPWM_STATE_L_DEFAULT_BIT);
        HAL_REG_SET(HAL_MCPWM_STATE_INIT_FLG[mcpwm_x & 0xf][HAL_MCPWM_PORT_1], HAL_MCPWM_STATE_H_DEFAULT_BIT | HAL_MCPWM_STATE_L_DEFAULT_BIT);
        HAL_REG_SET(HAL_MCPWM_STATE_INIT_FLG[mcpwm_x & 0xf][HAL_MCPWM_PORT_2], HAL_MCPWM_STATE_H_DEFAULT_BIT | HAL_MCPWM_STATE_L_DEFAULT_BIT);

        HAL_MCPWM_UpdatePolarityState(mcpwm_x, HAL_MCPWM_PORT_0);
        HAL_MCPWM_UpdatePolarityState(mcpwm_x, HAL_MCPWM_PORT_1);
        HAL_MCPWM_UpdatePolarityState(mcpwm_x, HAL_MCPWM_PORT_2);
    }
    else
    {
        HAL_REG_WRITE_BIT(HAL_MCPWM_STATE[mcpwm_x & 0xf][HAL_MCPWM_PORT_3], HAL_MCPWM_STATE_H_DEFAULT_BIT | HAL_MCPWM_STATE_L_DEFAULT_BIT, val);
        HAL_REG_WRITE_BIT(HAL_MCPWM_STATE[mcpwm_x & 0xf][HAL_MCPWM_PORT_4], HAL_MCPWM_STATE_H_DEFAULT_BIT | HAL_MCPWM_STATE_L_DEFAULT_BIT, val);
        HAL_REG_WRITE_BIT(HAL_MCPWM_STATE[mcpwm_x & 0xf][HAL_MCPWM_PORT_5], HAL_MCPWM_STATE_H_DEFAULT_BIT | HAL_MCPWM_STATE_L_DEFAULT_BIT, val);

        HAL_REG_SET(HAL_MCPWM_STATE_INIT_FLG[mcpwm_x & 0xf][HAL_MCPWM_PORT_3], HAL_MCPWM_STATE_H_DEFAULT_BIT | HAL_MCPWM_STATE_L_DEFAULT_BIT);
        HAL_REG_SET(HAL_MCPWM_STATE_INIT_FLG[mcpwm_x & 0xf][HAL_MCPWM_PORT_4], HAL_MCPWM_STATE_H_DEFAULT_BIT | HAL_MCPWM_STATE_L_DEFAULT_BIT);
        HAL_REG_SET(HAL_MCPWM_STATE_INIT_FLG[mcpwm_x & 0xf][HAL_MCPWM_PORT_5], HAL_MCPWM_STATE_H_DEFAULT_BIT | HAL_MCPWM_STATE_L_DEFAULT_BIT);

        HAL_MCPWM_UpdatePolarityState(mcpwm_x, HAL_MCPWM_PORT_3);
        HAL_MCPWM_UpdatePolarityState(mcpwm_x, HAL_MCPWM_PORT_4);
        HAL_MCPWM_UpdatePolarityState(mcpwm_x, HAL_MCPWM_PORT_5);
    }
}

/**
 * @brief 设置用于输出的gpio
 * @param mcpwm_x MCPWM模块编号
 * @param px 使用的GPIO口
 */
void HAL_MCPWM_SetGpioOut(HAL_MCPWM_x mcpwm_x, HAL_GPIO_Px px)
{
    (void)mcpwm_x;
    HAL_GPIO_SetAf(px, HAL_GPIO_AF_MCPWM);
    HAL_GPIO_SetMode(px, HAL_GPIO_MODE_OUT);
}
/**
 * @brief 配置用于故障输入的gpio
 * @param mcpwm_x MCPWM模块编号
 * @param px 使用的GPIO口
 */
void HAL_MCPWM_SetGpioFail(HAL_MCPWM_x mcpwm_x, HAL_GPIO_Px px)
{
    (void)mcpwm_x;
    HAL_GPIO_SetAf(px, HAL_GPIO_AF_MCPWM);
    HAL_GPIO_SetMode(px, HAL_GPIO_MODE_IN);
}

/**
 * @brief 设置FAIL信号来源
 * @param mcpwm_x 操作的模块编号
 * @param fail_x FAIL信号来源
 */
void HAL_MCPWM_SetFailSignal(HAL_MCPWM_x mcpwm_x, HAL_MCPWM_FAIL_x fail_x, HAL_MCPWM_FAIL_IN_x fail_in_x)
{
    uint32_t fail_mask;
    uint32_t fail_val;

    if (fail_x == HAL_MCPWM_FAIL_0)
    {
        fail_mask = MCPWM0_FAIL012_FAIL0_EN_BIT | MCPWM0_FAIL012_FAIL0_POL_BIT | MCPWM0_FAIL012_FAIL0_SEL_MASK;

        switch (fail_in_x)
        {
            case HAL_MCPWM_FAIL_IN_IO_HIGH: ///< 外部FAIL信号为高电平后mcpwm关闭输出
                fail_val = MCPWM0_FAIL012_FAIL0_EN_BIT;
                break;
            case HAL_MCPWM_FAIL_IN_IO_LOW: ///< 外部FAIL信号为低电平后mcpwm关闭输出
                fail_val = MCPWM0_FAIL012_FAIL0_EN_BIT | MCPWM0_FAIL012_FAIL0_POL_BIT;
                break;
            case HAL_MCPWM_FAIL_IN_CMP0_HIGH: ///<  CMP0为高电平后mcpwm关闭输出
                fail_val = MCPWM0_FAIL012_FAIL0_EN_BIT | MCPWM0_FAIL012_FAIL0_SEL(1);
                break;
            case HAL_MCPWM_FAIL_IN_CMP0_LOW: ///<  CMP0为低电平后mcpwm关闭输出
                fail_val = MCPWM0_FAIL012_FAIL0_EN_BIT | MCPWM0_FAIL012_FAIL0_POL_BIT | MCPWM0_FAIL012_FAIL0_SEL(1);
                break;
            case HAL_MCPWM_FAIL_IN_CLU0_HIGH: ///<  CMP0为高电平后mcpwm关闭输出
                fail_val = MCPWM0_FAIL012_FAIL0_EN_BIT | MCPWM0_FAIL012_FAIL0_SEL(2);
                break;
            case HAL_MCPWM_FAIL_IN_CLU0_LOW: ///<  CMP0为低电平后mcpwm关闭输出
                fail_val = MCPWM0_FAIL012_FAIL0_EN_BIT | MCPWM0_FAIL012_FAIL0_POL_BIT | MCPWM0_FAIL012_FAIL0_SEL(2);
                break;
            case HAL_MCPWM_FAIL_IN_CLU1_HIGH: ///<  CMP0为高电平后mcpwm关闭输出
                fail_val = MCPWM0_FAIL012_FAIL0_EN_BIT | MCPWM0_FAIL012_FAIL0_SEL(3);
                break;
            case HAL_MCPWM_FAIL_IN_CLU1_LOW: ///<  CMP0为低电平后mcpwm关闭输出
                fail_val = MCPWM0_FAIL012_FAIL0_EN_BIT | MCPWM0_FAIL012_FAIL0_POL_BIT | MCPWM0_FAIL012_FAIL0_SEL(3);
                break;
            default:
                fail_val = 0;
                break;
        }
    }
    else
    {
        fail_mask = MCPWM0_FAIL012_FAIL1_EN_BIT | MCPWM0_FAIL012_FAIL1_POL_BIT | MCPWM0_FAIL012_FAIL1_SEL_MASK;

        switch (fail_in_x)
        {
            case HAL_MCPWM_FAIL_IN_IO_HIGH: ///< 外部FAIL信号为高电平后mcpwm关闭输出
                fail_val = MCPWM0_FAIL012_FAIL1_EN_BIT;
                break;
            case HAL_MCPWM_FAIL_IN_IO_LOW: ///< 外部FAIL信号为低电平后mcpwm关闭输出
                fail_val = MCPWM0_FAIL012_FAIL1_EN_BIT | MCPWM0_FAIL012_FAIL1_POL_BIT;
                break;
            case HAL_MCPWM_FAIL_IN_CMP0_HIGH: ///<  CMP0为高电平后mcpwm关闭输出
                fail_val = MCPWM0_FAIL012_FAIL1_EN_BIT | MCPWM0_FAIL012_FAIL1_SEL(1);
                break;
            case HAL_MCPWM_FAIL_IN_CMP0_LOW: ///<  CMP0为低电平后mcpwm关闭输出
                fail_val = MCPWM0_FAIL012_FAIL1_EN_BIT | MCPWM0_FAIL012_FAIL1_POL_BIT | MCPWM0_FAIL012_FAIL1_SEL(1);
                break;
            case HAL_MCPWM_FAIL_IN_CLU0_HIGH: ///<  CMP0为高电平后mcpwm关闭输出
                fail_val = MCPWM0_FAIL012_FAIL1_EN_BIT | MCPWM0_FAIL012_FAIL1_SEL(2);
                break;
            case HAL_MCPWM_FAIL_IN_CLU0_LOW: ///<  CMP0为低电平后mcpwm关闭输出
                fail_val = MCPWM0_FAIL012_FAIL1_EN_BIT | MCPWM0_FAIL012_FAIL1_POL_BIT | MCPWM0_FAIL012_FAIL1_SEL(2);
                break;
            case HAL_MCPWM_FAIL_IN_CLU1_HIGH: ///<  CMP0为高电平后mcpwm关闭输出
                fail_val = MCPWM0_FAIL012_FAIL1_EN_BIT | MCPWM0_FAIL012_FAIL1_SEL(3);
                break;
            case HAL_MCPWM_FAIL_IN_CLU1_LOW: ///<  CMP0为低电平后mcpwm关闭输出
                fail_val = MCPWM0_FAIL012_FAIL1_EN_BIT | MCPWM0_FAIL012_FAIL1_POL_BIT | MCPWM0_FAIL012_FAIL1_SEL(3);
                break;
            default:
                fail_val = 0;
                break;
        }
    }
    if (mcpwm_x == HAL_MCPWM_0)
    {
        HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0xdead);
        HAL_REG_WRITE_BIT(HAL_MCPWM[mcpwm_x & 0xf]->FAIL012, fail_mask, fail_val);
        HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0);
    }
    else if (mcpwm_x == HAL_MCPWM_0_1)
    {
        HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0xdead);
        HAL_REG_WRITE_BIT(HAL_MCPWM[mcpwm_x & 0xf]->FAIL345, fail_mask, fail_val);
        HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0);
    }
}
/**
 * @brief 设置pwm输出ADC采样时间
 * @param mcpwm_x 操作的模块编号
 * @param t0 采样时间
 * @param t1 采样时间
 */
void HAL_MCPWM_SetAdcTrig(HAL_MCPWM_x mcpwm_x, int32_t t0, int32_t t1)
{
    if (mcpwm_x == HAL_MCPWM_0)
    {
        HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->TMR0, t0);
        HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->TMR1, t1);
    }
    else
    {
        HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->TMR2, t0);
        HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->TMR3, t1);
    }
}
/**
 * @brief 设置pwm输出ADC采样时间q15格式输入
 * @param mcpwm_x 操作的模块编号
 * @param t0 采样时间q15格式输入
 * @param t1 采样时间q15格式输入
 */
void HAL_MCPWM_SetAdcTrigQ15(HAL_MCPWM_x mcpwm_x, int32_t t0, int32_t t1)
{
    uint32_t th  = HAL_MCPWM_GetThCnt(mcpwm_x);
    int16_t tmr0 = ((int32_t)t0 * th) >> 15;
    int16_t tmr1 = ((int32_t)t1 * th) >> 15;
    HAL_MCPWM_SetAdcTrig(mcpwm_x, tmr0, tmr1);
}
/**
 * @brief 设置FAIL信号滤波宽度
 * @param mcpwm_x 操作的模块编号
 * @param cnt 滤波宽度
 */
void HAL_MCPWM_SetFailFilter(HAL_MCPWM_x mcpwm_x, uint32_t cnt)
{
    cnt >>= 4;
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0xdead);
    HAL_REG_WRITE_BIT_MASK_POS(HAL_MCPWM[mcpwm_x & 0xf]->FLT, MCPWM0_FLT_FLT_CLKDIV, cnt);
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0);
}

/**
 * @brief 设置影子寄存器自动更新时刻
 * @param mcpwm_x 操作的模块编号
 * @param update_x 更新事件选择
 * @param intv 更新间隔0~15,每intv+1次更新事件加载一次,0表示每次事件都更新
 */
void HAL_MCPWM_SetUpdateMode(HAL_MCPWM_x mcpwm_x, HAL_MCPWM_UPDATE_x update_x, uint32_t intv)
{
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0xdead);
    if ((mcpwm_x & 0xf0) == HAL_MCPWM_0)
    {
        HAL_REG_RESET(HAL_MCPWM[mcpwm_x & 0xf]->SDCFG, MCPWM0_SDCFG_TR0_T0_UEN_BIT | MCPWM0_SDCFG_TR0_T1_UEN_BIT | MCPWM0_SDCFG_TR0_UP_INTV_MASK);
        if (update_x != HAL_MCPWM_UPDATE_T1)
        {
            HAL_REG_SET(HAL_MCPWM[mcpwm_x & 0xf]->SDCFG, MCPWM0_SDCFG_TR0_T0_UEN_BIT);
        }
        if (update_x != HAL_MCPWM_UPDATE_T0)
        {
            HAL_REG_SET(HAL_MCPWM[mcpwm_x & 0xf]->SDCFG, MCPWM0_SDCFG_TR0_T1_UEN_BIT);
        }
        HAL_REG_WRITE_BIT_MASK_POS(HAL_MCPWM[mcpwm_x & 0xf]->SDCFG, MCPWM0_SDCFG_TR0_UP_INTV, intv);
    }
    else
    {
        HAL_REG_RESET(HAL_MCPWM[mcpwm_x & 0xf]->SDCFG, MCPWM0_SDCFG_TR1_T0_UEN_BIT | MCPWM0_SDCFG_TR1_T1_UEN_BIT | MCPWM0_SDCFG_TR1_UP_INTV_MASK);
        if (update_x != HAL_MCPWM_UPDATE_T1)
        {
            HAL_REG_SET(HAL_MCPWM[mcpwm_x & 0xf]->SDCFG, MCPWM0_SDCFG_TR1_T0_UEN_BIT);
        }
        if (update_x != HAL_MCPWM_UPDATE_T0)
        {
            HAL_REG_SET(HAL_MCPWM[mcpwm_x & 0xf]->SDCFG, MCPWM0_SDCFG_TR1_T1_UEN_BIT);
        }
        HAL_REG_WRITE_BIT_MASK_POS(HAL_MCPWM[mcpwm_x & 0xf]->SDCFG, MCPWM0_SDCFG_TR1_UP_INTV, intv);
    }
    HAL_REG_WRITE(HAL_MCPWM[mcpwm_x & 0xf]->PRT, 0);
}
