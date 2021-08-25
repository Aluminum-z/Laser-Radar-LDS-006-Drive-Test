/**
 * @file    pwm.c
 * @brief   PWM控制相关
 * @author  Alzn
 * @date    2021-08-15
 */

/*------ Includes ---------*/
#include "pwm.h"
/*------- Define ----------*/

/*------- Typedef ---------*/

/*------- Variable --------*/

/*------ Functions --------*/

/**
 * @brief   初始化PWM对象
 * @author  Alzn
 * @date    2021-08-15
 * @param   hPwm    PWM句柄
 * @param   hTim    定时器句柄
 * @param   channel   PWM对应的定时器通道
 * @param   dutyCycle 初始化的输出占空比
 * @retval  HAL Status @ref HAL_StatusTypeDef
 */
HAL_StatusTypeDef pwm_init(pwm_handle_t *hPwm, TIM_HandleTypeDef *hTim, uint32_t channel, float dutyCycle) {
  if ((NULL == hPwm) || (NULL == hTim))
  {
    return HAL_ERROR;
  }
  hPwm->hTim = hTim;
  hPwm->channel = channel;
  hPwm->dutyCycle = dutyCycle;
  if (HAL_OK != pwm_setOutputEnable(hPwm, CFGSTA_DISABLE))
  {
    return HAL_ERROR;
  }
  return pwm_setDutyCycle(hPwm, dutyCycle);
}

/**
 * @brief   设置输出开关
 * @author  Alzn
 * @date    2021-08-15
 * @param   hPwm        PWM句柄
 * @param   isEnable      开关状态 @ref cfgStatus_t
 */
HAL_StatusTypeDef pwm_setOutputEnable(pwm_handle_t *hPwm, uint32_t isEnable){
  if ((NULL == hPwm) || (NULL == hPwm->hTim))
  {
    return HAL_ERROR;
  }
  HAL_StatusTypeDef setRev = HAL_OK;
  if (CFGSTA_ENABLE == isEnable)
  {
    setRev = HAL_TIM_PWM_Start(hPwm->hTim, hPwm->channel);
  }
  else
  {
    setRev = HAL_TIM_PWM_Stop(hPwm->hTim, hPwm->channel);
  }
  if (HAL_OK == setRev)
  {
    hPwm->isEnable = isEnable;
  }
  return setRev;
}

/**
 * @brief   设置输出的占空比
 * @author  Alzn
 * @date    2021-08-15
 * @param   hPwm      PWM句柄
 * @param   dutyCycle   占空比
 */
HAL_StatusTypeDef pwm_setDutyCycle(pwm_handle_t *hPwm, float dutyCycle){
  if ((NULL == hPwm) || (NULL == hPwm->hTim))
  {
    return HAL_ERROR;
  }
  if (dutyCycle > 1.0f)
  {
    dutyCycle = 1.0f;
  }
  if (dutyCycle < 0.0f)
  {
    dutyCycle = 0.0f;
  }
  uint32_t compareVal = (float)__HAL_TIM_GET_AUTORELOAD(hPwm->hTim) * dutyCycle;
  __HAL_TIM_SET_COMPARE(hPwm->hTim, hPwm->channel, compareVal);
  return HAL_OK;
}

/* END OF FILE */