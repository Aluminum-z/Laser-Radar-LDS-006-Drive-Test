/**
 * @file    lcd_module.c
 * @brief   LCD初始化序列管理
 * @author  Alzn
 * @date    2021-08-08
 */

/*------ Includes ---------*/
#include "lcd_module.h"
#include "lcd_driver.h"
#include "lcd_reg.h"
/* TEST CODE START */
#include "user_main.h"
#include "usart.h"
#include <stdio.h>
/* TEST CODE END */
/*------- Define ----------*/

/*------- Typedef ---------*/

/*------- Variable --------*/

/*------ Functions --------*/

void lcd_setRange_ST7763_R61509V(const lcd_handle_t *hLcd, uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2);
void lcd_setRange_NT35510(const lcd_handle_t *hLcd, uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2);

HAL_StatusTypeDef lcd_chipInit_ST7763(lcd_handle_t *hLcd);
HAL_StatusTypeDef lcd_chipInit_R61509V(lcd_handle_t *hLcd);
HAL_StatusTypeDef lcd_chipInit_NT35510(lcd_handle_t *hLcd);

/**
 * @brief   初始化芯片
 * @author  Alzn
 * @date    2021-08-08
 * @param   hLcd   LCD句柄
 * @retval  HAL Status
 */
HAL_StatusTypeDef lcd_initChip(lcd_handle_t *hLcd) {
  HAL_StatusTypeDef rev = HAL_OK;
  uint16_t chipID = lcd_readReg(hLcd, 0x0000);
  if (LCD_CHIP_UNKNOWN == hLcd->initPara.chip) {
    switch (chipID) {
      case 0x7793:
        hLcd->initPara.chip = LCD_CHIP_ST7793;
        break;

      case 0xB509:
        hLcd->initPara.chip = LCD_CHIP_R61509V;
        break;

      default:
        hLcd->initPara.chip = LCD_CHIP_UNKNOWN;
        break;
    }
  }
  switch (hLcd->initPara.chip) {
    case LCD_CHIP_ST7793:
      rev = lcd_chipInit_ST7763(hLcd);
      break;

    case LCD_CHIP_R61509V:
      rev = lcd_chipInit_R61509V(hLcd);
      break;
    
    case LCD_CHIP_NT35510:
      rev = lcd_chipInit_NT35510(hLcd);
      break;

    default:
      rev = HAL_ERROR;
      break;
  }
  if (rev != HAL_OK)
  {
    hLcd->state = LCD_STATE_ERROR;
  }
  return rev;
}

/**
 * @brief   设置写入图像的地址范围
 * @author  Alzn
 * @date    2021-08-07
 * @param   hLcd   lcd句柄
 * @param   x1 左边界
 * @param   x2 右边界
 * @param   y1 上边界
 * @param   y2 下边界
 */
void lcd_setRange(const lcd_handle_t *hLcd, uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2) {
  switch (hLcd->initPara.chip) {
    case LCD_CHIP_ST7793:
    case LCD_CHIP_R61509V:
      lcd_setRange_ST7763_R61509V(hLcd, x1, x2, y1, y2);
      break;
    
    case LCD_CHIP_NT35510:
      lcd_setRange_NT35510(hLcd, x1, x2, y1, y2);
      break;

    default:
      break;
  }
}

/**
 * @brief   设置写入图像的范围 For ST7763/R61509V
 * @author  Alzn
 * @date    2021-08-08
 * @param   hLcd   lcd句柄
 * @param   x1 左边界
 * @param   x2 右边界
 * @param   y1 上边界
 * @param   y2 下边界
 */
void lcd_setRange_ST7763_R61509V(const lcd_handle_t *hLcd, uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2){
  lcd_writeReg(hLcd, 0x0200, y1);
  lcd_writeReg(hLcd, 0x0201, x1);

  lcd_writeReg(hLcd, 0x0212, x1);
  lcd_writeReg(hLcd, 0x0210, y1);

  lcd_writeReg(hLcd, 0x0213, x2);
  lcd_writeReg(hLcd, 0x0211, y2);

  lcd_writeCom(hLcd, 0x0202);
}

/**
 * @brief   设置写入图像的范围 For NT35510
 * @author  Alzn
 * @date    2021-08-08
 * @param   hLcd   lcd句柄
 * @param   x1 左边界
 * @param   x2 右边界
 * @param   y1 上边界
 * @param   y2 下边界
 */
void lcd_setRange_NT35510(const lcd_handle_t *hLcd, uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2){
  lcd_writeReg(hLcd, 0X2A00, x1 >> 8);
  lcd_writeReg(hLcd, 0X2A01, x1 & 0XFF);
  lcd_writeReg(hLcd, 0X2A02, x2 >> 8);
  lcd_writeReg(hLcd, 0X2A03, x2 & 0XFF);

  lcd_writeReg(hLcd, 0X2B00, y1 >> 8);
  lcd_writeReg(hLcd, 0X2B01, y1 & 0XFF);
  lcd_writeReg(hLcd, 0X2B02, y2 >> 8);
  lcd_writeReg(hLcd, 0X2B03, y2 & 0XFF);

  lcd_writeCom(hLcd, 0x2C00);
}

/**
 * @brief   初始化序列 For ST7793
 * @author  Unknown, Form internet.
 * @date    2021-08-08
 * @param   hLcd 　LCD句柄
 * @retval  HAL Status
 */
HAL_StatusTypeDef lcd_chipInit_ST7763(lcd_handle_t *hLcd) {
  lcd_writeReg(hLcd, 0x0000, 0x0000);
  lcd_writeReg(hLcd, 0x0000, 0x0000);
  lcd_writeReg(hLcd, 0x0000, 0x0000);
  lcd_writeReg(hLcd, 0x0000, 0x0000);
  HAL_Delay(15);
  lcd_writeReg(hLcd, 0x0400, 0x6200);
  lcd_writeReg(hLcd, 0x0008, 0x0808);

  lcd_writeReg(hLcd, 0x0380, 0x0C00);
  lcd_writeReg(hLcd, 0x0381, 0x5A0B);
  lcd_writeReg(hLcd, 0x0382, 0x0906);
  lcd_writeReg(hLcd, 0x0383, 0x1017);
  lcd_writeReg(hLcd, 0x0384, 0x2300);
  lcd_writeReg(hLcd, 0x0385, 0x1700);
  lcd_writeReg(hLcd, 0x0386, 0x6309);
  lcd_writeReg(hLcd, 0x0387, 0x0C09);
  lcd_writeReg(hLcd, 0x0388, 0x100C);
  lcd_writeReg(hLcd, 0x0389, 0x2232);

  lcd_writeReg(hLcd, 0x0010, 0x0016);
  lcd_writeReg(hLcd, 0x0011, 0x0101);
  lcd_writeReg(hLcd, 0x0012, 0x0000);
  lcd_writeReg(hLcd, 0x0013, 0x0001);

  lcd_writeReg(hLcd, 0x0100, 0x0330);
  lcd_writeReg(hLcd, 0x0101, 0x0237);
  lcd_writeReg(hLcd, 0x0103, 0x0D00);
  lcd_writeReg(hLcd, 0x0280, 0x6100);
  lcd_writeReg(hLcd, 0x0102, 0xC1B0);
  HAL_Delay(50);

  lcd_writeReg(hLcd, 0x0001, 0x0100);
  lcd_writeReg(hLcd, 0x0002, 0x0100);
  lcd_writeReg(hLcd, 0x0003, 0x1030);
  lcd_writeReg(hLcd, 0x0009, 0x0001);
  lcd_writeReg(hLcd, 0x000C, 0x0001);
  lcd_writeReg(hLcd, 0x0090, 0x8000);
  lcd_writeReg(hLcd, 0x000F, 0x0000);

  lcd_writeReg(hLcd, 0x0210, 0x0000);
  lcd_writeReg(hLcd, 0x0211, 0x00EF);
  lcd_writeReg(hLcd, 0x0212, 0x0000);
  lcd_writeReg(hLcd, 0x0213, 0x018F);
  lcd_writeReg(hLcd, 0x0500, 0x0000);
  lcd_writeReg(hLcd, 0x0501, 0x0000);
  lcd_writeReg(hLcd, 0x0502, 0x005F);
  lcd_writeReg(hLcd, 0x0401, 0x0001);
  lcd_writeReg(hLcd, 0x0404, 0x0000);
  HAL_Delay(50);

  lcd_writeReg(hLcd, 0x0001, 0x0000);
  lcd_writeReg(hLcd, 0x0003, 0x1038);

  lcd_writeReg(hLcd, 0x0007, 0x0100);
  HAL_Delay(50);

  lcd_writeReg(hLcd, 0x0200, 0x0000);
  lcd_writeReg(hLcd, 0x0201, 0x0000);
  return HAL_OK;
}

/**
 * @brief   初始化序列 For R61509V
 * @author  Unknown, Form internet.
 * @date    2021-08-08
 * @param   hLcd LCD句柄
 * @retval  HAL Status
 */
HAL_StatusTypeDef lcd_chipInit_R61509V(lcd_handle_t *hLcd) {
  lcd_writeReg(hLcd, 0x0000, 0x0000);
  lcd_writeReg(hLcd, 0x0000, 0x0000);
  lcd_writeReg(hLcd, 0x0000, 0x0000);
  lcd_writeReg(hLcd, 0x0000, 0x0000);
  HAL_Delay(15);
  lcd_writeReg(hLcd, 0x0400, 0x6200);
  lcd_writeReg(hLcd, 0x0008, 0x0808);

  lcd_writeReg(hLcd, 0x0300, 0x0C00);
  lcd_writeReg(hLcd, 0x0301, 0x5A0B);
  lcd_writeReg(hLcd, 0x0302, 0x0906);
  lcd_writeReg(hLcd, 0x0303, 0x1017);
  lcd_writeReg(hLcd, 0x0304, 0x2300);
  lcd_writeReg(hLcd, 0x0305, 0x1700);
  lcd_writeReg(hLcd, 0x0306, 0x6309);
  lcd_writeReg(hLcd, 0x0307, 0x0C09);
  lcd_writeReg(hLcd, 0x0308, 0x100C);
  lcd_writeReg(hLcd, 0x0309, 0x2232);

  lcd_writeReg(hLcd, 0x0010, 0x0016);
  lcd_writeReg(hLcd, 0x0011, 0x0101);
  lcd_writeReg(hLcd, 0x0012, 0x0000);
  lcd_writeReg(hLcd, 0x0013, 0x0001);

  lcd_writeReg(hLcd, 0x0100, 0x0330);
  lcd_writeReg(hLcd, 0x0101, 0x0237);
  lcd_writeReg(hLcd, 0x0103, 0x0D00);
  lcd_writeReg(hLcd, 0x0280, 0x6100);
  lcd_writeReg(hLcd, 0x0102, 0xC1B0);
  HAL_Delay(50);

  lcd_writeReg(hLcd, 0x0001, 0x0100);
  lcd_writeReg(hLcd, 0x0002, 0x0100);
  lcd_writeReg(hLcd, 0x0003, 0x1030);
  lcd_writeReg(hLcd, 0x0009, 0x0001);
  lcd_writeReg(hLcd, 0x000C, 0x0000);
  lcd_writeReg(hLcd, 0x0090, 0x8000);
  lcd_writeReg(hLcd, 0x000F, 0x0000);

  lcd_writeReg(hLcd, 0x0210, 0x0000);
  lcd_writeReg(hLcd, 0x0211, 0x00EF);
  lcd_writeReg(hLcd, 0x0212, 0x0000);
  lcd_writeReg(hLcd, 0x0213, 0x018F);
  lcd_writeReg(hLcd, 0x0500, 0x0000);
  lcd_writeReg(hLcd, 0x0501, 0x0000);
  lcd_writeReg(hLcd, 0x0502, 0x005F);
  lcd_writeReg(hLcd, 0x0401, 0x0000);
  lcd_writeReg(hLcd, 0x0404, 0x0000);
  HAL_Delay(50);

  lcd_writeReg(hLcd, 0x0001, 0x0000);
  lcd_writeReg(hLcd, 0x003, 0x1038);

  lcd_writeReg(hLcd, 0x0007, 0x0100);
  HAL_Delay(50);

  lcd_writeReg(hLcd, 0x0200, 0x0000);
  lcd_writeReg(hLcd, 0x0201, 0x0000);
  return HAL_OK;
}

/**
 * @brief   初始化序列 For NT35510
 * @author  Unknown, Form internet.
 * @date    2021-08-08
 * @param   hLcd LCD句柄
 * @retval  HAL Status
 */
HAL_StatusTypeDef lcd_chipInit_NT35510(lcd_handle_t *hLcd) {
  HAL_Delay(50);
  lcd_writeReg(hLcd, 0xF000, 0x55);
  lcd_writeReg(hLcd, 0xF001, 0xAA);
  lcd_writeReg(hLcd, 0xF002, 0x52);
  lcd_writeReg(hLcd, 0xF003, 0x08);
  lcd_writeReg(hLcd, 0xF004, 0x01);

  lcd_writeReg(hLcd, 0xB600, 0x34);
  lcd_writeReg(hLcd, 0xB601, 0x34);
  lcd_writeReg(hLcd, 0xB602, 0x34);

  lcd_writeReg(hLcd, 0xB000, 0x0D);
  lcd_writeReg(hLcd, 0xB001, 0x0D);
  lcd_writeReg(hLcd, 0xB002, 0x0D);

  lcd_writeReg(hLcd, 0xB700, 0x24);
  lcd_writeReg(hLcd, 0xB701, 0x24);
  lcd_writeReg(hLcd, 0xB702, 0x24);

  lcd_writeReg(hLcd, 0xB100, 0x0D);
  lcd_writeReg(hLcd, 0xB101, 0x0D);
  lcd_writeReg(hLcd, 0xB102, 0x0D);

  lcd_writeReg(hLcd, 0xB800, 0x24);
  lcd_writeReg(hLcd, 0xB801, 0x24);
  lcd_writeReg(hLcd, 0xB802, 0x24);

  lcd_writeReg(hLcd, 0xB200, 0x00);

  lcd_writeReg(hLcd, 0xB900, 0x24);
  lcd_writeReg(hLcd, 0xB901, 0x24);
  lcd_writeReg(hLcd, 0xB902, 0x24);

  lcd_writeReg(hLcd, 0xB300, 0x05);
  lcd_writeReg(hLcd, 0xB301, 0x05);
  lcd_writeReg(hLcd, 0xB302, 0x05);

  lcd_writeReg(hLcd, 0xBA00, 0x34);
  lcd_writeReg(hLcd, 0xBA01, 0x34);
  lcd_writeReg(hLcd, 0xBA02, 0x34);

  lcd_writeReg(hLcd, 0xB500, 0x0B);
  lcd_writeReg(hLcd, 0xB501, 0x0B);
  lcd_writeReg(hLcd, 0xB502, 0x0B);

  lcd_writeReg(hLcd, 0xBC00, 0X00);
  lcd_writeReg(hLcd, 0xBC01, 0xA3);
  lcd_writeReg(hLcd, 0xBC02, 0X00);

  lcd_writeReg(hLcd, 0xBD00, 0x00);
  lcd_writeReg(hLcd, 0xBD01, 0xA3);
  lcd_writeReg(hLcd, 0xBD02, 0x00);

  lcd_writeReg(hLcd, 0xBE00, 0x00);
  lcd_writeReg(hLcd, 0xBE01, 0x63);
  
  lcd_writeReg(hLcd, 0xD100, 0x00);
  lcd_writeReg(hLcd, 0xD101, 0x37);
  lcd_writeReg(hLcd, 0xD102, 0x00);
  lcd_writeReg(hLcd, 0xD103, 0x52);
  lcd_writeReg(hLcd, 0xD104, 0x00);
  lcd_writeReg(hLcd, 0xD105, 0x7B);
  lcd_writeReg(hLcd, 0xD106, 0x00);
  lcd_writeReg(hLcd, 0xD107, 0x99);
  lcd_writeReg(hLcd, 0xD108, 0x00);
  lcd_writeReg(hLcd, 0xD109, 0xB1);
  lcd_writeReg(hLcd, 0xD10A, 0x00);
  lcd_writeReg(hLcd, 0xD10B, 0xD2);
  lcd_writeReg(hLcd, 0xD10C, 0x00);
  lcd_writeReg(hLcd, 0xD10D, 0xF6);
  lcd_writeReg(hLcd, 0xD10E, 0x01);
  lcd_writeReg(hLcd, 0xD10F, 0x27);
  lcd_writeReg(hLcd, 0xD110, 0x01);
  lcd_writeReg(hLcd, 0xD111, 0x4E);
  lcd_writeReg(hLcd, 0xD112, 0x01);
  lcd_writeReg(hLcd, 0xD113, 0x8C);
  lcd_writeReg(hLcd, 0xD114, 0x01);
  lcd_writeReg(hLcd, 0xD115, 0xBE);
  lcd_writeReg(hLcd, 0xD116, 0x02);
  lcd_writeReg(hLcd, 0xD117, 0x0B);
  lcd_writeReg(hLcd, 0xD118, 0x02);
  lcd_writeReg(hLcd, 0xD119, 0x48);
  lcd_writeReg(hLcd, 0xD11A, 0x02);
  lcd_writeReg(hLcd, 0xD11B, 0x4A);
  lcd_writeReg(hLcd, 0xD11C, 0x02);
  lcd_writeReg(hLcd, 0xD11D, 0x7E);
  lcd_writeReg(hLcd, 0xD11E, 0x02);
  lcd_writeReg(hLcd, 0xD11F, 0xBC);
  lcd_writeReg(hLcd, 0xD120, 0x02);
  lcd_writeReg(hLcd, 0xD121, 0xE1);
  lcd_writeReg(hLcd, 0xD122, 0x03);
  lcd_writeReg(hLcd, 0xD123, 0x10);
  lcd_writeReg(hLcd, 0xD124, 0x03);
  lcd_writeReg(hLcd, 0xD125, 0x31);
  lcd_writeReg(hLcd, 0xD126, 0x03);
  lcd_writeReg(hLcd, 0xD127, 0x5A);
  lcd_writeReg(hLcd, 0xD128, 0x03);
  lcd_writeReg(hLcd, 0xD129, 0x73);
  lcd_writeReg(hLcd, 0xD12A, 0x03);
  lcd_writeReg(hLcd, 0xD12B, 0x94);
  lcd_writeReg(hLcd, 0xD12C, 0x03);
  lcd_writeReg(hLcd, 0xD12D, 0x9F);
  lcd_writeReg(hLcd, 0xD12E, 0x03);
  lcd_writeReg(hLcd, 0xD12F, 0xB3);
  lcd_writeReg(hLcd, 0xD130, 0x03);
  lcd_writeReg(hLcd, 0xD131, 0xB9);
  lcd_writeReg(hLcd, 0xD132, 0x03);
  lcd_writeReg(hLcd, 0xD133, 0xC1);
  lcd_writeReg(hLcd, 0xD200, 0x00);
  lcd_writeReg(hLcd, 0xD201, 0x37);
  lcd_writeReg(hLcd, 0xD202, 0x00);
  lcd_writeReg(hLcd, 0xD203, 0x52);
  lcd_writeReg(hLcd, 0xD204, 0x00);
  lcd_writeReg(hLcd, 0xD205, 0x7B);
  lcd_writeReg(hLcd, 0xD206, 0x00);
  lcd_writeReg(hLcd, 0xD207, 0x99);
  lcd_writeReg(hLcd, 0xD208, 0x00);
  lcd_writeReg(hLcd, 0xD209, 0xB1);
  lcd_writeReg(hLcd, 0xD20A, 0x00);
  lcd_writeReg(hLcd, 0xD20B, 0xD2);
  lcd_writeReg(hLcd, 0xD20C, 0x00);
  lcd_writeReg(hLcd, 0xD20D, 0xF6);
  lcd_writeReg(hLcd, 0xD20E, 0x01);
  lcd_writeReg(hLcd, 0xD20F, 0x27);
  lcd_writeReg(hLcd, 0xD210, 0x01);
  lcd_writeReg(hLcd, 0xD211, 0x4E);
  lcd_writeReg(hLcd, 0xD212, 0x01);
  lcd_writeReg(hLcd, 0xD213, 0x8C);
  lcd_writeReg(hLcd, 0xD214, 0x01);
  lcd_writeReg(hLcd, 0xD215, 0xBE);
  lcd_writeReg(hLcd, 0xD216, 0x02);
  lcd_writeReg(hLcd, 0xD217, 0x0B);
  lcd_writeReg(hLcd, 0xD218, 0x02);
  lcd_writeReg(hLcd, 0xD219, 0x48);
  lcd_writeReg(hLcd, 0xD21A, 0x02);
  lcd_writeReg(hLcd, 0xD21B, 0x4A);
  lcd_writeReg(hLcd, 0xD21C, 0x02);
  lcd_writeReg(hLcd, 0xD21D, 0x7E);
  lcd_writeReg(hLcd, 0xD21E, 0x02);
  lcd_writeReg(hLcd, 0xD21F, 0xBC);
  lcd_writeReg(hLcd, 0xD220, 0x02);
  lcd_writeReg(hLcd, 0xD221, 0xE1);
  lcd_writeReg(hLcd, 0xD222, 0x03);
  lcd_writeReg(hLcd, 0xD223, 0x10);
  lcd_writeReg(hLcd, 0xD224, 0x03);
  lcd_writeReg(hLcd, 0xD225, 0x31);
  lcd_writeReg(hLcd, 0xD226, 0x03);
  lcd_writeReg(hLcd, 0xD227, 0x5A);
  lcd_writeReg(hLcd, 0xD228, 0x03);
  lcd_writeReg(hLcd, 0xD229, 0x73);
  lcd_writeReg(hLcd, 0xD22A, 0x03);
  lcd_writeReg(hLcd, 0xD22B, 0x94);
  lcd_writeReg(hLcd, 0xD22C, 0x03);
  lcd_writeReg(hLcd, 0xD22D, 0x9F);
  lcd_writeReg(hLcd, 0xD22E, 0x03);
  lcd_writeReg(hLcd, 0xD22F, 0xB3);
  lcd_writeReg(hLcd, 0xD230, 0x03);
  lcd_writeReg(hLcd, 0xD231, 0xB9);
  lcd_writeReg(hLcd, 0xD232, 0x03);
  lcd_writeReg(hLcd, 0xD233, 0xC1);
  lcd_writeReg(hLcd, 0xD300, 0x00);
  lcd_writeReg(hLcd, 0xD301, 0x37);
  lcd_writeReg(hLcd, 0xD302, 0x00);
  lcd_writeReg(hLcd, 0xD303, 0x52);
  lcd_writeReg(hLcd, 0xD304, 0x00);
  lcd_writeReg(hLcd, 0xD305, 0x7B);
  lcd_writeReg(hLcd, 0xD306, 0x00);
  lcd_writeReg(hLcd, 0xD307, 0x99);
  lcd_writeReg(hLcd, 0xD308, 0x00);
  lcd_writeReg(hLcd, 0xD309, 0xB1);
  lcd_writeReg(hLcd, 0xD30A, 0x00);
  lcd_writeReg(hLcd, 0xD30B, 0xD2);
  lcd_writeReg(hLcd, 0xD30C, 0x00);
  lcd_writeReg(hLcd, 0xD30D, 0xF6);
  lcd_writeReg(hLcd, 0xD30E, 0x01);
  lcd_writeReg(hLcd, 0xD30F, 0x27);
  lcd_writeReg(hLcd, 0xD310, 0x01);
  lcd_writeReg(hLcd, 0xD311, 0x4E);
  lcd_writeReg(hLcd, 0xD312, 0x01);
  lcd_writeReg(hLcd, 0xD313, 0x8C);
  lcd_writeReg(hLcd, 0xD314, 0x01);
  lcd_writeReg(hLcd, 0xD315, 0xBE);
  lcd_writeReg(hLcd, 0xD316, 0x02);
  lcd_writeReg(hLcd, 0xD317, 0x0B);
  lcd_writeReg(hLcd, 0xD318, 0x02);
  lcd_writeReg(hLcd, 0xD319, 0x48);
  lcd_writeReg(hLcd, 0xD31A, 0x02);
  lcd_writeReg(hLcd, 0xD31B, 0x4A);
  lcd_writeReg(hLcd, 0xD31C, 0x02);
  lcd_writeReg(hLcd, 0xD31D, 0x7E);
  lcd_writeReg(hLcd, 0xD31E, 0x02);
  lcd_writeReg(hLcd, 0xD31F, 0xBC);
  lcd_writeReg(hLcd, 0xD320, 0x02);
  lcd_writeReg(hLcd, 0xD321, 0xE1);
  lcd_writeReg(hLcd, 0xD322, 0x03);
  lcd_writeReg(hLcd, 0xD323, 0x10);
  lcd_writeReg(hLcd, 0xD324, 0x03);
  lcd_writeReg(hLcd, 0xD325, 0x31);
  lcd_writeReg(hLcd, 0xD326, 0x03);
  lcd_writeReg(hLcd, 0xD327, 0x5A);
  lcd_writeReg(hLcd, 0xD328, 0x03);
  lcd_writeReg(hLcd, 0xD329, 0x73);
  lcd_writeReg(hLcd, 0xD32A, 0x03);
  lcd_writeReg(hLcd, 0xD32B, 0x94);
  lcd_writeReg(hLcd, 0xD32C, 0x03);
  lcd_writeReg(hLcd, 0xD32D, 0x9F);
  lcd_writeReg(hLcd, 0xD32E, 0x03);
  lcd_writeReg(hLcd, 0xD32F, 0xB3);
  lcd_writeReg(hLcd, 0xD330, 0x03);
  lcd_writeReg(hLcd, 0xD331, 0xB9);
  lcd_writeReg(hLcd, 0xD332, 0x03);
  lcd_writeReg(hLcd, 0xD333, 0xC1);

  lcd_writeReg(hLcd, 0xD400, 0x00);
  lcd_writeReg(hLcd, 0xD401, 0x37);
  lcd_writeReg(hLcd, 0xD402, 0x00);
  lcd_writeReg(hLcd, 0xD403, 0x52);
  lcd_writeReg(hLcd, 0xD404, 0x00);
  lcd_writeReg(hLcd, 0xD405, 0x7B);
  lcd_writeReg(hLcd, 0xD406, 0x00);
  lcd_writeReg(hLcd, 0xD407, 0x99);
  lcd_writeReg(hLcd, 0xD408, 0x00);
  lcd_writeReg(hLcd, 0xD409, 0xB1);
  lcd_writeReg(hLcd, 0xD40A, 0x00);
  lcd_writeReg(hLcd, 0xD40B, 0xD2);
  lcd_writeReg(hLcd, 0xD40C, 0x00);
  lcd_writeReg(hLcd, 0xD40D, 0xF6);
  lcd_writeReg(hLcd, 0xD40E, 0x01);
  lcd_writeReg(hLcd, 0xD40F, 0x27);
  lcd_writeReg(hLcd, 0xD410, 0x01);
  lcd_writeReg(hLcd, 0xD411, 0x4E);
  lcd_writeReg(hLcd, 0xD412, 0x01);
  lcd_writeReg(hLcd, 0xD413, 0x8C);
  lcd_writeReg(hLcd, 0xD414, 0x01);
  lcd_writeReg(hLcd, 0xD415, 0xBE);
  lcd_writeReg(hLcd, 0xD416, 0x02);
  lcd_writeReg(hLcd, 0xD417, 0x0B);
  lcd_writeReg(hLcd, 0xD418, 0x02);
  lcd_writeReg(hLcd, 0xD419, 0x48);
  lcd_writeReg(hLcd, 0xD41A, 0x02);
  lcd_writeReg(hLcd, 0xD41B, 0x4A);
  lcd_writeReg(hLcd, 0xD41C, 0x02);
  lcd_writeReg(hLcd, 0xD41D, 0x7E);
  lcd_writeReg(hLcd, 0xD41E, 0x02);
  lcd_writeReg(hLcd, 0xD41F, 0xBC);
  lcd_writeReg(hLcd, 0xD420, 0x02);
  lcd_writeReg(hLcd, 0xD421, 0xE1);
  lcd_writeReg(hLcd, 0xD422, 0x03);
  lcd_writeReg(hLcd, 0xD423, 0x10);
  lcd_writeReg(hLcd, 0xD424, 0x03);
  lcd_writeReg(hLcd, 0xD425, 0x31);
  lcd_writeReg(hLcd, 0xD426, 0x03);
  lcd_writeReg(hLcd, 0xD427, 0x5A);
  lcd_writeReg(hLcd, 0xD428, 0x03);
  lcd_writeReg(hLcd, 0xD429, 0x73);
  lcd_writeReg(hLcd, 0xD42A, 0x03);
  lcd_writeReg(hLcd, 0xD42B, 0x94);
  lcd_writeReg(hLcd, 0xD42C, 0x03);
  lcd_writeReg(hLcd, 0xD42D, 0x9F);
  lcd_writeReg(hLcd, 0xD42E, 0x03);
  lcd_writeReg(hLcd, 0xD42F, 0xB3);
  lcd_writeReg(hLcd, 0xD430, 0x03);
  lcd_writeReg(hLcd, 0xD431, 0xB9);
  lcd_writeReg(hLcd, 0xD432, 0x03);
  lcd_writeReg(hLcd, 0xD433, 0xC1);

  lcd_writeReg(hLcd, 0xD500, 0x00);
  lcd_writeReg(hLcd, 0xD501, 0x37);
  lcd_writeReg(hLcd, 0xD502, 0x00);
  lcd_writeReg(hLcd, 0xD503, 0x52);
  lcd_writeReg(hLcd, 0xD504, 0x00);
  lcd_writeReg(hLcd, 0xD505, 0x7B);
  lcd_writeReg(hLcd, 0xD506, 0x00);
  lcd_writeReg(hLcd, 0xD507, 0x99);
  lcd_writeReg(hLcd, 0xD508, 0x00);
  lcd_writeReg(hLcd, 0xD509, 0xB1);
  lcd_writeReg(hLcd, 0xD50A, 0x00);
  lcd_writeReg(hLcd, 0xD50B, 0xD2);
  lcd_writeReg(hLcd, 0xD50C, 0x00);
  lcd_writeReg(hLcd, 0xD50D, 0xF6);
  lcd_writeReg(hLcd, 0xD50E, 0x01);
  lcd_writeReg(hLcd, 0xD50F, 0x27);
  lcd_writeReg(hLcd, 0xD510, 0x01);
  lcd_writeReg(hLcd, 0xD511, 0x4E);
  lcd_writeReg(hLcd, 0xD512, 0x01);
  lcd_writeReg(hLcd, 0xD513, 0x8C);
  lcd_writeReg(hLcd, 0xD514, 0x01);
  lcd_writeReg(hLcd, 0xD515, 0xBE);
  lcd_writeReg(hLcd, 0xD516, 0x02);
  lcd_writeReg(hLcd, 0xD517, 0x0B);
  lcd_writeReg(hLcd, 0xD518, 0x02);
  lcd_writeReg(hLcd, 0xD519, 0x48);
  lcd_writeReg(hLcd, 0xD51A, 0x02);
  lcd_writeReg(hLcd, 0xD51B, 0x4A);
  lcd_writeReg(hLcd, 0xD51C, 0x02);
  lcd_writeReg(hLcd, 0xD51D, 0x7E);
  lcd_writeReg(hLcd, 0xD51E, 0x02);
  lcd_writeReg(hLcd, 0xD51F, 0xBC);
  lcd_writeReg(hLcd, 0xD520, 0x02);
  lcd_writeReg(hLcd, 0xD521, 0xE1);
  lcd_writeReg(hLcd, 0xD522, 0x03);
  lcd_writeReg(hLcd, 0xD523, 0x10);
  lcd_writeReg(hLcd, 0xD524, 0x03);
  lcd_writeReg(hLcd, 0xD525, 0x31);
  lcd_writeReg(hLcd, 0xD526, 0x03);
  lcd_writeReg(hLcd, 0xD527, 0x5A);
  lcd_writeReg(hLcd, 0xD528, 0x03);
  lcd_writeReg(hLcd, 0xD529, 0x73);
  lcd_writeReg(hLcd, 0xD52A, 0x03);
  lcd_writeReg(hLcd, 0xD52B, 0x94);
  lcd_writeReg(hLcd, 0xD52C, 0x03);
  lcd_writeReg(hLcd, 0xD52D, 0x9F);
  lcd_writeReg(hLcd, 0xD52E, 0x03);
  lcd_writeReg(hLcd, 0xD52F, 0xB3);
  lcd_writeReg(hLcd, 0xD530, 0x03);
  lcd_writeReg(hLcd, 0xD531, 0xB9);
  lcd_writeReg(hLcd, 0xD532, 0x03);
  lcd_writeReg(hLcd, 0xD533, 0xC1);

  lcd_writeReg(hLcd, 0xD600, 0x00);
  lcd_writeReg(hLcd, 0xD601, 0x37);
  lcd_writeReg(hLcd, 0xD602, 0x00);
  lcd_writeReg(hLcd, 0xD603, 0x52);
  lcd_writeReg(hLcd, 0xD604, 0x00);
  lcd_writeReg(hLcd, 0xD605, 0x7B);
  lcd_writeReg(hLcd, 0xD606, 0x00);
  lcd_writeReg(hLcd, 0xD607, 0x99);
  lcd_writeReg(hLcd, 0xD608, 0x00);
  lcd_writeReg(hLcd, 0xD609, 0xB1);
  lcd_writeReg(hLcd, 0xD60A, 0x00);
  lcd_writeReg(hLcd, 0xD60B, 0xD2);
  lcd_writeReg(hLcd, 0xD60C, 0x00);
  lcd_writeReg(hLcd, 0xD60D, 0xF6);
  lcd_writeReg(hLcd, 0xD60E, 0x01);
  lcd_writeReg(hLcd, 0xD60F, 0x27);
  lcd_writeReg(hLcd, 0xD610, 0x01);
  lcd_writeReg(hLcd, 0xD611, 0x4E);
  lcd_writeReg(hLcd, 0xD612, 0x01);
  lcd_writeReg(hLcd, 0xD613, 0x8C);
  lcd_writeReg(hLcd, 0xD614, 0x01);
  lcd_writeReg(hLcd, 0xD615, 0xBE);
  lcd_writeReg(hLcd, 0xD616, 0x02);
  lcd_writeReg(hLcd, 0xD617, 0x0B);
  lcd_writeReg(hLcd, 0xD618, 0x02);
  lcd_writeReg(hLcd, 0xD619, 0x48);
  lcd_writeReg(hLcd, 0xD61A, 0x02);
  lcd_writeReg(hLcd, 0xD61B, 0x4A);
  lcd_writeReg(hLcd, 0xD61C, 0x02);
  lcd_writeReg(hLcd, 0xD61D, 0x7E);
  lcd_writeReg(hLcd, 0xD61E, 0x02);
  lcd_writeReg(hLcd, 0xD61F, 0xBC);
  lcd_writeReg(hLcd, 0xD620, 0x02);
  lcd_writeReg(hLcd, 0xD621, 0xE1);
  lcd_writeReg(hLcd, 0xD622, 0x03);
  lcd_writeReg(hLcd, 0xD623, 0x10);
  lcd_writeReg(hLcd, 0xD624, 0x03);
  lcd_writeReg(hLcd, 0xD625, 0x31);
  lcd_writeReg(hLcd, 0xD626, 0x03);
  lcd_writeReg(hLcd, 0xD627, 0x5A);
  lcd_writeReg(hLcd, 0xD628, 0x03);
  lcd_writeReg(hLcd, 0xD629, 0x73);
  lcd_writeReg(hLcd, 0xD62A, 0x03);
  lcd_writeReg(hLcd, 0xD62B, 0x94);
  lcd_writeReg(hLcd, 0xD62C, 0x03);
  lcd_writeReg(hLcd, 0xD62D, 0x9F);
  lcd_writeReg(hLcd, 0xD62E, 0x03);
  lcd_writeReg(hLcd, 0xD62F, 0xB3);
  lcd_writeReg(hLcd, 0xD630, 0x03);
  lcd_writeReg(hLcd, 0xD631, 0xB9);
  lcd_writeReg(hLcd, 0xD632, 0x03);
  lcd_writeReg(hLcd, 0xD633, 0xC1);

  lcd_writeReg(hLcd, 0xF000, 0x55);
  lcd_writeReg(hLcd, 0xF001, 0xAA);
  lcd_writeReg(hLcd, 0xF002, 0x52);
  lcd_writeReg(hLcd, 0xF003, 0x08);
  lcd_writeReg(hLcd, 0xF004, 0x00);

  lcd_writeReg(hLcd, 0xB000, 0x08);
  lcd_writeReg(hLcd, 0xB001, 0x05);
  lcd_writeReg(hLcd, 0xB002, 0x02);
  lcd_writeReg(hLcd, 0xB003, 0x05);
  lcd_writeReg(hLcd, 0xB004, 0x02);
  lcd_writeReg(hLcd, 0xB600, 0x08);
  lcd_writeReg(hLcd, 0xB500, 0x50);

  lcd_writeReg(hLcd, 0xB700, 0x00);
  lcd_writeReg(hLcd, 0xB701, 0x00);

  lcd_writeReg(hLcd, 0xB800, 0x01);
  lcd_writeReg(hLcd, 0xB801, 0x05);
  lcd_writeReg(hLcd, 0xB802, 0x05);
  lcd_writeReg(hLcd, 0xB803, 0x05);

  lcd_writeReg(hLcd, 0xBC00, 0x00);
  lcd_writeReg(hLcd, 0xBC01, 0x00);
  lcd_writeReg(hLcd, 0xBC02, 0x00);

  lcd_writeReg(hLcd, 0xCC00, 0x03);
  lcd_writeReg(hLcd, 0xCC01, 0x00);
  lcd_writeReg(hLcd, 0xCC02, 0x00);

  lcd_writeReg(hLcd, 0xBD00, 0x01);
  lcd_writeReg(hLcd, 0xBD01, 0x84);
  lcd_writeReg(hLcd, 0xBD02, 0x07);
  lcd_writeReg(hLcd, 0xBD03, 0x31);
  lcd_writeReg(hLcd, 0xBD04, 0x00);

  lcd_writeReg(hLcd, 0xBA00, 0x01);

  lcd_writeReg(hLcd, 0xFF00, 0xAA);
  lcd_writeReg(hLcd, 0xFF01, 0x55);
  lcd_writeReg(hLcd, 0xFF02, 0x25);
  lcd_writeReg(hLcd, 0xFF03, 0x01);

  lcd_writeReg(hLcd, 0x3500, 0x00);
  lcd_writeReg(hLcd, 0x3600, 0x60);
  lcd_writeReg(hLcd, 0x3a00, 0x55);
  lcd_writeCom(hLcd, 0x1100);
  HAL_Delay(120);
  lcd_writeCom(hLcd, 0x2900);
  lcd_writeCom(hLcd, 0x2C00);

  return HAL_OK;
}

/* END OF FILE */