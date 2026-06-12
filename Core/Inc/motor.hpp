/*
 * motor.hpp
 *
 *  Created on: May 19, 2026
 *      Author: bylka
 */


#ifndef INC_MOTOR_HPP_
#define INC_MOTOR_HPP_

#include "main.h"

enum {
	MOTOR_STOP = 0,
	MOTOR_ONEEIGHTSPEED = 2500,
	MOTOR_QUARTERSPEED = 5000,
	MOTOR_HALFSPEED = 10000,
	MOTOR_FULLSPEED = 20000
};

class Motor {
	private:
		TIM_HandleTypeDef* htim;
		uint32_t pwmChannel;
	    GPIO_TypeDef* in1Port;
	    uint16_t in1Pin;
	    GPIO_TypeDef* in2Port;
	    uint16_t in2Pin;
	public:
		Motor(TIM_HandleTypeDef* _htim, uint32_t _pwmChannel,
					GPIO_TypeDef* _in1Port, uint16_t _in1Pin,
					GPIO_TypeDef* _in2Port, uint16_t _in2Pin);
		void MoveForward(uint32_t speed);
		void Reverse(uint32_t speed);
		void Stop(void);
};



#endif /* INC_MOTOR_HPP_ */
