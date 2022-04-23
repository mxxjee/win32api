#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "SoundMgr.h"


CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/MyButton/Start_real.bmp", L"Start");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/MyButton/Options_real.bmp", L"Options");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/MyButton/Exit_real.bmp", L"Exit");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Menu.bmp", L"Menu");

	 //start
	CObj*	pButton = CAbstractFactory<CMyButton>::Create(400.f, 200.f);
	pButton->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->AddObject(OBJ_BUTTON, pButton);
	
	//// start
	//pButton = CAbstractFactory<CMyButton>::Create(400.f, 300.f);
	//pButton->Set_FrameKey(L"Options");
	//CObjMgr::Get_Instance()->AddObject(OBJ_BUTTON, pButton);

	//5 start
	pButton = CAbstractFactory<CMyButton>::Create(400.f,290.f);
	pButton->Set_FrameKey(L"Exit");
	CObjMgr::Get_Instance()->AddObject(OBJ_BUTTON, pButton);

	
}

void CMyMenu::Update(void)
{
	CObjMgr::Get_Instance()->Update();
}

void CMyMenu::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMyMenu::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Menu");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CMyMenu::Release(void)
{
	//CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	//CSoundMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BUTTON);
}
