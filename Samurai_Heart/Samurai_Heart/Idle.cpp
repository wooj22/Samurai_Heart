#include "Idle.h"
#include <windows.h>

void Idle::Enter() {
	OutputDebugStringA("[Player] Idle Enter\n");

	// sprite & animation set
	player->currentSprite = &player->idleSprite;
	player->currentAnimation = &player->idleAnimation;
}

void Idle::ChangeStateLogic() {
	// run
	if (player->isMoveLKey || player->isMoveRKey)
		player->ChangeState(player->RUN);

	// jump
	if (player->isJumpKey)
		player->ChangeState(player->JUMP);
}

void Idle::UpdateLogic() {
	// gravity
	//player->GravityUpdate();

	// animation sprite update
	player->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = player->currentAnimation->GetCurrentFrame();
	player->currentSprite->SetFrameRect(currentFrame);
}

void Idle::Render() {
	// animation render
	RenderManager::Get().DrawImage(
		player->currentSprite->GetBitmap(), 
		player->screenPosition.x - player->width/2, player->screenPosition.y - player->height/2,
		player->currentSprite->GetFrameRect().X, player->currentSprite->GetFrameRect().Y,
		player->currentSprite->GetFrameRect().Width, player->currentSprite->GetFrameRect().Height);
}

void Idle::Exit() {
	OutputDebugStringA("[Player] Idle Exit\n");
}