//��ʼ������ Init(): ��ʼ������ľ�����Ϣ

#include "pch.h"
#include "player.h"
#include <graphics.h>
#include <conio.h>
#include <time.h>

// ��ʼ������
//����:
//	1.ÿ�з����а׿��λ��
//  2.�����ʼ������
//	3.��ҳ�ʼ״̬
//  4.ʧ�ܺ����
void PLAYER::Init()
{
	// ��ʼ������ÿ�а׿�λ����������ڡ�0��3��֮��
	for (int i = 0; i < MAXTASK; i++)
		m_Task[i] = rand() % 4; 

	m_iTask = 0;				// �ӵ�һ������ʼ
	m_nextTaskY = 200;			// �趨��һ������� Y ���꣬200��ʾ��ʼ��������Ķ���
	m_status = BEGIN;			// ������Ϸ��ʼ״̬
	m_failFrame = 0;			// ����ʧ�ܺ�Ķ�����֡����

	// ��ʼ����Ϸ����
	DrawFrame();
}