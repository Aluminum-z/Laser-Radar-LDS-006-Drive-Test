/**
 * @file    usart.c
 * @brief   串口库
 * @author  Alzn
 * @date    2021-08-07
 */

/*------ Includes ---------*/
#include "usart.h"
#include "stm32f4xx_hal_uart.h"
#include <string.h>
/*------- Define ----------*/

/*------- Typedef ---------*/

/*------- Variable --------*/

/*------ Functions --------*/

/**
 * @brief  发送字符串
 * @author Alzn
 * @date   2021-08-07
 * @param  hUart  串口句柄
 * @param  pStr    字符串指针
 * @retval HAL status
 */
HAL_StatusTypeDef usart_sendStr(UART_HandleTypeDef *hUart, const char *pStr) {
  if ((NULL == hUart) || (NULL == pStr)) {
    return HAL_ERROR;
  }
  size_t length = strlen(pStr);
  return HAL_UART_Transmit(hUart, (uint8_t *)pStr, length, HAL_MAX_DELAY);
}

/* END OF FILE */