#include "../include/hal_lksmcu_irq.h"
#include "../hal_lks32mc07x.h"
#include "lks32mc07x_user_manual.h"
#include "../include/hal_lksmcu_reg.h"
#include "../include/hal_lks32mc07x_reg.h"

/**
 * @brief 重置中断(等效于关闭中断)
 * @param irq 中断编号
 */
void HAL_IRQ_Reset(void)
{
    HAL_IRQ_Disable();
}

/**
 * @brief 使能全局中断
 * @param irq 中断编号
 */
void HAL_IRQ_Enable(void)
{
    __enable_irq();
}

/**
 * @brief 关闭全局中断
 * @param irq 中断编号
 */
void HAL_IRQ_Disable(void)
{
    __disable_irq();
}

/**
 * @brief 使能某个模块的中断
 * @param module 模块编号
 * @param priority 中断优先级
 */
void HAL_IRQ_ModuleEnable(HAL_IRQ_MODULE_x module, uint8_t priority)
{
    NVIC_SetPriority((IRQn_Type)module, priority);
    NVIC_EnableIRQ((IRQn_Type)module);
}

/**
 * @brief 关闭某个模块的中断
 * @param module 模块编号
 */
void HAL_IRQ_ModuleDisable(HAL_IRQ_MODULE_x module)
{
    NVIC_DisableIRQ((IRQn_Type)module);
}
/**
 * @brief 清除某个模块的中断
 * @param module 模块编号
 */
void HAL_IRQ_ModuleClear(HAL_IRQ_MODULE_x module)
{
    NVIC_ClearPendingIRQ((IRQn_Type)module);
}
