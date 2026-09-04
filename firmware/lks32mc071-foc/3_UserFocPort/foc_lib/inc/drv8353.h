#ifndef __DRV8353_H
#define __DRV8353_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DRV8353_REG_FAULT_STATUS_1      (0x00U)
#define DRV8353_REG_VGS_STATUS_2        (0x01U)
#define DRV8353_REG_DRIVER_CONTROL      (0x02U)
#define DRV8353_REG_GATE_DRIVE_HS       (0x03U)
#define DRV8353_REG_GATE_DRIVE_LS       (0x04U)
#define DRV8353_REG_OCP_CONTROL         (0x05U)
#define DRV8353_REG_CSA_CONTROL         (0x06U)

#define DRV8353_REG_DATA_MASK           (0x07FFU)
#define DRV8353_SPI_OK                  (0U)
#define DRV8353_SPI_TIMEOUT             (1U)
#define DRV8353_SPI_ABNORMAL            (2U)

void DRV8353_Init(void);
void DRV8353_Enable(void);
void DRV8353_Disable(void);
void DRV8353_ClearFault(void);
uint8_t DRV8353_FaultActive(void);
uint16_t DRV8353_ReadReg(uint8_t addr);
uint8_t DRV8353_WriteReg(uint8_t addr, uint16_t data);
uint32_t DRV8353_ReadFaultStatus(void);
uint8_t DRV8353_GetLastSpiStatus(void);

#ifdef __cplusplus
}
#endif

#endif
