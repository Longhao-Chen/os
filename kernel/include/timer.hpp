#ifndef _TIMER_HPP
#define _TIMER_HPP

void timer_init();
// 时间戳+1
void time_add();

// 获取时间
// 时钟频率100Hz
int get_time();

// 单位为秒
void sleep(float time);

#endif