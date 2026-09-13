/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： lks32mc07x_can.c\n
 * 文件标识： 无 \n
 * 内容摘要： CAN外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	       <th>Version   <th>Author  <th>Description
 * <tr><td>2023年2月23日 <td>1.0     <td>HuangMG     <td>创建
 * </table>
 */
#include "lks32mc07x_can.h"
#include "lks32mc07x_sys.h"
#include "string.h"

CANRxMsg g_rxMsg = {
    0,
    0,
    0,
    0,

    0,
    {0},
};

static bool GetBaudParam(u32 baud, u8 *presc, u8 *sjw, u8 *seg2, u8 *seg1);
static void CAN_Write_TBUF(u32 id, u8 ide, u8 rtr, u8 *msg, u8 len);

static void Set_CFG_STAT(u32 bitValue);
static void Reset_CFG_STAT(u32 bitValue);

static void Delay(u32 cnt);

/**
 * @brief    CAN初始化函数,采用2.0B/FD协议
 * 输入参数: CAN_InitTypeDef*: 初始化参数
 * @par 更新记录  V1.0  2024/07/03  YangZJ  创建
 */
void CAN_Init1(CAN_InitTypeDef *this)
{
    u8 s_presc, s_sjw, s_seg2, s_seg1;

    SYS_WR_PROTECT = 0x7a83; // 关闭写保护

    SYS_SFT_RST |= BIT19;  // 复位CAN
    SYS_SFT_RST &= ~BIT19; // 释放CAN复位

    SYS_CLK_FEN |= BIT19; // 使能CAN时钟

    CAN_CFG_STAT |= BIT7; // CAN复位模式
    CAN_ACFEN = 0x00;     // 关闭ID滤波功能

    if (this->SBaud > 0 && GetBaudParam(this->SBaud, &s_presc, &s_sjw, &s_seg2, &s_seg1))
    {
        CAN_SBAUD = (s_presc << 24) | (s_sjw << 16) | (s_seg2 << 8) | s_seg1; // 慢速波特率设置
    }

    CAN_CFG_STAT &= ~BIT7; // 正常输出模式
    CAN_TCMD   = 0x00;
    CAN_RTIE   = this->IE; // 默认开启 错误中断使能+接收中断使能
    CAN_ERRINT = this->ERRINT_IE;

    SYS_WR_PROTECT = 0x0; // 打开写保护
}

/**
 * @brief    CAN配置结构体初始化，并设置默认参数
 * @par 更新记录  V1.0  2022/09/19  YangZJ  创建
 */
void CAN_StructInit(CAN_InitTypeDef *this)
{
    this->SBaud     = 500;
    this->IE        = 0;
    this->ERRINT_IE = 0;
}

/*******************************************************************************
函数名称: void CAN_Initl(u8 BTR3,u8 BTR2,u8 BTR1,u8 BTR0)
功能描述: CAN初始化函数,采用2.0B协议
操作的表:

    输入参数: BTR0    S_SEG_1:段时间段 1 时间单元设定
           BTR1    S_SEG_2：段时间段 2 时间单元设定
           BTR2    S_SJW ： 再同步补偿宽度时间设定
                     BTR3    S_PRESC ：TQ 预分频率设定值
输出参数: 无
返回值:   无
其它说明:
修改日期     版本号     修改人    修改内容
-----------------------------------------------------------------------------
*******************************************************************************/
/**
 *@brief @b 函数名称:   void CAN_Init(u8 BTR3,u8 BTR2,u8 BTR1,u8 BTR0)
 *@brief @b 功能描述:   CAN初始化函数,采用2.0B协议
 *@see被调用函数：      无
 *@param输入参数：
   波特率    AN_SBAUD.PRESC[7:0]   CAN_SBAUD.SJW[6:0]  CAN_SBAUD.SEG2[6:0] CAN_SBAUD.SEG1[7:0] Sample Poin\n
    1Mbps             0x05                0x02                0x05               0x08             63% \n
    800Kbps           0x0B                0x01                0x03               0x04             60% \n
    666Kbps           0x0B                0x01                0x03               0x06             67% \n
    500Kbps           0x0B                0x02                0x05               0x08             63% \n
    400Kbps           0x0B                0x02                0x06               0x0B             65% \n
    250Kbps           0x17                0x02                0x05               0x08             63% \n
    200Kbps           0x17                0x02                0x06               0x0B             65% \n
    125Kbps           0x2F                0x02                0x05               0x08             63% \n
    100Kbps           0x2F                0x02                0x06               0x0B             65% \n
    80Kbps            0x35                0x02                0x06               0x0B             65% \n
    50Kbps            0x5F                0x02                0x06               0x0B             65% \n
    40Kbps            0x77                0x02                0x06               0x0B             65% \n
    25Kbps            0xBF                0x02                0x06               0x0B             65% \n
    20Kbps            0xEF                0x02                0x06               0x0B             65% \n
    10Kbps            0xEF                0x06                0x0D               0x18             65% \n
    05Kbps            0xEF                0x0D                0x1B               0x32             65%
 *@param输出参数：      无
 *@return返 回 值：     无
 *@note其它说明：       无
 *@warning             无
 *@par 示例代码：
 *@code
             CAN_Init(0x0B,0x02,0x05,0x08);    //CAN波特率500Khz
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author      <th>Description
 * <tr><td>2023年2月23日  <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
void CAN_Init(u8 BTR3, u8 BTR2, u8 BTR1, u8 BTR0)
{
    SYS_WR_PROTECT = 0x7a83; // 关闭写保护

    SYS_SFT_RST |= BIT19;  // 复位CAN
    SYS_SFT_RST &= ~BIT19; // 释放CAN复位

    SYS_CLK_FEN |= BIT19; // 使能CAN时钟

    CAN_CFG_STAT |= 1 << 7; // 复位模式

    CAN_ACFEN = 0x00;                                             // 关闭ID滤波功能
    CAN_SBAUD = BTR0 | (BTR1 << 8) | (BTR2 << 16) | (BTR3 << 24); // 波特率设置
    CAN_CFG_STAT &= ~(1 << 7);                                    // 正常输出模式
    CAN_TCMD = 0x00;
    CAN_RTIE |= 1 << 7;   // RFIFO有新的数据被接收到，中断源使能
    CAN_RTIE |= 1 << 1;   // 错误中断使能
    SYS_WR_PROTECT = 0x0; // 打开写保护
}

/*******************************************************************************
 函数名称：    void SoftDelay(void)
 功能描述：    软件延时函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
static void Delay(u32 cnt)
{
    volatile u32 t_cnt;

    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }
}

CanSendRet CAN_Send(CANTxMsg *tx_msg)
{
    u16 i = 0;

    if (tx_msg->len > 8)
    {
        return CanSend_DataTooLong;
    }

    if (tx_msg->tbsel == TBSel_PTB)
    {
        // PTB发送
        if (CAN->CFG_STAT & BIT1) // 本设备正在发送CAN帧
        {
            return CanSend_NotIdle; // 发送失败
        }

        CAN_TCMD &= ~BIT7; // PTB发送。CAN_TCMD.TBSEL，0-PTB 1-STB
        CAN_Write_TBUF(tx_msg->id, tx_msg->ide, tx_msg->rtr, tx_msg->buf, tx_msg->len);
        CAN_TCMD |= BIT4; // CAN 发送传输请求,触发PTB发送
        while (CAN_TCMD & BIT4)
        {
            Delay(100);
            if ((i++) >= 0x0ff)
            {
                return CanSend_Timeout; // 发送失败
            }
        }
        return CanSend_Succ; // 发送完成
    }
    else
    {
        // STB发送
        if ((CAN->TCTRL & 0x03) == 0x03)
        {
            return CanSend_STBFull; // 发送失败，STB满
        }

        CAN->TCMD |= BIT7; // STB发送。CAN_TCMD.TBSEL，0-PTB 1-STB
        CAN_Write_TBUF(tx_msg->id, tx_msg->ide, tx_msg->rtr, tx_msg->buf, tx_msg->len);
        CAN->TCTRL |= BIT6; // 置位TSNEXT，更新STB slot位置

        return CanSend_Succ; // STB添加成功即返回，还需调用CAN_Send_Trig触发发送
    }
}

/**
 * @brief    CANFD数据发送函数，采用CAN-FD协议，PTB发送
 * 输入参数: id: 发送id ide: 标准/扩展帧 rtr：远程帧/数据帧 fdf:CAN2.0/CANFD brs:切换波特率 *msg: 发送的数据  len:发送字节长度
 * 输出参数: 无
 * 返回值:   0：发送成功 !0：发送失败
 * 其它说明: id:标准ID(11位)/扩展ID(11位+18位)
 *           ide:0,标准帧;1,扩展帧
 *           rtr:0,数据帧;1,遥控帧
 *           fdf:0,CAN2.0;1,CANFD
 *           brs:0,不切换波特率;1,切换波特率
 *           len:要发送的数据长度，CAN2.0最大8字节，CANFD最大64字节
 * @par 更新记录
 */
CanSendRet My_CAN_Send_Msg(u32 id, u8 ide, u8 rtr, u8 *msg, u8 len)
{
    CANTxMsg tx_msg;
    tx_msg.id  = id;
    tx_msg.ide = ide;
    tx_msg.rtr = rtr;
    tx_msg.buf = msg;
    tx_msg.len = len;

    tx_msg.tbsel = TBSel_PTB;

    return CAN_Send(&tx_msg);
}

/**
 * @brief    CANFD数据发送函数，采用CAN-FD协议，STB发送。默认STB为FIFO模式。
 * 输入参数: id:发送id ide: 标准/扩展帧 rtr:远程帧/数据帧 fdf:CAN2.0/CANFD brs:切换波特率 *msg:发送的数据  len:发送字节长度
 * 输出参数: 无
 * 返回值:   0：发送成功 !0：发送失败
 * 其它说明: id:标准ID(11位)/扩展ID(11位+18位)
 *           ide:0,标准帧;1,扩展帧
 *           rtr:0,数据帧;1,遥控帧
 *           fdf:0,CAN2.0;1,CANFD
 *           brs:0,不切换波特率;1,切换波特率
 *           option:0,本次不发送;1,发送一帧;2,发送所有帧
 * @par 更新记录  V1.0  2023/02/13  HuangMG  创建
 */
CanSendRet CAN_Send_Trig(STBTransOption stb_trans)
{
    u32 i = 0;

    if (stb_trans == STB_TransAll)
    {
        CAN->TCMD |= BIT1;       // 触发所有STB发送
        while (CAN->TCMD & BIT1) // 最近一次是否传输完成
        {
            Delay(100);
            if ((i++) >= 0x0ff)
            {
                return CanSend_Timeout; // 发送失败
            }
        }
    }
    else if (stb_trans == STB_TransOne)
    {
        CAN->TCMD |= BIT2;       // 触发一帧STB发送
        while (CAN->TCMD & BIT2) // 最近一次是否传输完成
        {
            Delay(100);
            if ((i++) >= 0x0ff)
            {
                return CanSend_Timeout; // 发送失败
            }
        }
    }
    else
    {
        return CanSend_Succ; // 不需要发送，返回成功
    }

    return CanSend_Succ; // 发送完成
}

/*
 * 取消发送
 */
void CAN_Send_Cancel(TBSelOption tbsel)
{
    if (tbsel == TBSel_PTB)
    {
        CAN->TCMD |= BIT3;
    }
    else if (tbsel == TBSel_STB)
    {
        CAN->TCMD |= BIT0;
    }
}

/**
 * @brief    CAN接收数据
 * 输入参数: *rx_msg: 接收数据存储对象
 * 返回值:   CanRecvRet
 * @par 更新记录
 */
CanRecvRet CAN_Recv(CANRxMsg *rx_msg)
{
    u8 reg_inf;
    u8 dlc = 0;
    u16 rbufx;
    u8 x;

    if ((CAN_RCTRL & 0x03) > 0) /*Rx Buffer存有一帧或多帧数据，可以通过 RFIFO 寄存器读取*/
    {
        reg_inf = CAN_RBUF_01;

        // read ide,id
        if (reg_inf & BIT7) /*扩展帧*/
        {
            rx_msg->ide = 1;
            rx_msg->id  = CAN_RBUF_00 & 0x1FFFFFFF;
        }
        else /*标准帧*/
        {
            rx_msg->ide = 0;
            rx_msg->id  = CAN_RBUF_00 & 0x7ff;
        }

        // read rtr
        if (reg_inf & BIT6)
        {
            rx_msg->rtr = 1;
        }
        else
        {
            rx_msg->rtr = 0;
        }

        // read fdf,len
        dlc         = reg_inf & 0x0f;
        rx_msg->len = dlc;
        if (rx_msg->rtr)
        {
            rx_msg->len = 0;
        }

        // read buf
        x     = 0;
        rbufx = 2;
        while (x < rx_msg->len)
        {
            rx_msg->buf[x]     = CAN->RBUF[rbufx];
            rx_msg->buf[x + 1] = CAN->RBUF[rbufx] >> 8;
            rx_msg->buf[x + 2] = CAN->RBUF[rbufx] >> 16;
            rx_msg->buf[x + 3] = CAN->RBUF[rbufx] >> 24;
            x += 4;
            rbufx++;
        }

        CAN_RCTRL |= BIT4; /*释放 Rx Buffer Slot*/
        rx_msg->valid = 1;
        return CanRecv_Succ;
    }

    return CanRecv_NoData;
}

/**
 *@brief @b 函数名称:   u8 CAN_Receive_Msg(u32* id,u8* len ,u8* ide,u8* rtr,u8 *buf)
 *@brief @b 功能描述:   CAN轮询接收数据程序
 *@see被调用函数：       无
 *@param输入参数：       无
 *@param输出参数：       id:  接收帧id \n
                        len: 接收数据长度 \n
 *                      ide: 接收帧的类型，标准/扩展帧 \n
 *		                rtr：接收帧的类型，远程帧/数据帧 \n
 *		                *buf: 接收帧的数据存储缓存区
 *@return返 回 值：      0：接收完成 !0：接收失败
 *@note其它说明：
 *                      1、id:标准ID(11位)/扩展ID(11位+18位) \n
 *                      2、ide:0,标准帧;1,扩展帧 \n
 *                      3、rtr:0,数据帧;1,远程帧。
 *@warning              无
 *@par 示例代码：
 *@code
         //can_par.id存储接收帧ID，can_par.len接收数据个数
             can_par.ide存储接收帧类型标准/扩展帧，
             can_par.rtr存储接收帧类型远程帧/数据帧，can_par.RX存储接收帧数据
         CAN_Receive_Msg(&( can_par.id),&(can_par.len),&(can_par.ide),&(can_par.rtr),can_par.RX);
  @endcode
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version    <th>Author     <th>Description
 * <tr><td>2023年2月23日  <td>1.0      <td>HuangMG        <td>创建
 * </table>
 */
CanRecvRet CAN_Receive_Msg(u32 *id, u8 *len, u8 *ide, u8 *rtr, u8 *buf)
{
    CANRxMsg rx_msg;
    CanRecvRet ret;
    int i;

    ret = CAN_Recv(&rx_msg);
    if (ret == CanRecv_Succ)
    {
        *id  = rx_msg.id;
        *ide = rx_msg.ide;
        *rtr = rx_msg.rtr;
        for (i = 0; i < rx_msg.len; i++)
        {
            buf[i] = rx_msg.buf[i];
        }
        *len = rx_msg.len;
    }
    else
    {
        *id  = 0;
        *ide = 0;
        *rtr = 0;
        *len = 0;
    }

    return ret;
}

/**
 * @brief    CAN IDx接收滤波函数
 * 输入参数:  x: 滤波通道号。
              id: ID值。
 *            mask：屏蔽位。bit=0表示需要位匹配，bit=1表示不需要匹配。
 *            ide_filter：IDEFilter_St_Ex / IDEFilter_St / IDEFilter_Ex
 * @par 更新记录
 */
void IDx_Filter(u8 x, u32 id, u32 mask, IDEFilterOption ide_filter)
{
    CAN_CFG_STAT |= BIT7; // 复位模式

    CAN_ACFEN |= (1 << x);    // ACFx is Enabled
    CAN_ACFCTRL = (x & 0x0F); // ACFADR [3:0]

    // 1.set MASK
    CAN_ACFCTRL |= BIT5; // CAN_ACFCTRL.SELMASK==1 MASK
    if (ide_filter == IDEFilter_St_Ex)
    {
        CAN_ACF &= ~BIT30;
    }
    else if (ide_filter == IDEFilter_St)
    {
        CAN_ACF |= BIT30;
        CAN_ACF &= ~BIT29; // 只接收标准帧
    }
    else if (ide_filter == IDEFilter_Ex)
    {
        CAN_ACF |= BIT30;
        CAN_ACF |= BIT29; // 只接收扩展帧
    }

    CAN_ACF &= ~0x1FFFFFFF;
    CAN_ACF |= (mask & 0x1FFFFFFF); // set ACFx MASK

    // 2.set ACR
    CAN_ACFCTRL &= ~BIT5; // CAN_ACFCTRL.SELMASK==0 ACR
    CAN_ACF &= ~0x1FFFFFFF;
    CAN_ACF |= (id & 0x1FFFFFFF); // set ACFx ID

    Delay(100);
    CAN_CFG_STAT &= ~BIT7; // 正常输出模式
    Delay(100);
}

/**
 * @brief    CAN接收过滤器使能与禁止
 * @par 更新记录  V1.0  2022/09/19  YangZJ  创建
 */
void IDx_FilterCmd(u8 x, FuncState state)
{
    if (state == ENABLE)
    {
        CAN->ACFEN |= (1 << x);
    }
    else
    {
        CAN->ACFEN &= ~(1 << x);
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

example:
    Fclock = 96000000; PRESC = 11; CAN_BAUD = 500000;
    SEG = 96000000 / ((11+1) * 500000) - 3 = 13
    SEG1 + SEG2 = 12 + 1 = 11 + 2 = ... = 8 + 5
*/
static bool GetBaudParam(u32 baud, u8 *presc, u8 *sjw, u8 *seg2, u8 *seg1)
{
    bool ret = true;
    switch (baud)
    {
        case 1000:
            *presc = 0x05;
            *sjw   = 0x02;
            *seg2  = 0x05;
            *seg1  = 0x08;
            break;
        case 800:
            *presc = 0x0B;
            *sjw   = 0x01;
            *seg2  = 0x03;
            *seg1  = 0x04;
            break;
        case 666:
            *presc = 0x0B;
            *sjw   = 0x01;
            *seg2  = 0x03;
            *seg1  = 0x06;
            break;
        case 500:
            *presc = 0x0B;
            *sjw   = 0x02;
            *seg2  = 0x05;
            *seg1  = 0x08;
            break;
        case 400:
            *presc = 0x0B;
            *sjw   = 0x02;
            *seg2  = 0x06;
            *seg1  = 0x0B;
            break;
        case 250:
            *presc = 0x17;
            *sjw   = 0x02;
            *seg2  = 0x05;
            *seg1  = 0x08;
            break;
        case 200:
            *presc = 0x17;
            *sjw   = 0x02;
            *seg2  = 0x06;
            *seg1  = 0x0B;
            break;
        case 125:
            *presc = 0x2F;
            *sjw   = 0x02;
            *seg2  = 0x05;
            *seg1  = 0x08;
            break;
        case 100:
            *presc = 0x2F;
            *sjw   = 0x02;
            *seg2  = 0x06;
            *seg1  = 0x0B;
            break;
        case 80:
            *presc = 0x35;
            *sjw   = 0x02;
            *seg2  = 0x06;
            *seg1  = 0x0B;
            break;
        case 50:
            *presc = 0x5F;
            *sjw   = 0x02;
            *seg2  = 0x06;
            *seg1  = 0x0B;
            break;
        case 40:
            *presc = 0x77;
            *sjw   = 0x02;
            *seg2  = 0x06;
            *seg1  = 0x0B;
            break;
        case 25:
            *presc = 0xBF;
            *sjw   = 0x02;
            *seg2  = 0x06;
            *seg1  = 0x0B;
            break;
        case 20:
            *presc = 0xEF;
            *sjw   = 0x02;
            *seg2  = 0x06;
            *seg1  = 0x0B;
            break;
        case 10:
            *presc = 0xEF;
            *sjw   = 0x06;
            *seg2  = 0x0D;
            *seg1  = 0x18;
            break;
        case 5:
            *presc = 0xEF;
            *sjw   = 0x0D;
            *seg2  = 0x1B;
            *seg1  = 0x32;
            break;
        default:
            ret = false;
            break;
    }

    return ret;
}

static void CAN_Write_TBUF(u32 id, u8 ide, u8 rtr, u8 *msg, u8 len)
{
    u8 frame_inf = 0;
    u8 dlc       = 0;
    u16 tbufx    = 0;
    u32 tbufv    = 0;
    u16 x        = 0;

    if (ide == 0)
    {
        id &= 0x7FF; // 标准帧，11位ID
    }
    else
    {
        id &= 0x1FFFFFFF; // 扩展帧，29位ID
    }
    CAN_TBUF_00 = id;

    dlc = len;

    frame_inf |= (ide << 7); // 0标准/1扩展帧
    frame_inf |= (rtr << 6); // 0,数据帧;1,遥控帧
    frame_inf |= (dlc << 0); // dlc,发送数据长度
    CAN_TBUF_01 = frame_inf;

    // set CAN_TBUF_02 ~ CAN_TBUF_03
    x     = 0;
    tbufx = 2; // TBUF赋值从CAN_TBUF_02开始
    while (x < len)
    {
        tbufv = msg[x];
        if ((x + 1) < len) tbufv += (msg[x + 1] << 8);
        if ((x + 2) < len) tbufv += (msg[x + 2] << 16);
        if ((x + 3) < len) tbufv += (msg[x + 3] << 24);
        CAN->TBUF[tbufx] = tbufv;

        x += 4;
        tbufx++;
    }
}

/**
 * @brief    CAN_CFG_STAT按bit置位
 * @par 更新记录
 * CAN_CFG_STAT按bit置位方法，避免向CAN_CFG_STAT.Busoff位写1
 */
void Set_CFG_STAT(u32 bitValue)
{
    u32 tmp_cfg_stat;

    tmp_cfg_stat = CAN->CFG_STAT;
    tmp_cfg_stat &= ~BIT0;
    tmp_cfg_stat |= bitValue;

    CAN->CFG_STAT = tmp_cfg_stat;
}

/**
 * @brief    CAN_CFG_STAT按bit复位
 * @par 更新记录
 * CAN_CFG_STAT按bit复位方法，避免向CAN_CFG_STAT.Busoff位写1
 */
void Reset_CFG_STAT(u32 bitValue)
{
    u32 tmp_cfg_stat;

    tmp_cfg_stat = CAN->CFG_STAT;
    tmp_cfg_stat &= ~BIT0;
    tmp_cfg_stat &= ~bitValue;

    CAN->CFG_STAT = tmp_cfg_stat;
}

/**
 * @brief    内部回环模式使能/禁止
 * @par 更新记录
 * 自发自收，无需自应答，芯片RX和TX引脚可悬空。
 * 应在CAN初始化和ID滤波设置之后再使能。
 */
void CAN_LBMICmd(FuncState state)
{
    if (state == ENABLE)
    {
        Set_CFG_STAT(BIT5); // 开启内回环
    }
    else
    {
        Reset_CFG_STAT(BIT5); // 关闭内回环
    }
}

/**
 * @brief    外部回环模式使能/禁止
 * @par 更新记录
 * 自发自收，自应答，需将芯片RX和TX接入CAN收发器，收发器可以不挂入总线。
 * 应在CAN初始化和ID滤波设置之后再使能。
 */
void CAN_LBMECmd(FuncState state)
{
    if (state == ENABLE)
    {
        Set_CFG_STAT(BIT6); // 开启外回环
        CAN->RCTRL |= BIT7; // 使能自应答
    }
    else
    {
        Reset_CFG_STAT(BIT6); // 关闭外回环
        CAN->RCTRL &= ~BIT7;  // 关闭自应答
    }
}

/**
 * @brief    单次传输模式使能/禁止
 * @par 更新记录
 * PTB/STB单次传输模式使能，使能后错误不重发。
 * 应在CAN初始化和ID滤波设置之后再使能。
 */
void CAN_SS_Enable(TBSelOption tbsel, FuncState state)
{
    if (tbsel == TBSel_PTB)
    {
        if (state == ENABLE)
        {
            Set_CFG_STAT(BIT4);
        }
        else
        {
            Reset_CFG_STAT(BIT4);
        }
    }
    else if (tbsel == TBSel_STB)
    {
        if (state == ENABLE)
        {
            Set_CFG_STAT(BIT3);
        }
        else
        {
            Reset_CFG_STAT(BIT3);
        }
    }
}

/**
 * @brief    打开CAN模块时钟
 * @par 更新记录  V1.0  2022/09/19  YangZJ  创建
 */
void CAN_Enable(void)
{
    SYS_ModuleClockCmd(SYS_Module_CAN0, ENABLE);
    Reset_CFG_STAT(BIT7);
    Delay(100);
}
/**
 * @brief    关闭CAN模块时钟
 * @par 更新记录  V1.0  2022/09/19  YangZJ  创建
 */
void CAN_Disable(void)
{
    SYS_ModuleClockCmd(SYS_Module_CAN0, DISABLE);
    Set_CFG_STAT(BIT7);
}
/**
 * @brief    CAN模块进入复位模式
 * @par 更新记录  V1.0  2022/09/19  YangZJ  创建
 */
void CAN_Reset(void)
{
    Set_CFG_STAT(BIT7);
    Delay(100);
    Reset_CFG_STAT(BIT7);
    Delay(100);
}

/*
 * 发送缓冲区模式设置，对应CAN_TCTRL.TSMODE位
 */
void CAN_SetSTBMode(STBTransMode tsMode)
{
    /* 只有STB为空时，才能切换TSMode */
    if ((CAN_TCTRL & 0x03) > 0)
    {
        return;
    }

    if (tsMode == STB_FIFOMode)
    {
        CAN_TCTRL &= ~BIT5;
    }
    else
    {
        CAN_TCTRL |= BIT5;
    }
}

u8 CAN_STBFullGet(void)
{
    return (CAN->TCTRL & 0x03) == 0x03;
}

/**
 * @brief    获取can接收错误计数
 * @par 更新记录  V1.0  2022/09/19  YangZJ  创建
 */
u8 CAN_RxErrorCntGet(void)
{
    return CAN->RECNT & 0xFF;
}

/**
 * @brief    获取can发送错误计数
 * @par 更新记录  V1.0  2022/09/19  YangZJ  创建
 */
u8 CAN_TxErrorCntGet(void)
{
    return CAN->TECNT & 0xFF;
}

/**
 * @brief    获取can的error passive state
 * @par 更新记录
 */
u8 CAN_ErrorPassiveGet(void)
{
    return (CAN->ERRINT >> 6) & 0x01;
}

/**
 * @brief    获取can的bus off state
 * @par 更新记录
 */
u8 CAN_BusoffGet(void)
{
    return CAN->CFG_STAT & 0x01;
}

/**
 * @brief    获取can的kind of error，错误类别读取
 * @par 更新记录
 */
CANErrorKind CAN_KindOfErrorGet(void)
{
    u8 koer = (CAN->EALCAP >> 5) & 0x07;
    return (CANErrorKind)koer;
}

/**
 * @brief    获取can仲裁失败位置
 * @par 更新记录  V1.0  2022/09/19  YangZJ  创建
 */
u8 CAN_ArbitrationLostCap(void)
{
    return (CAN->EALCAP & 0x1f);
}

/**
 * @brief    获取can的Rx Buffer是否溢出
 * @par 更新记录
 */
u8 CAN_ROverflowGet(void)
{
    return (CAN->RCTRL >> 5) & 0x01;
}

/*! @} */
