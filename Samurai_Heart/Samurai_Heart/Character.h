#pragma once
#include "../GameEngineLib/Object.h"
#include "../GameEngineLib/Vector2.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "Sprite.h"
#include "Animation.h"

// player¿Í bossÀÇ base class
class Character : public Object
{
private:
	Vector2 position;
	float width;
	float height;
	float halfWidth;
	float halfHeight;

	Rigidbody rigidbody;
	BoxCollider collider;
	Sprite sprite;
	Animation animation;

public :
	Character() = default;
	~Character() override = default;

	virtual void Start() override {};
	virtual void Update() override {};
	virtual void Render() override {};
};