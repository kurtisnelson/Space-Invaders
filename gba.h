#ifndef MYLIB_H
#define MYLIB_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef u16 COLOR;
#define REG_DISPCNT *(u16 *)0x04000000
#define RGB(r,g,b) ((r)|((g)<<5)|((b)<<10))
#define DCNT_MODE3 0x0003
#define DCNT_BG2 0x0400
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160
extern u16 *videoBuffer;
void setPixel(u32, u32, COLOR);
COLOR color(u8, u8, u8);
void drawRect(u32, u32, u32, u32, COLOR);
#endif
