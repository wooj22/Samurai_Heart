#pragma once
#include "../GameEngineLib/Object.h"
#include "../GameEngineLib/Vector2.h"
#include "GameApp.h"
#include <string>

class UI_Text : public Object
{
private:
    // transform
    Vector2 screenPosition;

    // text
    string text;

public:
    UI_Text() = default;
    ~UI_Text() = default;

    void Start() {};
    void Update() {};
    void Render() override;

    void Init(string content, Vector2 pos);
    void SetText(string newText);
};

