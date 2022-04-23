#pragma once
#include "Obj.h"
class CReady :
	public CObj
{
public:
	enum STATE {ST_READY, ST_WALLOP, ST_END};
	CReady();
	~CReady();

public:
	virtual void Initialize();
	virtual void Render(HDC hdc);
	virtual void Late_Update();
	virtual void Release();
	virtual int  Update();

	void	Motion_Change();
	
private:
	float					m_fTime;
	STATE					m_ePreState = ST_END;
	STATE					m_eCurState = ST_READY;

	float					g_fSound;

};

