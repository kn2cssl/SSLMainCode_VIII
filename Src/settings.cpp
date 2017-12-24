#include "settings.hpp"
#include "main.h"
#include "stm32f4xx_hal.h"

const bool Settings::USBDebugON = true;
const bool Settings::USBErrorON = true;
const bool Settings::DebuggerDebugON = true;
const bool Settings::DebuggerErrorON = true;
const bool Settings::buzzerON = true;
unsigned char Settings::RID = 0x00;
bool Settings::RIDReaded = false;
void Settings::Read_RID()
{
	unsigned char hex0 = HAL_GPIO_ReadPin(HEX0_GPIO_Port,HEX0_Pin);
	unsigned char hex1 = HAL_GPIO_ReadPin(HEX1_GPIO_Port,HEX1_Pin);
	unsigned char hex2 = HAL_GPIO_ReadPin(HEX2_GPIO_Port,HEX2_Pin);
	unsigned char hex3 = HAL_GPIO_ReadPin(HEX3_GPIO_Port,HEX3_Pin);
	RID = hex2 * 8 + hex3 * 4 + hex0 * 2 + hex1;
	RIDReaded = true;
}
unsigned char Settings::Get_RID()
{
	if (!RIDReaded)
		Read_RID();
	return RID;
}

