/**
 * @file    ringBuffer.c
 * @brief   环形缓冲区库
 * @author  Alzn
 * @date    2021-08-09
 */

/*------ Includes ---------*/
#include "ringBuffer.h"
/*------- Define ----------*/

/*------- Typedef ---------*/

/*------- Variable --------*/

/*------ Functions --------*/

/**
 * @brief   初始化缓冲区
 * @author  Alzn
 * @date    2021-08-09
 * @param   p_hbuf         缓冲区句柄
 * @param   pDataOfBuf   缓冲区的数据指针, 用于存放缓冲区的数据
 * @param   bufSize       缓冲区大小, 最小不小于2个字节
 * @retval  Ring buffer status @ref ringBuf_status_t
 */
ringBuf_status_t ringBuf_init(ringBuffer_handle_t *p_hbuf, uint8_t *pDataOfBuf, size_t bufSize) {
  if ((NULL == p_hbuf) || (NULL == pDataOfBuf) || (bufSize < 2)) {
    return RINGBUF_ERROR;
  }
  p_hbuf->p_buffer = pDataOfBuf;
  p_hbuf->size = bufSize;
  p_hbuf->writeIndex = 1;
  p_hbuf->readIndex = 0;
  p_hbuf->status = RINGBUF_OK;
  return RINGBUF_OK;
}

/**
 * @brief   复位缓冲区
 * @author  Alzn
 * @date    2021-08-09
 * @param   p_hbuf   缓冲区句柄
 * @retval  Ring buffer status @ref ringBuf_status_t
 */
ringBuf_status_t ringBuf_reset(ringBuffer_handle_t *p_hbuf) {
  if ((NULL == p_hbuf) || (NULL == p_hbuf->p_buffer)) {
    return RINGBUF_ERROR;
  }
  p_hbuf->writeIndex = 1;
  p_hbuf->readIndex = 0;
  p_hbuf->status = RINGBUF_OK;
  return RINGBUF_OK;
}

/**
 * @brief   写数据
 * @author  Alzn
 * @date    2021-08-09
 * @param   p_hbuf   缓冲区句柄
 * @param   pData  数据指针
 * @param   size    数据个数
 * @retval  Ring buffer status @ref ringBuf_status_t
 */
ringBuf_status_t ringBuf_write(ringBuffer_handle_t *p_hbuf, uint8_t *pData, size_t size) {
  if ((NULL == p_hbuf) || (NULL == pData)) {
    return RINGBUF_ERROR;
  }
  if (RINGBUF_OK != p_hbuf->status) {
    return p_hbuf->status;
  }
  size_t writeIndex = p_hbuf->writeIndex;
  size_t readIndex = p_hbuf->readIndex;
  for (size_t i = 0; i < size; i++) {
    if (((writeIndex + 1) % p_hbuf->size) == readIndex) {
      p_hbuf->status = RINGBUF_OVERFLOW;
      p_hbuf->writeIndex = writeIndex;
      return RINGBUF_OVERFLOW;
    }
    p_hbuf->p_buffer[writeIndex] = pData[i];
    writeIndex++;
    writeIndex = writeIndex % p_hbuf->size;
  }
  p_hbuf->writeIndex = writeIndex;
  return RINGBUF_OK;
}

/**
 * @brief   获取缓冲区中可读取的数据个数
 * @author  Alzn
 * @date    2021-08-09
 * @param   p_hbuf   缓冲区句柄
 * @retval  可读取的数据个数
 */
size_t ringBuf_getCnt(const ringBuffer_handle_t *p_hbuf) {
  if (NULL == p_hbuf) {
    return 0;
  }
  size_t rev = 0;
  size_t writeIndex = p_hbuf->writeIndex;
  size_t readIndex = p_hbuf->readIndex;
  if ((RINGBUF_OK != p_hbuf->status) && (RINGBUF_OVERFLOW != p_hbuf->status)) {
    return 0;
  }
  if (writeIndex > readIndex) {
    rev = writeIndex - readIndex - 1;
  } else {
    rev = p_hbuf->size - readIndex + writeIndex - 1;
  }
  return rev;
}

/**
 * @brief   读数据
 * @author  Alzn
 * @date    2021-08-09
 * @param   p_hbuf   缓冲区句柄
 * @param   pData  数据指针
 * @param   size    需要读取的数据个数
 * @retval  实际读取的数据个数
 */
size_t ringBuf_read(ringBuffer_handle_t *p_hbuf, uint8_t *pData, size_t size) {
  if ((NULL == p_hbuf) || (NULL == pData)) {
    return 0;
  }
  size_t cnt = 0;
  size_t writeIndex = p_hbuf->writeIndex;
  size_t readIndex = p_hbuf->readIndex;
  if ((RINGBUF_OK != p_hbuf->status) && (RINGBUF_OVERFLOW != p_hbuf->status)) {
    return 0;
  }
  for (cnt = 0; cnt < size; cnt++) {
    if (((readIndex + 1) % p_hbuf->size) == writeIndex) {
      p_hbuf->readIndex = readIndex;
      return cnt;
    }
    readIndex++;
    readIndex = readIndex % p_hbuf->size;
    pData[cnt] = p_hbuf->p_buffer[readIndex];
  }
  p_hbuf->readIndex = readIndex;
  return cnt;
}

/* END OF FILE */