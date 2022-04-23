#pragma once

#include "Obj.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*		Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }
	CObj*		Get_SPlayer() { return m_ObjList[OBJ_SPLAYER].front(); }
	CObj*		Get_Potato() { return m_ObjList[OBJ_POTATO].front(); }
	CObj*		Get_Onion() { return m_ObjList[OBJ_ONION].front(); }
	CObj*		Get_Carrot() { return m_ObjList[OBJ_CARROT].front(); }
	CObj*		Get_EventEffect() { return m_ObjList[OBJ_EVENTEFFECT].front(); }
	CObj*		Get_EventCoint() { return m_ObjList[OBJ_EVENTCOIN].front(); }

	

	int		Get_Dice_Size() { return m_ObjList[OBJ_DICE].size(); }
	int		Get_DiceRoom_Size() { return m_ObjList[OBJ_DICEKING].size() +
		m_ObjList[OBJ_CARD].size();}


	//list<CObj*>*		Get_Player_list() { return &m_ObjList[OBJ_PLAYER]; }
	//list<CObj>*			Get_EventCoinlist() { return &m_ObjList[OBJ_EVENTCOIN]; }
	list<CObj*>*		Get_Effect() { return &m_ObjList[OBJ_EFFECT]; }
	list<CObj*>*		Get_EventEffectlist() { return &m_ObjList[OBJ_EVENTEFFECT]; }
	list<CObj*>*		Get_Bullet() { return &m_ObjList[OBJ_BULLET]; }
	list<CObj*>*		Get_PBullet() { return &m_ObjList[OBJ_PBULLET]; }
	list<CObj*>*		Get_OBullet() { return &m_ObjList[OBJ_OBULLET]; }
	list<CObj*>*		Get_CarrotBullet() { return &m_ObjList[OBJ_CBULLET]; }
	list<CObj*>*		Get_CarrotBeam() { return &m_ObjList[OBJ_CARROTBEAM]; }
	list<CObj*>*		Get_Coin() { return &m_ObjList[OBJ_COIN]; }
	

	int			Get_Flower_Size() { return m_ObjList[OBJ_FLOWER].size(); }
	int			Get_Size() { return m_ObjList[OBJ_CARROT].size() + m_ObjList[OBJ_POTATO].size() + m_ObjList[OBJ_ONION].size() + m_ObjList[OBJ_CBULLET].size(); }
	
	CObj*		Get_Target(OBJID eID, CObj* pObj);
	list<CObj*>*  Get_List(OBJID eID)
	{
		if (eID >= OBJ_END) return nullptr;

		return &m_ObjList[eID];
	}

public:
	void	AddObject(OBJID eID, CObj* pObj);
	int		Update(void);
	void	Late_Update(void);
	void	Render(HDC hDC);
	void	Release(void);

	void	Delete_ID(OBJID eID);

	void Load_Data(OBJID eID);
	void Save_Data(OBJID eID);

	void	Loda_Data2(OBJID eID);
private:
	list<CObj*>			m_ObjList[OBJ_END];
	list<CObj*>			m_RenderSort[RENDER_END];

public:
	static CObjMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObjMgr;
		}

		return m_pInstance;
	}
	static void		Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CObjMgr*		m_pInstance;
};

