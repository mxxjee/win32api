#include "stdafx.h"
#include "DiceRoom.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "LineMgr.h"
#include "DiceKing.h"
#include "SPlayer.h"
#include "Victory.h"
#include "SceneMgr.h"
#include "Ready.h"
#include "SoundMgr.h"
#include "CollisionMgr.h"
#include "Number2.h"

CDiceRoom::CDiceRoom()
	:iCnt(0),g_fSound(0.5f),iCnt2(0),m_fTime(0.f)
{
}


CDiceRoom::~CDiceRoom()
{
	Release();
}


void CDiceRoom::Initialize(void)
{
	//CSoundMgr::Get_Instance()->StopSound(SOUND_MAIN);
	CLineMgr::Get_Instance()->Load_Data2();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage02/Background.bmp", L"stage02BackGround");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stageclear_2.bmp", L"stageclear");
	CObjMgr::Get_Instance()->AddObject(OBJ_DICEKING, CAbstractFactory<CDiceKing>::Create());
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, CAbstractFactory<CSPlayer>::Create());
	CObjMgr::Get_Instance()->AddObject(OBJ_BACKGROUND, CAbstractFactory<CReady>::Create(400.f, 300.f));

	dynamic_cast<CSPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Bullet(CObjMgr::Get_Instance()->Get_Bullet());
	dynamic_cast<CSPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Intro();

	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/주사위.wav", SOUND_BGM, g_fSound);

	//dynamic_cast<CSPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Camera(false);
	
}

void CDiceRoom::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"주사위.wav", SOUND_BGM, g_fSound);
	CObjMgr::Get_Instance()->Update();

	if (GetAsyncKeyState('X'))
	{
		Release();
		//CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
		CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE);

		return;
	}
	
}

void CDiceRoom::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

	if (CObjMgr::Get_Instance()->Get_DiceRoom_Size()==0)
	{
		++iCnt;
	}

	//
	if (iCnt == 1)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_BACKGROUND, CAbstractFactory<CVictory>::Create(400.f, 300.f));
		++iCnt2;
	}

	if (iCnt2>=1)
	{
		m_fTime += 1.f;
		if (m_fTime >=60 )
		{
			CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CNumber2>::Create(400, 350));
			m_fTime = 0.f;
			iCnt2 = 0.f;
		}
		
		//iCnt2 = 0;
	}

	
		
}

void CDiceRoom::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"stage02BackGround");
	HDC		hFrontMemDC = CBmpMgr::Get_Instance()->Find_Image(L"stageclear");

	BitBlt(hDC,
		0, 0,
		WINCX,
		WINCY,
		hMemDC,
		0,
		0,
		SRCCOPY);

	//CLineMgr::Get_Instance()->Render(hDC);

	//if (iCnt2 == 1)
	//{



	//	BitBlt(hMemDC,
	//		200, 100,
	//		400,
	//		400,
	//		hFrontMemDC,
	//		0,
	//		0,
	//		SRCCOPY);

	//	TCHAR	szBuff[32] = L"";		//몬스터맞은횟수


	//	swprintf_s(szBuff, L"%d", (CCollisionMgr::Stage02Hit)/60);
	//	TextOut(hDC, 400, 350, szBuff, lstrlen(szBuff));

	//}

	CObjMgr::Get_Instance()->Render(hDC);

}

void CDiceRoom::Release(void)
{
	//CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_DICEKING);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BONBON);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BBULLET);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BACKGROUND);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_DICE);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_CARD);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_COIN);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BULLET);
	CLineMgr::Get_Instance()->Destroy_Instance();
}
