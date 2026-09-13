
#include "../include/hal_lksmcu_reset.h"
#include "../hal_lks32mc07x.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"
/**
 * @brief 复位内核
 */
void HAL_RESET_ResetCore()
{
    NVIC_SystemReset();
}

/**
 * @brief 寄存器复位
 */
void HAL_RESET_ResetRegister()
{
    // 系统寄存器解锁
    HAL_REG_SYS_UNLOCK();
    HAL_REG_SET(SYS_SFT_RST, 0xffff);
    HAL_REG_RESET(SYS_SFT_RST, 0);
    // 系统寄存器上锁
    HAL_REG_SYS_LOCK();
}

/**
 * @brief 全局复位(先复位寄存器再复位内核)
 */
void HAL_RESET_ResetGlobal()
{
    HAL_RESET_ResetRegister();
    NVIC_SystemReset();
}
