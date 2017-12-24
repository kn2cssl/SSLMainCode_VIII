#include "Logger.hpp"
#include "USB.hpp"
#include "debugger.hpp"
#include "time.hpp"

unsigned int Logger::logLine = 0;
void Logger::Log(char logStr[256])
{
	if (time.isValid)
	{
		USB.Log("<Log Line: %d at t = %f > \"%s\" \r\n",logLine,time.Get_Time(),logStr);
		debugger.Log("<Log Line: %d at t = %f > \"%s\" \r\n",logLine,time.Get_Time(),logStr);
	}
	else
	{
		USB.Log("<Log Line: %d at t = %f > \"%s\" \r\n",logLine,(float)0,logStr);
		debugger.Log("<Log Line: %d at t = %f > \"%s\" \r\n",logLine,(float)0,logStr);
	}
	logLine++;
}
