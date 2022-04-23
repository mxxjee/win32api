#include "stdafx.h"
#include "Vines.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Venes.h"

CVines::CVines()
	:m_fTime(0.f)
{
}


CVines::~CVines()
{
}

void CVines::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Flower/Vines.bmp", L"Vines");

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 200.f;

	m_eRender = RENDER_OBJ;

	m_pFrameKey = L"Vines";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;
}

int CVines::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_fTime += 1.f;

	//처음프레임 ==끝프레임 되면 set_dead()와 작은 거 소환


	Motion_Change();
	Move_Frame();

	Update_Rect();
	return OBJ_NOEVENT;
}

void CVines::Late_Update(void)
{
	if (m_fTime >= 120)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_VENES, CAbstractFactory<CVenes>::Create(m_tInfo.fX, m_tInfo.fY - 50.f));
		Set_Dead();
		m_fTime = 0.f;
	}
}

void CVines::Render(HDC hDC)
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

void CVines::Release(void)
{
}

void CVines::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 19;
			m_tFrame.dwFrameSpeed = 100;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		}
		m_ePreState = m_eCurState;
	}
}
