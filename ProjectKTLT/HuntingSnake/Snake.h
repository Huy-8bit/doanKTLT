#ifndef __snake_h__
#define __snake_h__

#include <thread>
#include <fstream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "Console.h"
#include "Data.h"

#pragma comment(lib, "winmm.lib")

//CONSTANT DEFINING
#define MAX_SNAKE_SIZE 32
#define MAX_FOOD_AMOUNT 4
#define MAX_SPEED 7
#define MAX_ROUND 7
#define MAX_LEVEL 7
#define STUDENT_ID "20127518201271852012739720127327"

//STRUCT DEFINING
struct MENU {
	string choice;
	int mode;
	char pressedButton;
};

struct HIGHSCORE {
	string name;
	int length;
};

// HIGNLENGTH
extern HIGHSCORE HighLength[5];
extern HIGHSCORE NewLength;

// SNAKE 
extern POINT snake[MAX_SNAKE_SIZE];
extern int STATE;
extern int CHAR_LOCK;
extern int MOVING;
extern int SPEED;
extern int SNAKE_SIZE;
extern int SIZE_PLUS;
extern int INDEX_ID;

// GATE
extern POINT gateP;

// FOOD
extern POINT food[4];
extern int FOOD_INDEX;

// GAME
extern int ROUND;
extern bool GATE_EXIST;
extern int WIN;
extern bool PLAYING_STATE;

//PROTOTYPE
MENU mainMenu();

void handleMainMenu();

void continueGame();

void continueMenu();

bool isValid(int x, int y);

void generateFood();

void resetData();

void startGame();

void exitGame(thread& t);

void settingMenu();

void pauseGame(HANDLE t);
void pauseMenu();

bool crashGate();
bool crashWall();
bool crashItself();
void blinkSnake();

void eat();

void processDead();

void deleteTail();


void drawFood();
void drawSnake();

void processGate();

// handle moving of snake
void MoveRight();
void MoveLeft();
void MoveDown();
void MoveUp();

void ThreadFunc();

bool isEmptyHighLengthFile();
void SaveHighLength();
void ResetHighLength();
void initializeHighLength();
void CreateNewHighLength();
void SortHighLength();
void showHighLength();

void initialGame();

#endif // !__snake_h__