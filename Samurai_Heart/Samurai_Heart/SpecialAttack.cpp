#include "SpecialAttack.h"
#include <windows.h>

void SpecialAttack::Enter() {
	OutputDebugStringA("[Player] SpecialAttack Enter\n");

	// flag
	player->isSpecialAttack = true;
	player->ChargeZero();

	// sprite & animation set
	player->currentSprite = &player->specialAttackSprite;
	player->currentAnimation = &player->specialAttackAnimation;

	// µ¹Áø
	if (player->isMoveLKey) player->rigidbody.SetVelocityX(-player->speed * 3.f);
	if (player->isMoveRKey) player->rigidbody.SetVelocityX(player->speed * 3.f);
}

void SpecialAttack::ChangeStateLogic() {
	// idle
	if (player->specialAttackAnimation.IsFinished())
		player->ChangeState(player->IDLE);
}

void SpecialAttack::UpdateLogic() {
	// animation sprite update
	player->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = player->currentAnimation->GetCurrentFrame();
	player->currentSprite->SetFrameRect(currentFrame);
}

void SpecialAttack::Render() {
	// animation render
	RenderManager::Get().DrawImage(
		player->currentSprite->GetBitmap(),
		player->screenPosition.x - player->width / 2, player->screenPosition.y - player->height / 2,
		player->currentSprite->GetFrameRect().X, player->currentSprite->GetFrameRect().Y,
		player->width, player->height);
}

void SpecialAttack::Exit() {
	player->isSpecialAttack = false;
	OutputDebugStringA("[Player] SpecialAttack Exit\n");
}