#include <dataType.hpp>
#include <asm.h>

static void frequency_set(uint8_t counter_port, uint8_t counter_no, uint8_t rwl,
			  uint8_t counter_mode, uint16_t counter_value)
{
	outb(0x43, (uint8_t)(counter_no << 6 | rwl << 4 | counter_mode << 1));
	outb(counter_port, (uint8_t)counter_value);
	outb(counter_port, (uint8_t)(counter_value >> 8));
}

/**
 * 初始化PIT 8253.
 */
void timer_init()
{
	frequency_set(0x40, 0, 3, 2, 11930);
}

static int timestamp = 0;

void time_add()
{
	timestamp++;
}

int get_time()
{
	return timestamp;
}

void sleep(float time)
{
	int t0 = timestamp;
	while (timestamp - t0 < (int)(time * 100.F))
		hlt_asm();
}