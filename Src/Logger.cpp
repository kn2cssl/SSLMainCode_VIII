#include "Logger.hpp"
#include "USB.hpp"
#include "debugger.hpp"

unsigned int Logger::logLine = 0;
void Logger::Log(char logStr[256])
{
	USB.Log("<Log Line: %d > \"%s\" \r\n",logLine,logStr);
	debugger.Log("<Log Line: %d > \"%s\" \r\n",logLine,logStr);
	logLine++;
}
