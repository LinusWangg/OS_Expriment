#include <iostream>   
#include <windows.h> 
#include<graphics.h>
using namespace std;
void Line_Midpoint(int x1, int y1, int x2, int y2, int color)
{
	int x = x1, y = y1;
	int a = y1 - y2, b = x2 - x1;
	int cx = (b >= 0 ? 1 : (b = -b, -1));
	int cy = (a <= 0 ? 1 : (a = -a, -1));

	putpixel(x, y, color);

	int d, d1, d2;
	if (-a <= b)		// 斜率绝对值 <= 1
	{
		d = 2 * a + b;
		d1 = 2 * a;
		d2 = 2 * (a + b);
		while (x != x2)
		{
			if (d < 0)
				y += cy, d += d2;
			else
				d += d1;
			x += cx;
			putpixel(x, y, color);
			Sleep(10);
		}
	}
	else				// 斜率绝对值 > 1
	{
		d = 2 * b + a;
		d1 = 2 * b;
		d2 = 2 * (a + b);
		while (y != y2)
		{
			if (d < 0)
				d += d1;
			else
				x += cx, d += d2;
			y += cy;
			putpixel(x, y, color);
			Sleep(10);
		}
	}
}


DWORD WINAPI Line1(LPVOID lpParamter)
{
	Line_Midpoint(100, 1, 1, 478, GREEN);
	return NULL;
}

DWORD WINAPI Line2(LPVOID lpParamter)
{
	Line_Midpoint(1, 478, 638, 1, GREEN);
	return NULL;
}

int main()
{
	initgraph(640, 480);

	HANDLE hThread1 = CreateThread(NULL, 0, Line1, NULL, 0, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, Line2, NULL, 0, NULL);

	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);

	CloseHandle(hThread1);
	CloseHandle(hThread2);

	getchar();
	closegraph();
	return 0;
}