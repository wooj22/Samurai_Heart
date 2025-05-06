#pragma once
#include "BaseState.h"
#include "Player.h"

class WallJump : public BaseState
{
private:
	// isWall 무시 시간
	float timer = 0.f;
	float cheakTime = 0.7f;
public:
	WallJump(Player* player) : BaseState(player) {}
	void Enter() override;
	void ChangeStateLogic() override;
	void UpdateLogic() override;
	void Render() override;
	void Exit() override;
};

