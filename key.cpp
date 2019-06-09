//按键函数 Hit(): 对按键实时处理，包括状态改变，音效实现等作用

#include "pch.h"
#include "player.h"
#include <graphics.h>
#include <conio.h>
#include <cstdio>

// 处理游戏者按键
void PLAYER::Hit(char key)
{
	switch (m_status)
	{
	case BEGIN:				// 游戏初次开始
		//m_keys 是初始设置的按键，分别是"asdf" and "jkl;" 判断是否按下的是指定的那几个按键，若否则无反应；
		if (strchr(m_keys, key) != NULL)
		{
			m_beginClock = clock();				// 记录游戏开始时的时钟
			m_status = RUNNING;					// 改变游戏状态
		}

	case RUNNING:			// 游戏运行中
	{
		//该函数返回在字符串 str 中第一次出现字符 c 的位置，如果未找到该字符则返回 NULL。
		const char* pdest = strchr(m_keys, key);
		byte pos;
		if (pdest != NULL)						// 判断是否是当前游戏者按键
		{
			pos = pdest - m_keys;				// 计算按键对应的位置
			if (pos == m_Task[m_iTask])			// 判断按键是否正确
			{
				//音效函数处理
				if (m_iTask == 0)
				{
					PlayMusic(pos);	
					//第一行直接播放按键音效
				}
				else if (m_iTask < MAXTASK)
				{
					CloseMusic(m_Task[m_iTask - 1]);
					PlayMusic(pos);
					//其他行先关闭上一次开启的音效，再开启按键音效
				}

				// 按键正确
				m_iTask++;   //任务向上
				m_nextTaskY += 100;

				if (m_iTask == MAXTASK)			// 任务全部完成
				{
					// 计算完成时间
					clock_t t = clock();
					// 计算执行时间
					m_lastTime = ((float)(clock() - m_beginClock)) / CLOCKS_PER_SEC;

					// 更新最好记录
					if (m_lastTime < m_bestTime)
						m_bestTime = m_lastTime;
					// 将最后一条任务滚动出屏幕
					m_iTask++;
					m_nextTaskY += 100;
					m_status = PASSANI;
				}
			}
			else
			{
				// 按键失败
				m_failErrorKey = pos;
				if (m_iTask != 0)
					CloseMusic(m_Task[m_iTask - 1]); //非首行出错，先关闭上行正确的音效，再播放失败提示音;
				PlayFailMusic();					//再播放失败提示音;
				m_status = FAILANI;
			}
		}

		break;
	}

	case PASSANI:			// 游戏成功后的动画
	case FAILANI:			// 游戏失败后的动画
		break;

	case PASS:				// 游戏通过后的成绩显示
	case FAIL:				// 游戏失败后的成绩显示
		if (strchr(m_keys, key) != NULL)
			Init();
		//实现“按任意键重新开始”功能
		break;
	}
}
