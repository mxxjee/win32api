#include "stdafx.h"
#include "BlueSeed.h"
#include "BmpMgr.h"


CBlueSeed::CBlueSeed()
{
}


CBlueSeed::~CBlueSeed()
{
}

void CBlueSeed::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Flower/Seed_Blue.bmp", L"Seed_Blue");

	m_tInfo.fX = rand() % WINCX;
	m_tInfo.fY = 10;

	m_tImageInfo.fX = m_tInfo.fX;
	m_tImageInfo.fY = 10;

	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_tImageInfo.fCX = 20.f;
	m_tImageInfo.fCY = 20.f;

	m_eRender = RENDER_OBJ;

	m_fSpeed = 2.f;


	m_pFrameKey = L"Seed_Blue";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;

	/*m_pFrameKey = L"short";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;*/
}

int CBlueSeed::Update(void)
{

	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fY += m_fSpeed;
	m_tImageInfo.fY += m_fSpeed;


	Motion_Change();
	Move_Frame();

	Update_Rect_Image();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBlueSeed::Late_Update(void)
{
	if (m_tInfo.fY >= 500)
		Set_Dead();
}

void CBlueSeed::Render(HDC hDC)
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
		(int)m_tRect.left, // 2, 3���� : ���� ���� ��ġ X,Y ��ǥ
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 4,5���� : ���� ���� X,Y ����
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9. 10���� : ������ ��Ʈ���� X,Y ������
		(int)m_tInfo.fCY,
		RGB(0, 64, 64));	// 11���� : ������ ���� 
}

void CBlueSeed::Release(void)
{
}

void CBlueSeed::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 39;
			m_tFrame.dwFrameSpeed = 200;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		}
		m_ePreState = m_eCurState;
	}
}

