#include "SerialPort.h"
#include <ctime>
int main()
{
	const char* name = "/dev/ttyUSB0";
	const char* message  = "DR150FS";
	const char* message2 = "DL150FS";
	SerialPort port = SerialPort(name, true);
	clock_t start = clock();
	while (true)
	{
		if ((clock()-start)/CLOCKS_PER_SEC > 1)
		{
			start = clock();
			printf("sending message \r\n");
			port.Write((void*)message, sizeof(message));
			port.Write((void*)message2, sizeof(message2));
		}
		char byte = port.ReadByte();
		while (byte != -1)
		{
			printf("%c",byte);
			byte = port.ReadByte();
		}
		//sleep(1);
	}
	return 0;
}
