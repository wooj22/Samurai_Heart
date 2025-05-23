#include "Idle.h"
#include <windows.h>

void Idle::Enter() 
{
	OutputDebugStringA("[Player] Idle Enter\n");

	// sprite & animation set
	player->currentSprite = &player->idleSprite;
	player->currentAnimation = &player->idleAnimation;

	player->rigidbody.SetVelocity((0, 0));
}

void Idle::ChangeStateLogic() 
{
	// run
	if (player->isMoveLKey || player->isMoveRKey)
		player->ChangeState(player->RUN);

	// jump
	if (player->isJumpKey && player->isGround)
		player->ChangeState(player->JUMP);

	// dash
	if(player->isDash && player->isGround)
		player->ChangeState(player->DASH);

	// defense
	if(player->isDefenseKey && player->isGround)
		player->ChangeState(player->DEFENSE);

	// attack
	if(player->isAttackKey && player->isGround)
		player->ChangeState(player->ATTACK);

	// specialAttack
	if (player->isSpecialAttackKey && player->isChargeMax &&player->isGround)
		player->ChangeState(player->SPECIAL_ATTACK);
}

void Idle::UpdateLogic() 
{
	// animation sprite update
	player->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = player->currentAnimation->GetCurrentFrame();
	player->currentSprite->SetFrameRect(currentFrame);
}

void Idle::Render() 
{
	// animation render
	RenderManager::Get().DrawImageFilp(
		player->currentSprite->GetBitmap(), player->lastDirection,
		player->screenPosition.x - player->width/2, player->screenPosition.y - player->height/2,
		player->currentSprite->GetFrameRect().X, player->currentSprite->GetFrameRect().Y,
		player->currentSprite->GetFrameRect().Width, player->currentSprite->GetFrameRect().Height);
}

void Idle::Exit() 
{
	OutputDebugStringA("[Player] Idle Exit\n");
}