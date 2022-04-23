#include "stdafx.h"
#include "Garden.h"
#include "BmpMgr.h"
#include "LineMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "SPlayer.h"
#include "Ready.h"
#include "SceneMgr.h"
#include "Mushroom.h"
#include "Flower.h"
#include "Victory.h"
#include "SoundMgr.h"
#include "CollisionMgr.h"
#include "Number.h"
#include "Number3.h"
#include "Stage.h"


CGarden::CGarden()
	:iCnt(0), g_fSound(0.5f), iCnt2(0),m_fTime(0.f)
{
}


CGarden::~CGarden()
{
	Release();
}

void CGarden::Initialize(void)
{
	//CSoundMgr::Get_Instance()->StopSound(SOUND_MAIN);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/²É.wav", SOUND_BGM, g_fSound);

	CLineMgr::Get_Instance()->Load_Data3();

	CObjMgr::Get_Instance()->AddObject(OBJ_BACKGROUND, CAbstractFactory<CMushroom>::Create(70.f, 343.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_BACKGROUND, CAbstractFactory<CMushroom>::Create(250.f, 333.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_BACKGROUND, CAbstractFactory<CMushroom>::Create(400.f, 360.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_FLOWER, CAbstractFactory<CFlower>::Create());
	CObjMgr::Get_Instance()->AddObject(OBJ_SPLAYER, CAbstractFactory<CSPlayer>::Create());
	
	

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage03/Background.bmp", L"stage03BackGround");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stageclear_2.bmp", L"stageclear");
	
	


	dynamic_cast<CSPlayer*>(CObjMgr::Get_Instance()->Get_SPlayer())->Set_Bullet(CObjMgr::Get_Instance()->Get_Bullet());
	dynamic_cast<CSPlayer*>(CObjMgr::Get_Instance()->Get_SPlayer())->Set_Intro();
	dynamic_cast<CSPlayer*>(CObjMgr::Get_Instance()->Get_SPlayer())->Set_Camera(false);

	CObjMgr::Get_Instance()->AddObject(OBJ_BACKGROUND, CAbstractFactory<CReady>::Create(400.f, 320.f));
}

void CGarden::Update(void)
{
	
	CSoundMgr::Get_Instance()->PlaySound(L"²É.wav", SOUND_BGM, g_fSound);



	if (GetAsyncKeyState('X'))
	{
		Release();
		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
		CStage::m_bHidden = true;
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE);

		return;
	}

	CObjMgr::Get_Instance()->Update();

}

void CGarden::Late_Update(void)

{
	CObjMgr::Get_Instance()->Late_Update();

	if (CObjMgr::Get_Instance()->Get_Flower_Size() == 0)
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
		m_fTime += 1.f;
		if (m_fTime >= 60)
		{
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CNumber3>::Create(400, 350));
			iCnt2 = 0.f;
		}
	}
		
}

void CGarden::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"stage03BackGround");
	HDC		hFrontMemDC = CBmpMgr::Get_Instance()->Find_Image(L"stageclear");

	BitBlt(hDC,
		0, 0,
		WINCX,
		WINCY,
		hMemDC,
		0,
		0,
		SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
	//CLineMgr::Get_Instance()->Render(hDC);
	//if (iCnt2 == 1)
	//{



	//	BitBlt(hDC,
	//		200, 100,
	//		400,
	//		400,
	//		hFrontMemDC,
	//		0,
	//		0,
	//		SRCCOPY);

	//	TCHAR	szBuff[32] = L"";		//¸ó½ºÅÍ¸ÂÀºÈ½¼ö


	//	swprintf_s(szBuff, L"%d", (CCollisionMgr::Stage03Hit) /60);
	//	TextOut(hDC, 400, 350, szBuff, lstrlen(szBuff));

	//}

	
}

void CGarden::Release(void)
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CSoundMgr::Get_Instance()->StopSound(SOUND_FLOWER);
	//CSoundMgr::Get_Instance()->Destroy_Instance();
	//OBJ_COLLISION,OBJ_ACORN, OBJ_FBULLET, OBJ_CLONG,OBJ_CSHORT
	CObjMgr::Get_Instance()->Delete_ID(OBJ_SPLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BULLET);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BACKGROUND);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_COIN);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_FLOWER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_FBULLET);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_CLONG);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_CSHORT);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_ACORN);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_SEED);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_VENES);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_COLLISION);

	CLineMgr::Get_Instance()->Destroy_Instance();
}
