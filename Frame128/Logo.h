#pragma once
#include "Scene.h"
#include "Obj.h"
#include "Charactor.h"


class CLogo : public CScene
{
public:
	CLogo();
	virtual ~CLogo();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	float	g_fSound;
};

