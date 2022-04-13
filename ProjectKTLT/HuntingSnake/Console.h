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
#define MENU_MUSIC				1
#define LEVEL_UP_MUSIC			2
#define DEAD_MUSIC				3
#define TYPE_KEY_SOUND			4
#define LOADING_SOUND			5
#define STARTING_SOUND			6

// VALUE FOR STATE
#define LIVE					1
#define DEAD					0

// CONTROL KEY
#define ESC_KEY					27
#define ENTER_KEY				13
#define PAUSE_KEY				'P'
#define SAVE_KEY				'T'
#define LOAD_KEY				'L'

#define UP_KEY					'W'
#define DOWN_KEY				'S'
#define LEFT_KEY				'A'
#define RIGHT_KEY				'D'

// Text in game menu
#define NEW_GAME_TEXT			"NEW GAME"
#define LOAD_GAME_TEXT			"LOAD GAME"
#define HIGH_SCORE_TEXT			"HIGH SCORE"
#define SETTING_TEXT			"SETTING"
#define EXIT_GAME_TEXT			"EXIT GAME"

#define NEW_GAME_MODE			0
#define LOAD_GAME_MODE			1
#define HIGH_SCORE_MODE			2
#define SETTING_MODE			3
#define EXIT_GAME_MODE			4

#define YES_TEXT				"Yes"
#define NO_TEXT					"No"
#define OK_TEXT					"OK"
#define EXIT_TEXT				"Exit"
#define RESUME_TEXT				"Resume"
#define RESTART_TEXT			"Restart"
#define CANCEL_TEXT				"Cancel"
#define SCORE_TEXT				"SCORE"
#define LEVEL_TEXT				"LEVEL"

// Value for PLAYING_STATE
#define RUNNING_STATE			1
#define SAVING_STATE			2
#define LOADING_STATE			3
#define LOSING_STATE			4
#define EXIT_STATE				5
#define WAITING_STATE			6
#define SETTING_STATE			7

extern int consoleHeigh;
extern int consoleWidth;
extern int borderHeigh;
extern int borderWidth;

extern POINT LENGTH_VALUE_POS;
extern POINT LEVEL_VALUE_POS;

extern bool HAS_MUSIC;

extern int pressedKey;

void GotoXY(POINT P);

void GotoXY(int x, int y);

void FixConsoleWindow();

void turnMusic(int index);

// PRINT BANNER AND LOGO
void printGameLogo();
void printLoadingBanner();
void printSavingBanner();
void printStartingBanner();
void printWinnerBanner();
void printLevelUpBanner();

void drawBoard(int x, int y, int width, int height);

void drawOutLine(int x, int y, int width, int height);

void drawBorderForSaveLoadBox(int x, int y, int width, int height);

// GATE
void randomPositionOfGate();
void drawGate();
void deleteGate();

void displaySnakeSize();

void displayLevel();

void deleteBox(int row, int column);

void deleteSnake();

void deleteFood();

void deleteEntityOnScreen();

void clearScreen();

void printColorText(int color, string text);

void goToXYAndPrintColorText(POINT P, string text, int color = COLOR_WHITE);

void goToXYAndPrintColorText(int x, int y, string text, int color = COLOR_WHITE);

void resetPressedKey();