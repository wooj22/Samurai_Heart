#include "MenuScene.h"
#include "GameApp.h"
#include "Map.h"
#include "../GameEngineLib/framework.h"

/// Start
void MenuScene::Start() {
	OutputDebugStringA("MenuScene Start\n");

	// fade in
	FadeManager::Get().StartFadeIn(1.5f);

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
	// object
	__super::Update();

	// fade
	FadeManager::Get().Update(TimeManager::Get().GetDeltaTime());

	//change scene
	if (InputManager::Get().GetKeyDown(VK_SPACE)) {
		FadeManager::Get().StartFadeOut(3.f);
	}
	if (FadeManager::Get().GetState() == FadeState::FadeOut) {
		if(FadeManager::Get().IsFadeDone())
			SceneManager::Get().ChangeScene(GameApp::PLAY);
	}
}

/// Render
void MenuScene::Render() {
	// object
	__super::Render();

	// ui
	RenderManager::Get().DrawTextW(L"Pressed Spacebar to Play", 700, 350);

	// fade
	FadeManager::Get().Render();
}

/// Exit
void MenuScene::Exit() {
	__super::Exit();

	OutputDebugStringA("MenuScene Exit\n");
}