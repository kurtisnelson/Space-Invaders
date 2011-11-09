/*
 * alien.h
 *
 *  Created on: Nov 8, 2011
 *      Author: kurt
 */

#ifndef ALIEN_H_
#define ALIEN_H_
#include "lib/gba.h"
#include "images/alien.h"
typedef struct {
  int r;
  int c;
  int health;
  COLOR * image;
} Alien;

void drawAlien(Alien a);
void moveAlien(Alien * a, int r, int c);
#endif /* ALIEN_H_ */
