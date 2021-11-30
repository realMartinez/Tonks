/*!
 *  \brief     Map Generation.
 *  \details   This file contains functions to generate the map.
 *  \author    Martin Olšiak
 */

#include "MapGen.h"




void textcolor(int color)
{
	static int __BACKGROUND;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;


	GetConsoleScreenBufferInfo(h, &csbiInfo);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		color + (__BACKGROUND << 4));

}



void output(char s, int playerColor)
{
	if (s == 'X')
	{
		textcolor(DARK_GRAY);
		_cprintf("%c", s);
	}
	else if (s == 'H')
	{
		textcolor(BROWN);
		_cprintf("%c", s);
	}
	else if (s == '=')
	{
		textcolor(GREEN);
		_cprintf("%c", s);
	}
	else if(s == 'T'){
		textcolor(playerColor);
		_cprintf("%c", s);
	}
	else if (s == ' ') {
		textcolor(0);
		_cprintf("%c", s);
	}

}



int GenerateMap(char** map, int* rows, int* cols) {


	int random = (rand() % ((*rows - 5) - (5) + 1)) + 5;
	int groundLevel = random + (rand() % ((1) - (0))) - 1;
	if (groundLevel >= *rows) {
		groundLevel = 8;
	}
	map[random][0] = '-';

	for (int i = 1; i < *cols - 1; i++) {
		int randomize = 0;

		if (groundLevel <= 1) {
			randomize = (rand() % ((2) - (1) + 1)) + 1;
		}
		else if (groundLevel >= (*rows - 2)) {
			randomize = (rand() % ((3) - (2) + 1)) + 2;
		}
		else {
			randomize = (rand() % ((3) - (1) + 1)) + 1;
		}
		groundLevel = groundLevel + (randomize-2);

		if (groundLevel > *rows || groundLevel < 0) {
			return 1;
		}

		map[groundLevel][i] = '=';

		for (int j = *rows - 2; j > groundLevel; j--) {
			map[j][i] = 'H';
		}
		for (int j = 1; j < groundLevel; j++) {
			map[j][i] = ' ';
		}
	}
	
	for (int i = 0; i < *cols; i++) {
		map[0][i] = 'X';
		map[*rows - 1][i] = 'X';
	}
	for (int i = 0; i < *rows; i++) {
		map[i][0] = 'X';
		map[i][*cols - 1] = 'X';
	}
	return 0;

}