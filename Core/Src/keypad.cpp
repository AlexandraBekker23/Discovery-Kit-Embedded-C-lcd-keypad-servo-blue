/*
 * keypad.cpp
 *
 *  Created on: Apr 9, 2026
 *      Author: bylka
 */

#include "keypad.hpp"
#include "lcd.hpp"

const char keypadMatrix[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

Keypad::Keypad(pinStruct_t* rPins, pinStruct_t* cPins) : rows(rPins), cols(cPins){

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	for(int i = 0; i < NUMBER_OF_ROWS; i++) {
		GPIO_InitStruct.Pin = rows[i].selectedPin;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(rows[i].port, &GPIO_InitStruct);
		HAL_GPIO_WritePin(rows[i].port, rows[i].selectedPin, GPIO_PIN_SET);
	}
	for(int i = 0; i < NUMBER_OF_COLUMNS; i++) {
		GPIO_InitStruct.Pin = cols[i].selectedPin;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		HAL_GPIO_Init(cols[i].port, &GPIO_InitStruct);
	}
}

char Keypad::GetKey(void) {
	for(int r = 0; r < NUMBER_OF_ROWS; r++) {
		HAL_GPIO_WritePin(rows[r].port, rows[r].selectedPin, GPIO_PIN_RESET);
		for(int c = 0; c < NUMBER_OF_COLUMNS; c++) {
			if(HAL_GPIO_ReadPin(cols[c].port, cols[c].selectedPin) == GPIO_PIN_RESET) {
				char pressedKey = keypadMatrix[r][c];
				                HAL_GPIO_WritePin(rows[r].port, rows[r].selectedPin, GPIO_PIN_SET);
				                return pressedKey;
			}
		}
		HAL_GPIO_WritePin(rows[r].port, rows[r].selectedPin, GPIO_PIN_SET);
	}
	return 0;
}


