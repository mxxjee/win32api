#include "stdafx.h"
#include "CarrotBullet.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"



CCarrotBullet::CCarrotBullet()
	:m_bDeath(false),g_fSound(1.f)
{
}


CCarrotBullet::~CCarrotBullet()
{
}

void CCarrotBullet::Initialize(void)
{
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/당근부서짐.wav", SOUND_EFFECT, g_fSound);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Carrot/Carrot_Missile-vert.bmp", L"Carrot_Bullet");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Onion/Enemy1Explode.bmp", L"CarrotBullet_Death");


	m_pTarget = CObjMgr::Get_Instance()->Get_Player();

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_tImageInfo.fCX = 30.f;
	m_tImageInfo.fCY = 30.f;


	iAttack = 1;

	m_fSpeed = 1.f;

	m_pFrameKey = L"Carrot_Bullet";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;


	m_eRender = RENDER_OBJ;
}

int CCarrotBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	float	deltaX = m_tInfo.fX - (m_pTarget)->Get_Info().fX;
	float	deltaY = m_tInfo.fY - (m_pTarget)->Get_Info().fY;

	float Diagonal = sqrt(deltaX*deltaX + deltaY*deltaY);

	deltaX = deltaX / Diagonal;
	deltaY = deltaY / Diagonal;

	m_tInfo.fX -= m_fSpeed* (deltaX);
	m_tInfo.fY -= m_fSpeed* (deltaY);

	if (m_tInfo.fY >= 400)
		m_tInfo.fY += 5.f;

	if (m_bDeath)
	{
		iAttack = 0;
		m_eCurState = ST_DEATH;
		Motion_Change();
		CSoundMgr::Get_Instance()->PlaySound(L"당근부서짐.wav", SOUND_EFFECT, g_fSound);
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{

			Set_Dead();

		}
	}

	m_tImageInfo.fX = m_tInfo.fX;
	m_tImageInfo.fY = m_tInfo.fY;

	Motion_Change();
	Move_Frame();

	Update_Rect_Image();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CCarrotBullet::Late_Update(void)
{
	
	if (m_tInfo.fX < 0 || m_tInfo.fY >= WINCY || m_tInfo.fX >= WINCX)
		m_bDead= true;
}

void CCarrotBullet::Render(HDC hDC)
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
		RGB(32, 29, 28));	// 11인자 : 제거할 색상 
}

void CCarrotBullet::Release(void)
{
}

void CCarrotBullet::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd =5;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		case ST_DEATH:
			m_tFrame.iFrameMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
