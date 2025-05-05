#pragma once
#include "../GameEngineLib/Vector2.h"
#include "Camera.h"
#include "GameApp.h"
#include <cstdio>
#include <Windows.h>

class BoxCollider
{
public:
	Vector2 min;    // left, up
	Vector2 max;    // right, down

	Vector2 screenMin;
	Vector2 screenMax;

    BoxCollider() = default;
	~BoxCollider() = default;

	// Collider Update
    void UpdateCollider(Vector2 position, float width, float height) {
		min.x = position.x - width / 2;
		min.y = position.y - height / 2;
		max.x = position.x + width / 2;
		max.y = position.y + height / 2;
	}

	// Screen Collider Update (Draw¿ë)
	void UpdateScreenCollider(Vector2 screenPos, float width, float height) {
		screenMin.x = screenPos.x - width / 2;
		screenMin.y = screenPos.y - height / 2;
		screenMax.x = screenPos.x + width / 2;
		screenMax.y = screenPos.y + height / 2;
	}

	// AABB Collision Check
    bool isCollision(BoxCollider other)
    {
        return !(max.x < other.min.x || min.x > other.max.x ||
            max.y < other.min.y || min.y > other.max.y);
    }

	// Draw Collider (Debug)
	void DrawCollider()
	{
		// world
		//RenderManager::Get().DrawBox(min, max.x - min.x, max.y - min.y);
	
		// screen
		RenderManager::Get().DrawBox(screenMin, screenMax.x - screenMin.x, screenMax.y - screenMin.y);
	}

	// Print Collider (Debug)
	void PrintCollider() {
		// ¿ùµå ÁÂÇ¥
		float worldWidth = max.x - min.x;
		float worldHeight = max.y - min.y;
		Vector2 worldCenter = {
			min.x + worldWidth / 2,
			min.y + worldHeight / 2
		};

		// ½ºÅ©¸° ÁÂÇ¥
		float screenWidth = screenMax.x - screenMin.x;
		float screenHeight = screenMax.y - screenMin.y;
		Vector2 screenCenter = {
			screenMin.x + screenWidth / 2,
			screenMin.y + screenHeight / 2
		};

		char buffer[300];
		sprintf_s(buffer,
			"[World]  Pos: (%.1f, %.1f), W: %.1f, H: %.1f\n"
			"[Screen] Pos: (%.1f, %.1f), W: %.1f, H: %.1f\n",
			worldCenter.x, worldCenter.y, worldWidth, worldHeight,
			screenCenter.x, screenCenter.y, screenWidth, screenHeight
		);
		OutputDebugStringA(buffer);
	}
};

