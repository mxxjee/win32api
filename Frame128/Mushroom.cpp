#include "stdafx.h"
#include "Mushroom.h"
#include "BmpMgr.h"

CMushroom::CMushroom()
{
}


CMushroom::~CMushroom()
{

}

void CMushroom::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Flower/Mushroom.bmp", L"Mushroom");

	m_tInfo.fCX = 126.f;
	m_tInfo.fCY = 70.f;

	m_eRender = RENDER_OBJ;

	m_pFrameKey = L"Mushroom";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;

	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 8;
	m_tFrame.dwFrameSpeed =100;
	m_tFrame.dwFrameTime = GetTickCount();
}

void CMushroom::Render(HDC hdc)
{
	/*Rectangle(hdc,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);*/

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hdc,
		(int)m_tRect.left, // 2, 3인자 : 복사 받을 위치 X,Y 좌표
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 4,5인자 : 복사 받을 X,Y 길이
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9. 10인자 : 복사할 비트맵의 X,Y 사이즈
		(int)m_tInfo.fCY,
		RGB(0, 64, 64));	// 11인자 : 제거할 색상 
}

void CMushroom::Late_Update()
{

}

void CMushroom::Release()
{

}

int CMushroom::Update()
{
	Motion_Change();
	Move_Frame();

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMushroom::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}
		m_ePreState = m_eCurState;
	}
}

