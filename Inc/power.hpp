#ifndef __POWER_HPP__
#define __POWER_HPP__

#include "main.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include <stdbool.h>

static class Power
{
	private:
		ADC_HandleTypeDef *hadc;
		float voltage;
		static const float minVoltage;
		static const float maxVoltage;	
	public:
		void Init(ADC_HandleTypeDef *_hadc);
		void Update();
		float Read_Voltage();
		bool Is_Voltage_Correct();
}power;

#endif
