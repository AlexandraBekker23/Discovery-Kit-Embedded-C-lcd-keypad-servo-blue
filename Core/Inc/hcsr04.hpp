/*
 * hcsr04.hpp
 *
 *  Created on: Apr 16, 2026
 *      Author: bylka
 */

#ifndef INC_HCSR04_HPP_
#define INC_HCSR04_HPP_


#include "main.h"
#include "stm32l4xx_hal.h"

class HCSR04 {
private:
    TIM_HandleTypeDef* htim;
    uint32_t distanceCM;

public:
    HCSR04(TIM_HandleTypeDef* _htim);

    void Start();
    uint32_t GetDistance();
};



#endif /* INC_HCSR04_HPP_ */
