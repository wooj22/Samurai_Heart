#pragma once
#include "../GameEngineLib/Singleton.h"
#include "../GameEngineLib/Vector2.h"
#include <windows.h>
#include <stdio.h>

class Map;
class Player;

class Camera : public Singleton<Camera>{
public:
    Vector2 position = (0,0);
    float width = 800;
    float height = 600;

    Camera() = default;
    Camera(Vector2 pos, float width_input, float height_input) :
        position(pos), width(width_input), height(height_input) {};
    ~Camera() = default;

    // position
    void SetPosition(Vector2 pos) { position = pos; }
    Vector2 GetPosition() { return position; }

    // size
    void SetSize(float width_input, float height_input) {
        width = width_input;
        height = height_input;
    }


    void FollowPlayer(Player* player, Map* map);
    Vector2 WorldToCameraPos(Vector2 worldPos);
    bool IsInViewByCenter(Vector2 worldCenterPos, float objWidth, float objHeight);
    bool IsInViewByTopLeft(Vector2 worldTopLeftPos, float objWidth, float objHeight);

    // debug
    void DebugPosition();
};