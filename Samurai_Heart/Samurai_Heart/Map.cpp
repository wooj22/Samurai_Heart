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
		// �ݺ��� ���� ��ġ ���
		Vector2 worldPos = position;
		worldPos.x += i * width;

		// ī�޶� ��ǥ�� ��ȯ
		Vector2 drawPos = Camera::Get().WorldToCameraPos(worldPos);

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

	// ���� �ݺ� Ƚ��
	widthImageCount = map->worldWidth / width;
	widthImageCount++; // �߸��� ����
}

// Set ScreenPositiona
void Background::SetScreenPosition() 
{
	screenPosition = Camera::Get().WorldToCameraPos(position);
}

/*----------- Ground -----------*/