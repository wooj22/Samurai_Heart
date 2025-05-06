#pragma once
#include "../GameEngineLib/framework.h"
#include "../GameEngineLib/WinGameApp.h"
#include "../GameEngineLib/SceneManager.h"
#include "Camera.h"
#include "FadeManager.h"

class GameApp : public WinGameApp
{
public:
	enum sceneName { MENU, PLAY };
	Camera camera;
	FadeManager fadeManager;

	GameApp(int inputWidth = 1920, int inputHeight = 1080) :
		WinGameApp(inputWidth, inputHeight) {};
	~GameApp() override = default;

	void Init() override;
	// update() : WinGameApp class에서 currentScene의 Objects update, render 호출중
	void Release() override;
	void MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};

