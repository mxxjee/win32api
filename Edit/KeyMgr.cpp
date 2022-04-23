#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr*		CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_bKeystate, sizeof(m_bKeystate));
}

CKeyMgr::~CKeyMgr()
{
}

bool CKeyMgr::Key_Pressing(int _iKey)
{
	if (GetAsyncKeyState(_iKey) & 0x8000)
		return true;

	return false;
}

bool CKeyMgr::Key_Down(int _iKey)
{
	// 이전에 눌림이 없고, 현재 눌렸을 때

	if ((!m_bKeystate[_iKey]) && (GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeystate[_iKey] = !m_bKeystate[_iKey];
		return true;
	}

	for (int i = 0; i < VK_MAX; ++i)
	{
		if (m_bKeystate[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_bKeystate[i] = !m_bKeystate[i];
	}

	return false;
}

bool CKeyMgr::Key_Up(int _iKey)
{
	if ((m_bKeystate[_iKey]) && !(GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeystate[_iKey] = !m_bKeystate[_iKey];
		return true;
	}

	for (int i = 0; i < VK_MAX; ++i)
	{
		if (!m_bKeystate[i] && (GetAsyncKeyState(i) & 0x8000))
			m_bKeystate[i] = !m_bKeystate[i];
	}

	return false;
}

bool CKeyMgr::Key_Toggle(int _iKey)
{
	if (!m_bKeystate[_iKey] && (GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeystate[_iKey] = !m_bKeystate[_iKey];
		return m_bKeystate[_iKey];
	}

	else if (m_bKeystate[_iKey] && (GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_bKeystate[_iKey] = !m_bKeystate[_iKey];
		return m_bKeystate[_iKey];
	}

	return false;
}

bool CKeyMgr::Key_State(int _iKey)
{
	return m_bKeystate[_iKey];
}
