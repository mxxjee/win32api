#include "stdafx.h"
#include "DiceKing.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Dice.h"
#include "Heart.h"
#include "Diamond.h"
#include "MonsterHit.h"
#include "SoundMgr.h"
#include "BonBon.h"

CDiceKing::CDiceKing()
	:m_fJumpTime(0.f), m_fPower(0.f),m_fTime(0.f), iCnt(0), m_fOriginSpeed(0.f), m_bIntro(true), m_bAttack(true),m_bIdle(false), m_bDice(true), m_bCard(false),
	iEffectCnt(1)
	, m_fCTime(0.f), m_bDeath(false),iCnt2(0), g_fSound(1.f), m_fBonTime(0.f), iCnt3(1)
{
	//m_tInfo는 충돌처리를 위한 info,
	//m_tImgInfo는 출력을 위한 info
}


CDiceKing::~CDiceKing()
{
}

void CDiceKing::Initialize(void)
{
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/다이스 인트로.wav", SOUND_EFFECT, g_fSound);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/다이스 죽음.wav", SOUND_EFFECT, g_fSound);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Dice/clap_2.bmp", L"Dice_clap");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Dice/death2.bmp", L"Dice_death");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Dice/idle_3.bmp", L"Dice_idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Dice/intro2.bmp", L"Dice_intro");

	

	m_tInfo.fCX = 800.f;
	m_tInfo.fCY = 600.f;

	
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 298.f;

	m_fPower = 5.f;

	m_fSpeed = 5.f;
	m_fOriginSpeed = m_fSpeed;

	iHp = 0;

	m_eRender = RENDER_BACKOBJ;


	m_pFrameKey = L"Dice_intro";
	m_eCurState = ST_INTRO;
	m_ePreState = ST_END;

	
}



int CDiceKing::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
		
		
	m_fTime += 1.f;

	if (m_bDice&&m_fTime >= 330)
	{
		m_bCard = true;
		CObjMgr::Get_Instance()->AddObject(OBJ_DICE, CAbstractFactory<CDice>::Create(m_tInfo.fX, 400.f));
		m_fTime = 0.f;
		iCnt = 2;
	}

	
	if (m_bIntro)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"다이스 인트로.wav", SOUND_MAIN, g_fSound);
		m_pFrameKey = L"Dice_intro";
		m_eCurState = ST_INTRO;

	}
	/*if (iCnt >= 5)
	{
		m_fTime += 1.f;

		if (m_fTime >= 300)
		{
			m_fSpeed = 0;
			m_tInfo.fX += m_fSpeed;
			iCnt = 0;
		}
		
	}*/
		
	if (!m_bIntro && m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_bIdle = true;
		m_pFrameKey = L"Dice_idle";
		m_eCurState = ST_IDLE;
		
	}

	if (m_bAttack && !m_bIntro && m_bIdle && m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
	{
		m_pFrameKey = L"Dice_clap";
		m_eCurState = ST_ATTACK;
		m_bIdle = true;
		
		
			
		
		iCnt = 1;


	}

	//dice king이 죽는 조건
	if (m_bCard&&CObjMgr::Get_Instance()->Get_Dice_Size() == 0)
	{
		//m_tInfo.fY =300.f;
		m_pFrameKey = L"Dice_death";
		m_eCurState = ST_DEATH;
		Motion_Change();
		++iCnt2;
		m_bDeath = true;
		CSoundMgr::Get_Instance()->PlaySound(L"다이스 죽음.wav", SOUND_MAIN, g_fSound);

		if (iEffectCnt == 1)
		{
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CMonsterHit>::Create(m_tInfo.fX, m_tInfo.fY));
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CMonsterHit>::Create(m_tInfo.fX - 30.f, m_tInfo.fY + 30.f));
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CMonsterHit>::Create(m_tInfo.fX + 30.f, m_tInfo.fY + 40.f));
			iEffectCnt = 0;
		}


		if (m_bDeath)
		{
			

			if (iCnt2 ==180)
			{

				m_bCard = false;
				Set_Dead();
			}
			
		}
			
		
	}
	

	if (m_bCard)
	{
		m_fCTime += 1.f;

		if (m_fCTime >= 180)
		{
			//CObjMgr::Get_Instance()->AddObject(OBJ_CARD, CAbstractFactory<CHeart>::Create(10.f, 500.f));
			CObjMgr::Get_Instance()->AddObject(OBJ_CARD, CAbstractFactory<CDiamond>::Create(700.f, 500.f));

			m_fCTime = 0.f;
		}

	}

	if (!m_bDeath)
	{
		m_fBonTime += 1.f;

		if (m_fBonTime >= 360)
		{
			CObjMgr::Get_Instance()->AddObject(OBJ_BONBON, CAbstractFactory<CBonBon>::Create(650.f, 450.f));
			m_fBonTime = 0.f;
		}
	}


	Motion_Change();
	Move_Frame();
	

	Update_Rect();

	return OBJ_NOEVENT;

}

void CDiceKing::Late_Update(void)
{
	//3초마다 생성

	/*if (m_tInfo.fX >= 700 || m_tInfo.fX<= 0)
	{
		m_fSpeed *= (-1);
		m_fOriginSpeed *= (-1);
	}*/



	
}

void CDiceKing::Render(HDC hDC)
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
			RGB(0, 64, 64));	// 11인자 : 제거할 색상 
	

	

	if (m_bIntro)
		m_bIntro = false;

	if (m_bIdle)
		m_bIdle = false;

	if (iCnt == 1)
		m_bAttack = false;

	if (iCnt == 2)
		m_bDice = false;


	
	

}

void CDiceKing::Release(void)
{
}



void CDiceKing::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 33;
			m_tFrame.dwFrameSpeed = 48;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_INTRO:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 47;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_ATTACK:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd =62;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();

			break;


		case ST_DEATH:
			
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 14;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			
			break;
		}
		m_ePreState = m_eCurState;
	}
}
