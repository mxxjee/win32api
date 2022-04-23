#pragma once
#include "Obj.h"
class CCoin :
	public CObj
{
public:
	enum STATE {ST_IDLE,ST_END};
	CCoin();
	~CCoin();

public:
	virtual void Initialize();
	virtual void Render(HDC hdc);
	virtual void Late_Update();
	virtual void Release();
	virtual int  Update();

	void	Motion_Change();


	STATE					m_ePreState = ST_END;
	STATE					m_eCurState = ST_IDLE;
};

