#ifndef __TIME_HPP__
#define __TIME_HPP__

#include "stm32f4xx_hal.h"

//copy to the main
/*
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	time.Time_Passed(htim);
}
*/

/*
void MX_TIM12_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;

  htim12.Instance = TIM12;
  htim12.Init.Prescaler = 21000;
  htim12.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim12.Init.Period = 1000;
  htim12.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
  if (HAL_TIM_Base_Init(&htim12) != HAL_OK)
  {
    Error_Handler();
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim12, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

void MX_TIM13_Init(void)
{

  htim13.Instance = TIM13;
  htim13.Init.Prescaler = 21000;
  htim13.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim13.Init.Period = 1000;
  htim13.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
  if (HAL_TIM_Base_Init(&htim13) != HAL_OK)
  {
    Error_Handler();
  }

}

void MX_TIM14_Init(void)
{

  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 21;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 1000;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }

}

*/

static class Time
{
	private:
		static TIM_HandleTypeDef *second,*mili,*micro;
		static unsigned int s;
	public:
		void Init(TIM_HandleTypeDef *sec,TIM_HandleTypeDef *mil,TIM_HandleTypeDef *mic);
		float Get_Time();
		unsigned int Get_Second();
		unsigned short int Get_Mili_Second();
		unsigned short int Get_Micro_Seccond();
		void Time_Passed(TIM_HandleTypeDef* htim);
}time;

#endif
