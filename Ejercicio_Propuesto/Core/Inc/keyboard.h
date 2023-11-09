/*
 * keyboard.h
 *
 *
 *      Author: JOHAN BEJARANO
 */

#ifndef INC_KEYBOARD_H_
#define INC_KEYBOARD_H_
#include <stdint.h>
#include <stdio.h>
#include "stm32l4xx_hal.h"

// Port definitions
#define ROW_1_GPIO_Port GPIOA  // Row ports
#define ROW_2_GPIO_Port GPIOB
#define ROW_3_GPIO_Port GPIOB
#define ROW_4_GPIO_Port GPIOB

#define COLUMN_1_GPIO_Port GPIOB // Column ports
#define COLUMN_2_GPIO_Port GPIOA
#define COLUMN_3_GPIO_Port GPIOA
#define COLUMN_4_GPIO_Port GPIOC

// Pin Definitions
#define ROW_1_Pin GPIO_PIN_10 // Pin Rows
#define ROW_2_Pin GPIO_PIN_3
#define ROW_3_Pin GPIO_PIN_5
#define ROW_4_Pin GPIO_PIN_4

#define COLUMN_1_Pin GPIO_PIN_10 // Pin Column
#define COLUMN_2_Pin GPIO_PIN_8
#define COLUMN_3_Pin GPIO_PIN_9
#define COLUMN_4_Pin GPIO_PIN_7

void keyboard_init(void); // Column initialization
uint16_t keyboard_handler(uint16_t column_to_evaluate); // Key selection

#endif /* INC_KEYBOARD_H_ */
