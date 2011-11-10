/*
 * bullet.h
 *
 *  Created on: Nov 10, 2011
 *      Author: kurt
 */

#ifndef BULLET_H_
#define BULLET_H_
#include "lib/gba.h"
typedef struct {
  int r;
  int c;
  int dR;
  int dC;
  int health;
  COLOR * image;
} Bullet;

void drawBullet(Bullet);
void moveBullet(Bullet *);
void hitBullet(Bullet *);
#endif /* BULLET_H_ */
