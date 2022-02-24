#include<iostream>
#include<string>
#include<windows.h>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include<vector>
#define MAX_SIZE_SNAKE 10
#define MAX_SIZE_FOOD 4
#define MAX_SPEED 3
using namespace std;
POINT snake[10];
POINT food[4];
int char_lock;
int moving;
int speed;
int height_console, width_console;
int food_index;
int size_snake;
int state;

void FixConsoleWindow() {
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void GotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
bool IsValid(int x, int y) {
    for (int i = 0; i < size_snake; i++) {
        if (snake[i].x == x && snake[i].y == y)
            return false;
    }
    return true;
}
void GenerateFood() {
    int x, y;
    srand(time(NULL));
    for (int i = 0; i < MAX_SIZE_FOOD; i++) {
        do {
            x = rand() % (width_console - 1) + 1;
            y = rand() % (height_console - 1) + 1;
        } while (IsValid(x, y) == false);
        food[i] = { x,y };
    }
}
void ResetData() {
    char_lock = 'A', moving = 'D', speed = 1, food_index = 0, size_snake = 6, width_console = 70, height_console = 20;
    snake[0] = { 10,5 };
    snake[1] = { 11,5 };
    snake[2] = { 12,5 };
    snake[3] = { 13,5 };
    snake[4] = { 14,5 };
    snake[5] = { 15,5 };
    GenerateFood();
}
void DrawBoard(int x, int y, int width, int height, int curPosX = 0, int curPosY = 0) {
    GotoXY(x, y);cout << 'X';
    for (int i = 1; i < width; i++)cout << 'X';
    cout << 'X';
    GotoXY(x, height + y);cout << 'X';
    for (int i = 1; i < width; i++)cout << 'X';
    cout << 'X';
    for (int i = y + 1; i < height + y; i++) {
        GotoXY(x, i);cout << 'X';
        GotoXY(x + width, i);cout << 'X';
    }
    GotoXY(curPosX, curPosY);
}
void ExitGame(HANDLE t) {
    system("cls");
    TerminateThread(t, 0);
}
void PauseGame(HANDLE t) {
    SuspendThread(t);
}
void Eat() {
    snake[size_snake] = food[food_index];
    if (food_index == MAX_SIZE_FOOD - 1) {
        food_index = 0;
        size_snake = 6;
        if (speed == MAX_SPEED) speed = 1;
        else speed++;
        GenerateFood();
    }
    else {
        food_index++;
        size_snake++;
    }
}
void ProcessDead() {
    state = 0;
    GotoXY(0, height_console + 1);
    cout << "Game Over";
}
void StartGame() {
    system("cls");
    ResetData();
    system("cls");
    DrawBoard(0, 0, width_console, height_console);
    state = 1;
}
void DrawSnakeAndFood(char* str) {
    GotoXY(food[food_index].x, food[food_index].y);
    cout << str;
    for (int i = 0; i < size_snake; i++) {
        GotoXY(snake[i].x, snake[i].y);
        cout << str;
    }
}
void MoveRight() {
    if (snake[size_snake - 1].x + 1 == width_console) {
        ProcessDead();
    }
    else {
        if (snake[size_snake - 1].x + 1 == food[food_index].x && snake[size_snake - 1].y == food[food_index].y) {
            Eat();
        }
        for (int i = 0; i < size_snake - 1; i++) {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[size_snake - 1].x++;
    }
}
void MoveLeft() {
    if (snake[size_snake - 1].x - 1 == 0) {
        ProcessDead();
    }
    else {
        if (snake[size_snake - 1].x - 1 == food[food_index].x && snake[size_snake - 1].y == food[food_index].y) {
            Eat();
        }
        for (int i = 0; i < size_snake - 1; i++) {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[size_snake - 1].x--;
    }
}
void MoveDown() {
    if (snake[size_snake - 1].y + 1 == height_console) {
        ProcessDead();
    }
    else {
        if (snake[size_snake - 1].x == food[food_index].x && snake[size_snake - 1].y + 1 == food[food_index].y) {
            Eat();
        }
        for (int i = 0; i < size_snake - 1; i++) {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[size_snake - 1].y++;
    }
}
void MoveUp() {
    if (snake[size_snake - 1].y - 1 == 0) {
        ProcessDead();
    }
    else {
        if (snake[size_snake - 1].x == food[food_index].x && snake[size_snake - 1].y - 1 == food[food_index].y) {
            Eat();
        }
        for (int i = 0; i < size_snake - 1; i++) {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[size_snake - 1].y--;
    }
}
void ThreadFunc() {
    while (1) {
        if (STATE == 1) {
            DrawSnakeAndFood(" ");
            switch (moving)
            {
            case 'A':
                MoveLeft();
                break;
            case 'D':
                MoveRight();
                break;
            case 'W':
                MoveUp();
                break;
            case 'S':
                MoveDown();
                break;
            }
            DrawSnakeAndFood("O");
            Sleep(1000 / SPEED);
        }
    }
}



int main() {

    int temp;

    FixConsoleWindow();

    StartGame();

    thread t1(ThreadFunc); //Create thread for snake

    HANDLE handle_t1 = t1.native_handle(); //Take handle of thread

    while (1) {

        temp = toupper(getch());
        if (STATE == 1) {
            if (temp == 'P') {
                PauseGame(handle_t1);
            }
            else if (temp == 27) {
                ExitGame(handle_t1);
                return;
            }
            else {
                ResumeThread(handle_t1);
                if ((temp != CHAR_LOCK) && (temp == 'D' || temp == 'A' || temp ==
                    'W' || temp == 'S'))
                {
                    if (temp == 'D') CHAR_LOCK = 'A';
                    else if (temp == 'W') CHAR_LOCK = 'S';
                    else if (temp == 'S') CHAR_LOCK = 'W';
                    else CHAR_LOCK = 'D';
                    MOVING = temp;

                }
            }
        }
        else {
            if (temp == 'Y') StartGame();
            else {
                ExitGame(handle_t1);
                return;
            }
        }
    }
    return 0;
}