#include "Buzzer.hpp"
#include "main.h"
#include "stm32f4xx_hal.h"
#include "settings.hpp"

void Buzzer::Wave(float freq,float pulse)
{
	if (!settings.buzzerON)
	{
		HAL_GPIO_WritePin(Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_RESET);
		return;
	}
	HAL_GPIO_WritePin(Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_SET);
	HAL_Delay((1000 * pulse) / freq);
	HAL_GPIO_WritePin(Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_RESET);
	HAL_Delay((1000 * (1 - pulse)) / freq);
}
void Buzzer::Set_State(bool state)
{
	if (!settings.buzzerON)
	{
		HAL_GPIO_WritePin(Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_RESET);
		return;
	}
	if (state)
		HAL_GPIO_WritePin(Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(Buzzer_GPIO_Port,Buzzer_Pin,GPIO_PIN_RESET);
}
