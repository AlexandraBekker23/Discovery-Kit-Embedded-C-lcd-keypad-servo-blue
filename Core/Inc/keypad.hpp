/*
 * keypad.hpp
 *
 *  Created on: Apr 9, 2026
 *      Author: bylka
 */

#ifndef INC_KEYPAD_HPP_
#define INC_KEYPAD_HPP_

#include "stm32l4xx_hal.h"

#define NUMBER_OF_ROWS      4
#define NUMBER_OF_COLUMNS   3

struct pinStruct_t {
	GPIO_TypeDef* port;
	uint16_t selectedPin;
};

class Keypad {
	private:
		pinStruct_t* rows;
		//int row_num;
		pinStruct_t* cols;
		//int col_num;
//		char keys[4][3] = {
//			{'1', '2', '3'},
//			{'4', '5', '6'},
//			{'7', '8', '9'},
//			{'*', '0', '#'}
//		};
	public:
		Keypad(pinStruct_t* rPins, pinStruct_t* cPins);
		char GetKey(void);
};



#endif /* INC_KEYPAD_HPP_ */
