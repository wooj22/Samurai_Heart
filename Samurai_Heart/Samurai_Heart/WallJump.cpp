#include "WallJump.h"
#include <windows.h>


void WallJump::Enter()
{
	OutputDebugStringA("[Player] WallJump Enter\n");

	// flag set
	player->isWall = false;
	player->isJumping = true;

	// sprite set
	player->currentSprite = &player->wallJumpSprite;
	player->currentSprite->SetFullFrameRect();

	// jump
	player->rigidbody.SetVelocityY(-player->jumpPower);

	// jump x move
	if(player->MoveLKey)
		player->rigidbody.SetVelocityX(-player->speed * 1.2f);
	if (player->MoveRKey)
		player->rigidbody.SetVelocityX(player->speed * 1.2f);
}

void WallJump::ChangeStateLogic()
{
	// idle
	if (player->isGround) player->ChangeState(player->IDLE);

	// wall slide
	if (player->isWall) player->ChangeState(player->WALL_SLIDE);
}

void WallJump::UpdateLogic()
{
	
}

void WallJump::Render()
{
	// sprite render
	RenderManager::Get().DrawImage(
		player->currentSprite->GetBitmap(),
		player->screenPosition.x - player->width / 2, player->screenPosition.y - player->height / 2,
		player->width, player->height);
}

void WallJump::Exit()
{
	player->isJumping = false;
	OutputDebugStringA("[Player] WallJump Exit\n");
}