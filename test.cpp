#include "SerialPort.h"

int main()
{
	const char* name = "/dev/ttyUSB0";
	const char* message = "test\r\n";
	SerialPort port = SerialPort(name, true);
	
	while (true)
	{
		//printf("sending message \r\n");
		port.Write((void*)message, 7);
		char byte = port.ReadByte();
		if (byte >= 0)
			printf("%c",byte);
		//sleep(1);
	}
	return 0;
}