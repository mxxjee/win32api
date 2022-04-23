#include "stdafx.h"
#include "PlayerHit.h"
#include "BmpMgr.h"

CPlayerHit::CPlayerHit()
	:m_fTime(0.f)
{
}


CPlayerHit::~CPlayerHit()
{
}

void CPlayerHit::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Hit_Player2.bmp", L"Hit_Player");

	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 70.f;

	m_eRender = RENDER_EFFECT;

	m_pFrameKey = L"Hit_Player";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;
}

int CPlayerHit::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Motion_Change();
	Move_Frame();

	Update_Rect();
	return OBJ_NOEVENT;
}

void CPlayerHit::Late_Update(void)
{
	m_fTime += 1.f;

	if (m_fTime >= 60)
		m_bDead = true;
}

void CPlayerHit::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);


	GdiTransparentBlt(hDC,
		(int)m_tRect.left, // 2, 3���� : ���� ���� ��ġ X,Y ��ǥ
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 4,5���� : ���� ���� X,Y ����
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9. 10���� : ������ ��Ʈ���� X,Y ������
		(int)m_tInfo.fCY,
		RGB(0, 54, 54));	// 11���� : ������ ���� 
}

void CPlayerHit::Release(void)
{
}

void CPlayerHit::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;


		}
		m_ePreState = m_eCurState;
	}
}
