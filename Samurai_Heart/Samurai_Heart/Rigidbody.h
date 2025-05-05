#pragma once
#include "../GameEngineLib/Vector2.h"

// 위치 적용은 외부에서
// position += rigidbody.GetVelocity() * deltaTime;

class Rigidbody
{
private:
    Vector2 velocity = { 0, 0 };       // 현재 속도
    float gravity = 980.0f;            // 중력 가속도 (픽셀/초^2)
    bool useGravity = true;            // 중력 적용 여부

public:
    Rigidbody() = default;
	~Rigidbody() = default;

    // gravity
    void SetGravity(float g) { gravity = g; }
    void UseGravity(bool use) { useGravity = use; }
    void UpdateGravity(float deltaTime)
    {
        if (useGravity)
            velocity.y += gravity * deltaTime;
    }

	// velocity setter
    void SetVelocity(const Vector2& v) { velocity = v; }
    void AddVelocity(const Vector2& v) { velocity += v; }
    void SetVelocityX(float x) { velocity.x = x; }
    void SetVelocityY(float y) { velocity.y = y; }
    void Stop() { velocity = { 0, 0 }; }

	// velocity getter
    Vector2 GetVelocity() const { return velocity; }
    float GetVelocityX() const { return velocity.x; }
    float GetVelocityY() const { return velocity.y; }
};

