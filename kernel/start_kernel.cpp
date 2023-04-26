#include <asm.h>
#include <interrupt.hpp>
#include <timer.hpp>
#include <tetris.hpp>

extern "C" {
void start_kernel();
}

void start_kernel()
{
	idt_init();
	timer_init();
	asm volatile("sti"); // 开中断
	while (true)
		TetrisSpace::runTetris();
}