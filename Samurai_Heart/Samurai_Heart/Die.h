#pragma once
#include "BaseState.h"
#include "Player.h"

class Die : public BaseState
{
private:
	float testTime = 3;
	float testTimer = 0;
public:
	Die(Player* player) : BaseState(player) {}
	void Enter() override;
	void ChangeStateLogic() override;
	void UpdateLogic() override;
	void Render() override;
	void Exit() override;
};

