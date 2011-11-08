/*
 * spaceinvaders.c
 *
 *  Created on: Nov 7, 2011
 *      Author: kurt
 */
#include "spaceinvaders.h"
#include "images/title.h"
#include "images/paused.h"
#include "lib/dma.h"
#include "lib/gba.h"
#include "lib/video.h"
#include "lib/input.h"

u32 needReset;
const COLOR gameScreen[38400] = {0};

int
main()
{
  // Set the display mode properly
  vMode3();
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
  autoDraw(title);
  zeroMem((void *)gameScreen, (short)38400);
  needReset = 0;
}

void
runGame()
{

  while (1)
    {
      if (KEY_DOWN_NOW(KEY_START)){
        KEY_RELEASED_WAIT(KEY_START);
        pauseGame();
      }
      if(needReset == 1 || resetCheck())
        return;
      waitForVBlank();
      autoDraw((u16 *)gameScreen);
    }
}

void
pauseGame()
{
  waitForVBlank();
  drawImage3(40, 80, PAUSED_WIDTH, PAUSED_HEIGHT, paused);
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
