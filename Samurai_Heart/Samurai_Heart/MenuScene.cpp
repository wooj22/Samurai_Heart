#include "MenuScene.h"
#include "GameApp.h"
#include "Map.h"
#include "../GameEngineLib/framework.h"

/// Start
void MenuScene::Start() {
	OutputDebugStringA("MenuScene Start\n");

	// map
	menuMap = new Map(1550.f, 400.f, 1550.f, 400.f);

	// background
	backImage = CreateObject<Background>();
	backImage->Init(L"../Resource/Map/Background/BackGround01.png",
		Vector2(0, 0), menuMap);

	// title
	titleImage = CreateObject<Prop>();
	titleImage->Init(L"../Resource/UI/Title.png",
		Vector2(525, 0));

	// camera
	Camera::Get().SetSize(1550.f, 400.f);

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