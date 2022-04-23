#include "stdafx.h"
#include "Mbullet.h"
#include "BmpMgr.h"


CMbullet::CMbullet()
{
}


CMbullet::~CMbullet()
{
}

void CMbullet::Initialize(void)
{
	m_tInfo.fX = 700.f;
	m_tInfo.fY = 480.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Potato/Potato_NonParryable_2.bmp", L"Potato_Bullet");

	

	m_fSpeed = 5.f;

	iAttack = 2;
	iHp = 0;

	


	m_tInfo.fCX = 120.f;
	m_tInfo.fCY = 120.f;

	m_tImageInfo.fCX = 80.f;
	m_tImageInfo.fCY = 80.f;

	m_pFrameKey = L"Potato_Bullet";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;

	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 1;
	m_tFrame.iFrameEnd = 8;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRender = RENDER_OBJ;

}

int CMbullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	

	m_tInfo.fX -= m_fSpeed;

	m_pFrameKey = L"SPlayer_Idle";
	m_eCurState = ST_IDLE;

	iAttack = 1;
	iHp = 30;

	m_tImageInfo.fX = m_tInfo.fX;
	m_tImageInfo.fY = m_tInfo.fY;

	Motion_Change();
	Move_Frame();

	Update_Rect_Image();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMbullet::Late_Update(void)
{
	if (0 >= m_tInfo.fX)
	{
		m_bDead = true;
	}
}

void CMbullet::Render(HDC hDC)
{
	/*Rectangle(hDC,
		m_tImageRect.left,
		m_tImageRect.top,
		m_tImageRect.right,
		m_tImageRect.bottom);*/


	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Potato_Bullet");




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
		RGB(32, 29, 28));	// 11인자 : 제거할 색상 
	
}

void CMbullet::Release(void)
{
}

void CMbullet::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart =0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}

		m_ePreState = m_eCurState;
	}
}
