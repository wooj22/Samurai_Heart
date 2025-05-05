#include "Run.h"
#include <windows.h>

void Run::Enter() {
	OutputDebugStringA("[Player] Run Enter\n");

	// sprite & animation set
	player->currentSprite = &player->runSprite;
	player->currentAnimation = &player->runAnimation;
}

void Run::ChangeStateLogic() {
	// idle
	if (!player->isMoveLKey && !player->isMoveRKey)
		player->ChangeState(player->IDLE);

	// jump
	if (player->isJumpKey && player->isGround)
		player->ChangeState(player->JUMP);

	// dash
	if (player->isDash && player->isGround)
		player->ChangeState(player->DASH);

	// defense
	if (player->isDefenseKey && player->isGround)
		player->ChangeState(player->DEFENSE);

	// attack
	if (player->isAttackKey && player->isGround)
		player->ChangeState(player->ATTACK);
}

void Run::UpdateLogic() {
	// test
	if (player->isMoveRKey) player->rigidbody.SetVelocityX(player->speed);
	if (player->isMoveLKey) player->rigidbody.SetVelocityX(-player->speed);

	// animation sprite update
	player->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = player->currentAnimation->GetCurrentFrame();
	player->currentSprite->SetFrameRect(currentFrame);
}

void Run::Render() {
	// animation render
	RenderManager::Get().DrawImage(
		player->currentSprite->GetBitmap(),
		player->screenPosition.x - player->width / 2, player->screenPosition.y - player->height / 2,
		player->currentSprite->GetFrameRect().X, player->currentSprite->GetFrameRect().Y,
		player->width, player->height);
}

void Run::Exit() {
	OutputDebugStringA("[Player] Run Exit\n");
}