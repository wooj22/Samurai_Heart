#pragma once
#include "../GameEngineLib/Vector2.h"
#include "GameApp.h"

class BoxCollider
{
public:
	Vector2 min;    // left, up
	Vector2 max;    // right, down

    BoxCollider() = default;
	~BoxCollider() = default;

	// Collider Update
    void UpdateCollider(Vector2 position, float width, float height) {
		min.x = position.x - width / 2;
		min.y = position.y - height / 2;
		max.x = position.x + width / 2;
		max.y = position.y + height / 2;
	}

	// AABB Collision Check
    bool isCollision(BoxCollider& other)
    {
        return !(max.x < other.min.x || min.x > other.max.x ||
            max.y < other.min.y || min.y > other.max.y);
    }

	// Draw Collider (Debug)
	void DrawCollider()
	{
		RenderManager::Get().DrawBox(min, max.x - min.x, max.y - min.y);
	}
};

