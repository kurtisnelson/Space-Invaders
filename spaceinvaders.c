/*
 * spaceinvaders.c
 *
 *  Created on: Nov 7, 2011
 *      Author: kurt
 */
#include "gba.c"
int main()
{
		// Set the display mode properly
        REG_DISPCNT= DCNT_MODE3 | DCNT_BG2;
        setPixel(100, 100, RED);
        while(1){

        }
        return 0;
}
