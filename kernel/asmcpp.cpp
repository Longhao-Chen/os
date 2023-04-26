#include <asm.h>
#include <dataType.hpp>

void put_color(char color, int addr)
{
	if (addr >= 0 && addr < 320 * 200)
		put_color_asm(color, addr);
}

void put_color(char color, int x, int y)
{
	if (x >= 0 && x < 320 && y >= 0 && y < 200)
		put_color(color, x + y * 320);
}

char get_color(int addr)
{
	if (addr >= 0 && addr < 320 * 200)
		return get_color_asm(addr);
	else
		return bg_color;
}

char get_color(int x, int y)
{
	if (x >= 0 && x < 320 && y >= 0 && y < 200)
		return get_color(x + y * 320);
    return bg_color;
}

/**
 *  向指定的端口写入一个字节的数据.
 */ 
void outb(uint16_t port, uint8_t data) {
    asm volatile ("outb %b0, %w1" : : "a" (data), "Nd" (port));   
}

/**
 * 将addr起始处的word_cnt个字节写入端口port.
 */ 
void outsw(uint16_t port, const void* addr, uint32_t word_cnt) {
    asm volatile ("cld; rep outsw" : "+S" (addr), "+c" (word_cnt) : "d" (port));
}

/**
 * 将从端口port读入的一个字节返回.
 */ 
uint8_t inb(uint16_t port) {
    uint8_t data;
    asm volatile ("inb %w1, %b0" : "=a" (data) : "Nd" (port));
    return data;
}

/**
 * 将从port读取的word_cnt字节写入addr.
 */ 
void insw(uint16_t port, void* addr, uint32_t word_cnt) {
    asm volatile ("cld; rep insw" : "+D" (addr), "+c" (word_cnt) : "d" (port) : "memory");
}