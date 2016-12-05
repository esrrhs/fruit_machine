#include <stdio.h>
#include <windows.h>
#include <WinBase.h>
#include <ctime>
#include <stdint.h>

char g_data[20] = {0};
void ini()
{
	for (int i = 0; i < 20; i++)
	{
		g_data[i] = 'o';
	}
}

void gotoxy(int x, int y)       //将光标移动到坐标为(x,y)的地方
{
	CONSOLE_SCREEN_BUFFER_INFO    csbiInfo;
	HANDLE    hConsoleOut;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void show(int cur)
{
	ini();

	while (cur > 20)
	{
		cur -= 20;
	}
	g_data[(int)cur] = '*';
	gotoxy(0, 0);

	for (int i = 0; i < 6; i++)
	{
		putchar(g_data[i]);
		putchar(' ');
	}
	putchar('\n');

	putchar(g_data[19]);
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(g_data[6]);
	putchar('\n');

	putchar(g_data[18]);
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(g_data[7]);
	putchar('\n');

	putchar(g_data[17]);
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(g_data[8]);
	putchar('\n');

	putchar(g_data[16]);
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(' ');
	putchar(g_data[9]);
	putchar('\n');

	for (int i = 15; i >= 10; i--)
	{
		putchar(g_data[i]);
		putchar(' ');
	}
	putchar('\n');
}

float getspeed(float distance)
{
	float speed = 2;
	if (distance > 2)
	{
		distance -= 2;
		speed = 5;
	}
	if (distance > 5)
	{
		distance -= 5;
		speed = 10;
	}
	if (distance > 10)
	{
		distance -= 10;
		speed = 30;
	}
	if (distance > 4 * 30)
	{
		distance -= 30;
		speed = 50;
	}
	return speed;
}

void update(int begin, int end, int distance)
{
	uint32_t last = (uint32_t)GetTickCount();
	float cur = begin;
	int realend = begin + distance;
	while (1)
	{
		uint32_t now = (uint32_t)GetTickCount();
		float elapse = float(now - last) / 1000;
		last = now;

		float speed = getspeed(realend - cur);

		cur += elapse * speed;
		
		if (cur >= realend)
		{
			show(end);
			break;
		}

		show(cur);

		Sleep(10);
	}
}

float getdistance(float time)
{
	float distance = 0;
	float elapse = 1;
	while (time >= 0)
	{
		if (time >= 5)
		{
			distance += elapse * 50;
		}
		else if (time >= 4)
		{
			distance += elapse * 30;
		}
		else if (time >= 3)
		{
			distance += elapse * 10;
		}
		else if (time >= 2)
		{
			distance += elapse * 5;
		}
		else if (time >= 1)
		{
			distance += elapse * 2;
		}

		time -= elapse;
	}
		
	return distance;
}

void calcbegin(int begin, int end, float runtime, int & newbegin, int & distance)
{
	int len = end >= begin ? end - begin : 20 - begin + end;
	distance = (int)getdistance(runtime);
	if (distance >= len)
	{
		newbegin = begin;

		begin += distance;
		begin %= 20;
		if (begin > end)
		{
			distance += 20 - begin + end;
		}
		if (begin < end)
		{
			distance += end - begin;
		}
	}
	else
	{
		begin = end - distance;
		if (begin < 0)
		{
			begin += 20;
		}
		newbegin = begin;
	}
}

void run()
{
	int begin = 0;
	int end = 19;
	int runtime = 1;

	int newbegin = 0;
	int distance = 0;

	calcbegin(begin, end, runtime, newbegin, distance);
		
	update(newbegin, end, distance);
}

int main()
{
	ini();
	run();
	printf("end");
	getchar();
	return 0;
}