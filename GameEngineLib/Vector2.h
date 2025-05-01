#pragma once
using namespace std;

class Vector2
{
public:
	float x, y;
	Vector2(float inputX = 0, float inputY = 0) : x(inputX), y(inputY) {};

	// operator
	Vector2 operator+ (const Vector2& vector2);
	Vector2 operator- (const Vector2& vector2);
	Vector2 operator* (float n);

	void operator+= (const Vector2& vector2);
	void operator-= (const Vector2& vector2);
	void operator*= (float n);

	// member function
	void Normalize();
	float Length();
	float LengthSquared();
	float Dot(const Vector2& vector2);
	float Distance(const Vector2& vector2);
};

