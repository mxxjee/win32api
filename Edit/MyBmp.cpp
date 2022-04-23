#include "stdafx.h"
#include "MyBmp.h"


CMyBmp::CMyBmp()
{
}


CMyBmp::~CMyBmp()
{
}

void CMyBmp::Load_Bmp(const TCHAR * pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,	// ���α׷� �ν��Ͻ� �ڵ�, ���μ����� ���� �о���� ������ �ƴ϶� ���Ϸκ��� �о�� ���̱� ������ NULL
		pFilePath,  // ���� ���
		IMAGE_BITMAP,  // � Ÿ���� �о�� �� ����
		0,	// ���� ������
		0,	// ���� ������
		LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE : ���Ͽ��� �̹����� �о���̰ڴٴ� �ɼ� LR_CREATEDIBSECTION : �о�� ������ dib���·� ��ȯ

	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CMyBmp::Release(void)
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
