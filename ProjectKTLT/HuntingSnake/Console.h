#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

#pragma warning (disable: 4996)

#define COLOR_BLUE				1
#define COLOR_GREEN				2
#define COLOR_LIGHT_BLUE		3
#define COLOR_RED				4
#define COLOR_PURPLE			5
#define COLOR_YELLOW			6
#define COLOR_WHITE				7

void GotoXY(int x, int y);

void printColorText(int color, char* text);

void FixConsoleWindow();

void turnBackgroundMusic(int index);

