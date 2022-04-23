#pragma once
#include "Obj.h"
class COBullet :
	public CObj
{
public:
	enum STATE{ ST_IDLE,ST_DEAD, ST_END };
	COBullet();
	~COBullet();


public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void 	Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	

	void	Motion_Change();

private:
	STATE					m_ePreState = ST_END;
	STATE					m_eCurState = ST_IDLE;

	bool					m_bGround;

	float					g_fSound;
};

