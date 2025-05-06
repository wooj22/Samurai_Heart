#include "Die.h"
#include <windows.h>

void Die::Enter() 
{
	OutputDebugStringA("[Player] Die Enter\n");

	// sprite & animation set
	player->currentSprite = &player->dieSprite;
	player->currentAnimation = &player->dieAnimation;

	player->rigidbody.SetVelocityX(0);
}

void Die::ChangeStateLogic()
{

}

void Die::UpdateLogic()
{
	// animation sprite update
	player->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
	Frame currentFrame = player->currentAnimation->GetCurrentFrame();
	player->currentSprite->SetFrameRect(currentFrame);
}

void Die::Render() 
{
	// animation render
	RenderManager::Get().DrawImageFilp(
		player->currentSprite->GetBitmap(), player->lastDirection,
		player->screenPosition.x - player->width / 2, player->screenPosition.y - player->height / 2,
		player->currentSprite->GetFrameRect().X, player->currentSprite->GetFrameRect().Y,
		player->width, player->height);
}

void Die::Exit() {
	OutputDebugStringA("[Player] Die Exit\n");
}