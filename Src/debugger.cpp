#include "debugger.hpp"
#include "main.h"
#include <stdio.h>
#include <stdarg.h>
#include "settings.hpp"
#include "stm32f4xx_hal.h"
#include "Logger.hpp"

char Debugger::str[256];
bool Debugger::isConnected = false;

void Debugger::Print(const char* format, ...)
{
	if (!isConnected)
		return;
	va_list argptr;
	va_start(argptr, format);
	unsigned long int l = vsprintf(str, format, argptr);
	va_end(argptr);
	puts(str,l);
}
void Debugger::Log(const char* format, ...)
{
	if (!isConnected)
		return;
	if (!settings.DebuggerDebugON)
		return;
	va_list argptr;
	va_start(argptr, format);
	unsigned long int l = vsprintf(str, format, argptr);
	va_end(argptr);
	puts(str,l);
}
void Debugger::Error(const char* format, ...)
{
	if (!isConnected)
		return;
	if (!settings.DebuggerErrorON)
		return;
	va_list argptr;
	va_start(argptr, format);
	unsigned long int l = vsprintf(str, format, argptr);
	va_end(argptr);
	puts(str,l);
}
void Debugger::puts(char* str,unsigned int l)
{
	for (unsigned int i = 0 ; i < l ; i++)
	{
		ITM_SendChar(str[i]);
		HAL_GPIO_TogglePin(USBTransmit_GPIO_Port,USBTransmit_Pin);
	}
}
void Debugger::Init()
{
	isConnected = true;
	logger.Log((char *)"Debugger Initialized");
}
