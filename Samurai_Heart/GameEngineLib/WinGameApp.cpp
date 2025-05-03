#include "pch.h"
#include "WinGameApp.h"
#include <sstream>

/*
* [WindowProc 윈도우 프로시저 메시지 콜백]
* MessageProc는 전역함수여야 하기 때문에 CreateWindowEx에 this를 넘겨 윈도우 클래스에 등록한다.
* HWND hwnd : 윈도우 핸들
* UINT uMsg : 윈도우 메시지
* WPARAM wParam : 정수 또는 포인터 크기
* LPARAM lParam : 비트필드 or WORD (x, y)
*/

// 게임 콘텐츠에서 윈도우 프로시저의 기능을 활용하기 위해 MessageProc()멤버 함수를 만들어 활용한다.
// 멤버 함수에 접근하기 위해서는 우선 생성된 객체를 찾아야 한다.
// lpCreateParams는 CREATESTRUCT(윈도우 생성 정보 구조체) 안에 있는 멤버 중 하나로,
// CreateWindowEx 함수 호출 시, WM_NCCREATE 메시지(윈도우 생성 가장 초기에 호출)를 통해 
// 윈도우 프로시저에 LPARAM lParam 매개변수로 전달된다.
// 즉, CreateWindowEx의 마지막 인자로 전달한 this 포인터가 WM_NCCREATE 메시지가 발생할 때
// lParam으로 전달되는 CREATESTRUCT 구조체 안의 lpCreateParams에 저장되어있는 것

// Q. 궁금한거 싱글톤이라면 객체를 굳이 찾지 않아도 되지 않는것 아닌가?
//    WinGameApp::Get().MessageProc(hwnd, uMsg, wParam, lParam);
// A. 맞다.
// Q. 그렇다면 왜 포인터를 저장하는 방식이 쓰일까?
// A. 다중 인스턴스 확장성을 고려하기 때문이다.
//    멀티 윈도우를 만들거나 여러개의 윈도우를 제어할때는 윈도우 클래스가 하나가 아닌 다중 인스턴스일 것이고
//	  윈도우 각각의 this를 저장하여 메세지를 받을때 마다 윈도우핸들에 설정된 주소로 MessageProc 를 호출해야하기 때문이다.

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	WinGameApp* pThis = nullptr;

	// 윈도우 생성시
	if (uMsg == WM_NCCREATE)
	{
		// lParam매개변수에서 this 추출
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		pThis = reinterpret_cast<WinGameApp*>(cs->lpCreateParams);

		// 윈도우 핸들의 GWLP_USERDATA(사용자 데이터 공간)에 this 저장
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
	}
	else {
		pThis = reinterpret_cast<WinGameApp*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (pThis)
		pThis->MessageProc(hwnd, uMsg, wParam, lParam);		// 객체의 멤버 함수 호출
	
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/// 메시지 처리
void WinGameApp::MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	// 게임 콘텐츠에서 override
}

/// Init
void WinGameApp::Init() 
{
	// module path save
	char szPath[MAX_PATH] = { 0, };
	GetModuleFileNameA(NULL, szPath, MAX_PATH);
	modulePath = szPath;
	OutputDebugStringA(string(string(modulePath) + string("\n")).c_str());

	// directory path save
	GetCurrentDirectoryA(MAX_PATH, szPath);
	workingPath = szPath;
	OutputDebugStringA(string(string(workingPath) + string("\n")).c_str());

	// get program handle
	hInstance = GetModuleHandle(NULL);

	// window class 정의
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WindowProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;
	wc.lpszClassName = winClassName.c_str();
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	RegisterClassEx(&wc);

	SIZE clientSize = { width, height };
	RECT clientRect = { 0, 0, clientSize.cx, clientSize.cy };
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);

	// window 창 생성  -> WM_NCCREATE 메시지 발생
	hWnd = CreateWindowEx(
		0,
		winClassName.c_str(),
		titleName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top,
		NULL,
		NULL,
		hInstance,
		this  // this가 WindowProc를 통해 CREATESTRUCT 구조체 타입의 lParamdp 에 저장된다
	);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// managers init
	inputManager.Init(hWnd);
	timeManager.Init();
	soundManager.Init();
	renderManager.Init(hWnd, width, height);
}

/// Update
void WinGameApp::Update()
{
	inputManager.Update();
	timeManager.Update();
	sceneManager.Update();
}

/// Render
void WinGameApp::Render()
{
	renderManager.DrawBackground();
	sceneManager.Render();
	renderManager.DrawBackToFront();
}

/// GameLoop
void WinGameApp::Run()
{
	MSG msg = {};
	while (isLoop)
	{
		// message
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// game
		Update();
		Render();
	}
}

/// Release
void WinGameApp::Release() 
{
	// managers release
	inputManager.Release();
	timeManager.Release();
	soundManager.Release();
	sceneManager.Release();
	renderManager.Release();
}

