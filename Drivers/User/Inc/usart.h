/**
 * @file    usart.h
 * @brief   串口库
 * @author  Alzn
 * @date    2021-08-07
 */
#ifndef _USART_H_
#define _USART_H_

#ifdef __cplusplus
extern "C" {
#endif

/*------ Includes ---------*/
#include "stm32f4xx_hal.h"
/*------- Define ----------*/

/*------- Typedef ---------*/

/*------- Functions ------ */
HAL_StatusTypeDef usart_sendStr(UART_HandleTypeDef *hUart, const char *pStr);
/*---- Extern variable ----*/

#ifdef __cplusplus
}
#endif

#endif /* _USART_H_ */
/* END OF FILE */