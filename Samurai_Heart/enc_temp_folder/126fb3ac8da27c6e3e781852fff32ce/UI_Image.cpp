#include "UI_Image.h"

void UI_Image::Render()
{
    RenderManager::Get().DrawRect(screenPosition, width, height, color);
}

void UI_Image::Init(Vector2 pos, float w, float h, Color c)
{
    screenPosition = pos;
    width = w;
    height = h;
    fillAmount = w;
    color = c;
}

void UI_Image::SetPosition(Vector2 pos)
{
    screenPosition = pos;
}

void UI_Image::SetSize(float w, float h)
{
    width = w;
    height = h;
}

void UI_Image::SetSizeW(float w)
{
    width = w;
}

void UI_Image::SetWidthRatio(float ratio)
{
    width = fillAmount * ratio;
}