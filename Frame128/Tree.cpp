#include "stdafx.h"
#include "Tree.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CTree::CTree()
{
}


CTree::~CTree()
{
}

void CTree::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Overworld/overworld_tree_2.bmp", L"OverWorld_Tree");

	m_tInfo.fCX = 711;
	m_tInfo.fCY = 654;

	m_eRender = RENDER_TREE;
}

void CTree::Render(HDC hdc)
{
	CScrollMgr::Get_Instance()->Scroll_Lock_stage();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"OverWorld_Tree");
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hdc,
		iScrollX, // 2, 3인자 : 복사 받을 위치 X,Y 좌표
		iScrollY,
		(int)m_tInfo.fCX,	// 4,5인자 : 복사 받을 X,Y 길이
		(int)m_tInfo.fCY,
		hMemDC,
		0,
		0,
		(int)m_tInfo.fCX,		// 9. 10인자 : 복사할 비트맵의 X,Y 사이즈
		(int)m_tInfo.fCY,
		RGB(99, 92, 99));	// 11인자 : 제거할 색상 
}

void CTree::Late_Update()
{
}

void CTree::Release()
{
}

int CTree::Update()
{
	return OBJ_NOEVENT;
}
