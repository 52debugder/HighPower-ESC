#ifndef __HAL_LKSMCU_CAN_H__
#define __HAL_LKSMCU_CAN_H__

#include <stdint.h>
#include "../include/hal_lksmcu_gpio.h"

typedef enum
{
    HAL_CAN_0,
} HAL_CAN_x;

/* CAN帧的属性 */
typedef enum
{
    /* 扩展帧、远程帧 */
    HAL_CAN_FRAME_IDE0_RTR0, ///<  ide=0 rtr=0
    HAL_CAN_FRAME_IDE0_RTR1, ///<  ide=0 rtr=1
    HAL_CAN_FRAME_IDE1_RTR0, ///<  ide=1 rtr=0
    HAL_CAN_FRAME_IDE1_RTR1, ///<  ide=1 rtr=1

    /* 仅适用于CANFD */
    HAL_CAN_FRAME_IDE0_RTR0_FD1_BRS0, ///<  ide=0 rtr=0 fd=1 brs=0
    HAL_CAN_FRAME_IDE0_RTR0_FD1_BRS1, ///<  ide=0 rtr=0 fd=1 brs=1

    HAL_CAN_FRAME_IDE1_RTR0_FD1_BRS0, ///<  ide=1 rtr=0 fd=1 brs=0
    HAL_CAN_FRAME_IDE1_RTR0_FD1_BRS1, ///<  ide=1 rtr=0 fd=1 brs=1
} HAL_CAN_FRAME_x;

/* Error of kind */
typedef enum
{
    HAL_CAN_ERROR_None    = 0, ///<  无错误
    HAL_CAN_ERROR_Bit     = 1, ///<  位错误
    HAL_CAN_ERROR_Form    = 2, ///<  形式错误
    HAL_CAN_ERROR_Stuff   = 3, ///<  填充错误
    HAL_CAN_ERROR_Ack     = 4, ///<  应答错误
    HAL_CAN_ERROR_Crc     = 5, ///<  CRC 错误
    HAL_CAN_ERROR_Unknown = 6, ///<  其他错误
} HAL_CAN_ERROR_x;

typedef enum
{
    HAL_CAN_TSSTAT_Empty    = 0,
    HAL_CAN_TSSTAT_LessHalf = 1,
    HAL_CAN_TSSTAT_Half     = 2,
    HAL_CAN_TSSTAT_Full     = 3,
} HAL_CAN_TSSTAT_x;

typedef enum
{
    HAL_CAN_AE_0,
    HAL_CAN_AE_1,
    HAL_CAN_AE_2,
    HAL_CAN_AE_3,

    /* 以下仅在45x支持 */
    HAL_CAN_AE_4,
    HAL_CAN_AE_5,
    HAL_CAN_AE_6,
    HAL_CAN_AE_7,

    HAL_CAN_AE_8,
    HAL_CAN_AE_9,
    HAL_CAN_AE_10,
    HAL_CAN_AE_11,

    HAL_CAN_AE_12,
    HAL_CAN_AE_13,
    HAL_CAN_AE_14,
    HAL_CAN_AE_15,
} HAL_CAN_AE_x;

/* STB发送时，需要填入的触发参数 */
typedef enum
{
    HAL_CAN_STBTrig_One, /* 触发STB发送一帧 */
    HAL_CAN_STBTrig_All, /* 触发STB发送所有帧 */
} HAL_CAN_STBTrig_x;

typedef enum
{
    HAL_CAN_STBMode_FIFO,     /* 发送缓冲区FIFO模式 */
    HAL_CAN_STBMode_Priority, /* 发送缓冲区优先级模式 */
} HAL_CAN_STBMode_x;

/* 设置ID过滤时，对标准帧和扩展帧的设置选项 */
typedef enum
{
    HAL_CAN_IDEFilter_All, /* 接收标准帧+扩展帧 */
    HAL_CAN_IDEFilter_St,  /* 只接收标准帧 */
    HAL_CAN_IDEFilter_Ex,  /* 只接收扩展帧 */
} HAL_CAN_IDEFilter_x;

void HAL_CAN_Reset(HAL_CAN_x can_x);
void HAL_CAN_Enable(HAL_CAN_x can_x);
void HAL_CAN_Disable(HAL_CAN_x can_x);

void HAL_CAN_SetBaud(HAL_CAN_x can_x, uint32_t baud);
void HAL_CAN_SetClockDiv(HAL_CAN_x can_x, uint32_t div); // 设置CAN预分频 div=实际除数(1~256)
uint32_t HAL_CAN_GetClockDiv(HAL_CAN_x can_x);           // 获取CAN预分频实际除数
uint32_t HAL_CAN_GetClockFreq(HAL_CAN_x can_x);          // 获取分频后工作时钟(Hz)
uint32_t HAL_CAN_GetBaud(HAL_CAN_x can_x);               // 获取当前标称波特率(bps)
void HAL_CAN_SetFastBaud(HAL_CAN_x can_x, uint32_t fbaud);
void HAL_CAN_SetTDC(HAL_CAN_x can_x, uint8_t sspoff);

/* PTB方式发送CAN数据 */
bool HAL_CAN_TxData(HAL_CAN_x can_x, uint32_t id, HAL_CAN_FRAME_x frame_x, uint8_t *buf, uint32_t len);

/* STB方式发送数据，写数据和触发分两步执行 */
bool HAL_CAN_TxData_STBWrite(HAL_CAN_x can_x, uint32_t id, HAL_CAN_FRAME_x frame_x, uint8_t *buf, uint32_t len);
bool HAL_CAN_TxData_STBTrig(HAL_CAN_x can_x, HAL_CAN_STBTrig_x trig);

void HAL_CAN_TxCancel(HAL_CAN_x can_x);

bool HAL_CAN_Txing(HAL_CAN_x can_x);
bool HAL_CAN_STBFull(HAL_CAN_x can_x);
HAL_CAN_TSSTAT_x HAL_CAN_TSStat(HAL_CAN_x can_x);

bool HAL_CAN_RxData(HAL_CAN_x can_x);
uint32_t HAL_CAN_RxDataID(HAL_CAN_x can_x);
uint8_t HAL_CAN_RxDataBuf(HAL_CAN_x can_x, uint8_t *buf);
uint8_t HAL_CAN_RxDataLen(HAL_CAN_x can_x);
uint8_t HAL_CAN_RxDataIde(HAL_CAN_x can_x);
uint8_t HAL_CAN_RxDataRtr(HAL_CAN_x can_x);
uint8_t HAL_CAN_RxDataFdf(HAL_CAN_x can_x);

void HAL_CAN_IDx_Filter(HAL_CAN_x can_x, u8 x, u32 id, u32 mask, HAL_CAN_IDEFilter_x ide_filter);
void HAL_CAN_IDx_FilterEnable(HAL_CAN_x can_x, HAL_CAN_AE_x ae_x);
void HAL_CAN_IDx_FilterDisable(HAL_CAN_x can_x, HAL_CAN_AE_x ae_x);

void HAL_CAN_SetSTBMode(HAL_CAN_x can_x, HAL_CAN_STBMode_x mode_x);

void HAL_CAN_LOM_Enable(HAL_CAN_x can_x);
void HAL_CAN_LOM_Disable(HAL_CAN_x can_x);

void HAL_CAN_LBMI_Enable(HAL_CAN_x can_x);
void HAL_CAN_LBMI_Disable(HAL_CAN_x can_x);

void HAL_CAN_LBME_Enable(HAL_CAN_x can_x);
void HAL_CAN_LBME_Disable(HAL_CAN_x can_x);

void HAL_CAN_SS_Enable(HAL_CAN_x can_x);
void HAL_CAN_SS_Disable(HAL_CAN_x can_x);

uint8_t HAL_CAN_RxErrorCnt(HAL_CAN_x can_x);
uint8_t HAL_CAN_TxErrorCnt(HAL_CAN_x can_x);
uint8_t HAL_CAN_ErrorPassive(HAL_CAN_x can_x);
uint8_t HAL_CAN_Busoff(HAL_CAN_x can_x);
uint8_t HAL_CAN_ArbitrationLostCap(HAL_CAN_x can_x);
uint8_t HAL_CAN_ROverflow(HAL_CAN_x can_x);
HAL_CAN_ERROR_x HAL_CAN_KindOfError(HAL_CAN_x can_x);

void HAL_CAN_SetGpioTx(HAL_CAN_x can_x, HAL_GPIO_Px gpio_x);
void HAL_CAN_SetGpioRx(HAL_CAN_x can_x, HAL_GPIO_Px gpio_x);

#endif
