#pragma once
#include "Obj.h"
class CNumber5 :
	public CObj
{
public:
	CNumber5();
	~CNumber5();

	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	TCHAR*	One(int	_iScore);
	TCHAR*	Two(int	_iScore);

	TCHAR*	m_pTwoKey;
};

