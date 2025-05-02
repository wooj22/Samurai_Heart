#pragma once
#include <vector>

/* Frame Struct */
struct Frame
{
	int x, y, width, height;     // atlas data (left, top, width, height)
    Frame(int x, int y, int width, int height, float duration)
        : x(x), y(y), width(width), height(height) {}
};

/* Animation Class */
class AnimationClip
{
private:
    std::vector<Frame> frames;  // 한 애니메이션에 포함된 프레임들
    int currentFrame = 0;
	float frameDuration = 0.0f;
    float timer = 0.0f;

public:
	AnimationClip() = default;
	~AnimationClip() = default;

    // Add Frame (atlas data)
    void AddFrame(Frame& frame) { frames.push_back(frame); }

    // Frame Update
    void UpdateFrame(float deltaTime)
    {
        if (frames.empty()) return;

        timer += deltaTime;
        while (timer >= frameDuration)
        {
            currentFrame = (currentFrame + 1) % frames.size();
            timer = 0;
        }
    }

	// Get Current Frame
    Frame GetCurrentFrame()
    {
        if (frames.empty()) return Frame(0, 0, 0, 0, 0);
        return frames[currentFrame];
    }

	// Reset Animation
    void Reset()
    {
        timer = 0.0f;
        currentFrame = 0;
    }
};

