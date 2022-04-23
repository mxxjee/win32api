#pragma once

#include "Obj.h"

class CCollisionMgr
{
public:
	enum STATE { ST_INTRO, ST_IDLE, ST_ATTACK, ST_DEATH, ST_END };
	CCollisionMgr();
	~CCollisionMgr();

public:
	//몬스터와 플레이어bullet들의 충돌처리
	static void	Collision_Rect_Potato(list<CObj*> Dest, list<CObj*> Sour);
	static void	Collision_Rect_Carrot(list<CObj*> Dest, list<CObj*> Sour);
	static void	Collision_Rect_Onion(list<CObj*> Dest, list<CObj*> Sour);
	static void	Collision_Rect_Ball(list<CObj*> Dest, list<CObj*> Sour);
	static	void Collision_Rect_Dice(list<CObj*> Dest, list<CObj*> Sour);
	static	void	Collision_Rect_PBullet(list<CObj*>Dest, list<CObj*>Sour);
	static  void  Collision_Rect_Card(list<CObj*>Dest, list<CObj*>Sour);
	static  void	Collision_Rect_CardHit(list<CObj*>Dest, list<CObj*>Sour);
	static	void	Collision_Rect_Flower(list<CObj*>Dest, list<CObj*>Sour);
	static	void	Collision_Rect_Face(list<CObj*>Dest, list<CObj*>Sour);
	static	void	Collision_Rect_SeedHit(list<CObj*>Dest, list<CObj*>Sour);
	static	void	Collision_Rect_Venes(list<CObj*>Dest, list<CObj*>Sour);
	static void		Collision_Rect_BBullet(list<CObj*>Dest, list<CObj*>Sour);
	static	void	Collision_Rect_Onion_EX(list<CObj*>Dest, list<CObj*>Sour);
	static	void	Collsion_Rect_CarrotBeam(list<CObj*>Dest, list<CObj*>Sour);
	static	void	Collision_Rect_Coin(list<CObj*>Dest, list<CObj*>Sour);


	static void	Collision_Rect(list<CObj*> Dest, list<CObj*> Sour);
	static void Collision_Rect_Hit(list<CObj*>Dest, list<CObj*>Sour);
	static void	Collision_RectEx(list<CObj*> Dest, list<CObj*> Sour);
	static void Collision_Sphere(list<CObj*> Dest, list<CObj*> Sour);
	static bool Check_Sphere(CObj* pDest, CObj* pSour);
	static bool Check_Rect(CObj* pDest, CObj* pSour, float* _pX ,float* _pY);

	static	int		Stage01Hit;
	static  int		Stage02Hit;
	static	int		Stage03Hit;


};

