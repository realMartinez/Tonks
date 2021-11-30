/*!
 *  \brief     Key Listener.
 *  \details   This file contains functions that listen and handle player input 
 *  \author    Martin Olšiak
 */
#include "Tonks.h"
#include "GameDataStructs.h"


//codes for input
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13


/**
 * Handles up arrow key input
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 */
void keyPressedUp(GameData* data, Player* players);
/**
 * Handles down arrow key input
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 */
void keyPressedDown(GameData* data, Player* players);
/**
 * Handles left arrow key input
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 */
void keyPressedLeft(GameData* data, Player* players);
/**
 * Handles right arrow key input
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 */
void keyPressedRight(GameData* data, Player* players);
/**
 * Handles enter key input
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 */
void keyPressedEnter(GameData* data, Player* players);
/**
 * Handles listening for input
 * @param GameData data contains general game related variables
 * @param Player players contains list of player related variables for each player
 */
void keyListener(GameData* data, Player* players);