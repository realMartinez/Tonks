/*!
 *  \brief     Map Generation.
 *  \details   This file contains functions to generate the map.
 *  \author    Martin Olšiak
 */
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHT_GRAY 7
#define DARK_GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_MAGENTA 12
#define YELLOW 13
#define WHITE 14

#include "Tonks.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Changes color of the next character printed
 * @param int color determines which color should be used
 **/
void textcolor(int color);

/**
 * Prints out character in specified color
 * @param char s character to be printed
 * @param int color determines which color should be used
 */
void output(char s, int playerColor);

/**
 * Randomly generates the map and stores it in array of pointers
 * @param char** map array of pointers in which the map will be stored
 * @param int* rows determines height of the map
 * @param int* cols determines width of the map
 */
int GenerateMap(char** map, int* rows, int* cols);