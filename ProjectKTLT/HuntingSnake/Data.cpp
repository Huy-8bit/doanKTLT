#include "Data.h"

// Handle save and load game
void saveMenu() {
	string fileName;
	const int nSaveSLot = 5;
	string text[nSaveSLot + 2] = {
				"Select slot to save:",
				"Save_slot_1",
				"Save_slot_2" ,
				"Save_slot_3" ,
				"Save_slot_4" ,
				"Save_slot_5" ,
				"Return" };

	int column = 35;
	int row = 11;
	POINT GAME_P = { (CONSOLE_WIDTH / 2) - 15, (CONSOLE_HEIGH / 2) - 3 };

	int selectingLine = 1;

	// turn off music
	turnMusic(0);

	// draw border for save box
	drawBorderForSaveLoadBox(GAME_P.x, GAME_P.y, column, row);
	
	bool hasContinued = true;
	while (hasContinued) {
		GotoXY(POINT{ GAME_P.x + 9, GAME_P.y + 2});
		cout << text[0];
		for (int i = 1; i < nSaveSLot + 2; i++) {
			if (selectingLine == i) {
				goToXYAndPrintColorText(POINT{ GAME_P.x + 12, GAME_P.y + 2 + i }, text[i], COLOR_LIGHT_BLUE);
			}
			else {
				GotoXY(POINT{ GAME_P.x + 12, GAME_P.y + 2 + i });
				cout << text[i];
			}
		}

		pressedKey = _getch();
		if (pressedKey != '\0') {
			if (pressedKey == UP_KEY) {
				if (selectingLine > 1) 
					selectingLine--;						
			}
			if (pressedKey == DOWN_KEY) {
				if (selectingLine < nSaveSLot + 1) 
					selectingLine++;				
			}
			if (pressedKey == ENTER_KEY) {				
				if (selectingLine == nSaveSLot + 1) {
					system("cls");
					hasContinued = false;
					//this->main_state = this->pre_state;
				}
				else {				
					//ofstream ofs("./save/" + text[choice] + ".bin", std::ios::binary);
					fileName = "./save/" + text[selectingLine] + ".txt";					
					saveData(fileName);
					GotoXY(60, 16 + selectingLine);
					cout << "Saved!";
					deleteBox(row, column);
					return;
				}
			}
			resetPressedKey();
		}
	}
}

void saveData(string fileName) {	
	ofstream ofs(fileName);

	ofstream f_user;
	f_user.open(".\\Data\\username.txt", ios::app);
	f_user << fileName << endl;
	f_user.close();

	//---------------------------------
	// open file
	// <SIZE_SNAKE> <SIZE_PLUS>
	ofs << SNAKE_SIZE << " " << SIZE_PLUS << endl;

	// save points of snake
	for (int i = 0; i < SNAKE_SIZE; i++)
		ofs << snake[i].x << " " << snake[i].y << endl;

	// save index of current food
	ofs << FOOD_INDEX << endl;
	// save position of current foo: x and y
	ofs << food[FOOD_INDEX].x << " " << food[FOOD_INDEX].y << endl;

	// if gate is exists, we need to save position of gate
	if (GATE_EXIST)
		ofs << gateP.x << " " << gateP.y << endl;
	else
		ofs << -1 << " " << -1 << endl;

	ofs << INDEX_ID << endl;
	ofs << SPEED << endl;
	ofs << ROUND << endl;
	ofs << MOVING << endl;
	ofs << CHAR_LOCK << endl;

	ofs << WIN;
	ofs.close();
	// close file
	//-----------------------------------------
	NewLength.name = fileName;
	NewLength.length = SNAKE_SIZE + SIZE_PLUS;

	CreateNewHighLength();
	SortHighLength();
}

void loadMenu() {
	string fileName;
	const int nSaveSLot = 5;
	string text[nSaveSLot + 2] = {
				"Select slot to load:",
				"Save_slot_1",
				"Save_slot_2" ,
				"Save_slot_3" ,
				"Save_slot_4" ,
				"Save_slot_5" ,
				"Return" };

	int column = 34;
	int row = 12;
	POINT GAME_P = { (BORDER_WIDTH - column) / 2, (BORDER_HEIGH - row) / 2};

	int selectingLine = 1;

	// turn off music
	turnMusic(0);

	// draw border for save box
	drawBorderForSaveLoadBox(GAME_P.x, GAME_P.y, column, row);

	while (true) {
		GotoXY(POINT{ GAME_P.x + 9, GAME_P.y + 2 });
		cout << text[0];
		for (int i = 1; i < nSaveSLot + 2; i++) {
			if (selectingLine == i) {
				goToXYAndPrintColorText(POINT{ GAME_P.x + 12, GAME_P.y + 2 + i }, text[i], COLOR_LIGHT_BLUE);
			}
			else {
				GotoXY(POINT{ GAME_P.x + 12, GAME_P.y + 2 + i });
				cout << text[i];
			}
		}

		pressedKey = _getch();
		if (pressedKey != '\0') {
			if (pressedKey == UP_KEY) {
				if (selectingLine > 1)
					selectingLine--;
			}
			if (pressedKey == DOWN_KEY) {
				if (selectingLine < nSaveSLot + 1)
					selectingLine++;
			}
			if (pressedKey == ENTER_KEY) {
				if (selectingLine != nSaveSLot + 1) {
					fileName = "./save/" + text[selectingLine] + ".txt";
					loadData(fileName);										
				}
				deleteBox(row, column);
				// TODO: loading Banner and sound effect

				continueGame();
				break;
			}
			resetPressedKey();
		}
	}
}

void loadData(string fileName) {
	
	ifstream ifs(fileName);
	int snakeSize_In, sizePLus_In;
	int foodIndex_In;
	POINT snakeP_In[MAX_SNAKE_SIZE];
	POINT foodP_In;
	POINT gateP_In;
	int indexId_In, speed_In, round_In, moving_In, charLock_In, win_In;

	if (ifs) {
		// TODO: check file is empty

		ifs >> snakeSize_In >> sizePLus_In;

		for (int i = 0; i < snakeSize_In; i++)
			ifs >> snakeP_In[i].x >> snakeP_In[i].y;

		ifs >> foodIndex_In;
		
		ifs >> foodP_In.x >> foodP_In.y;

		ifs >> gateP_In.x >> gateP_In.y;

		ifs >> indexId_In;
		ifs >> speed_In;
		ifs >> round_In;
		ifs >> moving_In;
		ifs >> charLock_In;
		ifs >> win_In;

		ifs.close();

		// delete entity on screen
		deleteEntityOnScreen();

		SNAKE_SIZE = snakeSize_In;
		SIZE_PLUS = sizePLus_In;
		for (int i = 0; i < snakeSize_In; i++)
			snake[i] = snakeP_In[i];

		FOOD_INDEX = foodIndex_In;
		food[foodIndex_In] = foodP_In;
	
		INDEX_ID = indexId_In;
		SPEED = speed_In;
		ROUND = round_In;
		MOVING = moving_In;
		CHAR_LOCK = charLock_In;
		WIN = win_In;

		// loading effect
		/*
		GotoXY((BORDER_WIDTH / 2) - 13, (BORDER_HEIGH / 2) - 2);
		cout << "Loading";
		for (int i = 0; i < 3; i++) {
			for (int i = 0; i < 2; i++) {
				Sleep(1000);
				cout << ".";
			}
		}
		*/

		if (gateP_In.x != -1 && gateP_In.y != -1) {
			gateP = gateP_In;
			GATE_EXIST = true;			
		}
	}
}
