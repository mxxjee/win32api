#include "stdafx.h"
#include "EventCoin.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "EventEffect.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Stage.h"
#include "SoundMgr.h"


CEventCoin::CEventCoin()
	
{
}


CEventCoin::~CEventCoin()
{
}

void CEventCoin::Initialize(void)
{

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Coin_Stretch.bmp", L"Coin_Stretch");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Coin_Overworld.bmp", L"Coin_Overworld");

	
	m_bInstance = true;
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_tImageInfo.fCX = 5.f;
	m_tImageInfo.fCY = 5.f;

	m_eCurState = ST_IDLE;
	m_eRender = RENDER_BACKCOIN;

	m_tFrame.iPosX = 2;
	m_tFrame.iPosY = 17;
	m_tFrame.iSizeX = 101;
	m_tFrame.iSizeY = 141;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 15;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

	

}

int CEventCoin::Update(void)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	if (m_bDead)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"돈.wav", SOUND_EFFECT, 1);
		++CStage::iCoinCnt;
		//CObjMgr::Get_Instance()->Get_EventEffect()->Set_Dead();
		return OBJ_DEAD;
	}
		

	

	m_tImageInfo.fX = m_tInfo.fX;
	m_tImageInfo.fY = m_tInfo.fY;

	if (m_bInstance)
	{
		//CObjMgr::Get_Instance()->AddObject(OBJ_EVENTEFFECT, CAbstractFactory<CEventEffect>::Create(m_tInfo.fX, m_tInfo.fY));
		//m_bInstance = false;
	}

	Motion_Change();
	Move_Frame();



	Update_Rect_Image();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CEventCoin::Late_Update(void)
{
}

void CEventCoin::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hStrecth = CBmpMgr::Get_Instance()->Find_Image(L"Coin_Stretch");
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Coin_Overworld");

	StretchBlt(hStrecth,
		0, 0,
		50, 50,
		hMemDC,
		m_tFrame.iPosX + m_tFrame.iFrameStart * (m_tFrame.iSizeX + m_tFrame.iPosX),
		m_tFrame.iPosY,
		m_tFrame.iSizeX, m_tFrame.iSizeY,
		SRCCOPY);


	GdiTransparentBlt(hDC,
		(int)m_tRect.left+ iScrollX, // 2, 3인자 : 복사 받을 위치 X,Y 좌표
		(int)m_tRect.top+iScrollY,
		(int)m_tInfo.fCX,	// 4,5인자 : 복사 받을 X,Y 길이
		(int)m_tInfo.fCY,
		hStrecth,
		0, 0,
		(int)m_tInfo.fCX,		// 9. 10인자 : 복사할 비트맵의 X,Y 사이즈
		(int)m_tInfo.fCY,
		RGB(0, 64, 64));	// 11인자 : 제거할 색상 
}

void CEventCoin::Release(void)
{
}

void CEventCoin::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iPosX = 2;
			m_tFrame.iPosY = 17;
			m_tFrame.iSizeX = 101;
			m_tFrame.iSizeY = 141;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}

		m_ePreState = m_eCurState;
	}
}
