#include "UI_Text.h"

void UI_Text::Render() 
{
    RenderManager::Get().DrawTextS(text, screenPosition.x, screenPosition.y);
}

void UI_Text::Init(string content, Vector2 pos) 
{
    text = content;
    screenPosition = pos;
}

void UI_Text::SetText(string newText) 
{
    text = newText;
}