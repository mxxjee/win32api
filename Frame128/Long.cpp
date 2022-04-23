#include "stdafx.h"
#include "Long.h"
#include "BmpMgr.h"


CLong::CLong()
{
}


CLong::~CLong()
{
}

void CLong::Initialize(void)
{

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Flower/long.bmp", L"long");
	m_tInfo.fCX = 600.f;
	m_tInfo.fCY = 100.f;

	m_tInfo.fX = 300.f;
	m_tInfo.fY = 500.f;

	m_eRender = RENDER_OBJ;


	m_pFrameKey = L"long";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;
}

int CLong::Update(void)
{


	Motion_Change();
	Move_Frame();

	Update_Rect();
	return OBJ_NOEVENT;

}

void CLong::Late_Update(void)
{

	if (m_tFrame.iFrameStart == 22)
		m_tFrame.iFrameStart = 21;
}

void CLong::Render(HDC hDC)
{
	/*Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);*/
	


	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);


	GdiTransparentBlt(hDC,
		(int)m_tRect.left, // 2, 3인자 : 복사 받을 위치 X,Y 좌표
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 4,5인자 : 복사 받을 X,Y 길이
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9. 10인자 : 복사할 비트맵의 X,Y 사이즈
		(int)m_tInfo.fCY,
		RGB(0, 54, 54));	// 11인자 : 제거할 색상 

}

void CLong::Release(void)
{
}

void CLong::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 22;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		}
		m_ePreState = m_eCurState;
	}
}
