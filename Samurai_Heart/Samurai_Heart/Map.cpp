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

	// ȭ���� ���� ũ�⿡ ���߾� ��� �̹��� ũ�� ����
	float scale = 600.f / height;  // ȭ���� ���� ũ�� (600)�� ��� �̹����� ���� ũ��� ������ ���� ���

	// ���� ũ�⿡ ���߾� ������ ���� ���� ũ��
	width = width * scale;
	height = 600.f;  // ���� ũ��� ȭ�� ũ��� ����

	position = pos;
}

// Set ScreenPosition
void Background::SetScreenPosition() 
{
	screenPosition = Camera::Get().WorldToCameraPos(position);
}

/*----------- Ground -----------*/