/*
 * dma.h
 *
 *  Created on: Nov 7, 2011
 *      Author: kurt
 */

#ifndef DMA_H_
#define DMA_H_
#define DMA_TRANSFER(_dst, _src, _count, _ch, _mode)  \
    REG_DMA##_ch##SAD = (u32)(_src),                  \
    REG_DMA##_ch##DAD = (u32)(_dst),                  \
    REG_DMA##_ch##CNT = (_count) | (_mode)            \

#define REG_DMA3SAD (*(REG *) 0x40000D4)
#define REG_DMA3DAD (*(REG *) 0x40000D8)
#define REG_DMA3CNT (*(REG *) 0x40000DC)
#define DMA_REPEAT (1 << 0x19)
#define DMA_16 (0 << 0x1A)
#define DMA_32 (1 << 0x1A)
#define DMA_VBLANK (1 << 0x1C)
#define DMA_ENABLE (1 << 0x1F)
#define DMA_DST_RELOAD (3 << 0x15)
#define DMA_SRC_FIXED (2 << 0x17)
void zeroMem(void *, short);
#endif /* DMA_H_ */
