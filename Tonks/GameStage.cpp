/*!
 *  \brief     Game Stage.
 *  \details   This file contains functions to draw, update the map and handle player actions.
 *  \author    Martin Olšiak
 */
#include "GameStage.h"
#include "Math.h"

void updatePlayerPosition(GameData* data, Player* players) {
	for (int i = 0; i < data->playerCount; i++) {
		if (players[i].hp == 0) {
			data->map[players[i].tankX][players[i].tankY] = ' ';
			continue;
		}

		int j = players[i].tankX;
		while (data->map[j + 1][players[i].tankY] == ' ') {
			if (j >= data->rows)
				break;
			data->map[j][players[i].tankY] = ' ';
			data->map[j + 1][players[i].tankY] = 'T';
			j++;
			players[i].tankX = j;


		}
	}
}
void updateGameStageScreen(GameData* data, Player* players) {
	system("cls");
	drawMap(data->map, &data->rows, &data->cols, &data->playerCount, players);
	drawPlayerInfo(players, &data->initiative, &data->playerCount);
}
void drawMap(char** map, int* rows, int* cols, int* playerCount, Player* players) {
	printf("\n\n");

	int color = 0;
	for (int i = 0; i < *rows; i++) {
		printf("		    ");

		for (int j = 0; j < *cols; j++) {
			if (map[i][j] == 'T') {

				for (int k = 0; k < *playerCount; k++) {
					if (i == players[k].tankX && j == players[k].tankY) {
						color = players[k].color;
					}

				}
			}
			output(map[i][j], color);
			color = 0;
		}
		printf("\n");
	}
}
void drawPlayerInfo(Player* players, int* initiative, int* playerCount) {
	printf("\n \n");



	for (int i = 0; i < *playerCount; i++) {

		if (players[i].hp <= 0) {
			continue;
		}

		if (i == *initiative) {
			textcolor(players[i].color);
			_cprintf("\n		  > Player: %s", players[i].name);
		}
		else {
			textcolor(15);
			_cprintf("\n		    Player: %s", players[i].name);
		}

		_cprintf("\n		    Hit Points:  %d", players[i].hp);
		_cprintf("\n		    Movement: %d", players[i].movementLeft);
		_cprintf("\n		    Cannon Angle: %d", players[i].aimAngle);
		_cprintf("\n		    TankX: %d", players[i].tankX);
		_cprintf("\n		    TankY: %d", players[i].tankY);
		printf("\n");
		textcolor(15);
	}
}
int checkFotWinContidion(GameData* data, Player* players) {
	int numberOfPlayers = 0;
	int winningPlayer = 0;
	for (int i = 0; i < data->playerCount; i++) {
		if (players[i].hp > 0) {
			numberOfPlayers++;
			winningPlayer = i;
		}
	}

	if (numberOfPlayers == 1) {
		system("cls");
		printf("\n\n\n		    PLAYER %s WON!", players[winningPlayer].name);
		data->gameStage = GAME_END_STAGE;
		return 0;
	}

	return 1;

}
int mapInit(GameData* data, Player* players) {
	system("cls");

	if (data->rows != -1) {
		data->map = (char**)malloc(data->rows * sizeof(char*));
		for (int i = 0; i < data->rows; i++)
			data->map[i] = (char*)malloc(data->cols * sizeof(char));

		if (GenerateMap(data->map, &data->rows, &data->cols) != 0) {
			return 1;
		}
		else {
			spawnPlayers(data, players);
			assignTanks(data, players);
			drawMap(data->map, &data->rows, &data->cols, &data->playerCount, players);
		}
	}
	else {
		loadMap(data, players);
		if (data->errorCode != 0) {
			return 1;
		}
		spawnPlayers(data, players);
		assignTanks(data, players);
		drawMap(data->map, &data->rows, &data->cols, &data->playerCount, players);

	}




	return 0;
}
void loadMap(GameData* data, Player* players) {
	FILE* fptr;
	FILE* ptr = fopen("\map.txt", "r");

	if (ptr == NULL) {
		data->errorCode = 2;

	}
	else {
		if (fscanf(ptr, "%d %d", &data->rows, &data->cols) != 2) {
			data->rows = 50;
			data->cols = 75;
			if (GenerateMap(data->map, &data->rows, &data->cols) != 0) {
				data->errorCode = 3;
				return;
			}
			spawnPlayers(data, players);
			assignTanks(data, players);
			drawMap(data->map, &data->rows, &data->cols, &data->playerCount, players);
			return;
		}
		data->rows = data->rows + 2;
		data->cols = data->cols + 2;
		data->map = (char**)malloc(data->rows * sizeof(char*));
		for (int i = 0; i < data->rows; i++)
			data->map[i] = (char*)malloc(data->cols * sizeof(char));

		char c = 0;
		int i = 1;
		int j = 1;
		while (c != '\n') {
			c = fgetc(ptr);
		}

		for (i; i < data->rows - 1; i++) {
			for (j; j < data->cols - 1; j++) {
				c = fgetc(ptr);
				if (c == '\n') {
					j--;
					continue;
				}

				if (c != ' ' && c != '=' && c != 'H') {
					if (!isspace(c)) {
						data->errorCode = 4;
						return;
					}
				}
				data->map[i][j] = c;

			}
			printf("\n");
			j = 1;
		}

		for (int k = 0; k < data->cols; k++) {
			data->map[0][k] = 'X';
			data->map[data->rows - 1][k] = 'X';
		}
		for (int l = 0; l < data->rows; l++) {
			data->map[l][0] = 'X';
			data->map[l][data->cols - 1] = 'X';
		}
		fclose(ptr);

	}
}
void assignTanks(GameData* data, Player* players) {
	time_t t;
	srand((unsigned)time(&t));
	int k = (rand() % ((data->playerCount - 1) - 0 + 1)) + 0;
	int startNum = k;

	for (int i = 1; i < (data->rows - 1); i++) {
		for (int j = 1; j < (data->cols - 1); j++) {
			if (data->map[i][j] == 'T') {
				players[k].tankX = i;
				players[k].tankY = j;
				k++;
				if (k > data->playerCount - 1)
					k = 0;
				if (k == startNum)
					return;
			}
		}
	}

}
void spawnPlayers(GameData* data, Player* players) {
	time_t t;
	srand((unsigned)time(&t));

	for (int i = 0; i < data->playerCount; i++) {
		bool posFound = false;
		int random = (rand() % ((data->cols - 1) - 0 + 1)) + 0;
		for (int j = 1; j < data->rows; j++) {
			if (data->map[j][random] == '=' && data->map[j - 1][random] == ' ') {
				data->map[j - 1][random] = 'T';
				posFound = true;
				break;
			}
		}
		if (posFound == false) {
			for (int k = 1; k < data->rows; k++) {
				for (int l = 1; l < data->cols; l++) {
					if (data->map[k][l] == '=' && data->map[k - 1][l] == ' ') {
						data->map[k - 1][l] = 'T';
						k = data->rows;
						l = data->cols;
					}
				}
			}

		}
	}
}
void playerMove(GameData* data, Player* players, int direction) {



	if (players[data->initiative].movementLeft > 0) {
		data->map[players[data->initiative].tankX][players[data->initiative].tankY] = ' ';

		int previousPosX = players[data->initiative].tankX;
		int previousPosY = players[data->initiative].tankY;


		if (data->map[previousPosX][previousPosY + direction] == ' ') {
			if (data->map[previousPosX + 1][previousPosY + direction] == '=' || data->map[previousPosX + 1][previousPosY + direction] == 'H') {
				//move straight
				players[data->initiative].tankX = previousPosX;
				players[data->initiative].tankY = previousPosY + direction;
			}
			else if (data->map[previousPosX + 1][previousPosY + direction] == ' ') {
				if (data->map[previousPosX + 2][previousPosY + direction] == '=' || data->map[previousPosX + 2][previousPosY + direction] == 'H') {
					//move down
					players[data->initiative].tankX = previousPosX + 1;
					players[data->initiative].tankY = previousPosY + direction;
				}


			}
		}
		else if (data->map[previousPosX][previousPosY + direction] == '=' || data->map[previousPosX][previousPosY + direction] == 'H') {
			if (data->map[previousPosX - 1][previousPosY + direction] == ' ') {
				//move up
				players[data->initiative].tankX = previousPosX - 1;
				players[data->initiative].tankY = previousPosY + direction;

			}
		}

		data->map[players[data->initiative].tankX][players[data->initiative].tankY] = 'T';
		players[data->initiative].movementLeft -= 1;

	}
}
void playerShoot(GameData* data, Player* players) {

	if (players[data->initiative].hp < 0) {
		data->initiative += 1;
		return;
	}
	int direction;
	bool hit = false;
	int angle = players[data->initiative].aimAngle;

	if (angle < 90) {
		direction = -1;
	}
	else if (angle > 90) {
		direction = 1;
	}
	else {
		direction = 0;
	}

	int x = players[data->initiative].tankX; // rows
	int y = players[data->initiative].tankY + direction; // cols

	if (angle == 90) {
		int curX = x;
		//Vertical Throw
		while (!hit) {
			curX--;

			if (curX <= 0) {
				tankTakeDamage(data, players, x, y);
				//TOP
				if (data->map[x - 1][y] == '=' || data->map[x - 1][y] == 'H') {
					data->map[x - 1][y] = ' ';
				}
				if (data->map[x - 1][y] == 'T') {
					tankTakeDamage(data, players, (x - 1), y);
				}
				//BOTTOM
				if (data->map[x + 1][y] == '=' || data->map[x + 1][y] == 'H') {
					data->map[x + 1][y] = ' ';
				}
				if (data->map[x + 1][y] == 'T') {
					tankTakeDamage(data, players, (x + 1), y);
				}
				//LEFT
				if (data->map[x][y - 1] == '=' || data->map[x][y - 1] == 'H') {
					data->map[x][y - 1] = ' ';
				}
				if (data->map[x][y - 1] == 'T') {
					tankTakeDamage(data, players, (x), y - 1);
				}
				//RIGHT
				if (data->map[x][y + 1] == '=' || data->map[x][y + 1] == 'H') {
					data->map[x][y + 1] = ' ';
				}
				if (data->map[x][y + 1] == 'T') {
					tankTakeDamage(data, players, (x), y + 1);
				}
				hit = true;
				break;
			}

			if (data->map[curX][players[data->initiative].tankY] != ' ') {
				if (data->map[curX][y] == 'T') {
					tankTakeDamage(data, players, curX, y);
				}
				else {
					data->map[curX][players[data->initiative].tankY] = ' ';

					if (curX > 0) {
						//TOP
						if (data->map[curX - 1][y] == '=' || data->map[curX - 1][y] == 'H') {
							data->map[curX - 1][y] = ' ';
						}
						if (data->map[curX - 1][y] == 'T') {
							tankTakeDamage(data, players, curX - 1, y);
						}
						//BOTTOM
						if (data->map[curX + 1][y] == '=' || data->map[curX + 1][y] == 'H') {
							data->map[curX + 1][y] = ' ';
						}
						if (data->map[curX + 1][y] == 'T') {
							tankTakeDamage(data, players, (curX + 1), y);
						}
						//LEFT
						if (data->map[curX][y - 1] == '=' || data->map[curX][y - 1] == 'H') {
							data->map[curX][y - 1] = ' ';
						}
						if (data->map[curX][y - 1] == 'T') {
							tankTakeDamage(data, players, curX, y - 1);
						}
						//RIGHT
						if (data->map[curX][y + 1] == '=' || data->map[curX][y + 1] == 'H') {
							data->map[curX][y + 1] = ' ';
						}
						if (data->map[curX][y + 1] == 'T') {
							tankTakeDamage(data, players, curX, y + 1);
						}
					}
				}
				hit = true;
				break;
			}
		}
	}
	else {
		//Angled Throw
		int tempY = 0;
		double curX = 0;

		double velocityX = TANK_SHOT_VELOCITY * sin(angle);
		double velocityY = TANK_SHOT_VELOCITY * cos(angle);

		//printf("ANGLE %d X %d Y %d\n" , angle, x, y);
		while (!hit) {

			if (y > data->cols || y < 0) {
				break;
			}

			double time = tempY / velocityY;
			curX = (velocityX * time) - (0.5 * 10 * pow(time, 2));

			//printf("Row:%f Col:%d \n ", x - (curX), tempY);

			if (x - (int)curX > 0 && x - (int)curX < data->rows) {
				if (data->map[x - (int)curX][y] != ' ') {
					//printf("HIT %c", data->map[x - (int)curX][y]);
					hit = true;
					if (data->map[x - (int)curX][y] == 'T') {
						//CENTER
						tankTakeDamage(data, players, (x - (int)curX), y);
						//TOP
						if (data->map[x - (int)curX - 1][y] == '=' || data->map[x - (int)curX - 1][y] == 'H') {
							data->map[x - (int)curX - 1][y] = ' ';
						}
						if (data->map[x - (int)curX - 1][y] == 'T') {
							tankTakeDamage(data, players, (x - (int)curX - 1), y);
						}
						//BOTTOM
						if (data->map[x - (int)curX + 1][y] == '=' || data->map[x - (int)curX + 1][y] == 'H') {
							data->map[x - (int)curX + 1][y] = ' ';
						}
						if (data->map[x - (int)curX + 1][y] == 'T') {
							tankTakeDamage(data, players, (x - (int)curX + 1), y);
						}
						//LEFT
						if (data->map[x - (int)curX][y - 1] == '=' || data->map[x - (int)curX][y - 1] == 'H') {
							data->map[x - (int)curX][y - 1] = ' ';
						}
						if (data->map[x - (int)curX][y - 1] == 'T') {
							tankTakeDamage(data, players, (x - (int)curX), y - 1);
						}
						//RIGHT
						if (data->map[x - (int)curX][y + 1] == '=' || data->map[x - (int)curX][y + 1] == 'H') {
							data->map[x - (int)curX][y + 1] = ' ';
						}
						if (data->map[x - (int)curX][y + 1] == 'T') {
							tankTakeDamage(data, players, (x - (int)curX), y + 1);
						}
					}
					else if (data->map[x - (int)curX][y] == 'X') {
						break;
					}
					else {
						//CENTER
						data->map[x - (int)curX][y] = ' ';
						//TOP
						if (data->map[x - (int)curX - 1][y] == '=' || data->map[x - (int)curX - 1][y] == 'H') {
							data->map[x - (int)curX - 1][y] = ' ';
						}
						if (data->map[x - (int)curX - 1][y] == 'T') {
							tankTakeDamage(data, players, (x - (int)curX - 1), y);
						}
						//BOTTOM
						if (data->map[x - (int)curX + 1][y] == '=' || data->map[x - (int)curX + 1][y] == 'H') {
							data->map[x - (int)curX + 1][y] = ' ';
						}
						if (data->map[x - (int)curX + 1][y] == 'T') {
							tankTakeDamage(data, players, (x - (int)curX + 1), y);
						}
						//LEFT
						if (data->map[x - (int)curX][y - 1] == '=' || data->map[x - (int)curX][y - 1] == 'H') {
							data->map[x - (int)curX][y - 1] = ' ';
						}
						if (data->map[x - (int)curX][y - 1] == 'T') {
							tankTakeDamage(data, players, (x - (int)curX), y - 1);
						}
						//RIGHT
						if (data->map[x - (int)curX][y + 1] == '=' || data->map[x - (int)curX][y + 1] == 'H') {
							data->map[x - (int)curX][y + 1] = ' ';
						}
						if (data->map[x - (int)curX][y + 1] == 'T') {
							tankTakeDamage(data, players, (x - (int)curX), y + 1);
						}

					}
				}
			}
			else {
				break;
			}
			tempY++;
			y += direction;
		}
	}




	players[data->initiative].movementLeft = TANK_MOVEMENT;
	updatePlayerPosition(data, players);
	updateInitiative(data, players);

}
void tankTakeDamage(GameData* data, Player* players, int x, int y) {

	players[data->initiative].hp -= TANK_DAMAGE;
	if (players[data->initiative].hp <= 0) {
		data->map[players[data->initiative].tankX][players[data->initiative].tankY] = ' ';
	}
}

void updateInitiative(GameData* data, Player* players) {

	data->initiative += 1;

	if (data->initiative >= data->playerCount) {
		data->initiative = 0;
	}

	if (players[data->initiative].hp <= 0)
		updateInitiative(data, players);


}