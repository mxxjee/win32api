#include "stdafx.h"
#include "OBullet.h"
#include "BmpMgr.h"
#include "SoundMgr.h"


COBullet::COBullet()
{
}


COBullet::~COBullet()
{
}

void COBullet::Initialize(void)
{
	g_fSound = 1.f;

	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/눈물충돌.wav", SOUND_EFFECT, g_fSound);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Onion/Onion_Proj_NonParryableA.bmp", L"Onion_Bullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Onion/Onion_Proj_ParryableSplash.bmp", L"OBullet_Death");

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_tImageInfo.fCX = 40.f;
	m_tImageInfo.fCY = 40.f;

	m_fSpeed = 8.f;
	
	m_pFrameKey = L"Onion_Bullet";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;

	m_eRender = RENDER_OBJ;

	iAttack = 1;
}

int COBullet::Update(void)
{
	

	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fY += m_fSpeed;

	m_tImageInfo.fX = m_tInfo.fX;
	m_tImageInfo.fY = m_tInfo.fY;

	m_pFrameKey = L"Onion_Bullet";

	Motion_Change();
	Move_Frame();
	
	Update_Rect_Image();
	Update_Rect();
	return OBJ_NOEVENT;
}

void COBullet::Late_Update(void)
{
	if (m_tInfo.fX < 0 || m_tInfo.fY >550)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"눈물충돌.wav", SOUND_EFFECT, g_fSound);
		m_pFrameKey = L"OBullet_Death";
		m_eCurState = ST_DEAD;
		m_fSpeed =3;
		m_bGround = true;
		Set_Dead();
	}
		

}

void COBullet::Render(HDC hDC)
{
	/*Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);*/

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


	if (m_bGround)
	{
		
		m_bGround = false;
	}

}

void COBullet::Release(void)
{
}

void COBullet::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		

		case ST_DEAD:
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
