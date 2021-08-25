/**
 * @file    lcd_reg.c
 * @brief   LCD寄存器相关
 * @author  Alzn
 * @date    2021-08-08
 */

/*------ Includes ---------*/
#include "lcd_reg.h"
/*------- Define ----------*/

/*------- Typedef ---------*/

/*------- Variable --------*/

/*------ Functions --------*/
extern inline void lcd_writeCom(const lcd_handle_t *hLcd, uint16_t command);
extern inline void lcd_writeData(const lcd_handle_t *hLcd, uint16_t data);
extern inline uint16_t lcd_readData(const lcd_handle_t *hLcd);

/**
 * @brief   初始化读写接口
 * @author  Alzn
 * @date    2021-08-08
 */
HAL_StatusTypeDef lcd_initInterface(lcd_handle_t *hLcd){
  const uint32_t bank1_baseAddress = 0x60000000;
  const uint32_t haddr_baseBitsPos = 26;
  if (NULL == hLcd)
  {
    return HAL_ERROR;
  }
  if (hLcd->initPara.chipSelect >= LCD_CHIP_SELECT_MAX)
  {
    return HAL_ERROR;
  }
  hLcd->pWriteCom = (uint16_t *)(bank1_baseAddress + (hLcd->initPara.chipSelect << haddr_baseBitsPos));
  if (hLcd->initPara.regSelect >= LCD_REG_SELECT_MAX)
  {
    return HAL_ERROR;
  }
  hLcd->pWriteData = hLcd->pWriteCom;
  hLcd->pWriteData = (uint16_t *)((uint32_t)(hLcd->pWriteData) | 0x01 << (hLcd->initPara.regSelect + 1));   //16bit数据线的地址需要左移1位
  return HAL_OK;
}

/**
 * @brief   写寄存器
 * @author  Alzn
 * @date    2021-08-07
 * @param   hLcd   lcd句柄
 * @param   reg   16-bits 寄存器地址
 * @param   data  16-bits 数据
 */
void lcd_writeReg(const lcd_handle_t *hLcd, uint16_t reg, uint16_t data) {
  lcd_writeCom(hLcd, reg);
  lcd_writeData(hLcd, data);
}

/**
 * @brief   读寄存器
 * @author  Alzn
 * @date    2021-08-08
 * @param   hLcd   lcd句柄
 * @param   reg     16-bits 寄存器地址
 * @return  16-bit  数据
 */
uint16_t lcd_readReg(const lcd_handle_t *hLcd, uint16_t reg){
  lcd_writeCom(hLcd, reg);
  return lcd_readData(hLcd);
}
/* END OF FILE */