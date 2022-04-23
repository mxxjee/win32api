#include "stdafx.h"
#include "ScrollMgr.h"
#include "Player.h"

CScrollMgr*		CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr()
	:m_fScrollX(0.f), m_fScrollY(0.f),m_pTarget(nullptr)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Initialize()
{
	m_fScrollX = 0.f;
	m_fScrollY = 0.f;
}

void CScrollMgr::Late_Update()
{

	

	if (m_pTarget)
	{
		POINTPOS tPos = { m_pTarget->Get_Info().fX,m_pTarget->Get_Info().fY };

		

		m_fScrollX = -(tPos.fX - WINCX * 0.5);
		m_fScrollY = -(tPos.fY - WINCY * 0.5);
	}

	
		//Scroll_Lock();
	

	
}

void CScrollMgr::Scroll_Lock()
{
	
	/*OriginScrollX = m_fScrollX;
	OriginScrollY = m_fScrollY;*/

	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;


	if (WINCX - 2000 > m_fScrollX)
		m_fScrollX = WINCX - 2000;

	if (WINCY - (720) > m_fScrollY)
		m_fScrollY = WINCY - 720;

	/*if (WINCX - 1920 > m_fScrollX)
		m_fScrollX = WINCX - 1920;

	if (WINCY - 1200 > m_fScrollY)
		m_fScrollY = WINCY - 1200;*/


}

void CScrollMgr::Scroll_Lock_stage()
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;


	if (WINCX - 1920 > m_fScrollX)
		m_fScrollX = WINCX - 1920;

	if (WINCY - (1080) > m_fScrollY)
		m_fScrollY = WINCY - 1080;
}
