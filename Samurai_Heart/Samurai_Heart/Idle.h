#pragma once
#include "BaseState.h"
#include "Player.h"

class Idle : public BaseState
{
public :
	Idle(Player* player) : BaseState(player) {}
	void Enter() override;
	void ChangeStateLogic() override;
	void UpdateLogic() override;
	void Render() override;
	void Exit() override;
};

