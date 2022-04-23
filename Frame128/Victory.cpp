#include "stdafx.h"
#include "Victory.h"
#include "BmpMgr.h"
#include "SoundMgr.h"


CVictory::CVictory()
	:m_bStop(false), g_fSound(1.f),iCnt(1)
{
}


CVictory::~CVictory()
{
}

void CVictory::Initialize()
{
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/게임성공.wav", SOUND_VICTORY, g_fSound);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Victory.bmp", L"Victory");
	m_tInfo.fCX = 600;
	m_tInfo.fCY = 600;

	m_eRender = RENDER_UI;

	m_pFrameKey = L"Victory";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;


	m_tFrame.iFrameMotion = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd =11;
	m_tFrame.dwFrameSpeed = 200;
	m_tFrame.dwFrameTime = GetTickCount();



}

void CVictory::Render(HDC hdc)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Victory");


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
		RGB(0, 64,64));	// 11인자 : 제거할 색상 

}

void CVictory::Late_Update()
{
	
}


void CVictory::Release()
{
}

int CVictory::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (iCnt == 1)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"게임성공.wav", SOUND_VICTORY, g_fSound);
		iCnt = 0;
	}


	if (m_tFrame.iFrameStart == 11)
	{
		m_bStop = true;
		Set_Dead();
	}



	Motion_Change();


	if(!m_bStop)
		Move_Frame();

	


	Update_Rect();

	return OBJ_NOEVENT;
}

void CVictory::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 11;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;

		}
		m_ePreState = m_eCurState;
	}
}
