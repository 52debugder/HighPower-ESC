/**
 * @file
 * @defgroup clu
 * @brief        CLU库函数
 * @author       YangZJ
 * @date         2023-02-27
 * @{
 */
#include "lks32mc07x_clu.h"
#include "lks32mc07x_user_manual.h"
/**
 * @brief CLU计算初始化
 */
void CLU_Init(CLU_TypeDef *CLUx, u8 CLU_MODEL_CLUx, CLU_InitTypeDef *this)
{
    CLU_Enable(CLUx);
    if ((CLU_MODEL_CLUx & CLU_MODEL_CLU0) != 0)
    {
        REG_IF_WRITE_BIT(CLUx->EN, CL0_EN0_C0EN_BIT, this->EN);           // CLUx 使能。默认关闭。 0: 关闭 1: 使能
        REG_IF_WRITE_BIT(CLUx->IE, CL0_IE0_C0FIE_BIT, this->FIE);         // CLUx 下降沿触发中断使能。默认关闭。 0: 关闭 1: 使能
        REG_IF_WRITE_BIT(CLUx->IE, CL0_IE0_C0RIE_BIT, this->RIE);         // CLUx 上升沿触发中断使能。默认关闭。 0: 关闭 1: 使能
        REG_WRITE_BIT_POS_MASK(CLUx->MX, CL0_MX0_C0MXA, this->MXA);       // CLUx A输入多路复用选择
        REG_WRITE_BIT_POS_MASK(CLUx->MX, CL0_MX0_C0MXB, this->MXB);       // CLUx B输入多路复用选择
        REG_WRITE_BIT_POS_MASK(CLUx->FN, CL0_FN0_C0FN, this->FN);         // CLUx 查找表功能选择。
        REG_IF_WRITE_BIT(CLUx->CF, CL0_CF0_C0OUTSEL_BIT, this->OUTSEL);   // CLUx 输出选取 0: D触发器输出 1: LUT输出
        REG_IF_WRITE_BIT(CLUx->CF, CL0_CF0_C0OEN_BIT, this->OEN);         // CLUx 输出使能。默认关闭。 0: 关闭 1: 使能
        REG_IF_WRITE_BIT(CLUx->CF, CL0_CF0_C0CLKINV_BIT, this->CLKINV);   // CLUx D触发器时钟电平反向。 0: 关闭 1: 使能
        REG_WRITE_BIT_POS_MASK(CLUx->CF, CL0_CF0_C0CLKSEL, this->CLKSEL); // CLUx D触发器时钟选择 。 0x0: 进位输入 0x1: MXA输入 0x2: ALTCLK0 0x3: ALTCLK1
        REG_SET(CLUx->CF, CL0_CF0_C0RST_BIT);                             // CLUx D触发器复位。该位写1复位。读取恒为0。
    }
    if ((CLU_MODEL_CLUx & CLU_MODEL_CLU1) != 0)
    {
        REG_IF_WRITE_BIT(CLUx->EN, CL0_EN0_C1EN_BIT, this->EN);           // CLUx 使能。默认关闭。 0: 关闭 1: 使能
        REG_IF_WRITE_BIT(CLUx->IE, CL0_IE0_C1FIE_BIT, this->FIE);         // CLUx 下降沿触发中断使能。默认关闭。 0: 关闭 1: 使能
        REG_IF_WRITE_BIT(CLUx->IE, CL0_IE0_C1RIE_BIT, this->RIE);         // CLUx 上升沿触发中断使能。默认关闭。 0: 关闭 1: 使能
        REG_WRITE_BIT_POS_MASK(CLUx->MX, CL0_MX0_C1MXA, this->MXA);       // CLUx A输入多路复用选择
        REG_WRITE_BIT_POS_MASK(CLUx->MX, CL0_MX0_C1MXB, this->MXB);       // CLUx B输入多路复用选择
        REG_WRITE_BIT_POS_MASK(CLUx->FN, CL0_FN0_C1FN, this->FN);         // CLUx 查找表功能选择。
        REG_IF_WRITE_BIT(CLUx->CF, CL0_CF0_C1OUTSEL_BIT, this->OUTSEL);   // CLUx 输出选取 0: D触发器输出 1: LUT输出
        REG_IF_WRITE_BIT(CLUx->CF, CL0_CF0_C1OEN_BIT, this->OEN);         // CLUx 输出使能。默认关闭。 0: 关闭 1: 使能
        REG_IF_WRITE_BIT(CLUx->CF, CL0_CF0_C1CLKINV_BIT, this->CLKINV);   // CLUx D触发器时钟电平反向。 0: 关闭 1: 使能
        REG_WRITE_BIT_POS_MASK(CLUx->CF, CL0_CF0_C1CLKSEL, this->CLKSEL); // CLUx D触发器时钟选择 。 0x0: 进位输入 0x1: MXA输入 0x2: ALTCLK0 0x3: ALTCLK1
        REG_SET(CLUx->CF, CL0_CF0_C1RST_BIT);                             // CLUx D触发器复位。该位写1复位。读取恒为0。
    }
    if ((CLU_MODEL_CLUx & CLU_MODEL_CLU2) != 0)
    {
        REG_IF_WRITE_BIT(CLUx->EN, CL0_EN0_C2EN_BIT, this->EN);           // CLUx 使能。默认关闭。 0: 关闭 1: 使能
        REG_IF_WRITE_BIT(CLUx->IE, CL0_IE0_C2FIE_BIT, this->FIE);         // CLUx 下降沿触发中断使能。默认关闭。 0: 关闭 1: 使能
        REG_IF_WRITE_BIT(CLUx->IE, CL0_IE0_C2RIE_BIT, this->RIE);         // CLUx 上升沿触发中断使能。默认关闭。 0: 关闭 1: 使能
        REG_WRITE_BIT_POS_MASK(CLUx->MX, CL0_MX0_C2MXA, this->MXA);       // CLUx A输入多路复用选择
        REG_WRITE_BIT_POS_MASK(CLUx->MX, CL0_MX0_C2MXB, this->MXB);       // CLUx B输入多路复用选择
        REG_WRITE_BIT_POS_MASK(CLUx->FN, CL0_FN0_C2FN, this->FN);         // CLUx 查找表功能选择。
        REG_IF_WRITE_BIT(CLUx->CF, CL0_CF0_C2OUTSEL_BIT, this->OUTSEL);   // CLUx 输出选取 0: D触发器输出 1: LUT输出
        REG_IF_WRITE_BIT(CLUx->CF, CL0_CF0_C2OEN_BIT, this->OEN);         // CLUx 输出使能。默认关闭。 0: 关闭 1: 使能
        REG_IF_WRITE_BIT(CLUx->CF, CL0_CF0_C2CLKINV_BIT, this->CLKINV);   // CLUx D触发器时钟电平反向。 0: 关闭 1: 使能
        REG_WRITE_BIT_POS_MASK(CLUx->CF, CL0_CF0_C2CLKSEL, this->CLKSEL); // CLUx D触发器时钟选择 。 0x0: 进位输入 0x1: MXA输入 0x2: ALTCLK0 0x3: ALTCLK1
        REG_SET(CLUx->CF, CL0_CF0_C2RST_BIT);                             // CLUx D触发器复位。该位写1复位。读取恒为0。
    }
    if ((CLU_MODEL_CLUx & CLU_MODEL_CLU3) != 0)
    {
        REG_IF_WRITE_BIT(CLUx->EN, CL0_EN0_C3EN_BIT, this->EN);           // CLUx 使能。默认关闭。 0: 关闭 1: 使能
        REG_IF_WRITE_BIT(CLUx->IE, CL0_IE0_C3FIE_BIT, this->FIE);         // CLUx 下降沿触发中断使能。默认关闭。 0: 关闭 1: 使能
        REG_IF_WRITE_BIT(CLUx->IE, CL0_IE0_C3RIE_BIT, this->RIE);         // CLUx 上升沿触发中断使能。默认关闭。 0: 关闭 1: 使能
        REG_WRITE_BIT_POS_MASK(CLUx->MX, CL0_MX0_C3MXA, this->MXA);       // CLUx A输入多路复用选择
        REG_WRITE_BIT_POS_MASK(CLUx->MX, CL0_MX0_C3MXB, this->MXB);       // CLUx B输入多路复用选择
        REG_WRITE_BIT_POS_MASK(CLUx->FN, CL0_FN0_C3FN, this->FN);         // CLUx 查找表功能选择。
        REG_IF_WRITE_BIT(CLUx->CF, CL0_CF0_C3OUTSEL_BIT, this->OUTSEL);   // CLUx 输出选取 0: D触发器输出 1: LUT输出
        REG_IF_WRITE_BIT(CLUx->CF, CL0_CF0_C3OEN_BIT, this->OEN);         // CLUx 输出使能。默认关闭。 0: 关闭 1: 使能
        REG_IF_WRITE_BIT(CLUx->CF, CL0_CF0_C3CLKINV_BIT, this->CLKINV);   // CLUx D触发器时钟电平反向。 0: 关闭 1: 使能
        REG_WRITE_BIT_POS_MASK(CLUx->CF, CL0_CF0_C3CLKSEL, this->CLKSEL); // CLUx D触发器时钟选择 。 0x0: 进位输入 0x1: MXA输入 0x2: ALTCLK0 0x3: ALTCLK1
        REG_SET(CLUx->CF, CL0_CF0_C3RST_BIT);                             // CLUx D触发器复位。该位写1复位。读取恒为0。
    }
}
/**
 * @brief CLU初始化结构体初始化
 */
void CLU_StructInit(CLU_InitTypeDef *this)
{
    this->FIE    = 0; ///< 下降沿中断使能
    this->RIE    = 0; ///< 上升沿中断使能
    this->EN     = 0; ///< 模块使能 0关闭模块 1打开模块
    this->MXA    = 0; ///< A输入复用选择 格式 CLU_MXA_CLUa_b a取值范围为[0 1 2 3] 对应不同的CLU b表示选择不同的输入信号
    this->MXB    = 0; ///< B输入复用选择 格式 CLU_MXB_CLUa_b a取值范围为[0 1 2 3] 对应不同的CLU b表示选择不同的输入信号
    this->FN     = 0; ///< 真值表 格式 CLU_FN_x x取值范围为[A NOTA A_NOTB ...]对应为最简与或式下的最小相 例如 y=a+bc+!c 表示为 CLU_FN_A|CLU_FN_B_C|CLU_FN_NOTC
    this->OUTSEL = 0; ///< 输出选择 0: D 触发器输出 1: LUT 输出
    this->OEN    = 0; ///< 输出使能 0: 关闭 1: 使能
    this->CLKINV = 0; ///< D 触发器时钟电平 0: 同相 1: 反向
    this->CLKSEL = 0; ///< D 触发器时钟选择 0x0: 进位输入 0x1: MXA 输入 0x2: ALTCLK0 0x3: ALTCLK1
}
/**
 * @brief CLU模块时钟使能
 */
void CLU_Enable(CLU_TypeDef *CLUx)
{
    (void)CLUx;
    SYS_ModuleClockCmd(SYS_Module_CL0, ENABLE);
}
/**
 * @brief CLU模块时钟关闭
 */
void CLU_Disable(CLU_TypeDef *CLUx)
{
    (void)CLUx;
    SYS_ModuleClockCmd(SYS_Module_CL0, DISABLE);
}
/**
 * @brief 获取CLU的输出值
 */
u8 CLU_ReadOutVolue(CLU_TypeDef *CLUx, u8 CLU_MODEL_CLUx)
{
    u8 OutVolue;
    if (CLUx->OUT & CLU_MODEL_CLUx)
    {
        OutVolue = 1;
    }
    else
    {
        OutVolue = 0;
    }
    return OutVolue;
}

/*! @} */
