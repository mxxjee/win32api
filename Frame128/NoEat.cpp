#include "stdafx.h"
#include "NoEat.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CNoEat::CNoEat()
{
}


CNoEat::~CNoEat()
{
}

void CNoEat::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/남은코인개수.bmp", L"Coin_2");

	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;

	m_eRender = RENDER_UI2;


}

int CNoEat::Update(void)
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CNoEat::Late_Update(void)
{
}

void CNoEat::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Coin_2");

	GdiTransparentBlt(hDC,
		(int)m_tRect.left, // 2, 3인자 : 복사 받을 위치 X,Y 좌표
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 4,5인자 : 복사 받을 X,Y 길이
		(int)m_tInfo.fCY,
		hMemDC,
		0,
		0,
		(int)m_tInfo.fCX,		// 9. 10인자 : 복사할 비트맵의 X,Y 사이즈
		(int)m_tInfo.fCY,
		RGB(0, 64, 64));	// 11인자 : 제거할 색상 
}

void CNoEat::Release(void)
{
}
