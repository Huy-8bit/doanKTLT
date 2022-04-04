#pragma once
#include "Snake.h"

#include <iostream>

using namespace std;

/*
struct GAME {
	char menuChoice;
	string preState;
	bool hasBackgroundMusic;
	string mainState;
};

extern GAME game;
*/

void saveMenu();

void saveData(string fileName);

void loadMenu();

void loadData(string fileName);
