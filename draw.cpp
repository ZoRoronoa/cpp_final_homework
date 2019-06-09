#include "pch.h"
#include "player.h"
#include <graphics.h>
#include <conio.h>
#include <time.h>

//���ƺ������ϣ�
//1.ÿ��ͼ�λ��ƶ��壻
//2.����ʧ�ܻ�����ƶ��壻
//3.������ɻ�����ƶ��壻
//4.ʵʱ�ɼ�������ƶ��壻
//5.���������������
// ���Ƹ���Ϸ�ߵ���Ϸ����
void PLAYER::Draw()
{
	switch (m_status)
	{
	case PASSANI:			// ��Ϸ�ɹ���Ķ���
		if (m_nextTaskY == 100)
		{
			m_status = PASS;
			DrawPass();
			break;
		}

	case BEGIN:				// ��Ϸ���ο�ʼ
	case RUNNING:			// ��Ϸ������
	{
		// ������洦�ھ�ֹ��ֱ�ӷ��ز����ػ�
		if (m_nextTaskY == 100)
			return;

		m_nextTaskY -= (m_nextTaskY - 100 + 9) / 10;
		DrawRealTimeScore(m_iTask);
		// ������ɵ�������
		int rowy = m_nextTaskY;
		int itask = m_iTask;
		do
		{
			rowy -= 100;
			itask--;
			DrawRow(rowy, itask);//����ÿ�еķ���

		} while (rowy > 0);

		// ����δ��ɵ�������
		rowy = m_nextTaskY;
		itask = m_iTask;
		do
		{
			DrawRow(rowy, itask);
			rowy += 100;
			itask++;
		} while (rowy < 400);

		break;
	}

	case FAILANI:			// ��Ϸʧ�ܺ�Ķ���
		DrawFail();
		break;

	case PASS:				// ��Ϸͨ����ĳɼ���ʾ
	case FAIL:				// ��Ϸʧ�ܺ�ĳɼ���ʾ
		break;
	}
}

// ������Ϸ��������
void PLAYER::DrawFrame()
{
	// �����
	setlinecolor(0xfb9700);
	Rectangle(0, 0, 243, 564);
	setfillcolor(0xeca549); 
	settextcolor(BLACK);
	settextstyle(16, 0, "Verdana");
	setbkmode(0xFF5555);

	// ��������
	SolidRectangle(2, 2, 241, 21);
	int w = textwidth(m_strName);
	OutTextXY((244 - w) / 2, 4, m_strName);

	// ���ɼ���
	SolidRectangle(2, 23, 241, 42);
	char tmp[50];
	sprintf_s(tmp, "��ü�¼�� %.3f ��", m_bestTime);
	
	OutTextXY(10, 26, tmp);
	// 2 <= x <= 241, 44 <= y <= 443 Ϊ��Ϸ��

	// ��������
	SolidRectangle(2, 445, 241, 462);
	for (int i = 0; i < 4; i++)
		OutTextXY(2 + i * 60 + 26, 446, m_keys[i]);
	
	//��ʵʱ�ɼ���
	SolidRectangle(2, 462, 241, 562);
	OutTextXY(10, 472, "����ɵķ�������:");
	OutTextXY(10, 500, "����Ҫ��ɵķ�������:");
	//����ʣ��ķ���������������ʵ��
}


// ������Ϸ�����е�һ������
void PLAYER::DrawRow(int baseY, int iTask)
{
	int fromY = baseY;				// �����е���ʼ y ����
	int toY = baseY + 99;			// �����е���ֹ y ����

	// ��� y ���곬����ʾ��Χ��������
	if (fromY < 0) fromY = 0;
	if (toY > 399) toY = 399;

	COLORREF c[4];					// �������ĸ��������ɫ

	//�������һ���ǻ�ɫ
	if (iTask < 0) //iTask = -1;
	{
		for (int i = 0; i < 4; i++)
			c[i] = YELLOW;
	}
	//���֮��ķ�������ɫ
	else if (iTask >= MAXTASK)
	{
		for (int i = 0; i < 4; i++)
			c[i] = GREEN;
	}
	//һ�����
	else
	{
		for (int i = 0; i < 4; i++)
			c[i] = WHITE;

		c[m_Task[iTask]] = (iTask < m_iTask) ? LIGHTGRAY : BLACK;
		//����֮���ɫ���齫��ɻ�ɫ
	}

	// �������е��ĸ�����
	setlinecolor(0xe9dbd6);
	for (int i = 0; i < 4; i++)
	{
		setfillcolor(c[i]);
		FillRectangle(2 + i * 60, 44 + 399 - fromY, 2 + i * 60 + 59, 44 + 399 - toY);
	}

	// ����ǵ�һ�У��ڷ������д����ʼ��������
	if (iTask == 0 && m_iTask == 0)
	{
		int w = textwidth("��ʼ");
		int h = textheight("��ʼ");
		int x = 2 + m_Task[iTask] * 60 + (60 - w) / 2;
		int y = 44 + 399 - 99 - fromY + (100 - h) / 2;
		//Ѱ�������кڿ����м�λ�ã���д����ʼ��������
		settextcolor(WHITE);
		settextstyle(16, 0, "Verdana");
		OutTextXY(x, y, "��ʼ");
	}
}


// ����ͨ����Ϸ��Ľ���
void PLAYER::DrawPass()
{
	// ���Ƴɹ��ı���
	setfillcolor(GREEN);
	SolidRectangle(2, 44, 241, 443);

	// ���"�ɹ�"
	settextcolor(WHITE);
	settextstyle(60, 0, "Verdana");
	int w = textwidth("�ɹ�");
	OutTextXY((244 - w) / 2, 100, "�ɹ�");

	// ����ɼ�
	char tmp[100];
	settextstyle(32, 0, "Verdana");
	sprintf_s(tmp, "�ɼ���%.3f ��", m_lastTime);
	w = textwidth(tmp);
	OutTextXY((244 - w) / 2, 200, tmp);
	sprintf_s(tmp, "�ٶȣ�%.3f/s", MAXTASK / m_lastTime);
	OutTextXY((244 - w) / 2, 240, tmp);

	// ������¿�ʼ����ʾ
	settextstyle(16, 0, "Verdana");
	w = textwidth("��������Ƽ����¿�ʼ");
	OutTextXY((244 - w) / 2, 400, "��������Ƽ����¿�ʼ");
}


// ������Ϸʧ�ܺ�Ľ���
void PLAYER::DrawFail()
{
	if (m_failFrame == 0)
	{	// ��ʼ����������˸Ч��������
		m_failRect.left = 3 + m_failErrorKey * 60;
		m_failRect.right = m_failRect.left + 57;
		m_failRect.bottom = m_nextTaskY + 1;
		m_failRect.top = m_nextTaskY + 98;

		if (m_failRect.top > 398) m_failRect.top = 398;
		m_failRect.bottom = 44 + 399 - m_failRect.bottom;
		m_failRect.top = 44 + 399 - m_failRect.top;
	}

	if (m_failFrame < 60)
	{	// ʵ����˸Ч��
		setfillcolor(((m_failFrame / 6) % 2 == 0) ? RED : LIGHTRED);
		SolidRectangle(m_failRect.left, m_failRect.bottom, m_failRect.right, m_failRect.top);
		m_failFrame++;
	}
	else
	{
		// �ı���Ϸ״̬
		m_status = FAIL;

		// ����ʧ�ܵı���
		setfillcolor(RED);
		SolidRectangle(2, 44, 241, 443);

		// ���"ʧ��"
		settextcolor(WHITE);
		settextstyle(60, 0, "Verdana");
		int w = textwidth("ʧ��");
		OutTextXY((244 - w) / 2, 100, "ʧ��");

		// �����ʷ�ɼ�
		settextstyle(20, 0, "Verdana");
		char tmp[100];
		sprintf_s(tmp, "��ʷ��óɼ���%.3f ��", m_bestTime);
		w = textwidth(tmp);
		OutTextXY((244 - w) / 2, 200, tmp);

		// ������¿�ʼ����ʾ
		settextstyle(16, 0, "Verdana");
		w = textwidth("��������Ƽ����¿�ʼ");
		OutTextXY((244 - w) / 2, 400, "��������Ƽ����¿�ʼ");
	}
}

//����ʵʱ�ɼ���
void PLAYER::DrawRealTimeScore(int iTask)
{
	setfillcolor(BLACK);
	SolidRectangle(150, 472, 178, 488);
	SolidRectangle(180, 500, 208, 516);
	char tmp2[5]; 
	sprintf_s(tmp2, "%d", iTask);
	char tmp3[5];
	sprintf_s(tmp3, "%d", MAXTASK - iTask);
	//��ʾʵʱ�ɼ�
	if (iTask <= MAXTASK)
	{
		OutTextXY(150, 472, tmp2);
		OutTextXY(180, 500, tmp3);
	}
	else
	{
		OutTextXY(150, 472, "END");
		OutTextXY(180, 500, "NO");		//������ʾ��λ�ã���ͬ
	}
}


//������ʾ��������
void PLAYER::OutTextXY(int x, int y, LPCTSTR s)							// ��ָ��λ������ַ���
{
	outtextxy(m_offset.x + x, m_offset.y + y, s);
}
void PLAYER::OutTextXY(int x, int y, char c)							// ��ָ��λ������ַ�
{
	outtextxy(m_offset.x + x, m_offset.y + y, c);
}
void PLAYER::Rectangle(int x1, int y1, int x2, int y2)					// ���ƾ���
{
	rectangle(m_offset.x + x1, m_offset.y + y1, m_offset.x + x2, m_offset.y + y2);
}
void PLAYER::FillRectangle(int x1, int y1, int x2, int y2)				// �����б߿�������
{
	fillrectangle(m_offset.x + x1, m_offset.y + y1, m_offset.x + x2, m_offset.y + y2);
	//4�������ֱ������Ϻ����ϵ�����
}
void PLAYER::SolidRectangle(int x1, int y1, int x2, int y2)				// �����ޱ߿�������
{
	solidrectangle(m_offset.x + x1, m_offset.y + y1, m_offset.x + x2, m_offset.y + y2);
}