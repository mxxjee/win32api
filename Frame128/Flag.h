#pragma once
#include "Obj.h"
class CFlag :
	public CObj
{
public:
	CFlag();
	~CFlag();

public:
	virtual void Initialize();
	virtual void Render(HDC hdc);
	virtual void Late_Update();
	virtual void Release();
	virtual int  Update();
};

