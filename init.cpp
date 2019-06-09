//初始化函数 Init(): 初始化任务的具体信息

#include "pch.h"
#include "player.h"
#include <graphics.h>
#include <conio.h>
#include <time.h>

// 初始化函数
//参数:
//	1.每行方块中白块的位置
//  2.最初开始的任务
//	3.玩家初始状态
//  4.失败后参数
void PLAYER::Init()
{
	// 初始化任务，每行白块位置随机生成在【0，3】之间
	for (int i = 0; i < MAXTASK; i++)
		m_Task[i] = rand() % 4; 

	m_iTask = 0;				// 从第一个任务开始
	m_nextTaskY = 200;			// 设定下一行任务的 Y 坐标，200表示开始会有下落的动画
	m_status = BEGIN;			// 设置游戏初始状态
	m_failFrame = 0;			// 重置失败后的动画的帧计数

	// 初始化游戏界面
	DrawFrame();
}