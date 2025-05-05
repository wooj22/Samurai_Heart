#pragma once
#include "../GameEngineLib/Vector2.h"

// ��ġ ������ �ܺο���
// position += rigidbody.GetVelocity() * deltaTime;

class Rigidbody
{
private:
    Vector2 velocity = { 0, 0 };       // ���� �ӵ�
    float gravity = 980.0f;            // �߷� ���ӵ� (�ȼ�/��^2)
    bool useGravity = true;            // �߷� ���� ����

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

