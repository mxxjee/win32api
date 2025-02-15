#include "stdafx.h"
#include "Tree3.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CTree3::CTree3()
{
}


CTree3::~CTree3()
{
}

void CTree3::Initialize()
{
	//694.f, 279.f
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Overworld/overworld_tree9.bmp", L"OverWorld_Tree3");

	m_tInfo.fCX = 142.f;
	m_tInfo.fCY = 136.f;

	/*m_tInfo.fX = 800.f;
	m_tInfo.fY = 279.f;*/


	m_eRender = RENDER_TREE;
}

void CTree3::Render(HDC hdc)
{
	CScrollMgr::Get_Instance()->Scroll_Lock_stage();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"OverWorld_Tree3");
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hdc,
		(int)m_tRect.left + iScrollX, // 2, 3인자 : 복사 받을 위치 X,Y 좌표
		(int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,	// 4,5인자 : 복사 받을 X,Y 길이
		(int)m_tInfo.fCY,
		hMemDC,
		0,
		0,
		(int)m_tInfo.fCX,		// 9. 10인자 : 복사할 비트맵의 X,Y 사이즈
		(int)m_tInfo.fCY,
		RGB(99, 92, 99));	// 11인자 : 제거할 색상 
}

void CTree3::Late_Update()
{
}

void CTree3::Release()
{
}

int CTree3::Update()
{
	Update_Rect();
	return OBJ_NOEVENT;
}

