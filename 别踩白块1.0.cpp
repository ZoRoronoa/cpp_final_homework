// 主函数，程序入口

#include "pch.h"
#include "player.h"
#include <graphics.h>
#include <conio.h>
#include <cstdio>
#include <time.h>
#include <stdlib.h>
//玩家昵称输入;
void InputName(char p1[], char p2[]);

int main()
{
	initgraph(640, 580);
	srand((unsigned)time(NULL));			// 设置随机函数种子

	setbkcolor(0x55FF55);
	cleardevice();//清理屏幕内容
	char player1name[13];
	char player2name[13];
	InputName(player1name, player2name);

	PLAYER p1(player1name, "asdf", 74, 8);		// 创建PLAYER1
	PLAYER p2(player2name, "jkl;", 322, 8);		// 创建PLAYER2
	char c = 0;

	while (c != 27)							// 按键"esc" 退出程序
	{
		while (_kbhit())					// 判断是否有按键
		{
			// 按键处理
			c = _getch();
			p1.Hit(c);
			p2.Hit(c);	
		}

		// 绘制游戏场景
		p1.Draw();
		p2.Draw();

		// 延时
		HpSleep(4);
	}

	// 结束游戏
	closegraph();							// 关闭绘图窗口
	return 0;
}

void InputName(char p1[], char p2[])
{
	setlinecolor(0xfb9700);
	loadimage(NULL, "test.jpg");
	InputBox(p1, 13, "输入玩家一昵称:");
	InputBox(p2, 13, "输入玩家二昵称:");
	clearrectangle(0, 0, 640, 580);			//清屏，背景图不再显示
}