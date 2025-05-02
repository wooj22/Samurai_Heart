#pragma once
#include <gdiplus.h>

class Sprite
{
private:
    Bitmap* bitmap = nullptr;     // ��ü ��������Ʈ ��Ʈ
    Rect sourceRect = { 0, 0, 0, 0 }; // ���� ����� ����

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

