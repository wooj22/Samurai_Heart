#pragma once
#include "BaseState.h"
#include "Player.h"

class Defense : public BaseState
{
public:
	Defense(Player* player) : BaseState(player) {}
	void Enter() override;
	void ChangeStateLogic() override;
	void UpdateLogic() override;
	void Render() override;
	void Exit() override;
};

