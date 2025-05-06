#include "pch.h"
#include "RenderManager.h"

/// Renderer Initialize
void RenderManager::Init(HWND hwnd, int width, int height) 
{
	// 윈도우 핸들 초기화
	this->hwnd = hwnd;
	this->width = width;
	this->height = height;

	// 더블 버퍼링 초기화
	frontBufferDC = GetDC(hwnd);
	backBufferDC = CreateCompatibleDC(frontBufferDC);
	backBufferBitmap = CreateCompatibleBitmap(frontBufferDC, width, height);
	SelectObject(backBufferDC, backBufferBitmap);

	// GDI+ 초기화
	Gdiplus::GdiplusStartupInput gsi;
	Gdiplus::GdiplusStartup(&gdiPlusToken, &gsi, nullptr);
	backBufferGraphics = Graphics::FromHDC(backBufferDC);
}

/// Load Image
void RenderManager::LoadImageFile(Bitmap*& bitmap, wchar_t* filePath) 
{
	bitmap = new Bitmap(filePath);
}

/// Copy Image
void RenderManager::CopyImage(Bitmap*& bitmapCopy, Bitmap*& bitmapOrigin) 
{
	bitmapCopy = bitmapOrigin->Clone(0, 0,
		bitmapOrigin->GetWidth(),
		bitmapOrigin->GetHeight(),
		bitmapOrigin->GetPixelFormat());
}

/// Filp Image
void RenderManager::FilpImage(Bitmap*& bitmap) 
{
	if(bitmap)	bitmap->RotateFlip(RotateNoneFlipX);
}

/// Backgrond Draw
void RenderManager::DrawBackground() 
{
	PatBlt(backBufferDC, 0, 0, width, height, BLACKNESS);
}

/// Image Draw
void RenderManager::DrawImage(Bitmap* bitmap, float posX, float posY)
{
	backBufferGraphics->DrawImage(bitmap, posX, posY);
}

// Image Draw rect
void RenderManager::DrawImage(Bitmap* image, float x, float y, float width, float height)
{
	RectF destRect(x, y, width, height);
	backBufferGraphics->DrawImage(image, destRect);
}

/// Image Draw with Atlas Frame
void RenderManager::DrawImage(Bitmap* bitmap, float posX, float posY, float srcX, float srcY, float srcW, float srcH)
{
	Rect srcRect(srcX, srcY, srcW, srcH);
	Rect destRect(posX, posY, srcW, srcH); // 스케일 없이 원본 크기로 그릴 경우

	backBufferGraphics->DrawImage(bitmap, destRect, srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height, UnitPixel);
}

/// Image Draw Rect + Filp
void RenderManager::DrawImage(Bitmap* image, int dir, float x, float y, float width, float height) {
	// left 반전
	if (dir == -1) {
		// 좌우 반전: 기준점을 오른쪽 끝으로 이동 후 좌우 반전
		backBufferGraphics->TranslateTransform(x + width, y);
		backBufferGraphics->ScaleTransform(-1, 1); // X축만 반전

		// 반전된 좌표계에서 (0, 0)에 그리기
		backBufferGraphics->DrawImage(image, Rect(0, 0, width, height));

		// 변환 초기화
		backBufferGraphics->ResetTransform();
	}
	else {
		// right (기본)
		RectF destRect(x, y, width, height);
		backBufferGraphics->DrawImage(image, destRect);
	}
}

/// Image Draw with Atlas Frame + Filp
void RenderManager::DrawImageFilp(Bitmap* bitmap, int dir, float posX, float posY, float srcX, float srcY, float srcW, float srcH) {
	Rect srcRect(srcX, srcY, srcW, srcH);
	Rect destRect(posX, posY, srcW, srcH);

	// left 반전
	if (dir == -1) {
		// 좌우 반전 매트릭스
		backBufferGraphics->TranslateTransform(posX + srcW, posY); // 우측 끝으로 이동 후
		backBufferGraphics->ScaleTransform(-1, 1); // 좌우 반전

		backBufferGraphics->DrawImage(bitmap, Rect(0, 0, srcW, srcH),
			srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height, UnitPixel);

		// 원래대로 복원
		backBufferGraphics->ResetTransform();
	}
	else {
		// right (기본)
		backBufferGraphics->DrawImage(bitmap, destRect,
			srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height, UnitPixel);
	}
}

// Text C Draw
void RenderManager::DrawTextC(const char* text, float posX, float posY)
{
	SetBkMode(backBufferDC, TRANSPARENT);
	SetTextColor(backBufferDC, RGB(255, 255, 255));
	TextOutA(backBufferDC, posX, posY, text, static_cast<int>(strlen(text)));
}

// Text W Draw
void RenderManager::DrawTextW(const wchar_t* text, float posX, float posY)
{
	SetBkMode(backBufferDC, TRANSPARENT);
	SetTextColor(backBufferDC, RGB(255, 255, 255));
	TextOutW(backBufferDC, posX, posY, text, wcslen(text));
}

// Text S Draw
void RenderManager::DrawTextS(const std::string& text, float posX, float posY) {
	SetBkMode(backBufferDC, TRANSPARENT);
	SetTextColor(backBufferDC, RGB(255, 255, 255));
	TextOutA(backBufferDC, posX, posY, text.c_str(), static_cast<int>(text.length()));
}

/// Back -> Front copy
void RenderManager::DrawBackToFront() {
	BitBlt(frontBufferDC, 0, 0, width, height, backBufferDC, 0, 0, SRCCOPY);
}

/// GDIRenderer Release
void RenderManager::Release() {
	// GDI+ 해제
	delete backBufferGraphics;
	Gdiplus::GdiplusShutdown(gdiPlusToken);
	DeleteObject(backBufferBitmap);
	DeleteDC(backBufferDC);
	ReleaseDC(hwnd, frontBufferDC);
}

/// Draw Box
void RenderManager::DrawBox(Vector2 minPos, float width, float height) {
	Pen redPen(Color(255, 255, 0, 0));
	backBufferGraphics->DrawRectangle(&redPen, minPos.x, minPos.y, width, height);
}