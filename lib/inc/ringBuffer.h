/**
 * @file    ringBuffer.h
 * @brief   环形缓冲区库
 * @author  Alzn
 * @date    2021-08-09
 */
#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

/*------ Includes ---------*/
#include <stddef.h>
#include <stdint.h>
/*------- Define ----------*/

/*------- Typedef ---------*/
typedef enum
{
  RINGBUF_RESET = 0,
  RINGBUF_OK,
  RINGBUF_ERROR,
  RINGBUF_OVERFLOW,
} ringBuf_status_t;

typedef struct
{
  uint8_t *p_buffer;
  uint32_t status;
  size_t size;
  size_t writeIndex;
  size_t readIndex;
} ringBuffer_handle_t;

/*------- Functions ------ */
ringBuf_status_t ringBuf_init(ringBuffer_handle_t *p_hbuf, uint8_t *pDataOfBuf, size_t bufSize);
ringBuf_status_t ringBuf_reset(ringBuffer_handle_t *p_hbuf);
ringBuf_status_t ringBuf_write(ringBuffer_handle_t *p_hbuf, uint8_t *pData, size_t size);
size_t ringBuf_getCnt(const ringBuffer_handle_t *p_hbuf);
size_t ringBuf_read(ringBuffer_handle_t *p_hbuf, uint8_t *pData, size_t size);

/*---- Extern variable ----*/

#ifdef __cplusplus
}
#endif

#endif /* _RINGBUFFER_H_ */
       /* END OF FILE */