#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	enum STATE { ST_IDLE, ST_WALKRIGHT, ST_WALKLEFT, ST_DOWN, ST_UP, ST_JUMP, ST_END };

public:
	CPlayer();
	virtual ~CPlayer();

public:
	
	void		Set_Camera(bool Camera) { m_bCamera = Camera; }
	bool		Get_Stage() { return m_bStage; }
	void		Set_Stage(bool bStage) { m_bStage = bStage; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void 	Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void	Key_Input(void);
	void	Jumping(void);
	void	Offset(void);
	void	Motion_Change(void);
	
	template<typename T>
	CObj*	Create_Bullet(DIRECTION eDir = END);

	
private:
	list<CObj*>*			m_pBullet;
	list<CObj*>*			m_pShield;

	POINT					m_tPosin;

	float					m_fPower;
	float					m_fJumpTime;

	float					m_fTime;
	float					m_fTime2;
	float					m_fTime3;
	float					m_fTime4;

	bool					m_bJump;

	bool					m_bCamera;
	bool					m_bStage;

	bool					m_bRight;
	bool					m_bLeft;
	bool					m_bUp;
	bool					m_bDown;

	bool					m_bWalkEffect;

	float					m_fOriginY;

	STATE					m_ePreState = ST_END;
	STATE					m_eCurState = ST_IDLE;

	int		iOffSetX;
	int		iOffSetY ;
	int		iCnt;

};


// Y = 파워 * 시간 - (중력 * 시간의 제곱) / 2