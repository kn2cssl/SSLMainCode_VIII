#include "DebugPCB.hpp"
#include "Logger.hpp"
#include "main.h"
#include "Motor.hpp"
#include "memory.hpp"
#include "debugger.hpp"
#include "wireless.hpp"

I2C_HandleTypeDef* DebugPCB::hi2c;
const unsigned char DebugPCB::START_BYTE = 0xAA;
const unsigned char DebugPCB::STOP_BYTE = 0x55;
const unsigned char DebugPCB::ORDER = 'O';
const unsigned char DebugPCB::WRITE_DATA = 'W';
const unsigned char DebugPCB::READ_DATA = 'R';
unsigned char DebugPCB::header[4];
unsigned char DebugPCB::data[4];
unsigned char DebugPCB::txBuffer[4];
DebugPCBState DebugPCB::state;

void DebugPCB::Init(I2C_HandleTypeDef* h)
{
	hi2c = h;
	Get_Header();
	logger.Log((char *)"DebugPCB initialized");
}
void DebugPCB::Get_Header()
{
	state = DEBUG_STATE_HEADER;
	HAL_I2C_Slave_Receive_IT(hi2c,header,4);
}
void DebugPCB::Receive_Ended(I2C_HandleTypeDef* h)
{
	if (h != hi2c)
		return;
	HAL_GPIO_TogglePin(DebugReceive_GPIO_Port,DebugReceive_Pin);
	if (state == DEBUG_STATE_HEADER)
		Parse_Header();
	else
		Parse_Data();
}
void DebugPCB::Transmit_Ended(I2C_HandleTypeDef* h)
{
	if (h != hi2c)
		return;
	HAL_GPIO_TogglePin(DebugTransmit_GPIO_Port,DebugTransmit_Pin);
	Get_Header();
}
void DebugPCB::Parse_Header()
{
	if (header[0] == START_BYTE && header[3] == STOP_BYTE)
	{
		switch (header[1])
		{
			case ORDER:
				Do_Order((DebugPCBOrderAddresses)header[2]);
				Get_Header();
			break;
			case WRITE_DATA:
				Get_Data();
			break;
			case READ_DATA:
				Send_Data();
			break;		
			default:
				Get_Header();
			break;
		};
	}
	else 
		Get_Header();
}
void DebugPCB::Get_Data()
{
	state = DEBUG_STATE_DATA;
	HAL_I2C_Slave_Receive_IT(hi2c,data,4);
}
void DebugPCB::Parse_Data()
{
	signed short int value;
	if (data[0] == START_BYTE && data[3] == STOP_BYTE)
	{
		value = data[1] * 256 + data[2];
	}
	Set_Var((DebugPCBVariableAddresses)header[2],value);
	Get_Header();
}
void DebugPCB::Send_Data()
{
	signed short int value = 10;
	value = Get_Var((DebugPCBVariableAddresses)header[2]);
	txBuffer[0] = START_BYTE;
	txBuffer[1] = ((unsigned short int)(value)) / 256;
	txBuffer[2] = ((unsigned short int)(value)) % 256;
	txBuffer[3] = STOP_BYTE;
	HAL_I2C_Slave_Transmit(hi2c,txBuffer,4,2);
	HAL_GPIO_TogglePin(DebugTransmit_GPIO_Port,DebugTransmit_Pin);
	Get_Header();
}
void DebugPCB::Set_Var(DebugPCBVariableAddresses addr,signed short int value)
{
	switch (addr)
	{
		case DEBUG_VARIABLE_SRPM_0:
			motors.rearRight.Set_RPM(value);
		break;
		case DEBUG_VARIABLE_SRPM_1:
			motors.frontRight.Set_RPM(value);			
		break;
		case DEBUG_VARIABLE_SRPM_2:
			motors.spinn.Set_RPM(value);			
		break;
		case DEBUG_VARIABLE_SRPM_3:
			motors.frontLeft.Set_RPM(value);			
		break;
		case DEBUG_VARIABLE_SRPM_4:
			motors.rearLeft.Set_RPM(value);			
		break;
		case DEBUG_VARIABLE_MOMENTOM_RPM_0:

		break;
		case DEBUG_VARIABLE_MOMENTOM_RPM_1:

		break;
		case DEBUG_VARIABLE_MOMENTOM_RPM_2:

		break;
		case DEBUG_VARIABLE_MOMENTOM_RPM_3:

		break;
		case DEBUG_VARIABLE_MOMENTOM_RPM_4:

		break;
		case DEBUG_VARIABLE_SHOOT_CHARGE:

		break;
		case DEBUG_VARIABLE_WIRELESS_SVX:

		break;
		case DEBUG_VARIABLE_WIRELESS_SVY:

		break;
		case DEBUG_VARIABLE_WIRELESS_SW:

		break;
		case DEBUG_VARIABLE_WIRELESS_VX:

		break;
		case DEBUG_VARIABLE_WIRELESS_VY:

		break;
		case DEBUG_VARIABLE_WIRELESS_W:

		break;
		case DEBUG_VARIABLE_WIRELESS_ALPHA:

		break;
		case DEBUG_VARIABLE_WIRELESS_SS:

		break;
	};
	return;
}
signed short int DebugPCB::Get_Var(DebugPCBVariableAddresses addr)
{
	signed short int value = 0;
	switch (addr)
	{
		case DEBUG_VARIABLE_SRPM_0:
			value = motors.rearRight.Get_SetedRPM();
		break;
		case DEBUG_VARIABLE_SRPM_1:
			value = motors.frontRight.Get_SetedRPM();
		break;
		case DEBUG_VARIABLE_SRPM_2:
			value = motors.spinn.Get_SetedRPM();
		break;
		case DEBUG_VARIABLE_SRPM_3:
			value = motors.frontLeft.Get_SetedRPM();
		break;
		case DEBUG_VARIABLE_SRPM_4:
			value = motors.rearLeft.Get_SetedRPM();
		break;
		case DEBUG_VARIABLE_MOMENTOM_RPM_0:
			value = motors.rearRight.Get_RPM();
		break;
		case DEBUG_VARIABLE_MOMENTOM_RPM_1:
			value = motors.frontRight.Get_RPM();
		break;
		case DEBUG_VARIABLE_MOMENTOM_RPM_2:
			value = motors.spinn.Get_RPM();
		break;
		case DEBUG_VARIABLE_MOMENTOM_RPM_3:
			value = motors.frontLeft.Get_RPM();
		break;
		case DEBUG_VARIABLE_MOMENTOM_RPM_4:
			value = motors.rearLeft.Get_RPM();
		break;
		case DEBUG_VARIABLE_SHOOT_CHARGE:
			//shoot needs to be impemented
		break;
		case DEBUG_VARIABLE_WIRELESS_SVX:
			value = memory.orderStruct.SVX;
		break;
		case DEBUG_VARIABLE_WIRELESS_SVY:
			value = memory.orderStruct.SVY;
		break;
		case DEBUG_VARIABLE_WIRELESS_SW:
			value = memory.orderStruct.SWr;
		break;
		case DEBUG_VARIABLE_WIRELESS_VX:
			value = memory.orderStruct.VX;
		break;
		case DEBUG_VARIABLE_WIRELESS_VY:
			value = memory.orderStruct.VY;
		break;
		case DEBUG_VARIABLE_WIRELESS_W:
			value = memory.orderStruct.Wr;
		break;
		case DEBUG_VARIABLE_WIRELESS_ALPHA:
			value = memory.orderStruct.alpha;
		break;
		case DEBUG_VARIABLE_WIRELESS_SS:
			value = memory.responseStruct.SS;
		break;
	};	
	return value;
}
void DebugPCB::Do_Order(DebugPCBOrderAddresses addr)
{
	switch (addr)
	{
		case DEBUG_ORDER_MOTOR_STOP_ALL:
			motors.rearRight.Stop();
			motors.frontRight.Stop();
			motors.spinn.Stop();
			motors.frontLeft.Stop();
			motors.rearLeft.Stop();
		break;
		case DEBUG_ORDER_MOTOR_STOP_0:
			motors.rearRight.Stop();
		break;
		case DEBUG_ORDER_MOTOR_STOP_1:
			motors.frontRight.Stop();
		break;
		case DEBUG_ORDER_MOTOR_STOP_2:
			motors.spinn.Stop();
		break;
		case DEBUG_ORDER_MOTOR_STOP_3:
			motors.frontLeft.Stop();
		break;
		case DEBUG_ORDER_MOTOR_STOP_4:
			motors.rearLeft.Stop();
		break;
		case DEBUG_ORDER_MOTOR_RUN_ALL:
			motors.rearRight.Run();
			motors.frontRight.Run();
			motors.spinn.Run();
			motors.frontLeft.Run();
			motors.rearLeft.Run();
		break;
		case DEBUG_ORDER_MOTOR_RUN_0:
			motors.rearRight.Run();
		break;
		case DEBUG_ORDER_MOTOR_RUN_1:
			motors.frontRight.Run();
		break;
		case DEBUG_ORDER_MOTOR_RUN_2:
			motors.spinn.Run();
		break;
		case DEBUG_ORDER_MOTOR_RUN_3:
			motors.frontLeft.Run();
		break;
		case DEBUG_ORDER_MOTOR_RUN_4:
			motors.rearLeft.Run();
		break;
		case DEBUG_ORDER_SHOOT:
			
		break;
		case DEBUG_ORDER_WIRELESS_ON:
			wireless.NRF_ON();
		break;
		case DEBUG_ORDER_WIRELESS_OFF:
			wireless.NRF_OFF();
		break;		
	};
}



