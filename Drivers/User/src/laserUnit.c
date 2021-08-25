/**
 * @file    laserUnit.c
 * @brief   激光雷达驱动 For LDS-006
 * @author  Alzn
 * @date    2021-08-15
 */

/*------ Includes ---------*/
#include "laserUnit.h"
#include <string.h>
/*------- Define ----------*/

/*------- Typedef ---------*/

/*------- Variable --------*/

/*------ Functions --------*/

/**
 * @brief   初始化雷达
 * @author  Alzn
 * @date    2021-08-15
 * @param   p_hrader      雷达句柄
 * @param   hUart       接受数据的串口句柄
 * @param   hTim        控制电机的定时器句柄
 * @param   timerChannel  控制电机的定时器输出通道
 */
HAL_StatusTypeDef laserUnit_init(laserUnit_handle_t *hRradar,
                                 UART_HandleTypeDef *hUart,
                                 TIM_HandleTypeDef *hTim,
                                 uint32_t timerChannel) {
  if ((NULL == hRradar) || (NULL == hUart) || (NULL == hTim)) {
    return HAL_ERROR;
  }
  uint8_t startCommand = 0x24;
  hRradar->hUart = hUart;
  hRradar->isFrameDataOK = false;
  hRradar->isRadarDataOK = false;
  memset((void *)hRradar->frameData, 0, sizeof(hRradar->frameData));
  memset((void *)&(hRradar->uartRxFrame), 0, sizeof(hRradar->uartRxFrame));
  memset((void *)hRradar->distance, 0, sizeof(hRradar->distance));
  memset((void *)hRradar->reflectivity, 0, sizeof(hRradar->reflectivity));
  if (HAL_OK != pwm_init(&hRradar->hpwm, hTim, timerChannel, 0.0f)) {
    return HAL_ERROR;
  }
  if (LINEARBUF_OK != linearBuf_init(&hRradar->hframeDataBuf, (uint8_t *)hRradar->frameData, sizeof(hRradar->frameData))) {
    return HAL_ERROR;
  }
  if (LINEARBUF_OK != linearBuf_init(&hRradar->huartRxFrameBuf, (uint8_t *)&hRradar->uartRxFrame, sizeof(hRradar->uartRxFrame))) {
    return HAL_ERROR;
  }
  pid_init_t pid_initStruct;
  pid_initStruct.kp = 0.000005f;
  pid_initStruct.ki = 0.0000001f;
  pid_initStruct.kd = 0.0000001f;
  pid_initStruct.cfgMeaVal = 21500.0f;
  pid_initStruct.ctrlVal = 0.5f;
  pid_initStruct.ctrlValMax = 0.9f;
  pid_initStruct.ctrlValMin = 0.3f;
  pid_init(&(hRradar->hpid), &pid_initStruct);

  pwm_setDutyCycle(&hRradar->hpwm, 0.50);
  pwm_setOutputEnable(&hRradar->hpwm, CFGSTA_ENABLE);

  HAL_UART_Receive_IT(hRradar->hUart, &hRradar->uartRxData, 1);
  HAL_UART_Transmit(hRradar->hUart, &startCommand, 1, HAL_MAX_DELAY);

  return HAL_OK;
}

/**
 * @brief   处理串口接收的数据的任务
 * @author  Alzn
 * @date    2021-08-18
 * @param   p_hrader      雷达句柄
 * @note    本函数需要放在main函数中不断执行
 */
void laserUnit_task(laserUnit_handle_t *hRradar) {
  if (NULL == hRradar) {
    return;
  }
  if ((false == hRradar->isFrameDataOK) || (true == hRradar->isRadarDataOK)) {
    return;
  }
  uint32_t dataIndex = 0;
  for (uint32_t frameIndex = 0; frameIndex < LASER_UNIT_FRAME_NUM; frameIndex++) {
    laserUnit_dataFrame_t *p_frame = &hRradar->frameData[frameIndex];
    for (uint32_t frameDataIndex = 0; frameDataIndex < LASER_UNIT_DATA_PER_FRAME; frameDataIndex++) {
      hRradar->distance[dataIndex] = p_frame->distanceData[frameDataIndex].distance;
      hRradar->reflectivity[dataIndex] = p_frame->distanceData[frameDataIndex].reflectivity;
      dataIndex++;
    }
  }
  hRradar->isFrameDataOK = false;
  hRradar->isRadarDataOK = true;
}

/**
 * @brief   获取雷达数据是否可用
 * @author  Alzn
 * @date    2021-08-19
 * @param   p_hrader      雷达句柄
 * @retval  true: 数据可用, false: 数据无效
 */
bool laserUnit_getIsDataOK(laserUnit_handle_t *hRradar) {
  if (NULL == hRradar) {
    return false;
  }
  return hRradar->isRadarDataOK;
}

/**
 * @brief   复位数据可用标志，进行下一次读数
 * @author  Alzn
 * @date    2021-08-19
 * @param   p_hrader      雷达句柄
 */
void laserUnit_resetDataOKFlag(laserUnit_handle_t *hRradar) {
  if (NULL == hRradar) {
    return;
  }
  hRradar->isRadarDataOK = false;
}

/**
 * @brief   获取距离数据指针
 * @author  Alzn
 * @date    2021-08-19
 * @param   p_hrader      雷达句柄
 * @return  距离数据指针, 数据个数为 LASER_UNIT_DATA_PER_CIRCLE
 */
uint16_t *laserUnit_getDistanceDataPtr(laserUnit_handle_t *hRradar) {
  if (NULL == hRradar) {
    return NULL;
  }
  return hRradar->distance;
}

/**
 * @brief   获取反射率相关的数据指针
 * @author  Alzn
 * @date    2021-08-19
 * @param   p_hrader      雷达句柄
 * @return  反射率相关的数据指针, 数据个数为 LASER_UNIT_DATA_PER_CIRCLE
 */
uint16_t *laserUnit_getReflectivityDataPtr(laserUnit_handle_t *hRradar){
  if (NULL == hRradar) {
    return NULL;
  }
  return hRradar->reflectivity;
}

/**
 * @brief   激光雷达用的串口接收回调函数
 * @author  Alzn
 * @date    2021-08-15
 * @param   p_hrader      雷达句柄
 * @param   hUart       串口句柄
 */
void laserUnit_uartRxCallBack(laserUnit_handle_t *hRradar, UART_HandleTypeDef *hUart) {
  if ((NULL == hRradar) || (NULL == hUart)) {
    return;
  }
  if (hUart != hRradar->hUart) {
    return;
  }
  if ((hRradar->uartRxData == 0xFA) && (linearBuf_getCnt(&hRradar->huartRxFrameBuf) == 0)) {
    linearBuf_write(&hRradar->huartRxFrameBuf, &hRradar->uartRxData, 1);
  } else if ((linearBuf_getCnt(&hRradar->huartRxFrameBuf) > 0)) {
    linearBuf_write(&hRradar->huartRxFrameBuf, &hRradar->uartRxData, 1);
    if (linearBuf_isFull(&hRradar->huartRxFrameBuf)) {
      uint16_t frameCnt = hRradar->uartRxFrame.frameCnt;
      if ((frameCnt == LASER_UNIT_FRAME_CNT_ERR) //跳过速度不对的地方
          || ((frameCnt >= LASER_UNIT_FRAME_CNT_4_SPEED_START)
              && (frameCnt <= LASER_UNIT_FRAME_CNT_4_SPEED_END))) {
        pid_setMeaVal(&hRradar->hpid, (float)hRradar->uartRxFrame.rotatingSpeed);
        pwm_setDutyCycle(&hRradar->hpwm, pid_getCtrlValue(&hRradar->hpid));
      }
      if ((false == hRradar->isFrameDataOK)
          && (frameCnt >= LASER_UNIT_FRAME_CNT_STRAT)
          && (frameCnt <= LASER_UNIT_FRAME_CNT_END)) {
        memcpy(&hRradar->frameData[frameCnt - LASER_UNIT_FRAME_CNT_STRAT], &hRradar->uartRxFrame, sizeof(hRradar->uartRxFrame));
        if (LASER_UNIT_FRAME_CNT_END == frameCnt) {
          hRradar->isFrameDataOK = true;
        }
      }
      linearBuf_reset(&hRradar->huartRxFrameBuf);
    }
  }
  HAL_UART_Receive_IT(hRradar->hUart, &hRradar->uartRxData, 1);
}

/* END OF FILE */