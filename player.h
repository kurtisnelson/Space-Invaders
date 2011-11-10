/*
 * player.h
 *
 *  Created on: Nov 10, 2011
 *      Author: kurt
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include "lib/gba.h"
typedef struct {
  int r;
  int c;
  int health;
  COLOR * image;
} Player;

void drawPlayer(Player);
void movePlayer(Player *, int, int);
void hitPlayer(Player *);
#endif /* PLAYER_H_ */
