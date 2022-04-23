#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
public:
	enum STATE { ST_INTRO,ST_UP, ST_LEFT, ST_RIGHT, ST_DOWN,ST_DEAD, ST_END };

	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void		Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void		Set_Death() { m_bCollision = true; }

	void		Set_State(TCHAR*	pFrameKey ,STATE CurState)
	{
		m_pFrameKey = pFrameKey;
		m_eCurState = CurState; }

	STATE		Get_State() { return ST_DEAD; }

	void	Motion_Change(void);

	void			Set_Hp(int _iAttack) { iHp -= _iAttack; }
	int			Get_iAttck() { return iAttack; }
	int			Get_Hp() { return iHp; }

	static			int		Stage01Bullet;
private:
	STATE					m_ePreState = ST_END;
	STATE					m_eCurState = ST_RIGHT;


	

	bool					m_bCollision;

	

};

