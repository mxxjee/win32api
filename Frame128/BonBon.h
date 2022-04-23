#pragma once
#include "Obj.h"
class CBonBon :
	public CObj
{
public:
	enum STATE {ST_IDLE,ST_END};
	CBonBon();
	~CBonBon();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


	void	Motion_Change(void);


	STATE					m_ePreState = ST_END;
	STATE					m_eCurState = ST_IDLE;

	float					m_fTime;
	float					m_fTime2;
};

