#include "SerialPort.h"

int main()
{
	const char* name = "/dev/ttyUSB0";
	SerialPort port = SerialPort(name, true);
	while (true)
		printf("%c", port.GetByte());
	return 0;
}