/*
 * dma.c
 *
 *  Created on: Nov 8, 2011
 *      Author: kurt
 */
#include "gba.h"
#include "dma.h"

void
zeroMem(void * addr, short count){
  int zero = 0;
  REG_DMA3SAD = (u32) &zero;
  REG_DMA3DAD = (u32) addr;
  REG_DMA3CNT = 0;
  REG_DMA3CNT |= count | DMA_ENABLE | DMA_32 | DMA_SRC_FIXED;
}

