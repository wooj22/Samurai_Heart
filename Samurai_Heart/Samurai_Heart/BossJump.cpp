#include "BossJump.h"
#include <windows.h>

void BossJump::Enter()
{
	// sprite & animation set
	boss->currentSprite = &boss->jumpUpSprite;
	boss->currentAnimation = &boss->jumpUpAnimation;

	boss->rigidbody.SetVelocity((0, 0));
}

void BossJump::ChangeStateLogic()
{

}

void BossJump::UpdateLogic()
{
	// animation sprite update
	boss->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = boss->currentAnimation->GetCurrentFrame();
	boss->currentSprite->SetFrameRect(currentFrame);
}

void BossJump::Render()
{
	// animation render
	RenderManager::Get().DrawImageFilp(
		boss->currentSprite->GetBitmap(), boss->lastDirection,
		boss->screenPosition.x - boss->width / 2, boss->screenPosition.y - boss->height / 2,
		boss->currentSprite->GetFrameRect().X, boss->currentSprite->GetFrameRect().Y,
		boss->currentSprite->GetFrameRect().Width, boss->currentSprite->GetFrameRect().Height);

}

void BossJump::Exit()
{

}