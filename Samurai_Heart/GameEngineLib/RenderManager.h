#pragma once
#include "gdiplus.h"
#pragma comment(lib, "gdiplus.lib")
#include "Singleton.h"
#include "framework.h"
#include "Vector2.h"
using namespace Gdiplus;
using namespace std;

class RenderManager : public Singleton<RenderManager>
{
private:
	// Window Handle
	HWND hwnd;
	int width, height;

	// Device Context
	HDC frontBufferDC;
	HDC backBufferDC;

	// Graphics
	Graphics* backBufferGraphics;
	HBITMAP backBufferBitmap;
	ULONG_PTR gdiPlusToken;

public:
	RenderManager() = default;
	~RenderManager() override = default;

	void Init(HWND hwnd, int width, int height);
	void Update() {};
	void Release();

	// Load
	void LoadImageFile(Bitmap*& bitmap, wchar_t* filePath);
	void CopyImage(Bitmap*& bitmapCopy, Bitmap*& bitmapOrigin);
	void FilpImage(Bitmap*& bitmap);

	// Draw
	void DrawBackground();
	void DrawImage(Bitmap* bitmap, float posX, float posY);
	void DrawImage(Bitmap* image, float x, float y, float width, float height);
	void DrawImage(Bitmap* bitmap, float posX, float posY, float srcX, float srcY, float srcW, float srcH);
	
	void DrawImageFilp(Bitmap* image, int dir, float x, float y, float width, float height);
	void DrawImageFilp(Bitmap* bitmap, int dir, float posX, float posY, float srcX, float srcY, float srcW, float srcH);
	
	void DrawTextC(const char* text, float posX, float posY);
	void DrawTextW(const wchar_t* text, float posX, float posY);
	void DrawTextS(const string& text, float posX, float posY);
	
	void DrawRect(Vector2 pos, float width, float height, Color color);
	void DrawFadeRect(BYTE alpha);
	void DrawBackToFront();

	// Debug (Å×µÎ¸®)
	void DrawBox(Vector2 minPos, float width, float height);
};

