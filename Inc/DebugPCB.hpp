#ifndef __DEBUGPCB_HPP__
#define __DEBUGPCB_HPP__

#include "stm32f4xx_hal.h"
#include <stdbool.h>

/*
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef* hi2c)
{
	debugPCB.Receive_Ended(hi2c);
}
void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef* hi2c)
{
	debugPCB.Transmit_Ended(hi2c);
}
*/

enum DebugPCBState
{
	DEBUG_STATE_HEADER,
	DEBUG_STATE_DATA
};

enum DebugPCBOrderAddresses
{
	DEBUG_ORDER_MOTOR_STOP_ALL = 0x00,
	DEBUG_ORDER_MOTOR_STOP_0 = 0x01,
	DEBUG_ORDER_MOTOR_STOP_1 = 0x02,
	DEBUG_ORDER_MOTOR_STOP_2 = 0x03,
	DEBUG_ORDER_MOTOR_STOP_3 = 0x04,
	DEBUG_ORDER_MOTOR_STOP_4 = 0x05,
	DEBUG_ORDER_MOTOR_RUN_ALL = 0x06,
	DEBUG_ORDER_MOTOR_RUN_0 = 0x07,
	DEBUG_ORDER_MOTOR_RUN_1 = 0x08,
	DEBUG_ORDER_MOTOR_RUN_2 = 0x09,
	DEBUG_ORDER_MOTOR_RUN_3 = 0x0A,
	DEBUG_ORDER_MOTOR_RUN_4 = 0x0B,
	DEBUG_ORDER_SHOOT = 0x50,
	DEBUG_ORDER_WIRELESS_ON = 0xA0,
	DEBUG_ORDER_WIRELESS_OFF = 0xA1
};

enum DebugPCBVariableAddresses
{
	DEBUG_VARIABLE_SRPM_0 = 0x00,
	DEBUG_VARIABLE_SRPM_1 = 0x01,
	DEBUG_VARIABLE_SRPM_2 = 0x02,
	DEBUG_VARIABLE_SRPM_3 = 0x03,
	DEBUG_VARIABLE_SRPM_4 = 0x04,
	DEBUG_VARIABLE_MOMENTOM_RPM_0 = 0x05,
	DEBUG_VARIABLE_MOMENTOM_RPM_1 = 0x06,
	DEBUG_VARIABLE_MOMENTOM_RPM_2 = 0x07,
	DEBUG_VARIABLE_MOMENTOM_RPM_3 = 0x08,
	DEBUG_VARIABLE_MOMENTOM_RPM_4 = 0x09,
	DEBUG_VARIABLE_SHOOT_CHARGE = 0x50,
	DEBUG_VARIABLE_WIRELESS_SVX = 0xA0,
	DEBUG_VARIABLE_WIRELESS_SVY = 0xA1,
	DEBUG_VARIABLE_WIRELESS_SW = 0xA2,
	DEBUG_VARIABLE_WIRELESS_VX = 0xA3,
	DEBUG_VARIABLE_WIRELESS_VY = 0xA4,
	DEBUG_VARIABLE_WIRELESS_W = 0xA5,
	DEBUG_VARIABLE_WIRELESS_ALPHA = 0xA6,
	DEBUG_VARIABLE_WIRELESS_SS = 0xA7	
};

static class DebugPCB
{
	private:
		static const unsigned char START_BYTE;
		static const unsigned char STOP_BYTE;
		static const unsigned char ORDER;
		static const unsigned char WRITE_DATA;
		static const unsigned char READ_DATA;
		static I2C_HandleTypeDef* hi2c;
		static unsigned char header[4];
		static unsigned char data[4];
		static unsigned char txBuffer[4];
		static DebugPCBState state;
		void Get_Header();
		void Parse_Header();
		void Get_Data();
		void Parse_Data();
		void Send_Data();
		void Set_Var(DebugPCBVariableAddresses addr,signed short int value);
		signed short int Get_Var(DebugPCBVariableAddresses addr);
		void Do_Order(DebugPCBOrderAddresses addr);
	public:
		void Init(I2C_HandleTypeDef* h);
		void Receive_Ended(I2C_HandleTypeDef* h);
		void Transmit_Ended(I2C_HandleTypeDef* h);
}debugPCB;

#endif
