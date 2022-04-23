#include "stdafx.h"
#include "Wall.h"
#include "ScrollMgr.h"


CWall::CWall()
{
}


CWall::~CWall()
{
}

void CWall::Initialize()
{
	eID = OBJ_WALL;
}

void CWall::Render(HDC hdc)
{
	Rectangle(hdc, m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(),
		m_tRect.top + CScrollMgr::Get_Instance()->Get_Scrolly(),
		m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(),
		m_tRect.bottom + CScrollMgr::Get_Instance()->Get_Scrolly());
}

void CWall::Late_Update()
{
}

void CWall::Release()
{
}

int CWall::Update()
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CWall::Collision()
{
}

void CWall::Collision(CObj * Obj)
{
}
