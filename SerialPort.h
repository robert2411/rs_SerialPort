/**************************************************************************************\
									SerialPort.h

Author		:	R.J.H.M.	Stevens
Begin		:	27-11-2014
				
Version		:	1.0.0

TODO		:	

Description	:	This is a cross platform serialPort Class

Dependencies:	

Changes		:
				03-11-2014	-		

\**************************************************************************************/
#ifndef SERIALPORT_H_
#define SERIALPORT_H_

#include <stdio.h>

/* linux files */
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

class SerialPort
{
	public:
		SerialPort(const char* portName, bool debugModues = false);
		~SerialPort();
		int Write(char* message);
		char* GetBuffer();
		char ReadByte();
	protected:
		int OpenPort();
		int ClosePort();
		
		bool m_portIsOpen;
		bool m_debugModus;
		const char* mp_portName;
		
		/*linux variable */
		
		int m_fd1;
		char* m_buff;
		char* m_buffer;
		char* m_bufptr;
		int m_wr;
		int m_nbytes;
		int m_tries;
		
};
#endif