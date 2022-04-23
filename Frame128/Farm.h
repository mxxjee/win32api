#pragma once

#include "Scene.h"

class CFarm : public CScene
{
public:
	CFarm();
	~CFarm();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


private:
	int			iCnt;
	int			iCnt2;
	int			iCnt3;

	float		g_fSound;
	float		m_fTime;
	float		m_fTime2;
};

