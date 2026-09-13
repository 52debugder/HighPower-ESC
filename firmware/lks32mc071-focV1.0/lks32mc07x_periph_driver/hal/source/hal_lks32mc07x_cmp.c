#include "../include/hal_lksmcu_cmp.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"

/**
 *@brief ADC寄存器结构体句柄
 */
typedef struct
{
    volatile uint32_t IE;     ///< 0x00 比较器中断使能寄存器
    volatile uint32_t IF;     ///< 0x04 比较器中断标志寄存器
    volatile uint32_t TCLK;   ///< 0x08 比较器分频时钟控制寄存器
    volatile uint32_t CFG;    ///< 0x0C 比较器控制寄存器
    volatile uint32_t BLCWIN; ///< 0x10 比较器开窗控制寄存器
    volatile uint32_t DATA;   ///< 0x14 比较器输出数值寄存器
} CMP_TypeDef;
/**
 * @brief 模块复位
 * @param cmp_x 使用的CMP模块编号
 */
void HAL_CMP_Reset(HAL_CMP_x cmp_x)
{
    HAL_CMP_Disable(cmp_x);
}

/**
 * @brief 模块打开
 * @param cmp_x 使用的CMP模块编号
 */
void HAL_CMP_Enable(HAL_CMP_x cmp_x)
{
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    switch (cmp_x)
    {
        case HAL_CMP_0:
            HAL_REG_SET(SYS_AFE_REG5, SYS_AFE_REG5_CMP0PDN_BIT);
            HAL_REG_SET(HAL_CMP[0]->CFG, CMP_CFG_CMP0_IN_EN_BIT);
            break;
        case HAL_CMP_1:
            HAL_REG_SET(SYS_AFE_REG5, SYS_AFE_REG5_CMP1PDN_BIT);
            HAL_REG_SET(HAL_CMP[0]->CFG, CMP_CFG_CMP1_IN_EN_BIT);
            break;
        case HAL_CMP_2:
            HAL_REG_SET(SYS_AFE_REG5, SYS_AFE_REG5_CMP2PDN_BIT);
            HAL_REG_SET(HAL_CMP[0]->CFG, CMP_CFG_CMP2_IN_EN_BIT);
            break;
        default:
            break;
    }
    HAL_REG_SET(SYS_CLK_FEN, SYS_CLK_FEN_CMP_CLK_EN_BIT);
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 模块关闭
 * @param cmp_x 使用的CMP模块编号
 */
void HAL_CMP_Disable(HAL_CMP_x cmp_x)
{
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    switch (cmp_x)
    {
        case HAL_CMP_0:
            HAL_REG_RESET(SYS_AFE_REG5, SYS_AFE_REG5_CMP0PDN_BIT);
            HAL_REG_RESET(HAL_CMP[0]->CFG, CMP_CFG_CMP0_IN_EN_BIT);
            break;
        case HAL_CMP_1:
            HAL_REG_RESET(SYS_AFE_REG5, SYS_AFE_REG5_CMP1PDN_BIT);
            HAL_REG_RESET(HAL_CMP[0]->CFG, CMP_CFG_CMP1_IN_EN_BIT);
            break;
        case HAL_CMP_2:
            HAL_REG_RESET(SYS_AFE_REG5, SYS_AFE_REG5_CMP2PDN_BIT);
            HAL_REG_RESET(HAL_CMP[0]->CFG, CMP_CFG_CMP2_IN_EN_BIT);
            break;
        default:
            break;
    }
    HAL_REG_IF_WRITE(SYS_CLK_FEN, SYS_CLK_FEN_CMP_CLK_EN_BIT, !(SYS_AFE_REG5 & (SYS_AFE_REG5_CMP0PDN_BIT | SYS_AFE_REG5_CMP1PDN_BIT | SYS_AFE_REG5_CMP2PDN_BIT)));
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 模块关闭
 * @param cmp_x 使用的CMP模块编号
 * @param channel_p_x 正端通道
 * @param channel_n_x 负端通道
 */
void HAL_CMP_SetChannel(HAL_CMP_x cmp_x, HAL_CMP_CHANNEL_IPx channel_p_x, HAL_CMP_CHANNEL_INx channel_n_x)
{
    switch (cmp_x)
    {
        case HAL_CMP_0:
            // 系统寄存器解锁
            HAL_REG_SYS_UNLOCK();
            HAL_REG_WRITE_BIT_MASK_POS(SYS_AFE_REG3, SYS_AFE_REG3_CMP0_SELP, channel_p_x);
            HAL_REG_WRITE_BIT_MASK_POS(SYS_AFE_REG3, SYS_AFE_REG3_CMP0_SELN, channel_n_x);
            // 系统寄存器上锁
            HAL_REG_SYS_LOCK();
            break;
        case HAL_CMP_1:
            // 系统寄存器解锁
            HAL_REG_SYS_UNLOCK();
            HAL_REG_WRITE_BIT_MASK_POS(SYS_AFE_REG3, SYS_AFE_REG3_CMP1_SELP, channel_p_x);
            HAL_REG_WRITE_BIT_MASK_POS(SYS_AFE_REG3, SYS_AFE_REG3_CMP1_SELN, channel_n_x);
            // 系统寄存器上锁
            HAL_REG_SYS_LOCK();
            break;
        case HAL_CMP_2:
            // 系统寄存器解锁
            HAL_REG_SYS_UNLOCK();
            if (channel_p_x == HAL_CMP_CHANNEL_IP1)
            {
                HAL_REG_WRITE_BIT_MASK_POS(SYS_AFE_REG2, SYS_AFE_REG2_CMP2_SELP, 1);
            }
            else
            {
                HAL_REG_WRITE_BIT_MASK_POS(SYS_AFE_REG2, SYS_AFE_REG2_CMP2_SELP, channel_p_x);
            }
            HAL_REG_WRITE_BIT_MASK_POS(SYS_AFE_REG3, SYS_AFE_REG3_CMP2_SELN, channel_n_x);
            // 系统寄存器上锁
            HAL_REG_SYS_LOCK();
            break;
        default:
            break;
    }
}

/**
 * @brief 获取CMP模块的数字滤波宽度
 * @param cmp_x CMP模块编号
 * @param filter 滤波宽度
 * @return 实际滤波宽度
 */
uint32_t HAL_CMP_SetDigitalFilter(HAL_CMP_x cmpx, uint32_t filter)
{
    (void)cmpx;
    if (filter == 0)
    {
        HAL_REG_RESET(HAL_CMP[0]->TCLK, CMP_TCLK_COMM_DIV_MASK | CMP_TCLK_FIL2_CLK_DIV16_MASK | CMP_TCLK_CLK2_EN_BIT | CMP_TCLK_FIL2_CLK_DIV2_MASK | CMP_TCLK_FIL1_CLK_DIV16_MASK | CMP_TCLK_CLK1_EN_BIT | CMP_TCLK_FIL1_CLK_DIV2_MASK | CMP_TCLK_FIL0_CLK_DIV16_MASK | CMP_TCLK_CLK0_EN_BIT | CMP_TCLK_FIL0_CLK_DIV2_MASK);
    }
    else
    {
        uint16_t div_2 = 0;
        for (; filter > CMP_TCLK_FIL0_CLK_DIV16_MAX;)
        {
            filter >>= 1;
            div_2++;
        }
        if (div_2 > CMP_TCLK_FIL0_CLK_DIV2_MAX)
        {
            div_2  = CMP_TCLK_FIL0_CLK_DIV2_MAX;
            filter = CMP_TCLK_FIL0_CLK_DIV16_MAX;
        }
        HAL_REG_RESET(HAL_CMP[0]->TCLK, CMP_TCLK_COMM_DIV_MASK);
        HAL_REG_SET(HAL_CMP[0]->TCLK, CMP_TCLK_CLK0_EN_BIT | CMP_TCLK_CLK1_EN_BIT | CMP_TCLK_CLK2_EN_BIT);
        HAL_REG_WRITE_BIT_MASK_POS(HAL_CMP[0]->TCLK, CMP_TCLK_FIL0_CLK_DIV2, div_2);
        HAL_REG_WRITE_BIT_MASK_POS(HAL_CMP[0]->TCLK, CMP_TCLK_FIL0_CLK_DIV16, filter);
        HAL_REG_WRITE_BIT_MASK_POS(HAL_CMP[0]->TCLK, CMP_TCLK_FIL1_CLK_DIV2, div_2);
        HAL_REG_WRITE_BIT_MASK_POS(HAL_CMP[0]->TCLK, CMP_TCLK_FIL1_CLK_DIV16, filter);
        HAL_REG_WRITE_BIT_MASK_POS(HAL_CMP[0]->TCLK, CMP_TCLK_FIL2_CLK_DIV2, div_2);
        HAL_REG_WRITE_BIT_MASK_POS(HAL_CMP[0]->TCLK, CMP_TCLK_FIL2_CLK_DIV16, filter);

        filter = filter << div_2;
    }
    return filter;
}

/**
 * @brief 设置CMP模块工作模式
 * @param cmp_x CMP模块编号
 * @param mode_x 工作模式
 */
void HAL_CMP_SetMode(HAL_CMP_x cmp_x, HAL_CMP_MODE_x mode_x)
{
    switch (mode_x)
    {
        case HAL_CMP_MODE_RISING_EDGE: // 上升沿触发
            HAL_REG_SET(HAL_CMP[cmp_x]->CFG, CMP_CFG_CMP0_IRQ_TRIG_BIT);
            HAL_REG_RESET(HAL_CMP[cmp_x]->CFG, CMP_CFG_CMP0_POL_BIT);
            break;
        case HAL_CMP_MODE_FALLING_EDGE: // 下降沿触发
            HAL_REG_SET(HAL_CMP[cmp_x]->CFG, CMP_CFG_CMP0_IRQ_TRIG_BIT);
            HAL_REG_SET(HAL_CMP[cmp_x]->CFG, CMP_CFG_CMP0_POL_BIT);
            break;
        case HAL_CMP_MODE_HIGH_LEVEL: // 高电平有效
            HAL_REG_RESET(HAL_CMP[cmp_x]->CFG, CMP_CFG_CMP0_IRQ_TRIG_BIT);
            HAL_REG_RESET(HAL_CMP[cmp_x]->CFG, CMP_CFG_CMP0_POL_BIT);
            break;
        case HAL_CMP_MODE_LOW_LEVEL: // 低电平有效
            HAL_REG_RESET(HAL_CMP[cmp_x]->CFG, CMP_CFG_CMP0_IRQ_TRIG_BIT);
            HAL_REG_SET(HAL_CMP[cmp_x]->CFG, CMP_CFG_CMP0_POL_BIT);
            break;
    }
}
/**
 * @brief 设置CMP模块的GPIO
 * @param cmp_x cmp模块编号
 * @param cmpgpio GPIO编号
 */
void HAL_CMP_SetGpioOut(HAL_CMP_x cmp_x, HAL_GPIO_Px cmpgpio)
{
    (void)cmp_x;
    HAL_GPIO_SetAf(cmpgpio, HAL_GPIO_AF_CMP_OUT);
    HAL_GPIO_SetMode(cmpgpio, HAL_GPIO_MODE_OUT);
}

/**
 * @brief 设置CMP模块的GPIO
 * @param cmp_x CMP模块编号
 * @param cmpgpio GPIO编号
 */
void HAL_CMP_SetGpioIn(HAL_CMP_x cmp_x, HAL_GPIO_Px cmpgpio)
{
    (void)cmp_x;
    HAL_GPIO_SetAf(cmpgpio, HAL_GPIO_AF_CMP);
    HAL_GPIO_SetMode(cmpgpio, HAL_GPIO_MODE_AFE);
}

/**
 * @brief 获取CMP比较结果
 * @param cmp_x CMP模块编号
 * @return 比较结果
 */
uint8_t HAL_CMP_GetData(HAL_CMP_x cmp_x)
{
    uint32_t flg = 0;
    switch (cmp_x)
    {
        case HAL_CMP_0:
            if (HAL_REG_READ_BIT(HAL_CMP[0]->TCLK, CMP_TCLK_CLK0_EN_BIT))
            {
                // 打开滤波之后返回滤波后的结果
                flg = HAL_REG_READ_BIT(HAL_CMP[0]->DATA, CMP_DATA_CMP0_FLT_DATA_BIT);
            }
            else
            {
                // 如果没有配置滤波，则返回滤波前的结果
                flg = HAL_REG_READ_BIT(HAL_CMP[0]->DATA, CMP_DATA_CMP0_RAW_DATA_BIT);
            }
            break;
        case HAL_CMP_1:
            if (HAL_REG_READ_BIT(HAL_CMP[0]->TCLK, CMP_TCLK_CLK1_EN_BIT))
            {
                // 打开滤波之后返回滤波后的结果
                flg = HAL_REG_READ_BIT(HAL_CMP[0]->DATA, CMP_DATA_CMP1_FLT_DATA_BIT);
            }
            else
            {
                // 如果没有配置滤波，则返回滤波前的结果
                flg = HAL_REG_READ_BIT(HAL_CMP[0]->DATA, CMP_DATA_CMP1_RAW_DATA_BIT);
            }
            break;
        case HAL_CMP_2:
            if (HAL_REG_READ_BIT(HAL_CMP[0]->TCLK, CMP_TCLK_CLK2_EN_BIT))
            {
                // 打开滤波之后返回滤波后的结果
                flg = HAL_REG_READ_BIT(HAL_CMP[0]->DATA, CMP_DATA_CMP2_FLT_DATA_BIT);
            }
            else
            {
                // 如果没有配置滤波，则返回滤波前的结果
                flg = HAL_REG_READ_BIT(HAL_CMP[0]->DATA, CMP_DATA_CMP2_RAW_DATA_BIT);
            }
            break;
        default:
            break;
    }
    if (flg == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
 * @brief 设置比较器回差
 * @param cmp_x CMP模块编号(回差为所有CMP模块共用配置,与cmp_x无关,本参数保留暂不使用)
 * @param hys_x 回差选择
 */
void HAL_CMP_SetHysteresis(HAL_CMP_x cmp_x, HAL_CMP_HYS_x hys_x)
{
    (void)cmp_x;
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    HAL_REG_IF_WRITE(SYS_AFE_REG3, SYS_AFE_REG3_CMP_HYS_BIT, hys_x);
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}
