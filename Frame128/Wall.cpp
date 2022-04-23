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
	//eID = OBJ_WALL;
	m_eRender = RENDER_BACKGROUND;
}

void CWall::Render(HDC hdc)
{
	Rectangle(hdc,
		m_tRect.left + CScrollMgr::Get_Instance()->Get_ScrollX(),
		m_tRect.top + CScrollMgr::Get_Instance()->Get_ScrollY(),
		m_tRect.right + CScrollMgr::Get_Instance()->Get_ScrollX(),
		m_tRect.bottom + CScrollMgr::Get_Instance()->Get_ScrollY());
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
