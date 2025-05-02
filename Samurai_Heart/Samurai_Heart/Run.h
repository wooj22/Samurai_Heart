#pragma once
#include "BaseState.h"

class Run : public BaseState
{
public:
	Run(Player* player) : BaseState(player) {}
	void Enter() override;
	void ChangeStateLogic() override;
	void UpdateLogic() override;
	void Render() override;
	void Exit() override;
};

