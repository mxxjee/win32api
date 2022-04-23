#pragma once

#include "Logo.h"
#include "MyMenu.h"
#include "Stage.h"
#include "Scene.h"
#include "Farm.h"
#include "DiceRoom.h"
#include "Tutorial.h"
#include "Garden.h"
#include "Ending.h"

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	static CSceneMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
		}

		return m_pInstance;
	}
	static void		Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

	//
	void		DeletePreScene()
	{
		
		if (m_pPreScene)
		{
			Safe_Delete(m_pPreScene);
			m_pScene->Initialize();
		}
	}

public:
	void		Scene_Change(SCENEID eID);
	//void		Scene_Change(SCENEID eID, int i);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);
	//CScene*		Get_Scene(int i) { return m_Scenevec[i]; }
	

private:
	static CSceneMgr*		m_pInstance;
	CScene*					m_pScene;
	CScene*					m_pPreScene;

	SCENEID					m_eCurScene = SC_LOGO;
	SCENEID					m_ePreScene = SC_END;

	//vector<CScene*>		m_Scenevec;


};

