#include "stdafx.h"
#include "Acorn.h"
#include "BmpMgr.h"


CAcorn::CAcorn()
	:m_fTime(0.f), m_bMove(false)
{
}


CAcorn::~CAcorn()
{
}

void CAcorn::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Flower/Acorn.bmp", L"Acorn");
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 3.f;

	m_eRender = RENDER_OBJ;

	m_pFrameKey = L"Acorn";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;


}

int CAcorn::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_fTime += 1.f;
	if (m_fTime >= 120)
	{
		m_bMove = true;
	}

	Motion_Cange();
	Move_Frame();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CAcorn::Late_Update(void)
{
	if (m_bMove)
	{
		m_tInfo.fX -= m_fSpeed;
		m_tInfo.fY += m_fSpeed;
		m_fTime = 0.f;
	}

	if (m_tInfo.fX <= 0 || m_tInfo.fY >WINCY)
		m_bDead =true;

}

void CAcorn::Render(HDC hDC)
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

void CAcorn::Release(void)
{
}

void CAcorn::Motion_Cange()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		}
		m_ePreState = m_eCurState;
	}
}


