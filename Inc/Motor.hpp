#ifndef __MOTOR_HPP__
#define __MOTOR_HPP__

#include "stm32f4xx_hal.h"

/*
void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart)
{
	motorsNetwork.Transmit_Ended(huart);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
	motorsNetwork.Receive_Ended(huart);
}
*/

static class MotorsNetwork
{
	private:
		static UART_HandleTypeDef* huart[5];
		static signed short int setedRPM[5];
		static signed short int momentomRPM[5];
		static unsigned char buffer[5][4];
		static const unsigned char START_BYTE;
		static const unsigned char STOP_BYTE;
		static bool isOn[5];
		void Toggle_LED(unsigned char i);
		void Send_Data(unsigned char motorNumber);
	public:
		void Transmit_Ended(UART_HandleTypeDef* h);
		void Receive_Ended(UART_HandleTypeDef* h);
		void Init(UART_HandleTypeDef* motorRightDown,UART_HandleTypeDef* motorRightTop,UART_HandleTypeDef* spinn,UART_HandleTypeDef* motorLeftTop,UART_HandleTypeDef* motorLeftDown);
		void Set_RPM(unsigned char motorNumber,signed short int RPM);
		signed short int Get_SetedRPM(unsigned char motorNumber);
		signed short int Get_RPM(unsigned char motorNumber);
		void Stop(unsigned char motorNumber);
		void Run(unsigned char motorNumber);
}motorsNetwork;

class RearRightMotor
{
	public:
		void Set_RPM(signed short int RPM);
		signed short int Get_SetedRPM();
		signed short int Get_RPM();
		void Stop();
		void Run();
};

class FrontRightMotor
{
	public:
		void Set_RPM(signed short int RPM);
		signed short int Get_SetedRPM();
		signed short int Get_RPM();
		void Stop();
		void Run();
};

class SpinnMotor
{
	public:
		void Set_RPM(signed short int RPM);
		signed short int Get_SetedRPM();
		signed short int Get_RPM();
		void Stop();
		void Run();
};

class FrontLeftMotor
{
	public:
		void Set_RPM(signed short int RPM);
		signed short int Get_SetedRPM();
		signed short int Get_RPM();
		void Stop();
		void Run();
};

class RearLeftMotor
{
	public:
		void Set_RPM(signed short int RPM);
		signed short int Get_SetedRPM();
		signed short int Get_RPM();
		void Stop();
		void Run();
};

static class Motors
{
	public:
		static RearRightMotor rearRight;
		static FrontRightMotor frontRight;
		static SpinnMotor spinn;
		static FrontLeftMotor frontLeft;
		static RearLeftMotor rearLeft;
	  void Set_RPM_From_Memory(void);
}motors;

#endif
