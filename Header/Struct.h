#pragma once

typedef struct tagInfo
{
	float	fX; 
	float	fY;
	float	fCX;
	float	fCY;
	/*int		iAttack=0;
	int		iHp=0;*/
}INFO;

typedef struct tagPointPos
{
	float	fX;
	float	fY;

	tagPointPos() { ZeroMemory(this, sizeof(tagPointPos)); }
	tagPointPos(float _fX, float _fY)
		: fX(_fX), fY(_fY){	}

}POINTPOS;

typedef	struct tagLineInfo
{
	POINTPOS tLeftPoint;
	POINTPOS tRightPoint;

	tagLineInfo(void) { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(POINTPOS& tLeft, POINTPOS& tRight)
		: tLeftPoint(tLeft), tRightPoint(tRight)	{}

}LINEINFO;

typedef struct tagFrame
{
	int		iFrameStart;
	int		iFrameEnd;
	int		iFrameMotion;
	int		iPosX;
	int		iPosY;
	int		iSizeX;
	int		iSizeY;

	DWORD	dwFrameSpeed;
	DWORD	dwFrameTime;

}FRAME;