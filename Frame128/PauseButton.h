#pragma once
#include "Obj.h"
class CPauseButton :
	public CObj
{
public:
	CPauseButton();
	~CPauseButton();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	int		m_iDrawID = 0;
};

