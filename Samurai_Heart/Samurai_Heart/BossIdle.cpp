#include "BossIdle.h"
#include <windows.h>

void BossIdle::Enter()
{
	// sprite & animation set
	boss->currentSprite = &boss->idleSprite;
	boss->currentAnimation = &boss->idleAnimation;

	boss->rigidbody.SetVelocity((0, 0));
}

void BossIdle::ChangeStateLogic() 
{

}

void BossIdle::UpdateLogic() 
{

}

void BossIdle::Render() 
{

}

void BossIdle::Exit() 
{

}