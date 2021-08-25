/**
 * @file    user_main.c
 * @brief   自定义main文件
 * @author  Alzn
 * @date    2021-08-07
 */

/*------ Includes ---------*/
#include "user_main.h"
#include "laserUnit.h"
#include "lcd_driver.h"
#include "ringBuffer.h"
#include "stm32f4xx_hal.h"
#include "usart.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>
/*------- Define ----------*/
#define uart_rxRingBuf_size 2048
#define uart_rxBuf_size 32
#define uart_txBuf_size 32
#define strBuf_size 64
#define dataBuf_size 32
/*------- Typedef ---------*/
typedef enum
{
  KEY_NULL = 0,
  KEY_UP,
  KEY_DOWN,
} keyValue_t;

/*-------- Const ----------*/
const uint32_t drawMaxLen = 200;
const uint32_t drawMidX = 400;
const uint32_t drawMidY = 200;
/*------- Variable --------*/
static keyValue_t keyBuf;
static lcd_handle_t hLcd;
static laserUnit_handle_t hRader;
static char strBuf[strBuf_size];
static uint32_t dataCnt = 0;
static uint32_t prePtsX[LASER_UNIT_DATA_PER_CIRCLE];
static uint32_t prePtsY[LASER_UNIT_DATA_PER_CIRCLE];

/*------ Functions --------*/
void sysInit(void);
void keyScanner(void);
void uartRxPrinter(void);
void txTester(void);

/**
 * @brief  自定义main循环
 * @author Alzn
 * @date   2021-08-07
 */
void userMain(void) {

  sysInit();
  while (1) {
    keyScanner();
    laserUnit_task(&hRader);
    if (laserUnit_getIsDataOK(&hRader)) {
      const uint16_t *p_distance = laserUnit_getDistanceDataPtr(&hRader);
      const uint16_t *p_reflectivity = laserUnit_getReflectivityDataPtr(&hRader);
      for (uint32_t i = 0; i < LASER_UNIT_DATA_PER_CIRCLE; i++) {
        uint32_t length = p_distance[i] / 5;
        uint32_t color = p_reflectivity[i];
        uint32_t pointX, pointY;
        float angle = (i * 2 * 3.1415926) / (float)LASER_UNIT_DATA_PER_CIRCLE;
        if (0 == color) {
          color = 0xA000;
          length = drawMaxLen;
        } else {
          color += 0x0AF0;
        }
        if (length > drawMaxLen) {
          length = drawMaxLen;
        }
        pointX = drawMidX + length * cosf(angle);
        pointY = drawMidY + length * sinf(angle);
        lcd_drawPoint(&hLcd, prePtsX[i], prePtsY[i], 0x0000);
        lcd_drawPoint(&hLcd, pointX, pointY, color);
        prePtsX[i] = pointX;
        prePtsY[i] = pointY;
      }
      dataCnt++;
      laserUnit_resetDataOKFlag(&hRader);
    }
    lcd_drawLine(&hLcd, drawMidX - drawMaxLen, drawMidY, drawMidX + drawMaxLen, drawMidY, 0x3186);
    lcd_drawLine(&hLcd, drawMidX, drawMidY - drawMaxLen, drawMidX, drawMidY + drawMaxLen, 0x3186);
    sprintf(strBuf, "pwm   = %8.5f", hRader.hpid.ctrlVal);
    lcd_drawString(&hLcd, 0, 0, strBuf, &lcd_font_consolas_16_8x14, 0xFFFF, 0x0000);
    sprintf(strBuf, "speed = %8.0f", hRader.hpid.meaVal);
    lcd_drawString(&hLcd, 0, 15, strBuf, &lcd_font_consolas_16_8x14, 0xFFFF, 0x0000);
    sprintf(strBuf, "cnt   = %8ld", dataCnt);
    lcd_drawString(&hLcd, 0, 30, strBuf, &lcd_font_consolas_16_8x14, 0xFFFF, 0x0000);
  }
}

/**
 * @brief  初始化系统
 * @author Alzn
 * @date   2021-08-07
 */
void sysInit(void) {
  /* LCD */
  hLcd.initPara.chip = LCD_CHIP_NT35510;
  hLcd.initPara.chipSelect = LCD_CHIP_SELECT_NE4;
  hLcd.initPara.regSelect = LCD_REG_SELECT_A6;
  hLcd.initPara.sizeX = 800;
  hLcd.initPara.sizeY = 480;
  lcd_init(&hLcd);

  laserUnit_init(&hRader, &huart2, &htim9, TIM_CHANNEL_1);

  usart_sendStr(&huart1, "System initialization completed.\r\n");
}

/**
 * @brief   按键扫描
 * @author  Alzn
 * @date    2021-08-10
 */
void keyScanner(void) {
  /*编码器驱动*/
  static _Bool keyFlagUp = 0, keyFlagDown = 0, keyFlagAll = 0;
  _Bool keyDownValue = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10);
  _Bool keyUpValue = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11);
  if (!keyFlagUp && !keyFlagDown && !keyFlagAll) {
    if (!keyDownValue && keyUpValue)
      keyFlagDown = 1;
    else if (!keyUpValue && keyDownValue)
      keyFlagUp = 1;
  }

  if ((keyFlagUp || keyFlagDown) && !keyFlagAll) {
    if (!keyDownValue && !keyUpValue) {
      keyFlagAll = 1;
    }
  }

  if ((keyUpValue && keyDownValue) && keyFlagAll) {
    if (keyFlagDown) {
      keyBuf = KEY_DOWN;
    }
    if (keyFlagUp) {
      keyBuf = KEY_UP;
    }
    keyFlagUp = 0;
    keyFlagDown = 0;
    keyFlagAll = 0;
  }
}

/**
 * @brief   UART接收回调
 * @author  Alzn
 * @date    2021-08-09
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  laserUnit_uartRxCallBack(&hRader, huart);
}

/* END OF FILE */