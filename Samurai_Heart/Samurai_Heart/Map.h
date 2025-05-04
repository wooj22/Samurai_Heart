#pragma once

class Map{
public:
    float width, height;
    float worldWidth, worldHeight; // 맵의 실제 크기

    Map() = default;
    Map(float w, float h, float worldW, float worldH)
        : width(w), height(h), worldWidth(worldW), worldHeight(worldH) {}
    ~Map() = default;
};
