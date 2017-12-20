#ifndef __USB_HPP__
#define __USB_HPP__

//copy this shit into usbd_cdc_if.cpp under CDC_Receive definition
//USB.Listen(Buf,Len);

static class USB
{
	private:
		static char str[256];
		static bool isConnected;
	public:
		static char buffer[256];
		static unsigned int length;
		void Init(void);
		void Print(const char* format, ...);
		void Log(const char* format, ...);
		void Error(const char* format, ...);
		void Listen(unsigned char * Buf, unsigned int *Len);
}USB;

#endif 
