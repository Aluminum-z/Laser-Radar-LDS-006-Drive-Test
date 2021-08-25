/**
 * @file    linearBuffer.c
 * @brief   线性缓冲区
 * @author  Alzn
 * @date    2021-08-15
 */

/*------ Includes ---------*/
#include "linearBuffer.h"
#include <string.h>
/*------- Define ----------*/

/*------- Typedef ---------*/

/*------- Variable --------*/

/*------ Functions --------*/

/**
 * @brief   初始化缓冲区
 * @author  Alzn
 * @date    2021-08-15
 * @param   p_hbuf    缓冲区句柄
 * @param   p_buf     缓冲区数据区指针
 * @param   bufSize   缓冲区大小
 * @retval  初始化状态, @ref inearBuffer_status_t
 */
inearBuffer_status_t linearBuf_init(linearBuffer_handle_t *p_hbuf, uint8_t *p_buf, size_t bufSize){
  if ((NULL == p_hbuf) || (NULL == p_buf) || (0 == bufSize))
  {
    return LINEARBUF_ERROR;
  }
  p_hbuf->p_buffer = p_buf;
  p_hbuf->size = bufSize;
  p_hbuf->dataCnt = 0;
  p_hbuf->status = LINEARBUF_OK;
  return LINEARBUF_OK;
}

/**
 * @brief   复位缓冲区
 * @author  Alzn
 * @date    2021-08-15
 * @param   p_hbuf  缓冲区句柄
 * @retval  复位状态, @ref inearBuffer_status_t
 */
inearBuffer_status_t linearBuf_reset(linearBuffer_handle_t *p_hbuf){
  if (NULL == p_hbuf)
  {
    return LINEARBUF_ERROR;
  }
  if (NULL == p_hbuf->p_buffer)
  {
    p_hbuf->status = LINEARBUF_ERROR;
    return LINEARBUF_ERROR;
  }
  p_hbuf->dataCnt = 0;
  p_hbuf->status = LINEARBUF_OK;
  return LINEARBUF_OK;
}

/**
 * @brief   写缓冲区
 * @author  Alzn
 * @date    2021-08-15
 * @param   p_hbuf    缓冲区句柄
 * @param   pData    数据指针
 * @param   dataSize  数据大小
 * @retval  写入状态, @ref inearBuffer_status_t
 */
inearBuffer_status_t linearBuf_write(linearBuffer_handle_t *p_hbuf, uint8_t *pData, size_t dataSize){
  if ((NULL == p_hbuf) || (NULL == pData))
  {
    return LINEARBUF_ERROR;
  }
  if (LINEARBUF_OK != p_hbuf->status)
  {
    return p_hbuf->status;
  }
  size_t writeCnt = p_hbuf->size - p_hbuf->dataCnt;
  if (dataSize < writeCnt)
  {
    writeCnt = dataSize;
  }
  memcpy((void *)&(p_hbuf->p_buffer[p_hbuf->dataCnt]), pData, writeCnt);
  p_hbuf->dataCnt += writeCnt;
  if (dataSize > writeCnt)
  {
    p_hbuf->status = LINEARBUF_OVERFLOW;
  }
  return p_hbuf->status;
}

/**
 * @brief   获取缓冲区内的数大小
 * @author  Alzn
 * @date    2021-08-15
 * @param   p_hbuf  缓冲区句柄
 * @retval  数据大小
 */
size_t linearBuf_getCnt(const linearBuffer_handle_t *p_hbuf){
  if (NULL == p_hbuf)
  {
    return 0;
  }
  return p_hbuf->dataCnt;
}

/**
 * @brief   读取缓冲区数据
 * @author  Alzn
 * @date    2021-08-15
 * @param   p_hbuf    缓冲区句柄
 * @param   pData    数据指针
 * @param   pos       读取的位置
 * @param   size      数据大小
 * @retval  写入状态, @ref inearBuffer_status_t
 */
size_t linearBuf_read(const linearBuffer_handle_t *p_hbuf, uint8_t *pData, size_t pos, size_t size){
  if ((NULL == p_hbuf) || (NULL == pData) || (NULL == p_hbuf->p_buffer))
  {
    return 0;
  }
  if ((LINEARBUF_OK != p_hbuf->status) && (LINEARBUF_OVERFLOW != p_hbuf->status))
  {
    return 0;
  }
  if (pos >= p_hbuf->dataCnt)
  {
    return 0;
  }
  size_t readCnt = p_hbuf->dataCnt - pos;
  if (size < readCnt)
  {
    readCnt = size;
  }
  memcpy((void *)pData, (void *)&(p_hbuf->p_buffer[pos]), readCnt);
  return readCnt;
}

/**
 * @brief   读取一个字节的数据
 * @author  Alzn
 * @date    2021-08-15
 * @param   p_hbuf    缓冲区句柄
 * @param   pos       读取的位置
 * @retval  数据
 */
uint8_t linearBuf_readByte(const linearBuffer_handle_t *p_hbuf, size_t pos){
  if ((NULL == p_hbuf) || (NULL == p_hbuf->p_buffer))
  {
    return 0;
  }
  if ((LINEARBUF_OK != p_hbuf->status) && (LINEARBUF_OVERFLOW != p_hbuf->status))
  {
    return 0;
  }
  if (pos >= p_hbuf->dataCnt)
  {
    return 0;
  }
  return p_hbuf->p_buffer[pos];
}

/**
 * @brief   检查缓冲区是否已经满
 * @author  Alzn
 * @date    2021-08-15
 * @param   p_hbuf    缓冲区句柄
 * @retval  true=已满, false = 未满
 */
bool linearBuf_isFull(const linearBuffer_handle_t *p_hbuf){
  if (NULL == p_hbuf)
  {
    return false;
  }
  if (p_hbuf->dataCnt >= p_hbuf->size)
  {
    return true;
  }
  return false;
}

/* END OF FILE */