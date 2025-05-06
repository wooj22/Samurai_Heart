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
	Camera::Get().SetPosition(Vector2(0, 0));

	__super::Start();
}

/// Update
void MenuScene::Update() {
	__super::Update();

	if (InputManager::Get().GetKeyDown(VK_SPACE))
		SceneManager::Get().ChangeScene(GameApp::PLAY);
}

/// Render
void MenuScene::Render() {
	__super::Render();
	RenderManager::Get().DrawTextW(L"Pressed Spacebar to Play", 700, 350);
}

/// Exit
void MenuScene::Exit() {
	__super::Exit();

	OutputDebugStringA("MenuScene Exit\n");
}