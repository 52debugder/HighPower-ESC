
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lksmcu_clk.h"
#include "../include/hal_lksmcu_can.h"
#include "../hal_lks32mc07x.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lks32mc07x_reg.h"

static uint32_t hal_rx_id[1]    = {0};
static uint8_t hal_rx_ide[1]    = {0};
static uint8_t hal_rx_rtr[1]    = {0};
static uint8_t hal_rx_len[1]    = {0};
static uint8_t hal_rx_buf[1][8] = {0};

static void Set_CFG_STAT(HAL_CAN_x can_x, u32 bitValue);
static void Reset_CFG_STAT(HAL_CAN_x can_x, u32 bitValue);
static void Delay(uint32_t cnt);

static bool GetBaudParam(u32 baud, u8 *presc, u8 *sjw, u8 *seg1, u8 *seg2);
static void CAN_Write_TBUF(HAL_CAN_x can_x, u32 id, HAL_CAN_FRAME_x frame_x, u8 *msg, u8 len);

/* 模块复位 */
void HAL_CAN_Reset(HAL_CAN_x can_x)
{
    switch (can_x)
    {
        case HAL_CAN_0:
            // 系统寄存器解锁
            HAL_REG_SYS_UNLOCK();
            HAL_REG_SET(SYS_SFT_RST, SYS_SFT_RST_CAN0_SFT_RST_BIT);
            HAL_REG_RESET(SYS_SFT_RST, SYS_SFT_RST_CAN0_SFT_RST_BIT);
            // 系统寄存器上锁
            HAL_REG_SYS_LOCK();

            Set_CFG_STAT(can_x, CAN_CFG_STAT_RESET_BIT);
            Reset_CFG_STAT(can_x, CAN_CFG_STAT_RESET_BIT);
            break;
        default:
            break;
    }
}

/* 模块使能 */
void HAL_CAN_Enable(HAL_CAN_x can_x)
{
    switch (can_x)
    {
        case HAL_CAN_0:
            // 系统寄存器解锁
            HAL_REG_SYS_UNLOCK();
            HAL_REG_SET(SYS_CLK_FEN, SYS_CLK_FEN_CAN0_CLK_EN_BIT);
            // 系统寄存器上锁
            HAL_REG_SYS_LOCK();

            Reset_CFG_STAT(can_x, CAN_CFG_STAT_RESET_BIT);
            break;
        default:
            break;
    }
}

/* 模块关闭 */
void HAL_CAN_Disable(HAL_CAN_x can_x)
{
    switch (can_x)
    {
        case HAL_CAN_0:
            // 系统寄存器解锁
            HAL_REG_SYS_UNLOCK();
            HAL_REG_RESET(SYS_CLK_FEN, SYS_CLK_FEN_CAN0_CLK_EN_BIT);
            // 系统寄存器上锁
            HAL_REG_SYS_LOCK();

            Set_CFG_STAT(can_x, CAN_CFG_STAT_RESET_BIT);
            break;
        default:
            break;
    }
}

void HAL_CAN_SetBaud(HAL_CAN_x can_x, uint32_t baud)
{
    u8 s_presc, s_sjw, s_seg1, s_seg2;

    Set_CFG_STAT(can_x, CAN_CFG_STAT_RESET_BIT); // 复位模式

    if (baud > 0 && GetBaudParam(baud, &s_presc, &s_sjw, &s_seg1, &s_seg2))
    {
        HAL_REG_WRITE(HAL_CAN[can_x]->SBAUD, CAN_SBAUD_S_PRESC(s_presc) | CAN_SBAUD_S_SJW(s_sjw) | CAN_SBAUD_S_SEG_2(s_seg2) | CAN_SBAUD_S_SEG_1(s_seg1));
    }

    Reset_CFG_STAT(can_x, CAN_CFG_STAT_RESET_BIT); // 正常输出模式
    Delay(100);
}

// 07x不支持FD
void HAL_CAN_SetFastBaud(HAL_CAN_x can_x, uint32_t fbaud)
{
    (void)can_x;
    (void)fbaud;
}

// 设置CAN预分频 (只改S_PRESC，位时序参数不变)
void HAL_CAN_SetClockDiv(HAL_CAN_x can_x, uint32_t div)
{
    if (div < 1) div = 1;
    Set_CFG_STAT(can_x, CAN_CFG_STAT_RESET_BIT);
    HAL_REG_WRITE_BIT_MASK_POS(HAL_CAN[can_x]->SBAUD, CAN_SBAUD_S_PRESC, div - 1);
    Reset_CFG_STAT(can_x, CAN_CFG_STAT_RESET_BIT);
    Delay(100);
}

// 获取CAN预分频实际除数
uint32_t HAL_CAN_GetClockDiv(HAL_CAN_x can_x)
{
    return HAL_REG_READ_BIT_MASK_POS(HAL_CAN[can_x]->SBAUD, CAN_SBAUD_S_PRESC) + 1;
}

// 获取分频后工作时钟
uint32_t HAL_CAN_GetClockFreq(HAL_CAN_x can_x)
{
    return HAL_CLK_GetMcuFreq() / HAL_CAN_GetClockDiv(can_x);
}

// 获取当前标称波特率
uint32_t HAL_CAN_GetBaud(HAL_CAN_x can_x)
{
    uint32_t clk  = HAL_CAN_GetClockFreq(can_x);
    uint32_t seg1 = HAL_REG_READ_BIT_MASK_POS(HAL_CAN[can_x]->SBAUD, CAN_SBAUD_S_SEG_1);
    uint32_t seg2 = HAL_REG_READ_BIT_MASK_POS(HAL_CAN[can_x]->SBAUD, CAN_SBAUD_S_SEG_2);
    return clk / (1 + (seg1 + 2) + (seg2 + 1));
}

void HAL_CAN_SetTDC(HAL_CAN_x can_x, uint8_t sspoff)
{
    (void)can_x;
    (void)sspoff;
}

bool HAL_CAN_TxData(HAL_CAN_x can_x, uint32_t id, HAL_CAN_FRAME_x frame_x, uint8_t *buf, uint32_t len)
{
    // PTB发送，先判断发送是否空闲
    if (HAL_CAN_Txing(can_x))
    {
        return false;
    }

    HAL_REG_RESET(HAL_CAN[can_x]->TCMD, CAN_TCMD_TBSEL_BIT);
    CAN_Write_TBUF(can_x, id, frame_x, buf, len);
    HAL_REG_SET(HAL_CAN[can_x]->TCMD, CAN_TCMD_TPE_BIT);

    return true;
}

/* STB方式发送数据，仅写数据 */
bool HAL_CAN_TxData_STBWrite(HAL_CAN_x can_x, uint32_t id, HAL_CAN_FRAME_x frame_x, uint8_t *buf, uint32_t len)
{
    if (HAL_CAN_STBFull(can_x))
    {
        return false; // 发送失败，STB满
    }

    // STB发送
    HAL_REG_SET(HAL_CAN[can_x]->TCMD, CAN_TCMD_TBSEL_BIT);
    CAN_Write_TBUF(can_x, id, frame_x, buf, len);
    HAL_REG_SET(HAL_CAN[can_x]->TCTRL, CAN_TCTRL_TSNEXT_BIT); // 置位TSNEXT，更新STB slot位置

    return true; // STB添加成功即返回，还需调用CAN_Send_Trig触发发送
}

/* STB方式发送数据，触发发送 */
bool HAL_CAN_TxData_STBTrig(HAL_CAN_x can_x, HAL_CAN_STBTrig_x trig)
{
    if (HAL_CAN_Txing(can_x))
    {
        return false;
    }

    if (trig == HAL_CAN_STBTrig_One)
    {
        HAL_REG_SET(HAL_CAN[can_x]->TCMD, CAN_TCMD_TSONE_BIT);
    }
    else if (trig == HAL_CAN_STBTrig_All)
    {
        HAL_REG_SET(HAL_CAN[can_x]->TCMD, CAN_TCMD_TSALL_BIT);
    }

    return true;
}

void HAL_CAN_TxCancel(HAL_CAN_x can_x)
{
    HAL_REG_SET(HAL_CAN[can_x]->TCMD, CAN_TCMD_TPA_BIT);
    HAL_REG_SET(HAL_CAN[can_x]->TCMD, CAN_TCMD_TSA_BIT);
}

bool HAL_CAN_Txing(HAL_CAN_x can_x)
{
    return HAL_REG_READ_BIT(HAL_CAN[can_x]->TCMD, CAN_TCMD_TPE_BIT | CAN_TCMD_TSONE_BIT | CAN_TCMD_TSALL_BIT);
}

bool HAL_CAN_STBFull(HAL_CAN_x can_x)
{
    return HAL_CAN_TSStat(can_x) == HAL_CAN_TSSTAT_Full;
}

HAL_CAN_TSSTAT_x HAL_CAN_TSStat(HAL_CAN_x can_x)
{
    uint8_t tsstat = HAL_REG_READ_BIT_MASK_POS(HAL_CAN[can_x]->TCTRL, CAN_TCTRL_TSSTAT);

    return (HAL_CAN_TSSTAT_x)tsstat;
}

/*
 * 从接收缓冲区读出数据，暂存到全局变量中
 * 返回值：成功读到数据返回1，无数据返回0
 */
bool HAL_CAN_RxData(HAL_CAN_x can_x)
{
    u8 reg_inf;
    u8 dlc = 0;
    u16 rbufx;
    u8 x;

    // if ((CAN_RCTRL & 0x03) > 0) /*Rx Buffer存有一帧或多帧数据，可以通过 RFIFO 寄存器读取*/
    if (HAL_REG_READ_BIT_MASK_POS(HAL_CAN[can_x]->RCTRL, CAN_RCTRL_RSTAT) > 0)
    {
        // reg_inf = CAN_RBUF_01;
        reg_inf = HAL_REG_READ(HAL_CAN[can_x]->RBUF[1]);

        // read ide,id
        if (reg_inf & BIT7) /*扩展帧*/
        {
            //            rx_msg->ide = 1;
            //            rx_msg->id  = CAN_RBUF_00 & 0x1FFFFFFF;
            hal_rx_ide[can_x] = 1;
            hal_rx_id[can_x]  = HAL_REG_READ(HAL_CAN[can_x]->RBUF[0]) & 0x1FFFFFFF;
        }
        else /*标准帧*/
        {
            //            rx_msg->ide = 0;
            //            rx_msg->id  = CAN_RBUF_00 & 0x7ff;
            hal_rx_ide[can_x] = 0;
            hal_rx_id[can_x]  = HAL_REG_READ(HAL_CAN[can_x]->RBUF[0]) & 0x7ff;
        }

        // read rtr
        if (reg_inf & BIT6)
        {
            //            rx_msg->rtr = 1;
            hal_rx_rtr[can_x] = 1;
        }
        else
        {
            //            rx_msg->rtr = 0;
            hal_rx_rtr[can_x] = 0;
        }

        // read fdf,len
        dlc               = reg_inf & 0x0f;
        hal_rx_len[can_x] = dlc;
        if (hal_rx_rtr[can_x])
        {
            hal_rx_len[can_x] = 0;
        }

        // read buf
        x     = 0;
        rbufx = 2;
        while (x < hal_rx_len[can_x])
        {
            hal_rx_buf[can_x][x]     = HAL_REG_READ(HAL_CAN[can_x]->RBUF[rbufx]);
            hal_rx_buf[can_x][x + 1] = HAL_REG_READ(HAL_CAN[can_x]->RBUF[rbufx]) >> 8;
            hal_rx_buf[can_x][x + 2] = HAL_REG_READ(HAL_CAN[can_x]->RBUF[rbufx]) >> 16;
            hal_rx_buf[can_x][x + 3] = HAL_REG_READ(HAL_CAN[can_x]->RBUF[rbufx]) >> 24;

            x += 4;
            rbufx++;
        }

        HAL_REG_SET(HAL_CAN[can_x]->RCTRL, CAN_RCTRL_RREL_BIT);

        return true;
    }

    return false;
}

uint32_t HAL_CAN_RxDataID(HAL_CAN_x can_x)
{
    return hal_rx_id[can_x];
}

uint8_t HAL_CAN_RxDataBuf(HAL_CAN_x can_x, uint8_t *buf)
{
    uint8_t len = hal_rx_len[can_x];
    for (uint8_t i = 0; i < len; i++)
    {
        buf[i] = hal_rx_buf[can_x][i];
    }

    return len;
}

uint8_t HAL_CAN_RxDataLen(HAL_CAN_x can_x)
{
    return hal_rx_len[can_x];
}

uint8_t HAL_CAN_RxDataIde(HAL_CAN_x can_x)
{
    return hal_rx_ide[can_x];
}

uint8_t HAL_CAN_RxDataRtr(HAL_CAN_x can_x)
{
    return hal_rx_rtr[can_x];
}

uint8_t HAL_CAN_RxDataFdf(HAL_CAN_x can_x)
{
    (void)can_x;
    return 0;
}

void HAL_CAN_IDx_Filter(HAL_CAN_x can_x, u8 ae_x, u32 id, u32 mask, HAL_CAN_IDEFilter_x ide_filter)
{
    if (ae_x > HAL_CAN_AE_3)
    {
        return;
    }

    Set_CFG_STAT(can_x, CAN_CFG_STAT_RESET_BIT); // 复位模式

    HAL_REG_SET(HAL_CAN[can_x]->ACFEN, 1 << ae_x);                                 // ACFx is Enabled
    HAL_REG_WRITE_BIT_MASK_POS(HAL_CAN[can_x]->ACFCTRL, CAN_ACFCTRL_ACFADR, ae_x); // ACFADR [3:0]

    // 1.set MASK
    HAL_REG_SET(HAL_CAN[can_x]->ACFCTRL, CAN_ACFCTRL_SELMASK_BIT); // CAN_ACFCTRL.SELMASK==1 MASK
    if (ide_filter == HAL_CAN_IDEFilter_All)
    {
        // CAN_ACF &= ~BIT30;
        HAL_REG_RESET(HAL_CAN[can_x]->ACF, CAN_ACF_IDCMP_BIT);
    }
    else if (ide_filter == HAL_CAN_IDEFilter_St)
    {
        //        CAN_ACF |= BIT30;
        //        CAN_ACF &= ~BIT29; // 只接收标准帧

        HAL_REG_SET(HAL_CAN[can_x]->ACF, CAN_ACF_IDCMP_BIT);
        HAL_REG_RESET(HAL_CAN[can_x]->ACF, CAN_ACF_IDMASK_BIT);
    }
    else if (ide_filter == HAL_CAN_IDEFilter_Ex)
    {
        //        CAN_ACF |= BIT30;
        //        CAN_ACF |= BIT29; // 只接收扩展帧

        HAL_REG_SET(HAL_CAN[can_x]->ACF, CAN_ACF_IDCMP_BIT);
        HAL_REG_SET(HAL_CAN[can_x]->ACF, CAN_ACF_IDMASK_BIT);
    }

    //    CAN_ACF &= ~0x1FFFFFFF;
    //    CAN_ACF |= (mask & 0x1FFFFFFF); // set ACFx MASK
    HAL_REG_WRITE_BIT_MASK_POS(HAL_CAN[can_x]->ACF, CAN_ACF_IDCODE_MASK, mask);

    // 2.set ACR
    //    CAN_ACFCTRL &= ~BIT5; // CAN_ACFCTRL.SELMASK==0 ACR
    //    CAN_ACF &= ~0x1FFFFFFF;
    //    CAN_ACF |= (id & 0x1FFFFFFF); // set ACFx ID
    HAL_REG_RESET(HAL_CAN[can_x]->ACFCTRL, CAN_ACFCTRL_SELMASK_BIT);
    HAL_REG_WRITE_BIT_MASK_POS(HAL_CAN[can_x]->ACF, CAN_ACF_IDCODE_MASK, id);

    Reset_CFG_STAT(can_x, CAN_CFG_STAT_RESET_BIT); // 正常输出模式
    Delay(100);
}

void HAL_CAN_IDx_FilterEnable(HAL_CAN_x can_x, HAL_CAN_AE_x ae_x)
{
    if (ae_x > HAL_CAN_AE_3)
    {
        return;
    }

    HAL_REG_SET(HAL_CAN[can_x]->ACFEN, 1 << ae_x);
}

void HAL_CAN_IDx_FilterDisable(HAL_CAN_x can_x, HAL_CAN_AE_x ae_x)
{
    if (ae_x > HAL_CAN_AE_3)
    {
        return;
    }

    HAL_REG_RESET(HAL_CAN[can_x]->ACFEN, 1 << ae_x);
}

/* 仅在45x下支持 */
void HAL_CAN_SetSTBMode(HAL_CAN_x can_x, HAL_CAN_STBMode_x mode_x) /* 设置STB发送缓冲区模式 */
{
    (void)can_x;
    (void)mode_x;
}

/**
 * @brief    监听模式使能/禁止
 * @par 更新记录
 * 如果设置了 TPE、TSONE 或 TSALL，则无法设置 LOM。如果 LOM 启
 * 用且 LBME 禁用，则无法启动传输。
 * LOM=1 和 LBME=0 禁止所有传输。
 * LOM=1 和 LBME=1 禁止应答相应接收到的帧和错误帧，但可以发送
 * 正常通信中，禁止使能该位。
 */
void HAL_CAN_LOM_Enable(HAL_CAN_x can_x)
{
    HAL_REG_SET(HAL_CAN[can_x]->TCMD, CAN_TCMD_LOM_BIT);
}

void HAL_CAN_LOM_Disable(HAL_CAN_x can_x)
{
    HAL_REG_RESET(HAL_CAN[can_x]->TCMD, CAN_TCMD_LOM_BIT);
}

/**
 * @brief    内部回环模式使能/禁止
 * @par 更新记录
 * 自发自收，无需自应答，芯片RX和TX引脚可悬空。
 * 应在CAN初始化和ID滤波设置之后再使能。
 */
void HAL_CAN_LBMI_Enable(HAL_CAN_x can_x)
{
    Set_CFG_STAT(can_x, CAN_CFG_STAT_LBMI_BIT);
}

void HAL_CAN_LBMI_Disable(HAL_CAN_x can_x)
{
    Reset_CFG_STAT(can_x, CAN_CFG_STAT_LBMI_BIT);
}

/**
 * @brief    外部回环模式使能/禁止
 * @par 更新记录
 * 自发自收，自应答，需将芯片RX和TX接入CAN收发器，收发器可以不挂入总线。
 * 应在CAN初始化和ID滤波设置之后再使能。
 */
void HAL_CAN_LBME_Enable(HAL_CAN_x can_x)
{
    Set_CFG_STAT(can_x, CAN_CFG_STAT_LBME_BIT);
    HAL_REG_SET(HAL_CAN[can_x]->RCTRL, CAN_RCTRL_SACK_BIT); // 使能自应答
}

void HAL_CAN_LBME_Disable(HAL_CAN_x can_x)
{
    Reset_CFG_STAT(can_x, CAN_CFG_STAT_LBME_BIT);
    HAL_REG_RESET(HAL_CAN[can_x]->RCTRL, CAN_RCTRL_SACK_BIT); // 关闭自应答
}

/**
 * @brief    单次传输模式使能/禁止
 * @par 更新记录
 * PTB/STB单次传输模式使能，使能后错误不重发。
 * 应在CAN初始化和ID滤波设置之后再使能。
 */
void HAL_CAN_SS_Enable(HAL_CAN_x can_x) /* 单次传输模式使能/禁止 */
{
    Set_CFG_STAT(can_x, CAN_CFG_STAT_TPSS_BIT);
    Set_CFG_STAT(can_x, CAN_CFG_STAT_TSSS_BIT);
}

void HAL_CAN_SS_Disable(HAL_CAN_x can_x)
{
    Reset_CFG_STAT(can_x, CAN_CFG_STAT_TPSS_BIT);
    Reset_CFG_STAT(can_x, CAN_CFG_STAT_TSSS_BIT);
}

uint8_t HAL_CAN_RxErrorCnt(HAL_CAN_x can_x)
{
    return HAL_REG_READ_BIT_MASK_POS(HAL_CAN[can_x]->RECNT, CAN_RECNT_RECNT);
}

uint8_t HAL_CAN_TxErrorCnt(HAL_CAN_x can_x)
{
    return HAL_REG_READ_BIT_MASK_POS(HAL_CAN[can_x]->TECNT, CAN_TECNT_TECNT);
}

uint8_t HAL_CAN_ErrorPassive(HAL_CAN_x can_x)
{
    return HAL_REG_READ_BIT(HAL_CAN[can_x]->TECNT, CAN_ERRINT_EPASS_BIT) > 0;
}

uint8_t HAL_CAN_Busoff(HAL_CAN_x can_x)
{
    return HAL_REG_READ_BIT(HAL_CAN[can_x]->CFG_STAT, CAN_CFG_STAT_BUSOFF_BIT) > 0;
}

uint8_t HAL_CAN_ArbitrationLostCap(HAL_CAN_x can_x)
{
    // return CAN_EALCAP_ALC(HAL_REG_READ(HAL_CAN[can_x]->EALCAP));
    return HAL_REG_READ_BIT_MASK_POS(HAL_CAN[can_x]->EALCAP, CAN_EALCAP_ALC);
}

uint8_t HAL_CAN_ROverflow(HAL_CAN_x can_x)
{
    return HAL_REG_READ_BIT(HAL_CAN[can_x]->RCTRL, CAN_RCTRL_ROV_BIT) > 0;
}

HAL_CAN_ERROR_x HAL_CAN_KindOfError(HAL_CAN_x can_x)
{
    // uint8_t koer = CAN_EALCAP_KOER(HAL_REG_REAG(HAL_CAN[can_x]->EALCAP));
    uint8_t koer = HAL_REG_READ_BIT_MASK_POS(HAL_CAN[can_x]->EALCAP, CAN_EALCAP_KOER);

    return (HAL_CAN_ERROR_x)koer;
}

void HAL_CAN_SetGpioTx(HAL_CAN_x can_x, HAL_GPIO_Px px)
{
    (void)can_x;
    HAL_GPIO_SetAf(px, HAL_GPIO_AF_CAN);
    HAL_GPIO_SetMode(px, HAL_GPIO_MODE_OUT);
}

void HAL_CAN_SetGpioRx(HAL_CAN_x can_x, HAL_GPIO_Px px)
{
    (void)can_x;
    HAL_GPIO_SetAf(px, HAL_GPIO_AF_CAN);
    HAL_GPIO_SetMode(px, HAL_GPIO_MODE_IN);
}

/**
 * @brief    CAN_CFG_STAT按bit置位
 * @par 更新记录
 * CAN_CFG_STAT按bit置位方法，避免向CAN_CFG_STAT.Busoff位写1
 */
void Set_CFG_STAT(HAL_CAN_x can_x, u32 bitValue)
{
    u32 tmp;
    tmp = HAL_REG_READ(HAL_CAN[can_x]->CFG_STAT);
    HAL_REG_WRITE(HAL_CAN[can_x]->CFG_STAT, (tmp & (~BIT0)) | bitValue);
}

/**
 * @brief    CAN_CFG_STAT按bit复位
 * @par 更新记录
 * CAN_CFG_STAT按bit复位方法，避免向CAN_CFG_STAT.Busoff位写1
 */
void Reset_CFG_STAT(HAL_CAN_x can_x, u32 bitValue)
{
    u32 tmp;
    tmp = HAL_REG_READ(HAL_CAN[can_x]->CFG_STAT);
    HAL_REG_WRITE(HAL_CAN[can_x]->CFG_STAT, (tmp & (~BIT0)) & (~bitValue));
}

/* 延时函数 */
static void Delay(u32 cnt)
{
    volatile u32 t_cnt;

    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }
}

/*
 波特率计算：
 TQ = (PRESC + 1) / Fclock
 Tseg1 = TQ * (SEG1 + 2)
 Tseg2 = TQ * (SEG2 + 1)
 CAN_BAUD = 1 / (Tseg1 + Tseg2) = 1 / (TQ * (SEG1 + 2 + SEG2 + 1)) = 1 / (TQ * (SEG1 + SEG2 + 3)) = Fclock / (PRESC + 1)*(SEG1 + SEG2 + 3)
 SEG1 + SEG2 = Fclock / ((PRESC + 1) * CAN_BAUD) - 3
 只要SEG1 + SEG2的总和固定，波特率就正确。
 另外：SEG1 > SEG2，SEG1略大于SEG2
       SEG2 >= SJW
 采样点位置：(1*TQ + Tseg1) / (1*TQ + Tseg1 + Tseg2) = (SEG1 + 3) / (SEG1 + SEG2 + 4)，应当在0.7~0.8之间

example:
    Fclock = 96000000; PRESC = 11; CAN_BAUD = 500000;
    SEG = 96000000 / ((11+1) * 500000) - 3 = 13
    SEG1 + SEG2 = 12 + 1 = 11 + 2 = ... = 8 + 5
*/
static const u16 baud_cnt        = 12 * 1;
static const u16 baud_param[][6] = {
    // mclk baud presc sjw seg1 seg2
    // 96MHz 主频
    {96, 1000, 5, 2, 10, 3}, // 76.47%
    {96, 800, 11, 2, 5, 2},  // 72.73%
    {96, 666, 11, 1, 7, 2},  // 76.92%
    {96, 500, 11, 2, 10, 3}, // 76.47%
    {96, 400, 11, 2, 13, 4}, // 76.19%
    {96, 250, 23, 2, 10, 3}, // 76.47%
    {96, 200, 23, 2, 13, 4}, // 76.19%
    {96, 125, 47, 2, 10, 3}, // 76.47%
    {96, 100, 47, 2, 13, 4}, // 76.19%
    {96, 80, 59, 2, 13, 4},  // 76.19%
    {96, 50, 95, 2, 13, 4},  // 76.19%
    {96, 40, 119, 2, 13, 4}, // 76.19%
    // {96,  25,    191,  2,   13,   4},    // 76.19%
    // {96,  20,    239,  2,   13,   4},    // 76.19%
    // {96,  10,    239,  6,   29,   8},    // 78.05%
    // {96,  5,     239,  13,  61,   16},   // 79.01%

    // 48MHz
    // {48,  1000,  2,    2,   10,   3},    // 76.47%
    // {48,  800,   5,    2,   5,    2},    // 72.73%
    // {48,  666,   5,    1,   7,    2},    // 76.92%
    // {48,  500,   5,    2,   10,   3},    // 76.47%
    // {48,  400,   5,    2,   13,   4},    // 76.19%
    // {48,  250,   11,   2,   10,   3},    // 76.47%
    // {48,  200,   11,   2,   13,   4},    // 76.19%
    // {48,  125,   23,   2,   10,   3},    // 76.47%
    // {48,  100,   23,   2,   13,   4},    // 76.19%
    // {48,  80,    29,   2,   13,   4},    // 76.19%
    // {48,  50,    47,   2,   13,   4},    // 76.19%
    // {48,  40,    59,   2,   13,   4},    // 76.19%
    // {48,  25,    95,   2,   13,   4},    // 76.19%
    // {48,  20,    119,  2,   13,   4},    // 76.19%
    // {48,  10,    119,  6,   29,   8},    // 78.05%
    // {48,  5,     119,  13,  61,   16},   // 79.01%

    // 24MHz
    // {24,  1000,  1,    2,   7,    2},    // 76.92%
    // {24,  800,   2,    2,   5,    2},    // 72.73%
    // {24,  666,   2,    1,   7,    2},    // 76.92%
    // {24,  500,   2,    2,   10,   3},    // 76.47%
    // {24,  400,   2,    2,   13,   4},    // 76.19%
    // {24,  250,   5,    2,   10,   3},    // 76.47%
    // {24,  200,   5,    2,   13,   4},    // 76.19%
    // {24,  125,   11,   2,   10,   3},    // 76.47%
    // {24,  100,   11,   2,   13,   4},    // 76.19%
    // {24,  80,    14,   2,   13,   4},    // 76.19%
    // {24,  50,    23,   2,   13,   4},    // 76.19%
    // {24,  40,    29,   2,   13,   4},    // 76.19%
    // {24,  25,    47,   2,   13,   4},    // 76.19%
    // {24,  20,    59,   2,   13,   4},    // 76.19%
    // {24,  10,    59,   6,   29,   8},    // 78.05%
    // {24,  5,     59,   13,  61,   16},   // 79.91%
};

static bool GetBaudParam(u32 baud, u8 *presc, u8 *sjw, u8 *seg1, u8 *seg2)
{
    u16 i;
    u32 mclk_mega = HAL_CLK_GetMcuFreq() / 1000000;
    for (i = 0; i < baud_cnt; i++)
    {
        if (baud_param[i][0] == mclk_mega && baud_param[i][1] == baud)
        {
            *presc = baud_param[i][2];
            *sjw   = baud_param[i][3];
            *seg1  = baud_param[i][4];
            *seg2  = baud_param[i][5];
            return true;
        }
    }

    return false;
}

static void CAN_Write_TBUF(HAL_CAN_x can_x, u32 id, HAL_CAN_FRAME_x frame_x, u8 *msg, u8 len)
{
    u8 frame_inf = 0;
    u8 ide       = 0;
    u8 rtr       = 0;
    u8 dlc       = 0;
    u8 tbufx     = 0;
    u32 tbufv    = 0;
    u8 x         = 0;

    if (len > 8)
    {
        len = 8;
    }

    switch (frame_x)
    {
        case HAL_CAN_FRAME_IDE0_RTR0:
            ide = 0;
            rtr = 0;
            break;
        case HAL_CAN_FRAME_IDE0_RTR1:
            ide = 0;
            rtr = 1;
            break;
        case HAL_CAN_FRAME_IDE1_RTR0:
            ide = 1;
            rtr = 0;
            break;
        case HAL_CAN_FRAME_IDE1_RTR1:
            ide = 1;
            rtr = 1;
            break;
        default:
            break;
    }

    if (ide == 0)
    {
        id &= 0x7FF; // 标准帧，11位ID
    }
    else
    {
        id &= 0x1FFFFFFF; // 扩展帧，29位ID
    }
    HAL_REG_WRITE(HAL_CAN[can_x]->TBUF[0], id);

    dlc = len;
    frame_inf |= (ide << 7); // 0标准/1扩展帧
    frame_inf |= (rtr << 6); // 0,数据帧;1,遥控帧
    frame_inf |= (dlc << 0); // dlc,发送数据长度
    HAL_REG_WRITE(HAL_CAN[can_x]->TBUF[1], frame_inf);

    // set CAN_TBUF_02 ~ CAN_TBUF_03
    // TBUF赋值从CAN_TBUF_02开始
    x     = 0;
    tbufx = 2;
    while (x < len)
    {
        tbufv = msg[x];
        if ((x + 1) < len)
            tbufv += (msg[x + 1] << 8);
        if ((x + 2) < len)
            tbufv += (msg[x + 2] << 16);
        if ((x + 3) < len)
            tbufv += (msg[x + 3] << 24);
        HAL_REG_WRITE(HAL_CAN[can_x]->TBUF[tbufx], tbufv);

        x += 4;
        tbufx++;
    }
}
