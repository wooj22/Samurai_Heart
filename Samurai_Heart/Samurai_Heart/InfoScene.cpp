#include "InfoScene.h"
#include "GameApp.h"
#include "../GameEngineLib/framework.h"

/// Start
void InfoScene::Start() {
	OutputDebugStringA("InfoScene Start\n");

	__super::Start();
}

/// Update
void InfoScene::Update() {
	__super::Update();

	if (InputManager::Get().IsKeyPressed(VK_SPACE))
		SceneManager::Get().ChangeScene(GameApp::MENU);
}

/// Render
void InfoScene::Render() {
	__super::Render();
	RenderManager::Get().DrawTextW(L"[Info Scene] Pressed Spacebar", 50, 50);
}

/// Exit
void InfoScene::Exit() {
	__super::Exit();

	OutputDebugStringA("InfoScene Exit\n");
}