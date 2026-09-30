#include "VOFA.h"
#include <stdio.h>
#include <stdlib.h>

// 发送字符串，逐字节写 UART1
static void UART_SendString(const char *str)
{
    while (*str != '\0')
    {
        UART_SendData(UART1, (uint32_t)(uint8_t)(*str));
        str++;
    }
}

void Print1_Motor_To_VOFA(float data, uint8_t length)
{
    char uart_buf[32];
    int32_t i = (int32_t)(data * 1000000.0f);   // 保留 6 位小数
    (void)length;

    int len = snprintf(uart_buf, sizeof(uart_buf),
                       "%ld.%06ld\n",
                       (long)(i / 1000000), (long)abs(i % 1000000));
    UART_SendString(uart_buf);
}

void Print2_Motor_To_VOFA(float data1, float data2)
{
    char uart_buf[64];
    int32_t i1 = (int32_t)(data1 * 1000.0f);
    int32_t i2 = (int32_t)(data2 * 1000.0f);

    int len = snprintf(uart_buf, sizeof(uart_buf),
                       "%ld.%03ld,%ld.%03ld\n",
                       (long)(i1 / 1000), (long)abs(i1 % 1000),
                       (long)(i2 / 1000), (long)abs(i2 % 1000));
    UART_SendString(uart_buf);
}

void Print3_Motor_To_VOFA(float data1, float data2, float data3)
{
    char uart_buf[96];
    int32_t i1 = (int32_t)(data1 * 1000.0f);
    int32_t i2 = (int32_t)(data2 * 1000.0f);
    int32_t i3 = (int32_t)(data3 * 1000.0f);

    int len = snprintf(uart_buf, sizeof(uart_buf),
                       "%ld.%03ld,%ld.%03ld,%ld.%03ld\n",
                       (long)(i1 / 1000), (long)abs(i1 % 1000),
                       (long)(i2 / 1000), (long)abs(i2 % 1000),
                       (long)(i3 / 1000), (long)abs(i3 % 1000));
    UART_SendString(uart_buf);
}

void Print4_Motor_To_VOFA(float data1, float data2, float data3, float data4)
{
    char uart_buf[128];
    int32_t i1 = (int32_t)(data1 * 1000.0f);
    int32_t i2 = (int32_t)(data2 * 1000.0f);
    int32_t i3 = (int32_t)(data3 * 1000.0f);
    int32_t i4 = (int32_t)(data4 * 1000.0f);

    int len = snprintf(uart_buf, sizeof(uart_buf),
                       "%ld.%03ld,%ld.%03ld,%ld.%03ld,%ld.%03ld\n",
                       (long)(i1 / 1000), (long)abs(i1 % 1000),
                       (long)(i2 / 1000), (long)abs(i2 % 1000),
                       (long)(i3 / 1000), (long)abs(i3 % 1000),
                       (long)(i4 / 1000), (long)abs(i4 % 1000));
    UART_SendString(uart_buf);
}

void Print5_Motor_To_VOFA(float data1, float data2, float data3, float data4, float data5)
{
    char uart_buf[160];
    int32_t i1 = (int32_t)(data1 * 1000.0f);
    int32_t i2 = (int32_t)(data2 * 1000.0f);
    int32_t i3 = (int32_t)(data3 * 1000.0f);
    int32_t i4 = (int32_t)(data4 * 1000.0f);
    int32_t i5 = (int32_t)(data5 * 1000.0f);

    int len = snprintf(uart_buf, sizeof(uart_buf),
                       "%ld.%03ld,%ld.%03ld,%ld.%03ld,%ld.%03ld,%ld.%03ld\n",
                       (long)(i1 / 1000), (long)abs(i1 % 1000),
                       (long)(i2 / 1000), (long)abs(i2 % 1000),
                       (long)(i3 / 1000), (long)abs(i3 % 1000),
                       (long)(i4 / 1000), (long)abs(i4 % 1000),
                       (long)(i5 / 1000), (long)abs(i5 % 1000));
    UART_SendString(uart_buf);
}

void Print8_Motor_To_VOFA(float d1, float d2, float d3, float d4,
                          float d5, float d6, float d7, float d8)
{
    char uart_buf[256];
    int32_t i1 = (int32_t)(d1 * 1000.0f);
    int32_t i2 = (int32_t)(d2 * 1000.0f);
    int32_t i3 = (int32_t)(d3 * 1000.0f);
    int32_t i4 = (int32_t)(d4 * 1000.0f);
    int32_t i5 = (int32_t)(d5 * 1000.0f);
    int32_t i6 = (int32_t)(d6 * 1000.0f);
    int32_t i7 = (int32_t)(d7 * 1000.0f);
    int32_t i8 = (int32_t)(d8 * 1000.0f);

    int len = snprintf(uart_buf, sizeof(uart_buf),
                       "%ld.%03ld,%ld.%03ld,%ld.%03ld,%ld.%03ld,"
                       "%ld.%03ld,%ld.%03ld,%ld.%03ld,%ld.%03ld\n",
                       (long)(i1 / 1000), (long)abs(i1 % 1000),
                       (long)(i2 / 1000), (long)abs(i2 % 1000),
                       (long)(i3 / 1000), (long)abs(i3 % 1000),
                       (long)(i4 / 1000), (long)abs(i4 % 1000),
                       (long)(i5 / 1000), (long)abs(i5 % 1000),
                       (long)(i6 / 1000), (long)abs(i6 % 1000),
                       (long)(i7 / 1000), (long)abs(i7 % 1000),
                       (long)(i8 / 1000), (long)abs(i8 % 1000));
    UART_SendString(uart_buf);
}