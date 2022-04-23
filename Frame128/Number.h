#pragma once
#include "Obj.h"
class CNumber :
	public CObj
{
public:
	CNumber();
	~CNumber();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	TCHAR*	One(int	_iScore); 
	TCHAR*	Two(int	_iScore);
	TCHAR*	Three(int	_iScore);


	TCHAR*	m_pTwoKey;
	TCHAR*	m_pThreeKey;

	int		iCnt;
};

