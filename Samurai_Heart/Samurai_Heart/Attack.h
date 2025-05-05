#pragma once
#include "BaseState.h"
#include "Player.h"

class Attack : public BaseState
{
private:
	int comboStep = 0;
public:
	Attack(Player* player) : BaseState(player) {}
	void Enter() override;
	void ChangeStateLogic() override;
	void UpdateLogic() override;
	void Render() override;
	void Exit() override;

	void SetAttackAnimation(int combo);
};