#include "stdafx.h"
#include "SceneMgr.h"
#include "ObjMgr.h"




CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_pPreScene(nullptr), m_eCurScene(SC_LOGO), m_ePreScene(SC_END)
{

}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{

		if (m_pScene)
		{
			m_pScene->m_bDead = true;
			m_pPreScene = m_pScene;
		}


		switch (m_eCurScene)
		{
		case SC_LOGO:
			m_pScene = new CLogo;
			m_pScene->Initialize();
			break;

		case SC_MENU:
			m_pScene = new CMyMenu;
			break;

		case SC_STAGE:
			m_pScene = new CStage;
			break;

		case SC_STAGE01:
			m_pScene = new CFarm;
			break;

		case SC_STAGE02:
			m_pScene = new CDiceRoom;
			break;

		case SC_STAGE03:
			m_pScene = new CGarden;
			break;
		case SC_ENDING:
			m_pScene = new CEnding;
			break;

		case SC_TUTORIAL:
			m_pScene = new CTutorial;
			break;

		
		}

		//m_pScene->Initialize();
		m_ePreScene = m_eCurScene;
	}

}

//void CSceneMgr::Scene_Change(SCENEID eID,int i)
//{
//
//
//	switch (eID)
//	{
//	case SC_LOGO:
//		m_pScene = new CLogo;
//		break;
//
//	case SC_MENU:
//		m_pScene = new CMyMenu;
//		break;
//
//	case SC_STAGE:
//		m_pScene = new CStage;
//		break;
//
//	case SC_STAGE01:
//		m_pScene = new CFarm;
//		break;
//
//	case SC_STAGE02:
//		m_pScene = new CForest;
//		break;
//
//	case SC_EDIT:
//		break;
//	}
//	m_pScene->Initialize();
//
//	m_ePreScene = m_eCurScene;
//
//}



void CSceneMgr::Update(void)
{
	if (m_pScene)
		m_pScene->Update();
}

void CSceneMgr::Late_Update(void)
{
	if (m_pScene)
		m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	if (m_pScene)
		m_pScene->Render(hDC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete(m_pScene);

	CObjMgr::Get_Instance()->Destroy_Instance();
}
