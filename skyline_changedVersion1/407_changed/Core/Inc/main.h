/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define camera15_Pin GPIO_PIN_5
#define camera15_GPIO_Port GPIOE
#define camera16_Pin GPIO_PIN_6
#define camera16_GPIO_Port GPIOE
#define camera1_Pin GPIO_PIN_4
#define camera1_GPIO_Port GPIOA
#define camera2_Pin GPIO_PIN_6
#define camera2_GPIO_Port GPIOA
#define camera6_Pin GPIO_PIN_6
#define camera6_GPIO_Port GPIOC
#define camera5_Pin GPIO_PIN_7
#define camera5_GPIO_Port GPIOC
#define camera7_Pin GPIO_PIN_8
#define camera7_GPIO_Port GPIOC
#define camera8_Pin GPIO_PIN_9
#define camera8_GPIO_Port GPIOC
#define camera3_Pin GPIO_PIN_8
#define camera3_GPIO_Port GPIOA
#define camera9_Pin GPIO_PIN_12
#define camera9_GPIO_Port GPIOC
#define camera10_Pin GPIO_PIN_6
#define camera10_GPIO_Port GPIOD
#define camera11_Pin GPIO_PIN_7
#define camera11_GPIO_Port GPIOD
#define camera13_Pin GPIO_PIN_9
#define camera13_GPIO_Port GPIOG
#define camera12_Pin GPIO_PIN_15
#define camera12_GPIO_Port GPIOG
#define camera4_Pin GPIO_PIN_6
#define camera4_GPIO_Port GPIOB
#define camera14_Pin GPIO_PIN_7
#define camera14_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
