#ifndef ARDUINO_SERIAL_H
#define ARDUINO_SERIAL_H

#include <windows.h>
#include <stdio.h>

class ArduinoSerial
{
	public:
		//members
		char* portIdentifier;

		//methods
		ArduinoSerial(char* portName);
		~ArduinoSerial();
		void connect(char* portName);
		void disconnect();
		bool isConnected();
		bool testConnection();
		int readData(char *buffer, unsigned int nbChar);
		bool writeData(char* buffer,unsigned int nbChar);
	private:
		//members
		HANDLE hSerial;
		bool connected;
		COMSTAT status;
		DWORD errors;
};

#endif
