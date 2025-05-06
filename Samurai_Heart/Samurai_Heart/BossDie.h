#pragma once
#include "BossBaseState.h"
#include "Boss.h"

class BossDie : public BossBaseState
{
public:
	BossDie(Boss* boss) : BossBaseState(boss) {}
	void Enter() override;
	void ChangeStateLogic() override;
	void UpdateLogic() override;
	void Render() override;
	void Exit() override;
	void SetAttackAnimation(int combo);
};

