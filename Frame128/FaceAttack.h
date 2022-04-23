#pragma once
#include "Obj.h"
class CFaceAttack :
	public CObj
{
public:
	CFaceAttack();
	~CFaceAttack();


public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	
	float			m_fTime;
};

