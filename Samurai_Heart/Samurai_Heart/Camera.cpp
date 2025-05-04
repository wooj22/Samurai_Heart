#include "Camera.h"
#include "Player.h"
#include "Map.h"

// Player 중심 고정
void Camera::FollowPlayer(Player* player, Map* map) {
    position.x = player->GetPosition().x - width / 2;
    position.y = player->GetPosition().y - height / 2;

    // 맵 경계
    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;

    if (position.x + width > map->worldWidth)
        position.x = map->worldWidth - width;
    if (position.y + height > map->worldHeight)
        position.y = map->worldHeight - height;
}

// 월드좌표 -> 카메라 좌표 반환
Vector2 Camera::WorldToCameraPos(Vector2 pos) {
    float camX = pos.x - position.x;
    float camY = pos.y - position.y;

    return Vector2(camX, camY);
}


// debug
float timer = 0;
float debugCoolTime = 0.5f;

void Camera::DebugPosition() {
    timer += TimeManager::Get().GetDeltaTime();

    if (timer >= debugCoolTime) {
        char buffer[128];
        sprintf_s(buffer, "[Camera] Position: (%.2f, %.2f)\n", position.x, position.y);
        OutputDebugStringA(buffer);

        timer = 0;
    }
}