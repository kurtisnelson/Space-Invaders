/*
 * player.c
 *
 *  Created on: Nov 10, 2011
 *      Author: kurt
 */
#include "player.h"
#include "lib/video.h"
#include "lib/color.h"
#include "images/player.h"

void
drawPlayer(Player a)
{
  if(a.image == 0)
    return;
  drawImage3(a.r, a.c, PLAYER_WIDTH, PLAYER_HEIGHT, a.image);
}

void
zeroPlayer(Player * p)
{
  p->c = 0;
  p->r = 0;
  p->image = 0;
  p->health = 0;
}

void
movePlayer(Player * a, int r, int c)
{
  if(a->health <= 0)
    return;
  int oldR = a->r;
  int oldC = a->c;
  if (a->c + c > 0 && a->c + c + PLAYER_WIDTH < SCREEN_WIDTH)
    a->c += c;
  if (a->r + r > 0 && a->r + r + PLAYER_HEIGHT < SCREEN_HEIGHT)
    a->r += r;
  if(oldR - a->r != 0)
    drawRect(oldR, oldC, PLAYER_WIDTH, PLAYER_HEIGHT, BLACK);
  else if(a->c > oldC)
    drawRect(oldR, oldC, c, PLAYER_HEIGHT, BLACK);
  else if(a->c < oldC)
    drawRect(oldR, a->c+PLAYER_WIDTH, -1*c, PLAYER_HEIGHT, BLACK);
  drawPlayer(*a);
}

void
hitPlayer(Player * a)
{
  a->health--;
  if (a->health <= 0)
    {
      drawRect(a->r, a->c, PLAYER_WIDTH, PLAYER_HEIGHT, BLACK);
      zeroPlayer(a);
    }
}

