#include "stdafx.h"
#include "Dice.h"
#include "LineMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"

CDice::CDice()
	:m_fJumpTime(0.f), m_fPower(0.f),m_bDeath(false), iCnt(0)
{
}


CDice::~CDice()
{
}

void CDice::Initialize(void)
{

	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/주사위 소리.wav", SOUND_BGM, 1);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Dice/Dice.bmp", L"Dice_Image");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Dice/Dice_Death_2.bmp", L"Dice_Death");


	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_eRender = RENDER_UI;

	m_fPower = 5.f;

	iHp = 35;				//30

	m_fSpeed = 2.f;


	m_pFrameKey = L"Dice_Image";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;


}

int CDice::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"주사위 소리.wav", SOUND_BGM, 1);

	if (m_bDead)
		return OBJ_DEAD;

	if (m_bDeath)
	{
		m_pFrameKey = L"Dice_Death";
		m_eCurState = ST_DEATH;
		Motion_Change();
		++iCnt;
		m_bDeath = true;

		if (m_bDeath)
		{
			if (iCnt == 60)
			{
				Set_Dead();
			}

		}


	}
	m_tInfo.fX += m_fSpeed;
	Jumping();
	
	Motion_Change();
	Move_Frame();


	Update_Rect();

	return OBJ_NOEVENT;
}

void CDice::Late_Update(void)
{
	if (m_tRect.right>=WINCX || m_tRect.left <=0)
		m_fSpeed *= -1.f;
}

void CDice::Render(HDC hDC)
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
		RGB(50, 56, 56));	// 11인자 : 제거할 색상 
}

void CDice::Release(void)
{
}

void CDice::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 23;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		case ST_DEATH:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd =15;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CDice::Jumping()
{
	float fY = 0.f;
	bool  bLineCol = CLineMgr::Get_Instance()->Collision_Line_Ball(m_tInfo.fX, &fY);

	m_fJumpTime += 0.02f;

	m_tInfo.fY -= m_fPower*m_fJumpTime - (5.f* m_fJumpTime*m_fJumpTime)*0.5f;

	if (bLineCol && (fY <= m_tInfo.fY))
	{
		m_fJumpTime = 0.f;
		m_tInfo.fY = fY;
	}
}
