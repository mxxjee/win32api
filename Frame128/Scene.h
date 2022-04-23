#pragma once

#include "Include.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void Initialize(void) = 0;
	virtual void Update(void) = 0;
	virtual void Late_Update(void) = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release(void) = 0;

	bool	Get_Dead() { return m_bDead; }

public:
	bool		m_bDead = false;
	bool		m_bPotatoDead = false;
};

