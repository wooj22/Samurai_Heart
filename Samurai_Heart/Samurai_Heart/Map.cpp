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
	for (int i = 0; i < widthImageCount; i++)
	{
		// 반복된 월드 위치 계산
		Vector2 worldPos = position;
		worldPos.x += i * width;

		// 카메라 좌표로 변환
		Vector2 drawPos = Camera::Get().WorldToCameraPos(worldPos);

		// draw
		RenderManager::Get().DrawImage(
			image,
			drawPos.x, drawPos.y,
			width, height
		);
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
	widthImageCount++; // 잘리는 영역
}

// Set ScreenPositiona
void Background::SetScreenPosition() 
{
	screenPosition = Camera::Get().WorldToCameraPos(position);
}


/*----------- Ground -----------*/
void Ground::Start()
{
	collider.SetTag(this->tag);
}

void Ground::Update()
{
	SetScreenPosition();

	// collider update
	collider.UpdateCollider(position, groundWidth, grouandHeight);
	collider.UpdateScreenCollider(screenPosition, groundWidth, grouandHeight);

	// debug
	//collider.PrintCollider();
}

void Ground::Render()
{
	for (int i = 0; i < widthImageCount; i++)
	{
		// 반복된 월드 위치 계산
		Vector2 worldPos = imagePosition;
		worldPos.x += i * imageWidth;

		// 카메라 좌표로 변환
		Vector2 drawPos = Camera::Get().WorldToCameraPos(worldPos);

		// draw
		RenderManager::Get().DrawImage(
			image,
			drawPos.x, drawPos.y,
			imageWidth, imageHeight
		);
	}

	collider.DrawCollider();
}

// Init
void Ground::Init(const wchar_t* path, Vector2 pos, Map* map)
{
	this->map = map;
	image = new Bitmap(path);

	// image
	imageWidth = image->GetWidth();
	imageHeight = image->GetHeight();
	imagePosition = pos;

	// ground
	groundWidth = map->worldWidth;
	grouandHeight = image->GetHeight();
	position = Vector2(map->worldWidth/2, pos.y + grouandHeight/2);

	// 가로 반복 횟수
	widthImageCount = map->worldWidth / imageWidth + 1; // 잘리는 영역
}

// Set ScreenPositiona
void Ground::SetScreenPosition()
{
	screenPosition = Camera::Get().WorldToCameraPos(position);
	imageScreenPosition = Camera::Get().WorldToCameraPos(imagePosition);
}