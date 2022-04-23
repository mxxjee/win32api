#pragma once
#include "Obj.h"
class CMushroom :
	public CObj
{
public:
	enum STATE {ST_IDLE,ST_END};
	CMushroom();
	~CMushroom();

public:
	virtual void Initialize();
	virtual void Render(HDC hdc);
	virtual void Late_Update();
	virtual void Release();
	virtual int  Update();

	void	Motion_Change();

private:
	STATE					m_ePreState = ST_END;
	STATE					m_eCurState = ST_IDLE;
};
