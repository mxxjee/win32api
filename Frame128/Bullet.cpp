#include "stdafx.h"
#include "Bullet.h"
#include "BmpMgr.h"

int		CBullet::Stage01Bullet = 0;

CBullet::CBullet()
	:m_bCollision(false)
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_eRender = RENDER_OBJ;

	m_fSpeed = 5.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Stretch.bmp", L"Stretch_Bullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Strecth_2.bmp", L"Stretch_Bullet2");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Bullet_2.bmp", L"Bullet");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BulletUp.bmp", L"Bullet_Up");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BulletSide.bmp", L"Bullet_Side");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BulletDeath.bmp", L"Bullet_Death");


	m_pFrameKey = L"Stretch_Bullet";
	m_eCurState = ST_INTRO;
	m_ePreState = ST_END;

	iAttack = 1;
	iHp = 0;

	

	m_tFrame.iPosX = 2;
	m_tFrame.iPosY = 291;
	m_tFrame.iSizeX = 105;
	m_tFrame.iSizeY = 100;
	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CBullet::Update(void)
{

	if (m_bDead)
	{
		return OBJ_DEAD;
	}
		
	
	


	switch (m_eDir)
	{
	case UP:
		
		//++Stage01Bullet;
		m_tInfo.fY -= m_fSpeed;
		m_pFrameKey = L"Bullet";
		m_eCurState = ST_UP;

		break;

	case DOWN:
		//++Stage01Bullet;
		m_tInfo.fY += m_fSpeed;
		/*m_pFrameKey = L"Bullet_Up";
		m_eCurState = ST_UP;*/
		break;

	case LEFT:
		//++Stage01Bullet;
		m_tInfo.fX -= m_fSpeed;
		m_pFrameKey = L"Bullet";
		m_eCurState = ST_LEFT;
		break;

	case RIGHT:
		++Stage01Bullet;
		m_tInfo.fX += m_fSpeed;
		m_pFrameKey = L"Bullet";
		m_eCurState = ST_RIGHT;
		break;


	}

	/*if (m_bCollision)
	{
		m_eDir = DEATH;
		m_eCurState = ST_DEAD;
		m_pFrameKey = L"Bullet_Death";
	}*/
	
	//m_eCurState = ST_DEAD;

	if (m_bCollision)
	{
		iAttack = 0;
		m_fSpeed = 0.f;
		m_tInfo.fCX = 150.f;
		m_tInfo.fCY = 150.f;
		m_pFrameKey = L"Bullet";
		m_eCurState = ST_DEAD;
		Motion_Change();
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			Set_Dead();
			
		}
	}

	
	Motion_Change();
	Move_Frame();
	

	Update_Rect();

	return OBJ_NOEVENT;
	
}

void CBullet::Late_Update()
{
	if (50>= m_tRect.left || WINCX <= m_tRect.right ||
		50>= m_tRect.top || WINCY < m_tRect.bottom)
	{
		
		m_bCollision = true;
	}

	

}

void CBullet::Render(HDC hDC)
{
	/*Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);*/

	if (m_eCurState == ST_DEAD)
	{
		HDC		hStrecth = CBmpMgr::Get_Instance()->Find_Image(L"Stretch_Bullet2");
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


	else
	{
		HDC		hStrecth = CBmpMgr::Get_Instance()->Find_Image(L"Stretch_Bullet");
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
	
	HDC		hStrecth = CBmpMgr::Get_Instance()->Find_Image(L"Stretch_Bullet");
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

void CBullet::Release(void)
{
	
}

void CBullet::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_INTRO:
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
		case ST_UP:
			m_tFrame.iPosX = 2;
			m_tFrame.iPosY = 26;
			m_tFrame.iSizeX = 75;
			m_tFrame.iSizeY = 75;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_LEFT:
			m_tFrame.iPosX = 2;
			m_tFrame.iPosY = 26;
			m_tFrame.iSizeX = 75;
			m_tFrame.iSizeY = 75;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_RIGHT:
			m_tFrame.iPosX = 2;
			m_tFrame.iPosY = 26;
			m_tFrame.iSizeX = 75;
			m_tFrame.iSizeY = 75;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_DOWN:
			m_tFrame.iPosX = 2;
			m_tFrame.iPosY = 26;
			m_tFrame.iSizeX = 75;
			m_tFrame.iSizeY = 75;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 4;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_DEAD:
			m_tFrame.iPosX = 2;
			m_tFrame.iPosY = 1008;
			m_tFrame.iSizeX = 403;
			m_tFrame.iSizeY = 395;
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}

		m_ePreState = m_eCurState;
	}
}
