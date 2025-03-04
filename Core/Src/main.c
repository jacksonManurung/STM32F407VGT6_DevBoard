/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main_app.h"
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
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */
GPIO_Properties_t led_1			= {.port = GPIOD, .pin = GPIO_PIN_12};
GPIO_Properties_t led_2			= {.port = GPIOD, .pin = GPIO_PIN_13};
GPIO_Properties_t led_3			= {.port = GPIOD, .pin = GPIO_PIN_14};
GPIO_Properties_t led_4			= {.port = GPIOD, .pin = GPIO_PIN_15};
GPIO_Properties_t push_button	= {.port = GPIOA, .pin = GPIO_PIN_0};

PushButton_Properties_t user_button[]	= {{.status = BUTTON_OFF, .orientation = ACTIVE_PULL_DOWN, .line = &push_button, .callback = NULL}};
LEDIndicator_Properties_t leds[]	= {
		{.state = LED_OFF, .orientation = ACTIVE_HIGH, .line = &led_1},
		{.state = LED_OFF, .orientation = ACTIVE_HIGH, .line = &led_2},
		{.state = LED_OFF, .orientation = ACTIVE_HIGH, .line = &led_3},
		{.state = LED_OFF, .orientation = ACTIVE_HIGH, .line = &led_4}
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void StartDefaultTask(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 128;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument) {
	/* USER CODE BEGIN 5 */
	/* Infinite loop */
	while(1) {
#if 1
		for(uint16_t index = 0; index < (sizeof(user_button) / sizeof(PushButton_Properties_t)); index++) {
			if(user_button[index].line != NULL) {
				if(HAL_GPIO_ReadPin(user_button[index].line->port, user_button[index].line->pin) == (user_button[index].orientation == ACTIVE_PULL_UP) ? GPIO_PIN_SET : GPIO_PIN_RESET) {
					switch(user_button[index].status) {
					case BUTTON_OFF : {
						user_button[index].status		= BUTTON_PUSHED;
						user_button[index].delay		= HAL_GetTick();
						break;
					}
					case BUTTON_PUSHED : {
						if((HAL_GetTick() - user_button[index].delay) >= PUSH_BUTTON_DEBOUNCE_DELAY) {
							user_button[index].status	= BUTTON_LOCK;
							if(user_button[index].callback != NULL)
								user_button[index].callback(NULL);
						}
						break;
					}
					case BUTTON_LOCK :
					default : {break;}
					}
				}
				else if(HAL_GPIO_ReadPin(user_button[index].line->port, user_button[index].line->pin) == (user_button[index].orientation == ACTIVE_PULL_UP) ? GPIO_PIN_RESET : GPIO_PIN_SET) {
					if(user_button[index].status != BUTTON_OFF)
						user_button[index].status		= BUTTON_OFF;
				}
			}
		}
#endif

#if 1
		for (uint16_t index = 0; index < (sizeof(leds) / sizeof(LEDIndicator_Properties_t)); index++) {
			if(leds[index].line != NULL) {
				switch(leds[index].state) {
					case LED_ON : {
						if(HAL_GPIO_ReadPin(leds[index].line->port, leds[index].line->pin) == (leds[index].orientation == ACTIVE_LOW) ? GPIO_PIN_SET : GPIO_PIN_RESET)
							HAL_GPIO_WritePin(leds[index].line->port, leds[index].line->pin, (leds[index].orientation == ACTIVE_LOW) ? GPIO_PIN_RESET : GPIO_PIN_SET);
						break;
					}
					case LED_BLINK : {
						if((HAL_GPIO_ReadPin(leds[index].line->port, leds[index].line->pin) == (leds[index].orientation == ACTIVE_LOW) ? GPIO_PIN_SET : GPIO_PIN_RESET) && ((HAL_GetTick() - leds[index].delay) >= LED_BLINK_OFF_DELAY)) {
							leds[index].delay	= HAL_GetTick();
							HAL_GPIO_WritePin(leds[index].line->port, leds[index].line->pin, (leds[index].orientation == ACTIVE_LOW) ? GPIO_PIN_RESET : GPIO_PIN_SET);
						}
						else if((HAL_GPIO_ReadPin(leds[index].line->port, leds[index].line->pin) == (leds[index].orientation == ACTIVE_LOW) ? GPIO_PIN_RESET : GPIO_PIN_SET) && ((HAL_GetTick() - leds[index].delay) >= LED_BLINK_ON_DELAY)) {
							leds[index].delay	= HAL_GetTick();
							HAL_GPIO_WritePin(leds[index].line->port, leds[index].line->pin, (leds[index].orientation == ACTIVE_LOW) ? GPIO_PIN_SET : GPIO_PIN_RESET);
						}
						break;
					}
					case LED_OFF :
					default : {
						if(HAL_GPIO_ReadPin(leds[index].line->port, leds[index].line->pin) == (leds[index].orientation == ACTIVE_LOW) ? GPIO_PIN_RESET : GPIO_PIN_SET)
							HAL_GPIO_WritePin(leds[index].line->port, leds[index].line->pin, (leds[index].orientation == ACTIVE_LOW) ? GPIO_PIN_SET : GPIO_PIN_RESET);
						break;
					}
				}
			}
			else continue;
		}
#endif
		osDelay(1U);
	}
	/* USER CODE END 5 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
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

