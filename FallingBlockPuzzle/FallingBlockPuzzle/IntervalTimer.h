//======================================
//      インターバルタイマー
//======================================
#ifndef __INTERVAL_TIMER_H
#define __INTERVAL_TIMER_H
#include <time.h>  // clock_t, clock()

typedef struct {
	clock_t interval;
	clock_t nextClock;
} IntervalTimer;

// タイマースタート
void StartTimer(IntervalTimer* timer, int fps);
// インターバル経過した?
bool IsInterval(IntervalTimer* timer);

#endif // __INTERVAL_TIMER_H