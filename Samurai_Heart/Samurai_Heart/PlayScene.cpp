#include "PlayScene.h"
#include "GameApp.h"
#include "Player.h"
#include "Map.h"
#include "../GameEngineLib/framework.h"

Player* player;
Map* playMap;
Background* backImage1;
Background* backImage2;
Ground* ground;

/// Start
void PlayScene::Start() {
	OutputDebugStringA("PlayScene Start\n");

	// play map
	playMap = new Map(800.f, 600.f, 4000.f, 700.f);

	// backgroun
	backImage1 = CreateObject<Background>();
	backImage1->Init(L"../Resource/Map/Background/BackGround01.png", 
		Vector2(0,0), playMap);

	backImage2 = CreateObject<Background>();
	backImage2->Init(L"../Resource/Map/Background/BackGround02.png",
		Vector2(0, 0), playMap);

	// ground
	ground = CreateObject<Ground>();
	ground->Init(L"../Resource/Map/Ground/Ground01.png",
		Vector2(0, 600), playMap);


	// player
	player = CreateObject<Player>();
	player->SetPosition(Vector2(100, 500));

	// camera
	Camera::Get().SetSize(800.f, 600.f);

	__super::Start();
}

/// Update
void PlayScene::Update() {
	// objcet
	__super::Update();

	// camera
	Camera::Get().FollowPlayer(player, playMap);
	Camera::Get().DebugPosition();

	// ground collision
	player->isCollision(ground->GetCollider());
	
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