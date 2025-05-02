#pragma once

class Player;

// 추상클래스 FSM
class BaseState
{
protected : 
    Player* player;

public :
	BaseState(Player* player) : player(player) {}

    virtual void Enter() = 0;
    virtual void ChangeStateLogic() = 0;
    virtual void UpdateLogic() = 0;
	virtual void Render() = 0;
    virtual void Exit() = 0;
};

