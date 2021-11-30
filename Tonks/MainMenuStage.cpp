/*!
 *  \brief     Main Menu Stage.
 *  \details   This file contains functions to draw, animate, update game menus and handles main game loop.
 *  \author    Martin Olšiak
 */
#include "MainMenuStage.h"
#include "GameDataStructs.h"




void drawMenu(int* selected, int* rows, int* cols, int* playerCount, bool* controlsShown) {
	char* mapSize;
	if (*rows == 10) {
		mapSize = "Small";
	}
	else if (*rows == 25) {
		mapSize = "Big";
	}
	else if (*rows == 15) {
		mapSize = "Medium";
	}
	else {
		mapSize = "Load Map";
	}

	printf("         _______  __   ____   ___    __  ___   __   _____\n        (__   __) )_) (    ) (   \\  |  )(   ) /  ) /  __ \\\n           | |        / /| |  |   \\ | |  | | / /   \\ <  \\_)\n           | |       / /_| |  | |\\ \\| |  |  ` <    _`'=.\n           | |      / /~~| |  | | \\   |  | |~\\ \\  ( \\__>`\\\n          (___)   (__/   |__)(___) \\___)(___) \\__) \\_____/ \n");
	printf("\n \n \n");

	if (*selected == 0) {
		printf("\n			>   Start Game");
	}
	else {
		printf("\n			    Start Game");
	}
	if (*selected == 1) {
		printf("\n			>   Map : %s", mapSize);
	}
	else {
		printf("\n			    Map : %s", mapSize);
	}

	if (*selected == 2) {
		printf("\n			>   Player Count: %d", *playerCount);
	}
	else {
		printf("\n			    Player Count: %d", *playerCount);
	}
	if (*selected == 3) {
		printf("\n			>   Controls");
	}
	else {
		printf("\n			    Controls");
	}

	if (*controlsShown == true) {
		printf("\n\n\n			    Up Arrow Key - Change aim angle of tak by +5");
		printf("\n			    Down Arrow Key - Change aim angle of tak by -5");
		printf("\n			    Right Arrow Key - Move to the right by 1");
		printf("\n			    Left Arrow Key - Move to the left by 1");
		printf("\n			    Enter - Fire and End turn");
	}

	


}
void animateMenu(int* selected, int* gameStage, clock_t* startTime, bool* screenOn, int* rows, int* cols, int* playerCount, bool* controlsShown) {


	clock_t currentTime = clock() * 1000 / CLOCKS_PER_SEC;
	clock_t time_spent = -((*startTime - currentTime) * 1000 / CLOCKS_PER_SEC);
	int i = -1;

	//printf("Current Time %d - Time spend %d ms\n", currentTime, time_spent);

	if (time_spent >= 500 && !*screenOn) {
		system("cls");
		drawMenu(selected, rows, cols, playerCount, controlsShown);
		*screenOn = true;
	}
	if (time_spent >= 1000 && screenOn) {

		system("cls");
		drawMenu(&i, rows, cols, playerCount, controlsShown);
		*startTime = currentTime;
		*screenOn = false;
	}



}
void drawPlayerMenu(GameData* data, Player* players) {

	int colors[MAX_PLAYERS] = { 9, 4, 13, 10, 11, 12, 5, 3 };
	data->keyListenerEnabled = false;


	for (int i = 0; i < data->playerCount; i++) {

		printf("         _______  __   ____   ___    __  ___   __   _____\n        (__   __) )_) (    ) (   \\  |  )(   ) /  ) /  __ \\\n           | |        / /| |  |   \\ | |  | | / /   \\ <  \\_)\n           | |       / /_| |  | |\\ \\| |  |  ` <    _`'=.\n           | |      / /~~| |  | | \\   |  | |~\\ \\  ( \\__>`\\\n          (___)   (__/   |__)(___) \\___)(___) \\__) \\_____/ \n");
		printf("\n \n \n");


		printf("\n			    Player %d Name: ", i + 1);

		scanf("%s", players[i].name);
		players[i].color = colors[i];

		system("cls");
	}


	system("cls");
	printf("\n \n \n");
	printf("\n			    Press Enter to start the game ");


	data->gameStage = GAME_PRESTAGE;
	data->keyListenerEnabled = true;






}
void gameLoop(GameData* data, Player* players) {

	clock_t startTime = clock() * 1000 / CLOCKS_PER_SEC;


	bool screenOn;

	system("cls");
	drawMenu(&data->menuSelected, &data->rows, &data->cols, &data->playerCount, &data->controlsShown);
	screenOn = true;
	data->keyListenerEnabled = true;

	while (data->gameStage != GAME_END_STAGE) {

		if (data->gameStage == MAIN_MENU_STAGE)
			animateMenu(&data->menuSelected, &data->gameStage, &startTime, &screenOn, &data->rows, &data->cols, &data->playerCount, &data->controlsShown);
		if (data->playerWon == true)
			break;
		if (data->errorCode != 0) {
			system("cls");
			switch (data->errorCode) {
			case 1:
				printf("Error%d: FAILED TO ALLOCATE MEMORY.", data->errorCode);
				break;
			case 2:
				printf("Error%d: FAILED TO OPEN FILE.", data->errorCode);
				break;
			case 3:
				printf("Error%d: FAILED TO GENERATE MAP.", data->errorCode);
				break;
			case 4:
				printf("Error%d: File \map.txt not found.", data->errorCode);
				break;
			}

			break;
		}

		keyListener(data, players);
	}
}
void gameStart(GameData* data, Player* players) {
	printf("         _______  __   ____   ___    __  ___   __   _____\n        (__   __) )_) (    ) (   \\  |  )(   ) /  ) /  __ \\\n           | |        / /| |  |   \\ | |  | | / /   \\ <  \\_)\n           | |       / /_| |  | |\\ \\| |  |  ` <    _`'=.\n           | |      / /~~| |  | | \\   |  | |~\\ \\  ( \\__>`\\\n          (___)   (__/   |__)(___) \\___)(___) \\__) \\_____/ \n");
	printf("\n \n \n \n");
	printf("			   [ O ]\n			     \\ \\      p\n			      \\ \\  \\o/\n			       \\ \\--'---_\n			       /\\ \\   / ~~\\_\n			 ./---/__|=/_/------//~~~\\\n			/___________________/O   O \\\n			(===(\_________(===(Oo o o O)\n			 \\~~~\\____/     \\---\\Oo__o--\n			   ~~~~~~~       ~~~~~~~~~~\n		");
	Sleep(2500);
	system("cls");
	data->gameStage = MAIN_MENU_STAGE;
	//printf("STAGE");
	gameLoop(data, players);
}



