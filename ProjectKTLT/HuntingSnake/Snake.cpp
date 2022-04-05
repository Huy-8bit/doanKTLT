#include "Snake.h"

HIGHLENGTH HighLength[5];
HIGHLENGTH NewLength;

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
int ROUND;
bool GATE_EXIST;
int WIN;

//handle crash and effect 

bool crashGate() {
	POINT head = { snake[SNAKE_SIZE - 1].x, snake[SNAKE_SIZE - 1].y };
	return (head.x == gateP.x + 1 && head.y == gateP.y) || (head.x == gateP.x - 1 && head.y == gateP.y - 1)
		|| (head.x == gateP.x && head.y == gateP.y && CHAR_LOCK == 'S') || (head.x == gateP.x + 1 && head.y == gateP.y - 1)
		|| (head.x == gateP.x - 1 && head.y == gateP.y);
}

bool crashWall() {
	return (snake[SNAKE_SIZE - 1].x + 1 == BORDER_WIDTH + 1
		|| snake[SNAKE_SIZE - 1].x == 0
		|| snake[SNAKE_SIZE - 1].y + 1 == BORDER_HEIGH
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
MENU gameMenu() {
	MENU menu;

	const int TOTAL_SELECTION = 3;
	string options[TOTAL_SELECTION] = { "NEW GAME", "HIGH LENGTH", "EXIT GAME" };

	int selectingLine = 0;
	int SELECTING_COLOR = COLOR_LIGHT_BLUE;
	POINT MENU_P{ (CONSOLE_WIDTH / 2) - 5, (CONSOLE_HEIGH / 2) + 3 };

	// Step 1: Print logo of game
	printGameLogo();

	// default
	menu.choice = newgame_Menu;
	
	while (true) {
		// Step 2: Print options of game
		for (int i = 0; i < TOTAL_SELECTION; i++) {
			if (selectingLine == i)
				goToXYAndPrintColorText(POINT{ MENU_P.x, MENU_P.y + i * 2 }, options[i], SELECTING_COLOR);
			else
				goToXYAndPrintColorText(POINT{ MENU_P.x, MENU_P.y + i * 2 }, options[i]);

		}
		//----
		menu.pressedButton = _getch();
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
				if (selectingLine == 0)
					menu.choice = options[0];
									
				else if (selectingLine == 1) {
					ShowHighLength();
					menu.choice = options[1];
				}
				else if (selectingLine == 2)
					menu.choice = options[2];

				break;
			}
		}		
	}
	return menu;
}

void continueGame() {
	if (GATE_EXIST) {
		drawGate();
	}
	drawSnake();
	drawFood();

	displaySnakeSize();
	displayRoundNumber();
	turnMusic(MAIN_MUSIC);
}

bool continueMenu() {
	bool Continue = true;

	int column = 34;
	int row = 8;
	int game_X = (BORDER_WIDTH - column) / 2;
	int game_Y = (BORDER_HEIGH - row) / 2;
	POINT GAME_P = { game_X, game_Y };
	MENU select;

	POINT yesP = { GAME_P.x + 10, GAME_P.y + 4 };
	POINT noP = { GAME_P.x + 22, GAME_P.y + 4 };

	//GotoXY(food[FOOD_INDEX]);
	//cout << " ";

	drawOutLine(GAME_P.x, GAME_P.y, column, row);

	GotoXY(POINT{ GAME_P.x + 3, GAME_P.y + 2 });
	cout << "Do you want to play continue?";
	goToXYAndPrintColorText(yesP, yes_Text, COLOR_LIGHT_BLUE);

	GotoXY(noP);
	cout << no_Text;
	select.choice = yes_Text;

	if (pressedKey == 'D' || pressedKey == ENTER_KEY)
		pressedKey = 'A';

	while (true) {
		if (select.choice == yes_Text) {
			select.pressedButton = pressedKey;
			if (select.pressedButton == ENTER_KEY)
				break;
			if (select.pressedButton == 'D') {
				goToXYAndPrintColorText(yesP, yes_Text);

				goToXYAndPrintColorText(noP, no_Text, COLOR_LIGHT_BLUE);
				select.choice = no_Text;
			}
		}
		if (select.choice == no_Text) {
			select.pressedButton = pressedKey;
			if (select.pressedButton == ENTER_KEY)
				break;
			if (select.pressedButton == 'A')
			{
				goToXYAndPrintColorText(yesP, yes_Text, COLOR_LIGHT_BLUE);
	
				goToXYAndPrintColorText(noP, no_Text);
				select.choice = yes_Text;
			}
		}
	}
	if (select.choice == yes_Text)
		startGame();
	if (select.choice == no_Text)
		Continue = false;

	return Continue;
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
	if (!GATE_EXIST)
		drawFood();

	if (snake[SNAKE_SIZE - 1].x == gateP.x && snake[SNAKE_SIZE - 1].y == gateP.y && GATE_EXIST && CHAR_LOCK == 'W') {
		SNAKE_SIZE--;
		SIZE_PLUS++;
	}

	displayRoundNumber();

	if (SNAKE_SIZE == 0) {
		deleteGate();

		// Level up
		WIN++;
		ROUND++;
		SPEED++;
		SNAKE_SIZE = 4 * ROUND;
		SIZE_PLUS = 0;

		for (int i = 0; i < SNAKE_SIZE; i++) {
			snake[i].x = gateP.x;
			snake[i].y = gateP.y;
		}

		snake[SNAKE_SIZE - 1].x = gateP.x;
		snake[SNAKE_SIZE - 1].y = gateP.y + 1;
	}
}

//Xu ly top 5 HIGH LENGTH
bool IsEmptyHighLengthFile()
{
	ifstream ifs;
	string name;
	int length;

	ifs.open(".\\Data\\highlength.txt");
	if (ifs >> name >> length)
	{
		ifs.close();
		return false;
	}

	ifs.close();
	return true;
}

void SaveHighLength()
{
	remove(".\\Data\\highlength.txt");

	ofstream fo;
	fo.open(".\\Data\\highlength.txt");

	for (int i = 0; i < 4; i++)
		fo << HighLength[i].name << " " << HighLength[i].length << endl;
	fo << HighLength[4].name << " " << HighLength[4].length;

	fo.close();
}

void ResetHighLength()
{
	for (int i = 0; i < 5; i++)
	{
		HighLength[i].name = "[NONE]";
		HighLength[i].length = 4;
	}
	SaveHighLength();
}

void initializeHighLength() {
	if (!IsEmptyHighLengthFile()) {
		string name;
		int length;

		ifstream fi;
		fi.open(".\\Data\\highlength.txt");

		int i = 0;

		while (fi >> name >> length)
		{
			HighLength[i].name = name;
			HighLength[i].length = length;
			i++;
		}

		fi.close();
	}
	else
		ResetHighLength();
}

void CreateNewHighLength()
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

void SortHighLength() {
	for (int i = 0; i < 4; i++)
		for (int j = i + 1; j < 5; j++)
			if (HighLength[i].length < HighLength[j].length)
			{
				string name = HighLength[i].name;
				HighLength[i].name = HighLength[j].name;
				HighLength[j].name = name;

				int length = HighLength[i].length;
				HighLength[i].length = HighLength[j].length;
				HighLength[j].length = length;
			}
	SaveHighLength();
}

void ShowHighLength() {
	ifstream ifs;
	ifs.open(".\\Data\\highlength.txt");

	string name;
	int length;

	system("cls");

	int column = 31;
	int row = 9;
	int xHighLength = (CONSOLE_WIDTH / 2) - 15;
	int yHighLength = (CONSOLE_HEIGH / 2) - 4;

	for (int j = 0; j < row; j++)
	{
		GotoXY(POINT{ xHighLength, yHighLength + j });
		for (int k = 0; k < column; k++)
		{
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

	while (true)
	{
		GotoXY(POINT{ xHighLength + 10, yHighLength + 1 });
		cout << "HIGH LENGTH";

		int i = 0;

		while (ifs >> name >> length)
		{
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
	CONSOLE_WIDTH = csbi.srWindow.Right - csbi.srWindow.Left;
	BORDER_WIDTH = CONSOLE_WIDTH - 25;
	CONSOLE_HEIGH = csbi.srWindow.Bottom - csbi.srWindow.Top;
	BORDER_HEIGH = CONSOLE_HEIGH;

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);

	STATE = DEAD;
}

bool isValid(int x, int y) {
	for (int i = 0; i < SNAKE_SIZE; i++)
		if (snake[i].x == x && snake[i].y == y)
			return false;
	return true;
}

void resetData() {
	WIN = 0;
	ROUND = 1;
	GATE_EXIST = false;
	INDEX_ID = 4;
	CHAR_LOCK = 'A', MOVING = 'D', SPEED = 1; FOOD_INDEX = 0, SNAKE_SIZE = 4;
	SIZE_PLUS = 0;

	snake[0] = { BORDER_WIDTH / 2 - 2, BORDER_HEIGH / 2 };
	snake[1] = { BORDER_WIDTH / 2 - 1, BORDER_HEIGH / 2 };
	snake[2] = { BORDER_WIDTH / 2, BORDER_HEIGH / 2 };
	snake[3] = { BORDER_WIDTH / 2 + 1, BORDER_HEIGH / 2 };

	generateFood();
}

void startGame() {
	system("cls");

	resetData();

	drawBoard(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGH);
	STATE = LIVE;

	turnMusic(MAIN_MUSIC);
}

void exitGame(thread& t) {
	system("cls");
	t.detach();
}

bool pauseMenu() {	
	turnMusic(0);
	bool isContinued = true;

	// draw banner pause
	int column = 34;
	int row = 8;
	string choice;
	char pressedButton;
	int game_X = (BORDER_WIDTH - column) / 2;
	int game_Y = (BORDER_HEIGH - row) / 2;
	POINT GAME_P = { game_X, game_Y };
	POINT pausing_P = { GAME_P.x + 14, GAME_P.y + 2 };
	POINT resume_P = { GAME_P.x + 8, GAME_P.y + 4 };
	POINT exit_P = { GAME_P.x + 22, GAME_P.y + 4 };

	drawOutLine(GAME_P.x, GAME_P.y, column, row);

	GotoXY(pausing_P);
	cout << "PAUSING";
	goToXYAndPrintColorText(resume_P, resume_Text, COLOR_LIGHT_BLUE);

	GotoXY(exit_P);
	cout << exit_Text;

	choice = resume_Text;

	while (true) {
		pressedKey = _getch();
		if (choice == resume_Text) {
			pressedButton = pressedKey;
			if (pressedButton == ENTER_KEY)
				break;
			if (pressedButton == RIGHT_KEY) {
				goToXYAndPrintColorText(resume_P, resume_Text);

				goToXYAndPrintColorText(exit_P, exit_Text, COLOR_LIGHT_BLUE);
				choice = exit_Text;
			}
		}
		if (choice == exit_Text) {
			pressedButton = pressedKey;
			if (pressedButton == ENTER_KEY)
				break;
			if (pressedButton == LEFT_KEY)
			{
				goToXYAndPrintColorText(resume_P, resume_Text, COLOR_LIGHT_BLUE);

				goToXYAndPrintColorText(exit_P, exit_Text);
				choice = resume_Text;
			}
		}
	}
	if (choice == resume_Text) {
		// continue game
		deleteBox(row, column);
		continueGame();
	}
	else if (choice == exit_Text) {
		isContinued = false;
	}
	return isContinued;
}

void pauseGame(HANDLE t) {
	// stop the thread
	SuspendThread(t);	
}

void processDead() {
	STATE = DEAD;
	turnMusic(DEAD_MUSIC);
	blinkSnake();
}

void generateFood() {
	int x, y;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX_FOOD_AMOUNT; i++) {
		do {
			x = rand() % (BORDER_WIDTH - 2) + 1;
			y = rand() % (BORDER_HEIGH - 2) + 1;
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
		drawGate();
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
		if (snake[SNAKE_SIZE - 1].x + 1 == food[FOOD_INDEX].x && snake[SNAKE_SIZE - 1].y == food[FOOD_INDEX].y)
		{
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
	while (true) {
		if (STATE == LIVE) {
			deleteTail();
			switch (MOVING)
			{
			case 'A':
				CHAR_LOCK = 'D';
				MoveLeft();
				break;
			case 'D':
				CHAR_LOCK = 'A';
				MoveRight();
				break;
			case 'W':
				CHAR_LOCK = 'S';
				MoveUp();
				break;
			case 'S':
				CHAR_LOCK = 'W';
				MoveDown();
				break;
			}
			processGate();
			if (WIN == 9) {
				system("cls");
				printWinnerBanner();
			}
			else
				drawSnake();
			Sleep(300 / SPEED);
		}
		else {			
			if (!continueMenu()) {
				system("cls");
				exit(0);
			}
		}
	}
}



