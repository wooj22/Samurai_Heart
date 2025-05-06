#include "Attack.h"
#include <windows.h>

void Attack::Enter()
{
	OutputDebugStringA("[Player] Attack Enter\n");

	// flag
	player->isAttack = true;

	// sprite & animation set
	comboStep = 0;
	SetAttackAnimation(comboStep);
	player->currentAnimation->Reset();

	// attack
	player->DoAttack(player->power);
}

void Attack::ChangeStateLogic()
{
	// 공격 키가 안눌려있고 현재 애니메이션이 끝났을 때
	if (!player->isAttackKey && player->currentAnimation->IsFinished())
	{
		// special attack
		if (player->isSpecialAttackKey && player->isChargeMax && player->isGround)
			player->ChangeState(player->SPECIAL_ATTACK);

		// run
		if (player->isMoveLKey || player->isMoveRKey)
			player->ChangeState(player->RUN);
		// idle
		else
			player->ChangeState(player->IDLE);

	}
}

void Attack::UpdateLogic()
{
	// sprtie & animation update
	player->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = player->currentAnimation->GetCurrentFrame();
	player->currentSprite->SetFrameRect(currentFrame);

	// attack animation change  //TODO :: cooltime으로 확장성 높이기
	// 한 공격 애니메이션이 시작되는 지점
	if (player->isAttackKey && player->currentAnimation->IsFinished())
	{
		// animation
		comboStep++;
		SetAttackAnimation(comboStep);
		player->currentAnimation->Reset();
		comboStep = comboStep == 2 ? -1 : comboStep;

		// attack
		player->DoAttack(player->power);

		// move
		if (player->isMoveLKey) player->lastDirection = -1;
		if (player->isMoveRKey) player->lastDirection = 1;

		player->rigidbody.SetVelocityX(player->speed * player->lastDirection);
	}

	// 감속
	player->rigidbody.SetVelocityX(player->rigidbody.GetVelocityX() * 0.7f);
}

void Attack::Render()
{
	// animation render
	RenderManager::Get().DrawImageFilp(
		player->currentSprite->GetBitmap(), player->lastDirection,
		player->screenPosition.x - player->width / 2, player->screenPosition.y - player->height / 2,
		player->currentSprite->GetFrameRect().X, player->currentSprite->GetFrameRect().Y,
		player->currentSprite->GetFrameRect().Width, player->currentSprite->GetFrameRect().Height);
}

void Attack::Exit()
{
	player->isAttack = true;
	OutputDebugStringA("[Player] Attack Exit\n");
}

// Set Attack Animation
void Attack::SetAttackAnimation(int combo)
{
	switch (combo)
	{
	case 0:
		player->currentSprite = &player->attack01Sprite;
		player->currentAnimation = &player->attack01Animation;
		// sound
		SoundManager::Get().PlaySFX("../Resource/Sound/SFX_Attack01.mp3");
		break;
	case 1:
		player->currentSprite = &player->attack02Sprite;
		player->currentAnimation = &player->attack02Animation;
		// sound
		SoundManager::Get().PlaySFX("../Resource/Sound/SFX_Attack02.mp3");
		break;
	case 2:
		player->currentSprite = &player->attack03Sprite;
		player->currentAnimation = &player->attack03Animation;
		// sound
		SoundManager::Get().PlaySFX("../Resource/Sound/SFX_Attack03.mp3");
		break;
	}
}