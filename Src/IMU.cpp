#include "IMU.hpp"
#include "Logger.hpp"
#include "Error.hpp"
#include "Time.hpp"

I2C_HandleTypeDef* IMU::hi2c;
float IMU::xOffset = 0;
float IMU::yOffset = 0;
float IMU::xVelocity = 0;
float IMU::yVelocity = 0;
float IMU::lastTime = 0;
unsigned char IMU::rawXAcceleration[2];
unsigned char IMU::rawYAcceleration[2];
unsigned char IMU::rawWr[2];
IMUState IMU::state;
const unsigned char IMU::ADDRESS = 0xd0;
const float IMU::ACCELERATION_SCALE = 19.56;
const float IMU::W_SCALE =  4.3633;
const unsigned int IMU::OFFSET_TRIALS = 500;

bool IMU::Is_Device_Ready()
{
	if (HAL_I2C_IsDeviceReady(hi2c,ADDRESS,50,100) == HAL_OK)
		return true;
	return false;
}
void IMU::Init(I2C_HandleTypeDef* _hi2c)
{
	hi2c = _hi2c;
	Clear();
	if (Is_Device_Ready())
		logger.Log((char *)"IMU Initialized");
	else 
		error.Happend(IMU_NOT_OKAY,(char *)"IMU Failed at Device Ready");
	Mem_Write_Byte(0x6b,0x00); //awake
	logger.Log((char *)"IMU Getting Offsets");
	Set_X_Offset(Get_X_Offset());
	Set_Y_Offset(Get_Y_Offset());
	logger.Log((char *)"IMU Getting Data");
	Get_Raw_X_Acceleration();
}
void IMU::Clear()
{
	xOffset = 0;
	yOffset = 0;
	xVelocity = 0;
	yVelocity = 0;
	lastTime = 0;
}
void IMU::Mem_Read_Byte(unsigned char memAddr,unsigned char* data)
{
	HAL_I2C_Mem_Read(hi2c,ADDRESS,memAddr,1,data,1,1);
	HAL_GPIO_TogglePin(IMUOk_GPIO_Port,IMUOk_Pin);
}
void IMU::Mem_Write_Byte(unsigned char memAddr,unsigned char data)
{
	HAL_I2C_Mem_Write(hi2c,ADDRESS,memAddr,1,(unsigned char *)&data,1,1);
	HAL_GPIO_TogglePin(IMUOk_GPIO_Port,IMUOk_Pin);
}
void IMU::Get_Raw_X_Acceleration()
{
	HAL_I2C_Mem_Read_IT(hi2c,ADDRESS,0x3b,1,rawXAcceleration,2);
	state = READING_RAW_X_ACCELERATION;
}
float IMU::Get_X_Acceleration()
{
	float ret = 0;
	signed short int data;
	data = (signed)((unsigned short int)rawXAcceleration[0] << 8 | (unsigned short int)rawXAcceleration[1]);
	ret = float(((float)(data)/(float)32767.0) * (float)ACCELERATION_SCALE);
	ret -= xOffset;
	return ret;
}
void IMU::Get_Raw_Y_Acceleration()
{
	HAL_I2C_Mem_Read_IT(hi2c,ADDRESS,0x3d,1,rawYAcceleration,2);
	state = READING_RAW_Y_ACCELERATION;
}
float IMU::Get_Y_Acceleration()
{
	signed short int data;
	float ret;
	data = (signed)((unsigned short int)rawYAcceleration[0] << 8 | (unsigned short int)rawYAcceleration[1]);
	ret = float(((float)(data)/(float)32767.0) * (float)ACCELERATION_SCALE);
	ret -= yOffset;
	return ret;
}
void IMU::Get_Raw_Wr()
{
	HAL_I2C_Mem_Read_IT(hi2c,ADDRESS,0x47,1,rawWr,2);
	state = READING_RAW_WR;
}
float IMU::Get_Wr()
{
	signed short int data;
	float ret;
	data = (signed)((unsigned short int)rawWr[0] << 8 | (unsigned short int)rawWr[1]);
	ret = float(((float)(data)/(float)32767.0) * (float)W_SCALE);
	return ret;
}
float IMU::Get_X_Offset()
{
	/*float max = -1000;
	float min = 1000;
	float x;
	for(unsigned int t = 0; t <= OFFSET_TRIALS; t++)
	{
		x = Get_X_Acceleration();
		if(max < x)
			max = x;
		if(min > x)
			min = x;
	}
	return (max+min)/(float)2.0;*/
	return 0;
}
float IMU::Get_Y_Offset()
{
	/*float max = -1000;
	float min = 1000;
	float x;
	for(unsigned int t = 0; t <= OFFSET_TRIALS; t++)
	{
		x = Get_Y_Acceleration();
		if(max < x)
			max = x;
		if(min > x)
			min = x;
	}
	return (max+min)/(float)2.0;	*/
	return 0;
}
void IMU::Set_X_Offset(float offset)
{
	xOffset += offset;
	if (xOffset > float(18))
		xOffset = 18;
	else if (xOffset < float(-18))
		xOffset = -18;
		
	//xOffset = offset;
}
void IMU::Set_Y_Offset(float offset)
{
	yOffset += offset;
	//yOffset = offset;
}
void IMU::Calculate()
{
	if (lastTime != 0)
	{
		xVelocity += Get_X_Acceleration() * (time.Get_Time() - lastTime);
		yVelocity += Get_Y_Acceleration() * (time.Get_Time() - lastTime);
	}
	lastTime = time.Get_Time();
}
float IMU::Get_X_Velocity()
{
	return xVelocity;
}
float IMU::Get_Y_Velocity()
{
	return yVelocity;
}
void IMU::Read_Finished(I2C_HandleTypeDef* hi2c)
{
	if (hi2c != IMU::hi2c)
		return;
	HAL_GPIO_TogglePin(IMUOk_GPIO_Port,IMUOk_Pin);
	switch(state)
	{
		case READING_RAW_X_ACCELERATION:
			Get_Raw_Y_Acceleration();
			return;
		case READING_RAW_Y_ACCELERATION:
			Get_Raw_Wr();
			return;
		case READING_RAW_WR:
			Get_Raw_X_Acceleration();
			return;
	};
}
