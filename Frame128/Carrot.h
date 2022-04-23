#pragma once
#include "Obj.h"
class CCarrot :
	public CObj
{
public:
	enum STATE { ST_INTRO, ST_IDLE, ST_ATTACK, ST_DEATH, ST_END };

	CCarrot();
	~CCarrot();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void		Set_Bullet(list<CObj*>* pBullet) { m_pBullet = pBullet; }
	void		Set_State(STATE CurState) { m_eCurState = CurState; }
	STATE		Get_State() { return ST_DEATH; }
	bool		Get_Death() { return m_bDeath; }
	void		Set_Death() { m_bDeath = true; }

	

	void	Motion_Change(void);


private:
	list<CObj*>*			m_pBullet;


	STATE					m_ePreState = ST_END;
	STATE					m_eCurState = ST_IDLE;

	bool					m_bDeath;
	bool					m_bIntro;
	bool					m_bAttack;

	int						iEffectCnt;
	float					m_fTime;
	float					m_flTime;

	float					m_f2Time;
	float					m_fl2Time;


	int						iCnt;
	int						iCnt2;

	float					g_fSound;
};

