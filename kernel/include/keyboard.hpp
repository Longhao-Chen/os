#ifndef _KEYBOARD_HPP
#define _KEYBOARD_HPP
// 键盘中断处理
void intr_keyboard();
// 设置按键函数
void setKeyFun(int index, void (*fun)());
#endif