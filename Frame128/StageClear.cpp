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
		(int)m_tRect.left , // 2, 3���� : ���� ���� ��ġ X,Y ��ǥ
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

void CStageClear::Release(void)
{
}
