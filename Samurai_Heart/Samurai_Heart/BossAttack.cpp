#include "BossAttack.h"
#include <windows.h>

void BossAttack::Enter()
{
	// sprite & animation set
	comboStep = 0;
	SetAttackAnimation(comboStep);
	boss->currentAnimation->Reset();

	boss->rigidbody.SetVelocityX(0);
}

void BossAttack::ChangeStateLogic()
{
	// 공격 끝나고
	if (boss->currentAnimation->IsFinished()) {
		// run (trace)
		if (boss->distance > boss->attackLimit) boss->ChangeState(boss->RUN);

		// idle
		if (boss->distance > boss->traceLimit) boss->ChangeState(boss->IDLE);
	}
}

void BossAttack::UpdateLogic()
{
	// attack animation change
	// 한 공격 애니메이션이 시작되는 지점
	if (boss->currentAnimation->IsFinished()) {
		// animation
		comboStep++;
		SetAttackAnimation(comboStep);
		boss->currentAnimation->Reset();
		comboStep = comboStep == 1 ? -1 : comboStep;

		// attack
		boss->DoAttack();
	}

	// animation sprite update
	boss->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = boss->currentAnimation->GetCurrentFrame();
	boss->currentSprite->SetFrameRect(currentFrame);
}

void BossAttack::Render()
{
	// animation render
	RenderManager::Get().DrawImageFilp(
		boss->currentSprite->GetBitmap(), boss->direction,
		boss->screenPosition.x - boss->width / 2, boss->screenPosition.y - boss->height / 2,
		boss->currentSprite->GetFrameRect().X, boss->currentSprite->GetFrameRect().Y,
		boss->currentSprite->GetFrameRect().Width, boss->currentSprite->GetFrameRect().Height);

}

void BossAttack::Exit()
{

}


// Set Attack Animation
void BossAttack::SetAttackAnimation(int combo)
{
	switch (combo)
	{
	case 0:
		boss->currentSprite = &boss->attack01Sprite;
		boss->currentAnimation = &boss->attack01Animation;
		break;
	case 1:
		boss->currentSprite = &boss->attack02Sprite;
		boss->currentAnimation = &boss->attack02Animation;
		break;
	}
}