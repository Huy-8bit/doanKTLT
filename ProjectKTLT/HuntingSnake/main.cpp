#include "Snake.h"

void controlInGame() {
	thread t1(ThreadFunc);
	HANDLE handle_t1 = t1.native_handle();

	// control in game
	while (true) {
		pressedKey = toupper(_getch());
		if (STATE == LIVE) {
			// max level
			if (LEVEL - 1 == MAX_LEVEL) {
				pauseGame(handle_t1);
				break;
			}
			// Pause game
			else if (pressedKey == PAUSE_KEY) {
				pauseGame(handle_t1);
				// if player want to stop game
				pauseMenu();
				if(PLAYING_STATE == WAITING_STATE)
					break;
				else 
					ResumeThread(handle_t1);
			}
			// Save game
			else if (pressedKey == SAVE_KEY) {
				pauseGame(handle_t1);
				PLAYING_STATE = SAVING_STATE;
				saveMenu();
				continueGame();
				ResumeThread(handle_t1);
			}
			// load game
			else if (pressedKey == LOAD_KEY) {
				pauseGame(handle_t1);
				PLAYING_STATE = LOADING_STATE;
				loadMenu();
				continueGame();
				ResumeThread(handle_t1);
			}
			// exit game
			else if (pressedKey == ESC_KEY) {
				pauseGame(handle_t1);
				PLAYING_STATE = WAITING_STATE;
				break;
			}
			else {
				if ((pressedKey != CHAR_LOCK && pressedKey != MOVING) && (pressedKey == RIGHT_KEY || pressedKey == LEFT_KEY || pressedKey == UP_KEY || pressedKey == DOWN_KEY)) {
					if (HAS_MUSIC)
						turnMusic(TYPE_KEY_SOUND);

					MOVING = pressedKey;
					ResumeThread(handle_t1);
				}
			}
		}
		else if(pressedKey == ENTER_KEY) {
			break;
		}
	}
	exitGame(t1);
}

int main() {
	initialGame();
	initializeHighScore();
	turnMusic(MENU_MUSIC);
	
	while (true) {
		switch (PLAYING_STATE)
		{
		case WAITING_STATE:
			handleMainMenu();
			break;

		case RUNNING_STATE:
			startNewGame();
			controlInGame();
			break;

		case LOADING_STATE:
			startGame();
			controlInGame();
			break;

		case LOSING_STATE:
			break;

		case EXIT_STATE:
			return 0;


		default:
			break;
		}
	}

	return 0;
}