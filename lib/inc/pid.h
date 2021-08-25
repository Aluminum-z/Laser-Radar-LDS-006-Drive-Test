/**
 * @file    pid.h
 * @brief   PID 控制
 * @author  Alzn
 * @date    2021-08-15
 */
#ifndef _PID_H_
#define _PID_H_

#ifdef __cplusplus
extern "C" {
#endif

/*------ Includes ---------*/
#include <stddef.h>
#include <stdint.h>
/*------- Define ----------*/

/*------- Typedef ---------*/
typedef struct {
  float kp;         /*!< 误差系数 */
  float ki;         /*!< 积分系数 */
  float kd;         /*!< 差分系数 */
  float cfgMeaVal;  /*!< 期望的测量值 */
  float ctrlVal;    /*!< 初始控制值 */
  float ctrlValMin; /*!< 最小的控制值 */
  float ctrlValMax; /*!< 最大的控制值 */
} pid_init_t;

typedef struct {
  float kp;
  float ki;
  float kd;
  float i;
  float preErr;
  float cfgMeaVal;
  float meaVal;
  float ctrlVal;
  float ctrlValMin;
  float ctrlValMax;
} pid_handle_t;

/*------- Functions ------ */

void pid_init(pid_handle_t *p_hpid, pid_init_t *p_init);
float pid_setMeaVal(pid_handle_t *p_hpid, float meaVal);
float pid_getCtrlValue(pid_handle_t *p_hpid);

/*---- Extern variable ----*/

#ifdef __cplusplus
}
#endif

#endif /* _PID_H_ */

/* END OF FILE */