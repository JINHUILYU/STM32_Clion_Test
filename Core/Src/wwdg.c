/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    wwdg.c
  * @brief   This file provides code for the configuration
  *          of the WWDG instances.
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
#include "wwdg.h"

/* USER CODE BEGIN 0 */
#include "led.h"
/* USER CODE END 0 */

WWDG_HandleTypeDef hwwdg;

/* WWDG init function */
void MX_WWDG_Init(void)
{

  /* USER CODE BEGIN WWDG_Init 0 */

  /* USER CODE END WWDG_Init 0 */

  /* USER CODE BEGIN WWDG_Init 1 */

  /* USER CODE END WWDG_Init 1 */
  hwwdg.Instance = WWDG;
  hwwdg.Init.Prescaler = WWDG_PRESCALER_8;
  hwwdg.Init.Window = 95;
  hwwdg.Init.Counter = 127;
  hwwdg.Init.EWIMode = WWDG_EWI_DISABLE;
  if (HAL_WWDG_Init(&hwwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN WWDG_Init 2 */
    __HAL_WWDG_ENABLE_IT(&hwwdg, WWDG_IT_EWI);	//开启唤醒中断
  /* USER CODE END WWDG_Init 2 */

}

void HAL_WWDG_MspInit(WWDG_HandleTypeDef* wwdgHandle)
{

  if(wwdgHandle->Instance==WWDG)
  {
  /* USER CODE BEGIN WWDG_MspInit 0 */

  /* USER CODE END WWDG_MspInit 0 */
    /* WWDG clock enable */
    __HAL_RCC_WWDG_CLK_ENABLE();

    /* WWDG interrupt Init */
    HAL_NVIC_SetPriority(WWDG_IRQn, 2, 3);
    HAL_NVIC_EnableIRQ(WWDG_IRQn);
  /* USER CODE BEGIN WWDG_MspInit 1 */

  /* USER CODE END WWDG_MspInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/**
 * @brief	窗口看门狗中断服务函数
 *
 * @param   void
 *
 * @return  void
 */
void WWDG_IRQHandler(void);

/**
 * @brief	中断服务函数处理过程
 *			此函数会被HAL_WWDG_IRQHandler()调用
 *
 * @param   hwwdg	窗口看门狗句柄
 *
 * @return  void
 */
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef* WWDG_Handler)
{
    HAL_WWDG_Refresh(&hwwdg); // 更新窗口看门狗值
    LED_B_TogglePin;
}
/* USER CODE END 1 */
