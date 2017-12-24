#include "memory.hpp"
#include "Logger.hpp"
#include "Settings.hpp"
#include <math.h>
#include "IMU.hpp"
#include "Time.hpp"
#include <math.h>

char Memory::order[32];
char Memory::response[32];
WirelessOrderData Memory::orderStruct;
WirelessResponseData Memory::responseStruct;
VisionData Memory::visionData;
MotorSetPoints Memory::motorsSetPoints;
float Memory::lastTime;
float Memory::cst;

void Memory::Init()
{
	Clear_Wireless_Data();
	Free_Wheel();
	lastTime = 0;
	logger.Log((char *)"Memory Initialized");	
}
void Memory::Clear_Wireless_Data()
{
	for (unsigned char i = 0 ; i < 32 ; i++)
	{
		order[i] = 0 ;
		response[i] = 0 ;
	}
}
void Memory::Free_Wheel()
{
	order[0] = settings.Get_RID();
	order[1] = 1;
	order[2] = 2;
	order[3] = 3;
	order[4] = 4;
}
void Memory::Update_Order_Struct()
{
	orderStruct.RID = order[0];
	orderStruct.SVX = order[1] * 256 + order[2];
	orderStruct.SVY = order[3] * 256 + order[4];
	orderStruct.SWr = order[5] * 256 + order[6];
	orderStruct.VX = order[7] * 256 + order[8];
	orderStruct.VY = order[9] * 256 + order[10];
	orderStruct.Wr = order[11] * 256 + order[12];
	orderStruct.alpha = order[13] * 256 + order[14];
	orderStruct.kick = order[15];
	orderStruct.chip = order[16];
	orderStruct.spinn = order[17];	
}
void Memory::Update_Response_Struct()
{
	response[15] = responseStruct.SS;
}
void Memory::Update_Vision_Data()
{
	visionData.SVX = (float)orderStruct.SVX / (float)1000;
	visionData.SVY = (float)orderStruct.SVY / (float)1000;
	visionData.SWr = (float)orderStruct.SWr / (float)1000;
	visionData.VX = (float)orderStruct.VX / (float)1000;
	visionData.VY = (float)orderStruct.VY / (float)1000;
	visionData.Wr = (float)orderStruct.Wr / (float)1000;
	visionData.alpha = (float)orderStruct.alpha / (float)1000;
	visionData.cosAlpha = cos(visionData.alpha);
	visionData.sinAlpha = sin(visionData.alpha);
	visionData.SVX = (float)visionData.SVX * visionData.cosAlpha + (float)visionData.SVY * visionData.sinAlpha;
	visionData.SVY = -(float)visionData.SVX * visionData.sinAlpha + (float)visionData.SVY * visionData.cosAlpha;
	visionData.VX = (float)visionData.VX * visionData.cosAlpha + (float)visionData.VY * visionData.sinAlpha;
	visionData.VY = -(float)visionData.VX * visionData.sinAlpha + (float)visionData.VY * visionData.cosAlpha;	
}
void Memory::Set_IMU_Offsets()
{
	if (time.Get_Time() > (float)(1))
	{
		float dvx = float(imu.Get_X_Velocity()) - float(visionData.VX);
		float dvy = float(imu.Get_Y_Velocity()) - float(visionData.VY);
		float dt = time.Get_Time() - lastTime;
		//imu.Set_X_Offset((dvx) / float(100 * cst));
		//imu.Set_Y_Offset((dvy) / float(100 * cst));
		imu.Set_X_Offset((dvx) / (dt * float(cst)));
		imu.Set_Y_Offset((dvy) / (dt * float(cst)));
	}
	lastTime = time.Get_Time();
}
void Memory::Update()
{
	Update_Order_Struct();
	Update_Response_Struct();
	Update_Vision_Data();
	Set_IMU_Offsets();
}
