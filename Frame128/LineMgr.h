#pragma once

#include "Line.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void		Initialize(void);
	void		Render(HDC hDC);
	void		Release(void);

	void		Load_Data1(void);
	void		Load_Data2(void);
	void		Load_Data3(void);
	void		Load_Data4(void);

	bool		Collision_Line(float& fX, float* pY);
	bool		Collision_Line(float& fX, float& fY, float* pY);
	bool		Collision_Line_Ball(float& fX, float* pY);

public:
	static CLineMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CLineMgr;
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
	static CLineMgr*		m_pInstance;
	list<CLine*>			m_LineList;
};

