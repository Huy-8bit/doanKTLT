#ifndef __snake_h__
#define __snake_h__

#include <thread>
#include <fstream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <string.h>
//#include <mmsystem.h>

#include <conio.h>
#include <Windows.h>
#include <iostream>

#pragma comment(lib, "winmm.lib")
#pragma warning (disable: 4996)

using namespace std;

//CONSTANT DEFINING
#define MAX_SIZE_SNAKE 32
#define MAX_SIZE_FOOD 4
#define MAX_SPEED 7
#define MAX_ROUND 7
#define STUDENT_ID "20127518201271852012739720127327"

//STRUCT DEFINING
struct MENU
{
	char* choice;
	char selecting;
};

struct HIGHLENGTH
{
	string name;
	int length;
};

//GLOBAL VARIABLES
extern HIGHLENGTH HighLength[5];
extern HIGHLENGTH NewLength;
extern POINT snake[MAX_SIZE_SNAKE];
extern POINT food[4];

// gate point
extern POINT gateP;
extern int INDEX_ID;
extern int CHAR_LOCK;
extern int MOVING;
extern int SPEED;
extern int HEIGH_CONSOLE;
extern int WIDTH_CONSOLE;
extern int FOOD_INDEX;
extern int SIZE_SNAKE;
extern int SIZE_PLUS;
extern int STATE;
extern int ROUND;
extern bool GATE_EXIST;
extern char newgame[];
extern char highlength[];
extern char exitgame[];
extern char yes[];
extern char no[];
extern char ok[];
extern int temp;
extern int win;

//PROTOTYPE
MENU gameMenu();

bool ContinueGame();

bool IsValid(int x, int y);

void GenerateFood();

void ResetData();

void StartGame();

void ExitGame(thread& t);

void PauseGame(HANDLE t);

bool CrashGate();
bool CrashWall();
bool CrashItself();
void BlinkSnake();

void Eat();



void ProcessDead();



void DeleteTail();

void GotoXY(int x, int y);

void FixConsoleWindow();

void DrawBoard(int x, int y, int width, int height);

void PrintLogo();

void DrawFood();
void DrawSnake();

void DrawGate();
void ProcessGate();
void PrintWinner();




void MoveRight();
void MoveLeft();
void MoveDown();
void MoveUp();

void ThreadFunc();

bool IsExistedFileName(string FileName);
bool IsValidFileName(string FileName);
void SaveData();
void LoadData();

void DeleteBox();
void TextColor(int color, char* OutputContent);

bool IsEmptyHighLengthFile();
void SaveHighLength();
void ResetHighLength();
void InitializeHighLength();
void CreateNewHighLength();
void SortHighLength();
void ShowHighLength();

void InitialGame();

#endif // !__snake_h__