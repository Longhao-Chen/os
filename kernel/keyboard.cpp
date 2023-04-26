#include <keyboard.hpp>
#include <asm.h>
#include <dataType.hpp>

// up down left right L R
static void (*keyboard_fun[6])();
static bool e0 = false; //是否接收到e0

void intr_keyboard()
{
	uint8_t scanCode = inb(0x60);
	if (scanCode == 0xe0) {
		e0 = true;
		return;
	} else if (scanCode == 0x26)
		keyboard_fun[4]();
	else if (scanCode == 0x13)
		keyboard_fun[5]();
	else if (e0)
		if (scanCode == 0x48)
			keyboard_fun[0]();
		else if (scanCode == 0x50)
			keyboard_fun[1]();
		else if (scanCode == 0x4b)
			keyboard_fun[2]();
		else if (scanCode == 0x4d)
			keyboard_fun[3]();
	e0 = false;
}

void setKeyFun(int index, void (*fun)())
{
	keyboard_fun[index] = fun;
}