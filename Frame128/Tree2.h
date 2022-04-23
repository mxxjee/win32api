#pragma once
#include "Obj.h"
class CTree2 :
	public CObj
{
public:
	CTree2();
	~CTree2();

public:
	virtual void Initialize();
	virtual void Render(HDC hdc);
	virtual void Late_Update();
	virtual void Release();
	virtual int  Update();
};

