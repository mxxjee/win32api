#pragma once
#include "Obj.h"
class CDice :
	public CObj
{
public:
	enum STATE {ST_IDLE,ST_DEATH,ST_END};
	CDice();
	~CDice();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void		Set_State(STATE CurState) { m_eCurState = CurState; }
	STATE		Get_State() { return ST_DEATH; }
	bool		Get_Death() { return m_bDeath; }
	void		Set_Death() { m_bDeath = true; }


	void	Motion_Change();

	void	Jumping();



private:
	STATE					m_ePreState = ST_END;
	STATE					m_eCurState = ST_IDLE;


	float			m_fJumpTime;
	float			m_fPower;

	bool			m_bDeath;

	int				iCnt;
};

