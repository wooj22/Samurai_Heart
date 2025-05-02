#pragma once
#include <gdiplus.h>

class Sprite
{
private:
    Bitmap* bitmap = nullptr;     // 전체 스프라이트 시트
    Rect sourceRect = { 0, 0, 0, 0 }; // 현재 출력할 영역

public:
    Sprite() = default;

    void Load(const wchar_t* path)
    {
        if (bitmap) delete bitmap;
        bitmap = new Bitmap(path);
    }

    void SetSourceRect(const Frame& frame)
    {
        sourceRect = Rect(frame.x, frame.y, frame.width, frame.height);
    }

    Bitmap* GetBitmap() const { return bitmap; }
    Rect GetSourceRect() const { return sourceRect; }

    ~Sprite()
    {
        delete bitmap;
    }
};

