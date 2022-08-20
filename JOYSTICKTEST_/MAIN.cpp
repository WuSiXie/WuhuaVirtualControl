#include<iostream>
#include<windows.h>
#define DEVICE_SYM L"\\\\.\\WuhuaController"
//¶ÁÉè±¸
#define READ_CTL_CODE CTL_CODE(FILE_DEVICE_UNKNOWN,0x830,METHOD_BUFFERED,FILE_READ_ACCESS)

//Ð´Éè±¸
#define WRITE_CTL_CODE CTL_CODE(FILE_DEVICE_UNKNOWN,0x831,METHOD_BUFFERED,FILE_WRITE_ACCESS)

struct
{
	UINT8 axisX;
	UINT8 axisY;
	UINT8 axisZ;
	UINT8 axisRX;
	UINT8 axisRY;
	UINT8 axisRZ;
	UINT8 axisT;
	unsigned char ButtonG1;
	unsigned char ButtonG2;
	unsigned char ButtonG3;
}Buffer;

VOID printBin(int Numb)
{
	char s[40];
	_itoa_s(Numb, s, 2);
	printf("%s\n", s);
}

DWORD WriteDevice(HANDLE hDevice, UINT8* szBuff, DWORD dwLen)
{
	DWORD dwWrite = 0;
	DeviceIoControl(hDevice, WRITE_CTL_CODE, szBuff, dwLen, NULL, 0, &dwWrite, NULL);
	return dwWrite;
}
int main()
{
	HANDLE hDevice;
	hDevice = CreateFile(DEVICE_SYM, GENERIC_READ | GENERIC_WRITE,0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	printf("handle created\n");
	system("pause");
	if (hDevice == NULL || hDevice == INVALID_HANDLE_VALUE)
	{
		printf("open Device error!\n");
		printf("DRIVER MIGHT NOT WORKING!\n");
		system("pause");
		return 0;
	}
	printf("THE DRIVER IS WORKING PROPERLY\n");
	printf("READY TO ENTER IN TO CONTROLLER TEST\n");
	printf("How many times do you want the program to test?\n");
	int i;
	UINT8 axisnumb = 0;
	bool axisup = true;
	bool SendStatus = false;
	DWORD NOBW;
	scanf_s("%d", &i);
	printf("%d",i);
	while (i!=0)
	{
		NOBW = 0;
		i--;
		printf("NOBW = 0, i--\n");
		if (axisnumb == 127)
			axisup = false;
		else if (axisnumb == -127)
			axisup = true;
		if (axisup)
			axisnumb = axisnumb + 1;
		else
			axisnumb = axisnumb - 1;
		Buffer.axisX = axisnumb;
		Buffer.axisY = axisnumb;
		Buffer.axisZ = axisnumb;
		Buffer.axisRX = axisnumb;
		Buffer.axisRY = axisnumb;
		Buffer.axisRZ = axisnumb;
		Buffer.axisT = axisnumb;
		if (Buffer.ButtonG1)
		{
			Buffer.ButtonG1 = 0;
			Buffer.ButtonG2 = 0;
			Buffer.ButtonG3 = 0;
			printf("if,%d\n%d\n%d\n", Buffer.ButtonG1, Buffer.ButtonG2, Buffer.ButtonG3);
		}
		else
		{
			Buffer.ButtonG1 = 0B11110000;
			Buffer.ButtonG2 = 255;
			Buffer.ButtonG3 = 255;
			printf("else,%d\n%d\n%d\n", Buffer.ButtonG1, Buffer.ButtonG2, Buffer.ButtonG3);
		}
		printBin(Buffer.axisX);
		printBin(Buffer.axisY);
		printBin(Buffer.axisZ);
		printBin(Buffer.axisRX);
		printBin(Buffer.axisRY);
		printBin(Buffer.axisRZ);
		printBin(Buffer.axisT);
		printBin(Buffer.ButtonG1);
		printBin(Buffer.ButtonG2);
		printBin(Buffer.ButtonG3);
		printf("axis&button set\n");
		SendStatus = WriteFile(hDevice, &Buffer, 10, &NOBW, NULL);
		printf("fileWrited\n");
		if (!SendStatus)
		{
			printf("Sending Failure\n");
			break;
		}
		printf("Sending SUCCESS %d times remaning\n", i);

	}

	CloseHandle(hDevice);
	system("pause");
	return 0;

}
