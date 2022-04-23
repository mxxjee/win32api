#include "stdafx.h"
#include "SPlayer.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "LineMgr.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Coin.h"
#include "BulletEffect.h"
#include "JumpEffect.h"
#include "PlayerHit.h"
#include "Overwalk.h"
#include "SoundMgr.h"
#include "Stagewalk.h"

CSPlayer::CSPlayer()
	: m_bJump(false), m_fJumpTime(0.f), m_fPower(0.f), m_bCamera(false), m_bStand(false),
	m_bDown(false),m_fTime(0.f), m_bLeft(false), m_bIntro(true), m_bDownFrame(false), m_bHit(false), iHit(0), m_bJumpEffect(false),iHitCnt(1)
	, iEffectCnt(0), iBulletCnt(0),m_bDash(false),iDashCnt(0),m_bRight(false),m_bLeft2(false),m_fRightTime(0.f),m_fLeftTime(0.f),
	m_fDeathTime(0.f),m_bDeath(false)
	
{
}


CSPlayer::~CSPlayer()
{
	Release();
}

void CSPlayer::Initialize(void)
{
	g_fSound = 1.f;

	iBulletCnt = 0;

	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/점프.wav", SOUND_EFFECT, g_fSound);
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/총쏘기.wav", SOUND_EFFECT, g_fSound);
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/인트로.wav", SOUND_EFFECT, g_fSound);
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/맞았을때.wav", SOUND_EFFECT, g_fSound);
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 500.f;

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_fSpeed = 5.f;
	m_fDiagonal = 100.f;

	m_fPower = 20.f;

	
	iHp = 30;

	m_eRender = RENDER_OBJ;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerIdle.bmp", L"SPlayer_Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/DuckIdle.bmp", L"SPlayer_Duck");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Jump.bmp", L"SPlayer_Jump");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Run3.bmp", L"SPlayer_Run");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Groundhit.bmp", L"SPlayer_hit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/UpShoot.bmp", L"SPlayer_UpShot");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Shootaim.bmp", L"SPlayer_Shoot");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/RunShoot.bmp", L"SPlayer_RunShoot");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Intro.bmp", L"SPlayer_Intro");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Groundhit.bmp", L"SPlayer_Hit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Run_Left3.bmp", L"SPlayer_LeftRun");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/RunShoot_Left.bmp", L"SPlayer_RunShootleft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Dash_Right.bmp", L"Dash_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Death.bmp", L"Death");

	CObjMgr::Get_Instance()->AddObject(OBJ_COIN, CAbstractFactory<CCoin>::Create(30.f, 550.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_COIN, CAbstractFactory<CCoin>::Create(100.f, 550.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_COIN, CAbstractFactory<CCoin>::Create(170.f, 550.f));

	m_pFrameKey = L"SPlayer_Idle";
	m_eCurState = ST_INTRO;
	m_ePreState = ST_END;

	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 4;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CSPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (iHitCnt == 1)
	{
		iHitCnt = 0;
	}

	Key_Input();

	if(!m_bDeath)
		Jumping();


	if (m_bHit)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"맞았을때.wav", SOUND_EFFECT, 0.5);
		
		++iHit;
		++iEffectCnt;
		m_pFrameKey = L"SPlayer_hit";
		m_eCurState = ST_HIT;
		++iHitCnt;
		
			
	}


	if (iHitCnt == 1)
	{
		//CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CPlayerHit>::Create(m_tInfo.fX + iScrollX, m_tInfo.fY + iScrollY - 50.f));
		//iHitCnt = 0;
	}
	if (m_eCurState == ST_HIT)
	{
		//CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CPlayerHit>::Create(m_tInfo.fX + iScrollX, m_tInfo.fY + iScrollY));
	}

	if (iDashCnt >= 2)
	{
		m_pFrameKey = L"Dash_Right";
		m_eCurState = ST_RIGTHDASH;
		m_fSpeed = 8.f;
		iDashCnt = 0;
		Motion_Change();
	}

	if (m_eCurState == ST_DEATH)
	{
		
		m_bDeath = true;
		Motion_Change();
		
		
		
	}

	/*if (m_bDeath)
	{
		m_tInfo.fY -= 10.f;
		m_fDeathTime += 1.f;

		if (m_fDeathTime >= 180)
		{
			Set_Dead();
			m_fDeathTime = 0.f;
			m_bDeath = false;
		}
	}
*/
	Motion_Change();
	Move_Frame();
	
	


	Update_Rect();

	return OBJ_NOEVENT;
}

void CSPlayer::Late_Update(void)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_bCamera == false)
	{
		if (m_tInfo.fX >= WINCX)
		{
			m_tInfo.fX -= m_fSpeed;
		}

		if (m_tInfo.fX <= 0)
		{
			m_tInfo.fX += m_fSpeed;
		}
	}
	

	if (!m_bDown)
	{

		if (m_tInfo.fCY < 100.f)
		{
			m_tInfo.fY -= 10.f;
			m_tInfo.fCY += 20.f;
		}

	}

	if (m_bDownFrame)
	{
		m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
		m_bDownFrame = false;
	}

	if (iHit == 1 && !CObjMgr::Get_Instance()->Get_Coin()->empty())
	{
		CObjMgr::Get_Instance()->Get_Coin()->pop_back();

	}



	if (m_bHit)
	{
		m_bHit = false;
		
	}

	

	/*if (m_fJumpTime == 0 && m_bJumpEffect)
	{
		m_bJumpEffect = false;
		CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CJumpEffect>::Create(m_tInfo.fX + iScrollX, m_tInfo.fY + iScrollY + 50.f));

	}*/
		
	if (m_eCurState == ST_LEFTSHOOT || m_eCurState == ST_LEFTRUNSHOT || m_eCurState == ST_RIGHTRUNSHOT ||
		m_eCurState == ST_RIGHTSHOOT || m_eCurState == ST_UPSHOT)
	{
		++iBulletCnt;
	}

	
}

void CSPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//Rectangle(hDC,
	//	m_tRect.left+ iScrollX,
	//	m_tRect.top + iScrollY,
	//	m_tRect.right + iScrollX,
	//	m_tRect.bottom+ iScrollY);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX, // 2, 3인자 : 복사 받을 위치 X,Y 좌표
		(int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,	// 4,5인자 : 복사 받을 X,Y 길이
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9. 10인자 : 복사할 비트맵의 X,Y 사이즈
		(int)m_tInfo.fCY,
		RGB(99, 92, 99));	// 11인자 : 제거할 색상 


	if (m_bCamera)
		CScrollMgr::Get_Instance()->Set_Target(this);

	if (m_bIntro)
		m_bIntro = false;

	if(!m_bHit)
		iHit = 0;

	if (iDashCnt == 0)
		m_fSpeed = 5.f;

}

void CSPlayer::Release(void)
{
}

void CSPlayer::Key_Input()
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//위로 샷 발사 
	if (GetAsyncKeyState(VK_UP))
	{
		
		m_bJumpEffect = false;
		m_fTime += 1.f;
		CSoundMgr::Get_Instance()->PlaySound(L"총쏘기2.wav", SOUND_BULLET, 0.2);
		//++iBulletCnt;
		if (m_fTime >= 15)
		{
			
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CBulletEffect>::Create(m_tInfo.fX + iScrollX , m_tInfo.fY + iScrollY - 50.f));
			m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX + iScrollX, m_tInfo.fY + iScrollY - 30.f, UP));
			
		}

	
		m_bLeft = false;
		m_pFrameKey = L"SPlayer_UpShot";
		m_eCurState = ST_UPSHOT;
	}
	
	if (m_fTime >= 15)
		m_fTime = 0;
	

	//오른쪽 가만히
	else if (CKeyMgr::Get_Instance()->Key_Up(VK_RIGHT))
	{
		
		m_bJumpEffect = false;
		m_bLeft = false;
		m_pFrameKey = L"SPlayer_Idle";
		m_eCurState = ST_IDLERIGHT;

	}

	//왼쪽 가만히
	else if (CKeyMgr::Get_Instance()->Key_Up(VK_LEFT)||CKeyMgr::Get_Instance()->Key_Down(VK_LEFT))
	{
		m_bJumpEffect = false;
		m_bLeft = true;
		m_pFrameKey = L"SPlayer_Idle";
		m_eCurState = ST_IDLELEFT;
	}




	//왼쪽으로 달릴때
	else if (GetAsyncKeyState(VK_LEFT))
	{
		m_bLeft2 = true;
		m_bJumpEffect = false;
		m_tInfo.fX -= m_fSpeed;
		m_pFrameKey = L"SPlayer_LeftRun";
		m_eCurState = ST_WALKLEFT;
		//Motion_Change();

		if (m_bLeft2 && !m_bJump)
		{
			m_fLeftTime += 1.f;
			if (5.f <= m_fLeftTime)
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CStagewalk>::Create(m_tInfo.fX + 50.f, m_tInfo.fY + 30.f));
				m_bLeft2 = false;
				m_fLeftTime = 0.f;
			}
		}
		

		if ((GetAsyncKeyState(VK_SPACE)))
		{
			CSoundMgr::Get_Instance()->PlaySound(L"점프.wav", SOUND_EFFECT, g_fSound);
			m_bJumpEffect = false;
			m_bJump = true;
			m_fPower = 16.f;
			m_fOriginY = m_tInfo.fY;
			m_pFrameKey = L"SPlayer_Jump";
			m_eCurState = ST_JUMPLEFT;
			return;
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_bJumpEffect = false;
			m_bDown = true;
			m_pFrameKey = L"SPlayer_Duck";
			m_eCurState = ST_LEFTDOWN;
		}

		//왼쪽 샷
		else if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
		{
		
			m_bJumpEffect = false;
			m_bLeft = true;
			CSoundMgr::Get_Instance()->PlaySound(L"총쏘기2.wav", SOUND_BULLET, 0.2);
			//++iBulletCnt;
			m_fTime += 1.f;
			if (m_fTime >= 15.f)
			{
				
				CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CBulletEffect>::Create(m_tInfo.fX + iScrollX - 50.f, m_tInfo.fY + iScrollY));
				m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX + iScrollX - 30.f, m_tInfo.fY + iScrollY, LEFT));
			}
			
			m_pFrameKey = L"SPlayer_RunShootleft";
			m_eCurState = ST_LEFTRUNSHOT;
			return;
		}

		if (m_fTime >= 15.f)
			m_fTime = 0.f;

		
	}

	//그냥 쏠때 (왼쪽)
	else if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
		
		m_bLeft = true;
		m_bJumpEffect = false;
		m_fTime += 1.f;
		CSoundMgr::Get_Instance()->PlaySound(L"총쏘기2.wav", SOUND_BULLET, 0.2);
		if (m_fTime >= 15.f)
		{
			
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CBulletEffect>::Create(m_tInfo.fX + iScrollX - 50.f, m_tInfo.fY + iScrollY));
			m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX + iScrollX - 30.f, m_tInfo.fY + iScrollY, LEFT));
		}
		////++iBulletCnt;
		m_pFrameKey = L"SPlayer_Shoot";
		m_eCurState = ST_LEFTSHOOT;
		return;
	}

	if (m_fTime >= 15.f)
		m_fTime = 0.f;

	//그냥쏠때(오른쪽)
	else if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
		
		m_bJumpEffect = false;
		m_bLeft = false;
		m_fTime += 1.f;
		CSoundMgr::Get_Instance()->PlaySound(L"총쏘기2.wav", SOUND_BULLET, 0.2);
		if (m_fTime >= 15.f)
		{
			
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CBulletEffect>::Create(m_tInfo.fX + iScrollX + 50.f, m_tInfo.fY + iScrollY));
			m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX + iScrollX + 30.f, m_tInfo.fY + iScrollY, RIGHT));
		}
		//++iBulletCnt;
		m_pFrameKey = L"SPlayer_Shoot";
		m_eCurState = ST_RIGHTSHOOT;
		return;
	}
	if (m_fTime >= 15.f)
		m_fTime = 0.f;

	//오른쪽으로 달릴때
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		m_bRight = true;
		//++iDashCnt;
		m_bJumpEffect = false;
		m_bLeft = false;
		m_tInfo.fX += m_fSpeed;
		m_pFrameKey = L"SPlayer_Run";
		m_eCurState = ST_WALKRIGHT;
		if (m_bRight && m_bJump==false)
		{
			m_fRightTime += 1.f;
			if (m_fRightTime >= 5.f)
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CStagewalk>::Create(m_tInfo.fX -50.f, m_tInfo.fY + 30.f ));
				m_bRight = false;
				m_fRightTime = 0.f;
			}
		}

	   if((GetAsyncKeyState(VK_SPACE)))
	   {
		   CSoundMgr::Get_Instance()->PlaySound(L"점프.wav", SOUND_EFFECT, g_fSound);
		   m_bJumpEffect = false;
		   m_bJump = true;
		   m_fPower = 16.f;
		   m_fOriginY = m_tInfo.fY;
		   m_pFrameKey = L"SPlayer_Jump";
		   m_eCurState = ST_JUMPRIGHT;
		   return;
	   }
	   else if (GetAsyncKeyState(VK_DOWN))
	   {
		   m_bJumpEffect = false;
		   m_bDown = true;
		   m_pFrameKey = L"SPlayer_Duck";
		   m_eCurState = ST_RIGHTDOWN;
	   }

	   else if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	   {
		  
		   m_bLeft = false;
		   m_bJumpEffect = false;
		   CSoundMgr::Get_Instance()->PlaySound(L"총쏘기2.wav", SOUND_BULLET, 0.2);
		   if (m_fTime >= 15.f)
		   {
			  
			   CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CBulletEffect>::Create(m_tInfo.fX + iScrollX + 50.f, m_tInfo.fY + iScrollY));
			   m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX + iScrollX + 30.f, m_tInfo.fY + iScrollY, RIGHT));
		   }

		   //++iBulletCnt
		   m_pFrameKey = L"SPlayer_RunShoot";
		   m_eCurState = ST_RIGHTRUNSHOT;
		   return;
	   }

	   if (m_fTime >= 15.f)
		   m_fTime = 0.f;

	}

	else if (GetAsyncKeyState(VK_DOWN))
	{
		m_bJumpEffect = false;
		m_bDown = true;
		m_pFrameKey = L"SPlayer_Duck";
		m_eCurState = ST_RIGHTDOWN;

		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{
			//찌부 스프라이트가 다 돌았을때 불변수를 true로 만들어서 고정
			m_bDownFrame = true;
		}
	}

	
	else if (GetAsyncKeyState(VK_SPACE))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"점프.wav", SOUND_EFFECT, g_fSound);
		m_bJumpEffect = false;
		m_bJump = true;
		m_fPower = 16.f;
		m_fOriginY = m_tInfo.fY;
		m_pFrameKey = L"SPlayer_Jump";
		m_eCurState = ST_JUMPRIGHT;
		
		return;
	}


	
	//인트로
	else if (CKeyMgr::Get_Instance()->Key_Pressing('C'))
	{
		m_bJumpEffect = false;
		m_pFrameKey = L"SPlayer_Intro";
		m_eCurState = ST_INTRO;
		return;
	}

	
	//else if (CKeyMgr::Get_Instance()->Key_Up(VK_RIGHT))
	//{
	//	++iDashCnt;
	//	return;
	//}

	//else if (CKeyMgr::Get_Instance()->Key_(VK_RIGHT))
	//{
	//	++iDashCnt;
	//	return;
	//}
	
	else if (m_bLeft)
		m_eCurState = ST_IDLELEFT;
	
	else
		m_eCurState = ST_IDLERIGHT;

}

void CSPlayer::Motion_Change()
{



	//ST_LEFTSHOOT, 
	//ST_RIGHTSHOOT,
	//ST_RIGHTDOWN, 
	//ST_LEFTDOWN,
	//ST_LEFTHIT,
	//ST_RIGHTHIT,
	//ST_UPSHOT, 
	//ST_JUMPRIGHT,
	//ST_JUMPLEFT


	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLERIGHT:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_IDLELEFT:
			m_tFrame.iFrameMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_WALKRIGHT:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.dwFrameSpeed = 30;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_WALKLEFT:
			m_tFrame.iFrameMotion =0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 14;
			m_tFrame.dwFrameSpeed = 30;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_LEFTSHOOT:
			m_tFrame.iFrameMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			
			break;

		case ST_RIGHTSHOOT:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_JUMPLEFT:
			m_tFrame.iFrameMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 20;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_JUMPRIGHT:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.dwFrameSpeed = 20;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_RIGHTDOWN:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.dwFrameSpeed = 20;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_LEFTDOWN:
			m_tFrame.iFrameMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 12;
			m_tFrame.dwFrameSpeed = 20;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_INTRO:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 26;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_RIGHTRUNSHOT:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 17;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_LEFTRUNSHOT:
			m_tFrame.iFrameMotion =0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 17;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_HIT:
			m_tFrame.iFrameMotion = 1;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 17;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_RIGTHDASH:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_DEATH:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 23;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CSPlayer::Jumping()
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	float fLY;
	float fRY;
	float Info_Left_X = (float)m_tRect.left;
	float Info_Top_Y = (float)m_tRect.top;
	float Info_Right_X = (float)m_tRect.right;
	float Info_Bottom_Y = (float)m_tRect.bottom;

	bool		bLineCol_RX = CLineMgr::Get_Instance()->Collision_Line(Info_Right_X, Info_Bottom_Y, &fRY);
	bool		bLineCol_LX = CLineMgr::Get_Instance()->Collision_Line(Info_Left_X, Info_Bottom_Y, &fLY);
	m_bStand = (bLineCol_RX || bLineCol_LX);

	/*if (m_bStand)
	{*/
		if (m_bJump)
		{

			m_fJumpTime += 0.1f;
			m_tInfo.fY -= (m_fPower * m_fJumpTime - (9.8f * m_fJumpTime * m_fJumpTime) / 2.f);
			if (bLineCol_RX && (fRY <= m_tInfo.fY + (m_tInfo.fCY * 0.5)))
			{
				m_bJump = false;
				m_fJumpTime = 0.f;
				m_tInfo.fY = (float)(fRY - (m_tInfo.fCY*0.5));

			}

			if (bLineCol_LX && (fLY <= m_tInfo.fY + (m_tInfo.fCY * 0.5)))
			{
				m_bJump = false;
				m_fJumpTime = 0.f;
				m_tInfo.fY = (float)(fLY - (m_tInfo.fCY*0.5));
				//CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CJumpEffect>::Create(m_tInfo.fX + iScrollX, m_tInfo.fY + iScrollY));

			}

	

		}
		else
		{
			if (m_bJump)
			{
				m_tInfo.fY -= (m_fPower * m_fJumpTime - (9.8f * m_fJumpTime * m_fJumpTime) / 2.f);
			}
			else
			{
				m_bJump = true;
				m_fPower = 0.f;
				m_fOriginY = m_tInfo.fY;
			}
		}
	}

//}

void CSPlayer::Down()
{
	if (m_bDown)
	{
		if (m_tInfo.fCY > 50.f)
		{
			m_tInfo.fY += 10.f;
			m_tInfo.fCY -= 20.f;
		}
	}


	m_bDown = false;
}

CObj * CSPlayer::Create_Bullet(DIRECTION eDir)
{
	CObj*		pBullet = new CBullet;
	pBullet->Initialize();
	pBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	pBullet->Set_Dir(eDir);

	return pBullet;
}
