#include "stdafx.h"
#include "Potato.h"
#include "AbstractFactory.h"
#include "MBullet.h"
#include "BmpMgr.h"
#include "Onion.h"
#include "OBullet.h"
#include "ObjMgr.h"
#include "MonsterHit.h"
#include "SoundMgr.h"


CPotato::CPotato()
	:m_fTime(0.f),m_flTime(0.f), iCnt(0), m_bIntro(true), m_bDeath(false), m_bRealDeath(false), m_fOTime(false), iEffectCnt(1)
{
}


CPotato::~CPotato()
{
	Release();
}

void CPotato::Initialize(void)
{
	g_fSound = 1.f;

	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/감자 뱉어낼때.wav", SOUND_EFFECT, g_fSound);
	

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Potato/Potato_Death.bmp", L"Potato_Death");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Potato/Potato_Idle.bmp", L"Potato_Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Potato/Potato_Intro.bmp", L"Potato_Intro");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Potato/Potato_Spit_Attack.bmp", L"Potato_Attack");


	//float	fX; 
	//float	fY;
	//float	fCX;
	//float	fCY;

	m_tInfo = { 700, 450.f, 250.f, 250.f };

	m_tImageInfo.fX = 780.f;
	m_tImageInfo.fY = 450.f;

	m_tImageInfo.fCX = 200.f;
	m_tImageInfo.fCY = 200.f;

	iAttack = 0;
	iHp = 20;               //20

	m_eRender = RENDER_OBJ;
	m_fSpeed = 2.f;


	m_pFrameKey = L"Potato_Intro";
	m_eCurState = ST_INTRO;
	m_ePreState = ST_END;

	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();



}

int CPotato::Update(void)
{
	
	if (m_bDead)
	{
		//죽으면 양파 생성

		CObjMgr::Get_Instance()->AddObject(OBJ_ONION, CAbstractFactory<COnion>::Create());
		dynamic_cast<COnion*>(CObjMgr::Get_Instance()->Get_Onion())->Set_Bullet(CObjMgr::Get_Instance()->Get_OBullet());

		return OBJ_DEAD;
	}
	

	/*float	fWidth = 0.f, fHeight = 0.f, fRadian = 0.f;

	fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
	fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

	m_fDiagonal = sqrtf(fWidth* fWidth + fHeight* fHeight);

	fRadian = acosf(fWidth / m_fDiagonal);

	/ *if (m_pTarget->Get_Info().fY > m_tInfo.fY)
		fRadian = (2.f * PI) - fRadian;* /

	/ *	m_tInfo.fX += cosf(fRadian) * m_fSpeed;
	m_tInfo.fY -= sinf(fRadian) * m_fSpeed;* /

	m_fAngle = fRadian * (180.f / PI);

	if (m_pTarget->Get_Info().fY > m_tInfo.fY)
		m_fAngle *= -1.f;
		//m_fAngle = 360.f - m_fAngle;

	m_tInfo.fX += cosf(m_fAngle * (PI / 180.f)) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * (PI / 180.f)) * m_fSpeed;*/

	if (m_bIntro)
	{
		m_eCurState = ST_INTRO;
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			m_bIntro = false;
			m_pFrameKey = L"Potato_Idle";
			m_eCurState = ST_IDLE;
		}
		
	}

	
	
		
	if (m_bDeath)
	{
		m_pFrameKey = L"Potato_Death";
		m_eCurState = ST_DEATH;
		Motion_Change();

		if (iEffectCnt == 1)
		{
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CMonsterHit>::Create(m_tInfo.fX, m_tInfo.fY));
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CMonsterHit>::Create(m_tInfo.fX - 30.f, m_tInfo.fY + 30.f));
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CMonsterHit>::Create(m_tInfo.fX + 50.f, m_tInfo.fY - 45.f));
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CMonsterHit>::Create(m_tInfo.fX - 40.f, m_tInfo.fY - 45.f));
			iEffectCnt = 0;
		}
		if (m_eCurState == ST_DEATH &&m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			m_tInfo.fY += 90.f;
			
			}
		}
	


	

	if (!m_bDeath)
	{
		m_flTime += 1.f;
		//삼초에 한번 (3발)
		if (m_flTime >= 180)
		{
			m_fTime += 1.f;
			m_pFrameKey = L"Potato_Attack";
			m_eCurState = ST_ATTACK;

			if (m_fTime >= 60)
			{
				iCnt++;
				CSoundMgr::Get_Instance()->PlaySound(L"감자 뱉어낼때.wav", SOUND_EFFECT, g_fSound);
				CObjMgr::Get_Instance()->AddObject(OBJ_PBULLET, CAbstractFactory<CMbullet>::Create(m_tInfo.fX, m_tInfo.fY + 30));
				m_fTime = 0.f;
				if (iCnt > 2)
				{
					iCnt = 0;
					m_flTime = 0.f;
				}

			}


		}
	}
	



	Motion_Change();
	Move_Frame();

	
	

		

	

	Update_Rect_Image();
	Update_Rect();

	

	return OBJ_NOEVENT;
}


void CPotato::Late_Update(void)
{


	

	if (m_tInfo.fY >= WINCY)
		Set_Dead();

	
}

void CPotato::Render(HDC hDC)
{
	/*Rectangle(hDC,
		m_tImageRect.left,
		m_tImageRect.top,
		m_tImageRect.right,
		m_tImageRect.bottom);*/

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	
	GdiTransparentBlt(hDC,
		(int)m_tRect.left, // 2, 3인자 : 복사 받을 위치 X,Y 좌표
		(int)m_tRect.top ,
		(int)m_tInfo.fCX,	// 4,5인자 : 복사 받을 X,Y 길이
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9. 10인자 : 복사할 비트맵의 X,Y 사이즈
		(int)m_tInfo.fCY,
		RGB(32, 29, 28));	// 11인자 : 제거할 색상 

	
}

void CPotato::Release(void)
{
	
}

void CPotato::Motion_Change(void)
{
	//ST_INTRO
	//ST_IDLE
	//ST_ATTACK
	//ST_DEATH
	//ST_END

	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_INTRO:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_IDLE:
			m_tFrame.iFrameMotion =0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_ATTACK:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 23;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case DEATH:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.dwFrameSpeed = 3000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
