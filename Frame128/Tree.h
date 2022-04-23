#pragma once
#include "Obj.h"
class CTree :
	public CObj
{
public:
	CTree();
	~CTree();

public:
	virtual void Initialize();
	virtual void Render(HDC hdc);
	virtual void Late_Update();
	virtual void Release();
	virtual int  Update();
};

