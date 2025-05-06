#pragma once
#include "../GameEngineLib/Scene.h"

class Map;
class Background;
class Prop;

class MenuScene : public Scene
{
public:
	MenuScene() = default;
	~MenuScene() = default;

	void Start() override;
	void Update() override;
	void Render() override;
	void Exit() override;

private:
	Map* menuMap;
	Background* backImage;
	Prop* titleImage;
};

