/*!
 *  \brief     Main.
 *  \details   This file contains game data, player data and starts the game.
 *  \author    Martin Olšiak
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include "MainMenuStage.h"
#include "GameStage.h"
#include "GameDataStructs.h"


#define ENTRY_STAGE 0
#define MAIN_MENU_STAGE 1
#define MENU_STAGE 2
#define PLAYER_STAGE 3
#define GAME_PRESTAGE 4
#define GAME_STAGE 5
#define GAME_END_STAGE 6

#define TANK_DAMAGE 5
#define TANK_HP 10
#define TANK_MOVEMENT 2
#define TANK_SHOT_VELOCITY 15

#define MAX_PLAYERS 8

//Error codes 1 = failed to malloc 2 = failed to open file 3 = failed to generate map 4 = invalid file

/**
 * Hides console cursor
 */
void hidecursor();
/**
 * Frees allocated memory 
 * @param char** map array of pointers containing map data
 * @param int rows number of rows of the array
 */
void Cleanup(char** map, int  rows);