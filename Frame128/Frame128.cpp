// Frame128.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Frame128.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// ���� ����:
HWND	  g_hWnd;
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);		// ���� ������ â�� ����� ���� â �Ӽ�, ��Ÿ���� �����ϴ� �Լ�
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,			// �޸𸮿� �Ҵ�Ǵ� ��ü, �� ��ü
                     _In_opt_ HINSTANCE hPrevInstance,	// ���� ����Ǿ��� �ν��Ͻ��� �ڵ� ��, ���� ��� null, ȣȯ���� ���� ������ �� �츮�� ����� �� ����
                     _In_ LPWSTR    lpCmdLine,			// LP�� �����͸� ����, LPTSTR ���ڿ� �����͸� �ǹ�, TSTR: �����ڵ�, �ƽ�Ű�ڵ� ��� ȣȯ
                     _In_ int       nCmdShow)			// ������ â�� ��Ÿ���� �����ϴ� ���ڰ��� �ش�
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FRAME128, szWindowClass, MAX_LOADSTRING);

    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FRAME128));

    MSG msg;
	msg.message = WM_NULL;

	CMainGame*	pMainGame = new CMainGame;

	if (nullptr != pMainGame)
		pMainGame->Initialize();

	DWORD dwTime = GetTickCount();	//958
		  
	while (true)
	{
		// PM_REMOVE : �޼��� �о�Ȱ� ���ÿ� �޽��� ť���� �޽����� �����ϴ� �ɼ�
		// PM_NOREMOVE : �޼��� ť�� �޼����� �����ϴ����� �ľ�, �޽����� �о������ GetMessage�Լ��� �ٽ� ȣ��

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))		// Ű���� �޼����� �����Ͽ� ���α׷����� ���� ����� �� �ֵ��� ���ִ� �Լ�
			{
				TranslateMessage(&msg);	// getmessage���� ������ �޽����� �����Ѵ�.
				DispatchMessage(&msg);	// �ý��� �޼��� ť���� ���� �޼����� ���α׷��� �˼� �ִ� �޼����� ��ȯ�ϴ� �Լ�(->wndProc�� ����)
			}
		}	
		else
		{
			// �츮�� ���� update �Ǵ� render �Լ��� �ǽð����� ȣ��

			// GetDC();
			// GetAsyncKeyState()

				// 1024 + 10		980
			if (dwTime + 10 < GetTickCount())
			{
				//srand((unsigned)time(NULL));

				pMainGame->Update();
				pMainGame->Late_Update();
				pMainGame->Render();

				//1024
				dwTime = GetTickCount();
			}	

			/*pMainGame->Update();
			pMainGame->Late_Update();
			pMainGame->Render();*/
		}
	}

	if (nullptr != pMainGame)
	{
		/*delete pMainGame;
		pMainGame = nullptr;*/

		Safe_Delete(pMainGame);
	}


    return (int) msg.wParam;
} 



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FRAME128));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	RECT	rc{ 0, 0 , WINCX, WINCY };

   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   // ��� ������ �������ִ� �Լ�

   // rc = rc������ + �⺻ â �ɼ� ������ + �޴� �� ������ ��� ���� 
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   HWND hWnd = CreateWindowW(szWindowClass, // ������ ������ Ŭ������ ������ �̸��� �״�� �־��ش�
	   szTitle, // ������ â ����� �̸��� ��Ÿ�� ���ڿ�
	   WS_OVERLAPPEDWINDOW, // ������� �ϴ� ������ â�� ���¸� ����, �⺻�� �ɼ�
       200, 50,	// ������� x,y ��, ������ â�� �����ϴ� ��ġ
	   rc.right - rc.left, rc.bottom - rc.top,	// ������ ������ â�� ����, ���� ������
	   nullptr, 
	   nullptr, 
	   hInstance, 
	   nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;	
		}
		break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �޴� ������ ���� �м��մϴ�.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(g_hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
  

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
