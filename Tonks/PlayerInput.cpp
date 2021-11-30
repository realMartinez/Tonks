/*!
 *  \brief     Key Listener.
 *  \details   This file contains functions that listen and handle player input
 *  \author    Martin Olšiak
 */
#include "PlayerInput.h"



void keyPressedUp(GameData* data, Player* players) {
	if (data->gameStage == MAIN_MENU_STAGE) {
		if (data->menuSelected == 0)
			data->menuSelected = 3;
		else
			data->menuSelected = data->menuSelected - 1;

		system("cls");
		drawMenu(&data->menuSelected, &data->rows, &data->cols, &data->playerCount, &data->controlsShown);
	}

	if (data->gameStage == GAME_STAGE && players[data->initiative].hp > 0) {
		players[data->initiative].aimAngle += 5;
		if (players[data->initiative].aimAngle > 180)
			players[data->initiative].aimAngle = 180;
		updateGameStageScreen(data, players);
	}
}
void keyPressedDown(GameData* data, Player* players) {
	if (data->gameStage == MAIN_MENU_STAGE) {
		if (data->menuSelected == 3)
			data->menuSelected = 0;
		else
			data->menuSelected = data->menuSelected + 1;

		system("cls");
		drawMenu(&data->menuSelected, &data->rows, &data->cols, &data->playerCount, &data->controlsShown);
	}

	if (data->gameStage == GAME_STAGE && players[data->initiative].hp > 0) {
		players[data->initiative].aimAngle -= 5;
		if (players[data->initiative].aimAngle < 0)
			players[data->initiative].aimAngle = 0;
		updateGameStageScreen(data, players);
	}
}
void keyPressedLeft(GameData* data, Player* players) {

	if (data->gameStage == MAIN_MENU_STAGE) {
		switch (data->menuSelected) {
		case 1:
			if (data->rows == -1) {
				data->rows = 10;
				data->cols = 30;
			}
			else if (data->rows == 25) {
				//load
				data->rows = -1;
			}
			else if (data->rows == 15) {
				data->rows = 25;
				data->cols = 75;
			}
			else {
				data->rows = 15;
				data->cols = 45;
			}

			break;
		case 2:
			if (data->playerCount == 2) {
				data->playerCount = 8;
			}
			else {
				data->playerCount -= 1;
			}
			break;
		default:
			break;
		}
		system("cls");
		drawMenu(&data->menuSelected, &data->rows, &data->cols, &data->playerCount, &data->controlsShown);
	}

	if (data->gameStage == GAME_STAGE && players[data->initiative].hp > 0) {

		playerMove(data, players, -1);
		updatePlayerPosition(data, players);
		updateGameStageScreen(data, players);
	}

}
void keyPressedRight(GameData* data, Player* players) {

	if (data->gameStage == MAIN_MENU_STAGE) {
		switch (data->menuSelected) {
		case 1:
			if (data->rows == -1) {
				data->rows = 25;
				data->cols = 75;
			}
			else if (data->rows == 25) {
				data->rows = 15;
				data->cols = 45;
			}
			else if (data->rows == 15) {
				data->rows = 10;
				data->cols = 30;
			}
			else {
				//load map
				data->rows = -1;
			}


			break;
		case 2:
			if (data->playerCount == 8) {
				data->playerCount = 2;
			}
			else {
				data->playerCount += 1;
			}
			break;
		default:
			break;
		}
		system("cls");
		drawMenu(&data->menuSelected, &data->rows, &data->cols, &data->playerCount, &data->controlsShown);
	}


	if (data->gameStage == GAME_STAGE) {

		playerMove(data, players, +1);
		updatePlayerPosition(data, players);
		updateGameStageScreen(data, players);
	}

}
void keyPressedEnter(GameData* data, Player* players) {
	if (data->gameStage == MAIN_MENU_STAGE) {
		if (data->menuSelected == 0) {
			data->gameStage = PLAYER_STAGE;
			system("cls");
			drawPlayerMenu(data, players);
		}
		else if (data->menuSelected == 3) {
			if (data->controlsShown == false)
				data->controlsShown = true;
			else
				data->controlsShown = false;
			system("cls");
			drawMenu(&data->menuSelected, &data->rows, &data->cols, &data->playerCount, &data->controlsShown);

		}
	}
	else if (data->gameStage == GAME_PRESTAGE) {
		if (mapInit(data, players) != 0)
			return;
		drawPlayerInfo(players, &data->initiative, &data->playerCount);
		data->gameStage = GAME_STAGE;
	}
	else if (data->gameStage == GAME_STAGE && players[data->initiative].hp > 0) {

		playerShoot(data, players);
		updateGameStageScreen(data, players);
		if (checkFotWinContidion(data, players) == 0) {
			data->keyListenerEnabled = false;
			data->playerWon = true;

		}

	}
}
void keyListener(GameData* data, Player* players) {

	if (data->keyListenerEnabled) {
		int c = 0;
		if (kbhit())
			switch ((c = getch())) {
			case KEY_UP:
				//printf("\nUP");
				keyPressedUp(data, players);
				break;
			case KEY_DOWN:
				//printf("\nDOWN");
				keyPressedDown(data, players);
				break;
			case KEY_LEFT:
				//printf("\nLEFT");
				keyPressedLeft(data, players);
				break;
			case KEY_RIGHT:
				//printf("\nRIGHT");
				keyPressedRight(data, players);
				break;
			case KEY_ENTER:
				//printf("\nENTER");
				keyPressedEnter(data, players);
				break;
			default:
				break;
			}
	}

}