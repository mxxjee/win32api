#include "stdafx.h"
#include "Ready.h"
#include "BmpMgr.h"
#include "SoundMgr.h"


CReady::CReady()
	:m_fTime(0.f)
{
}


CReady::~CReady()
{
}

void CReady::Initialize()
{
	g_fSound = 1.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ready_4.bmp", L"Ready");
	//시작멘트
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/시작멘트.wav", SOUND_MAIN, g_fSound);
	m_tInfo.fCX = 800;
	m_tInfo.fCY = 600;

	m_eRender = RENDER_UI;

	m_pFrameKey = L"Ready";
	m_eCurState = ST_READY;
	m_ePreState = ST_END;


	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 49;
	m_tFrame.dwFrameSpeed = 50;
	m_tFrame.dwFrameTime = GetTickCount();
}

void CReady::Render(HDC hdc)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ready");


	GdiTransparentBlt(hdc,
		(int)m_tRect.left, // 2, 3인자 : 복사 받을 위치 X,Y 좌표
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 4,5인자 : 복사 받을 X,Y 길이
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iFrameMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 9. 10인자 : 복사할 비트맵의 X,Y 사이즈
		(int)m_tInfo.fCY,
		RGB(0, 64, 64));	// 11인자 : 제거할 색상 
}

void CReady::Late_Update()
{
}

void CReady::Release()
{
}

int CReady::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	
	CSoundMgr::Get_Instance()->PlaySound(L"시작멘트.wav", SOUND_MAIN, g_fSound);


	m_fTime += 1.f;
	if (m_tFrame.iFrameStart == 49)
	{
		

		if (m_fTime >= 60)
		{
			m_fTime = 0.f;
			Set_Dead();
		}
			
	}



	Motion_Change();
	Move_Frame();




	Update_Rect();

	
	return OBJ_NOEVENT;
}

void CReady::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_READY:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 49;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}
		m_ePreState = m_eCurState;
	}
}
