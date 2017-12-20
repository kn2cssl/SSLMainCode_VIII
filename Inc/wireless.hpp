#ifndef __WIRELESS_HPP__
#define __WIRELESS_HPP__

#include "nrf24l01.hpp"
#include <stdbool.h>

static class Wireless
{
	private:
		static float lastDataArrivelTime;
		static NRF hnrf;
		static bool isOn;
		void NRF_Init(SPI_HandleTypeDef *hspi);
		void NRF_Set_Address();
		void NRF_Write_Buffer(char str[32]);
		void NRF_Read_Buffer(char str[32]);
		void NRF_Transmition(bool state);
		bool NRF_Data_Ready();
	public:
		void Init(SPI_HandleTypeDef *hspi);
		void NRF_Data_Arrived();
		void NRF_OFF();
		void NRF_ON();
}wireless;

#endif
