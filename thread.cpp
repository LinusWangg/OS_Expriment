#include<iostream>
#include<windows.h>
using namespace std;

DWORD WINAPI Fun(LPVOID lpParamter){
	for (int i = 0; i < 10; i++)
        cout << "A Thread Fun Display!" << endl;Sleep(200);
    return 0L;
}

int main()
{
    HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);
    CloseHandle(hThread);
    for (int i = 0; i < 10; i++)
        cout << "Main Thread Display!" << endl;Sleep(500);
    return 0;
}
