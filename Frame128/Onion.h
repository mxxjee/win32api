#pragma once
#include "Obj.h"
class COnion :
	public CObj
{
public:
	enum STATE { ST_INTRO, ST_IDLE, ST_ATTACK, ST_DEATH, ST_END };

	COnion();
	~COnion();

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


	int						iCnt;
	int						iEffectCnt;

	float					m_flTime;
	float					m_fTime;

	bool					m_bDeath;
	bool					m_bIntro;

	STATE					m_ePreState = ST_END;
	STATE					m_eCurState = ST_IDLE;

	float					g_fSound;
};

