#pragma once
#include "../GameEngineLib/Scene.h"
#include "UIManager.h"

class Player;
class Boss;
class Map;
class Background;
class Prop;
class Ground;
class Wall;
class UI_Text;
class UI_Image;

class PlayScene : public Scene
{
public:
	PlayScene() = default;
	~PlayScene() = default;

	void Start() override;
	void Update() override;
	void Render() override;
	void Exit() override;

private:
	Player* player;
	Boss* boss;

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
	Wall* wall1;
	Wall* wall2;
	Wall* wall3;
	Wall* wall4;
	Wall* wall5;
	Wall* wall6;

	UI_Text* bossHp_text;
	UI_Image* bossHp_Image;

	UI_Text* playerHp_text;
	UI_Image* playerHp_Image;

	UI_Text* playerCharge_text;
	UI_Image* playerChage_Image;

	UI_Text* info1_text;
	UI_Text* info2_text;

	// ui manager
	UIManager UiManager;	

	void CreateMap();
	void CreateUI();
};

