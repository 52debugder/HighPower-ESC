#include "../include/hal_lksmcu_init.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lksmcu_irq.h"
#include "../include/hal_lks32mc07x_reg.h"
void HAL_INIT_SysInit(void)
{
    HAL_CLK_SetMcuFreq(HAL_CLK_FREQ_RC_96MHZ);
    HAL_FLASH_EnableCache(HAL_FLASH_0);
}

void HAL_INIT_PowerReady(HAL_INIT_POWER_x powerx)
{
    __disable_irq();
    switch (powerx)
    {
        case HAL_INIT_POWER_3_3V: // 等待3.3V电源就绪，判断阈值为2.8V
            if (HAL_REG_READ_BIT_MASK_POS(SYS_AFE_INFO, SYS_AFE_INFO_Version) > 3)
            {
                // 设置掉电检测电压
                HAL_REG_SYS_UNLOCK();
                HAL_REG_WRITE_BIT_MASK_POS(HAL_SYS[0]->REG6, SYS_AFE_REG6_PVDSEL, 3);
                HAL_REG_RESET(HAL_SYS[0]->REG6, (SYS_AFE_REG6_VSR_PDT_BIT | SYS_AFE_REG6_PD_PDT_BIT));
                HAL_REG_SYS_LOCK();
                // 等待电源就绪
                while (HAL_REG_READ_BIT(HAL_SYS[0]->DBG, SYS_AFE_DBG_PWR_WEAK_BIT))
                {
                    __NOP();
                }
            }
            else
            {
                // 芯片版本小于等于3，阈值电压最低3.25V
                // 考虑到3.3VLDO的精度 3.235 到 3.365以及mcu本身的离散性
                // 不支持3.3V的电压稳定判断，这里直接跳过
            }
            break;
        case HAL_INIT_POWER_5V: // 等待5.0V电源就绪，判断阈值为4.0V
            // 设置掉电检测电压
            HAL_REG_SYS_UNLOCK();
            HAL_REG_WRITE_BIT_MASK_POS(HAL_SYS[0]->REG6, SYS_AFE_REG6_PVDSEL, 0);
            HAL_REG_RESET(HAL_SYS[0]->REG6, (SYS_AFE_REG6_VSR_PDT_BIT | SYS_AFE_REG6_PD_PDT_BIT));
            HAL_REG_SYS_LOCK();
            // 等待电源就绪
            while (HAL_REG_READ_BIT(HAL_SYS[0]->DBG, SYS_AFE_DBG_PWR_WEAK_BIT))
            {
                __NOP();
            }
            break;
    }
    // 清除中断标志位
    HAL_IRQ_ModuleClear(HAL_IRQ_MODULE_INIT0);
}
