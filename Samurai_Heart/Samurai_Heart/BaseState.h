#pragma once

class Player;

// �߻�Ŭ���� FSM
class BaseState
{
protected : 
    Player* player;

public :
	BaseState(Player* player) : player(player) {}

    virtual void Enter() = 0;       // state ���� 1ȸ
    virtual void ChangeStateLogic() = 0;
    virtual void UpdateLogic() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;        // state ���� 1ȸ
};

