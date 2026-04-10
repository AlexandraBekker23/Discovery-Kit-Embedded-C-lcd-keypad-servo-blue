/*
 * servo.h
 *
 *  Created on: Mar 26, 2026
 *      Author: bylka
 */

#ifndef INC_SERVO_HPP_
#define INC_SERVO_HPP_

#include "main.h"
#include "stm32l4xx_hal.h"

enum {
	SERVO_RIGHTPOSITION = 1000,
	SERVO_MIDPOSITION = 2500,
	SERVO_LEFTPOSITION = 4100,
};

class Servo
{
	private:
		TIM_HandleTypeDef* _htim;
		uint32_t _channel;
	public:
		Servo(TIM_HandleTypeDef* htim, uint32_t channel);
		void Start();
		void TurnShaft(uint32_t position);
};



#endif /* INC_SERVO_HPP_ */
