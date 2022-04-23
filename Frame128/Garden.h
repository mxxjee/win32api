#pragma once
#include "Scene.h"
class CGarden :
	public CScene
{
public:
	CGarden();
	~CGarden();
	
public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	int			iCnt;
	int			iCnt2;
	float		g_fSound;
	float		m_fTime;
	
};

