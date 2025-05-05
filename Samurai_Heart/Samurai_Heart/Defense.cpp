#include "Defense.h"
#include <windows.h>

void Defense::Enter() 
{
	OutputDebugStringA("[Player] Defense Enter\n");
	
	// flag set
	player->isDefense = true;

	// sprite set
	player->currentSprite = &player->DefenseSprite;
	player->currentSprite->SetFullFrameRect();

	player->rigidbody.SetVelocity((0, 0));
}

void Defense::ChangeStateLogic() 
{
	// idle
	if (!player->isDefenseKey) player->ChangeState(player->IDLE);
}

void Defense::UpdateLogic() 
{

}

void Defense::Render() 
{
	// sprite render
	RenderManager::Get().DrawImage(
		player->currentSprite->GetBitmap(),
		player->screenPosition.x - player->width / 2, player->screenPosition.y - player->height / 2,
		player->width, player->height);
}

void Defense::Exit() {
	player->isDefense = false;
	OutputDebugStringA("[Player] Defense Exit\n");
}