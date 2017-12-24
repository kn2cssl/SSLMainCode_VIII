#include "USB.hpp"
#include "main.h"
#include <stdio.h>
#include <stdarg.h>
#include "usbd_cdc_if.h"
#include "usb_device.h"
#include "settings.hpp"
#include "Logger.hpp"

char USB::str[256];
char USB::buffer[256];
unsigned int USB::length;		
bool USB::isConnected = false;

void USB::Print(const char* format, ...)
{
	if (!isConnected)
		return;
	va_list argptr;
	va_start(argptr, format);
	unsigned long int l = vsprintf(str, format, argptr);
	va_end(argptr);
	CDC_Transmit_FS((unsigned char *)str,l);
	HAL_GPIO_TogglePin(USBTransmit_GPIO_Port,USBTransmit_Pin);
}
void USB::Log(const char* format, ...)
{
	if (!isConnected)
		return;
	if (!settings.USBDebugON)
		return;
	va_list argptr;
	va_start(argptr, format);
	unsigned long int l = vsprintf(str, format, argptr);
	va_end(argptr);
	CDC_Transmit_FS((unsigned char *)str,l);
	HAL_GPIO_TogglePin(USBTransmit_GPIO_Port,USBTransmit_Pin);
}
void USB::Error(const char* format, ...)
{
	if (!isConnected)
		return;
	if (!settings.USBErrorON)
		return;
	va_list argptr;
	va_start(argptr, format);
	unsigned long int l = vsprintf(str, format, argptr);
	va_end(argptr);
	CDC_Transmit_FS((unsigned char *)str,l);
	HAL_GPIO_TogglePin(USBTransmit_GPIO_Port,USBTransmit_Pin);
}
void USB::Listen(unsigned char * Buf, unsigned int *Len)
{
	for (int i = 0 ; i < *Len ; i++)
		buffer[i] = Buf[i];
	length = *Len;
	HAL_GPIO_TogglePin(USBReceive_GPIO_Port,USBReceive_Pin);
}
void USB::Init()
{
	MX_USB_DEVICE_Init();
	isConnected = true;
	logger.Log((char *)"USB Initialized");
}
