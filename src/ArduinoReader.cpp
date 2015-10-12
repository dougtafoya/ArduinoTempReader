#include <windows.h>
#include <stdio.h>
#include "StringUtils.h"
#include "ArduinoSerial.h"

#define CHANGE_INTERVAL 5000

int main(int argc, char* argv[], char* envp[])
{
	if(argc > 1)	
	{
		if(compareString(argv[1],"connect"))
		{
			if(argc > 2)
			{
				printf("Connecting to port %s\n", argv[2]);
				
				ArduinoSerial ardtest(argv[2]);
				
				int currentTemp = 0;
				ULONGLONG lastChange = 0;

				while(ardtest.isConnected())
				{
					char buf[128] = "";
					int readResult = ardtest.readData(buf,sizeof(buf));
					
					if(readResult > 0)
					{
						int newTemp = atoi(buf);
						ULONGLONG readTime = GetTickCount64();
						ULONGLONG timeSinceLastChange = readTime - lastChange;
						
						//displaying a change at min of 5 seconds
						if(newTemp != currentTemp && timeSinceLastChange > CHANGE_INTERVAL)
						{
							SYSTEMTIME ct;
							GetLocalTime(&ct);

							printf("[%s: %i bytes at %i/%i/%i %i:%i:%i] Temperature change! Old: %i New: %i\n",ardtest.portIdentifier,readResult,ct.wMonth,ct.wDay,ct.wYear,ct.wHour,ct.wMinute,ct.wSecond,currentTemp,newTemp);	
							currentTemp = newTemp;
							lastChange = readTime;
						}
						
					}
					else if(readResult == -1)
					{
						printf("Read failed\n");
					}

					Sleep(750);

					if(GetAsyncKeyState(VK_F12))
					{
						ardtest.disconnect();
					}

					
					if(GetAsyncKeyState(VK_F11))
					{
						printf("Writting to file\n");

						HANDLE outputFile = CreateFile("outputdata.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
						if(outputFile)
						{
							DWORD bytesWrote;
							WriteFile(outputFile,(void*)buf,stringLength(buf),&bytesWrote,NULL);
						}
						else
						{
							printf("Couldnt open file\n");
						}
						
						CloseHandle(outputFile);
					}
				}
			}
			else
			{
				printf("No port to connect to passed\n");
			}
		}
		else
		{
			printf("Unknown command passed\n");
		}
	}
	else
	{
		printf("No command passed\n");
	}

}
