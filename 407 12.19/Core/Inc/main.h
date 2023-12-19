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
#define MOTOR1A_Pin GPIO_PIN_0
#define MOTOR1A_GPIO_Port GPIOF
#define MOTOR1B_Pin GPIO_PIN_1
#define MOTOR1B_GPIO_Port GPIOF
#define MOTOR2A_Pin GPIO_PIN_2
#define MOTOR2A_GPIO_Port GPIOF
#define MOTOR2B_Pin GPIO_PIN_3
#define MOTOR2B_GPIO_Port GPIOF
#define MOTOR3A_Pin GPIO_PIN_4
#define MOTOR3A_GPIO_Port GPIOF
#define MOTOR3B_Pin GPIO_PIN_5
#define MOTOR3B_GPIO_Port GPIOF
#define STEPPEROPP_Pin GPIO_PIN_5
#define STEPPEROPP_GPIO_Port GPIOC
#define MOTOR4A_Pin GPIO_PIN_11
#define MOTOR4A_GPIO_Port GPIOF
#define FREEOPP1_Pin GPIO_PIN_12
#define FREEOPP1_GPIO_Port GPIOB
#define FREEOPP2_Pin GPIO_PIN_13
#define FREEOPP2_GPIO_Port GPIOB
#define FREEOPP5_Pin GPIO_PIN_8
#define FREEOPP5_GPIO_Port GPIOD
#define FREEOPP6_Pin GPIO_PIN_9
#define FREEOPP6_GPIO_Port GPIOD
#define FREEOPP7_Pin GPIO_PIN_10
#define FREEOPP7_GPIO_Port GPIOD
#define FREEOPP8_Pin GPIO_PIN_11
#define FREEOPP8_GPIO_Port GPIOD
#define FREEOPP3_Pin GPIO_PIN_10
#define FREEOPP3_GPIO_Port GPIOC
#define FREEOPP4_Pin GPIO_PIN_11
#define FREEOPP4_GPIO_Port GPIOC
#define camera13_Pin GPIO_PIN_9
#define camera13_GPIO_Port GPIOG
#define camera12_Pin GPIO_PIN_15
#define camera12_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
