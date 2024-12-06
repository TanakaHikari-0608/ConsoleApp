//======================================
//      インターバルタイマー
//======================================
#include "IntervalTimer.h"
#include <time.h>  // clock()

// タイマースタート
void StartTimer(IntervalTimer* timer, int fps)
{
	timer->interval = 1000 / fps;
	timer->nextClock = clock() + timer->interval;
}
// インターバル経過したか?
bool IsInterval(IntervalTimer* timer)
{
	clock_t nowClock = clock();
	if (nowClock >= timer->nextClock) {
		timer->nextClock = nowClock + timer->interval;
		return true;
	}
	return false;
}