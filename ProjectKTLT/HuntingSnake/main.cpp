#include "Snake.h"

int main() {
	initialGame();
	initializeHighLength();
	turnMusic(MENU_MUSIC);
	
	MENU choose = gameMenu();

	while (true) {
		if (choose.pressedButton == ENTER_KEY) {
			if (choose.choice == highlength_Menu || choose.choice == exitgame_Menu) {
				STATE = 0;
				system("cls");
				break;
			}
			system("cls");
			STATE = LIVE;
			break;
		}
	}
	if (STATE == LIVE) {
		startGame();
		thread t1(ThreadFunc);
		HANDLE handle_t1 = t1.native_handle();

		while (true) {
			pressedKey = toupper(_getch());
			if (STATE == LIVE) {
				// max level
				if (WIN == 9) { 
					pauseGame(handle_t1);
					exitGame(t1);
					return 0;
				}
				// Pause game
				else if (pressedKey == PAUSE_KEY) {					
					pauseGame(handle_t1);
					// if player want to stop game
					if (!pauseMenu()) {
						exitGame(t1);
						return 0;
					}

					ResumeThread(handle_t1);
				}
				// Save game
				else if (pressedKey == SAVE_KEY) {
					pauseGame(handle_t1);
					saveMenu();
					exitGame(t1);
					return 0;
				}
				// load game
				else if (pressedKey == LOAD_KEY) {
					pauseGame(handle_t1);
					loadMenu();					
					ResumeThread(handle_t1);
				}
				// exit game
				else if (pressedKey == ESC_KEY) {
					exitGame(t1);
					return 0;
				}
				else {
					if ((pressedKey != CHAR_LOCK) && (pressedKey == 'D' || pressedKey == 'A' || pressedKey == 'W' || pressedKey == 'S')) {
						MOVING = pressedKey;
						ResumeThread(handle_t1);
					}
				}
			}
		}
	}
	return 0;
}