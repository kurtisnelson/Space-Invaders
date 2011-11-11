/*
 * video.c
 *
 *  Created on: Nov 7, 2011
 *      Author: kurt
 */
#include "video.h"
#include "dma.h"
#include "gba.h"

u16 *videoBuffer = (u16 *) 0x06000000;

void
vMode3()
{
  REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
}

void
setPixel(u32 r, u32 c, COLOR color)
{
  videoBuffer[(r * SCREEN_WIDTH) + c] = color;
}

void
waitForVBlank()
{
  while (REG_VCOUNT >= 160)
    ; // wait till VDraw
  while (REG_VCOUNT < 160)
    ; // wait till VBlank
}

void
drawImage3(int r, int c, int width, int height, const u16* image)
{
  if(width == SCREEN_WIDTH && height == SCREEN_HEIGHT)
    {
      REG_DMA3SAD = (u32) image;
      REG_DMA3DAD = (u32) videoBuffer;
      REG_DMA3CNT = 0;
      REG_DMA3CNT |= SCREEN_WIDTH*SCREEN_HEIGHT | DMA_ENABLE | DMA_16;
    }
  else
    {
  int row = 0;
  while (row < height)
    {
      REG_DMA3SAD = (u32) image;
      REG_DMA3DAD = (u32) (videoBuffer + ((r + row) * SCREEN_WIDTH) + c);
      REG_DMA3CNT = 0;
      REG_DMA3CNT |= width | DMA_ENABLE | DMA_16;
      image += width;
      row++;
    }
    }
}

void
drawRect(u32 r, u32 c, u32 width, u32 height, COLOR color)
{
  if(width == SCREEN_WIDTH && height == SCREEN_HEIGHT)
    {
      REG_DMA3SAD = (u32) &color;
      REG_DMA3DAD = (u32) videoBuffer;
      REG_DMA3CNT = 0;
      REG_DMA3CNT |= SCREEN_WIDTH*SCREEN_HEIGHT | DMA_ENABLE | DMA_16 | DMA_SRC_FIXED;
    }
  else
    {
  int row = 0;
  while (row < height)
    {
      REG_DMA3SAD = (u32) &color;
      REG_DMA3DAD = (u32) (videoBuffer + ((r + row) * SCREEN_WIDTH) + c);
      REG_DMA3CNT = 0;
      REG_DMA3CNT |= width | DMA_ENABLE | DMA_16 | DMA_SRC_FIXED;
      row++;
    }
    }
}

void
autoDraw(const u16 * screen)
{
  REG_DMA3SAD = (u32) screen;
  REG_DMA3DAD = (u32) videoBuffer;
  REG_DMA3CNT = 0;
  REG_DMA3CNT |= SCREEN_WIDTH * SCREEN_HEIGHT | DMA_ENABLE | DMA_16;
}
