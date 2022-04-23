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

	//ó�������� ==�������� �Ǹ� set_dead()�� ���� �� ��ȯ


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
