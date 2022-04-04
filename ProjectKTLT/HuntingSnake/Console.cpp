#include "Console.h"

int CONSOLE_HEIGH;
int CONSOLE_WIDTH;
int BORDER_HEIGH;
int BORDER_WIDTH;

POINT LENGTH_POS;
POINT ROUND_POS;

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
	case MAIN_MUSIC:
		PlaySound(TEXT(".\\Sound\\main.wav"), NULL, SND_LOOP | SND_ASYNC);
		break;
	case MENU_MUSIC:
		PlaySound(TEXT(".\\Sound\\menu.wav"), NULL, SND_LOOP | SND_ASYNC);
		break;
	case DEAD_MUSIC:
		PlaySound(TEXT(".\\Sound\\die.wav"), NULL, SND_LOOP | SND_ASYNC);
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
	for (int i = 0; i < width + 1; i++) {
		GotoXY(POINT{ x + i, y });
		cout << (unsigned char)223;
		GotoXY(POINT{ x + width - i - 1, y + height - 1 });
		cout << (unsigned char)220;
		Sleep(2);
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

	LENGTH_POS = { BORDER_WIDTH + 10, 2 };
	ROUND_POS = { BORDER_WIDTH + 9, 3 };

	GotoXY(POINT{ BORDER_WIDTH + 2, 2 });
	cout << "LENGTH  ";
	GotoXY(LENGTH_POS);
	cout << SNAKE_SIZE;

	GotoXY(POINT{ BORDER_WIDTH + 2, 3 });
	cout << "ROUND  ";
	GotoXY(ROUND_POS);
	cout << ROUND;

	GotoXY(POINT{ BORDER_WIDTH + 2, 4 });
	cout << "[" << (char)PAUSE_KEY << "]  PAUSE";
	GotoXY(POINT{ BORDER_WIDTH + 2, 5 });
	cout << "[" << (char)SAVE_KEY << "]  SAVE";
	GotoXY(POINT{ BORDER_WIDTH + 2, 6 });
	cout << "[" << (char)LOAD_KEY << "]  LOAD";
	GotoXY(POINT{ BORDER_WIDTH + 2, 7 });
	cout << "[ESC]  EXIT GAME";
	GotoXY(POINT{ BORDER_WIDTH + 2, 8 });
	cout << "[" << (char)UP_KEY << "]  MOVE UP";
	GotoXY(POINT{ BORDER_WIDTH + 2, 9 });
	cout << "[" << (char)DOWN_KEY << "]  MOVE DOWN";
	GotoXY(POINT{ BORDER_WIDTH + 2, 10 });
	cout << "[" << (char)LEFT_KEY << "]  MOVE LEFT";
	GotoXY(POINT{ BORDER_WIDTH + 2, 11 });
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

void drawGate() {

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
	GotoXY(LENGTH_POS);
	cout << SNAKE_SIZE;
}

void displayRoundNumber() {
	GotoXY(ROUND_POS);
	cout << ROUND;
}

void deleteBox(int row, int column) {
	int xgame = (BORDER_WIDTH - column) / 2;
	int ygame = (BORDER_HEIGH - row) / 2;

	for (int i = 0; i < row; i++) {
		GotoXY(POINT{ xgame, ygame + i });
		for (int j = 0; j < column; j++) {
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


void resetPressedKey() {
	pressedKey = '\0';
}