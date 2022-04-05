#ifndef __snake_h__
#define __snake_h__

#include <thread>
#include <fstream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <string.h>
//#include <mmsystem.h>

#include "Console.h"
#include "Data.h"

#pragma comment(lib, "winmm.lib")

//CONSTANT DEFINING
#define MAX_SNAKE_SIZE 32
#define MAX_FOOD_AMOUNT 4
#define MAX_SPEED 7
#define MAX_ROUND 7
#define STUDENT_ID "20127518201271852012739720127327"

//STRUCT DEFINING
struct MENU {
	string choice;
	char pressedButton;
};

struct HIGHLENGTH {
	string name;
	int length;
};

// HIGNLENGTH
extern HIGHLENGTH HighLength[5];
extern HIGHLENGTH NewLength;

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

//PROTOTYPE
MENU gameMenu();

void continueGame();

bool continueMenu();

bool isValid(int x, int y);

void generateFood();

void resetData();

void startGame();

void exitGame(thread& t);

void pauseGame(HANDLE t);
bool pauseMenu();

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

bool IsEmptyHighLengthFile();
void SaveHighLength();
void ResetHighLength();
void initializeHighLength();
void CreateNewHighLength();
void SortHighLength();
void ShowHighLength();

void initialGame();

#endif // !__snake_h__