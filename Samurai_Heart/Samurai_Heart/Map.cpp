#include "Map.h"

/*----------- BackGround -----------*/
void Background::Start() 
{
	
}

void Background::Update() 
{
	SetScreenPosition();
}

void Background::Render() 
{
	float pos = 0;

	for (int i = 0; i < widthImageCount; i++) {
		RenderManager::Get().DrawImage(
			image,
			screenPosition.x + pos, screenPosition.y,
			width, height
		);

		pos += width;
	}
}

// Init
void Background::Init(const wchar_t* path, Vector2 pos, Map* map)
{
	// image load
	image = new Bitmap(path);

	// size
	width = image->GetWidth();
	height = image->GetHeight();

	// map height size scalse setting
	float scale = map->worldHeight / height;
	width = width * scale;
	height = map->worldHeight;

	// position
	position = pos;

	// 가로 반복 횟수
	widthImageCount = map->worldWidth / width;
}

// Set ScreenPosition
void Background::SetScreenPosition() 
{
	screenPosition = Camera::Get().WorldToCameraPos(position);
}

/*----------- Ground -----------*/