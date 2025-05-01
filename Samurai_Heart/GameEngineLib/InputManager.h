#pragma once
#include "Singleton.h"

class InputManager : public Singleton<InputManager>
{
private:
	HWND m_hWnd;			// 윈도우 핸들
	POINT m_mouseClient;	// 마우스 좌표
	SHORT m_prevState[256] = { 0 };
	SHORT m_currState[256] = { 0 };

public:
	InputManager() = default;
	~InputManager() override = default;

	void Init(HWND hWnd);
	void Update();
	void Release() {};

	bool IsKeyDown(int vKey);
	bool IsKeyPressed(int vKey);
	bool IsKeyReleased(int vKey);

	friend class Singleton<InputManager>;
};