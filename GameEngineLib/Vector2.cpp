#include "pch.h"
#include "Vector2.h"
#include <cmath>

Vector2 Vector2::operator+ (const Vector2& vector2) {
	Vector2 result;

	result.x = this->x + vector2.x;
	result.y = this->y + vector2.y;

	return result;
}

Vector2 Vector2::operator- (const Vector2& vector2) {
	Vector2 result;

	result.x = this->x - vector2.x;
	result.y = this->y - vector2.y;

	return result;
}

Vector2 Vector2::operator* (float n) {
	Vector2 result;

	result.x = this->x * n;
	result.y = this->y * n;

	return result;
}


void Vector2::operator+= (const Vector2& vector2) {
	this->x += vector2.x;
	this->y += vector2.y;
}

void Vector2::operator-= (const Vector2& vector2) {
	this->x -= vector2.x;
	this->y -= vector2.y;
}

void Vector2::operator*= (float n) {
	this->x *= n;
	this->y *= n;
}

// 자신을 방향 벡터로 변환
void Vector2::Normalize() {
	float dist = sqrt(this->x * this->x + this->y * this->y);
	this->x = this->x / dist;
	this->y = this->y / dist;
}

// 자신의 길이 반환
float Vector2::Length() {
	return sqrt(this->x * this->x + this->y * this->y);
}

// 자신의 길이 반환 (루트 없이 제곱된 길이)
float Vector2::LengthSquared() {
	return this->x * this->x + this->y * this->y;
}

// 자신과 vector2의 내적 반환
float Vector2::Dot(const Vector2& vector2) {
	return this->x * vector2.x + this->y * vector2.y;
}

// 자신과 vector2의 거리 반환
float Vector2::Distance(const Vector2& vector2) {
	float distX = this->x - vector2.x;
	float distY = this->y - vector2.y;

	float dist = sqrt(distX * distX + distY * distY);
	return dist;
}