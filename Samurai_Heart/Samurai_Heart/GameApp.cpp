#include "GameApp.h"
#include "MenuScene.h"
#include "PlayScene.h"

/// Game Init
void GameApp::Init() {
	__super::Init();

	// scene ���
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

/// ������ ���ν��� �޽��� ó��
void GameApp::MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	__super::MessageProc(hwnd, uMsg, wParam, lParam);

	// game�� Ȱ���� message ó��
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	}
}