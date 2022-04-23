#pragma once

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	float		Get_ScrollX(void) { return m_fScrollX; }
	float		Get_Scrolly(void) { return m_fScrollY; }

public:
	void		Set_ScrollX(float _fX) { m_fScrollX += _fX; }
	void		Set_ScrollY(float _fy) { m_fScrollY += _fy; }
	void		Update();
	void		Key_Input();

public:
	static CScrollMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CScrollMgr;
		}

		return m_pInstance;
	}
	static void		Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CScrollMgr*		m_pInstance;
	float					m_fScrollX = 0.f;
	float					m_fScrollY = 0.f;
};

