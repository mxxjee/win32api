#include "stdafx.h"
#include "MainGame.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"

bool m_bPause = false;

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

	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	CSceneMgr::Get_Instance()->Scene_Change(SC_LOGO);
	CSoundMgr::Get_Instance()->Initialize();


}

void CMainGame::Update(void)
{
	//마우스로 찍어서 해당 좌표 알아내기
	/*POINT    pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	float fX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fY = CScrollMgr::Get_Instance()->Get_ScrollY();
	cout << pt.x - fX << "\t" << pt.y  << endl;*/

	if (!m_bPause)
	{
		CSceneMgr::Get_Instance()->DeletePreScene();

		CSceneMgr::Get_Instance()->Update();
	}
	if (GetAsyncKeyState(VK_TAB))
	{
		if (m_bPause)
		{
			m_bPause = false;
		}
	}

	
}

void CMainGame::Late_Update(void)
{
	if (!m_bPause)
	{
		CSceneMgr::Get_Instance()->Late_Update();
		CScrollMgr::Get_Instance()->Late_Update();
	}

	
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

	BitBlt(m_DC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);

	if(!m_bPause)
		CSceneMgr::Get_Instance()->Render(hBackDC);

}

void CMainGame::Release(void)
{
	
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CSceneMgr::Get_Instance()->Destroy_Instance();
	CSoundMgr::Get_Instance()->Destroy_Instance();



	ReleaseDC(g_hWnd, m_DC);
}
