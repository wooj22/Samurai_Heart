#include "PlayScene.h"
#include "GameApp.h"
#include "Player.h"
#include "Map.h"
#include "../GameEngineLib/framework.h"

Player* player;
Map* playMap;
Background* backImage1;
Background* backImage2;
Prop* prop1;
Prop* prop2;
Prop* prop3;
Prop* prop4;
Prop* prop5;
Prop* prop6;
Prop* prop7;
Prop* prop8;
Prop* prop9;
Prop* prop10;
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

	// prop
	prop1 = CreateObject<Prop>();
	prop1->Init(L"../Resource/Map/Props/House01.png",
		Vector2(0, 234));

	prop2= CreateObject<Prop>();
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

	// player
	player = CreateObject<Player>();
	player->SetPosition(Vector2(100, 300));

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