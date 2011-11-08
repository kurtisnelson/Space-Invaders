/*
 * spaceinvaders.c
 *
 *  Created on: Nov 7, 2011
 *      Author: kurt
 */
#include "spaceinvaders.h"
int
main()
{
  // Set the display mode properly
  REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
  while (1)
    {

      runGame();
    }
  return (0);
}

void
runGame()
{
  if(KEY_DOWN_NOW(1))
    return;
}
