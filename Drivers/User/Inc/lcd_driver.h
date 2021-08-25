/**
 * @file    lcd_driver.h
 * @brief   液晶驱动
 * @author  Alzn
 * @date    2021-08-07
 */
#ifndef _LCD_DRIVER_H_
#define _LCD_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

/*------ Includes ---------*/
#include "stm32f4xx_hal.h"
#include "lcd_font.h"
/*------- Define ----------*/

/*------- Typedef ---------*/
#define LCD_SIZE_X 400
#define LCD_SIZE_Y 240

typedef enum
{
  LCD_CHIP_SELECT_NE1 = 0,
  LCD_CHIP_SELECT_NE2,
  LCD_CHIP_SELECT_NE3,
  LCD_CHIP_SELECT_NE4,
  LCD_CHIP_SELECT_MAX,
} lcd_chipSelect_t;

typedef enum
{
  LCD_REG_SELECT_A0 = 0,
  LCD_REG_SELECT_A1,
  LCD_REG_SELECT_A2,
  LCD_REG_SELECT_A3,
  LCD_REG_SELECT_A4,
  LCD_REG_SELECT_A5,
  LCD_REG_SELECT_A6,
  LCD_REG_SELECT_A7,
  LCD_REG_SELECT_A8,
  LCD_REG_SELECT_A9,
  LCD_REG_SELECT_A10,
  LCD_REG_SELECT_A11,
  LCD_REG_SELECT_A12,
  LCD_REG_SELECT_A13,
  LCD_REG_SELECT_A14,
  LCD_REG_SELECT_A15,
  LCD_REG_SELECT_A16,
  LCD_REG_SELECT_A17,
  LCD_REG_SELECT_A18,
  LCD_REG_SELECT_A19,
  LCD_REG_SELECT_A20,
  LCD_REG_SELECT_A21,
  LCD_REG_SELECT_A22,
  LCD_REG_SELECT_A23,
  LCD_REG_SELECT_A24,
  LCD_REG_SELECT_A25,
  LCD_REG_SELECT_MAX,
} lcd_regSelect_t;

typedef enum
{
  LCD_CHIP_UNKNOWN = 0,
  LCD_CHIP_R61509V,
  LCD_CHIP_ST7793,
  LCD_CHIP_NT35510,
} lcd_chip_t;

typedef enum
{
  LCD_STATE_RESET = 0,
  LCD_STATE_READY,
  LCD_STATE_BUSY,
  LCD_STATE_ERROR,
} lcd_state_t;

typedef struct {
  uint32_t chip;       /*!< 液晶控制芯片 @ref lcd_chip_t */
  uint32_t sizeX;     /*!< x方向上的像素数 */
  uint32_t sizeY;     /*!< y方向上的像素数 */
  uint32_t chipSelect; /*!< 片选, 枚举值 @ref lcd_chipSelect_t */
  uint32_t regSelect;  /*!< 寄存器选择(地址线) @ref lcd_regSelect_t */
} lcd_initPara_t;

typedef struct {
  lcd_initPara_t initPara; /*!< 参数 */
  uint16_t *pWriteCom; /*!< 写入命令的数据地址 */
  uint16_t *pWriteData;    /*!< 写入数据的数据地址 */
  HAL_LockTypeDef lock;    /*!< 锁 */
  lcd_state_t state;
} lcd_handle_t;

/*------- Functions ------ */

HAL_StatusTypeDef lcd_init(lcd_handle_t *hLcd);
void lcd_clear(const lcd_handle_t *hLcd, uint16_t color);
void lcd_drawBlock(const lcd_handle_t *hLcd, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void lcd_drawPoint(const lcd_handle_t *hLcd, uint16_t x, uint16_t y, uint16_t color);
void lcd_drawLine(const lcd_handle_t *hLcd, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void lcd_drawBitPicture(const lcd_handle_t *hLcd, uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *p_pic, uint16_t color, uint16_t backColor);
void lcd_drawString(const lcd_handle_t *hLcd, uint16_t x, uint16_t y, const char *pStr, const lcd_font_t *pFont, uint16_t color, uint16_t backColor);
/*---- Extern variable ----*/

#ifdef __cplusplus
}
#endif

#endif /* _LCD_DRIVER_H_ */

/* END OF FILE */