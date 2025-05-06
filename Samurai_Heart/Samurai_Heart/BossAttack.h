#pragma once
#include "BossBaseState.h"
#include "Boss.h"

class BossAttack : public BossBaseState
{
private:
	int comboStep = 0;
public:
	BossAttack(Boss* boss) : BossBaseState(boss) {}
	void Enter() override;
	void ChangeStateLogic() override;
	void UpdateLogic() override;
	void Render() override;
	void Exit() override;
	void SetAttackAnimation(int combo);
};

