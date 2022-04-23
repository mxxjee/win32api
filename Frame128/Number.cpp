#include "stdafx.h"
#include "Number.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "StageClear.h"


CNumber::CNumber()
	:m_pTwoKey(nullptr),m_pThreeKey(nullptr),iCnt(0)
{
}


CNumber::~CNumber()
{
}

void CNumber::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Number/0.bmp", L"0");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Number/1.bmp", L"1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Number/2.bmp", L"2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Number/3.bmp", L"3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Number/4.bmp", L"4");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Number/5.bmp", L"5");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Number/6.bmp", L"6");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Number/7.bmp", L"7");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Number/8.bmp", L"8");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Number/9.bmp", L"9");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stageclear_2.bmp", L"stageclear");

	m_pFrameKey = L"1";
	m_pTwoKey = L"1";
	m_pThreeKey = L"1";

	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 70.f;
	
	m_eRender = RENDER_EFFECT;
}

int CNumber::Update(void)
{
	One(60);
	Two(60);
	Three(60);

	++iCnt;
	Update_Rect();
	return OBJ_NOEVENT;
}

void CNumber::Late_Update(void)
{
	/*if (iCnt == 1)
		CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CStageClear>::Create());*/
	
}

void CNumber::Render(HDC hDC)
{
	
	HDC		hFrontMemDC = CBmpMgr::Get_Instance()->Find_Image(L"stageclear");

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	HDC		hMemDC1 = CBmpMgr::Get_Instance()->Find_Image(m_pTwoKey);
	HDC		hMemDC2 = CBmpMgr::Get_Instance()->Find_Image(m_pThreeKey);

	BitBlt(hDC,
		200, 100,
		400,
		400,
		hFrontMemDC,
		0,
		0,
		SRCCOPY);


	GdiTransparentBlt(hDC,
		(int)m_tRect.left + 60, // 2, 3���� : ���� ���� ��ġ X,Y ��ǥ
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 4,5���� : ���� ���� X,Y ����
		(int)m_tInfo.fCY,
		hMemDC,
		0,
		0,
		(int)m_tInfo.fCX,		// 9. 10���� : ������ ��Ʈ���� X,Y ������
		(int)m_tInfo.fCY,
		RGB(0, 64, 64));	// 11���� : ������ ���� 

	GdiTransparentBlt(hDC,
		(int)m_tRect.left-10 , // 2, 3���� : ���� ���� ��ġ X,Y ��ǥ
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 4,5���� : ���� ���� X,Y ����
		(int)m_tInfo.fCY,
		hMemDC1,
		0,
		0,
		(int)m_tInfo.fCX,		// 9. 10���� : ������ ��Ʈ���� X,Y ������
		(int)m_tInfo.fCY,
		RGB(0, 64, 64));	// 11���� : ������ ���� 

	GdiTransparentBlt(hDC,
		(int)m_tRect.left - 80, // 2, 3���� : ���� ���� ��ġ X,Y ��ǥ
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 4,5���� : ���� ���� X,Y ����
		(int)m_tInfo.fCY,
		hMemDC2,
		0,
		0,
		(int)m_tInfo.fCX,		// 9. 10���� : ������ ��Ʈ���� X,Y ������
		(int)m_tInfo.fCY,
		RGB(0, 64, 64));	// 11���� : ������ ���� 
}

void CNumber::Release(void)
{

}

TCHAR * CNumber::One(int _iScore)
{
	if ((_iScore % 10) == 0)
		m_pFrameKey = L"0";
	
	if ((_iScore % 10) == 1)
		m_pFrameKey = L"1";

	if ((_iScore % 10) == 2)
		m_pFrameKey = L"2";

	if ((_iScore % 10) == 3)
		m_pFrameKey = L"3";

	if ((_iScore % 10) == 3)
		m_pFrameKey = L"3";

	if ((_iScore % 10) == 4)
		m_pFrameKey = L"4";

	if ((_iScore % 10) == 5)
		m_pFrameKey = L"5";

	if ((_iScore % 10) == 6)
		m_pFrameKey = L"6";

	if ((_iScore % 10) == 7)
		m_pFrameKey = L"7";

	if ((_iScore % 10) == 8)
		m_pFrameKey = L"8";

	if ((_iScore % 10) == 9)
		m_pFrameKey = L"9";

	return m_pFrameKey;
}

TCHAR * CNumber::Two(int _iScore)
{
	if (0== (_iScore % 100)/10 )
		m_pTwoKey = L"0";

	if (1== (_iScore % 100)/10 )
		m_pTwoKey = L"1";

	if (2 == (_iScore % 100) / 10)
		m_pTwoKey = L"2";

	if (3 == (_iScore % 100) / 10)
		m_pTwoKey = L"3";

	if (4 == (_iScore % 100) / 10)
		m_pTwoKey = L"4";

	if (5 == (_iScore % 100) / 10)
		m_pTwoKey = L"5";

	if (6 == (_iScore % 100) / 10)
		m_pTwoKey = L"6";

	if (7 == (_iScore % 100) / 10)
		m_pTwoKey = L"7";
	
	if (8 == (_iScore % 100) / 10)
		m_pTwoKey = L"8";

	if (9 == (_iScore % 100) / 10)
		m_pTwoKey = L"9";

	return m_pTwoKey;
}

TCHAR * CNumber::Three(int _iScore)
{
	if (((_iScore % 1000) / 100) == 0)
		m_pThreeKey = L"0";

	if (((_iScore % 1000) / 100) == 1)
		m_pThreeKey = L"1";

	if (((_iScore % 1000) / 100) == 2)
		m_pThreeKey = L"2";

	if (((_iScore % 1000) / 100) == 3)
		m_pThreeKey = L"3";

	if (((_iScore % 1000) / 100) == 3)
		m_pThreeKey = L"3";

	if (((_iScore % 1000) / 100) == 4)
		m_pThreeKey = L"4";

	if (((_iScore % 1000) / 100) == 5)
		m_pThreeKey = L"5";

	if (((_iScore % 1000) / 100) == 6)
		m_pThreeKey = L"6";

	if (((_iScore % 1000) / 100) == 7)
		m_pThreeKey = L"7";

	if (((_iScore % 1000) / 100) == 8)
		m_pThreeKey = L"8";

	if (((_iScore % 1000) / 100) == 9)
		m_pThreeKey = L"9";

	return m_pThreeKey;
}
