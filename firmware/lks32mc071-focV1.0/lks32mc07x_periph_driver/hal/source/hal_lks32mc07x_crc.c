#include "../include/hal_lksmcu_crc.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"

// 仅内部使用
typedef enum
{
    CRC_WIDTH_8,
    CRC_WIDTH_16,
    CRC_WIDTH_32
} CRC_Width;
// 仅内部使用
typedef struct
{
    uint32_t polynomial; // 公式
    uint32_t initValue;  // 初始值
    uint32_t xorOut;     // 结果异或值
    uint8_t reflectIn;   // 输入反转使能
    uint8_t reflectOut;  // 输出反转使能
    CRC_Width width;     // 数据宽度
} CRC_Model_Params;
// 仅内部使用
static const CRC_Model_Params crcModels[] = {
    {0x07, 0x00, 0x00, 0, 0, CRC_WIDTH_8},                    // CRC8
    {0x07, 0x00, 0x55, 0, 0, CRC_WIDTH_8},                    // CRC8_ITU
    {0x07, 0xFF, 0x00, 1, 1, CRC_WIDTH_8},                    // CRC8_ROHC
    {0x31, 0x00, 0x00, 1, 1, CRC_WIDTH_8},                    // CRC8_MAXIMx
    {0x8005, 0x0000, 0x0000, 1, 1, CRC_WIDTH_16},             // CRC16_IBMx1
    {0x8005, 0x0000, 0xFFFF, 1, 1, CRC_WIDTH_16},             // CRC16_MAXIM
    {0x8005, 0xFFFF, 0xFFFF, 1, 1, CRC_WIDTH_16},             // CRC16_USBx1
    {0x8005, 0xFFFF, 0x0000, 1, 1, CRC_WIDTH_16},             // CRC16_MODBU
    {0x1021, 0x0000, 0x0000, 1, 1, CRC_WIDTH_16},             // CRC16_CCITT
    {0x1021, 0xFFFF, 0x0000, 0, 0, CRC_WIDTH_16},             // CRC16_CCITT_FALSE
    {0x1021, 0xFFFF, 0xFFFF, 1, 1, CRC_WIDTH_16},             // CRC16_X25
    {0x1021, 0x0000, 0x0000, 0, 0, CRC_WIDTH_16},             // CRC16_XMODEM
    {0x3D65, 0x0000, 0xFFFF, 1, 1, CRC_WIDTH_16},             // CRC16_DNP
    {0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, 1, 1, CRC_WIDTH_32}, // CRC32
    {0x04C11DB7, 0xFFFFFFFF, 0x00000000, 0, 0, CRC_WIDTH_32}, // CRC32_MPEG_2
};
// 仅内部使用
static uint32_t HAL_CRC_Reflect(uint32_t data, uint8_t width)
{
    uint32_t result = 0;
    uint8_t i;
    for (i = 0; i < width; i++)
    {
        if (data & (1 << i))
        {
            result |= (1 << (width - 1 - i));
        }
    }
    return result;
}

/**
 * @brief CRC模块复位
 * @param CRC_x CRC模块编号
 */
void HAL_CRC_Reset(HAL_CRC_x CRC_x)
{
    (void)CRC_x;
    HAL_REG_SYS_UNLOCK();
    HAL_REG_SET(SYS_SFT_RST, SYS_SFT_RST_CRC0_SFT_RST_BIT);
    HAL_REG_SYS_LOCK();
}

/**
 * @brief CRC模块使能
 * @param CRC_x CRC模块编号
 */
void HAL_CRC_Enable(HAL_CRC_x CRC_x)
{
    (void)CRC_x;
    HAL_REG_SYS_UNLOCK();
    HAL_REG_SET(SYS_CLK_FEN, SYS_CLK_FEN_CRC0_CLK_EN_BIT);
    HAL_REG_SYS_LOCK();
}

/**
 * @brief CRC模块失能
 * @param CRC_x CRC模块编号
 */
void HAL_CRC_Disable(HAL_CRC_x CRC_x)
{
    (void)CRC_x;
    HAL_REG_SYS_UNLOCK();
    HAL_REG_RESET(SYS_CLK_FEN, SYS_CLK_FEN_CRC0_CLK_EN_BIT);
    HAL_REG_SYS_LOCK();
}

/**
 * @brief CRC计算
 * @param CRC_x CRC模块编号
 * @param model CRC模型
 * @param data 数据地址
 * @param len 数据长度
 */
uint32_t HAL_CRC_Calc(HAL_CRC_x CRC_x, HAL_CRC_MODEL_x model, uint8_t *data, uint32_t len)
{
    const CRC_Model_Params *params = &crcModels[model];
    uint32_t crc                   = params->initValue;
    uint8_t width_bytes            = (params->width == CRC_WIDTH_8) ? 1 : (params->width == CRC_WIDTH_16) ? 2
                                                                                                          : 4;
    uint8_t width_bits             = width_bytes * 8;
    uint32_t top_bit               = 1 << (width_bits - 1);
    uint32_t mask                  = (width_bits < 32) ? (uint32_t)((1 << width_bits) - 1) : 0xFFFFFFFF;
    uint32_t i;
    (void)CRC_x;
    if (model >= sizeof(crcModels) / sizeof(crcModels[0]))
    {
        return 0; // 无效模型
    }
    for (i = 0; i < len; i++)
    {
        uint32_t j;
        uint8_t byte = data[i];
        if (params->reflectIn)
        {
            byte = HAL_CRC_Reflect(byte, 8);
        }

        // 根据CRC宽度处理输入
        if (params->width == CRC_WIDTH_8)
        {
            crc ^= (uint32_t)byte;
        }
        else if (params->width == CRC_WIDTH_16)
        {
            crc ^= (uint32_t)byte << 8; // 假设数据是大端序输入
        }
        else
        {
            crc ^= (uint32_t)byte << 24;
        }
        for (j = 0; j < 8; j++)
        {
            if (crc & top_bit)
            {
                crc = (crc << 1) ^ params->polynomial;
            }
            else
            {
                crc <<= 1;
            }
            crc &= mask; // 确保只保留有效位
        }
    }

    if (params->reflectOut)
    {
        crc = HAL_CRC_Reflect(crc, width_bits);
    }

    crc ^= params->xorOut;

    // 根据宽度返回适当大小的值
    if (params->width == CRC_WIDTH_8)
    {
        return crc & 0xFF;
    }
    else if (params->width == CRC_WIDTH_16)
    {
        return crc & 0xFFFF;
    }
    return crc;
}
