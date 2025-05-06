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
	// run (trace)
	if (boss->distance <= boss->traceLimit) boss->ChangeState(boss->RUN);

	// attack
	if (boss->distance <= boss->attackLimit) boss->ChangeState(boss->ATTACK);
}

void BossIdle::UpdateLogic() 
{
	// animation sprite update
	boss->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = boss->currentAnimation->GetCurrentFrame();
	boss->currentSprite->SetFrameRect(currentFrame);
}

void BossIdle::Render() 
{
	// animation render
	RenderManager::Get().DrawImageFilp(
		boss->currentSprite->GetBitmap(), boss->direction,
		boss->screenPosition.x - boss->width / 2, boss->screenPosition.y - boss->height / 2,
		boss->currentSprite->GetFrameRect().X, boss->currentSprite->GetFrameRect().Y,
		boss->currentSprite->GetFrameRect().Width, boss->currentSprite->GetFrameRect().Height);

}

void BossIdle::Exit() 
{

}