#include "Camera.h"
#include "Player.h"
#include "Map.h"

// Player 중심 고정
void Camera::FollowPlayer(Player* player, Map* map) {
    position.x = player->GetPosition().x - width / 2;
    position.y = player->GetPosition().y - height / 1.5;

    // 맵 경계
    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;

    if (position.x + width > map->worldWidth)
        position.x = map->worldWidth - width;
    if (position.y + height > map->worldHeight)
        position.y = map->worldHeight - height;
}

// 월드좌표 -> 카메라 좌표 반환
Vector2 Camera::WorldToCameraPos(Vector2 worldPos) {
    float camX = worldPos.x - position.x;
    float camY = worldPos.y - position.y;

    return Vector2(camX, camY);
}


// 컬링 (center)
bool Camera::IsInViewByCenter(Vector2 worldCenterPos, float objWidth, float objHeight, float margin)
{
    float left = position.x - margin;
    float right = position.x + this->width + margin;
    float top = position.y - margin;
    float bottom = position.y + this->height + margin;

    float halfW = width * 0.5f;
    float halfH = height * 0.5f;

    return (worldCenterPos.x + halfW >= left && worldCenterPos.x - halfW <= right &&
        worldCenterPos.y + halfH >= top && worldCenterPos.y - halfH <= bottom);
}

// 컬링 (left, top)
bool Camera::IsInViewByTopLeft(Vector2 worldTopLeftPos, float objWidth, float objHeight, float margin)
{
    float left = position.x - margin;
    float right = position.x + this->width + margin;
    float top = position.y - margin;
    float bottom = position.y + this->height + margin;

    return (worldTopLeftPos.x + width >= left && worldTopLeftPos.x <= right &&
        worldTopLeftPos.y + height >= top && worldTopLeftPos.y <= bottom);
}

// debug
float timer = 0;
float debugCoolTime = 1.f;

void Camera::DebugPosition() {
    timer += TimeManager::Get().GetDeltaTime();

    if (timer >= debugCoolTime) {
        char buffer[128];
        sprintf_s(buffer, "[Camera] Position: (%.2f, %.2f)\n", position.x, position.y);
        OutputDebugStringA(buffer);

        timer = 0;
    }
}