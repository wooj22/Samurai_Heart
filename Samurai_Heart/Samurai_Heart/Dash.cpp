#include "Dash.h"
#include <windows.h>

void Dash::Enter() 
{
	OutputDebugStringA("[Player] Dash Enter\n");

	// sprite set
	player->currentSprite = &player->dashSprite;
	player->currentSprite->SetFullFrameRect();

	// gravity X
	player->rigidbody.UseGravity(false);

	// dash
	player->rigidbody.SetVelocityX(player->dashSpeed * player->lastDirection);
}

void Dash::ChangeStateLogic() 
{
	// idle
	if (player->dashTimer >= player->dashTime)
		player->ChangeState(player->IDLE);
}

void Dash::UpdateLogic() 
{
	player->dashTimer += TimeManager::Get().GetDeltaTime();
}

void Dash::Render() 
{
	// sprite render
	RenderManager::Get().DrawImageFilp(
		player->currentSprite->GetBitmap(), player->lastDirection,
		player->screenPosition.x - player->width / 2, player->screenPosition.y - player->height / 2,
		player->width, player->height);
}

void Dash::Exit()
{
	player->isDash = false;
	player->dashTimer = 0;
	player->rigidbody.UseGravity(true);
	OutputDebugStringA("[Player] Dash Exit\n");
}