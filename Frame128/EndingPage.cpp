#include "stdafx.h"
#include "EndingPage.h"
#include "BmpMgr.h"


CEndingPage::CEndingPage()
{
}


CEndingPage::~CEndingPage()
{
}

void CEndingPage::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/EndingPage.bmp", L"EndingPage");

	m_tInfo.fCX = WINCX;
	m_tInfo.fCY = WINCY;

	m_eRender = RENDER_OBJ;

	m_pFrameKey = L"EndingPage";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;

}

int CEndingPage::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	/*if (m_tFrame.iFrameStart == 21)
	{
		m_tFrame.iFrameStart = 21;
		
	}*/

	
	Motion_Change();
	if (m_tFrame.iFrameStart <= 21)
		Move_Frame();

	return OBJ_NOEVENT;
}

void CEndingPage::Late_Update(void)
{

	
}

void CEndingPage::Render(HDC hDC)
{
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
		RGB(0, 64, 64));	// 11인자 : 제거할 색상 

	
}

void CEndingPage::Release(void)
{
}

void CEndingPage::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 22;
			m_tFrame.dwFrameSpeed =60;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		}
		m_ePreState = m_eCurState;
	}
}
