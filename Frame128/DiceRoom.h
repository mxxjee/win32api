#pragma once
#include "Scene.h"

class CDiceRoom :public CScene
{
public:
	CDiceRoom();
	~CDiceRoom();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	int		iCnt;
	float	g_fSound;
	float	m_fTime;

	int		iCnt2;
};

