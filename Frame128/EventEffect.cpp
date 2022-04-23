#include "stdafx.h"
#include "EventEffect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"

CEventEffect::CEventEffect()
{
}


CEventEffect::~CEventEffect()
{
}

void CEventEffect::Initialize(void)
{

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Coin_Effect_Stretch.bmp", L"Effect_Stretch");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Coin_Overworld.bmp", L"Coin_Overworld");

	


	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;

	m_tImageInfo.fCX = 5.f;
	m_tImageInfo.fCY = 5.f;

	m_eCurState = ST_IDLE;
	m_eRender = RENDER_COINEFFECT;

	m_tFrame.iPosX = 2;
	m_tFrame.iPosY = 747;
	m_tFrame.iSizeX = 327;
	m_tFrame.iSizeY = 284;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

}

int CEventEffect::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;



	m_tImageInfo.fX = m_tInfo.fX;
	m_tImageInfo.fY = m_tInfo.fY;

	Motion_Change();
	Move_Frame();



	Update_Rect_Image();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CEventEffect::Late_Update(void)
{
}

void CEventEffect::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hStrecth = CBmpMgr::Get_Instance()->Find_Image(L"Effect_Stretch");
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Coin_Overworld");

	StretchBlt(hStrecth,
		0, 0,
		200, 200,
		hMemDC,
		m_tFrame.iPosX + m_tFrame.iFrameStart * (m_tFrame.iSizeX + m_tFrame.iPosX),
		m_tFrame.iPosY,
		m_tFrame.iSizeX, m_tFrame.iSizeY,
		SRCCOPY);


	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, // 2, 3인자 : 복사 받을 위치 X,Y 좌표
		(int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,	// 4,5인자 : 복사 받을 X,Y 길이
		(int)m_tInfo.fCY,
		hStrecth,
		0, 0,
		(int)m_tInfo.fCX,		// 9. 10인자 : 복사할 비트맵의 X,Y 사이즈
		(int)m_tInfo.fCY,
		RGB(0, 64, 64));	// 11인자 : 제거할 색상 
}

void CEventEffect::Release(void)
{
}

void CEventEffect::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iPosX = 2;
			m_tFrame.iPosY = 747;
			m_tFrame.iSizeX = 327;
			m_tFrame.iSizeY = 284;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}

		m_ePreState = m_eCurState;
	}
}

