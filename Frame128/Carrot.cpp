#include "stdafx.h"
#include "Carrot.h"
#include "CarrotBeam.h"
#include "CarrotBullet.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "MonsterHit.h"
#include "SoundMgr.h"

CCarrot::CCarrot()
	:m_bDeath(false),m_flTime(0.f),m_fTime(0.f),iCnt(0), m_f2Time(0.f), m_fl2Time(0.f), iCnt2(0), m_bIntro(true),m_bAttack(false), iEffectCnt(1)
	,g_fSound(1.f)
{
}


CCarrot::~CCarrot()
{
}

void CCarrot::Initialize(void)
{
	srand((unsigned int)time(NULL));


	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/당근죽음.wav", SOUND_EFFECT, g_fSound);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Carrot/Dirt/Carrot_Intro_300.bmp", L"Carrot_Intro");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Carrot/Dirt/Carrot_Attack_300.bmp", L"Carrot_Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Carrot/Dirt/Carrot_Beam_300.bmp", L"Carrot_Attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Carrot/Dirt/Carrot_Death_300.bmp", L"Carrot_Death");

	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 300.f;

	m_tInfo.fX = 400.f;
	m_tInfo.fY = 250.f;

	m_eRender = RENDER_OBJ;


	iAttack = 0;
	iHp = 20;        //15


	m_pFrameKey = L"Carrot_Intro";
	m_eCurState = ST_INTRO;
	m_ePreState = ST_END;

	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CCarrot::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	
	//계속 내려오는 플레이어를 따라가는 당근
	m_flTime += 1.f;

	m_pFrameKey = L"Carrot_Idle";
	m_eCurState = ST_IDLE;
	//삼초에 한번 (3발) 
	if (m_flTime >= 180)
	{
		m_fTime += 1.f;
		if (m_fTime >= 60)
		{
			iCnt++;
			//m_pBullet->push_back(CAbstractFactory<CCarrotBullet>::Create(rand() % WINCX, 30.f, NULL));
			CObjMgr::Get_Instance()->AddObject(OBJ_CBULLET, CAbstractFactory<CCarrotBullet>::Create(rand() % WINCX, 30.f, NULL));

			/*for (auto& Iter : (C))
				Iter->Set_Target(CObjMgr::Get_Instance()->Get_Player());*/

			m_fTime = 0.f;
			if (iCnt > 2)
			{
				iCnt = 0;
				m_flTime = 0.f;
			}

		}

	}

	//플레이어를 향해 쏘는 빔 
	//5초에 한번

	m_fl2Time += 1.f;


	if (m_fl2Time >= 300)
	{
		m_f2Time += 1.f;
		m_pFrameKey = L"Carrot_Attack";
		m_eCurState = ST_ATTACK;
		m_bAttack = true;
		Motion_Change();
		if (m_f2Time >= 180)
		{
			iCnt2++;
			//m_pBullet->push_back(CAbstractFactory<CCarrotBeam>::Create(m_tInfo.fX, m_tInfo.fY, NULL));
			CObjMgr::Get_Instance()->AddObject(OBJ_CARROTBEAM, CAbstractFactory<CCarrotBeam>::Create(m_tInfo.fX, m_tInfo.fY, NULL));
			/*CObjMgr::Get_Instance()->AddObject(OBJ_CARROTBEAM, CAbstractFactory<CCarrotBeam>::Create(m_tInfo.fX, m_tInfo.fY, NULL));
			CObjMgr::Get_Instance()->AddObject(OBJ_CARROTBEAM, CAbstractFactory<CCarrotBeam>::Create(m_tInfo.fX, m_tInfo.fY+10, NULL));*/

			/*for (auto& Iter : (*m_pBullet))
				Iter->Set_Target(CObjMgr::Get_Instance()->Get_Player());*/

			m_f2Time = 0.f;
			if (iCnt2 >=2 )
			{
				iCnt2 = 0;
				m_f2Time = 0.f;
			}

		}


	}



	/*if (m_bAttack == false)
	{
		m_pFrameKey = L"Carrot_Idle";
		m_eCurState = ST_IDLE;
	}*/

	if (m_bIntro)
	{
		m_eCurState = ST_INTRO;
		Motion_Change();

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			m_bIntro = false;
			m_pFrameKey = L"Carrot_Idle";
			m_eCurState = ST_IDLE;
		}

	}




	if (m_bDeath)
	{
		m_pFrameKey = L"Carrot_Death";
		m_eCurState = ST_DEATH;
		m_tInfo.fY += 2.f;
		Motion_Change();
		if (iEffectCnt == 1)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"당근죽음.wav", SOUND_MAIN, g_fSound);
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CMonsterHit>::Create(m_tInfo.fX, m_tInfo.fY));
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CMonsterHit>::Create(m_tInfo.fX - 30.f, m_tInfo.fY + 30.f));
			iEffectCnt = 0.f;
		}
		if (m_eCurState == ST_DEATH &&m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			

		}
	}

	Motion_Change();
	Move_Frame();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CCarrot::Late_Update(void)
{

	if (m_tInfo.fY >= 300.f)
		Set_Dead();
}

void CCarrot::Render(HDC hDC)
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

	if (m_bAttack)
		m_bAttack = false;
}

void CCarrot::Release(void)
{
}

void CCarrot::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_INTRO:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 25;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 21;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_ATTACK:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd =3;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case DEATH:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.dwFrameSpeed = 3000;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
