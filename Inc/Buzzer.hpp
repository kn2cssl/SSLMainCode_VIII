#ifndef __BUZZER_HPP__
#define __BUZZER_HPP__

#include <stdbool.h>

static class Buzzer
{
	public:
		void Wave(float freq,float pulse = 0.5); //is 1 second
		void Set_State(bool state);
}buzzer;

#endif

