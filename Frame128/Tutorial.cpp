#include "stdafx.h"
#include "Tutorial.h"
#include "BmpMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "SPlayer.h"
#include "SceneMgr.h"
#include "Bullet.h"
#include "SoundMgr.h"

CTutorial::CTutorial()
{
}

CTutorial::~CTutorial()
{
	Release();
}

void CTutorial::Initialize(void)
{
	g_fSound = 1.f;

	CSoundMgr::Get_Instance()->StopSound(SOUND_MAIN);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/튜토리얼.wav", SOUND_BGM, g_fSound);

	CLineMgr::Get_Instance()->Load_Data1();


	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, CAbstractFactory<CSPlayer>::Create());



	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tutorial/Tutorial_BackGround.bmp", L"TutorialBack");





	////카메라가 플레이어를 따라가도록하게한다.
	dynamic_cast<CSPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Bullet(CObjMgr::Get_Instance()->Get_Bullet());
	dynamic_cast<CSPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Camera(true);






}

void CTutorial::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"튜토리얼.wav", SOUND_BGM, g_fSound);
	CObjMgr::Get_Instance()->Update();

}

void CTutorial::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

	if ((CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX >= 1847 && CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX <= 1967)
		&& (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY >= 556 && CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY <= 648))
	{
		if (GetAsyncKeyState('Z'))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE);

		}
		return;
	}


}

void CTutorial::Render(HDC hDC)
{

	CScrollMgr::Get_Instance()->Scroll_Lock();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"TutorialBack");

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC,
		iScrollX, iScrollY,
		2000,
		720,
		hMemDC,
		0,
		0,
		SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
	//CLineMgr::Get_Instance()->Render(hDC);



}

void CTutorial::Release(void)
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_MAIN);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BULLET);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_COIN);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);

	CLineMgr::Get_Instance()->Destroy_Instance();

}


