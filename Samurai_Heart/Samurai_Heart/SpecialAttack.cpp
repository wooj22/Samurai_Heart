#include "SpecialAttack.h"
#include <windows.h>

void SpecialAttack::Enter() 
{
	OutputDebugStringA("[Player] SpecialAttack Enter\n");

	// flag
	player->isSpecialAttack = true;
	player->ChargeZero();

	// sprite & animation set
	player->currentSprite = &player->specialAttackSprite;
	player->currentAnimation = &player->specialAttackAnimation;

	// last direction
	if (player->isMoveLKey) player->lastDirection = -1;
	if (player->isMoveRKey) player->lastDirection = 1;

	// µ¹Áø
	player->rigidbody.SetVelocityX(player->specialAttackSpeed * player->lastDirection);
}

void SpecialAttack::ChangeStateLogic()
{
	// idle
	if (player->specialAttackAnimation.IsFinished())
		player->ChangeState(player->IDLE);
}

void SpecialAttack::UpdateLogic() 
{
	// animation sprite update
	player->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = player->currentAnimation->GetCurrentFrame();
	player->currentSprite->SetFrameRect(currentFrame);
}

void SpecialAttack::Render()
{
	// animation render
	RenderManager::Get().DrawImageFilp(
		player->currentSprite->GetBitmap(), player->lastDirection,
		player->screenPosition.x - player->width / 2, player->screenPosition.y - player->height / 2,
		player->currentSprite->GetFrameRect().X, player->currentSprite->GetFrameRect().Y,
		player->width, player->height);
}

void SpecialAttack::Exit() 
{
	player->isSpecialAttack = false;
	OutputDebugStringA("[Player] SpecialAttack Exit\n");
}