#include "Idle.h"
#include <windows.h>

void Idle::Enter() {
	OutputDebugStringA("[Player] Idle Enter\n");

	// sprite & animation set
	player->currentSprite = &player->idleSprite;
	player->currentAnimation = &player->idleAnimation;
}

void Idle::ChangeStateLogic() {
	
}

void Idle::UpdateLogic() {
	// animation update
	player->currentAnimation->UpdateFrame(TimeManager::Get().GetDeltaTime());
}

void Idle::Render() {
	// animation render
	RenderManager::Get().DrawImage(player->currentSprite->GetBitmap(), 
		1000, 500, 
		player->currentAnimation->GetCurrentFrame().x, player->currentAnimation->GetCurrentFrame().y,
		player->width, player->height);
}

void Idle::Exit() {
	OutputDebugStringA("[Player] Idle Exit\n");
}