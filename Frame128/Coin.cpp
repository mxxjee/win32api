#include "stdafx.h"
#include "Coin.h"
#include "BmpMgr.h"


CCoin::CCoin()
{
}


CCoin::~CCoin()
{
}

void CCoin::Initialize()
{
	//158527
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Strecth_coin2.bmp", L"Stretch_Coin");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Coin.bmp", L"Coin");

	m_tInfo.fCX = 75.f;
	m_tInfo.fCY = 75.f;

	m_pFrameKey = L"Coin";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;

	m_eRender = RENDER_OBJ;

	/*m_tFrame.iPosX = 2;
	m_tFrame.iPosY = 17;
	m_tFrame.iSizeX = 101;
	m_tFrame.iSizeY = 141;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 15;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();*/
	
}

void CCoin::Render(HDC hdc)
{
	//HDC		hStrecth = CBmpMgr::Get_Instance()->Find_Image(L"Stretch_Coin");
	//HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//StretchBlt(hStrecth,
	//	0, 0,
	//	(int)m_tInfo.fCX, (int)m_tInfo.fCY,
	//	hMemDC,
	//	m_tFrame.iPosX + m_tFrame.iFrameStart * (m_tFrame.iSizeX + m_tFrame.iPosX),
	//	m_tFrame.iPosY,
	//	m_tFrame.iSizeX, m_tFrame.iSizeY,
	//	SRCCOPY);


	//GdiTransparentBlt(hdc,
	//	(int)m_tRect.left, // 2, 3인자 : 복사 받을 위치 X,Y 좌표
	//	(int)m_tRect.top,
	//	(int)m_tInfo.fCX,	// 4,5인자 : 복사 받을 X,Y 길이
	//	(int)m_tInfo.fCY,
	//	hStrecth,
	//	0, 0,
	//	(int)m_tInfo.fCX,		// 9. 10인자 : 복사할 비트맵의 X,Y 사이즈
	//	(int)m_tInfo.fCY,
	//	RGB(112,112,112));	// 11인자 : 제거할 색상 

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
		RGB(70, 70, 70));	// 11인자 : 제거할 색상 
}


void CCoin::Late_Update()
{
}

void CCoin::Release()
{
}

int CCoin::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	Motion_Change();
	Move_Frame();


	Update_Rect();

	return OBJ_NOEVENT;
}

void CCoin::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			/*m_tFrame.iPosX = 2;
			m_tFrame.iPosY = 17;
			m_tFrame.iSizeX = 101;
			m_tFrame.iSizeY = 141;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();*/
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 13;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();

			break;
	

		}

		m_ePreState = m_eCurState;
	}
}
