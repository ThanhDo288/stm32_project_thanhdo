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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
void SystemClock_Config(void);
void USART_Init(void){
	
RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
GPIOA->CRL = 0;
GPIOA->CRL |= (3<<8);   // output mode 50 MHz for PA2
GPIOA->CRL |= (2<<10);  // Alternate Func Push Pull For PA2
	
GPIOA->CRL &= ~(3<<12);   // Intput Mode For PA3
GPIOA->CRL |= (2<<14);  // Input Pull Up/ Down For PA3	
	
GPIOA->ODR |= 1<<3;  // Pull Up for PA3
RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
USART2->CR1 = 0x00;   // Clear ALL
//USART2->BRR = 8000000 /(9600);// (7<<0) | (24<<4);   // Baud rate of 115200, PCLK1 at 45MHz
USART2->BRR |=0x000;
USART2->BRR |= (52<<4) |(8<<0);
USART2->CR1 |= (1<<2); // RE=1 Enable the Receiver
USART2->CR1 |= (1<<3);  // TE=1.. Enable Transmitter 
	USART2->CR1 |= (1<<13);   // UE = 1... Enable USART

	}
char USART2_InChar(void){
	while((USART2->SR & USART_SR_RXNE) == 0); // Wait until RXNE flag is set  // wait until RXFE is 0
  return (char)(USART2->DR & 0xFF);
}
void UART2_SendString( char* str) {
    while (*str != '\0') {
        while (!(USART2->SR & USART_SR_TXE)); // Ð?i tr?ng d? g?i
        USART2->DR = (uint16_t)(*str++); // G?i t?ng ký t? trong chu?i
    }
}  
void USART2_OutChar(void){
	
	while (USART2->SR & (1<<7)==0); // Ð?i TXE flag du?c set, cho phép truy?n d? li?u; // Wait until TXE flag is set // wait until TXFF is 0
  	USART2->DR |= 0x01;
	while(USART2->SR &(1<<6)==0);
}

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
  /* USER CODE BEGIN 2 */
   USART_Init(); 
  /* USER CODE END 2 */
 char buffer[]="hello\n";
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	//USART2_OutChar();
		HAL_Delay(500);
    /* USER CODE BEGIN 3 */
		UART2_SendString(buffer);
		HAL_Delay(500);
		USART2_InChar();
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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
