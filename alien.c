/*
 * alien.c
 *
 *  Created on: Nov 8, 2011
 *      Author: kurt
 */
#include "alien.h"
#include "lib/color.h"
#include "lib/video.h"

void
drawAlien(Alien a)
{
  drawImage3(a.r, a.c, ALIEN_WIDTH, ALIEN_HEIGHT, a.image);
}

void
moveAlien(Alien * a, int r, int c)
{
  int oldR = a->r;
  int oldC = a->c;
  if (a->c + c + ALIEN_WIDTH < SCREEN_WIDTH && a->c + c > 0)
    a->c += c;
  if (a->r + r + ALIEN_HEIGHT < SCREEN_HEIGHT && a->r + r > 0)
    a->r += r;
  drawRect(oldR, oldC, ALIEN_WIDTH, ALIEN_HEIGHT, BLACK);
  drawAlien(*a);
}
