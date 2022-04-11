#include "Console.h"

int CONSOLE_HEIGH;
int CONSOLE_WIDTH;
int BORDER_HEIGH;
int BORDER_WIDTH;

POINT LENGTH_VALUE_POS;
POINT ROUND_VALUE_POS;
bool HAS_MUSIC;

int pressedKey;

void printColorText(int color, string text) {	
	static int __BACKGROUND;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

	GetConsoleScreenBufferInfo(h, &csbiInfo);
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (__BACKGROUND << 4));

	cout << text;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 + (__BACKGROUND << 4));
}

void GotoXY(POINT P) {
	GotoXY(P.x, P.y);
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void goToXYAndPrintColorText(POINT P, string text, int color) {
	GotoXY(P);
	printColorText(color, text);
}

void goToXYAndPrintColorText(int x, int y, string text, int color) {
	GotoXY(x, y);
	printColorText(color, text);
}

void FixConsoleWindow() {
	RECT ConsoleRect;
	HWND consoleWindow = GetConsoleWindow();
	GetWindowRect(consoleWindow, &ConsoleRect);
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
	MoveWindow(consoleWindow, ConsoleRect.left, ConsoleRect.top, 600, 500, TRUE);
}

void turnMusic(int index) {
	switch (index)
	{
	case MENU_MUSIC:
		PlaySound(TEXT(".\\Sound\\menu.wav"), NULL, SND_LOOP | SND_ASYNC);
		break;
	case LEVEL_UP_MUSIC:
		PlaySound(TEXT(".\\Sound\\LevelUp.wav"), NULL, SND_SYNC);
		break;
	case DEAD_MUSIC:
		PlaySound(TEXT(".\\Sound\\LoseGame.wav"), NULL, SND_ASYNC);
		break;
	case TYPE_KEY_SOUND:
		PlaySound(TEXT(".\\Sound\\TypeKey.wav"), NULL, SND_ASYNC);
		break;
	case LOADING_SOUND:
		PlaySound(TEXT(".\\Sound\\LoadGame.wav"), NULL, SND_LOOP | SND_ASYNC);
		break;
	case STARTING_SOUND:
		PlaySound(TEXT(".\\Sound\\StartGame.wav"), NULL, SND_ASYNC);
		break;
	default:
		PlaySound(NULL, 0, 0);
		break;
	}	
}

void printGameLogo() {
	int logo_X = (CONSOLE_WIDTH / 2) - 20;
	int logo_Y = (CONSOLE_HEIGH / 2) - 8;

	const int logoLength = 6;
	string logo[logoLength] = {
					"   _____   _   _              _  __  ______ ",
					"  / ____| | \\ | |     /\\     | |/ / |  ____|",
					" | (___   |  \\| |    /  \\    | ' /  | |__   ",
					"  \\___ \\  | . ` |   / /\\ \\   |  <   |  __|  ", 
					"  ____) | | |\\  |  / ____ \\  | . \\  | |____ ",
					" |_____/  |_| \\_| /_/    \\_\\ |_|\\_\\ |______|"
	};
	
	// use for loop to change color of logo
	for (int i = 1; i <= 14; i++) {
		// use for loop to print logo
		for (int j = 0; j < logoLength; j++) {
			goToXYAndPrintColorText(POINT{ logo_X, logo_Y + j }, logo[j], i);
		}
		Sleep(70);
	}
}

void printLoadingBanner() {
	int logo_X;
	int logo_Y;

	if (PLAYING_STATE) {
		logo_X = (BORDER_WIDTH / 2) - 25;
		logo_Y = (BORDER_HEIGH / 2) - 2;
	}
	else {
		logo_X = (CONSOLE_WIDTH / 2) - 25;
		logo_Y = (CONSOLE_HEIGH / 2) - 2;
	}

	const int logoLength = 5;
	string logo[logoLength] = {
					"  _                 _ _           ",
					" | |   ___  __ _ __| (_)_ _  __ _ ",
					" | |__/ _ \\/ _` / _` | | ' \\/ _` |",
					" |____\\___/\\__,_\\__,_|_|_||_\\__, |",
					"                            |___/ "
	};
	POINT dotP = { logo_X + logo[3].length() + 2 , logo_Y + 2 };
	
	if (HAS_MUSIC)
		turnMusic(LOADING_SOUND);
	// use for loop to print logo
	for (int i = 0; i < logoLength; i++) {
		goToXYAndPrintColorText(POINT{ logo_X, logo_Y + i }, logo[i]);
	}

	// print DOT ... effect
	for (int i = 0; i < 3; i++) {
		Sleep(700);
		GotoXY(dotP.x + i * 4 + 1, dotP.y);
		cout << "_";
		GotoXY(dotP.x + i * 4, dotP.y + 1);
		cout << "(_)";
	}

	turnMusic(0);

	// delete banner
	clearScreen();
}

void printSavingBanner() {
	int logo_X = (BORDER_WIDTH / 2) - 22;
	int logo_Y = (BORDER_HEIGH / 2) - 2;

	const int logoLength = 5;
	string logo[logoLength] = {
					"  ___           _           ",
					" / __| __ ___ _(_)_ _  __ _ ",
					" \\__ \\/ _` \\ V / | ' \\/ _` |",
					" |___/\\__,_|\\_/|_|_||_\\__, |",
					"                      |___/ "
	};
	POINT dotP = { logo_X + logo[3].length() + 2 , logo_Y + 2 };

	if (HAS_MUSIC)
		turnMusic(LOADING_SOUND);
	// use for loop to print logo
	for (int i = 0; i < logoLength; i++) {
		goToXYAndPrintColorText(logo_X, logo_Y + i, logo[i]);
	}

	// print DOT ... effect
	for (int i = 0; i < 3; i++) {
		Sleep(700);
		GotoXY(dotP.x + i * 4 + 1, dotP.y);
		cout << "_";
		GotoXY(dotP.x + i * 4, dotP.y + 1);
		cout << "(_)";
	}

	turnMusic(0);

	// delete banner
	clearScreen();
}

void printStartingBanner() {
	int logo_X = (BORDER_WIDTH / 2) - 18;
	int logo_Y = (BORDER_HEIGH / 2) - 2;

	const int logoLength = 4;
	string logo[logoLength] = {
					"  ___ _            _   ",
					" / __| |_ __ _ _ _| |_ ",
					" \\__ \\  _/ _` | '_|  _|",
					" |___/\\__\\__,_|_|  \\__|"				
	};
	string index[12] = {
		"  ____",
		" |__ /",
		"  |_ \\",
		" |___/",
		"  ___ ", 
		" |_  )",
		"  / / ",
		" /___|", 
		"  _ ",
		" / |", 
		" | |",
		" |_|"};
	POINT indexP = { logo_X + 16 , logo_Y };

	if (HAS_MUSIC)
		turnMusic(STARTING_SOUND);
	// use for loop to print logo "START"
	for (int i = 0; i < logoLength; i++) {
		goToXYAndPrintColorText(logo_X, logo_Y + i, logo[i]);
	}
	Sleep(250);
	clearScreen();

	for (int i = 1; i < 4; i++) {
		for (int j = (i - 1) * 4; j < 4 * i; j++) {
			goToXYAndPrintColorText(indexP.x, indexP.y + j - 4 * (i - 1), index[j]);
		}
		Sleep(1000);
		clearScreen();
	}

	turnMusic(0);

	// delete banner
	clearScreen();
}

void printWinnerBanner() {
	int xwinner = (CONSOLE_WIDTH / 2) - 12;
	int ywinner = (CONSOLE_HEIGH / 2) - 3;
	system("cls");
	int n = 1;
	string banner[6]{ " __          __  _____   _   _ ",
					 " \\ \\        / / |_   _| | \\ | |",
					 "  \\ \\  /\\  / /    | |   |  \\| |",
					 "   \\ \\/  \\/ /     | |   | . ` |",
					 "    \\  /\\  /     _| |_  | |\\  |",
					 "     \\/  \\/     |_____| |_| \\_|" };
	while (true)
	{
		for (int i = 0; i < 6; i++) {
			//GotoXY(POINT{ xwinner, ywinner + i });
			goToXYAndPrintColorText(POINT{ xwinner, ywinner + i }, banner[i], i + 1);
		}
		n++;
		if (n == 14)
			n = 1;
		Sleep(72);
	}
}

void drawBoard(int x, int y, int width, int height) {
	int leftMargin = 4;
	int topMargin = 3;

	for (int i = 0; i < width + 1; i++) {
		GotoXY(POINT{ x + i, y });
		cout << (unsigned char)223;
		GotoXY(POINT{ x + width - i - 1, y + height - 1 });
		cout << (unsigned char)220;
		Sleep(1);
	}
	for (int i = 0; i < height; i++) {
		GotoXY(x + width, y + height - i - 1);
		cout << (unsigned char)219;
		GotoXY(x, i );
		cout << (unsigned char)219;
		GotoXY(BORDER_WIDTH, i);
		cout << (unsigned char)219;
		Sleep(5);
	}

	POINT lengthTextPos = { BORDER_WIDTH + leftMargin + 4, topMargin };
	POINT roundTextPos = { BORDER_WIDTH + leftMargin + 5, topMargin + 2 };
	LENGTH_VALUE_POS = { lengthTextPos.x + (int)strlen(LENGTH_TEXT) + 2, lengthTextPos.y };
	ROUND_VALUE_POS = { roundTextPos.x + (int)strlen(ROUND_TEXT) + 2, roundTextPos.y };

	GotoXY(lengthTextPos);
	cout << LENGTH_TEXT << "  ";
	GotoXY(LENGTH_VALUE_POS);
	cout << SNAKE_SIZE;

	GotoXY(roundTextPos);
	cout << ROUND_TEXT << "  ";
	GotoXY(ROUND_VALUE_POS);
	cout << ROUND;

	GotoXY(POINT{ BORDER_WIDTH + leftMargin, 10 });
	cout << "[" << (char)PAUSE_KEY << "]    PAUSE";
	GotoXY(POINT{ BORDER_WIDTH + leftMargin, 11 });
	cout << "[" << (char)SAVE_KEY << "]    SAVE";
	GotoXY(POINT{ BORDER_WIDTH + leftMargin, 12 });
	cout << "[" << (char)LOAD_KEY << "]    LOAD";
	GotoXY(POINT{ BORDER_WIDTH + leftMargin, 13 });
	cout << "[ESC]  EXIT GAME";

	
	int guideLine = 20;
	// Guide Line
	GotoXY(BORDER_WIDTH + leftMargin + 2, guideLine);
	cout << "GUIDE PLAYER";
	GotoXY(BORDER_WIDTH + leftMargin, ++guideLine);
	cout << "[" << (char)UP_KEY << "]  MOVE UP";
	GotoXY(BORDER_WIDTH + leftMargin, ++guideLine);
	cout << "[" << (char)DOWN_KEY << "]  MOVE DOWN";
	GotoXY(BORDER_WIDTH + leftMargin, ++guideLine);
	cout << "[" << (char)LEFT_KEY << "]  MOVE LEFT";
	GotoXY(BORDER_WIDTH + leftMargin, ++guideLine);
	cout << "[" << (char)RIGHT_KEY << "]  MOVE RIGHT";
}

void drawOutLine(int x, int y, int width, int height) {
	for (int i = 0; i < height; i++) {
		GotoXY(x, y + i );
		for (int j = 0; j < width; j++) {
			if (i == 0)
				cout << (unsigned char)220;
			else if (i == height - 1)
				cout << (unsigned char)223;
			else if (j == 0 || j == width - 1)
				cout << (unsigned char)219;
			else
				cout << " ";
		}
	}
}

void drawBorderForSaveLoadBox(int x, int y, int width, int height) {
	for (int i = 0; i < height; i++) {
		GotoXY(x, y + i );
		for (int j = 0; j < width; j++) {
			if (i == 0)
				cout << (unsigned char)220;
			else if (i == height - 1)
				cout << (unsigned char)223;
			else if (j == 0 || j == width - 1)
				cout << (unsigned char)219;
			else
				cout << " ";
		}
	}
}

void randomPositionOfGate() {
	do {
		gateP.x = rand() % (BORDER_WIDTH - 4) + 2;
		gateP.y = rand() % (BORDER_HEIGH - 4) + 3;
	} while (!isValid(gateP.x, gateP.y) || !isValid(gateP.x - 1, gateP.y) || !isValid(gateP.x + 1, gateP.y)
		|| !isValid(gateP.x - 1, gateP.y - 1) || !isValid(gateP.x + 1, gateP.y - 1));
}

void drawGate() {

	randomPositionOfGate();

	GotoXY(POINT{ gateP.x + 1, gateP.y });
	cout << (unsigned char)223;
	GotoXY(POINT{ gateP.x - 1, gateP.y - 1 });
	cout << (unsigned char)219;
	GotoXY(POINT{ gateP.x, gateP.y });
	cout << (unsigned char)223;
	GotoXY(POINT{ gateP.x + 1, gateP.y - 1 });
	cout << (unsigned char)219;
	GotoXY(POINT{ gateP.x - 1, gateP.y });
	cout << (unsigned char)223;

	GATE_EXIST = true;
}

void deleteGate() {
	GotoXY(POINT{ gateP.x + 1, gateP.y });
	cout << " ";
	GotoXY(POINT{ gateP.x - 1, gateP.y - 1 });
	cout << " ";
	GotoXY(POINT{ gateP.x, gateP.y });
	cout << " ";
	GotoXY(POINT{ gateP.x + 1, gateP.y - 1 });
	cout << " ";
	GotoXY(POINT{ gateP.x - 1, gateP.y });
	cout << " ";

	GATE_EXIST = false;
}

void displaySnakeSize() {
	GotoXY(LENGTH_VALUE_POS);
	cout << SNAKE_SIZE;
}

void displayRoundNumber() {
	GotoXY(ROUND_VALUE_POS);
	cout << ROUND;
}

void deleteBox(int height, int width) {
	int xgame;
	int ygame;
	if (PLAYING_STATE) {
		xgame = (BORDER_WIDTH - width) / 2;
		ygame = (BORDER_HEIGH - height) / 2;
	}
	else {
		xgame = (CONSOLE_WIDTH - width) / 2;
		ygame = (CONSOLE_HEIGH - height) / 2;
	}
	 
	for (int i = 0; i < height; i++) {
		GotoXY(POINT{ xgame, ygame + i });
		for (int j = 0; j < width; j++) {
			cout << " ";
		}
	}
}

void deleteSnake() {
	for (int i = 0; i < SNAKE_SIZE; i++) {
		GotoXY(snake[i]);
		cout << " ";
	}
}

void deleteFood() {
	GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
	cout << " ";
}

void deleteEntityOnScreen() {
	// Delete Food
	deleteFood();

	// Delete Snake
	deleteSnake();

	if (GATE_EXIST)
		deleteGate();
}

void clearScreen() {
	int xgame = 1;
	int ygame = 1;

	for (int i = 0; i < BORDER_HEIGH - 2; i++) {
		GotoXY(POINT{ 1, 1 + i });
		for (int j = 0; j < BORDER_WIDTH - 1; j++) {
			cout << " ";
		}
	}
}

void resetPressedKey() {
	pressedKey = '\0';
}