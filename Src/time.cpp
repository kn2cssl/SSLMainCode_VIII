#include "time.hpp"
#include "Logger.hpp"

TIM_HandleTypeDef *Time::mili;
TIM_HandleTypeDef *Time::micro;
unsigned int Time::s;
bool Time::isValid = false;

void Time::Init(TIM_HandleTypeDef *mil,TIM_HandleTypeDef *mic)
{
	mili = mil;
	micro = mic;
	HAL_TIM_Base_Start_IT(mili);
	HAL_TIM_Base_Start(mic);
	s = 0;
	isValid = true;
	logger.Log((char*)"Timers Initialized");
}
float Time::Get_Time()
{
	return (float)s + ((float)(mili ->Instance -> CNT) / (float)2000.0) + ((float)(micro ->Instance -> CNT) / (float)1000000.0) ;
}
unsigned int Time::Get_Second()
{
	return s;
}
unsigned short int Time::Get_Mili_Second()
{
	return (mili ->Instance -> CNT) / float(2);
}
unsigned short int Time::Get_Micro_Second()
{
	return (micro ->Instance -> CNT);
}
void Time::Time_Passed(TIM_HandleTypeDef* htim)
{
	if (htim == mili)
	{
		s++;
	}
}
