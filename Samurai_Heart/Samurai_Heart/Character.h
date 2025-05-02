#pragma once
#include "../GameEngineLib/Object.h"
#include "../GameEngineLib/Vector2.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "Sprite.h"
#include "AnimationClip.h"

class Character : public Object
{
protected:
	// transform
	Vector2 position;
	float width;
	float height;

	// components
	Rigidbody rigidbody;
	BoxCollider collider;
	Sprite* currentSprite;
	AnimationClip* currentAnimation;

public :
	Character() = default;
	~Character() override = default;

	virtual void Start() override {};
	virtual void Update() override {};
	virtual void Render() override {};
};