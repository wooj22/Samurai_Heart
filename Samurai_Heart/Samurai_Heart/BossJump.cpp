#include "BossJump.h"
#include <windows.h>

void BossJump::Enter()
{
	// flag
	boss->isJumping = true;
	boss->isGround = false;

	// sprite & animation set
	boss->currentSprite = &boss->jumpUpSprite;
	boss->currentAnimation = &boss->jumpUpAnimation;

	// jump (1회)
	boss->rigidbody.SetVelocityY(-boss->jumpPower);
}

void BossJump::ChangeStateLogic()
{
	// idle
	if (boss->isGround) boss->ChangeState(boss->IDLE);
}

void BossJump::UpdateLogic()
{
	// 플레이어 반대방향으로 날아가기
	boss->rigidbody.SetVelocityX(boss->speed * 2.0f * -boss->direction);

	// up & down sprite upate
	float velocityY = boss->rigidbody.GetVelocity().y;

	// up
	if (velocityY < 0)
	{
		boss->currentSprite = &boss->jumpUpSprite;
		boss->currentAnimation = &boss->jumpUpAnimation;
	}
	// down
	else if (velocityY > 0)
	{
		boss->currentSprite = &boss->jumpDownSprite;
		boss->currentAnimation = &boss->jumpDownAnimation;

		// 내려올때 천천히
		boss->rigidbody.SetGravity(boss->gravity * 0.2f);
	}

	// frame update
	boss->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = boss->currentAnimation->GetCurrentFrame();
	boss->currentSprite->SetFrameRect(currentFrame);
}

void BossJump::Render()
{
	// animation render
	RenderManager::Get().DrawImageFilp(
		boss->currentSprite->GetBitmap(), -boss->direction,
		boss->screenPosition.x - boss->width / 2, boss->screenPosition.y - boss->height / 2,
		boss->currentSprite->GetFrameRect().X, boss->currentSprite->GetFrameRect().Y,
		boss->currentSprite->GetFrameRect().Width, boss->currentSprite->GetFrameRect().Height);

}

void BossJump::Exit()
{
	boss->rigidbody.SetGravity(boss->gravity);
	boss->isJumping = false;
}