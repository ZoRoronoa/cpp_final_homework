//player类的定义

#pragma once
#include "pch.h"
#include <graphics.h>
#include <conio.h>
#include <cstdio>
#include <time.h>
#undef UNICODE
#undef _UNICODE //防止中文字符出现问题

const int MAXTASK = 50; // 定义游戏需要完成的黑块数量，这里设置的是100个

//延时函数声明
void HpSleep(int ms);

// 游戏状态常量声明
enum STATUS {
	BEGIN,			// 游戏开始
	RUNNING,		// 游戏运行中
	PASSANI,		// 游戏通过的动画
	PASS,			// 游戏通过
	FAILANI,		// 游戏失败的动画
	FAIL			// 游戏失败
};			

// 游戏者类（每个游戏者都有一个独立的游戏区域）
class PLAYER
{
private:
	STATUS	m_status;						// 游戏状态
	const char*	m_strName;					// 游戏者名称
	//TODO: POINT类是库里自带的类，可用于讲来的扩充.
	POINT	m_offset;						// 界面的偏移量，即每个游戏区域的左上角的位置
	const char*	m_keys;						// 预设需要点击的按键

	// 任务 (即每行黄色块的序号）
	//byte 类型 typedef unsigned char BYTE 类型别名（无符号char）
	byte	m_Task[MAXTASK];			// 任务列表  char 类型数组；
	byte	m_iTask;					// 当前需要执行的任务 ID | char 类型数组
	int		m_nextTaskY;				// 界面中下一个任务的 Y 坐标

	// 时钟和游戏记录， 获取时间
	clock_t	m_beginClock;				// 游戏开始的时钟计数， 注意typedef long clock_t
	float	m_bestTime;					// 最佳纪录的完成时间
	float	m_lastTime;					// 本次游戏的完成时间

	// 控制失败动画的变量
	byte	m_failErrorKey;				// 按错的键的序号（值为 0、1、2、3）
	//TODO： RECT是一个类，有利于程序的扩充。（UML图形等等）
	RECT	m_failRect;					// 按错的键的区域， RECT为一个类，绘制矩形
	int		m_failFrame;				// 失败后的动画的帧计数

public:
	PLAYER(const char* name, const char* keys, int offsetx, int offsety);		// 构造函数
	void Hit(char key);												// 处理游戏者按键
	void Draw();													// 绘制该游戏者的游戏界面
	void PlayMusic(int i);											//实现每次按键的音效
	void CloseMusic(int j);											//每次按键之前需要关闭上次开启的音效
	void PlayFailMusic();											//若按键错误，启动失败的音效
	void CloseFailMusic();											//关闭音效
private:
	void Init();													// 初始化当前游戏者的游戏信息
	void DrawFrame();												// 绘制游戏界面的外框
	void DrawRow(int baseY, int iTask);								// 绘制游戏界面中的一行任务
	void DrawPass();												// 绘制通过游戏后的界面
	void DrawFail();												// 绘制游戏失败后的界面
	void DrawRealTimeScore(int iTask);								// 绘制实时完成的方块数和尚未完成的方块数
	//其他基本绘制函数
	void OutTextXY(int x, int y, LPCTSTR s);						// 在指定位置输出字符串
	void OutTextXY(int x, int y, char c);							// 在指定位置输出字符
	void Rectangle(int x1, int y1, int x2, int y2);					// 绘制矩形
	void FillRectangle(int x1, int y1, int x2, int y2);				//绘制有边框填充矩形
	void SolidRectangle(int x1, int y1, int x2, int y2);			//绘制无边框填充矩形
};