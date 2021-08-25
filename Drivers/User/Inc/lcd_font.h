/**
 * @file    lcd_font.h
 * @brief   字库
 * @author  Alzn
 * @date    2021-08-08
 */
#ifndef _LCD_FONT_H_
#define _LCD_FONT_H_

#ifdef __cplusplus
extern "C" {
#endif

/*------ Includes ---------*/
#include "stdint.h"
/*------- Define ----------*/

/*------- Typedef ---------*/
typedef struct 
{
  uint16_t width;
  uint16_t height;
  uint16_t bytePerChar;
  uint16_t byte;
  uint16_t charStart;
  uint16_t charEnd;
  const uint8_t *pData;
}lcd_font_t;

/*---- Extern variable ----*/
extern const lcd_font_t lcd_font_consolas_16_8x14;

#ifdef __cplusplus
}
#endif

#endif /* _LCD_FONT_H_ */
/* END OF FILE */