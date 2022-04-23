#include "stdafx.h"
#include "Flower.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "FaceAttack.h"
#include "ObjMgr.h"
#include "Acorn.h"
#include "FlowerBullet.h"
#include "long.h"
#include "Short.h"
#include "MonsterHit.h"
#include "SoundMgr.h"
#include "Seed.h"
#include "BlueSeed.h"


CFlower::CFlower()
	:m_bIntro(true), iCnt(1),m_bIdle(false),m_fTime(0.f), m_bFaceAttack(true), iFaceCnt(1), iFaceCnt2(0),
	m_bBullet(false), iBulletCnt(0), m_bFinal(false),m_bFianlAttack(false),m_bFinalIntro(true), m_bMotion(true),m_fBulletTime(0.f), 
	m_bMakeBullet(false),m_fFlowerTime(0.f), iTreeCnt(1),m_fShortTime1(0.f),m_fShortTime2(0.f),m_fShortTime3(0.f), m_bShort(false),m_bDeath(false)
	,iEffectCnt(1),g_fSound(1.f), iSeedCnt(1),m_fTime3(0.f), m_fTime4(0.f)
{
}


CFlower::~CFlower()
{
}

void CFlower::Initialize(void)
{
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/꽃인트로.wav", SOUND_EFFECT, g_fSound);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/불렛생성시 웃음.wav", SOUND_EFFECT, g_fSound);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/꽃변신2.wav", SOUND_FLOWER, g_fSound);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/꽃 죽음.wav", SOUND_EFFECT, g_fSound);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/얼굴공격.wav", SOUND_FLOWER, g_fSound);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/줄기소환.wav", SOUND_EFFECT, g_fSound);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Flower/intro_2.bmp", L"Flower_Intro");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Flower/idle_4.bmp", L"Flower_Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Flower/face_attack2.bmp", L"Flower_FaceAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Flower/attack_2.bmp", L"Flower_BulletAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Flower/Fianl_Intro.bmp", L"Flower_FianlIntro");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Flower/fianl_attack.bmp", L"Flower_FianlAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Flower/Death.bmp", L"Flower_Death");


	

	m_tInfo.fCX = WINCX;
	m_tInfo.fCY = WINCY;

	m_tImageInfo.fCX = 200.f;
	m_tImageInfo.fCY = 450.f;

	m_tImageInfo.fX = 650.f;
	m_tImageInfo.fY = 300.f;

	iHp = 60;

	m_eRender = RENDER_OBJ;

	m_pFrameKey = L"Flower_Intro";
	m_eCurState = ST_INTRO;
	m_ePreState = ST_END;

	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 20;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CFlower::Update(void)
{

	if (m_bDead)
		return OBJ_DEAD;

	if (iHp <= 0)
		m_bDeath = true;

	if (m_bDeath)
	{
		m_pFrameKey = L"Flower_Death";
		m_eCurState = ST_DEATH;
		Motion_Change();
		CSoundMgr::Get_Instance()->PlaySound(L"꽃 죽음.wav", SOUND_EFFECT, g_fSound);
		if (iEffectCnt == 1)
		{
			
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CMonsterHit>::Create(600.f, 200.f));
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CMonsterHit>::Create(540.f, 150.f));
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CMonsterHit>::Create(500.f, 250.f));
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CMonsterHit>::Create(560.f,350.f));
			iEffectCnt = 0;
		}
	}

	if (m_bDeath && m_eCurState == ST_DEATH && m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_bDead = true;
	}

	if (m_bFianlAttack && m_eCurState == ST_FINALINTRO && m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_pFrameKey = L"Flower_FianlAttack";
		m_eCurState = ST_FINALATTACK;
		Motion_Change();

		if (iTreeCnt == 1)
		{
			
			CObjMgr::Get_Instance()->AddObject(OBJ_CLONG, CAbstractFactory<CLong>::Create());
			m_bShort = true;
			iTreeCnt = 0;
		}

		
		

		

	}

	if (m_bShort)
	{
		m_fShortTime1 += 1.f;
		m_fShortTime2 += 1.f;

		if (m_fShortTime1 >= 300)
		{
			CObjMgr::Get_Instance()->AddObject(OBJ_CSHORT, CAbstractFactory<CShort>::Create(90.f, 400.f));
			CObjMgr::Get_Instance()->AddObject(OBJ_CSHORT, CAbstractFactory<CShort>::Create(400.f, 400.f));
			m_fShortTime1 = 0.f;
		}

		if (m_fShortTime2 >= 180)
		{
			CObjMgr::Get_Instance()->AddObject(OBJ_CSHORT, CAbstractFactory<CShort>::Create(230.f, 400.f));
			m_fShortTime2 = 0.f;
		}
	}

	//마지막 발악
	if (!m_bFianlAttack && iHp <= 30)
	{
		m_bFinal = true;
		m_bFinalIntro = true;
		m_bBullet = false;
		m_bFaceAttack = false;
		m_bIntro = false;
		m_bIdle = false;
		iSeedCnt = 0;
		

		if (m_bFinalIntro)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"꽃변신2.wav", SOUND_FLOWER, g_fSound);
			m_pFrameKey = L"Flower_FianlIntro";
			m_eCurState = ST_FINALINTRO;
			m_bFinalIntro = false;
			m_bFianlAttack = true;

			Motion_Change();
		

		}

		
		
	}

	if (m_eCurState == ST_FINALATTACK && m_tFrame.iFrameStart >= 11)
	{
		m_fFlowerTime += 1.f;

		if (m_fFlowerTime >= 30)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"줄기소환.wav", SOUND_EFFECT, g_fSound);
			CObjMgr::Get_Instance()->AddObject(OBJ_FBULLET, CAbstractFactory<CFlowerBullet>::Create(500.f, 200.f));
			m_fFlowerTime = 0.f;
		}
	}
	
	if (iSeedCnt >= 1)
	{
		m_fTime3 += 1.f;
		m_fTime4 += 1.f;

		if (m_fTime3>= 120)
		{
			//CObjMgr::Get_Instance()->AddObject(OBJ_SEED, CAbstractFactory<CSeed>::Create());
			CObjMgr::Get_Instance()->AddObject(OBJ_SEED, CAbstractFactory<CBlueSeed>::Create());
			//CObjMgr::Get_Instance()->AddObject(OBJ_SEED, CAbstractFactory<CSeed>::Create(rand() % WINCX, 10, NULL));
			m_fTime3 = 0.f;
		}

		//빨간색씨앗  - 줄기, 잎생성
		if (m_fTime4 >= 300)
		{
			CObjMgr::Get_Instance()->AddObject(OBJ_SEED, CAbstractFactory<CSeed>::Create());
			m_fTime4 = 0.f;
		}
	}
	
	
	if (iFaceCnt2 == 3)
	
	{
		CSoundMgr::Get_Instance()->StopSound( SOUND_FLOWER);
		iFaceCnt2 = 0;
		m_bFaceAttack = false;
 		m_bBullet = true;

	}
		
	

	if (m_bIntro)
	{

		CSoundMgr::Get_Instance()->PlaySound(L"꽃인트로.wav", SOUND_EFFECT, g_fSound);
		m_pFrameKey = L"Flower_Intro";
		m_eCurState = ST_INTRO;
		Motion_Change();

	}

	if (!m_bFinal && !m_bIntro && m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_bIdle = true;
		

	}

	if (m_bIdle)
	{
		m_pFrameKey = L"Flower_Idle";
		m_eCurState = ST_IDLE;
		Motion_Change();
	}

	

	//머리 아래공격
	m_fTime += 1.f;
	if (m_bFaceAttack && m_fTime >= 480)
	{
		++iFaceCnt;
		if (iFaceCnt >= 1)
		{
			CSoundMgr::Get_Instance()->PlaySound(L"얼굴공격.wav", SOUND_FLOWER, g_fSound);
			++iFaceCnt2;
			++iSeedCnt;
			m_pFrameKey = L"Flower_FaceAttack";
			m_eCurState = ST_ATTACK;
			Motion_Change();
			CObjMgr::Get_Instance()->AddObject(OBJ_COLLISION, CAbstractFactory<CFaceAttack>::Create());
			
		}	
		m_fTime = 0.f;
	}

	//불렛발사 공격
	if (m_bBullet)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"불렛생성시 웃음.wav", SOUND_EFFECT, g_fSound);
		m_bIdle = false;
		//++iBulletCnt;
		m_pFrameKey = L"Flower_BulletAttack";
		m_eCurState = ST_BULLET;
		Motion_Change();
	}

	if (m_eCurState == ST_BULLET && m_tFrame.iFrameStart == 17)
	{
		m_bMakeBullet = true;
	

	}
	
	if (m_bMakeBullet)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_ACORN, CAbstractFactory<CAcorn>::Create(550.f, 300.f));
		CObjMgr::Get_Instance()->AddObject(OBJ_ACORN, CAbstractFactory<CAcorn>::Create(550.f, 360.f));
		CObjMgr::Get_Instance()->AddObject(OBJ_ACORN, CAbstractFactory<CAcorn>::Create(550.f, 420.f));
		m_bMakeBullet = false;
	}
	/*if (m_bFianlAttack &&m_eCurState == ST_FINALINTRO && m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_pFrameKey = L"Flower_FianlAttack";
 		m_eCurState = ST_FINALATTACK;
		Motion_Change();
	}*/

	//if (m_bFianlAttack)
	//{
	//	m_pFrameKey = L"Flower_FianlAttack";
	//	m_eCurState = ST_FINALATTACK;
	//	Motion_Change();
	//	Move_Frame();
	//}
	/*if (iBulletCnt >= 5 && m_bBullet)
	{
		m_bIdle = true;
		m_bBullet = false;
	}
*/

	
	

	Motion_Change();
	Move_Frame();

	Update_Rect_Image();
	

	return OBJ_NOEVENT;
}

void CFlower::Late_Update(void)
{
	/*if (m_eCurState == ST_ATTACK && m_tFrame.iFrameStart == 10)
	{
		m_tFrame.dwFrameSpeed = 130.f;
		if (m_tFrame.iFrameStart == 16)
		{
			if(m_tFrame.dwFrameSpeed >=50)
				m_tFrame.dwFrameSpeed -= 50.f;
		}
			
	
	}*/


	

	
}

void CFlower::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	/*Rectangle(hDC,
		m_tImageRect.left,
		m_tImageRect.top,
		m_tImageRect.right,
		m_tImageRect.bottom);
*/
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
		RGB(0, 54, 54));	// 11인자 : 제거할 색상 

	if (m_bIntro)
		m_bIntro = false;

	if (m_bIdle)
		m_bIdle = false;


		
}

void CFlower::Release(void)
{
}

void CFlower::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_INTRO:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 20;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 18;
			m_tFrame.dwFrameSpeed =60;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		case ST_ATTACK:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 28;
			m_tFrame.dwFrameSpeed = 80;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_BULLET:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 25;
			m_tFrame.dwFrameSpeed = 80;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_FINALINTRO:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 27;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_FINALATTACK:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 22;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_DEATH:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
