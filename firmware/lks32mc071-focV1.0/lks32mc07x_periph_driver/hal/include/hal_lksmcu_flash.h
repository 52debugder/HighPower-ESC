#ifndef __HAL_LKSMCU_FLASH_H__
#define __HAL_LKSMCU_FLASH_H__

#include "stdint.h"
typedef enum
{
    HAL_FLASH_0, ///< 内部flash
    HAL_FLASH_1, ///< 外部flash
} HAL_FLASH_x;
// 初始化
void HAL_FLASH_Reset(HAL_FLASH_x);   // 模块复位,预留接口
void HAL_FLASH_Enable(HAL_FLASH_x);  // 模块打开,预留接口
void HAL_FLASH_Disable(HAL_FLASH_x); // 模块关闭,预留接口

void HAL_FLASH_EnableCache(HAL_FLASH_x);                                              // 使能flash缓存加速
void HAL_FLASH_DisableCache(HAL_FLASH_x);                                             // 关闭flash缓存加速
uint32_t HAL_FLASH_ReadSectorSize(HAL_FLASH_x);                                       // 获取一个扇区的大小,和HAL_FLASH_SECTOR_SIZE等效
void HAL_FLASH_Read(HAL_FLASH_x, uint32_t flashaddr, void *data, uint32_t len);       // 任意长度
uint8_t HAL_FLASH_ReadUint8(HAL_FLASH_x, uint32_t flashaddr);                         // 读(U8)
uint16_t HAL_FLASH_ReadUint16(HAL_FLASH_x, uint32_t flashaddr);                       // 读(U16)
uint32_t HAL_FLASH_ReadUint32(HAL_FLASH_x, uint32_t flashaddr);                       // 读(U32)
void HAL_FLASH_Erase(HAL_FLASH_x, uint32_t flashaddr, uint32_t len);                  // 扇区擦除,len只能是扇区大小的整数倍,不够一个扇区的部分会被忽略
void HAL_FLASH_Program(HAL_FLASH_x, uint32_t flashaddr, uint8_t *data, uint32_t len); // 编程
void HAL_FLASH_Update(HAL_FLASH_x, uint32_t flashaddr, uint8_t *data, uint32_t len);  // 更新数据,等效先擦除再编程

// 安全参数（调用时自动分配地址
// 支持大小为 500的uint8_t的数据
// 保留3个word用来校验
// 状态+CRC32+保留位
// 调用时必须传入defaultdata（确保极端情况下，data的数据安全）
void HAL_FLASH_SecurityParameterSave(HAL_FLASH_x, void *defaultdata, void *data, uint32_t len);     // 保存数据（仅变化时保存，最多可能会关闭中断20mS）
uint32_t HAL_FLASH_SecurityParameterRead(HAL_FLASH_x, void *defaultdata, void *data, uint32_t len); // 读数据

#endif
