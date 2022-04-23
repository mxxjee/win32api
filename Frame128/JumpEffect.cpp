#include "stdafx.h"
#include "JumpEffect.h"


CJumpEffect::CJumpEffect()
	:m_fTime(0.f)
{
}


CJumpEffect::~CJumpEffect()
{
}

void CJumpEffect::Initialize(void)
{
	m_tInfo.fCX =80.f;
	m_tInfo.fCY = 30.f;

	m_eRender = RENDER_OBJ;

}

int CJumpEffect::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CJumpEffect::Late_Update(void)
{
	m_fTime += 1.f;

	if (m_fTime >=30)
	{
		m_bDead = true;
		m_fTime = 0.f;
	}
}

void CJumpEffect::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CJumpEffect::Release(void)
{
}

void CJumpEffect::Motion_Change()
{
}
