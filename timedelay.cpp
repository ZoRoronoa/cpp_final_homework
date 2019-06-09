//��ʱ���� HpSleep(int ms) ��������
//��ʱ�����ã� ʹ�����½����ٶȱ���

#include "pch.h"
#include "player.h"
#include <time.h>

// ��ȷ��ʱ����(���Ծ�ȷ�� 1ms������ ��1ms)
void HpSleep(int ms)
{
	static clock_t oldclock = clock();		// ��̬��������¼��һ�� tick
											//��ȡʱ��
	oldclock += ms * CLOCKS_PER_SEC / 1000;	// ���� tick
	if (clock() > oldclock)					// ����Ѿ���ʱ��������ʱ
		oldclock = clock();
	else
		while (clock() < oldclock)			// ��ʱ
			Sleep(1);						// �ͷ� CPU ����Ȩ������ CPU ռ���� 
}