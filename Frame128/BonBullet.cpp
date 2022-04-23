#include "stdafx.h"
#include "BonBullet.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"


CBonBullet::CBonBullet()
	:m_fTime(0.f), m_fTime2(0.f), g_fSound(1.f),iCnt(1)
{
}


CBonBullet::~CBonBullet()
{
}

void CBonBullet::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Dice/BBullet.bmp", L"BBullet");
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/팝콘.wav", SOUND_EFFECT, g_fSound);

	m_tInfo.fX = 650.f;
	m_tInfo.fY = 450.f;

	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_tImageInfo.fX = m_tInfo.fX;
	m_tImageInfo.fY = m_tInfo.fY;

	m_tImageInfo.fCX = 20.f;
	m_tImageInfo.fCY = 20.f;

	m_fSpeed = 5.f;

	m_eRender = RENDER_OBJ;

	m_pFrameKey = L"BBullet";
	m_eCurState = ST_IDLE;
	m_ePreState = ST_END;
}

int CBonBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (iCnt == 1)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"팝콘.wav", SOUND_EFFECT, g_fSound);
		iCnt = 0;

	}
		

	m_tInfo.fX -= m_fSpeed;
	
	m_tImageInfo.fX = m_tInfo.fX;
	m_tImageInfo.fY = m_tInfo.fY;


	Motion_Change();
	Move_Frame();

	Update_Rect_Image();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBonBullet::Late_Update(void)
{
	if (m_tInfo.fX <= 0)
		m_bDead = true;
	
}

void CBonBullet::Render(HDC hDC)
{
	/*Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);*/

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);


	GdiTransparentBlt(hDC,
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

void CBonBullet::Release(void)
{
}

void CBonBullet::Motion_Change(void)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case ST_IDLE:
			m_tFrame.iFrameMotion = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 25;
			m_tFrame.dwFrameSpeed = 50;
			m_tFrame.dwFrameTime = GetTickCount();
			break;



		}
		m_ePreState = m_eCurState;
	}
}

