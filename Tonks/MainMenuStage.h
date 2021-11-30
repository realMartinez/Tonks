/*!
 *  \brief     Main Menu Stage.
 *  \details   This file contains functions to draw, animate, update game menus and handles main game loop.
 *  \author    Martin Olšiak
 */

#include "Tonks.h"
#include "PlayerInput.h"
#include "GameDataStructs.h"



/**
 * Prints out main menu
 * @param int* selected contains which menu option is selected
 * @param int* rows height of the map
 * @param int* cols width of the map
 * @param int playerCount contains number of players playing
 * @param bool controlsShown
 */
void drawMenu(int* selected, int* rows, int* cols, int* playerCount, bool* controlsShown);
/**
 * Prints out player selection menu
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 */
void drawPlayerMenu(GameData* data, Player* players);
/**
 * Animates the main menu
 * @param int* selected contains which menu option is selected
 * @param int* gameStage contains in which stage the game is
 * @param clock_t* startTime processor time of function call
 * @param bool* screenOn animation stage
 * @param int* rows height of the map
 * @param int* cols width of the map
 * @param int playerCount contains number of players playing
 */
void animateMenu(int* selected, int* gameStage, clock_t* startTime, bool* screenOn, int* rows, int* cols, int* playerCount, bool* controlsShown);
/**
 * Main game loop
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 */
void gameLoop(GameData* data, Player* players);
/**
 * Starting screen and game start
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 */
void gameStart(GameData* data, Player* players);


