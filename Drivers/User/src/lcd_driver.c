/**
 * @file    lcd_driver.c
 * @brief   液晶驱动
 * @author  Alzn
 * @date    2021-08-07
 */

/*------ Includes ---------*/
#include "lcd_driver.h"
#include "lcd_module.h"
#include "lcd_reg.h"
/*------- Define ----------*/

/*------- Typedef ---------*/

/*------- Variable --------*/

/*------ Functions --------*/
/**
 * @brief   初始化液晶屏
 * @author  Alzn
 * @date    2021-08-07
 * @param   hLcd   lcd句柄
 * @retval  HAL Status
 */
HAL_StatusTypeDef lcd_init(lcd_handle_t *hLcd) {
  if (NULL == hLcd) {
    return HAL_ERROR;
  }
  if (LCD_STATE_RESET == hLcd->state) {
    hLcd->lock = HAL_UNLOCKED;
  }
  if (HAL_OK != lcd_initInterface(hLcd)) {
    return HAL_ERROR;
  }
  if (HAL_OK != lcd_initChip(hLcd)) {
    return HAL_ERROR;
  }
  lcd_clear(hLcd, 0x0000);
  return HAL_OK;
}

/**
 * @brief   清屏
 * @author  Alzn
 * @date    2021-08-07
 * @param   hLcd   lcd句柄
 * @param   color 清屏的颜色
 */
void lcd_clear(const lcd_handle_t *hLcd, uint16_t color) {
  uint32_t pixelSum = hLcd->initPara.sizeX * hLcd->initPara.sizeY;
  lcd_setRange(hLcd, 0, hLcd->initPara.sizeX - 1, 0, hLcd->initPara.sizeY - 1);
  for (uint32_t i = 0; i < pixelSum; i++) {
    lcd_writeData(hLcd, color);
  }
}

/**
 * @brief   绘制方块块
 * @author  Alzn
 * @date    2021-08-07
 * @param   hLcd   lcd句柄
 * @param   x       x坐标
 * @param   y       y坐标
 * @param   width   宽度
 * @param   height  高度
 */
void lcd_drawBlock(const lcd_handle_t *hLcd, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
  uint32_t pixelSum = width * height;
  lcd_setRange(hLcd, x, x + width - 1, y, y + height - 1);
  for (uint32_t i = 0; i < pixelSum; i++) {
    lcd_writeData(hLcd, color);
  }
}

/**
 * @brief   绘制一个点
 * @author  Alzn
 * @date    2021-08-07
 * @param   hLcd   lcd句柄
 * @param   x     x坐标
 * @param   y     y坐标
 * @param   color 颜色
 */
void lcd_drawPoint(const lcd_handle_t *hLcd, uint16_t x, uint16_t y, uint16_t color) {

  lcd_setRange(hLcd, x, x, y, y);
  lcd_writeData(hLcd, color);
}

/**
 * @brief   绘制线(支持斜线)
 * @author  Alzn
 * @date    2021-08-07
 * @param   hLcd   lcd句柄
 * @param   x1 线起点x坐标
 * @param   y1 线起点y坐标
 * @param   x2 线终点x坐标
 * @param   y2 线终点y坐标
 * @param   color 线颜色
 */
void lcd_drawLine(const lcd_handle_t *hLcd, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
  int32_t x, y, d, incX, incY, dAddLess, dAddBigger;
  int32_t roopNum, roopStepX, roopStepY, stepX, stepY;
  incX = x2 - x1;
  incY = y2 - y1;
  if (NULL == hLcd) {
    return;
  }
  if (incX < 0) {
    x1 += incX;
    x2 -= incX;
    y1 += incY;
    y2 -= incY;
    incX = -incX;
    incY = -incY;
  }
  if (incY < 0) {
    incY = -incY;
  }
  if (incX > incY) {
    d = -incX;
    dAddBigger = 2 * (incY - incX);
    dAddLess = 2 * incY;
    roopNum = incX;
    roopStepX = 1;
    roopStepY = 0;
    stepX = 0;
    stepY = 1;
  } else {
    d = -incY;
    dAddBigger = 2 * (incX - incY);
    dAddLess = 2 * incX;
    roopNum = incY;
    roopStepX = 0;
    roopStepY = 1;
    stepX = 1;
    stepY = 0;
  }
  if (y2 < y1) {
    roopStepY *= -1;
    stepY *= -1;
  }
  x = x1;
  y = y1;
  for (int32_t i = 0; i <= roopNum; i++) {
    lcd_drawPoint(hLcd, x, y, color);
    if (d < 0) {
      d += dAddLess;
    } else {
      d += dAddBigger;
      x += stepX;
      y += stepY;
    }
    x += roopStepX;
    y += roopStepY;
  }
}

/**
 * @brief   绘制二进制定义的图像
 * @author  Alzn
 * @date    2021-08-08
 * @note    图像先从左往右8bit为一组扫描，然后从上往下
 * @param   hLcd   lcd句柄
 * @param   x       x坐标(左上)
 * @param   y       y坐标
 * @param   width   宽度
 * @param   height  高度
 * @param   p_pic   二进制图像地址
 * @param   color   前景图像
 * @param   bk_colo 背景图像
 */
void lcd_drawBitPicture(const lcd_handle_t *hLcd, uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *p_pic, uint16_t color, uint16_t backColor) {
  const uint16_t dataBits = 8;
  uint16_t drawY;
  const uint8_t *pWriteData = p_pic;
  uint8_t mask = 0x80;
  uint16_t drawBits;
  uint16_t xRoop = width / dataBits;
  if (width % dataBits != 0)
  {
    xRoop += 1;
  }
  if ((NULL == hLcd) || (NULL == p_pic)) {
    return;
  }
  for (uint16_t iY = 0; iY < height; iY++)
  {
    drawY = y + iY;
    lcd_setRange(hLcd, x, x + width - 1, drawY, drawY);
    for (uint16_t iX = 0; iX < xRoop; iX++)
    {
      drawBits = width - iX * dataBits;
      if (drawBits > dataBits) {
        drawBits = dataBits;
      }
      mask = 0x80;
      for (uint16_t bit = 0; bit < drawBits; bit++) {
        lcd_writeData(hLcd, ((*pWriteData & mask) == mask) ? color : backColor);
        mask = mask >> 1;
      }
      pWriteData++;
    }
  }
}

/**
 * @brief   绘制字符串
 * @author  Alzn
 * @date    2021-08-08
 * @param   hLcd     lcd句柄
 * @param   x         x坐标, (左上)
 * @param   y         y坐标
 * @param   pStr     文本指针
 * @param   pFont    字体指针
 * @param   color     文本颜色
 * @param   backColor  背景颜色
 */
void lcd_drawString(const lcd_handle_t *hLcd, uint16_t x, uint16_t y, const char *pStr, const lcd_font_t *pFont, uint16_t color, uint16_t backColor) {
  if ((NULL == hLcd) || (NULL == pStr) || (NULL == pFont)) {
    return;
  }
  uint16_t drawX = x;
  for (const char *p_char = pStr; *p_char != '\0'; p_char++)
  {
    if ((*p_char >= pFont->charStart) && (*p_char <= pFont->charEnd))
    {
      lcd_drawBitPicture(hLcd, drawX, y, pFont->width, pFont->height, pFont->pData + (*p_char - pFont->charStart) * pFont->bytePerChar, color, backColor);
    }
    else
    {
      lcd_drawBlock(hLcd, drawX, y, pFont->width, pFont->height, backColor);
    }
    drawX += pFont->width;
  }
}

/* END OF FILE */