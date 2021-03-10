/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f0xx_hal.h"

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
#define button1_Pin GPIO_PIN_0
#define button1_GPIO_Port GPIOA
#define button1_EXTI_IRQn EXTI0_1_IRQn
#define button2_Pin GPIO_PIN_1
#define button2_GPIO_Port GPIOA
#define button2_EXTI_IRQn EXTI0_1_IRQn
#define button3_Pin GPIO_PIN_2
#define button3_GPIO_Port GPIOA
#define button3_EXTI_IRQn EXTI2_3_IRQn
#define button4_Pin GPIO_PIN_3
#define button4_GPIO_Port GPIOA
#define button4_EXTI_IRQn EXTI2_3_IRQn
#define button5_Pin GPIO_PIN_4
#define button5_GPIO_Port GPIOA
#define button5_EXTI_IRQn EXTI4_15_IRQn
#define button6_Pin GPIO_PIN_5
#define button6_GPIO_Port GPIOA
#define button6_EXTI_IRQn EXTI4_15_IRQn
#define button7_Pin GPIO_PIN_6
#define button7_GPIO_Port GPIOA
#define button7_EXTI_IRQn EXTI4_15_IRQn
#define button8_Pin GPIO_PIN_7
#define button8_GPIO_Port GPIOA
#define button8_EXTI_IRQn EXTI4_15_IRQn
#define led1_Pin GPIO_PIN_0
#define led1_GPIO_Port GPIOB
#define led2_Pin GPIO_PIN_1
#define led2_GPIO_Port GPIOB
#define led3_Pin GPIO_PIN_2
#define led3_GPIO_Port GPIOB
#define button9_Pin GPIO_PIN_8
#define button9_GPIO_Port GPIOA
#define button9_EXTI_IRQn EXTI4_15_IRQn
#define button10_Pin GPIO_PIN_9
#define button10_GPIO_Port GPIOA
#define button10_EXTI_IRQn EXTI4_15_IRQn
#define led4_Pin GPIO_PIN_3
#define led4_GPIO_Port GPIOB
#define led5_Pin GPIO_PIN_4
#define led5_GPIO_Port GPIOB
#define led6_Pin GPIO_PIN_5
#define led6_GPIO_Port GPIOB
#define led7_Pin GPIO_PIN_6
#define led7_GPIO_Port GPIOB
#define led8_Pin GPIO_PIN_7
#define led8_GPIO_Port GPIOB
#define led9_Pin GPIO_PIN_8
#define led9_GPIO_Port GPIOB
#define led10_Pin GPIO_PIN_9
#define led10_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
