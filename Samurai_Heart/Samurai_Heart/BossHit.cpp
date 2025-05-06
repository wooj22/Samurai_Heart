#include "BossHit.h"
#include <windows.h>

void BossHit::Enter()
{
	// sprite & animation set
	boss->currentSprite = &boss->hitSprite;
	boss->currentAnimation = &boss->hitAnimation;

	// 밀려나기
	boss->rigidbody.SetVelocityX(boss->speed * -boss->direction);
}

void BossHit::ChangeStateLogic()
{
	// idle
	if (boss->hitInvincibilityTimer >= boss->hitInvincibilityTime) {
		boss->ChangeState(boss->IDLE);
		boss->hitInvincibilityTimer = 0;
	}
}

void BossHit::UpdateLogic()
{
	boss->hitInvincibilityTimer += TimeManager::Get().GetDeltaTime();

	// 감속
	boss->rigidbody.SetVelocityX(boss->rigidbody.GetVelocityX() * 0.7f);

	// animation sprite update
	boss->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = boss->currentAnimation->GetCurrentFrame();
	boss->currentSprite->SetFrameRect(currentFrame);
}

void BossHit::Render()
{
	// animation render
	RenderManager::Get().DrawImageFilp(
		boss->currentSprite->GetBitmap(), boss->direction,
		boss->screenPosition.x - boss->width / 2, boss->screenPosition.y - boss->height / 2,
		boss->currentSprite->GetFrameRect().X, boss->currentSprite->GetFrameRect().Y,
		boss->currentSprite->GetFrameRect().Width, boss->currentSprite->GetFrameRect().Height);

}

void BossHit::Exit()
{
	boss->isHit = false;
}
