#pragma once
#include <gdiplus.h>
#include "AnimationClip.h"

class Sprite
{
private:
    Bitmap* bitmap = nullptr;     // 전체 스프라이트 시트
    Rect sourceRect = { 0, 0, 0, 0 }; // 현재 출력할 영역

public:
    Sprite() = default;
	~Sprite() { delete bitmap; }

	// Load Image
    void Load(const wchar_t* path)
    {
        if (bitmap) delete bitmap;
        bitmap = new Bitmap(path);
    }

	// Set Frame Rect
    void SetFrameRect(Frame& frame)
    {
        sourceRect = Rect(frame.x, frame.y, frame.width, frame.height);
    }

    // Get Bitmap
    Bitmap* GetBitmap() { return bitmap; }

    // Get Frame Rect
    Rect GetFrameRect() { return sourceRect; }
};

