#ifndef __ERROR_HPP__
#define __ERROR_HPP__

enum ErrorMode
{
	BATTRY_LOW = 0,
	NRF_NOT_OKAY = 1,   //high 0.9
	IMU_NOT_OKAY = 2,   //high 0.5
	SHOOT_NOT_OKAY = 3, //low 0.5
	MOTOR_NOT_OKAY = 4  //low 0.9
};

static class Error
{
	private:
		static float freq[5];
		static float pulse[5];
	public:
		void Happend(ErrorMode em,char errorStr[256]);
}error;

#endif
