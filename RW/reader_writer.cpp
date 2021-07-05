#include <iostream>   
#include <windows.h>   
using namespace std;

int readcount = 0;
HANDLE hsem1 = CreateSemaphore(NULL, 1, 1, NULL); // for readcount
HANDLE mutex = CreateSemaphore(NULL, 1, 1, NULL); // for reader
HANDLE hsem3 = CreateSemaphore(NULL, 1, 1, NULL); // for writer
DWORD WINAPI Reader(LPVOID lpParamter)
{
	int k=0;
	WaitForSingleObject(mutex, 0xFFFFFFFF);
	if (readcount == 0)
		WaitForSingleObject(hsem3, 0xFFFFFFFF);
	WaitForSingleObject(hsem1, 0xFFFFFFFF);
	readcount++;
	k=readcount;
	ReleaseSemaphore(hsem1, 1, NULL);
	ReleaseSemaphore(mutex, 1, NULL);
	cout << "im reading " << readcount << endl;
	cout << "im out " << k << endl;
	WaitForSingleObject(hsem1, 0xFFFFFFFF);
	readcount--;
	ReleaseSemaphore(hsem1, 1, NULL);
	if(readcount==0)
		ReleaseSemaphore(hsem3, 1, NULL);
	return 0L;
}

DWORD WINAPI Writer(LPVOID lpParamter)
{
	WaitForSingleObject(mutex, 0xFFFFFFFF);
	WaitForSingleObject(hsem3, 0xFFFFFFFF);
	cout << "im writing " << endl;
	ReleaseSemaphore(hsem3, 1, NULL);
	ReleaseSemaphore(mutex, 1, NULL);
	return 0L;
}

int main()
{
	HANDLE hThread1 = CreateThread(NULL, 0, Reader, NULL, 0, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, Writer, NULL, 0, NULL);
	HANDLE hThread3 = CreateThread(NULL, 0, Reader, NULL, 0, NULL);
	HANDLE hThread4 = CreateThread(NULL, 0, Reader, NULL, 0, NULL);
	HANDLE hThread5 = CreateThread(NULL, 0, Reader, NULL, 0, NULL);
	HANDLE hThread6 = CreateThread(NULL, 0, Reader, NULL, 0, NULL);
	HANDLE hThread7 = CreateThread(NULL, 0, Reader, NULL, 0, NULL);
	HANDLE hThread8 = CreateThread(NULL, 0, Reader, NULL, 0, NULL);
	HANDLE hThread9 = CreateThread(NULL, 0, Reader, NULL, 0, NULL);
	HANDLE hThread10 = CreateThread(NULL, 0, Writer, NULL, 0, NULL);

	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);
	WaitForSingleObject(hThread3, INFINITE);
	WaitForSingleObject(hThread4, INFINITE);
	WaitForSingleObject(hThread5, INFINITE);
	WaitForSingleObject(hThread6, INFINITE);
	WaitForSingleObject(hThread7, INFINITE);
	WaitForSingleObject(hThread8, INFINITE);
	WaitForSingleObject(hThread9, INFINITE);
	WaitForSingleObject(hThread10, INFINITE);

	CloseHandle(hThread1);
	CloseHandle(hThread2);
	CloseHandle(hThread3);
	CloseHandle(hThread4);
	CloseHandle(hThread5);
	CloseHandle(hThread6);
	CloseHandle(hThread7);
	CloseHandle(hThread8);
	CloseHandle(hThread9);
	CloseHandle(hThread10);
	CloseHandle(hsem1);
	CloseHandle(mutex);
	CloseHandle(hsem3);
	return 0;
}
