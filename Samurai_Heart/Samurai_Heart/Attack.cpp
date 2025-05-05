#include "Attack.h"
#include <windows.h>

void Attack::Enter()
{
	OutputDebugStringA("[Player] Attack Enter\n");

	// sprite & animation set
	player->currentSprite = &player->idleSprite;
	player->currentAnimation = &player->idleAnimation;

	player->rigidbody.SetVelocity((0, 0));
}

void Attack::ChangeStateLogic()
{
	// run
	if (player->isMoveLKey || player->isMoveRKey)
		player->ChangeState(player->RUN);

	// jump
	if (player->isJumpKey && player->isGround)
		player->ChangeState(player->JUMP);

	// dash
	if (player->isDash && player->isGround)
		player->ChangeState(player->DASH);

	// defense
	if (player->isDefenseKey && player->isGround)
		player->ChangeState(player->DEFENSE);
}

void Attack::UpdateLogic()
{
	// animation sprite update
	player->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = player->currentAnimation->GetCurrentFrame();
	player->currentSprite->SetFrameRect(currentFrame);
}

void Attack::Render()
{
	// animation render
	RenderManager::Get().DrawImage(
		player->currentSprite->GetBitmap(),
		player->screenPosition.x - player->width / 2, player->screenPosition.y - player->height / 2,
		player->currentSprite->GetFrameRect().X, player->currentSprite->GetFrameRect().Y,
		player->currentSprite->GetFrameRect().Width, player->currentSprite->GetFrameRect().Height);
}

void Attack::Exit()
{
	OutputDebugStringA("[Player] Attack Exit\n");
}