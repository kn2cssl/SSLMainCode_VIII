#include "Error.hpp"
#include "Buzzer.hpp"
#include "USB.hpp"
#include "stm32f4xx_hal.h"
#include "debugger.hpp"

float Error::freq[5] = {1,50,50,1,1};
float Error::pulse[5] = {0.5,0.7,0.5,0.5,0.7};

void Error::Happend(ErrorMode em,char errorStr[256])
{
	if (em == BATTRY_LOW)
	{
		buzzer.Set_State(true);
		while (true)
		{
			USB.Print("<Error> \"%s\" \r\n",errorStr);
			debugger.Print("<Error> \"%s\" \r\n",errorStr);
			HAL_Delay(100);
		}
	}
	else
	{
		while (true)
		{
			buzzer.Wave(freq[em],pulse[em]);
			USB.Print("<Error> \"%s\" \r\n",errorStr);
			debugger.Print("<Error> \"%s\" \r\n",errorStr);
		}
	}
}
