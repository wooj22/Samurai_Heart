#pragma once
#include "../GameEngineLib/Singleton.h"

enum class FadeState
{
    None,
    FadeIn,
    FadeOut
};

class FadeManager : public Singleton<FadeManager>
{
private:
    FadeState state = FadeState::None;
    float alpha = 0.0f;          // 0.0f (����) ~ 1.0f (������)
    float speed = 1.0f;          // �ʴ� ��ȭ��
    bool isDone = true;

public:
    void StartFadeIn(float fadeSpeed = 1.0f);
    void StartFadeOut(float fadeSpeed = 1.0f);
    void Update(float deltaTime);
    void Render();

    bool IsFadeDone() const { return isDone; }
    FadeState GetState() const { return state; }
};

