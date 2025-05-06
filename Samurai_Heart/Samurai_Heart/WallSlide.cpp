#include "WallSlide.h"

void WallSlide::Enter() {
	OutputDebugStringA("[Player] WallSlide Enter\n");

	// sprite & animation set
	player->currentSprite = &player->wallSlideSprite;
	player->currentAnimation = &player->wallSlideAnimation;

	// wall direction
	float x = player->rigidbody.GetVelocityX();
	player->wallDirection = x<0 ? -1 : 1;

	// slide
	player->rigidbody.UseGravity(false);
	player->rigidbody.SetVelocityX(0);
	player->rigidbody.SetVelocityY(player->wallSlideSpeed);
}

void WallSlide::ChangeStateLogic() {
	// idle
	if (player->isGround) player->ChangeState(player->IDLE);

	// wall jump
	if (player->isJumpKey) player->ChangeState(player->WALL_JUMP);
}

void WallSlide::UpdateLogic() {
	// animation sprite update
	player->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = player->currentAnimation->GetCurrentFrame();
	player->currentSprite->SetFrameRect(currentFrame);
}

void WallSlide::Render() {
	// animation render
	RenderManager::Get().DrawImage(
		player->currentSprite->GetBitmap(),
		player->screenPosition.x - player->width / 2, player->screenPosition.y - player->height / 2,
		player->currentSprite->GetFrameRect().X, player->currentSprite->GetFrameRect().Y,
		player->width, player->height);
}

void WallSlide::Exit() {
	player->rigidbody.UseGravity(true);
	OutputDebugStringA("[Player] WallSlide Exit\n");
}