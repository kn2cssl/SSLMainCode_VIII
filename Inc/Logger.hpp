#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

static class Logger
{
	private:
		static unsigned int logLine;
	public:
		void Log(char logStr[256]);
}logger;

#endif 
