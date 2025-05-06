#include "GameApp.h"
#include "MenuScene.h"
#include "PlayScene.h"

/// Game Init
void GameApp::Init() {
	__super::Init();

	// scene 등록
	SceneManager::Get().CreateScene<MenuScene>();
	SceneManager::Get().CreateScene<PlayScene>();
	
	SceneManager::Get().SetCurrentScene(MENU);
	SceneManager::Get().Init();

	// camera
	Camera::Get().SetSize(1550.f, 400.f);
}

/// Game Release
void GameApp::Release() {
	__super::Release();
}

/// 윈도우 프로시저 메시지 처리
void GameApp::MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	__super::MessageProc(hwnd, uMsg, wParam, lParam);

	// game에 활용할 message 처리
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	}
}