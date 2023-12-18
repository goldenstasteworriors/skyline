#include<main.h>
motor Motor;
extern float setpointSpeed = 30;
void SystemClock_Config(void);

int main(void)
{
	/*PID Init*/
	Pid_Typedef pid = {
  .SetPoint = 30.0,
  .PreError = 0.0,
  .LastError = 0.0,
  .dError = 0.0,
  .SumError = 0.0,
  .SetPointLast = 0.0,
  .P = 1.0,
  .I = 0.1,
  .D = 0.01,
  .IMax = 100.0,
  .ErrorMax = 10.0,
  .OutMax = 100.0,
  .deadband = 0.1,
  .POut = 0.0,
  .IOut = 0.0,
  .DOut = 0.0,
	};
	HAL_Init();

	SystemClock_Config();

	MX_GPIO_Init();
	MX_TIM1_Init();
	MX_TIM6_Init();
	MX_TIM5_Init();
	MX_USART1_UART_Init();
	Motor_Init();
	while (1)
	{
		float actualSpeed = getActualSpeed();
		float controlOutput = PID_Calc(&pid, setpointSpeed - actualSpeed);
		applyControlOutput(controlOutput);
	}
}

void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 50;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
		| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}
}
void Error_Handler(void)
{
	__disable_irq();
	while (1)
	{
	}
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{

}
#endif /* USE_FULL_ASSERT */
