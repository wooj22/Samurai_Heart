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
	/*RenderManager::Get().DrawImage(
		image, screenPosition.x, screenPosition.y);*/

	RenderManager::Get().DrawImage(
		image,
		screenPosition.x,
		screenPosition.y,
		width,
		height
	);
}

// Init - bitmap, size, pos
void Background::Init(const wchar_t* path, Vector2 pos)
{
	image = new Bitmap(path);

	if (image->GetLastStatus() != Ok) {
		OutputDebugStringA("Failed to load background image\n");
		delete image;
		image = nullptr;
	}

	width = image->GetWidth();
	height = image->GetHeight();

	// 화면의 세로 크기에 맞추어 배경 이미지 크기 변경
	float scale = 600.f / height;  // 화면의 세로 크기 (600)를 배경 이미지의 세로 크기로 나누어 비율 계산

	// 세로 크기에 맞추어 비율을 맞춘 가로 크기
	width = width * scale;
	height = 600.f;  // 세로 크기는 화면 크기로 고정

	position = pos;
}

// Set ScreenPosition
void Background::SetScreenPosition() 
{
	screenPosition = Camera::Get().WorldToCameraPos(position);
}

/*----------- Ground -----------*/