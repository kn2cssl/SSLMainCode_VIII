#include "power.hpp"
#include "USB.hpp"
#include "Error.hpp"
#include "Logger.hpp"

const float Power::minVoltage = 11.0;
const float Power::maxVoltage = 12.6;

void Power::Init(ADC_HandleTypeDef *_hadc)
{
	hadc = _hadc;
	//wait for Capacitors to be fully charged and having a stable High Voltage
	HAL_Delay(100);
	if (!Is_Voltage_Correct())
		return;
	logger.Log((char *)"Power Initialized");
	char str[256];
	sprintf(str,"V = %f",Read_Voltage());
	logger.Log(str);
}
void Power::Update()
{
	HAL_ADC_Start(hadc);
	HAL_ADC_PollForConversion(hadc,10);
	unsigned short int readed = HAL_ADC_GetValue(hadc);
  voltage = readed * (3.3 / 4096) * (61 / 11) * 1.1;
	HAL_ADC_Stop(hadc);
}
float Power::Read_Voltage()
{
	return voltage;
}
bool Power::Is_Voltage_Correct()
{
	Update();
	if (voltage <= maxVoltage && voltage >= minVoltage)
		return true;
	error.Happend(BATTRY_LOW,(char *)"Battry Low");
	return false;
}

