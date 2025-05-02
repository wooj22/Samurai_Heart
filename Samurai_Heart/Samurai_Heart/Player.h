#pragma once
#include "Character.h"
#include "../GameEngineLib/framework.h"

class Player : public Character
{
//private:
//	Vector2 position;
//	float width;
//	float height;
//	float halfWidth;
//	float halfHeight;
//
//	Rigidbody rigidbody;
//	BoxCollider collider;


public:
	Player() { OutputDebugStringA("Player Create\n"); }
	~Player() override {};

	void Start() override;
	void Update() override;
	void Render() override;
};

