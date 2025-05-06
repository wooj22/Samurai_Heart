#pragma once
#include "BossBaseState.h"
#include "Boss.h"

class BossHit : public BossBaseState
{
public:
	BossHit(Boss* boss) : BossBaseState(boss) {}
	void Enter() override;
	void ChangeStateLogic() override;
	void UpdateLogic() override;
	void Render() override;
	void Exit() override;
	void SetAttackAnimation(int combo);
};

