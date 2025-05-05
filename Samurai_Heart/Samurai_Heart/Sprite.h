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
	~Sprite() { 
        if (bitmap == nullptr) {
            OutputDebugStringA("~Sprite : bitmap is nullptr!\n");
        }
        else {
            delete bitmap;
        }
    }

	// Load Image
    void Load(const wchar_t* path)
    {
        if (bitmap) {
            delete bitmap;
            bitmap = nullptr;
        }

        bitmap = new Bitmap(path);
        if (bitmap->GetLastStatus() != Ok) {
            OutputDebugStringA("Bitmap load failed!\n");
            delete bitmap;
            bitmap = nullptr;
        }
    }

	// Set Frame Rect
    void SetFrameRect(Frame& frame)
    {
        sourceRect = Rect(frame.x, frame.y, frame.width, frame.height);
    }

    // Set Full Frame Rect
    void SetFullFrameRect() {
        sourceRect.X = 0;
        sourceRect.Y = 0;
        sourceRect.Width = bitmap->GetWidth();
        sourceRect.Height = bitmap->GetHeight();
    }

    // Get Bitmap
    Bitmap* GetBitmap() { return bitmap; }

    // Get Frame Rect
    Rect GetFrameRect() { return sourceRect; }
};

