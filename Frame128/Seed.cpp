#include "stdafx.h"
#include "Seed.h"
#include "BmpMgr.h"
#include "Vines.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CSeed::CSeed()
	
{
}


CSeed::~CSeed()
{
}

void CSeed::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Flower/Seed_Red.bmp", L"Seed_Red");

	m_tInfo.fX = rand() % WINCX;
	m_tInfo.fY = 10;

	m_tImageInfo.fX = m_tInfo.fX;
	m_tImageInfo.fY = 10;

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_tImageInfo.fCX = 30.f;
	m_tImageInfo.fCY = 30.f;

	m_eRender = RENDER_OBJ;

	m_fSpeed = 3.2f;


	m_pFrameKey = L"Seed_Red";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;

	/*m_pFrameKey = L"short";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;*/
}

int CSeed::Update(void)
{
	
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fY += m_fSpeed;
	m_tImageInfo.fY += m_fSpeed;

	if (m_tInfo.fY >= 500)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CVines>::Create(m_tInfo.fX, m_tInfo.fY - 50));
		Set_Dead();
	}

	Motion_Change();
	Move_Frame();

	Update_Rect_Image();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CSeed::Late_Update(void)
{
	
		
}

void CSeed::Render(HDC hDC)
{
	//Rectangle(hDC,
	//	m_tRect.left,
	//	m_tRect.top,
	//	m_tRect.right,
	//	m_tRect.bottom);

	////Rectangle(hDC,
	////	m_tImageRect.left,
	////	m_tImageRect.top,
	////	m_tImageRect.right,
	////	m_tImageRect.bottom);

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

void CSeed::Release(void)
{
}

void CSeed::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 40;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		}
		m_ePreState = m_eCurState;
	}
}
