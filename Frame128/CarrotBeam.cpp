#include "stdafx.h"
#include "CarrotBeam.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"


CCarrotBeam::CCarrotBeam()
	:g_fSound(1.f)
{
}


CCarrotBeam::~CCarrotBeam()
{
}

void CCarrotBeam::Initialize(void)
{
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/당근빔.wav", SOUND_EFFECT, g_fSound);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Carrot/Carrot_BeamProj.bmp", L"Carrot_Beam");

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_pTarget = CObjMgr::Get_Instance()->Get_Player();

	m_fSpeed = 5.f;

	iAttack = 1;

	m_pFrameKey = L"Carrot_Beam";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;

	
	m_eRender = RENDER_OBJ;
}

int CCarrotBeam::Update(void)
{

	CSoundMgr::Get_Instance()->PlaySound(L"당근빔.wav", SOUND_EFFECT, g_fSound);

	if (m_bDead)
		return OBJ_DEAD;

	float	deltaX = m_tInfo.fX - (m_pTarget)->Get_Info().fX;
	float	deltaY = m_tInfo.fY - (m_pTarget)->Get_Info().fY;

	float Diagonal = sqrt(deltaX*deltaX + deltaY*deltaY);

	deltaX = deltaX / Diagonal;
	deltaY = deltaY / Diagonal;

	m_tInfo.fX -= m_fSpeed* (deltaX);
	m_tInfo.fY -= m_fSpeed* (deltaY);



	Motion_Change();
	Move_Frame();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CCarrotBeam::Late_Update(void)
{
	if (m_tInfo.fX >= 400.f &&m_tInfo.fY >300.f)
	{
		m_tInfo.fY += 20.f;
		m_tInfo.fX += 20.f;
	}


	else if (m_tInfo.fX <= 400.f &&m_tInfo.fY >300.f)
	{
		m_tInfo.fY += 20.f;
		m_tInfo.fX -= 20.f;
	}
		

	if (m_tInfo.fY >= WINCY || m_tInfo.fX <=100.f || m_tInfo.fX >=WINCX)
		Set_Dead();
}

void CCarrotBeam::Render(HDC hDC)
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

}

void CCarrotBeam::Release(void)
{
}

void CCarrotBeam::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}

		m_ePreState = m_eCurState;
	}
}
