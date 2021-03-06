// Week11.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Week11.h"
#include <string.h>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

LPWSTR g_lpCmdLine;
DWORD pid;

BOOLEAN flag;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	
	WCHAR buf[128] = { 0, };
	

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	//g_lpCmdLine = lpCmdLine;

	int value = 0;
	value = _wtoi(lpCmdLine);	//_wtoi() 문자열 형식으로 가지고 있는 값을 실수로 변경

	pid = (int) value;
	wsprintfW(buf, L"Recv value: %d", value);
	MessageBox(NULL, buf, buf, MB_OK);
	
	
	

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WEEK11, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WEEK11));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WEEK11));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WEEK11);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

// OS가 프로세스를 생성한 다음 프로세스의 정보를 반환 받기 위한 용도이다.
//생성 후 반환되는 프로세스의 정보
PROCESS_INFORMATION g_pi;	//글로벌 프로세스 인포메이션
//실행되는 프로세스의 초기 상태 값
//생성 전 필요한 설정 정보
STARTUPINFO g_si;



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_RBUTTONDOWN:
	{
		HANDLE handle;
		//TerminateProcess(g_pi.hProcess, 0);

		//handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());	//반환값이 핸들임 ( 어떤 프로세스에 대한 핸들값을 얻어오는 것)	첫번째 인수 프로세스의 모든 권한을 달라 세번째 인수 PID(그 PID에 해당하는 프로세스의 핸들을 얻을 수 있도록)
		
		
			handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
			TerminateProcess(handle, 0);	
		
		
		
		
		

		

		//ExitProcess(0);
	}break;

	
	case WM_LBUTTONDOWN:
	{
		DWORD a;

		WCHAR buf[128] = { };
		WCHAR note[128] = L"c:\\windows\\system32\\notepad.exe";
		WCHAR me[128] = L"C:\\Users\\dongn\\source\\repos\\Week11\\Debug\\Week11.exe";		//내 프로세스 위치 정보
		
		
		//자식을 만들어주는 놈임
		//CreateProcess(NULL,note,NULL,NULL,FALSE,0,NULL,NULL,&g_si,&g_pi);
		CreateProcess(NULL, note , NULL, NULL, FALSE, 0, NULL, NULL, &g_si, &g_pi);

		
		wsprintfW(me, L"C:\\Users\\dongn\\source\\repos\\Week11\\Debug\\Week11.exe %d", g_pi.dwProcessId);
		
		MessageBox(NULL, me, L"메모장 pid를 가진 경로", MB_OK);
		
		
		//pid = g_pi.dwProcessId;

		
		
		CreateProcess(NULL, me,NULL,NULL,FALSE,0, NULL,NULL,&g_si,&g_pi);
		
		



		
		
		
		
		
		//과제
		//lbuttondown이 되면 노트패드가 실행되고 m'이 자신의 형제인 노트패드를 terminate시킴
		//메인 프로그램에서 노트패드를 실행해서 자기 자신을 죽이는 건 아무 문제가 없다.
		//하지만 m'가 실행이됬을때 m'가 notepad를 죽이려면 notepad의 정보를 알고있어야 죽일 수 있다.
	}

		break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
			WCHAR buf[128] = { 0, };
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
			wsprintfW(buf, L"Child - PID[ %d ] TID[ %d ]", g_pi.dwProcessId, g_pi.dwThreadId);
			TextOut(hdc, 10, 10, buf, lstrlen(buf));
			wsprintfW(buf, L"My Information - PID[ %d ] TID[ %d ]",
				GetCurrentProcessId(), GetCurrentThreadId());
			TextOut(hdc, 10, 30, buf, lstrlenW(buf));
			

            EndPaint(hWnd, &ps);
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

// 정보 대화 상자의 메시지 처리기입니다.
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
