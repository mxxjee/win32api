#pragma once
#include "Obj.h"

class CPotato :
	public CObj
{
public:
	enum STATE { ST_INTRO, ST_IDLE, ST_ATTACK, ST_DEATH, ST_END };
	CPotato();
	virtual ~CPotato();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void		Set_State(STATE CurState) { m_eCurState = CurState; }
	void		Set_Death() { m_bDeath = true; }
	void		Set_Bullet(list<CObj*>* pBullet) { m_pBullet = pBullet; }
	STATE		Get_State() { return ST_DEATH; }
	bool		Get_Death() { return m_bDeath; }


	void			Set_Hp(int _iAttack) { iHp -= _iAttack; }


	int			Get_iAttck() { return iAttack; }
	int			Get_Hp() { return iHp; }

	void	Motion_Change(void);

	
private:

	list<CObj*>*			m_pBullet;

	STATE					m_ePreState = ST_END;
	STATE					m_eCurState = ST_IDLE;

	float					m_fOTime;
	float					m_fTime;
	float					m_flTime;

	int						iCnt;
	int						iEffectCnt;

	bool					m_bIntro;
	bool					m_bDeath;
	bool					m_bRealDeath;

	float					g_fSound;

};

