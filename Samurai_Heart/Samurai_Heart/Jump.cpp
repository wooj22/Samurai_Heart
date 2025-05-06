#include "Jump.h"
#include <windows.h>

void Jump::Enter() {
	OutputDebugStringA("[Player] Jump Enter\n");

	// flag set
	player->isJumping = true;
	player->isGround = false;

	// sprite & animation set
	player->currentSprite = &player->jumpSprite;
	player->currentAnimation = &player->jumpAnimation;

	// jump (1회)
	player->rigidbody.SetVelocityY(-player->jumpPower);

	// sound
	SoundManager::Get().PlaySFX("../Resource/Sound/SFX_Jump.mp3");
}

void Jump::ChangeStateLogic() {
	// idle
	if (player->isGround) player->ChangeState(player->IDLE);

	// wall
	if (player->isWall) player->ChangeState(player->WALL_SLIDE);
}

void Jump::UpdateLogic() {
	// animation sprite update
	player->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = player->currentAnimation->GetCurrentFrame();
	player->currentSprite->SetFrameRect(currentFrame);
}

void Jump::Render() {
	// animation render
	RenderManager::Get().DrawImageFilp(
		player->currentSprite->GetBitmap(), player->lastDirection,
		player->screenPosition.x - player->width / 2, player->screenPosition.y - player->height / 2,
		player->currentSprite->GetFrameRect().X, player->currentSprite->GetFrameRect().Y,
		player->width, player->height);
}

void Jump::Exit() {
	// flag set
	player->isJumping = false;

	OutputDebugStringA("[Player] Jump Exit\n");
}