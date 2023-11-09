#include "keyboard.h"


/*** Debounce the key press (remove noise in the key) ***/
#define KEY_DEBOUNCE_MS 100 /*!> Minimum time required for since last press */

/**
 * @brief This functions initialize the functionality of the keypad
 */
void keyboard_init(void)
{
	// Configure the row pins as outputs and set them high
	 ROW_1_GPIO_Port->BSRR = ROW_1_Pin;
	 ROW_2_GPIO_Port->BSRR = ROW_2_Pin;
	 ROW_3_GPIO_Port->BSRR = ROW_3_Pin;
	 ROW_4_GPIO_Port->BSRR = ROW_4_Pin;
}

/**
 * @brief  This function debounces and identify keypad events.
 * @param  column_to_evaluate: the column where the event happened.
 * @retval 0xFF -> invalid key. [0x00 - 0x0F] -> valid key.
 */
uint16_t keyboard_handler(uint16_t column_to_evaluate)
{
	uint16_t key_pressed = 0xFF; // Value to return
	static uint32_t last_pressed_tick = 0;
	if (HAL_GetTick() <= (last_pressed_tick + KEY_DEBOUNCE_MS)) // less than KEY_DEBOUNCE_MS since last press. Probably noise
	{
		return key_pressed; // return 0xFF
	}
	last_pressed_tick = HAL_GetTick();

	/*** Check in which column the event happened ***/
	switch (column_to_evaluate)
	{
	case COLUMN_1_Pin:
		ROW_1_GPIO_Port->BSRR = ROW_1_Pin; // turn on row 1
		ROW_2_GPIO_Port->BRR = ROW_2_Pin;  // turn off row 2
		ROW_3_GPIO_Port->BRR = ROW_3_Pin;  // turn off row 3
		ROW_4_GPIO_Port->BRR = ROW_4_Pin;  // turn off row 4
		if (COLUMN_1_GPIO_Port->IDR & COLUMN_1_Pin)
		{
			key_pressed = 0x01; // if column 1 is still high -> column 1 + row 1 = key 1
			break;
		}

		ROW_1_GPIO_Port->BRR = ROW_1_Pin; 	// turn off row 1
		ROW_2_GPIO_Port->BSRR = ROW_2_Pin;  // turn on row 2
		ROW_3_GPIO_Port->BRR = ROW_3_Pin;   // turn off row 3
		ROW_4_GPIO_Port->BRR = ROW_4_Pin;   // turn off row 4
		if (COLUMN_1_GPIO_Port->IDR & COLUMN_1_Pin)
		{
			key_pressed = 0x04; // if column 1 is still high -> column 1 + row 2 = key 4
			break;
		}

		ROW_1_GPIO_Port->BRR = ROW_1_Pin;   // turn off row 1
		ROW_2_GPIO_Port->BRR = ROW_2_Pin; 	// turn off row 2
		ROW_3_GPIO_Port->BSRR = ROW_3_Pin;  // turn on row 3
		ROW_4_GPIO_Port->BRR = ROW_4_Pin;   // turn off row 4
		if (COLUMN_1_GPIO_Port->IDR & COLUMN_1_Pin)
		{
			key_pressed = 0x07; // if column 1 is still high -> column 1 + row 3 = key 7
			break;
		}

		ROW_1_GPIO_Port->BRR = ROW_1_Pin;	// turn off row 4
		ROW_2_GPIO_Port->BRR = ROW_2_Pin;	// turn off row 4
		ROW_3_GPIO_Port->BRR = ROW_3_Pin;	// turn off row 3
		ROW_4_GPIO_Port->BSRR = ROW_4_Pin; 	// turn on row 4
		if (COLUMN_1_GPIO_Port->IDR & COLUMN_1_Pin)
		{
			key_pressed = 0x0E; // if column 1 is still high -> column 1 + row 4 = key *
			break;
		}
		break;


	case COLUMN_2_Pin:
		ROW_1_GPIO_Port->BSRR = ROW_1_Pin; // turn on row 1
		ROW_2_GPIO_Port->BRR = ROW_2_Pin;  // turn off row 2
		ROW_3_GPIO_Port->BRR = ROW_3_Pin;  // turn off row 3
		ROW_4_GPIO_Port->BRR = ROW_4_Pin;  // turn off row 4
		if (COLUMN_2_GPIO_Port->IDR & COLUMN_2_Pin)
		{
			key_pressed = 0x02; // if column 2 is still high -> column 2 + row 1 = key 2
			break;
		}

		ROW_1_GPIO_Port->BRR = ROW_1_Pin; 	// turn off row 1
		ROW_2_GPIO_Port->BSRR = ROW_2_Pin;  // turn on row 2
		ROW_3_GPIO_Port->BRR = ROW_3_Pin;   // turn off row 3
		ROW_4_GPIO_Port->BRR = ROW_4_Pin;	// turn off row 4
		if (COLUMN_2_GPIO_Port->IDR & COLUMN_2_Pin)
		{
			key_pressed = 0x05; // if column 2 is still high -> column 2 + row 2 = key 5
			break;
		}

		ROW_1_GPIO_Port->BRR = ROW_1_Pin;	// turn off row 1
		ROW_2_GPIO_Port->BRR = ROW_2_Pin; 	// turn off row 2
		ROW_3_GPIO_Port->BSRR = ROW_3_Pin;  // turn on row 3
		ROW_4_GPIO_Port->BRR = ROW_4_Pin; 	// turn off row 4
		if (COLUMN_2_GPIO_Port->IDR & COLUMN_2_Pin)
		{
			key_pressed = 0x08; // if column 2 is still high -> column 2 + row 3 = key 8
			break;
		}

		ROW_1_GPIO_Port->BRR = ROW_1_Pin;	// turn off row 1
		ROW_2_GPIO_Port->BRR = ROW_2_Pin;	// turn off row 2
		ROW_3_GPIO_Port->BRR = ROW_3_Pin;	// turn off row 3
		ROW_4_GPIO_Port->BSRR = ROW_4_Pin;	// turn on row 4
		if (COLUMN_2_GPIO_Port->IDR & COLUMN_2_Pin)
		{
			key_pressed = 0x00; // if column 2 is still high -> column 2 + row 4 = key 0
			break;
		}
		break;

	case COLUMN_3_Pin:
		ROW_1_GPIO_Port->BSRR = ROW_1_Pin; // turn on row 1
		ROW_2_GPIO_Port->BRR = ROW_2_Pin;  // turn off row 2
		ROW_3_GPIO_Port->BRR = ROW_3_Pin;  // turn off row 3
		ROW_4_GPIO_Port->BRR = ROW_4_Pin;  // turn off row 4
		if (COLUMN_3_GPIO_Port->IDR & COLUMN_3_Pin)
		{
			key_pressed = 0x03; // if column 3 is still high -> column 3 + row 1 = key 3
			break;
		}

		ROW_1_GPIO_Port->BRR = ROW_1_Pin; 	// turn off row 1
		ROW_2_GPIO_Port->BSRR = ROW_2_Pin;  // turn on row 2
		ROW_3_GPIO_Port->BRR = ROW_3_Pin;   // turn off row 3
		ROW_4_GPIO_Port->BRR = ROW_4_Pin;	// turn off row 4
		if (COLUMN_3_GPIO_Port->IDR & COLUMN_3_Pin)
		{
			key_pressed = 0x06; // if column 3 is still high -> column 3 + row 2 = key 6
			break;
		}

		ROW_1_GPIO_Port->BRR = ROW_1_Pin;	// turn off row 1
		ROW_2_GPIO_Port->BRR = ROW_2_Pin; 	// turn off row 2
		ROW_3_GPIO_Port->BSRR = ROW_3_Pin;  // turn on row 3
		ROW_4_GPIO_Port->BRR = ROW_4_Pin;	// turn off row 4
		if (COLUMN_3_GPIO_Port->IDR & COLUMN_3_Pin)
		{
			key_pressed = 0x09; // if column 3 is still high -> column 3 + row 3 = key 9
			break;
		}

		ROW_1_GPIO_Port->BRR = ROW_1_Pin;	// turn off row 1
		ROW_2_GPIO_Port->BRR = ROW_2_Pin;	// turn off row 2
		ROW_3_GPIO_Port->BRR = ROW_3_Pin;	// turn off row 3
		ROW_4_GPIO_Port->BSRR = ROW_4_Pin;	// turn on row 4
		if (COLUMN_3_GPIO_Port->IDR & COLUMN_3_Pin)
		{
			key_pressed = 0x10; // if column 3 is still high -> column 3 + row 4 = key #
			break;
		}
		break;

	case COLUMN_4_Pin:
		ROW_1_GPIO_Port->BSRR = ROW_1_Pin; // turn on row 1
		ROW_2_GPIO_Port->BRR = ROW_2_Pin;  // turn off row 2
		ROW_3_GPIO_Port->BRR = ROW_3_Pin;  // turn off row 3
		ROW_4_GPIO_Port->BRR = ROW_4_Pin;  // turn off row 4
		if (COLUMN_4_GPIO_Port->IDR & COLUMN_4_Pin)
		{
			key_pressed = 0x0A; // if column 4 is still high -> column 4 + row 1 = key A
			break;
		}

		ROW_1_GPIO_Port->BRR = ROW_1_Pin; 	// turn off row 1
		ROW_2_GPIO_Port->BSRR = ROW_2_Pin; // turn on row 2
		ROW_3_GPIO_Port->BRR = ROW_3_Pin;  // turn off row 3
		ROW_4_GPIO_Port->BRR = ROW_4_Pin;
		if (COLUMN_4_GPIO_Port->IDR & COLUMN_4_Pin)
		{
			key_pressed = 0x0B; // if column 4 is still high -> column 4 + row 2 = key B
			break;
		}

		ROW_1_GPIO_Port->BRR = ROW_1_Pin; 	// turn off row 1
		ROW_2_GPIO_Port->BRR = ROW_2_Pin; // turn on row 2
		ROW_3_GPIO_Port->BSRR = ROW_3_Pin;  // turn off row 3
		ROW_4_GPIO_Port->BRR = ROW_4_Pin;
		if (COLUMN_4_GPIO_Port->IDR & COLUMN_4_Pin)
		{
			key_pressed = 0x0C; // if column 4 is still high -> column 4 + row 3 = key C
			break;
		}

		ROW_1_GPIO_Port->BRR = ROW_1_Pin; 	// turn off row 1
		ROW_2_GPIO_Port->BRR = ROW_2_Pin; // turn on row 2
		ROW_3_GPIO_Port->BRR = ROW_3_Pin;  // turn off row 3
		ROW_4_GPIO_Port->BSRR = ROW_4_Pin;	// turn on row 4
		if (COLUMN_4_GPIO_Port->IDR & COLUMN_4_Pin)
		{
			key_pressed = 0x0D; // if column 4 is still high -> column 4 + row 4 = key D
			break;
		}
		break;

		default:
			/* This should not be reached */
			printf("Unknown column: %x\r\n", column_to_evaluate);
		break;
	}

	return key_pressed; // invalid: 0xFF, valid:[0x00-0x0F]
}

