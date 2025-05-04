#pragma once

class Map{
public:
    float width, height;
    float worldWidth, worldHeight; // ���� ���� ũ��

    Map() = default;
    Map(float w, float h, float worldW, float worldH)
        : width(w), height(h), worldWidth(worldW), worldHeight(worldH) {}
    ~Map() = default;
};
