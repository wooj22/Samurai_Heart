#include "UIManager.h"
#include "UI_Image.h"

void UIManager::InitUI(UI_Image* bossHp, UI_Image* playeHp, UI_Image* playerChage) 
{
    bossHp_Image = bossHp;
    playerHp_Image = playeHp;
    playerChage_Image = playerChage;
}

void UIManager::InitDate(float maxBossHp, float maxPlayerHp, float maxPlayerCharge) 
{
    maxBossHp = maxBossHp;
    maxPlayerHp = maxPlayerHp;
    maxPlayerCharge = maxPlayerCharge;
}

void UIManager::UpdateBossHP_Image(float bossHp) 
{
    float ratio = bossHp / maxBossHp;
    bossHp_Image->SetWidthRatio(ratio);
}

void UIManager::UpdatePlayerHP_Image(float playerHp) 
{
    float ratio = playerHp / maxPlayerHp;
    playerHp_Image->SetWidthRatio(ratio);
}

void UIManager::UpdatePlayerChage_Image(float playerChage) 
{
    float ratio = playerChage / maxPlayerCharge;
    playerChage_Image->SetWidthRatio(ratio);
}