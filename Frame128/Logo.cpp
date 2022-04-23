#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"


CLogo::CLogo()
	:g_fSound(1.f)
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize(void)
{
	
	

	CObjMgr::Get_Instance()->AddObject(OBJ_CHAR, CAbstractFactory<CCharactor>::Create());
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/title_screen_background.bmp", L"Title");
	
	 CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Logo.wav", SOUND_EFFECT, g_fSound);
	
	
}

void CLogo::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"Logo.wav", SOUND_EFFECT, g_fSound);
	
	CObjMgr::Get_Instance()->Update();
}

void CLogo::Late_Update(void)
{
	

	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);
		return;
	}

	CObjMgr::Get_Instance()->Late_Update();
	
}

void CLogo::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Title");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CLogo::Release(void)
{
	//¿©±â¼­´Â À½¾Ç ²¨Áö¸é¾ÈµÅ¿ä ¸Þ´º±îÁö
	CObjMgr::Get_Instance()->Delete_ID(OBJ_CHAR);
}
