//
// Created by Lyu on 2023/10/21.
//
#include "led.h"


/**
 * @brief	LED IO初始化函数
 *
 * @param   void
 *
 * @return  void
 */
void LED_Init(void) {
    /*
        LED-R	PE7
        LED-G	PE8
        LED-B	PE9
    */
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_GPIOE_CLK_ENABLE(); // 使能GPIOE时钟
    // 初始化结构体 GPIO_InitStruct
    GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9; // PE7.8.9
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // 推挽输出
    GPIO_InitStruct.Pull = GPIO_PULLUP; // 上拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // 高速
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct); // 初始化GPIO

    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_SET); // 默认关闭LED
}
