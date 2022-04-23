#pragma once
#include "Obj.h"
class CFlower :
	public CObj
{
public:
	enum STATE{ST_INTRO, ST_IDLE, ST_ATTACK,ST_BULLET,ST_FINALINTRO, ST_FINALATTACK, ST_DEATH,ST_END};
	CFlower();
	~CFlower();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void		Motion_Change();

	void		Set_State(STATE CurState) { m_eCurState = CurState; }
	void		Set_Death() { m_bDeath = true; }
	STATE		Get_State() { return ST_DEATH; }
	bool		Get_Death() { return m_bDeath; }

	STATE					m_ePreState = ST_END;
	STATE					m_eCurState = ST_INTRO;

	bool					m_bIntro;
	bool					m_bIdle;
	bool					m_bFaceAttack;
	bool					m_bBullet;
	bool					m_bFinal;
	bool					m_bFinalIntro;
	bool					m_bFianlAttack;
	bool					m_bMotion;
	bool					m_bMakeBullet;
	bool					m_bShort;
	bool					m_bDeath;


	int						iCnt;
	int						iIntroCnt;
	int						iTreeCnt;
	int						iEffectCnt;

	float					m_fTime;
	float					m_fTime2;
	float					m_fTime3;
	float					m_fTime4;

	float					m_fBulletTime;
	float					m_fFlowerTime;
	float					m_fTreeTime;
	float					m_fShortTime1;
	float					m_fShortTime2;
	float					m_fShortTime3;
	float					g_fSound;


	
	int						iFaceCnt;
	int						iFaceCnt2;

	int						iBulletCnt;

	int						iSeedCnt;



};

