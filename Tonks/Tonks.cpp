/*!
 *  \brief     Main.
 *  \details   This file contains game data, player data and starts the game.
 *  \author    Martin Olšiak
 */

#include "Tonks.h"





void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void Cleanup(char** map, int rows) {
	for (int i = 0; i < rows; i++)
		free(map[i]);
	free(map);
}

int main()
{
	//Startup

	Player* players = (Player*)malloc(MAX_PLAYERS * sizeof(*players));;
	for (int i = 0; i < MAX_PLAYERS; i++) {
		strcpy_s(players[i].name, "default");
		players[i].hp = TANK_HP;
		players[i].movementLeft = TANK_MOVEMENT;
		players[i].aimAngle = 0;
		players[i].tankX = 0;
		players[i].tankY = 0;

	}

	GameData data;
	data.rows = -1;
	data.cols = 0;
	data.keyListenerEnabled = false;
	data.gameStage = ENTRY_STAGE;
	data.menuSelected = 0;
	data.playerCount = 2;
	data.map = 0;
	data.initiative = 0;
	data.playerWon = false;
	data.errorCode = 0;
	data.controlsShown = false;

	hidecursor();
	gameStart(&data, players);

	Cleanup(data.map, data.rows);
	return data.errorCode;
}
