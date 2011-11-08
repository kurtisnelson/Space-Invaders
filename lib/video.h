/*
 * video.h
 *
 *  Created on: Nov 7, 2011
 *      Author: kurt
 */

#ifndef VIDEO_H_
#define VIDEO_H_
#include "gba.h"
#include "color.h"
#define REG_VCOUNT (*(REG *)0x04000006)
#define REG_DISPCNT (*(REG *)0x04000000)
#define DCNT_MODE3 0x0003
#define DCNT_BG2 0x0400
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160
extern u16 *videoBuffer;
void setPixel(u32, u32, COLOR);
COLOR color(u8, u8, u8);
void drawRect(u32, u32, u32, u32, COLOR);
void waitForVBlank();
void drawImage3(int, int, int, int, const u16*);
void autoDraw(const u16*);
void vMode3();
#endif /* VIDEO_H_ */
