#pragma once
#include "Obj.h"
class CCarrotBullet :
	public CObj
{
public:

	enum STATE { ST_IDLE, ST_DEATH, ST_END };
	CCarrotBullet();
	~CCarrotBullet();


public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void	Set_Death() { m_bDeath = true; }

	void	Motion_Change();

private:
	STATE					m_ePreState = ST_END;
	STATE					m_eCurState = ST_IDLE;
	bool					m_bDeath;

	float					g_fSound;
	
};

