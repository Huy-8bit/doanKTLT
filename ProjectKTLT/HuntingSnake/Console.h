#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>

#include "Snake.h"

using namespace std;

#pragma warning (disable: 4996)

// COLOR
#define COLOR_BLUE				1
#define COLOR_GREEN				2
#define COLOR_LIGHT_BLUE		3
#define COLOR_RED				4
#define COLOR_PURPLE			5
#define COLOR_YELLOW			6
#define COLOR_WHITE				7

// MUSIC 
#define MAIN_MUSIC				1
#define MENU_MUSIC				2
#define DEAD_MUSIC				3

// VALUE FOR STATE
#define LIVE					1
#define DEAD					0

// CONTROL KEY
#define ESC_KEY					27
#define ENTER_KEY				13
#define PAUSE_KEY				'P'
#define SAVE_KEY				'F'
#define LOAD_KEY				'L'
#define UP_KEY					'w'
#define DOWN_KEY				's'
#define LEFT_KEY				'a'
#define RIGHT_KEY				'd'

// Text in game menu
#define newgame_Menu			"NEW GAME"
#define highlength_Menu			"HIGH LENGTH"
#define setting_Menu			"SETTING"
#define exitgame_Menu			"EXIT GAME"

#define yes_Text				"Yes"
#define no_Text					"No"
#define ok_Text					"OK"
#define exit_Text				"Exit"
#define resume_Text				"Resume"


extern int CONSOLE_HEIGH;
extern int CONSOLE_WIDTH;
extern int BORDER_HEIGH;
extern int BORDER_WIDTH;

extern POINT LENGTH_POS;
extern POINT ROUND_POS;

extern int pressedKey;

void GotoXY(POINT P);

void GotoXY(int x, int y);

void FixConsoleWindow();

void turnMusic(int index);

void printGameLogo();

void printWinnerBanner();

void drawBoard(int x, int y, int width, int height);

void drawOutLine(int x, int y, int width, int height);

void drawBorderForSaveLoadBox(int x, int y, int width, int height);

// GATE
void randomPositionOfGate();
void drawGate();
void deleteGate();

void displaySnakeSize();

void displayRoundNumber();

void deleteBox(int row, int column);

void deleteSnake();

void deleteFood();

void deleteEntityOnScreen();

void clearScreen();

void printColorText(int color, string text);

void goToXYAndPrintColorText(POINT P, string text, int color = 7);

void resetPressedKey();