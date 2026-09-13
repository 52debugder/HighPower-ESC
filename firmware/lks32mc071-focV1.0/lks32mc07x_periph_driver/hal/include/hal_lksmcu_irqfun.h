
#ifndef __HAL_LKSMCU_IRQFUN_H__
#define __HAL_LKSMCU_IRQFUN_H__

#include "../hal_lks32mc07x.h"

uint8_t HAL_HALL_IrqChange(HAL_HALL_x);
uint8_t HAL_HALL_IrqChangeFlg(HAL_HALL_x hall);
void HAL_HALL_IrqChangeEnable(HAL_HALL_x);
void HAL_HALL_IrqChangeDisable(HAL_HALL_x hall);
void HAL_HALL_IrqChangeClear(HAL_HALL_x hall);

uint8_t HAL_HALL_IrqOver(HAL_HALL_x);
uint8_t HAL_HALL_IrqOverFlg(HAL_HALL_x hall);
void HAL_HALL_IrqOverEnable(HAL_HALL_x);
void HAL_HALL_IrqOverDisable(HAL_HALL_x hall);
void HAL_HALL_IrqOverClear(HAL_HALL_x hall);

uint8_t HAL_ADC_IrqSamp1(HAL_ADC_x);
uint8_t HAL_ADC_IrqSamp1Flg(HAL_ADC_x adc);
void HAL_ADC_IrqSamp1Enable(HAL_ADC_x);
void HAL_ADC_IrqSamp1Disable(HAL_ADC_x adc);
void HAL_ADC_IrqSamp1Clear(HAL_ADC_x adc);

uint8_t HAL_ADC_IrqSamp2(HAL_ADC_x);
uint8_t HAL_ADC_IrqSamp2Flg(HAL_ADC_x adc);
void HAL_ADC_IrqSamp2Enable(HAL_ADC_x);
void HAL_ADC_IrqSamp2Disable(HAL_ADC_x adc);
void HAL_ADC_IrqSamp2Clear(HAL_ADC_x adc);

uint8_t HAL_MCPWM_IrqOverflow(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqOverflowFlg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqOverflowEnable(HAL_MCPWM_x);
void HAL_MCPWM_IrqOverflowDisable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqOverflowClear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqZeroCross(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqZeroCrossFlg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqZeroCrossEnable(HAL_MCPWM_x);
void HAL_MCPWM_IrqZeroCrossDisable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqZeroCrossClear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqFail0(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqFail0Flg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqFail0Enable(HAL_MCPWM_x);
void HAL_MCPWM_IrqFail0Disable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqFail0Clear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqFail1(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqFail1Flg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqFail1Enable(HAL_MCPWM_x);
void HAL_MCPWM_IrqFail1Disable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqFail1Clear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqFail(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqFailFlg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqFailEnable(HAL_MCPWM_x);
void HAL_MCPWM_IrqFailDisable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqFailClear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_CMP_IrqCompare(HAL_CMP_x);
uint8_t HAL_CMP_IrqCompareFlg(HAL_CMP_x cmp_x);
void HAL_CMP_IrqCompareEnable(HAL_CMP_x);
void HAL_CMP_IrqCompareDisable(HAL_CMP_x cmp_x);
void HAL_CMP_IrqCompareClear(HAL_CMP_x cmp_x);

uint8_t HAL_TIMER_IrqOverflow(HAL_TIMER_x);
uint8_t HAL_TIMER_IrqOverflowFlg(HAL_TIMER_x timer_x);
void HAL_TIMER_IrqOverflowEnable(HAL_TIMER_x);
void HAL_TIMER_IrqOverflowDisable(HAL_TIMER_x timer_x);
void HAL_TIMER_IrqOverflowClear(HAL_TIMER_x timer_x);

uint8_t HAL_TIMER_IrqCompare0(HAL_TIMER_x);
uint8_t HAL_TIMER_IrqCompare0Flg(HAL_TIMER_x timer_x);
void HAL_TIMER_IrqCompare0Enable(HAL_TIMER_x);
void HAL_TIMER_IrqCompare0Disable(HAL_TIMER_x timer_x);
void HAL_TIMER_IrqCompare0Clear(HAL_TIMER_x timer_x);

uint8_t HAL_TIMER_IrqCompare1(HAL_TIMER_x);
uint8_t HAL_TIMER_IrqCompare1Flg(HAL_TIMER_x timer_x);
void HAL_TIMER_IrqCompare1Enable(HAL_TIMER_x);
void HAL_TIMER_IrqCompare1Disable(HAL_TIMER_x timer_x);
void HAL_TIMER_IrqCompare1Clear(HAL_TIMER_x timer_x);

uint8_t HAL_UART_IrqTxDone(HAL_UART_x);
uint8_t HAL_UART_IrqTxDoneFlg(HAL_UART_x uart_x);
void HAL_UART_IrqTxDoneEnable(HAL_UART_x);
void HAL_UART_IrqTxDoneDisable(HAL_UART_x uart_x);
void HAL_UART_IrqTxDoneClear(HAL_UART_x uart_x);

uint8_t HAL_UART_IrqRxDone(HAL_UART_x);
uint8_t HAL_UART_IrqRxDoneFlg(HAL_UART_x uart_x);
void HAL_UART_IrqRxDoneEnable(HAL_UART_x);
void HAL_UART_IrqRxDoneDisable(HAL_UART_x uart_x);
void HAL_UART_IrqRxDoneClear(HAL_UART_x uart_x);

uint8_t HAL_UART_IrqStopErr(HAL_UART_x);
uint8_t HAL_UART_IrqStopErrFlg(HAL_UART_x uart_x);
void HAL_UART_IrqStopErrEnable(HAL_UART_x);
void HAL_UART_IrqStopErrDisable(HAL_UART_x uart_x);
void HAL_UART_IrqStopErrClear(HAL_UART_x uart_x);

uint8_t HAL_UART_IrqCheckErr(HAL_UART_x);
uint8_t HAL_UART_IrqCheckErrFlg(HAL_UART_x uart_x);
void HAL_UART_IrqCheckErrEnable(HAL_UART_x);
void HAL_UART_IrqCheckErrDisable(HAL_UART_x uart_x);
void HAL_UART_IrqCheckErrClear(HAL_UART_x uart_x);

uint8_t HAL_CAN_IrqRxDone(HAL_CAN_x);
uint8_t HAL_CAN_IrqRxDoneFlg(HAL_CAN_x can_x);
void HAL_CAN_IrqRxDoneEnable(HAL_CAN_x);
void HAL_CAN_IrqRxDoneDisable(HAL_CAN_x can_x);
void HAL_CAN_IrqRxDoneClear(HAL_CAN_x can_x);

uint8_t HAL_CAN_IrqTxDone(HAL_CAN_x);
uint8_t HAL_CAN_IrqTxDoneFlg(HAL_CAN_x can_x);
void HAL_CAN_IrqTxDoneEnable(HAL_CAN_x);
void HAL_CAN_IrqTxDoneDisable(HAL_CAN_x can_x);
void HAL_CAN_IrqTxDoneClear(HAL_CAN_x can_x);

uint8_t HAL_CAN_IrqAll(HAL_CAN_x);
uint8_t HAL_CAN_IrqAllFlg(HAL_CAN_x can_x);
void HAL_CAN_IrqAllEnable(HAL_CAN_x);
void HAL_CAN_IrqAllDisable(HAL_CAN_x can_x);
void HAL_CAN_IrqAllClear(HAL_CAN_x can_x);

uint8_t HAL_UART_IrqTxBufEmpty(HAL_UART_x);
uint8_t HAL_UART_IrqTxBufEmptyFlg(HAL_UART_x uart_x);
void HAL_UART_IrqTxBufEmptyEnable(HAL_UART_x);
void HAL_UART_IrqTxBufEmptyDisable(HAL_UART_x uart_x);
void HAL_UART_IrqTxBufEmptyClear(HAL_UART_x uart_x);

uint8_t HAL_UART_IrqTxOv(HAL_UART_x);
uint8_t HAL_UART_IrqTxOvFlg(HAL_UART_x uart_x);
void HAL_UART_IrqTxOvEnable(HAL_UART_x);
void HAL_UART_IrqTxOvDisable(HAL_UART_x uart_x);
void HAL_UART_IrqTxOvClear(HAL_UART_x uart_x);

uint8_t HAL_UART_IrqRxOv(HAL_UART_x);
uint8_t HAL_UART_IrqRxOvFlg(HAL_UART_x uart_x);
void HAL_UART_IrqRxOvEnable(HAL_UART_x);
void HAL_UART_IrqRxOvDisable(HAL_UART_x uart_x);
void HAL_UART_IrqRxOvClear(HAL_UART_x uart_x);

uint8_t HAL_UART_IrqLbd(HAL_UART_x);
uint8_t HAL_UART_IrqLbdFlg(HAL_UART_x uart_x);
void HAL_UART_IrqLbdEnable(HAL_UART_x);
void HAL_UART_IrqLbdDisable(HAL_UART_x uart_x);
void HAL_UART_IrqLbdClear(HAL_UART_x uart_x);

uint8_t HAL_UART_IrqIdle(HAL_UART_x);
uint8_t HAL_UART_IrqIdleFlg(HAL_UART_x uart_x);
void HAL_UART_IrqIdleEnable(HAL_UART_x);
void HAL_UART_IrqIdleDisable(HAL_UART_x uart_x);
void HAL_UART_IrqIdleClear(HAL_UART_x uart_x);

uint8_t HAL_ADC_IrqWatchdog(HAL_ADC_x);
uint8_t HAL_ADC_IrqWatchdogFlg(HAL_ADC_x adc);
void HAL_ADC_IrqWatchdogEnable(HAL_ADC_x);
void HAL_ADC_IrqWatchdogDisable(HAL_ADC_x adc);
void HAL_ADC_IrqWatchdogClear(HAL_ADC_x adc);

uint8_t HAL_ADC_IrqHardErr(HAL_ADC_x);
uint8_t HAL_ADC_IrqHardErrFlg(HAL_ADC_x adc);
void HAL_ADC_IrqHardErrEnable(HAL_ADC_x);
void HAL_ADC_IrqHardErrDisable(HAL_ADC_x adc);
void HAL_ADC_IrqHardErrClear(HAL_ADC_x adc);

uint8_t HAL_ADC_IrqSoftErr(HAL_ADC_x);
uint8_t HAL_ADC_IrqSoftErrFlg(HAL_ADC_x adc);
void HAL_ADC_IrqSoftErrEnable(HAL_ADC_x);
void HAL_ADC_IrqSoftErrDisable(HAL_ADC_x adc);
void HAL_ADC_IrqSoftErrClear(HAL_ADC_x adc);

uint8_t HAL_ADC_IrqIdleSamp(HAL_ADC_x);
uint8_t HAL_ADC_IrqIdleSampFlg(HAL_ADC_x adc);
void HAL_ADC_IrqIdleSampEnable(HAL_ADC_x);
void HAL_ADC_IrqIdleSampDisable(HAL_ADC_x adc);
void HAL_ADC_IrqIdleSampClear(HAL_ADC_x adc);

uint8_t HAL_MCPWM_IrqUpdate(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqUpdateFlg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqUpdateEnable(HAL_MCPWM_x);
void HAL_MCPWM_IrqUpdateDisable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqUpdateClear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqTmr0(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqTmr0Flg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTmr0Enable(HAL_MCPWM_x);
void HAL_MCPWM_IrqTmr0Disable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTmr0Clear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqTmr1(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqTmr1Flg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTmr1Enable(HAL_MCPWM_x);
void HAL_MCPWM_IrqTmr1Disable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTmr1Clear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqTmr2(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqTmr2Flg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTmr2Enable(HAL_MCPWM_x);
void HAL_MCPWM_IrqTmr2Disable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTmr2Clear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqTmr3(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqTmr3Flg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTmr3Enable(HAL_MCPWM_x);
void HAL_MCPWM_IrqTmr3Disable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTmr3Clear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqTH00(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqTH00Flg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH00Enable(HAL_MCPWM_x);
void HAL_MCPWM_IrqTH00Disable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH00Clear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqTH01(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqTH01Flg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH01Enable(HAL_MCPWM_x);
void HAL_MCPWM_IrqTH01Disable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH01Clear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqTH10(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqTH10Flg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH10Enable(HAL_MCPWM_x);
void HAL_MCPWM_IrqTH10Disable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH10Clear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqTH11(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqTH11Flg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH11Enable(HAL_MCPWM_x);
void HAL_MCPWM_IrqTH11Disable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH11Clear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqTH20(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqTH20Flg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH20Enable(HAL_MCPWM_x);
void HAL_MCPWM_IrqTH20Disable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH20Clear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqTH21(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqTH21Flg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH21Enable(HAL_MCPWM_x);
void HAL_MCPWM_IrqTH21Disable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH21Clear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqTH30(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqTH30Flg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH30Enable(HAL_MCPWM_x);
void HAL_MCPWM_IrqTH30Disable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH30Clear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqTH31(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqTH31Flg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH31Enable(HAL_MCPWM_x);
void HAL_MCPWM_IrqTH31Disable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH31Clear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqTH40(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqTH40Flg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH40Enable(HAL_MCPWM_x);
void HAL_MCPWM_IrqTH40Disable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH40Clear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqTH41(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqTH41Flg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH41Enable(HAL_MCPWM_x);
void HAL_MCPWM_IrqTH41Disable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH41Clear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqTH50(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqTH50Flg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH50Enable(HAL_MCPWM_x);
void HAL_MCPWM_IrqTH50Disable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH50Clear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_MCPWM_IrqTH51(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqTH51Flg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH51Enable(HAL_MCPWM_x);
void HAL_MCPWM_IrqTH51Disable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqTH51Clear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_I2C_IrqDone(HAL_I2C_x);
uint8_t HAL_I2C_IrqDoneFlg(HAL_I2C_x i2c_x);
void HAL_I2C_IrqDoneEnable(HAL_I2C_x);
void HAL_I2C_IrqDoneDisable(HAL_I2C_x i2c_x);
void HAL_I2C_IrqDoneClear(HAL_I2C_x i2c_x);

uint8_t HAL_I2C_IrqBusErr(HAL_I2C_x);
uint8_t HAL_I2C_IrqBusErrFlg(HAL_I2C_x i2c_x);
void HAL_I2C_IrqBusErrEnable(HAL_I2C_x);
void HAL_I2C_IrqBusErrDisable(HAL_I2C_x i2c_x);
void HAL_I2C_IrqBusErrClear(HAL_I2C_x i2c_x);

uint8_t HAL_I2C_IrqStop(HAL_I2C_x);
uint8_t HAL_I2C_IrqStopFlg(HAL_I2C_x i2c_x);
void HAL_I2C_IrqStopEnable(HAL_I2C_x);
void HAL_I2C_IrqStopDisable(HAL_I2C_x i2c_x);
void HAL_I2C_IrqStopClear(HAL_I2C_x i2c_x);

uint8_t HAL_SPI_IrqDone(HAL_SPI_x);
uint8_t HAL_SPI_IrqDoneFlg(HAL_SPI_x spi_x);
void HAL_SPI_IrqDoneEnable(HAL_SPI_x);
void HAL_SPI_IrqDoneDisable(HAL_SPI_x spi_x);
void HAL_SPI_IrqDoneClear(HAL_SPI_x spi_x);

uint8_t HAL_SPI_IrqErr(HAL_SPI_x);
uint8_t HAL_SPI_IrqErrFlg(HAL_SPI_x spi_x);
void HAL_SPI_IrqErrEnable(HAL_SPI_x);
void HAL_SPI_IrqErrDisable(HAL_SPI_x spi_x);
void HAL_SPI_IrqErrClear(HAL_SPI_x spi_x);

uint8_t HAL_SPI_IrqOverflow(HAL_SPI_x);
uint8_t HAL_SPI_IrqOverflowFlg(HAL_SPI_x spi_x);
void HAL_SPI_IrqOverflowEnable(HAL_SPI_x);
void HAL_SPI_IrqOverflowDisable(HAL_SPI_x spi_x);
void HAL_SPI_IrqOverflowClear(HAL_SPI_x spi_x);

uint8_t HAL_DMA_IrqDone(HAL_DMA_x);
uint8_t HAL_DMA_IrqDoneFlg(HAL_DMA_x dma_x);
void HAL_DMA_IrqDoneEnable(HAL_DMA_x);
void HAL_DMA_IrqDoneDisable(HAL_DMA_x dma_x);
void HAL_DMA_IrqDoneClear(HAL_DMA_x dma_x);

uint8_t HAL_GPIO_Irq(uint8_t);
uint8_t HAL_GPIO_IrqFlg(uint8_t line);
void HAL_GPIO_IrqEnable(uint8_t);
void HAL_GPIO_IrqDisable(uint8_t line);
void HAL_GPIO_IrqClear(uint8_t line);

uint8_t HAL_SW_Irq(uint8_t);
uint8_t HAL_SW_IrqFlg(uint8_t x);
void HAL_SW_IrqEnable(uint8_t);
void HAL_SW_IrqDisable(uint8_t x);
void HAL_SW_IrqClear(uint8_t x);
void HAL_SW_IrqTrig(uint8_t);

// 硬件不支持的中断(空实现)

uint8_t HAL_ADC_IrqSamp3(HAL_ADC_x);
uint8_t HAL_ADC_IrqSamp3Flg(HAL_ADC_x adc);
void HAL_ADC_IrqSamp3Enable(HAL_ADC_x);
void HAL_ADC_IrqSamp3Disable(HAL_ADC_x adc);
void HAL_ADC_IrqSamp3Clear(HAL_ADC_x adc);

uint8_t HAL_ADC_IrqSamp4(HAL_ADC_x);
uint8_t HAL_ADC_IrqSamp4Flg(HAL_ADC_x adc);
void HAL_ADC_IrqSamp4Enable(HAL_ADC_x);
void HAL_ADC_IrqSamp4Disable(HAL_ADC_x adc);
void HAL_ADC_IrqSamp4Clear(HAL_ADC_x adc);

uint8_t HAL_ADC_IrqWatchdog1(HAL_ADC_x);
uint8_t HAL_ADC_IrqWatchdog1Flg(HAL_ADC_x adc);
void HAL_ADC_IrqWatchdog1Enable(HAL_ADC_x);
void HAL_ADC_IrqWatchdog1Disable(HAL_ADC_x adc);
void HAL_ADC_IrqWatchdog1Clear(HAL_ADC_x adc);

uint8_t HAL_DMA_IrqErr(HAL_DMA_x);
uint8_t HAL_DMA_IrqErrFlg(HAL_DMA_x dma_x);
void HAL_DMA_IrqErrEnable(HAL_DMA_x);
void HAL_DMA_IrqErrDisable(HAL_DMA_x dma_x);
void HAL_DMA_IrqErrClear(HAL_DMA_x dma_x);

void HAL_DMA_IrqErrTrig(HAL_DMA_x);

void HAL_DMA_IrqDoneTrig(HAL_DMA_x);

void HAL_GPIO_IrqTrig(uint8_t);

uint8_t HAL_MCPWM_IrqShort(HAL_MCPWM_x);
uint8_t HAL_MCPWM_IrqShortFlg(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqShortEnable(HAL_MCPWM_x);
void HAL_MCPWM_IrqShortDisable(HAL_MCPWM_x mcpwmx);
void HAL_MCPWM_IrqShortClear(HAL_MCPWM_x mcpwmx);

uint8_t HAL_UART_IrqAbd(HAL_UART_x);
uint8_t HAL_UART_IrqAbdFlg(HAL_UART_x uart_x);
void HAL_UART_IrqAbdEnable(HAL_UART_x);
void HAL_UART_IrqAbdDisable(HAL_UART_x uart_x);
void HAL_UART_IrqAbdClear(HAL_UART_x uart_x);

#endif
