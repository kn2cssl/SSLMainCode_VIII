#ifndef __DEBUGGER_HPP__
#define __DEBUGGER_HPP__

static class Debugger
{
	private:
		static char str[256];
		static char logStr[256];
		static unsigned int logLine;
		static bool isConnected;
		void puts(char* str,unsigned int l);
	public:
		void Init(void);
		void Print(const char* format, ...);
		void Log(const char* format, ...);
		void Error(const char* format, ...);
}debugger;


#endif
