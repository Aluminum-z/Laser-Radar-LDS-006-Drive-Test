/**
 * @file    user_main.h
 * @brief   自定义main函数
 * @author  Alzn
 * @date    2021-08-07
 */
#ifndef _USER_MAIN_H_
#define _USER_MAIN_H_

#ifdef __cplusplus
extern "C" {
#endif

/*------ Includes ---------*/
#include "stm32f4xx_hal.h"
/*------- Define ----------*/

/*------- Typedef ---------*/

/*------- Functions ------ */
void userMain(void);

/*---- Extern variable ----*/
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

extern SRAM_HandleTypeDef hsram1;
extern TIM_HandleTypeDef htim9;

#ifdef __cplusplus
}
#endif

#endif /* _USER_MAIN_H_ */
/* END OF FILE */