#include "stdafx.h"
#include "PauseButton.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"


CPauseButton::CPauseButton()
{
}


CPauseButton::~CPauseButton()
{
}

void CPauseButton::Initialize(void)
{
	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 70.f;

	m_eRender = RENDER_UI2;
}

int CPauseButton::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPauseButton::Late_Update(void)
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!lstrcmp(L"Pause", m_pFrameKey))
			{
 				if (!m_bPause)
				{
					CSoundMgr::Get_Instance()->StopAll();
					m_bPause = true;
					
				}
					
			}
				

			return;
		}

		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;

}

void CPauseButton::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left, // 2, 3인자 : 복사 받을 위치 X,Y 좌표
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 4,5인자 : 복사 받을 X,Y 길이
		(int)m_tInfo.fCY,
		hMemDC,
		m_iDrawID * (int)m_tInfo.fCX,
		0,
		(int)m_tInfo.fCX,		// 9. 10인자 : 복사할 비트맵의 X,Y 사이즈
		(int)m_tInfo.fCY,
		RGB(0, 64, 64));	// 11인자 : 제거할 색상 
}

void CPauseButton::Release(void)
{

}

