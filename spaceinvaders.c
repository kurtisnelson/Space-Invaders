/*
 * spaceinvaders.c
 *
 *  Created on: Nov 7, 2011
 *      Author: kurt
 */
//#include <stdlib.h>
#include "spaceinvaders.h"
#include "alien.h"
#include "player.h"
#include "bullet.h"
#include "images/player.h"
#include "images/alien.h"
#include "images/bullet.h"
#include "images/title.h"
#include "images/paused.h"
#include "images/gameover.h"
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
  int lives = 2;
  while (1)
    {
      int levelResult = startLevel(level);
      if (levelResult == 0)
        {
          lives--;
          deathFlash();
          if (lives <= 0)
            endGame();
        }
      else if (levelResult == -1)
        {
          if (needReset == 1)
                  return;
          endGame();
        }
      else
        {
          level = levelResult;
        }
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
  else if (level == 2)
    numEnemies = 15;
  else
    numEnemies = 21;
  int aliveEnemies = numEnemies;

  //Setup player
  Player player;
  player.c = (SCREEN_WIDTH - PLAYER_WIDTH) / 2;
  player.r = 140;
  player.health = 1;
  player.image = (COLOR *) playerImg;

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
  //Track bullets
  Bullet bullets[MAX_BULLETS];
  for (int i = 0; i < MAX_BULLETS; i++)
    {
      bullets[i].health = 0;
      bullets[i].image = 0;
    }
  waitForVBlank();
  drawGame(enemies, player, bullets);
  volatile int counter = 0;
  int bulletTimer = 0;
  //Starting Alien movement
  int rD = 0;
  int cD = 4;
  //MAIN GAME LOOP
  while (1)
    {
      if (KEY_DOWN_NOW(KEY_START))
        {
          KEY_RELEASED_WAIT(KEY_START);
          pauseGame();
          drawGame(enemies, player, bullets);
        }

      //Move aliens
      waitForVBlank();
      if (!(counter % 3000))
        {
          for (int i = 0; i < numEnemies; i++)
            {
              if (enemies[i].health > 0
                  && (enemies[i].c + ALIEN_WIDTH + cD >= SCREEN_WIDTH
                      || enemies[i].c + cD <= 0))
                {
                  cD *= -1;
                  rD = ALIEN_HEIGHT;
                }
            }
          for (int i = 0; i < numEnemies; i++)
            {
              moveAlien(&enemies[i], rD, cD);
            }
          rD = 0;
        }

      //Move bullets
      waitForVBlank();
      if (!(counter % 400))
        {
          for (int i = 0; i < MAX_BULLETS; i++)
            {
              moveBullet(&bullets[i]);
            }
        }

      //Move player
      if (!(counter % 250))
        {
          if (KEY_DOWN_NOW(KEY_LEFT))
            {
              movePlayer(&player, 0, -2);
            }
          else if (KEY_DOWN_NOW(KEY_RIGHT))
            {
              movePlayer(&player, 0, 2);
            }
        }

      //Possible alien shoot
      if (!(counter % 15000))
        {
          if (1)
            {
              //SHOOT
              for (int i = numEnemies; i >= 0; i--)
                {
                  if (enemies[i].health > 0)
                    {
                      for (int j = 0; j < MAX_BULLETS; j++)
                        {
                          if (bullets[j].health <= 0)
                            {
                              bullets[j].c = enemies[j].c + (ALIEN_WIDTH / 2);
                              bullets[j].r = enemies[j].r + ALIEN_HEIGHT + 1;
                              bullets[j].dR = 2;
                              bullets[j].dC = 0;
                              bullets[j].health = 1;
                              bullets[j].image = (COLOR *) bulletImg;
                              drawBullet(bullets[j]);
                              break;
                            }
                        }
                      break;
                    }
                }
            }
        }

      //Player shoot
      if (bulletTimer <= 0 && !(counter % 300))
        {
          if (KEY_DOWN_NOW(KEY_A))
            {
              bulletTimer = 5000;
              for (int i = 0; i < MAX_BULLETS; i++)
                {
                  if (bullets[i].health == 0)
                    {
                      bullets[i].c = player.c + (PLAYER_WIDTH / 2);
                      bullets[i].r = player.r - BULLET_HEIGHT;
                      bullets[i].dR = -2;
                      bullets[i].dC = 0;
                      bullets[i].health = 1;
                      bullets[i].image = (COLOR *) bulletImg;
                      drawBullet(bullets[i]);
                      break;
                    }
                }
            }
        }
      else
        {
          if (bulletTimer > 0)
            bulletTimer--;
        }

      //Check for player v alien collision or projectile v alien collision
      if (!(counter % 125))
        {
          for (int i = 0; i < numEnemies; i++)
            {
              if (enemies[i].health > 0)
                {
                  //First check if alien hit player.
                  if (checkCollide(enemies[i].r + ALIEN_HEIGHT, enemies[i].c,
                      enemies[i].c + ALIEN_WIDTH, player.r, player.c,
                      player.c + PLAYER_WIDTH))
                    {
                      hitPlayer(&player);
                    }
                  //Check if bullet hits.
                  for (int j = 0; j < MAX_BULLETS; j++)
                    {
                      if (bullets[j].health > 0)
                        {
                              if (checkCollide(enemies[i].r + ALIEN_HEIGHT,
                                  enemies[i].c, enemies[i].c + ALIEN_WIDTH,
                                  bullets[j].r, bullets[j].c,
                                  bullets[j].c + BULLET_WIDTH))
                                {
                                  //Both the bullet and the enemy should lose health
                                  hitBullet(&bullets[j]);
                                  hitAlien(&enemies[i]);
                                  if (enemies[i].health == 0)
                                    aliveEnemies--;
                                }
                        }
                    }
                }
            } //End enemies check
        }
      //Check if bullet hit player
      if (!(counter % 200))
        {
          for (int j = 0; j < MAX_BULLETS; j++)
            {
              if (bullets[j].health > 0)
                {
                  //checkCollision has some strange bug, so I'm not using it.
                  if(bullets[j].r + BULLET_HEIGHT > player.r && bullets[j].c >= player.c && bullets[j].c <= player.c + PLAYER_WIDTH)
                    {
                      //The player and the bullet should lose health
                      hitPlayer(&player);
                      hitBullet(&bullets[j]);
                    }
                }
            }
        }
      //End level conditions:
      if (aliveEnemies <= 0)
        return (level + 1);
      if (player.health <= 0)
        return (0);
      counter++;
      if (needReset == 1 || resetCheck())
        return (-1);
    }
  //END MAIN GAME LOOP
  return (-1);
}

void
drawGame(Alien * enemies, Player player, Bullet * bullets)
{
  waitForVBlank();
  autoDraw(gameScreen);
  for (int i = 0; i < numEnemies; i++)
    {
      drawAlien(enemies[i]);
    }
  drawPlayer(player);
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

void
endGame()
{
  waitForVBlank();
  drawImage3(0, 0, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, gameover);
  while (1)
    {
      if (resetCheck())
        return;
    }
}

//Has a bug, no idea what.
int
checkCollide(int downBottom, int downLeft, int downRight, int upTop, int upLeft,
    int upRight)
{
  if (downBottom >= upTop)
    {
      if (downLeft <= upLeft && downRight >= upLeft)
          return (1);
      if (downRight >= upRight && downLeft <= upRight)
          return (1);
    }
  return (0);
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

void
deathFlash()
{
  waitForVBlank();
  drawRect(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, RED);
  delay(1);
}

void
delay(int i)
{
  volatile int waste = 0;
  while(waste < i*100000)
    waste++;
  return;
}
