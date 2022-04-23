#pragma once

#include "Obj.h"

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	float		Get_ScrollX(void) { return m_fScrollX; }
	float		Get_ScrollY(void) { return m_fScrollY; }

public:
	void		Set_ScrollX(float _fX) { m_fScrollX += _fX; }
	void		Set_ScrollY(float _fY) { m_fScrollY += _fY; }

	void		Set_Target(CObj* _Obj) { m_pTarget = _Obj; }
	void		Initialize();

	void		Late_Update();
	void		Scroll_Lock();
	void		Scroll_Lock_stage();

public:
	static CScrollMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CScrollMgr;
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
private:
	static CScrollMgr*		m_pInstance;
	float					m_fScrollX = 0.f;
	float					m_fScrollY = 0.f;

	float					OriginScrollX = 0.f;
	float					OriginScrollY = 0.f;

	CObj*				m_pTarget;
};

