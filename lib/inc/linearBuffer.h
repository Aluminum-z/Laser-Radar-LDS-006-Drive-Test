/**
 * @file    linearBuffer.h
 * @brief   线性缓冲区
 * @author  Alzn
 * @date    2021-08-15
 */
#ifndef _LINEARBUFFER_H_
#define _LINEARBUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

/*------ Includes ---------*/
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
/*------- Define ----------*/

/*------- Typedef ---------*/
typedef enum
{
  LINEARBUF_RESET = 0,
  LINEARBUF_OK,
  LINEARBUF_ERROR,
  LINEARBUF_OVERFLOW,
} inearBuffer_status_t;

typedef struct
{
  uint8_t *p_buffer;
  uint32_t status;
  size_t size;
  size_t dataCnt;
}linearBuffer_handle_t;

/*------- Functions ------ */

inearBuffer_status_t linearBuf_init(linearBuffer_handle_t *p_hbuf, uint8_t *p_buf, size_t bufSize);
inearBuffer_status_t linearBuf_reset(linearBuffer_handle_t *p_hbuf);
inearBuffer_status_t linearBuf_write(linearBuffer_handle_t *p_hbuf, uint8_t *pData, size_t dataSize);
size_t linearBuf_getCnt(const linearBuffer_handle_t *p_hbuf);
size_t linearBuf_read(const linearBuffer_handle_t *p_hbuf, uint8_t *pData, size_t pos, size_t size);
uint8_t linearBuf_readByte(const linearBuffer_handle_t *p_hbuf, size_t pos);
bool linearBuf_isFull(const linearBuffer_handle_t *p_hbuf);

/*---- Extern variable ----*/

#ifdef __cplusplus
}
#endif

#endif /* _LINEARBUFFER_H_ */
/* END OF FILE */