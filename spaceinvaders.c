/*
 * spaceinvaders.c
 *
 *  Created on: Nov 7, 2011
 *      Author: kurt
 */
#include "spaceinvaders.h"
#include "alien.h"
#include "images/title.h"
#include "images/paused.h"
#include "lib/dma.h"
#include "lib/gba.h"
#include "lib/video.h"
#include "lib/input.h"

u32 needReset;
const COLOR gameScreen[38400] =
  { 0 };
static int numEnemies;

int
main()
{
  // Set the display mode properly
  vMode3();
  needReset = 1;
  while (1)
    {
      if (KEY_DOWN_NOW(KEY_START))
        {
          KEY_RELEASED_WAIT(KEY_START);
          runGame();
        }
      if (needReset)
        {
          reset();
        }
    }
  return (0);
}

void
reset()
{
  autoDraw(title);
  zeroMem((void *) gameScreen, (short) 38400);
  needReset = 0;
}

void
runGame()
{
  int level = 1;
  while (1)
    {
      level = startLevel(level);
      if (needReset == 1 || resetCheck())
        return;
    }
}

int
startLevel(int level)
{
  //Setup level parameters
  if (level == 1)
    numEnemies = 8;
  //Setup enemies
  Alien enemies[numEnemies];
  int dC = 0;
  int dR = 0;
  for (int i = 0; i < numEnemies; i++)
    {
      enemies[i].c = ALIEN_WIDTH + dC;
      enemies[i].r = 3 + dR;
      enemies[i].image = (COLOR *) alien;
      enemies[i].health = 1;
      if (dC + 4 * ALIEN_WIDTH > SCREEN_WIDTH)
        {
          dR += ALIEN_HEIGHT + 4;
          dC = dR;
        }
      else
        {
          dC += ALIEN_WIDTH + 4;
        }
    }

  drawGame(enemies);
  volatile int counter = 0;
  int rD = 0;
  int cD = 5;
  while (1)
    {
      if (KEY_DOWN_NOW(KEY_START))
        {
          KEY_RELEASED_WAIT(KEY_START);
          pauseGame();
          drawGame(enemies);
        }
      //Move aliens!
      if (!(counter % 50000))
        {
          if(enemies[numEnemies-1].c + ALIEN_WIDTH + cD >= SCREEN_WIDTH || enemies[0].c + cD <= 0){
            cD *= -1;
            rD = ALIEN_HEIGHT;
          }
          for (int i = 0; i < numEnemies; i++)
            {
              waitForVBlank();
              moveAlien(&enemies[i], rD, cD);
            }
          rD = 0;
        }
      //Move player
      if(!(counter % 10000))
        {
          if(KEY_DOWN_NOW(KEY_LEFT))
            {

            }
          else if(KEY_DOWN_NOW(KEY_RIGHT))
            {

            }
        }
      //Shoot
      if(!(counter % 20000))
        {
          if(KEY_DOWN_NOW(KEY_A))
            {

            }
        }
      //Check for player v alien collision or projectile v alien collision
      //TODO eliminate alien from array if dead
      counter++;
      if (needReset == 1 || resetCheck())
        return (0);
    }
  return (0);
}

void
drawGame(Alien * enemies)
{
  autoDraw(gameScreen);
  waitForVBlank();
  for (int i = 0; i < numEnemies; i++)
    {
      drawAlien(enemies[i]);
    }
}

void
pauseGame()
{
  waitForVBlank();
  drawImage3(40, 80, PAUSED_WIDTH, PAUSED_HEIGHT, paused);
  while (1)
    {
      if (KEY_DOWN_NOW(KEY_START))
        {
          KEY_RELEASED_WAIT(KEY_START);
          return;
        }
      if (resetCheck())
        return;
    }
}

int
resetCheck()
{
  if (KEY_DOWN_NOW(KEY_SELECT))
    {
      needReset = 1;
      return (1);
    }
  return (0);
}
