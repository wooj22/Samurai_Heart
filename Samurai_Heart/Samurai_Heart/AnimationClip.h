#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/* Frame Struct */
// atlas data (left, top, width, height)
struct Frame
{
	int x, y, width, height;
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

    // Load Frame Data From File
    void LoadFrameDataFromFile(const string& filePath) {
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

            // �Ľ�
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
    void AddFrame(const Frame& frame) { frames.push_back(frame); }

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
        if (frames.empty()) return Frame();
        return frames[currentFrame];
    }

    // Animation Finished return
    bool IsFinished() {
        return (currentFrame == static_cast<int>(frames.size()) - 1 && timer == 0.0f);
    }

	// Reset Animation
    void Reset()
    {
        timer = 0.0f;
        currentFrame = 0;
    }
};

