//
// Created by Lyu on 2023/10/21.
//

#ifndef TEST_BEEP_H
#define TEST_BEEP_H
#include "main.h"

#define BEEP(n)	(n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET))
#define BEEP_TogglePin	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_2)


void BEEP_Init(void);
#endif //TEST_BEEP_H
