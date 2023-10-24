//
// Created by Lyu on 2023/10/21.
//

#ifndef TEST_LED_H
#define TEST_LED_H

#include "main.h"
// LED-R	PE7
// ����nֵ������LED������
#define LED_R(n)            (n ? HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET))
// ��תLED
#define LED_R_TogglePin     HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_7)

// LED-G	PE8
// ����nֵ������LED������
#define LED_G(n)            (n ? HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET))
// ��תLED
#define LED_G_TogglePin     HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8)

// LED-B	PE9
// ����nֵ������LED������
#define LED_B(n)            (n ? HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET))
// ��תLED
#define LED_B_TogglePin     HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9)

/**
 * @brief	LED IO��ʼ������
 */
void LED_Init(void);

#endif //TEST_LED_H
