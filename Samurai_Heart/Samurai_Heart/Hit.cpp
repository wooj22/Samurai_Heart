#include "Hit.h"
#include <windows.h>

void Hit::Enter() 
{
	OutputDebugStringA("[Player] Hit Enter\n");

	// sprite & animation set
	player->currentSprite = &player->hitSprite;
	player->currentAnimation = &player->hitAnimation;

	player->rigidbody.SetVelocityX(0);
}

void Hit::ChangeStateLogic()
{
	player->hitInvincibilityTimer += TimeManager::Get().GetDeltaTime();
	if (player->hitInvincibilityTimer >= player->hitInvincibilityTime) {
		player->ChangeState(player->IDLE);
		player->hitInvincibilityTimer = 0;
	}
}

void Hit::UpdateLogic()
{
	// animation sprite update
	player->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = player->currentAnimation->GetCurrentFrame();
	player->currentSprite->SetFrameRect(currentFrame);
}

void Hit::Render() 
{
	// animation render
	RenderManager::Get().DrawImageFilp(
		player->currentSprite->GetBitmap(), player->lastDirection,
		player->screenPosition.x - player->width / 2, player->screenPosition.y - player->height / 2,
		player->currentSprite->GetFrameRect().X, player->currentSprite->GetFrameRect().Y,
		player->width, player->height);
}

void Hit::Exit() 
{
	player->isHit = false;
	OutputDebugStringA("[Player] Hit Exit\n");
}