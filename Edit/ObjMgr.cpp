#include "stdafx.h"
#include "ObjMgr.h"
#include "Wall.h"
#include "AbstractFactory.h"

CObjMgr*		CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
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
			iter->Late_Update();
	}

	
}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(hDC);
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

void CObjMgr::Load_Data(OBJID eID)
{
	if (OBJ_WALL == eID)
	{
		HANDLE	hFile = CreateFile(L"../Data/Wall.dat",
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

	}
	MessageBox(g_hWnd, _T("Load 己傍"), _T("己傍"), MB_OK);
}

void CObjMgr::Save_Data(OBJID eID)
{
	if (OBJ_WALL == eID)
	{
		HANDLE	hFile = CreateFile(L"../Data/Wall2.dat",
			GENERIC_WRITE,
			NULL,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
			return;
		}

		DWORD		dwByte = 0;


		INFO	m_tInfo{};

		for (auto& iter : *CObjMgr::Get_Instance()->Get_List(OBJ_WALL))
		{
			WriteFile(hFile, &(iter->Get_Info()), sizeof(m_tInfo), &dwByte, nullptr);
		}
		CloseHandle(hFile);

	}
	MessageBox(g_hWnd, _T("Save 己傍"), _T("己傍"), MB_OK);
}

