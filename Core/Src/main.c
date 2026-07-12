/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "gpdma.h"
#include "icache.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Servo.h"
#include <stdio.h>
#include <string.h>
#include "UseServo.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t RxBuff[1];			
uint8_t DataBuff[1024]; // ����1��Ϣ�洢
uint8_t DataNum;		

uint8_t RxBuff3[1];			
uint8_t DataBuff3[1024]; //����3��Ϣ�洢
uint8_t DataNum3;
const uint8_t cmd_stop[] = {"ֹͣ"};

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/***�رձ�׼���µİ�����ģʽ����ʵ�����Լ���д�ĺ����滻��׼���еĺ���****/



#if 0
//�жϷ�ʽ����
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	
}s
// �жϷ�����ֹ
void HAL_UART_AbortTransmitCpltCallback(UART_HandleTypeDef *huart){
	
}
#endif
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{

        
   
        if(huart->Instance == USART1){
        HAL_UART_Transmit(&huart1, DataBuff, Size, 100);  
        
        uint8_t newline[] = "\r\n";
        HAL_UART_Transmit(&huart1, newline, 2, 100);

        HAL_UARTEx_ReceiveToIdle_DMA(&huart1, DataBuff, sizeof(DataBuff));
        }
   
        if(huart->Instance == USART3){
        HAL_UART_Transmit(&huart1, DataBuff3 ,Size, 100);  // ��ʱ100ms
        uint8_t newline[] = "\r\n";
        HAL_UART_Transmit(&huart1, newline, 2, 100);
        HAL_UARTEx_ReceiveToIdle_DMA(&huart3, DataBuff3 ,sizeof(DataBuff3));
            
        } 

}


/* USER CODE END 0 */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void SystemPower_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void beepLoop(int n){//�����������Ͷ���   ��main����֮ǰ
	for(int i=0;i<n;i++){
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);	
		HAL_Delay(300);//�ӳ�500ms  Ҳ���� 0.5s
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET);
		HAL_Delay(300);
	}
}




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

  /* Configure the System Power */
  SystemPower_Config();

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_GPDMA1_Init();
  MX_ICACHE_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM15_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	Servo_Init();
	
	beepLoop(3);
    stop(); 
    beepLoop(1);
	//move1(5);

   state = 1;

    stop();
    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, DataBuff, sizeof(DataBuff));
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, DataBuff3, sizeof(DataBuff3));

	
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
         if(strcmp((char*)DataBuff3, "stop\r\n") == 0)
        {
            
            beepLoop(1);
            move0();
            memset(DataBuff3, 0, sizeof(DataBuff3));
            state = 2;
        }
        if(strcmp((char*)DataBuff3, "start\r\n") == 0) 
        {
            beepLoop(1);
            move0();
            memset(DataBuff3, 0, sizeof(DataBuff3));
            state = 1;
        }
       if(strcmp((char*)DataBuff3, "stand\r\n") == 0)
        {
            move0();
            memset(DataBuff3, 0, sizeof(DataBuff3));
            state = 1;
        }
       if(strcmp((char*)DataBuff3, "sleep\r\n") == 0)
        {
            stop();
            memset(DataBuff3, 0, sizeof(DataBuff3));
            state = -1;
        }
        if(strcmp((char*)DataBuff3, "move1\r\n") == 0)
        {
            
            move0();
            move1();
            memset(DataBuff3, 0, sizeof(DataBuff3));
            state = 2;
            
        }
        if(strcmp((char*)DataBuff3, "move2\r\n") == 0)
        {
            
            move0();
            move2();
            memset(DataBuff3, 0, sizeof(DataBuff3));
            state = 2;
           
        }
        if(strcmp((char*)DataBuff3, "move3\r\n") == 0)
        {
            
            move0();
            HAL_Delay(1000);
            move3();
            HAL_Delay(2000);
            move0();
            memset(DataBuff3, 0, sizeof(DataBuff3));
            state = 1;
            
        }
                if(strcmp((char*)DataBuff3, "move4\r\n") == 0)
        {
            
            move0();
            HAL_Delay(1000);
            move4();
            memset(DataBuff3, 0, sizeof(DataBuff3));
            state = 1;
            
        }
        /////////////////��������//////////////////////
        if(strcmp((char*)DataBuff3, "move6\r\n") == 0)
        {
            move6();
            state = 2;
        }
        if(strcmp((char*)DataBuff3, "move5\r\n") == 0)
        {
            move5();
            state = 2;
        }


        
       
        

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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_0;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV4;
  RCC_OscInitStruct.PLL.PLLM = 3;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 1;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Power Configuration
  * @retval None
  */
static void SystemPower_Config(void)
{

  /*
   * Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral
   */
  HAL_PWREx_DisableUCPDDeadBattery();
/* USER CODE BEGIN PWR */
/* USER CODE END PWR */
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
#ifdef USE_FULL_ASSERT
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
