/*
 * bullet.c
 *
 *  Created on: Nov 10, 2011
 *      Author: kurt
 */
#include "bullet.h"
#include "lib/video.h"
#include "lib/color.h"
#include "images/bullet.h"

void
drawBullet(Bullet a)
{
  if(a.health == 0)
    return;
  drawImage3(a.r, a.c, BULLET_WIDTH, BULLET_HEIGHT, a.image);
}

void
moveBullet(Bullet * a)
{
  if(a->health <= 0)
    return;
  int oldR = a->r;
  int oldC = a->c;
  if (a->c + a->dC > 0 && a->c + a->dC + BULLET_WIDTH < SCREEN_WIDTH)
    a->c += a->dC;
  else
    a->health = 0;
  if (a->r + a->dR > 0 && a->r + a->dR + BULLET_HEIGHT < SCREEN_HEIGHT)
    a->r += a->dR;
  else
    a->health = 0;
  drawRect(oldR, oldC, BULLET_WIDTH, BULLET_HEIGHT, BLACK);
  drawBullet(*a);
}

void
hitBullet(Bullet * a)
{
  a->health--;
  if (a->health <= 0)
    {
      drawRect(a->r, a->c, BULLET_WIDTH, BULLET_HEIGHT, BLACK);
      a->r = 0;
      a->c = 0;
      a->image = 0;
    }
}

