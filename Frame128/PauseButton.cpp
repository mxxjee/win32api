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
		(int)m_tRect.left, // 2, 3���� : ���� ���� ��ġ X,Y ��ǥ
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 4,5���� : ���� ���� X,Y ����
		(int)m_tInfo.fCY,
		hMemDC,
		m_iDrawID * (int)m_tInfo.fCX,
		0,
		(int)m_tInfo.fCX,		// 9. 10���� : ������ ��Ʈ���� X,Y ������
		(int)m_tInfo.fCY,
		RGB(0, 64, 64));	// 11���� : ������ ���� 
}

void CPauseButton::Release(void)
{

}

