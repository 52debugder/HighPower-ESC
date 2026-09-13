#include "../include/hal_lksmcu_flash.h"
#include "../hal_lks32mc07x.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"
// 使用三个扇区（确保在随机分配地址时，能分配到至少两个扇区）
static volatile const uint8_t HAL_FLASH_data[3 * 512] = {0};
/**
 * @brief 模块复位,预留接口
 * @param flash 模块类型
 */
void HAL_FLASH_Reset(HAL_FLASH_x flash)
{
    (void)flash;
}

/**
 * @brief 模块打开,预留接口
 * @param flash 模块类型
 */
void HAL_FLASH_Enable(HAL_FLASH_x flash)
{
    (void)flash;
}

/**
 * @brief 模块关闭,预留接口
 * @param flash 模块类型
 */
void HAL_FLASH_Disable(HAL_FLASH_x flash)
{
    (void)flash;
}

/**
 * @brief 使能flash缓存加速
 * @param flash 模块类型
 */
void HAL_FLASH_EnableCache(HAL_FLASH_x flash)
{
    (void)flash;
    HAL_REG_SET(FLASH_CFG, FLASH_CFG_PREF_BIT);
}

/**
 * @brief 关闭flash缓存加速
 * @param flash 模块类型
 */
void HAL_FLASH_DisableCache(HAL_FLASH_x flash)
{
    (void)flash;
    HAL_REG_RESET(FLASH_CFG, FLASH_CFG_PREF_BIT);
}

/**
 * @brief 获取一个扇区的大小,和HAL_FLASH_SECTOR_SIZE等效
 * @param flash 模块类型
 * @return uint32_t 扇区大小
 */
uint32_t HAL_FLASH_ReadSectorSize(HAL_FLASH_x flash)
{
    (void)flash;
    return 512;
}

/**
 * @brief 读FLASH取数据
 * @param flash 模块类型
 * @param flashaddr flash地址
 * @param data 读取的数据指针
 * @param len 读取长度
 */
void HAL_FLASH_Read(HAL_FLASH_x flash, uint32_t flashaddr, void *data, uint32_t len)
{
    uint32_t i;
    for (i = 0; i < len; i++)
    {
        ((uint8_t *)data)[i] = HAL_FLASH_ReadUint8(flash, flashaddr + i);
    }
}

/**
 * @brief 读FLASH取数据
 * @param flash 模块类型
 * @param flashaddr flash地址
 * @return  读取的数据
 */
uint8_t HAL_FLASH_ReadUint8(HAL_FLASH_x flash, uint32_t flashaddr)
{
    (void)flash;
    return REG8(flashaddr);
}

/**
 * @brief 读FLASH取数据
 * @param flash 模块类型
 * @param flashaddr flash地址
 * @return  读取的数据
 */
uint16_t HAL_FLASH_ReadUint16(HAL_FLASH_x flash, uint32_t flashaddr)
{
    (void)flash;
    return REG16(flashaddr);
}

/**
 * @brief 读FLASH取数据
 * @param flash 模块类型
 * @param flashaddr flash地址
 * @return  读取的数据
 */
uint32_t HAL_FLASH_ReadUint32(HAL_FLASH_x flash, uint32_t flashaddr)
{
    (void)flash;
    return REG32(flashaddr);
}

/**
 * @brief 扇区擦除,len只能是扇区大小的整数倍,不够一个扇区的部分会被忽略
 * @param flash 模块类型
 * @param flashaddr flash地址
 * @param len 擦除长度
 */
void HAL_FLASH_Erase(HAL_FLASH_x flash, uint32_t flashaddr, uint32_t len)
{
    (void)flash;
    HAL_REG_SYS_UNLOCK();
    HAL_REG_WRITE(SYS_FLSE, 0x8FCA);
    HAL_REG_SET(FLASH_CFG, FLASH_CFG_ERS_EN_BIT);
    HAL_REG_RESET(FLASH_CFG, FLASH_CFG_ERS_TYPE_BIT | FLASH_CFG_REGION_BIT); // 确保擦除区域是MAIN并且是扇区擦除
    for (; ((int32_t)len) > 0; len -= 512, flashaddr += 512)
    {
        HAL_REG_WRITE(FLASH_ADDR, flashaddr);
        HAL_REG_WRITE(FLASH_ERASE, 0x7654dcba);
    }
    HAL_REG_WRITE_BIT(FLASH_CFG, FLASH_CFG_ERS_EN_BIT | FLASH_CFG_ERS_TYPE_BIT | FLASH_CFG_REGION_BIT, 0);
    HAL_REG_WRITE(SYS_FLSE, 0);
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 编程
 * @param flash 模块类型
 * @param flashaddr flash地址,低两位会被忽略
 * @param data 数据指针
 * @param len 数据长度
 */
void HAL_FLASH_Program(HAL_FLASH_x flash, uint32_t flashaddr, uint8_t *data, uint32_t len)
{
    uint8_t *p;
    uint32_t len1 = len;
    (void)flash;
    HAL_REG_SYS_UNLOCK();
    HAL_REG_WRITE(SYS_FLSP, 0x8F35);
    HAL_REG_SET(FLASH_CFG, FLASH_CFG_PRG_EN_BIT | FLASH_CFG_ADR_INC_BIT);
    HAL_REG_RESET(FLASH_CFG, FLASH_CFG_REGION_BIT); // 确保编程区域是MAIN
    flashaddr &= ~0x3;
    HAL_REG_WRITE(FLASH_ADDR, flashaddr);
    for (p = data; len1 > 0; len1 -= 4, p += 4)
    {
        HAL_REG_WRITE(FLASH_WDATA, p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24));
    }
    HAL_REG_RESET(FLASH_CFG, FLASH_CFG_PRG_EN_BIT | FLASH_CFG_ADR_INC_BIT);
    HAL_REG_WRITE(SYS_FLSP, 0);
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 更新数据,等效先擦除再编程
 * @param flash 模块类型
 * @param flashaddr flash地址
 * @param data 数据指针
 * @param len 数据长度
 */
void HAL_FLASH_Update(HAL_FLASH_x flash, uint32_t flashaddr, uint8_t *data, uint32_t len)
{
    HAL_FLASH_Erase(flash, flashaddr, len);
    HAL_FLASH_Program(flash, flashaddr, data, len);
}

// 仅内部使用，计算CRC32
static uint32_t HAL_FLASH_SecurityParameterCrc(HAL_FLASH_x flash, uint32_t addr)
{
    uint32_t crc              = 0xFFFFFFFF; // CRC32初始值
    const uint32_t polynomial = 0xEDB88320; // CRC32多项式

    uint32_t i;
    for (i = 0; i < 504; i++)
    {
        uint32_t j;
        uint8_t byte = HAL_FLASH_ReadUint8(flash, addr + i);

        // 将字节与CRC的高8位异或
        crc ^= byte;
        // 处理每个bit
        for (j = 0; j < 8; j++)
        {
            if (crc & 1)
            {
                crc = (crc >> 1) ^ polynomial;
            }
            else
            {
                crc >>= 1;
            }
        }
    }

    return ~crc; // 取反得到最终结果
}

/**
 * @brief 保存安全参数
 * @param flash 模块类型
 * @param defaultdata 默认值
 * @param data 待写入的数据
 * @param len 数据长度
 */
void HAL_FLASH_SecurityParameterSave(HAL_FLASH_x flash, void *defaultdata, void *data, uint32_t len)
{
    uint32_t addr0 = ((uint32_t)(uintptr_t)HAL_FLASH_data + 512) & ~0x1ff;
    uint32_t addr1 = addr0 + 512;
    uint32_t flg   = 0;
    uint32_t addr  = HAL_FLASH_SecurityParameterRead(flash, 0, 0, 0);
    if (addr != 0xffffffff)
    {
        uint32_t i;
        for (i = 0; i < len; i++)
        {
            // 判断待写入的数据和flash保存的数据是否一致
            if (((uint8_t *)data)[i] != HAL_FLASH_ReadUint8(flash, addr + i))
            {
                flg = 1;
                break;
            }
        }
    }
    else
    {
        uint32_t i;
        for (i = 0; i < len; i++)
        {
            // 判断待写入的数据和默认数据是否一致
            if (((uint8_t *)data)[i] != ((uint8_t *)defaultdata)[i])
            {
                flg = 1;
                break;
            }
        }
    }
    if (flg != 0) // 需要保存数据
    {
        uint32_t cnt;
        uint32_t cnt1;
        uint32_t crc;
        if (addr == addr0)
        {
            cnt  = HAL_FLASH_ReadUint32(flash, addr0 + 500);
            cnt1 = cnt + 1;
            if (cnt1 == 0) // 溢出后从1开始计数
            {
                cnt1 = 1;
            }
            HAL_FLASH_Erase(flash, addr1, 512);                      // 擦除另一个扇区
            HAL_FLASH_Program(flash, addr1, data, len);              // 写入用户数据
            HAL_FLASH_Program(flash, addr1 + 500, (void *)&cnt1, 4); // 写入计数
            crc = HAL_FLASH_SecurityParameterCrc(flash, addr1);      // 计算CRC结果
            HAL_FLASH_Program(flash, addr1 + 504, (void *)&crc, 4);  // 写入crc

            if (cnt == 0xffffffff) // 溢出后清空另一个扇区（确保HAL_FLASH_SecurityParameterRead判断正确）
            {
                HAL_FLASH_Erase(flash, addr0, 512);
            }
        }
        else if (addr == addr1)
        {
            cnt  = HAL_FLASH_ReadUint32(flash, addr0 + 500);
            cnt1 = cnt + 1;
            if (cnt1 == 0) // 溢出后从1开始计数
            {
                cnt1 = 1;
            }
            HAL_FLASH_Erase(flash, addr0, 512);
            HAL_FLASH_Program(flash, addr0, data, len);
            HAL_FLASH_Program(flash, addr0 + 500, (void *)&cnt1, 4);
            crc = HAL_FLASH_SecurityParameterCrc(flash, addr0);
            HAL_FLASH_Program(flash, addr0 + 504, (void *)&crc, 4);

            if (cnt == 0xffffffff) // 溢出后清空另一个扇区（确保HAL_FLASH_SecurityParameterRead判断正确）
            {
                HAL_FLASH_Erase(flash, addr0, 512);
            }
        }
        else
        {
            cnt = 1;                                                // 第一次写入时，写入数据到扇区0，并从1开始计数
            HAL_FLASH_Erase(flash, addr1, 512);                     // 擦除另一个扇区
            HAL_FLASH_Program(flash, addr1, data, len);             // 写入用户数据
            HAL_FLASH_Program(flash, addr1 + 500, (void *)&cnt, 4); // 写入计数
            crc = HAL_FLASH_SecurityParameterCrc(flash, addr1);     // 计算CRC结果
            HAL_FLASH_Program(flash, addr1 + 504, (void *)&crc, 4); // 写入crc
        }
    }
}

/**
 * @brief 读取安全参数
 * @param flash 模块类型
 * @param data 数据指针
 * @param len 数据长度
 * @return 使用的flash地址
 */
uint32_t HAL_FLASH_SecurityParameterRead(HAL_FLASH_x flash, void *defaultdata, void *data, uint32_t len)
{
    uint32_t addr0 = ((uint32_t)(uintptr_t)HAL_FLASH_data + 512) & ~0x1ff;
    uint32_t addr1 = addr0 + 512;
    uint32_t addr  = 0;
    uint32_t val0  = REG32(addr0 + 500);
    uint32_t val1  = REG32(addr1 + 500);
    if (val0 > val1)
    {
        // 优先使用扇区0
        if (HAL_FLASH_SecurityParameterCrc(flash, addr0) == HAL_FLASH_ReadUint32(flash, addr0 + 504))
        { // 确保校验通过
            addr = addr0;
        }
        else if (HAL_FLASH_SecurityParameterCrc(flash, addr1) == HAL_FLASH_ReadUint32(flash, addr1 + 504))
        {
            addr = addr1;
        }
        else
        {
            // 两个扇区数据都丢失，则返回默认参数
            // 运行时flash被误擦除
            // flash未初始化
            // flash保存的参数和默认值一致（如果flash数据不做任何修改，则不会触发保存的动作）

            addr = 0xffffffff;
        }
    }
    else
    {
        // 优先使用扇区1
        if (HAL_FLASH_SecurityParameterCrc(flash, addr1) == HAL_FLASH_ReadUint32(flash, addr1 + 504))
        { // 确保校验通过
            addr = addr1;
        }
        else if (HAL_FLASH_SecurityParameterCrc(flash, addr0) == HAL_FLASH_ReadUint32(flash, addr0 + 504))
        {
            addr = addr0;
        }
        else
        {
            // 两个扇区数据都丢失，则返回默认参数
            // 运行时flash被误擦除
            // flash未初始化
            // flash保存的参数和默认值一致（如果flash数据不做任何修改，则不会触发保存的动作）
            addr = 0xffffffff;
        }
    }
    if (len != 0)
    {
        if (addr != 0xffffffff)
        {
            HAL_FLASH_Read(flash, addr, data, len);
        }
        else
        {
            uint32_t i;
            for (i = 0; i < len; i++)
            {
                ((uint8_t *)data)[i] = ((uint8_t *)defaultdata)[i];
            }
        }
    }
    return addr;
}
