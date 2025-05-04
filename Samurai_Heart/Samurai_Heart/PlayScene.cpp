#include "PlayScene.h"
#include "GameApp.h"
#include "Player.h"
#include "Map.h"
#include "../GameEngineLib/framework.h"

Player* player;
Map* map;

/// Start
void PlayScene::Start() {
	OutputDebugStringA("PlayScene Start\n");

	map = new Map(800.f, 600.f, 2000.f, 600.f);
	player = CreateObject<Player>();
	player->SetPosition(Vector2(1500, 300));
	Camera::Get().SetSize(800.f, 600.f);

	__super::Start();
}

/// Update
void PlayScene::Update() {
	__super::Update();
	Camera::Get().FollowPlayer(player, map);
	Camera::Get().DebugPosition();
	

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