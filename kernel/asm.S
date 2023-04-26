; 内核颜色打印功能实现
TI_GDT equ 0
RPL0 equ 0
SELECTOR_VIDEO equ (0x0003 << 3) + TI_GDT + RPL0

[bits 32]
section .text
global put_color_asm
global get_color_asm
global hlt_asm
global outb

put_color_asm:
    pushad
    mov ebx, [esp + 40]
    mov ecx, [esp + 36]
    mov ax, SELECTOR_VIDEO
    mov gs, ax

    mov [gs:ebx], cl

    popad
    ret

get_color_asm:
    mov ecx, [esp + 4]
    mov ax, SELECTOR_VIDEO
    mov gs, ax

    mov eax, [gs:ecx]
    ret

hlt_asm:
    hlt
    ret

; ----------------- 中断处理方面 ---------------------------------

; 对于CPU会自动压入错误码的中断类型，无需额外的操作
%define ERROR_CODE nop
; 如果CPU没有压入错误码，为了保持处理逻辑的一致性，手动压入一个0
%define ZERO push 0

; 中断处理函数数组
extern idt_table

section .data
global intr_entry_table
intr_entry_table:

; 中断处理程序宏定义
%macro VECTOR 2
section .text
intr%1entry:
    %2
    cli
    ; 保存上下文
    push ds
    push es
    push fs
    push gs
    pushad

    mov al, 0x20
    out 0xa0, al
    out 0x20, al

    push %1

    ; 调用C的中断处理函数
    call [idt_table + 4 * %1]
    jmp intr_exit

section .data
    dd intr%1entry

%endmacro

section .text
global intr_exit
intr_exit:
    add esp, 4
    popad
    pop gs
    pop fs
    pop es
    pop ds
    add esp, 4
    sti
    iretd

VECTOR 0x00, ZERO
VECTOR 0x01, ZERO
VECTOR 0x02, ZERO
VECTOR 0x03, ZERO
VECTOR 0x04, ZERO
VECTOR 0x05, ZERO
VECTOR 0x06, ZERO
VECTOR 0x07, ZERO
VECTOR 0x08, ZERO
VECTOR 0x09, ZERO
VECTOR 0x0a, ZERO
VECTOR 0x0b, ZERO
VECTOR 0x0c, ZERO
VECTOR 0x0d, ZERO
VECTOR 0x0e, ZERO
VECTOR 0x0f, ZERO
VECTOR 0x10, ZERO
VECTOR 0x11, ZERO
VECTOR 0x12, ZERO
VECTOR 0x13, ZERO
VECTOR 0x14, ZERO
VECTOR 0x15, ZERO
VECTOR 0x16, ZERO
VECTOR 0x17, ZERO
VECTOR 0x18, ZERO
VECTOR 0x19, ZERO
VECTOR 0x1a, ZERO
VECTOR 0x1b, ZERO
VECTOR 0x1c, ZERO
VECTOR 0x1d, ZERO
VECTOR 0x1e, ERROR_CODE
VECTOR 0x1f, ZERO
VECTOR 0x20, ZERO   ; 时钟
VECTOR 0x21, ZERO   ; 键盘
VECTOR 0x22, ZERO
VECTOR 0x23, ZERO
VECTOR 0x24, ZERO
VECTOR 0x25, ZERO
VECTOR 0x26, ZERO
VECTOR 0x27, ZERO
VECTOR 0x28, ZERO
VECTOR 0x29, ZERO
VECTOR 0x2a, ZERO
VECTOR 0x2b, ZERO
VECTOR 0x2c, ZERO
VECTOR 0x2d, ZERO
VECTOR 0x2e, ZERO
VECTOR 0x2f, ZERO