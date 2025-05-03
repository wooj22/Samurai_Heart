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
            WCHAR buffer[256];
            swprintf(buffer, 256, L"~Sprite : Deleting bitmap at %p\n", bitmap);
            OutputDebugStringW(buffer);

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

    // Get Bitmap
    Bitmap* GetBitmap() { return bitmap; }

    // Get Frame Rect
    Rect GetFrameRect() { return sourceRect; }
};

