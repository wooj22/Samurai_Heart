#pragma once
#include "../GameEngineLib/Singleton.h"

class UI_Text;
class UI_Image;

// playScene Àü¿ë
class UIManager : public Singleton<UIManager>
{
private:
	UI_Image* bossHp_Image;
	UI_Image* playerHp_Image;
	UI_Image* playerChage_Image;

	float maxBossHp;
	float maxPlayerHp;
	float maxPlayerCharge;

public:
	void InitUI(UI_Image* bossHp, UI_Image* playeHp, UI_Image* playerChage);
	void InitDate(float i_maxBossHp, float i_maxPlayerHp, float i_maxPlayerCharge);
	
	void UpdateBossHP_Image(float bossHp);
	void UpdatePlayerHP_Image(float playerHp);
	void UpdatePlayerChage_Image(float playerChage);
};

