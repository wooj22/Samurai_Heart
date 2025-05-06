#include "WallJump.h"
#include <windows.h>


void WallJump::Enter()
{
	OutputDebugStringA("[Player] WallJump Enter\n");
	
	// timer
	timer = 0;

	// flag set
	player->isWall = false;
	player->isJumping = true;

	// sprite set
	player->currentSprite = &player->wallJumpSprite;
	player->currentSprite->SetFullFrameRect();

	// jump
	player->rigidbody.SetVelocityY(-player->jumpPower);	

	player->lastDirection = -player->wallDirection; // wall의 반대 방향
	player->rigidbody.SetVelocityX(player->speed * 1.2f * player->lastDirection);	

	// sound
	SoundManager::Get().PlaySFX("../Resource/Sound/SFX_Jump.mp3");
}

void WallJump::ChangeStateLogic()
{
	// idle
	if (player->isGround) player->ChangeState(player->IDLE);

	// wall slide
	if (timer >= cheakTime) {
		if (player->isWall) player->ChangeState(player->WALL_SLIDE);
	}
}

void WallJump::UpdateLogic()
{
	timer += TimeManager::Get().GetDeltaTime();
}

void WallJump::Render()
{
	// sprite render
	RenderManager::Get().DrawImageFilp(
		player->currentSprite->GetBitmap(),player->lastDirection,
		player->screenPosition.x - player->width / 2, player->screenPosition.y - player->height / 2,
		player->width, player->height);
}

void WallJump::Exit()
{
	player->isJumping = false;
	OutputDebugStringA("[Player] WallJump Exit\n");
}