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
				"Return" 
	};

	int boxWidth = 34;
	int boxHeight = 12;
	POINT GAME_P = { (borderWidth - boxWidth) / 2, (borderHeigh - boxHeight) / 2 }; 

	int selectingLine = 1;

	// turn off music
	turnMusic(0);

	// draw border for save box
	drawBorderForSaveLoadBox(GAME_P.x, GAME_P.y, boxWidth, boxHeight);
		
	while (true) {
		GotoXY(POINT{ GAME_P.x + 9, GAME_P.y + 2});
		cout << text[0];
		for (int i = 1; i < nSaveSLot + 2; i++) {
			if (selectingLine == i) {
				goToXYAndPrintColorText(GAME_P.x + 12, GAME_P.y + 2 + i, text[i], COLOR_LIGHT_BLUE);
			}
			else {
				GotoXY(GAME_P.x + 12, GAME_P.y + 2 + i);
				cout << text[i];
			}
		}

		pressedKey = toupper(_getch());
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
				deleteBox(boxHeight, boxWidth);
				deleteEntityOnScreen();
				if (selectingLine != nSaveSLot + 1) {																
					fileName = "./save/" + text[selectingLine] + ".txt";					
					saveData(fileName);	
					// saving effect
					printSavingBanner();

				}
				break;
			}
			resetPressedKey();
		}
	}
}

void saveData(string fileName) {	
	ofstream ofs(fileName);

	//---------------------------------
	// open file
	if (ofs) {
		// <SIZE_SNAKE> <SIZE_PLUS>
		ofs << SNAKE_SIZE << " " << SIZE_PLUS << endl;

		// save points of snake
		for (int i = 0; i < SNAKE_SIZE; i++)
			ofs << snake[i].x << " " << snake[i].y << endl;

		// save index of current food
		ofs << FOOD_INDEX << endl;
		// save position of current food: x and y
		ofs << food[FOOD_INDEX].x << " " << food[FOOD_INDEX].y << endl;

		// if gate is exists, we need to save position of gate
		if (GATE_EXIST)
			ofs << gateP.x << " " << gateP.y << endl;
		else
			ofs << -1 << " " << -1 << endl;

		ofs << INDEX_ID << endl;
		ofs << SPEED << endl;
		ofs << LEVEL << endl;
		ofs << MOVING << endl;
		ofs << CHAR_LOCK;

		ofs.close();
	}
	else {
		cout << fileName << " could not be opened." << endl;
		exit(EXIT_FAILURE);
	}
	// close file
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

	int boxWidth = 34;
	int boxHeight = 12;
	POINT GAME_P;
	if (PLAYING_STATE == LOADING_STATE) {
		GAME_P = { (borderWidth - boxWidth) / 2, (borderHeigh - boxHeight) / 2 };
	}
	else {
		GAME_P = { (consoleWidth - boxWidth) / 2, (consoleHeigh - boxHeight) / 2 };
	}
	
	int selectingLine = 1;

	// turn off music
	turnMusic(0);

	// draw border for save box
	drawBorderForSaveLoadBox(GAME_P.x, GAME_P.y, boxWidth, boxHeight);

	while (true) {
		GotoXY(GAME_P.x + 9, GAME_P.y + 2 );
		cout << text[0];
		for (int i = 1; i < nSaveSLot + 2; i++) {
			if (selectingLine == i) {
				goToXYAndPrintColorText(GAME_P.x + 12, GAME_P.y + 2 + i, text[i], COLOR_LIGHT_BLUE);
			}
			else {
				GotoXY(GAME_P.x + 12, GAME_P.y + 2 + i);
				cout << text[i];
			}
		}

		pressedKey = toupper(_getch());
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
				deleteBox(boxHeight, boxWidth);
				if (selectingLine != nSaveSLot + 1) {
					fileName = "./save/" + text[selectingLine] + ".txt";

					loadData(fileName);	
					// loading Banner and sound effect	
					printLoadingBanner();
				}															
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
	int indexId_In, speed_In, level_In, moving_In, charLock_In;

	if (ifs) {
		// TODO: check file is empty
		if (ifs.eof()) {
			ifs.close();
			return;
		}
			

		ifs >> snakeSize_In >> sizePLus_In;

		for (int i = 0; i < snakeSize_In; i++)
			ifs >> snakeP_In[i].x >> snakeP_In[i].y;

		ifs >> foodIndex_In;
		
		ifs >> foodP_In.x >> foodP_In.y;

		ifs >> gateP_In.x >> gateP_In.y;

		ifs >> indexId_In;
		ifs >> speed_In;
		ifs >> level_In;
		ifs >> moving_In;
		ifs >> charLock_In;

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
		LEVEL = level_In;
		MOVING = moving_In;
		CHAR_LOCK = charLock_In;
		
		if (gateP_In.x != -1 && gateP_In.y != -1) {
			gateP = gateP_In;
			GATE_EXIST = true;			
		}		
	}
	else {
		cout << fileName << " could not be opened." << endl;
		exit(EXIT_FAILURE);
	}
}
