//player的函数定义

#include "pch.h"
#include "player.h"
#include <graphics.h>
#include <conio.h>

// 构造函数
//	参数：
//		name: 游戏者名称
//		keys: 游戏者所用按键（指向长度为 4 的字符串）
//		offsetx, offsety: 游戏者对应的游戏区域在主窗口中的偏移量
PLAYER::PLAYER(const char* name, const char* keys, int offsetx, int offsety)
{
	m_strName = name;
	m_keys = keys;
	m_offset.x = offsetx;
	m_offset.y = offsety;

	m_bestTime = 99;	// 设置最佳成绩
	Init();				// 初始化游戏者，Init函数完成其他变量的初始化;
}