#include "PlayScene.h"
#include "GameApp.h"
#include "Player.h"
#include "../GameEngineLib/framework.h"

/// Start
void PlayScene::Start() {
	OutputDebugStringA("PlayScene Start\n");
	Player* player = CreateObject<Player>();
	player->SetPosition(Vector2(1000, 500));

	__super::Start();
}

/// Update
void PlayScene::Update() {
	__super::Update();
	
	if (InputManager::Get().GetKeyDown(VK_SPACE))
		SceneManager::Get().ChangeScene(GameApp::MENU);
}

/// Render
void PlayScene::Render() {
	__super::Render();
	RenderManager::Get().DrawTextW(L"Pressed [Spacebar] -> Menu Scene", 50, 50);
}

/// Exit
void PlayScene::Exit() {
	__super::Exit();

	OutputDebugStringA("PlayScene Exit\n");
}