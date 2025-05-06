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
	// idle
	if (boss->curDist < boss->traceLimit) boss->ChangeState(boss->IDLE);
}

void BossRun::UpdateLogic()
{
	

	// animation sprite update
	boss->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = boss->currentAnimation->GetCurrentFrame();
	boss->currentSprite->SetFrameRect(currentFrame);
}

void BossRun::Render()
{
	// animation render
	RenderManager::Get().DrawImageFilp(
		boss->currentSprite->GetBitmap(), boss->lastDirection,
		boss->screenPosition.x - boss->width / 2, boss->screenPosition.y - boss->height / 2,
		boss->currentSprite->GetFrameRect().X, boss->currentSprite->GetFrameRect().Y,
		boss->currentSprite->GetFrameRect().Width, boss->currentSprite->GetFrameRect().Height);

}

void BossRun::Exit()
{

}