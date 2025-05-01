#pragma once
#include "../GameEngineLib/Scene.h"

class InfoScene : public Scene
{
public :
	InfoScene() = default;
	~InfoScene() = default;

	void Start() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

