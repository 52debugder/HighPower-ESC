#include "VOFA.h"

// void Print1_Motor_To_VOFA(float data, uint8_t length)
// {
//     char uart_buf[20];
//     sprintf(uart_buf, "%.6f\n", data);
//     UART_SendData(UART0, (uint32_t)uart_buf);
//     UART_SendData(UART0, (uint32_t)"\n");
// }

// void Print2_Motor_To_VOFA(float data1, float data2)
// {

//     char uart_buf[256]; // 足够长以容纳三个数据
//     // 使用逗号分隔，结尾加换行，VOFA 的 FireWater 协议才能正确识别成一帧
//     int len = sprintf(uart_buf, "%.3f,%.3f\n", data1, data2);
    
//     // 一次性发送，不要分段发送逗号和换行
//     HAL_UART_Transmit(&huart10, (uint8_t *)uart_buf, len, 10);
// }

// void Print3_Motor_To_VOFA(float data1, float data2, float data3)
// {
//     char uart_buf[256]; // 足够长以容纳三个数据
//     // 使用逗号分隔，结尾加换行，VOFA 的 FireWater 协议才能正确识别成一帧
//     int len = sprintf(uart_buf, "%.3f,%.3f,%.3f\n", data1, data2, data3);
    
//     // 一次性发送，不要分段发送逗号和换行
//     HAL_UART_Transmit(&huart10, (uint8_t *)uart_buf, len, 10);
// }

// void Print4_Motor_To_VOFA(float data1, float data2, float data3, float data4)
// {
//     char uart_buf[256]; // 足够长以容纳三个数据
//     // 使用逗号分隔，结尾加换行，VOFA 的 FireWater 协议才能正确识别成一帧
//     int len = sprintf(uart_buf, "%.3f,%.3f,%.3f,%.3f\n", data1, data2, data3, data4);
    
//     // 一次性发送，不要分段发送逗号和换行
//     HAL_UART_Transmit(&huart10, (uint8_t *)uart_buf, len, 10);
// }

// void Print5_Motor_To_VOFA(float data1, float data2, float data3, float data4, float data5)
// {
//     char uart_buf[256 * 4]; // 足够长以容纳三个数据
//     // 使用逗号分隔，结尾加换行，VOFA 的 FireWater 协议才能正确识别成一帧
//     int len = sprintf(uart_buf, "%.3f,%.3f,%.3f,%.3f, %.3f,%.3f\n", data1, data2, data3, data4, data5);
    
//     // 一次性发送，不要分段发送逗号和换行
//     HAL_UART_Transmit(&huart10, (uint8_t *)uart_buf, len, 10);
// }

// void Print8_Motor_To_VOFA(float d1, float d2, float d3, float d4,
//                           float d5, float d6, float d7, float d8)
// {
//     char uart_buf[256];
//     int len = snprintf(uart_buf, sizeof(uart_buf),
//                        "%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f\n",
//                        d1, d2, d3, d4, d5, d6, d7, d8);
//     HAL_UART_Transmit(&huart10, (uint8_t *)uart_buf, len, 10);
// }

