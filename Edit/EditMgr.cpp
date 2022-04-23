#include "stdafx.h"
#include "EditMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "Wall.h"
#include "ObjMgr.h"

CEditMgr*		CEditMgr::m_pInstance = nullptr;


CEditMgr::CEditMgr()
	:m_pObject(nullptr), m_eObj_ID(OBJ_END), m_ePreObj_ID(OBJ_END)
{
}


CEditMgr::~CEditMgr()
{
	Release();
}

void CEditMgr::Key_Input()
{
	POINT pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= CScrollMgr::Get_Instance()->Get_Scrolly();

	if (CKeyMgr::Get_Instance()->Key_Down('Q'))//Wall배치
	{
		if (m_pObject)
			delete m_pObject;

		m_pObject = new CWall;
		m_ePreObj_ID = m_eObj_ID;
		m_eObj_ID = OBJ_WALL;
		m_pObject->Initialize();
		m_pObject->Set_Size(30.f, 30.f);
	}

	//else if (CKeyMgr::Get_Instance()->Key_Down('W'))//Item배치
	//{
	//	if (m_pObject)
	//		delete m_pObject;

	//	m_pObject = new CItem;
	//	m_ePreObj_ID = m_eObj_ID;
	//	m_eObj_ID = OBJ_ITEM;
	//	m_pObject->Initialize();
	//	
	//}

	//else if (CKeyMgr::Get_Instance()->Key_Down('E'))//Monster배치
	//{
	//	if (m_pObject)
	//		delete m_pObject;

	//	m_pObject = new CMonster;
	//	m_ePreObj_ID = m_eObj_ID;
	//	m_eObj_ID = OBJ_MONSTER;
	//	m_pObject->Initialize();
	//	//m_pObject->Set_Size(100.f, 100.f);
	//}

	//else if (CKeyMgr::Get_Instance()->Key_Down('R'))//MoveWall배치
	//{
	//	if (m_pObject)
	//		delete m_pObject;

	//	m_pObject = new CMoveWall;
	//	m_ePreObj_ID = m_eObj_ID;
	//	m_eObj_ID = OBJ_MOVEWALL;
	//	m_pObject->Initialize();
	//	m_pObject->Set_Size(100.f, 50.f);
	//}

	//else if (CKeyMgr::Get_Instance()->Key_Down('T'))//Goal배치
	//{
	//	if (m_pObject)
	//		delete m_pObject;

	//	m_pObject = new CGoal;
	//	m_ePreObj_ID = m_eObj_ID;
	//	m_eObj_ID = OBJ_GOAL;
	//	m_pObject->Initialize();
	//	m_pObject->Set_Size(200.f, 150.f);
	//}

	if (m_pObject)
		m_pObject->Set_Pos((float)pt.x, (float)pt.y);


	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))//push_back Object
	{
		if (m_pObject)
		{
			CObjMgr::Get_Instance()->AddObject(m_eObj_ID, m_pObject);
			switch (m_eObj_ID)
			{
			case OBJ_WALL:
				m_pObject = new CWall;
				m_pObject->Set_Size(30.f, 30.f);
				break;

				//case OBJ_ITEM:
				//	m_pObject = new CItem;
				//	break;

			/*case OBJ_MONSTER:
				m_pObject = new CMonster;
				break;*/

				/*case OBJ_MOVEWALL:
				m_pObject = new CMoveWall;
				m_pObject->Set_Size(100.f, 50.f);
				break;*/

			//case OBJ_GOAL:
			//	m_pObject = new CGoal;
			//	m_pObject->Set_Size(200.f, 150.f);
			//	break;
			}
			m_pObject->Initialize();
			m_pObject->Set_Pos((float)pt.x, (float)pt.y);
		}
	}

	//if (CKeyMgr::Get_Instance()->Key_Down(VK_DELETE))//이전 물체만 삭제
	//{

	//}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F7))
		Save_Data();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F8))
		Load_Data();


}

void CEditMgr::Update()
{
	Key_Input();
	if (m_pObject)
		m_pObject->Update();
}

void CEditMgr::Render(HDC hdc)
{
	if (m_pObject)
		m_pObject->Render(hdc);
}

void CEditMgr::Save_Data()
{
	CObjMgr::Get_Instance()->Save_Data(OBJ_WALL);
	//CObjMgr::Get_Instance()->Save_Data(OBJ_ITEM);
	//CObjMgr::Get_Instance()->Save_Data(OBJ_MONSTER);
	//CObjMgr::Get_Instance()->Save_Data(OBJ_MOVEWALL);
//	CObjMgr::Get_Instance()->Save_Data(OBJ_GOAL);

}

void CEditMgr::Load_Data()
{
	CObjMgr::Get_Instance()->Load_Data(OBJ_WALL);
	//CObjMgr::Get_Instance()->Load_Data(OBJ_ITEM);
	//CObjMgr::Get_Instance()->Load_Data(OBJ_MONSTER);
	//CObjMgr::Get_Instance()->Load_Data(OBJ_MOVEWALL);
	//CObjMgr::Get_Instance()->Load_Data(OBJ_GOAL);
}

void CEditMgr::Release()
{
	if (m_pObject)
	{
		delete m_pObject;
		m_pObject = nullptr;
	}
}
