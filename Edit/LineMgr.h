#pragma once

#include "Line.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void		Initialize(void);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	bool		Collision_Line(float& fX, float* pY);


private:
	void		Key_Input(void);
	void		Save_Data(void);
	void		Load_Data(void);


public:
	static CLineMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CLineMgr;
		}

		return m_pInstance;
	}
	static void		Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CLineMgr*		m_pInstance;

	POINTPOS				m_tLinePoint[2];
	TCHAR	szBuff[32];
	list<CLine*>			m_LineList;
	POINT	pt{};
};

// ���� �����Ϳ� ��ũ�� �����Ͽ� ���� �����
// 1. �÷��̾��� �̵� ����� �ݴ� �������� ��ũ�� ���� ������
// EX)  m_tInfo.fX += m_speed;
//	    m_scrollX -= m_speed;

// 2. ��ũ�� ���� ��� �׸��� �ڵ��� ����
// 3. ���콺 ��ũ�ѵ� ���� ó���ؾ� ������ �߻����� ����(���콺�� �ݵ�� 0, 0 ~ 800,600�̶�� ��� ������������ ������)
