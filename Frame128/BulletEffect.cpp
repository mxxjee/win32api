#include "stdafx.h"
#include "BulletEffect.h"
#include "BmpMgr.h"

CBulletEffect::CBulletEffect()
	:m_fTime(0.f)
{
}


CBulletEffect::~CBulletEffect()
{
}

void CBulletEffect::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Bullet_2.bmp", L"Bullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Stretch_intro.bmp", L"Bullet_Intro_Stretch");
	
	m_tInfo.fCX = 45.f;
	m_tInfo.fCY = 45.f;

	m_pFrameKey = L"Bullet";
	m_eCurState = ST_IDLE;

	m_tFrame.iPosX = 2;
	m_tFrame.iPosY = 291;
	m_tFrame.iSizeX = 105;
	m_tFrame.iSizeY = 100;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRender = RENDER_OBJ;
}

int CBulletEffect::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	Motion_Change();
	Move_Frame();

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBulletEffect::Late_Update(void)
{
	m_fTime += 1.f;

	if (m_fTime >= 30)
	{
		m_bDead = true;
		m_fTime = 0;
	}
		

}

void CBulletEffect::Render(HDC hDC)
{
	HDC		hStrecth = CBmpMgr::Get_Instance()->Find_Image(L"Bullet_Intro_Stretch");
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	StretchBlt(hStrecth,
		0, 0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iPosX + m_tFrame.iFrameStart * (m_tFrame.iSizeX + m_tFrame.iPosX),
		m_tFrame.iPosY,
		m_tFrame.iSizeX, m_tFrame.iSizeY,
		SRCCOPY);


	GdiTransparentBlt(hDC,
		(int)m_tRect.left, // 2, 3인자 : 복사 받을 위치 X,Y 좌표
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 4,5인자 : 복사 받을 X,Y 길이
		(int)m_tInfo.fCY,
		hStrecth,
		0, 0,
		(int)m_tInfo.fCX,		// 9. 10인자 : 복사할 비트맵의 X,Y 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));	// 11인자 : 제거할 색상 
}

void CBulletEffect::Release(void)
{
}

void CBulletEffect::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iPosX = 2;
			m_tFrame.iPosY = 291;
			m_tFrame.iSizeX = 105;
			m_tFrame.iSizeY = 100;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		

		}

		m_ePreState = m_eCurState;
	}
}
