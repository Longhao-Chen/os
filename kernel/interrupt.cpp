#include <interrupt.hpp>
#include <asm.h>
#include <timer.hpp>
#include <keyboard.hpp>

const uint8_t IDT_DESC_CNT = 0x30;
const uint8_t PIC_M_CTRL = 0x20;
const uint8_t PIC_M_DATA = 0x21;
const uint8_t PIC_S_CTRL = 0xa0;
const uint8_t PIC_S_DATA = 0xa1;

struct gate_desc {
	uint16_t func_offset_low_word;
	uint16_t selector;
	uint8_t dcount;

	uint8_t attribute;
	uint16_t func_offset_high_word;
};

// 中断的名称.
char *intr_name[IDT_DESC_CNT];
intr_handler idt_table[IDT_DESC_CNT];
static void make_idt_desc(struct gate_desc *p_gdesc, uint8_t attr,
			  intr_handler function);
static struct gate_desc idt[IDT_DESC_CNT];

extern intr_handler intr_entry_table[IDT_DESC_CNT];

// 通用的中断处理函数.
static void general_intr_handler(uint8_t vec_nr)
{
	if (vec_nr == 0x27 || vec_nr == 0x2f) {
		// 伪中断，无需处理
		return;
	}
	switch (vec_nr)
	{
	case 0x20:
		time_add();
		break;
	case 0x21:
		// 键盘中断
		intr_keyboard();
		break;
	}
}

// 通用(默认)的异常/中断处理器注册.
static void exception_handler_init(void)
{
	int i;
	for (i = 0; i < IDT_DESC_CNT; i++) {
		idt_table[i] = (void *)general_intr_handler;
		intr_name[i] = (char *)"unknown";
	}
}

// 创建中断门描述符.
static void make_idt_desc(struct gate_desc *p_gdesc, uint8_t attr,
			  intr_handler function)
{
	p_gdesc->func_offset_low_word = (uint32_t)function & 0x0000FFFF;
	p_gdesc->selector = SELECTOR_K_CODE;
	p_gdesc->dcount = 0;
	p_gdesc->attribute = attr;
	p_gdesc->func_offset_high_word = ((uint32_t)function & 0xFFFF0000) >>
					 16;
}

// 初始化中断描述符表.
static void idt_desc_init(void)
{
	int i;
	for (i = 0; i < IDT_DESC_CNT; i++) {
		make_idt_desc(&idt[i], IDT_DESC_ATTR_DPL0, intr_entry_table[i]);
	}
}

static void pic_init(void)
{
	// 初始化主片
	outb(PIC_M_CTRL, 0x11);
	// 0x20 中断开始
	outb(PIC_M_DATA, 0x20);

	outb(PIC_M_DATA, 0x04);
	outb(PIC_M_DATA, 0x01);

	outb(PIC_S_CTRL, 0x11);
	outb(PIC_S_DATA, 0x28);

	outb(PIC_S_DATA, 0x02);
	outb(PIC_S_DATA, 0x01);

	// 中断屏蔽寄存器，只打开 时钟和键盘
	outb(PIC_M_DATA, 0xfc);
	outb(PIC_S_DATA, 0xff);
}

void idt_init()
{
	idt_desc_init();
	exception_handler_init();
	pic_init();

	// 加载idt
	uint64_t idt_operand =
		((sizeof(idt) - 1) | ((uint64_t)((uint32_t)idt << 16)));
	asm volatile("lidt %0" : : "m"(idt_operand));
}