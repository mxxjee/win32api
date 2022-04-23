#include "stdafx.h"
#include "Onion.h"
#include "AbstractFactory.h"
#include "OBullet.h"
#include "BmpMgr.h"
#include "Carrot.h"
#include "ObjMgr.h"
#include "MonsterHit.h"
#include "SoundMgr.h"

COnion::COnion()
	:m_flTime(0.f),m_fTime(0.f), iCnt(0), m_bDeath(false), m_bIntro(true),iEffectCnt(1), g_fSound(1.f)
{
}


COnion::~COnion()
{
}

void COnion::Initialize(void)
{
	srand((unsigned int)time(NULL));

	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/양파 공격2.wav", SOUND_ONION, g_fSound);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/양파죽음.wav", SOUND_EFFECT, g_fSound);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/당근인트로.wav", SOUND_EFFECT, g_fSound);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Onion/Onion_Death.bmp", L"Onion_Death");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Onion/Onion_Attack.bmp", L"Onion_Attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Onion/Onion_Intro.bmp", L"Onion_Intro");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Onion/Onion_ChangeToAttack.bmp", L"Onion_Idle");

	m_tInfo = { 400, 400.f, 350.f, 350.f };

	//float	fX; 
	//float	fY;
	//float	fCX;
	//float	fCY;
	m_tImageInfo.fX = 400.f;
	m_tImageInfo.fY = 400.f;

	m_tImageInfo.fCX = 200.f;
	m_tImageInfo.fCY = 200.f;

	iHp = 20;			//20
	iAttack = 0;

	m_eRender = RENDER_OBJ;

	m_pFrameKey = L"Onion_Intro";
	m_eCurState = ST_INTRO;
	m_ePreState = ST_END;

	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 23;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();


}

int COnion::Update(void)
{
	

	if (m_bDead)
	{
		//죽으면 당근생성
		CSoundMgr::Get_Instance()->PlaySound(L"당근인트로.wav", SOUND_ONION, g_fSound);
		CObjMgr::Get_Instance()->AddObject(OBJ_CARROT, CAbstractFactory<CCarrot>::Create());
		dynamic_cast<CCarrot*>(CObjMgr::Get_Instance()->Get_Carrot())->Set_Bullet(CObjMgr::Get_Instance()->Get_CarrotBullet());
		dynamic_cast<CCarrot*>(CObjMgr::Get_Instance()->Get_Carrot())->Set_Bullet(CObjMgr::Get_Instance()->Get_CarrotBeam());

		return OBJ_DEAD;
	}
		

	if (m_bIntro)
	{
		m_eCurState = ST_INTRO;

	}

	m_flTime += 1.f;

	if (!m_bDeath)
	{
		//5초에 한번 (5발) 
		if (m_flTime >= 180)
		{
			m_fTime += 1.f;
			m_pFrameKey = L"Onion_Attack";
			m_eCurState = ST_ATTACK;
			CSoundMgr::Get_Instance()->PlaySound(L"양파 공격2.wav", SOUND_ONION, 0.5f);
			if (m_fTime >= 30)
			{
				iCnt++;

				m_pBullet->push_back(CAbstractFactory<COBullet>::Create(rand() % WINCX, 30, NULL));
				m_fTime = 0.f;
				if (iCnt > 15)
				{
					iCnt = 0;
					m_flTime = 0.f;
				}

			}


		}
	}
	

	if (m_bDeath)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_ONION);
		m_pFrameKey = L"Onion_Death";
		m_eCurState = ST_DEATH;

		if (iEffectCnt == 1)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"양파죽음.wav", SOUND_EFFECT, g_fSound);
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CMonsterHit>::Create(m_tInfo.fX, m_tInfo.fY));
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CMonsterHit>::Create(m_tInfo.fX - 30.f, m_tInfo.fY + 30.f));
			
			iEffectCnt = 0;
		}

		if (m_eCurState == ST_DEATH &&m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			
			m_tInfo.fY += 30.f;
			
		}
		
	}


	Motion_Change();
	Move_Frame();



	if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_bIntro = false;
	/*	m_pFrameKey = L"Onion_Idle";
		m_eCurState = ST_IDLE;*/
	}

	
	Update_Rect_Image();
	Update_Rect();



	return OBJ_NOEVENT;
}

void COnion::Late_Update(void)
{
	if (m_tInfo.fY >= WINCY)
		Set_Dead();
	
}

void COnion::Render(HDC hDC)
{
	/*Rectangle(hDC,
		m_tImageRect.left,
		m_tImageRect.top,
		m_tImageRect.right,
		m_tImageRect.bottom);*/

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

void COnion::Release(void)
{
}

void COnion::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_INTRO:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 23;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_ATTACK:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case DEATH:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 31;
			m_tFrame.dwFrameSpeed = 2000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
