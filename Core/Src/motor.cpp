/*
 * motor.cpp
 *
 *  Created on: Jun 9, 2026
 *      Author: bylka
 */

#include "motor.hpp"

Motor::Motor(TIM_HandleTypeDef* _htim,
        uint32_t _pwmChannel,
        GPIO_TypeDef* _in1Port, uint16_t _in1Pin,
        GPIO_TypeDef* _in2Port, uint16_t _in2Pin) {
	htim = _htim;
	pwmChannel = _pwmChannel;
	in1Port = _in1Port;
	in1Pin = _in1Pin;
	in2Port = _in2Port;
	in2Pin = _in2Pin;

	HAL_TIM_PWM_Start(htim, pwmChannel);
}

void Motor::MoveForward(uint32_t speed)
{
// Напрямок 1
HAL_GPIO_WritePin(in1Port, in1Pin, GPIO_PIN_SET);
HAL_GPIO_WritePin(in2Port, in2Pin, GPIO_PIN_RESET);

// Встановлюємо швидкість (Duty Cycle)
__HAL_TIM_SET_COMPARE(htim, pwmChannel, speed);
}

void Motor::Reverse(uint32_t speed)
{
// Напрямок 2 (протилежний)
HAL_GPIO_WritePin(in1Port, in1Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(in2Port, in2Pin, GPIO_PIN_SET);

// Встановлюємо швидкість (Duty Cycle)
__HAL_TIM_SET_COMPARE(htim, pwmChannel, speed);
}

void Motor::Stop(void)
{
// Обидва піни в нуль — мотор котиться по інерції або гальмує
HAL_GPIO_WritePin(in1Port, in1Pin, GPIO_PIN_RESET);
HAL_GPIO_WritePin(in2Port, in2Pin, GPIO_PIN_RESET);

// Швидкість в 0
__HAL_TIM_SET_COMPARE(htim, pwmChannel, MOTOR_STOP);
}
