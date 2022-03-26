#include "Snake.h"

HIGHLENGTH HighLength[5];
HIGHLENGTH NewLength;
POINT snake[MAX_SIZE_SNAKE];
POINT food[4];
POINT gateP;
int INDEX_ID;
int CHAR_LOCK;
int MOVING;
int SPEED;
int HEIGH_CONSOLE;
int WIDTH_CONSOLE;
int FOOD_INDEX;
int SIZE_SNAKE;
int SIZE_PLUS;
int STATE;
int ROUND;
bool GATE_EXIST;

char newgame[] = "NEW GAME";
char highlength[] = "HIGH LENGTH";
char exitgame[] = "EXIT GAME";
char yes[] = "Yes";
char no[] = "No";
char ok[] = "OK";

int temp;
int win;

//handle crash and effect 

bool CrashGate()
{
	POINT head = { snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y };
	return (head.x == gateP.x + 1 && head.y == gateP.y) || (head.x == gateP.x - 1 && head.y == gateP.y - 1)
		|| (head.x == gateP.x && head.y == gateP.y && CHAR_LOCK == 'S') || (head.x == gateP.x + 1 && head.y == gateP.y - 1)
		|| (head.x == gateP.x - 1 && head.y == gateP.y);
}

bool CrashWall()
{
	return (snake[SIZE_SNAKE - 1].x + 1 == WIDTH_CONSOLE + 1
		|| snake[SIZE_SNAKE - 1].x == 0
		|| snake[SIZE_SNAKE - 1].y + 1 == HEIGH_CONSOLE
		|| snake[SIZE_SNAKE - 1].y == 0);
}

bool CrashItself()
{
	for (int i = 0; i < SIZE_SNAKE - 1; i++)
		if (snake[i].x == snake[SIZE_SNAKE - 1].x && snake[i].y == snake[SIZE_SNAKE - 1].y)
			return true;
	return false;
}

void BlinkSnake()
{
	for (int j = 0; j < 5; j++)
	{
		Sleep(200);
		for (int i = 0; i < SIZE_SNAKE; i++)
		{
			GotoXY(snake[i].x, snake[i].y);
			cout << STUDENT_ID[i];
		}
		Sleep(100);
		for (int i = 0; i < SIZE_SNAKE; i++)
		{
			GotoXY(snake[i].x, snake[i].y);
			cout << " ";
		}
	}
}

//Xu ly giao dien chinh (menu) va hop thoai thoat (exit)
void PrintLogo()
{
	int logo_X = (WIDTH_CONSOLE / 2) - 26;
	int logo_Y = (HEIGH_CONSOLE / 2) - 5;

	for (int i = 1; i <= 14; i++)
	{
		char Line[] = "  S-S-S   N-N     N      A-A      K    K  E-E-E-E";
		GotoXY(logo_X, logo_Y);
		printColorText(i, Line);

		strcpy(Line, " S        N  N    N     A   A     K  K    E");
		GotoXY(logo_X, logo_Y + 1);
		printColorText(i, Line);

		strcpy(Line, "  S-S-S   N   N   N    A-A-A-A    K-K     E-E-E-E");
		GotoXY(logo_X, logo_Y + 2);
		printColorText(i, Line);

		strcpy(Line, "       S  N    N  N   A       A   K  K    E");
		GotoXY(logo_X, logo_Y + 3);		
		printColorText(i, Line);

		strcpy(Line, "  S-S-S   N     N-N  A         A  K    K  E-E-E-E");
		GotoXY(logo_X, logo_Y + 4);		
		printColorText(i, Line);
		Sleep(70);
	}
}

MENU gameMenu()
{
	MENU select;

	int menu_X = (WIDTH_CONSOLE / 2) - 5;
	int menu_Y = (HEIGH_CONSOLE / 2) + 3;

	PrintLogo();

	GotoXY(menu_X, menu_Y);
	printColorText(COLOR_LIGHT_BLUE, newgame);
	
	GotoXY(menu_X, menu_Y + 2);
	cout << highlength;

	GotoXY(menu_X, menu_Y + 4);
	cout << exitgame;

	select.choice = newgame;
	while (true)
	{
		if (select.choice == newgame)
		{
			select.selecting = _getch();
			if ((int)select.selecting == 13)
				break;
			if (select.selecting == 's')
			{				
				GotoXY(menu_X, menu_Y);
				printColorText(COLOR_WHITE, newgame);
					
				GotoXY(menu_X, menu_Y + 2);
				printColorText(COLOR_LIGHT_BLUE, highlength);
				select.choice = highlength;
			}
		}
		if (select.choice == highlength)
		{
			select.selecting = _getch();
			if ((int)select.selecting == 13)
			{
				ShowHighLength();
				break;
			}
			if (select.selecting == 's')
			{
				GotoXY(menu_X, menu_Y + 2);
				printColorText(COLOR_WHITE, highlength);

				GotoXY(menu_X, menu_Y + 4);
				printColorText(COLOR_LIGHT_BLUE, exitgame);
				select.choice = exitgame;
			}
			if (select.selecting == 'w')
			{
				GotoXY(menu_X, menu_Y + 2);
				printColorText(COLOR_WHITE, highlength);

				GotoXY(menu_X, menu_Y);
				printColorText(COLOR_LIGHT_BLUE, newgame);
				select.choice = newgame;
			}
		}
		if (select.choice == exitgame)
		{
			select.selecting = _getch();
			if ((int)select.selecting == 13)
				break;
			if (select.selecting == 'w')
			{
				GotoXY(menu_X, menu_Y + 4);
				printColorText(COLOR_WHITE, exitgame);

				GotoXY(menu_X, menu_Y + 2);
				printColorText(COLOR_LIGHT_BLUE, highlength);
				select.choice = highlength;
			}
		}
	}
	return select;
}

bool ContinueGame()
{
	bool Continue = true;

	int column = 30;
	int row = 7;
	int game_X = (WIDTH_CONSOLE / 2) - 15;
	int game_Y = (HEIGH_CONSOLE / 2) - 3;
	MENU select;

	GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
	cout << " ";

	for (int i = 0; i < row; i++)
	{
		GotoXY(game_X, game_Y + i);
		for (int j = 0; j < column; j++)
		{
			if (i == 0)
				cout << (unsigned char)220;
			else if (i == row - 1)
				cout << (unsigned char)223;
			else if (j == 0 || j == column - 1)
				cout << (unsigned char)219;
			else
				cout << " ";
		}
	}

	GotoXY(game_X + 3, game_Y + 2);
	cout << "Do you want to play more?";
	GotoXY(game_X + 8, game_Y + 4);
	printColorText(COLOR_LIGHT_BLUE, yes);
	GotoXY(game_X + 20, game_Y + 4);
	cout << no;
	select.choice = yes;

	if (temp == 'D' || temp == '13') temp = 'A';

	while (true)
	{
		if (select.choice == yes)
		{
			select.selecting = temp;
			if ((int)select.selecting == 13)
				break;
			if (select.selecting == 'D')
			{
				GotoXY(game_X + 8, game_Y + 4);
				printColorText(COLOR_WHITE, yes);
				GotoXY(game_X + 20, game_Y + 4);
				printColorText(COLOR_LIGHT_BLUE, no);
				select.choice = no;
			}
		}
		if (select.choice == no)
		{
			select.selecting = temp;
			if ((int)select.selecting == 13)
				break;
			if (select.selecting == 'A')
			{
				GotoXY(game_X + 8, game_Y + 4);				
				printColorText(COLOR_LIGHT_BLUE, yes);
	
				GotoXY(game_X + 20, game_Y + 4);					
				printColorText(COLOR_WHITE, no);
				select.choice = yes;
			}
		}
	}
	if (select.choice == yes)
		StartGame();
	if (select.choice == no)
		Continue = false;

	return Continue;
}

// Draw food and snake
void DrawFood()
{
	GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);

	char* food = new char[2];
	food[0] = (unsigned char)219;
	food[1] = '\0';
	printColorText(COLOR_RED, food);

	delete[] food;
}

void DrawSnake()
{
	for (int i = 0; i < SIZE_SNAKE; i++)
	{
		char body = STUDENT_ID[i];
		GotoXY(snake[i].x, snake[i].y);
		cout << body;
	}
}

void DeleteTail()
{
	for (int i = 0; i < SIZE_SNAKE; i++)
	{
		GotoXY(snake[i].x, snake[i].y);
		cout << " ";
	}
}

// Handle save and load game
bool IsExistedFileName(string FileName)
{
	ifstream f_user(".\\Data\\username.txt");
	string tmp;

	while (f_user >> tmp)
		if (tmp == FileName)
		{
			f_user.close();
			return true;
		}
	f_user.close();
	return false;
}

bool IsValidFileName(string filename)
{
	for (int i = 0; i < filename.length(); i++)
		if (filename[i] == '>' || filename[i] == '<' || filename[i] == ':'
			|| filename[i] == '"' || filename[i] == '/' || filename[i] == '\\'
			|| filename[i] == '|' || filename[i] == '?' || filename[i] == '*')
			return false;
	return true;
}

void SaveData()
{
	string filename;

	int column = 30;
	int row = 8;
	int game_X = (WIDTH_CONSOLE / 2) - 15;
	int game_Y = (HEIGH_CONSOLE / 2) - 3;

	for (int i = 0; i < row; i++)
	{
		GotoXY(game_X, game_Y + i);
		for (int j = 0; j < column; j++)
		{
			if (i == 0)
				cout << (unsigned char)220;
			else if (i == row - 1)
				cout << (unsigned char)223;
			else if (j == 0 || j == column - 1)
				cout << (unsigned char)219;
			else
				cout << " ";
		}
	}

	GotoXY(game_X + 9, game_Y + 2);
	cout << "Save and Exit";
	GotoXY(game_X + 14, game_Y + 5);
	printColorText(3, ok);
	GotoXY(game_X + 3, game_Y + 3);
	cout << "Name: ";

	do
	{
		GotoXY(game_X + 9, game_Y + 3);
		cin >> filename;
		GotoXY(game_X + 3, game_Y + 4);
		if (IsExistedFileName(filename))
			cout << "File existed, re-type!";
		if (!IsValidFileName(filename))
			cout << "Invalid char, re-type!";
		if (filename.length() > 18)
			cout << "Too long, re-type!";

		if (IsExistedFileName(filename) || !IsValidFileName(filename) || filename.length() > 18)
		{
			GotoXY(game_X + 9, game_Y + 3);
			for (int i = 0; i < 18; i++)
				cout << " ";
		}
	} while (IsExistedFileName(filename) || !IsValidFileName(filename) || filename.length() > 18);

	DeleteBox();

	ofstream fo(".\\Data\\" + filename);

	ofstream f_user;
	f_user.open(".\\Data\\username.txt", ios::app);
	f_user << filename << endl;
	f_user.close();

	fo << SIZE_SNAKE << " " << SIZE_PLUS << endl;

	for (int i = 0; i < SIZE_SNAKE; i++)
		fo << snake[i].x << " " << snake[i].y << endl;

	fo << FOOD_INDEX << endl;

	fo << food[FOOD_INDEX].x << " " << food[FOOD_INDEX].y << endl;

	if (GATE_EXIST)
		fo << gateP.x << " " << gateP.y << endl;
	else
		fo << -1 << " " << -1 << endl;

	fo << INDEX_ID << endl;

	fo << SPEED << endl;

	fo << ROUND << endl;

	fo << MOVING << endl;

	fo << CHAR_LOCK << endl;

	fo << win;

	fo.close();

	NewLength.name = filename;
	NewLength.length = SIZE_SNAKE + SIZE_PLUS;

	CreateNewHighLength();
	SortHighLength();
}

void LoadData()
{
	string FileName;
	int column = 30;
	int row = 8;
	int xgame = (WIDTH_CONSOLE / 2) - 15;
	int ygame = (HEIGH_CONSOLE / 2) - 3;

	for (int i = 0; i < row; i++)
	{
		GotoXY(xgame, ygame + i);
		for (int j = 0; j < column; j++)
		{
			if (i == 0)
				cout << (unsigned char)220;
			else if (i == row - 1)
				cout << (unsigned char)223;
			else if (j == 0 || j == column - 1)
				cout << (unsigned char)219;
			else
				cout << " ";
		}
	}

	GotoXY(xgame + 11, ygame + 2);
	cout << "Load data";
	GotoXY(xgame + 14, ygame + 5);
	printColorText(3, ok);
	GotoXY(xgame + 3, ygame + 3);
	cout << "Name: ";

	do
	{
		GotoXY(xgame + 9, ygame + 3);
		cin >> FileName;
		if (!IsExistedFileName(FileName))
		{
			GotoXY(xgame + 3, ygame + 4);
			cout << "Not existed user!";
			GotoXY(xgame + 9, ygame + 3);
			for (int i = 0; i < 18; i++)
				cout << " ";
		}
	} while (!IsExistedFileName(FileName));

	DeleteBox();

	for (int i = 0; i < SIZE_SNAKE; i++)
	{
		GotoXY(snake[i].x, snake[i].y);
		cout << " ";
	}

	ifstream fi(".\\Data\\" + FileName);

	fi >> SIZE_SNAKE >> SIZE_PLUS;

	GotoXY(8, HEIGH_CONSOLE);
	cout << SIZE_SNAKE + SIZE_PLUS;

	for (int i = 0; i < SIZE_SNAKE; i++)
		fi >> snake[i].x >> snake[i].y;

	GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);

	fi >> FOOD_INDEX;
	cout << " ";
	fi >> food[FOOD_INDEX].x >> food[FOOD_INDEX].y;

	fi >> gateP.x >> gateP.y;
	if (gateP.x != -1 && gateP.y != -1)
	{
		GotoXY(gateP.x + 1, gateP.y);
		cout << (unsigned char)223;
		GotoXY(gateP.x - 1, gateP.y - 1);
		cout << (unsigned char)219;
		GotoXY(gateP.x, gateP.y);
		cout << (unsigned char)223;
		GotoXY(gateP.x + 1, gateP.y - 1);
		cout << (unsigned char)219;
		GotoXY(gateP.x - 1, gateP.y);
		cout << (unsigned char)223;
		GATE_EXIST = true;
	}

	fi >> INDEX_ID;

	fi >> SPEED;

	fi >> ROUND;

	fi >> MOVING;

	fi >> CHAR_LOCK;

	fi >> win;

	fi.close();
}

//Xu ly nguyen do dai snake va khi an xong food o mot cap

void DrawGate()
{
	do
	{
		gateP.x = rand() % (WIDTH_CONSOLE - 4) + 2;
		gateP.y = rand() % (HEIGH_CONSOLE - 4) + 3;
	} while (!IsValid(gateP.x, gateP.y) || !IsValid(gateP.x - 1, gateP.y) || !IsValid(gateP.x + 1, gateP.y)
		|| !IsValid(gateP.x - 1, gateP.y - 1) || !IsValid(gateP.x + 1, gateP.y - 1));

	GotoXY(gateP.x + 1, gateP.y);
	cout << (unsigned char)223;
	GotoXY(gateP.x - 1, gateP.y - 1);
	cout << (unsigned char)219;
	GotoXY(gateP.x, gateP.y);
	cout << (unsigned char)223;
	GotoXY(gateP.x + 1, gateP.y - 1);
	cout << (unsigned char)219;
	GotoXY(gateP.x - 1, gateP.y);
	cout << (unsigned char)223;

	GATE_EXIST = true;
}

void ProcessGate()
{
	if (!GATE_EXIST)
		DrawFood();
	if (snake[SIZE_SNAKE - 1].x == gateP.x && snake[SIZE_SNAKE - 1].y == gateP.y && GATE_EXIST && CHAR_LOCK == 'W')
	{
		SIZE_SNAKE--;
		SIZE_PLUS++;
	}

	GotoXY(24, HEIGH_CONSOLE);
	cout << ROUND;

	if (SIZE_SNAKE == 0)
	{
		GotoXY(gateP.x + 1, gateP.y);
		cout << " ";
		GotoXY(gateP.x - 1, gateP.y - 1);
		cout << " ";
		GotoXY(gateP.x, gateP.y);
		cout << " ";
		GotoXY(gateP.x + 1, gateP.y - 1);
		cout << " ";
		GotoXY(gateP.x - 1, gateP.y);
		cout << " ";

		GATE_EXIST = false;

		win++;
		ROUND++;
		SPEED++;
		SIZE_SNAKE = 4 * ROUND;
		SIZE_PLUS = 0;

		for (int i = 0; i < SIZE_SNAKE; i++)
		{
			snake[i].x = gateP.x;
			snake[i].y = gateP.y;
		}

		snake[SIZE_SNAKE - 1].x = gateP.x;
		snake[SIZE_SNAKE - 1].y = gateP.y + 1;
	}
}

void PrintWinner()
{
	int xwinner = (WIDTH_CONSOLE / 2) - 12;
	int ywinner = (HEIGH_CONSOLE / 2) - 3;
	system("cls");
	int i = 1;
	while (true)
	{
		char Line1[] = "W   W   W  II  N-N     N";
		GotoXY(xwinner, ywinner);
		printColorText(i, Line1);
		strcpy(Line1, "W   W   W  II  N  N    N");
		GotoXY(xwinner, ywinner + 1);
		printColorText(i, Line1);
		strcpy(Line1, "W  W W  W  II  N   N   N");
		GotoXY(xwinner, ywinner + 2);
		printColorText(i, Line1);
		strcpy(Line1, "W W   W W  II  N    N  N");
		GotoXY(xwinner, ywinner + 3);
		printColorText(i, Line1);
		strcpy(Line1, "W       W  II  N     N-N");
		GotoXY(xwinner, ywinner + 4);
		printColorText(i, Line1);
		i++;
		if (i == 14)
			i = 1;
		Sleep(72);
	}
}

//Xu ly top 5 HIGH LENGTH
bool IsEmptyHighLengthFile()
{
	ifstream fi;
	string name;
	int length;

	fi.open(".\\Data\\highlength.txt");
	if (fi >> name >> length)
	{
		fi.close();
		return false;
	}

	fi.close();
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

void InitializeHighLength()
{
	if (!IsEmptyHighLengthFile())
	{
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

void SortHighLength()
{
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

void ShowHighLength()
{
	ifstream fi;
	fi.open(".\\Data\\highlength.txt");

	string name;
	int length;

	system("cls");

	int column = 31;
	int row = 9;
	int xHighLength = (WIDTH_CONSOLE / 2) - 15;
	int yHighLength = (HEIGH_CONSOLE / 2) - 4;

	for (int j = 0; j < row; j++)
	{
		GotoXY(xHighLength, yHighLength + j);
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
		GotoXY(xHighLength + 10, yHighLength + 1);
		cout << "HIGH LENGTH";

		int i = 0;

		while (fi >> name >> length)
		{
			GotoXY(xHighLength + 4, yHighLength + i + 3);
			cout << "#" << i + 1 << ". ";
			GotoXY(xHighLength + 8, yHighLength + i + 3);
			cout << name;
			GotoXY(xHighLength + 27, yHighLength + i + 3);
			cout << length;
			i++;
		}

		if (_kbhit())
			break;
	}
	fi.close();
}

// Another functions
void InitialGame()
{
	system("title Snake");
	FixConsoleWindow();
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	WIDTH_CONSOLE = csbi.srWindow.Right - csbi.srWindow.Left;
	HEIGH_CONSOLE = csbi.srWindow.Bottom - csbi.srWindow.Top - 1;

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);

	STATE = 0;
}

bool IsValid(int x, int y)
{
	for (int i = 0; i < SIZE_SNAKE; i++)
		if (snake[i].x == x && snake[i].y == y)
			return false;
	return true;
}

void ResetData()
{
	win = 0;
	ROUND = 1;
	GATE_EXIST = false;
	INDEX_ID = 4;
	CHAR_LOCK = 'A', MOVING = 'D', SPEED = 1; FOOD_INDEX = 0, SIZE_SNAKE = 4;
	SIZE_PLUS = 0;

	snake[0] = { WIDTH_CONSOLE / 2 - 2, HEIGH_CONSOLE / 2 };
	snake[1] = { WIDTH_CONSOLE / 2 - 1, HEIGH_CONSOLE / 2 };
	snake[2] = { WIDTH_CONSOLE / 2, HEIGH_CONSOLE / 2 };
	snake[3] = { WIDTH_CONSOLE / 2 + 1, HEIGH_CONSOLE / 2 };

	GenerateFood();
}

void StartGame()
{
	system("cls");

	ResetData();

	DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE);
	STATE = 1;

	//PlaySound(L".\\Sound\\main.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	turnBackgroundMusic(1);
}

void ExitGame(thread& t)
{
	system("cls");
	t.detach();
}

void PauseGame(HANDLE t)
{
	SuspendThread(t);
	// draw banner pause
}

void ProcessDead()
{
	STATE = 0;
	PlaySound(L".\\Sound\\die.wav", NULL, SND_ASYNC);
	BlinkSnake();
}

void GenerateFood()
{
	int x, y;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX_SIZE_FOOD; i++)
	{
		do
		{
			x = rand() % (WIDTH_CONSOLE - 2) + 1;
			y = rand() % (HEIGH_CONSOLE - 2) + 1;
		} while (IsValid(x, y) == false);
		food[i] = { x, y };
	}
}

void Eat()
{
	snake[SIZE_SNAKE] = food[FOOD_INDEX];

	SIZE_SNAKE++;
	INDEX_ID++;
	GotoXY(0, HEIGH_CONSOLE);
	cout << "Length: " << SIZE_SNAKE;

	if (FOOD_INDEX == MAX_SIZE_FOOD - 1)
	{
		DrawGate();
		FOOD_INDEX = 0;
		GenerateFood();
	}
	else
		FOOD_INDEX++;
}

void MoveRight()
{
	if (CrashWall() || CrashItself() || (CrashGate() && GATE_EXIST))
	{
		ProcessDead();
	}
	else
	{
		if (snake[SIZE_SNAKE - 1].x + 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y)
		{
			Eat();
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++)
		{
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SIZE_SNAKE - 1].x++;
	}
}

void MoveLeft()
{
	if (CrashWall() || CrashItself() || (CrashGate() && GATE_EXIST))
	{
		ProcessDead();
	}
	else
	{
		if (snake[SIZE_SNAKE - 1].x - 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y)
		{
			Eat();
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++)
		{
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SIZE_SNAKE - 1].x--;
	}
}

void MoveDown()
{
	if (CrashWall() || CrashItself() || (CrashGate() && GATE_EXIST))
	{
		ProcessDead();
	}
	else
	{
		if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y + 1 == food[FOOD_INDEX].y)
		{
			Eat();
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++)
		{
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SIZE_SNAKE - 1].y++;
	}
}

void MoveUp()
{
	if (CrashWall() || CrashItself() || (CrashGate() && GATE_EXIST))
	{
		ProcessDead();
	}
	else
	{
		if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y - 1 == food[FOOD_INDEX].y)
		{
			Eat();
		}
		for (int i = 0; i < SIZE_SNAKE - 1; i++)
		{
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SIZE_SNAKE - 1].y--;
	}
}

void ThreadFunc()
{
	while (true)
	{
		if (STATE == 1)
		{
			DeleteTail();
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
			ProcessGate();
			if (win == 9) {
				system("cls");
				PrintWinner();
			}
			else
				DrawSnake();
			Sleep(300 / SPEED);
		}
		else
		{
			bool Continue = ContinueGame();
			if (!Continue)
			{
				system("cls");
				exit(0);
			}
		}
	}
}

void DrawBoard(int x, int y, int width, int height)
{
	for (int i = 0; i < width + 1; i++)
	{
		GotoXY(x + i, y);
		cout << (unsigned char)223;
		GotoXY(x + width - i - 1, y + height - 1);
		cout << (unsigned char)220;
		Sleep(5);
	}
	for (int i = 0; i < height; i++)
	{
		GotoXY(x + width, y + height - i - 1);
		cout << (unsigned char)219;
		GotoXY(x, i);
		cout << (unsigned char)219;
		Sleep(15);
	}
	GotoXY(0, height);
	cout << "Length: " << SIZE_SNAKE << " \t Round: " << ROUND;
	GotoXY(0, height + 1);
	cout << "Pause : P \t Save : L \t Load: T \t Force exit: Esc";
}

void DeleteBox()
{
	int column = 30;
	int row = 8;
	int xgame = (WIDTH_CONSOLE / 2) - 15;
	int ygame = (HEIGH_CONSOLE / 2) - 3;

	for (int i = 0; i < row; i++)
	{
		GotoXY(xgame, ygame + i);
		for (int j = 0; j < column; j++)
		{
			if (i == 0)
				cout << " ";
			else if (i == row - 1)
				cout << " ";
			else if (j == 0 || j == column - 1)
				cout << " ";
			else
				cout << " ";
		}
	}
}


