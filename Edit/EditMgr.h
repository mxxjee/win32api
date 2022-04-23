#pragma once

#include "Include.h"

class CObj;

class CEditMgr
{
private:
	CEditMgr();
	~CEditMgr();

public:
	void	Key_Input();
	void	Update();
	void	Render(HDC hdc);
	void	Release();

	void	Save_Data();
	void	Load_Data();



public:
	static CEditMgr*		Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CEditMgr;
		}

		return m_pInstance;

	}
	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CEditMgr*		m_pInstance;


	CObj*	m_pObject;
	OBJID	m_eObj_ID;
	OBJID	m_ePreObj_ID;
};

