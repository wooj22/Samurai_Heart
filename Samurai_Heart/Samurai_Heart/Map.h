#pragma once
#include "../GameEngineLib/Object.h"
#include "BoxCollider.h"

/* Map 영역 */
class Map{
public:
    float width, height;            // 뷰포트 크기
    float worldWidth, worldHeight;  // 맵의 실제 크기

    Map(float w, float h, float worldW, float worldH)
        : width(w), height(h), worldWidth(worldW), worldHeight(worldH) {}
    ~Map() = default;
};

/* Bacgroudn Image */
class Background : public Object {
private:
    Vector2 position;
    Vector2 screenPosition;
    float width, height;
    Bitmap* image;         
    Map* map;
    int widthImageCount;
   
public:
    Background() = default;
    ~Background() { delete image; }

    void Start() override;
    void Update() override;
    void Render() override;

    void Init(const wchar_t* path, Vector2 pos, Map* map);
    void SetScreenPosition();
};


/* Ground */
class Ground : public Object {
private:
    Vector2 position;
    Vector2 screenPosition;
    float width, height;
    Bitmap* image;
    BoxCollider collider;

public:
    Ground(const wchar_t* path, Vector2 pos, float width_input, float height_input)
        : position(pos), width(width_input), height(height_input)
    {
        image = new Bitmap(path);
    }
    ~Ground() { delete image; }

    void Start() override;
    void Update() override;
    void Render() override;

    BoxCollider& GetCollider() { return collider; }
};