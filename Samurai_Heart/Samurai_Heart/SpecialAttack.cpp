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

	// 돌진
	player->rigidbody.SetVelocityX(player->specialAttackSpeed * player->lastDirection);

	// sound
	SoundManager::Get().PlaySFX("../Resource/Sound/SFX_SpecialAttack.mp3");
}

void SpecialAttack::ChangeStateLogic()
{
	// 공격이 끝났을 때
	if (player->specialAttackAnimation.IsFinished()) 
	{
		// attack
		if (player->isAttackKey && player->isGround)
			player->ChangeState(player->ATTACK);

		// run
		if (player->isMoveLKey || player->isMoveRKey)
			player->ChangeState(player->RUN);
		// idle
		else
			player->ChangeState(player->IDLE);
	}	
}

void SpecialAttack::UpdateLogic() 
{
	// attack (지나가는동안 계속 줌)
	player->DoAttack(player->specialAttackPower);

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