//延时函数 HpSleep(int ms) 函数主体
//延时的作用： 使方块下降的速度变慢

#include "pch.h"
#include "player.h"
#include <time.h>

// 精确延时函数(可以精确到 1ms，精度 ±1ms)
void HpSleep(int ms)
{
	static clock_t oldclock = clock();		// 静态变量，记录上一次 tick
											//获取时间
	oldclock += ms * CLOCKS_PER_SEC / 1000;	// 更新 tick
	if (clock() > oldclock)					// 如果已经超时，无需延时
		oldclock = clock();
	else
		while (clock() < oldclock)			// 延时
			Sleep(1);						// 释放 CPU 控制权，降低 CPU 占用率 
}