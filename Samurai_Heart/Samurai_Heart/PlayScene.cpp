#include "PlayScene.h"
#include "GameApp.h"
#include "Player.h"
#include "Boss.h"
#include "Map.h"
#include "../GameEngineLib/framework.h"

/// Start
void PlayScene::Start() {
	OutputDebugStringA("PlayScene Start\n");

	// map
	CreateMap();

	// player
	player = CreateObject<Player>();
	player->SetPosition(Vector2(100, 300));

	// boss
	boss = CreateObject<Boss>();
	boss->SetPosition(Vector2(1000, 150));

	// set
	player->SetBoss(boss);
	boss->SetPlayer(player);

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

	// collision - ground
	player->isCollision(ground->GetCollider());
	boss->isCollision(ground->GetCollider());

	// collision - wall
	if (player->isCollision(wall1->GetCollider()) ||
		player->isCollision(wall2->GetCollider()) ||
		player->isCollision(wall3->GetCollider()) ||
		player->isCollision(wall4->GetCollider()) ||
		player->isCollision(wall5->GetCollider()) ||
		player->isCollision(wall6->GetCollider()))
	{
		player->isWall = true;
	}
	else
		player->isWall = false;

	
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


// Cerate Map
void PlayScene::CreateMap() {
	// play map
	playMap = new Map(800.f, 600.f, 4000.f, 700.f);

	// backgroun
	backImage1 = CreateObject<Background>();
	backImage1->Init(L"../Resource/Map/Background/BackGround01.png",
		Vector2(0, 0), playMap);

	backImage2 = CreateObject<Background>();
	backImage2->Init(L"../Resource/Map/Background/BackGround02.png",
		Vector2(0, 0), playMap);

	// prop
	prop1 = CreateObject<Prop>();
	prop1->Init(L"../Resource/Map/Props/House01.png",
		Vector2(0, 234));

	prop2 = CreateObject<Prop>();
	prop2->Init(L"../Resource/Map/Props/House02.png",
		Vector2(336, 112));

	prop3 = CreateObject<Prop>();
	prop3->Init(L"../Resource/Map/Props/House03.png",
		Vector2(756, 264));

	prop4 = CreateObject<Prop>();
	prop4->Init(L"../Resource/Map/Props/House01.png",
		Vector2(1198, 234));

	prop5 = CreateObject<Prop>();
	prop5->Init(L"../Resource/Map/Props/House02.png",
		Vector2(1564, 112));

	prop6 = CreateObject<Prop>();
	prop6->Init(L"../Resource/Map/Props/House03.png",
		Vector2(2006, 264));

	prop7 = CreateObject<Prop>();
	prop7->Init(L"../Resource/Map/Props/House01.png",
		Vector2(2448, 234));

	prop8 = CreateObject<Prop>();
	prop8->Init(L"../Resource/Map/Props/House02.png",
		Vector2(2814, 112));

	prop9 = CreateObject<Prop>();
	prop9->Init(L"../Resource/Map/Props/House03.png",
		Vector2(3234, 264));

	prop10 = CreateObject<Prop>();
	prop10->Init(L"../Resource/Map/Props/House01.png",
		Vector2(3700, 234));

	// ground
	ground = CreateObject<Ground>();
	ground->Init(L"../Resource/Map/Ground/Ground01.png",
		Vector2(0, 600), playMap);

	// wall
	wall1 = CreateObject<Wall>();
	wall1->Init(L"../Resource/Map/Ground/Wall.png",
		Vector2(0, 300));

	wall2 = CreateObject<Wall>();
	wall2->Init(L"../Resource/Map/Ground/Wall.png",
		Vector2(1000, 300));

	wall3 = CreateObject<Wall>();
	wall3->Init(L"../Resource/Map/Ground/Wall.png",
		Vector2(1350, 300));

	wall4 = CreateObject<Wall>();
	wall4->Init(L"../Resource/Map/Ground/Wall.png",
		Vector2(2300, 300));

	wall5 = CreateObject<Wall>();
	wall5->Init(L"../Resource/Map/Ground/Wall.png",
		Vector2(2650, 300));

	wall6 = CreateObject<Wall>();
	wall6->Init(L"../Resource/Map/Ground/Wall.png",
		Vector2(4000, 300));
}