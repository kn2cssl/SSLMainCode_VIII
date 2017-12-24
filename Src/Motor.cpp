#include "Motor.hpp"
#include "Logger.hpp"
#include "main.h"
#include "debugger.hpp"
#include "Memory.hpp"

UART_HandleTypeDef* MotorsNetwork::huart[5];
signed short int MotorsNetwork::setedRPM[5];
signed short int MotorsNetwork::momentomRPM[5];
unsigned char MotorsNetwork::buffer[5][4];
const unsigned char MotorsNetwork::START_BYTE = 0xAA;
const unsigned char MotorsNetwork::STOP_BYTE = 0x55;
bool MotorsNetwork::isOn[5];

RearRightMotor Motors::rearRight;
FrontRightMotor Motors::frontRight;
SpinnMotor Motors::spinn;
FrontLeftMotor Motors::frontLeft;
RearLeftMotor Motors::rearLeft;	

void MotorsNetwork::Transmit_Ended(UART_HandleTypeDef* h)
{
	for (unsigned char i = 0 ; i < 5 ; i++)
		if (huart[i] == h)
			HAL_UART_Receive_IT(huart[i],buffer[i],4);
}
void MotorsNetwork::Receive_Ended(UART_HandleTypeDef* h)
{
	for (unsigned char i = 0 ; i < 5 ; i++)
		if (huart[i] == h)
		{
			if (buffer[i][0] == START_BYTE && buffer[i][3] == STOP_BYTE)
			{
				momentomRPM[i] = buffer[i][1] * 256 + buffer[i][2];
				Toggle_LED(i);
			}
		}
}
void MotorsNetwork::Init(UART_HandleTypeDef* motorRightDown,UART_HandleTypeDef* motorRightTop,UART_HandleTypeDef* spinn,UART_HandleTypeDef* motorLeftTop,UART_HandleTypeDef* motorLeftDown)
{
	huart[0] = motorRightDown;
	huart[1] = motorRightTop;
	huart[2] = spinn;
	huart[3] = motorLeftTop;
	huart[4] = motorLeftDown;
	for (unsigned char i = 0 ; i < 5 ; i ++)
	{
		setedRPM[i] = 0;
		momentomRPM[i] = 0;
		isOn[i] = true;
	}
	logger.Log((char *)"Motors Initialized");
}
void MotorsNetwork::Send_Data(unsigned char motorNumber)
{
	static unsigned char str[5][4];
	str[motorNumber][0] = START_BYTE;
	if (isOn[motorNumber])
	{
		str[motorNumber][1] = ((unsigned short int)setedRPM[motorNumber] / 256);
		str[motorNumber][2] = ((unsigned short int)setedRPM[motorNumber] % 256);
	}
	else 
	{
		str[motorNumber][1] = 0;
		str[motorNumber][2] = 0;
	}
	str[motorNumber][3] = STOP_BYTE;
	HAL_UART_Transmit_IT(huart[motorNumber],str[motorNumber],4);	
}
void MotorsNetwork::Set_RPM(unsigned char motorNumber,signed short int RPM)
{
	setedRPM[motorNumber] = RPM;
	Send_Data(motorNumber);
}
signed short int MotorsNetwork::Get_RPM(unsigned char motorNumber)
{
	return momentomRPM[motorNumber];
}
signed short int MotorsNetwork::Get_SetedRPM(unsigned char motorNumber)
{
	return setedRPM[motorNumber];
}
void MotorsNetwork::Stop(unsigned char motorNumber)
{
	isOn[motorNumber] = false;
	Send_Data(motorNumber);
}
void MotorsNetwork::Run(unsigned char motorNumber)
{
	isOn[motorNumber] = true;
	Send_Data(motorNumber);	
}
void MotorsNetwork::Toggle_LED(unsigned char i)
{
	switch(i)
	{
		case 0:
			HAL_GPIO_TogglePin(MD3_GPIO_Port,MD3_Pin);
		break;
		case 1:
			HAL_GPIO_TogglePin(MD4_GPIO_Port,MD4_Pin);
		break;
		case 2:
			HAL_GPIO_TogglePin(MDSpinn_GPIO_Port,MDSpinn_Pin);
		break;
		case 3:
			HAL_GPIO_TogglePin(MD1_GPIO_Port,MD1_Pin);
		break;
		case 4:
			HAL_GPIO_TogglePin(MD2_GPIO_Port,MD2_Pin);
		break;
	};
}

void RearRightMotor::Set_RPM(signed short int RPM)
{
	motorsNetwork.Set_RPM(0,RPM);
}
signed short int RearRightMotor::Get_RPM()
{
	return motorsNetwork.Get_RPM(0);
}
signed short int RearRightMotor::Get_SetedRPM()
{
	return motorsNetwork.Get_SetedRPM(0);
}
void RearRightMotor::Stop()
{
	motorsNetwork.Stop(0);
}
void RearRightMotor::Run()
{
	motorsNetwork.Run(0);
}

void FrontRightMotor::Set_RPM(signed short int RPM)
{
	motorsNetwork.Set_RPM(1,RPM);
}
signed short int FrontRightMotor::Get_RPM()
{
	return motorsNetwork.Get_RPM(1);
}
signed short int FrontRightMotor::Get_SetedRPM()
{
	return motorsNetwork.Get_SetedRPM(1);
}
void FrontRightMotor::Stop()
{
	motorsNetwork.Stop(1);
}
void FrontRightMotor::Run()
{
	motorsNetwork.Run(1);
}

void SpinnMotor::Set_RPM(signed short int RPM)
{
	motorsNetwork.Set_RPM(2,RPM);
}
signed short int SpinnMotor::Get_RPM()
{
	return motorsNetwork.Get_RPM(2);
}
signed short int SpinnMotor::Get_SetedRPM()
{
	return motorsNetwork.Get_SetedRPM(2);
}
void SpinnMotor::Stop()
{
	motorsNetwork.Stop(2);
}
void SpinnMotor::Run()
{
	motorsNetwork.Run(2);
}

void FrontLeftMotor::Set_RPM(signed short int RPM)
{
	motorsNetwork.Set_RPM(3,RPM);
}
signed short int FrontLeftMotor::Get_RPM()
{
	return motorsNetwork.Get_RPM(3);
}
signed short int FrontLeftMotor::Get_SetedRPM()
{
	return motorsNetwork.Get_SetedRPM(3);
}
void FrontLeftMotor::Stop()
{
	motorsNetwork.Stop(3);
}
void FrontLeftMotor::Run()
{
	motorsNetwork.Run(3);
}

void RearLeftMotor::Set_RPM(signed short int RPM)
{
	motorsNetwork.Set_RPM(4,RPM);
}
signed short int RearLeftMotor::Get_RPM()
{
	return motorsNetwork.Get_RPM(4);
}
signed short int RearLeftMotor::Get_SetedRPM()
{
	return motorsNetwork.Get_SetedRPM(4);
}
void RearLeftMotor::Stop()
{
	motorsNetwork.Stop(4);
}
void RearLeftMotor::Run()
{
	motorsNetwork.Run(4);
}

void Motors::Set_RPM_From_Memory(void)
{
	rearRight.Set_RPM(memory.motorsSetPoints.rearRight);
	frontRight.Set_RPM(memory.motorsSetPoints.frontRight);
	spinn.Set_RPM(memory.motorsSetPoints.spinn);
	frontLeft.Set_RPM(memory.motorsSetPoints.frontLeft);
	rearLeft.Set_RPM(memory.motorsSetPoints.rearLeft);
}

