#include "stdafx.h"
#include "Venes.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

CVenes::CVenes()
	:m_bDeath(false)
{
}


CVenes::~CVenes()
{
}

void CVenes::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Flower/Venes.bmp", L"Venes");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Flower/Venes_Death.bmp", L"Venes_Death");

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_pTarget = CObjMgr::Get_Instance()->Get_SPlayer();

	m_fSpeed = 2.f;

	m_eRender = RENDER_OBJ;

	m_pFrameKey = L"Venes";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;
}

int CVenes::Update(void)
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

	if (m_bDeath)
	{
		
		m_eCurState = ST_DEATH;
		m_pFrameKey = L"Venes_Death";
		Motion_Change();
		//CSoundMgr::Get_Instance()->PlaySound(L"당근부서짐.wav", SOUND_EFFECT, g_fSound);
		if (m_tFrame.iFrameStart == m_tFrame.iFrameEnd)
		{

			Set_Dead();

		}
	}

	Motion_Change();
	Move_Frame();

	Update_Rect();
	return OBJ_NOEVENT;
}

void CVenes::Late_Update(void)
{
}

void CVenes::Render(HDC hDC)
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
}

void CVenes::Release(void)
{
}

void CVenes::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		case ST_DEATH:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 13;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		}
		m_ePreState = m_eCurState;
	}
}
