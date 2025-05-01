#pragma once
#include "InputManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "RenderManager.h"
#include "Singleton.h"
using namespace std;

class WinGameApp : public Singleton<WinGameApp>
{
private:
	// window
	HINSTANCE		hInstance;		// 실행중인 프로그램 인스턴스 핸들
	HWND			hWnd;			// 윈도우 핸들
	int				width = 1024;
	int				height = 768;
	wstring			winClassName = L"woo";
	wstring			titleName = L"GDI+ Windows Project";
	string			modulePath;
	string			workingPath;

	// managers
	InputManager    inputManager;
	TimeManager     timeManager;
	SoundManager    soundManager;
	RenderManager   renderManager;
	SceneManager    sceneManager;

	void Update();
	void Render();

public:
	bool isLoop = true;

	WinGameApp(int inputWidth = 1920, int inputHeight = 1080) :
		width(inputWidth), height(inputHeight), hInstance(nullptr), hWnd(nullptr) {};
	virtual ~WinGameApp() = default;

	virtual void Init();
	void Run();
	virtual void Release();
	virtual void MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

