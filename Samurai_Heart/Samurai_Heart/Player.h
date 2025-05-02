#pragma once
#include "Character.h"

class Player : public Character
{
private:

public:
	Player() {};
	~Player() override {};
	void Start() override;
	void Update() override;
	void Render() override;
};

