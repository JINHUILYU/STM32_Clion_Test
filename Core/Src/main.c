/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "beep.h"
#include "key.h"
#include "led.h"
#include "stdio.h"
#include "retarget.h"
#include <string.h>

#define RXBUFFERSIZE  256 // �������ֽ���
char RxBuffer[RXBUFFERSIZE]; // ���ջ�����
uint8_t aRxBuffer; // �����жϻ���
uint8_t Uart1_Rx_Cnt = 0; // ���ջ������

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    /* USER CODE BEGIN 1 */
    u8 key;
    u8 len;
    u16 times = 0;
    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    /* USER CODE BEGIN 2 */
    LED_Init(); // ��ʼ��LED
    BEEP_Init(); // ��ʼ��������
    KEY_Init(); // ��ʼ������
    RetargetInit(&huart1); // ��ʼ���ض���
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    HAL_UART_Receive_IT(&huart1, (uint8_t *) &aRxBuffer, 1); // �����ж�
    while (1) {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
#ifdef Exp1
        /**
         * ʵ��һ��LED��˸
         */
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET); // PE7��1�������
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET); // PE8��1���̵���
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET); // PE9��1��������
        HAL_Delay(1000); // ��ʱ1000ms
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET); // PE7��0�������
        HAL_Delay(1000); // ��ʱ1000ms
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET); // PE7��1�������
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET); // PE8��1���̵���
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET); // PE9��1��������
        HAL_Delay(1000); // ��ʱ1000ms
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET); // PE8��0���̵���
        HAL_Delay(1000); // ��ʱ1000ms
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET); // PE7��1�������
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET); // PE8��1���̵���
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET); // PE9��1��������
        HAL_Delay(1000); // ��ʱ1000ms
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET); // PE9��0��������
        HAL_Delay(1000); // ��ʱ1000ms
#endif

#ifdef Exp2
        /**
         * ʵ���������������
         */
        BEEP(1);
        HAL_Delay(500); // ��ʱ500ms
        BEEP(0);
        HAL_Delay(1000); // ��ʱ1000ms
#endif

#ifdef Exp3
        /**
         * ʵ��������������LED��
         */
        key = KEY_Scan(0);          //����ɨ�裬��֧��������

        switch (key) {
            case WKUP_PRES:        //���Ʒ�����״̬��ת
                BEEP_TogglePin;
                break;

            case KEY2_PRES:        //����LED_B���״̬��ת
                LED_B_TogglePin;
                break;

            case KEY1_PRES:        //����LED_G�̵�״̬��ת
                LED_G_TogglePin;
                break;

            case KEY0_PRES:        //����LED_R����״̬��ת
                LED_R_TogglePin;
                break;
            default:
                break;
        }

        HAL_Delay(10); // ��ʱ10ms
#endif

#ifdef Exp4
        /**
         * ʵ���ģ�����ͨ��
         */
        times++;
        if (times % 5000 == 0) {
            printf("�ȴ���������...\r\n");
        }
        if (times % 200 == 0) {
            printf("���������ݣ��Իس�������\r\n");
        }
        if (times % 30 == 0) {
            LED_B_TogglePin; // LED��˸����ʾ������������
        }
        HAL_Delay(10); // ��ʱ10ms
#endif

#ifdef Exp5
        printf("Hello, world!\r\n"); // �س�����
        HAL_Delay(1000); // ��ʱ10ms
#endif

    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
    RCC_OscInitStruct.MSIState = RCC_MSI_ON;
    RCC_OscInitStruct.MSICalibrationValue = 0;
    RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    /* Prevent unused argument(s) compilation warning */
    UNUSED(huart);
    /* NOTE: This function Should not be modified, when the callback is needed,
             the HAL_UART_TxCpltCallback could be implemented in the user file
     */

    if (Uart1_Rx_Cnt >= 255)  //����ж�
    {
        Uart1_Rx_Cnt = 0;
        memset(RxBuffer, 0x00, sizeof(RxBuffer));
        HAL_UART_Transmit(&huart1, (uint8_t *) "�������", 10, 0xFFFF);
    } else {
        RxBuffer[Uart1_Rx_Cnt++] = aRxBuffer;   //��������ת��

        if ((RxBuffer[Uart1_Rx_Cnt - 1] == 0x0A) && (RxBuffer[Uart1_Rx_Cnt - 2] == 0x0D)) //�жϽ���λ
        {
            printf("������������ǣ�");
            HAL_UART_Transmit(&huart1, (uint8_t *) &RxBuffer, Uart1_Rx_Cnt, 0xFFFF); //���յ�����Ϣ���ͳ�ȥ
            while (HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);//���UART���ͽ���
//            if (strstr(RxBuffer, "LED=0")) {
//                HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET); // �����
//                printf("LED��\r\n");
//            } else if (strstr(RxBuffer, "LED=1")) {
//                HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET); // �����
//                printf("LED��\r\n");
//            }
            printf("\r\n"); // ���뻻��
            Uart1_Rx_Cnt = 0;
            memset(RxBuffer, 0x00, sizeof(RxBuffer)); //�������
        }
    }
    HAL_UART_Receive_IT(&huart1, (uint8_t *) &aRxBuffer, 1);   //�ٿ��������ж�
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
