/*
 * input.h
 *
 *  Created on: Nov 7, 2011
 *      Author: kurt
 */

#ifndef INPUT_H_
#define INPUT_H_
#define REG_KEYINPUT (*(REG *) 0x04000130)
#define REG_KEYCNT (*(REG *) 0x04000132)
#define KEY_DOWN_NOW(key) (~REG_KEYINPUT & (key))
#define KEY_RELEASED_WAIT(key) while(KEY_DOWN_NOW(key)){;}
//Define some keys
#define KEY_A (1)
#define KEY_B (1 << 1)
#define KEY_SELECT (1 << 2)
#define KEY_START (1 << 3)
#define KEY_RIGHT (1 << 4)
#define KEY_LEFT (1 << 5)
#define KEY_UP (1 << 6)
#define KEY_DOWN (1 << 7)
#define KEY_R (1 << 8)
#define KEY_L (1 << 9)



#endif /* INPUT_H_ */
