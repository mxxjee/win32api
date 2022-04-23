#pragma once
#include "Scene.h"

#include "Player.h"

class CStage :
	public CScene
{
public:
	CStage();
	virtual ~CStage();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	float g_fSound;
	static	bool	m_bHidden;
	static	int		iCoinCnt;

	float		m_fEndTime;
};

