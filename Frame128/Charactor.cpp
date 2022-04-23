#include "stdafx.h"
#include "Charactor.h"
#include "BmpMgr.h"


CCharactor::CCharactor()
{
}


CCharactor::~CCharactor()
{
}

void CCharactor::Initialize(void)
{
	m_tInfo.fCX = 536.4411764705882;
	m_tInfo.fCY = 307.f;

	m_tInfo.fX = 400.f;
	m_tInfo.fY = 500.f;

	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/title_char.bmp", L"Title_Char");

	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 33;
	m_tFrame.dwFrameSpeed = 40;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRender = RENDER_OBJ;

}

int CCharactor::Update(void)
{

	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CCharactor::Late_Update(void)
{

}

void CCharactor::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Title_Char");



	GdiTransparentBlt(hDC,
		(int)m_tRect.left, // 2, 3���� : ���� ���� ��ġ X,Y ��ǥ
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 4,5���� : ���� ���� X,Y ����
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9. 10���� : ������ ��Ʈ���� X,Y ������
		(int)m_tInfo.fCY,
		RGB(255, 43, 213));	// 11���� : ������ ���� 
}

void CCharactor::Release(void)
{
}
