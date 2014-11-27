#this will command all the files
NAME = serialPort
CC = g++
all:
	$(CC)  test.cpp SerialPort.cpp -o $(NAME)
clean:
	rm -rf $(NAME)
