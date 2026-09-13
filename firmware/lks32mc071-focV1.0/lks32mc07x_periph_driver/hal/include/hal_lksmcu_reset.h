#ifndef __HAL_LKSMCU_RESET_H__
#define __HAL_LKSMCU_RESET_H__
void HAL_RESET_ResetCore(void);     // 复位内核
void HAL_RESET_ResetRegister(void); // 寄存器复位
void HAL_RESET_ResetGlobal(void);   // 全局复位(先复位寄存器再复位内核)
#endif
