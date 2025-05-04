#include "PlayScene.h"
#include "GameApp.h"
#include "Player.h"
#include "../GameEngineLib/framework.h"

/// Start
void PlayScene::Start() {
	OutputDebugStringA("PlayScene Start\n");
	Player* player = CreateObject<Player>();
	player->SetPosition(Vector2(300, 300));

	__super::Start();
}

/// Update
void PlayScene::Update() {
	__super::Update();
	
	if (InputManager::Get().GetKeyDown('M'))
		SceneManager::Get().ChangeScene(GameApp::MENU);
}

/// Render
void PlayScene::Render() {
	__super::Render();
	RenderManager::Get().DrawTextW(L"Pressed [M] -> Menu Scene", 50, 50);
}

/// Exit
void PlayScene::Exit() {
	__super::Exit();

	OutputDebugStringA("PlayScene Exit\n");
}