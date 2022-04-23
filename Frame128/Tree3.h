#pragma once
#include "Obj.h"
class CTree3 :
	public CObj
{
public:
	CTree3();
	~CTree3();

public:
	virtual void Initialize();
	virtual void Render(HDC hdc);
	virtual void Late_Update();
	virtual void Release();
	virtual int  Update();
};