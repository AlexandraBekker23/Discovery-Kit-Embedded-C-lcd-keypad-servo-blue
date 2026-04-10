
#include <servo.hpp>

Servo::Servo(TIM_HandleTypeDef* htim, uint32_t channel)
{
	_htim = htim;
	_channel = channel;
}

void Servo::Start()
{
	HAL_TIM_PWM_Start(_htim, _channel);
}

void Servo::TurnShaft(uint32_t position)
{
	__HAL_TIM_SET_COMPARE(_htim, _channel, position);
}
