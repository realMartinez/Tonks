/*!
 *  \brief     Game Stage.
 *  \details   This file contains functions to draw, update the map and handle player actions.
 *  \author    Martin Olšiak
 */


#include "MapGen.h"
#include "PlayerInput.h"
#include "Tonks.h"


/**
 * Refreshes the screen in Game Stage
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 */
void updateGameStageScreen(GameData* data, Player* players);
/**
 * Prints out the map
 * @param char** map array of pointers containing map data
 * @param int* rows height of the map
 * @param int* cols width of the map
 * @param int playerCount contains number of players playing
 * @param Player players contains list of player related variables for each player
 */
void drawMap(char** map, int* rows, int* cols, int* playerCount, Player* players);
/**
 * Prints out player related info
 * @param Player players contains list of player related variables for each player
 * @param int* initiative contains current initiative
 * @param int* playerCount contains number of players playing
 */
void drawPlayerInfo(Player* player, int* initiative, int* playerCount);
/**
 * Checks whether player has won
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 */
int checkFotWinContidion(GameData* data, Player* players);
/**
 * Handles map initialization and generation
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 */
int mapInit(GameData* data, Player* players);
/**
 * Puts players on the map
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 */
void spawnPlayers(GameData* data, Player* players);
/**
 * Loads map from file
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 */
void loadMap(GameData* data, Player* players);
/**
 * Assigns tanks to players
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 */
void assignTanks(GameData* data, Player* players);
/**
 * Handles player movement
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 * @param int direction determines if player is facing left or right
 */
void playerMove(GameData* data, Player* players, int direction);
/**
 * Handles player shooting
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 */
void playerShoot(GameData* data, Player* players);
/**
 * Handles damage distribution
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 * @param int x position of target on x axis
 * @param int y position of target on y axis
 */
void tankTakeDamage(GameData* data, Player* players, int x, int y);
/**
 * Updates current initiative
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 */
void updateInitiative(GameData* data, Player* players);
/**
 * Updates player positions when falling
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 */
void updatePlayerPosition(GameData* data, Player* players);
