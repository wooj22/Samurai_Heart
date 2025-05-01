#pragma once
#include "../GameEngineLib/Scene.h"

class PlayScene : public Scene
{
public:
	PlayScene() = default;
	~PlayScene() = default;

	void Start() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

