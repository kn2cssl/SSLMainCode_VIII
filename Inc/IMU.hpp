#ifndef __IMU_HPP__
#define __IMU_HPP__

#include "stm32f4xx_hal.h"
#include <stdbool.h>

enum IMUState
{
	READING_RAW_X_ACCELERATION,
	READING_RAW_Y_ACCELERATION,
	READING_RAW_WR
};

static class IMU
{
	private:
		static I2C_HandleTypeDef* hi2c;
		static float yOffset;
		static float xVelocity;
		static float yVelocity;
		static float lastTime;
		static unsigned char rawXAcceleration[2];
		static unsigned char rawYAcceleration[2];
		static unsigned char rawWr[2];
		static IMUState state;
		static const unsigned char ADDRESS;
		static const float ACCELERATION_SCALE;
		static const float W_SCALE;
		static const unsigned int OFFSET_TRIALS;
		bool Is_Device_Ready();
		void Mem_Read_Byte(unsigned char memAddr,unsigned char* data);
		void Mem_Write_Byte(unsigned char memAddr,unsigned char data);
		void Get_Raw_X_Acceleration();
		void Get_Raw_Y_Acceleration();
		void Get_Raw_Wr();
		float Get_X_Acceleration();
		float Get_Y_Acceleration();
		float Get_X_Offset();
		float Get_Y_Offset();
	public:
		static float xOffset;
		void Clear();
		void Init(I2C_HandleTypeDef* _hi2c);
		void Set_X_Offset(float offset);
		void Set_Y_Offset(float offset);
		void Calculate();
		float Get_X_Velocity();
		float Get_Y_Velocity();
		float Get_Wr();
		void Read_Finished(I2C_HandleTypeDef* hi2c);
}imu;


#endif
