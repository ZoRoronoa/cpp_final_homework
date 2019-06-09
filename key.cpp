//�������� Hit(): �԰���ʵʱ��������״̬�ı䣬��Чʵ�ֵ�����

#include "pch.h"
#include "player.h"
#include <graphics.h>
#include <conio.h>
#include <cstdio>

// ������Ϸ�߰���
void PLAYER::Hit(char key)
{
	switch (m_status)
	{
	case BEGIN:				// ��Ϸ���ο�ʼ
		//m_keys �ǳ�ʼ���õİ������ֱ���"asdf" and "jkl;" �ж��Ƿ��µ���ָ�����Ǽ����������������޷�Ӧ��
		if (strchr(m_keys, key) != NULL)
		{
			m_beginClock = clock();				// ��¼��Ϸ��ʼʱ��ʱ��
			m_status = RUNNING;					// �ı���Ϸ״̬
		}

	case RUNNING:			// ��Ϸ������
	{
		//�ú����������ַ��� str �е�һ�γ����ַ� c ��λ�ã����δ�ҵ����ַ��򷵻� NULL��
		const char* pdest = strchr(m_keys, key);
		byte pos;
		if (pdest != NULL)						// �ж��Ƿ��ǵ�ǰ��Ϸ�߰���
		{
			pos = pdest - m_keys;				// ���㰴����Ӧ��λ��
			if (pos == m_Task[m_iTask])			// �жϰ����Ƿ���ȷ
			{
				//��Ч��������
				if (m_iTask == 0)
				{
					PlayMusic(pos);	
					//��һ��ֱ�Ӳ��Ű�����Ч
				}
				else if (m_iTask < MAXTASK)
				{
					CloseMusic(m_Task[m_iTask - 1]);
					PlayMusic(pos);
					//�������ȹر���һ�ο�������Ч���ٿ���������Ч
				}

				// ������ȷ
				m_iTask++;   //��������
				m_nextTaskY += 100;

				if (m_iTask == MAXTASK)			// ����ȫ�����
				{
					// �������ʱ��
					clock_t t = clock();
					// ����ִ��ʱ��
					m_lastTime = ((float)(clock() - m_beginClock)) / CLOCKS_PER_SEC;

					// ������ü�¼
					if (m_lastTime < m_bestTime)
						m_bestTime = m_lastTime;
					// �����һ�������������Ļ
					m_iTask++;
					m_nextTaskY += 100;
					m_status = PASSANI;
				}
			}
			else
			{
				// ����ʧ��
				m_failErrorKey = pos;
				if (m_iTask != 0)
					CloseMusic(m_Task[m_iTask - 1]); //�����г����ȹر�������ȷ����Ч���ٲ���ʧ����ʾ��;
				PlayFailMusic();					//�ٲ���ʧ����ʾ��;
				m_status = FAILANI;
			}
		}

		break;
	}

	case PASSANI:			// ��Ϸ�ɹ���Ķ���
	case FAILANI:			// ��Ϸʧ�ܺ�Ķ���
		break;

	case PASS:				// ��Ϸͨ����ĳɼ���ʾ
	case FAIL:				// ��Ϸʧ�ܺ�ĳɼ���ʾ
		if (strchr(m_keys, key) != NULL)
			Init();
		//ʵ�֡�����������¿�ʼ������
		break;
	}
}
