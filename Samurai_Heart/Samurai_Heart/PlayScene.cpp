#include "PlayScene.h"
#include "GameApp.h"
#include "Player.h"
#include "Map.h"
#include "../GameEngineLib/framework.h"

Player* player;
Map* playMap;
Background* backImage;

/// Start
void PlayScene::Start() {
	OutputDebugStringA("PlayScene Start\n");

	// play map
	playMap = new Map(800.f, 600.f, 1500.f, 700.f);

	// image resorce
	backImage = CreateObject<Background>();
	backImage->Init(L"../Resource/Map/Background/BackGround01.png", 
		Vector2(0,0), playMap);

	// player
	player = CreateObject<Player>();
	player->SetPosition(Vector2(100, 500));

	// camera
	Camera::Get().SetSize(800.f, 600.f);

	__super::Start();
}

/// Update
void PlayScene::Update() {
	__super::Update();
	Camera::Get().FollowPlayer(player, playMap);
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