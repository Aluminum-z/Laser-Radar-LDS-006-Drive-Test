/**
 * @file    pid.c
 * @brief   PID 控制
 * @author  Alzn
 * @date    2021-08-15
 */

/*------ Includes ---------*/
#include "pid.h"
/*------- Define ----------*/

/*------- Typedef ---------*/

/*------- Variable --------*/

/*------ Functions --------*/

/**
 * @brief   初始化PID
 * @author  Alzn
 * @date    2021-08-15
 * @param   p_hpid      PID句柄
 * @param   p_init      初始化参数
 */
void pid_init(pid_handle_t *p_hpid, pid_init_t *p_init){
  if (NULL == p_hpid)
  {
    return;
  }
  p_hpid->kp = p_init->kp;
  p_hpid->ki = p_init->ki;
  p_hpid->kd = p_init->kd;
  p_hpid->i = 0.0f;
  p_hpid->preErr = 0.0f;
  p_hpid->cfgMeaVal = p_init->cfgMeaVal;
  p_hpid->meaVal = p_init->cfgMeaVal;
  p_hpid->ctrlVal = p_init->ctrlVal;
  p_hpid->ctrlValMin = p_init->ctrlValMin;
  p_hpid->ctrlValMax = p_init->ctrlValMax;
}

/**
 * @brief   设置当前的测量值
 * @author  Alzn
 * @date    2021-08-15
 * @param   p_hpid      PID句柄
 * @param   meaVal      当前的测量值
 * @retval  控制值
 */
float pid_setMeaVal(pid_handle_t *p_hpid, float meaVal){
  if (NULL == p_hpid)
  {
    return 0.0f;
  }
  float err = p_hpid->cfgMeaVal - meaVal;
  float d = (err - p_hpid->preErr);
  p_hpid->preErr = err;
  p_hpid->i += err;
  p_hpid->ctrlVal = (p_hpid->kp) * err + (p_hpid->ki) * (p_hpid->i) + (p_hpid->kd) * d;
  if (p_hpid->ctrlVal < p_hpid->ctrlValMin)
  {
    p_hpid->ctrlVal = p_hpid->ctrlValMin;
  }
  if (p_hpid->ctrlVal > p_hpid->ctrlValMax)
  {
    p_hpid->ctrlVal = p_hpid->ctrlValMax;
  }
  p_hpid->meaVal = meaVal;
  return p_hpid->ctrlVal;
}

/**
 * @brief   获取控制值
 * @author  Alzn
 * @date    2021-08-15
 * @param   p_hpid      PID句柄
 * @retval  控制值
 */
float pid_getCtrlValue(pid_handle_t *p_hpid){
  if (NULL == p_hpid)
  {
    return 0.0f;
  }
  return p_hpid->ctrlVal;
}

/* END OF FILE */