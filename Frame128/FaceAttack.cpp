#include "stdafx.h"
#include "FaceAttack.h"


CFaceAttack::CFaceAttack()
	:m_fTime(0.f)
{
}


CFaceAttack::~CFaceAttack()
{
}

void CFaceAttack::Initialize(void)
{
	m_tInfo.fX = 200.f;
	m_tInfo.fY = 500.f;
	m_tInfo.fCX = 700.f;
	m_tInfo.fCY = 200.f;

	m_eRender = RENDER_OBJ;
}

int CFaceAttack::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_fTime += 1.f;

	if (m_fTime >= 150)
	{
		m_bDead = true;
		m_fTime = 0.f;
	}


	Update_Rect();
	return OBJ_NOEVENT;
}

void CFaceAttack::Late_Update(void)
{
}

void CFaceAttack::Render(HDC hDC)
{
	/*Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);*/
}

void CFaceAttack::Release(void)
{
}
