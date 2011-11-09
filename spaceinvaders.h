/*
 * spaceinvaders.h
 *
 *  Created on: Nov 7, 2011
 *      Author: kurt
 */

#ifndef SPACEINVADERS_H_
#define SPACEINVADERS_H_
#include "lib/gba.h"
#include "alien.h"
#define START_ENEMIES 10;
void runGame();
void pauseGame();
int resetCheck();
int startLevel(int);
void drawGame(Alien *);
void reset();
extern u32 needReset;
#endif /* SPACEINVADERS_H_ */
