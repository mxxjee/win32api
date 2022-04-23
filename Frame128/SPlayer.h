#pragma once
#include "Obj.h"
class CSPlayer :
	public CObj
{
public:
	enum STATE { ST_INTRO,ST_IDLELEFT,ST_IDLERIGHT, ST_WALKRIGHT, ST_WALKLEFT, ST_LEFTSHOOT, ST_RIGHTSHOOT,ST_RIGHTDOWN, ST_LEFTDOWN, ST_LEFTHIT, ST_RIGHTHIT, ST_UPSHOT,  ST_JUMPRIGHT, ST_JUMPLEFT,ST_RIGHTRUNSHOT,ST_LEFTRUNSHOT,ST_HIT, ST_RIGTHDASH,
		ST_LEFTDASH,ST_DEATH,ST_END };

	CSPlayer();
	~CSPlayer();


public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void 	Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void	Key_Input();
	void	Motion_Change();

	void	Jumping();
	void	Down();

	void		Set_Bullet(list<CObj*>* pBullet) { m_pBullet = pBullet; }
	void	Set_Camera(bool		bCamera) { m_bCamera = bCamera; }
	CObj*	Create_Bullet(DIRECTION eDir);


	void			Set_Hp(int _iAttack) { iHp -= _iAttack; }
	int			Get_iAttck() { return iAttack; }
	int			Get_Hp() { return iHp; }
	int			Get_BulletCnt()	{ return iBulletCnt; }

	void		Set_Intro() { m_bIntro = true; }
	void		Set_Hit() { m_bHit = true; }
	void		Set_State() { m_eCurState = ST_DEATH; }
	void		Set_FrameKey() {m_pFrameKey =  L"Death";}
	


private:
	//������ �ʿ��� ����
	float					m_fPower;
	float					m_fJumpTime;
	bool					m_bJump;

	//��ο� �ʿ��� ����
	bool					m_bDown;

	//��ũ���� �÷��̾� ���󰡵��� �ϱ����� ����
	bool					m_bCamera;

	//����Ÿ�� ���� ���� ����
	bool					m_bStand;
	float					m_fOriginY;
	

	//�ؽ�ó ü���� ���� ����
	STATE					m_ePreState = ST_END;
	STATE					m_eCurState = ST_IDLERIGHT;

	
	list<CObj*>*			m_pBullet;

	float					m_fTime;
	bool					m_bLeft;
	bool					m_bIntro;
	bool					m_bDownFrame;
	bool					m_bHit;
	bool					m_bJumpEffect;
	bool					m_bDash;


	int						iHit;
	int						iEffectCnt;
	int						iHitCnt;
	int						iDashCnt;

	float					g_fSound;

	int						iBulletCnt;

	//����Ʈ����
	bool				m_bRight;
	bool				m_bLeft2;
	bool				m_bDeath;

	float				m_fRightTime;
	float				m_fLeftTime;
	float				m_fDeathTime;

};

