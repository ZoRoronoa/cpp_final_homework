//player�ĺ�������

#include "pch.h"
#include "player.h"
#include <graphics.h>
#include <conio.h>

// ���캯��
//	������
//		name: ��Ϸ������
//		keys: ��Ϸ�����ð�����ָ�򳤶�Ϊ 4 ���ַ�����
//		offsetx, offsety: ��Ϸ�߶�Ӧ����Ϸ�������������е�ƫ����
PLAYER::PLAYER(const char* name, const char* keys, int offsetx, int offsety)
{
	m_strName = name;
	m_keys = keys;
	m_offset.x = offsetx;
	m_offset.y = offsety;

	m_bestTime = 99;	// ������ѳɼ�
	Init();				// ��ʼ����Ϸ�ߣ�Init����������������ĳ�ʼ��;
}