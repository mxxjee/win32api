#pragma once
#include "Obj.h"
class CDiceKing :
	public CObj
{
public:
	enum STATE {ST_INTRO, ST_IDLE, ST_ATTACK, ST_DEATH,ST_END};
	CDiceKing();
	~CDiceKing();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


	//void		Jumping();
	void		Motion_Change();

private:
	float			m_fTime;
	float			m_fJumpTime;
	float			m_fPower;
	float			m_fOriginSpeed;
	float			m_fCTime;

	float			m_fBonTime;

	STATE					m_ePreState = ST_END;
	STATE					m_eCurState = ST_INTRO;


	int				iCnt;
	int				iCnt2;
	int				iEffectCnt;

	bool			m_bIntro;
	bool			m_bIdle;
	bool			m_bAttack;
	bool			m_bDice;
	bool			m_bCard;
	bool			m_bDeath;

	float			g_fSound;
	int				iCnt3;
};

