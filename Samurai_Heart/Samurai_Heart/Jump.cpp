#include "Jump.h"
#include <windows.h>

void Jump::Enter() {
	OutputDebugStringA("[Player] Jump Enter\n");

	// flag set
	player->isJumping = true;

	// sprite & animation set
	player->currentSprite = &player->jumpDownSprite;
	player->currentAnimation = &player->jumpDownAnimation;
}

void Jump::ChangeStateLogic() {
	if (player->isGround) player->ChangeState(player->IDLE);

	// test
	if(InputManager::Get().GetKeyDown('J')) player->ChangeState(player->IDLE);
}

void Jump::UpdateLogic() {
	// animation sprite update
	player->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = player->currentAnimation->GetCurrentFrame();
	player->currentSprite->SetFrameRect(currentFrame);
}

void Jump::Render() {
	// animation render
	RenderManager::Get().DrawImage(
		player->currentSprite->GetBitmap(),
		player->screenPosition.x - player->width / 2, player->screenPosition.y - player->height / 2,
		player->currentSprite->GetFrameRect().X, player->currentSprite->GetFrameRect().Y,
		player->width, player->height);
}

void Jump::Exit() {
	// flag set
	player->isJumping = false;

	OutputDebugStringA("[Player] Jump Exit\n");
}