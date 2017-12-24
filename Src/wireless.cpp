#include "wireless.hpp"
#include "main.h"
#include "stm32f4xx_hal.h"
#include "spi.h"
#include "settings.hpp"
#include "USB.hpp"
#include "Error.hpp"
#include "Logger.hpp"
#include "memory.hpp"
#include "time.hpp"

NRF Wireless::hnrf;
float Wireless::lastDataArrivelTime;
bool Wireless::isOn;

void Wireless::Init(SPI_HandleTypeDef *hspi)
{
	NRF_Init(hspi);
	lastDataArrivelTime = 0;
}
void Wireless::NRF_Init(SPI_HandleTypeDef *hspi)
{
	isOn = true;
	NRF_Transmition(false);
	HAL_Delay(10);
	char Address[5] = { 0x11,0x22,0x33,0x44,0x11};
	hnrf.CEPort = CE_GPIO_Port;
	hnrf.CEPin  = CE_Pin;
	hnrf.CSPort = CSN_GPIO_Port;
	hnrf.CSPin  = CSN_Pin;
	hnrf.module = hspi;
	hnrf.clear_Interrupts();
	hnrf.flush_TX();
	hnrf.flush_RX();
	hnrf.init_milad(_RX_MODE,_CH_1,_2Mbps,Address,_Address_Width,_Buffer_Size,RF_PWR_MAX);
	hnrf.writeReg(W_REGISTER | DYNPD,0x01);
	hnrf.writeReg(W_REGISTER | FEATURE,0x06);
	hnrf.clear_All();
	HAL_Delay(2);
	if ((unsigned char)hnrf.get_Status() != 0xFF)
		logger.Log((char *)"NRF Initialized");
	else
		error.Happend(NRF_NOT_OKAY,(char *)"NRF is not Connected");
	NRF_Set_Address();
	NRF_Transmition(true);
}
void Wireless::NRF_Set_Address()
{
	unsigned char robotID = settings.Get_RID();
	char Address[5] = { 0x11,0x22,0x33,0x44,0x11};
	Address[4] = (robotID << 4) | robotID;
	hnrf.set_RX_Pipe(0,Address,5,32);
	hnrf.set_TX_Address(Address,5);
	if (robotID < 6 )
		hnrf.set_CH(_CH_1);
	else
		hnrf.set_CH(_CH_0);
	char str[256];
	sprintf(str,"NRF Address is Setted with RID %x",robotID);
	logger.Log(str);
}
void Wireless::NRF_Write_Buffer(char str[32])
{
	hnrf.clear_Interrupts();
	hnrf.flush_TX();
	hnrf.write_TX_Buf(str,32);
	hnrf.writeReg(STATUSe,0x7E);
}
void Wireless::NRF_Read_Buffer(char str[32])
{
	hnrf.read_RX_Buf(str,32);
	hnrf.clear_Interrupts();
	hnrf.flush_RX();
	hnrf.writeReg(STATUSe,0x7E);
}
void Wireless::NRF_Transmition(bool state)
{
	if (state && isOn)
	{
		HAL_GPIO_WritePin(CE_GPIO_Port,CE_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(NRFOK_GPIO_Port,NRFOK_Pin,GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(CE_GPIO_Port,CE_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(NRFOK_GPIO_Port,NRFOK_Pin,GPIO_PIN_RESET);
	}
	float nowTime = time.Get_Time();
	while (time.Get_Time() - nowTime < (float)0.002);
}
bool Wireless::NRF_Data_Ready()
{
	unsigned char status = hnrf.get_Status();
	if ((status & 0x40) == 0x40 )
		return true;
	return false;
}
void Wireless::NRF_Data_Arrived()
{
	if (!NRF_Data_Ready())
		return;
	HAL_GPIO_WritePin(DataArrived_GPIO_Port,DataArrived_Pin,GPIO_PIN_SET);
	NRF_Transmition(false);
	char str[32];
	NRF_Read_Buffer(str);
	if (str[0] == settings.Get_RID())
	{
		HAL_GPIO_WritePin(DataCorrect_GPIO_Port,DataCorrect_Pin,GPIO_PIN_SET);
		memory.responseStruct.SS = (float(1) / ((time.Get_Time() - lastDataArrivelTime) * float(4)));
		lastDataArrivelTime = time.Get_Time();
		for (unsigned char i = 0 ; i < 32 ; i ++)
			memory.order[i] = str[i];
		memory.Update();
		NRF_Write_Buffer(memory.response);
	}
	NRF_Transmition(true);
	HAL_GPIO_WritePin(DataArrived_GPIO_Port,DataArrived_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DataCorrect_GPIO_Port,DataCorrect_Pin,GPIO_PIN_RESET);
}
void Wireless::NRF_OFF()
{
	isOn = false;
}
void Wireless::NRF_ON()
{
	isOn = true;
}
