//
// Created by Lyu on 2023/10/23.
//
#include "exti.h"
#include "key.h"
#include "beep.h"
#include "led.h"

/**
 * @brief	外部中断初始化函数
 *
 * @param   void
 *
 * @return  void
 */
// 初始化内容与MX_GPIO_Init()中的部分内容相同
void EXTI_Init(void) {
    /*
        KEY0 	- PD10
        KEY1 	- PD9
        KEY2 	- PD8
        WK_UP 	- PC13
    */
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOC_CLK_ENABLE(); // 开启GPIOC时钟
    __HAL_RCC_GPIOD_CLK_ENABLE(); // 开启GPIOD时钟

    GPIO_Initure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10; // PD8.9.10 | 表示按位或运算
    GPIO_Initure.Mode = GPIO_MODE_IT_FALLING; // 下降沿触发GPIO_MODE_IT_FALLING
    GPIO_Initure.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOD, &GPIO_Initure);

    GPIO_Initure.Pin = GPIO_PIN_13; // PC13
    GPIO_Initure.Mode = GPIO_MODE_IT_RISING; // 上升沿触发
    GPIO_Initure.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOC, &GPIO_Initure);

    // 中断线8,9
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0); // 设置抢占优先级为2，子优先级为0
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn); // 使能中断线0

    // 中断线10,13
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 1); // 设置抢占优先级为2，子优先级为1
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn); // 使能中断线13
}

/**
 * @brief	EXTI9_5中断服务函数
 *
 * @param   void
 *
 * @return  void
 */
void EXTI9_5_IRQHandler(void);


/**
 * @brief	EXTI15_10中断服务函数
 *
 * @param   void
 *
 * @return  void
 */
void EXTI15_10_IRQHandler(void);


/**
 * @brief	外部中断回调函数，中断服务程序中需要做的事情,在HAL库中所有的外部中断服务函数都会调用此函数
 *
 * @param   GPIO_Pin	中断引脚号
 *
 * @return  void
 */
// 外部中断回调函数
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//    HAL_Delay(50); // 消抖
//    switch (GPIO_Pin) {
//        case GPIO_PIN_13: // 控制蜂鸣器状态翻转
//            if (WK_UP == 1) // 按键按下，蜂鸣器高电平有效
//                BEEP_TogglePin;
//            break;
//
//        case GPIO_PIN_8: // 控制LED_B灯状态翻转
//            if (KEY2 == 0) // 按键按下，LED_B低电平有效
//                LED_B_TogglePin;
//            break;
//
//        case GPIO_PIN_9: // 控制LED_G灯状态翻转
//            if (KEY1 == 0) // 按键按下，LED_G低电平有效
//                LED_G_TogglePin;
//            break;
//
//        case GPIO_PIN_10: // 控制LED_R灯状态翻转
//            if (KEY0 == 0) // 按键按下，LED_R低电平有效
//                LED_R_TogglePin;
//            break;
//        default:
//            break;
//    }
}



