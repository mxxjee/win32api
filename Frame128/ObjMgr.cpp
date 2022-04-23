#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "AbstractFactory.h"
#include "Wall.h"

CObjMgr*		CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
	m_RenderSort[RENDER_END];
}


CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Target(OBJID eID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj*	pTarget = nullptr;
	float	fDistance = 0.f;

	for (auto& Iter : m_ObjList[eID])
	{
		if (Iter->Get_Dead())
			continue;

		float fWidth = fabs(Iter->Get_Info().fX - pObj->Get_Info().fX);
		float fHeight = fabs(Iter->Get_Info().fY - pObj->Get_Info().fY);

		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = Iter;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
}

void CObjMgr::AddObject(OBJID eID, CObj * pObj)
{
	if ((OBJ_END <= eID) || (pObj == nullptr))
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjMgr::Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		auto& iter = m_ObjList[i].begin();

		for (; iter != m_ObjList[i].end();)
		{
			int	iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
}

void CObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;

			//Y sorting 적용 
			RENDERID eRender = iter->Get_RenderID();
			m_RenderSort[eRender].push_back(iter);
		}
	}


	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_WALL], m_ObjList[OBJ_PLAYER]); // 밀어내기 

	//감자에 관한 충돌
	CCollisionMgr::Collision_Rect_Potato(m_ObjList[OBJ_POTATO], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::Collision_Rect_PBullet(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_PBULLET]);
	 
	
	//양파에 관한 충돌
	CCollisionMgr::Collision_Rect_Onion(m_ObjList[OBJ_ONION], m_ObjList[OBJ_BULLET]);  //총알이 onion에 닿았을때
	CCollisionMgr::Collision_Rect_Onion_EX(m_ObjList[OBJ_ONION], m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_OBULLET]);
	
	

	//당근에 관한 충돌
	CCollisionMgr::Collision_Rect_Hit(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_CBULLET]);
	CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_CARROT], m_ObjList[OBJ_PLAYER]);   
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_CBULLET]);
	CCollisionMgr::Collsion_Rect_CarrotBeam(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_CARROTBEAM]);
	CCollisionMgr::Collision_Rect_Carrot(m_ObjList[OBJ_CARROT], m_ObjList[OBJ_BULLET]);

	//Dice에 관한 충돌
	//CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_CARD]);//이건 카드랑밀리는거
	CCollisionMgr::Collision_Rect_CardHit(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_CARD]);
	CCollisionMgr::Collision_Rect_Dice(m_ObjList[OBJ_DICE], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::Collision_Rect_Card(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_CARD]);
	CCollisionMgr::Collision_Rect_BBullet(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BBULLET]);
	CCollisionMgr::Collision_Rect_Onion_EX(m_ObjList[OBJ_BONBON], m_ObjList[OBJ_PLAYER]);

	//Flower에 관한 충돌
	CCollisionMgr::Collision_Rect_Flower(m_ObjList[OBJ_BULLET],m_ObjList[OBJ_FLOWER]);
	CCollisionMgr::Collision_Rect_Face(m_ObjList[OBJ_SPLAYER], m_ObjList[OBJ_COLLISION]);
	CCollisionMgr::Collision_Rect_Face(m_ObjList[OBJ_SPLAYER], m_ObjList[OBJ_CLONG]);
	CCollisionMgr::Collision_Rect_Face(m_ObjList[OBJ_SPLAYER], m_ObjList[OBJ_CSHORT]);
	CCollisionMgr::Collision_Rect_Face(m_ObjList[OBJ_SPLAYER], m_ObjList[OBJ_FBULLET]);
	CCollisionMgr::Collision_Rect_SeedHit(m_ObjList[OBJ_SPLAYER], m_ObjList[OBJ_SEED]);
	CCollisionMgr::Collision_Rect_Venes(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_VENES]);
	CCollisionMgr::Collision_Rect_Face(m_ObjList[OBJ_SPLAYER], m_ObjList[OBJ_VENES]);


	//코인에 관한 충돌
	CCollisionMgr::Collision_Rect_Coin(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_EVENTCOIN]);

}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < RENDER_END; ++i)
	{
		if(i!=RENDER_UI)
			m_RenderSort[i].sort(CompareY<CObj*>);
			
		if (i != RENDER_BACKGROUND)				//맵에 충돌처리하기 위한 네모 안보이게하려고 
		{
			for (auto& iter : m_RenderSort[i])
				iter->Render(hDC);
			
		}

		m_RenderSort[i].clear();
	}

}

void CObjMgr::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}

void CObjMgr::Delete_ID(OBJID eID)
{

	for (auto& iter : m_ObjList[eID])
			Safe_Delete<CObj*>(iter);

	m_ObjList[eID].clear();

}

void CObjMgr::Loda_Data2(OBJID eID)
{
	if (OBJ_WALL == eID)
	{
		HANDLE	hFile = CreateFile(L"../Data/Wall2.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
			return;
		}

		DWORD		dwByte = 0;


		INFO	m_tInfo{};
		while (true)
		{
			ReadFile(hFile, &m_tInfo, sizeof(m_tInfo), &dwByte, nullptr);

			if (0 == dwByte)
				break;

			CObjMgr::Get_Instance()->AddObject(OBJ_WALL, CAbstractFactory<CWall>::Create(m_tInfo));
		}

		CloseHandle(hFile);
		//MessageBox(g_hWnd, _T("Load 성공"), _T("성공"), MB_OK);
	}
}


