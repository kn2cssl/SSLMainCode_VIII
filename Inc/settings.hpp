#ifndef __SETTINGS_HPP__
#define __SETTINGS_HPP__

#include <stdbool.h>

static class Settings
{
	private:
		static unsigned char RID;
		static bool RIDReaded;
		void Read_RID(void);
	public:
		static const bool USBDebugON;
		static const bool USBErrorON;
		static const bool DebuggerDebugON;
		static const bool DebuggerErrorON;
		static const bool buzzerON;	
		unsigned char Get_RID(void);
}settings;

#endif
