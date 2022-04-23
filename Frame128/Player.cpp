#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "GuideBullet.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Overwalk.h"
#include "Stage.h"
#include "SoundMgr.h"

CPlayer::CPlayer()
	: m_bJump(false), m_fJumpTime(0.f), m_fPower(0.f), m_bCamera(false), m_bStage(false), m_bRight(false),
	iCnt(0), m_bWalkEffect(false), m_fTime(0.f), m_fTime2(0.f), m_fTime3(0.f), m_bLeft(false),
	m_bUp(false),m_bDown(false), m_fTime4(0.f)
{
	ZeroMemory(&m_tPosin, sizeof(POINT));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 350.f;

	m_tInfo.fCX = 103.0625;
	m_tInfo.fCY = 113;

	m_fSpeed = 5.f;
	m_fDiagonal = 100.f;

	m_fPower = 20.f;


	iAttack = 0;
	iHp = 0;

	//eID = OBJ_PLAYER;
	m_eRender = RENDER_OBJ;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Overworld_real.bmp", L"Player_State");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_UP.bmp", L"Player_UP");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LEFT.bmp", L"Player_LEFT");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RIGHT.bmp", L"Player_RIGHT");

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LU.bmp", L"Player_LU");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_LD.bmp", L"Player_LD");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RU.bmp", L"Player_RU");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_RD.bmp", L"Player_RD");

	m_pFrameKey = L"Player_State";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;

	m_tFrame.iFrameMotion = 5;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 9;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();


	

}

int CPlayer::Update(void)
{
	//if (!CObjMgr::Get_Instance()->Get_Effect()->empty())
	//{
	//	CObjMgr::Get_Instance()->Get_Effect()->pop_back();
	//	//iCnt = 0;
	//}

	/*if (iCnt >= 1)
		iCnt = 0;*/

	Key_Input();
	//Jumping();
	Offset();

	if (CStage::iCoinCnt == 10)
	{
		
		
		m_eCurState = ST_JUMP;
		Motion_Change();
	}
	Motion_Change();

	Move_Frame();


	Update_Rect();

	
	

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	if (m_eCurState == ST_JUMP)
		CSoundMgr::Get_Instance()->PlaySound(L"예에.wav", SOUND_EFFECT, 1);

}

void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	

	//Rectangle(hDC,
	//	m_tRect.left + iScrollX,
	//	m_tRect.top + iScrollY,
	//	m_tRect.right + iScrollX,
	//	m_tRect.bottom + iScrollY);

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Player_State");
	

		 

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
		RGB(99, 92,99));	// 11인자 : 제거할 색상 

	if (m_bCamera)
		CScrollMgr::Get_Instance()->Set_Target(this);

	//if (m_bRight)
	//	m_bRight = false;

	

}

void CPlayer::Release(void)
{
	//CBmpMgr::Get_Instance()->Destroy_Instance();
	//CScrollMgr::Get_Instance()->Destroy_Instance();

}

void CPlayer::Key_Input(void)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	float	fY = 0.f;

	if (GetAsyncKeyState(VK_UP))
	{
		m_bUp = true;
		m_tInfo.fY -= m_fSpeed;
		m_pFrameKey = L"Player_UP";
		m_eCurState = ST_UP;

		if (m_bUp)
		{
			m_fTime2 += 1.f;
			if (m_fTime2 >= 10)
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<COverwalk>::Create(m_tInfo.fX , m_tInfo.fY + 50.f));
				m_bUp = false;
				m_fTime2 = 0.f;
			}
		}
		
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_bDown = true;
		m_tInfo.fY += m_fSpeed;
		m_pFrameKey = L"Player_DOWN";
		m_eCurState = ST_DOWN;
		if (m_bDown)
		{
			m_fTime3 += 1.f;
			if (m_fTime3 >= 10)
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<COverwalk>::Create(m_tInfo.fX, m_tInfo.fY - 50.f));
				m_bUp = false;
				m_fTime3 = 0.f;
			}
		}
	}

	else if (GetAsyncKeyState(VK_LEFT))
	{
		m_bLeft = true;
		m_tInfo.fX -= m_fSpeed;
		m_pFrameKey = L"Player_LEFT";
		m_eCurState = ST_WALKLEFT;
		if (m_bLeft)
		{
			m_fTime4 += 1.f;
			if (m_fTime4 >= 10)
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<COverwalk>::Create(m_tInfo.fX + 50.f, m_tInfo.fY));
				m_bLeft = false;
				m_fTime4 = 0.f;
			}
		}
	}
		

	else if (GetAsyncKeyState(VK_RIGHT))
	{
		m_bRight = true;
		m_tInfo.fX += m_fSpeed;
		m_pFrameKey = L"Player_RIGHT";
		m_eCurState = ST_WALKRIGHT;
		if (m_bRight)
		{

			m_fTime += 1.f;
			if (m_fTime >= 10)
			{
				CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<COverwalk>::Create(m_tInfo.fX - 50.f, m_tInfo.fY ));
				m_bRight = false;
				m_fTime = 0.f;
			}
			
			
		}
			
		
	}

	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		/*m_bJump = true;
		m_fOriginY = m_tInfo.fY;*/
		m_eCurState = ST_JUMP;
		return;
	}

	/*else if (CKeyMgr::Get_Instance()->Key_Up(VK_RIGHT))
	{

		iCnt = 0;
	}*/

	
	
	else
		m_eCurState = ST_IDLE;
}

void CPlayer::Jumping(void)
{
	float		fY = 0.f;

	bool		bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	if (m_bJump)
	{
		m_fJumpTime += 0.2f;
		m_tInfo.fY -= m_fPower * m_fJumpTime - (9.8f * m_fJumpTime * m_fJumpTime) / 2.f;

		if (bLineCol && (fY <= m_tInfo.fY))
		{
			m_bJump = false;
			m_fJumpTime = 0.f;
			m_tInfo.fY = fY;
		}
	}

	else if (bLineCol)
		m_tInfo.fY = fY;
}

void CPlayer::Offset(void)
{
	int		iOffSetX = WINCX >> 1;
	int		iOffSetY = WINCY >> 1;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (iOffSetX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	if (iOffSetX  < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	if (iOffSetY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	if (iOffSetY  < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
}

void CPlayer::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 4; 
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_WALKRIGHT:
			m_tFrame.iFrameMotion = 2;
			m_tFrame.iFrameStart = 4;
			m_tFrame.iFrameEnd = 13;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_DOWN:
			m_tFrame.iFrameMotion = 4;
			m_tFrame.iFrameStart = 2;
			m_tFrame.iFrameEnd = 14;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_UP:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 4;
			m_tFrame.iFrameEnd = 15;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_WALKLEFT:
			m_tFrame.iFrameMotion = 6;
			m_tFrame.iFrameStart = 2;
			m_tFrame.iFrameEnd = 14;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_JUMP:
			m_tFrame.iFrameMotion =9;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

template<typename T>
CObj* CPlayer::Create_Bullet(DIRECTION eDir)
{
	CObj*		pBullet = new T;
	pBullet->Initialize();
	pBullet->Set_Pos((float)m_tPosin.x, (float)m_tPosin.y);
	

	return pBullet;
}


