/**
 * @file    pwm.h
 * @brief   PWM控制
 * @author  Alzn
 * @date    2021-08-15
 */
#ifndef _PWM_H_
#define _PWM_H_

#ifdef __cplusplus
extern "C" {
#endif

/*------ Includes ---------*/
#include "baseType.h"
#include "stm32f4xx_hal.h"
/*------- Define ----------*/

/*------- Typedef ---------*/
/*! PWM控制的对象结构 */
typedef struct
{
  TIM_HandleTypeDef *hTim; /*!< PWM定时器 */
  uint32_t channel;        /*!< PWM对应的定时器通道 */
  uint32_t isEnable;       /*!<  输出是否使能 */
  float dutyCycle;         /*!< PWM占空比 */
} pwm_handle_t;

/*------- Functions ------ */

HAL_StatusTypeDef pwm_init(pwm_handle_t *hPwm, TIM_HandleTypeDef *hTim, uint32_t channel, float dutyCycle);
HAL_StatusTypeDef pwm_setOutputEnable(pwm_handle_t *hPwm, uint32_t isEnable);
HAL_StatusTypeDef pwm_setDutyCycle(pwm_handle_t *hPwm, float dutyCycle);

/*---- Extern variable ----*/

#ifdef __cplusplus
}
#endif

#endif /* _PWM_H_ */

/* END OF FILE */