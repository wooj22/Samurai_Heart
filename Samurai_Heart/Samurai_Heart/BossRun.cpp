#include "BossRun.h"
#include <windows.h>

void BossRun::Enter()
{
	// sprite & animation set
	boss->currentSprite = &boss->runSprite;
	boss->currentAnimation = &boss->runAnimation;
}

void BossRun::ChangeStateLogic()
{
	// attack
	if (boss->distance <= boss->attackLimit) boss->ChangeState(boss->ATTACK);

	// idle
	if (boss->distance > boss->traceLimit) boss->ChangeState(boss->IDLE);
}

void BossRun::UpdateLogic()
{
	// trace run
	boss->rigidbody.SetVelocityX(boss->speed * boss->direction);

	// animation sprite update
	boss->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = boss->currentAnimation->GetCurrentFrame();
	boss->currentSprite->SetFrameRect(currentFrame);
}

void BossRun::Render()
{
	// animation render
	RenderManager::Get().DrawImageFilp(
		boss->currentSprite->GetBitmap(), boss->direction,
		boss->screenPosition.x - boss->width / 2, boss->screenPosition.y - boss->height / 2,
		boss->currentSprite->GetFrameRect().X, boss->currentSprite->GetFrameRect().Y,
		boss->currentSprite->GetFrameRect().Width, boss->currentSprite->GetFrameRect().Height);

}

void BossRun::Exit()
{

}