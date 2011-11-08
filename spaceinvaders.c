/*
 * spaceinvaders.c
 *
 *  Created on: Nov 7, 2011
 *      Author: kurt
 */
#include "spaceinvaders.h"
#include "images/title.h"
#include "images/paused.h"
u32 needReset;
int
main()
{
  // Set the display mode properly
  REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
  needReset = 1;
  while (1)
    {
      drawRect(0,0,10,10,GREEN);
      if (KEY_DOWN_NOW(KEY_START)){
        KEY_RELEASED_WAIT(KEY_START);
        runGame();
      }
      if(needReset){
          reset();
      }
    }
  return (0);
}

void
reset()
{
  autodraw(title);
  needReset = 0;
}

void
runGame()
{
  while (1)
    {
      drawRect(0,0,10,10,BLUE);
      if (KEY_DOWN_NOW(KEY_START)){
        KEY_RELEASED_WAIT(KEY_START);
        pauseGame();
      }
      if(needReset == 1 || resetCheck())
        return;
    }
}

void
pauseGame()
{
  drawImage3(20, 20, PAUSED_HEIGHT, PAUSED_WIDTH, paused);
  drawRect(0,0,10,10,RED);
  while (1)
    {
      if (KEY_DOWN_NOW(KEY_START)){
        KEY_RELEASED_WAIT(KEY_START);
        return;
      }
      if(resetCheck())
        return;
    }
}

int
resetCheck()
{
  if(KEY_DOWN_NOW(KEY_SELECT)){
      needReset = 1;
      return (1);
  }
  return (0);
}
