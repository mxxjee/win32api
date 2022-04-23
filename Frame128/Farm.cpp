#include "stdafx.h"
#include "Farm.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "SPlayer.h"
#include "Potato.h"
#include "LineMgr.h"
#include "Onion.h"
#include "Ready.h"
#include "Victory.h"
#include "SoundMgr.h"
#include "CollisionMgr.h"
#include "Number.h"
#include "PauseButton.h"


CFarm::CFarm()
	:iCnt(0),g_fSound(0.5f), iCnt2(0),m_fTime(0.f),iCnt3(0), m_fTime2(0.f)
{
}


CFarm::~CFarm()
{
	Release();
}

void CFarm::Initialize(void)
{
	//CSoundMgr::Get_Instance()->StopSound(SOUND_MAIN);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/³óÀå.wav", SOUND_BGM, g_fSound);
	CLineMgr::Get_Instance()->Load_Data2();


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage01/Background.bmp", L"stage01BackGround");
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stageclear_2.bmp", L"stageclear");


	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, CAbstractFactory<CSPlayer>::Create(200, 500, NULL));
	CObjMgr::Get_Instance()->AddObject(OBJ_POTATO, CAbstractFactory<CPotato>::Create(700.f,450.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_BACKGROUND, CAbstractFactory<CReady>::Create(400.f, 300.f));

	
	dynamic_cast<CSPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Bullet(CObjMgr::Get_Instance()->Get_Bullet());
	dynamic_cast<CSPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Intro();
	dynamic_cast<CSPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Camera(false);


	//CObj*		pPause = CAbstractFactory<CPauseButton>::Create(70.f, 50.f);
	//pPause->Set_FrameKey(L"Pause");
	//CObjMgr::Get_Instance()->AddObject(OBJ_BUTTON, pPause);
}

void CFarm::Update(void)
{
	

	CSoundMgr::Get_Instance()->PlaySound(L"³óÀå.wav", SOUND_BGM, g_fSound);
	CObjMgr::Get_Instance()->Update();

	

	if (GetAsyncKeyState('X'))
	{
		Release();
		
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE);
	
		return;
	}

	
	/*if (CObjMgr::Get_Instance()->Get_Coin()->empty())
	{
		dynamic_cast<CSPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_State();
		dynamic_cast<CSPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_FrameKey();
	}*/

}

void CFarm::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

	//if (dynamic_cast<CPotato*>(CObjMgr::Get_Instance()->Get_Potato())->Get_Dead())
	//{
	//	CObjMgr::Get_Instance()->AddObject(OBJ_ONION, CAbstractFactory<COnion>::Create());
	//	dynamic_cast<COnion*>(CObjMgr::Get_Instance()->Get_Onion())->Set_Bullet(CObjMgr::Get_Instance()->Get_OBullet());
	//}

	//dynamic_cast<COnion*>(CObjMgr::Get_Instance()->Get_Onion())->Set_Bullet(CObjMgr::Get_Instance()->Get_OBullet());

	if (CObjMgr::Get_Instance()->Get_Size() == 0)
	{
		++iCnt;
	}

	if (iCnt == 1)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_BACKGROUND, CAbstractFactory<CVictory>::Create(400.f, 300.f));
		
		++iCnt2;
		
	}

	if (iCnt2 >= 1)
	{
		m_fTime2 += 1.f;
		if (m_fTime2 >= 60)
		{
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CNumber>::Create(400, 350));
			iCnt2 = 0;
		}
		
	}
		
		
}

void CFarm::Render(HDC hDC)
{
	//L"stageclear"
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"stage01BackGround");
	//HDC		hFrontMemDC = CBmpMgr::Get_Instance()->Find_Image(L"stageclear");

	BitBlt(hDC,
		0, 0,
		WINCX,
		WINCY,
		hMemDC,
		0,
		0,
		SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);

	if (iCnt2 == 1)
	{
	
	

		

		//TCHAR	szBuff[32] = L"";		//¸ó½ºÅÍ¸ÂÀºÈ½¼ö


		/*swprintf_s(szBuff, L"%d", (CCollisionMgr::Stage01Hit)/60);
		TextOut(hDC, 400,350, szBuff, lstrlen(szBuff));*/

	}
	

	//CLineMgr::Get_Instance()->Render(hDC);
}

void CFarm::Release(void)
{
	//CSoundMgr::Get_Instance()->Destroy_Instance();
	//CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	//CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);

	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BULLET);

	CObjMgr::Get_Instance()->Delete_ID(OBJ_PBULLET);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_POTATO);

	CObjMgr::Get_Instance()->Delete_ID(OBJ_CARROT);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_CBULLET);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_CARROTBEAM);

	CObjMgr::Get_Instance()->Delete_ID(OBJ_ONION);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_OBULLET);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BACKGROUND);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BUTTON);

	CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_COIN);
	CLineMgr::Get_Instance()->Destroy_Instance();


}
