#include "GameApp.h"

/// Game Init
void GameApp::Init() {
	__super::Init();

	// scene ���
	
}

/// Game Release
void GameApp::Release() {
	__super::Release();
}

/// ������ ���ν��� �޽��� ó��
void GameApp::MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	__super::MessageProc(hwnd, uMsg, wParam, lParam);

	// game�� Ȱ���� message ó��
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	}
}