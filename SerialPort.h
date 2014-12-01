/**************************************************************************************\
									SerialPort.h

Author		:	R.J.H.M.	Stevens
Begin		:	27-11-2014
				
Version		:	1.0.0

TODO		:	

Description	:	This is a cross platform serialPort Class

Dependencies:	

Changes		:
				02-12-2014 - Worked on the baud rate	

\**************************************************************************************/
#ifndef SERIALPORT_H_
#define SERIALPORT_H_

#include <stdio.h>
#include <sstream>
#include <string>

/* linux files */
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <stdlib.h>

template<typename T>
std::string toString(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}
/**
 * This is a simple class to communicate with the serial port on linux it has a fixt baudrate of 9600
 */
class SerialPort
{
	public:
		SerialPort(const char* portName, bool debugModues = false);
		~SerialPort();
		int Write(void* message, int size);
		char ReadByte();
		
	protected:
		int OpenPort();
		int ClosePort();
		int SetParams();
		
		bool m_portIsOpen;
		bool m_debugModus;
		const char* mp_portName;
		int m_boudRate;
		/*linux variable */
		
		int m_fd1;
		
};
#endif
