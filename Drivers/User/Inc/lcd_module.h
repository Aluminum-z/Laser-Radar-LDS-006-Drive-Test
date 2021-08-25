/**
 * @file    lcd_module.h
 * @brief   LCD模块管理
 * @author  Alzn
 * @date    2021-08-08
 */
#ifndef _LCD_MODULE_H_
#define _LCD_MODULE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*------ Includes ---------*/
#include "stm32f4xx_hal.h"
#include "lcd_driver.h"
/*------- Define ----------*/

/*------- Typedef ---------*/


/*------- Functions ------ */
HAL_StatusTypeDef lcd_initChip(lcd_handle_t *hLcd);
void lcd_setRange(const lcd_handle_t *hLcd, uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2);
/*---- Extern variable ----*/

#ifdef __cplusplus
}
#endif

#endif /* _LCD_MODULE_H_ */
/* END OF FILE */