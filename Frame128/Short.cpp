#include "stdafx.h"
#include "Short.h"
#include "BmpMgr.h"

CShort::CShort()
{
}


CShort::~CShort()
{
}

void CShort::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Flower/short.bmp", L"short");

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 300.f;

	m_eRender = RENDER_OBJ;


	m_pFrameKey = L"short";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;
}

int CShort::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Motion_Change();
	Move_Frame();


	Update_Rect();
	return OBJ_NOEVENT;
}

void CShort::Late_Update(void)
{
	if (m_tFrame.iFrameStart >= 15)
		m_tFrame.dwFrameSpeed = 200.f;

	if (m_tFrame.iFrameStart == 20)
	{
		m_tFrame.dwFrameSpeed = 50.f;
		Set_Dead();
	}
}

void CShort::Render(HDC hDC)
{
	/*Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);*/

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);


	GdiTransparentBlt(hDC,
		(int)m_tRect.left, // 2, 3���� : ���� ���� ��ġ X,Y ��ǥ
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 4,5���� : ���� ���� X,Y ����
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9. 10���� : ������ ��Ʈ���� X,Y ������
		(int)m_tInfo.fCY,
		RGB(0, 54, 54));	// 11���� : ������ ���� 
}

void CShort::Release(void)
{
}

void CShort::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 20;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		}
		m_ePreState = m_eCurState;
	}
}
