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
}

void Attack::ChangeStateLogic()
{
	// ���� Ű�� �ȴ����ְ� ���� �ִϸ��̼��� ������ ��
	if (!player->isAttackKey && player->currentAnimation->IsFinished())
	{
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

	// attack animation change  //TODO :: cooltime���� Ȯ�强 ���̱�
	if (player->isAttackKey && player->currentAnimation->IsFinished())
	{
		comboStep++;
		SetAttackAnimation(comboStep);
		player->currentAnimation->Reset();

		comboStep = comboStep == 2 ? -1 : comboStep;

		// �ѹ� attack �Ҷ����� �ӵ��ֱ� (���� coolTime�� ��� ���� �־��)
		if (player->isMoveLKey) player->lastDirection = -1;
		if (player->isMoveRKey) player->lastDirection = 1;

		player->rigidbody.SetVelocityX(player->speed * player->lastDirection);
	}

	// ����
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
		break;
	case 1:
		player->currentSprite = &player->attack02Sprite;
		player->currentAnimation = &player->attack02Animation;
		break;
	case 2:
		player->currentSprite = &player->attack03Sprite;
		player->currentAnimation = &player->attack03Animation;
		break;
	}
}