#pragma once
#include "Obj.h"
class CPlayerHit :
	public CObj
{
public:
	enum STATE {ST_IDLE,ST_END};
	CPlayerHit();
	~CPlayerHit();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void	Motion_Change();
private:
	float					m_fTime;


	STATE					m_ePreState = ST_END;
	STATE					m_eCurState = ST_IDLE;
};

