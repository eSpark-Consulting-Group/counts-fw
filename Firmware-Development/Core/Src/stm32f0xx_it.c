/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

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
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_FS;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line 0 and 1 interrupts.
  */
void EXTI0_1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_1_IRQn 0 */
  if (HAL_GPIO_ReadPin(GPIOA, button1_Pin) == 0) {
	  HAL_GPIO_WritePin(GPIOB, led1_Pin, GPIO_PIN_SET);
	  CDC_Transmit_FS("1", sizeof ("1"));
  }

  else { HAL_GPIO_WritePin(GPIOB, led1_Pin, GPIO_PIN_RESET); }
  /* USER CODE END EXTI0_1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI0_1_IRQn 1 */
  if (HAL_GPIO_ReadPin(GPIOA, button2_Pin) == 0) {
  	HAL_GPIO_WritePin(GPIOB, led2_Pin, GPIO_PIN_SET);
  	CDC_Transmit_FS("2", sizeof ("2"));
  }

  else { HAL_GPIO_WritePin(GPIOB, led2_Pin, GPIO_PIN_RESET); }
  /* USER CODE END EXTI0_1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line 2 and 3 interrupts.
  */
void EXTI2_3_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI2_3_IRQn 0 */
  if (HAL_GPIO_ReadPin(GPIOA, button3_Pin) == 0) {
	  HAL_GPIO_WritePin(GPIOB, led3_Pin, GPIO_PIN_SET);
	  CDC_Transmit_FS("3", sizeof ("3"));
  }

  else { HAL_GPIO_WritePin(GPIOB, led3_Pin, GPIO_PIN_RESET); }
  /* USER CODE END EXTI2_3_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
  /* USER CODE BEGIN EXTI2_3_IRQn 1 */
  if (HAL_GPIO_ReadPin(GPIOA, button4_Pin) == 0) {
	  HAL_GPIO_WritePin(GPIOB, led4_Pin, GPIO_PIN_SET);
	  CDC_Transmit_FS("4", sizeof ("4"));
  }

  else { HAL_GPIO_WritePin(GPIOB, led4_Pin, GPIO_PIN_RESET); }
  /* USER CODE END EXTI2_3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line 4 to 15 interrupts.
  */
void EXTI4_15_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_15_IRQn 0 */
	if (HAL_GPIO_ReadPin(GPIOA, button5_Pin) == 0) {
		HAL_GPIO_WritePin(GPIOB, led5_Pin, GPIO_PIN_SET);
		CDC_Transmit_FS("5", sizeof ("5"));
	}

	else { HAL_GPIO_WritePin(GPIOB, led5_Pin, GPIO_PIN_RESET); }

	if (HAL_GPIO_ReadPin(GPIOA, button6_Pin) == 0) {
		HAL_GPIO_WritePin(GPIOB, led6_Pin, GPIO_PIN_SET);
		CDC_Transmit_FS("6", sizeof ("6"));
	}

	else { HAL_GPIO_WritePin(GPIOB, led6_Pin, GPIO_PIN_RESET); }

	if (HAL_GPIO_ReadPin(GPIOA, button7_Pin) == 0) {
		HAL_GPIO_WritePin(GPIOB, led7_Pin, GPIO_PIN_SET);
		CDC_Transmit_FS("7", sizeof ("7"));
	}

	else { HAL_GPIO_WritePin(GPIOB, led7_Pin, GPIO_PIN_RESET); }
  /* USER CODE END EXTI4_15_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
  /* USER CODE BEGIN EXTI4_15_IRQn 1 */
  if (HAL_GPIO_ReadPin(GPIOA, button8_Pin) == 0) {
	  HAL_GPIO_WritePin(GPIOB, led8_Pin, GPIO_PIN_SET);
	  CDC_Transmit_FS("8", sizeof ("8"));
  }

  else { HAL_GPIO_WritePin(GPIOB, led8_Pin, GPIO_PIN_RESET); }

  if (HAL_GPIO_ReadPin(GPIOA, button9_Pin) == 0) {
	  HAL_GPIO_WritePin(GPIOB, led9_Pin, GPIO_PIN_SET);
  	  CDC_Transmit_FS("9", sizeof ("9"));
  }

  else { HAL_GPIO_WritePin(GPIOB, led9_Pin, GPIO_PIN_RESET); }

  if (HAL_GPIO_ReadPin(GPIOA, button10_Pin) == 0) {
	  HAL_GPIO_WritePin(GPIOB, led10_Pin, GPIO_PIN_SET);
	  CDC_Transmit_FS("10", sizeof ("10"));
  }

  else { HAL_GPIO_WritePin(GPIOB, led10_Pin, GPIO_PIN_RESET); }
  /* USER CODE END EXTI4_15_IRQn 1 */
}

/**
  * @brief This function handles USB global interrupt / USB wake-up interrupt through EXTI line 18.
  */
void USB_IRQHandler(void)
{
  /* USER CODE BEGIN USB_IRQn 0 */

  /* USER CODE END USB_IRQn 0 */
  HAL_PCD_IRQHandler(&hpcd_USB_FS);
  /* USER CODE BEGIN USB_IRQn 1 */

  /* USER CODE END USB_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
