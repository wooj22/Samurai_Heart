#pragma once

#include "../GameEngineLib/Object.h"
#include "../GameEngineLib/Vector2.h"
#include "GameApp.h"

class UI_Image : public Object
{
private:
    // transform
    Vector2 screenPosition;  // Left-Top ±‚¡ÿ
    float width;
    float height;
    Color color;

public:
    UI_Image() = default;
    ~UI_Image() = default;

    void Start() override {};
    void Update() override {};
    void Render() override;

    void Init(Vector2 pos, float w, float h, Color c);
    void SetPosition(Vector2 pos);
    void SetSize(float w, float h);
    void SetSizeW(float w);
    void SetWidthRatio(float ratio);
};

