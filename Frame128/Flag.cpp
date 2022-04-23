#include "stdafx.h"
#include "Flag.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"


CFlag::CFlag()
{
}


CFlag::~CFlag()
{
}

void CFlag::Initialize()
{
	m_tInfo.fCX = 74.5f;
	m_tInfo.fCY = 100.f;

	//eID = OBJ_FLAG;

	m_eRender = RENDER_OBJ;


	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 11;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CFlag::Update()
{
	
	Move_Frame();
	Update_Rect();
	
	return OBJ_NOEVENT;
}

void CFlag::Late_Update()
{
	

	//튜토리얼 방으로
	if((CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX >=300 && CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX <= 400)
		&&(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY >= 360 && CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY <= 400))
	{
		if (GetAsyncKeyState('Z'))
		{
			if (!lstrcmp(L"Tutorial", m_pFrameKey))
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_TUTORIAL);
			}
				
			return;
		}
	}


	//양파보스방으로 
	else if ((CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX >= 900 && CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX <= 1000)
		&& (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY >= 600 && CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY <= 800))
	{
		if (GetAsyncKeyState('Z'))
		{
			if (!lstrcmp(L"Stage1", m_pFrameKey))
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE01);
			}

			return;
		}
	}

	//주사위 방으로 

	else if ((CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX >= 1800 && CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX <= 1900)
		&& (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY >= 600 && CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY <= 700))
	{
		if (GetAsyncKeyState('Z'))
		{
			if (!lstrcmp(L"Stage2", m_pFrameKey))
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE02);
			}

			return;
		}
	}

	//꽃 방으로

	else if ((CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX >= 1690 && CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX <= 1780)
		&& (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY >= 400 && CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY <= 500))
	{
		if (GetAsyncKeyState('Z'))
		{
			if (!lstrcmp(L"Stage3", m_pFrameKey))
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE03);
			}

			return;
		}
	}
		


}

	


void CFlag::Render(HDC hdc)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hdc,
		(int)m_tRect.left+ iScrollX, // 2, 3인자 : 복사 받을 위치 X,Y 좌표
		(int)m_tRect.top+iScrollY,
		(int)m_tInfo.fCX,	// 4,5인자 : 복사 받을 X,Y 길이
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9. 10인자 : 복사할 비트맵의 X,Y 사이즈
		(int)m_tInfo.fCY,
		RGB(99, 92, 99));	// 11인자 : 제거할 색상 
}



void CFlag::Release()
{

}


