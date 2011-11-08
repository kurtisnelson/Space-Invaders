/*
 * spaceinvaders.h
 *
 *  Created on: Nov 7, 2011
 *      Author: kurt
 */

#ifndef SPACEINVADERS_H_
#define SPACEINVADERS_H_
#include "lib/gba.c"
void runGame();
void pauseGame();
int resetCheck();
void reset();
extern u32 needReset;
#endif /* SPACEINVADERS_H_ */
