/**
 * @file    lcd_reg.h
 * @brief   LCD寄存器相关
 * @author  Alzn
 * @date    2021-08-08
 */
#ifndef _LCD_REG_H_
#define _LCD_REG_H_

#ifdef __cplusplus
extern "C" {
#endif

/*------ Includes ---------*/
#include "lcd_driver.h"

/*------- Define ----------*/

/*------- Typedef ---------*/

/*------- Functions ------ */
/**
 * @brief   写命令
 * @author  Alzn
 * @date    2021-08-07
 * @param   hLcd   lcd句柄
 * @param   command 16-bits 命令
 */
inline void lcd_writeCom(const lcd_handle_t *hLcd, uint16_t command) {
  *(hLcd->pWriteCom) = command;
}

/**
 * @brief   写数据
 * @author  Alzn
 * @date    2021-08-07
 * @param   hLcd   lcd句柄
 * @param   data 16-bits 数据
 */
inline void lcd_writeData(const lcd_handle_t *hLcd, uint16_t data) {
  *(hLcd->pWriteData) = data;
}

/**
 * @brief   读数据
 * @author  Alzn
 * @date    2021-08-08
 * @param   hLcd   lcd句柄
 * @return  16-bit数据
 */
inline uint16_t lcd_readData(const lcd_handle_t *hLcd){
  return *(hLcd->pWriteData);
}

HAL_StatusTypeDef lcd_initInterface(lcd_handle_t *hLcd);
void lcd_writeReg(const lcd_handle_t *hLcd, uint16_t reg, uint16_t data);
uint16_t lcd_readReg(const lcd_handle_t *hLcd, uint16_t reg);
/*---- Extern variable ----*/

#ifdef __cplusplus
}
#endif

#endif /* _LCD_REG_H_ */

/* END OF FILE */