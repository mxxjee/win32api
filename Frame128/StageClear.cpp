#include "stdafx.h"
#include "StageClear.h"
#include "BmpMgr.h"


CStageClear::CStageClear()
{
}


CStageClear::~CStageClear()
{
}

void CStageClear::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stageclear_2.bmp", L"stageclear");
	m_tInfo.fCX = 400.f;
	m_tInfo.fCY = 400.f;

	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;

	m_eRender = RENDER_OBJ;
}

int CStageClear::Update(void)
{
	Update_Rect();
	return OBJ_NOEVENT;
}

void CStageClear::Late_Update(void)
{
}

void CStageClear::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"stageclear");

	GdiTransparentBlt(hDC,
		(int)m_tRect.left , // 2, 3인자 : 복사 받을 위치 X,Y 좌표
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

void CStageClear::Release(void)
{
}
