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

#include "hardware_init.h"
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
#define DRV8353_DELAY_BETWEEN_WORDS     (50U)

#define DRV8353_DCR_CLR_FLT             (BIT0)
#define DRV8353_DCR_BRAKE               (BIT1)
#define DRV8353_DCR_COAST               (BIT2)
#define DRV8353_DCR_PWM_MODE_SHIFT      (5U)
#define DRV8353_DCR_PWM_MODE_MASK       (3U << DRV8353_DCR_PWM_MODE_SHIFT)
#define DRV8353_DCR_PWM_MODE_6PWM       (0U << DRV8353_DCR_PWM_MODE_SHIFT)

#define DRV8353_GATE_LOCK_SHIFT         (8U)
#define DRV8353_GATE_LOCK_UNLOCK        (3U << DRV8353_GATE_LOCK_SHIFT)
#define DRV8353_GATE_IDRIVEP_SHIFT      (4U)
#define DRV8353_GATE_IDRIVEN_SHIFT      (0U)
#define DRV8353_GATE_IDRIVEP_100MA      (2U)
#define DRV8353_GATE_IDRIVEN_200MA      (2U)

#define DRV8353_LS_CBC                  (BIT10)
#define DRV8353_LS_TDRIVE_SHIFT         (8U)
#define DRV8353_LS_TDRIVE_1000NS        (1U)

#define DRV8353_OCP_DEAD_TIME_SHIFT     (8U)
#define DRV8353_OCP_DEAD_TIME_100NS     (1U)
#define DRV8353_OCP_MODE_SHIFT          (6U)
#define DRV8353_OCP_MODE_RETRY          (1U)
#define DRV8353_OCP_DEG_SHIFT           (4U)
#define DRV8353_OCP_DEG_4US             (2U)
#define DRV8353_OCP_VDS_LVL_1V          (13U)

#define DRV8353_CSA_VREF_DIV2           (BIT9)
#define DRV8353_CSA_GAIN_SHIFT          (6U)
#define DRV8353_CSA_GAIN_20VV           (2U)
#define DRV8353_CSA_SEN_LVL_1V          (3U)

#define DRV8353_STATUS1_FAULT           (BIT10)
#define DRV8353_STATUS2_GDUV            (BIT6)

#define DRV8353_DEFAULT_DRIVER_CONTROL  (DRV8353_DCR_PWM_MODE_6PWM)
#define DRV8353_DEFAULT_GATE_HS         (DRV8353_GATE_LOCK_UNLOCK | \
                                         (DRV8353_GATE_IDRIVEP_100MA << DRV8353_GATE_IDRIVEP_SHIFT) | \
                                         (DRV8353_GATE_IDRIVEN_200MA << DRV8353_GATE_IDRIVEN_SHIFT))
#define DRV8353_DEFAULT_GATE_LS         (DRV8353_LS_CBC | \
                                         (DRV8353_LS_TDRIVE_1000NS << DRV8353_LS_TDRIVE_SHIFT) | \
                                         (DRV8353_GATE_IDRIVEP_100MA << DRV8353_GATE_IDRIVEP_SHIFT) | \
                                         (DRV8353_GATE_IDRIVEN_200MA << DRV8353_GATE_IDRIVEN_SHIFT))
#define DRV8353_DEFAULT_OCP_CONTROL     ((DRV8353_OCP_DEAD_TIME_100NS << DRV8353_OCP_DEAD_TIME_SHIFT) | \
                                         (DRV8353_OCP_MODE_RETRY << DRV8353_OCP_MODE_SHIFT) | \
                                         (DRV8353_OCP_DEG_4US << DRV8353_OCP_DEG_SHIFT) | \
                                         DRV8353_OCP_VDS_LVL_1V)
#define DRV8353_DEFAULT_CSA_CONTROL     (DRV8353_CSA_VREF_DIV2 | \
                                         (DRV8353_CSA_GAIN_20VV << DRV8353_CSA_GAIN_SHIFT) | \
                                         DRV8353_CSA_SEN_LVL_1V)
#define DRV8353_DEFAULT_DRIVER_CONFIG   (0U)

static uint8_t drv8353_last_spi_status = DRV8353_SPI_OK;

volatile drv8353_regs_t g_drv8353_regs;
volatile uint8_t g_drv8353_config_status = DRV8353_CONFIG_SPI_ERR;

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
    SoftDelay(DRV8353_DELAY_BETWEEN_WORDS);

    return (uint16_t)(SPI0_RXDATA & 0xFFFFU);
}

static uint8_t drv8353_update_driver_control(uint16_t set_bits, uint16_t clear_bits)
{
    uint16_t reg;

    reg = DRV8353_ReadReg(DRV8353_REG_DRIVER_CONTROL);
    if (DRV8353_GetLastSpiStatus() != DRV8353_SPI_OK)
        return DRV8353_CONFIG_SPI_ERR;

    reg &= (uint16_t)~clear_bits;
    reg |= set_bits;

    return DRV8353_WriteRegVerify(DRV8353_REG_DRIVER_CONTROL,
                                  reg,
                                  (uint16_t)~DRV8353_DCR_CLR_FLT & DRV8353_REG_DATA_MASK);
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

uint8_t DRV8353_ClearFaultBySpi(void)
{
    uint8_t status;

    status = DRV8353_WriteReg(DRV8353_REG_DRIVER_CONTROL,
                              DRV8353_DEFAULT_DRIVER_CONTROL | DRV8353_DCR_CLR_FLT);
    if (status != DRV8353_SPI_OK)
        return DRV8353_CONFIG_SPI_ERR;

    SoftDelay(DRV8353_DELAY_BETWEEN_WORDS);
    status = DRV8353_WriteRegVerify(DRV8353_REG_DRIVER_CONTROL,
                                    DRV8353_DEFAULT_DRIVER_CONTROL,
                                    (uint16_t)~DRV8353_DCR_CLR_FLT & DRV8353_REG_DATA_MASK);

    return status;
}

uint8_t DRV8353_ConfigureDefault(void)
{
    uint8_t status;

    status = DRV8353_ClearFaultBySpi();
    if (status != DRV8353_CONFIG_OK)
    {
        g_drv8353_config_status = status;
        return status;
    }

    status = DRV8353_WriteRegVerify(DRV8353_REG_DRIVER_CONTROL,
                                    DRV8353_DEFAULT_DRIVER_CONTROL,
                                    DRV8353_REG_DATA_MASK);
    if (status != DRV8353_CONFIG_OK)
        goto drv8353_config_exit;

    status = DRV8353_WriteRegVerify(DRV8353_REG_GATE_DRIVE_HS,
                                    DRV8353_DEFAULT_GATE_HS,
                                    DRV8353_REG_DATA_MASK);
    if (status != DRV8353_CONFIG_OK)
        goto drv8353_config_exit;

    status = DRV8353_WriteRegVerify(DRV8353_REG_GATE_DRIVE_LS,
                                    DRV8353_DEFAULT_GATE_LS,
                                    DRV8353_REG_DATA_MASK);
    if (status != DRV8353_CONFIG_OK)
        goto drv8353_config_exit;

    status = DRV8353_WriteRegVerify(DRV8353_REG_OCP_CONTROL,
                                    DRV8353_DEFAULT_OCP_CONTROL,
                                    DRV8353_REG_DATA_MASK);
    if (status != DRV8353_CONFIG_OK)
        goto drv8353_config_exit;

    status = DRV8353_WriteRegVerify(DRV8353_REG_CSA_CONTROL,
                                    DRV8353_DEFAULT_CSA_CONTROL,
                                    DRV8353_REG_DATA_MASK);
    if (status != DRV8353_CONFIG_OK)
        goto drv8353_config_exit;

    status = DRV8353_WriteRegVerify(DRV8353_REG_DRIVER_CONFIG,
                                    DRV8353_DEFAULT_DRIVER_CONFIG,
                                    DRV8353_REG_DATA_MASK);
    if (status != DRV8353_CONFIG_OK)
        goto drv8353_config_exit;

    DRV8353_ReadAllRegs(&g_drv8353_regs);
    if (((g_drv8353_regs.fault_status_1 & DRV8353_STATUS1_FAULT) != 0U) ||
        ((g_drv8353_regs.fault_status_2 & DRV8353_STATUS2_GDUV) != 0U))
    {
        status = DRV8353_CONFIG_FAULT_ACTIVE;
    }

drv8353_config_exit:
    g_drv8353_config_status = status;
    return status;
}

uint8_t DRV8353_SetCoast(uint8_t enable)
{
    return drv8353_update_driver_control((enable != 0U) ? DRV8353_DCR_COAST : 0U,
                                         (enable != 0U) ? 0U : DRV8353_DCR_COAST);
}

uint8_t DRV8353_SetBrake(uint8_t enable)
{
    return drv8353_update_driver_control((enable != 0U) ? DRV8353_DCR_BRAKE : 0U,
                                         (enable != 0U) ? 0U : DRV8353_DCR_BRAKE);
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

uint8_t DRV8353_WriteRegVerify(uint8_t addr, uint16_t data, uint16_t verify_mask)
{
    uint16_t read_back;

    if (DRV8353_WriteReg(addr, data) != DRV8353_SPI_OK)
        return DRV8353_CONFIG_SPI_ERR;

    read_back = DRV8353_ReadReg(addr);
    if (DRV8353_GetLastSpiStatus() != DRV8353_SPI_OK)
        return DRV8353_CONFIG_SPI_ERR;

    if ((read_back & verify_mask) != (data & verify_mask))
        return DRV8353_CONFIG_VERIFY_ERR;

    return DRV8353_CONFIG_OK;
}

void DRV8353_ReadAllRegs(volatile drv8353_regs_t *regs)
{
    if (regs == 0)
        return;

    regs->fault_status_1 = DRV8353_ReadReg(DRV8353_REG_FAULT_STATUS_1);
    regs->fault_status_2 = DRV8353_ReadReg(DRV8353_REG_VGS_STATUS_2);
    regs->driver_control = DRV8353_ReadReg(DRV8353_REG_DRIVER_CONTROL);
    regs->gate_drive_hs = DRV8353_ReadReg(DRV8353_REG_GATE_DRIVE_HS);
    regs->gate_drive_ls = DRV8353_ReadReg(DRV8353_REG_GATE_DRIVE_LS);
    regs->ocp_control = DRV8353_ReadReg(DRV8353_REG_OCP_CONTROL);
    regs->csa_control = DRV8353_ReadReg(DRV8353_REG_CSA_CONTROL);
    regs->driver_config = DRV8353_ReadReg(DRV8353_REG_DRIVER_CONFIG);
}

uint32_t DRV8353_ReadFaultStatus(void)
{
    uint16_t status1;
    uint16_t status2;

    status1 = DRV8353_ReadReg(DRV8353_REG_FAULT_STATUS_1);
    status2 = DRV8353_ReadReg(DRV8353_REG_VGS_STATUS_2);

    g_drv8353_regs.fault_status_1 = status1;
    g_drv8353_regs.fault_status_2 = status2;

    return ((uint32_t)(status1 & DRV8353_REG_DATA_MASK) |
            ((uint32_t)(status2 & DRV8353_REG_DATA_MASK) << 11));
}

uint8_t DRV8353_GetLastSpiStatus(void)
{
    return drv8353_last_spi_status;
}
