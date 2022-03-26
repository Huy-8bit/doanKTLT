#include "Console.h"

void printColorText(int color, char* text)
{
	
	static int __BACKGROUND;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

	GetConsoleScreenBufferInfo(h, &csbiInfo);
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (__BACKGROUND << 4));

	cout << text;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 + (__BACKGROUND << 4));
}

void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void FixConsoleWindow()
{
	RECT ConsoleRect;
	HWND consoleWindow = GetConsoleWindow();
	GetWindowRect(consoleWindow, &ConsoleRect);
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
	MoveWindow(consoleWindow, ConsoleRect.left, ConsoleRect.top, 500, 500, TRUE);
}

void turnBackgroundMusic(int index)
{
	if (index == 1)
		PlaySound(TEXT(".\\Sound\\main.wav"), NULL, SND_LOOP | SND_ASYNC);
	else if (index == 2)
		PlaySound(TEXT("./sound/Background2.WAV"), NULL, SND_LOOP | SND_ASYNC);
	else
		PlaySound(NULL, 0, 0);
}