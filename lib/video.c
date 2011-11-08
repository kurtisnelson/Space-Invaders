/*
 * video.c
 *
 *  Created on: Nov 7, 2011
 *      Author: kurt
 */
#include "color.h"
#include "video.h"
#include "dma.h"
u16 *videoBuffer = (u16 *) 0x06000000;

void
setPixel(u32 r, u32 c, COLOR color)
{
  videoBuffer[(r * SCREEN_WIDTH) + c] = color;
}

void
drawRect(u32 r, u32 c, u32 width, u32 height, COLOR color)
{
  for (int i = c; i < c + width; i++)
    {
      for (int j = r; j < r + height; j++)
        {
          setPixel(j, i, color);
        }
    }
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
  REG_DMA3SAD = (u32) image;
  REG_DMA3DAD = (u32) videoBuffer + (r*SCREEN_WIDTH+c);
  REG_DMA3CNT = width;
  REG_DMA3CNT |= DMA_ENABLE | DMA_16 | DMA_DST_RELOAD;
}

void autodraw(const u16 * screen)
{
  REG_DMA3SAD = (u32) screen;
  REG_DMA3DAD = (u32) videoBuffer;
  REG_DMA3CNT = SCREEN_WIDTH*SCREEN_HEIGHT;
  REG_DMA3CNT |= DMA_ENABLE | DMA_16 | DMA_VBLANK | DMA_DST_RELOAD;
}
