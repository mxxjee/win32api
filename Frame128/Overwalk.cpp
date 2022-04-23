#include "stdafx.h"
#include "Overwalk.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


COverwalk::COverwalk()
	:m_fTime(0.f)
{
}


COverwalk::~COverwalk()
{
}

void COverwalk::Initialize(void)
{
	

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Walk_Overworld.bmp", L"Walk_Overworld");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Walk_Overworld_Stretch.bmp", L"Walk_Overworld_Stretch");

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_pFrameKey = L"Walk_Overworld";

	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;

	m_eRender = RENDER_BACKOBJ;

	

	m_tFrame.iPosX = 2;
	m_tFrame.iPosY = 85;
	m_tFrame.iSizeX = 79;
	m_tFrame.iSizeY = 79;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 18;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
}

int COverwalk::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Motion_Change();
	Move_Frame();

	Update_Rect();
	return OBJ_NOEVENT;
}

void COverwalk::Late_Update(void)
{
	m_fTime += 1.f;

	if (m_fTime >=30)
	{
		m_bDead = true;
		m_fTime = 0.f;
	}
}

void COverwalk::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hStrecth = CBmpMgr::Get_Instance()->Find_Image(L"Walk_Overworld_Stretch");
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	StretchBlt(hStrecth,
		0, 0,
		50, 50,
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
		RGB(255, 255, 255));	// 11인자 : 제거할 색상 

		//CScrollMgr::Get_Instance()->Set_Target(this);
}

void COverwalk::Release(void)
{
}

void COverwalk::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iPosX = 2;
			m_tFrame.iPosY = 2;
			m_tFrame.iSizeX = 79;
			m_tFrame.iSizeY = 79;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 18;
			m_tFrame.dwFrameSpeed =20;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		}
		m_ePreState = m_eCurState;
	}
}
