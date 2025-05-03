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

	if (InputManager::Get().GetKeyDown('P'))
		SceneManager::Get().ChangeScene(GameApp::PLAY);

	if(InputManager::Get().GetKeyDown('I'))
		SceneManager::Get().ChangeScene(GameApp::INFO);
}

/// Render
void MenuScene::Render() {
	__super::Render();
	RenderManager::Get().DrawTextW(L"Samurai Heart", 50, 50);
	RenderManager::Get().DrawTextW(L"Pressed [P] -> Play Scene", 50, 80);
	RenderManager::Get().DrawTextW(L"Pressed [I] -> Info Scene", 50, 120);
}

/// Exit
void MenuScene::Exit() {
	__super::Exit();

	OutputDebugStringA("MenuScene Exit\n");
}