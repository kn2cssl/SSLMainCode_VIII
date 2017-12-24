#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

struct WirelessOrderData
{
	unsigned char RID;
	signed short int SVX;
	signed short int SVY;
	signed short int SWr;
	signed short int VX;
	signed short int VY;
	signed short int Wr;
	signed short int alpha;
	unsigned char kick;
	unsigned char chip;
	unsigned char spinn;
};
struct VisionData
{
	float SVX;
	float SVY;
	float SWr;
	float VX;
	float VY;
	float Wr;
	float alpha;	
	float cosAlpha;
	float sinAlpha;
};
struct WirelessResponseData
{
	unsigned char SS;
};
struct MotorSetPoints
{
	signed short int rearRight;
	signed short int frontRight;
	signed short int spinn;
	signed short int frontLeft;
	signed short int rearLeft;	
};
static class Memory
{
	private:
		void Update_Order_Struct();
		void Update_Response_Struct();
		void Update_Vision_Data();
		void Set_IMU_Offsets();
		static float lastTime;
	public:
		static char order[32];						//wireless data comming into robot
		static char response[32];				//wireless data going out of robot
		static WirelessOrderData orderStruct;
		static WirelessResponseData responseStruct;
		static VisionData visionData;
		static MotorSetPoints motorsSetPoints;
		static float cst;
	
		void Init();
		void Clear_Wireless_Data();
		void Free_Wheel();
		void Update();
}memory;

#endif 
