/**
 * 文件：drv8353.c
 * 说明：DRV8353S 栅极驱动器的 SPI 寄存器访问和故障复位流程。
 *
 * 板级连接：
 * EN     -> P1.10
 * nFAULT -> P2.3，低电平有效
 * nSCS   -> P2.12，手动片选，低电平有效
 * SDO    -> P2.9/SPI_DI，开漏输出，板上或片内需要上拉
 * SDI    -> P2.10/SPI_DO
 * SCLK   -> P2.1/SPI_CLK
 */

#include "drv8353.h"

#include "hardware_config.h"
#include "lks32mc07x_gpio.h"
#include "lks32mc07x_sys.h"

extern void SoftDelay(u32 cnt);

#define DRV8353_SPI_READ_BIT            (0x8000U)
#define DRV8353_SPI_ADDR_SHIFT          (11U)
#define DRV8353_SPI_ADDR_MASK           (0x0FU)

#define DRV8353_SPI_CFG_ENABLE          (BIT0)
#define DRV8353_SPI_CFG_MASTER          (BIT4)
#define DRV8353_SPI_CFG_CPHA_FALL_SAMPLE (BIT3)

#define DRV8353_SPI_IE_COMPLETE_FLAG    (BIT2)
#define DRV8353_SPI_IE_ABNORMAL_FLAG    (BIT1)
#define DRV8353_SPI_IE_OVERFLOW_FLAG    (BIT0)
#define DRV8353_SPI_IE_ALL_FLAGS        (DRV8353_SPI_IE_COMPLETE_FLAG | \
                                         DRV8353_SPI_IE_ABNORMAL_FLAG | \
                                         DRV8353_SPI_IE_OVERFLOW_FLAG)
#define DRV8353_SPI_DIV_CPU_MODE        (BIT15)
#define DRV8353_SPI_BAUD_DIV            (23U)
#define DRV8353_SPI_BITS                (16U)
#define DRV8353_SPI_TIMEOUT_COUNT       (60000U)

#define DRV8353_DELAY_CS_SETUP          (4U)
#define DRV8353_DELAY_AFTER_ENABLE      (3000U)
#define DRV8353_DELAY_RESET_LOW         (200U)
#define DRV8353_DELAY_RESET_WAKE        (3000U)

static uint8_t drv8353_last_spi_status = DRV8353_SPI_OK;

static void drv8353_select(void)
{
    GPIO_ResetBits(DRV8353_NSCS_GPIO, DRV8353_NSCS_PIN);
    SoftDelay(DRV8353_DELAY_CS_SETUP);
}

static void drv8353_deselect(void)
{
    SoftDelay(DRV8353_DELAY_CS_SETUP);
    GPIO_SetBits(DRV8353_NSCS_GPIO, DRV8353_NSCS_PIN);
    SoftDelay(DRV8353_DELAY_CS_SETUP);
}

static uint16_t drv8353_make_read_frame(uint8_t addr)
{
    return (uint16_t)(DRV8353_SPI_READ_BIT |
                      (((uint16_t)addr & DRV8353_SPI_ADDR_MASK) << DRV8353_SPI_ADDR_SHIFT));
}

static uint16_t drv8353_make_write_frame(uint8_t addr, uint16_t data)
{
    return (uint16_t)((((uint16_t)addr & DRV8353_SPI_ADDR_MASK) << DRV8353_SPI_ADDR_SHIFT) |
                      (data & DRV8353_REG_DATA_MASK));
}

static uint16_t drv8353_transfer16(uint16_t tx_data)
{
    uint32_t timeout = DRV8353_SPI_TIMEOUT_COUNT;

    drv8353_last_spi_status = DRV8353_SPI_TIMEOUT;
    SPI0_IE = DRV8353_SPI_IE_ALL_FLAGS;

    drv8353_select();
    SPI0_TXDATA = tx_data;

    while ((SPI0_IE & DRV8353_SPI_IE_COMPLETE_FLAG) == 0U)
    {
        if ((SPI0_IE & (DRV8353_SPI_IE_ABNORMAL_FLAG | DRV8353_SPI_IE_OVERFLOW_FLAG)) != 0U)
        {
            drv8353_last_spi_status = DRV8353_SPI_ABNORMAL;
            break;
        }

        if (timeout == 0U)
            break;

        timeout--;
    }

    if ((SPI0_IE & DRV8353_SPI_IE_COMPLETE_FLAG) != 0U)
        drv8353_last_spi_status = DRV8353_SPI_OK;

    drv8353_deselect();
    SPI0_IE = DRV8353_SPI_IE_ALL_FLAGS;

    return (uint16_t)(SPI0_RXDATA & 0xFFFFU);
}

void DRV8353_Init(void)
{
    SYS_ModuleClockCmd(SYS_Module_SPI0, ENABLE);
    SYS_SPIClkDiv(SYS_Clk_SPIDiv1);

    GPIO_SetBits(DRV8353_NSCS_GPIO, DRV8353_NSCS_PIN);
    GPIO_ResetBits(DRV8353_EN_GPIO, DRV8353_EN_PIN);

    SPI0_CFG = 0U;
    SPI0_SIZE = DRV8353_SPI_BITS;
    SPI0_DIV = DRV8353_SPI_DIV_CPU_MODE | DRV8353_SPI_BAUD_DIV;
    SPI0_IE = DRV8353_SPI_IE_ALL_FLAGS;
    SPI0_CFG = DRV8353_SPI_CFG_ENABLE |
               DRV8353_SPI_CFG_MASTER |
               DRV8353_SPI_CFG_CPHA_FALL_SAMPLE;
}

void DRV8353_Enable(void)
{
    GPIO_SetBits(DRV8353_EN_GPIO, DRV8353_EN_PIN);
    SoftDelay(DRV8353_DELAY_AFTER_ENABLE);
}

void DRV8353_Disable(void)
{
    GPIO_ResetBits(DRV8353_EN_GPIO, DRV8353_EN_PIN);
}

void DRV8353_ClearFault(void)
{
    GPIO_ResetBits(DRV8353_EN_GPIO, DRV8353_EN_PIN);
    SoftDelay(DRV8353_DELAY_RESET_LOW);
    GPIO_SetBits(DRV8353_EN_GPIO, DRV8353_EN_PIN);
    SoftDelay(DRV8353_DELAY_RESET_WAKE);
    (void)DRV8353_ReadFaultStatus();
}

uint8_t DRV8353_FaultActive(void)
{
    return (GPIO_ReadInputDataBit(DRV8353_NFAULT_GPIO, DRV8353_NFAULT_PIN) == 0U) ? 1U : 0U;
}

uint16_t DRV8353_ReadReg(uint8_t addr)
{
    uint16_t rx_data;

    rx_data = drv8353_transfer16(drv8353_make_read_frame(addr));
    return (uint16_t)(rx_data & DRV8353_REG_DATA_MASK);
}

uint8_t DRV8353_WriteReg(uint8_t addr, uint16_t data)
{
    (void)drv8353_transfer16(drv8353_make_write_frame(addr, data));
    return drv8353_last_spi_status;
}

uint32_t DRV8353_ReadFaultStatus(void)
{
    uint16_t status1;
    uint16_t status2;

    status1 = DRV8353_ReadReg(DRV8353_REG_FAULT_STATUS_1);
    status2 = DRV8353_ReadReg(DRV8353_REG_VGS_STATUS_2);

    return ((uint32_t)(status1 & DRV8353_REG_DATA_MASK) |
            ((uint32_t)(status2 & DRV8353_REG_DATA_MASK) << 11));
}

uint8_t DRV8353_GetLastSpiStatus(void)
{
    return drv8353_last_spi_status;
}
