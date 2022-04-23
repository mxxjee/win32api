#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_fSpeed(0.f), m_eDir(END), m_bDead(false), m_fAngle(0.f), m_fDiagonal(0.f), m_eRender(RENDER_END), m_pFrameKey(nullptr),
	iAttack(0),iHp(0)
{
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CObj::~CObj()
{
}

void CObj::Update_Rect(void)
{
	m_tRect.left  = long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top   = long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CObj::Update_Rect_Image(void)
{
	m_tImageRect.left = long(m_tImageInfo.fX - (m_tImageInfo.fCX * 0.5f));
	m_tImageRect.top = long(m_tImageInfo.fY - (m_tImageInfo.fCY * 0.5f));
	m_tImageRect.right = long(m_tImageInfo.fX + (m_tImageInfo.fCX * 0.5f));
	m_tImageRect.bottom = long(m_tImageInfo.fY + (m_tImageInfo.fCY * 0.5f));
}

void CObj::Move_Frame(void)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}
