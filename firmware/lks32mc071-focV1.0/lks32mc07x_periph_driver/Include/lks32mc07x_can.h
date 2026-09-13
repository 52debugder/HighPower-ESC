/**
 * @file
 * @copyright (C)2015, LINKO SEMICONDUCTOR Co.ltd
 * @brief 文件名称： LKS32MC07x_can.h\n
 * 文件标识： 无 \n
 * 内容摘要： CAN外设驱动程序 \n
 * 其它说明： 无 \n
 *@par 修改日志:
 * <table>
 * <tr><th>Date	        <th>Version  <th>Author  <th>Description
 * <tr><td>2023年2月22日 <td>1.0     <td>HuangMG    <td>创建
 * </table>
 */
#ifndef _LKS32MC07X_CAN_H_
#define _LKS32MC07X_CAN_H_

///< Includes ------------------------------------------------------------------
#include "lks32mc07x_lib.h"

typedef struct
{
    u32 id;     /**<接收ID号 */
    u8 len;     /**<接收数据长度 */
    u8 ide;     /**<接收数据类型0标准/1扩展帧 */
    u8 rtr;     /**<接收数据类型0数据帧/1远程帧*/
    u8 TX[8];   /**<数据发生缓冲区 */
    u8 RX[8];   /**<接收数据缓冲区*/
    u32 rx_sta; /**<接收错误标志位*/
} can_parameter;

// extern can_parameter can_par;

typedef struct
{
    __IO u32 RBUF[4];   ///< 0x00~0x0C CAN Rx Buffer寄存器
    __IO u32 resv0[16]; ///< 0x10~0x4F

    __IO u32 TBUF[4];   ///< 0x50~0x5C CAN Tx Buffer寄存器
    __IO u32 resv1[16]; ///< 0x60~0x9F

    __IO u8 CFG_STAT; ///< 0xA0 CAN配置和状态寄存器
    __IO u8 TCMD;     ///< 0xA1 CAN发送命令寄存器
    __IO u8 TCTRL;    ///< 0xA2 CAN发送控制寄存器
    __IO u8 RCTRL;    ///< 0xA3 CAN接收控制寄存器

    __IO u8 RTIE;   ///< 0xA4 CAN发送接收中断控制寄存器
    __IO u8 RTIF;   ///< 0xA5 CAN发送接收中断标志寄存器
    __IO u8 ERRINT; ///< 0xA6 CAN错误中断使能和标志寄存器
    __IO u8 LIMIT;  ///< 0xA7 CAN警告寄存器
    __IO u32 SBAUD; ///< 0xA8 CAN波特率配置寄存器

    __IO u32 resv2; ///< 0xAC

    __IO u8 EALCAP; ///< 0xB0 CAN错误信息和丢失仲裁信息记录寄存器

    __IO u8 resv3; ///< 0xB1

    __IO u8 RECNT;   ///< 0xB2 CAN接收错误计数器寄存器
    __IO u8 TECNT;   ///< 0xB3 CAN发送错误计数器寄存器
    __IO u8 ACFCTRL; ///< 0xB4 CAN ID过滤器控制寄存器

    __IO u8 resv4; ///< 0xB5

    __IO u16 ACFEN; ///< 0xB6 CAN ID过滤器使能寄存器
    __IO u32 ACF;   ///< 0xB8 CAN ID过滤器选择寄存器
} CAN_TypeDef;

#ifndef CAN
#define CAN ((CAN_TypeDef *)CAN0_BASE)
#endif

#define CAN_MODE_LOM   BIT8 ///< [8] 监听模式使能位
#define CAN_MODE_RESET BIT7 ///< [7] 模块复位模式
#define CAN_MODE_LBME  BIT6 ///< [6] 外部回环模式使能位
#define CAN_MODE_LBMI  BIT5 ///< [5] 内部回环模式使能位
#define CAN_MODE_TPSS  BIT4 ///< [4] PTB 单次传输模式使能位
#define CAN_MODE_TSSS  BIT3 ///< [3] STB 单次传输模式使能位

// RTIE中断使能定义
#define CAN_RTIE_RIE   BIT7 ///< [7] 接收中断使能（Receive Interrupt Enable）
#define CAN_RTIE_ROIE  BIT6 ///< [6] 接收溢出中断使能（Receive Overrun Interrupt Enable）
#define CAN_RTIE_RFIE  BIT5 ///< [5] Rx Buffer 满中断使能（Rx Buffer Full Interrupt Enable）
#define CAN_RTIE_RAFIE BIT4 ///< [4] Rx Buffer 将满中断使能（Rx Buffer Almost Full Interrupt Enable）
#define CAN_RTIE_TPIE  BIT3 ///< [3] PTB 发送中断使能（Transmission Primary Interrupt Enable）
#define CAN_RTIE_TSIE  BIT2 ///< [2] STB 发送中断使能（Transmission Secondary Interrupt Enable）
#define CAN_RTIE_EIE   BIT1 ///< [1] 错误中断使能（Error Interrupt Enable）
#define CAN_RTIE_TSFF  BIT0 ///< [0] Tx Buffer 标志位    1：STB Slot 被全部填满  0：STB Slot 没有被全部填满

// ERRINT中断使能定义
#define CAN_ERRINT_EPIE BIT5 ///< [13] 被动错误中断使能（Error Passive Interrupt Enable） 1：使能0：禁止
#define CAN_ERRINT_ALIE BIT3 ///< [11] 仲裁失败中断使能（Arbitration Lost Interrupt Enable） 1：使能0：禁止
#define CAN_ERRINT_BEIE BIT1 ///< [8 ] 总线错误中断使能（Bus Error Interrupt Enable） 1：使能0：禁止

// RTIE中断标志位
#define CAN_RTIF_RIF   BIT7 ///< [7 ] 接收中断标志位（Receive Interrupt Flag） 1：接收到有效帧（数据帧或者远程帧），写 1 清零   0：没有接收到有效帧
#define CAN_RTIF_ROIF  BIT6 ///< [6 ] 接收溢出中断标志位（Receive Overrun Interrupt Flag） 1：Rx Buffer 至少有一帧未读走的数据被覆盖    0：Rx Buffer 无覆盖 溢出时 ROIF 和 RFIF 同时置 1，写 1 清零
#define CAN_RTIF_RFIF  BIT5 ///< [5 ] Rx Buffer 满中断标志位（Rx Buffer Full Interrupt Flag） 1：Rx Buffer 满，写 1 清零    0：Rx Buffer 未满
#define CAN_RTIF_RAFIF BIT4 ///< [4 ] Rx Buffer 将满中断标志位（Rx Buffer Almost Full Interrupt Flag） 1：被填充的 Rx Buffer Slot 数目大于等于 AFWL 设定值   0：被填充的 Rx Buffer Slot 数目小于 AFWL 设定值
#define CAN_RTIF_TPIF  BIT3 ///< [3 ] PTB 发送中断标志（Transmission Primary Interrupt Flag） 1：触发 PTB 发送，发送成功完成。写 1 清零   0：无 PTB 发送请求，无完成标志
#define CAN_RTIF_TSIF  BIT2 ///< [2 ] STB 发送中断标志（Transmission Secondary Interrupt Flag） 1：触发 STB 发送，发送成功完成。写 1 清零 0：无 STB 发送请求，无完成标志
#define CAN_RTIF_EIF   BIT1 ///< [1 ] 错误中断标志（Error Interrupt Flag） 1：错误计数器的值发生变化，大于或者小于错误警告寄存器的设定值。   写 1 清零  0：无错误计数器的值从小于错误警告寄存器的设定值变为大于设定值，或者从大于设定值变为小于设定值，均会触发中断标志。另外，进入 Bus Off 或从 Bus Off 退出，也会触发。
#define CAN_RTIF_AIF   BIT0 ///< [0 ] 取消发送中断标志（Abort Interrupt Flag） 1：通过 TPA 和 TSA 请求的发送消息被成功取消。写 1 清零0：未取消发送数据  AIF 没有对应的使能寄存器

// ERRINT中断标志位
#define CAN_ERRINT_EWARN BIT7 ///< [15] 错误计数值超过门限中断标志位1：RECNT 或者 TECNT 大于等于 EWL 设定值，写 1 清零0：RECNT 或者 TECNT 小于 EWL 设定值
#define CAN_ERRINT_EPASS BIT6 ///< [14] CAN 设备处于被动错误状态1：CAN 设备处于被动错误状态0：CAN 设备处于主动错误状态
#define CAN_ERRINT_EPIF  BIT4 ///< [12] 被动错误中断标志（Error Passive Interrupt Flag） 1：发生主动错误到被动错误（或者相反）的改变，写 1 清零0：未发生
#define CAN_ERRINT_ALIF  BIT2 ///< [10] 仲裁失败中断标志位（Arbitration Lost Interrupt Flag） 1：仲裁失败，写 1 清零    0：仲裁成功
#define CAN_ERRINT_BEIF  BIT0 ///< [8 ] 总线错误中断标志（Bus Error Interrupt Flag）1：总线错误，写 1 清零0：无总线错误

typedef enum
{
    CanError_None    = 0, ///<  无错误
    CanErorr_Bit     = 1, ///<  位错误
    CanErorr_Form    = 2, ///<  形式错误
    CanErorr_Stuff   = 3, ///<  填充错误
    CanErorr_Ack     = 4, ///<  应答错误
    CanErorr_Crc     = 5, ///<  CRC 错误
    CanErorr_Unknown = 6, ///<  其他错误
} CANErrorKind;

// CAN模块初始化
typedef struct
{
    u32 SBaud; /* 2.0B波特率，必须大于0。 */

    u32 IE;        /* 初始化时要使能的中断 */
    u32 ERRINT_IE; /* 错误中断使能 */
} CAN_InitTypeDef;

/* CAN_Send执行结果 */
typedef enum
{
    CanSend_Succ,        /* CAN发送成功 */
    CanSend_DataTooLong, /* CAN发送失败，数据过长 */
    CanSend_NotIdle,     /* CAN发送成功，当前非空闲 */
    CanSend_Timeout,     /* CAN发送超时 */
    CanSend_STBFull,     /* STB缓冲区已满 */
} CanSendRet;

/* CAN_Recv执行结果 */
typedef enum
{
    CanRecv_Succ,   /* 执行成功，取得数据 */
    CanRecv_NoData, /* 执行失败，无数据 */
} CanRecvRet;

/* STB发送时，需要填入的触发参数 */
typedef enum
{
    STB_TransNo,  /* 本次调用仅添加进STB，暂不发送 */
    STB_TransOne, /* 本次调用添加到STB后，发送一帧 */
    STB_TransAll, /* 本次调用添加到STB后，发送所有帧 */
} STBTransOption;

typedef enum
{
    STB_FIFOMode,     /* 发送缓冲区FIFO模式 */
    STB_PriorityMode, /* 发送缓冲区优先级模式 */
} STBTransMode;

typedef enum
{
    TBSel_PTB = 0, /* Tx Buffer 选择 PTB */
    TBSel_STB = 1, /* Tx Buffer 选择 STB */
} TBSelOption;

/* 设置ID过滤时，对标准帧和扩展帧的设置选项 */
typedef enum
{
    IDEFilter_St_Ex, /* 接收标准帧+扩展帧 */
    IDEFilter_St,    /* 只接收标准帧 */
    IDEFilter_Ex,    /* 只接收扩展帧 */
} IDEFilterOption;

typedef struct
{
    u32 id;
    u8 ide;
    u8 rtr;

    u8 *buf;
    u8 len;

    TBSelOption tbsel; /* TBSel_PTB或TBSel_STB。如果指定STB，CAN_Send()之后还需调用CAN_Send_Trig()触发发送 */
    u8 ss;             /* 0-错误时自动重发，1-单次发送不重发 */
} CANTxMsg;

#define CANRXMSG_HEADLEN 8 /* CANRxMsg中id~len的字节数 */
typedef struct
{
    u32 id;
    u8 ide;
    u8 rtr;
    u8 valid; /* 是否有效，接收成功valid=1，处理完设置valid=0 */

    u8 len;
    u8 buf[64];
} CANRxMsg;

extern CANRxMsg g_rxMsg;

void CAN_Init(u8 BTR3, u8 BTR2, u8 BTR1, u8 BTR0);

void CAN_StructInit(CAN_InitTypeDef *this);
void CAN_Init1(CAN_InitTypeDef *this);

CanSendRet CAN_Send(CANTxMsg *tx_msg);
CanSendRet CAN_Send_Trig(STBTransOption stb_trans); /* 触发STB缓冲区数据发出 */

CanSendRet My_CAN_Send_Msg(u32 id, u8 ide, u8 rtr, u8 *msg, u8 len);

CanRecvRet CAN_Recv(CANRxMsg *rx_msg);
CanRecvRet CAN_Receive_Msg(u32 *id, u8 *len, u8 *ide, u8 *rtr, u8 *buf);

void CAN_Send_Cancel(TBSelOption tbsel);

void IDx_Filter(u8 x, u32 id, u32 mask, IDEFilterOption ide_filter);
void IDx_FilterCmd(u8 x, FuncState state);

void CAN_LBMICmd(FuncState state); /* 内部回环模式使能/禁止 */
void CAN_LBMECmd(FuncState state); /* 外部回环模式使能/禁止 */

void CAN_SS_Enable(TBSelOption tbsel, FuncState state); /* 单次传输模式使能 */

void CAN_Enable(void);
void CAN_Disable(void);

void CAN_Reset(void);

void CAN_SetSTBMode(STBTransMode tsMode);

u8 CAN_STBFullGet(void);

u8 CAN_RxErrorCntGet(void);
u8 CAN_TxErrorCntGet(void);
u8 CAN_ErrorPassiveGet(void);
u8 CAN_BusoffGet(void);

CANErrorKind CAN_KindOfErrorGet(void);
u8 CAN_ArbitrationLostCap(void);
u8 CAN_ROverflowGet(void);

#define ID0_Filter(a, b, c) IDx_Filter(0, a, b, c)
#define ID1_Filter(a, b, c) IDx_Filter(1, a, b, c)
#define ID2_Filter(a, b, c) IDx_Filter(2, a, b, c)
#define ID3_Filter(a, b, c) IDx_Filter(3, a, b, c)

#endif
