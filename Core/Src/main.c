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

#define RXBUFFERSIZE  256 // 最大接收字节数
char RxBuffer[RXBUFFERSIZE]; // 接收缓冲区
uint8_t aRxBuffer; // 接收中断缓冲
uint8_t Uart1_Rx_Cnt = 0; // 接收缓冲计数

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
    LED_Init(); // 初始化LED
    BEEP_Init(); // 初始化蜂鸣器
    KEY_Init(); // 初始化按键
    RetargetInit(&huart1); // 初始化重定向
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    HAL_UART_Receive_IT(&huart1, (uint8_t *) &aRxBuffer, 1); // 接收中断
    while (1) {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
#ifdef Exp1
        /**
         * 实验一：LED闪烁
         */
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET); // PE7置1，红灯灭
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET); // PE8置1，绿灯灭
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET); // PE9置1，蓝灯灭
        HAL_Delay(1000); // 延时1000ms
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET); // PE7置0，红灯亮
        HAL_Delay(1000); // 延时1000ms
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET); // PE7置1，红灯灭
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET); // PE8置1，绿灯灭
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET); // PE9置1，蓝灯灭
        HAL_Delay(1000); // 延时1000ms
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET); // PE8置0，绿灯亮
        HAL_Delay(1000); // 延时1000ms
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET); // PE7置1，红灯灭
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET); // PE8置1，绿灯灭
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET); // PE9置1，蓝灯灭
        HAL_Delay(1000); // 延时1000ms
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET); // PE9置0，蓝灯亮
        HAL_Delay(1000); // 延时1000ms
#endif

#ifdef Exp2
        /**
         * 实验二：蜂鸣器发声
         */
        BEEP(1);
        HAL_Delay(500); // 延时500ms
        BEEP(0);
        HAL_Delay(1000); // 延时1000ms
#endif

#ifdef Exp3
        /**
         * 实验三：按键控制LED灯
         */
        key = KEY_Scan(0);          //按键扫描，不支持连续按

        switch (key) {
            case WKUP_PRES:        //控制蜂鸣器状态翻转
                BEEP_TogglePin;
                break;

            case KEY2_PRES:        //控制LED_B红灯状态翻转
                LED_B_TogglePin;
                break;

            case KEY1_PRES:        //控制LED_G绿灯状态翻转
                LED_G_TogglePin;
                break;

            case KEY0_PRES:        //控制LED_R蓝灯状态翻转
                LED_R_TogglePin;
                break;
            default:
                break;
        }

        HAL_Delay(10); // 延时10ms
#endif

#ifdef Exp4
        /**
         * 实验四：串口通信
         */
        times++;
        if (times % 5000 == 0) {
            printf("等待接收数据...\r\n");
        }
        if (times % 200 == 0) {
            printf("请输入数据，以回车键结束\r\n");
        }
        if (times % 30 == 0) {
            LED_B_TogglePin; // LED闪烁，表示程序正在运行
        }
        HAL_Delay(10); // 延时10ms
#endif

#ifdef Exp5
        printf("Hello, world!\r\n"); // 回车换行
        HAL_Delay(1000); // 延时10ms
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

    if (Uart1_Rx_Cnt >= 255)  //溢出判断
    {
        Uart1_Rx_Cnt = 0;
        memset(RxBuffer, 0x00, sizeof(RxBuffer));
        HAL_UART_Transmit(&huart1, (uint8_t *) "数据溢出", 10, 0xFFFF);
    } else {
        RxBuffer[Uart1_Rx_Cnt++] = aRxBuffer;   //接收数据转存

        if ((RxBuffer[Uart1_Rx_Cnt - 1] == 0x0A) && (RxBuffer[Uart1_Rx_Cnt - 2] == 0x0D)) //判断结束位
        {
            printf("您输入的数据是：");
            HAL_UART_Transmit(&huart1, (uint8_t *) &RxBuffer, Uart1_Rx_Cnt, 0xFFFF); //将收到的信息发送出去
            while (HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);//检测UART发送结束
//            if (strstr(RxBuffer, "LED=0")) {
//                HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET); // 红灯亮
//                printf("LED亮\r\n");
//            } else if (strstr(RxBuffer, "LED=1")) {
//                HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET); // 红灯灭
//                printf("LED灭\r\n");
//            }
            printf("\r\n"); // 插入换行
            Uart1_Rx_Cnt = 0;
            memset(RxBuffer, 0x00, sizeof(RxBuffer)); //清空数组
        }
    }
    HAL_UART_Receive_IT(&huart1, (uint8_t *) &aRxBuffer, 1);   //再开启接收中断
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
