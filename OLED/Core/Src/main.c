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
#include "stm32f1xx.h"
#include"Shin.h"
#define Size 8
int put,get,i;
char buffer[Size];
uint32_t data;
char Mess_tx[8]="1.256";
uint32_t Positon;
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#include <string.h>
#include "st7735.h"
#include "GFX_FUNCTIONS.h"
#include "fonts.h"
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
void delay_ms(){
	int i=900000;
	while(i--){
		__asm__("nop");
}}
void super_delay(){
	int i=10;
	while(i--){
		delay_ms();
}
}

void delay(int cycle){
	int i=900000*(cycle/100);
	while(i--){
		__asm__("nop");
	}
}
void GPIO_ADC(){
	RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
	GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
	//PIOA->CRL |= GPIO_CRL_CNF0_0;
}
void ADC_Init(){
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;
	ADC1->CR2&=~ADC_CR2_ADON;
	ADC1->SQR3=0;
	ADC1->SMPR2=ADC_SMPR2_SMP0;
	ADC1->CR2|=ADC_CR2_ADON;
	ADC1->CR2|=ADC_CR2_SWSTART;
}
uint32_t ADC_In(){
	uint32_t result;
	//while(!(ADC1->SR&ADC_SR_EOC)){};
		//Heart_beat();
		result=ADC1->DR&0xFFF;
		return result;
}
void GPIO_UARTrx(){
	RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
		GPIOA->CRL&=~(GPIO_CRL_MODE2|GPIO_CRL_CNF2|GPIO_CRL_MODE3|GPIO_CRL_CNF3);
		GPIOA->CRL|=(GPIO_CRL_CNF2_1|GPIO_CRL_MODE2_0|GPIO_CRL_MODE2_1); //MODE[11],50MHz
		//GPIOA->CRH|=GPIO_CRH_MODE9_1;
		GPIOA->CRL |= GPIO_CRL_CNF3_1;
		GPIOA->ODR |= 1<<3;
}
void UART_init(){
	RCC->APB1ENR|=RCC_APB1ENR_USART2EN;
		USART2->CR1=0;
		USART2->CR2=0;
		USART2->BRR=(0x06<<0) | (0xEA<<4);
		USART2->CR1 |= USART_CR1_RXNEIE;
		USART2->CR1|= USART_CR1_TE|USART_CR1_RE; //TE la bit 0x08
		USART2->CR1|=USART_CR1_UE;//tuong tu TE thi UE la bit so 0x2000;
		USART2->CR2 |= USART_CR2_STOP_1;
	}
uint32_t Convert(uint32_t input){
  // copy this from Lab 8
    return input*5/10; // replace this line
}
void convert_mess(uint32_t position) {
	int tmp,fix;
	int i, n = 1000,k=3;
	fix = position;
	tmp = fix;
		tmp = tmp / n;
		fix -= tmp * n;
		n /= 10;
		Mess_tx[1]=(char)(tmp+0x30);
	Mess_tx[2]=0x2E;
	for (i = 1; i < 4; i++) {
		tmp = fix;
		tmp = tmp / n;
		fix -= tmp * n;
		n /= 10;
		Mess_tx[k]=(char)(tmp+0x30);
		k++;
	}
}
void Fifo_Init() {
//Complete this
	get=0;
	put=0;
}

// *********** FiFo_Put**********
// Adds an element to the FIFO
// Input: Character to be inserted
// Output: 1 for success and 0 for failure
//         failure is when the buffer is full
uint32_t Fifo_Put(char data){
  //Complete this routine
   if(((put+1)%Size)==get) return 0;
	buffer[put]=data;
	put=(put+1)%Size;
   return(1);

}

// *********** Fifo_Get**********
// Gets an element from the FIFO
// Input: none
// Output: If the FIFO is empty return 0
//         If the FIFO has data, remove it, and return it
uint32_t Fifo_Get(void){
	char result;
  //Complete this routine
  if((get%Size)==put) return 0;
	result=buffer[get];
	get=(get+1)%Size;
   return result;
}
int Fifo_emty(void){
	if((get%Size)==put) return 1;
	return 0;
}
uint32_t Fifo_check_get(){
	while(Fifo_emty()){}
	return Fifo_Get();
}
void Heart_beat(){
	RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
		GPIOA->CRH&=~(GPIO_CRH_MODE10|GPIO_CRH_CNF10);
		GPIOA->CRH|=GPIO_CRH_MODE10;
		GPIOA->BSRR=GPIO_BSRR_BS10;
		//super_delay(9000000);
		//GPIOA->BSRR=GPIO_BSRR_BR10;
		//HAL_Delay(500);
		//GPIOA->BSRR=GPIO_BSRR_BR10;
		//HAL_Delay(500);
	}
void USART2_IRQHandler(){
	char k;
	k=USART2->DR;
	Fifo_Put(k);
}
uint8_t UART_getchar(){
	uint8_t k;
	while(!(USART2->SR & (1<<5))){};
	k=USART2->DR;
		return k;
}
void UART1_OutChar(char data){
	//int b=0;
	while(!(USART2->SR&USART_SR_TXE)){}
		//int a=0;
	 Heart_beat();
		USART2->DR=data;
		//a=9;
		//Heart_beat();
	while(!(USART2->SR&USART_SR_TC)){
	//int a=0;
	};
	}
int data_fifo;
int main(void)
{
	NVIC_EnableIRQ(USART2_IRQn);
	int index=0;
	GPIO_ADC();
	//Heart_beat();
	ADC_Init();
	UART_init();
	GPIO_UARTrx();
//	NVIC_EnableIRQ(USART2_IRQn);
    	Mess_tx[0]='<';
//		Mess_tx[1]='1';
//		Mess_tx[2]='.';
//		Mess_tx[3]='2';
//		Mess_tx[4]='3';
//		Mess_tx[5]='6';
		char Mess_Rx[8]="1.333";

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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  ST7735_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //int i,index=0;
 // char Message_zz[7]="1.234";
  //Heart_beat();
  while (1)
  {
//	  Heart_beat();
//	  while(!(USART2->SR & (1<<5))){
//		  Heart_beat();
//	  		data=USART2->DR;
//	  		Fifo_Put(data);
//	  }
	 //UART1_IQRHandler();
	  //data_fifo = Fifo_check_get();
	  //Heart_beat();
//	  if(1){
//		  if(1){
//			  	 Message_zz[5]='9';
//			  for(i=0;i<6;i++){
//				  Message_zz[index++]='9';
//			  }
//			  index =0;
//	  }
//	  }
    /* USER CODE END WHILE */
	  ADC1->CR2|=ADC_CR2_ADON;
	  	  ADC1->CR2|=ADC_CR2_SWSTART;
	  		//test1=ADC_In();
	  	Positon=Convert(ADC_In());
	  	convert_mess(Positon);
	  	int j;
	  for(j=0;j<6;j++){
  			UART1_OutChar(Mess_tx[j]);}
  	//		int a=0;
	  if(Fifo_Get()=='<'){
	  				for(i=0;i<5;i++){
	  						Mess_Rx[i]=Fifo_check_get();

	  			}
	  }
  			//Mess_Rx[i]=UART_getchar();
//	  			int b=0;
	  ST7735_FillScreen(ST7735_BLACK);
	  //ST7735_WriteString(0,3,"A",Font_7x10,ST7735_RED,ST7735_BLACK);
	    //ST7735_WriteString(0, 0, "MicroPeta", Font_7x10, ST7735_RED, ST7735_BLACK);
	    //ST7735_WriteString(0, 3, Mess_Rx, Font_16x26, ST7735_GREEN, ST7735_BLACK);
	    ST7735_DrawImage(10, 9, 100, 200, image_data_Image);
	    //ST7735_WriteString(0, 3*10+3*18, "March  2023", Font_16x26, ST7735_BLUE, ST7735_BLACK);
	    HAL_Delay(200);
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_1LINE;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB0 PB1 PB10 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
