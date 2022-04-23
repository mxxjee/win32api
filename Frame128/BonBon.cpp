#include "stdafx.h"
#include "BonBon.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "BonBullet.h"
#include "BmpMgr.h"



CBonBon::CBonBon()
	:m_fTime(0.f), m_fTime2(0.f)
{
}


CBonBon::~CBonBon()
{
}

void CBonBon::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Dice/BonBon.bmp", L"BonBon");
	m_tInfo.fX = 650.f;
	m_tInfo.fY = 500.f;

	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;

	m_eRender = RENDER_OBJ;

	m_pFrameKey = L"BonBon";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;
	
}

int CBonBon::Update(void)
{
	if(m_bDead)
		return OBJ_DEAD;


	

	Motion_Change();
	Move_Frame();

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBonBon::Late_Update(void)
{

	m_fTime2 += 1.f;

	if (m_fTime2 >= 190)
	{
		m_bDead = true;
		m_fTime2 = 0.f;
	}

	m_fTime += 1.f;

	if (!m_bDead &&m_fTime >= 60)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_BBULLET, CAbstractFactory<CBonBullet>::Create(650.f, 425.f));
		m_fTime = 0.f;
	}
}

void CBonBon::Render(HDC hDC)
{
	//Rectangle(hDC,
	//	m_tRect.left,
	//	m_tRect.top,
	//	m_tRect.right,
	//	m_tRect.bottom);


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

void CBonBon::Release(void)
{
}

void CBonBon::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 47;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;



		}
		m_ePreState = m_eCurState;
	}
}
