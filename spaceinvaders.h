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
#include "player.h"
#include "bullet.h"
#define START_ENEMIES 10
#define MAX_BULLETS 15
void runGame();
void pauseGame();
void endGame();
int resetCheck();
int checkCollide();
int startLevel(int);
void drawGame(Alien *, Player, Bullet *);
void reset();
extern u32 needReset;
#endif /* SPACEINVADERS_H_ */
