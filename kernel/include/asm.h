#ifndef _ASM_H
#define _ASM_H
#include <dataType.hpp>

const char bg_color = 0;
/*
0x1: 蓝色
0x2: 绿色
0x3: 青色
0x4: 红色
0x5: 粉色
0x6: 橘黄色
0x7: 灰色
0x9: 蓝偏青
*/
void put_color(char color, int addr);
void put_color(char color, int x, int y);
char get_color(int addr);
char get_color(int x, int y);

/**
 *  向指定的端口写入一个字节的数据.
 */ 
void outb(uint16_t port, uint8_t data);

/**
 * 将addr起始处的word_cnt个字节写入端口port.
 */ 
void outsw(uint16_t port, const void* addr, uint32_t word_cnt);

/**
 * 将从端口port读入的一个字节返回.
 */ 
uint8_t inb(uint16_t port);

/**
 * 将从port读取的word_cnt字节写入addr.
 */ 
void insw(uint16_t port, void* addr, uint32_t word_cnt);

extern "C" {
// 向int的位置写入颜色char
extern void put_color_asm(char, int);
// 读取int位置处的颜色
extern char get_color_asm(int);
// hlt指令
extern void hlt_asm(void);
}
#endif