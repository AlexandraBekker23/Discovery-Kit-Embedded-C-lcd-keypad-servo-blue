/*
 * hcsr04.cpp
 *
 *  Created on: Apr 16, 2026
 *      Author: bylka
 */
#include "hcsr04.hpp"

HCSR04::HCSR04(TIM_HandleTypeDef* _htim) : htim(_htim), distanceCM(0) {}

void HCSR04::Start() {
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_3);

    HAL_TIM_IC_Start(htim, TIM_CHANNEL_1);
}


uint32_t HCSR04::GetDistance(void) {
    if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC1)) {

        uint32_t pulseWidth = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

        if (pulseWidth > 0) {
            distanceCM = pulseWidth / 58;
        }
        __HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_CC1);
    }
    return distanceCM;
}

