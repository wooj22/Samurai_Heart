// FadeManager.cpp
#include "FadeManager.h"
#include "GameApp.h"

void FadeManager::StartFadeIn(float fadeSpeed)
{
    state = FadeState::FadeIn;
    speed = fadeSpeed;
    alpha = 1.0f;
    isDone = false;
}

void FadeManager::StartFadeOut(float fadeSpeed)
{
    state = FadeState::FadeOut;
    speed = fadeSpeed;
    alpha = 0.0f;
    isDone = false;
}

void FadeManager::Update(float deltaTime)
{
    if (state == FadeState::None || isDone)
        return;

    if (state == FadeState::FadeIn)
    {
        alpha -= speed * deltaTime;
        if (alpha <= 0.0f)
        {
            alpha = 0.0f;
            state = FadeState::None;
            isDone = true;
        }
    }
    else if (state == FadeState::FadeOut)
    {
        alpha += speed * deltaTime;
        if (alpha >= 1.0f)
        {
            alpha = 1.0f;
            isDone = true;
        }
    }
}

void FadeManager::Render()
{
    if (state != FadeState::None || !isDone)
    {
        BYTE a = static_cast<BYTE>(alpha * 255.0f);
        RenderManager::Get().DrawFadeRect(a);
    }
}
