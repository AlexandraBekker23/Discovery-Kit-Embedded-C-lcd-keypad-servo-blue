/*
 * lcd.h
 *
 *  Created on: Apr 2, 2026
 *      Author: bylka
 */

#ifndef INC_LCD_HPP_
#define INC_LCD_HPP_

#include "stm32l4xx_hal.h"

class LCD
{
	private:
		I2C_HandleTypeDef* hi2c;
		uint8_t addr;
		void WriteByte(uint8_t byte, uint8_t rs_bit);

	public:
		LCD(I2C_HandleTypeDef* h, uint8_t address);
		void Init();
		void SetCursor(uint8_t row, uint8_t col);
		void Print(char data);
		void Print(const char* pData);
		void Print(uint32_t data);
		void Clear();
};


#endif /* INC_LCD_HPP_ */
