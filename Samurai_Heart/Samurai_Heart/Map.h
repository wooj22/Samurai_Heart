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
    // transfrom
    Vector2 position;
    Vector2 screenPosition;
    float width, height;

    // image
    Bitmap* image;        

    // tileing
    //Map* map;
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
    string tag = "Ground";
    
    // transform (충돌 영역, center)
    Vector2 position;                   // 전체 ground 중심 position
    Vector2 screenPosition;             // 전체 ground screen position
    float groundWidth, grouandHeight;   // 전체 ground 영역

    // tileing transform (반복되는 각 이미지, left top)
    Vector2 imagePosition;              
    Vector2 imageScreenPosition;
    float imageWidth, imageHeight;      

    // image
    Bitmap* image;

    // collider -> isGround cheak
    BoxCollider collider;

    // tileing
    Map* map;
    int widthImageCount;

public:
    Ground() = default;
    ~Ground() { delete image; }

    void Start() override;
    void Update() override;
    void Render() override;

    void Init(const wchar_t* path, Vector2 pos, Map* map);
    void SetScreenPosition();
    string GetTag() { return tag; }
    BoxCollider GetCollider() { return collider; }
};