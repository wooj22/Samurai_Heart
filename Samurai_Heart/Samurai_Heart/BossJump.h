#pragma once
#include "BossBaseState.h"
#include "Boss.h"

class BossJump : public BossBaseState
{
public:
	BossJump(Boss* boss) : BossBaseState(boss) {}
	void Enter() override;
	void ChangeStateLogic() override;
	void UpdateLogic() override;
	void Render() override;
	void Exit() override;
};

