#pragma once
#include "BossBaseState.h"
#include "Boss.h"

class BossRun : public BossBaseState
{
public:
	BossRun(Boss* boss) : BossBaseState(boss) {}
	void Enter() override;
	void ChangeStateLogic() override;
	void UpdateLogic() override;
	void Render() override;
	void Exit() override;
};


