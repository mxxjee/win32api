#include "stdafx.h"
#include "MainGame.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "EditMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"


CMainGame::CMainGame()
	: m_dwTime(GetTickCount()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Overworld/overworld.bmp", L"Back");
	//CLineMgr::Get_Instance()->Initialize();
	

}

void CMainGame::Update(void)
{
	CScrollMgr::Get_Instance()->Update();
	//CLineMgr::Get_Instance()->Update();
	CEditMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	HDC		hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");

	int ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int Scrolly = CScrollMgr::Get_Instance()->Get_Scrolly();


	BitBlt(m_DC, ScrollX, Scrolly, 1920, 1080, hBackDC, 0, 0, SRCCOPY);

	CEditMgr::Get_Instance()->Render(m_DC);
	CObjMgr::Get_Instance()->Render(m_DC);
	//CLineMgr::Get_Instance()->Render(m_DC);
}

void CMainGame::Release(void)
{
	
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	//CLineMgr::Get_Instance()->Destroy_Instance();
	CEditMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);
}