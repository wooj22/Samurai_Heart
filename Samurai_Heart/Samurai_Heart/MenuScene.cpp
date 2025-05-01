#include "MenuScene.h"
#include "GameApp.h"
#include "../GameEngineLib/framework.h"

/// Start
void MenuScene::Start() {
	OutputDebugStringA("MenuScene Start\n");

	__super::Start();
}

/// Update
void MenuScene::Update() {
	__super::Update();

	if (InputManager::Get().IsKeyPressed(VK_SPACE))
		SceneManager::Get().ChangeScene(GameApp::PLAY);
}

/// Render
void MenuScene::Render() {
	__super::Render();
	RenderManager::Get().DrawTextW(L"[Menu Scene] Pressed Spacebar", 50, 50);
}

/// Exit
void MenuScene::Exit() {
	__super::Exit();

	OutputDebugStringA("MenuScene Exit\n");
}