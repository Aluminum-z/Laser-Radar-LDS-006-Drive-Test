/**
 * @file    laserUnit.h
 * @brief   激光雷达驱动 For LDS-006
 * @author  Alzn
 * @date    2021-08-15
 */
#ifndef _LASERUNIT_H_
#define _LASERUNIT_H_

#ifdef __cplusplus
extern "C" {
#endif

/*------ Includes ---------*/
#include "linearBuffer.h"
#include "pid.h"
#include "pwm.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>
/*------- Define ----------*/
#define LASER_UNIT_DATA_PER_FRAME 4                                                      /*!< 每一个帧的数据个数 */
#define LASER_UNIT_FRAME_CNT_STRAT 0xA0                                                  /*!< 第一个数据帧的帧号 */
#define LASER_UNIT_FRAME_CNT_END 0xF9                                                    /*!< 最后一个数据帧的帧号 */
#define LASER_UNIT_FRAME_NUM (LASER_UNIT_FRAME_CNT_END - LASER_UNIT_FRAME_CNT_STRAT + 1) /*!< 有效的数据帧个数 */
#define LASER_UNIT_FRAME_CNT_4_SPEED_START 0xA6                                          /*!< 速度比较正常的起始数据帧号 */
#define LASER_UNIT_FRAME_CNT_4_SPEED_END 0xF3                                            /*!< 速度比较正常的终止数据帧号 */
#define LASER_UNIT_FRAME_CNT_ERR 0xFB                                                    /*!< 速度不对时的数据帧号 */
#define LASER_UNIT_DATA_PER_CIRCLE (LASER_UNIT_DATA_PER_FRAME * LASER_UNIT_FRAME_NUM)    /*!< 一圈的数据个数 */

/*------- Typedef ---------*/
#pragma pack(push, 1)
/*! 距离数据结构 */
typedef struct
{
  uint16_t distance;     /*!< 距离 */
  uint16_t reflectivity; /*!< 反射率 */
} laserUnit_distancsData_t;

/*! 数据帧结构 */
typedef struct
{
  uint8_t start;                                                    /*!< 帧的起始, = 0xFA */
  uint8_t frameCnt;                                                 /*!< 帧计数(正常: 0xA0 ~ 0xF9, 转速错误: 0xFB) */
  uint16_t rotatingSpeed;                                           /*!< 转速 */
  laserUnit_distancsData_t distanceData[LASER_UNIT_DATA_PER_FRAME]; /*!< 数据 */
  uint16_t checkSum;                                                /*!< 校验和, 等于上述数据按字节相加的和 */
} laserUnit_dataFrame_t;
#pragma pack(pop)

/*! 激光雷达驱动对象数据结构 */
typedef struct
{
  UART_HandleTypeDef *hUart; /*!< 接收数据的串口句柄 */
  pwm_handle_t hpwm;           /*!< 调整电机转速的PWM句柄 */
  pid_handle_t hpid;           /*!< 调整电机转速的PID句柄 */

  linearBuffer_handle_t hframeDataBuf;   /*!< 帧缓冲区管理句柄 */
  linearBuffer_handle_t huartRxFrameBuf; /*!< 串口接收的单个帧管理句柄 */

  laserUnit_dataFrame_t frameData[LASER_UNIT_FRAME_NUM]; /*!< 帧缓冲区 */

  bool isFrameDataOK; /* 串口接收数据缓冲区是否可用 */
  bool isRadarDataOK; /* 雷达数据是否可用 */

  laserUnit_dataFrame_t uartRxFrame; /*!< 串口接收的单个帧 */
  uint8_t uartRxData;                /*!< 串口接收单个数据的缓冲区 */

  uint16_t distance[LASER_UNIT_DATA_PER_CIRCLE];     /*!< 距离数据, 单位: 毫米 */
  uint16_t reflectivity[LASER_UNIT_DATA_PER_CIRCLE]; /*!< 反射率, 单位: 未知 */
} laserUnit_handle_t;
/*------- Functions ------ */

HAL_StatusTypeDef laserUnit_init(laserUnit_handle_t *hRradar,
                                 UART_HandleTypeDef *hUart,
                                 TIM_HandleTypeDef *hTim,
                                 uint32_t timerChannel);

void laserUnit_task(laserUnit_handle_t *hRradar);
bool laserUnit_getIsDataOK(laserUnit_handle_t *hRradar);
void laserUnit_resetDataOKFlag(laserUnit_handle_t *hRradar);

uint16_t *laserUnit_getDistanceDataPtr(laserUnit_handle_t *hRradar);
uint16_t *laserUnit_getReflectivityDataPtr(laserUnit_handle_t *hRradar);

void laserUnit_uartRxCallBack(laserUnit_handle_t *hRradar, UART_HandleTypeDef *hUart);

/*---- Extern variable ----*/

#ifdef __cplusplus
}
#endif

#endif /* _LASERUNIT_H_ */

/* END OF FILE */