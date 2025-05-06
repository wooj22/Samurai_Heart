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
bool Camera::IsInViewByCenter(Vector2 worldCenterPos, float objWidth, float objHeight)
{
    float halfCamW = width / 2.f;
    float halfCamH = height / 2.f;

    float camLeft = position.x - halfCamW;
    float camRight = position.x + halfCamW;
    float camTop = position.y - halfCamH;
    float camBottom = position.y + halfCamH;

    float objLeft = worldCenterPos.x - objWidth / 2.f;
    float objRight = worldCenterPos.x + objWidth / 2.f;
    float objTop = worldCenterPos.y - objHeight / 2.f;
    float objBottom = worldCenterPos.y + objHeight / 2.f;

    return !(objRight < camLeft || objLeft > camRight ||
        objBottom < camTop || objTop > camBottom);
}

// 컬링 (left, top)
bool Camera::IsInViewByTopLeft(Vector2 worldTopLeftPos, float objWidth, float objHeight)
{
    float halfCamW = width / 2.f;
    float halfCamH = height / 2.f;

    float camLeft = position.x - halfCamW;
    float camRight = position.x + halfCamW;
    float camTop = position.y - halfCamH;
    float camBottom = position.y + halfCamH;

    float objLeft = worldTopLeftPos.x;
    float objRight = worldTopLeftPos.x + objWidth;
    float objTop = worldTopLeftPos.y;
    float objBottom = worldTopLeftPos.y + objHeight;

    return !(objRight < camLeft || objLeft > camRight ||
        objBottom < camTop || objTop > camBottom);
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