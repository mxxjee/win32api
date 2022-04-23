#include "stdafx.h"
#include "Eat.h"
#include "BmpMgr.h"


CEat::CEat()
{
}


CEat::~CEat()
{
}

void CEat::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/�������ΰ���.bmp", L"Coin_1");

	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;

	m_eRender = RENDER_UI2;
}

int CEat::Update(void)
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CEat::Late_Update(void)
{
}

void CEat::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Coin_1");

	GdiTransparentBlt(hDC,
		(int)m_tRect.left, // 2, 3���� : ���� ���� ��ġ X,Y ��ǥ
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 4,5���� : ���� ���� X,Y ����
		(int)m_tInfo.fCY,
		hMemDC,
		0,
		0,
		(int)m_tInfo.fCX,		// 9. 10���� : ������ ��Ʈ���� X,Y ������
		(int)m_tInfo.fCY,
		RGB(0, 64, 64));	// 11���� : ������ ���� 
}

void CEat::Release(void)
{
}
