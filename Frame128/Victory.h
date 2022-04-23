#pragma once
#include "Obj.h"
class CVictory :
	public CObj
{
public:
	enum STATE {ST_IDLE,ST_END};
	CVictory();
	~CVictory();

public:
	virtual void Initialize();
	virtual void Render(HDC hdc);
	virtual void Late_Update();
	virtual void Release();
	virtual int  Update();

	void	Motion_Change();


	STATE					m_ePreState = ST_END;
	STATE					m_eCurState = ST_IDLE;

	bool					m_bStop;
	int						iCnt;

	float					g_fSound;
};

