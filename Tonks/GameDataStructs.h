/*!
 *  \brief     Game Structs.
 *  \details   This file contains structs used within the project
 *  \author    Martin Olšiak
 */

#pragma once
typedef struct Player {
	char name[20];
	int tankX;
	int tankY;
	int color;
	int hp;
	int movementLeft;
	int aimAngle;
};

typedef struct GameData {
	int rows;
	int cols;
	bool keyListenerEnabled;
	int gameStage;
	int menuSelected;
	bool controlsShown;
	int playerCount;
	int initiative;
	char** map;
	bool playerWon;
	int errorCode;
};