#pragma once

class Boss;

// �߻�Ŭ���� FSM
class BossBaseState
{
protected:
    Boss* boss;

public:
    BossBaseState(Boss* boss) : boss(boss) {}

    virtual void Enter() = 0;       // state ���� 1ȸ
    virtual void ChangeStateLogic() = 0;
    virtual void UpdateLogic() = 0;
    virtual void Render() = 0;
    virtual void Exit() = 0;        // state ���� 1ȸ
};
