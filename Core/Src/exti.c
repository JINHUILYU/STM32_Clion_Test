//
// Created by Lyu on 2023/10/23.
//
#include "exti.h"
#include "key.h"
#include "beep.h"
#include "led.h"

/**
 * @brief	�ⲿ�жϳ�ʼ������
 *
 * @param   void
 *
 * @return  void
 */
// ��ʼ��������MX_GPIO_Init()�еĲ���������ͬ
void EXTI_Init(void) {
    /*
        KEY0 	- PD10
        KEY1 	- PD9
        KEY2 	- PD8
        WK_UP 	- PC13
    */
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOC_CLK_ENABLE(); // ����GPIOCʱ��
    __HAL_RCC_GPIOD_CLK_ENABLE(); // ����GPIODʱ��

    GPIO_Initure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10; // PD8.9.10 | ��ʾ��λ������
    GPIO_Initure.Mode = GPIO_MODE_IT_FALLING; // �½��ش���GPIO_MODE_IT_FALLING
    GPIO_Initure.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOD, &GPIO_Initure);

    GPIO_Initure.Pin = GPIO_PIN_13; // PC13
    GPIO_Initure.Mode = GPIO_MODE_IT_RISING; // �����ش���
    GPIO_Initure.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOC, &GPIO_Initure);

    // �ж���8,9
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0); // ������ռ���ȼ�Ϊ2�������ȼ�Ϊ0
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn); // ʹ���ж���0

    // �ж���10,13
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 1); // ������ռ���ȼ�Ϊ2�������ȼ�Ϊ1
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn); // ʹ���ж���13
}

/**
 * @brief	EXTI9_5�жϷ�����
 *
 * @param   void
 *
 * @return  void
 */
void EXTI9_5_IRQHandler(void);


/**
 * @brief	EXTI15_10�жϷ�����
 *
 * @param   void
 *
 * @return  void
 */
void EXTI15_10_IRQHandler(void);


/**
 * @brief	�ⲿ�жϻص��������жϷ����������Ҫ��������,��HAL�������е��ⲿ�жϷ�����������ô˺���
 *
 * @param   GPIO_Pin	�ж����ź�
 *
 * @return  void
 */
// �ⲿ�жϻص�����
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//    HAL_Delay(50); // ����
//    switch (GPIO_Pin) {
//        case GPIO_PIN_13: // ���Ʒ�����״̬��ת
//            if (WK_UP == 1) // �������£��������ߵ�ƽ��Ч
//                BEEP_TogglePin;
//            break;
//
//        case GPIO_PIN_8: // ����LED_B��״̬��ת
//            if (KEY2 == 0) // �������£�LED_B�͵�ƽ��Ч
//                LED_B_TogglePin;
//            break;
//
//        case GPIO_PIN_9: // ����LED_G��״̬��ת
//            if (KEY1 == 0) // �������£�LED_G�͵�ƽ��Ч
//                LED_G_TogglePin;
//            break;
//
//        case GPIO_PIN_10: // ����LED_R��״̬��ת
//            if (KEY0 == 0) // �������£�LED_R�͵�ƽ��Ч
//                LED_R_TogglePin;
//            break;
//        default:
//            break;
//    }
}



