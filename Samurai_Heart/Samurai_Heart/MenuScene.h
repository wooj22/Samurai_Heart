#pragma once
#include "../GameEngineLib/Scene.h"

class MenuScene : public Scene
{
public:
	MenuScene() = default;
	~MenuScene() = default;

	void Start() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

