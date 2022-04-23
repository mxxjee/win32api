#include "stdafx.h"
#include "FlowerBullet.h"
#include "BmpMgr.h"


CFlowerBullet::CFlowerBullet()
{
}


CFlowerBullet::~CFlowerBullet()
{
}

void CFlowerBullet::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Flower/bullet.bmp", L"Flowerbullet");
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_eRender = RENDER_OBJ;

	m_fSpeed = 3.f;

	m_pFrameKey = L"Flowerbullet";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;
}

int CFlowerBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	m_tInfo.fX -= m_fSpeed;

	Motion_Change();
	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CFlowerBullet::Late_Update(void)
{
	if (m_tInfo.fX <= 0)
		m_bDead = true;
}

void CFlowerBullet::Render(HDC hDC)
{
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

void CFlowerBullet::Release(void)
{

}

void CFlowerBullet::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		}
		m_ePreState = m_eCurState;
	}
}
