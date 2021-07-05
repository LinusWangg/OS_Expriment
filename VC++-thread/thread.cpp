#include<iostream>
#include<windows.h>
using namespace std;
HANDLE hMutex = NULL;//ª•≥‚¡ø

DWORD WINAPI Fun(LPVOID lpParamter) {
	cout << "A Thread Fun Display!" << endl;
	return 0L;
}

DWORD WINAPI Fun2(LPVOID lpParamter) {
	cout << "Another Thread Fun Display!" << endl;
	return 0L;
}

HANDLE h1[10];
HANDLE h2[10];

int main()
{
	for (int i = 0; i < 10; i++)
		h1[i] = CreateThread(NULL, 0, Fun, NULL, 0, NULL);
	for (int i = 0; i < 10; i++)
		h2[i] = CreateThread(NULL, 0, Fun2, NULL, 0, NULL);
	for (int i = 0; i < 10; i++) {
		WaitForSingleObject(h1[i], INFINITE);
		WaitForSingleObject(h2[i], INFINITE);
	}
	for (int i = 0; i < 10; i++) {
		CloseHandle(h1[i]);
		CloseHandle(h2[i]);
	}
	return 0;
}

