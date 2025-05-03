#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

/* Frame Struct */
struct Frame
{
	int x, y, width, height;     // atlas data (left, top, width, height)
	Frame() = default;
    Frame(int x, int y, int width, int height, float duration)
        : x(x), y(y), width(width), height(height) {}
};

/* Animation Class */
class AnimationClip
{
private:
    vector<Frame> frames;  // �� �ִϸ��̼ǿ� ���Ե� �����ӵ�
    int currentFrame = 0;
	float frameDuration = 0.0f;
    float timer = 0.0f;

public:
	AnimationClip() = default;
	~AnimationClip() = default;

    // Load From File
    void LoadFromFile(const string& filePath) {
        ifstream file(filePath);
        string line;

        if (!file.is_open()) {
            cerr << "Failed to open file: " << filePath << std::endl;
            return;
        }

        // ù ��° ���� �ǳʶ� (���)
        std::getline(file, line);

        while (std::getline(file, line)) {
            istringstream ss(line);
            string token;
            Frame frame;

            // ù ��° �� (frame index)�� ����
            getline(ss, token, ',');

            // ���� ���� �ʿ��� ���� �Ľ�
            getline(ss, token, ','); frame.x = std::stoi(token);
            getline(ss, token, ','); frame.y = std::stoi(token);
            getline(ss, token, ','); frame.width = std::stoi(token);
            getline(ss, token, ','); frame.height = std::stoi(token);

            AddFrame(frame);
        }

        file.close();
    }

    // Set Frame Duration
    void SetFrameDuration(float duration) { frameDuration = duration; }

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

