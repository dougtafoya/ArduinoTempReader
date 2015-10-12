#include "ArduinoSerial.h"

ArduinoSerial::ArduinoSerial(char* portName)
{
	this->connected = false;
	this->connect(portName);
}

ArduinoSerial::~ArduinoSerial()
{
	if(this->connected)
	{
		this->disconnect();	
	}	
}

void ArduinoSerial::connect(char* portName)
{
	if(!this->connected)
	{
		this->hSerial = CreateFile(portName,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

		if(this->hSerial == INVALID_HANDLE_VALUE)
		{
			if(GetLastError() == ERROR_FILE_NOT_FOUND)
			{
				printf("Error handle could not be attached to port %s\n",portName);
			}
			else
			{
				printf("General error attaching handle to port!\n");
			}
		}
		else
		{
			DCB dcbSerialParams = {0};

			if(!GetCommState(this->hSerial,&dcbSerialParams))
			{
				printf("Failed to get current serial params\n");
			}
			else
			{
				dcbSerialParams.BaudRate = CBR_9600;
				dcbSerialParams.ByteSize = 8;
				dcbSerialParams.StopBits = ONESTOPBIT;
				dcbSerialParams.Parity = NOPARITY;

				dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;

				if(!SetCommState(hSerial,&dcbSerialParams))
				{
					printf("Could not set serial port parameters\n");
				}
				else
				{
					this->portIdentifier = portName;
					this->connected = true;
					PurgeComm(this->hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
					Sleep(2000);
					printf("Successfully connected to %s\nPress F12 to quit\n",portName);
				}
			}
		}
	}
	else
	{
		printf("Already connected to %s\n", this->portIdentifier);
	}	
}

void ArduinoSerial::disconnect()
{
	if(this->connected)
	{
		printf("Disconnecting from port %s\n",portIdentifier);
		CloseHandle(this->hSerial);
		this->connected = false;
	}
	else
	{
		printf("Connection is not currently open\n");
	}
}

bool ArduinoSerial::isConnected()
{
	//need to add code to check connection
	return this->connected;
}

int ArduinoSerial::readData(char *buffer, unsigned int nbChar)
{
	//Number of bytes we'll have read
    DWORD bytesRead;
    //Number of bytes we'll really ask to read
    unsigned int toRead;

    //Use the ClearCommError function to get status info on the Serial port
    ClearCommError(this->hSerial, &this->errors, &this->status);

    //Check if there is something to read
    if(this->status.cbInQue > 0)
    {
        if(this->status.cbInQue >= 2)
        {
        	toRead = 2;
        }
        else
        {
        	toRead = this->status.cbInQue;
        }

        //Try to read the require number of chars, and return the number of read bytes on success
        if(ReadFile(this->hSerial, buffer, toRead, &bytesRead, NULL))
        {
        	PurgeComm(this->hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
            return bytesRead;
        }
        else
        {
        	return -1;
        }
    }

    //if we get here it means we have no data from board meaning its disconnected?
    //printf("Connection lost from %s\n",this->portIdentifier);
    //this->connected = false;
    return 0;

}

bool ArduinoSerial::writeData(char* buffer,unsigned int nbChar)
{
	DWORD bytesSend;
    //Try to write the buffer on the Serial port
    if(!WriteFile(this->hSerial, (void *)buffer, nbChar, &bytesSend, 0))
    {
        //In case it don't work get comm error and return false
        ClearCommError(this->hSerial, &this->errors, &this->status);

        return false;
    }
    else
    {
    	return true;
    }
}
