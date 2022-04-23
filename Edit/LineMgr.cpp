#include "stdafx.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"

CLineMgr*		CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
	ZeroMemory(m_tLinePoint, sizeof(POINTPOS));
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{

}

int CLineMgr::Update(void)
{


	for (auto& iter : m_LineList)
		iter->Update();

	Key_Input();


	return 0;
}

void CLineMgr::Late_Update(void)
{
}

void CLineMgr::Render(HDC hDC)
{
	swprintf_s(szBuff, L"( %d, %d )", pt.x, pt.y);
	TextOut(hDC, pt.x + CScrollMgr::Get_Instance()->Get_ScrollX(), pt.y + CScrollMgr::Get_Instance()->Get_Scrolly(), szBuff, lstrlen(szBuff));


	for (auto& iter : m_LineList)
		iter->Render(hDC);
}

void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();
}

bool CLineMgr::Collision_Line(float& fX, float* pY)
{
	if (m_LineList.empty())
		return false;

	CLine* pTargetLine = nullptr;

	for (auto& iter : m_LineList)
	{
		if (fX >= iter->Get_Info().tLeftPoint.fX &&
			fX <= iter->Get_Info().tRightPoint.fX)
		{
			pTargetLine = iter;
		}
	}

	if (!pTargetLine)
		return false;

	// �� ���� ������ ������ ������
	// Y - y1 = ((y2 - y1) / (x2 - x1)) * (X - x1)
	// Y  = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	float fX1 = pTargetLine->Get_Info().tLeftPoint.fX;
	float fX2 = pTargetLine->Get_Info().tRightPoint.fX;
	float fY1 = pTargetLine->Get_Info().tLeftPoint.fY;
	float fY2 = pTargetLine->Get_Info().tRightPoint.fY;

	*pY = ((fY2 - fY1) / (fX2 - fX1)) * (fX - fX1) + fY1;

	return true;
}

void CLineMgr::Key_Input(void)
{


	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= (int)CScrollMgr::Get_Instance()->Get_Scrolly();


	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		// �� ó�� ���ۿ�
		if ((!m_tLinePoint[0].fX) && (!m_tLinePoint[0].fY))
		{
			// 0 ���� left ��
			m_tLinePoint[0].fX = (float)pt.x;
			m_tLinePoint[0].fY = (float)pt.y;
		}

		else
		{
			// 1 ���� right ��
			m_tLinePoint[1].fX = (float)pt.x;
			m_tLinePoint[1].fY = (float)pt.y;

			LINEINFO	 tInfo = { m_tLinePoint[0], m_tLinePoint[1] };
			m_LineList.push_back(new CLine(tInfo));

			m_tLinePoint[0].fX = m_tLinePoint[1].fX;
			m_tLinePoint[0].fY = m_tLinePoint[1].fY;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_TAB))//������
	{
		ZeroMemory(m_tLinePoint, sizeof(m_tLinePoint));
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F5))
		Save_Data();


	if (CKeyMgr::Get_Instance()->Key_Down(VK_F6))
		Load_Data();
}


void CLineMgr::Save_Data(void)
{
	// ���� ���� �Լ�
	HANDLE	hFile = CreateFile(L"../Data/MyMap3.dat",	// ������ ��ο� �̸��� ���
		GENERIC_WRITE,		// ���� ���� ��� (��� : WRITE, �Է� : READ)
		NULL,				// ���� ���, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����ϴ°��� ���� ����, NULL ���� �� ��������
		NULL,				// ���� �Ӽ� ���, NULL�� ��� �⺻�� ����
		CREATE_ALWAYS,		// ������ ������ ����, ������ ���� ����, OPEN_EXISTING - ������ �ִ� ��쿡�� �ε�
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ����, ���� ���� ����� ����), �ƹ��� �Ӽ��� ���� ���� ��� ����
		NULL);	// ������ ������ �Ӽ��� ������ ���ø� ����, �츰 �� �����̱� ������ NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		// 1. �ڵ�
		// 2. �˾� â�� �����ӿ� ������ �ϴ� �޽���(�����ڵ�)
		// 3. �˾� â�� ������ �ϴ� ���� �޽���
		// 4. ��ư ����, MB_OK �� Ȯ�θ� , MB_OKCANCEL Ȯ��, ��� ��ư

		return;
	}

	DWORD		dwByte = 0;

	for (auto& iter : m_LineList)
	{
		WriteFile(hFile, &(iter->Get_Info()), sizeof(LINEINFO), &dwByte, nullptr);
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save ����"), _T("����"), MB_OK);
}

void CLineMgr::Load_Data(void)
{
	// ���� ���� �Լ�
	HANDLE	hFile = CreateFile(L"../Data/MyMap2.dat",	// ������ ��ο� �̸��� ���
		GENERIC_READ,		// ���� ���� ��� (��� : WRITE, �Է� : READ)
		NULL,				// ���� ���, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����ϴ°��� ���� ����, NULL ���� �� ��������
		NULL,				// ���� �Ӽ� ���, NULL�� ��� �⺻�� ����
		OPEN_EXISTING,		// ������ ������ ����, ������ ���� ����, OPEN_EXISTING - ������ �ִ� ��쿡�� �ε�
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ����, ���� ���� ����� ����), �ƹ��� �Ӽ��� ���� ���� ��� ����
		NULL);	// ������ ������ �Ӽ��� ������ ���ø� ����, �츰 �� �����̱� ������ NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		// 1. �ڵ�
		// 2. �˾� â�� �����ӿ� ������ �ϴ� �޽���(�����ڵ�)
		// 3. �˾� â�� ������ �ϴ� ���� �޽���
		// 4. ��ư ����, MB_OK �� Ȯ�θ� , MB_OKCANCEL Ȯ��, ��� ��ư

		return;
	}

	DWORD			dwByte = 0;
	LINEINFO		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo));
	}

	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load ����"), _T("����"), MB_OK);
}
