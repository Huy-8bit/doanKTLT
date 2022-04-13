#include "Snake.h"

HIGHSCORE HighLength[5];
HIGHSCORE NewLength;

// SNAKE
POINT snake[MAX_SNAKE_SIZE];
int STATE;
int CHAR_LOCK;
int MOVING; // the direction in which the snake will go
int SPEED;
int SNAKE_SIZE;
int SIZE_PLUS;
int INDEX_ID;

// FOOD
POINT food[4];
int FOOD_INDEX;

POINT gateP;

// GAME
int LEVEL;
bool GATE_EXIST;
//int WIN;
int PLAYING_STATE;

//handle crash and effect 
bool crashGate() {
	POINT head = { snake[SNAKE_SIZE - 1].x, snake[SNAKE_SIZE - 1].y };
	return (head.x == gateP.x + 1 && head.y == gateP.y) || (head.x == gateP.x - 1 && head.y == gateP.y - 1)
		|| (head.x == gateP.x && head.y == gateP.y && CHAR_LOCK == 'S') || (head.x == gateP.x + 1 && head.y == gateP.y - 1)
		|| (head.x == gateP.x - 1 && head.y == gateP.y);
}

bool crashWall() {
	return (snake[SNAKE_SIZE - 1].x == borderWidth
		|| snake[SNAKE_SIZE - 1].x == 0
		|| snake[SNAKE_SIZE - 1].y + 1 == borderHeigh
		|| snake[SNAKE_SIZE - 1].y == 0);
}

bool crashItself() {
	for (int i = 0; i < SNAKE_SIZE - 1; i++)
		if (snake[i].x == snake[SNAKE_SIZE - 1].x && snake[i].y == snake[SNAKE_SIZE - 1].y)
			return true;
	return false;
}

void blinkSnake() {
	for (int j = 0; j < 5; j++) {
		Sleep(200);
		for (int i = 0; i < SNAKE_SIZE; i++) {
			GotoXY(snake[i]);
			cout << STUDENT_ID[i];
		}
		Sleep(100);
		for (int i = 0; i < SNAKE_SIZE; i++) {
			GotoXY(snake[i]);
			cout << " ";
		}
	}
}

//Xu ly giao dien chinh (menu) va hop thoai thoat (exit)
MENU mainMenu() {
	system("cls");	
	MENU menu;

	const int TOTAL_SELECTION = 5;
	string options[TOTAL_SELECTION] = { NEW_GAME_TEXT, LOAD_GAME_TEXT, HIGH_SCORE_TEXT, SETTING_TEXT, EXIT_GAME_TEXT };

	int selectingLine = 0;
	int SELECTING_COLOR = COLOR_LIGHT_BLUE;
	POINT MENU_P{ (consoleWidth / 2) - 5, (consoleHeigh / 2) + 3 };

	if (HAS_MUSIC)
		turnMusic(MENU_MUSIC);

	// Step 1: Print logo of game
	printGameLogo();

	// default
	menu.choice = NEW_GAME_TEXT;
	
	while (true) {
		// Step 2: Print options of game
		for (int i = 0; i < TOTAL_SELECTION; i++) {
			if (selectingLine == i)
				goToXYAndPrintColorText(POINT{ MENU_P.x, MENU_P.y + i * 2 }, options[i], SELECTING_COLOR);
			else
				goToXYAndPrintColorText(POINT{ MENU_P.x, MENU_P.y + i * 2 }, options[i]);
		}
		//----

		menu.pressedButton = toupper(_getch());

		// Step 3: handle options for user
		if (menu.pressedButton != '\0') {
			if (menu.pressedButton == UP_KEY) {
				if (selectingLine > 0) selectingLine--;
				menu.pressedButton = '\0';
			}
			else if (menu.pressedButton == DOWN_KEY) {
				if (selectingLine < TOTAL_SELECTION) selectingLine++;
				menu.pressedButton = '\0';
			}
			else if (menu.pressedButton == ENTER_KEY) {
				menu.choice = options[selectingLine];
				menu.mode = selectingLine;
				break;
			}
		}		
	}
	return menu;
}

void handleMainMenu() {
	MENU chooseMenu;
	
	while (true) {
		chooseMenu = mainMenu();
		if (chooseMenu.pressedButton == ENTER_KEY) {
			system("cls");
			switch (chooseMenu.mode)
			{				
			case NEW_GAME_MODE:				
				PLAYING_STATE = RUNNING_STATE;
				return;

			case LOAD_GAME_MODE:				
				loadMenu();	
				PLAYING_STATE = LOADING_STATE;
				system("cls");
				return;

			case HIGH_SCORE_MODE:				
				showHighScore();	
				PLAYING_STATE = WAITING_STATE;
				break;

			case SETTING_MODE:
				PLAYING_STATE = WAITING_STATE;
				settingMenu();		
				break;

			case EXIT_GAME_MODE:
				PLAYING_STATE = EXIT_STATE;
				break;

			default:
				break;
			}			
			system("cls");			
		}
	}
}

void continueGame() {
	if (GATE_EXIST) {
		drawGate();
	}
	else {
		drawFood();
	}
	drawSnake();
	
	displaySnakeSize();
	displayLevel();

	PLAYING_STATE = RUNNING_STATE;
	STATE = LIVE;
}

void continueMenu() {

	int boxWidth = 34;
	int boxHeight = 8;
	int game_X = (borderWidth - boxWidth) / 2;
	int game_Y = (borderHeigh - boxHeight) / 2;
	POINT GAME_P = { game_X, game_Y };
	MENU select;

	POINT restartP = { GAME_P.x + 8, GAME_P.y + 4 };
	POINT cancelP = { GAME_P.x + 20, GAME_P.y + 4 };

	drawOutLine(GAME_P.x, GAME_P.y, boxWidth, boxHeight);

	GotoXY(POINT{ GAME_P.x + 13, GAME_P.y + 2 });
	cout << "YOU LOSED";
	goToXYAndPrintColorText(restartP, RESTART_TEXT, COLOR_LIGHT_BLUE);

	GotoXY(cancelP);
	cout << CANCEL_TEXT;
	select.choice = RESTART_TEXT;
	
	if (pressedKey == RIGHT_KEY || pressedKey == ENTER_KEY)
		pressedKey = LEFT_KEY;
		
	// handle user's selection
	while (true) {
		select.pressedButton = pressedKey;
		if (select.pressedButton == ENTER_KEY)
			break;

		if (select.choice == RESTART_TEXT) {
			if (select.pressedButton == RIGHT_KEY) {
				goToXYAndPrintColorText(restartP, RESTART_TEXT);

				goToXYAndPrintColorText(cancelP, CANCEL_TEXT, COLOR_LIGHT_BLUE);
				select.choice = CANCEL_TEXT;
			}
		}
		if (select.choice == CANCEL_TEXT) {
			if (select.pressedButton == LEFT_KEY) {
				goToXYAndPrintColorText(restartP, RESTART_TEXT, COLOR_LIGHT_BLUE);
	
				goToXYAndPrintColorText(cancelP, CANCEL_TEXT);
				select.choice = RESTART_TEXT;
			}
		}
	}
	if (select.choice == RESTART_TEXT)
		PLAYING_STATE = RUNNING_STATE;
	else if (select.choice == CANCEL_TEXT)
		PLAYING_STATE = WAITING_STATE;
}

void settingMenu() {
	int boxWidth = 30;
	int boxHeight = 8;

	int game_X;
	int game_Y;
	
	if (PLAYING_STATE == SETTING_STATE) {
		game_X = (consoleWidth - boxWidth) / 2;
		game_Y = (consoleHeigh - boxHeight) / 2;		
	}
	else {
		game_X = (borderWidth - boxWidth) / 2;
		game_Y = (borderHeigh - boxHeight) / 2;
	}
	
	POINT outlineP = { game_X, game_Y };
	POINT chooseP = { game_X + 2 , game_Y + 2 };
	
	system("cls");
	drawOutLine(outlineP.x, outlineP.y, boxWidth, boxHeight);
	string text[4] = { "SETTING", "Background music:  ON", "Return", "Background music: OFF" };

	int choice = 1;
	bool state = HAS_MUSIC;

	GotoXY(chooseP.x + 10, chooseP.y);
	cout << text[0];
	while (true) {
		for (int i = 1; i < 3; i++) {
			if (choice == i) {
				GotoXY(chooseP.x + 3, chooseP.y + i);
				if (i == 1) {					
					if (state)
						printColorText(COLOR_LIGHT_BLUE, text[i]);				
					else 
						printColorText(COLOR_LIGHT_BLUE, text[i + 2]);											
				}
				else 
					printColorText(COLOR_LIGHT_BLUE, text[i]);					
			}
			else {
				GotoXY(chooseP.x + 3, chooseP.y + i);
				if (i == 1) 
					state ? cout << text[i] : cout << text[i + 2];							
				else 
					cout << text[i];
			}
		}
		pressedKey = toupper(_getch());
		if (pressedKey != '\0') {
			if (pressedKey == UP_KEY) {
				if (choice > 1) 
					choice--;				
			}
			if (pressedKey == DOWN_KEY) {
				if (choice < 2) 
					choice++;				
			}
			if (pressedKey == ENTER_KEY) {				
				switch (choice)
				{
				case 1:
					state = !state;
					HAS_MUSIC = state;
					turnMusic(MENU_MUSIC);					
					if (!state)
						turnMusic(0);
					break;
				case 2:
					return;					
				}
			}
			resetPressedKey();
		}
	}
}

// Draw food and snake
void drawFood() {
	string str;
	str = (unsigned char)219;
	goToXYAndPrintColorText(food[FOOD_INDEX], str, COLOR_RED);
}

void drawSnake() {
	for (int i = 0; i < SNAKE_SIZE; i++) {
		char body = STUDENT_ID[i];
		GotoXY(snake[i]);
		cout << body;
	}
}

void deleteTail() {
	for (int i = 0; i < SNAKE_SIZE; i++) {
		GotoXY(snake[i]);
		cout << " ";
	}
}

//Xu ly nguyen do dai snake va khi an xong food o mot cap
void processGate() {
	if (GATE_EXIST) {
		if (snake[SNAKE_SIZE - 1].x == gateP.x &&
			snake[SNAKE_SIZE - 1].y == gateP.y &&
			CHAR_LOCK == UP_KEY) {
			SNAKE_SIZE--;
			SIZE_PLUS++;
		}
	}	
	else {
		drawFood();
	}

	displayLevel();

	if (SNAKE_SIZE == 0) {
		deleteGate();
		GATE_EXIST = false;

		// Level up
		LEVEL++;
		SPEED++;
		SNAKE_SIZE = 4 * LEVEL;
		SIZE_PLUS = 0;

		for (int i = 0; i < SNAKE_SIZE; i++) {
			snake[i].x = gateP.x;
			snake[i].y = gateP.y;
		}
				
		snake[SNAKE_SIZE - 1].x = gateP.x;
		snake[SNAKE_SIZE - 1].y = gateP.y + 1;
		
		printLevelUpBanner();
	}
}

//Xu ly top 5 HIGH LENGTH
bool isEmptyHighLengthFile() {
	ifstream ifs;
	string name;
	int length;

	ifs.open(".\\Data\\highlength.txt");
	if (ifs >> name >> length) {
		ifs.close();
		return false;
	}

	ifs.close();
	return true;
}

void saveHighScore() {
	remove(".\\Data\\highlength.txt");

	ofstream ofs;
	ofs.open(".\\Data\\highlength.txt");

	for (int i = 0; i < 4; i++)
		ofs << HighLength[i].name << " " << HighLength[i].length << endl;
	ofs << HighLength[4].name << " " << HighLength[4].length;

	ofs.close();
}

void resetHighScore() {
	for (int i = 0; i < 5; i++) {
		HighLength[i].name = "[NONE]";
		HighLength[i].length = 4;
	}
	saveHighScore();
}

void initializeHighScore() {
	if (!isEmptyHighLengthFile()) {
		string name;
		int length;

		ifstream ifs;
		ifs.open(".\\Data\\highlength.txt");

		int i = 0;

		while (ifs >> name >> length) {
			HighLength[i].name = name;
			HighLength[i].length = length;
			i++;
		}

		ifs.close();
	}
	else
		resetHighScore();
}

void createNewHighScore()
{
	int minLength = HighLength[0].length;
	int index = 0;
	for (int i = 0; i < 5; i++)
	{
		if (HighLength[i].name == "[NONE]")
		{
			minLength = HighLength[i].length;
			index = i;
			break;
		}
		else if (HighLength[i].length < minLength)
		{
			minLength = HighLength[i].length;
			index = i;
		}
	}

	if (NewLength.length > minLength || (NewLength.length == 4 && HighLength[index].name == "[NONE]"))
	{
		HighLength[index].name = NewLength.name;
		HighLength[index].length = NewLength.length;
	}
}

void sortHighScore() {
	for (int i = 0; i < 4; i++)
		for (int j = i + 1; j < 5; j++)
			if (HighLength[i].length < HighLength[j].length) {
				string name = HighLength[i].name;
				HighLength[i].name = HighLength[j].name;
				HighLength[j].name = name;

				int score = HighLength[i].length;
				HighLength[i].length = HighLength[j].length;
				HighLength[j].length = score;
			}
	saveHighScore();
}

void showHighScore() {
	ifstream ifs;
	ifs.open(".\\Data\\highlength.txt");

	string name;
	int length;

	system("cls");

	int column = 31;
	int row = 9;
	int xHighLength = (consoleWidth / 2) - 15;
	int yHighLength = (consoleHeigh / 2) - 4;

	for (int j = 0; j < row; j++) {
		GotoXY(POINT{ xHighLength, yHighLength + j });
		for (int k = 0; k < column; k++) {
			if (j == 0)
				cout << (unsigned char)220;
			else if (j == 2 && k != 0 && k != column - 1)
				cout << "*";
			else if (j == row - 1)
				cout << (unsigned char)223;
			else if (k == 0 || k == column - 1)
				cout << (unsigned char)219;
			else
				cout << " ";
		}
	}

	while (true) {
		GotoXY(POINT{ xHighLength + 10, yHighLength + 1 });
		cout << "HIGH LENGTH";

		int i = 0;

		while (ifs >> name >> length) {
			GotoXY(POINT{ xHighLength + 4, yHighLength + i + 3 });
			cout << "#" << i + 1 << ". ";
			GotoXY(POINT{ xHighLength + 8, yHighLength + i + 3 });
			cout << name;
			GotoXY(POINT{ xHighLength + 27, yHighLength + i + 3 });
			cout << length;
			i++;
		}

		if (_kbhit())
			break;
	}
	ifs.close();
}

// Another functions
void initialGame() {
	system("title Snake");
	FixConsoleWindow();
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left;
	borderWidth = consoleWidth - 25;
	consoleHeigh = csbi.srWindow.Bottom - csbi.srWindow.Top;
	borderHeigh = consoleHeigh;

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);

	STATE = DEAD;
	PLAYING_STATE = WAITING_STATE;
	HAS_MUSIC = true;
}

bool isValid(int x, int y) {
	for (int i = 0; i < SNAKE_SIZE; i++)
		if (snake[i].x == x && snake[i].y == y)
			return false;
	return true;
}

void resetData() {
	LEVEL = 1;
	GATE_EXIST = false;
	INDEX_ID = 4;
	CHAR_LOCK = LEFT_KEY, MOVING = RIGHT_KEY, SPEED = 1; FOOD_INDEX = 0, SNAKE_SIZE = 4;
	SIZE_PLUS = 0;

	for (int i = 0; i < SNAKE_SIZE; i++) {
		snake[i] = { borderWidth / 2 - 2 + i, borderHeigh / 2 };
	}

	STATE = LIVE;

	generateFood();
}

void startNewGame() {
	system("cls");

	resetData();

	drawBoard(0, 0, consoleWidth, consoleHeigh);

	printStartingBanner();

	turnMusic(0);
}

void startGame() {
	system("cls");

	drawBoard(0, 0, consoleWidth, consoleHeigh);

	printStartingBanner();

	continueGame();

	turnMusic(0);
}

void exitGame(thread& t) {
	system("cls");
	t.detach();
}

void pauseMenu() {	

	// draw banner pause
	int boxWidth = 34;
	int boxHeight = 8;
	MENU menu;
	
	int game_X = (borderWidth - boxWidth) / 2;
	int game_Y = (borderHeigh - boxHeight) / 2;
	POINT GAME_P = { game_X, game_Y };
	POINT pausing_P = { GAME_P.x + 14, GAME_P.y + 2 };
	POINT resume_P = { GAME_P.x + 8, GAME_P.y + 4 };
	POINT exit_P = { GAME_P.x + 22, GAME_P.y + 4 };

	drawOutLine(GAME_P.x, GAME_P.y, boxWidth, boxHeight);

	GotoXY(pausing_P);
	cout << "PAUSING";
	goToXYAndPrintColorText(resume_P, RESUME_TEXT, COLOR_LIGHT_BLUE);

	GotoXY(exit_P);
	cout << EXIT_TEXT;

	menu.choice = RESUME_TEXT;

	while (true) {
		pressedKey = toupper(_getch());
		menu.pressedButton = pressedKey;
		if (menu.pressedButton == ENTER_KEY)
			break;
		if (menu.choice == RESUME_TEXT) {			
			if (menu.pressedButton == RIGHT_KEY) {
				goToXYAndPrintColorText(resume_P, RESUME_TEXT);

				goToXYAndPrintColorText(exit_P, EXIT_TEXT, COLOR_LIGHT_BLUE);
				menu.choice = EXIT_TEXT;
			}
		}
		else if (menu.choice == EXIT_TEXT) {		
			if (menu.pressedButton == LEFT_KEY)
			{
				goToXYAndPrintColorText(resume_P, RESUME_TEXT, COLOR_LIGHT_BLUE);

				goToXYAndPrintColorText(exit_P, EXIT_TEXT);
				menu.choice = RESUME_TEXT;
			}
		}
	}
	if (menu.choice == RESUME_TEXT) {
		// continue game
		deleteBox(boxHeight, boxWidth);
		continueGame();
	}
	else if (menu.choice == EXIT_TEXT) {
		PLAYING_STATE = WAITING_STATE;
	}
}

void pauseGame(HANDLE t) {
	// stop the thread
	SuspendThread(t);	
}

void processDead() {
	STATE = DEAD;
	if(HAS_MUSIC)
		turnMusic(DEAD_MUSIC);
	blinkSnake();
}

void generateFood() {
	int x, y;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX_FOOD_AMOUNT; i++) {
		do {
			x = rand() % (borderWidth - 2) + 1;
			y = rand() % (borderHeigh - 2) + 1;
		} while (!isValid(x, y));
		food[i] = { x, y };
	}
}

void eat() {
	snake[SNAKE_SIZE] = food[FOOD_INDEX];

	SNAKE_SIZE++;
	INDEX_ID++;
	displaySnakeSize();
	
	if (FOOD_INDEX == MAX_FOOD_AMOUNT - 1) {
		randomPositionOfGate();
		drawGate();
		GATE_EXIST = true;
		FOOD_INDEX = 0;
		generateFood();
	}
	else
		FOOD_INDEX++;
}

void MoveRight() {
	if (crashWall() || crashItself() || (crashGate() && GATE_EXIST)) {
		processDead();
	}
	else {
		if (snake[SNAKE_SIZE - 1].x + 1 == food[FOOD_INDEX].x && snake[SNAKE_SIZE - 1].y == food[FOOD_INDEX].y) {
			eat();
		}
		for (int i = 0; i < SNAKE_SIZE - 1; i++) {
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SNAKE_SIZE - 1].x++;
	}
}

void MoveLeft()
{
	if (crashWall() || crashItself() || (crashGate() && GATE_EXIST))
	{
		processDead();
	}
	else
	{
		if (snake[SNAKE_SIZE - 1].x - 1 == food[FOOD_INDEX].x && snake[SNAKE_SIZE - 1].y == food[FOOD_INDEX].y)
		{
			eat();
		}
		for (int i = 0; i < SNAKE_SIZE - 1; i++)
		{
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SNAKE_SIZE - 1].x--;
	}
}

void MoveDown()
{
	if (crashWall() || crashItself() || (crashGate() && GATE_EXIST))
	{
		processDead();
	}
	else
	{
		if (snake[SNAKE_SIZE - 1].x == food[FOOD_INDEX].x && snake[SNAKE_SIZE - 1].y + 1 == food[FOOD_INDEX].y)
		{
			eat();
		}
		for (int i = 0; i < SNAKE_SIZE - 1; i++)
		{
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SNAKE_SIZE - 1].y++;
	}
}

void MoveUp()
{
	if (crashWall() || crashItself() || (crashGate() && GATE_EXIST))
	{
		processDead();
	}
	else
	{
		if (snake[SNAKE_SIZE - 1].x == food[FOOD_INDEX].x && snake[SNAKE_SIZE - 1].y - 1 == food[FOOD_INDEX].y)
		{
			eat();
		}
		for (int i = 0; i < SNAKE_SIZE - 1; i++)
		{
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SNAKE_SIZE - 1].y--;
	}
}

void ThreadFunc() {
	while (STATE == LIVE) {
		deleteTail();
		switch (MOVING)
		{
		case LEFT_KEY:
			CHAR_LOCK = RIGHT_KEY;
			MoveLeft();
			break;
		case RIGHT_KEY:
			CHAR_LOCK = LEFT_KEY;
			MoveRight();
			break;
		case UP_KEY:
			CHAR_LOCK = DOWN_KEY;
			MoveUp();
			break;
		case DOWN_KEY:
			CHAR_LOCK = UP_KEY;
			MoveDown();
			break;
		}
		processGate();
		if (LEVEL - 1 == MAX_LEVEL) {
			system("cls");
			printWinnerBanner();
		}
		else
			drawSnake();
		Sleep(300 / SPEED);
	}
	if(STATE == DEAD)
		continueMenu();
}



