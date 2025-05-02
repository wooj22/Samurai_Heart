#pragma once
#include <gdiplus.h>
#include "AnimationClip.h"

class Sprite
{
private:
    Bitmap* bitmap = nullptr;     // ��ü ��������Ʈ ��Ʈ
    Rect sourceRect = { 0, 0, 0, 0 }; // ���� ����� ����

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

