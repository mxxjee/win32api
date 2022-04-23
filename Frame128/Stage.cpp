#include "stdafx.h"
#include "Stage.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "Flag.h"
#include "SoundMgr.h"
#include "Tree.h"
#include "Tree2.h"
#include "Tree3.h"
#include "EventCoin.h"
#include "NoEat.h"
#include "Eat.h"
#include "Number4.h"
#include "Number5.h"
#include "Ending.h"
#include "SceneMgr.h"
#include "PauseButton.h"

bool	CStage::m_bHidden = false;
int		CStage::iCoinCnt = 0;

CStage::CStage()
	:m_fEndTime(0.f)
{
}

CStage::~CStage()
{
	Release();
}

void CStage::Initialize(void)
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	 g_fSound = 0.5f;

	 CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/메인.wav", SOUND_MAIN, g_fSound);
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Overworld/overworld.bmp", L"OverWorld");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/남은코인개수.bmp", L"Coin_2");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/OverWorld/Flag.bmp", L"Tutorial");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/OverWorld/Flag.bmp", L"Stage1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/OverWorld/Flag.bmp", L"Stage2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/OverWorld/Flag.bmp", L"Stage3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Pause.bmp", L"Pause");



	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CTree>::Create());
	CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CTree2>::Create(958.f,350.f));
	CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CTree3>::Create(1530.f, 362.f));

	CObjMgr::Get_Instance()->Loda_Data2(OBJ_WALL);

	//카메라가 플레이어를 따라가도록하게한다.
	dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Camera(true);
	dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Stage(true);

	//튜토리얼로 가기위한 깃발
	CObj*	pFlag = CAbstractFactory<CFlag>::Create(358.f, 354.f);
	pFlag->Set_FrameKey(L"Tutorial");
	CObjMgr::Get_Instance()->AddObject(OBJ_FLAG, pFlag);

	//1스테이지로 가기위한 깃발
	pFlag = CAbstractFactory<CFlag>::Create(904.f, 671.f);
	pFlag->Set_FrameKey(L"Stage1");
	CObjMgr::Get_Instance()->AddObject(OBJ_FLAG, pFlag);

	//2스테이지로 가기위한 깃발
	pFlag = CAbstractFactory<CFlag>::Create(1850.f, 620.f);
	pFlag->Set_FrameKey(L"Stage2");
	CObjMgr::Get_Instance()->AddObject(OBJ_FLAG, pFlag);

	//3스테이지로 가기위한 깃발
	pFlag = CAbstractFactory<CFlag>::Create(1735.f, 439.f);
	pFlag->Set_FrameKey(L"Stage3");
	CObjMgr::Get_Instance()->AddObject(OBJ_FLAG, pFlag);

	//버튼
	CObj*		pPause = CAbstractFactory<CPauseButton>::Create(70.f, 70.f);
	pPause->Set_FrameKey(L"Pause");
	CObjMgr::Get_Instance()->AddObject(OBJ_BUTTON, pPause);


	if (m_bHidden)
	{
		CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CNoEat>::Create(300.f, 50.f));
		CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CEat>::Create(550.f, 45.f));
		CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CNumber4>::Create(300.f, 100.f));
		CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CNumber5>::Create(550.f, 100.f));
		
		//CObjMgr::Get_Instance()->AddObject(OBJ_EVENTCOIN, CAbstractFactory<CEventCoin>::Create(1530.f, 362.f));

		//코인 10개
		CObjMgr::Get_Instance()->AddObject(OBJ_EVENTCOIN, CAbstractFactory<CEventCoin>::Create(917.f, 337.f));
		CObjMgr::Get_Instance()->AddObject(OBJ_EVENTCOIN, CAbstractFactory<CEventCoin>::Create(1488.f, 370.f));
		CObjMgr::Get_Instance()->AddObject(OBJ_EVENTCOIN, CAbstractFactory<CEventCoin>::Create(1230.f, 83.f));
		CObjMgr::Get_Instance()->AddObject(OBJ_EVENTCOIN, CAbstractFactory<CEventCoin>::Create(614.f, 512.f));
		CObjMgr::Get_Instance()->AddObject(OBJ_EVENTCOIN, CAbstractFactory<CEventCoin>::Create(430.f, 424.f));
		CObjMgr::Get_Instance()->AddObject(OBJ_EVENTCOIN, CAbstractFactory<CEventCoin>::Create(1089.f, 186.f));
		CObjMgr::Get_Instance()->AddObject(OBJ_EVENTCOIN, CAbstractFactory<CEventCoin>::Create(1421.f, 118.f));
		CObjMgr::Get_Instance()->AddObject(OBJ_EVENTCOIN, CAbstractFactory<CEventCoin>::Create(400.f, 486.f));
		CObjMgr::Get_Instance()->AddObject(OBJ_EVENTCOIN, CAbstractFactory<CEventCoin>::Create(1757.f, 571.f));
		CObjMgr::Get_Instance()->AddObject(OBJ_EVENTCOIN, CAbstractFactory<CEventCoin>::Create(1059.f, 435.f));

		
	}

}

void CStage::Update(void)
{

	CSoundMgr::Get_Instance()->PlaySound(L"메인.wav", SOUND_MAIN, g_fSound);

	CObjMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();

	if (CStage::iCoinCnt==10)
	{
		//Release();
		m_fEndTime += 1.f;
		
	}
}

void CStage::Late_Update(void)
{


	CObjMgr::Get_Instance()->Late_Update();

	if (m_fEndTime >= 180)
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_MAIN);
		CSceneMgr::Get_Instance()->Scene_Change(SC_ENDING);
		m_fEndTime = 0.f;
		return;
	}

}

void CStage::Render(HDC hDC)
{

	CScrollMgr::Get_Instance()->Scroll_Lock_stage();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"OverWorld");

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC,
		iScrollX, iScrollY,
		1920,
		1080,
		hMemDC,
		0,
		0,
		SRCCOPY);

	


	CObjMgr::Get_Instance()->Render(hDC);

}

void CStage::Release(void)
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_MAIN);
	//CSoundMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_EVENTCOIN);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_EVENTEFFECT);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BUTTON);


	CObjMgr::Get_Instance()->Delete_ID(OBJ_FLAG);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_WALL);
	//CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);


	CScrollMgr::Get_Instance()->Destroy_Instance();
	

}





