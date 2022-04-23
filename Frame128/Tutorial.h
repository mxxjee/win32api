#pragma once
#include "Scene.h"
class CTutorial :
	public CScene
{
public:
	CTutorial();
	~CTutorial();

public:
	virtual void Initialize(void);
	virtual void Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);

	float		g_fSound;
};

