#include "BossDie.h"
#include <windows.h>

void BossDie::Enter()
{
	// sprite & animation set
	boss->currentSprite = &boss->dieSprite;
	boss->currentAnimation = &boss->dieAnimation;

	boss->rigidbody.SetVelocity((0, 0));
}

void BossDie::ChangeStateLogic()
{
	
}

void BossDie::UpdateLogic()
{
	// animation sprite update
	boss->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = boss->currentAnimation->GetCurrentFrame();
	boss->currentSprite->SetFrameRect(currentFrame);
}

void BossDie::Render()
{
	// animation render
	RenderManager::Get().DrawImageFilp(
		boss->currentSprite->GetBitmap(), boss->direction,
		boss->screenPosition.x - boss->width / 2, boss->screenPosition.y - boss->height / 2,
		boss->currentSprite->GetFrameRect().X, boss->currentSprite->GetFrameRect().Y,
		boss->currentSprite->GetFrameRect().Width, boss->currentSprite->GetFrameRect().Height);

}

void BossDie::Exit()
{

}
