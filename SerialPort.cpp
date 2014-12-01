#include "SerialPort.h"
/* this class is based on code from http://softexpert.wordpress.com/2007/10/18/how-to-connect-to-a-serial-port-in-linux-using-c/ */

SerialPort::SerialPort(const char* portName, bool debugModues)
{
	m_debugModus = debugModues;
	mp_portName = portName;
	m_boudRate = 9600;
	m_portIsOpen = false;
	
	if(m_debugModus) printf("The serialPort class started in debug modus!\r\n");
	
	OpenPort();
	SetParams();
	
}

int SerialPort::OpenPort()
{
	if(m_debugModus) printf("Ser: Opening port\r\n");
	
	m_fd1=open(mp_portName, O_RDWR | O_NOCTTY );//| O_NDELAY);

	if (m_fd1 == -1 )
	{
		if(m_debugModus) printf("open_port: Unable to open %s\r\n",mp_portName);
		m_portIsOpen = false;
	}
	else
	{
		fcntl(m_fd1, F_SETFL,0);
		if(m_debugModus) printf("Port 1 has been sucessfully opened and %d is the file description \r\n",m_fd1);
		m_portIsOpen = true;
	}
}
int SerialPort::SetParams()
{
	/* this function is based on code from http://stackoverflow.com/questions/18108932/linux-c-serial-port-reading-writing */
	struct termios tty;
	struct termios tty_old;
	memset (&tty, 0, sizeof tty);

	/* Save old tty parameters */
	tty_old = tty;

	/* Set Baud Rate */
	cfsetospeed (&tty, (speed_t)B9600);
	cfsetispeed (&tty, (speed_t)B9600);

	/* Setting other Port Stuff */
	tty.c_cflag     &=  ~PARENB;        // Make 8n1
	tty.c_cflag     &=  ~CSTOPB;
	tty.c_cflag     &=  ~CSIZE;
	tty.c_cflag     |=  CS8;

	tty.c_cflag     &=  ~CRTSCTS;       // no flow control
	tty.c_cc[VMIN]      =   1;                  // read doesn't block
	tty.c_cc[VTIME]     =   5;                  // 0.5 seconds read timeout
	tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

	/* Make raw */
	cfmakeraw(&tty);

	/* Flush Port, then applies attributes */
	tcflush( m_fd1, TCIFLUSH );
	
	return 0;
}

char SerialPort::ReadByte()
{
	char byte = -1;
	int returnVal = -2;
	
	if(m_portIsOpen)
		returnVal=read(m_fd1,(void*)&byte,sizeof(char));
	return byte;
}

int SerialPort::Write(void* message, int size)
{
	int wr = -1;
	if(m_portIsOpen)
	{
		wr=write(m_fd1,message,size);
	}
	if (wr != size)
		return -1;
	return 0;
}

int SerialPort::ClosePort()
{
	if (m_portIsOpen)
		close(m_fd1);
}


SerialPort::~SerialPort()
{
	ClosePort();
}
