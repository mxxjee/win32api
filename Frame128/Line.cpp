#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"

CLine::CLine()
	: m_tInfo()
{
}
CLine::CLine(LINEINFO& tLine)
	:m_tInfo(tLine)
{

}

CLine::CLine(POINTPOS& tLeft, POINTPOS& tRight)
	: m_tInfo(tLeft, tRight)
{

}

CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	MoveToEx(hDC, (int)m_tInfo.tLeftPoint.fX + iScrollX, (int)m_tInfo.tLeftPoint.fY+ iScrollY, nullptr);
	LineTo(hDC, (int)m_tInfo.tRightPoint.fX + iScrollX, (int)m_tInfo.tRightPoint.fY+ iScrollY);
}
